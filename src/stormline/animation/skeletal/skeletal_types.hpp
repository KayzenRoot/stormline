#ifndef STORMLINE_ANIMATION_SKELETAL_SKELETAL_TYPES_HPP
#define STORMLINE_ANIMATION_SKELETAL_SKELETAL_TYPES_HPP

#include <cstdint>

namespace stormline::animation::skeletal {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i32 = std::int32_t;
using f32 = float;

inline constexpr u32 kMaxRetargetProfiles = 16;
inline constexpr u32 kMaxRetargetPairs = 64;
inline constexpr u32 kMaxBlendNodes = 64;
inline constexpr u32 kMaxIkChains = 32;
inline constexpr u32 kMaxIkIterations = 64;
inline constexpr u32 kMaxRagdollProfiles = 16;
inline constexpr u32 kMaxCompressionProfiles = 16;
inline constexpr u32 kMaxSyncGroups = 32;
inline constexpr u32 kMaxTickWindow = 240;

enum class SkeletalError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    RetargetInvalid,
    BlendInvalid,
    IkInvalid,
    RagdollInvalid,
    CompressionInvalid,
    SyncInvalid,
    Incomplete,
    Unsupported
};

enum class BlendKind : std::uint8_t { Lerp, Additive, Mask, Blend1D, Blend2D };

struct SkeletalDiagnostic {
    SkeletalError code{SkeletalError::None};
    u32 owner_id{0};
    u32 index{0};
};

namespace detail {

inline SkeletalError set_skeletal_error(
    SkeletalDiagnostic& diagnostic, SkeletalError code, u32 owner_id,
    u32 index) noexcept {
    diagnostic = SkeletalDiagnostic{code, owner_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return value == value && value - value == 0.0f;
}

inline bool unit_scalar_in(f32 value, f32 minimum, f32 maximum) noexcept {
    return finite(value) && value >= minimum && value <= maximum;
}

inline bool valid_blend_kind(BlendKind kind) noexcept {
    switch (kind) {
        case BlendKind::Lerp:
        case BlendKind::Additive:
        case BlendKind::Mask:
        case BlendKind::Blend1D:
        case BlendKind::Blend2D:
            return true;
    }
    return false;
}

}  // namespace detail

}  // namespace stormline::animation::skeletal

#endif  // STORMLINE_ANIMATION_SKELETAL_SKELETAL_TYPES_HPP
