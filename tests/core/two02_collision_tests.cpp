#include "stormline/tilemap/collision_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::tilemap;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

TileCollisionDesc valid_collision() {
    TileCollisionDesc collision{};
    collision.tile_id = 42;
    collision.revision = 1;
    collision.shape_count = 2;
    collision.shapes[0] = CollisionShapeDesc{1, 1, CollisionShapeKind::Rect,
                                              0.0f, 0.0f, 16.0f, 16.0f,
                                              true, false};
    collision.shapes[1] = CollisionShapeDesc{2, 1, CollisionShapeKind::Segment,
                                              0.0f, 16.0f, 16.0f, 0.0f,
                                              false, false};
    return collision;
}

bool run_col01() {
    begin();
    TileCollisionDesc collision = valid_collision();
    TileCollisionPlan plan{};
    TilemapDiagnostic diagnostic{};

    expect(plan_tile_collision(collision, plan, diagnostic)
               == TilemapError::None,
           "valid collision");
    expect(plan.shape_count == 2 && plan.solid_count == 1, "valid plan");

    collision.tile_id = 0;
    expect(plan_tile_collision(collision, plan, diagnostic)
               == TilemapError::InvalidArgument,
           "zero tile");
    expect(plan.shape_count == 0 && plan.solid_count == 0, "reset");

    collision = valid_collision();
    collision.shape_count = kMaxCollisionShapes + 1;
    expect(plan_tile_collision(collision, plan, diagnostic)
               == TilemapError::CapacityFull,
           "shape cap");
    collision = valid_collision();
    collision.shapes[0].width = 0.0f;
    expect(plan_tile_collision(collision, plan, diagnostic)
               == TilemapError::CollisionInvalid,
           "zero rect width");
    collision = valid_collision();
    collision.shapes[0].height = -1.0f;
    expect(plan_tile_collision(collision, plan, diagnostic)
               == TilemapError::CollisionInvalid,
           "negative rect height");
    collision = valid_collision();
    collision.shapes[1].width = 0.0f;
    collision.shapes[1].height = 0.0f;
    expect(plan_tile_collision(collision, plan, diagnostic)
               == TilemapError::CollisionInvalid,
           "zero segment");
    collision = valid_collision();
    collision.shapes[0].x = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_tile_collision(collision, plan, diagnostic)
               == TilemapError::NonFiniteValue,
           "nonfinite shape");
    collision = valid_collision();
    collision.shapes[1].shape_id = 1;
    expect(plan_tile_collision(collision, plan, diagnostic)
               == TilemapError::DuplicateId,
           "duplicate shape");
    collision = valid_collision();
    collision.shapes[0].solid = false;
    collision.shapes[0].one_way = true;
    expect(plan_tile_collision(collision, plan, diagnostic)
               == TilemapError::CollisionInvalid,
           "one-way without solid");
    collision = valid_collision();
    collision.shapes[0].kind = static_cast<CollisionShapeKind>(200);
    expect(plan_tile_collision(collision, plan, diagnostic)
               == TilemapError::InvalidArgument,
           "invalid kind");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two02_collision_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "col01") { success = run_col01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
