#include "stormline/graphics/lighting/gi_plan.hpp"

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

bool run_gi01() {
    begin();
    GiPlan plan{};
    LightingDiagnostic diagnostic{};

    GiRequest request{};
    request.requested = GiMode::Baked;
    request.baked_available = true;
    expect(plan_gi(request, plan, diagnostic) == LightingError::None, "baked");
    expect(plan.mode == GiMode::Baked && !plan.degraded, "baked mode");

    request.baked_available = false;
    request.probe_available = true;
    expect(plan_gi(request, plan, diagnostic) == LightingError::None, "probe");
    expect(plan.mode == GiMode::ProbeFallback && plan.degraded, "probe mode");

    request.probe_available = false;
    request.environment_available = true;
    expect(plan_gi(request, plan, diagnostic) == LightingError::None,
           "environment");
    expect(plan.mode == GiMode::Environment && plan.degraded,
           "environment mode");

    request.environment_available = false;
    expect(plan_gi(request, plan, diagnostic) == LightingError::GiUnavailable,
           "unavailable");
    expect(plan.mode == GiMode::Unsupported && !plan.degraded, "unavailable reset");

    request = GiRequest{};
    request.requested = GiMode::Environment;
    request.environment_available = true;
    expect(plan_gi(request, plan, diagnostic) == LightingError::None,
           "environment direct");
    expect(plan.mode == GiMode::Environment && !plan.degraded,
           "environment direct mode");
    request.environment_available = false;
    expect(plan_gi(request, plan, diagnostic) == LightingError::GiUnavailable,
           "environment missing");

    request = GiRequest{};
    request.requested = GiMode::ProbeFallback;
    request.probe_available = true;
    expect(plan_gi(request, plan, diagnostic) == LightingError::None,
           "probe direct");
    expect(plan.mode == GiMode::ProbeFallback && !plan.degraded,
           "probe direct mode");
    request.probe_available = false;
    expect(plan_gi(request, plan, diagnostic) == LightingError::GiUnavailable,
           "probe missing");

    request = GiRequest{};
    request.requested = GiMode::Unsupported;
    expect(plan_gi(request, plan, diagnostic) == LightingError::Unsupported,
           "unsupported");
    request.requested = static_cast<GiMode>(200);
    expect(plan_gi(request, plan, diagnostic) == LightingError::InvalidArgument,
           "invalid enum");
    expect(diagnostic.code == LightingError::InvalidArgument, "diagnostic");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx06_gi_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "gi01") { success = run_gi01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
