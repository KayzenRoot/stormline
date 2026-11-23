#include "stormline/graphics/post/reconstruction_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::post;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_rcn01() {
    begin();
    ReconstructionRequest request{};
    ReconstructionPlan plan{};
    PostDiagnostic diagnostic{};

    expect(plan_reconstruction(request, plan, diagnostic) == PostError::None,
           "native");
    expect(plan.strategy == ReconstructionStrategy::Native && !plan.degraded,
           "native plan");

    request.preferred = ReconstructionStrategy::Spatial;
    expect(plan_reconstruction(request, plan, diagnostic) == PostError::None,
           "spatial");
    expect(plan.strategy == ReconstructionStrategy::Spatial && !plan.degraded,
           "spatial plan");

    request.preferred = ReconstructionStrategy::Taa;
    expect(plan_reconstruction(request, plan, diagnostic) == PostError::None,
           "taa fallback");
    expect(plan.strategy == ReconstructionStrategy::Spatial && plan.degraded,
           "taa fallback plan");
    request.depth_available = true;
    request.velocity_available = true;
    request.history_available = true;
    expect(plan_reconstruction(request, plan, diagnostic) == PostError::None,
           "taa");
    expect(plan.strategy == ReconstructionStrategy::Taa && !plan.degraded,
           "taa plan");

    request.preferred = ReconstructionStrategy::VendorUpscale;
    expect(plan_reconstruction(request, plan, diagnostic) == PostError::None,
           "vendor fallback");
    expect(plan.strategy == ReconstructionStrategy::Spatial && plan.degraded,
           "vendor fallback plan");
    request.reactive_mask_available = true;
    request.vendor_available = true;
    expect(plan_reconstruction(request, plan, diagnostic) == PostError::None,
           "vendor");
    expect(plan.strategy == ReconstructionStrategy::VendorUpscale
               && !plan.degraded,
           "vendor plan");

    request.preferred = static_cast<ReconstructionStrategy>(200);
    expect(plan_reconstruction(request, plan, diagnostic)
               == PostError::InvalidArgument,
           "invalid enum");
    expect(plan.strategy == ReconstructionStrategy::Native, "reset");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx07_reconstruction_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "rcn01") { success = run_rcn01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
