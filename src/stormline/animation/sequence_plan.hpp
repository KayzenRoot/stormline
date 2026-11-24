#ifndef STORMLINE_ANIMATION_SEQUENCE_PLAN_HPP
#define STORMLINE_ANIMATION_SEQUENCE_PLAN_HPP

#include "stormline/animation/animation_types.hpp"

namespace stormline::animation {

struct SequenceCue {
    u32 cue_id{0};
    u32 revision{0};
    TrackKind kind{TrackKind::Sprite};
    u64 tick{0};
    u64 duration_ticks{0};
};

struct SequenceTrack {
    u32 track_id{0};
    u32 revision{0};
    TrackKind kind{TrackKind::Sprite};
    u32 cue_count{0};
    std::array<SequenceCue, kMaxSequenceCues> cues{};
};

struct SequenceDesc {
    u32 sequence_id{0};
    u32 revision{0};
    u32 timebase_denominator{0};
    u64 duration_ticks{0};
    u32 track_count{0};
    std::array<SequenceTrack, kMaxSequenceTracks> tracks{};
    u32 nesting_depth{0};
};

struct SequencePlan {
    u32 track_count{0};
    u32 cue_count{0};
    u32 max_depth{0};
};

[[nodiscard]] inline AnimationError plan_sequence(
    const SequenceDesc& sequence, SequencePlan& plan,
    AnimationDiagnostic& diagnostic) noexcept {
    plan = SequencePlan{};
    diagnostic = AnimationDiagnostic{};
    if (sequence.sequence_id == 0 || sequence.revision == 0
        || sequence.timebase_denominator == 0
        || sequence.duration_ticks == 0) {
        return detail::set_animation_error(
            diagnostic, AnimationError::InvalidArgument, sequence.sequence_id,
            0);
    }
    if (sequence.nesting_depth > kMaxSequenceDepth) {
        return detail::set_animation_error(
            diagnostic, AnimationError::DepthExceeded, sequence.sequence_id, 0);
    }
    if (sequence.track_count == 0
        || sequence.track_count > kMaxSequenceTracks) {
        return detail::set_animation_error(
            diagnostic, AnimationError::SequenceInvalid, sequence.sequence_id,
            0);
    }
    std::array<u32, kMaxSequenceTracks * kMaxSequenceCues> cue_ids{};
    u32 cue_id_count = 0;
    u32 total_cues = 0;
    for (u32 track_index = 0; track_index < sequence.track_count;
         ++track_index) {
        const SequenceTrack& track = sequence.tracks[track_index];
        if (track.track_id == 0 || track.revision == 0
            || !detail::valid_track_kind(track.kind)) {
            return detail::set_animation_error(
                diagnostic, AnimationError::SequenceInvalid,
                sequence.sequence_id, track_index);
        }
        for (u32 previous = 0; previous < track_index; ++previous) {
            if (sequence.tracks[previous].track_id == track.track_id) {
                return detail::set_animation_error(
                    diagnostic, AnimationError::DuplicateId,
                    sequence.sequence_id, track_index);
            }
        }
        if (track.cue_count > kMaxSequenceCues) {
            return detail::set_animation_error(
                diagnostic, AnimationError::SequenceInvalid,
                sequence.sequence_id, track_index);
        }
        for (u32 cue_index = 0; cue_index < track.cue_count; ++cue_index) {
            const SequenceCue& cue = track.cues[cue_index];
            if (cue.cue_id == 0 || cue.revision == 0
                || !detail::valid_track_kind(cue.kind)) {
                return detail::set_animation_error(
                    diagnostic, AnimationError::SequenceInvalid,
                    sequence.sequence_id, cue_index);
            }
            for (u32 seen = 0; seen < cue_id_count; ++seen) {
                if (cue_ids[seen] == cue.cue_id) {
                    return detail::set_animation_error(
                        diagnostic, AnimationError::DuplicateId,
                        sequence.sequence_id, cue_index);
                }
            }
            cue_ids[cue_id_count] = cue.cue_id;
            ++cue_id_count;
            if (cue.tick > sequence.duration_ticks
                || cue.duration_ticks
                    > sequence.duration_ticks - cue.tick) {
                return detail::set_animation_error(
                    diagnostic, AnimationError::TimeInvalid,
                    sequence.sequence_id, cue_index);
            }
            ++total_cues;
        }
    }
    plan.track_count = sequence.track_count;
    plan.cue_count = total_cues;
    plan.max_depth = sequence.nesting_depth;
    return AnimationError::None;
}

}  // namespace stormline::animation

#endif  // STORMLINE_ANIMATION_SEQUENCE_PLAN_HPP
