#include "stormline/procedural/rule_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::procedural;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

RuleDesc rule(u32 id, u32 condition, f32 weight, u32 priority, bool enabled) {
    RuleDesc desc{};
    desc.rule_id = id;
    desc.revision = 1;
    desc.condition_code = condition;
    desc.weight = weight;
    desc.priority = priority;
    desc.enabled = enabled;
    return desc;
}

RuleSetDesc rule_set() {
    RuleSetDesc desc{};
    desc.graph_id = 20;
    desc.revision = 1;
    desc.rule_count = 3;
    desc.rules[0] = rule(1, 10, 0.5f, 2, true);
    desc.rules[1] = rule(2, 11, 0.25f, 5, true);
    desc.rules[2] = rule(3, 12, 0.75f, 1, false);
    return desc;
}

bool run_rule01() {
    begin();
    RuleSetDesc rules = rule_set();
    RulePlan plan{};
    ProcDiagnostic diagnostic{};
    expect(plan_rules(rules, plan, diagnostic) == ProcError::None,
           "valid rules");
    expect(plan.rule_count == 3 && plan.enabled_count == 2
               && plan.total_weight == 1.5f && plan.max_priority == 5,
           "valid plan");
    expect(diagnostic.code == ProcError::None, "success diagnostic");
    RulePlan repeat{};
    expect(plan_rules(rules, repeat, diagnostic) == ProcError::None,
           "repeat rules");
    expect(repeat.enabled_count == plan.enabled_count
               && repeat.max_priority == plan.max_priority,
           "deterministic plan");

    rules.rule_count = 0;
    expect(plan_rules(rules, plan, diagnostic) == ProcError::None,
           "empty rules");
    expect(plan.rule_count == 0 && plan.enabled_count == 0,
           "empty plan");

    rules = rule_set();
    rules.graph_id = 0;
    expect(plan_rules(rules, plan, diagnostic)
               == ProcError::InvalidArgument,
           "zero graph");
    expect(plan.rule_count == 0 && plan.total_weight == 0.0f,
           "reset on zero graph");
    rules = rule_set();
    rules.revision = 0;
    expect(plan_rules(rules, plan, diagnostic)
               == ProcError::InvalidArgument,
           "zero revision");
    rules = rule_set();
    rules.rule_count = kMaxRules + 1;
    expect(plan_rules(rules, plan, diagnostic) == ProcError::CapacityFull,
           "rule overflow");

    rules = rule_set();
    rules.rules[1].rule_id = 0;
    expect(plan_rules(rules, plan, diagnostic) == ProcError::RuleInvalid,
           "zero rule id");
    expect(diagnostic.index == 1, "zero rule diagnostic");
    rules = rule_set();
    rules.rules[1].revision = 0;
    expect(plan_rules(rules, plan, diagnostic) == ProcError::RuleInvalid,
           "zero rule revision");
    rules = rule_set();
    rules.rules[1].condition_code = 0;
    expect(plan_rules(rules, plan, diagnostic) == ProcError::RuleInvalid,
           "zero condition");
    rules = rule_set();
    rules.rules[2].rule_id = 1;
    expect(plan_rules(rules, plan, diagnostic) == ProcError::DuplicateId,
           "duplicate rule");
    expect(diagnostic.index == 2, "duplicate rule diagnostic");

    rules = rule_set();
    rules.rules[0].weight = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_rules(rules, plan, diagnostic) == ProcError::OutOfRange,
           "nan weight");
    rules = rule_set();
    rules.rules[0].weight = -0.1f;
    expect(plan_rules(rules, plan, diagnostic) == ProcError::OutOfRange,
           "negative weight");
    rules = rule_set();
    rules.rules[0].weight = 1.1f;
    expect(plan_rules(rules, plan, diagnostic) == ProcError::OutOfRange,
           "weight above one");

    rules = rule_set();
    rules.rule_count = kMaxRules;
    for (u32 index = 0; index < kMaxRules; ++index) {
        rules.rules[index] = rule(index + 1, index + 1, 1.0f, index,
                                  index % 2 == 0);
    }
    expect(plan_rules(rules, plan, diagnostic) == ProcError::None,
           "capacity rules");
    expect(plan.rule_count == kMaxRules && plan.enabled_count == 16
               && plan.total_weight == 32.0f && plan.max_priority == 31,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world05_rule_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "rule01") { success = run_rule01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
