#include "stormline/graphics/canvas2d/camera_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::canvas2d;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_cam01() {
    begin();
    CanvasCameraDesc camera{};
    camera.viewport_width = 1920;
    camera.viewport_height = 1080;
    camera.position_x = 32.0f;
    camera.position_y = -16.0f;
    camera.zoom = 2.0f;
    camera.dpi_scale = 1.5f;
    camera.letterbox = true;
    CameraPlan plan{};
    CanvasDiagnostic diagnostic{};

    expect(plan_camera(camera, plan, diagnostic) == CanvasError::None,
           "valid camera");
    expect(plan.effective_zoom == 3.0f && plan.dpi_scale == 1.5f
               && plan.letterbox,
           "valid plan");

    camera.viewport_width = 0;
    expect(plan_camera(camera, plan, diagnostic) == CanvasError::CameraInvalid,
           "zero viewport");
    expect(plan.effective_zoom == 1.0f && !plan.letterbox, "reset");

    camera = CanvasCameraDesc{};
    camera.viewport_width = 800;
    camera.viewport_height = 600;
    camera.zoom = 0.0f;
    expect(plan_camera(camera, plan, diagnostic) == CanvasError::CameraInvalid,
           "zero zoom");
    camera.zoom = -1.0f;
    expect(plan_camera(camera, plan, diagnostic) == CanvasError::CameraInvalid,
           "negative zoom");
    camera.zoom = 1.0f;
    camera.dpi_scale = 0.0f;
    expect(plan_camera(camera, plan, diagnostic) == CanvasError::CameraInvalid,
           "zero dpi");
    camera.dpi_scale = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_camera(camera, plan, diagnostic)
               == CanvasError::NonFiniteValue,
           "nonfinite dpi");
    camera.dpi_scale = 1.0f;
    camera.position_x = std::numeric_limits<f32>::infinity();
    expect(plan_camera(camera, plan, diagnostic)
               == CanvasError::NonFiniteValue,
           "nonfinite position");
    camera.position_x = 0.0f;
    camera.zoom = std::numeric_limits<f32>::max();
    camera.dpi_scale = 2.0f;
    expect(plan_camera(camera, plan, diagnostic) == CanvasError::OutOfRange,
           "zoom overflow");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two01_camera_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "cam01") { success = run_cam01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
