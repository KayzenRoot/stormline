#include "stormline/graphics/post/motion_blur.hpp"

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

bool run_mbl01() {
    begin();
    MotionBlurDesc description{};
    MotionBlurPlan plan{};
    PostDiagnostic diagnostic{};

    expect(plan_motion_blur(description, plan, diagnostic) == PostError::None,
           "disabled default");
    expect(!plan.enabled, "disabled plan");

    description.enabled = true;
    description.max_velocity_pixels = 32.0f;
    expect(plan_motion_blur(description, plan, diagnostic) == PostError::None,
           "enabled");
    expect(plan.enabled, "enabled plan");

    description.reduced_motion = true;
    expect(plan_motion_blur(description, plan, diagnostic) == PostError::None,
           "reduced motion");
    expect(!plan.enabled, "reduced motion plan");

    description.reduced_motion = false;
    description.max_velocity_pixels = 0.0f;
    expect(plan_motion_blur(description, plan, diagnostic)
               == PostError::Unsupported,
           "unsupported enable");
    expect(!plan.enabled, "unsupported reset");

    description.max_velocity_pixels = 1.0f;
    description.shutter_angle_degrees = -1.0f;
    expect(plan_motion_blur(description, plan, diagnostic)
               == PostError::OutOfRange,
           "shutter low");
    description.shutter_angle_degrees = 361.0f;
    expect(plan_motion_blur(description, plan, diagnostic)
               == PostError::OutOfRange,
           "shutter high");
    description.shutter_angle_degrees = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_motion_blur(description, plan, diagnostic)
               == PostError::NonFiniteValue,
           "shutter nan");
    description.shutter_angle_degrees = 180.0f;
    description.max_velocity_pixels = -1.0f;
    expect(plan_motion_blur(description, plan, diagnostic)
               == PostError::OutOfRange,
           "velocity negative");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx07_motion_blur_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "mbl01") { success = run_mbl01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
