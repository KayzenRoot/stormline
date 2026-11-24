#include "stormline/spatial/cell_plan.hpp"
#include "stormline/spatial/interest_plan.hpp"
#include "stormline/spatial/origin_plan.hpp"
#include "stormline/spatial/streaming_plan.hpp"

#include <cstdio>
#include <limits>
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

struct Plans {
    CellPlan cells{};
    InterestPlan interest{};
    OriginPlan origin{};
    StreamingPlan streaming{};
    SpatialDiagnostic diagnostic{};
};

CellDesc cell(u64 key, i64 x, i64 z) {
    CellDesc desc{};
    desc.cell_key = key;
    desc.x = x;
    desc.z = z;
    desc.revision = 1;
    return desc;
}

CellSetDesc make_cells() {
    CellSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 1;
    desc.cell_count = 4;
    desc.cells[0] = cell(1, -2, -1);
    desc.cells[1] = cell(2, 0, 0);
    desc.cells[2] = cell(3, 1, 2);
    desc.cells[3] = cell(4, 2, -2);
    return desc;
}

InterestSourceDesc interest_source(
    u32 id, InterestRole role, f32 min_x, f32 min_z, f32 max_x, f32 max_z,
    bool required) {
    InterestSourceDesc desc{};
    desc.source_id = id;
    desc.revision = 1;
    desc.role = role;
    desc.bounds = InterestBounds{min_x, min_z, max_x, max_z};
    desc.priority = id;
    desc.required_complete = required;
    return desc;
}

InterestSetDesc make_interest() {
    InterestSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 1;
    desc.source_count = 3;
    desc.sources[0] = interest_source(1, InterestRole::Player, -3.0f, -2.0f,
                                      3.0f, 2.0f, true);
    desc.sources[1] = interest_source(2, InterestRole::Camera, -4.0f, -1.0f,
                                      4.0f, 1.0f, true);
    desc.sources[2] = interest_source(3, InterestRole::Ai, 0.0f, -3.0f, 2.0f,
                                      3.0f, false);
    return desc;
}

OriginEpochDesc make_origin() {
    OriginEpochDesc desc{};
    desc.world_id = 10;
    desc.revision = 1;
    desc.old_epoch = 1;
    desc.new_epoch = 2;
    desc.old_x = 0.5f;
    desc.old_y = -0.5f;
    desc.old_z = 1.0f;
    desc.new_x = -1.0f;
    desc.new_y = 0.5f;
    desc.new_z = -0.5f;
    desc.physics_ack = true;
    desc.render_ack = true;
    desc.network_ack = true;
    return desc;
}

StreamingCellDesc streaming_cell(u64 key, CellPriority priority, u64 budget) {
    StreamingCellDesc desc{};
    desc.cell_key = key;
    desc.revision = 1;
    desc.priority = priority;
    desc.request_generation = 1;
    desc.cancel_generation = 0;
    desc.byte_budget = budget;
    return desc;
}

StreamingPlanDesc make_streaming() {
    StreamingPlanDesc desc{};
    desc.world_id = 10;
    desc.revision = 1;
    desc.cell_count = 4;
    desc.cells[0] = streaming_cell(1, CellPriority::Pinned, 4096);
    desc.cells[1] = streaming_cell(2, CellPriority::Prefetch, 2048);
    desc.cells[2] = streaming_cell(3, CellPriority::Optional, 1024);
    desc.cells[3] = streaming_cell(4, CellPriority::Evict, 0);
    return desc;
}

bool plan_all(const CellSetDesc& cells, const InterestSetDesc& interest,
              const OriginEpochDesc& origin, const StreamingPlanDesc& streaming,
              Plans& plans) {
    return plan_cells(cells, plans.cells, plans.diagnostic)
               == SpatialError::None
           && plan_interest(interest, plans.interest, plans.diagnostic)
               == SpatialError::None
           && plan_origin_change(origin, plans.origin, plans.diagnostic)
               == SpatialError::None
           && plan_streaming(streaming, plans.streaming, plans.diagnostic)
               == SpatialError::None;
}

