#ifndef STORMLINE_ANIMATION_SKELETAL_SYNC_PLAN_HPP
#define STORMLINE_ANIMATION_SKELETAL_SYNC_PLAN_HPP

#include <array>

#include "stormline/animation/skeletal/skeletal_types.hpp"

namespace stormline::animation::skeletal {

struct SyncGroupDesc {
    u32 group_id{0};
    u32 revision{0};
    u32 leader_id{0};
    u32 member_count{0};
    f32 phase{0.0f};
    bool enabled{false};
};

struct SyncSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 group_count{0};
    std::array<SyncGroupDesc, kMaxSyncGroups> groups{};
};

struct SyncPlan {
    u32 group_count{0};
    u32 phased_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] inline SkeletalError plan_sync(
    const SyncSetDesc& sync, SyncPlan& plan,
    SkeletalDiagnostic& diagnostic) noexcept {
    plan = SyncPlan{};
    diagnostic = SkeletalDiagnostic{};
    if (sync.owner_id == 0 || sync.revision == 0) {
        return detail::set_skeletal_error(
            diagnostic, SkeletalError::InvalidArgument, sync.owner_id, 0);
    }
    if (sync.group_count > kMaxSyncGroups) {
        return detail::set_skeletal_error(
            diagnostic, SkeletalError::CapacityFull, sync.owner_id, 0);
    }
    for (u32 index = 0; index < sync.group_count; ++index) {
        const SyncGroupDesc& group = sync.groups[index];
        if (group.group_id == 0 || group.revision == 0
            || group.leader_id == 0) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::SyncInvalid, sync.owner_id, index);
        }
        if (group.member_count == 0 || group.member_count > 32
            || !detail::unit_scalar_in(group.phase, 0.0f, 1.0f)) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::OutOfRange, sync.owner_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (sync.groups[previous].group_id == group.group_id) {
                return detail::set_skeletal_error(
                    diagnostic, SkeletalError::DuplicateId, sync.owner_id,
                    index);
            }
        }
    }
    plan.group_count = sync.group_count;
    for (u32 index = 0; index < sync.group_count; ++index) {
        const SyncGroupDesc& group = sync.groups[index];
        if (group.phase != 0.0f) {
            ++plan.phased_count;
        }
        if (group.enabled) {
            ++plan.enabled_count;
        }
    }
    return SkeletalError::None;
}

}  // namespace stormline::animation::skeletal

#endif  // STORMLINE_ANIMATION_SKELETAL_SYNC_PLAN_HPP
