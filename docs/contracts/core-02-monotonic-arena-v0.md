# CORE-02 INTERNAL_ONLY Monotonic Arena Contract v0 (NLE-PRPLAN-CORE-02-05)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO POOL/BUDGET/TELEMETRY`. **Base:** `9d49dc3da22d245daf1df95d0f27ee56588904af`. **ADR:** [ADR-0097](../adr/0097-core-02-monotonic-arena.md). **WO:** [NLE-PRPLAN-CORE-02-05](../work-orders/NLE-PRPLAN-CORE-02-05.md).

## Objective and bounded scope

Provide a fixed-capacity monotonic arena with one backing allocation, bump allocation, explicit reset and high-water accounting. No per-slice free, pools, budgets, leak tracking, telemetry, frame/job barriers, global/static arena, third-party dependency or public ABI.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`; no module completion claim.

## Internal API (exact names)

```cpp
#pragma once

#include "stormline/core/memory/memory_block.hpp"

#include <cstddef>
#include <cstdint>
#include <memory_resource>
#include <thread>

namespace stormline::core::memory {

enum class ArenaError : std::uint8_t {
    None,
    InvalidCapacity,
    InvalidSize,
    InvalidAlignment,
    AlignmentExceedsBacking,
    OutOfMemory,
    NotInitialized,
    WrongThread,
    InternalFailure
};

struct ArenaSlice final {
    std::byte* data{nullptr};
    std::size_t size{0};
    std::size_t offset{0};
};

class MonotonicArena final {
public:
    static constexpr std::size_t default_capacity = 64 * 1024;
    static constexpr std::size_t default_backing_alignment = 64;

    explicit MonotonicArena(std::size_t capacity = default_capacity,
                            std::size_t backing_alignment = default_backing_alignment,
                            std::pmr::memory_resource* resource = nullptr) noexcept;
    ~MonotonicArena() noexcept;

    MonotonicArena(const MonotonicArena&) = delete;
    MonotonicArena& operator=(const MonotonicArena&) = delete;
    MonotonicArena(MonotonicArena&&) = delete;
    MonotonicArena& operator=(MonotonicArena&&) = delete;

    [[nodiscard]] ArenaError allocate(std::size_t bytes, std::size_t alignment,
                                      ArenaSlice& out) noexcept;
    [[nodiscard]] ArenaError reset() noexcept;
    [[nodiscard]] std::size_t capacity() const noexcept;
    [[nodiscard]] std::size_t used() const noexcept;
    [[nodiscard]] std::size_t remaining() const noexcept;
    [[nodiscard]] std::size_t high_water() const noexcept;
    [[nodiscard]] bool valid() const noexcept;

private:
    MemoryBlock backing_;
    std::size_t capacity_{0};
    std::size_t offset_{0};
    std::size_t high_water_{0};
    std::size_t backing_alignment_{default_backing_alignment};
    std::thread::id owner_thread_;
    ArenaError init_error_{ArenaError::None};
};

}  // namespace stormline::core::memory
```

Headers include only C++ standard/internal memory headers; no SDL/platform/third-party type.

## Semantics

### Constructor

- Records the owner thread.
- `capacity == 0` → `init_error_=InvalidCapacity`, `valid()==false`.
- `backing_alignment` not a power of two → `init_error_=InvalidAlignment`, invalid.
- Allocates one backing `MemoryBlock` of exactly `capacity` bytes with `backing_alignment` via `MemoryBlock::allocate(resource, capacity, alignment, MemoryDomain::Frame, backing_)`.
- Allocation failure stores `OutOfMemory`/`Invalid*` and leaves `valid()==false`; no exceptions cross the constructor.

### `allocate(bytes, alignment, out)`

1. Wrong owner thread → `WrongThread`.
2. Invalid arena (backing failure) → stored init error (`NotInitialized` if none).
3. `bytes == 0` → `InvalidSize`; alignment not power of two → `InvalidAlignment`.
4. `alignment > backing_alignment_` → `AlignmentExceedsBacking`.
5. Align `offset_` up to `alignment`; if padding overflow, aligned offset exceeds capacity, or `bytes > capacity - aligned`, → `OutOfMemory`; state unchanged.
6. Success: `out.data = backing_.data() + aligned`, `out.size=bytes`, `out.offset=aligned`; `offset_ = aligned + bytes`; `high_water_ = max(high_water_, offset_)`; return `None`.

### `reset()`

- Wrong owner thread → `WrongThread`; invalid arena → stored init error.
- Sets `offset_=0`; **does not** release/zero the backing block; preserves `high_water_`; returns `None`.

### Queries

- `capacity()`, `used()`, `remaining()`, `high_water()` and `valid()` are read-only/no-throw.
- `remaining() == capacity - used` when valid; no SDL call.

### Lifetime and failure

- The arena owns one backing `MemoryBlock`; the destructor releases it once (no-throw).
- The resource must outlive the arena/backing block; a null resource resolves to the system baseline.
- No global/static arena, no hidden thread, no per-slice free, no exception across the API.
- Reset is not a frame/job barrier; CORE-04 owns tick boundaries and readers/jobs/GPU fences.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| ARN-01 | basic allocation/reset | slice aligned/writable; used/high-water update; reset rewinds, high-water preserved |
| ARN-02 | alignment | slices at 1/8/16/32/64 honor alignment; no overlap |
| ARN-03 | overflow | fill capacity; next allocation `OutOfMemory`; state unchanged; reset recovers |
| ARN-04 | invalid inputs | zero capacity/bytes, non-power-of-two, alignment > backing, invalid arena typed |
| ARN-05 | lifetime/resource | 1000 alloc/reset cycles; counting resource sees one backing alloc/free; no live leak |
| ARN-06 | wrong-thread/regression | worker allocate/reset `WrongThread`; existing 73 CTests pass |

Pools, budgets, leak tracking, telemetry, frame/job barriers, allocator winners, ABI and release are out of scope.

## Exact implementation allowlist for packet -05

1. `src/stormline/core/memory/monotonic_arena.hpp`
2. `src/stormline/core/memory/monotonic_arena.cpp`
3. `tests/core/monotonic_arena_tests.cpp`
4. `CMakeLists.txt` (additive arena target/tests only)
5. `.github/workflows/core01-internal-headless.yml` (additive CORE-02-05 path filters only)
6. `docs/evidence/NLE-PRPLAN-CORE-02-05.md`

`docs/work-orders/NLE-PRPLAN-CORE-02-05.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, existing regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, per-slice free/pool/budget/leak/telemetry/global/static/ABI/release overclaim, or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or release. `NLE-D009 OPEN`; no release.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0004 `PROPOSED`; ADR-0097 bounded; G3 global `NOT_CLEARED`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -05 remains blocked until then.**
