#include "stormline/graphics/post/camera_exposure.hpp"

#include <cstdio>
#include <limits>
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

[[nodiscard]] CameraViewDesc camera(u32 id = 1) {
    CameraViewDesc value{};
    value.camera_id = id;
    value.revision = 1;
    value.projection = ProjectionKind::Perspective;
    value.vertical_fov_radians = 1.0f;
    value.aspect = 16.0f / 9.0f;
    value.near_distance = 0.1f;
    value.far_distance = 1000.0f;
    value.render_width = 1920;
    value.render_height = 1080;
    value.output_width = 1920;
    value.output_height = 1080;
    value.scene_generation = 7;
    return value;
}

bool run_cam_exp() {
    begin();
    CameraSet cameras{};
    PostDiagnostic diagnostic{};

    expect(add_camera(cameras, camera()) == PostError::None, "add");
    CameraViewDesc ortho = camera(2);
    ortho.projection = ProjectionKind::Orthographic;
    ortho.ortho_height = 10.0f;
    expect(add_camera(cameras, ortho) == PostError::None, "ortho");
    expect(validate_cameras(cameras, diagnostic) == PostError::None, "valid");
    expect(add_camera(cameras, camera()) == PostError::DuplicateId, "duplicate");
    expect(add_camera(cameras, camera(0)) == PostError::InvalidCamera, "zero id");

    CameraViewDesc invalid = camera(3);
    invalid.revision = 0;
    expect(add_camera(cameras, invalid) == PostError::InvalidCamera,
           "zero revision");
    invalid = camera(3);
    invalid.projection = static_cast<ProjectionKind>(200);
    expect(add_camera(cameras, invalid) == PostError::InvalidProjection,
           "projection enum");
    invalid = camera(3);
    invalid.aspect = 0.0f;
    expect(add_camera(cameras, invalid) == PostError::InvalidCamera, "aspect");
    invalid = camera(3);
    invalid.near_distance = 0.0f;
    expect(add_camera(cameras, invalid) == PostError::InvalidCamera, "near");
    invalid = camera(3);
    invalid.far_distance = invalid.near_distance;
    expect(add_camera(cameras, invalid) == PostError::InvalidCamera, "far");
    invalid = camera(3);
    invalid.render_width = 0;
    expect(add_camera(cameras, invalid) == PostError::InvalidCamera, "render width");
    invalid = camera(3);
    invalid.output_height = 0;
    expect(add_camera(cameras, invalid) == PostError::InvalidCamera, "output height");
    invalid = camera(3);
    invalid.jitter.x = std::numeric_limits<f32>::quiet_NaN();
    expect(add_camera(cameras, invalid) == PostError::NonFiniteValue, "jitter");
    invalid = camera(3);
    invalid.jitter_world_only = false;
    expect(add_camera(cameras, invalid) == PostError::InvalidCamera,
           "world only");
    invalid = camera(3);
    invalid.scene_generation = 0;
    expect(add_camera(cameras, invalid) == PostError::InvalidCamera,
           "generation");
    invalid = camera(3);
    invalid.vertical_fov_radians = 0.0f;
    expect(add_camera(cameras, invalid) == PostError::InvalidProjection, "fov");
    invalid = camera(3);
    invalid.vertical_fov_radians = kPi;
    expect(add_camera(cameras, invalid) == PostError::InvalidProjection, "fov max");
    invalid = camera(3);
    invalid.projection = ProjectionKind::Orthographic;
    invalid.ortho_height = 0.0f;
    expect(add_camera(cameras, invalid) == PostError::InvalidProjection,
           "ortho height");
    invalid = camera(3);
    invalid.vertical_fov_radians = std::numeric_limits<f32>::infinity();
    expect(add_camera(cameras, invalid) == PostError::NonFiniteValue, "fov inf");

    CameraSet duplicate_set{};
    duplicate_set.count = 2;
    duplicate_set.cameras[0] = camera(1);
    duplicate_set.cameras[1] = camera(1);
    expect(validate_cameras(duplicate_set, diagnostic) == PostError::DuplicateId,
           "manual duplicate");
    CameraSet overflow{};
    overflow.count = kMaxCameras + 1;
    expect(validate_cameras(overflow, diagnostic) == PostError::InvalidArgument,
           "capacity");

    ExposureDesc exposure{};
    ExposurePlan exposure_plan{};
    expect(plan_exposure(exposure, exposure_plan, diagnostic) == PostError::None,
           "exposure default");
    expect(exposure_plan.ev100 == 0.0f && !exposure_plan.auto_exposure
               && exposure_plan.flash_resilient,
           "exposure plan");

    exposure.auto_exposure = true;
    exposure.ev100 = 100.0f;
    expect(plan_exposure(exposure, exposure_plan, diagnostic) == PostError::None,
           "auto exposure");
    expect(exposure_plan.auto_exposure, "auto flag");

    exposure = ExposureDesc{};
    exposure.ev100 = 20.0f;
    expect(plan_exposure(exposure, exposure_plan, diagnostic)
               == PostError::OutOfRange,
           "ev range");
    exposure = ExposureDesc{};
    exposure.min_ev = 1.0f;
    exposure.max_ev = 0.0f;
    expect(plan_exposure(exposure, exposure_plan, diagnostic)
               == PostError::OutOfRange,
           "ev order");
    exposure = ExposureDesc{};
    exposure.dark_adapt_seconds = 0.0f;
    expect(plan_exposure(exposure, exposure_plan, diagnostic)
               == PostError::OutOfRange,
           "dark adapt");
    exposure = ExposureDesc{};
    exposure.bright_adapt_seconds = 0.0f;
    expect(plan_exposure(exposure, exposure_plan, diagnostic)
               == PostError::OutOfRange,
           "bright adapt");
    exposure = ExposureDesc{};
    exposure.low_percentile = 0.95f;
    exposure.high_percentile = 0.9f;
    expect(plan_exposure(exposure, exposure_plan, diagnostic)
               == PostError::OutOfRange,
           "percentile order");
    exposure = ExposureDesc{};
    exposure.high_percentile = 101.0f;
    expect(plan_exposure(exposure, exposure_plan, diagnostic)
               == PostError::OutOfRange,
           "percentile max");
    exposure = ExposureDesc{};
    exposure.ev100 = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_exposure(exposure, exposure_plan, diagnostic)
               == PostError::NonFiniteValue,
           "ev nan");
    expect(exposure_plan.ev100 == 0.0f, "exposure reset");

    expect(std::string_view(post_error_name(PostError::None)) == "None",
           "error none");
    expect(std::string_view(post_error_name(static_cast<PostError>(200)))
               == "Unknown",
           "error unknown");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx07_camera_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "cam01") { success = run_cam_exp(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
