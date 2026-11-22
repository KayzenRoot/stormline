#include "stormline/data/vfs/vfs_overlay.hpp"

#include <cstdio>
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

bool run_overlay01() {
    begin();
    MountTable table;
    expect(table.add(mount(1, "", 0)) == VfsError::None, "root mount");
    expect(table.add(mount(2, "engine", 10)) == VfsError::None, "engine mount");
    expect(table.add(mount(3, "project", 20)) == VfsError::None, "project mount");
    expect(table.add(mount(4, "project/sub", 30)) == VfsError::None, "sub mount");

    VfsPath path{};
    LookupResult result{};
    expect(make_path("engine/a", path) == VfsError::None, "engine path");
    expect(resolve(table, path, result) == VfsError::None, "resolve engine");
    expect(result.mount.value == 2 && view(result.relative) == "a",
           "engine selected");
    expect(result.shadowed_count == 1, "engine shadow");

    expect(make_path("project/sub/x", path) == VfsError::None, "sub path");
    expect(resolve(table, path, result) == VfsError::None, "resolve sub");
    expect(result.mount.value == 4 && view(result.relative) == "x", "sub selected");
    expect(result.shadowed_count == 2, "sub shadows");

    expect(make_path("other/file", path) == VfsError::None, "other path");
    expect(resolve(table, path, result) == VfsError::None, "resolve root");
    expect(result.mount.value == 1 && view(result.relative) == "other/file",
           "root fallback");

    MountTable tie;
    expect(tie.add(mount(10, "a", 5)) == VfsError::None, "tie a");
    expect(tie.add(mount(5, "a/b", 5)) == VfsError::None, "tie a/b");
    expect(make_path("a/b/c", path) == VfsError::None, "tie path");
    expect(resolve(tie, path, result) == VfsError::None, "resolve tie");
    expect(result.mount.value == 5, "lower id wins tie");
    expect(result.shadowed_count == 1, "tie shadow");

    expect(make_path("ab", path) == VfsError::None, "boundary path");
    expect(resolve(tie, path, result) == VfsError::NotFound, "component boundary");
    expect(result.status == VfsError::NotFound, "not found status");

    expect(make_path("a/only", path) == VfsError::None, "a/only path");
    expect(resolve(tie, path, result) == VfsError::None, "resolve a/only");
    expect(result.mount.value == 10 && view(result.relative) == "only",
           "a root selected");

    MountTable empty;
    expect(make_path("nothing", path) == VfsError::None, "nothing path");
    expect(resolve(empty, path, result) == VfsError::NotFound, "empty table");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) { std::fprintf(stderr, "usage: stormline_data01_overlay_test <mode>\n"); return 2; }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "overlay01") { success = run_overlay01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
