#ifndef STORMLINE_GRAPHICS_VFX_POOL_PLAN_HPP
#define STORMLINE_GRAPHICS_VFX_POOL_PLAN_HPP

#include "stormline/graphics/vfx/graph_plan.hpp"

namespace stormline::graphics::vfx {

struct VfxQualityBudget {
    u32 max_particles{0};
    u32 max_ribbons{0};
    u32 max_trails{0};
    u32 max_light_requests{0};
};

struct VfxPoolDesc {
    u32 pool_id{0};
    u32 capacity{0};
    u32 generation{0};
    u32 expected_generation{0};
    u32 particles{0};
    u32 ribbons{0};
    u32 trails{0};
    u32 light_requests{0};
};

struct VfxPoolPlan {
    u32 admitted_particles{0};
    u32 admitted_ribbons{0};
    u32 admitted_trails{0};
    u32 admitted_lights{0};
    u32 available{0};
    bool degraded{false};
};

namespace detail {

inline u32 clamp_request(u32 requested, u32 cap) noexcept {
    return requested > cap ? cap : requested;
}

}  // namespace detail

[[nodiscard]] inline VfxError plan_pool(
    const VfxPoolDesc& pool, const VfxQualityBudget& budget,
    VfxPoolPlan& plan, VfxDiagnostic& diagnostic) noexcept {
    plan = VfxPoolPlan{};
    diagnostic = VfxDiagnostic{};
    if (pool.pool_id == 0 || pool.capacity == 0) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, pool.pool_id, 0, 0);
    }
    if (pool.generation != pool.expected_generation) {
        return detail::set_vfx_error(
            diagnostic, VfxError::StaleGeneration, pool.pool_id, 0, 0);
    }
    if (budget.max_particles == 0 || budget.max_ribbons == 0
        || budget.max_trails == 0 || budget.max_light_requests == 0) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, pool.pool_id, 0, 0);
    }
    const u64 requested = static_cast<u64>(pool.particles) + pool.ribbons
        + pool.trails + pool.light_requests;
    if (requested > pool.capacity) {
        return detail::set_vfx_error(
            diagnostic, VfxError::PoolExhausted, pool.pool_id, 0, 0);
    }
    plan.admitted_particles =
        detail::clamp_request(pool.particles, budget.max_particles);
    plan.admitted_ribbons =
        detail::clamp_request(pool.ribbons, budget.max_ribbons);
    plan.admitted_trails =
        detail::clamp_request(pool.trails, budget.max_trails);
    plan.admitted_lights =
        detail::clamp_request(pool.light_requests, budget.max_light_requests);
    plan.degraded = plan.admitted_particles != pool.particles
        || plan.admitted_ribbons != pool.ribbons
        || plan.admitted_trails != pool.trails
        || plan.admitted_lights != pool.light_requests;
    const u64 admitted = static_cast<u64>(plan.admitted_particles)
        + plan.admitted_ribbons + plan.admitted_trails + plan.admitted_lights;
    plan.available =
        static_cast<u32>(static_cast<u64>(pool.capacity) - admitted);
    return VfxError::None;
}

}  // namespace stormline::graphics::vfx

#endif  // STORMLINE_GRAPHICS_VFX_POOL_PLAN_HPP
