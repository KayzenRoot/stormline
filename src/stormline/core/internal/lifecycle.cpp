#include "stormline/core/internal/lifecycle.hpp"

#include <thread>

namespace stormline::core::internal {
namespace {

bool on_owner_thread(const std::thread::id& owner) noexcept {
    return std::this_thread::get_id() == owner;
}

}  // namespace

LifecycleController::LifecycleController() noexcept
    : owner_thread_(std::this_thread::get_id()) {}

LifecycleError LifecycleController::request_suspend() noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return LifecycleError::WrongThread;
        }
        if (state_ != LifecycleState::Running) {
            return LifecycleError::InvalidTransition;
        }
        state_ = LifecycleState::SuspendPending;
        return LifecycleError::None;
    } catch (...) {
        return LifecycleError::InternalFailure;
    }
}

LifecycleError LifecycleController::acknowledge_suspend() noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return LifecycleError::WrongThread;
        }
        if (state_ != LifecycleState::SuspendPending) {
            return LifecycleError::InvalidTransition;
        }
        state_ = LifecycleState::Suspended;
        return LifecycleError::None;
    } catch (...) {
        return LifecycleError::InternalFailure;
    }
}

LifecycleError LifecycleController::request_resume() noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return LifecycleError::WrongThread;
        }
        if (state_ != LifecycleState::Suspended) {
            return LifecycleError::InvalidTransition;
        }
        state_ = LifecycleState::ResumePending;
        return LifecycleError::None;
    } catch (...) {
        return LifecycleError::InternalFailure;
    }
}

LifecycleError LifecycleController::acknowledge_resume() noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return LifecycleError::WrongThread;
        }
        if (state_ != LifecycleState::ResumePending) {
            return LifecycleError::InvalidTransition;
        }
        state_ = LifecycleState::Running;
        return LifecycleError::None;
    } catch (...) {
        return LifecycleError::InternalFailure;
    }
}

LifecycleError LifecycleController::request_shutdown() noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return LifecycleError::WrongThread;
        }
        if (state_ == LifecycleState::Terminated) {
            return LifecycleError::AlreadyTerminated;
        }
        if (state_ == LifecycleState::ShutdownPending) {
            return LifecycleError::None;
        }
        state_ = LifecycleState::ShutdownPending;
        return LifecycleError::None;
    } catch (...) {
        return LifecycleError::InternalFailure;
    }
}

LifecycleError LifecycleController::acknowledge_shutdown() noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return LifecycleError::WrongThread;
        }
        if (state_ == LifecycleState::Terminated) {
            return LifecycleError::AlreadyTerminated;
        }
        if (state_ != LifecycleState::ShutdownPending) {
            return LifecycleError::InvalidTransition;
        }
        state_ = LifecycleState::Terminated;
        return LifecycleError::None;
    } catch (...) {
        return LifecycleError::InternalFailure;
    }
}

LifecycleError LifecycleController::request_terminate() noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return LifecycleError::WrongThread;
        }
        if (state_ == LifecycleState::Terminated) {
            return LifecycleError::AlreadyTerminated;
        }
        state_ = LifecycleState::Terminated;
        return LifecycleError::None;
    } catch (...) {
        return LifecycleError::InternalFailure;
    }
}

LifecycleError LifecycleController::observe(const InputEvent& event) noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return LifecycleError::WrongThread;
        }
        if (event.type == InputEventType::Quit
            || event.type == InputEventType::WindowCloseRequested) {
            return request_shutdown();
        }
        return LifecycleError::None;
    } catch (...) {
        return LifecycleError::InternalFailure;
    }
}

LifecycleState LifecycleController::state() const noexcept {
    return state_;
}

bool LifecycleController::should_continue() const noexcept {
    return state_ != LifecycleState::ShutdownPending
           && state_ != LifecycleState::Terminated;
}

}  // namespace stormline::core::internal
