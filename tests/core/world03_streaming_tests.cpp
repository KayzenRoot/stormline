#include "stormline/spatial/streaming_plan.hpp"

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

StreamingCellDesc streaming_cell(
    u64 key, CellPriority priority, u32 request_generation,
    u32 cancel_generation, u64 byte_budget) {
    StreamingCellDesc desc{};
    desc.cell_key = key;
    desc.revision = 1;
    desc.priority = priority;
    desc.request_generation = request_generation;
    desc.cancel_generation = cancel_generation;
    desc.byte_budget = byte_budget;
    return desc;
}

StreamingPlanDesc streaming_plan() {
    StreamingPlanDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.cell_count = 4;
    desc.cells[0] = streaming_cell(1, CellPriority::Pinned, 3, 0,
                                   256ull * 1024ull * 1024ull);
    desc.cells[1] = streaming_cell(2, CellPriority::Prefetch, 4, 2,
                                   128ull * 1024ull * 1024ull);
    desc.cells[2] = streaming_cell(3, CellPriority::Optional, 1, 1, 4096);
    desc.cells[3] = streaming_cell(4, CellPriority::Evict, 5, 5, 0);
    return desc;
}

bool run_str01() {
    begin();
    StreamingPlanDesc desc = streaming_plan();
    StreamingPlan plan{};
    SpatialDiagnostic diagnostic{};
    expect(plan_streaming(desc, plan, diagnostic) == SpatialError::None,
           "valid streaming");
    expect(plan.cell_count == 4 && plan.pinned_count == 1
               && plan.prefetch_count == 1,
           "valid counts");
    expect(plan.total_bytes == 384ull * 1024ull * 1024ull + 4096ull,
           "valid total");
    expect(diagnostic.code == SpatialError::None,
           "success diagnostic");
    StreamingPlan repeat{};
    expect(plan_streaming(desc, repeat, diagnostic) == SpatialError::None,
           "repeat streaming");
    expect(repeat.total_bytes == plan.total_bytes
               && repeat.pinned_count == plan.pinned_count,
           "deterministic plan");

    desc.cell_count = 0;
    expect(plan_streaming(desc, plan, diagnostic) == SpatialError::None,
           "empty streaming");
    expect(plan.cell_count == 0 && plan.total_bytes == 0,
           "empty counts");

    desc = streaming_plan();
    desc.world_id = 0;
    expect(plan_streaming(desc, plan, diagnostic)
               == SpatialError::InvalidArgument,
           "zero world");
    expect(plan.cell_count == 0 && plan.total_bytes == 0,
           "reset on zero world");
    desc = streaming_plan();
    desc.revision = 0;
    expect(plan_streaming(desc, plan, diagnostic)
               == SpatialError::InvalidArgument,
           "zero revision");
    desc = streaming_plan();
    desc.cell_count = kMaxStreamingCells + 1;
    expect(plan_streaming(desc, plan, diagnostic)
               == SpatialError::CapacityFull,
           "cell overflow");

    desc = streaming_plan();
    desc.cells[2].cell_key = 0;
    expect(plan_streaming(desc, plan, diagnostic)
               == SpatialError::StreamInvalid,
           "zero cell key");
    expect(diagnostic.index == 2, "zero key diagnostic");
    desc = streaming_plan();
    desc.cells[3].cell_key = 1;
    expect(plan_streaming(desc, plan, diagnostic)
               == SpatialError::DuplicateId,
           "duplicate cell key");
    expect(diagnostic.index == 3, "duplicate key diagnostic");
    desc = streaming_plan();
    desc.cells[0].priority =
        static_cast<CellPriority>(static_cast<u8>(99));
    expect(plan_streaming(desc, plan, diagnostic)
               == SpatialError::StreamInvalid,
           "unknown priority");
    desc = streaming_plan();
    desc.cells[1].request_generation = 0;
    expect(plan_streaming(desc, plan, diagnostic)
               == SpatialError::StreamInvalid,
           "zero request generation");
    desc = streaming_plan();
    desc.cells[1].cancel_generation = 5;
    expect(plan_streaming(desc, plan, diagnostic)
               == SpatialError::StreamInvalid,
           "cancel after request");
    expect(diagnostic.index == 1, "cancel diagnostic");
    desc = streaming_plan();
    desc.cells[1].cancel_generation = 4;
    expect(plan_streaming(desc, plan, diagnostic) == SpatialError::None,
           "cancel equal request");
    desc = streaming_plan();
    desc.cells[0].byte_budget = kMaxCellBytes;
    expect(plan_streaming(desc, plan, diagnostic) == SpatialError::None,
           "max cell budget");
    desc = streaming_plan();
    desc.cells[0].byte_budget = kMaxCellBytes + 1;
    expect(plan_streaming(desc, plan, diagnostic)
               == SpatialError::OutOfRange,
           "cell budget overflow");

    desc = streaming_plan();
    desc.cell_count = kMaxStreamingCells;
    for (u32 index = 0; index < kMaxStreamingCells; ++index) {
        desc.cells[index] =
            streaming_cell(static_cast<u64>(index) + 1,
                           index % 2 == 0 ? CellPriority::Pinned
                                          : CellPriority::Prefetch,
                           index + 1, index, kMaxCellBytes);
    }
    expect(plan_streaming(desc, plan, diagnostic) == SpatialError::None,
           "capacity streaming");
    expect(plan.cell_count == kMaxStreamingCells
               && plan.pinned_count == 32 && plan.prefetch_count == 32,
           "capacity counts");
    expect(plan.total_bytes == 64ull * kMaxCellBytes,
           "capacity total");

    u64 total = ~u64{0};
    expect(!detail::checked_add_u64(total, 1), "checked add overflow");
    expect(total == ~u64{0}, "checked add preserves");
    total = 0;
    expect(detail::checked_add_u64(total, kMaxCellBytes)
               && total == kMaxCellBytes,
           "checked add success");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world03_streaming_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "str01") { success = run_str01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
