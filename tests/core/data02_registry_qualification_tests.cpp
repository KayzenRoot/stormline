#include "stormline/data/registry/asset_registry.hpp"

#include <array>
#include <cstdio>
#include <string>
#include <string_view>

namespace {
using namespace stormline::data::registry;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] AssetRecord record(
    u64 id, u64 project, std::string_view path, AssetKind kind) {
    AssetRecord value{};
    value.id = AssetId{0, id};
    value.project = ProjectId{project};
    value.kind = kind;
    (void)vfs::make_path(path, value.path);
    return value;
}

bool run_qlf_r01() {
    begin();
    AssetRegistry registry;
    expect(registry.add(record(1, 1, "art/a", AssetKind::Texture)) == RegistryError::None, "a");
    expect(registry.add(record(2, 1, "art/b", AssetKind::Material)) == RegistryError::None, "b");
    expect(registry.add(record(3, 1, "other/c", AssetKind::Mesh)) == RegistryError::None, "c");
    AssetRegistry::Tag hero{};
    expect(AssetRegistry::make_tag("hero", hero) == RegistryError::None, "tag");
    expect(registry.add_tag(AssetId{0, 1}, hero) == RegistryError::None, "tag add");
    std::array<AssetRegistry::MetadataEntry, 2> metadata{};
    expect(AssetRegistry::make_metadata_entry("id", "42", metadata[0]) == RegistryError::None,
           "meta id");
    expect(AssetRegistry::make_metadata_entry("kind", "texture", metadata[1])
           == RegistryError::None, "meta kind");
    expect(registry.set_metadata(AssetId{0, 1}, 1, metadata) == RegistryError::None, "meta set");
    const AssetRegistry::DependencyEdge edge{
        AssetId{0, 2}, AssetId{0, 1}, AssetRegistry::DependencyKind::Runtime};
    expect(registry.add_dependency(edge) == RegistryError::None, "edge");

    AssetRegistry::AssetQuery filter{};
    filter.project = ProjectId{1};
    filter.has_tag = true;
    filter.tag = hero;
    std::array<AssetId, 4> ids{};
    u32 count = 0;
    u32 next = 0;
    expect(registry.query(filter, ids, count, next) == RegistryError::None, "query tag");
    expect(count == 1 && ids[0].low == 1, "query tag id");

    AssetRegistry::AssetReference reference{};
    expect(AssetRegistry::make_reference(AssetId{0, 1}, AssetKind::Texture, 0, reference)
           == RegistryError::None, "reference");
    AssetRecord resolved{};
    expect(registry.resolve_reference(reference, resolved) == RegistryError::None,
           "resolve before");
    vfs::VfsPath moved{};
    expect(vfs::make_path("art/moved", moved) == vfs::VfsError::None, "moved path");
    expect(registry.rename(AssetId{0, 1}, moved) == RegistryError::None, "rename");
    expect(registry.resolve_reference(reference, resolved) == RegistryError::None
           && vfs::view(resolved.path) == "art/moved", "reference after rename");
    expect(registry.impact(AssetId{0, 1}, ids, count) == RegistryError::None
           && count == 1 && ids[0].low == 2, "impact");
    return finish();
}

struct Snapshot {
    u32 assets{0};
    u32 dependencies{0};
    u32 unresolved{0};
    std::array<AssetId, 4> query_ids{};
    u32 query_count{0};
    u32 tag_count{0};
    u32 metadata_count{0};
    u32 impact_count{0};
    std::array<AssetId, 4> impact_ids{};
    bool rename_visible{false};
};

