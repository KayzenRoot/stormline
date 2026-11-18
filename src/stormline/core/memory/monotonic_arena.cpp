#include "stormline/core/memory/monotonic_arena.hpp"

#include <algorithm>
#include <thread>

namespace stormline::core::memory {
namespace {

bool on_owner_thread(const std::thread::id& owner) noexcept {
    return std::this_thread::get_id() == owner;
}

constexpr bool is_power_of_two(std::size_t value) noexcept {
    return value != 0 && (value & (value - 1)) == 0;
}

}  // namespace

MonotonicArena::MonotonicArena(std::size_t capacity, std::size_t backing_alignment,
                               std::pmr::memory_resource* resource) noexcept
    : capacity_(capacity),
      backing_alignment_(backing_alignment),
      owner_thread_(std::this_thread::get_id()) {
    if (capacity_ == 0) {
        init_error_ = ArenaError::InvalidCapacity;
        capacity_ = 0;
        return;
    }
    if (!is_power_of_two(backing_alignment_)) {
        init_error_ = ArenaError::InvalidAlignment;
        capacity_ = 0;
        return;
    }

    const MemoryError error = MemoryBlock::allocate(
        resource, capacity_, backing_alignment_, MemoryDomain::Frame, backing_);
    if (error != MemoryError::None) {
        init_error_ = error == MemoryError::OutOfMemory ? ArenaError::OutOfMemory
                                                        : ArenaError::NotInitialized;
        capacity_ = 0;
    }
}

ArenaError MonotonicArena::allocate(std::size_t bytes, std::size_t alignment,
                                    ArenaSlice& out) noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return ArenaError::WrongThread;
        }
        if (!valid()) {
            return init_error_ == ArenaError::None ? ArenaError::NotInitialized : init_error_;
        }
        if (bytes == 0) {
            return ArenaError::InvalidSize;
        }
        if (!is_power_of_two(alignment)) {
            return ArenaError::InvalidAlignment;
        }
        if (alignment > backing_alignment_) {
            return ArenaError::AlignmentExceedsBacking;
        }

        const std::size_t padding = (alignment - (offset_ % alignment)) % alignment;
        if (padding > capacity_ - offset_) {
            return ArenaError::OutOfMemory;
        }
        const std::size_t aligned = offset_ + padding;
        if (bytes > capacity_ - aligned) {
            return ArenaError::OutOfMemory;
        }

        out.data = backing_.data() + aligned;
        out.size = bytes;
        out.offset = aligned;
        offset_ = aligned + bytes;
        high_water_ = std::max(high_water_, offset_);
        return ArenaError::None;
    } catch (...) {
        return ArenaError::InternalFailure;
    }
}

ArenaError MonotonicArena::reset() noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return ArenaError::WrongThread;
        }
        if (!valid()) {
            return init_error_ == ArenaError::None ? ArenaError::NotInitialized : init_error_;
        }
        offset_ = 0;
        return ArenaError::None;
    } catch (...) {
        return ArenaError::InternalFailure;
    }
}

std::size_t MonotonicArena::capacity() const noexcept {
    return capacity_;
}

std::size_t MonotonicArena::used() const noexcept {
    return offset_;
}

std::size_t MonotonicArena::remaining() const noexcept {
    return capacity_ - offset_;
}

std::size_t MonotonicArena::high_water() const noexcept {
    return high_water_;
}

bool MonotonicArena::valid() const noexcept {
    return init_error_ == ArenaError::None && backing_.valid();
}

}  // namespace stormline::core::memory
