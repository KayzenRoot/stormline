#include "stormline/physics2d/shape_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::physics2d;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

ShapeDesc shape(
    u32 id, u32 body_id, ShapeKind kind, bool sensor) {
    ShapeDesc desc{};
    desc.shape_id = id;
    desc.body_id = body_id;
    desc.revision = 1;
    desc.kind = kind;
    desc.half_x = 1.0f;
    desc.half_y = 0.5f;
    desc.radius = 0.75f;
    desc.density = 1.0f;
    desc.sensor = sensor;
    return desc;
}

ShapeSetDesc shape_set() {
    ShapeSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.shape_count = 4;
    desc.shapes[0] = shape(1, 1, ShapeKind::Circle, false);
    desc.shapes[1] = shape(2, 1, ShapeKind::Box, false);
    desc.shapes[2] = shape(3, 2, ShapeKind::Capsule, true);
    desc.shapes[3] = shape(4, 2, ShapeKind::Polygon, false);
    return desc;
}

bool run_col01() {
    begin();
    ShapeSetDesc shapes = shape_set();
    ShapePlan plan{};
    Physics2DDiagnostic diagnostic{};
    expect(plan_shapes(shapes, plan, diagnostic) == Physics2DError::None,
           "valid shapes");
    expect(plan.shape_count == 4 && plan.circle_count == 1
               && plan.box_count == 1 && plan.capsule_count == 1
               && plan.polygon_count == 1 && plan.sensor_count == 1,
           "valid plan");
    expect(diagnostic.code == Physics2DError::None, "success diagnostic");
    ShapePlan repeat{};
    expect(plan_shapes(shapes, repeat, diagnostic) == Physics2DError::None,
           "repeat shapes");
    expect(repeat.sensor_count == plan.sensor_count
               && repeat.polygon_count == plan.polygon_count,
           "deterministic plan");

    shapes.world_id = 0;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::InvalidArgument,
           "zero world");
    expect(plan.shape_count == 0 && plan.sensor_count == 0,
           "reset on zero world");
    shapes = shape_set();
    shapes.revision = 0;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::InvalidArgument,
           "zero revision");
    shapes = shape_set();
    shapes.shape_count = kMaxShapes + 1;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::CapacityFull,
           "shape overflow");

    shapes = shape_set();
    shapes.shapes[1].shape_id = 0;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::ShapeInvalid,
           "zero shape id");
    expect(diagnostic.index == 1, "zero shape diagnostic");
    shapes = shape_set();
    shapes.shapes[1].body_id = 0;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::ShapeInvalid,
           "zero body ref");
    shapes = shape_set();
    shapes.shapes[1].revision = 0;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::ShapeInvalid,
           "zero shape revision");
    shapes = shape_set();
    shapes.shapes[1].kind =
        static_cast<ShapeKind>(static_cast<u8>(99));
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::ShapeInvalid,
           "unknown kind");
    shapes = shape_set();
    shapes.shapes[3].shape_id = 1;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::DuplicateId,
           "duplicate shape");
    expect(diagnostic.index == 3, "duplicate shape diagnostic");

    shapes = shape_set();
    shapes.shapes[0].radius = 0.0f;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::ShapeInvalid,
           "zero circle radius");
    shapes = shape_set();
    shapes.shapes[1].half_x = 0.0f;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::ShapeInvalid,
           "zero box half x");
    shapes = shape_set();
    shapes.shapes[1].half_y = -1.0f;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::ShapeInvalid,
           "negative box half y");
    shapes = shape_set();
    shapes.shapes[0].radius = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::NonFiniteValue,
           "nan dimension");
    shapes = shape_set();
    shapes.shapes[0].density = -1.0f;
    expect(plan_shapes(shapes, plan, diagnostic)
               == Physics2DError::OutOfRange,
           "negative density");

    shapes = shape_set();
    shapes.shape_count = kMaxShapes;
    for (u32 index = 0; index < kMaxShapes; ++index) {
        shapes.shapes[index] =
            shape(index + 1, index % 2 + 1,
                  static_cast<ShapeKind>(index % 4), index % 2 == 0);
    }
    expect(plan_shapes(shapes, plan, diagnostic) == Physics2DError::None,
           "capacity shapes");
    expect(plan.shape_count == kMaxShapes && plan.circle_count == 32
               && plan.box_count == 32 && plan.capsule_count == 32
               && plan.polygon_count == 32 && plan.sensor_count == 64,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim01_shape_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "col01") { success = run_col01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
