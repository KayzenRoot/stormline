# GFX-05 INTERNAL_ONLY Logical Material/Texture Contract v0 (NLE-PRPLAN-GFX-05-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `11d658e`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **WO:** [NLE-PRPLAN-GFX-05-02](../work-orders/NLE-PRPLAN-GFX-05-02.md).

## Objective

Freeze the first bounded GFX-05 logical API: PBR parameter validation, texture/mip metadata, optional virtual-page requests, sampler profiles, decal ordering and transparency sort/overdraw budgets. No native GPU, codec/decoder, shader compiler, allocator, dependency, ABI or release.

## Admission and boundaries

- Formal dependencies are `GFX-02` and `DATA-03`; neither is module-qualified.
- GFX-05 owns logical material/texture semantics.
- GFX-02 shaders; DATA-01/02/03/04/05 assets/import/cook; GFX-01 RHI; GFX-03 upload/residency; GFX-04 visibility; GFX-06 lighting; GFX-07 tone mapping.
- No Vulkan/D3D12/Metal/WebGPU, KTX2/Basis, image codec, GPU allocator or renderer is selected.

## Policy invariants

- **No native GPU or codec.** Metadata only; no image decode/encode, upload, BRDF evaluation or rendering.
- **Bounded and finite.** Fixed capacities; NaN/Inf and out-of-range values rejected.
- **Fail closed.** Duplicate/unknown IDs, invalid mips/samplers/alpha states, decal conflicts and budgets are typed errors.
- **Deterministic.** Stable integer sort keys and IDs determine output.
- **No residency or performance claim.** Virtual-page requests are logical proposals only.
- **No artifact claim.** Parameters and texture metadata are not pixels, a cooked image or a GPU resource.

## Internal API (logical, exact names)

