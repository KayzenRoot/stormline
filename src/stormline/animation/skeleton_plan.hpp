#ifndef STORMLINE_ANIMATION_SKELETON_PLAN_HPP
#define STORMLINE_ANIMATION_SKELETON_PLAN_HPP

#include "stormline/animation/animation_types.hpp"

namespace stormline::animation {

struct BoneDesc {
    u32 bone_id{0};
    u32 revision{0};
    u32 parent_id{0};
    f32 local_x{0.0f};
    f32 local_y{0.0f};
    f32 local_rotation{0.0f};
};

struct SkeletonDesc {
    u32 skeleton_id{0};
    u32 revision{0};
    u32 bone_count{0};
    std::array<BoneDesc, kMaxBones> bones{};
};

struct SkeletonPlan {
    u32 bone_count{0};
    u32 max_depth{0};
    u32 root_count{0};
};

namespace detail {

inline constexpr u32 kMaxBoneDepth = 16;

}  // namespace detail

[[nodiscard]] inline AnimationError plan_skeleton(
    const SkeletonDesc& skeleton, SkeletonPlan& plan,
    AnimationDiagnostic& diagnostic) noexcept {
    plan = SkeletonPlan{};
    diagnostic = AnimationDiagnostic{};
    if (skeleton.skeleton_id == 0 || skeleton.revision == 0) {
        return detail::set_animation_error(
            diagnostic, AnimationError::InvalidArgument, skeleton.skeleton_id,
            0);
    }
    if (skeleton.bone_count == 0 || skeleton.bone_count > kMaxBones) {
        return detail::set_animation_error(
            diagnostic, AnimationError::SkeletonInvalid, skeleton.skeleton_id,
            0);
    }
    for (u32 index = 0; index < skeleton.bone_count; ++index) {
        const BoneDesc& bone = skeleton.bones[index];
        if (bone.bone_id == 0 || bone.revision == 0) {
            return detail::set_animation_error(
                diagnostic, AnimationError::SkeletonInvalid,
                skeleton.skeleton_id, index);
        }
        if (!detail::finite(bone.local_x) || !detail::finite(bone.local_y)
            || !detail::finite(bone.local_rotation)) {
            return detail::set_animation_error(
                diagnostic, AnimationError::NonFiniteValue,
                skeleton.skeleton_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (skeleton.bones[previous].bone_id == bone.bone_id) {
                return detail::set_animation_error(
                    diagnostic, AnimationError::DuplicateId,
                    skeleton.skeleton_id, index);
            }
        }
    }
    SkeletonPlan computed{};
    computed.bone_count = skeleton.bone_count;
    for (u32 index = 0; index < skeleton.bone_count; ++index) {
        const BoneDesc& bone = skeleton.bones[index];
        if (bone.parent_id == bone.bone_id) {
            return detail::set_animation_error(
                diagnostic, AnimationError::SkeletonInvalid,
                skeleton.skeleton_id, index);
        }
        u32 parent_index = kMaxBones;
        if (bone.parent_id != 0) {
            for (u32 candidate = 0; candidate < skeleton.bone_count;
                 ++candidate) {
                if (skeleton.bones[candidate].bone_id == bone.parent_id) {
                    parent_index = candidate;
                    break;
                }
            }
            if (parent_index == kMaxBones) {
                return detail::set_animation_error(
                    diagnostic, AnimationError::SkeletonInvalid,
                    skeleton.skeleton_id, index);
            }
        } else {
            ++computed.root_count;
        }
        std::array<bool, kMaxBones> seen{};
        u32 depth = 1;
        u32 cursor = index;
        seen[cursor] = true;
        while (skeleton.bones[cursor].parent_id != 0) {
            if (depth >= detail::kMaxBoneDepth) {
                return detail::set_animation_error(
                    diagnostic, AnimationError::DepthExceeded,
                    skeleton.skeleton_id, index);
            }
            cursor = parent_index;
            if (seen[cursor]) {
                return detail::set_animation_error(
                    diagnostic, AnimationError::SkeletonInvalid,
                    skeleton.skeleton_id, index);
            }
            seen[cursor] = true;
            ++depth;
            parent_index = kMaxBones;
            if (skeleton.bones[cursor].parent_id != 0) {
                for (u32 candidate = 0; candidate < skeleton.bone_count;
                     ++candidate) {
                    if (skeleton.bones[candidate].bone_id
                        == skeleton.bones[cursor].parent_id) {
                        parent_index = candidate;
                        break;
                    }
                }
                if (parent_index == kMaxBones) {
                    return detail::set_animation_error(
                        diagnostic, AnimationError::SkeletonInvalid,
                        skeleton.skeleton_id, index);
                }
            }
        }
        if (depth > computed.max_depth) {
            computed.max_depth = depth;
        }
    }
    plan = computed;
    return AnimationError::None;
}

}  // namespace stormline::animation

#endif  // STORMLINE_ANIMATION_SKELETON_PLAN_HPP
