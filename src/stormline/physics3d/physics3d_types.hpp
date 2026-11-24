#ifndef STORMLINE_PHYSICS3D_PHYSICS3D_TYPES_HPP
#define STORMLINE_PHYSICS3D_PHYSICS3D_TYPES_HPP

#include <cstdint>

namespace stormline::physics3d {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i32 = std::int32_t;
using f32 = float;

inline constexpr u32 kMaxBodies = 64;
inline constexpr u32 kMaxShapes = 128;
inline constexpr u32 kMaxLayers = 32;
inline constexpr u32 kMaxQueries = 32;
inline constexpr u32 kMaxConstraints = 64;
inline constexpr u32 kMaxIntegrations = 64;
inline constexpr u32 kMaxQueryResults = 1024;
inline constexpr u32 kMaxTotalQueryResults = 8192;

enum class Physics3DError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    BodyInvalid,
    ShapeInvalid,
    LayerInvalid,
    QueryInvalid,
    ConstraintInvalid,
    IntegrationInvalid,
    Incomplete,
    Unsupported
};

enum class BodyKind : std::uint8_t { Static, Kinematic, Dynamic };
enum class ShapeKind : std::uint8_t {
    Sphere,
    Box,
    Capsule,
    Convex,
    Compound,
    Mesh,
    Heightfield
};
enum class QueryKind : std::uint8_t { Ray, Overlap, Sweep, ShapeCast };
enum class ConstraintKind : std::uint8_t {
    Fixed,
    Distance,
    Hinge,
    Slider,
    ConeTwist,
    SixDof
};
enum class IntegrationKind : std::uint8_t {
    Scene,
    Streaming,
    Authority,
    Tick
};

struct Physics3DDiagnostic {
    Physics3DError code{Physics3DError::None};
    u32 world_id{0};
    u32 index{0};
};

namespace detail {

inline Physics3DError set_physics3d_error(
    Physics3DDiagnostic& diagnostic, Physics3DError code, u32 world_id,
    u32 index) noexcept {
    diagnostic = Physics3DDiagnostic{code, world_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return value == value && value - value == 0.0f;
}

inline bool valid_body_kind(BodyKind kind) noexcept {
    switch (kind) {
        case BodyKind::Static:
        case BodyKind::Kinematic:
        case BodyKind::Dynamic:
            return true;
    }
    return false;
}

inline bool valid_shape_kind(ShapeKind kind) noexcept {
    switch (kind) {
        case ShapeKind::Sphere:
        case ShapeKind::Box:
        case ShapeKind::Capsule:
        case ShapeKind::Convex:
        case ShapeKind::Compound:
        case ShapeKind::Mesh:
        case ShapeKind::Heightfield:
            return true;
    }
    return false;
}

inline bool valid_query_kind(QueryKind kind) noexcept {
    switch (kind) {
        case QueryKind::Ray:
        case QueryKind::Overlap:
        case QueryKind::Sweep:
        case QueryKind::ShapeCast:
            return true;
    }
    return false;
}

inline bool valid_constraint_kind(ConstraintKind kind) noexcept {
    switch (kind) {
        case ConstraintKind::Fixed:
        case ConstraintKind::Distance:
        case ConstraintKind::Hinge:
        case ConstraintKind::Slider:
        case ConstraintKind::ConeTwist:
        case ConstraintKind::SixDof:
            return true;
    }
    return false;
}

inline bool valid_integration_kind(IntegrationKind kind) noexcept {
    switch (kind) {
        case IntegrationKind::Scene:
        case IntegrationKind::Streaming:
        case IntegrationKind::Authority:
        case IntegrationKind::Tick:
            return true;
    }
    return false;
}

inline bool unit_quaternion(f32 x, f32 y, f32 z, f32 w) noexcept {
    if (!finite(x) || !finite(y) || !finite(z) || !finite(w)) {
        return false;
    }
    const f32 length_squared = x * x + y * y + z * z + w * w;
    return length_squared >= 0.999f && length_squared <= 1.001f;
}

inline bool unit_axis(f32 x, f32 y, f32 z) noexcept {
    if (!finite(x) || !finite(y) || !finite(z)) {
        return false;
    }
    const f32 length_squared = x * x + y * y + z * z;
    return length_squared >= 0.999f && length_squared <= 1.001f;
}

inline bool nonzero_direction(f32 x, f32 y, f32 z) noexcept {
    if (!finite(x) || !finite(y) || !finite(z)) {
        return false;
    }
    return x * x + y * y + z * z > 0.0f;
}

inline bool checked_add_u32(u32& total, u32 value) noexcept {
    if (value > ~u32{0} - total) {
        return false;
    }
    total += value;
    return true;
}

}  // namespace detail

}  // namespace stormline::physics3d

#endif  // STORMLINE_PHYSICS3D_PHYSICS3D_TYPES_HPP
