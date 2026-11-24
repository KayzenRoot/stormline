#include "stormline/spatial/cell_plan.hpp"

#include <climits>
#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::spatial;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

CellDesc cell(u64 key, i64 x, i64 z, u32 revision = 1) {
    CellDesc desc{};
    desc.cell_key = key;
    desc.x = x;
    desc.z = z;
    desc.revision = revision;
    return desc;
}

CellSetDesc cell_set() {
    CellSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.cell_count = 4;
    desc.cells[0] = cell(1, 0, 0);
    desc.cells[1] = cell(2, 1, 0);
    desc.cells[2] = cell(3, -1, 2);
    desc.cells[3] = cell(4, 5, -3);
    return desc;
}

bool run_cel01() {
    begin();
    i64 result = 0;
    expect(cell_floor_div(0, 4, result) && result == 0,
           "floor zero");
    expect(cell_floor_div(7, 4, result) && result == 1,
           "floor positive");
    expect(cell_floor_div(-1, 4, result) && result == -1,
           "floor negative one");
    expect(cell_floor_div(-4, 4, result) && result == -1,
           "floor exact negative");
    expect(cell_floor_div(-5, 4, result) && result == -2,
           "floor negative fraction");
    expect(cell_floor_div(INT64_MIN, 2, result)
               && result == INT64_MIN / 2,
           "floor int64 min");
    expect(cell_floor_div(INT64_MAX, 2, result)
               && result == INT64_MAX / 2,
           "floor int64 max");
    result = 77;
    expect(!cell_floor_div(1, 0, result) && result == 77,
           "floor zero size rejected");
    expect(!cell_floor_div(1, -4, result) && result == 77,
           "floor negative size rejected");
    expect(!cell_floor_div(INT64_MIN, -1, result),
           "floor int64 min overflow rejected");

    CellSetDesc cells = cell_set();
    CellPlan plan{};
    SpatialDiagnostic diagnostic{};
    expect(plan_cells(cells, plan, diagnostic) == SpatialError::None,
           "valid cells");
    expect(plan.cell_count == 4 && plan.min_x == -1 && plan.max_x == 5
               && plan.min_z == -3 && plan.max_z == 2,
           "valid bounds");
    expect(diagnostic.code == SpatialError::None,
           "success diagnostic");
    CellPlan repeat{};
    expect(plan_cells(cells, repeat, diagnostic) == SpatialError::None,
           "repeat cells");
    expect(plan.min_x == repeat.min_x && plan.max_x == repeat.max_x
               && plan.min_z == repeat.min_z && plan.max_z == repeat.max_z,
           "deterministic bounds");

    cells.world_id = 0;
    expect(plan_cells(cells, plan, diagnostic)
               == SpatialError::InvalidArgument,
           "zero world");
    expect(plan.cell_count == 0 && plan.min_x == 0 && plan.max_x == 0,
           "reset on zero world");
    cells = cell_set();
    cells.revision = 0;
    expect(plan_cells(cells, plan, diagnostic)
               == SpatialError::InvalidArgument,
           "zero revision");
    cells = cell_set();
    cells.cell_count = 0;
    expect(plan_cells(cells, plan, diagnostic)
               == SpatialError::CellInvalid,
           "zero count");
    cells.cell_count = kMaxSpatialCells + 1;
    expect(plan_cells(cells, plan, diagnostic)
               == SpatialError::CapacityFull,
           "count overflow");

    cells = cell_set();
    cells.cells[2].cell_key = 0;
    expect(plan_cells(cells, plan, diagnostic)
               == SpatialError::CellInvalid,
           "zero cell key");
    expect(diagnostic.index == 2 && diagnostic.source_id == cells.world_id,
           "zero key diagnostic");
    cells = cell_set();
    cells.cells[1].revision = 0;
    expect(plan_cells(cells, plan, diagnostic)
               == SpatialError::CellInvalid,
           "zero cell revision");
    expect(diagnostic.index == 1, "zero revision diagnostic");
    cells = cell_set();
    cells.cells[3].cell_key = 1;
    expect(plan_cells(cells, plan, diagnostic)
               == SpatialError::DuplicateId,
           "duplicate key");
    expect(diagnostic.index == 3, "duplicate key diagnostic");
    cells = cell_set();
    cells.cells[2].x = 1;
    cells.cells[2].z = 0;
    expect(plan_cells(cells, plan, diagnostic)
               == SpatialError::DuplicateId,
           "duplicate coordinate");
    expect(diagnostic.index == 2, "duplicate coordinate diagnostic");

    cells = cell_set();
    cells.cell_count = kMaxSpatialCells;
    for (u32 index = 0; index < kMaxSpatialCells; ++index) {
        cells.cells[index] =
            cell(static_cast<u64>(index) + 1,
                 static_cast<i64>(index) - 32, static_cast<i64>(index));
    }
    expect(plan_cells(cells, plan, diagnostic) == SpatialError::None,
           "capacity cells");
    expect(plan.cell_count == kMaxSpatialCells && plan.min_x == -32
               && plan.max_x == 31 && plan.min_z == 0
               && plan.max_z == 63,
           "capacity bounds");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world03_cell_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "cel01") { success = run_cel01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
