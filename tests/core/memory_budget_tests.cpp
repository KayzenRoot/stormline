#include "stormline/core/memory/memory_budget.hpp"

#include <cstddef>
#include <cstdio>
#include <string_view>
#include <thread>

namespace {

using stormline::core::memory::BudgetError;
using stormline::core::memory::BudgetStatus;
using stormline::core::memory::MemoryBudget;

int failures = 0;

void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}

void begin_case() {
    failures = 0;
}

bool finish_case() {
    return failures == 0;
}

bool run_basic() {
    begin_case();
    MemoryBudget budget(100, 200);
    expect(budget.valid(), "budget is valid");
    expect(budget.used() == 0, "fresh budget unused");
    expect(budget.status() == BudgetStatus::Within, "fresh budget within");
    expect(budget.remaining_hard() == 200, "fresh remaining hard");

    BudgetStatus status = BudgetStatus::HardLimit;
    expect(budget.try_reserve(50, status) == BudgetError::None, "reserve 50 succeeds");
    expect(status == BudgetStatus::Within, "50 is within");
    expect(budget.used() == 50, "used 50");

    expect(budget.try_reserve(50, status) == BudgetError::None, "reserve second 50 succeeds");
    expect(status == BudgetStatus::SoftPressure, "100 hits soft pressure");
    expect(budget.used() == 100, "used 100");

    expect(budget.try_reserve(100, status) == BudgetError::None, "reserve to hard succeeds");
    expect(status == BudgetStatus::HardLimit, "200 hits hard limit");
    expect(budget.used() == 200, "used 200");
    expect(budget.remaining_hard() == 0, "no hard capacity remaining");

    expect(budget.release(100) == BudgetError::None, "release 100 succeeds");
    expect(budget.used() == 100, "used 100 after release");
    expect(budget.status() == BudgetStatus::SoftPressure, "release returns to soft pressure");
    expect(budget.release(100) == BudgetError::None, "release final 100 succeeds");
    expect(budget.used() == 0, "used 0 after release");
    expect(budget.status() == BudgetStatus::Within, "release returns within");
    return finish_case();
}

bool run_invalid() {
    begin_case();
    {
        MemoryBudget zero_soft(0, 10);
        expect(!zero_soft.valid(), "zero soft limit invalid");
        BudgetStatus status = BudgetStatus::Within;
        expect(zero_soft.try_reserve(1, status) == BudgetError::InvalidLimit,
               "zero soft limit reserve rejected");
        expect(zero_soft.release(1) == BudgetError::InvalidLimit,
               "zero soft limit release rejected");
        expect(zero_soft.remaining_hard() == 0, "invalid budget has no remaining");
        expect(zero_soft.status() == BudgetStatus::HardLimit, "invalid budget is fail-closed");
    }
    {
        MemoryBudget zero_hard(10, 0);
        expect(!zero_hard.valid(), "zero hard limit invalid");
    }
    {
        MemoryBudget inverted(20, 10);
        expect(!inverted.valid(), "soft > hard invalid");
    }
    return finish_case();
}

bool run_hard() {
    begin_case();
    MemoryBudget budget(50, 100);
    BudgetStatus status = BudgetStatus::Within;
    expect(budget.try_reserve(100, status) == BudgetError::None, "reserve exactly hard succeeds");
    expect(status == BudgetStatus::HardLimit, "exact hard status");
    expect(budget.used() == 100, "used exactly hard");

    status = BudgetStatus::Within;
    expect(budget.try_reserve(1, status) == BudgetError::ExceededHardLimit,
           "hard overflow rejected");
    expect(status == BudgetStatus::HardLimit, "hard overflow reports hard");
    expect(budget.used() == 100, "hard overflow leaves used unchanged");
    expect(budget.remaining_hard() == 0, "hard overflow remaining zero");

    expect(budget.release(100) == BudgetError::None, "release full usage succeeds");
    expect(budget.used() == 0, "release resets usage");
    expect(budget.status() == BudgetStatus::Within, "release resets status");
    return finish_case();
}

bool run_underflow() {
    begin_case();
    MemoryBudget budget(10, 100);
    BudgetStatus status = BudgetStatus::Within;
    expect(budget.try_reserve(10, status) == BudgetError::None, "reserve 10 succeeds");
    expect(budget.try_reserve(0, status) == BudgetError::InvalidBytes,
           "zero reserve rejected");
    expect(budget.release(0) == BudgetError::InvalidBytes, "zero release rejected");
    expect(budget.release(11) == BudgetError::ReleaseUnderflow,
           "release above used is rejected");
    expect(budget.used() == 10, "underflow leaves used unchanged");
    expect(budget.release(10) == BudgetError::None, "exact release succeeds");
    expect(budget.used() == 0, "exact release resets usage");
    return finish_case();
}

bool run_lifetime() {
    begin_case();
    MemoryBudget budget(64, 256);
    BudgetStatus status = BudgetStatus::Within;
    bool ok = true;
    for (int cycle = 0; cycle < 1000 && ok; ++cycle) {
        ok = budget.try_reserve(8, status) == BudgetError::None;
        ok = ok && budget.release(8) == BudgetError::None;
        ok = ok && budget.used() == 0;
        ok = ok && budget.status() == BudgetStatus::Within;
    }
    expect(ok, "1000 reserve/release cycles succeed");
    return finish_case();
}

bool run_wrong_thread() {
    begin_case();
    MemoryBudget budget(64, 256);
    BudgetError worker_reserve = BudgetError::None;
    BudgetError worker_release = BudgetError::None;
    std::thread worker([&budget, &worker_reserve, &worker_release] {
        BudgetStatus status = BudgetStatus::Within;
        worker_reserve = budget.try_reserve(8, status);
        worker_release = budget.release(8);
    });
    worker.join();
    expect(worker_reserve == BudgetError::WrongThread, "worker reserve rejected");
    expect(worker_release == BudgetError::WrongThread, "worker release rejected");
    expect(budget.used() == 0, "worker calls leave budget unused");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: %s <basic|invalid|hard|underflow|lifetime|wrong_thread>\n",
                     argv[0]);
        return 2;
    }

    const std::string_view mode(argv[1]);
    if (mode == "basic") {
        return run_basic() ? 0 : 1;
    }
    if (mode == "invalid") {
        return run_invalid() ? 0 : 1;
    }
    if (mode == "hard") {
        return run_hard() ? 0 : 1;
    }
    if (mode == "underflow") {
        return run_underflow() ? 0 : 1;
    }
    if (mode == "lifetime") {
        return run_lifetime() ? 0 : 1;
    }
    if (mode == "wrong_thread") {
        return run_wrong_thread() ? 0 : 1;
    }

    std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return 2;
}
