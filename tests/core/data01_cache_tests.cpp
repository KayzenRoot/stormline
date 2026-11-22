#include "stormline/data/vfs/vfs_cache.hpp"

#include <array>
#include <cstdio>
#include <string>
#include <string_view>

namespace {
using namespace stormline::data::vfs;
int failures = 0;
void expect(bool c, const char* d) { if (!c) { std::fprintf(stderr, "FAIL: %s\n", d); ++failures; } }
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_cache01() {
    begin();
    PathCache cache;
    const MountId mount{1};
    VfsPath path{};
    expect(make_path("a/b", path) == VfsError::None, "path");
    const std::array<std::uint8_t, 4> bytes{1, 2, 3, 4};
    expect(cache.put(mount, 1, path, bytes) == VfsError::None, "put");
    expect(cache.size() == 1, "size");
    std::array<std::uint8_t, 8> output{};
    u32 out_size = 0;
    expect(cache.get(mount, 1, path, output, out_size) == VfsError::None, "get");
    expect(out_size == 4 && output[0] == 1 && output[3] == 4, "get bytes");
    const std::array<std::uint8_t, 2> update{9, 8};
    expect(cache.put(mount, 1, path, update) == VfsError::None, "update");
    expect(cache.size() == 1, "update size");
    expect(cache.get(mount, 1, path, output, out_size) == VfsError::None && out_size == 2,
           "updated get");
    expect(cache.get(mount, 2, path, output, out_size) == VfsError::StaleMount,
           "stale generation");
    expect(cache.get(MountId{2}, 1, path, output, out_size) == VfsError::NotFound,
           "not found");

    std::array<std::uint8_t, 1> small{};
    expect(cache.get(mount, 1, path, small, out_size) == VfsError::BufferFull,
           "small output");
    expect(out_size == 2, "required size");
    expect(cache.put(MountId{}, 1, path, bytes) == VfsError::InvalidArgument,
           "invalid mount");
    expect(cache.put(mount, 0, path, bytes) == VfsError::InvalidArgument,
           "invalid generation");
    std::array<std::uint8_t, kMaxStorageBytes + 1> huge{};
    expect(cache.put(mount, 1, path, huge) == VfsError::InvalidArgument,
           "too large");

    const std::array<std::uint8_t, 1> one{1};
    PathCache full_cache;
    for (u32 index = 0; index < kMaxCacheEntries; ++index) {
        VfsPath fill{};
        expect(make_path("f" + std::to_string(index), fill) == VfsError::None,
               "fill path");
        expect(full_cache.put(MountId{2}, 1, fill, one) == VfsError::None, "fill cache");
    }
    expect(full_cache.size() == kMaxCacheEntries, "cache capacity");
    expect(full_cache.put(MountId{2}, 1, path, one) == VfsError::BufferFull,
           "cache full");
    expect(full_cache.dropped() == 1, "cache dropped");
    expect(full_cache.invalidate_mount(MountId{2}) == kMaxCacheEntries, "invalidate");
    expect(full_cache.size() == 0, "size after invalidate");
    cache.clear();
    expect(cache.size() == 0 && cache.dropped() == 0, "clear");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) { std::fprintf(stderr, "usage: stormline_data01_cache_test <mode>\n"); return 2; }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "cache01") { success = run_cache01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
