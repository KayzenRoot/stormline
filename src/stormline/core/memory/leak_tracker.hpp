#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <thread>

namespace stormline::core::memory {

struct LeakToken {
    std::uint32_t index{0};
    std::uint32_t generation{0};

    [[nodiscard]] bool operator==(const LeakToken& other) const noexcept = default;
};

enum class LeakError : std::uint8_t {
    None,
    InvalidBytes,
    CapacityExceeded,
    InvalidToken,
    WrongThread,
    InternalFailure
};

class LeakTracker final {
public:
    static constexpr std::size_t capacity = 128;

    LeakTracker() noexcept;
    ~LeakTracker() noexcept = default;

    LeakTracker(const LeakTracker&) = delete;
    LeakTracker& operator=(const LeakTracker&) = delete;
    LeakTracker(LeakTracker&&) = delete;
    LeakTracker& operator=(LeakTracker&&) = delete;

    [[nodiscard]] LeakError track(std::size_t bytes, LeakToken& token) noexcept;
    [[nodiscard]] LeakError release(LeakToken token) noexcept;
    [[nodiscard]] std::size_t live_allocations() const noexcept;
    [[nodiscard]] std::size_t live_bytes() const noexcept;
    [[nodiscard]] std::size_t peak_allocations() const noexcept;
    [[nodiscard]] std::size_t peak_bytes() const noexcept;
    [[nodiscard]] bool empty() const noexcept;

private:
    struct Slot {
        std::size_t bytes{0};
        std::uint32_t generation{0};
        bool active{false};
    };

    std::array<Slot, capacity> slots_{};
    std::size_t live_allocations_{0};
    std::size_t live_bytes_{0};
    std::size_t peak_allocations_{0};
    std::size_t peak_bytes_{0};
    std::thread::id owner_thread_;
};

}  // namespace stormline::core::memory
