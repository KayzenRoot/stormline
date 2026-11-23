#include "stormline/tilemap/collision_plan.hpp"
#include "stormline/tilemap/grid_plan.hpp"
#include "stormline/tilemap/parallax_plan.hpp"
#include "stormline/tilemap/streaming_plan.hpp"
#include "stormline/tilemap/tile_plan.hpp"

#include <cstdio>
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

struct Pipeline {
    GridCellPlan grid{};
    TileCellPlan tile{};
    TileCollisionPlan collision{};
    ParallaxPlan parallax{};
    StreamingPlan streaming{};
    TilemapDiagnostic diagnostic{};
};

GridDesc grid_desc() {
    GridDesc grid{};
    grid.map_id = 1;
    grid.revision = 1;
    grid.tile_width = 16;
    grid.tile_height = 16;
    grid.chunk_width = 32;
    grid.chunk_height = 32;
    grid.min_cell_x = -64;
    grid.min_cell_y = -64;
    grid.max_cell_x = 64;
    grid.max_cell_y = 64;
    return grid;
}

bool run_pipeline(Pipeline& pipeline) {
    pipeline = Pipeline{};
    const GridDesc grid = grid_desc();
    if (plan_grid_cell(grid, -1, -33, pipeline.grid, pipeline.diagnostic)
        != TilemapError::None) {
        return false;
    }
    TileCellDesc tile{};
    tile.map_id = 1;
    tile.layer_id = 1;
    tile.revision = 1;
    tile.cell_x = -1;
    tile.cell_y = -33;
    tile.tile_id = 42;
    tile.tile_revision = 1;
    tile.transform = TileTransform::Rotate90;
    if (plan_tile_cell(tile, pipeline.tile, pipeline.diagnostic)
        != TilemapError::None) {
        return false;
    }
    TileCollisionDesc collision{};
    collision.tile_id = 42;
    collision.revision = 1;
    collision.shape_count = 1;
    collision.shapes[0] = CollisionShapeDesc{1, 1, CollisionShapeKind::Rect,
                                              0.0f, 0.0f, 16.0f, 16.0f,
                                              true, false};
    if (plan_tile_collision(collision, pipeline.collision, pipeline.diagnostic)
        != TilemapError::None) {
        return false;
    }
    ParallaxLayerDesc parallax{};
    parallax.layer_id = 1;
    parallax.revision = 1;
    parallax.factor_x = 0.5f;
    parallax.factor_y = 0.25f;
    parallax.repeat_x = true;
    if (plan_parallax(parallax, pipeline.parallax, pipeline.diagnostic)
        != TilemapError::None) {
        return false;
    }
    StreamingRequest request{};
    request.map_id = 1;
    request.revision = 1;
    request.visible_chunks = 4;
    request.prefetch_chunks = 6;
    request.request_count = 8;
    request.requested_bytes = 1024;
    request.failed_chunks = 1;
    return plan_streaming(request, StreamingBudget{8, 16, 24, 4096},
                          pipeline.streaming, pipeline.diagnostic)
        == TilemapError::None;
}

bool same_pipeline(const Pipeline& left, const Pipeline& right) {
    return left.grid.chunk_x == right.grid.chunk_x
        && left.grid.chunk_y == right.grid.chunk_y
        && left.grid.local_x == right.grid.local_x
        && left.grid.local_y == right.grid.local_y
        && left.tile.tile_id == right.tile.tile_id
        && left.tile.transform == right.tile.transform
        && left.collision.shape_count == right.collision.shape_count
        && left.collision.solid_count == right.collision.solid_count
        && left.parallax.factor_x == right.parallax.factor_x
        && left.parallax.factor_y == right.parallax.factor_y
        && left.parallax.repeat_x == right.parallax.repeat_x
        && left.streaming.visible_chunks == right.streaming.visible_chunks
        && left.streaming.bytes == right.streaming.bytes
        && left.streaming.degraded == right.streaming.degraded
        && left.diagnostic.code == right.diagnostic.code;
}

bool run_qlft201() {
    begin();
    Pipeline pipeline{};
    expect(run_pipeline(pipeline), "integrated pipeline");
    expect(pipeline.grid.chunk_x == -1 && pipeline.grid.local_x == 31,
           "grid plan");
    expect(pipeline.grid.chunk_y == -2 && pipeline.grid.local_y == 31,
           "grid y plan");
    expect(pipeline.tile.tile_id == 42
               && pipeline.tile.transform == TileTransform::Rotate90,
           "tile plan");
    expect(pipeline.collision.shape_count == 1
               && pipeline.collision.solid_count == 1,
           "collision plan");
    expect(pipeline.parallax.factor_x == 0.5f && pipeline.parallax.repeat_x,
           "parallax plan");
    expect(pipeline.streaming.visible_chunks == 4
               && pipeline.streaming.bytes == 1024,
           "streaming plan");
    return finish();
}

