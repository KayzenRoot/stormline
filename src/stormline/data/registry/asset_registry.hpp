#ifndef STORMLINE_DATA_REGISTRY_ASSET_REGISTRY_HPP
#define STORMLINE_DATA_REGISTRY_ASSET_REGISTRY_HPP

#include "stormline/data/registry/registry_types.hpp"

#include <array>
#include <limits>
#include <span>

namespace stormline::data::registry {

class AssetRegistry final {
public:
    AssetRegistry() noexcept = default;

    [[nodiscard]] RegistryError add(const AssetRecord& record) noexcept {
        if (!valid(record.id)) {
            return RegistryError::InvalidId;
        }
        if (!valid(record.project) || record.status != AssetStatus::Active
            || record.revision != 1 || record.schema_version != 0) {
            return RegistryError::InvalidArgument;
        }
        vfs::VfsPath path{};
        if (record.path.length > vfs::kMaxPathBytes) {
            return RegistryError::InvalidPath;
        }
        if (vfs::make_path(vfs::view(record.path), path) != vfs::VfsError::None) {
            return RegistryError::InvalidPath;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (assets_[index].id.high == record.id.high
                && assets_[index].id.low == record.id.low) {
                return RegistryError::DuplicateId;
            }
            if (assets_[index].project.value == record.project.value
                && vfs::view(assets_[index].path) == vfs::view(path)) {
                return RegistryError::DuplicatePath;
            }
        }
        if (size_ >= kMaxAssets) {
            return RegistryError::CapacityFull;
        }
        AssetRecord stored = record;
        stored.path = path;
        assets_[size_] = stored;
        ++size_;
        return RegistryError::None;
    }

    [[nodiscard]] RegistryError find(AssetId id, AssetRecord& out) const noexcept {
        for (u32 index = 0; index < size_; ++index) {
            if (assets_[index].id.high != id.high || assets_[index].id.low != id.low) {
                continue;
            }
            out = assets_[index];
            return out.status == AssetStatus::Active
                ? RegistryError::None
                : RegistryError::Tombstoned;
        }
        return RegistryError::NotFound;
    }

    [[nodiscard]] RegistryError find_by_path(
        ProjectId project, const vfs::VfsPath& path, AssetId& out) const noexcept {
        if (!valid(project) || path.length > vfs::kMaxPathBytes) {
            return RegistryError::InvalidArgument;
        }
        for (u32 index = 0; index < size_; ++index) {
            const AssetRecord& asset = assets_[index];
            if (asset.project.value != project.value
                || vfs::view(asset.path) != vfs::view(path)) {
                continue;
            }
            out = asset.id;
            return asset.status == AssetStatus::Active
                ? RegistryError::None
                : RegistryError::Tombstoned;
        }
        return RegistryError::NotFound;
    }

    [[nodiscard]] bool at(u32 index, AssetRecord& out) const noexcept {
        if (index >= size_) {
            return false;
        }
        out = assets_[index];
        return true;
    }

    enum class DependencyKind : std::uint8_t { Runtime, Build, Editor };

    struct DependencyEdge {
        AssetId from{};
        AssetId to{};
        DependencyKind kind{DependencyKind::Runtime};
    };

    [[nodiscard]] RegistryError add_dependency(const DependencyEdge& edge) noexcept {
        if (!valid(edge.from) || !valid(edge.to)
            || static_cast<std::uint8_t>(edge.kind)
                > static_cast<std::uint8_t>(DependencyKind::Editor)) {
            return RegistryError::InvalidArgument;
        }
        if (edge.from.high == edge.to.high && edge.from.low == edge.to.low) {
            return RegistryError::DependencyCycle;
        }
        AssetRecord source{};
        const RegistryError source_status = find(edge.from, source);
        if (source_status != RegistryError::None) {
            return source_status;
        }
        for (u32 index = 0; index < dependency_count_; ++index) {
            const DependencyEdge& existing = edges_[index];
            if (same_id(existing.from, edge.from) && same_id(existing.to, edge.to)
                && existing.kind == edge.kind) {
                return RegistryError::None;
            }
        }
        if (dependency_count_ >= kMaxDependencies) {
            return RegistryError::CapacityFull;
        }
        if (reaches(edge.to, edge.from)) {
            return RegistryError::DependencyCycle;
        }
        edges_[dependency_count_] = edge;
        ++dependency_count_;
        return RegistryError::None;
    }

    [[nodiscard]] RegistryError remove_dependency(
        AssetId from, AssetId to, DependencyKind kind) noexcept {
        if (!valid(from) || !valid(to)) {
            return RegistryError::InvalidArgument;
        }
        for (u32 index = 0; index < dependency_count_; ++index) {
            const DependencyEdge& edge = edges_[index];
            if (!same_id(edge.from, from) || !same_id(edge.to, to) || edge.kind != kind) {
                continue;
            }
            for (u32 next = index + 1; next < dependency_count_; ++next) {
                edges_[next - 1] = edges_[next];
            }
            --dependency_count_;
            return RegistryError::None;
        }
        return RegistryError::NotFound;
    }

