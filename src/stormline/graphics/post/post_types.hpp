#ifndef STORMLINE_GRAPHICS_POST_POST_TYPES_HPP
#define STORMLINE_GRAPHICS_POST_POST_TYPES_HPP

#include <array>
#include <cstdint>

namespace stormline::graphics::post {

using u8 = std::uint8_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using f32 = float;

inline constexpr u32 kMaxCameras = 8;
inline constexpr f32 kPi = 3.14159265358979323846f;

enum class PostError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteValue,
    OutOfRange,
    InvalidProjection,
    InvalidCamera,
    ColorSpaceMismatch,
    DoubleTransferGuard,
    HdrUnavailable,
    HistoryInvalid,
    TemporalUnsupported,
    BudgetExceeded,
    Unsupported
};

enum class ProjectionKind : std::uint8_t { Perspective, Orthographic };
enum class ColorTransfer : std::uint8_t { Linear, Srgb };
enum class ToneCurve : std::uint8_t { None, Neutral, Filmic };
enum class OutputMode : std::uint8_t { SdrSrgb, Hdr10Pq };
enum class ReconstructionStrategy : std::uint8_t {
    Native,
    Spatial,
    Taa,
    VendorUpscale
};

struct Vec2 {
    f32 x{0.0f};
    f32 y{0.0f};
};

struct PostDiagnostic {
    PostError code{PostError::None};
    u32 camera_id{0};
    u32 index{0};
};

struct CameraViewDesc {
    u32 camera_id{0};
    u32 revision{0};
    ProjectionKind projection{ProjectionKind::Perspective};
    f32 vertical_fov_radians{0.0f};
    f32 aspect{1.0f};
    f32 ortho_height{0.0f};
    f32 near_distance{0.0f};
    f32 far_distance{0.0f};
    u32 render_width{0};
    u32 render_height{0};
    u32 output_width{0};
    u32 output_height{0};
    Vec2 jitter{};
    Vec2 previous_jitter{};
    bool jitter_world_only{true};
    u64 scene_generation{0};
};

struct CameraSet {
    u32 count{0};
    std::array<CameraViewDesc, kMaxCameras> cameras{};
};

}  // namespace stormline::graphics::post

#endif  // STORMLINE_GRAPHICS_POST_POST_TYPES_HPP
