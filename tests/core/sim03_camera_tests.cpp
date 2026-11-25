#include "stormline/character/camera_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::character;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

CameraDesc camera(u32 id, bool follow) {
    CameraDesc desc{};
    desc.camera_id = id;
    desc.revision = 1;
    desc.target_controller_id = 1;
    desc.distance = 4.0f;
    desc.height = 1.5f;
    desc.yaw_offset_degrees = 45.0f;
    desc.pitch_degrees = -15.0f;
    desc.position_damping = 0.2f;
    desc.rotation_damping = 0.3f;
    desc.follow_enabled = follow;
    desc.independent_from_animation = true;
    return desc;
}

CameraSetDesc camera_set() {
    CameraSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.camera_count = 2;
    desc.cameras[0] = camera(1, true);
    desc.cameras[1] = camera(2, false);
    return desc;
}

bool run_cam01() {
    begin();
    CameraSetDesc cameras = camera_set();
    CameraPlan plan{};
    CharacterDiagnostic diagnostic{};
    expect(plan_cameras(cameras, plan, diagnostic) == CharacterError::None,
           "valid cameras");
    expect(plan.camera_count == 2 && plan.follow_count == 1
               && plan.independent_count == 2,
           "valid plan");
    expect(diagnostic.code == CharacterError::None, "success diagnostic");

    CameraPlan repeat{};
    expect(plan_cameras(cameras, repeat, diagnostic) == CharacterError::None,
           "repeat cameras");
    expect(repeat.follow_count == plan.follow_count, "deterministic plan");

    cameras.owner_id = 0;
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::InvalidArgument,
           "zero owner");
    expect(plan.camera_count == 0, "reset on zero owner");
    cameras = camera_set();
    cameras.revision = 0;
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::InvalidArgument,
           "zero revision");
    cameras = camera_set();
    cameras.camera_count = kMaxCameras + 1;
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::CapacityFull,
           "camera overflow");

    cameras = camera_set();
    cameras.cameras[1].camera_id = 0;
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::CameraInvalid,
           "zero camera id");
    expect(diagnostic.index == 1, "zero camera diagnostic");
    cameras = camera_set();
    cameras.cameras[1].revision = 0;
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::CameraInvalid,
           "zero revision");
    cameras = camera_set();
    cameras.cameras[1].target_controller_id = 0;
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::CameraInvalid,
           "zero target");
    cameras = camera_set();
    cameras.cameras[1].independent_from_animation = false;
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::CameraInvalid,
           "animation-coupled camera");

    cameras = camera_set();
    cameras.cameras[1].distance = -1.0f;
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::OutOfRange,
           "negative distance");
    cameras = camera_set();
    cameras.cameras[1].pitch_degrees = 90.0f;
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::OutOfRange,
           "pitch above range");
    cameras = camera_set();
    cameras.cameras[1].position_damping = 1.5f;
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::OutOfRange,
           "position damping above one");
    cameras = camera_set();
    cameras.cameras[1].rotation_damping = -0.5f;
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::OutOfRange,
           "rotation damping below zero");
    cameras = camera_set();
    cameras.cameras[1].height =
        std::numeric_limits<f32>::quiet_NaN();
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::NonFiniteValue,
           "non-finite height");
    cameras = camera_set();
    cameras.cameras[1].camera_id = 1;
    expect(plan_cameras(cameras, plan, diagnostic)
               == CharacterError::DuplicateId,
           "duplicate camera");
    expect(diagnostic.index == 1, "duplicate camera diagnostic");

    cameras = camera_set();
    cameras.camera_count = kMaxCameras;
    for (u32 index = 0; index < kMaxCameras; ++index) {
        cameras.cameras[index] = camera(index + 1, index % 2 == 0);
    }
    expect(plan_cameras(cameras, plan, diagnostic) == CharacterError::None,
           "capacity cameras");
    expect(plan.camera_count == kMaxCameras
               && plan.follow_count == kMaxCameras / 2
               && plan.independent_count == kMaxCameras,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim03_camera_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "cam01") { success = run_cam01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