bool run_qlft202() {
    begin();
    Pipeline first{};
    Pipeline second{};
    expect(run_pipeline(first), "first run");
    expect(run_pipeline(second), "second run");
    expect(same_pipeline(first, second), "deterministic plans");
    for (u32 attempt = 0; attempt < 100; ++attempt) {
        Pipeline repeated{};
        expect(run_pipeline(repeated), "repeat succeeds");
        expect(same_pipeline(first, repeated), "repeat identical");
        if (failures != 0) {
            break;
        }
    }
    return finish();
}

bool run_qlft203() {
    begin();
    Pipeline pipeline{};
    expect(run_pipeline(pipeline), "baseline pipeline");
    TilemapDiagnostic diagnostic{};

    GridDesc grid = grid_desc();
    expect(plan_grid_cell(grid, 99, 0, pipeline.grid, diagnostic)
               == TilemapError::CoordinateOutOfBounds,
           "grid failure");
    expect(plan_grid_cell(grid, -1, -1, pipeline.grid, diagnostic)
               == TilemapError::None,
           "grid recovery");

    TileCellDesc tile{};
    tile.map_id = 1;
    tile.layer_id = 1;
    tile.revision = 1;
    tile.tile_id = 0;
    expect(plan_tile_cell(tile, pipeline.tile, diagnostic)
               == TilemapError::TileInvalid,
           "tile failure");
    tile.tile_id = 42;
    tile.tile_revision = 1;
    expect(plan_tile_cell(tile, pipeline.tile, diagnostic) == TilemapError::None,
           "tile recovery");

    TileCollisionDesc collision{};
    collision.tile_id = 42;
    collision.revision = 1;
    collision.shape_count = 2;
    collision.shapes[0] = CollisionShapeDesc{1, 1, CollisionShapeKind::Rect,
                                              0.0f, 0.0f, 0.0f, 16.0f,
                                              true, false};
    expect(plan_tile_collision(collision, pipeline.collision, diagnostic)
               == TilemapError::CollisionInvalid,
           "collision failure");
    collision.shapes[0].width = 16.0f;
    collision.shape_count = 1;
    expect(plan_tile_collision(collision, pipeline.collision, diagnostic)
               == TilemapError::None,
           "collision recovery");

    ParallaxLayerDesc parallax{};
    parallax.layer_id = 1;
    parallax.revision = 1;
    parallax.factor_x = 5.0f;
    expect(plan_parallax(parallax, pipeline.parallax, diagnostic)
               == TilemapError::ParallaxInvalid,
           "parallax failure");
    parallax.factor_x = 1.0f;
    expect(plan_parallax(parallax, pipeline.parallax, diagnostic)
               == TilemapError::None,
           "parallax recovery");

    StreamingRequest request{};
    request.map_id = 1;
    request.revision = 1;
    request.request_count = 1;
    request.failed_chunks = 2;
    expect(plan_streaming(request, StreamingBudget{8, 16, 24, 4096},
                          pipeline.streaming, diagnostic)
               == TilemapError::StreamingInvalid,
           "streaming failure");
    request.failed_chunks = 0;
    expect(plan_streaming(request, StreamingBudget{8, 16, 24, 4096},
                          pipeline.streaming, diagnostic)
               == TilemapError::None,
           "streaming recovery");
    return finish();
}

bool run_qlft204() {
    begin();
    TilemapDiagnostic diagnostic{};
    StreamingRequest request{};
    request.map_id = 1;
    request.revision = 1;
    request.request_count = 1000;
    StreamingPlan streaming{};
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        expect(plan_streaming(request, StreamingBudget{8, 16, 24, 4096},
                              streaming, diagnostic) == TilemapError::None,
               "bounded streaming succeeds");
        expect(streaming.request_count == 24 && streaming.degraded,
               "bounded streaming clamps");
        if (failures != 0) {
            break;
        }
    }
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        Pipeline pipeline{};
        expect(run_pipeline(pipeline), "bounded pipeline succeeds");
        if (failures != 0) {
            break;
        }
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two02_tilemap_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlft201") { success = run_qlft201(); }
    else if (mode == "qlft202") { success = run_qlft202(); }
    else if (mode == "qlft203") { success = run_qlft203(); }
    else if (mode == "qlft204") { success = run_qlft204(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
