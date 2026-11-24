#include "stormline/scene/prefab_variant_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::scene;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

VariantOverrideDesc override_desc(u32 node, u32 type, u32 field) {
    VariantOverrideDesc desc{};
    desc.node_id = node;
    desc.component_type_id = type;
    desc.field_id = field;
    return desc;
}

PrefabVariantDesc variant() {
    PrefabVariantDesc desc{};
    desc.variant_id = 40;
    desc.revision = 1;
    desc.base_prefab_id = 30;
    desc.base_revision = 2;
    desc.override_count = 3;
    desc.overrides[0] = override_desc(1, 10, 1);
    desc.overrides[1] = override_desc(1, 10, 2);
    desc.overrides[2] = override_desc(2, 11, 1);
    return desc;
}

bool run_var01() {
    begin();
    PrefabVariantDesc value = variant();
    PrefabVariantPlan plan{};
    SceneDiagnostic diagnostic{};

    expect(plan_prefab_variant(value, plan, diagnostic) == SceneError::None,
           "valid variant");
    expect(plan.override_count == 3, "valid plan");
    PrefabVariantPlan repeat{};
    expect(plan_prefab_variant(value, repeat, diagnostic) == SceneError::None,
           "repeat variant");
    expect(plan.override_count == repeat.override_count,
           "deterministic plan");

    value.variant_id = 0;
    expect(plan_prefab_variant(value, plan, diagnostic)
               == SceneError::InvalidArgument,
           "zero variant");
    expect(plan.override_count == 0, "reset on zero variant");
    value = variant();
    value.revision = 0;
    expect(plan_prefab_variant(value, plan, diagnostic)
               == SceneError::InvalidArgument,
           "zero revision");
    value = variant();
    value.base_prefab_id = 0;
    expect(plan_prefab_variant(value, plan, diagnostic)
               == SceneError::InvalidArgument,
           "zero base prefab");
    value = variant();
    value.base_revision = 0;
    expect(plan_prefab_variant(value, plan, diagnostic)
               == SceneError::InvalidArgument,
           "zero base revision");

    value = variant();
    value.override_count = 0;
    expect(plan_prefab_variant(value, plan, diagnostic)
               == SceneError::VariantInvalid,
           "zero overrides");
    value.override_count = kMaxVariantOverrides + 1;
    expect(plan_prefab_variant(value, plan, diagnostic)
               == SceneError::VariantInvalid,
           "override overflow");

    value = variant();
    value.overrides[0].node_id = 0;
    expect(plan_prefab_variant(value, plan, diagnostic)
               == SceneError::VariantInvalid,
           "zero node");
    value = variant();
    value.overrides[0].component_type_id = 0;
    expect(plan_prefab_variant(value, plan, diagnostic)
               == SceneError::VariantInvalid,
           "zero type");
    value = variant();
    value.overrides[0].field_id = 0;
    expect(plan_prefab_variant(value, plan, diagnostic)
               == SceneError::VariantInvalid,
           "zero field");
    value = variant();
    value.overrides[1] = override_desc(1, 10, 1);
    expect(plan_prefab_variant(value, plan, diagnostic)
               == SceneError::DuplicateId,
           "duplicate key");
    value = variant();
    value.overrides[0].base_changed = true;
    value.overrides[0].variant_changed = true;
    expect(plan_prefab_variant(value, plan, diagnostic)
               == SceneError::VariantInvalid,
           "conflict");

    value = variant();
    value.override_count = kMaxVariantOverrides;
    for (u32 index = 0; index < kMaxVariantOverrides; ++index) {
        value.overrides[index] = override_desc(index + 1, 10, 1);
    }
    expect(plan_prefab_variant(value, plan, diagnostic) == SceneError::None,
           "capacity variant");
    expect(plan.override_count == kMaxVariantOverrides, "capacity count");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world02_variant_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "var01") { success = run_var01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
