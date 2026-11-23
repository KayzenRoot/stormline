# GFX-07 INTERNAL_ONLY Camera/Color/Post Contract v0 (NLE-PRPLAN-GFX-07-02)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `d049446`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **WO:** [NLE-PRPLAN-GFX-07-02](../work-orders/NLE-PRPLAN-GFX-07-02.md).

## Objective

Freeze the first bounded GFX-07 logical API: camera/projection/exposure validation, tone/color checks, SDR/HDR output fallback, reconstruction strategy, optional motion blur and render-scale/upscale metadata. No native GPU, swapchain, HDR signal, tone mapper, LUT/OCIO runtime, TAA, vendor SDK, dependency, ABI or release.

## Admission and boundaries

- Formal dependency is `GFX-06`; it is not module-qualified.
- GFX-07 owns logical camera/exposure/post plans and typed fallback metadata.
- GFX-01 swapchain/HDR capability; GFX-02 shaders; GFX-03 graph/history; GFX-04 velocity; GFX-05 materials; GFX-06 lighting; DATA-02/03/04 identity/assets/scene.
- No Vulkan/D3D12/Metal/WebGPU, HDR monitor, LUT/OCIO runtime, FSR/DLSS/XeSS or frame-generation dependency is selected.

## Policy invariants

- **No native GPU or image output.** Metadata/planning only; no swapchain, shader, pixel, tone map, AA, blur, upscale, LUT or HDR signal.
- **Bounded and finite.** Fixed capacities; NaN/Inf, zero dimensions, illegal exposure/shutter and overflow are rejected.
- **Fail closed.** Unknown IDs/modes/transfers, stale generations, double transfer/tone and invalid history are typed errors or safe fallback.
- **Deterministic.** Stable IDs and declared order determine output.
- **SDR baseline.** SDR sRGB is the mandatory fallback; HDR is never inferred from an internal float format or web canvas.
- **No visual/performance claim.** Plans are not images, HDR captures, color accuracy, latency or frame-time results.

## Internal API (logical, exact names)

```cpp
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
    Native, Spatial, Taa, VendorUpscale
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

[[nodiscard]] const char* post_error_name(PostError error) noexcept;
[[nodiscard]] PostError add_camera(
    CameraSet& set, const CameraViewDesc& camera) noexcept;
[[nodiscard]] PostError validate_cameras(
    const CameraSet& set, PostDiagnostic& diagnostic) noexcept;

struct ExposureDesc {
    f32 ev100{0.0f};
    bool auto_exposure{false};
    f32 min_ev{-8.0f};
    f32 max_ev{8.0f};
    f32 dark_adapt_seconds{1.0f};
    f32 bright_adapt_seconds{1.0f};
    f32 low_percentile{0.1f};
    f32 high_percentile{0.9f};
    bool flash_resilient{true};
};

struct ExposurePlan {
    f32 ev100{0.0f};
    bool auto_exposure{false};
    bool flash_resilient{true};
};

[[nodiscard]] PostError plan_exposure(
    const ExposureDesc& exposure, ExposurePlan& plan,
    PostDiagnostic& diagnostic) noexcept;

struct ColorPlanDesc {
    ColorTransfer input_transfer{ColorTransfer::Linear};
    ColorTransfer output_transfer{ColorTransfer::Srgb};
    ToneCurve tone_curve{ToneCurve::Neutral};
    f32 exposure_stops{0.0f};
    f32 white_point_nits{203.0f};
    bool tone_already_applied{false};
    bool gamma_already_applied{false};
};

struct ColorPlan {
    ColorTransfer output_transfer{ColorTransfer::Srgb};
    ToneCurve tone_curve{ToneCurve::Neutral};
    f32 exposure_stops{0.0f};
};

[[nodiscard]] PostError plan_color(
    const ColorPlanDesc& description, ColorPlan& plan,
    PostDiagnostic& diagnostic) noexcept;

struct HdrCapability {
    bool display_hdr{false};
    bool swapchain_hdr{false};
    bool os_hdr{false};
    bool pq_supported{false};
};

struct OutputRequest {
    bool prefer_hdr{false};
};

struct OutputPlan {
    OutputMode mode{OutputMode::SdrSrgb};
    bool degraded{false};
};

[[nodiscard]] PostError plan_output(
    const HdrCapability& capability, const OutputRequest& request,
    OutputPlan& plan, PostDiagnostic& diagnostic) noexcept;

struct ReconstructionRequest {
    ReconstructionStrategy preferred{ReconstructionStrategy::Native};
    bool depth_available{false};
    bool velocity_available{false};
    bool history_available{false};
    bool reactive_mask_available{false};
    bool vendor_available{false};
};

struct ReconstructionPlan {
    ReconstructionStrategy strategy{ReconstructionStrategy::Native};
    bool degraded{false};
};

[[nodiscard]] PostError plan_reconstruction(
    const ReconstructionRequest& request, ReconstructionPlan& plan,
    PostDiagnostic& diagnostic) noexcept;

struct MotionBlurDesc {
    bool enabled{false};
    bool reduced_motion{false};
    f32 shutter_angle_degrees{180.0f};
    f32 max_velocity_pixels{0.0f};
};

struct MotionBlurPlan {
    bool enabled{false};
};

[[nodiscard]] PostError plan_motion_blur(
    const MotionBlurDesc& description, MotionBlurPlan& plan,
    PostDiagnostic& diagnostic) noexcept;

struct UpscaleRequest {
    u32 render_width{0};
    u32 render_height{0};
    u32 output_width{0};
    u32 output_height{0};
    ReconstructionStrategy strategy{ReconstructionStrategy::Native};
};

struct UpscalePlan {
    u32 scale_numerator{1};
    u32 scale_denominator{1};
    bool reconstructed{false};
};

[[nodiscard]] PostError plan_upscale(
    const UpscaleRequest& request, UpscalePlan& plan,
    PostDiagnostic& diagnostic) noexcept;

}  // namespace stormline::graphics::post
```

