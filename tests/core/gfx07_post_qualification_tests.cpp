#include "stormline/graphics/post/motion_blur.hpp"
#include "stormline/graphics/post/upscale_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::post;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

struct Pipeline {
    CameraSet cameras{};
    ExposurePlan exposure{};
    ColorPlan color{};
    OutputPlan output{};
    ReconstructionPlan reconstruction{};
    MotionBlurPlan blur{};
    UpscalePlan upscale{};
    PostDiagnostic diagnostic{};
};

CameraViewDesc valid_camera(u32 id) {
    CameraViewDesc camera{};
    camera.camera_id = id;
    camera.revision = 3;
    camera.projection = ProjectionKind::Perspective;
    camera.vertical_fov_radians = 1.0471975512f;
    camera.aspect = 1.7777778f;
    camera.near_distance = 0.1f;
    camera.far_distance = 1000.0f;
    camera.render_width = 1920;
    camera.render_height = 1080;
    camera.output_width = 3840;
    camera.output_height = 2160;
    camera.jitter = Vec2{0.25f, -0.25f};
    camera.previous_jitter = Vec2{-0.25f, 0.25f};
    camera.jitter_world_only = true;
    camera.scene_generation = 42;
    return camera;
}

bool run_pipeline(Pipeline& pipeline) {
    pipeline = Pipeline{};
    if (add_camera(pipeline.cameras, valid_camera(7)) != PostError::None) {
        return false;
    }
    if (validate_cameras(pipeline.cameras, pipeline.diagnostic)
        != PostError::None) {
        return false;
    }
    ExposureDesc exposure{};
    exposure.auto_exposure = true;
    exposure.low_percentile = 0.1f;
    exposure.high_percentile = 99.0f;
    if (plan_exposure(exposure, pipeline.exposure, pipeline.diagnostic)
        != PostError::None) {
        return false;
    }
    const ColorPlanDesc color{};
    if (plan_color(color, pipeline.color, pipeline.diagnostic)
        != PostError::None) {
        return false;
    }
    HdrCapability capability{};
    capability.display_hdr = true;
    capability.swapchain_hdr = true;
    capability.os_hdr = true;
    capability.pq_supported = true;
    const OutputRequest output{true};
    if (plan_output(capability, output, pipeline.output, pipeline.diagnostic)
        != PostError::None) {
        return false;
    }
    ReconstructionRequest reconstruction{};
    reconstruction.preferred = ReconstructionStrategy::VendorUpscale;
    reconstruction.depth_available = true;
    reconstruction.velocity_available = true;
    reconstruction.history_available = true;
    reconstruction.reactive_mask_available = true;
    reconstruction.vendor_available = true;
    if (plan_reconstruction(reconstruction, pipeline.reconstruction,
                            pipeline.diagnostic) != PostError::None) {
        return false;
    }
    MotionBlurDesc blur{};
    blur.enabled = true;
    blur.shutter_angle_degrees = 180.0f;
    blur.max_velocity_pixels = 2.0f;
    if (plan_motion_blur(blur, pipeline.blur, pipeline.diagnostic)
        != PostError::None) {
        return false;
    }
    const UpscaleRequest upscale{1920, 1080, 3840, 2160,
                                 ReconstructionStrategy::VendorUpscale};
    return plan_upscale(upscale, pipeline.upscale, pipeline.diagnostic)
        == PostError::None;
}

bool same_pipeline(const Pipeline& left, const Pipeline& right) {
    const CameraViewDesc& a = left.cameras.cameras[0];
    const CameraViewDesc& b = right.cameras.cameras[0];
    return left.cameras.count == right.cameras.count
        && a.camera_id == b.camera_id && a.revision == b.revision
        && a.render_width == b.render_width
        && a.output_width == b.output_width
        && left.exposure.ev100 == right.exposure.ev100
        && left.exposure.auto_exposure == right.exposure.auto_exposure
        && left.exposure.flash_resilient == right.exposure.flash_resilient
        && left.color.output_transfer == right.color.output_transfer
        && left.color.tone_curve == right.color.tone_curve
        && left.color.exposure_stops == right.color.exposure_stops
        && left.output.mode == right.output.mode
        && left.output.degraded == right.output.degraded
        && left.reconstruction.strategy == right.reconstruction.strategy
        && left.reconstruction.degraded == right.reconstruction.degraded
        && left.blur.enabled == right.blur.enabled
        && left.upscale.scale_numerator == right.upscale.scale_numerator
        && left.upscale.scale_denominator == right.upscale.scale_denominator
        && left.upscale.reconstructed == right.upscale.reconstructed
        && left.diagnostic.code == right.diagnostic.code;
}

