#include "stormline/character/input_plan.hpp"

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

InputActionDesc action(u32 id, u32 axis, bool enabled) {
    InputActionDesc desc{};
    desc.action_id = id;
    desc.revision = 1;
    desc.axis_index = axis;
    desc.dead_zone = 0.2f;
    desc.scale = 1.0f;
    desc.buffer_ticks = 6;
    desc.consume_on_use = true;
    desc.enabled = enabled;
    return desc;
}

InputSetDesc input_set() {
    InputSetDesc desc{};
    desc.owner_id = 10;
    desc.revision = 2;
    desc.action_count = 3;
    desc.actions[0] = action(1, 0, true);
    desc.actions[1] = action(2, 1, false);
    desc.actions[2] = action(3, 0, true);
    desc.actions[2].buffer_ticks = 0;
    return desc;
}

bool run_input01() {
    begin();
    InputSetDesc input = input_set();
    InputPlan plan{};
    CharacterDiagnostic diagnostic{};
    expect(plan_input(input, plan, diagnostic) == CharacterError::None,
           "valid input");
    expect(plan.action_count == 3 && plan.axis_count == 1
               && plan.buffered_count == 2 && plan.enabled_count == 2,
           "valid plan");
    expect(diagnostic.code == CharacterError::None, "success diagnostic");

    InputPlan repeat{};
    expect(plan_input(input, repeat, diagnostic) == CharacterError::None,
           "repeat input");
    expect(repeat.buffered_count == plan.buffered_count,
           "deterministic plan");

    input.owner_id = 0;
    expect(plan_input(input, plan, diagnostic)
               == CharacterError::InvalidArgument,
           "zero owner");
    expect(plan.action_count == 0, "reset on zero owner");
    input = input_set();
    input.revision = 0;
    expect(plan_input(input, plan, diagnostic)
               == CharacterError::InvalidArgument,
           "zero revision");
    input = input_set();
    input.action_count = kMaxInputActions + 1;
    expect(plan_input(input, plan, diagnostic)
               == CharacterError::CapacityFull,
           "action overflow");

    input = input_set();
    input.actions[1].action_id = 0;
    expect(plan_input(input, plan, diagnostic)
               == CharacterError::InputInvalid,
           "zero action id");
    expect(diagnostic.index == 1, "zero action diagnostic");
    input = input_set();
    input.actions[1].revision = 0;
    expect(plan_input(input, plan, diagnostic)
               == CharacterError::InputInvalid,
           "zero revision");
    input = input_set();
    input.actions[1].axis_index = 8;
    expect(plan_input(input, plan, diagnostic)
               == CharacterError::InputInvalid,
           "axis overflow");

    input = input_set();
    input.actions[1].dead_zone = 1.5f;
    expect(plan_input(input, plan, diagnostic)
               == CharacterError::OutOfRange,
           "dead zone above one");
    input = input_set();
    input.actions[1].scale = 0.0f;
    expect(plan_input(input, plan, diagnostic)
               == CharacterError::OutOfRange,
           "zero scale");
    input = input_set();
    input.actions[1].buffer_ticks = kMaxTickWindow + 1;
    expect(plan_input(input, plan, diagnostic)
               == CharacterError::OutOfRange,
           "buffer overflow");
    input = input_set();
    input.actions[1].dead_zone =
        std::numeric_limits<f32>::quiet_NaN();
    expect(plan_input(input, plan, diagnostic)
               == CharacterError::NonFiniteValue,
           "non-finite dead zone");
    input = input_set();
    input.actions[2].action_id = 1;
    expect(plan_input(input, plan, diagnostic)
               == CharacterError::DuplicateId,
           "duplicate action");
    expect(diagnostic.index == 2, "duplicate action diagnostic");

    input = input_set();
    input.action_count = kMaxInputActions;
    for (u32 index = 0; index < kMaxInputActions; ++index) {
        input.actions[index] = action(index + 1, index % 8,
                                      index % 2 == 0);
    }
    expect(plan_input(input, plan, diagnostic) == CharacterError::None,
           "capacity input");
    expect(plan.action_count == kMaxInputActions
               && plan.axis_count == kMaxInputActions - 8
               && plan.enabled_count == kMaxInputActions / 2,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim03_input_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "input01") { success = run_input01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
