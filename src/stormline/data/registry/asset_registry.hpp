#ifndef STORMLINE_DATA_REGISTRY_ASSET_REGISTRY_HPP
#define STORMLINE_DATA_REGISTRY_ASSET_REGISTRY_HPP

#include "stormline/data/registry/registry_types.hpp"

#include <array>
#include <limits>

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
    std::array<AssetRecord, kMaxAssets> assets_{};
    u32 size_{0};
};

}  // namespace stormline::data::registry

#endif  // STORMLINE_DATA_REGISTRY_ASSET_REGISTRY_HPP
