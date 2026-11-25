#include "stormline/character/locomotion_plan.hpp"

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

LocomotionSetDesc locomotion_set() {
    LocomotionSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.locomotion_count = 3;
    desc.locomotion[0] = make_locomotion(1, true);
    desc.locomotion[1] = make_locomotion(2, false);
    desc.locomotion[1].jump_height = 0.0f;
    desc.locomotion[2] = make_locomotion(3, true);
    desc.locomotion[2].dash_speed = 0.0f;
    return desc;
}

bool run_loco01() {
    begin();
    LocomotionSetDesc locomotion = locomotion_set();
    LocomotionPlan plan{};
    CharacterDiagnostic diagnostic{};
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::None,
           "valid locomotion");
    expect(plan.locomotion_count == 3 && plan.ground_count == 3
               && plan.air_count == 3 && plan.jump_count == 2
               && plan.dash_count == 2 && plan.enabled_count == 2,
           "valid plan");
    expect(diagnostic.code == CharacterError::None, "success diagnostic");

    LocomotionPlan repeat{};
    expect(plan_locomotion(locomotion, repeat, diagnostic)
               == CharacterError::None,
           "repeat locomotion");
    expect(repeat.enabled_count == plan.enabled_count, "deterministic plan");

    locomotion.owner_id = 0;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::InvalidArgument,
           "zero owner");
    expect(plan.locomotion_count == 0, "reset on zero owner");
    locomotion = locomotion_set();
    locomotion.revision = 0;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::InvalidArgument,
           "zero revision");
    locomotion = locomotion_set();
    locomotion.locomotion_count = kMaxLocomotion + 1;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::CapacityFull,
           "locomotion overflow");

    locomotion = locomotion_set();
    locomotion.locomotion[1].locomotion_id = 0;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::LocomotionInvalid,
           "zero locomotion id");
    expect(diagnostic.index == 1, "zero locomotion diagnostic");
    locomotion = locomotion_set();
    locomotion.locomotion[1].revision = 0;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::LocomotionInvalid,
           "zero revision");
    locomotion = locomotion_set();
    locomotion.locomotion[1].controller_id = 0;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::LocomotionInvalid,
           "zero controller");

    locomotion = locomotion_set();
    locomotion.locomotion[1].walk_speed = -1.0f;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::OutOfRange,
           "negative walk speed");
    locomotion = locomotion_set();
    locomotion.locomotion[1].run_speed = 1.0f;
    locomotion.locomotion[1].walk_speed = 2.0f;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::OutOfRange,
           "run below walk");
    locomotion = locomotion_set();
    locomotion.locomotion[1].acceleration = 0.0f;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::OutOfRange,
           "zero acceleration");
    locomotion = locomotion_set();
    locomotion.locomotion[1].deceleration = 0.0f;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::OutOfRange,
           "zero deceleration");
    locomotion = locomotion_set();
    locomotion.locomotion[1].walk_speed =
        std::numeric_limits<f32>::quiet_NaN();
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::NonFiniteValue,
           "non-finite speed");

    locomotion = locomotion_set();
    locomotion.locomotion[1].jump_buffer_ticks = kMaxTickWindow + 1;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::OutOfRange,
           "jump buffer overflow");
    locomotion = locomotion_set();
    locomotion.locomotion[1].coyote_ticks = kMaxTickWindow + 1;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::OutOfRange,
           "coyote overflow");
    locomotion = locomotion_set();
    locomotion.locomotion[1].dash_ticks = kMaxTickWindow + 1;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::OutOfRange,
           "dash ticks overflow");
    locomotion = locomotion_set();
    locomotion.locomotion[2].locomotion_id = 1;
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::DuplicateId,
           "duplicate locomotion");
    expect(diagnostic.index == 2, "duplicate locomotion diagnostic");

    locomotion = locomotion_set();
    locomotion.locomotion_count = kMaxLocomotion;
    for (u32 index = 0; index < kMaxLocomotion; ++index) {
        locomotion.locomotion[index] =
            make_locomotion(index + 1, index % 2 == 0);
    }
    expect(plan_locomotion(locomotion, plan, diagnostic)
               == CharacterError::None,
           "capacity locomotion");
    expect(plan.locomotion_count == kMaxLocomotion
               && plan.enabled_count == kMaxLocomotion / 2,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim03_locomotion_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "loco01") { success = run_loco01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
