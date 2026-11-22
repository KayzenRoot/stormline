#include "stormline/data/registry/asset_registry.hpp"

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
    u64 id, u64 project, std::string_view path, AssetKind kind = AssetKind::Texture) {
    AssetRecord value{};
    value.id = AssetId{0, id};
    value.project = ProjectId{project};
    (void)vfs::make_path(path, value.path);
    value.kind = kind;
    return value;
}

bool run_id01() {
    begin();
    AssetRegistry registry;
    const AssetRecord texture = record(10, 1, "art/wood.png");
    expect(registry.add(texture) == RegistryError::None, "add");
    expect(registry.size() == 1, "size");

    AssetRecord found{};
    expect(registry.find(AssetId{0, 10}, found) == RegistryError::None, "find active");
    expect(found.project.value == 1 && vfs::view(found.path) == "art/wood.png", "find values");
    expect(found.kind == AssetKind::Texture && found.status == AssetStatus::Active,
           "find status");

    AssetId by_path{};
    expect(registry.find_by_path(ProjectId{1}, texture.path, by_path) == RegistryError::None,
           "path lookup");
    expect(by_path.low == 10, "path id");

    expect(registry.add(texture) == RegistryError::DuplicateId, "duplicate id");
    AssetRecord same_path = record(11, 1, "art/wood.png");
    expect(registry.add(same_path) == RegistryError::DuplicatePath, "duplicate path");
    AssetRecord other_project = record(12, 2, "art/wood.png");
    expect(registry.add(other_project) == RegistryError::None, "same path other project");

    expect(registry.tombstone(AssetId{0, 10}) == RegistryError::None, "tombstone");
    expect(registry.find(AssetId{0, 10}, found) == RegistryError::Tombstoned, "find tombstone");
    expect(found.status == AssetStatus::Tombstoned && found.revision == 2, "tombstone values");
    expect(registry.find_by_path(ProjectId{1}, texture.path, by_path) == RegistryError::Tombstoned,
           "path tombstone");
    expect(registry.tombstone(AssetId{0, 10}) == RegistryError::Tombstoned, "double tombstone");

    expect(registry.find(AssetId{0, 99}, found) == RegistryError::NotFound, "missing id");
    expect(registry.find_by_path(ProjectId{1}, record(1, 1, "missing").path, by_path)
           == RegistryError::NotFound, "missing path");
    expect(registry.tombstone(AssetId{0, 99}) == RegistryError::NotFound, "missing tombstone");

    AssetRecord invalid = record(20, 1, "invalid");
    invalid.id = AssetId{};
    expect(registry.add(invalid) == RegistryError::InvalidId, "invalid id");
    invalid = record(21, 1, "invalid");
    invalid.project = ProjectId{};
    expect(registry.add(invalid) == RegistryError::InvalidArgument, "invalid project");
    invalid = record(22, 1, "invalid");
    invalid.revision = 2;
    expect(registry.add(invalid) == RegistryError::InvalidArgument, "invalid revision");
    invalid = record(23, 1, "invalid");
    invalid.status = AssetStatus::Tombstoned;
    expect(registry.add(invalid) == RegistryError::InvalidArgument, "invalid status");

    AssetRecord forged = record(24, 1, "forged");
    forged.path.length = vfs::kMaxPathBytes + 1;
    expect(registry.add(forged) == RegistryError::InvalidPath, "forged path");
    AssetRecord bad_path = record(25, 1, "bad");
    bad_path.path.length = 1;
    bad_path.path.bytes[0] = ':';
    expect(registry.add(bad_path) == RegistryError::InvalidPath, "invalid path");

    AssetRecord out{};
    expect(!registry.at(100, out), "at range");

    AssetRegistry full;
    for (u32 index = 0; index < kMaxAssets; ++index) {
        const AssetRecord value = record(index + 1, 9, "cap/" + std::to_string(index));
        expect(full.add(value) == RegistryError::None, "fill");
    }
    expect(full.size() == kMaxAssets, "capacity");
    expect(full.add(record(1000, 9, "cap/overflow")) == RegistryError::CapacityFull,
           "capacity full");
    expect(full.size() == kMaxAssets, "capacity stable");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data02_id_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "id01") { success = run_id01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
