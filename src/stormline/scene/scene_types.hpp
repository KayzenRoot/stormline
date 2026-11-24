#ifndef STORMLINE_SCENE_SCENE_TYPES_HPP
#define STORMLINE_SCENE_SCENE_TYPES_HPP

#include <cstdint>

namespace stormline::scene {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxSceneNodes = 64;
inline constexpr u32 kMaxSceneDepth = 16;
inline constexpr u32 kMaxPrefabRefs = 16;
inline constexpr u32 kMaxPrefabDepth = 4;
inline constexpr u32 kMaxVariantOverrides = 32;
inline constexpr u32 kMaxSceneInstances = 16;
inline constexpr u32 kMaxInstanceExpansion = 4096;

enum class SceneError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    HierarchyInvalid,
    PrefabInvalid,
    VariantInvalid,
    InstanceInvalid,
    TransformInvalid,
    DepthExceeded,
    Unsupported
};

enum class ReparentMode : std::uint8_t { KeepLocal, KeepWorld };

struct SceneDiagnostic {
    SceneError code{SceneError::None};
    u32 source_id{0};
    u32 index{0};
};

namespace detail {

inline SceneError set_scene_error(
    SceneDiagnostic& diagnostic, SceneError code, u32 source_id,
    u32 index) noexcept {
    diagnostic = SceneDiagnostic{code, source_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return value == value && value - value == 0.0f;
}

inline bool valid_reparent_mode(ReparentMode mode) noexcept {
    switch (mode) {
        case ReparentMode::KeepLocal:
        case ReparentMode::KeepWorld:
            return true;
    }
    return false;
}

}  // namespace detail

}  // namespace stormline::scene

#endif  // STORMLINE_SCENE_SCENE_TYPES_HPP
