#ifndef STORMLINE_PROCEDURAL_GENERATOR_PLAN_HPP
#define STORMLINE_PROCEDURAL_GENERATOR_PLAN_HPP

#include <array>

#include "stormline/procedural/procedural_types.hpp"

namespace stormline::procedural {

struct ContentGeneratorDesc {
    u32 generator_id{0};
    u32 revision{0};
    GeneratorCategory category{GeneratorCategory::Biome};
    u32 seed_domain_id{0};
    u32 output_cap{0};
};

struct GeneratorSetDesc {
    u32 graph_id{0};
    u32 revision{0};
    u32 generator_count{0};
    std::array<ContentGeneratorDesc, kMaxContentGenerators> generators{};
};

struct GeneratorPlan {
    u32 generator_count{0};
    u32 biome_count{0};
    u32 geometry_count{0};
    u32 placement_count{0};
    u32 rule_count{0};
    u32 total_output_cap{0};
};

[[nodiscard]] inline ProcError plan_generators(
    const GeneratorSetDesc& generators, GeneratorPlan& plan,
    ProcDiagnostic& diagnostic) noexcept {
    plan = GeneratorPlan{};
    diagnostic = ProcDiagnostic{};
    if (generators.graph_id == 0 || generators.revision == 0) {
        return detail::set_proc_error(
            diagnostic, ProcError::InvalidArgument, generators.graph_id, 0);
    }
    if (generators.generator_count > kMaxContentGenerators) {
        return detail::set_proc_error(
            diagnostic, ProcError::CapacityFull, generators.graph_id, 0);
    }
    for (u32 index = 0; index < generators.generator_count; ++index) {
        const ContentGeneratorDesc& generator = generators.generators[index];
        if (generator.generator_id == 0 || generator.revision == 0
            || generator.seed_domain_id == 0
            || !detail::valid_generator_category(generator.category)) {
            return detail::set_proc_error(
                diagnostic, ProcError::GeneratorInvalid,
                generators.graph_id, index);
        }
        if (generator.output_cap == 0
            || generator.output_cap > kMaxGeneratorOutputCap) {
            return detail::set_proc_error(
                diagnostic, ProcError::OutOfRange, generators.graph_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (generators.generators[previous].generator_id
                == generator.generator_id) {
                return detail::set_proc_error(
                    diagnostic, ProcError::DuplicateId, generators.graph_id,
                    index);
            }
        }
    }
    plan.generator_count = generators.generator_count;
    for (u32 index = 0; index < generators.generator_count; ++index) {
        const ContentGeneratorDesc& generator = generators.generators[index];
        switch (generator.category) {
            case GeneratorCategory::Biome:
                ++plan.biome_count;
                break;
            case GeneratorCategory::Geometry:
                ++plan.geometry_count;
                break;
            case GeneratorCategory::Placement:
                ++plan.placement_count;
                break;
            case GeneratorCategory::Rule:
                ++plan.rule_count;
                break;
        }
        if (!detail::checked_add_u32(plan.total_output_cap,
                                     generator.output_cap)
            || plan.total_output_cap > kMaxTotalOutputCap) {
            plan = GeneratorPlan{};
            return detail::set_proc_error(
                diagnostic, ProcError::OutOfRange, generators.graph_id,
                index);
        }
    }
    return ProcError::None;
}

}  // namespace stormline::procedural

#endif  // STORMLINE_PROCEDURAL_GENERATOR_PLAN_HPP
