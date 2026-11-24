#ifndef STORMLINE_PROCEDURAL_SEED_PLAN_HPP
#define STORMLINE_PROCEDURAL_SEED_PLAN_HPP

#include <array>

#include "stormline/procedural/procedural_types.hpp"

namespace stormline::procedural {

struct SeedDomainDesc {
    u32 domain_id{0};
    u32 derivation_version{0};
    u32 channel_count{0};
};

struct SeedSetDesc {
    u32 project_id{0};
    u32 graph_id{0};
    u64 seed_high{0};
    u64 seed_low{0};
    u32 domain_count{0};
    std::array<SeedDomainDesc, kMaxSeedDomains> domains{};
};

struct SeedPlan {
    u32 domain_count{0};
    u32 total_channels{0};
    u64 seed_high{0};
    u64 seed_low{0};
};

[[nodiscard]] inline ProcError plan_seed_domains(
    const SeedSetDesc& seed, SeedPlan& plan,
    ProcDiagnostic& diagnostic) noexcept {
    plan = SeedPlan{};
    diagnostic = ProcDiagnostic{};
    if (seed.project_id == 0 || seed.graph_id == 0) {
        return detail::set_proc_error(
            diagnostic, ProcError::InvalidArgument, seed.project_id, 0);
    }
    if (seed.seed_high == 0 && seed.seed_low == 0) {
        return detail::set_proc_error(
            diagnostic, ProcError::SeedInvalid, seed.project_id, 0);
    }
    if (seed.domain_count == 0) {
        return detail::set_proc_error(
            diagnostic, ProcError::SeedInvalid, seed.project_id, 0);
    }
    if (seed.domain_count > kMaxSeedDomains) {
        return detail::set_proc_error(
            diagnostic, ProcError::CapacityFull, seed.project_id, 0);
    }
    for (u32 index = 0; index < seed.domain_count; ++index) {
        const SeedDomainDesc& domain = seed.domains[index];
        if (domain.domain_id == 0 || domain.derivation_version == 0) {
            return detail::set_proc_error(
                diagnostic, ProcError::SeedInvalid, seed.project_id, index);
        }
        if (domain.channel_count == 0 || domain.channel_count > 8) {
            return detail::set_proc_error(
                diagnostic, ProcError::OutOfRange, seed.project_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (seed.domains[previous].domain_id == domain.domain_id) {
                return detail::set_proc_error(
                    diagnostic, ProcError::DuplicateId, seed.project_id,
                    index);
            }
        }
    }
    plan.domain_count = seed.domain_count;
    plan.seed_high = seed.seed_high;
    plan.seed_low = seed.seed_low;
    for (u32 index = 0; index < seed.domain_count; ++index) {
        if (!detail::checked_add_u32(plan.total_channels,
                                     seed.domains[index].channel_count)
            || plan.total_channels > 128) {
            plan = SeedPlan{};
            return detail::set_proc_error(
                diagnostic, ProcError::OutOfRange, seed.project_id, index);
        }
    }
    return ProcError::None;
}

}  // namespace stormline::procedural

#endif  // STORMLINE_PROCEDURAL_SEED_PLAN_HPP
