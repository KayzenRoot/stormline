#ifndef STORMLINE_DATA_BUNDLE_COOK_PLAN_HPP
#define STORMLINE_DATA_BUNDLE_COOK_PLAN_HPP

#include "stormline/data/bundle/bundle_types.hpp"

#include <span>

namespace stormline::data::bundle {

[[nodiscard]] inline BundleError validate_target(
    const TargetProfile& target) noexcept {
    if (target.profile_id == 0) {
        return BundleError::InvalidTarget;
    }
    if ((target.feature_flags & ~static_cast<u32>(0x7F)) != 0) {
        return BundleError::UnsupportedFeature;
    }
    if (target.quality_tier < 1 || target.quality_tier > 3) {
        return BundleError::InvalidTarget;
    }
    return BundleError::None;
}

[[nodiscard]] inline BundleError make_cook_plan(
    const TargetProfile& target, std::span<const CookAsset> assets,
    CookPlan& out) noexcept {
    out = CookPlan{};
    const BundleError target_status = validate_target(target);
    if (target_status != BundleError::None) {
        return target_status;
    }
    if (assets.empty() || assets.size() > kMaxCookAssets) {
        return BundleError::InvalidArgument;
    }
    for (u32 index = 0; index < static_cast<u32>(assets.size()); ++index) {
        if (!registry::valid(assets[index].asset) || assets[index].source_revision == 0) {
            return BundleError::InvalidArgument;
        }
        for (u32 earlier = 0; earlier < index; ++earlier) {
            if (assets[earlier].asset.high == assets[index].asset.high
                && assets[earlier].asset.low == assets[index].asset.low) {
                return BundleError::DuplicateId;
            }
        }
    }
    out.profile_id = target.profile_id;
    out.asset_count = static_cast<u32>(assets.size());
    out.estimated_bytes = out.asset_count * kMaxChunkBytes;
    out.warning_count = 0;
    return BundleError::None;
}

}  // namespace stormline::data::bundle

#endif  // STORMLINE_DATA_BUNDLE_COOK_PLAN_HPP
