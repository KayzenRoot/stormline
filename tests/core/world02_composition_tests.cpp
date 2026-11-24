#include "stormline/scene/prefab_composition_plan.hpp"

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

PrefabRefDesc ref(u32 id) {
    PrefabRefDesc desc{};
    desc.prefab_id = id;
    desc.revision = 1;
    return desc;
}

PrefabSourceDesc prefab() {
    PrefabSourceDesc desc{};
    desc.prefab_id = 30;
    desc.revision = 1;
    desc.depth = 2;
    desc.nested_count = 2;
    desc.nested[0] = ref(31);
    desc.nested[1] = ref(32);
    return desc;
}

bool run_pfc01() {
    begin();
    PrefabSourceDesc source = prefab();
    PrefabCompositionPlan plan{};
    SceneDiagnostic diagnostic{};

    expect(plan_prefab_composition(source, plan, diagnostic)
               == SceneError::None,
           "valid prefab");
    expect(plan.nested_count == 2 && plan.depth == 2, "valid plan");
    PrefabCompositionPlan repeat{};
    expect(plan_prefab_composition(source, repeat, diagnostic)
               == SceneError::None,
           "repeat prefab");
    expect(plan.nested_count == repeat.nested_count
               && plan.depth == repeat.depth,
           "deterministic plan");

    source.prefab_id = 0;
    expect(plan_prefab_composition(source, plan, diagnostic)
               == SceneError::InvalidArgument,
           "zero prefab");
    expect(plan.nested_count == 0 && plan.depth == 0,
           "reset on zero prefab");
    source = prefab();
    source.revision = 0;
    expect(plan_prefab_composition(source, plan, diagnostic)
               == SceneError::InvalidArgument,
           "zero revision");
    source = prefab();
    source.depth = kMaxPrefabDepth + 1;
    expect(plan_prefab_composition(source, plan, diagnostic)
               == SceneError::DepthExceeded,
           "depth overflow");
    source = prefab();
    source.nested_count = kMaxPrefabRefs + 1;
    expect(plan_prefab_composition(source, plan, diagnostic)
               == SceneError::PrefabInvalid,
           "nested overflow");

    source = prefab();
    source.nested[0].prefab_id = 0;
    expect(plan_prefab_composition(source, plan, diagnostic)
               == SceneError::PrefabInvalid,
           "zero nested id");
    source = prefab();
    source.nested[0].revision = 0;
    expect(plan_prefab_composition(source, plan, diagnostic)
               == SceneError::PrefabInvalid,
           "zero nested revision");
    source = prefab();
    source.nested[0].prefab_id = 30;
    expect(plan_prefab_composition(source, plan, diagnostic)
               == SceneError::PrefabInvalid,
           "self reference");
    source = prefab();
    source.nested[1].prefab_id = 31;
    expect(plan_prefab_composition(source, plan, diagnostic)
               == SceneError::DuplicateId,
           "duplicate nested");

    source = prefab();
    source.nested_count = 0;
    expect(plan_prefab_composition(source, plan, diagnostic)
               == SceneError::None,
           "no nested");
    expect(plan.nested_count == 0, "no nested plan");

    source = prefab();
    source.depth = kMaxPrefabDepth;
    source.nested_count = kMaxPrefabRefs;
    for (u32 index = 0; index < kMaxPrefabRefs; ++index) {
        source.nested[index] = ref(index + 40);
    }
    expect(plan_prefab_composition(source, plan, diagnostic)
               == SceneError::None,
           "capacity prefab");
    expect(plan.nested_count == kMaxPrefabRefs
               && plan.depth == kMaxPrefabDepth,
           "capacity counts");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world02_composition_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "pfc01") { success = run_pfc01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
