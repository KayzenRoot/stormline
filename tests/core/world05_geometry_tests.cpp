#include "stormline/procedural/geometry_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::procedural;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

GeometryRecipeDesc recipe(
    u32 id, PrimitiveKind primitive, f32 scale, u32 lod) {
    GeometryRecipeDesc desc{};
    desc.recipe_id = id;
    desc.revision = 1;
    desc.primitive = primitive;
    desc.source_asset_id = 100 + id;
    desc.unit_scale = scale;
    desc.lod_count = lod;
    return desc;
}

GeometrySetDesc geometry_set() {
    GeometrySetDesc desc{};
    desc.graph_id = 20;
    desc.revision = 1;
    desc.recipe_count = 4;
    desc.recipes[0] = recipe(1, PrimitiveKind::Box, 1.0f, 1);
    desc.recipes[1] = recipe(2, PrimitiveKind::Plane, 2.0f, 2);
    desc.recipes[2] = recipe(3, PrimitiveKind::Sphere, 0.5f, 4);
    desc.recipes[3] = recipe(4, PrimitiveKind::Heightfield, 4.0f, 8);
    return desc;
}

bool run_geo01() {
    begin();
    GeometrySetDesc geometry = geometry_set();
    GeometryPlan plan{};
    ProcDiagnostic diagnostic{};
    expect(plan_geometry(geometry, plan, diagnostic) == ProcError::None,
           "valid geometry");
    expect(plan.recipe_count == 4 && plan.box_count == 1
               && plan.plane_count == 1 && plan.sphere_count == 1
               && plan.heightfield_count == 1 && plan.max_unit_scale == 4.0f,
           "valid plan");
    expect(diagnostic.code == ProcError::None, "success diagnostic");
    GeometryPlan repeat{};
    expect(plan_geometry(geometry, repeat, diagnostic) == ProcError::None,
           "repeat geometry");
    expect(repeat.max_unit_scale == plan.max_unit_scale
               && repeat.heightfield_count == plan.heightfield_count,
           "deterministic plan");

    geometry.recipe_count = 0;
    expect(plan_geometry(geometry, plan, diagnostic) == ProcError::None,
           "empty geometry");
    expect(plan.recipe_count == 0 && plan.max_unit_scale == 0.0f,
           "empty plan");

    geometry = geometry_set();
    geometry.graph_id = 0;
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::InvalidArgument,
           "zero graph");
    expect(plan.recipe_count == 0 && plan.box_count == 0,
           "reset on zero graph");
    geometry = geometry_set();
    geometry.revision = 0;
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::InvalidArgument,
           "zero revision");
    geometry = geometry_set();
    geometry.recipe_count = kMaxGeometryRecipes + 1;
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::CapacityFull,
           "recipe overflow");

    geometry = geometry_set();
    geometry.recipes[1].recipe_id = 0;
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::GeometryInvalid,
           "zero recipe id");
    expect(diagnostic.index == 1, "zero recipe diagnostic");
    geometry = geometry_set();
    geometry.recipes[1].revision = 0;
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::GeometryInvalid,
           "zero recipe revision");
    geometry = geometry_set();
    geometry.recipes[1].source_asset_id = 0;
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::GeometryInvalid,
           "zero source");
    geometry = geometry_set();
    geometry.recipes[1].primitive =
        static_cast<PrimitiveKind>(static_cast<u8>(99));
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::GeometryInvalid,
           "unknown primitive");
    geometry = geometry_set();
    geometry.recipes[2].recipe_id = 1;
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::DuplicateId,
           "duplicate recipe");
    expect(diagnostic.index == 2, "duplicate recipe diagnostic");

    geometry = geometry_set();
    geometry.recipes[0].unit_scale = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::OutOfRange,
           "nan scale");
    geometry = geometry_set();
    geometry.recipes[0].unit_scale = 0.0f;
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::OutOfRange,
           "zero scale");
    geometry = geometry_set();
    geometry.recipes[0].unit_scale = -1.0f;
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::OutOfRange,
           "negative scale");
    geometry = geometry_set();
    geometry.recipes[0].lod_count = 0;
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::OutOfRange,
           "zero lod");
    geometry = geometry_set();
    geometry.recipes[0].lod_count = 9;
    expect(plan_geometry(geometry, plan, diagnostic)
               == ProcError::OutOfRange,
           "lod overflow");

    geometry = geometry_set();
    geometry.recipe_count = kMaxGeometryRecipes;
    for (u32 index = 0; index < kMaxGeometryRecipes; ++index) {
        geometry.recipes[index] =
            recipe(index + 1, static_cast<PrimitiveKind>(index % 4),
                   static_cast<f32>(index + 1), 1 + index % 8);
    }
    expect(plan_geometry(geometry, plan, diagnostic) == ProcError::None,
           "capacity geometry");
    expect(plan.recipe_count == kMaxGeometryRecipes
               && plan.box_count == 8 && plan.plane_count == 8
               && plan.sphere_count == 8 && plan.heightfield_count == 8
               && plan.max_unit_scale == 32.0f,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world05_geometry_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "geo01") { success = run_geo01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
