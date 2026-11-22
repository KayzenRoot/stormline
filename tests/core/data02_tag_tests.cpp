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

[[nodiscard]] AssetRecord record(u64 id, std::string_view path) {
    AssetRecord value{};
    value.id = AssetId{0, id};
    value.project = ProjectId{1};
    (void)vfs::make_path(path, value.path);
    return value;
}

bool run_tag01() {
    begin();
    AssetRegistry::Tag tag{};
    expect(AssetRegistry::make_tag("hero", tag) == RegistryError::None, "tag");
    expect(tag.length == 4, "tag length");
    expect(AssetRegistry::make_tag("", tag) == RegistryError::InvalidTag, "empty");
    std::string max_tag(32, 'a');
    expect(AssetRegistry::make_tag(max_tag, tag) == RegistryError::None, "max tag");
    std::string too_long(33, 'a');
    expect(AssetRegistry::make_tag(too_long, tag) == RegistryError::InvalidTag, "long tag");
    expect(AssetRegistry::make_tag("has space", tag) == RegistryError::InvalidTag, "space");
    expect(AssetRegistry::make_tag("has/slash", tag) == RegistryError::InvalidTag, "slash");
    expect(AssetRegistry::make_tag("has:colon", tag) == RegistryError::InvalidTag, "colon");
    expect(AssetRegistry::make_tag("has\\slash", tag) == RegistryError::InvalidTag, "backslash");
    expect(AssetRegistry::make_tag(std::string_view("\x01", 1), tag) == RegistryError::InvalidTag,
           "control");
    expect(AssetRegistry::make_tag(std::string_view("\x7F", 1), tag) == RegistryError::InvalidTag,
           "non ascii");

    AssetRegistry registry;
    expect(registry.add(record(1, "a")) == RegistryError::None, "add a");
    expect(registry.add(record(2, "b")) == RegistryError::None, "add b");
    AssetRegistry::Tag hero{};
    expect(AssetRegistry::make_tag("hero", hero) == RegistryError::None, "make hero");
    expect(registry.add_tag(AssetId{0, 1}, hero) == RegistryError::None, "add tag");
    expect(registry.add_tag(AssetId{0, 1}, hero) == RegistryError::None, "duplicate tag");
    expect(registry.has_tag(AssetId{0, 1}, hero), "has tag");
    expect(!registry.has_tag(AssetId{0, 2}, hero), "isolated tag");

    std::array<AssetRegistry::Tag, 4> output{};
    u32 count = 0;
    expect(registry.tags_of(AssetId{0, 1}, output, count) == RegistryError::None, "list");
    expect(count == 1 && output[0].length == 4, "list value");

    std::array<AssetRegistry::Tag, 8> fill{};
    for (u32 index = 1; index < kMaxTagsPerAsset; ++index) {
        AssetRegistry::Tag value{};
        expect(AssetRegistry::make_tag("tag" + std::to_string(index), value)
               == RegistryError::None, "make fill tag");
        expect(registry.add_tag(AssetId{0, 1}, value) == RegistryError::None, "fill tag");
    }
    AssetRegistry::Tag ninth{};
    expect(AssetRegistry::make_tag("tag9", ninth) == RegistryError::None, "make ninth");
    expect(registry.add_tag(AssetId{0, 1}, ninth) == RegistryError::CapacityFull, "tag quota");
    expect(registry.tags_of(AssetId{0, 1}, fill, count) == RegistryError::None, "list all");
    expect(count == kMaxTagsPerAsset, "tag count");
    std::array<AssetRegistry::Tag, 3> small{};
    expect(registry.tags_of(AssetId{0, 1}, small, count) == RegistryError::BufferFull,
           "tag buffer");
    expect(count == kMaxTagsPerAsset, "tag required");

    expect(registry.remove_tag(AssetId{0, 1}, hero) == RegistryError::None, "remove tag");
    expect(!registry.has_tag(AssetId{0, 1}, hero), "remove has");
    expect(registry.remove_tag(AssetId{0, 1}, hero) == RegistryError::NotFound, "remove missing");
    expect(registry.remove_tag(AssetId{0, 9}, hero) == RegistryError::NotFound, "remove asset");
    expect(registry.add_tag(AssetId{0, 9}, hero) == RegistryError::NotFound, "add missing asset");
    expect(registry.add_tag(AssetId{}, hero) == RegistryError::InvalidArgument, "invalid asset");

    expect(registry.tombstone(AssetId{0, 2}) == RegistryError::None, "tombstone b");
    expect(registry.add_tag(AssetId{0, 2}, hero) == RegistryError::Tombstoned, "tombstone tag");
    expect(registry.tags_of(AssetId{0, 2}, output, count) == RegistryError::Tombstoned,
           "tombstone list");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data02_tag_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "tag01") { success = run_tag01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
