# CORE-02 INTERNAL_ONLY System Allocator Baseline Contract v0 (NLE-PRPLAN-CORE-02-04)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NO ALLOCATOR SELECTION`. **Base:** `4920c2f4e3bf787f58c867c2df5bd321eaca8729`. **ADR:** [ADR-0096](../adr/0096-core-02-system-allocator-baseline.md). **WO:** [NLE-PRPLAN-CORE-02-04](../work-orders/NLE-PRPLAN-CORE-02-04.md).

## Objective and bounded scope

Provide an explicit `SystemMemoryResource` over `::operator new/delete` as the reproducible C++ baseline, integrate it with `MemoryBlock`, and run a report-only comparative harness against `std::pmr::new_delete_resource`, `::operator new/delete` and `malloc/free`. No mimalloc/rpmalloc selection, global override, arena, budget, leak tracker, telemetry, public ABI or release.

## Capability admission

Formal dependency `CORE-01` remains. Admitted only via completed `CORE-01-03/-06/-07/-08` capabilities, as in ADR-0096; no module completion claim.

## Internal API (exact names)

```cpp
#pragma once

#include <cstddef>
#include <memory_resource>

namespace stormline::core::memory {

class SystemMemoryResource final : public std::pmr::memory_resource {
public:
    SystemMemoryResource() noexcept = default;
    ~SystemMemoryResource() override = default;

    SystemMemoryResource(const SystemMemoryResource&) = delete;
    SystemMemoryResource& operator=(const SystemMemoryResource&) = delete;
    SystemMemoryResource(SystemMemoryResource&&) = delete;
    SystemMemoryResource& operator=(SystemMemoryResource&&) = delete;

private:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* pointer, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

}  // namespace stormline::core::memory
```

The header includes only C++ standard headers. No SDL/platform/third-party type.

## Semantics

### `do_allocate(bytes, alignment)`

- `bytes == 0` allocates **1 byte**; deallocation of the original 0-byte request also uses 1 byte.
- `alignment` must be a power of two (the `memory_resource` contract); ordinary `::operator new(bytes)` is used when `alignment <= alignof(std::max_align_t)`, otherwise `::operator new(bytes, std::align_val_t(alignment))`.
- Allocation failure propagates `std::bad_alloc`; no catch/translate inside the resource.
- No global state, logging, counters or allocation override.

### `do_deallocate(pointer, bytes, alignment)`

- Matches the allocation path: aligned delete for over-aligned blocks, ordinary delete otherwise.
- Null pointer is not a valid input under the `memory_resource` contract; it is not intentionally dereferenced.
- No throw; no global state.

### `do_is_equal(other)`

- Returns `this == &other`; two distinct system resources are not equal even though both use the same underlying C++ allocator.

### Integration

- `MemoryBlock::allocate(&resource, bytes, alignment, domain, out)` accepts the resource; the resource must outlive the block.
- A null resource still resolves to `std::pmr::new_delete_resource()`.
- `MemoryBlock` release calls `deallocate` with the original bytes/alignment exactly once.

### Benchmark

A test mode compares `SystemMemoryResource`, `std::pmr::new_delete_resource`, `::operator new/delete` and `malloc/free` over deterministic size/alignment sets. It prints ns/op and ratios and asserts only correctness. **No timing threshold, winner selection, RSS/fragmentation claim or performance PASS.**

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| SYS-01 | basic resource | allocate 256/alignment 64, aligned pointer, writable, deallocate once |
| SYS-02 | alignment | alignments 1/8/16/32/64/128/4096 respected; matching deallocation |
| SYS-03 | MemoryBlock integration | `MemoryBlock` over `SystemMemoryResource`; release; ownership invalid |
| SYS-04 | zero/lifetime | zero-byte path; 10,000 alloc/dealloc cycles; no live allocation in ASan |
| SYS-05 | cross-thread release | allocate owner, deallocate worker; default/system resource thread-safe |
| SYS-06 | report-only benchmark/regression | prints ns/op; no threshold; existing 67 CTests pass |

No allocator winner, third-party dependency, global override or performance PASS is part of this contract.

## Exact implementation allowlist for packet -04

1. `src/stormline/core/memory/system_memory_resource.hpp`
2. `src/stormline/core/memory/system_memory_resource.cpp`
3. `tests/core/system_memory_resource_tests.cpp`
4. `CMakeLists.txt` (additive system-resource target/tests only)
5. `.github/workflows/core01-internal-headless.yml` (additive CORE-02-04 path filters only)
6. `docs/evidence/NLE-PRPLAN-CORE-02-04.md`

`docs/work-orders/NLE-PRPLAN-CORE-02-04.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, existing regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, global override, third-party dependency, allocator winner/performance/ABI/release overclaim, or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or release. SDL3 zlib notice preserved; `NLE-D009 OPEN`.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0004 `PROPOSED`; ADR-0096 bounded; G3 global `NOT_CLEARED`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -04 remains blocked until then.**
