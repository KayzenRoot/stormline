#ifndef STORMLINE_GRAPHICS_SHADER_SHADER_INCREMENTAL_HPP
#define STORMLINE_GRAPHICS_SHADER_SHADER_INCREMENTAL_HPP

#include "stormline/graphics/shader/shader_parser.hpp"

#include <algorithm>

namespace stormline::graphics::shader {

struct DependencyRef {
    u64 id{0};
    u64 revision{0};
};

struct DependencySet {
    u32 count{0};
    std::array<DependencyRef, kMaxDependencies> dependencies{};
};

struct IncrementalState {
    u64 dependency_fingerprint{0};
    u64 cache_key{0};
};

namespace detail {

inline constexpr u64 kDependencyFnvOffset = 1469598103934665603ULL;
inline constexpr u64 kDependencyFnvPrime = 1099511628211ULL;

inline void dependency_hash_u64(u64& hash, u64 value) noexcept {
    hash ^= static_cast<u8>((value >> 56) & 0xFFu);
    hash *= kDependencyFnvPrime;
    hash ^= static_cast<u8>((value >> 48) & 0xFFu);
    hash *= kDependencyFnvPrime;
    hash ^= static_cast<u8>((value >> 40) & 0xFFu);
    hash *= kDependencyFnvPrime;
    hash ^= static_cast<u8>((value >> 32) & 0xFFu);
    hash *= kDependencyFnvPrime;
    hash ^= static_cast<u8>((value >> 24) & 0xFFu);
    hash *= kDependencyFnvPrime;
    hash ^= static_cast<u8>((value >> 16) & 0xFFu);
    hash *= kDependencyFnvPrime;
    hash ^= static_cast<u8>((value >> 8) & 0xFFu);
    hash *= kDependencyFnvPrime;
    hash ^= static_cast<u8>(value & 0xFFu);
    hash *= kDependencyFnvPrime;
}

}  // namespace detail

[[nodiscard]] inline ShaderError dependency_fingerprint(
    const DependencySet& dependencies, u64& out) noexcept {
    out = 0;
    if (dependencies.count == 0 || dependencies.count > kMaxDependencies) {
        return ShaderError::InvalidArgument;
    }
    std::array<DependencyRef, kMaxDependencies> sorted{};
    for (u32 index = 0; index < dependencies.count; ++index) {
        const DependencyRef& dependency = dependencies.dependencies[index];
        if (dependency.id == 0 || dependency.revision == 0) {
            return ShaderError::InvalidArgument;
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (dependencies.dependencies[previous].id == dependency.id) {
                return ShaderError::InvalidArgument;
            }
        }
        sorted[index] = dependency;
    }
    std::sort(sorted.begin(), sorted.begin() + dependencies.count,
              [](const DependencyRef& left, const DependencyRef& right) {
                  return left.id < right.id;
              });
    u64 hash = detail::kDependencyFnvOffset;
    for (u32 index = 0; index < dependencies.count; ++index) {
        detail::dependency_hash_u64(hash, sorted[index].id);
        detail::dependency_hash_u64(hash, sorted[index].revision);
    }
    if (hash == 0) {
        return ShaderError::InvalidArgument;
    }
    out = hash;
    return ShaderError::None;
}

[[nodiscard]] inline ShaderError plan_incremental(
    const DependencySet& dependencies, const IncrementalState& previous,
    bool& out_rebuild, u64& out_fingerprint) noexcept {
    out_rebuild = true;
    out_fingerprint = 0;
    u64 fingerprint = 0;
    const ShaderError status = dependency_fingerprint(dependencies, fingerprint);
    if (status != ShaderError::None) {
        return status;
    }
    out_fingerprint = fingerprint;
    out_rebuild = previous.dependency_fingerprint == 0
        || previous.cache_key == 0
        || previous.dependency_fingerprint != fingerprint;
    return ShaderError::None;
}

}  // namespace stormline::graphics::shader

#endif  // STORMLINE_GRAPHICS_SHADER_SHADER_INCREMENTAL_HPP