[[nodiscard]] bool snapshot(Snapshot& out) {
    AssetRegistry registry;
    if (registry.add(record(1, 1, "art/a", AssetKind::Texture)) != RegistryError::None
        || registry.add(record(2, 1, "art/b", AssetKind::Material)) != RegistryError::None
        || registry.add(record(3, 1, "other/c", AssetKind::Mesh)) != RegistryError::None) {
        return false;
    }
    AssetRegistry::Tag hero{};
    if (AssetRegistry::make_tag("hero", hero) != RegistryError::None
        || registry.add_tag(AssetId{0, 1}, hero) != RegistryError::None) {
        return false;
    }
    std::array<AssetRegistry::MetadataEntry, 1> metadata{};
    if (AssetRegistry::make_metadata_entry("id", "42", metadata[0]) != RegistryError::None
        || registry.set_metadata(AssetId{0, 1}, 1, metadata) != RegistryError::None) {
        return false;
    }
    const AssetRegistry::DependencyEdge edge{
        AssetId{0, 2}, AssetId{0, 1}, AssetRegistry::DependencyKind::Runtime};
    if (registry.add_dependency(edge) != RegistryError::None) {
        return false;
    }
    out.assets = registry.size();
    out.dependencies = registry.dependency_count();
    out.unresolved = registry.unresolved_dependencies();
    AssetRegistry::AssetQuery filter{};
    filter.project = ProjectId{1};
    filter.has_tag = true;
    filter.tag = hero;
    u32 next = 0;
    if (registry.query(filter, out.query_ids, out.query_count, next) != RegistryError::None) {
        return false;
    }
    std::array<AssetRegistry::Tag, kMaxTagsPerAsset> tags{};
    if (registry.tags_of(AssetId{0, 1}, tags, out.tag_count) != RegistryError::None) {
        return false;
    }
    std::array<AssetRegistry::MetadataEntry, kMaxMetadataEntriesPerAsset> metadata_out{};
    if (registry.metadata(AssetId{0, 1}, metadata_out, out.metadata_count)
        != RegistryError::None) {
        return false;
    }
    if (registry.impact(AssetId{0, 1}, out.impact_ids, out.impact_count)
        != RegistryError::None) {
        return false;
    }
    vfs::VfsPath moved{};
    if (vfs::make_path("art/moved", moved) != vfs::VfsError::None
        || registry.rename(AssetId{0, 1}, moved) != RegistryError::None) {
        return false;
    }
    AssetRecord resolved{};
    out.rename_visible = registry.find(AssetId{0, 1}, resolved) == RegistryError::None
        && vfs::view(resolved.path) == "art/moved";
    return true;
}

bool run_qlf_r02() {
    begin();
    Snapshot first{};
    Snapshot second{};
    expect(snapshot(first), "first");
    expect(snapshot(second), "second");
    expect(first.assets == second.assets, "assets repeat");
    expect(first.dependencies == second.dependencies, "deps repeat");
    expect(first.unresolved == second.unresolved, "unresolved repeat");
    expect(first.query_count == second.query_count, "query count repeat");
    bool same_query = true;
    for (u32 index = 0; index < 4; ++index) {
        same_query = same_query && first.query_ids[index].high == second.query_ids[index].high
            && first.query_ids[index].low == second.query_ids[index].low;
    }
    expect(same_query, "query ids repeat");
    expect(first.impact_count == second.impact_count, "impact count repeat");
    bool same_impact = true;
    for (u32 index = 0; index < 4; ++index) {
        same_impact = same_impact && first.impact_ids[index].high == second.impact_ids[index].high
            && first.impact_ids[index].low == second.impact_ids[index].low;
    }
    expect(same_impact, "impact ids repeat");
    expect(first.rename_visible == second.rename_visible, "rename repeat");
    return finish();
}

bool run_qlf_r03() {
    begin();
    AssetRegistry registry;
    expect(registry.add(record(1, 1, "a", AssetKind::Texture)) == RegistryError::None, "add");
    expect(registry.add(record(1, 1, "a", AssetKind::Texture)) == RegistryError::DuplicateId,
           "duplicate id");
    expect(registry.add(record(2, 1, "b", AssetKind::Mesh)) == RegistryError::None,
           "after duplicate");
    expect(registry.add(record(3, 1, "a", AssetKind::Mesh)) == RegistryError::DuplicatePath,
           "duplicate path");
    expect(registry.add(record(4, 1, "d", AssetKind::Mesh)) == RegistryError::None,
           "after path");

    expect(registry.rename(AssetId{0, 9}, record(9, 1, "x", AssetKind::Mesh).path)
           == RegistryError::NotFound, "rename missing");
    vfs::VfsPath moved{};
    expect(vfs::make_path("moved", moved) == vfs::VfsError::None, "moved");
    expect(registry.rename(AssetId{0, 1}, moved) == RegistryError::None,
           "rename after missing");

    const AssetRegistry::DependencyEdge self{
        AssetId{0, 1}, AssetId{0, 1}, AssetRegistry::DependencyKind::Runtime};
    expect(registry.add_dependency(self) == RegistryError::DependencyCycle, "self cycle");
    const AssetRegistry::DependencyEdge valid{
        AssetId{0, 2}, AssetId{0, 1}, AssetRegistry::DependencyKind::Runtime};
    expect(registry.add_dependency(valid) == RegistryError::None, "edge after cycle");

    AssetRegistry::Tag bad{};
    expect(AssetRegistry::make_tag("bad tag", bad) == RegistryError::InvalidTag, "bad tag");
    expect(AssetRegistry::make_tag("good", bad) == RegistryError::None, "good tag");
    expect(registry.add_tag(AssetId{0, 1}, bad) == RegistryError::None, "tag after bad");

    AssetRegistry::MetadataEntry entry{};
    expect(AssetRegistry::make_metadata_entry("bad key", "v", entry)
           == RegistryError::InvalidArgument, "bad key");
    expect(AssetRegistry::make_metadata_entry("good", "v", entry) == RegistryError::None,
           "good key");
    expect(registry.set_metadata(AssetId{0, 1}, 1, std::span(&entry, 1))
           == RegistryError::None, "metadata after bad");

    AssetRegistry::AssetQuery filter{};
    filter.project = ProjectId{};
    std::array<AssetId, 2> ids{};
    u32 count = 0;
    u32 next = 0;
    expect(registry.query(filter, ids, count, next) == RegistryError::InvalidArgument,
           "bad query");
    filter.project = ProjectId{1};
    expect(registry.query(filter, ids, count, next) == RegistryError::None, "query after bad");

    AssetRegistry::AssetReference reference{};
    reference = AssetRegistry::AssetReference{AssetId{0, 1}, AssetKind::Mesh, 0};
    AssetRecord resolved{};
    expect(registry.resolve_reference(reference, resolved) == RegistryError::InvalidArgument,
           "kind mismatch");
    reference.expected_kind = AssetKind::Texture;
    expect(registry.resolve_reference(reference, resolved) == RegistryError::None,
           "reference after mismatch");
    return finish();
}

