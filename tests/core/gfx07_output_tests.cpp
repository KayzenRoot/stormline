#include "stormline/graphics/post/output_plan.hpp"

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

bool run_hdr01() {
    begin();
    HdrCapability capability{};
    OutputRequest request{};
    OutputPlan plan{};
    PostDiagnostic diagnostic{};

    expect(plan_output(capability, request, plan, diagnostic) == PostError::None,
           "sdr default");
    expect(plan.mode == OutputMode::SdrSrgb && !plan.degraded, "sdr plan");

    capability.display_hdr = true;
    capability.swapchain_hdr = true;
    capability.os_hdr = true;
    capability.pq_supported = true;
    request.prefer_hdr = true;
    expect(plan_output(capability, request, plan, diagnostic) == PostError::None,
           "hdr");
    expect(plan.mode == OutputMode::Hdr10Pq && !plan.degraded, "hdr plan");

    HdrCapability partial = capability;
    partial.display_hdr = false;
    expect(plan_output(partial, request, plan, diagnostic) == PostError::None,
           "display fallback");
    expect(plan.mode == OutputMode::SdrSrgb && plan.degraded, "display degraded");
    partial = capability;
    partial.swapchain_hdr = false;
    expect(plan_output(partial, request, plan, diagnostic) == PostError::None,
           "swapchain fallback");
    expect(plan.mode == OutputMode::SdrSrgb && plan.degraded,
           "swapchain degraded");
    partial = capability;
    partial.os_hdr = false;
    expect(plan_output(partial, request, plan, diagnostic) == PostError::None,
           "os fallback");
    expect(plan.mode == OutputMode::SdrSrgb && plan.degraded, "os degraded");
    partial = capability;
    partial.pq_supported = false;
    expect(plan_output(partial, request, plan, diagnostic) == PostError::None,
           "pq fallback");
    expect(plan.mode == OutputMode::SdrSrgb && plan.degraded, "pq degraded");

    request.prefer_hdr = false;
    expect(plan_output(capability, request, plan, diagnostic) == PostError::None,
           "sdr preference");
    expect(plan.mode == OutputMode::SdrSrgb && !plan.degraded,
           "sdr preference plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx07_output_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "hdr01") { success = run_hdr01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
