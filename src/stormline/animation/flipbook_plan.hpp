#ifndef STORMLINE_ANIMATION_FLIPBOOK_PLAN_HPP
#define STORMLINE_ANIMATION_FLIPBOOK_PLAN_HPP

#include <limits>

#include "stormline/animation/animation_types.hpp"

namespace stormline::animation {

struct FlipbookFrame {
    u32 frame_id{0};
    u32 sprite_id{0};
    u32 atlas_region_id{0};
    u32 hold_frames{0};
};

struct FlipbookDesc {
    u32 clip_id{0};
    u32 revision{0};
    u32 timebase_denominator{0};
    u32 frame_count{0};
    std::array<FlipbookFrame, kMaxFlipbookFrames> frames{};
};

struct FlipbookPlan {
    u32 frame_count{0};
    u64 total_frames{0};
};

[[nodiscard]] inline AnimationError plan_flipbook(
    const FlipbookDesc& flipbook, FlipbookPlan& plan,
    AnimationDiagnostic& diagnostic) noexcept {
    plan = FlipbookPlan{};
    diagnostic = AnimationDiagnostic{};
    if (flipbook.clip_id == 0 || flipbook.revision == 0
        || flipbook.timebase_denominator == 0) {
        return detail::set_animation_error(
            diagnostic, AnimationError::InvalidArgument, flipbook.clip_id, 0);
    }
    if (flipbook.frame_count == 0
        || flipbook.frame_count > kMaxFlipbookFrames) {
        return detail::set_animation_error(
            diagnostic, AnimationError::FlipbookInvalid, flipbook.clip_id, 0);
    }
    u64 total = 0;
    for (u32 index = 0; index < flipbook.frame_count; ++index) {
        const FlipbookFrame& frame = flipbook.frames[index];
        if (frame.frame_id == 0 || frame.sprite_id == 0
            || frame.atlas_region_id == 0 || frame.hold_frames == 0) {
            return detail::set_animation_error(
                diagnostic, AnimationError::FlipbookInvalid, flipbook.clip_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (flipbook.frames[previous].frame_id == frame.frame_id) {
                return detail::set_animation_error(
                    diagnostic, AnimationError::DuplicateId, flipbook.clip_id,
                    index);
            }
        }
        if (total > std::numeric_limits<u64>::max() - frame.hold_frames) {
            return detail::set_animation_error(
                diagnostic, AnimationError::OutOfRange, flipbook.clip_id,
                index);
        }
        total += frame.hold_frames;
    }
    if (total == 0) {
        return detail::set_animation_error(
            diagnostic, AnimationError::TimeInvalid, flipbook.clip_id, 0);
    }
    plan.frame_count = flipbook.frame_count;
    plan.total_frames = total;
    return AnimationError::None;
}

}  // namespace stormline::animation

#endif  // STORMLINE_ANIMATION_FLIPBOOK_PLAN_HPP
