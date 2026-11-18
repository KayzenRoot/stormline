# CORE-02 INTERNAL_ONLY Memory Budget Contract v0 (NLE-PRPLAN-CORE-02-06)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO SMF/TELEMETRY/WIRING`. **Base:** `42ab4b74b686e9856c150101895a9e6182c964b5`. **ADR:** [ADR-0098](../adr/0098-core-02-memory-budget.md). **WO:** [NLE-PRPLAN-CORE-02-06](../work-orders/NLE-PRPLAN-CORE-02-06.md).

## Objective and bounded scope

Provide deterministic soft/hard memory budget accounting with typed reservation/release, pressure status and owner-thread enforcement. No allocation interception, SMF graph, reclaim hooks, telemetry, leak tracking, frame/job barriers, global budget, public ABI or release.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`.

## Internal API (exact names)

```cpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <thread>

namespace stormline::core::memory {

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
    MemoryBudget(std::size_t soft_limit, std::size_t hard_limit) noexcept;
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
    BudgetError init_error_{BudgetError::None};
};

}  // namespace stormline::core::memory
```

Header includes only C++ standard headers; no SDL/platform/third-party type.

## Semantics

### Constructor

- `soft_limit == 0`, `hard_limit == 0`, or `soft_limit > hard_limit` → invalid (`InvalidLimit`); limits/used are zeroed; no exception.
- Otherwise records owner thread and valid limits.

### `try_reserve(bytes, status)`

1. Wrong owner thread → `WrongThread`; status unchanged.
2. Invalid budget → stored error (`InvalidLimit`/`NotInitialized`).
3. `bytes == 0` → `InvalidBytes`, status unchanged.
4. `bytes > hard_limit - used` → `ExceededHardLimit`, `status=HardLimit`, no mutation.
5. Otherwise `used += bytes`; status is `HardLimit` at/above hard, `SoftPressure` at/above soft, otherwise `Within`; return `None`.

### `release(bytes)`

1. Wrong thread → `WrongThread`.
2. Invalid budget → stored error.
3. `bytes == 0` → `InvalidBytes`, no mutation.
4. `bytes > used` → `ReleaseUnderflow`, no mutation.
5. Otherwise `used -= bytes`; status recomputed (Hard/Soft/Within); return `None`.

### Queries

- `used`, limits and `remaining_hard` are read-only; invalid budget reports zero limits/remaining.
- `status()` is `HardLimit` for invalid budgets (fail-closed), otherwise derived from used/soft/hard.
- No allocation, no timing/telemetry, no global state, no exception across the API.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| BGT-01 | basic accounting | reserve to soft/hard; status transitions; release recomputes |
| BGT-02 | invalid limits | zero/soft>hard invalid; reserve returns InvalidLimit; status HardLimit |
| BGT-03 | hard rejection | non-mutating ExceededHardLimit; used unchanged; remaining correct |
| BGT-04 | bytes/underflow | zero reserve/release InvalidBytes; release > used ReleaseUnderflow, no mutation |
| BGT-05 | lifetime | 1000 reserve/release cycles return used 0/Within |
| BGT-06 | wrong-thread/regression | worker calls WrongThread; existing 80 CTests pass |

Allocation wiring, reclaim, telemetry, leak tracking, SMF, frame/job barriers, ABI and release are out of scope.

## Exact implementation allowlist for packet -06

1. `src/stormline/core/memory/memory_budget.hpp`
2. `src/stormline/core/memory/memory_budget.cpp`
3. `tests/core/memory_budget_tests.cpp`
4. `CMakeLists.txt` (additive budget target/tests only)
5. `.github/workflows/core01-internal-headless.yml` (additive CORE-02-06 path filters only)
6. `docs/evidence/NLE-PRPLAN-CORE-02-06.md`

`docs/work-orders/NLE-PRPLAN-CORE-02-06.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, allocation interception/SMF/telemetry/global/ABI/release overclaim, or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or release. `NLE-D009 OPEN`.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0004 `PROPOSED`; ADR-0098 bounded; G3 global `NOT_CLEARED`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -06 remains blocked until then.**
