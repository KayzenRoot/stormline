#include "stormline/data/vfs/vfs_storage.hpp"

#include <array>
#include <cstdio>
#include <string>

namespace {
using namespace stormline::data::vfs;
int failures = 0;
void expect(bool c, const char* d) { if (!c) { std::fprintf(stderr, "FAIL: %s\n", d); ++failures; } }
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_storage01() {
    begin();
    MemoryStorage storage;
    VfsPath path{};
    expect(make_path("assets/texture.bin", path) == VfsError::None, "path");
    const std::array<std::uint8_t, 4> bytes{1, 2, 3, 4};
    expect(storage.put(path, bytes) == VfsError::None, "put");
    expect(storage.size() == 1, "size");
    std::array<std::uint8_t, 8> output{};
    u32 out_size = 0;
    expect(storage.read(path, output, out_size) == VfsError::None, "read");
    expect(out_size == 4 && output[0] == 1 && output[3] == 4, "read bytes");

    const std::array<std::uint8_t, 2> update{9, 8};
    expect(storage.put(path, update) == VfsError::None, "update");
    expect(storage.size() == 1, "update size");
    expect(storage.read(path, output, out_size) == VfsError::None && out_size == 2,
           "updated read");

    std::array<std::uint8_t, 1> small{};
    expect(storage.read(path, small, out_size) == VfsError::BufferFull, "small output");
    expect(out_size == 2, "required size");

    VfsPath missing{};
    expect(make_path("missing.bin", missing) == VfsError::None, "missing path");
    expect(storage.read(missing, output, out_size) == VfsError::NotFound, "missing read");
    expect(storage.erase(missing) == VfsError::NotFound, "missing erase");

    std::array<std::uint8_t, kMaxStorageBytes + 1> huge{};
    expect(storage.put(path, huge) == VfsError::InvalidArgument, "too large");
    VfsPath forged{};
    forged.length = kMaxPathBytes + 1;
    expect(storage.put(forged, bytes) == VfsError::InvalidPath, "forged path");

    VfsPath bad{};
    bad.length = 1;
    bad.bytes[0] = ':';
    expect(storage.put(bad, bytes) == VfsError::PathEscape, "invalid path");

    MemoryStorage full;
    const std::array<std::uint8_t, 1> one{1};
    for (u32 index = 0; index < kMaxStorageFiles; ++index) {
        VfsPath fill{};
        expect(make_path("f" + std::to_string(index), fill) == VfsError::None, "fill path");
        expect(full.put(fill, one) == VfsError::None, "fill");
    }
    expect(full.size() == kMaxStorageFiles, "capacity");
    expect(full.put(path, one) == VfsError::BufferFull, "full");
    expect(full.size() == kMaxStorageFiles, "full size");

    expect(storage.erase(path) == VfsError::None, "erase");
    expect(storage.size() == 0, "size after erase");
    expect(storage.read(path, output, out_size) == VfsError::NotFound, "read after erase");

    StorageBackend& backend = storage;
    expect(storage.put(path, bytes) == VfsError::None, "dispatch put");
    expect(backend.read(path, output, out_size) == VfsError::None && out_size == 4,
           "dispatch read");

    VfsPath root{};
    expect(storage.put(root, one) == VfsError::None, "root put");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) { std::fprintf(stderr, "usage: stormline_data01_storage_test <mode>\n"); return 2; }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "storage01") { success = run_storage01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
