#pragma once

#include "stormline/core/memory/memory_block.hpp"

#include <cstddef>
#include <cstdint>
#include <memory_resource>
#include <thread>

namespace stormline::core::memory {

enum class ArenaError : std::uint8_t {
    None,
    InvalidCapacity,
    InvalidSize,
    InvalidAlignment,
    AlignmentExceedsBacking,
    OutOfMemory,
    NotInitialized,
    WrongThread,
    InternalFailure
};

struct ArenaSlice final {
    std::byte* data{nullptr};
    std::size_t size{0};
    std::size_t offset{0};
};

class MonotonicArena final {
public:
    static constexpr std::size_t default_capacity = 64 * 1024;
    static constexpr std::size_t default_backing_alignment = 64;

    explicit MonotonicArena(std::size_t capacity = default_capacity,
                            std::size_t backing_alignment = default_backing_alignment,
                            std::pmr::memory_resource* resource = nullptr) noexcept;
    ~MonotonicArena() noexcept = default;

    MonotonicArena(const MonotonicArena&) = delete;
    MonotonicArena& operator=(const MonotonicArena&) = delete;
    MonotonicArena(MonotonicArena&&) = delete;
    MonotonicArena& operator=(MonotonicArena&&) = delete;

    [[nodiscard]] ArenaError allocate(std::size_t bytes, std::size_t alignment,
                                      ArenaSlice& out) noexcept;
    [[nodiscard]] ArenaError reset() noexcept;
    [[nodiscard]] std::size_t capacity() const noexcept;
    [[nodiscard]] std::size_t used() const noexcept;
    [[nodiscard]] std::size_t remaining() const noexcept;
    [[nodiscard]] std::size_t high_water() const noexcept;
    [[nodiscard]] bool valid() const noexcept;

private:
    MemoryBlock backing_;
    std::size_t capacity_{0};
    std::size_t offset_{0};
    std::size_t high_water_{0};
    std::size_t backing_alignment_{default_backing_alignment};
    std::thread::id owner_thread_;
    ArenaError init_error_{ArenaError::None};
};

}  // namespace stormline::core::memory
