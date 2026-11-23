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

bool run_til01() {
    begin();
    TileCellDesc cell{};
    cell.map_id = 1;
    cell.layer_id = 2;
    cell.revision = 1;
    cell.cell_x = -1;
    cell.cell_y = -33;
    cell.tile_id = 42;
    cell.tile_revision = 3;
    cell.transform = TileTransform::Rotate90;
    TileCellPlan plan{};
    TilemapDiagnostic diagnostic{};

    expect(plan_tile_cell(cell, plan, diagnostic) == TilemapError::None,
           "valid tile");
    expect(!plan.empty && plan.tile_id == 42
               && plan.transform == TileTransform::Rotate90,
           "valid plan");

    cell.empty = true;
    expect(plan_tile_cell(cell, plan, diagnostic) == TilemapError::TileInvalid,
           "empty with tile");
    cell.tile_id = 0;
    cell.tile_revision = 0;
    cell.transform = TileTransform::None;
    expect(plan_tile_cell(cell, plan, diagnostic) == TilemapError::None,
           "empty tile");
    expect(plan.empty && plan.tile_id == 0, "empty plan");

    cell.map_id = 0;
    expect(plan_tile_cell(cell, plan, diagnostic)
               == TilemapError::InvalidArgument,
           "zero map");
    expect(!plan.empty && plan.tile_id == 0, "reset");

    cell.map_id = 1;
    cell.empty = false;
    cell.tile_id = 42;
    cell.tile_revision = 3;
    cell.transform = TileTransform::FlipX;
    cell.orientation = TileOrientation::Isometric;
    expect(plan_tile_cell(cell, plan, diagnostic) == TilemapError::Unsupported,
           "nonorthogonal transform");
    cell.orientation = TileOrientation::Orthogonal;
    cell.transform = static_cast<TileTransform>(200);
    expect(plan_tile_cell(cell, plan, diagnostic)
               == TilemapError::InvalidArgument,
           "invalid transform");
    cell.transform = TileTransform::None;
    cell.orientation = static_cast<TileOrientation>(200);
    expect(plan_tile_cell(cell, plan, diagnostic)
               == TilemapError::InvalidArgument,
           "invalid orientation");
    cell.orientation = TileOrientation::Orthogonal;
    cell.tile_revision = 0;
    expect(plan_tile_cell(cell, plan, diagnostic) == TilemapError::TileInvalid,
           "zero tile revision");
    cell.tile_revision = 1;
    cell.layer_id = 0;
    expect(plan_tile_cell(cell, plan, diagnostic)
               == TilemapError::InvalidArgument,
           "zero layer");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two02_tile_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "til01") { success = run_til01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
