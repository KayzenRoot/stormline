#include "stormline/core/memory/memory_budget.hpp"

#include <thread>

namespace stormline::core::memory {
namespace {

bool on_owner_thread(const std::thread::id& owner) noexcept {
    return std::this_thread::get_id() == owner;
}

BudgetStatus status_for(std::size_t used, std::size_t soft, std::size_t hard) noexcept {
    if (used >= hard) {
        return BudgetStatus::HardLimit;
    }
    if (used >= soft) {
        return BudgetStatus::SoftPressure;
    }
    return BudgetStatus::Within;
}

}  // namespace

MemoryBudget::MemoryBudget(std::size_t soft_limit, std::size_t hard_limit) noexcept
    : soft_limit_(soft_limit),
      hard_limit_(hard_limit),
      owner_thread_(std::this_thread::get_id()) {
    if (soft_limit_ == 0 || hard_limit_ == 0 || soft_limit_ > hard_limit_) {
        init_error_ = BudgetError::InvalidLimit;
        soft_limit_ = 0;
        hard_limit_ = 0;
    }
}

BudgetError MemoryBudget::try_reserve(std::size_t bytes, BudgetStatus& status) noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return BudgetError::WrongThread;
        }
        if (!valid()) {
            return init_error_ == BudgetError::None ? BudgetError::NotInitialized
                                                    : init_error_;
        }
        if (bytes == 0) {
            return BudgetError::InvalidBytes;
        }
        if (bytes > hard_limit_ - used_) {
            status = BudgetStatus::HardLimit;
            return BudgetError::ExceededHardLimit;
        }
        used_ += bytes;
        status = status_for(used_, soft_limit_, hard_limit_);
        return BudgetError::None;
    } catch (...) {
        return BudgetError::InternalFailure;
    }
}

BudgetError MemoryBudget::release(std::size_t bytes) noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return BudgetError::WrongThread;
        }
        if (!valid()) {
            return init_error_ == BudgetError::None ? BudgetError::NotInitialized
                                                    : init_error_;
        }
        if (bytes == 0) {
            return BudgetError::InvalidBytes;
        }
        if (bytes > used_) {
            return BudgetError::ReleaseUnderflow;
        }
        used_ -= bytes;
        return BudgetError::None;
    } catch (...) {
        return BudgetError::InternalFailure;
    }
}

std::size_t MemoryBudget::used() const noexcept {
    return used_;
}

std::size_t MemoryBudget::soft_limit() const noexcept {
    return soft_limit_;
}

std::size_t MemoryBudget::hard_limit() const noexcept {
    return hard_limit_;
}

std::size_t MemoryBudget::remaining_hard() const noexcept {
    return valid() ? hard_limit_ - used_ : 0;
}

BudgetStatus MemoryBudget::status() const noexcept {
    if (!valid()) {
        return BudgetStatus::HardLimit;
    }
    return status_for(used_, soft_limit_, hard_limit_);
}

bool MemoryBudget::valid() const noexcept {
    return init_error_ == BudgetError::None && soft_limit_ > 0 && hard_limit_ >= soft_limit_;
}

}  // namespace stormline::core::memory
