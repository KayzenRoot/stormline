#ifndef STORMLINE_TERRAIN_TERRAIN_TYPES_HPP
#define STORMLINE_TERRAIN_TERRAIN_TYPES_HPP

#include <cstdint>

namespace stormline::terrain {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f32 = float;

inline constexpr u32 kMaxTerrainPatches = 64;
inline constexpr u32 kMaxPatchNeighbors = 8;
inline constexpr u32 kMaxTerrainLod = 8;
inline constexpr u32 kMaxSplatLayers = 16;
inline constexpr u32 kMaxVegetationGroups = 32;
inline constexpr u32 kMaxVegetationInstances = 4096;
inline constexpr u32 kMaxWaterBodies = 32;
inline constexpr u32 kMaxSkyProfiles = 16;
inline constexpr u32 kMaxWeatherZones = 32;

enum class TerrainError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    PatchInvalid,
    SplatInvalid,
    VegetationInvalid,
    WaterInvalid,
    SkyInvalid,
    WeatherInvalid,
    Incomplete,
    Unsupported
};

enum class PatchTopology : std::uint8_t { Heightfield, MeshSurface };
enum class WaterClass : std::uint8_t { Ocean, Lake, River, Local };
enum class QualityTier : std::uint8_t { Low, Medium, High, Ultra };

struct TerrainDiagnostic {
    TerrainError code{TerrainError::None};
    u32 asset_id{0};
    u32 index{0};
};

namespace detail {

inline TerrainError set_terrain_error(
    TerrainDiagnostic& diagnostic, TerrainError code, u32 asset_id,
    u32 index) noexcept {
    diagnostic = TerrainDiagnostic{code, asset_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return value == value && value - value == 0.0f;
}

inline bool valid_patch_topology(PatchTopology topology) noexcept {
    switch (topology) {
        case PatchTopology::Heightfield:
        case PatchTopology::MeshSurface:
            return true;
    }
    return false;
}

inline bool valid_water_class(WaterClass water_class) noexcept {
    switch (water_class) {
        case WaterClass::Ocean:
        case WaterClass::Lake:
        case WaterClass::River:
        case WaterClass::Local:
            return true;
    }
    return false;
}

inline bool valid_quality_tier(QualityTier tier) noexcept {
    switch (tier) {
        case QualityTier::Low:
        case QualityTier::Medium:
        case QualityTier::High:
        case QualityTier::Ultra:
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

}  // namespace stormline::terrain

#endif  // STORMLINE_TERRAIN_TERRAIN_TYPES_HPP
