#ifndef STORMLINE_GRAPHICS_VFX_EMITTER_PLAN_HPP
#define STORMLINE_GRAPHICS_VFX_EMITTER_PLAN_HPP

#include <cmath>
#include <limits>

#include "stormline/graphics/vfx/graph_plan.hpp"

namespace stormline::graphics::vfx {

struct VfxEmitterDesc {
    u32 emitter_id{0};
    u32 revision{0};
    u32 graph_id{0};
    u32 graph_revision{0};
    u32 spawn_per_tick{0};
    u32 burst_count{0};
    f32 lifetime_seconds{0.0f};
    u64 seed{0};
    SimulationPolicy policy{SimulationPolicy::CpuReference};
};

struct VfxSpawnBudget {
    u32 max_spawn_per_tick{0};
    u32 max_alive{0};
};

struct VfxEmitterPlan {
    u32 spawn_per_tick{0};
    u32 alive_capacity{0};
    SimulationPolicy policy{SimulationPolicy::CpuReference};
};

[[nodiscard]] inline VfxError plan_emitter(
    const VfxEmitterDesc& emitter, const VfxSpawnBudget& budget,
    VfxEmitterPlan& plan, VfxDiagnostic& diagnostic) noexcept {
    plan = VfxEmitterPlan{};
    diagnostic = VfxDiagnostic{};
    if (emitter.emitter_id == 0 || emitter.revision == 0
        || emitter.graph_id == 0 || emitter.graph_revision == 0) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, emitter.emitter_id,
            emitter.graph_id, 0);
    }
    if (!detail::valid_simulation_policy(emitter.policy)) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, emitter.emitter_id,
            emitter.graph_id, 0);
    }
    if (!std::isfinite(emitter.lifetime_seconds)) {
        return detail::set_vfx_error(
            diagnostic, VfxError::NonFiniteValue, emitter.emitter_id,
            emitter.graph_id, 0);
    }
    if (!(emitter.lifetime_seconds > 0.0f)) {
        return detail::set_vfx_error(
            diagnostic, VfxError::OutOfRange, emitter.emitter_id,
            emitter.graph_id, 0);
    }
    if (budget.max_spawn_per_tick == 0 || budget.max_alive == 0) {
        return detail::set_vfx_error(
            diagnostic, VfxError::InvalidArgument, emitter.emitter_id,
            emitter.graph_id, 0);
    }
    if (emitter.spawn_per_tick
        > std::numeric_limits<u32>::max() - emitter.burst_count) {
        return detail::set_vfx_error(
            diagnostic, VfxError::OutOfRange, emitter.emitter_id,
            emitter.graph_id, 0);
    }
    const u32 requested = emitter.spawn_per_tick + emitter.burst_count;
    if (requested > budget.max_spawn_per_tick
        || emitter.burst_count > budget.max_alive) {
        return detail::set_vfx_error(
            diagnostic, VfxError::SpawnBudgetExceeded, emitter.emitter_id,
            emitter.graph_id, 0);
    }
    plan.spawn_per_tick = requested;
    plan.alive_capacity = budget.max_alive;
    plan.policy = emitter.policy;
    return VfxError::None;
}

}  // namespace stormline::graphics::vfx

#endif  // STORMLINE_GRAPHICS_VFX_EMITTER_PLAN_HPP