bool run_qlfg701() {
    begin();
    Pipeline pipeline{};
    expect(run_pipeline(pipeline), "integrated pipeline succeeds");
    expect(pipeline.cameras.count == 1, "camera admitted");
    expect(pipeline.cameras.cameras[0].camera_id == 7, "camera identity");
    expect(pipeline.cameras.cameras[0].scene_generation == 42,
           "scene generation");
    expect(pipeline.exposure.auto_exposure, "auto exposure preserved");
    expect(pipeline.exposure.flash_resilient, "flash resilience preserved");
    expect(pipeline.color.output_transfer == ColorTransfer::Srgb,
           "sRGB output");
    expect(pipeline.color.tone_curve == ToneCurve::Neutral, "neutral tone");
    expect(pipeline.output.mode == OutputMode::Hdr10Pq, "HDR selected");
    expect(!pipeline.output.degraded, "HDR not degraded");
    expect(pipeline.reconstruction.strategy
               == ReconstructionStrategy::VendorUpscale,
           "vendor reconstruction");
    expect(!pipeline.reconstruction.degraded, "reconstruction not degraded");
    expect(pipeline.blur.enabled, "motion blur enabled");
    expect(pipeline.upscale.scale_numerator == 1
               && pipeline.upscale.scale_denominator == 2,
           "scale fraction 1/2");
    expect(pipeline.upscale.reconstructed, "reconstructed flag");
    expect(pipeline.diagnostic.code == PostError::None, "diagnostic clear");
    return finish();
}

bool run_qlfg702() {
    begin();
    Pipeline first{};
    Pipeline second{};
    expect(run_pipeline(first), "first run");
    expect(run_pipeline(second), "second run");
    expect(same_pipeline(first, second), "deterministic plans");
    for (u32 attempt = 0; attempt < 100; ++attempt) {
        Pipeline repeated{};
        expect(run_pipeline(repeated), "repeat succeeds");
        expect(same_pipeline(first, repeated), "repeat identical");
        if (failures != 0) {
            break;
        }
    }
    return finish();
}

bool run_qlfg703() {
    begin();
    Pipeline pipeline{};
    expect(run_pipeline(pipeline), "baseline pipeline");

    const u32 count_before = pipeline.cameras.count;
    expect(add_camera(pipeline.cameras, valid_camera(7))
               == PostError::DuplicateId,
           "duplicate camera typed failure");
    expect(pipeline.cameras.count == count_before, "duplicate keeps capacity");
    expect(add_camera(pipeline.cameras, valid_camera(8)) == PostError::None,
           "valid add after duplicate");

    ExposureDesc exposure{};
    exposure.ev100 = 99.0f;
    expect(plan_exposure(exposure, pipeline.exposure, pipeline.diagnostic)
               == PostError::OutOfRange,
           "invalid exposure typed failure");
    exposure.ev100 = 0.0f;
    expect(plan_exposure(exposure, pipeline.exposure, pipeline.diagnostic)
               == PostError::None,
           "valid exposure after failure");

    ColorPlanDesc color{};
    color.output_transfer = ColorTransfer::Linear;
    expect(plan_color(color, pipeline.color, pipeline.diagnostic)
               == PostError::Unsupported,
           "invalid color typed failure");
    color.output_transfer = ColorTransfer::Srgb;
    expect(plan_color(color, pipeline.color, pipeline.diagnostic)
               == PostError::None,
           "valid color after failure");

    MotionBlurDesc blur{};
    blur.enabled = true;
    expect(plan_motion_blur(blur, pipeline.blur, pipeline.diagnostic)
               == PostError::Unsupported,
           "invalid blur typed failure");
    blur.max_velocity_pixels = 1.0f;
    expect(plan_motion_blur(blur, pipeline.blur, pipeline.diagnostic)
               == PostError::None,
           "valid blur after failure");
    expect(pipeline.blur.enabled, "valid blur enabled");

    UpscaleRequest upscale{1920, 1080, 3840, 2160,
                           ReconstructionStrategy::Native};
    expect(plan_upscale(upscale, pipeline.upscale, pipeline.diagnostic)
               == PostError::Unsupported,
           "native mismatch typed failure");
    upscale.strategy = ReconstructionStrategy::Spatial;
    expect(plan_upscale(upscale, pipeline.upscale, pipeline.diagnostic)
               == PostError::None,
           "valid upscale after failure");
    expect(pipeline.upscale.scale_numerator == 1
               && pipeline.upscale.scale_denominator == 2,
           "recovered scale fraction");
    return finish();
}

bool run_qlfg704() {
    begin();
    CameraSet cameras{};
    for (u32 id = 1; id <= kMaxCameras; ++id) {
        expect(add_camera(cameras, valid_camera(id)) == PostError::None,
               "capacity fill");
    }
    expect(cameras.count == kMaxCameras, "capacity reached");
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        expect(add_camera(cameras, valid_camera(kMaxCameras + 1))
                   == PostError::CapacityFull,
               "capacity bounded");
        if (failures != 0) {
            break;
        }
    }
    expect(cameras.count == kMaxCameras, "capacity retained");
    PostDiagnostic diagnostic{};
    expect(validate_cameras(cameras, diagnostic) == PostError::None,
           "capacity set still valid");
    const UpscaleRequest upscale{1600, 900, 2560, 1440,
                                 ReconstructionStrategy::Spatial};
    UpscalePlan plan{};
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        expect(plan_upscale(upscale, plan, diagnostic) == PostError::None,
               "bounded upscale succeeds");
        expect(plan.scale_numerator == 5 && plan.scale_denominator == 8,
               "bounded fraction stable");
        if (failures != 0) {
            break;
        }
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx07_post_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlfg701") { success = run_qlfg701(); }
    else if (mode == "qlfg702") { success = run_qlfg702(); }
    else if (mode == "qlfg703") { success = run_qlfg703(); }
    else if (mode == "qlfg704") { success = run_qlfg704(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