bool run_qlfw301() {
    begin();
    const CellSetDesc cells = make_cells();
    const InterestSetDesc interest = make_interest();
    const OriginEpochDesc origin = make_origin();
    const StreamingPlanDesc streaming = make_streaming();
    Plans plans{};
    expect(plan_all(cells, interest, origin, streaming, plans),
           "integrated plans");
    expect(plans.cells.cell_count == 4 && plans.cells.min_x == -2
               && plans.cells.max_x == 2 && plans.cells.min_z == -2
               && plans.cells.max_z == 2,
           "integrated cell bounds");
    expect(plans.interest.source_count == 3
               && plans.interest.complete_count == 2
               && plans.interest.incomplete_count == 1,
           "integrated interest counts");
    expect(plans.interest.union_bounds.min_x <= -2.0f
               && plans.interest.union_bounds.max_x >= 2.0f
               && plans.interest.union_bounds.min_z <= -2.0f
               && plans.interest.union_bounds.max_z >= 2.0f,
           "interest covers cells");
    expect(plans.origin.accepted && plans.origin.old_epoch == 1
               && plans.origin.new_epoch == 2,
           "integrated origin");
    expect(plans.streaming.cell_count == 4
               && plans.streaming.pinned_count == 1
               && plans.streaming.prefetch_count == 1
               && plans.streaming.total_bytes == 7168,
           "integrated streaming");
    expect(plans.diagnostic.code == SpatialError::None,
           "integrated diagnostic");
    return finish();
}

bool run_qlfw302() {
    begin();
    const CellSetDesc cells = make_cells();
    const InterestSetDesc interest = make_interest();
    const OriginEpochDesc origin = make_origin();
    const StreamingPlanDesc streaming = make_streaming();
    Plans first{};
    expect(plan_all(cells, interest, origin, streaming, first),
           "deterministic first");
    for (u32 attempt = 0; attempt < 100; ++attempt) {
        Plans repeat{};
        expect(plan_all(cells, interest, origin, streaming, repeat),
               "deterministic repeat success");
        expect(repeat.cells.cell_count == first.cells.cell_count
                   && repeat.cells.min_x == first.cells.min_x
                   && repeat.cells.max_x == first.cells.max_x
                   && repeat.cells.min_z == first.cells.min_z
                   && repeat.cells.max_z == first.cells.max_z,
               "cells identical");
        expect(repeat.interest.source_count == first.interest.source_count
                   && repeat.interest.complete_count
                       == first.interest.complete_count
                   && repeat.interest.union_bounds.min_x
                       == first.interest.union_bounds.min_x
                   && repeat.interest.union_bounds.max_z
                       == first.interest.union_bounds.max_z,
               "interest identical");
        expect(repeat.origin.old_epoch == first.origin.old_epoch
                   && repeat.origin.new_epoch == first.origin.new_epoch
                   && repeat.origin.accepted == first.origin.accepted,
               "origin identical");
        expect(repeat.streaming.cell_count == first.streaming.cell_count
                   && repeat.streaming.pinned_count
                       == first.streaming.pinned_count
                   && repeat.streaming.prefetch_count
                       == first.streaming.prefetch_count
                   && repeat.streaming.total_bytes
                       == first.streaming.total_bytes,
               "streaming identical");
    }
    return finish();
}

