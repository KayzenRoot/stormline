#ifndef STORMLINE_GRAPHICS_SHADER_SHADER_CACHE_HPP
#define STORMLINE_GRAPHICS_SHADER_SHADER_CACHE_HPP

#include "stormline/graphics/shader/shader_variant.hpp"

namespace stormline::graphics::shader {

struct CacheKey {
    u64 value{0};
};

struct CacheEntry {
    CacheKey key{};
    u64 payload_fingerprint{0};
};

namespace detail {

inline constexpr u64 kCacheFnvOffset = 1469598103934665603ULL;
inline constexpr u64 kCacheFnvPrime = 1099511628211ULL;

inline void hash_byte(u64& hash, u8 value) noexcept {
    hash ^= value;
    hash *= kCacheFnvPrime;
}

inline void hash_u64(u64& hash, u64 value) noexcept {
    hash_byte(hash, static_cast<u8>((value >> 56) & 0xFFu));
    hash_byte(hash, static_cast<u8>((value >> 48) & 0xFFu));
    hash_byte(hash, static_cast<u8>((value >> 40) & 0xFFu));
    hash_byte(hash, static_cast<u8>((value >> 32) & 0xFFu));
    hash_byte(hash, static_cast<u8>((value >> 24) & 0xFFu));
    hash_byte(hash, static_cast<u8>((value >> 16) & 0xFFu));
    hash_byte(hash, static_cast<u8>((value >> 8) & 0xFFu));
    hash_byte(hash, static_cast<u8>(value & 0xFFu));
}

inline void hash_u32(u64& hash, u32 value) noexcept {
    hash_byte(hash, static_cast<u8>((value >> 24) & 0xFFu));
    hash_byte(hash, static_cast<u8>((value >> 16) & 0xFFu));
    hash_byte(hash, static_cast<u8>((value >> 8) & 0xFFu));
    hash_byte(hash, static_cast<u8>(value & 0xFFu));
}

inline void hash_u16(u64& hash, u16 value) noexcept {
    hash_byte(hash, static_cast<u8>((value >> 8) & 0xFFu));
    hash_byte(hash, static_cast<u8>(value & 0xFFu));
}

}  // namespace detail

[[nodiscard]] inline ShaderError make_cache_key(
    const VariantKey& variant, u64 dependency_fingerprint,
    CacheKey& out) noexcept {
    out = CacheKey{};
    u64 hash = detail::kCacheFnvOffset;
    detail::hash_u64(hash, variant.source_fingerprint);
    detail::hash_u32(hash, variant.recipe_version);
    detail::hash_u16(hash, variant.switch_bits);
    detail::hash_byte(hash, static_cast<u8>(variant.stage));
    detail::hash_u64(hash, dependency_fingerprint);
    if (hash == 0) {
        return ShaderError::InvalidArgument;
    }
    out.value = hash;
    return ShaderError::None;
}

class ShaderCache final {
public:
    ShaderCache() noexcept = default;

    [[nodiscard]] ShaderError put(
        const CacheKey& key, u64 payload_fingerprint) noexcept {
        if (key.value == 0 || payload_fingerprint == 0) {
            return ShaderError::InvalidArgument;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (entries_[index].key.value == key.value) {
                return entries_[index].payload_fingerprint == payload_fingerprint
                    ? ShaderError::None
                    : ShaderError::CacheMismatch;
            }
        }
        if (size_ >= kMaxCacheEntries) {
            return ShaderError::CacheFull;
        }
        entries_[size_] = CacheEntry{key, payload_fingerprint};
        ++size_;
        return ShaderError::None;
    }

    [[nodiscard]] ShaderError get(
        const CacheKey& key, u64& out_payload) const noexcept {
        out_payload = 0;
        if (key.value == 0) {
            return ShaderError::InvalidArgument;
        }
        for (u32 index = 0; index < size_; ++index) {
            if (entries_[index].key.value == key.value) {
                out_payload = entries_[index].payload_fingerprint;
                return ShaderError::None;
            }
        }
        return ShaderError::CacheMiss;
    }

    [[nodiscard]] u32 size() const noexcept { return size_; }

    void clear() noexcept {
        entries_ = {};
        size_ = 0;
    }

private:
    std::array<CacheEntry, kMaxCacheEntries> entries_{};
    u32 size_{0};
};

}  // namespace stormline::graphics::shader

#endif  // STORMLINE_GRAPHICS_SHADER_SHADER_CACHE_HPP
