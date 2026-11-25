#include "stormline/character/controller_plan.hpp"
#include "stormline/character/locomotion_plan.hpp"
#include "stormline/character/input_plan.hpp"
#include "stormline/character/camera_plan.hpp"

#include <cstdio>
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

struct Plans {
    ControllerPlan controllers{};
    LocomotionPlan locomotion{};
    InputPlan input{};
    CameraPlan cameras{};
    CharacterDiagnostic diagnostic{};
};

ControllerDesc make_controller(u32 id, ControllerDimension dimension,
                               ControllerMode mode, bool enabled) {
    ControllerDesc desc{};
    desc.controller_id = id;
    desc.revision = 1;
    desc.entity_id = 100 + id;
    desc.dimension = dimension;
    desc.mode = mode;
    desc.half_x = 0.5f;
    desc.half_y = 1.0f;
    desc.half_z = dimension == ControllerDimension::TwoD ? 0.0f : 0.5f;
    desc.up_y = 1.0f;
    desc.max_slope_degrees = 45.0f;
    desc.step_height = 0.3f;
    desc.enabled = enabled;
    return desc;
}

ControllerSetDesc make_controllers() {
    ControllerSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.controller_count = 2;
    desc.controllers[0] = make_controller(
        1, ControllerDimension::TwoD, ControllerMode::Kinematic, true);
    desc.controllers[1] = make_controller(
        2, ControllerDimension::ThreeD, ControllerMode::Dynamic, false);
    return desc;
}

LocomotionDesc make_locomotion(u32 id, bool enabled) {
    LocomotionDesc desc{};
    desc.locomotion_id = id;
    desc.revision = 1;
    desc.controller_id = 1;
    desc.walk_speed = 2.0f;
    desc.run_speed = 5.0f;
    desc.air_speed = 3.0f;
    desc.acceleration = 10.0f;
    desc.deceleration = 12.0f;
    desc.jump_height = 1.5f;
    desc.jump_buffer_ticks = 6;
    desc.coyote_ticks = 4;
    desc.dash_speed = 8.0f;
    desc.dash_ticks = 10;
    desc.enabled = enabled;
    return desc;
}

LocomotionSetDesc make_locomotion_set() {
    LocomotionSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.locomotion_count = 2;
    desc.locomotion[0] = make_locomotion(1, true);
    desc.locomotion[1] = make_locomotion(2, false);
    desc.locomotion[1].jump_height = 0.0f;
    return desc;
}

InputActionDesc make_action(u32 id, u32 axis, bool enabled) {
    InputActionDesc desc{};
    desc.action_id = id;
    desc.revision = 1;
    desc.axis_index = axis;
    desc.dead_zone = 0.2f;
    desc.scale = 1.0f;
    desc.buffer_ticks = 6;
    desc.enabled = enabled;
    return desc;
}

InputSetDesc make_input() {
    InputSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.action_count = 3;
    desc.actions[0] = make_action(1, 0, true);
    desc.actions[1] = make_action(2, 1, false);
    desc.actions[2] = make_action(3, 0, true);
    desc.actions[2].buffer_ticks = 0;
    return desc;
}

CameraDesc make_camera(u32 id, bool follow) {
    CameraDesc desc{};
    desc.camera_id = id;
    desc.revision = 1;
    desc.target_controller_id = 1;
    desc.distance = 4.0f;
    desc.height = 1.5f;
    desc.pitch_degrees = -15.0f;
    desc.position_damping = 0.2f;
    desc.rotation_damping = 0.3f;
    desc.follow_enabled = follow;
    desc.independent_from_animation = true;
    return desc;
}

CameraSetDesc make_cameras() {
    CameraSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.camera_count = 2;
    desc.cameras[0] = make_camera(1, true);
    desc.cameras[1] = make_camera(2, false);
    return desc;
}

bool plan_all(const ControllerSetDesc& controllers,
              const LocomotionSetDesc& locomotion, const InputSetDesc& input,
              const CameraSetDesc& cameras, Plans& plans) {
    return plan_controllers(controllers, plans.controllers, plans.diagnostic)
               == CharacterError::None
           && plan_locomotion(locomotion, plans.locomotion,
                              plans.diagnostic)
               == CharacterError::None
           && plan_input(input, plans.input, plans.diagnostic)
               == CharacterError::None
           && plan_cameras(cameras, plans.cameras, plans.diagnostic)
               == CharacterError::None;
}

bool plan_default(Plans& plans) {
    return plan_all(make_controllers(), make_locomotion_set(), make_input(),
                    make_cameras(), plans);
}

bool run_qlfs301() {
    begin();
    Plans plans{};
    expect(plan_default(plans), "integrated plans");
    expect(plans.controllers.controller_count == 2
               && plans.controllers.two_d_count == 1
               && plans.controllers.three_d_count == 1
               && plans.controllers.kinematic_count == 1
               && plans.controllers.dynamic_count == 1
               && plans.controllers.enabled_count == 1,
           "controller plan");
    expect(plans.locomotion.locomotion_count == 2
               && plans.locomotion.ground_count == 2
               && plans.locomotion.jump_count == 1
               && plans.locomotion.dash_count == 2
               && plans.locomotion.enabled_count == 1,
           "locomotion plan");
    expect(plans.input.action_count == 3 && plans.input.axis_count == 1
               && plans.input.buffered_count == 2
               && plans.input.enabled_count == 2,
           "input plan");
    expect(plans.cameras.camera_count == 2 && plans.cameras.follow_count == 1
               && plans.cameras.independent_count == 2,
           "camera plan");
    expect(plans.diagnostic.code == CharacterError::None,
           "integrated diagnostic");
    return finish();
}

