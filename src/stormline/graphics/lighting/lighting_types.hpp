#ifndef STORMLINE_GRAPHICS_LIGHTING_LIGHTING_TYPES_HPP
#define STORMLINE_GRAPHICS_LIGHTING_LIGHTING_TYPES_HPP

#include <array>
#include <cstdint>

namespace stormline::graphics::lighting {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxLights = 64;
inline constexpr u32 kMaxCascades = 4;
inline constexpr u32 kMaxShadowPages = 64;
inline constexpr u32 kMaxProbes = 64;
inline constexpr u32 kMaxProbeCells = 65536;
inline constexpr u32 kMaxVolumetrics = 16;
inline constexpr f32 kPi = 3.14159265358979323846f;

enum class LightingError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    InvalidLightKind,
    InvalidUnit,
    InvalidCascade,
    ShadowPageMissing,
    ShadowBudgetExceeded,
    GiUnavailable,
    InvalidProbe,
    HistoryInvalid,
    ReflectionOffscreen,
    VolumetricBudgetExceeded,
    Unsupported
};

enum class LightKind : std::uint8_t {
    Directional,
    Point,
    Spot,
    AreaRect,
    Environment,
    Stylized2D
};

enum class LightUnit : std::uint8_t { Lux, Candela, Luminance };
enum class ShadowMode : std::uint8_t { Disabled, Cascaded, Local };
enum class GiMode : std::uint8_t { Baked, Environment, ProbeFallback, Unsupported };
enum class ReflectionMode : std::uint8_t { ScreenSpace, Probe, Environment, Unsupported };
enum class VolumetricTier : std::uint8_t { Analytic, Froxel };

struct Vec3 {
    f32 x{0.0f};
    f32 y{0.0f};
    f32 z{0.0f};
};

struct LightingDiagnostic {
    LightingError code{LightingError::None};
    u32 light_id{0};
    u32 page_id{0};
    u32 index{0};
};

struct LightDesc {
    u32 id{0};
    u32 revision{0};
    LightKind kind{LightKind::Directional};
    LightUnit unit{LightUnit::Lux};
    Vec3 color{1.0f, 1.0f, 1.0f};
    f32 intensity{0.0f};
    Vec3 position{};
    Vec3 direction{0.0f, -1.0f, 0.0f};
    f32 range{0.0f};
    f32 inner_angle{0.0f};
    f32 outer_angle{0.0f};
    f32 width{0.0f};
    f32 height{0.0f};
    u32 channel_mask{1u};
    ShadowMode shadow{ShadowMode::Disabled};
};

struct LightSet {
    u32 count{0};
    std::array<LightDesc, kMaxLights> lights{};
};

}  // namespace stormline::graphics::lighting

#endif  // STORMLINE_GRAPHICS_LIGHTING_LIGHTING_TYPES_HPP
