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

bool run_dep01() {
    begin();
    AssetRegistry registry;
    expect(registry.add(record(1, "a")) == RegistryError::None, "add a");
    expect(registry.add(record(2, "b")) == RegistryError::None, "add b");
    expect(registry.add(record(3, "c")) == RegistryError::None, "add c");

    const AssetRegistry::DependencyEdge ab{
        AssetId{0, 1}, AssetId{0, 2}, AssetRegistry::DependencyKind::Runtime};
    const AssetRegistry::DependencyEdge ac{
        AssetId{0, 1}, AssetId{0, 3}, AssetRegistry::DependencyKind::Build};
    expect(registry.add_dependency(ab) == RegistryError::None, "add ab");
    expect(registry.add_dependency(ac) == RegistryError::None, "add ac");
    expect(registry.add_dependency(ab) == RegistryError::None, "duplicate edge");
    expect(registry.dependency_count() == 2, "edge count");

    std::array<AssetId, 4> output{};
    u32 count = 0;
    expect(registry.dependencies_of(AssetId{0, 1}, output, count) == RegistryError::None,
           "forward");
    expect(count == 2 && output[0].low == 2 && output[1].low == 3, "forward sorted");
    expect(registry.dependents_of(AssetId{0, 2}, output, count) == RegistryError::None,
           "reverse");
    expect(count == 1 && output[0].low == 1, "reverse value");

    std::array<AssetId, 1> small{};
    expect(registry.dependencies_of(AssetId{0, 1}, small, count) == RegistryError::BufferFull,
           "forward small");
    expect(count == 2, "forward required");

    expect(registry.has_dependency(AssetId{0, 1}, AssetId{0, 2},
                                   AssetRegistry::DependencyKind::Runtime), "has");
    expect(!registry.has_dependency(AssetId{0, 2}, AssetId{0, 1},
                                    AssetRegistry::DependencyKind::Runtime), "missing has");
    expect(registry.remove_dependency(AssetId{0, 1}, AssetId{0, 2},
                                      AssetRegistry::DependencyKind::Runtime)
           == RegistryError::None, "remove");
    expect(registry.remove_dependency(AssetId{0, 1}, AssetId{0, 2},
                                      AssetRegistry::DependencyKind::Runtime)
           == RegistryError::NotFound, "remove missing");

    expect(registry.unresolved_dependencies() == 0, "resolved count");
    const AssetRegistry::DependencyEdge ad{
        AssetId{0, 1}, AssetId{0, 9}, AssetRegistry::DependencyKind::Editor};
    expect(registry.add_dependency(ad) == RegistryError::None, "unresolved edge");
    expect(registry.unresolved_dependencies() == 1, "unresolved count");

    const AssetRegistry::DependencyEdge ca{
        AssetId{0, 3}, AssetId{0, 1}, AssetRegistry::DependencyKind::Runtime};
    expect(registry.add_dependency(ca) == RegistryError::DependencyCycle, "cycle");
    const AssetRegistry::DependencyEdge self{
        AssetId{0, 1}, AssetId{0, 1}, AssetRegistry::DependencyKind::Runtime};
    expect(registry.add_dependency(self) == RegistryError::DependencyCycle, "self cycle");
    const AssetRegistry::DependencyEdge missing_source{
        AssetId{0, 9}, AssetId{0, 1}, AssetRegistry::DependencyKind::Runtime};
    expect(registry.add_dependency(missing_source) == RegistryError::NotFound, "missing source");
    const AssetRegistry::DependencyEdge invalid{
        AssetId{}, AssetId{0, 1}, AssetRegistry::DependencyKind::Runtime};
    expect(registry.add_dependency(invalid) == RegistryError::InvalidArgument, "invalid edge");

    expect(registry.tombstone(AssetId{0, 3}) == RegistryError::None, "tombstone c");
    expect(registry.unresolved_dependencies() == 2, "tombstone unresolved");
    expect(registry.dependencies_of(AssetId{0, 1}, output, count) == RegistryError::None,
           "forward after tombstone");
    expect(count == 2 && output[0].low == 3 && output[1].low == 9, "forward sorted after");

    expect(registry.dependencies_of(AssetId{0, 9}, output, count) == RegistryError::NotFound,
           "missing forward source");
    expect(registry.dependents_of(AssetId{0, 9}, output, count) == RegistryError::None,
           "unresolved dependents");
    expect(count == 1 && output[0].low == 1, "unresolved dependent value");
    expect(registry.dependents_of(AssetId{0, 8}, output, count) == RegistryError::None,
           "empty dependents");
    expect(count == 0, "empty dependents count");

    AssetRegistry full;
    for (u32 index = 0; index < kMaxAssets; ++index) {
        expect(full.add(record(index + 1, "d/" + std::to_string(index))) == RegistryError::None,
               "fill asset");
    }
    u32 added = 0;
    for (u32 target = 1; target < kMaxAssets && added < kMaxDependencies; ++target) {
        for (u32 kind = 0; kind < 3 && added < kMaxDependencies; ++kind) {
            const AssetRegistry::DependencyEdge edge{
                AssetId{0, 1}, AssetId{0, target + 1},
                static_cast<AssetRegistry::DependencyKind>(kind)};
            expect(full.add_dependency(edge) == RegistryError::None, "fill edge");
            ++added;
        }
    }
    expect(full.dependency_count() == kMaxDependencies, "edge capacity");
    const AssetRegistry::DependencyEdge overflow{
        AssetId{0, 1}, AssetId{0, 64}, AssetRegistry::DependencyKind::Runtime};
    expect(full.add_dependency(overflow) == RegistryError::CapacityFull, "edge full");
    expect(full.dependency_count() == kMaxDependencies, "edge capacity stable");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data02_dependency_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "dep01") { success = run_dep01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
