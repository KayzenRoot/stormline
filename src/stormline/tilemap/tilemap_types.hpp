#ifndef STORMLINE_TILEMAP_TILEMAP_TYPES_HPP
#define STORMLINE_TILEMAP_TILEMAP_TYPES_HPP

#include <array>
#include <cstdint>

namespace stormline::tilemap {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f32 = float;

inline constexpr u32 kMaxCollisionShapes = 8;
inline constexpr u32 kMaxStreamingChunks = 256;

enum class TilemapError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    CoordinateOutOfBounds,
    GridInvalid,
    TileInvalid,
    CollisionInvalid,
    ParallaxInvalid,
    StreamingInvalid,
    BudgetExceeded,
    StaleRevision,
    Unsupported
};

enum class TileOrientation : std::uint8_t {
    Orthogonal,
    Isometric,
    Staggered,
    HexAxial
};

enum class TileTransform : std::uint8_t {
    None,
    FlipX,
    FlipY,
    Rotate90,
    Rotate180,
    Rotate270
};

enum class CollisionShapeKind : std::uint8_t { Rect, Segment };

enum class ChunkState : std::uint8_t {
    Unloaded,
    Requested,
    Fetching,
    Cancelled,
    Failed,
    Ready
};

struct TilemapDiagnostic {
    TilemapError code{TilemapError::None};
    u32 source_id{0};
    u32 index{0};
};

namespace detail {

inline TilemapError set_tilemap_error(
    TilemapDiagnostic& diagnostic, TilemapError code, u32 source_id,
    u32 index) noexcept {
    diagnostic = TilemapDiagnostic{code, source_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return value == value && value - value == 0.0f;
}

inline bool valid_orientation(TileOrientation orientation) noexcept {
    switch (orientation) {
        case TileOrientation::Orthogonal:
        case TileOrientation::Isometric:
        case TileOrientation::Staggered:
        case TileOrientation::HexAxial:
            return true;
    }
    return false;
}

inline bool valid_transform(TileTransform transform) noexcept {
    switch (transform) {
        case TileTransform::None:
        case TileTransform::FlipX:
        case TileTransform::FlipY:
        case TileTransform::Rotate90:
        case TileTransform::Rotate180:
        case TileTransform::Rotate270:
            return true;
    }
    return false;
}

inline bool valid_shape_kind(CollisionShapeKind kind) noexcept {
    switch (kind) {
        case CollisionShapeKind::Rect:
        case CollisionShapeKind::Segment:
            return true;
    }
    return false;
}

}  // namespace detail

}  // namespace stormline::tilemap

#endif  // STORMLINE_TILEMAP_TILEMAP_TYPES_HPP
