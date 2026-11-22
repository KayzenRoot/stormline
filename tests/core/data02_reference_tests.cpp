#include "stormline/data/registry/asset_registry.hpp"

#include <array>
#include <cstdio>
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

[[nodiscard]] AssetRecord record(u64 id, std::string_view path, AssetKind kind) {
    AssetRecord value{};
    value.id = AssetId{0, id};
    value.project = ProjectId{1};
    value.kind = kind;
    (void)vfs::make_path(path, value.path);
    return value;
}

bool run_ref01() {
    begin();
    AssetRegistry registry;
    expect(registry.add(record(1, "art/a", AssetKind::Texture)) == RegistryError::None, "a");
    expect(registry.add(record(2, "art/b", AssetKind::Material)) == RegistryError::None, "b");
    expect(registry.add(record(3, "art/c", AssetKind::Scene)) == RegistryError::None, "c");
    expect(registry.add(record(4, "art/d", AssetKind::Mesh)) == RegistryError::None, "d");

    AssetRegistry::AssetReference reference{};
    expect(AssetRegistry::make_reference(AssetId{0, 1}, AssetKind::Texture, 7, reference)
           == RegistryError::None, "make ref");
    AssetRecord resolved{};
    expect(registry.resolve_reference(reference, resolved) == RegistryError::None, "resolve");
    expect(resolved.id.low == 1 && resolved.kind == AssetKind::Texture, "resolve value");
    reference.expected_kind = AssetKind::Mesh;
    expect(registry.resolve_reference(reference, resolved) == RegistryError::InvalidArgument,
           "kind mismatch");
    reference.asset = AssetId{0, 9};
    expect(registry.resolve_reference(reference, resolved) == RegistryError::NotFound,
           "missing ref");
    expect(AssetRegistry::make_reference(AssetId{}, AssetKind::Unknown, 0, reference)
           == RegistryError::InvalidId, "invalid ref");

    const AssetRegistry::DependencyEdge ba{
        AssetId{0, 2}, AssetId{0, 1}, AssetRegistry::DependencyKind::Runtime};
    const AssetRegistry::DependencyEdge cb{
        AssetId{0, 3}, AssetId{0, 2}, AssetRegistry::DependencyKind::Runtime};
    const AssetRegistry::DependencyEdge dc{
        AssetId{0, 4}, AssetId{0, 3}, AssetRegistry::DependencyKind::Runtime};
    expect(registry.add_dependency(ba) == RegistryError::None, "ba");
    expect(registry.add_dependency(cb) == RegistryError::None, "cb");
    expect(registry.add_dependency(dc) == RegistryError::None, "dc");

    std::array<AssetId, 4> output{};
    u32 count = 0;
    expect(registry.impact(AssetId{0, 1}, output, count) == RegistryError::None, "impact");
    expect(count == 3 && output[0].low == 2 && output[1].low == 3 && output[2].low == 4,
           "impact transitive sorted");
    std::array<AssetId, 2> small{};
    expect(registry.impact(AssetId{0, 1}, small, count) == RegistryError::BufferFull,
           "impact small");
    expect(count == 3, "impact required");
    expect(registry.impact(AssetId{0, 4}, output, count) == RegistryError::None
           && count == 0, "impact leaf");
    expect(registry.impact(AssetId{0, 9}, output, count) == RegistryError::NotFound,
           "impact missing");

    vfs::VfsPath moved{};
    expect(vfs::make_path("art/moved", moved) == vfs::VfsError::None, "moved path");
    expect(registry.rename(AssetId{0, 1}, moved) == RegistryError::None, "rename");
    AssetRecord found{};
    expect(registry.find(AssetId{0, 1}, found) == RegistryError::None
           && vfs::view(found.path) == "art/moved" && found.revision == 2, "rename value");
    vfs::VfsPath old_path{};
    (void)vfs::make_path("art/a", old_path);
    AssetId lookup{};
    expect(registry.find_by_path(ProjectId{1}, old_path, lookup) == RegistryError::NotFound,
           "old path gone");
    expect(registry.find_by_path(ProjectId{1}, moved, lookup) == RegistryError::None
           && lookup.low == 1, "new path maps id");

    expect(AssetRegistry::make_reference(AssetId{0, 1}, AssetKind::Texture, 0, reference)
           == RegistryError::None, "post rename ref");
    expect(registry.resolve_reference(reference, resolved) == RegistryError::None
           && vfs::view(resolved.path) == "art/moved", "reference stable");

    vfs::VfsPath collision{};
    (void)vfs::make_path("art/b", collision);
    expect(registry.rename(AssetId{0, 1}, collision) == RegistryError::DuplicatePath,
           "rename collision");
    vfs::VfsPath invalid{};
    invalid.length = 1;
    invalid.bytes[0] = ':';
    expect(registry.rename(AssetId{0, 1}, invalid) == RegistryError::InvalidPath,
           "rename invalid");
    expect(registry.rename(AssetId{0, 9}, moved) == RegistryError::NotFound, "rename missing");

    expect(registry.tombstone(AssetId{0, 3}) == RegistryError::None, "tombstone c");
    expect(registry.rename(AssetId{0, 3}, moved) == RegistryError::Tombstoned,
           "rename tombstone");
    expect(registry.resolve_reference(
               AssetRegistry::AssetReference{AssetId{0, 3}, AssetKind::Scene, 0}, resolved)
           == RegistryError::Tombstoned, "tombstone ref");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data02_reference_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "ref01") { success = run_ref01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
