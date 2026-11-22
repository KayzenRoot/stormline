#pragma once

#include <cstdint>

namespace stormline::experimental {

enum class HostState : std::uint8_t { stopped, running };
enum class HostError : std::uint8_t { none, already_running, not_running };

class HeadlessHost final {
public:
    [[nodiscard]] constexpr HostError start() noexcept {
        if (state_ == HostState::running) {
            return HostError::already_running;
        }
        state_ = HostState::running;
        ++start_count_;
        return HostError::none;
    }

    [[nodiscard]] constexpr HostError stop() noexcept {
        if (state_ != HostState::running) {
            return HostError::not_running;
        }
        state_ = HostState::stopped;
        return HostError::none;
    }

    [[nodiscard]] constexpr HostState state() const noexcept { return state_; }
    [[nodiscard]] constexpr std::uint64_t starts() const noexcept { return start_count_; }

private:
    HostState state_{HostState::stopped};
    std::uint64_t start_count_{0};
};

} // namespace stormline::experimental
