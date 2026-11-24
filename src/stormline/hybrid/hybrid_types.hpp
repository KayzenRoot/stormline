#ifndef STORMLINE_HYBRID_HYBRID_TYPES_HPP
#define STORMLINE_HYBRID_HYBRID_TYPES_HPP

#include <cstdint>

namespace stormline::hybrid {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxHybridLayers = 16;
inline constexpr u32 kMaxHybridObjects = 64;
inline constexpr u32 kMaxHybridEffects = 8;
inline constexpr u32 kMaxSubviewDepth = 4;
inline constexpr u32 kMaxSubviewExtent = 16384;

enum class HybridError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    CameraInvalid,
    LayerInvalid,
    SortInvalid,
    EffectInvalid,
    ViewInvalid,
    DepthExceeded,
    Unsupported
};

enum class ProjectionKind : std::uint8_t { Orthographic, Perspective };

enum class CompositionMode : std::uint8_t {
    SharedDepthWorld,
    OrderedCanvasOverlay,
    IsolatedSubview
};

enum class AlphaPolicy : std::uint8_t { Opaque, Masked, Blended };

enum class ObjectKind : std::uint8_t { Sprite, Mesh, Vfx, Ui };

enum class FallbackReason : std::uint8_t {
    None,
    Unavailable,
    Unsupported,
    BudgetExceeded,
    ProjectionMismatch
};

struct HybridDiagnostic {
    HybridError code{HybridError::None};
    u32 source_id{0};
    u32 index{0};
};

namespace detail {

inline HybridError set_hybrid_error(
    HybridDiagnostic& diagnostic, HybridError code, u32 source_id,
    u32 index) noexcept {
    diagnostic = HybridDiagnostic{code, source_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return value == value && value - value == 0.0f;
}

inline bool valid_projection(ProjectionKind kind) noexcept {
    switch (kind) {
        case ProjectionKind::Orthographic:
        case ProjectionKind::Perspective:
            return true;
    }
    return false;
}

inline bool valid_mode(CompositionMode mode) noexcept {
    switch (mode) {
        case CompositionMode::SharedDepthWorld:
        case CompositionMode::OrderedCanvasOverlay:
        case CompositionMode::IsolatedSubview:
            return true;
    }
    return false;
}

inline bool valid_alpha(AlphaPolicy alpha) noexcept {
    switch (alpha) {
        case AlphaPolicy::Opaque:
        case AlphaPolicy::Masked:
        case AlphaPolicy::Blended:
            return true;
    }
    return false;
}

inline bool valid_object_kind(ObjectKind kind) noexcept {
    switch (kind) {
        case ObjectKind::Sprite:
        case ObjectKind::Mesh:
        case ObjectKind::Vfx:
        case ObjectKind::Ui:
            return true;
    }
    return false;
}

inline bool valid_fallback(FallbackReason reason) noexcept {
    switch (reason) {
        case FallbackReason::None:
        case FallbackReason::Unavailable:
        case FallbackReason::Unsupported:
        case FallbackReason::BudgetExceeded:
        case FallbackReason::ProjectionMismatch:
            return true;
    }
    return false;
}

}  // namespace detail

}  // namespace stormline::hybrid

#endif  // STORMLINE_HYBRID_HYBRID_TYPES_HPP
