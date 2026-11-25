#ifndef STORMLINE_ANIMATION_SKELETAL_RETARGET_PLAN_HPP
#define STORMLINE_ANIMATION_SKELETAL_RETARGET_PLAN_HPP

#include <array>

#include "stormline/animation/skeletal/skeletal_types.hpp"

namespace stormline::animation::skeletal {

struct RetargetJointPair {
    u32 source_joint{0};
    u32 target_joint{0};
};

struct RetargetProfileDesc {
    u32 retarget_id{0};
    u32 revision{0};
    f32 bind_scale{1.0f};
    u32 pair_count{0};
    std::array<RetargetJointPair, kMaxRetargetPairs> pairs{};
    bool enabled{false};
};

struct RetargetSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 profile_count{0};
    std::array<RetargetProfileDesc, kMaxRetargetProfiles> profiles{};
};

struct RetargetPlan {
    u32 profile_count{0};
    u32 total_pair_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] inline SkeletalError plan_retargets(
    const RetargetSetDesc& retargets, RetargetPlan& plan,
    SkeletalDiagnostic& diagnostic) noexcept {
    plan = RetargetPlan{};
    diagnostic = SkeletalDiagnostic{};
    if (retargets.owner_id == 0 || retargets.revision == 0) {
        return detail::set_skeletal_error(
            diagnostic, SkeletalError::InvalidArgument, retargets.owner_id, 0);
    }
    if (retargets.profile_count > kMaxRetargetProfiles) {
        return detail::set_skeletal_error(
            diagnostic, SkeletalError::CapacityFull, retargets.owner_id, 0);
    }
    for (u32 index = 0; index < retargets.profile_count; ++index) {
        const RetargetProfileDesc& profile = retargets.profiles[index];
        if (profile.retarget_id == 0 || profile.revision == 0) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::RetargetInvalid, retargets.owner_id,
                index);
        }
        if (!detail::finite(profile.bind_scale)
            || !(profile.bind_scale > 0.0f)) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::OutOfRange, retargets.owner_id,
                index);
        }
        if (profile.pair_count > kMaxRetargetPairs) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::CapacityFull, retargets.owner_id,
                index);
        }
        for (u32 pair_index = 0; pair_index < profile.pair_count;
             ++pair_index) {
            const RetargetJointPair& pair = profile.pairs[pair_index];
            if (pair.source_joint == 0 || pair.target_joint == 0) {
                return detail::set_skeletal_error(
                    diagnostic, SkeletalError::RetargetInvalid,
                    retargets.owner_id, index);
            }
            for (u32 previous = 0; previous < pair_index; ++previous) {
                if (profile.pairs[previous].source_joint
                        == pair.source_joint
                    || profile.pairs[previous].target_joint
                        == pair.target_joint) {
                    return detail::set_skeletal_error(
                        diagnostic, SkeletalError::DuplicateId,
                        retargets.owner_id, index);
                }
            }
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (retargets.profiles[previous].retarget_id
                == profile.retarget_id) {
                return detail::set_skeletal_error(
                    diagnostic, SkeletalError::DuplicateId,
                    retargets.owner_id, index);
            }
        }
    }
    plan.profile_count = retargets.profile_count;
    for (u32 index = 0; index < retargets.profile_count; ++index) {
        const RetargetProfileDesc& profile = retargets.profiles[index];
        plan.total_pair_count += profile.pair_count;
        if (profile.enabled) {
            ++plan.enabled_count;
        }
    }
    return SkeletalError::None;
}

}  // namespace stormline::animation::skeletal

#endif  // STORMLINE_ANIMATION_SKELETAL_RETARGET_PLAN_HPP