bool run_qlf_r04() {
    begin();
    AssetRegistry registry;
    u32 added = 0;
    for (u32 index = 0; index < 10000; ++index) {
        const RegistryError status =
            registry.add(record(index + 1, 1, "fill/" + std::to_string(index),
                                AssetKind::Texture));
        if (status == RegistryError::None) {
            ++added;
        } else {
            expect(status == RegistryError::CapacityFull, "add overload");
        }
    }
    expect(added == kMaxAssets, "asset capacity");
    expect(registry.size() == kMaxAssets, "asset size stable");

    u32 edges = 0;
    u32 attempts = 0;
    for (u32 target = 1; target < kMaxAssets && attempts < 10000; ++target) {
        for (u32 kind = 0; kind < 3 && attempts < 10000; ++kind) {
            const AssetRegistry::DependencyEdge edge{
                AssetId{0, 1}, AssetId{0, target + 1},
                static_cast<AssetRegistry::DependencyKind>(kind)};
            const RegistryError status = registry.add_dependency(edge);
            ++attempts;
            if (status == RegistryError::None) {
                ++edges;
            } else {
                expect(status == RegistryError::CapacityFull, "edge overload");
            }
        }
    }
    expect(edges == kMaxDependencies, "edge capacity");
    expect(registry.dependency_count() == kMaxDependencies, "edge size stable");

    AssetRegistry::Tag tag{};
    u32 tags = 0;
    for (u32 index = 0; index < 10000; ++index) {
        expect(AssetRegistry::make_tag("t" + std::to_string(index), tag)
               == RegistryError::None, "tag path");
        const RegistryError status = registry.add_tag(AssetId{0, 1}, tag);
        if (status == RegistryError::None) {
            ++tags;
        } else {
            expect(status == RegistryError::CapacityFull, "tag overload");
        }
    }
    expect(tags == kMaxTagsPerAsset, "tag capacity");

    std::array<AssetRegistry::MetadataEntry, 9> nine{};
    for (u32 index = 0; index < 9; ++index) {
        expect(AssetRegistry::make_metadata_entry("k" + std::to_string(index), "v", nine[index])
               == RegistryError::None, "meta fill");
    }
    for (u32 index = 0; index < 10000; ++index) {
        expect(registry.set_metadata(AssetId{0, 1}, 1, nine) == RegistryError::CapacityFull,
               "meta overload");
    }

    AssetRegistry::AssetQuery filter{};
    filter.project = ProjectId{1};
    std::array<AssetId, kMaxAssets> ids{};
    u32 count = 0;
    u32 next = 0;
    for (u32 index = 0; index < 10000; ++index) {
        expect(registry.query(filter, ids, count, next) == RegistryError::None,
               "query overload");
        if (count != kMaxAssets || next != 0) {
            expect(false, "query stable");
            break;
        }
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data02_registry_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") { success = run_qlf_r01(); }
    else if (mode == "qlf02") { success = run_qlf_r02(); }
    else if (mode == "qlf03") { success = run_qlf_r03(); }
    else if (mode == "qlf04") { success = run_qlf_r04(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
