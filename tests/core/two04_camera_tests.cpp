#include "stormline/hybrid/camera_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::hybrid;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

CameraDesc orthographic() {
    CameraDesc desc{};
    desc.camera_id = 1;
    desc.revision = 1;
    desc.projection = ProjectionKind::Orthographic;
    desc.near_plane = 0.1f;
    desc.far_plane = 1000.0f;
    desc.ortho_half_height = 10.0f;
    desc.ortho_aspect = 1.5f;
    return desc;
}

CameraDesc perspective() {
    CameraDesc desc{};
    desc.camera_id = 2;
    desc.revision = 1;
    desc.projection = ProjectionKind::Perspective;
    desc.near_plane = 0.1f;
    desc.far_plane = 100.0f;
    desc.perspective_fov_degrees = 60.0f;
    desc.perspective_aspect = 1.7777778f;
    return desc;
}

bool run_cam01() {
    begin();
    CameraDesc camera = orthographic();
    CameraPlan plan{};
    HybridDiagnostic diagnostic{};

    expect(plan_camera(camera, plan, diagnostic) == HybridError::None,
           "valid orthographic");
    expect(plan.projection == ProjectionKind::Orthographic
               && plan.primary_extent == 10.0f && plan.aspect == 1.5f
               && plan.near_plane == 0.1f && plan.far_plane == 1000.0f,
           "orthographic plan");

    camera = perspective();
    expect(plan_camera(camera, plan, diagnostic) == HybridError::None,
           "valid perspective");
    expect(plan.projection == ProjectionKind::Perspective
               && plan.primary_extent == 60.0f
               && plan.aspect == 1.7777778f,
           "perspective plan");

    CameraPlan repeat{};
    expect(plan_camera(camera, repeat, diagnostic) == HybridError::None,
           "repeat perspective");
    expect(plan.primary_extent == repeat.primary_extent
               && plan.aspect == repeat.aspect,
           "deterministic camera");

    camera = orthographic();
    camera.camera_id = 0;
    expect(plan_camera(camera, plan, diagnostic)
               == HybridError::InvalidArgument,
           "zero camera");
    expect(plan.primary_extent == 0.0f && plan.aspect == 0.0f,
           "reset on zero camera");
    camera = orthographic();
    camera.revision = 0;
    expect(plan_camera(camera, plan, diagnostic)
               == HybridError::InvalidArgument,
           "zero revision");

    camera = orthographic();
    camera.projection = static_cast<ProjectionKind>(200);
    expect(plan_camera(camera, plan, diagnostic) == HybridError::CameraInvalid,
           "invalid projection");

    camera = orthographic();
    camera.near_plane = 0.0f;
    expect(plan_camera(camera, plan, diagnostic) == HybridError::CameraInvalid,
           "zero near");
    camera.near_plane = -1.0f;
    expect(plan_camera(camera, plan, diagnostic) == HybridError::CameraInvalid,
           "negative near");
    camera = orthographic();
    camera.far_plane = 0.05f;
    expect(plan_camera(camera, plan, diagnostic) == HybridError::CameraInvalid,
           "far before near");
    camera.far_plane = camera.near_plane;
    expect(plan_camera(camera, plan, diagnostic) == HybridError::CameraInvalid,
           "far equals near");

    camera = orthographic();
    camera.near_plane = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_camera(camera, plan, diagnostic)
               == HybridError::NonFiniteValue,
           "nan near");
    camera = orthographic();
    camera.far_plane = std::numeric_limits<f32>::infinity();
    expect(plan_camera(camera, plan, diagnostic)
               == HybridError::NonFiniteValue,
           "infinite far");
    camera = orthographic();
    camera.ortho_half_height
        = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_camera(camera, plan, diagnostic)
               == HybridError::NonFiniteValue,
           "nan half height");
    camera = orthographic();
    camera.ortho_aspect = 0.0f;
    expect(plan_camera(camera, plan, diagnostic) == HybridError::CameraInvalid,
           "zero ortho aspect");
    camera.ortho_aspect = -1.0f;
    expect(plan_camera(camera, plan, diagnostic) == HybridError::CameraInvalid,
           "negative ortho aspect");
    camera = orthographic();
    camera.ortho_half_height = 0.0f;
    expect(plan_camera(camera, plan, diagnostic) == HybridError::CameraInvalid,
           "zero half height");

    camera = perspective();
    camera.perspective_fov_degrees = 0.0f;
    expect(plan_camera(camera, plan, diagnostic) == HybridError::CameraInvalid,
           "zero fov");
    camera.perspective_fov_degrees = 180.0f;
    expect(plan_camera(camera, plan, diagnostic) == HybridError::CameraInvalid,
           "fov 180");
    camera.perspective_fov_degrees = 200.0f;
    expect(plan_camera(camera, plan, diagnostic) == HybridError::CameraInvalid,
           "fov over 180");
    camera.perspective_fov_degrees = 0.5f;
    expect(plan_camera(camera, plan, diagnostic) == HybridError::None,
           "small fov");
    camera = perspective();
    camera.perspective_aspect = 0.0f;
    expect(plan_camera(camera, plan, diagnostic) == HybridError::CameraInvalid,
           "zero perspective aspect");
    camera = perspective();
    camera.perspective_fov_degrees
        = std::numeric_limits<f32>::infinity();
    expect(plan_camera(camera, plan, diagnostic)
               == HybridError::NonFiniteValue,
           "infinite fov");

    camera = orthographic();
    camera.near_plane = std::numeric_limits<f32>::min();
    camera.far_plane = std::numeric_limits<f32>::max();
    camera.ortho_half_height = std::numeric_limits<f32>::max();
    expect(plan_camera(camera, plan, diagnostic) == HybridError::None,
           "finite extremes");
    expect(plan.primary_extent == std::numeric_limits<f32>::max(),
           "extreme extent");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two04_camera_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "cam01") { success = run_cam01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
