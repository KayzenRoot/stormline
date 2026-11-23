#include "stormline/graphics/geometry/geometry_instance.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::geometry;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] InstanceDesc instance(u32 id, u32 mesh, u32 material) {
    InstanceDesc value{};
    value.id = id;
    value.mesh_id = mesh;
    value.material_id = material;
    value.bounds.center = Vec3{1.0f, 2.0f, 3.0f};
    value.bounds.radius = 1.0f;
    value.bounds.known = true;
    return value;
}

bool run_ins01() {
    begin();
    InstanceSet set{};
    set.scene_generation = 1;
    expect(add_instance(set, instance(1, 10, 20)) == GeometryError::None, "add 1");
    expect(add_instance(set, instance(2, 10, 20)) == GeometryError::None, "add 2");
    expect(add_instance(set, instance(3, 11, 20)) == GeometryError::None, "add 3");
    expect(add_instance(set, instance(3, 12, 20)) == GeometryError::DuplicateId,
           "duplicate");
    expect(add_instance(set, InstanceDesc{}) == GeometryError::InvalidArgument,
           "empty");
    InstanceDesc invalid_radius = instance(4, 10, 20);
    invalid_radius.bounds.radius = -1.0f;
    expect(add_instance(set, invalid_radius) == GeometryError::InvalidBounds,
           "negative radius");
    invalid_radius = instance(4, 10, 20);
    invalid_radius.bounds.radius = std::numeric_limits<f32>::quiet_NaN();
    expect(add_instance(set, invalid_radius) == GeometryError::InvalidBounds,
           "nan radius");
    invalid_radius = instance(4, 10, 20);
    invalid_radius.bounds.center.x = std::numeric_limits<f32>::infinity();
    expect(add_instance(set, invalid_radius) == GeometryError::InvalidBounds,
           "infinite center");

    InstanceDesc unknown = instance(4, 11, 21);
    unknown.bounds.known = false;
    expect(add_instance(set, unknown) == GeometryError::None, "unknown bounds");
    expect(set.count == 4, "count");

    GeometryDiagnostic diagnostic{};
    InstanceSet invalid_set = set;
    invalid_set.scene_generation = 0;
    expect(validate_instances(invalid_set, diagnostic)
               == GeometryError::InvalidArgument,
           "generation");

    BatchPlan plan{};
    expect(plan_batches(set, plan, diagnostic) == GeometryError::None, "batches");
    expect(plan.count == 3, "batch count");
    expect(plan.batches[0].mesh_id == 10 && plan.batches[0].material_id == 20
               && plan.batches[0].count == 2,
           "batch 0");
    expect(plan.batches[1].mesh_id == 11 && plan.batches[1].material_id == 20
               && plan.batches[1].count == 1,
           "batch 1");
    expect(plan.batches[2].mesh_id == 11 && plan.batches[2].material_id == 21
               && plan.batches[2].count == 1,
           "batch 2");

    InstanceSet full{};
    full.scene_generation = 1;
    for (u32 index = 0; index < kMaxInstances; ++index) {
        expect(add_instance(full, instance(index + 1, 1, 1)) == GeometryError::None,
               "fill");
    }
    expect(add_instance(full, instance(kMaxInstances + 1, 1, 1))
               == GeometryError::CapacityFull,
           "capacity");

    InstanceSet many_batches{};
    many_batches.scene_generation = 1;
    for (u32 index = 0; index < kMaxBatches + 1; ++index) {
        expect(add_instance(many_batches, instance(index + 1, index + 1, 1))
                   == GeometryError::None, "many batch add");
    }
    expect(plan_batches(many_batches, plan, diagnostic) == GeometryError::CapacityFull,
           "batch capacity");

    expect(std::string_view(geometry_error_name(GeometryError::DuplicateId))
               == "DuplicateId", "error name");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx04_instance_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "ins01") { success = run_ins01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
