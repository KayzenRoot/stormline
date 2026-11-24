#ifndef STORMLINE_SPATIAL_SPATIAL_TYPES_HPP
#define STORMLINE_SPATIAL_SPATIAL_TYPES_HPP

#include <cstdint>

namespace stormline::spatial {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f32 = float;

inline constexpr u32 kMaxSpatialCells = 64;
inline constexpr u32 kMaxInterestSources = 16;
inline constexpr u32 kMaxStreamingCells = 64;
inline constexpr u64 kMaxCellBytes = 1024ull * 1024ull * 1024ull;

enum class SpatialError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    CellInvalid,
    InterestInvalid,
    OriginInvalid,
    StreamInvalid,
    Incomplete,
    Unsupported
};

enum class InterestRole : std::uint8_t {
    Player, Camera, Ai, Quest, Net, Audio, Editor
};

enum class CellPriority : std::uint8_t {
    Pinned, Prefetch, Optional, Evict
};

struct SpatialDiagnostic {
    SpatialError code{SpatialError::None};
    u32 source_id{0};
    u32 index{0};
};

namespace detail {

inline SpatialError set_spatial_error(
    SpatialDiagnostic& diagnostic, SpatialError code, u32 source_id,
    u32 index) noexcept {
    diagnostic = SpatialDiagnostic{code, source_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return value == value && value - value == 0.0f;
}

inline bool valid_interest_role(InterestRole role) noexcept {
    switch (role) {
        case InterestRole::Player:
        case InterestRole::Camera:
        case InterestRole::Ai:
        case InterestRole::Quest:
        case InterestRole::Net:
        case InterestRole::Audio:
        case InterestRole::Editor:
            return true;
    }
    return false;
}

inline bool valid_cell_priority(CellPriority priority) noexcept {
    switch (priority) {
        case CellPriority::Pinned:
        case CellPriority::Prefetch:
        case CellPriority::Optional:
        case CellPriority::Evict:
            return true;
    }
    return false;
}

inline bool checked_add_u64(u64& total, u64 value) noexcept {
    if (value > ~u64{0} - total) {
        return false;
    }
    total += value;
    return true;
}

}  // namespace detail

}  // namespace stormline::spatial

#endif  // STORMLINE_SPATIAL_SPATIAL_TYPES_HPP
