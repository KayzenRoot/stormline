#pragma once

#include <cstddef>
#include <cstdint>
#include <thread>

namespace stormline::core::memory {

class MemoryTelemetry;

enum class BudgetStatus : std::uint8_t {
    Within,
    SoftPressure,
    HardLimit
};

enum class BudgetError : std::uint8_t {
    None,
    InvalidLimit,
    InvalidBytes,
    ExceededHardLimit,
    ReleaseUnderflow,
    WrongThread,
    NotInitialized,
    InternalFailure
};

class MemoryBudget final {
public:
    MemoryBudget(std::size_t soft_limit, std::size_t hard_limit,
                 MemoryTelemetry* telemetry = nullptr) noexcept;
    ~MemoryBudget() noexcept = default;

    MemoryBudget(const MemoryBudget&) = delete;
    MemoryBudget& operator=(const MemoryBudget&) = delete;
    MemoryBudget(MemoryBudget&&) = delete;
    MemoryBudget& operator=(MemoryBudget&&) = delete;

    [[nodiscard]] BudgetError try_reserve(std::size_t bytes, BudgetStatus& status) noexcept;
    [[nodiscard]] BudgetError release(std::size_t bytes) noexcept;
    [[nodiscard]] std::size_t used() const noexcept;
    [[nodiscard]] std::size_t soft_limit() const noexcept;
    [[nodiscard]] std::size_t hard_limit() const noexcept;
    [[nodiscard]] std::size_t remaining_hard() const noexcept;
    [[nodiscard]] BudgetStatus status() const noexcept;
    [[nodiscard]] bool valid() const noexcept;

private:
    std::size_t soft_limit_{0};
    std::size_t hard_limit_{0};
    std::size_t used_{0};
    std::thread::id owner_thread_;
    MemoryTelemetry* telemetry_{nullptr};
    BudgetError init_error_{BudgetError::None};
};

}  // namespace stormline::core::memory
