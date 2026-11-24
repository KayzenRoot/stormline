#include "stormline/physics3d/shape_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::physics3d;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

ShapeDesc shape(u32 id, ShapeKind kind, bool sensor) {
    ShapeDesc desc{};
    desc.shape_id = id;
    desc.body_id = 1;
    desc.revision = 1;
    desc.kind = kind;
    desc.half_x = 1.0f;
    desc.half_y = 1.0f;
    desc.half_z = 1.0f;
    desc.radius = 0.5f;
    desc.half_height = 0.25f;
    desc.density = 1.0f;
    desc.material_id = 7;
    desc.sensor = sensor;
    return desc;
}

ShapeSetDesc shape_set() {
    ShapeSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.shape_count = 4;
    desc.shapes[0] = shape(1, ShapeKind::Sphere, false);
    desc.shapes[1] = shape(2, ShapeKind::Box, true);
    desc.shapes[2] = shape(3, ShapeKind::Capsule, false);
    desc.shapes[3] = shape(4, ShapeKind::Mesh, false);
    return desc;
}

bool run_shape301() {
    begin();
    ShapeSetDesc shapes = shape_set();
    ShapePlan plan{};
    Physics3DDiagnostic diagnostic{};
    expect(plan_shapes(shapes, plan, diagnostic) == Physics3DError::None,
           "valid shapes");
    expect(plan.shape_count == 4 && plan.sphere_count == 1
               && plan.box_count == 1 && plan.capsule_count == 1
               && plan.mesh_count == 1 && plan.sensor_count == 1,
           "valid plan");
    expect(diagnostic.code == Physics3DError::None, "success diagnostic");

    ShapePlan repeat{};
    expect(plan_shapes(shapes, repeat, diagnostic) == Physics3DError::None,
           "repeat shapes");
    expect(repeat.sensor_count == plan.sensor_count, "deterministic plan");

    shapes.world_id = 0;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "zero world");
    expect(plan.shape_count == 0, "reset on zero world");
    shapes = shape_set();
    shapes.revision = 0;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "zero revision");
    shapes = shape_set();
    shapes.shape_count = kMaxShapes + 1;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::CapacityFull,
           "shape overflow");

    shapes = shape_set();
    shapes.shapes[1].shape_id = 0;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::ShapeInvalid,
           "zero shape id");
    expect(diagnostic.index == 1, "zero shape diagnostic");
    shapes = shape_set();
    shapes.shapes[1].body_id = 0;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::ShapeInvalid,
           "zero body id");
    shapes = shape_set();
    shapes.shapes[1].revision = 0;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::ShapeInvalid,
           "zero revision");
    shapes = shape_set();
    shapes.shapes[1].material_id = 0;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::ShapeInvalid,
           "zero material");
    shapes = shape_set();
    shapes.shapes[1].kind = static_cast<ShapeKind>(9);
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::ShapeInvalid,
           "invalid kind");

    shapes = shape_set();
    shapes.shapes[2].radius = 0.0f;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::ShapeInvalid,
           "capsule zero radius");
    shapes = shape_set();
    shapes.shapes[2].half_height = -1.0f;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::ShapeInvalid,
           "capsule negative height");
    shapes = shape_set();
    shapes.shapes[1].half_z = 0.0f;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::ShapeInvalid,
           "box zero half extent");
    shapes = shape_set();
    shapes.shapes[0].radius = 0.0f;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::ShapeInvalid,
           "sphere zero radius");

    shapes = shape_set();
    shapes.shapes[1].density = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::NonFiniteValue,
           "non-finite density");
    shapes = shape_set();
    shapes.shapes[1].density = -1.0f;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "negative density");
    shapes = shape_set();
    shapes.shapes[2].shape_id = 1;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics3DError::DuplicateId,
           "duplicate shape");
    expect(diagnostic.index == 2, "duplicate shape diagnostic");

    shapes = shape_set();
    shapes.shape_count = kMaxShapes;
    for (u32 index = 0; index < kMaxShapes; ++index) {
        shapes.shapes[index] =
            shape(index + 1, static_cast<ShapeKind>(index % 7), index % 2 == 0);
    }
    expect(plan_shapes(shapes, plan, diagnostic) == Physics3DError::None,
           "capacity shapes");
    expect(plan.shape_count == kMaxShapes
               && plan.sensor_count == kMaxShapes / 2,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim02_shape_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "shape301") { success = run_shape301(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
