#ifndef STORMLINE_ANIMATION_SKELETAL_RAGDOLL_PLAN_HPP
#define STORMLINE_ANIMATION_SKELETAL_RAGDOLL_PLAN_HPP

#include <array>

#include "stormline/animation/skeletal/skeletal_types.hpp"

namespace stormline::animation::skeletal {

struct RagdollProfileDesc {
    u32 ragdoll_id{0};
    u32 revision{0};
    u32 body_mapping_id{0};
    u32 constraint_mapping_id{0};
    f32 activation_weight{1.0f};
    bool auto_activate{false};
    bool enabled{false};
};

struct RagdollSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 profile_count{0};
    std::array<RagdollProfileDesc, kMaxRagdollProfiles> profiles{};
};

struct RagdollPlan {
    u32 profile_count{0};
    u32 auto_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] inline SkeletalError plan_ragdolls(
    const RagdollSetDesc& ragdolls, RagdollPlan& plan,
    SkeletalDiagnostic& diagnostic) noexcept {
    plan = RagdollPlan{};
    diagnostic = SkeletalDiagnostic{};
    if (ragdolls.owner_id == 0 || ragdolls.revision == 0) {
        return detail::set_skeletal_error(
            diagnostic, SkeletalError::InvalidArgument, ragdolls.owner_id, 0);
    }
    if (ragdolls.profile_count > kMaxRagdollProfiles) {
        return detail::set_skeletal_error(
            diagnostic, SkeletalError::CapacityFull, ragdolls.owner_id, 0);
    }
    for (u32 index = 0; index < ragdolls.profile_count; ++index) {
        const RagdollProfileDesc& profile = ragdolls.profiles[index];
        if (profile.ragdoll_id == 0 || profile.revision == 0
            || profile.body_mapping_id == 0
            || profile.constraint_mapping_id == 0) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::RagdollInvalid, ragdolls.owner_id,
                index);
        }
        if (!detail::unit_scalar_in(profile.activation_weight, 0.0f, 1.0f)) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::OutOfRange, ragdolls.owner_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (ragdolls.profiles[previous].ragdoll_id
                == profile.ragdoll_id) {
                return detail::set_skeletal_error(
                    diagnostic, SkeletalError::DuplicateId, ragdolls.owner_id,
                    index);
            }
        }
    }
    plan.profile_count = ragdolls.profile_count;
    for (u32 index = 0; index < ragdolls.profile_count; ++index) {
        const RagdollProfileDesc& profile = ragdolls.profiles[index];
        if (profile.auto_activate) {
            ++plan.auto_count;
        }
        if (profile.enabled) {
            ++plan.enabled_count;
        }
    }
    return SkeletalError::None;
}

}  // namespace stormline::animation::skeletal

#endif  // STORMLINE_ANIMATION_SKELETAL_RAGDOLL_PLAN_HPP
