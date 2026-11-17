#pragma once

#include "stormline/core/internal/event_queue.hpp"

#include <cstdint>
#include <thread>

namespace stormline::core::internal {

enum class LifecycleState : std::uint8_t {
    Running,
    SuspendPending,
    Suspended,
    ResumePending,
    ShutdownPending,
    Terminated
};

enum class LifecycleError : std::uint8_t {
    None,
    WrongThread,
    InvalidTransition,
    AlreadyTerminated,
    InternalFailure
};

class LifecycleController final {
public:
    LifecycleController() noexcept;
    ~LifecycleController() noexcept = default;

    LifecycleController(const LifecycleController&) = delete;
    LifecycleController& operator=(const LifecycleController&) = delete;
    LifecycleController(LifecycleController&&) = delete;
    LifecycleController& operator=(LifecycleController&&) = delete;

    [[nodiscard]] LifecycleError request_suspend() noexcept;
    [[nodiscard]] LifecycleError acknowledge_suspend() noexcept;
    [[nodiscard]] LifecycleError request_resume() noexcept;
    [[nodiscard]] LifecycleError acknowledge_resume() noexcept;
    [[nodiscard]] LifecycleError request_shutdown() noexcept;
    [[nodiscard]] LifecycleError acknowledge_shutdown() noexcept;
    [[nodiscard]] LifecycleError request_terminate() noexcept;
    [[nodiscard]] LifecycleError observe(const InputEvent& event) noexcept;

    [[nodiscard]] LifecycleState state() const noexcept;
    [[nodiscard]] bool should_continue() const noexcept;

private:
    LifecycleState state_{LifecycleState::Running};
    std::thread::id owner_thread_;
};

}  // namespace stormline::core::internal
