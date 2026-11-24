#ifndef STORMLINE_PROCEDURAL_PROCEDURAL_TYPES_HPP
#define STORMLINE_PROCEDURAL_PROCEDURAL_TYPES_HPP

#include <cstdint>

namespace stormline::procedural {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i64 = std::int64_t;
using f32 = float;

inline constexpr u32 kMaxSeedDomains = 16;
inline constexpr u32 kMaxGraphNodes = 64;
inline constexpr u32 kMaxGraphEdges = 128;
inline constexpr u32 kMaxGraphDepth = 16;
inline constexpr u32 kMaxNodeFanOut = 8;
inline constexpr u32 kMaxRules = 32;
inline constexpr u32 kMaxBiomeZones = 16;
inline constexpr u32 kMaxGeometryRecipes = 32;
inline constexpr u32 kMaxContentGenerators = 32;
inline constexpr u32 kMaxGeneratorOutputCap = 4096;
inline constexpr u32 kMaxTotalOutputCap = 65536;

enum class ProcError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    SeedInvalid,
    GraphInvalid,
    RuleInvalid,
    BiomeInvalid,
    GeometryInvalid,
    GeneratorInvalid,
    CycleDetected,
    Incomplete,
    Unsupported
};

enum class PrimitiveKind : std::uint8_t { Box, Plane, Sphere, Heightfield };
enum class GeneratorCategory : std::uint8_t { Biome, Geometry, Placement, Rule };

struct ProcDiagnostic {
    ProcError code{ProcError::None};
    u32 source_id{0};
    u32 index{0};
};

namespace detail {

inline ProcError set_proc_error(
    ProcDiagnostic& diagnostic, ProcError code, u32 source_id,
    u32 index) noexcept {
    diagnostic = ProcDiagnostic{code, source_id, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return value == value && value - value == 0.0f;
}

inline bool valid_primitive(PrimitiveKind primitive) noexcept {
    switch (primitive) {
        case PrimitiveKind::Box:
        case PrimitiveKind::Plane:
        case PrimitiveKind::Sphere:
        case PrimitiveKind::Heightfield:
            return true;
    }
    return false;
}

inline bool valid_generator_category(GeneratorCategory category) noexcept {
    switch (category) {
        case GeneratorCategory::Biome:
        case GeneratorCategory::Geometry:
        case GeneratorCategory::Placement:
        case GeneratorCategory::Rule:
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

}  // namespace stormline::procedural

#endif  // STORMLINE_PROCEDURAL_PROCEDURAL_TYPES_HPP
