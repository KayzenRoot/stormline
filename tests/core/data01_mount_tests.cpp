#include "stormline/data/vfs/vfs_mount.hpp"

#include <cstdio>
#include <string>
#include <string_view>

namespace {
using namespace stormline::data::vfs;
int failures = 0;
void expect(bool c, const char* d) { if (!c) { std::fprintf(stderr, "FAIL: %s\n", d); ++failures; } }
void begin() { failures = 0; }
bool finish() { return failures == 0; }

MountInfo mount(u64 id, const char* root, u32 priority) {
    MountInfo info{};
    info.id.value = id;
    (void)make_path(root, info.root);
    info.priority = priority;
    return info;
}

bool run_mount01() {
    begin();
    MountTable table;
    expect(table.size() == 0 && table.generation() == 0, "initial table");
    expect(table.add(mount(1, "engine", 1)) == VfsError::None, "add engine");
    expect(table.add(mount(2, "project", 2)) == VfsError::None, "add project");
    expect(table.size() == 2 && table.generation() == 2, "size/generation");
    MountInfo out{};
    expect(table.find(MountId{1}, out) && view(out.root) == "engine"
               && out.priority == 1 && out.generation == 1,
           "find engine");
    expect(table.at(1, out) && out.id.value == 2, "at project");
    expect(!table.at(2, out), "at out of range");
    expect(!table.find(MountId{9}, out), "find missing");

    expect(table.add(mount(1, "other", 0)) == VfsError::MountCollision,
           "duplicate id");
    expect(table.add(mount(3, "engine", 0)) == VfsError::MountCollision,
           "duplicate root");
    expect(table.add(mount(0, "zero", 0)) == VfsError::InvalidMount,
           "invalid id");
    MountInfo bad_mode = mount(4, "bad", 0);
    bad_mode.mode = static_cast<MountMode>(2);
    expect(table.add(bad_mode) == VfsError::InvalidMount, "invalid mode");

    for (u64 id = 3; id <= kMaxMounts; ++id) {
        const std::string root = "m" + std::to_string(id);
        expect(table.add(mount(id, root.c_str(), 0)) == VfsError::None, "fill mount");
    }
    expect(table.size() == kMaxMounts, "mount capacity");
    expect(table.add(mount(kMaxMounts + 1, "overflow", 0)) == VfsError::BufferFull,
           "mount full");

    expect(table.remove(MountId{1}) == VfsError::None, "remove engine");
    expect(table.size() == kMaxMounts - 1, "size after remove");
    expect(table.remove(MountId{1}) == VfsError::NotFound, "remove missing");
    table.clear();
    expect(table.size() == 0, "clear size");
    expect(table.generation() > kMaxMounts, "generation grows");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) { std::fprintf(stderr, "usage: stormline_data01_mount_test <mode>\n"); return 2; }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "mount01") { success = run_mount01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
