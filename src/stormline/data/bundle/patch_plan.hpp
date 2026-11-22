#ifndef STORMLINE_DATA_BUNDLE_PATCH_PLAN_HPP
#define STORMLINE_DATA_BUNDLE_PATCH_PLAN_HPP

#include "stormline/data/bundle/bundle_manifest.hpp"

namespace stormline::data::bundle {

struct PatchPlan {
    u64 base_generation{0};
    u64 target_generation{0};
    u32 reuse_count{0};
    u32 fetch_count{0};
};

[[nodiscard]] inline BundleError make_patch_plan(
    const BundleManifest& base, const BundleManifest& target,
    PatchPlan& out) noexcept {
    out = PatchPlan{};
    if (base.generation() == 0 || target.generation() == 0
        || base.generation() == target.generation()) {
        return BundleError::PatchConflict;
    }
    u32 reuse = 0;
    u32 fetch = 0;
    for (u32 index = 0; index < target.size(); ++index) {
        ManifestEntry target_entry{};
        if (!target.at(index, target_entry)) {
            continue;
        }
        ManifestEntry base_entry{};
        if (base.find(target_entry.chunk_id, base_entry) == BundleError::None
            && base_entry.fingerprint == target_entry.fingerprint) {
            ++reuse;
        } else {
            ++fetch;
        }
    }
    out.base_generation = base.generation();
    out.target_generation = target.generation();
    out.reuse_count = reuse;
    out.fetch_count = fetch;
    return BundleError::None;
}

}  // namespace stormline::data::bundle

#endif  // STORMLINE_DATA_BUNDLE_PATCH_PLAN_HPP
