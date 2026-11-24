#ifndef STORMLINE_PHYSICS3D_INTEGRATION_PLAN_HPP
#define STORMLINE_PHYSICS3D_INTEGRATION_PLAN_HPP

#include <array>

#include "stormline/physics3d/physics3d_types.hpp"

namespace stormline::physics3d {

inline constexpr u32 kMaxTickHz = 240;

struct IntegrationDesc {
    u32 integration_id{0};
    u32 revision{0};
    IntegrationKind kind{IntegrationKind::Scene};
    u32 world_id{0};
    u32 scene_id{0};
    u32 cell_id{0};
    u32 tick_hz{0};
    u32 authority_bits{0};
};

struct IntegrationSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 integration_count{0};
    std::array<IntegrationDesc, kMaxIntegrations> integrations{};
};

struct IntegrationPlan {
    u32 integration_count{0};
    u32 scene_count{0};
    u32 streaming_count{0};
    u32 authority_count{0};
    u32 tick_count{0};
    u32 min_tick_hz{0};
    u32 max_tick_hz{0};
};

[[nodiscard]] inline Physics3DError plan_integrations(
    const IntegrationSetDesc& integrations, IntegrationPlan& plan,
    Physics3DDiagnostic& diagnostic) noexcept {
    plan = IntegrationPlan{};
    diagnostic = Physics3DDiagnostic{};
    if (integrations.world_id == 0 || integrations.revision == 0) {
        return detail::set_physics3d_error(
            diagnostic, Physics3DError::InvalidArgument,
            integrations.world_id, 0);
    }
    if (integrations.integration_count > kMaxIntegrations) {
        return detail::set_physics3d_error(
            diagnostic, Physics3DError::CapacityFull, integrations.world_id,
            0);
    }
    for (u32 index = 0; index < integrations.integration_count; ++index) {
        const IntegrationDesc& entry = integrations.integrations[index];
        if (entry.integration_id == 0 || entry.revision == 0
            || entry.world_id == 0 || !detail::valid_integration_kind(entry.kind)) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::IntegrationInvalid,
                integrations.world_id, index);
        }
        if (entry.world_id != integrations.world_id) {
            return detail::set_physics3d_error(
                diagnostic, Physics3DError::InvalidArgument,
                integrations.world_id, index);
        }
        switch (entry.kind) {
            case IntegrationKind::Scene:
                if (entry.scene_id == 0) {
                    return detail::set_physics3d_error(
                        diagnostic, Physics3DError::IntegrationInvalid,
                        integrations.world_id, index);
                }
                break;
            case IntegrationKind::Streaming:
                if (entry.cell_id == 0) {
                    return detail::set_physics3d_error(
                        diagnostic, Physics3DError::IntegrationInvalid,
                        integrations.world_id, index);
                }
                break;
            case IntegrationKind::Authority:
                if (entry.authority_bits == 0) {
                    return detail::set_physics3d_error(
                        diagnostic, Physics3DError::IntegrationInvalid,
                        integrations.world_id, index);
                }
                break;
            case IntegrationKind::Tick:
                if (entry.tick_hz == 0 || entry.tick_hz > kMaxTickHz) {
                    return detail::set_physics3d_error(
                        diagnostic, Physics3DError::OutOfRange,
                        integrations.world_id, index);
                }
                break;
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (integrations.integrations[previous].integration_id
                == entry.integration_id) {
                return detail::set_physics3d_error(
                    diagnostic, Physics3DError::DuplicateId,
                    integrations.world_id, index);
            }
        }
    }
    plan.integration_count = integrations.integration_count;
    for (u32 index = 0; index < integrations.integration_count; ++index) {
        const IntegrationDesc& entry = integrations.integrations[index];
        switch (entry.kind) {
            case IntegrationKind::Scene:
                ++plan.scene_count;
                break;
            case IntegrationKind::Streaming:
                ++plan.streaming_count;
                break;
            case IntegrationKind::Authority:
                ++plan.authority_count;
                break;
            case IntegrationKind::Tick:
                ++plan.tick_count;
                if (plan.min_tick_hz == 0 || entry.tick_hz < plan.min_tick_hz) {
                    plan.min_tick_hz = entry.tick_hz;
                }
                if (entry.tick_hz > plan.max_tick_hz) {
                    plan.max_tick_hz = entry.tick_hz;
                }
                break;
        }
    }
    return Physics3DError::None;
}

}  // namespace stormline::physics3d

#endif  // STORMLINE_PHYSICS3D_INTEGRATION_PLAN_HPP
