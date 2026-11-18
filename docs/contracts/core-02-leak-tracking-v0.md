# CORE-02 INTERNAL_ONLY Leak Tracking Contract v0 (NLE-PRPLAN-CORE-02-07)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO INTERCEPTION/TELEMETRY/GLOBAL`. **Base:** `74524e55237436a6b4501aab58b31e76cd1d5479`. **ADR:** [ADR-0099](../adr/0099-core-02-leak-tracking.md). **WO:** [NLE-PRPLAN-CORE-02-07](../work-orders/NLE-PRPLAN-CORE-02-07.md).

## Objective and bounded scope

Provide deterministic, explicit tracking of outstanding caller-declared allocations using generation-checked tokens, live/peak counters and owner-thread enforcement. A leak in this slice is an outstanding tracked token at a checkpoint, not proof of process-wide or third-party leaks. No allocation interception, pointer capture, global registry, telemetry export, I/O, SMF integration, public ABI or release.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`.

## Internal API (exact names)

```cpp
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
```

Header includes only C++ standard headers; no SDL/platform/third-party type, no pointer address, no dynamic container.

## Semantics

### Constructor

- Records the owner thread. No other state; the tracker is always valid and never allocates.

### `track(bytes, token)`

1. Wrong owner thread → `WrongThread`; token and counters unchanged.
2. `bytes == 0` → `InvalidBytes`; token and counters unchanged.
3. No inactive slot → `CapacityExceeded`; token and counters unchanged.
4. Otherwise select the first inactive slot, increment its generation (skipping 0 on wrap), store bytes, mark active, set `token = {index, generation}`, increment live counters, update peak counters, return `None`.

`token` is written only on success. Tokens are opaque handles; `index 0 / generation 0` is never a valid issued token.

### `release(token)`

1. Wrong owner thread → `WrongThread`.
2. `index >= capacity`, slot inactive, or generation mismatch → `InvalidToken`; no mutation.
3. Otherwise mark the slot inactive, decrement live allocation/byte counters, return `None`.

Peak counters never decrease. Releasing a slot permits reuse with a new generation; any older token for that slot is rejected.

### Queries

- `live_allocations`, `live_bytes`, `peak_allocations`, `peak_bytes` are read-only.
- `empty()` is `live_allocations() == 0`.
- No allocation, no pointer/address exposure, no timing/telemetry, no global state, no exception across the API.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| LKT-01 | basic accounting | track two entries; live/peak bytes/count correct; release one; release all; peaks retained |
| LKT-02 | invalid bytes | zero-byte track returns InvalidBytes; counters/peak/token unchanged |
| LKT-03 | capacity and reuse | 128 tracks fill capacity; 129th non-mutating CapacityExceeded; release frees a slot; reuse issues a new generation |
| LKT-04 | token validity | default/forged/out-of-range/stale/double-release tokens return InvalidToken without mutation |
| LKT-05 | lifetime | 1000 track/release cycles return empty with peak count 1 |
| LKT-06 | wrong-thread/regression | worker track/release return WrongThread; existing 86 CTests pass |

Allocation interception, pointer tracking, telemetry/export, reporting, SMF, frame/job barriers, ABI and release are out of scope.

## Exact implementation allowlist for packet -07

1. `src/stormline/core/memory/leak_tracker.hpp`
2. `src/stormline/core/memory/leak_tracker.cpp`
3. `tests/core/leak_tracker_tests.cpp`
4. `CMakeLists.txt` (additive leak-tracker target/tests only)
5. `.github/workflows/core01-internal-headless.yml` (additive CORE-02-07 path filters only)
6. `docs/evidence/NLE-PRPLAN-CORE-02-07.md`

`docs/work-orders/NLE-PRPLAN-CORE-02-07.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, allocation interception/pointer map/telemetry/global/ABI/release overclaim, or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or release. `NLE-D009 OPEN`.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0004 `PROPOSED`; ADR-0099 bounded; G3 global `NOT_CLEARED`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -07 remains blocked until then.**
