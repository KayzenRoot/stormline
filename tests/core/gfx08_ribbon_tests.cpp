#include "stormline/graphics/vfx/ribbon_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::vfx;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_rib01() {
    begin();
    VfxRibbonDesc ribbon{};
    ribbon.source_id = 4;
    ribbon.revision = 2;
    ribbon.sample_count = 6;
    ribbon.width = 0.25f;
    ribbon.min_sample_distance = 0.1f;
    ribbon.max_segments = 8;
    ribbon.max_vertices = 16;
    VfxRibbonPlan plan{};
    VfxDiagnostic diagnostic{};

    expect(plan_ribbon(ribbon, plan, diagnostic) == VfxError::None,
           "valid ribbon");
    expect(plan.segments == 5 && plan.vertices == 12, "valid plan");

    ribbon.source_id = 0;
    expect(plan_ribbon(ribbon, plan, diagnostic) == VfxError::InvalidArgument,
           "zero source");
    expect(plan.segments == 0 && plan.vertices == 0, "reset");

    ribbon.source_id = 4;
    ribbon.sample_count = 1;
    expect(plan_ribbon(ribbon, plan, diagnostic) == VfxError::GeometryInvalid,
           "too few samples");
    ribbon.sample_count = kMaxRibbonSamples + 1;
    expect(plan_ribbon(ribbon, plan, diagnostic) == VfxError::GeometryInvalid,
           "too many samples");
    ribbon.sample_count = 6;
    ribbon.width = 0.0f;
    expect(plan_ribbon(ribbon, plan, diagnostic) == VfxError::GeometryInvalid,
           "zero width");
    ribbon.width = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_ribbon(ribbon, plan, diagnostic) == VfxError::NonFiniteValue,
           "nonfinite width");
    ribbon.width = 0.25f;
    ribbon.min_sample_distance = -1.0f;
    expect(plan_ribbon(ribbon, plan, diagnostic) == VfxError::GeometryInvalid,
           "negative distance");
    ribbon.min_sample_distance = 0.1f;
    ribbon.max_segments = 0;
    expect(plan_ribbon(ribbon, plan, diagnostic) == VfxError::InvalidArgument,
           "zero segment cap");
    ribbon.max_segments = 8;
    ribbon.max_vertices = 11;
    expect(plan_ribbon(ribbon, plan, diagnostic) == VfxError::BudgetExceeded,
           "vertex cap");
    ribbon.max_vertices = 16;
    ribbon.max_segments = 4;
    expect(plan_ribbon(ribbon, plan, diagnostic) == VfxError::BudgetExceeded,
           "segment cap");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx08_ribbon_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "rib01") { success = run_rib01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
