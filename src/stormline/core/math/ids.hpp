#ifndef STORMLINE_CORE_MATH_IDS_HPP
#define STORMLINE_CORE_MATH_IDS_HPP

#include "stormline/core/math/math_types.hpp"

#include <array>
#include <cstdint>

namespace stormline::core::math {

struct PersistentId {
    std::uint64_t high{0};
    std::uint64_t low{0};

    friend constexpr bool operator==(PersistentId, PersistentId) noexcept = default;
};

struct RuntimeHandle {
    std::uint32_t index{0};
    std::uint32_t generation{0};

    friend constexpr bool operator==(RuntimeHandle, RuntimeHandle) noexcept = default;
};

struct IdBytes {
    std::array<std::uint8_t, 16> bytes{};
};

[[nodiscard]] constexpr bool valid(PersistentId id) noexcept {
    return id.high != 0 || id.low != 0;
}

[[nodiscard]] constexpr bool valid(RuntimeHandle handle) noexcept {
    return handle.index != 0 && handle.generation != 0;
}

[[nodiscard]] constexpr bool handle_is_current(
    RuntimeHandle handle, std::uint32_t current_generation) noexcept {
    return valid(handle) && handle.generation == current_generation;
}

[[nodiscard]] inline IdBytes encode_persistent_id(PersistentId id) noexcept {
    IdBytes result{};
    for (std::size_t index = 0; index < 8; ++index) {
        const unsigned shift = static_cast<unsigned>((7 - index) * 8);
        result.bytes[index] = static_cast<std::uint8_t>((id.high >> shift) & 0xffU);
        result.bytes[8 + index] = static_cast<std::uint8_t>((id.low >> shift) & 0xffU);
    }
    return result;
}

[[nodiscard]] inline MathResult<PersistentId> decode_persistent_id(
    const IdBytes& bytes) noexcept {
    std::uint64_t high = 0;
    std::uint64_t low = 0;
    for (std::size_t index = 0; index < 8; ++index) {
        high = (high << 8) | bytes.bytes[index];
        low = (low << 8) | bytes.bytes[8 + index];
    }
    if (high == 0 && low == 0) {
        return MathResult<PersistentId>{PersistentId{}, MathError::InvalidId};
    }
    return MathResult<PersistentId>{PersistentId{high, low}, MathError::None};
}

}  // namespace stormline::core::math

#endif  // STORMLINE_CORE_MATH_IDS_HPP
