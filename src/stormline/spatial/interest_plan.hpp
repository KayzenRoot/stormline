#ifndef STORMLINE_SPATIAL_INTEREST_PLAN_HPP
#define STORMLINE_SPATIAL_INTEREST_PLAN_HPP

#include <array>

#include "stormline/spatial/spatial_types.hpp"

namespace stormline::spatial {

struct InterestBounds {
    f32 min_x{0.0f};
    f32 min_z{0.0f};
    f32 max_x{0.0f};
    f32 max_z{0.0f};
};

struct InterestSourceDesc {
    u32 source_id{0};
    u32 revision{0};
    InterestRole role{InterestRole::Player};
    InterestBounds bounds{};
    u32 priority{0};
    bool required_complete{false};
};

struct InterestSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 source_count{0};
    std::array<InterestSourceDesc, kMaxInterestSources> sources{};
};

struct InterestPlan {
    u32 source_count{0};
    u32 complete_count{0};
    u32 incomplete_count{0};
    InterestBounds union_bounds{};
};

[[nodiscard]] inline SpatialError plan_interest(
    const InterestSetDesc& interest, InterestPlan& plan,
    SpatialDiagnostic& diagnostic) noexcept {
    plan = InterestPlan{};
    diagnostic = SpatialDiagnostic{};
    if (interest.world_id == 0 || interest.revision == 0) {
        return detail::set_spatial_error(
            diagnostic, SpatialError::InvalidArgument, interest.world_id, 0);
    }
    if (interest.source_count > kMaxInterestSources) {
        return detail::set_spatial_error(
            diagnostic, SpatialError::CapacityFull, interest.world_id, 0);
    }
    for (u32 index = 0; index < interest.source_count; ++index) {
        const InterestSourceDesc& source = interest.sources[index];
        if (source.source_id == 0 || source.revision == 0) {
            return detail::set_spatial_error(
                diagnostic, SpatialError::InterestInvalid, source.source_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (interest.sources[previous].source_id == source.source_id) {
                return detail::set_spatial_error(
                    diagnostic, SpatialError::DuplicateId, source.source_id,
                    index);
            }
        }
        if (!detail::valid_interest_role(source.role)) {
            return detail::set_spatial_error(
                diagnostic, SpatialError::InterestInvalid, source.source_id,
                index);
        }
        const InterestBounds& bounds = source.bounds;
        if (!detail::finite(bounds.min_x) || !detail::finite(bounds.min_z)
            || !detail::finite(bounds.max_x)
            || !detail::finite(bounds.max_z)) {
            return detail::set_spatial_error(
                diagnostic, SpatialError::NonFiniteValue, source.source_id,
                index);
        }
        if (!(bounds.min_x < bounds.max_x)
            || !(bounds.min_z < bounds.max_z)) {
            return detail::set_spatial_error(
                diagnostic, SpatialError::OutOfRange, source.source_id,
                index);
        }
    }
    plan.source_count = interest.source_count;
    for (u32 index = 0; index < interest.source_count; ++index) {
        const InterestSourceDesc& source = interest.sources[index];
        if (source.required_complete) {
            ++plan.complete_count;
        } else {
            ++plan.incomplete_count;
        }
        if (index == 0) {
            plan.union_bounds = source.bounds;
            continue;
        }
        if (source.bounds.min_x < plan.union_bounds.min_x) {
            plan.union_bounds.min_x = source.bounds.min_x;
        }
        if (source.bounds.min_z < plan.union_bounds.min_z) {
            plan.union_bounds.min_z = source.bounds.min_z;
        }
        if (source.bounds.max_x > plan.union_bounds.max_x) {
            plan.union_bounds.max_x = source.bounds.max_x;
        }
        if (source.bounds.max_z > plan.union_bounds.max_z) {
            plan.union_bounds.max_z = source.bounds.max_z;
        }
    }
    return SpatialError::None;
}

}  // namespace stormline::spatial

#endif  // STORMLINE_SPATIAL_INTEREST_PLAN_HPP
