#include "stormline/graphics/material/decal.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::material;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] DecalDesc decal(u32 id, u32 layer) {
    DecalDesc value{};
    value.id = id;
    value.layer = layer;
    value.x = 1.0f;
    value.y = 2.0f;
    value.z = 3.0f;
    value.radius = 0.5f;
    value.opacity = 1.0f;
    return value;
}

bool run_dec01() {
    begin();
    DecalPlan plan{};
    MaterialDiagnostic diagnostic{};

    expect(plan_decals(DecalSet{}, plan, diagnostic) == MaterialError::None,
           "empty");
    expect(plan.count == 0, "empty count");

    DecalSet set{};
    set.count = 3;
    set.decals[0] = decal(20, 2);
    set.decals[1] = decal(10, 1);
    set.decals[2] = decal(30, 2);
    expect(plan_decals(set, plan, diagnostic) == MaterialError::None, "plan");
    expect(plan.count == 3, "plan count");
    expect(plan.decal_ids[0] == 10 && plan.decal_ids[1] == 20
               && plan.decal_ids[2] == 30,
           "layer id order");

    set.decals[0] = decal(20, 1);
    set.decals[1] = decal(10, 1);
    set.decals[2] = decal(30, 1);
    expect(plan_decals(set, plan, diagnostic) == MaterialError::None,
           "same layer");
    expect(plan.decal_ids[0] == 10 && plan.decal_ids[1] == 20
               && plan.decal_ids[2] == 30,
           "id order");

    set.decals[1] = decal(20, 1);
    expect(plan_decals(set, plan, diagnostic)
               == MaterialError::DecalConflict,
           "duplicate");
    expect(plan.count == 0, "duplicate reset");
    expect(diagnostic.code == MaterialError::DecalConflict, "duplicate diag");

    set.decals[1] = decal(0, 1);
    expect(plan_decals(set, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "zero id");
    set.decals[1] = decal(10, 32);
    expect(plan_decals(set, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "layer");
    set.decals[1] = decal(10, 1);
    set.decals[1].radius = 0.0f;
    expect(plan_decals(set, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "radius zero");
    set.decals[1].radius = -1.0f;
    expect(plan_decals(set, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "radius negative");
    set.decals[1].radius = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_decals(set, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "radius nan");
    set.decals[1] = decal(10, 1);
    set.decals[1].opacity = -0.1f;
    expect(plan_decals(set, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "opacity low");
    set.decals[1].opacity = 1.1f;
    expect(plan_decals(set, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "opacity high");
    set.decals[1] = decal(10, 1);
    set.decals[1].x = std::numeric_limits<f32>::infinity();
    expect(plan_decals(set, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "position");
    expect(diagnostic.index == 1, "diagnostic index");

    set.decals[0] = decal(1, 0);
    set.decals[1] = decal(2, 0);
    set.decals[2] = decal(3, 0);
    set.count = kMaxDecals + 1;
    expect(plan_decals(set, plan, diagnostic)
               == MaterialError::CapacityFull,
           "capacity");
    expect(plan.count == 0, "capacity reset");

    set.count = kMaxDecals;
    for (u32 index = 0; index < set.count; ++index) {
        set.decals[index] = decal(index + 1, index % 7);
    }
    expect(plan_decals(set, plan, diagnostic) == MaterialError::None,
           "max valid");
    expect(plan.count == kMaxDecals, "max count");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx05_decal_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "dec01") { success = run_dec01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