```cpp
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

[[nodiscard]] const char* material_error_name(MaterialError error) noexcept;
[[nodiscard]] MaterialError add_material(
    MaterialSet& set, const MaterialDesc& material) noexcept;
[[nodiscard]] MaterialError validate_materials(
    const MaterialSet& set, MaterialDiagnostic& diagnostic) noexcept;

struct TextureDesc {
    u32 id{0};
    u32 width{0};
    u32 height{0};
    u16 levels{0};
    TextureFormat format{TextureFormat::Rgba8Unorm};
    ColorSpace color_space{ColorSpace::Linear};
    TextureUsage usage{TextureUsage::BaseColor};
};
struct TextureSet {
    u32 count{0};
    std::array<TextureDesc, kMaxTextures> textures{};
};
[[nodiscard]] MaterialError add_texture(
    TextureSet& set, const TextureDesc& texture) noexcept;
[[nodiscard]] MaterialError validate_textures(
    const TextureSet& set, MaterialDiagnostic& diagnostic) noexcept;

struct VirtualTexture {
    u32 texture_id{0};
    u32 page_size{0};
    u32 page_count{0};
};
struct ResidentPages {
    u32 count{0};
    std::array<u32, kMaxPages> page_ids{};
};
struct RequestedPages {
    u32 count{0};
    std::array<u32, kMaxPages> page_ids{};
};
struct PagePlan {
    u32 count{0};
    std::array<u32, kMaxPages> page_ids{};
    u32 pages_bytes{0};
    bool truncated{false};
};
[[nodiscard]] MaterialError plan_pages(
    const VirtualTexture& texture, const RequestedPages& requested,
    const ResidentPages& resident, u32 budget_pages,
    PagePlan& plan, MaterialDiagnostic& diagnostic) noexcept;

struct MipLevel {
    u32 width{0};
    u32 height{0};
    u32 bytes{0};
};
struct MipChain {
    u32 texture_id{0};
    u32 count{0};
    std::array<MipLevel, kMaxMips> levels{};
};
[[nodiscard]] MaterialError build_mip_chain(
    const TextureDesc& texture, MipChain& chain,
    MaterialDiagnostic& diagnostic) noexcept;

struct SamplerProfile {
    TextureFormat format{TextureFormat::Rgba8Unorm};
    FilterMode min_filter{FilterMode::Linear};
    FilterMode mag_filter{FilterMode::Linear};
    FilterMode mip_filter{FilterMode::Linear};
    WrapMode wrap_u{WrapMode::Repeat};
    WrapMode wrap_v{WrapMode::Repeat};
    f32 lod_bias{0.0f};
    f32 lod_min{0.0f};
    f32 lod_max{12.0f};
    u32 max_anisotropy{1};
    bool compare{false};
};
[[nodiscard]] MaterialError validate_sampler(
    const SamplerProfile& sampler, MaterialDiagnostic& diagnostic) noexcept;

struct DecalDesc {
    u32 id{0};
    u32 layer{0};
    f32 x{0.0f};
    f32 y{0.0f};
    f32 z{0.0f};
    f32 radius{0.0f};
    f32 opacity{1.0f};
    bool normal_blend{false};
};
struct DecalSet {
    u32 count{0};
    std::array<DecalDesc, kMaxDecals> decals{};
};
struct DecalPlan {
    u32 count{0};
    std::array<u32, kMaxDecals> decal_ids{};
};
[[nodiscard]] MaterialError plan_decals(
    const DecalSet& set, DecalPlan& plan,
    MaterialDiagnostic& diagnostic) noexcept;

struct TransparentItem {
    u32 id{0};
    f32 depth{0.0f};
    AlphaMode alpha{AlphaMode::Blend};
    BlendMode blend{BlendMode::AlphaBlend};
    bool depth_write{false};
};
struct TransparentSet {
    u32 count{0};
    std::array<TransparentItem, kMaxTransparentItems> items{};
};
struct TransparencyPlan {
    u32 count{0};
    std::array<u32, kMaxTransparentItems> item_ids{};
    u32 overdraw_count{0};
};
[[nodiscard]] MaterialError plan_transparency(
    const TransparentSet& set, u32 max_items,
    TransparencyPlan& plan, MaterialDiagnostic& diagnostic) noexcept;

}  // namespace stormline::graphics::material
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `GFX-05-03`.

## Semantics

- **Materials:** `id` and `revision` nonzero; IDs unique in `MaterialSet`; finite `base_color`, `emissive`, `metallic`, `roughness`, `occlusion`, `normal_scale` and `alpha_cutoff`. `base_color`/`emissive` components and scalar PBR values are in `[0,1]`; `normal_scale` is `>0`; `alpha_cutoff` is in `[0,1]`. `Mask` requires cutoff `>0`; `Opaque`/`Blend`/`Transmission` do not require a cutoff. Model and alpha enums must be declared values. `add_material` fails atomically on capacity/duplicate; validation reports the first offending index.
- **Textures:** `id` nonzero/unique; `width`/`height` in `[1,16384]`; `levels` in `[1,12]` and equal to `floor(log2(max(width,height)))+1`, capped only by `kMaxMips`; format/usage/color-space declared. `BaseColor` must be `Srgb`; `Normal`/`Orm`/`Height` must be `Linear`; `Emissive` accepts `Srgb` or `Linear`; `Occlusion` must be `Linear`. Depth32Float is valid only for non-color metadata. No pixels are read.
- **Virtual pages:** `page_size` and `page_count` nonzero; `page_count * page_size` fits `u32`; page IDs are `1..page_count`; requested/resident IDs are unique and in range. Resident requests are skipped; remaining requests retain ascending request order. `budget_pages` bounds admitted requests; an over-budget or over-capacity result sets `truncated=true` and returns the admitted prefix, not a partial page. `pages_bytes` is `admitted * page_size` with checked arithmetic. No residency is claimed.
- **Mips:** chain is derived only from `TextureDesc`; format byte size is `Rgba8Unorm`/`Rgba8Srgb`/`Depth32Float` = 4 and `Rgba16Float` = 8. Each level dimension is `max(1, dimension >> level)`; byte size is checked `width * height * bytes_per_pixel`; levels beyond `kMaxMips` fail `InvalidMipChain`. No image or mip pixels are generated.
- **Samplers:** filter/wrap enums declared; `lod_bias`, `lod_min`, `lod_max` finite and in `[-16,16]`; `lod_min <= lod_max`; `max_anisotropy` is a power of two in `[1,16]`; `compare=true` requires `Depth32Float`. Sampler validation does not inspect a texture.
- **Decals:** IDs nonzero/unique; `layer < 32`; position/radius finite; `radius > 0`; opacity in `[0,1]`. Plan is sorted by `(layer, id)` ascending; capacity overflow returns `CapacityFull` without a partial plan; repeated IDs return `DecalConflict`.
- **Transparency:** each item `id` nonzero/unique; `depth` finite; alpha must be `Blend` or `Transmission`; `depth_write` must be `false`; `blend` must be `AlphaBlend` or `Premultiplied` for blend alpha and `AlphaBlend` for transmission. Plan is sorted by depth descending, then id ascending (back-to-front). `max_items` nonzero and at most `kMaxTransparentItems`; exceeding it returns `TransparencyBudgetExceeded`. `overdraw_count` is the number of admitted items after the first, saturating at `u32` max. No blending or rendering occurs.
- **Common:** all functions are `noexcept`; no allocation, exception, file, network, GPU, codec, thread or global state. On error, outputs are zero-initialized or empty; inputs are never modified.

## Test oracles (future GFX-05-03..-09)

| ID | Scenario | Oracle |
|---|---|---|
| PBR-01 | material parameters | add/duplicate/capacity, finite/range/model/alpha/cutoff, atomic failure |
| VTX-01 | texture metadata and pages | add/duplicate/dimensions/levels/format/color use, resident skip, budget, truncation, invalid IDs |
| MIP-01 | mip metadata | derived dimensions/bytes per format, max levels, invalid levels/overflow |
| SMP-01 | sampler profiles | filter/wrap/LOD range/order/anisotropy/compare |
| DEC-01 | decals | duplicate/capacity/layer/radius/opacity, deterministic `(layer,id)` order |
| TRN-01 | transparency | alpha/blend/depth-write, back-to-front order, budget/overdraw, bounded capacity |
| QLF-G501 | integrated | materials->textures->mips->samplers->pages->decals->transparency |
| QLF-G502 | deterministic repeat | identical integrated plans/bytes/orders |
| QLF-G503 | failure recovery | typed error followed by valid operation |
| QLF-G504 | bounded overload | 10,000 attempts keep capacities and reject non-finite input |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/graphics/material/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp`.

