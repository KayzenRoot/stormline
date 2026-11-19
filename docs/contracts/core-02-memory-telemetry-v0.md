# CORE-02 INTERNAL_ONLY Memory Telemetry Contract v0 (NLE-PRPLAN-CORE-02-08)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO INTERCEPTION/EXPORT/GLOBAL`. **Base:** `dd76fceb6b9e835dd505c24a3c89065317528440`. **ADR:** [ADR-0100](../adr/0100-core-02-memory-telemetry.md). **WO:** [NLE-PRPLAN-CORE-02-08](../work-orders/NLE-PRPLAN-CORE-02-08.md).

## Objective and bounded scope

Provide deterministic in-process memory telemetry counters with per-`MemoryDomain` categories, live/peak/cumulative accounting, explicit underflow rejection and optional instrumentation hooks for the existing block, arena, budget and leak primitives. No global interception, pointer/call-site capture, timestamps, sampling thread, I/O, export pipeline, third-party tooling, public ABI or release.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`.

## Internal API (exact names)

```cpp
#pragma once

#include "stormline/core/memory/memory_block.hpp"
#include "stormline/core/memory/memory_budget.hpp"

#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>

namespace stormline::core::memory {

inline constexpr std::size_t memory_telemetry_domain_count = 9;

enum class TelemetryError : std::uint8_t {
    None,
    InvalidBytes,
    InvalidDomain,
    ReleaseUnderflow,
    InternalFailure
};

struct MemoryTelemetryDomainSnapshot {
    std::uint64_t allocations{0};
    std::uint64_t releases{0};
    std::uint64_t live_allocations{0};
    std::uint64_t live_bytes{0};
    std::uint64_t peak_live_bytes{0};
    std::uint64_t total_allocated_bytes{0};
    std::uint64_t total_released_bytes{0};
};

struct MemoryTelemetryBudgetSnapshot {
    std::uint64_t reservations{0};
    std::uint64_t releases{0};
    std::uint64_t reserved_bytes{0};
    std::uint64_t released_bytes{0};
    std::uint64_t peak_reserved_bytes{0};
    std::uint64_t soft_pressure_events{0};
    std::uint64_t hard_rejections{0};
};

struct MemoryTelemetryLeakSnapshot {
    std::uint64_t tracked{0};
    std::uint64_t released{0};
    std::uint64_t tracked_bytes{0};
    std::uint64_t released_bytes{0};
    std::uint64_t peak_tracked_bytes{0};
};

struct MemoryTelemetryArenaSnapshot {
    std::uint64_t slices{0};
    std::uint64_t slice_bytes{0};
    std::uint64_t high_water_bytes{0};
};

struct MemoryTelemetrySnapshot {
    std::array<MemoryTelemetryDomainSnapshot, memory_telemetry_domain_count> domains{};
    MemoryTelemetryBudgetSnapshot budget;
    MemoryTelemetryLeakSnapshot leak;
    MemoryTelemetryArenaSnapshot arena;
    std::uint64_t allocations{0};
    std::uint64_t releases{0};
    std::uint64_t live_allocations{0};
    std::uint64_t live_bytes{0};
    std::uint64_t peak_live_bytes{0};
    std::uint64_t total_allocated_bytes{0};
    std::uint64_t total_released_bytes{0};
};

class MemoryTelemetry final {
public:
    static constexpr std::size_t domain_count = memory_telemetry_domain_count;

    MemoryTelemetry() noexcept = default;
    ~MemoryTelemetry() noexcept = default;

    MemoryTelemetry(const MemoryTelemetry&) = delete;
    MemoryTelemetry& operator=(const MemoryTelemetry&) = delete;
    MemoryTelemetry(MemoryTelemetry&&) = delete;
    MemoryTelemetry& operator=(MemoryTelemetry&&) = delete;

    [[nodiscard]] TelemetryError record_allocate(MemoryDomain domain, std::size_t bytes) noexcept;
    [[nodiscard]] TelemetryError record_release(MemoryDomain domain, std::size_t bytes) noexcept;

