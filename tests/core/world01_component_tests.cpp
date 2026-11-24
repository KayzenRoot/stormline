#include "stormline/world/component_schema_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::world;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

ComponentFieldDesc field(u32 id, FieldKind kind, f32 minimum, f32 maximum) {
    ComponentFieldDesc desc{};
    desc.field_id = id;
    desc.kind = kind;
    desc.range_min = minimum;
    desc.range_max = maximum;
    return desc;
}

ComponentSchemaDesc schema(u32 id) {
    ComponentSchemaDesc desc{};
    desc.type_id = id;
    desc.version = 1;
    desc.field_count = 1;
    desc.fields[0] = field(1, FieldKind::U32, 0.0f, 100.0f);
    return desc;
}

ComponentRegistryDesc registry() {
    ComponentRegistryDesc desc{};
    desc.world_epoch = 9;
    desc.type_count = 2;
    desc.types[0] = schema(1);
    desc.types[0].field_count = 2;
    desc.types[0].fields[0] = field(1, FieldKind::U32, 0.0f, 100.0f);
    desc.types[0].fields[1] = field(2, FieldKind::F32, -1.0f, 1.0f);
    desc.types[1] = schema(2);
    desc.types[1].fields[0] = field(1, FieldKind::EntityRef, 0.0f, 0.0f);
    return desc;
}

bool run_cmp01() {
    begin();
    ComponentRegistryDesc components = registry();
    ComponentRegistryPlan plan{};
    WorldDiagnostic diagnostic{};

    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::None,
           "valid registry");
    expect(plan.type_count == 2 && plan.field_count == 3, "valid plan");
    ComponentRegistryPlan repeat{};
    expect(plan_component_registry(components, repeat, diagnostic)
               == WorldError::None,
           "repeat registry");
    expect(plan.type_count == repeat.type_count
               && plan.field_count == repeat.field_count,
           "deterministic plan");

    components.world_epoch = 0;
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::InvalidArgument,
           "zero epoch");
    expect(plan.type_count == 0 && plan.field_count == 0,
           "reset on zero epoch");
    components = registry();
    components.type_count = 0;
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::ComponentInvalid,
           "zero types");
    components.type_count = kMaxComponentTypes + 1;
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::ComponentInvalid,
           "type overflow");

    components = registry();
    components.types[0].type_id = 0;
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::ComponentInvalid,
           "zero type id");
    components = registry();
    components.types[0].version = 0;
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::ComponentInvalid,
           "zero version");
    components = registry();
    components.types[1].type_id = 1;
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::DuplicateId,
           "duplicate type");

    components = registry();
    components.types[0].field_count = 0;
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::ComponentInvalid,
           "zero fields");
    components.types[0].field_count = kMaxComponentFields + 1;
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::ComponentInvalid,
           "field overflow");

    components = registry();
    components.types[0].fields[0].field_id = 0;
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::ComponentInvalid,
           "zero field id");
    components = registry();
    components.types[0].fields[1].field_id = 1;
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::DuplicateId,
           "duplicate field");
    components = registry();
    components.types[0].fields[0].kind = static_cast<FieldKind>(200);
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::ComponentInvalid,
           "invalid kind");
    components = registry();
    components.types[0].fields[0].range_min
        = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::NonFiniteValue,
           "nan range");
    components = registry();
    components.types[0].fields[0].range_max
        = std::numeric_limits<f32>::infinity();
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::NonFiniteValue,
           "infinite range");
    components = registry();
    components.types[0].fields[0].range_min = 2.0f;
    components.types[0].fields[0].range_max = 1.0f;
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::OutOfRange,
           "reversed range");

    components = registry();
    components.type_count = kMaxComponentTypes;
    for (u32 index = 0; index < kMaxComponentTypes; ++index) {
        components.types[index] = schema(index + 1);
        components.types[index].fields[0]
            = field(1, FieldKind::U32, 0.0f, 10.0f);
    }
    expect(plan_component_registry(components, plan, diagnostic)
               == WorldError::None,
           "capacity registry");
    expect(plan.type_count == kMaxComponentTypes
               && plan.field_count == kMaxComponentTypes,
           "capacity counts");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world01_component_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "cmp01") { success = run_cmp01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