bool run_qlfs302() {
    begin();
    Plans first{};
    expect(plan_default(first), "deterministic first");
    for (u32 attempt = 0; attempt < 100; ++attempt) {
        Plans repeat{};
        expect(plan_default(repeat), "deterministic repeat success");
        expect(repeat.controllers.enabled_count
                   == first.controllers.enabled_count,
               "controllers identical");
        expect(repeat.locomotion.jump_count == first.locomotion.jump_count,
               "locomotion identical");
        expect(repeat.input.buffered_count == first.input.buffered_count,
               "input identical");
        expect(repeat.cameras.follow_count == first.cameras.follow_count,
               "cameras identical");
    }
    return finish();
}

bool run_qlfs303() {
    begin();
    Plans plans{};

    ControllerSetDesc controllers = make_controllers();
    controllers.controllers[1].controller_id = 1;
    expect(plan_controllers(controllers, plans.controllers,
                            plans.diagnostic)
               == CharacterError::DuplicateId,
           "controller failure");
    expect(plans.controllers.controller_count == 0, "controller reset");
    expect(plan_controllers(make_controllers(), plans.controllers,
                            plans.diagnostic)
               == CharacterError::None,
           "controller recovery");

    LocomotionSetDesc locomotion = make_locomotion_set();
    locomotion.locomotion[1].locomotion_id = 1;
    expect(plan_locomotion(locomotion, plans.locomotion, plans.diagnostic)
               == CharacterError::DuplicateId,
           "locomotion failure");
    expect(plans.locomotion.locomotion_count == 0, "locomotion reset");
    expect(plan_locomotion(make_locomotion_set(), plans.locomotion,
                           plans.diagnostic)
               == CharacterError::None,
           "locomotion recovery");

    InputSetDesc input = make_input();
    input.actions[2].action_id = 1;
    expect(plan_input(input, plans.input, plans.diagnostic)
               == CharacterError::DuplicateId,
           "input failure");
    expect(plans.input.action_count == 0, "input reset");
    expect(plan_input(make_input(), plans.input, plans.diagnostic)
               == CharacterError::None,
           "input recovery");

    CameraSetDesc cameras = make_cameras();
    cameras.cameras[1].camera_id = 1;
    expect(plan_cameras(cameras, plans.cameras, plans.diagnostic)
               == CharacterError::DuplicateId,
           "camera failure");
    expect(plans.cameras.camera_count == 0, "camera reset");
    expect(plan_cameras(make_cameras(), plans.cameras, plans.diagnostic)
               == CharacterError::None,
           "camera recovery");
    return finish();
}

bool run_qlfs304() {
    begin();
    Plans plans{};
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        ControllerSetDesc controllers = make_controllers();
        controllers.controller_count = kMaxControllers;
        for (u32 index = 0; index < kMaxControllers; ++index) {
            controllers.controllers[index] = make_controller(
                index + 1,
                index % 2 == 0 ? ControllerDimension::TwoD
                               : ControllerDimension::ThreeD,
                index % 3 == 0 ? ControllerMode::Dynamic
                               : ControllerMode::Kinematic,
                index % 2 == 0);
        }
        expect(plan_controllers(controllers, plans.controllers,
                                plans.diagnostic)
                   == CharacterError::None,
               "overload controllers");
        expect(plans.controllers.controller_count <= kMaxControllers,
               "controller cap");

        LocomotionSetDesc locomotion = make_locomotion_set();
        locomotion.locomotion_count = kMaxLocomotion;
        for (u32 index = 0; index < kMaxLocomotion; ++index) {
            locomotion.locomotion[index] =
                make_locomotion(index + 1, index % 2 == 0);
        }
        expect(plan_locomotion(locomotion, plans.locomotion,
                               plans.diagnostic)
                   == CharacterError::None,
               "overload locomotion");
        expect(plans.locomotion.locomotion_count <= kMaxLocomotion,
               "locomotion cap");

        InputSetDesc input = make_input();
        input.action_count = kMaxInputActions;
        for (u32 index = 0; index < kMaxInputActions; ++index) {
            input.actions[index] = make_action(index + 1, index % 8,
                                               index % 2 == 0);
        }
        expect(plan_input(input, plans.input, plans.diagnostic)
                   == CharacterError::None,
               "overload input");
        expect(plans.input.action_count <= kMaxInputActions, "input cap");

        CameraSetDesc cameras = make_cameras();
        cameras.camera_count = kMaxCameras;
        for (u32 index = 0; index < kMaxCameras; ++index) {
            cameras.cameras[index] = make_camera(index + 1, index % 2 == 0);
        }
        expect(plan_cameras(cameras, plans.cameras, plans.diagnostic)
                   == CharacterError::None,
               "overload cameras");
        expect(plans.cameras.camera_count <= kMaxCameras, "camera cap");
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_sim03_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlfs301") { success = run_qlfs301(); }
    else if (mode == "qlfs302") { success = run_qlfs302(); }
    else if (mode == "qlfs303") { success = run_qlfs303(); }
    else if (mode == "qlfs304") { success = run_qlfs304(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
