#include "stormline/graphics/post/tone_color.hpp"

#include <cstdio>
#include <limits>
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

bool run_col01() {
    begin();
    ColorPlanDesc description{};
    ColorPlan plan{};
    PostDiagnostic diagnostic{};

    expect(plan_color(description, plan, diagnostic) == PostError::None,
           "default");
    expect(plan.output_transfer == ColorTransfer::Srgb
               && plan.tone_curve == ToneCurve::Neutral
               && plan.exposure_stops == 0.0f,
           "default plan");

    description.output_transfer = ColorTransfer::Linear;
    expect(plan_color(description, plan, diagnostic) == PostError::Unsupported,
           "linear output");
    description = ColorPlanDesc{};
    description.input_transfer = static_cast<ColorTransfer>(200);
    expect(plan_color(description, plan, diagnostic)
               == PostError::ColorSpaceMismatch,
           "input enum");
    description = ColorPlanDesc{};
    description.output_transfer = static_cast<ColorTransfer>(200);
    expect(plan_color(description, plan, diagnostic)
               == PostError::ColorSpaceMismatch,
           "output enum");
    description = ColorPlanDesc{};
    description.tone_curve = static_cast<ToneCurve>(200);
    expect(plan_color(description, plan, diagnostic)
               == PostError::InvalidArgument,
           "tone enum");
    description = ColorPlanDesc{};
    description.exposure_stops = 17.0f;
    expect(plan_color(description, plan, diagnostic) == PostError::OutOfRange,
           "stops high");
    description.exposure_stops = -17.0f;
    expect(plan_color(description, plan, diagnostic) == PostError::OutOfRange,
           "stops low");
    description = ColorPlanDesc{};
    description.exposure_stops = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_color(description, plan, diagnostic)
               == PostError::NonFiniteValue,
           "stops nan");
    description = ColorPlanDesc{};
    description.white_point_nits = 0.0f;
    expect(plan_color(description, plan, diagnostic) == PostError::OutOfRange,
           "white point");
    description.white_point_nits = std::numeric_limits<f32>::infinity();
    expect(plan_color(description, plan, diagnostic)
               == PostError::NonFiniteValue,
           "white point inf");
    description = ColorPlanDesc{};
    description.tone_already_applied = true;
    expect(plan_color(description, plan, diagnostic)
               == PostError::DoubleTransferGuard,
           "tone guard");
    description = ColorPlanDesc{};
    description.gamma_already_applied = true;
    expect(plan_color(description, plan, diagnostic)
               == PostError::DoubleTransferGuard,
           "gamma guard");
    expect(plan.exposure_stops == 0.0f, "reset");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx07_color_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "col01") { success = run_col01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
