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

[[nodiscard]] AssetRecord record(
    u64 id, u64 project, std::string_view path, AssetKind kind) {
    AssetRecord value{};
    value.id = AssetId{0, id};
    value.project = ProjectId{project};
    value.kind = kind;
    (void)vfs::make_path(path, value.path);
    return value;
}

bool run_query01() {
    begin();
    AssetRegistry registry;
    expect(registry.add(record(4, 1, "other/d", AssetKind::Texture)) == RegistryError::None,
           "add d");
    expect(registry.add(record(3, 2, "art/c", AssetKind::Texture)) == RegistryError::None,
           "add c");
    expect(registry.add(record(2, 1, "art/b", AssetKind::Mesh)) == RegistryError::None,
           "add b");
    expect(registry.add(record(1, 1, "art/a", AssetKind::Texture)) == RegistryError::None,
           "add a");

    AssetRegistry::Tag hero{};
    expect(AssetRegistry::make_tag("hero", hero) == RegistryError::None, "hero tag");
    expect(registry.add_tag(AssetId{0, 1}, hero) == RegistryError::None, "a hero");
    expect(registry.add_tag(AssetId{0, 3}, hero) == RegistryError::None, "c hero");

    AssetRegistry::Tag enemy{};
    expect(AssetRegistry::make_tag("enemy", enemy) == RegistryError::None, "enemy tag");
    expect(registry.add_tag(AssetId{0, 2}, enemy) == RegistryError::None, "b enemy");

    AssetRegistry::AssetQuery filter{};
    filter.project = ProjectId{1};
    std::array<AssetId, 4> output{};
    u32 count = 0;
    u32 next = 0;
    expect(registry.query(filter, output, count, next) == RegistryError::None, "project query");
    expect(count == 3 && output[0].low == 1 && output[1].low == 2 && output[2].low == 4,
           "project sorted");
    expect(next == 0, "project next");

    filter.has_kind = true;
    filter.kind = AssetKind::Texture;
    expect(registry.query(filter, output, count, next) == RegistryError::None, "kind query");
    expect(count == 2 && output[0].low == 1 && output[1].low == 4, "kind filtered");

    filter.has_kind = false;
    filter.has_tag = true;
    filter.tag = hero;
    expect(registry.query(filter, output, count, next) == RegistryError::None, "tag query");
    expect(count == 1 && output[0].low == 1, "tag filtered");

    filter.has_tag = false;
    filter.has_prefix = true;
    expect(vfs::make_path("art", filter.prefix) == vfs::VfsError::None, "prefix");
    expect(registry.query(filter, output, count, next) == RegistryError::None, "prefix query");
    expect(count == 2 && output[0].low == 1 && output[1].low == 2, "prefix filtered");

    filter.has_kind = true;
    filter.kind = AssetKind::Texture;
    filter.has_tag = true;
    filter.tag = hero;
    expect(registry.query(filter, output, count, next) == RegistryError::None, "combined");
    expect(count == 1 && output[0].low == 1, "combined filtered");

    filter.has_tag = false;
    filter.has_kind = false;
    filter.has_prefix = false;
    std::array<AssetId, 2> page{};
    filter.offset = 1;
    expect(registry.query(filter, page, count, next) == RegistryError::None, "page");
    expect(count == 2 && page[0].low == 2 && page[1].low == 4 && next == 0, "page values");

    filter.offset = 1;
    std::array<AssetId, 1> one{};
    expect(registry.query(filter, one, count, next) == RegistryError::None, "page one");
    expect(count == 1 && one[0].low == 2 && next == 2, "page cursor");

    filter.offset = 9;
    expect(registry.query(filter, output, count, next) == RegistryError::None, "past end");
    expect(count == 0 && next == 0, "past end values");

    filter.offset = 0;
    std::array<AssetId, 0> empty{};
    expect(registry.query(filter, empty, count, next) == RegistryError::InvalidArgument,
           "empty output");
    filter.project = ProjectId{};
    expect(registry.query(filter, output, count, next) == RegistryError::InvalidArgument,
           "invalid project");
    filter.project = ProjectId{1};
    filter.has_prefix = true;
    filter.prefix.length = vfs::kMaxPathBytes + 1;
    expect(registry.query(filter, output, count, next) == RegistryError::InvalidArgument,
           "invalid prefix");
    filter.has_prefix = false;
    filter.has_tag = true;
    filter.tag.length = 0;
    expect(registry.query(filter, output, count, next) == RegistryError::InvalidArgument,
           "invalid tag");

    filter.has_tag = false;
    filter.offset = 0;
    expect(registry.tombstone(AssetId{0, 1}) == RegistryError::None, "tombstone a");
    expect(registry.query(filter, output, count, next) == RegistryError::None, "after tombstone");
    expect(count == 2 && output[0].low == 2 && output[1].low == 4, "tombstone excluded");

    filter.project = ProjectId{2};
    expect(registry.query(filter, output, count, next) == RegistryError::None, "project 2");
    expect(count == 1 && output[0].low == 3, "project isolated");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data02_query_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "query01") { success = run_query01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
