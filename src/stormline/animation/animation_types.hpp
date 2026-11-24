#ifndef STORMLINE_ANIMATION_ANIMATION_TYPES_HPP
#define STORMLINE_ANIMATION_ANIMATION_TYPES_HPP

#include <array>
#include <cstdint>

namespace stormline::animation {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f32 = float;

inline constexpr u32 kMaxFlipbookFrames = 64;
inline constexpr u32 kMaxBones = 32;
inline constexpr u32 kMaxBlendClips = 4;
inline constexpr u32 kMaxSequenceTracks = 16;
inline constexpr u32 kMaxSequenceCues = 16;
inline constexpr u32 kMaxSequenceDepth = 4;

enum class AnimationError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    TimeInvalid,
    FlipbookInvalid,
    SkeletonInvalid,
    BlendInvalid,
    SequenceInvalid,
    DepthExceeded,
    EventInvalid,
    Unsupported
};

enum class TrackKind : std::uint8_t {
    Sprite,
    Bone,
    Camera,
    Audio,
    Vfx,
    GameplayEvent
};

struct AnimationDiagnostic {
    AnimationError code{AnimationError::None};
    u32 source_id{0};
    u32 index{0};
};

namespace detail {

inline AnimationError set_animation_error(
    AnimationDiagnostic& diagnostic, AnimationError code, u32 source_id,
    u32 index) noexcept {
    diagnostic = AnimationDiagnostic{code, source_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return value == value && value - value == 0.0f;
}

inline bool valid_track_kind(TrackKind kind) noexcept {
    switch (kind) {
        case TrackKind::Sprite:
        case TrackKind::Bone:
        case TrackKind::Camera:
        case TrackKind::Audio:
        case TrackKind::Vfx:
        case TrackKind::GameplayEvent:
            return true;
    }
    return false;
}

}  // namespace detail

}  // namespace stormline::animation

#endif  // STORMLINE_ANIMATION_ANIMATION_TYPES_HPP
