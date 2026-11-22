#ifndef STORMLINE_DATA_IMPORT_ANIMATION_METADATA_HPP
#define STORMLINE_DATA_IMPORT_ANIMATION_METADATA_HPP

#include "stormline/data/import/import_types.hpp"

namespace stormline::data::imports {

struct AnimationMetadata {
    u32 joint_count{0};
    u32 track_count{0};
    u32 keyframe_count{0};
    u32 duration_ms{0};
};

[[nodiscard]] inline ImportError validate_animation(
    const AnimationMetadata& metadata, u32& warning_count) noexcept {
    warning_count = 0;
    if (metadata.joint_count == 0 || metadata.joint_count > kMaxAnimationJoints
        || metadata.track_count == 0 || metadata.track_count > kMaxAnimationTracks
        || metadata.keyframe_count == 0
        || metadata.keyframe_count > kMaxAnimationKeyframes
        || metadata.duration_ms == 0
        || metadata.duration_ms > kMaxAnimationDurationMs) {
        return ImportError::InvalidAnimation;
    }
    return ImportError::None;
}

}  // namespace stormline::data::imports

#endif  // STORMLINE_DATA_IMPORT_ANIMATION_METADATA_HPP
