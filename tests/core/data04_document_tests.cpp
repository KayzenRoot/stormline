#include "stormline/data/scene/scene_document.hpp"

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

[[nodiscard]] ComponentRecord component(u64 id, u64 entity_id, u32 type) {
    ComponentRecord value{};
    value.id = ComponentId{id};
    value.entity = EntityId{entity_id};
    value.type_id = type;
    value.type_version = 1;
    return value;
}

[[nodiscard]] AssetRef asset_ref(u64 asset, u64 entity_id, u32 role) {
    AssetRef value{};
    value.asset = registry::AssetId{0, asset};
    value.entity = EntityId{entity_id};
    value.role = role;
    return value;
}

[[nodiscard]] SceneDocument make_document() {
    SceneDocument document;
    (void)document.init(SceneId{1}, registry::ProjectId{1}, SchemaDescriptor{1, 1, 0, 1});
    return document;
}

bool run_doc01() {
    begin();
    SceneDocument document;
    expect(document.init(SceneId{}, registry::ProjectId{1}, SchemaDescriptor{1, 1, 0, 1})
           == SceneError::InvalidArgument, "invalid scene");
    expect(document.init(SceneId{1}, registry::ProjectId{}, SchemaDescriptor{1, 1, 0, 1})
           == SceneError::InvalidArgument, "invalid project");
    expect(document.init(SceneId{1}, registry::ProjectId{1}, SchemaDescriptor{2, 1, 0, 1})
           == SceneError::InvalidSchema, "invalid schema");
    expect(document.init(SceneId{1}, registry::ProjectId{1}, SchemaDescriptor{1, 1, 0, 1})
           == SceneError::None, "init");
    expect(document.scene().value == 1 && document.revision() == 1, "init values");

    expect(document.add_entity(entity(1, 0, "root")) == SceneError::None, "root");
    EntityRecord found{};
    expect(document.find_entity(EntityId{1}, found) == SceneError::None
           && found.name_length == 4, "find root");
    expect(document.add_entity(entity(1, 0, "other")) == SceneError::DuplicateId,
           "duplicate entity");
    expect(document.add_entity(entity(2, 0, "")) == SceneError::InvalidArgument,
           "empty name");
    expect(document.add_entity(entity(2, 0, "bad:name")) == SceneError::InvalidArgument,
           "bad name");
    expect(document.add_entity(entity(2, 2, "self")) == SceneError::ParentCycle,
           "self parent");
    expect(document.add_entity(entity(2, 9, "missing")) == SceneError::NotFound,
           "missing parent");
    expect(document.add_entity(entity(2, 1, "child")) == SceneError::None, "child");

    expect(document.add_component(component(1, 1, 10)) == SceneError::None, "component");
    ComponentRecord component_out{};
    expect(document.find_component(ComponentId{1}, component_out) == SceneError::None
           && component_out.entity.value == 1, "find component");
    expect(document.add_component(component(1, 1, 10)) == SceneError::DuplicateId,
           "duplicate component");
    expect(document.add_component(component(2, 9, 10)) == SceneError::NotFound,
           "missing component entity");

    expect(document.add_asset_ref(asset_ref(7, 1, 1)) == SceneError::None, "asset ref");
    expect(document.add_asset_ref(asset_ref(7, 1, 1)) == SceneError::DuplicateId,
           "duplicate ref");
    expect(document.add_asset_ref(asset_ref(7, 1, 2)) == SceneError::None,
           "different role");
    expect(document.add_asset_ref(asset_ref(0, 1, 1)) == SceneError::InvalidArgument,
           "invalid asset");
    expect(document.add_asset_ref(asset_ref(7, 9, 1)) == SceneError::NotFound,
           "missing ref entity");

    expect(document.entity_count() == 2 && document.component_count() == 1
           && document.asset_ref_count() == 2, "counts");
    expect(document.remove_entity(EntityId{1}) == SceneError::None, "remove");
    expect(document.entity_count() == 1 && document.component_count() == 0
           && document.asset_ref_count() == 0, "cascade");
    expect(document.remove_entity(EntityId{9}) == SceneError::NotFound, "remove missing");
    expect(document.set_enabled(EntityId{2}, false) == SceneError::None, "disable");
    expect(document.find_entity(EntityId{2}, found) == SceneError::None && !found.enabled,
           "disabled value");
    expect(document.set_enabled(EntityId{9}, true) == SceneError::NotFound,
           "disable missing");

    SceneDocument full = make_document();
    for (u32 index = 0; index < kMaxEntities; ++index) {
        expect(full.add_entity(entity(index + 1, 0, "e" + std::to_string(index)))
               == SceneError::None, "fill entity");
    }
    expect(full.entity_count() == kMaxEntities, "entity capacity");
    expect(full.add_entity(entity(1000, 0, "overflow")) == SceneError::CapacityFull,
           "entity full");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data04_document_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "doc01") { success = run_doc01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