No implementation is provided. Names or semantics may be refined only by an audited contract correction before `GFX-07-03`.

## Semantics

- **Cameras:** IDs/revisions nonzero and unique; projection declared; aspect, near and far finite with `aspect>0` and `0<near<far`; render/output dimensions positive; jitter finite; `jitter_world_only` must be true; scene generation nonzero. Perspective requires `0<fov<pi`; Orthographic requires `ortho_height>0`. UI is unjittered by contract.
- **Exposure:** EV/min/max finite with `min_ev<=max_ev` and `ev100` in range when manual; adaptation times finite `>0`; percentiles finite with `0<=low<high<=100`; auto/flash flags preserved. No histogram is read.
- **Color:** transfers and tone curve declared; exposure stops finite in `[-16,16]`; white point finite `>0`; `tone_already_applied` or `gamma_already_applied` returns `DoubleTransferGuard`. Output transfer is fixed to sRGB for this slice.
- **HDR output:** HDR is selected only when all four capability flags are true and `prefer_hdr` is set; otherwise SDR sRGB with `degraded=true` when HDR was preferred. Internal float format never implies HDR.
- **Reconstruction:** Native/Spatial are always safe. TAA requires depth/velocity/history; Vendor upscale also requires vendor availability and reactive mask. Missing prerequisites degrade to Spatial with `degraded=true`; unknown strategy fails closed.
- **Motion blur:** shutter angle finite in `[0,360]`; max velocity finite `>=0`; reduced-motion or disabled input forces `enabled=false`; enabling without positive motion metadata returns `Unsupported`. No vectors are sampled.
- **Upscale:** dimensions positive; `output>=render`; fraction reduced by GCD; `reconstructed = render != output`. Native with differing dimensions returns `Unsupported`; other strategies are metadata only. No SDK or kernel exists.
- **Common:** all functions `noexcept`; no allocation, exception, file, network, GPU, thread or global state. Invalid input zeroes/defaults outputs. No plan is an image, HDR signal or GPU resource.

## Test oracles (future GFX-07-03..-09)

| ID | Scenario | Oracle |
|---|---|---|
| CAM-01 | camera/projection | add/duplicate/capacity, perspective/ortho, near/far/aspect/dims/jitter/generation |
| EXP-01 | exposure | manual/auto, EV range, adaptive times, percentiles, flash |
| COL-01 | tone/color | transfers, tone curve, stops, white point, double-transfer guard |
| HDR-01 | output negotiation | HDR all-capable, partial/unknown fallback, SDR preference |
| RCN-01 | reconstruction | native/spatial/TAA/vendor prerequisites and fallback |
| MBL-01 | motion blur | enable/disable, reduced motion, shutter/velocity bounds |
| UPS-01 | upscale | scale reduction, native mismatch, reconstructed flag, invalid dims |
| QLF-G701 | integrated | camera->exposure->color->output->reconstruction->blur->upscale |
| QLF-G702 | deterministic repeat | identical plans/flags/fractions |
| QLF-G703 | failure recovery | typed error followed by valid operation |
| QLF-G704 | bounded overload | 10,000 attempts keep capacities |

## Implementation allowlists

Headers are internal and header-only under `src/stormline/graphics/post/`. CMake adds one `INTERFACE` target and one test executable per packet; no production `.cpp`.

### `GFX-07-03` (camera/exposure)

1. `src/stormline/graphics/post/post_types.hpp`
2. `src/stormline/graphics/post/camera_exposure.hpp`
3. `tests/core/gfx07_camera_tests.cpp`
4. `CMakeLists.txt`
5. `.github/workflows/core01-internal-headless.yml`
6. `docs/evidence/NLE-PRPLAN-GFX-07-03.md`

### `GFX-07-04` (tone/color)

1. `src/stormline/graphics/post/tone_color.hpp`
2. `tests/core/gfx07_color_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-07-04.md`

### `GFX-07-05` (HDR output)

1. `src/stormline/graphics/post/output_plan.hpp`
2. `tests/core/gfx07_output_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-07-05.md`

### `GFX-07-06` (reconstruction/AA)

1. `src/stormline/graphics/post/reconstruction_plan.hpp`
2. `tests/core/gfx07_reconstruction_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-07-06.md`

### `GFX-07-07` (motion blur)

1. `src/stormline/graphics/post/motion_blur.hpp`
2. `tests/core/gfx07_motion_blur_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-07-07.md`

### `GFX-07-08` (upscale)

1. `src/stormline/graphics/post/upscale_plan.hpp`
2. `tests/core/gfx07_upscale_tests.cpp`
3. `CMakeLists.txt`
4. `.github/workflows/core01-internal-headless.yml`
5. `docs/evidence/NLE-PRPLAN-GFX-07-08.md`

### `GFX-07-09` (qualification)

1. `tests/core/gfx07_post_qualification_tests.cpp`
2. `CMakeLists.txt`
3. `.github/workflows/core01-internal-headless.yml`
4. `docs/evidence/NLE-PRPLAN-GFX-07-09.md`

`GFX-07-10` is documentary closeout only. Qualification is internal/CI-only; no native GPU, swapchain, HDR signal, tone mapper, TAA, vendor SDK, rendering, hardware, ABI or release claim.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/display/SDK selection, submission, host I/O, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.
