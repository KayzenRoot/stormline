#ifndef STORMLINE_CHARACTER_CHARACTER_TYPES_HPP
#define STORMLINE_CHARACTER_CHARACTER_TYPES_HPP

#include <cstdint>

namespace stormline::character {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i32 = std::int32_t;
using f32 = float;

inline constexpr u32 kMaxControllers = 32;
inline constexpr u32 kMaxLocomotion = 32;
inline constexpr u32 kMaxInputActions = 64;
inline constexpr u32 kMaxCameras = 16;
inline constexpr u32 kMaxTickWindow = 240;

enum class CharacterError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    ControllerInvalid,
    LocomotionInvalid,
    InputInvalid,
    CameraInvalid,
    Incomplete,
    Unsupported
};

enum class ControllerDimension : std::uint8_t { TwoD, ThreeD };
enum class ControllerMode : std::uint8_t { Kinematic, Dynamic };

struct CharacterDiagnostic {
    CharacterError code{CharacterError::None};
    u32 owner_id{0};
    u32 index{0};
};

namespace detail {

inline CharacterError set_character_error(
    CharacterDiagnostic& diagnostic, CharacterError code, u32 owner_id,
    u32 index) noexcept {
    diagnostic = CharacterDiagnostic{code, owner_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return value == value && value - value == 0.0f;
}

inline bool valid_dimension(ControllerDimension dimension) noexcept {
    switch (dimension) {
        case ControllerDimension::TwoD:
        case ControllerDimension::ThreeD:
            return true;
    }
    return false;
}

inline bool valid_mode(ControllerMode mode) noexcept {
    switch (mode) {
        case ControllerMode::Kinematic:
        case ControllerMode::Dynamic:
            return true;
    }
    return false;
}

inline bool unit_axis(f32 x, f32 y, f32 z) noexcept {
    if (!finite(x) || !finite(y) || !finite(z)) {
        return false;
    }
    const f32 length_squared = x * x + y * y + z * z;
    return length_squared >= 0.999f && length_squared <= 1.001f;
}

}  // namespace detail

}  // namespace stormline::character

#endif  // STORMLINE_CHARACTER_CHARACTER_TYPES_HPP