bool run_qlfw303() {
    begin();
    Plans plans{};
    CellSetDesc cells = make_cells();
    cells.cells[3].cell_key = 1;
    expect(plan_cells(cells, plans.cells, plans.diagnostic)
               == SpatialError::DuplicateId,
           "cell failure");
    expect(plans.cells.cell_count == 0, "cell reset");
    cells = make_cells();
    expect(plan_cells(cells, plans.cells, plans.diagnostic)
               == SpatialError::None,
           "cell recovery");
    expect(plans.cells.cell_count == 4
               && plans.diagnostic.code == SpatialError::None,
           "cell recovery state");

    InterestSetDesc interest = make_interest();
    interest.sources[1].bounds.max_z = std::numeric_limits<f32>::infinity();
    expect(plan_interest(interest, plans.interest, plans.diagnostic)
               == SpatialError::NonFiniteValue,
           "interest failure");
    expect(plans.interest.source_count == 0, "interest reset");
    interest = make_interest();
    expect(plan_interest(interest, plans.interest, plans.diagnostic)
               == SpatialError::None,
           "interest recovery");
    expect(plans.interest.source_count == 3
               && plans.diagnostic.code == SpatialError::None,
           "interest recovery state");

    OriginEpochDesc origin = make_origin();
    origin.new_epoch = origin.old_epoch;
    expect(plan_origin_change(origin, plans.origin, plans.diagnostic)
               == SpatialError::OriginInvalid,
           "origin failure");
    expect(plans.origin.old_epoch == 0 && !plans.origin.accepted,
           "origin reset");
    origin = make_origin();
    expect(plan_origin_change(origin, plans.origin, plans.diagnostic)
               == SpatialError::None,
           "origin recovery");
    expect(plans.origin.accepted && plans.diagnostic.code == SpatialError::None,
           "origin recovery state");

    StreamingPlanDesc streaming = make_streaming();
    streaming.cells[2].cancel_generation = 2;
    expect(plan_streaming(streaming, plans.streaming, plans.diagnostic)
               == SpatialError::StreamInvalid,
           "streaming failure");
    expect(plans.streaming.cell_count == 0 && plans.streaming.total_bytes == 0,
           "streaming reset");
    streaming = make_streaming();
    expect(plan_streaming(streaming, plans.streaming, plans.diagnostic)
               == SpatialError::None,
           "streaming recovery");
    expect(plans.streaming.cell_count == 4
               && plans.streaming.total_bytes == 7168
               && plans.diagnostic.code == SpatialError::None,
           "streaming recovery state");
    return finish();
}

bool run_qlfw304() {
    begin();
    Plans plans{};
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        CellSetDesc cells{};
        cells.world_id = 10;
        cells.revision = 1;
        cells.cell_count = kMaxSpatialCells;
        for (u32 index = 0; index < kMaxSpatialCells; ++index) {
            cells.cells[index] =
                cell(static_cast<u64>(attempt) * 64ull + index + 1,
                     static_cast<i64>(index), -static_cast<i64>(index));
        }
        expect(plan_cells(cells, plans.cells, plans.diagnostic)
                   == SpatialError::None,
               "overload cells");
        expect(plans.cells.cell_count <= kMaxSpatialCells, "overload cell cap");

        InterestSetDesc interest{};
        interest.world_id = 10;
        interest.revision = 1;
        interest.source_count = kMaxInterestSources;
        for (u32 index = 0; index < kMaxInterestSources; ++index) {
            const f32 base = static_cast<f32>(index);
            interest.sources[index] =
                interest_source(index + 1, InterestRole::Player, base, base,
                                base + 1.0f, base + 1.0f, false);
        }
        expect(plan_interest(interest, plans.interest, plans.diagnostic)
                   == SpatialError::None,
               "overload interest");
        expect(plans.interest.source_count <= kMaxInterestSources,
               "overload interest cap");

        OriginEpochDesc origin = make_origin();
        expect(plan_origin_change(origin, plans.origin, plans.diagnostic)
                   == SpatialError::None,
               "overload origin");
        expect(plans.origin.accepted, "overload origin accepted");

        StreamingPlanDesc streaming{};
        streaming.world_id = 10;
        streaming.revision = 1;
        streaming.cell_count = kMaxStreamingCells;
        for (u32 index = 0; index < kMaxStreamingCells; ++index) {
            streaming.cells[index] =
                streaming_cell(static_cast<u64>(attempt) * 64ull + index + 1,
                               index % 2 == 0 ? CellPriority::Pinned
                                              : CellPriority::Prefetch,
                               1024ull * 1024ull);
        }
        expect(plan_streaming(streaming, plans.streaming, plans.diagnostic)
                   == SpatialError::None,
               "overload streaming");
        expect(plans.streaming.cell_count <= kMaxStreamingCells,
               "overload streaming cap");
        expect(plans.streaming.total_bytes
                   == 64ull * 1024ull * 1024ull,
               "overload streaming total");

        if (attempt % 100 == 0) {
            cells.cell_count = kMaxSpatialCells + 1;
            expect(plan_cells(cells, plans.cells, plans.diagnostic)
                       == SpatialError::CapacityFull,
                   "overload cell rejection");
            expect(plans.cells.cell_count == 0, "overload cell reset");
        }
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world03_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlfw301") { success = run_qlfw301(); }
    else if (mode == "qlfw302") { success = run_qlfw302(); }
    else if (mode == "qlfw303") { success = run_qlfw303(); }
    else if (mode == "qlfw304") { success = run_qlfw304(); }
    else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
