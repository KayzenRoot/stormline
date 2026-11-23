#ifndef STORMLINE_GRAPHICS_CANVAS2D_CANVAS_TYPES_HPP
#define STORMLINE_GRAPHICS_CANVAS2D_CANVAS_TYPES_HPP

#include <array>
#include <cstdint>

namespace stormline::graphics::canvas2d {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxLayers = 16;
inline constexpr u32 kMaxAtlasRegions = 64;
inline constexpr u32 kMaxLights = 8;

enum class CanvasError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    SpriteInvalid,
    AtlasInvalid,
    LayerOrderInvalid,
    CameraInvalid,
    SnapInvalid,
    LightBudgetExceeded,
    MaterialMismatch,
    Unsupported
};

enum class BlendMode : std::uint8_t { Opaque, Mask, Blend, Additive };
enum class FilterMode : std::uint8_t { Nearest, Linear };
enum class SnapMode : std::uint8_t { None, Integer };
enum class FalloffKind : std::uint8_t { Constant, Linear, Radial };

struct CanvasDiagnostic {
    CanvasError code{CanvasError::None};
    u32 source_id{0};
    u32 index{0};
};

namespace detail {

inline CanvasError set_canvas_error(
    CanvasDiagnostic& diagnostic, CanvasError code, u32 source_id,
    u32 index) noexcept {
    diagnostic = CanvasDiagnostic{code, source_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return value == value && value - value == 0.0f;
}

inline bool valid_blend(BlendMode blend) noexcept {
    switch (blend) {
        case BlendMode::Opaque:
        case BlendMode::Mask:
        case BlendMode::Blend:
        case BlendMode::Additive:
            return true;
    }
    return false;
}

inline bool valid_filter(FilterMode filter) noexcept {
    switch (filter) {
        case FilterMode::Nearest:
        case FilterMode::Linear:
            return true;
    }
    return false;
}

inline bool valid_snap_mode(SnapMode mode) noexcept {
    switch (mode) {
        case SnapMode::None:
        case SnapMode::Integer:
            return true;
    }
    return false;
}

inline bool valid_falloff(FalloffKind falloff) noexcept {
    switch (falloff) {
        case FalloffKind::Constant:
        case FalloffKind::Linear:
        case FalloffKind::Radial:
            return true;
    }
    return false;
}

}  // namespace detail

}  // namespace stormline::graphics::canvas2d

#endif  // STORMLINE_GRAPHICS_CANVAS2D_CANVAS_TYPES_HPP
