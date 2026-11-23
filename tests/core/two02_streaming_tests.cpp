#include "stormline/tilemap/streaming_plan.hpp"

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

bool run_str01() {
    begin();
    StreamingRequest request{};
    request.map_id = 1;
    request.revision = 1;
    request.visible_chunks = 4;
    request.prefetch_chunks = 6;
    request.request_count = 8;
    request.requested_bytes = 1024;
    request.failed_chunks = 1;
    StreamingBudget budget{8, 16, 24, 4096};
    StreamingPlan plan{};
    TilemapDiagnostic diagnostic{};

    expect(plan_streaming(request, budget, plan, diagnostic)
               == TilemapError::None,
           "valid streaming");
    expect(plan.visible_chunks == 4 && plan.prefetch_chunks == 6
               && plan.request_count == 8 && plan.bytes == 1024
               && !plan.degraded,
           "valid plan");

    request.visible_chunks = 9;
    request.prefetch_chunks = 20;
    request.request_count = 30;
    request.requested_bytes = 5000;
    expect(plan_streaming(request, budget, plan, diagnostic)
               == TilemapError::None,
           "degraded streaming");
    expect(plan.visible_chunks == 8 && plan.prefetch_chunks == 16
               && plan.request_count == 24 && plan.bytes == 4096
               && plan.degraded,
           "clamped plan");

    request.map_id = 0;
    expect(plan_streaming(request, budget, plan, diagnostic)
               == TilemapError::InvalidArgument,
           "zero map");
    expect(plan.visible_chunks == 0 && !plan.degraded, "reset");

    request = StreamingRequest{};
    request.map_id = 1;
    request.revision = 1;
    request.request_count = 2;
    request.failed_chunks = 3;
    expect(plan_streaming(request, budget, plan, diagnostic)
               == TilemapError::StreamingInvalid,
           "failed exceeds requests");
    request.failed_chunks = 0;
    budget.max_bytes = 0;
    expect(plan_streaming(request, budget, plan, diagnostic)
               == TilemapError::StreamingInvalid,
           "zero byte budget");
    budget = StreamingBudget{8, 16, 24, 4096};
    budget.max_requests = 0;
    expect(plan_streaming(request, budget, plan, diagnostic)
               == TilemapError::StreamingInvalid,
           "zero request budget");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two02_streaming_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "str01") { success = run_str01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
