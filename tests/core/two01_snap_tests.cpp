#include "stormline/graphics/canvas2d/snap_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::canvas2d;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_snp01() {
    begin();
    CanvasSnapDesc snap{};
    snap.mode = SnapMode::Integer;
    snap.filter = FilterMode::Nearest;
    snap.scale_x = 2.0f;
    snap.scale_y = 3.0f;
    snap.offset_x = 0.4f;
    snap.offset_y = -1.6f;
    SnapPlan plan{};
    CanvasDiagnostic diagnostic{};

    expect(plan_snap(snap, plan, diagnostic) == CanvasError::None,
           "integer snap");
    expect(plan.snapped_offset_x == 0.0f && plan.snapped_offset_y == -2.0f,
           "rounded offsets");
    expect(!plan.degraded, "integer scale");

    snap.scale_x = 2.5f;
    expect(plan_snap(snap, plan, diagnostic) == CanvasError::None,
           "degraded integer");
    expect(plan.degraded, "degraded receipt");

    snap = CanvasSnapDesc{};
    snap.filter = FilterMode::Linear;
    snap.offset_x = 0.4f;
    expect(plan_snap(snap, plan, diagnostic) == CanvasError::None,
           "continuous");
    expect(plan.snapped_offset_x == 0.4f && !plan.degraded, "continuous plan");

    snap.mode = static_cast<SnapMode>(200);
    expect(plan_snap(snap, plan, diagnostic) == CanvasError::InvalidArgument,
           "invalid mode");
    snap.mode = SnapMode::None;
    snap.filter = static_cast<FilterMode>(200);
    expect(plan_snap(snap, plan, diagnostic) == CanvasError::InvalidArgument,
           "invalid filter");
    snap.filter = FilterMode::Linear;
    snap.scale_x = 0.0f;
    expect(plan_snap(snap, plan, diagnostic) == CanvasError::SnapInvalid,
           "zero scale");
    snap.scale_x = -1.0f;
    expect(plan_snap(snap, plan, diagnostic) == CanvasError::SnapInvalid,
           "negative scale");
    snap.scale_x = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_snap(snap, plan, diagnostic) == CanvasError::NonFiniteValue,
           "nonfinite scale");
    snap.scale_x = 1.0f;
    snap.offset_y = std::numeric_limits<f32>::infinity();
    expect(plan_snap(snap, plan, diagnostic) == CanvasError::NonFiniteValue,
           "nonfinite offset");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two01_snap_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "snp01") { success = run_snp01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
