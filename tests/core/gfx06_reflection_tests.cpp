#include "stormline/graphics/lighting/reflection_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::lighting;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_ref01() {
    begin();
    ReflectionPlan plan{};
    LightingDiagnostic diagnostic{};

    ReflectionRequest request{};
    request.preferred = ReflectionMode::ScreenSpace;
    request.ssr_available = true;
    request.probe_available = true;
    request.environment_available = true;
    expect(plan_reflections(request, plan, diagnostic) == LightingError::None,
           "ssr");
    expect(plan.mode == ReflectionMode::ScreenSpace
               && plan.fallback == ReflectionMode::Probe
               && plan.offscreen_fallback && !plan.degraded,
           "ssr plan");

    request.ssr_available = false;
    expect(plan_reflections(request, plan, diagnostic) == LightingError::None,
           "probe fallback");
    expect(plan.mode == ReflectionMode::Probe
               && plan.fallback == ReflectionMode::Environment
               && !plan.offscreen_fallback && plan.degraded,
           "probe fallback plan");

    request.probe_available = false;
    expect(plan_reflections(request, plan, diagnostic) == LightingError::None,
           "environment fallback");
    expect(plan.mode == ReflectionMode::Environment
               && plan.fallback == ReflectionMode::Unsupported
               && !plan.offscreen_fallback && plan.degraded,
           "environment fallback plan");

    request.environment_available = false;
    expect(plan_reflections(request, plan, diagnostic)
               == LightingError::ReflectionOffscreen,
           "offscreen");
    expect(plan.mode == ReflectionMode::Unsupported && !plan.degraded,
           "offscreen reset");

    request = ReflectionRequest{};
    request.preferred = ReflectionMode::Probe;
    request.probe_available = true;
    request.environment_available = true;
    expect(plan_reflections(request, plan, diagnostic) == LightingError::None,
           "probe direct");
    expect(plan.mode == ReflectionMode::Probe
               && plan.fallback == ReflectionMode::Environment
               && !plan.degraded,
           "probe direct plan");

    request.probe_available = false;
    expect(plan_reflections(request, plan, diagnostic) == LightingError::None,
           "probe to environment");
    expect(plan.mode == ReflectionMode::Environment && plan.degraded,
           "probe to environment plan");

    request.environment_available = false;
    expect(plan_reflections(request, plan, diagnostic)
               == LightingError::ReflectionOffscreen,
           "probe unavailable");

    request = ReflectionRequest{};
    request.preferred = ReflectionMode::Environment;
    request.environment_available = true;
    expect(plan_reflections(request, plan, diagnostic) == LightingError::None,
           "environment direct");
    expect(plan.mode == ReflectionMode::Environment && !plan.degraded,
           "environment direct plan");
    request.environment_available = false;
    expect(plan_reflections(request, plan, diagnostic)
               == LightingError::ReflectionOffscreen,
           "environment missing");

    request = ReflectionRequest{};
    request.preferred = ReflectionMode::Unsupported;
    expect(plan_reflections(request, plan, diagnostic) == LightingError::Unsupported,
           "unsupported");
    request.preferred = static_cast<ReflectionMode>(200);
    expect(plan_reflections(request, plan, diagnostic)
               == LightingError::InvalidArgument,
           "invalid enum");
    request = ReflectionRequest{};
    request.roughness_band = 4;
    expect(plan_reflections(request, plan, diagnostic)
               == LightingError::InvalidArgument,
           "roughness");
    expect(diagnostic.code == LightingError::InvalidArgument, "diagnostic");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx06_reflection_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "ref01") { success = run_ref01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
