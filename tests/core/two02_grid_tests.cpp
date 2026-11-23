#include "stormline/tilemap/grid_plan.hpp"

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

GridDesc valid_grid() {
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

bool run_grd01() {
    begin();
    GridDesc grid = valid_grid();
    GridCellPlan plan{};
    TilemapDiagnostic diagnostic{};

    expect(plan_grid_cell(grid, -1, -1, plan, diagnostic) == TilemapError::None,
           "negative cell");
    expect(plan.chunk_x == -1 && plan.local_x == 31
               && plan.chunk_y == -1 && plan.local_y == 31,
           "negative floor math");
    expect(plan_grid_cell(grid, -32, -32, plan, diagnostic)
               == TilemapError::None,
           "exact negative chunk");
    expect(plan.chunk_x == -1 && plan.local_x == 0
               && plan.chunk_y == -1 && plan.local_y == 0,
           "exact negative local");
    expect(plan_grid_cell(grid, -33, -33, plan, diagnostic)
               == TilemapError::None,
           "previous chunk");
    expect(plan.chunk_x == -2 && plan.local_x == 31
               && plan.chunk_y == -2 && plan.local_y == 31,
           "previous chunk local");
    expect(plan_grid_cell(grid, 0, 0, plan, diagnostic) == TilemapError::None,
           "origin");
    expect(plan.chunk_x == 0 && plan.local_x == 0, "origin plan");
    expect(plan_grid_cell(grid, 32, 31, plan, diagnostic) == TilemapError::None,
           "positive cell");
    expect(plan.chunk_x == 1 && plan.local_x == 0
               && plan.chunk_y == 0 && plan.local_y == 31,
           "positive plan");

    grid.map_id = 0;
    expect(plan_grid_cell(grid, 0, 0, plan, diagnostic)
               == TilemapError::InvalidArgument,
           "zero map");
    expect(plan.chunk_x == 0 && plan.local_x == 0, "reset");

    grid = valid_grid();
    grid.chunk_width = 0;
    expect(plan_grid_cell(grid, 0, 0, plan, diagnostic)
               == TilemapError::GridInvalid,
           "zero chunk");
    grid = valid_grid();
    grid.tile_height = 0;
    expect(plan_grid_cell(grid, 0, 0, plan, diagnostic)
               == TilemapError::GridInvalid,
           "zero tile");
    grid = valid_grid();
    grid.min_cell_x = 10;
    grid.max_cell_x = -10;
    expect(plan_grid_cell(grid, 0, 0, plan, diagnostic)
               == TilemapError::GridInvalid,
           "reversed bounds");
    grid = valid_grid();
    expect(plan_grid_cell(grid, 65, 0, plan, diagnostic)
               == TilemapError::CoordinateOutOfBounds,
           "out of bounds");
    grid = valid_grid();
    grid.revision = 0;
    expect(plan_grid_cell(grid, 0, 0, plan, diagnostic)
               == TilemapError::InvalidArgument,
           "zero revision");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two02_grid_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "grd01") { success = run_grd01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
