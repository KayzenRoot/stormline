#include "stormline/data/vfs/vfs_path.hpp"

#include <cstdio>
#include <string>
#include <string_view>

namespace {
using namespace stormline::data::vfs;
int failures = 0;
void expect(bool c, const char* d) { if (!c) { std::fprintf(stderr, "FAIL: %s\n", d); ++failures; } }
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_path01() {
    begin();
    VfsPath path{};
    expect(make_path("", path) == VfsError::None && empty(path), "empty root");
    expect(make_path("a", path) == VfsError::None && view(path) == "a", "single component");
    expect(make_path("a/b/c", path) == VfsError::None && view(path) == "a/b/c", "components");
    expect(make_path("/a", path) == VfsError::PathEscape, "leading slash");
    expect(make_path("a/", path) == VfsError::PathEscape, "trailing slash");
    expect(make_path("a//b", path) == VfsError::InvalidPath, "double slash");
    expect(make_path("a/../b", path) == VfsError::PathEscape, "dot dot");
    expect(make_path("../a", path) == VfsError::PathEscape, "leading dot dot");
    expect(make_path("a/./b", path) == VfsError::PathEscape, "dot");
    expect(make_path(std::string(1, '\\') + "a", path) == VfsError::PathEscape, "backslash");
    expect(make_path("C:/a", path) == VfsError::PathEscape, "drive");
    expect(make_path("//server/share", path) == VfsError::PathEscape, "UNC");
    expect(make_path(std::string_view("a\0b", 3), path) == VfsError::InvalidPath, "nul");
    expect(make_path(std::string_view("a/\x01/b", 5), path) == VfsError::InvalidPath, "control");
    expect(make_path("a/\xC3\xA9", path) == VfsError::InvalidPath, "non-ascii");
    expect(make_path("a/b.", path) == VfsError::InvalidPath, "trailing dot");
    expect(make_path("a/b ", path) == VfsError::InvalidPath, "trailing space");
    expect(make_path("CON", path) == VfsError::InvalidPath, "reserved con");
    expect(make_path("con.txt", path) == VfsError::InvalidPath, "reserved con ext");
    expect(make_path("COM1", path) == VfsError::InvalidPath, "reserved com1");
    expect(make_path(std::string(65, 'a'), path) == VfsError::InvalidPath, "component too long");
    expect(make_path(std::string(513, 'a'), path) == VfsError::InvalidPath, "total too long");

    const std::string component(64, 'a');
    const std::string max_path = component + "/" + component + "/" + component + "/"
        + component + "/" + component + "/" + component + "/" + component + "/"
        + std::string(57, 'b');
    expect(max_path.size() == 512, "max fixture size");
    expect(make_path(max_path, path) == VfsError::None && path.length == 512, "max path accepted");

    VfsPath a{};
    VfsPath ab{};
    VfsPath a_b{};
    expect(make_path("a", a) == VfsError::None, "prefix a");
    expect(make_path("ab", ab) == VfsError::None, "prefix ab");
    expect(make_path("a/b", a_b) == VfsError::None, "prefix a/b");
    expect(is_prefix(a, a), "prefix equal");
    expect(is_prefix(a, a_b), "prefix component");
    expect(is_prefix(VfsPath{}, ab), "empty prefix");
    expect(!is_prefix(a, ab), "prefix boundary reject");
    expect(!is_prefix(ab, a), "prefix longer reject");
    expect(view(VfsPath{}).empty(), "empty view");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) { std::fprintf(stderr, "usage: stormline_data01_path_test <mode>\n"); return 2; }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "path01") { success = run_path01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
