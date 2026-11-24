#ifndef STORMLINE_PROCEDURAL_RULE_PLAN_HPP
#define STORMLINE_PROCEDURAL_RULE_PLAN_HPP

#include <array>

#include "stormline/procedural/procedural_types.hpp"

namespace stormline::procedural {

struct RuleDesc {
    u32 rule_id{0};
    u32 revision{0};
    u32 condition_code{0};
    f32 weight{0.0f};
    u32 priority{0};
    bool enabled{false};
};

struct RuleSetDesc {
    u32 graph_id{0};
    u32 revision{0};
    u32 rule_count{0};
    std::array<RuleDesc, kMaxRules> rules{};
};

struct RulePlan {
    u32 rule_count{0};
    u32 enabled_count{0};
    f32 total_weight{0.0f};
    u32 max_priority{0};
};

[[nodiscard]] inline ProcError plan_rules(
    const RuleSetDesc& rules, RulePlan& plan,
    ProcDiagnostic& diagnostic) noexcept {
    plan = RulePlan{};
    diagnostic = ProcDiagnostic{};
    if (rules.graph_id == 0 || rules.revision == 0) {
        return detail::set_proc_error(
            diagnostic, ProcError::InvalidArgument, rules.graph_id, 0);
    }
    if (rules.rule_count > kMaxRules) {
        return detail::set_proc_error(
            diagnostic, ProcError::CapacityFull, rules.graph_id, 0);
    }
    for (u32 index = 0; index < rules.rule_count; ++index) {
        const RuleDesc& rule = rules.rules[index];
        if (rule.rule_id == 0 || rule.revision == 0
            || rule.condition_code == 0) {
            return detail::set_proc_error(
                diagnostic, ProcError::RuleInvalid, rules.graph_id, index);
        }
        if (!detail::finite(rule.weight) || !(rule.weight >= 0.0f)
            || !(rule.weight <= 1.0f)) {
            return detail::set_proc_error(
                diagnostic, ProcError::OutOfRange, rules.graph_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (rules.rules[previous].rule_id == rule.rule_id) {
                return detail::set_proc_error(
                    diagnostic, ProcError::DuplicateId, rules.graph_id,
                    index);
            }
        }
    }
    plan.rule_count = rules.rule_count;
    if (rules.rule_count == 0) {
        return ProcError::None;
    }
    for (u32 index = 0; index < rules.rule_count; ++index) {
        const RuleDesc& rule = rules.rules[index];
        if (rule.enabled) {
            ++plan.enabled_count;
        }
        plan.total_weight += rule.weight;
        if (!(plan.total_weight <= 32.0f)) {
            plan = RulePlan{};
            return detail::set_proc_error(
                diagnostic, ProcError::OutOfRange, rules.graph_id, index);
        }
        if (rule.priority > plan.max_priority) {
            plan.max_priority = rule.priority;
        }
    }
    return ProcError::None;
}

}  // namespace stormline::procedural

#endif  // STORMLINE_PROCEDURAL_RULE_PLAN_HPP
