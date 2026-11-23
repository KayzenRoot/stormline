#include "stormline/graphics/vfx/pool_plan.hpp"

#include <cstdio>
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

bool run_pool01() {
    begin();
    VfxPoolDesc pool{};
    pool.pool_id = 3;
    pool.capacity = 100;
    pool.generation = 2;
    pool.expected_generation = 2;
    pool.particles = 20;
    pool.ribbons = 5;
    pool.trails = 3;
    pool.light_requests = 2;
    VfxQualityBudget budget{30, 10, 10, 4};
    VfxPoolPlan plan{};
    VfxDiagnostic diagnostic{};

    expect(plan_pool(pool, budget, plan, diagnostic) == VfxError::None,
           "valid pool");
    expect(plan.admitted_particles == 20 && plan.admitted_ribbons == 5
               && plan.admitted_trails == 3 && plan.admitted_lights == 2,
           "admitted counts");
    expect(plan.available == 70 && !plan.degraded, "available");

    pool.pool_id = 0;
    expect(plan_pool(pool, budget, plan, diagnostic)
               == VfxError::InvalidArgument,
           "zero pool");
    expect(plan.available == 0, "reset");

    pool.pool_id = 3;
    pool.generation = 1;
    expect(plan_pool(pool, budget, plan, diagnostic)
               == VfxError::StaleGeneration,
           "stale generation");
    pool.generation = 2;
    pool.capacity = 0;
    expect(plan_pool(pool, budget, plan, diagnostic)
               == VfxError::InvalidArgument,
           "zero capacity");
    pool.capacity = 25;
    expect(plan_pool(pool, budget, plan, diagnostic)
               == VfxError::PoolExhausted,
           "pool exhausted");
    pool.capacity = 100;
    expect(plan_pool(pool, VfxQualityBudget{0, 10, 10, 4}, plan, diagnostic)
               == VfxError::InvalidArgument,
           "zero budget");
    budget = VfxQualityBudget{10, 2, 1, 1};
    expect(plan_pool(pool, budget, plan, diagnostic) == VfxError::None,
           "degraded pool");
    expect(plan.admitted_particles == 10 && plan.admitted_ribbons == 2
               && plan.admitted_trails == 1 && plan.admitted_lights == 1,
           "clamped counts");
    expect(plan.degraded && plan.available == 86, "degraded receipt");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx08_pool_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "pool01") { success = run_pool01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