    void record_budget_reserve(std::size_t bytes, BudgetStatus status) noexcept;
    void record_budget_release(std::size_t bytes) noexcept;
    void record_budget_rejection() noexcept;
    void record_leak_track(std::size_t bytes) noexcept;
    void record_leak_release(std::size_t bytes) noexcept;
    void record_arena_slice(std::size_t bytes, std::size_t high_water_bytes) noexcept;

    void snapshot(MemoryTelemetrySnapshot& out) const noexcept;
    [[nodiscard]] bool empty() const noexcept;

private:
    struct Counters {
        std::atomic<std::uint64_t> allocations{0};
        std::atomic<std::uint64_t> releases{0};
        std::atomic<std::uint64_t> live_allocations{0};
        std::atomic<std::uint64_t> live_bytes{0};
        std::atomic<std::uint64_t> peak_live_bytes{0};
        std::atomic<std::uint64_t> total_allocated_bytes{0};
        std::atomic<std::uint64_t> total_released_bytes{0};
    };

    std::array<Counters, memory_telemetry_domain_count> domains_{};
    std::atomic<std::uint64_t> allocations_{0};
    std::atomic<std::uint64_t> releases_{0};
    std::atomic<std::uint64_t> live_allocations_{0};
    std::atomic<std::uint64_t> live_bytes_{0};
    std::atomic<std::uint64_t> peak_live_bytes_{0};
    std::atomic<std::uint64_t> total_allocated_bytes_{0};
    std::atomic<std::uint64_t> total_released_bytes_{0};
    std::atomic<std::uint64_t> budget_reservations_{0};
    std::atomic<std::uint64_t> budget_releases_{0};
    std::atomic<std::uint64_t> budget_reserved_bytes_{0};
    std::atomic<std::uint64_t> budget_released_bytes_{0};
    std::atomic<std::uint64_t> budget_peak_reserved_bytes_{0};
    std::atomic<std::uint64_t> budget_soft_pressure_events_{0};
    std::atomic<std::uint64_t> budget_hard_rejections_{0};
    std::atomic<std::uint64_t> leak_tracked_{0};
    std::atomic<std::uint64_t> leak_released_{0};
    std::atomic<std::uint64_t> leak_tracked_bytes_{0};
    std::atomic<std::uint64_t> leak_released_bytes_{0};
    std::atomic<std::uint64_t> leak_peak_tracked_bytes_{0};
    std::atomic<std::uint64_t> arena_slices_{0};
    std::atomic<std::uint64_t> arena_slice_bytes_{0};
    std::atomic<std::uint64_t> arena_high_water_bytes_{0};
};

}  // namespace stormline::core::memory
```

The header includes only standard headers plus the existing internal block/budget headers that provide `MemoryDomain` and `BudgetStatus`; no SDL/platform/third-party type.

## Semantics

### `record_allocate(domain, bytes)`

1. `bytes == 0` → `InvalidBytes`; no mutation.
2. Domain value outside `0..domain_count-1` → `InvalidDomain`; no mutation.
3. Otherwise increment domain and aggregate allocation counters, live allocations/bytes and total allocated bytes; update domain and aggregate peak live bytes with atomic max; return `None`.

### `record_release(domain, bytes)`

1. `bytes == 0` → `InvalidBytes`; no mutation.
2. Invalid domain → `InvalidDomain`; no mutation.
3. No live allocation or insufficient live bytes in the domain → `ReleaseUnderflow`; no mutation.
4. Otherwise decrement domain and aggregate live allocation/bytes counters, increment release and total-released counters; return `None`.

Underflow checks and updates use atomic compare-exchange; counters are data-race free. A concurrent `snapshot()` is a non-transactional read of individual atomics and is not promised to be a single point-in-time view. After all recording threads quiesce, `allocations == releases + live_allocations` and `total_allocated_bytes == total_released_bytes + live_bytes`.

### Instrumentation records

- `record_budget_reserve(bytes, status)`: reservation count/bytes, peak reserved bytes; increments soft-pressure events when `status == SoftPressure`.
- `record_budget_release(bytes)`: release count/bytes.
- `record_budget_rejection()`: hard-rejection count.
- `record_leak_track/release(bytes)`: tracked/released counts and bytes; peak tracked bytes.
- `record_arena_slice(bytes, high_water_bytes)`: successful slice count, cumulative slice bytes and maximum observed high-water.

These records are monotonic counters and do not change live real-allocation counters. They are noexcept and ignore arithmetic saturation beyond 64-bit wraparound; callers do not receive errors.

### `snapshot(out)` and `empty()`

- `snapshot` loads all counters with relaxed atomics into the supplied structure; aggregate domain values are read from aggregate counters and are expected to equal the domain sums after quiescence.
- `empty()` is true only when aggregate live allocations and live bytes are zero; budget/leak/arena cumulative counters do not affect it.
- No allocation, pointer/address exposure, timing, I/O, telemetry export, global state or exception across the API.

## Integration contract

- `MemoryBlock::allocate(resource, bytes, alignment, domain, out, telemetry = nullptr)` records the real allocation after success; `release` records the real free. If the telemetry record fails after allocation, the block deallocates and returns `InternalFailure`. The telemetry pointer must outlive the block.
- `MonotonicArena(capacity, alignment, resource, telemetry = nullptr)` passes telemetry to its backing block and calls `record_arena_slice` after each successful slice; `reset` does not erase cumulative telemetry.
- `MemoryBudget(soft, hard, telemetry = nullptr)` records successful reserves/releases, soft-pressure events and hard rejections; rejected/invalid operations do not record a reservation.
- `LeakTracker(telemetry = nullptr)` records successful track/release events.
- All new parameters default to `nullptr`; existing call sites and behavior remain source-compatible and unchanged when telemetry is absent.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| TLM-01 | basic/domain accounting | allocate/release in two domains; per-domain and aggregate live/peak/cumulative values exact; invariant holds |
| TLM-02 | invalid input | zero bytes and invalid domain return typed errors without mutation |
| TLM-03 | underflow | release without allocation or above live bytes returns `ReleaseUnderflow`; counters unchanged |
| TLM-04 | integration | block, arena, budget and leak hooks update their respective counters; no cross-contamination; telemetry-null path unchanged |
| TLM-05 | concurrency | 4 worker threads allocate/release 10,000 pairs; after join allocations=releases=40,000, live=0, no lost updates |
| TLM-06 | benchmark/regression | report-only ns/op printed for a fixed pair loop; existing 99 Linux / 98 Windows/macOS CTests pass |

No export, sampling thread, frame/job barrier, pointer map, SMF, ABI or release.

## Exact implementation allowlist for packet -08

1. `src/stormline/core/memory/memory_telemetry.hpp`
2. `src/stormline/core/memory/memory_telemetry.cpp`
3. `tests/core/memory_telemetry_tests.cpp`
4. `src/stormline/core/memory/memory_block.hpp` and `.cpp` (optional telemetry hook only)
5. `src/stormline/core/memory/monotonic_arena.hpp` and `.cpp` (optional telemetry hook only)
6. `src/stormline/core/memory/memory_budget.hpp` and `.cpp` (optional telemetry hook only)
7. `src/stormline/core/memory/leak_tracker.hpp` and `.cpp` (optional telemetry hook only)
8. `CMakeLists.txt` (additive telemetry target/tests and required target links)
9. `.github/workflows/core01-internal-headless.yml` (additive CORE-02-08 path filters only)
10. `docs/evidence/NLE-PRPLAN-CORE-02-08.md`

`docs/work-orders/NLE-PRPLAN-CORE-02-08.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, global interception/export/pointer map/third-party/ABI/release overclaim, or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or release. `NLE-D009 OPEN`.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0004 `PROPOSED`; ADR-0100 bounded; G3 global `NOT_CLEARED`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -08 remains blocked until then.**
