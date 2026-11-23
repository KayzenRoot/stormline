#include "stormline/graphics/canvas2d/light_plan.hpp"

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

bool run_lgt01() {
    begin();
    CanvasLightDesc light{};
    light.light_id = 9;
    light.revision = 1;
    light.intensity = 2.0f;
    light.radius = 3.0f;
    light.color_r = 1.0f;
    light.color_g = 0.5f;
    light.color_b = 0.25f;
    light.layer_id = 2;
    light.falloff = FalloffKind::Linear;
    CanvasLightBudget budget{4, 4.0f};
    LightPlan plan{};
    CanvasDiagnostic diagnostic{};

    expect(plan_light(light, budget, plan, diagnostic) == CanvasError::None,
           "valid light");
    expect(plan.intensity == 2.0f && plan.radius == 3.0f && !plan.clamped,
           "valid plan");

    light.intensity = 8.0f;
    expect(plan_light(light, budget, plan, diagnostic) == CanvasError::None,
           "clamped light");
    expect(plan.intensity == 4.0f && plan.clamped, "clamp receipt");

    light.light_id = 0;
    expect(plan_light(light, budget, plan, diagnostic)
               == CanvasError::InvalidArgument,
           "zero light");
    expect(plan.intensity == 0.0f && !plan.clamped, "reset");

    light.light_id = 9;
    light.intensity = -1.0f;
    expect(plan_light(light, budget, plan, diagnostic)
               == CanvasError::OutOfRange,
           "negative intensity");
    light.intensity = 1.0f;
    light.radius = 0.0f;
    expect(plan_light(light, budget, plan, diagnostic)
               == CanvasError::OutOfRange,
           "zero radius");
    light.radius = 1.0f;
    light.color_g = 1.5f;
    expect(plan_light(light, budget, plan, diagnostic)
               == CanvasError::OutOfRange,
           "color range");
    light.color_g = 0.5f;
    light.falloff = static_cast<FalloffKind>(200);
    expect(plan_light(light, budget, plan, diagnostic)
               == CanvasError::InvalidArgument,
           "invalid falloff");
    light.falloff = FalloffKind::Radial;
    budget.max_lights = 0;
    expect(plan_light(light, budget, plan, diagnostic)
               == CanvasError::LightBudgetExceeded,
           "light budget");
    budget = CanvasLightBudget{4, 4.0f};
    budget.max_intensity = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_light(light, budget, plan, diagnostic)
               == CanvasError::NonFiniteValue,
           "nonfinite budget");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two01_light_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "lgt01") { success = run_lgt01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