### `GFX-05-03` (PBR material)

1. `src/stormline/graphics/material/material_types.hpp`
2. `src/stormline/graphics/material/pbr_material.hpp`
3. `tests/core/gfx05_material_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-GFX-05-03.md`

### `GFX-05-04` (textures and virtual pages)

1. `src/stormline/graphics/material/virtual_texture.hpp`
2. `tests/core/gfx05_texture_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-05-04.md`

### `GFX-05-05` (mips)

1. `src/stormline/graphics/material/texture_mip.hpp`
2. `tests/core/gfx05_mip_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-05-05.md`

### `GFX-05-06` (filters)

1. `src/stormline/graphics/material/texture_sampler.hpp`
2. `tests/core/gfx05_sampler_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-05-06.md`

### `GFX-05-07` (decals)

1. `src/stormline/graphics/material/decal.hpp`
2. `tests/core/gfx05_decal_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-05-07.md`

### `GFX-05-08` (transparency)

1. `src/stormline/graphics/material/transparency.hpp`
2. `tests/core/gfx05_transparency_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-05-08.md`

### `GFX-05-09` (qualification)

1. `tests/core/gfx05_material_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-GFX-05-09.md`

`GFX-05-10` is documentary closeout only. Qualification is internal/CI-only; no native GPU, codec, submission, rendering, hardware, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/codec/decoder selection, submission, host I/O, public ABI/release claim or HIGH/CRITICAL. Revert normally; never force push.
