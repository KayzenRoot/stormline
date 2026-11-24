#ifndef STORMLINE_PHYSICS2D_PHYSICS2D_TYPES_HPP
#define STORMLINE_PHYSICS2D_PHYSICS2D_TYPES_HPP

#include <cstdint>

namespace stormline::physics2d {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i32 = std::int32_t;
using f32 = float;

inline constexpr u32 kMaxBodies = 64;
inline constexpr u32 kMaxShapes = 128;
inline constexpr u32 kMaxQueries = 32;
inline constexpr u32 kMaxJoints = 64;
inline constexpr u32 kMaxTriggers = 64;
inline constexpr u32 kMaxMasks = 32;
inline constexpr u32 kMaxQueryResults = 1024;
inline constexpr u32 kMaxTotalQueryResults = 8192;

enum class Physics2DError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    BodyInvalid,
    ShapeInvalid,
    QueryInvalid,
    JointInvalid,
    TriggerInvalid,
    MaskInvalid,
    Incomplete,
    Unsupported
};

enum class BodyKind : std::uint8_t { Static, Kinematic, Dynamic };
enum class ShapeKind : std::uint8_t { Circle, Box, Capsule, Polygon };
enum class QueryKind : std::uint8_t { Ray, Overlap, ShapeCast };
enum class JointKind : std::uint8_t { Distance, Revolute, Prismatic, Weld };

struct Physics2DDiagnostic {
    Physics2DError code{Physics2DError::None};
    u32 world_id{0};
    u32 index{0};
};

namespace detail {

inline Physics2DError set_physics2d_error(
    Physics2DDiagnostic& diagnostic, Physics2DError code, u32 world_id,
    u32 index) noexcept {
    diagnostic = Physics2DDiagnostic{code, world_id, index};
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
        case ShapeKind::Circle:
        case ShapeKind::Box:
        case ShapeKind::Capsule:
        case ShapeKind::Polygon:
            return true;
    }
    return false;
}

inline bool valid_query_kind(QueryKind kind) noexcept {
    switch (kind) {
        case QueryKind::Ray:
        case QueryKind::Overlap:
        case QueryKind::ShapeCast:
            return true;
    }
    return false;
}

inline bool valid_joint_kind(JointKind kind) noexcept {
    switch (kind) {
        case JointKind::Distance:
        case JointKind::Revolute:
        case JointKind::Prismatic:
        case JointKind::Weld:
            return true;
    }
    return false;
}

inline bool checked_add_u32(u32& total, u32 value) noexcept {
    if (value > ~u32{0} - total) {
        return false;
    }
    total += value;
    return true;
}

}  // namespace detail

}  // namespace stormline::physics2d

#endif  // STORMLINE_PHYSICS2D_PHYSICS2D_TYPES_HPP
