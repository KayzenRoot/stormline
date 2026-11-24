#ifndef STORMLINE_SPATIAL_ORIGIN_PLAN_HPP
#define STORMLINE_SPATIAL_ORIGIN_PLAN_HPP

#include "stormline/spatial/spatial_types.hpp"

namespace stormline::spatial {

struct OriginEpochDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 old_epoch{0};
    u32 new_epoch{0};
    f32 old_x{0.0f};
    f32 old_y{0.0f};
    f32 old_z{0.0f};
    f32 new_x{0.0f};
    f32 new_y{0.0f};
    f32 new_z{0.0f};
    bool physics_ack{false};
    bool render_ack{false};
    bool network_ack{false};
};

struct OriginPlan {
    u32 old_epoch{0};
    u32 new_epoch{0};
    bool accepted{false};
};

[[nodiscard]] inline SpatialError plan_origin_change(
    const OriginEpochDesc& origin, OriginPlan& plan,
    SpatialDiagnostic& diagnostic) noexcept {
    plan = OriginPlan{};
    diagnostic = SpatialDiagnostic{};
    if (origin.world_id == 0 || origin.revision == 0) {
        return detail::set_spatial_error(
            diagnostic, SpatialError::InvalidArgument, origin.world_id, 0);
    }
    if (origin.old_epoch == 0 || origin.new_epoch == 0
        || origin.old_epoch == origin.new_epoch) {
        return detail::set_spatial_error(
            diagnostic, SpatialError::OriginInvalid, origin.world_id, 0);
    }
    if (!detail::finite(origin.old_x) || !detail::finite(origin.old_y)
        || !detail::finite(origin.old_z) || !detail::finite(origin.new_x)
        || !detail::finite(origin.new_y) || !detail::finite(origin.new_z)) {
        return detail::set_spatial_error(
            diagnostic, SpatialError::NonFiniteValue, origin.world_id, 0);
    }
    plan.old_epoch = origin.old_epoch;
    plan.new_epoch = origin.new_epoch;
    plan.accepted =
        origin.physics_ack && origin.render_ack && origin.network_ack;
    return SpatialError::None;
}

}  // namespace stormline::spatial

#endif  // STORMLINE_SPATIAL_ORIGIN_PLAN_HPP
