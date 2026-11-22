#include "stormline/data/vfs/vfs_cache.hpp"
#include "stormline/data/vfs/vfs_capability.hpp"
#include "stormline/data/vfs/vfs_mount.hpp"
#include "stormline/data/vfs/vfs_overlay.hpp"
#include "stormline/data/vfs/vfs_storage.hpp"

#include <array>
#include <cstdio>
#include <string>
#include <string_view>

namespace {
using namespace stormline::data::vfs;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

struct Fixture {
    MountTable mounts{};
    CapabilitySet capabilities{};
    PathCache cache{};
    MemoryStorage storage{};
};

[[nodiscard]] bool build_fixture(Fixture& fixture) {
    VfsPath base{};
    VfsPath patch{};
    VfsPath full{};
    if (make_path("base", base) != VfsError::None
        || make_path("base/tex", patch) != VfsError::None
        || make_path("base/tex/a.bin", full) != VfsError::None) {
        return false;
    }
    const MountInfo first{MountId{1}, base, 10, MountMode::ReadOnly, 0};
    const MountInfo second{MountId{2}, patch, 20, MountMode::ReadOnly, 0};
    if (fixture.mounts.add(first) != VfsError::None
        || fixture.mounts.add(second) != VfsError::None) {
        return false;
    }
    if (fixture.capabilities.grant(AccessCapability{WorkspaceId{7}, MountId{2}, true})
        != VfsError::None) {
        return false;
    }
    LookupResult lookup{};
    if (resolve(fixture.mounts, full, lookup) != VfsError::None) {
        return false;
    }
    const std::array<std::uint8_t, 4> bytes{0xA1, 0xB2, 0xC3, 0xD4};
    if (fixture.cache.put(lookup.mount, lookup.generation, lookup.relative, bytes)
        != VfsError::None) {
        return false;
    }
    return fixture.storage.put(full, bytes) == VfsError::None;
}

bool run_qlf01() {
    begin();
    Fixture fixture{};
    expect(build_fixture(fixture), "fixture");
    VfsPath full{};
    expect(make_path("base/tex/a.bin", full) == VfsError::None, "path");
    LookupResult lookup{};
    expect(resolve(fixture.mounts, full, lookup) == VfsError::None, "resolve");
    expect(lookup.mount.value == 2, "overlay mount");
    expect(view(lookup.relative) == "a.bin", "relative suffix");
    expect(lookup.shadowed_count == 1, "shadow count");
    expect(fixture.capabilities.allows(WorkspaceId{7}, MountId{2}), "allowed mount");
    expect(!fixture.capabilities.allows(WorkspaceId{7}, MountId{1}), "denied mount");

    std::array<std::uint8_t, 8> output{};
    u32 out_size = 0;
    expect(fixture.cache.get(lookup.mount, lookup.generation, lookup.relative, output,
                             out_size) == VfsError::None, "cache get");
    expect(out_size == 4 && output[0] == 0xA1 && output[3] == 0xD4, "cache bytes");
    expect(fixture.storage.read(full, output, out_size) == VfsError::None, "storage read");
    expect(out_size == 4 && output[0] == 0xA1 && output[3] == 0xD4, "storage bytes");

    VfsPath missing{};
    expect(make_path("base/other.bin", missing) == VfsError::None, "missing path");
    expect(resolve(fixture.mounts, missing, lookup) == VfsError::None, "base mount");
    expect(lookup.mount.value == 1 && lookup.shadowed_count == 0, "base selection");
    return finish();
}

struct Snapshot {
    VfsError resolve_status{VfsError::InternalFailure};
    MountId mount{};
    std::string relative{};
    u64 generation{0};
    u32 shadowed{0};
    VfsError cache_status{VfsError::InternalFailure};
    std::array<std::uint8_t, 4> cache_bytes{};
    VfsError storage_status{VfsError::InternalFailure};
    std::array<std::uint8_t, 4> storage_bytes{};
};

[[nodiscard]] bool snapshot(Snapshot& out) {
    Fixture fixture{};
    if (!build_fixture(fixture)) {
        return false;
    }
    VfsPath full{};
    if (make_path("base/tex/a.bin", full) != VfsError::None) {
        return false;
    }
    LookupResult lookup{};
    out.resolve_status = resolve(fixture.mounts, full, lookup);
    if (out.resolve_status != VfsError::None) {
        return false;
    }
    out.mount = lookup.mount;
    out.relative = std::string(view(lookup.relative));
    out.generation = lookup.generation;
    out.shadowed = lookup.shadowed_count;
    u32 out_size = 0;
    out.cache_status = fixture.cache.get(lookup.mount, lookup.generation,
                                         lookup.relative, out.cache_bytes, out_size);
    if (out.cache_status != VfsError::None || out_size != 4) {
        return false;
    }
    out.storage_status = fixture.storage.read(full, out.storage_bytes, out_size);
    return out.storage_status == VfsError::None && out_size == 4;
}

bool run_qlf02() {
    begin();
    Snapshot first{};
    Snapshot second{};
    expect(snapshot(first), "first snapshot");
    expect(snapshot(second), "second snapshot");
    expect(first.resolve_status == second.resolve_status, "resolve repeat");
    expect(first.mount.value == second.mount.value, "mount repeat");
    expect(first.relative == second.relative, "relative repeat");
    expect(first.generation == second.generation, "generation repeat");
    expect(first.shadowed == second.shadowed, "shadow repeat");
    expect(first.cache_status == second.cache_status, "cache status repeat");
    expect(first.cache_bytes == second.cache_bytes, "cache bytes repeat");
    expect(first.storage_status == second.storage_status, "storage status repeat");
    expect(first.storage_bytes == second.storage_bytes, "storage bytes repeat");
    return finish();
}

bool run_qlf03() {
    begin();
    VfsPath path{};
    expect(make_path("../escape", path) == VfsError::PathEscape, "traversal rejected");
    expect(make_path("safe/file", path) == VfsError::None, "valid path after rejection");

    MountTable mounts;
    VfsPath root{};
    VfsPath other{};
    expect(make_path("root", root) == VfsError::None, "mount path");
    expect(make_path("other", other) == VfsError::None, "mount path 2");
    MountInfo mount{MountId{1}, root, 0, MountMode::ReadOnly, 0};
    expect(mounts.add(mount) == VfsError::None, "mount add");
    expect(mounts.add(mount) == VfsError::MountCollision, "mount collision");
    mount.id = MountId{2};
    mount.root = other;
    expect(mounts.add(mount) == VfsError::None, "mount add after collision");

    LookupResult lookup{};
    VfsPath unknown{};
    expect(make_path("unknown/file", unknown) == VfsError::None, "unknown path");
    expect(resolve(mounts, unknown, lookup) == VfsError::NotFound, "unresolved");
    VfsPath known{};
    expect(make_path("root/file", known) == VfsError::None, "known path");
    expect(resolve(mounts, known, lookup) == VfsError::None, "resolved after miss");

    CapabilitySet capabilities;
    expect(!capabilities.allows(WorkspaceId{3}, MountId{1}), "capability denied");
    expect(capabilities.grant(AccessCapability{WorkspaceId{3}, MountId{1}, true})
           == VfsError::None, "capability grant");
    expect(capabilities.allows(WorkspaceId{3}, MountId{1}), "capability allowed");

    PathCache cache;
    std::array<std::uint8_t, 8> output{};
    u32 out_size = 0;
    expect(cache.get(MountId{1}, 1, path, output, out_size) == VfsError::NotFound,
           "cache miss");
    const std::array<std::uint8_t, 2> bytes{4, 5};
    expect(cache.put(MountId{1}, 2, path, bytes) == VfsError::None, "cache put");
    expect(cache.get(MountId{1}, 1, path, output, out_size) == VfsError::StaleMount,
           "cache stale");
    expect(cache.get(MountId{1}, 2, path, output, out_size) == VfsError::None,
           "cache hit after stale");

    MemoryStorage storage;
    expect(storage.read(path, output, out_size) == VfsError::NotFound, "storage miss");
    expect(storage.put(path, bytes) == VfsError::None, "storage put");
    expect(storage.read(path, output, out_size) == VfsError::None, "storage hit");
    expect(storage.erase(path) == VfsError::None, "storage erase");
    expect(storage.read(path, output, out_size) == VfsError::NotFound,
           "storage miss after erase");
    return finish();
}

bool run_qlf04() {
    begin();
    MountTable mounts;
    for (u32 index = 0; index < kMaxMounts; ++index) {
        VfsPath root{};
        expect(make_path("m" + std::to_string(index), root) == VfsError::None,
               "mount fill path");
        const MountInfo mount{MountId{index + 1}, root, 0, MountMode::ReadOnly, 0};
        expect(mounts.add(mount) == VfsError::None, "mount fill");
    }
    for (u32 index = 0; index < 10000; ++index) {
        VfsPath root{};
        expect(make_path("overload/" + std::to_string(index), root) == VfsError::None,
               "overload path");
        const MountInfo mount{MountId{1000 + index}, root, 0, MountMode::ReadOnly, 0};
        expect(mounts.add(mount) == VfsError::BufferFull, "mount overload");
    }
    expect(mounts.size() == kMaxMounts, "mount capacity stable");
    expect(mounts.generation() == kMaxMounts, "mount generation stable");

    PathCache cache;
    const std::array<std::uint8_t, 1> byte{7};
    for (u32 index = 0; index < kMaxCacheEntries; ++index) {
        VfsPath path{};
        expect(make_path("c" + std::to_string(index), path) == VfsError::None,
               "cache fill path");
        expect(cache.put(MountId{1}, 1, path, byte) == VfsError::None, "cache fill");
    }
    for (u32 index = 0; index < 10000; ++index) {
        VfsPath path{};
        expect(make_path("drop/" + std::to_string(index), path) == VfsError::None,
               "cache overload path");
        expect(cache.put(MountId{1}, 1, path, byte) == VfsError::BufferFull,
               "cache overload");
    }
    expect(cache.size() == kMaxCacheEntries, "cache capacity stable");
    expect(cache.dropped() == 10000, "cache drops counted");

    MemoryStorage storage;
    for (u32 index = 0; index < kMaxStorageFiles; ++index) {
        VfsPath path{};
        expect(make_path("s" + std::to_string(index), path) == VfsError::None,
               "storage fill path");
        expect(storage.put(path, byte) == VfsError::None, "storage fill");
    }
    for (u32 index = 0; index < 10000; ++index) {
        VfsPath path{};
        expect(make_path("store/" + std::to_string(index), path) == VfsError::None,
               "storage overload path");
        expect(storage.put(path, byte) == VfsError::BufferFull, "storage overload");
    }
    expect(storage.size() == kMaxStorageFiles, "storage capacity stable");

    VfsPath cache_path{};
    expect(make_path("c0", cache_path) == VfsError::None, "existing cache path");
    std::array<std::uint8_t, 1> output{};
    u32 out_size = 0;
    expect(cache.get(MountId{1}, 1, cache_path, output, out_size) == VfsError::None
           && out_size == 1 && output[0] == 7, "cache survives overload");
    VfsPath storage_path{};
    expect(make_path("s0", storage_path) == VfsError::None, "existing storage path");
    expect(storage.read(storage_path, output, out_size) == VfsError::None
           && out_size == 1 && output[0] == 7, "storage survives overload");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data01_vfs_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") { success = run_qlf01(); }
    else if (mode == "qlf02") { success = run_qlf02(); }
    else if (mode == "qlf03") { success = run_qlf03(); }
    else if (mode == "qlf04") { success = run_qlf04(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
