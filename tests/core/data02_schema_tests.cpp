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

bool run_schema01() {
    begin();
    AssetRegistry::MetadataEntry entry{};
    expect(AssetRegistry::make_metadata_entry("id", "42", entry) == RegistryError::None,
           "entry");
    expect(entry.key_length == 2 && entry.value_length == 2, "entry lengths");
    expect(AssetRegistry::make_metadata_entry("", "x", entry) == RegistryError::InvalidArgument,
           "empty key");
    expect(AssetRegistry::make_metadata_entry("bad key", "x", entry)
           == RegistryError::InvalidArgument, "bad key");
    expect(AssetRegistry::make_metadata_entry(std::string(33, 'a'), "x", entry)
           == RegistryError::InvalidArgument, "long key");
    expect(AssetRegistry::make_metadata_entry("k", std::string(65, 'v'), entry)
           == RegistryError::InvalidArgument, "long value");
    expect(AssetRegistry::make_metadata_entry("k", std::string_view("\x01", 1), entry)
           == RegistryError::InvalidArgument, "control value");
    expect(AssetRegistry::make_metadata_entry(std::string(32, 'a'), std::string(64, 'v'), entry)
           == RegistryError::None, "max entry");

    AssetRegistry registry;
    expect(registry.add(record(1, "a")) == RegistryError::None, "add a");
    expect(registry.add(record(2, "b")) == RegistryError::None, "add b");

    std::array<AssetRegistry::MetadataEntry, 2> entries{};
    expect(AssetRegistry::make_metadata_entry("id", "42", entries[0]) == RegistryError::None,
           "id entry");
    expect(AssetRegistry::make_metadata_entry("kind", "texture", entries[1])
           == RegistryError::None, "kind entry");
    expect(registry.set_metadata(AssetId{0, 1}, 1, entries) == RegistryError::None, "set");
    AssetRecord found{};
    expect(registry.find(AssetId{0, 1}, found) == RegistryError::None
           && found.schema_version == 1, "schema version");

    std::array<AssetRegistry::MetadataEntry, 3> output{};
    u32 count = 0;
    expect(registry.metadata(AssetId{0, 1}, output, count) == RegistryError::None, "list");
    expect(count == 2 && output[0].value[0] == '4', "list values");

    std::array<AssetRegistry::MetadataEntry, 2> duplicate{};
    expect(AssetRegistry::make_metadata_entry("same", "a", duplicate[0]) == RegistryError::None,
           "dup 1");
    expect(AssetRegistry::make_metadata_entry("same", "b", duplicate[1]) == RegistryError::None,
           "dup 2");
    expect(registry.set_metadata(AssetId{0, 1}, 1, duplicate) == RegistryError::InvalidArgument,
           "duplicate keys");
    expect(registry.metadata(AssetId{0, 1}, output, count) == RegistryError::None
           && count == 2, "atomic rejection");

    std::array<AssetRegistry::MetadataEntry, 1> one{};
    expect(AssetRegistry::make_metadata_entry("only", "v", one[0]) == RegistryError::None,
           "one");
    expect(registry.set_metadata(AssetId{0, 1}, 1, one) == RegistryError::None, "replace");
    expect(registry.metadata(AssetId{0, 1}, output, count) == RegistryError::None
           && count == 1, "replace count");

    std::array<AssetRegistry::MetadataEntry, 1> small{};
    expect(registry.metadata(AssetId{0, 1}, small, count) == RegistryError::None,
           "small exact");
    std::array<AssetRegistry::MetadataEntry, 0> empty{};
    expect(registry.metadata(AssetId{0, 1}, empty, count) == RegistryError::BufferFull,
           "buffer");
    expect(count == 1, "buffer required");

    std::array<AssetRegistry::MetadataEntry, 9> nine{};
    for (u32 index = 0; index < 9; ++index) {
        expect(AssetRegistry::make_metadata_entry("k" + std::to_string(index), "v", nine[index])
               == RegistryError::None, "nine entry");
    }
    expect(registry.set_metadata(AssetId{0, 1}, 1, nine) == RegistryError::CapacityFull,
           "quota");

    std::array<AssetRegistry::MetadataEntry, 0> clear{};
    expect(registry.set_metadata(AssetId{0, 1}, 1, clear) == RegistryError::None, "clear");
    expect(registry.find(AssetId{0, 1}, found) == RegistryError::None
           && found.schema_version == 0, "clear version");
    expect(registry.metadata(AssetId{0, 1}, output, count) == RegistryError::None
           && count == 0, "clear count");

    expect(registry.set_metadata(AssetId{0, 1}, 2, one) == RegistryError::InvalidSchema,
           "schema unsupported");
    expect(registry.set_metadata(AssetId{0, 9}, 1, one) == RegistryError::NotFound,
           "missing asset");
    expect(registry.set_metadata(AssetId{}, 1, one) == RegistryError::InvalidArgument,
           "invalid asset");
    expect(registry.tombstone(AssetId{0, 2}) == RegistryError::None, "tombstone b");
    expect(registry.set_metadata(AssetId{0, 2}, 1, one) == RegistryError::Tombstoned,
           "tombstone set");
    expect(registry.metadata(AssetId{0, 2}, output, count) == RegistryError::Tombstoned,
           "tombstone get");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data02_schema_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "schema01") { success = run_schema01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