    [[nodiscard]] bool has_dependency(
        AssetId from, AssetId to, DependencyKind kind) const noexcept {
        for (u32 index = 0; index < dependency_count_; ++index) {
            const DependencyEdge& edge = edges_[index];
            if (same_id(edge.from, from) && same_id(edge.to, to) && edge.kind == kind) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] RegistryError dependencies_of(
        AssetId from, std::span<AssetId> output, u32& out_count) const noexcept {
        out_count = 0;
        if (!valid(from)) {
            return RegistryError::InvalidArgument;
        }
        AssetRecord source{};
        const RegistryError source_status = find(from, source);
        if (source_status != RegistryError::None) {
            return source_status;
        }
        AssetId matches[kMaxDependencies]{};
        u32 count = 0;
        for (u32 index = 0; index < dependency_count_; ++index) {
            if (same_id(edges_[index].from, from)) {
                matches[count++] = edges_[index].to;
            }
        }
        return copy_sorted(matches, count, output, out_count);
    }

    [[nodiscard]] RegistryError dependents_of(
        AssetId to, std::span<AssetId> output, u32& out_count) const noexcept {
        out_count = 0;
        if (!valid(to)) {
            return RegistryError::InvalidArgument;
        }
        AssetId matches[kMaxDependencies]{};
        u32 count = 0;
        for (u32 index = 0; index < dependency_count_; ++index) {
            if (same_id(edges_[index].to, to)) {
                matches[count++] = edges_[index].from;
            }
        }
        return copy_sorted(matches, count, output, out_count);
    }

    struct Tag {
        std::array<char, kMaxTagBytes> bytes{};
        u32 length{0};
    };

    [[nodiscard]] static RegistryError make_tag(
        std::string_view text, Tag& out) noexcept {
        if (text.empty() || text.size() > kMaxTagBytes) {
            return RegistryError::InvalidTag;
        }
        Tag tag{};
        for (u32 index = 0; index < static_cast<u32>(text.size()); ++index) {
            const char byte = text[index];
            if (byte < 0x21 || byte > 0x7E || byte == '/'
                || byte == ':' || static_cast<unsigned char>(byte) == 0x5Cu) {
                return RegistryError::InvalidTag;
            }
            tag.bytes[index] = byte;
        }
        tag.length = static_cast<u32>(text.size());
        out = tag;
        return RegistryError::None;
    }

    [[nodiscard]] RegistryError add_tag(AssetId id, const Tag& tag) noexcept {
        if (!valid(id) || tag.length == 0 || tag.length > kMaxTagBytes) {
            return RegistryError::InvalidArgument;
        }
        AssetRecord asset{};
        const RegistryError asset_status = find(id, asset);
        if (asset_status != RegistryError::None) {
            return asset_status;
        }
        u32 count = 0;
        for (u32 index = 0; index < tag_count_; ++index) {
            if (!same_id(tags_[index].asset, id)) {
                continue;
            }
            ++count;
            if (same_tag(tags_[index].tag, tag)) {
                return RegistryError::None;
            }
        }
        if (count >= kMaxTagsPerAsset) {
            return RegistryError::CapacityFull;
        }
        if (tag_count_ >= kMaxAssets * kMaxTagsPerAsset) {
            return RegistryError::CapacityFull;
        }
        tags_[tag_count_] = TagEntry{id, tag};
        ++tag_count_;
        return RegistryError::None;
    }

    [[nodiscard]] RegistryError remove_tag(AssetId id, const Tag& tag) noexcept {
        if (!valid(id) || tag.length == 0) {
            return RegistryError::InvalidArgument;
        }
        AssetRecord asset{};
        const RegistryError asset_status = find(id, asset);
        if (asset_status != RegistryError::None) {
            return asset_status;
        }
        for (u32 index = 0; index < tag_count_; ++index) {
            if (!same_id(tags_[index].asset, id) || !same_tag(tags_[index].tag, tag)) {
                continue;
            }
            for (u32 next = index + 1; next < tag_count_; ++next) {
                tags_[next - 1] = tags_[next];
            }
            --tag_count_;
            return RegistryError::None;
        }
        return RegistryError::NotFound;
    }

    [[nodiscard]] bool has_tag(AssetId id, const Tag& tag) const noexcept {
        for (u32 index = 0; index < tag_count_; ++index) {
            if (same_id(tags_[index].asset, id) && same_tag(tags_[index].tag, tag)) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] RegistryError tags_of(
        AssetId id, std::span<Tag> output, u32& out_count) const noexcept {
        out_count = 0;
        if (!valid(id)) {
            return RegistryError::InvalidArgument;
        }
        AssetRecord asset{};
        const RegistryError asset_status = find(id, asset);
        if (asset_status != RegistryError::None) {
            return asset_status;
        }
        u32 required = 0;
        for (u32 index = 0; index < tag_count_; ++index) {
            if (same_id(tags_[index].asset, id)) {
                ++required;
            }
        }
        out_count = required;
        if (required > output.size()) {
            return RegistryError::BufferFull;
        }
        u32 written = 0;
        for (u32 index = 0; index < tag_count_; ++index) {
            if (same_id(tags_[index].asset, id)) {
                output[written++] = tags_[index].tag;
            }
        }
        return RegistryError::None;
    }

    [[nodiscard]] u32 dependency_count() const noexcept { return dependency_count_; }

    [[nodiscard]] u32 unresolved_dependencies() const noexcept {
        u32 unresolved = 0;
        for (u32 index = 0; index < dependency_count_; ++index) {
            AssetRecord target{};
            if (find(edges_[index].to, target) != RegistryError::None
                || target.status != AssetStatus::Active) {
                ++unresolved;
            }
        }
        return unresolved;
    }

    [[nodiscard]] RegistryError tombstone(AssetId id) noexcept {
        for (u32 index = 0; index < size_; ++index) {
            AssetRecord& asset = assets_[index];
            if (asset.id.high != id.high || asset.id.low != id.low) {
                continue;
            }
            if (asset.status == AssetStatus::Tombstoned) {
                return RegistryError::Tombstoned;
            }
            if (asset.revision == std::numeric_limits<u64>::max()) {
                return RegistryError::InternalFailure;
            }
            asset.status = AssetStatus::Tombstoned;
            ++asset.revision;
            return RegistryError::None;
        }
        return RegistryError::NotFound;
    }

    [[nodiscard]] u32 size() const noexcept { return size_; }

private:
    static bool same_id(AssetId lhs, AssetId rhs) noexcept {
        return lhs.high == rhs.high && lhs.low == rhs.low;
    }

    static bool same_tag(const Tag& lhs, const Tag& rhs) noexcept {
        if (lhs.length != rhs.length) {
            return false;
        }
        for (u32 index = 0; index < lhs.length; ++index) {
            if (lhs.bytes[index] != rhs.bytes[index]) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] bool reaches(AssetId start, AssetId target) const noexcept {
        AssetId stack[kMaxAssets]{};
        AssetId visited[kMaxAssets]{};
        u32 stack_size = 0;
        u32 visited_size = 0;
        stack[stack_size++] = start;
        while (stack_size > 0) {
            const AssetId current = stack[--stack_size];
            if (same_id(current, target)) {
                return true;
            }
            bool seen = false;
            for (u32 index = 0; index < visited_size; ++index) {
                if (same_id(visited[index], current)) {
                    seen = true;
                    break;
                }
            }
            if (seen) {
                continue;
            }
            if (visited_size < kMaxAssets) {
                visited[visited_size++] = current;
            }
            for (u32 index = 0; index < dependency_count_; ++index) {
                if (same_id(edges_[index].from, current) && stack_size < kMaxAssets) {
                    stack[stack_size++] = edges_[index].to;
                }
            }
        }
        return false;
    }

    static RegistryError copy_sorted(
        AssetId* matches, u32 count, std::span<AssetId> output,
        u32& out_count) noexcept {
        for (u32 index = 1; index < count; ++index) {
            const AssetId key = matches[index];
            u32 position = index;
            while (position > 0 && less(key, matches[position - 1])) {
                matches[position] = matches[position - 1];
                --position;
            }
            matches[position] = key;
        }
        u32 unique = 0;
        for (u32 index = 0; index < count; ++index) {
            if (unique == 0 || !same_id(matches[unique - 1], matches[index])) {
                matches[unique++] = matches[index];
            }
        }
        out_count = unique;
        if (unique > output.size()) {
            return RegistryError::BufferFull;
        }
        for (u32 index = 0; index < unique; ++index) {
            output[index] = matches[index];
        }
        return RegistryError::None;
    }

    struct TagEntry {
        AssetId asset{};
        Tag tag{};
    };

    std::array<AssetRecord, kMaxAssets> assets_{};
    std::array<DependencyEdge, kMaxDependencies> edges_{};
    std::array<TagEntry, kMaxAssets * kMaxTagsPerAsset> tags_{};
    u32 size_{0};
    u32 dependency_count_{0};
    u32 tag_count_{0};
};

}  // namespace stormline::data::registry

#endif  // STORMLINE_DATA_REGISTRY_ASSET_REGISTRY_HPP
