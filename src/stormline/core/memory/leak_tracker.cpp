#include "stormline/core/memory/leak_tracker.hpp"

#include <thread>

namespace stormline::core::memory {
namespace {

bool on_owner_thread(const std::thread::id& owner) noexcept {
    return std::this_thread::get_id() == owner;
}

}  // namespace

LeakTracker::LeakTracker() noexcept : owner_thread_(std::this_thread::get_id()) {}

LeakError LeakTracker::track(std::size_t bytes, LeakToken& token) noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return LeakError::WrongThread;
        }
        if (bytes == 0) {
            return LeakError::InvalidBytes;
        }
        for (std::size_t index = 0; index < slots_.size(); ++index) {
            Slot& slot = slots_[index];
            if (slot.active) {
                continue;
            }
            ++slot.generation;
            if (slot.generation == 0) {
                slot.generation = 1;
            }
            slot.bytes = bytes;
            slot.active = true;
            token.index = static_cast<std::uint32_t>(index);
            token.generation = slot.generation;
            ++live_allocations_;
            live_bytes_ += bytes;
            if (live_allocations_ > peak_allocations_) {
                peak_allocations_ = live_allocations_;
            }
            if (live_bytes_ > peak_bytes_) {
                peak_bytes_ = live_bytes_;
            }
            return LeakError::None;
        }
        return LeakError::CapacityExceeded;
    } catch (...) {
        return LeakError::InternalFailure;
    }
}

LeakError LeakTracker::release(LeakToken token) noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return LeakError::WrongThread;
        }
        if (token.index >= slots_.size()) {
            return LeakError::InvalidToken;
        }
        Slot& slot = slots_[token.index];
        if (!slot.active || slot.generation != token.generation) {
            return LeakError::InvalidToken;
        }
        live_bytes_ -= slot.bytes;
        --live_allocations_;
        slot.bytes = 0;
        slot.active = false;
        return LeakError::None;
    } catch (...) {
        return LeakError::InternalFailure;
    }
}

std::size_t LeakTracker::live_allocations() const noexcept {
    return live_allocations_;
}

std::size_t LeakTracker::live_bytes() const noexcept {
    return live_bytes_;
}

std::size_t LeakTracker::peak_allocations() const noexcept {
    return peak_allocations_;
}

std::size_t LeakTracker::peak_bytes() const noexcept {
    return peak_bytes_;
}

bool LeakTracker::empty() const noexcept {
    return live_allocations_ == 0;
}

}  // namespace stormline::core::memory
