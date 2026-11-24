#ifndef STORMLINE_ANIMATION_TIMELINE_PLAN_HPP
#define STORMLINE_ANIMATION_TIMELINE_PLAN_HPP

#include <limits>

#include "stormline/animation/animation_types.hpp"

namespace stormline::animation {

struct TimelineDesc {
    u32 timeline_id{0};
    u32 revision{0};
    u32 fps_numerator{0};
    u32 fps_denominator{0};
    u64 duration_frames{0};
    u32 sample_rate{0};
    u64 loop_start_frame{0};
    u64 loop_end_frame{0};
};

struct TimelinePlan {
    u64 frame_count{0};
    u64 sample_count{0};
    u64 loop_length_frames{0};
};

namespace detail {

inline bool checked_mul_u64(u64 left, u64 right, u64& result) noexcept {
    if (left != 0 && right > std::numeric_limits<u64>::max() / left) {
        return false;
    }
    result = left * right;
    return true;
}

}  // namespace detail

[[nodiscard]] inline AnimationError plan_timeline(
    const TimelineDesc& timeline, TimelinePlan& plan,
    AnimationDiagnostic& diagnostic) noexcept {
    plan = TimelinePlan{};
    diagnostic = AnimationDiagnostic{};
    if (timeline.timeline_id == 0 || timeline.revision == 0
        || timeline.fps_numerator == 0 || timeline.fps_denominator == 0
        || timeline.duration_frames == 0 || timeline.sample_rate == 0) {
        return detail::set_animation_error(
            diagnostic, AnimationError::InvalidArgument, timeline.timeline_id,
            0);
    }
    if (timeline.loop_end_frame <= timeline.loop_start_frame
        || timeline.loop_end_frame > timeline.duration_frames) {
        return detail::set_animation_error(
            diagnostic, AnimationError::TimeInvalid, timeline.timeline_id, 0);
    }
    u64 scaled = 0;
    if (!detail::checked_mul_u64(
            timeline.duration_frames, timeline.fps_denominator, scaled)
        || !detail::checked_mul_u64(scaled, timeline.sample_rate, scaled)) {
        return detail::set_animation_error(
            diagnostic, AnimationError::OutOfRange, timeline.timeline_id, 0);
    }
    plan.frame_count = timeline.duration_frames;
    plan.sample_count = scaled / timeline.fps_numerator;
    plan.loop_length_frames
        = timeline.loop_end_frame - timeline.loop_start_frame;
    return AnimationError::None;
}

}  // namespace stormline::animation

#endif  // STORMLINE_ANIMATION_TIMELINE_PLAN_HPP
