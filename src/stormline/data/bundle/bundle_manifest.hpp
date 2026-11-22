#ifndef STORMLINE_DATA_BUNDLE_BUNDLE_MANIFEST_HPP
#define STORMLINE_DATA_BUNDLE_BUNDLE_MANIFEST_HPP

#include "stormline/data/bundle/stream_window.hpp"

namespace stormline::data::bundle {

[[nodiscard]] inline u64 fnv1a64(std::span<const u8> bytes) noexcept {
    u64 value = 14695981039346656037ULL;
    for (const u8 byte : bytes) {
        value ^= byte;
        value *= 1099511628211ULL;
    }
    return value;
}

[[nodiscard]] inline BundleError verify_chunk(
    const BundleManifest& manifest, u64 chunk_id,
    std::span<const u8> bytes) noexcept {
    ManifestEntry entry{};
    const BundleError status = manifest.find(chunk_id, entry);
    if (status != BundleError::None) {
        return status;
    }
    if (bytes.size() != entry.length) {
        return BundleError::InvalidArgument;
    }
    if (fnv1a64(bytes) != entry.fingerprint) {
        return BundleError::FingerprintMismatch;
    }
    return BundleError::None;
}

}  // namespace stormline::data::bundle

#endif  // STORMLINE_DATA_BUNDLE_BUNDLE_MANIFEST_HPP
