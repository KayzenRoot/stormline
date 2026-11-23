#ifndef STORMLINE_GRAPHICS_VFX_VFX_TYPES_HPP
#define STORMLINE_GRAPHICS_VFX_VFX_TYPES_HPP

#include <array>
#include <cstdint>

namespace stormline::graphics::vfx {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxGraphNodes = 16;
inline constexpr u32 kMaxGraphEdges = 32;
inline constexpr u32 kMaxEmitters = 8;
inline constexpr u32 kMaxRibbonSamples = 16;
inline constexpr u32 kMaxTrailSamples = 16;

enum class VfxError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    GraphCycle,
    GraphTooComplex,
    PortTypeMismatch,
    SpawnBudgetExceeded,
    GeometryInvalid,
    MaterialMismatch,
    DensityInvalid,
    PoolExhausted,
    StaleGeneration,
    BudgetExceeded,
    Unsupported
};

enum class VfxNodeKind : std::uint8_t {
    Emitter,
    Init,
    Force,
    Update,
    Event,
    Render,
    Output
};

enum class VfxPortType : std::uint8_t {
    Flow,
    Scalar,
    Vector,
    Color,
    Material,
    Geometry
};

enum class SimulationPolicy : std::uint8_t {
    CpuReference,
    CpuRender,
    GpuCompute
};

enum class BlendMode : std::uint8_t {
    Opaque,
    Mask,
    Blend,
    Additive
};

enum class DepthPolicy : std::uint8_t {
    TestAndWrite,
    TestOnly,
    Disabled
};

struct VfxDiagnostic {
    VfxError code{VfxError::None};
    u32 source_id{0};
    u32 node_id{0};
    u32 index{0};
};

}  // namespace stormline::graphics::vfx

#endif  // STORMLINE_GRAPHICS_VFX_VFX_TYPES_HPP
