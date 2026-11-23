#include "stormline/tilemap/parallax_plan.hpp"

#include <cstdio>
#include <limits>
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

bool run_prx01() {
    begin();
    ParallaxLayerDesc parallax{};
    parallax.layer_id = 3;
    parallax.revision = 1;
    parallax.factor_x = 0.5f;
    parallax.factor_y = 0.25f;
    parallax.repeat_x = true;
    ParallaxPlan plan{};
    TilemapDiagnostic diagnostic{};

    expect(plan_parallax(parallax, plan, diagnostic) == TilemapError::None,
           "valid parallax");
    expect(plan.factor_x == 0.5f && plan.factor_y == 0.25f
               && plan.repeat_x && !plan.repeat_y,
           "valid plan");

    parallax.layer_id = 0;
    expect(plan_parallax(parallax, plan, diagnostic)
               == TilemapError::InvalidArgument,
           "zero layer");
    expect(plan.factor_x == 1.0f && !plan.repeat_x, "reset");

    parallax.layer_id = 3;
    parallax.factor_y = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_parallax(parallax, plan, diagnostic)
               == TilemapError::NonFiniteValue,
           "nonfinite factor");
    parallax.factor_y = 0.25f;
    parallax.factor_x = -0.1f;
    expect(plan_parallax(parallax, plan, diagnostic)
               == TilemapError::ParallaxInvalid,
           "negative factor");
    parallax.factor_x = 4.5f;
    expect(plan_parallax(parallax, plan, diagnostic)
               == TilemapError::ParallaxInvalid,
           "factor cap");
    parallax.factor_x = 1.0f;
    parallax.revision = 0;
    expect(plan_parallax(parallax, plan, diagnostic)
               == TilemapError::InvalidArgument,
           "zero revision");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two02_parallax_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "prx01") { success = run_prx01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
