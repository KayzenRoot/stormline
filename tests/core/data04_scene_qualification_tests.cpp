#include "stormline/data/scene/scene_diff.hpp"
#include "stormline/data/scene/scene_patch.hpp"

#include <array>
#include <cstdio>
#include <string>
#include <string_view>

namespace {
using namespace stormline::data::scene;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] EntityRecord entity(u64 id, std::string_view name) {
    EntityRecord value{};
    value.id = EntityId{id};
    value.name_length = static_cast<u32>(name.size());
    for (u32 index = 0; index < value.name_length; ++index) {
        value.name[index] = name[index];
    }
    return value;
}

[[nodiscard]] SceneDocument document() {
    SceneDocument value;
    (void)value.init(SceneId{1}, registry::ProjectId{1}, SchemaDescriptor{1, 1, 0, 1});
    return value;
}

bool run_qlf_s01() {
    begin();
    SceneDocument scene = document();
    expect(scene.add_entity(entity(1, "root")) == SceneError::None, "root");
    expect(scene.add_entity(entity(2, "child")) == SceneError::None, "child");
    ComponentRecord component{ComponentId{1}, EntityId{1}, 10, 1};
    expect(scene.add_component(component) == SceneError::None, "component");
    AssetRef ref{registry::AssetId{0, 7}, EntityId{1}, 1};
    expect(scene.add_asset_ref(ref) == SceneError::None, "ref");

    ScenePatch patch{1, 1, SceneId{1}};
    std::array<PatchOperation, 1> operations{};
    operations[0].kind = PatchOp::AddEntity;
    operations[0].entity = entity(3, "added");
    expect(apply_patch(scene, patch, operations) == SceneError::None, "patch");
    expect(scene.revision() == 2 && scene.entity_count() == 3, "patch values");

    SceneDocument before = document();
    (void)before.add_entity(entity(1, "root"));
    std::array<DiffEntry, 4> output{};
    u32 count = 0;
    expect(diff(before, scene, output, count) == SceneError::None, "diff");
    expect(count >= 1 && output[0].kind == DiffKind::Added, "diff added");
    return finish();
}

struct Snapshot {
    u64 revision{0};
    u32 entities{0};
    u32 components{0};
    u32 refs{0};
    u32 diff_count{0};
};

[[nodiscard]] bool snapshot(Snapshot& out) {
    SceneDocument scene = document();
    if (scene.add_entity(entity(1, "root")) != SceneError::None
        || scene.add_entity(entity(2, "child")) != SceneError::None) {
        return false;
    }
    ScenePatch patch{1, 1, SceneId{1}};
    std::array<PatchOperation, 1> operations{};
    operations[0].kind = PatchOp::SetEnabled;
    operations[0].target = EntityId{2};
    operations[0].enabled = false;
    if (apply_patch(scene, patch, operations) != SceneError::None) {
        return false;
    }
    SceneDocument base = document();
    if (base.add_entity(entity(1, "root")) != SceneError::None) {
        return false;
    }
    std::array<DiffEntry, 4> diff_entries{};
    if (diff(base, scene, diff_entries, out.diff_count) != SceneError::None) {
        return false;
    }
    out.revision = scene.revision();
    out.entities = scene.entity_count();
    out.components = scene.component_count();
    out.refs = scene.asset_ref_count();
    return true;
}

bool run_qlf_s02() {
    begin();
    Snapshot first{};
    Snapshot second{};
    expect(snapshot(first), "first");
    expect(snapshot(second), "second");
    expect(first.revision == second.revision, "revision repeat");
    expect(first.entities == second.entities, "entity repeat");
    expect(first.components == second.components, "component repeat");
    expect(first.refs == second.refs, "ref repeat");
    expect(first.diff_count == second.diff_count, "diff repeat");
    return finish();
}

bool run_qlf_s03() {
    begin();
    SceneDocument scene;
    expect(scene.init(SceneId{1}, registry::ProjectId{1}, SchemaDescriptor{1, 4, 0, 1})
           == SceneError::UnsupportedSchema, "schema error");
    expect(scene.init(SceneId{1}, registry::ProjectId{1}, SchemaDescriptor{1, 1, 0, 1})
           == SceneError::None, "after schema");
    expect(scene.add_entity(entity(1, "root")) == SceneError::None, "add");
    expect(scene.add_entity(entity(1, "duplicate")) == SceneError::DuplicateId, "duplicate");
    expect(scene.add_entity(entity(2, "child")) == SceneError::None, "after duplicate");
    expect(scene.add_entity(entity(3, "self")) == SceneError::None, "third");
    ScenePatch stale{1, 99, SceneId{1}};
    std::array<PatchOperation, 1> operations{};
    operations[0].kind = PatchOp::SetEnabled;
    operations[0].target = EntityId{1};
    operations[0].enabled = false;
    expect(apply_patch(scene, stale, operations) == SceneError::StaleRevision, "stale");
    ScenePatch valid{2, 1, SceneId{1}};
    expect(apply_patch(scene, valid, operations) == SceneError::None, "after stale");

    SceneDocument other;
    (void)other.init(SceneId{2}, registry::ProjectId{1}, SchemaDescriptor{1, 1, 0, 1});
    std::array<DiffEntry, 2> diff_entries{};
    u32 count = 0;
    expect(diff(scene, other, diff_entries, count) == SceneError::InvalidArgument,
           "diff mismatch");
    return finish();
}

bool run_qlf_s04() {
    begin();
    SceneDocument scene = document();
    u32 entities = 0;
    for (u32 index = 0; index < 10000; ++index) {
        const SceneError status = scene.add_entity(
            entity(index + 1, "e" + std::to_string(index)));
        if (status == SceneError::None) {
            ++entities;
        } else {
            expect(status == SceneError::CapacityFull, "entity overload");
        }
    }
    expect(entities == kMaxEntities, "entity capacity");

    u32 components = 0;
    for (u32 index = 0; index < 10000; ++index) {
        const SceneError status = scene.add_component(
            ComponentRecord{ComponentId{index + 1}, EntityId{1}, 10, 1});
        if (status == SceneError::None) {
            ++components;
        } else {
            expect(status == SceneError::CapacityFull, "component overload");
        }
    }
    expect(components == kMaxComponents, "component capacity");

    u32 refs = 0;
    for (u32 index = 0; index < 10000; ++index) {
        const SceneError status = scene.add_asset_ref(
            AssetRef{registry::AssetId{0, index + 1}, EntityId{1}, index});
        if (status == SceneError::None) {
            ++refs;
        } else {
            expect(status == SceneError::CapacityFull, "ref overload");
        }
    }
    expect(refs == kMaxAssetRefs, "ref capacity");

    for (u32 index = 0; index < 10000; ++index) {
        ScenePatch patch{index + 1, scene.revision(), SceneId{1}};
        std::array<PatchOperation, 1> operations{};
        operations[0].kind = PatchOp::SetEnabled;
        operations[0].target = EntityId{1};
        operations[0].enabled = (index % 2) == 0;
        expect(apply_patch(scene, patch, operations) == SceneError::None, "patch overload");
    }
    expect(scene.revision() == 10001, "revision monotonic");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data04_scene_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") { success = run_qlf_s01(); }
    else if (mode == "qlf02") { success = run_qlf_s02(); }
    else if (mode == "qlf03") { success = run_qlf_s03(); }
    else if (mode == "qlf04") { success = run_qlf_s04(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
