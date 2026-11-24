#ifndef STORMLINE_PHYSICS2D_MASK_PLAN_HPP
#define STORMLINE_PHYSICS2D_MASK_PLAN_HPP

#include <array>

#include "stormline/physics2d/physics2d_types.hpp"

namespace stormline::physics2d {

struct MaskDesc {
    u32 mask_id{0};
    u32 revision{0};
    u32 category_bits{0};
    u32 collision_bits{0};
    u32 group_index{0};
};

struct MaskSetDesc {
    u32 world_id{0};
    u32 revision{0};
    u32 mask_count{0};
    std::array<MaskDesc, kMaxMasks> masks{};
};

struct MaskPlan {
    u32 mask_count{0};
    u32 group_count{0};
    u32 symmetric_pair_count{0};
};

[[nodiscard]] inline bool masks_compatible(
    const MaskDesc& a, const MaskDesc& b) noexcept {
    if (a.group_index != 0 || b.group_index != 0) {
        return a.group_index != 0 && a.group_index == b.group_index;
    }
    return (a.category_bits & b.collision_bits) != 0
        && (b.category_bits & a.collision_bits) != 0;
}

[[nodiscard]] inline Physics2DError plan_masks(
    const MaskSetDesc& masks, MaskPlan& plan,
    Physics2DDiagnostic& diagnostic) noexcept {
    plan = MaskPlan{};
    diagnostic = Physics2DDiagnostic{};
    if (masks.world_id == 0 || masks.revision == 0) {
        return detail::set_physics2d_error(
            diagnostic, Physics2DError::InvalidArgument, masks.world_id, 0);
    }
    if (masks.mask_count > kMaxMasks) {
        return detail::set_physics2d_error(
            diagnostic, Physics2DError::CapacityFull, masks.world_id, 0);
    }
    for (u32 index = 0; index < masks.mask_count; ++index) {
        const MaskDesc& mask = masks.masks[index];
        if (mask.mask_id == 0 || mask.revision == 0
            || mask.category_bits == 0 || mask.collision_bits == 0) {
            return detail::set_physics2d_error(
                diagnostic, Physics2DError::MaskInvalid, masks.world_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (masks.masks[previous].mask_id == mask.mask_id) {
                return detail::set_physics2d_error(
                    diagnostic, Physics2DError::DuplicateId, masks.world_id,
                    index);
            }
        }
    }
    plan.mask_count = masks.mask_count;
    for (u32 index = 0; index < masks.mask_count; ++index) {
        const MaskDesc& mask = masks.masks[index];
        if (mask.group_index == 0) {
            continue;
        }
        bool seen = false;
        for (u32 previous = 0; previous < index; ++previous) {
            if (masks.masks[previous].group_index == mask.group_index) {
                seen = true;
                break;
            }
        }
        if (!seen) {
            ++plan.group_count;
        }
    }
    for (u32 first = 0; first < masks.mask_count; ++first) {
        for (u32 second = first + 1; second < masks.mask_count; ++second) {
            if (masks_compatible(masks.masks[first], masks.masks[second])) {
                ++plan.symmetric_pair_count;
            }
        }
    }
    return Physics2DError::None;
}

}  // namespace stormline::physics2d

#endif  // STORMLINE_PHYSICS2D_MASK_PLAN_HPP
