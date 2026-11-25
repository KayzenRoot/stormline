#include "stormline/character/controller_plan.hpp"

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

ControllerDesc controller(u32 id, ControllerDimension dimension,
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
    desc.up_x = 0.0f;
    desc.up_y = 1.0f;
    desc.up_z = 0.0f;
    desc.max_slope_degrees = 45.0f;
    desc.step_height = 0.3f;
    desc.enabled = enabled;
    return desc;
}

ControllerSetDesc controller_set() {
    ControllerSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.controller_count = 3;
    desc.controllers[0] =
        controller(1, ControllerDimension::TwoD, ControllerMode::Kinematic,
                   true);
    desc.controllers[1] =
        controller(2, ControllerDimension::ThreeD, ControllerMode::Dynamic,
                   false);
    desc.controllers[2] =
        controller(3, ControllerDimension::ThreeD, ControllerMode::Kinematic,
                   true);
    return desc;
}

bool run_ctrl01() {
    begin();
    ControllerSetDesc controllers = controller_set();
    ControllerPlan plan{};
    CharacterDiagnostic diagnostic{};
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::None,
           "valid controllers");
    expect(plan.controller_count == 3 && plan.two_d_count == 1
               && plan.three_d_count == 2 && plan.kinematic_count == 2
               && plan.dynamic_count == 1 && plan.enabled_count == 2,
           "valid plan");
    expect(diagnostic.code == CharacterError::None, "success diagnostic");

    ControllerPlan repeat{};
    expect(plan_controllers(controllers, repeat, diagnostic)
               == CharacterError::None,
           "repeat controllers");
    expect(repeat.enabled_count == plan.enabled_count, "deterministic plan");

    controllers.owner_id = 0;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::InvalidArgument,
           "zero owner");
    expect(plan.controller_count == 0, "reset on zero owner");
    controllers = controller_set();
    controllers.revision = 0;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::InvalidArgument,
           "zero revision");
    controllers = controller_set();
    controllers.controller_count = kMaxControllers + 1;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::CapacityFull,
           "controller overflow");

    controllers = controller_set();
    controllers.controllers[1].controller_id = 0;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::ControllerInvalid,
           "zero controller id");
    expect(diagnostic.index == 1, "zero controller diagnostic");
    controllers = controller_set();
    controllers.controllers[1].revision = 0;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::ControllerInvalid,
           "zero revision");
    controllers = controller_set();
    controllers.controllers[1].dimension =
        static_cast<ControllerDimension>(9);
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::ControllerInvalid,
           "invalid dimension");
    controllers = controller_set();
    controllers.controllers[1].mode = static_cast<ControllerMode>(9);
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::ControllerInvalid,
           "invalid mode");

    controllers = controller_set();
    controllers.controllers[0].half_z = 0.5f;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::ControllerInvalid,
           "2d with depth");
    controllers = controller_set();
    controllers.controllers[1].half_z = 0.0f;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::ControllerInvalid,
           "3d without depth");
    controllers = controller_set();
    controllers.controllers[1].half_x = 0.0f;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::ControllerInvalid,
           "zero half extent");
    controllers = controller_set();
    controllers.controllers[1].up_y = 2.0f;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::ControllerInvalid,
           "non-unit up axis");
    controllers = controller_set();
    controllers.controllers[0].up_z = 0.5f;
    controllers.controllers[0].up_y = 0.866f;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::ControllerInvalid,
           "2d tilted up axis");

    controllers = controller_set();
    controllers.controllers[1].max_slope_degrees = 91.0f;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::OutOfRange,
           "slope above 90");
    controllers = controller_set();
    controllers.controllers[1].step_height = -1.0f;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::OutOfRange,
           "negative step height");
    controllers = controller_set();
    controllers.controllers[1].half_y =
        std::numeric_limits<f32>::quiet_NaN();
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::NonFiniteValue,
           "non-finite extent");
    controllers = controller_set();
    controllers.controllers[2].controller_id = 1;
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::DuplicateId,
           "duplicate controller");
    expect(diagnostic.index == 2, "duplicate controller diagnostic");

    controllers = controller_set();
    controllers.controller_count = kMaxControllers;
    for (u32 index = 0; index < kMaxControllers; ++index) {
        controllers.controllers[index] = controller(
            index + 1,
            index % 2 == 0 ? ControllerDimension::TwoD
                           : ControllerDimension::ThreeD,
            index % 3 == 0 ? ControllerMode::Dynamic
                           : ControllerMode::Kinematic,
            index % 2 == 0);
    }
    expect(plan_controllers(controllers, plan, diagnostic)
               == CharacterError::None,
           "capacity controllers");
    expect(plan.controller_count == kMaxControllers
               && plan.two_d_count == kMaxControllers / 2
               && plan.enabled_count == kMaxControllers / 2,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim03_controller_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "ctrl01") { success = run_ctrl01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
