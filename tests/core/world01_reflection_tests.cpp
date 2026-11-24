#include "stormline/world/reflection_plan.hpp"

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

ReflectionFieldDesc field(
    u32 id, u32 name, FieldKind kind, f32 minimum, f32 maximum,
    bool editable, bool serialized) {
    ReflectionFieldDesc desc{};
    desc.field_id = id;
    desc.name_id = name;
    desc.kind = kind;
    desc.range_min = minimum;
    desc.range_max = maximum;
    desc.editable = editable;
    desc.serialized = serialized;
    return desc;
}

ReflectionSetDesc reflection() {
    ReflectionSetDesc desc{};
    desc.world_epoch = 13;
    desc.type_count = 2;
    desc.types[0].type_id = 1;
    desc.types[0].version = 1;
    desc.types[0].field_count = 2;
    desc.types[0].fields[0] = field(
        1, 100, FieldKind::U32, 0.0f, 100.0f, true, true);
    desc.types[0].fields[1] = field(
        2, 101, FieldKind::F32, -1.0f, 1.0f, true, false);
    desc.types[1].type_id = 2;
    desc.types[1].version = 1;
    desc.types[1].field_count = 1;
    desc.types[1].fields[0] = field(
        1, 200, FieldKind::EntityRef, 0.0f, 0.0f, false, true);
    return desc;
}

bool run_ref01() {
    begin();
    ReflectionSetDesc reflected = reflection();
    ReflectionPlan plan{};
    WorldDiagnostic diagnostic{};

    expect(plan_reflection(reflected, plan, diagnostic) == WorldError::None,
           "valid reflection");
    expect(plan.type_count == 2 && plan.field_count == 3
               && plan.editable_count == 2 && plan.serialized_count == 2,
           "valid plan");
    ReflectionPlan repeat{};
    expect(plan_reflection(reflected, repeat, diagnostic) == WorldError::None,
           "repeat reflection");
    expect(plan.type_count == repeat.type_count
               && plan.field_count == repeat.field_count
               && plan.editable_count == repeat.editable_count
               && plan.serialized_count == repeat.serialized_count,
           "deterministic plan");

    reflected.world_epoch = 0;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::InvalidArgument,
           "zero epoch");
    expect(plan.type_count == 0 && plan.field_count == 0,
           "reset on zero epoch");
    reflected = reflection();
    reflected.type_count = 0;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::ReflectionInvalid,
           "zero types");
    reflected.type_count = kMaxComponentTypes + 1;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::ReflectionInvalid,
           "type overflow");

    reflected = reflection();
    reflected.types[0].type_id = 0;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::ReflectionInvalid,
           "zero type id");
    reflected = reflection();
    reflected.types[0].version = 0;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::ReflectionInvalid,
           "zero version");
    reflected = reflection();
    reflected.types[1].type_id = 1;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::DuplicateId,
           "duplicate type");

    reflected = reflection();
    reflected.types[0].field_count = 0;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::ReflectionInvalid,
           "zero fields");
    reflected.types[0].field_count = kMaxComponentFields + 1;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::ReflectionInvalid,
           "field overflow");

    reflected = reflection();
    reflected.types[0].fields[0].field_id = 0;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::ReflectionInvalid,
           "zero field id");
    reflected = reflection();
    reflected.types[0].fields[0].name_id = 0;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::ReflectionInvalid,
           "zero name id");
    reflected = reflection();
    reflected.types[0].fields[1].field_id = 1;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::DuplicateId,
           "duplicate field id");
    reflected = reflection();
    reflected.types[0].fields[1].name_id = 100;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::DuplicateId,
           "duplicate name id");
    reflected = reflection();
    reflected.types[0].fields[0].kind = static_cast<FieldKind>(200);
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::ReflectionInvalid,
           "invalid kind");
    reflected = reflection();
    reflected.types[0].fields[0].range_min
        = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::NonFiniteValue,
           "nan range");
    reflected = reflection();
    reflected.types[0].fields[0].range_min = 2.0f;
    reflected.types[0].fields[0].range_max = 1.0f;
    expect(plan_reflection(reflected, plan, diagnostic)
               == WorldError::OutOfRange,
           "reversed range");

    reflected = reflection();
    reflected.type_count = kMaxComponentTypes;
    for (u32 index = 0; index < kMaxComponentTypes; ++index) {
        reflected.types[index].type_id = index + 1;
        reflected.types[index].version = 1;
        reflected.types[index].field_count = 1;
        reflected.types[index].fields[0] = field(
            1, 1000 + index, FieldKind::U32, 0.0f, 1.0f, false, false);
    }
    expect(plan_reflection(reflected, plan, diagnostic) == WorldError::None,
           "capacity reflection");
    expect(plan.type_count == kMaxComponentTypes
               && plan.field_count == kMaxComponentTypes
               && plan.editable_count == 0,
           "capacity counts");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world01_reflection_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "ref01") { success = run_ref01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
