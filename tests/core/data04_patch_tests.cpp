#include "stormline/data/scene/scene_patch.hpp"

#include <array>
#include <cstdio>
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

[[nodiscard]] EntityRecord entity(u64 id, u64 parent, std::string_view name) {
    EntityRecord value{};
    value.id = EntityId{id};
    value.parent = EntityId{parent};
    value.name_length = static_cast<u32>(name.size());
    for (u32 index = 0; index < value.name_length; ++index) {
        value.name[index] = name[index];
    }
    return value;
}

[[nodiscard]] SceneDocument make_document() {
    SceneDocument document;
    (void)document.init(SceneId{1}, registry::ProjectId{1}, SchemaDescriptor{1, 1, 0, 1});
    (void)document.add_entity(entity(1, 0, "root"));
    (void)document.add_entity(entity(2, 1, "child"));
    return document;
}

[[nodiscard]] PatchOperation add_op(u64 id, u64 parent, std::string_view name) {
    PatchOperation operation{};
    operation.kind = PatchOp::AddEntity;
    operation.entity = entity(id, parent, name);
    return operation;
}

[[nodiscard]] PatchOperation remove_op(u64 id) {
    PatchOperation operation{};
    operation.kind = PatchOp::RemoveEntity;
    operation.target = EntityId{id};
    return operation;
}

[[nodiscard]] PatchOperation enable_op(u64 id, bool enabled) {
    PatchOperation operation{};
    operation.kind = PatchOp::SetEnabled;
    operation.target = EntityId{id};
    operation.enabled = enabled;
    return operation;
}

bool run_patch01() {
    begin();
    SceneDocument document = make_document();
    expect(document.revision() == 1, "initial revision");
    ScenePatch patch{1, 1, SceneId{1}};
    std::array<PatchOperation, 3> operations{
        add_op(3, 1, "added"), enable_op(2, false), remove_op(1)};
    expect(apply_patch(document, patch, operations) == SceneError::None, "apply");
    expect(document.revision() == 2, "revision bump");
    expect(document.entity_count() == 2, "remove count");
    EntityRecord found{};
    expect(document.find_entity(EntityId{1}, found) == SceneError::NotFound, "removed");
    expect(document.find_entity(EntityId{3}, found) == SceneError::None, "added");
    expect(document.find_entity(EntityId{2}, found) == SceneError::None && !found.enabled,
           "disabled");

    const u64 revision = document.revision();
    ScenePatch stale{2, 1, SceneId{1}};
    expect(apply_patch(document, stale, operations) == SceneError::StaleRevision, "stale");
    expect(document.revision() == revision, "stale unchanged");

    ScenePatch wrong_scene{3, revision, SceneId{2}};
    expect(apply_patch(document, wrong_scene, operations) == SceneError::InvalidPatch,
           "wrong scene");
    ScenePatch zero{0, revision, SceneId{1}};
    expect(apply_patch(document, zero, operations) == SceneError::InvalidArgument, "zero op");

    ScenePatch failed{4, revision, SceneId{1}};
    std::array<PatchOperation, 2> bad{add_op(6, 0, "ok"), add_op(7, 99, "missing")};
    expect(apply_patch(document, failed, bad) == SceneError::NotFound, "failed patch");
    expect(document.revision() == revision && document.entity_count() == 2,
           "failure atomic");
    expect(document.find_entity(EntityId{6}, found) == SceneError::NotFound,
           "failed add rollback");

    std::array<PatchOperation, kMaxPatchOps + 1> too_many{};
    expect(apply_patch(document, failed, too_many) == SceneError::InvalidPatch,
           "too many ops");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data04_patch_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "patch01") { success = run_patch01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
