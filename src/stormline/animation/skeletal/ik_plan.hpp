#ifndef STORMLINE_ANIMATION_SKELETAL_IK_PLAN_HPP
#define STORMLINE_ANIMATION_SKELETAL_IK_PLAN_HPP

#include <array>

#include "stormline/animation/skeletal/skeletal_types.hpp"

namespace stormline::animation::skeletal {

struct IkChainDesc {
    u32 chain_id{0};
    u32 revision{0};
    u32 bone_count{0};
    u32 iterations{0};
    f32 tolerance{0.0f};
    f32 target_weight{1.0f};
    bool enabled{false};
};

struct IkSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 chain_count{0};
    std::array<IkChainDesc, kMaxIkChains> chains{};
};

struct IkPlan {
    u32 chain_count{0};
    u32 total_bone_count{0};
    u32 max_iterations{0};
    u32 enabled_count{0};
};

[[nodiscard]] inline SkeletalError plan_ik(
    const IkSetDesc& ik, IkPlan& plan,
    SkeletalDiagnostic& diagnostic) noexcept {
    plan = IkPlan{};
    diagnostic = SkeletalDiagnostic{};
    if (ik.owner_id == 0 || ik.revision == 0) {
        return detail::set_skeletal_error(
            diagnostic, SkeletalError::InvalidArgument, ik.owner_id, 0);
    }
    if (ik.chain_count > kMaxIkChains) {
        return detail::set_skeletal_error(
            diagnostic, SkeletalError::CapacityFull, ik.owner_id, 0);
    }
    for (u32 index = 0; index < ik.chain_count; ++index) {
        const IkChainDesc& chain = ik.chains[index];
        if (chain.chain_id == 0 || chain.revision == 0) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::IkInvalid, ik.owner_id, index);
        }
        if (chain.bone_count == 0 || chain.bone_count > 16
            || chain.iterations > kMaxIkIterations) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::OutOfRange, ik.owner_id, index);
        }
        if (!detail::finite(chain.tolerance)
            || !(chain.tolerance >= 0.0f)
            || !detail::unit_scalar_in(chain.target_weight, 0.0f, 1.0f)) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::OutOfRange, ik.owner_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (ik.chains[previous].chain_id == chain.chain_id) {
                return detail::set_skeletal_error(
                    diagnostic, SkeletalError::DuplicateId, ik.owner_id,
                    index);
            }
        }
    }
    plan.chain_count = ik.chain_count;
    for (u32 index = 0; index < ik.chain_count; ++index) {
        const IkChainDesc& chain = ik.chains[index];
        plan.total_bone_count += chain.bone_count;
        if (chain.iterations > plan.max_iterations) {
            plan.max_iterations = chain.iterations;
        }
        if (chain.enabled) {
            ++plan.enabled_count;
        }
    }
    return SkeletalError::None;
}

}  // namespace stormline::animation::skeletal

#endif  // STORMLINE_ANIMATION_SKELETAL_IK_PLAN_HPP
