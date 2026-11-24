#include "stormline/physics2d/trigger_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::physics2d;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

TriggerDesc trigger(
    u32 id, u32 body_id, u32 shape_id, bool enter, bool exit) {
    TriggerDesc desc{};
    desc.trigger_id = id;
    desc.revision = 1;
    desc.body_id = body_id;
    desc.shape_id = shape_id;
    desc.mask_bits = 0xffffffffu;
    desc.enter_enabled = enter;
    desc.exit_enabled = exit;
    return desc;
}

TriggerSetDesc trigger_set() {
    TriggerSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.trigger_count = 3;
    desc.triggers[0] = trigger(1, 1, 10, true, false);
    desc.triggers[1] = trigger(2, 2, 11, false, true);
    desc.triggers[2] = trigger(3, 3, 12, true, true);
    return desc;
}

bool run_trg01() {
    begin();
    TriggerSetDesc triggers = trigger_set();
    TriggerPlan plan{};
    Physics2DDiagnostic diagnostic{};
    expect(plan_triggers(triggers, plan, diagnostic) == Physics2DError::None,
           "valid triggers");
    expect(plan.trigger_count == 3 && plan.enter_count == 2
               && plan.exit_count == 2 && plan.both_count == 1,
           "valid plan");
    expect(diagnostic.code == Physics2DError::None, "success diagnostic");
    TriggerPlan repeat{};
    expect(plan_triggers(triggers, repeat, diagnostic)
               == Physics2DError::None,
           "repeat triggers");
    expect(repeat.both_count == plan.both_count
               && repeat.enter_count == plan.enter_count,
           "deterministic plan");

    triggers.world_id = 0;
    expect(plan_triggers(triggers, plan, diagnostic)
               == Physics2DError::InvalidArgument,
           "zero world");
    expect(plan.trigger_count == 0 && plan.both_count == 0,
           "reset on zero world");
    triggers = trigger_set();
    triggers.revision = 0;
    expect(plan_triggers(triggers, plan, diagnostic)
               == Physics2DError::InvalidArgument,
           "zero revision");
    triggers = trigger_set();
    triggers.trigger_count = kMaxTriggers + 1;
    expect(plan_triggers(triggers, plan, diagnostic)
               == Physics2DError::CapacityFull,
           "trigger overflow");

    triggers = trigger_set();
    triggers.triggers[1].trigger_id = 0;
    expect(plan_triggers(triggers, plan, diagnostic)
               == Physics2DError::TriggerInvalid,
           "zero trigger id");
    expect(diagnostic.index == 1, "zero trigger diagnostic");
    triggers = trigger_set();
    triggers.triggers[1].revision = 0;
    expect(plan_triggers(triggers, plan, diagnostic)
               == Physics2DError::TriggerInvalid,
           "zero trigger revision");
    triggers = trigger_set();
    triggers.triggers[1].body_id = 0;
    expect(plan_triggers(triggers, plan, diagnostic)
               == Physics2DError::TriggerInvalid,
           "zero body ref");
    triggers = trigger_set();
    triggers.triggers[1].shape_id = 0;
    expect(plan_triggers(triggers, plan, diagnostic)
               == Physics2DError::TriggerInvalid,
           "zero shape ref");
    triggers = trigger_set();
    triggers.triggers[1].mask_bits = 0;
    expect(plan_triggers(triggers, plan, diagnostic)
               == Physics2DError::TriggerInvalid,
           "zero mask");
    triggers = trigger_set();
    triggers.triggers[1].enter_enabled = false;
    triggers.triggers[1].exit_enabled = false;
    expect(plan_triggers(triggers, plan, diagnostic)
               == Physics2DError::TriggerInvalid,
           "no event enabled");
    triggers = trigger_set();
    triggers.triggers[2].trigger_id = 1;
    expect(plan_triggers(triggers, plan, diagnostic)
               == Physics2DError::DuplicateId,
           "duplicate trigger");
    expect(diagnostic.index == 2, "duplicate trigger diagnostic");

    triggers = trigger_set();
    triggers.trigger_count = kMaxTriggers;
    for (u32 index = 0; index < kMaxTriggers; ++index) {
        triggers.triggers[index] =
            trigger(index + 1, index + 1, index + 1, true, index % 2 == 0);
    }
    expect(plan_triggers(triggers, plan, diagnostic) == Physics2DError::None,
           "capacity triggers");
    expect(plan.trigger_count == kMaxTriggers && plan.enter_count == 64
               && plan.exit_count == 32 && plan.both_count == 32,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim01_trigger_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "trg01") { success = run_trg01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
