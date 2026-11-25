#ifndef STORMLINE_ANIMATION_SKELETAL_COMPRESSION_PLAN_HPP
#define STORMLINE_ANIMATION_SKELETAL_COMPRESSION_PLAN_HPP

#include <array>

#include "stormline/animation/skeletal/skeletal_types.hpp"

namespace stormline::animation::skeletal {

struct CompressionProfileDesc {
    u32 profile_id{0};
    u32 revision{0};
    u32 translation_bits{0};
    u32 rotation_bits{0};
    u32 scale_bits{0};
    u32 keyframe_interval{0};
    bool lossless{false};
    bool enabled{false};
};

struct CompressionSetDesc {
    u32 owner_id{0};
    u32 revision{0};
    u32 profile_count{0};
    std::array<CompressionProfileDesc, kMaxCompressionProfiles> profiles{};
};

struct CompressionPlan {
    u32 profile_count{0};
    u32 lossless_count{0};
    u32 enabled_count{0};
};

[[nodiscard]] inline SkeletalError plan_compression(
    const CompressionSetDesc& compression, CompressionPlan& plan,
    SkeletalDiagnostic& diagnostic) noexcept {
    plan = CompressionPlan{};
    diagnostic = SkeletalDiagnostic{};
    if (compression.owner_id == 0 || compression.revision == 0) {
        return detail::set_skeletal_error(
            diagnostic, SkeletalError::InvalidArgument, compression.owner_id,
            0);
    }
    if (compression.profile_count > kMaxCompressionProfiles) {
        return detail::set_skeletal_error(
            diagnostic, SkeletalError::CapacityFull, compression.owner_id, 0);
    }
    for (u32 index = 0; index < compression.profile_count; ++index) {
        const CompressionProfileDesc& profile = compression.profiles[index];
        if (profile.profile_id == 0 || profile.revision == 0) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::CompressionInvalid,
                compression.owner_id, index);
        }
        if (profile.translation_bits == 0 || profile.translation_bits > 32
            || profile.rotation_bits == 0 || profile.rotation_bits > 32
            || profile.scale_bits == 0 || profile.scale_bits > 32
            || profile.keyframe_interval == 0
            || profile.keyframe_interval > kMaxTickWindow) {
            return detail::set_skeletal_error(
                diagnostic, SkeletalError::OutOfRange, compression.owner_id,
                index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (compression.profiles[previous].profile_id
                == profile.profile_id) {
                return detail::set_skeletal_error(
                    diagnostic, SkeletalError::DuplicateId,
                    compression.owner_id, index);
            }
        }
    }
    plan.profile_count = compression.profile_count;
    for (u32 index = 0; index < compression.profile_count; ++index) {
        const CompressionProfileDesc& profile = compression.profiles[index];
        if (profile.lossless) {
            ++plan.lossless_count;
        }
        if (profile.enabled) {
            ++plan.enabled_count;
        }
    }
    return SkeletalError::None;
}

}  // namespace stormline::animation::skeletal

#endif  // STORMLINE_ANIMATION_SKELETAL_COMPRESSION_PLAN_HPP
