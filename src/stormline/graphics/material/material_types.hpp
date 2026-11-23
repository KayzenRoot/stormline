#ifndef STORMLINE_GRAPHICS_MATERIAL_MATERIAL_TYPES_HPP
#define STORMLINE_GRAPHICS_MATERIAL_MATERIAL_TYPES_HPP

#include <array>
#include <cstdint>

namespace stormline::graphics::material {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using f32 = float;

inline constexpr u32 kMaxMaterials = 64;
inline constexpr u32 kMaxTextures = 64;
inline constexpr u32 kMaxMips = 12;
inline constexpr u32 kMaxDecals = 32;
inline constexpr u32 kMaxTransparentItems = 64;
inline constexpr u32 kMaxPages = 128;

enum class MaterialError : std::uint8_t {
    None,
    InvalidArgument,
    DuplicateId,
    NotFound,
    CapacityFull,
    NonFiniteParameter,
    OutOfRange,
    InvalidMipChain,
    InvalidSampler,
    InvalidAlphaMode,
    DecalConflict,
    TransparencyBudgetExceeded,
    StaleGeneration
};

enum class MaterialModel : std::uint8_t { PbrMetallicRoughness, Unlit, Stylized };
enum class AlphaMode : std::uint8_t { Opaque, Mask, Blend, Transmission };
enum class ColorSpace : std::uint8_t { Srgb, Linear };
enum class TextureUsage : std::uint8_t { BaseColor, Normal, Orm, Emissive, Occlusion, Height };
enum class TextureFormat : std::uint8_t { Rgba8Unorm, Rgba8Srgb, Rgba16Float, Depth32Float };
enum class FilterMode : std::uint8_t { Nearest, Linear };
enum class WrapMode : std::uint8_t { Clamp, Repeat, Mirror };
enum class BlendMode : std::uint8_t { Opaque, AlphaBlend, Premultiplied };

struct MaterialDiagnostic {
    MaterialError code{MaterialError::None};
    u32 material_id{0};
    u32 texture_id{0};
    u32 index{0};
};

struct PbrParameters {
    std::array<f32, 3> base_color{1.0f, 1.0f, 1.0f};
    f32 metallic{0.0f};
    f32 roughness{1.0f};
    f32 occlusion{1.0f};
    std::array<f32, 3> emissive{0.0f, 0.0f, 0.0f};
    f32 normal_scale{1.0f};
    f32 alpha_cutoff{0.5f};
    AlphaMode alpha{AlphaMode::Opaque};
};

struct MaterialDesc {
    u32 id{0};
    u32 revision{0};
    MaterialModel model{MaterialModel::PbrMetallicRoughness};
    PbrParameters parameters{};
    bool double_sided{false};
};

struct MaterialSet {
    u32 count{0};
    std::array<MaterialDesc, kMaxMaterials> materials{};
};

}  // namespace stormline::graphics::material

#endif  // STORMLINE_GRAPHICS_MATERIAL_MATERIAL_TYPES_HPP
