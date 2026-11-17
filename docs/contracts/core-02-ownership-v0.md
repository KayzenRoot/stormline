# CORE-02 INTERNAL_ONLY Ownership Contract v0 (NLE-PRPLAN-CORE-02-03)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NOT EXTERNAL ABI`. **Base:** `bb7229496a5c015ae4d2e31be444381cefc49c1f`. **ADR:** [ADR-0087](../adr/0087-core-02-ownership-slice.md). **Capability admission:** [ADR-0086](../adr/0086-capability-based-l1-dependency.md). **WO:** [NLE-PRPLAN-CORE-02-03](../work-orders/NLE-PRPLAN-CORE-02-03.md).

## Objective and bounded scope

Provide the first internal memory-ownership primitive: a move-only `MemoryBlock` that obtains memory from an explicit C++20 `std::pmr::memory_resource`, records its exact allocation parameters and domain, and releases it exactly once. This is the ownership foundation for later allocator, arena, budget, leak-tracking and telemetry packets.

Out of scope: global allocator selection/replacement, mimalloc/rpmalloc/Tracy/SMF, benchmark harness, pools, arenas, frame/job reset barriers, budget graph, leak tracking, telemetry, snapshots, plugin SDK/ABI, GPU VRAM, renderer/GPU/audio/network, public release.

## Dependency and capability admission

- Formal module dependency: `CORE-01` (unchanged in registry/manifest).
- Admitted capabilities, satisfied by completed packets: `CORE01_HEADLESS_BUILD_AND_TEST` (`-03`), `CORE01_PORTABLE_PATHS` (`-06`), `CORE01_SDL3_BUILD_BASELINE` (`-07`), `CORE01_NATIVE_CI_MATRIX` (`-08`).
- Not required and not used: window lifecycle runtime, input/event pump, DPI, IME, hotplug, sleep/resume, soak/qualification, renderer/GPU/audio, network, public ABI, packaging/release.
- The code links no SDL target and calls no SDL API. SDL3 remains part of the existing shared CMake build baseline only.

## Internal API (exact names)

Namespace `stormline::core::memory`, header `stormline/core/memory/memory_block.hpp`, no symbol/ABI stability guarantee:

```cpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <memory_resource>

namespace stormline::core::memory {

enum class MemoryDomain : std::uint8_t {
    Persistent,
    Frame,
    Job,
    Streaming,
    Vfx,
    AudioRealtime,
    Network,
    Editor,
    Plugin
};

enum class MemoryError : std::uint8_t {
    None,
    InvalidSize,
    InvalidAlignment,
    OutOfMemory,
    AlreadyOwned,
    InternalFailure
};

class MemoryBlock final {
public:
    MemoryBlock() noexcept = default;
    ~MemoryBlock() noexcept;

    MemoryBlock(const MemoryBlock&) = delete;
    MemoryBlock& operator=(const MemoryBlock&) = delete;
    MemoryBlock(MemoryBlock&& other) noexcept;
    MemoryBlock& operator=(MemoryBlock&& other) noexcept;

    [[nodiscard]] static MemoryError allocate(
        std::pmr::memory_resource* resource,
        std::size_t bytes,
        std::size_t alignment,
        MemoryDomain domain,
        MemoryBlock& out) noexcept;

    [[nodiscard]] MemoryError release() noexcept;
    [[nodiscard]] std::byte* data() noexcept;
    [[nodiscard]] const std::byte* data() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] std::size_t alignment() const noexcept;
    [[nodiscard]] MemoryDomain domain() const noexcept;
    [[nodiscard]] bool valid() const noexcept;
    [[nodiscard]] explicit operator bool() const noexcept;

private:
    MemoryBlock(std::pmr::memory_resource* resource, void* data, std::size_t bytes,
                std::size_t alignment, MemoryDomain domain) noexcept;

    std::pmr::memory_resource* resource_{nullptr};
    void* data_{nullptr};
    std::size_t bytes_{0};
    std::size_t alignment_{0};
    MemoryDomain domain_{MemoryDomain::Persistent};
};

}  // namespace stormline::core::memory
```

The header includes only C++ standard headers. It must not include SDL, platform headers, or any third-party header.

## Semantics

### `allocate(resource, bytes, alignment, domain, out)`

1. `out.valid()` → `AlreadyOwned`; no resource call, `out` unchanged.
2. `bytes == 0` → `InvalidSize`; no resource call.
3. `alignment == 0` or not a power of two → `InvalidAlignment`; no resource call.
4. `resource == nullptr` resolves to `std::pmr::new_delete_resource()`; a non-null resource must outlive the block.
5. Call `resource->allocate(bytes, alignment)` inside a `try` block.
   - `std::bad_alloc` → `OutOfMemory`.
   - any other exception → `InternalFailure`.
   - null pointer without an exception → `OutOfMemory`; no `deallocate`.
6. On success, `out` owns the pointer and the exact `bytes`, `alignment`, resource and domain; return `None`.
7. The returned pointer must be aligned to `alignment`; the implementation checks this and fails safely before handing out an unaligned block.

### `release()`

- Invalid block → `None` (idempotent); no resource call.
- Valid block → clear the ownership state first, then call `resource->deallocate(data, bytes, alignment)` exactly once with the original values.
- A throwing `deallocate` returns `InternalFailure`; the block is already invalid, so no double release occurs.
- Release is allowed from any thread only when the chosen resource is thread-safe; the default `new_delete_resource()` is thread-safe. The block itself is not thread-safe for concurrent access.

### Move construction and assignment

- Move construction transfers the ownership token and leaves the source invalid.
- Move assignment first releases any block already owned by the destination (exactly once), then transfers the source token and leaves the source invalid.
- Self-move-assignment is a no-op.
- Move operations are `noexcept` and do not call allocation.

### Destructor and failure behavior

- The destructor calls `release()` and ignores the returned error; it does not throw.
- No C++ exception crosses the API.
- No global mutable state, singleton, default-resource replacement, hidden allocation or ambient authority.
- `data()`, `constant data()` return the owned pointer; `size()`, `alignment()` and `domain()` return the recorded values; `valid()` and `operator bool` report `data_ != nullptr`.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| OWN-01 | basic allocate/write/read/release | `None`; non-null; size/alignment/domain exact; bytes writable; release `None`; invalid afterwards |
| OWN-02 | invalid size/alignment | `bytes=0` → `InvalidSize`; alignments 0 and non-powers-of-two → `InvalidAlignment`; no allocation; `out` unchanged |
| OWN-03 | already-owned destination | second allocate → `AlreadyOwned`; original pointer/metadata unchanged; no extra resource call |
| OWN-04 | move constructor/assignment | source invalid; destination valid with same pointer/metadata; previous destination released exactly once; self-move no-op |
| OWN-05 | repeated release/destructor | release twice → `None` both times; exactly one deallocate; destructor releases once |
| OWN-06 | custom counting resource and OOM | exact bytes/alignment received and returned; `bad_alloc` → `OutOfMemory`; no deallocate on failure |
| OWN-07 | cross-thread ownership transfer | move into worker, release there; default resource safe; counting resource live count zero after join |
| OWN-08 | regression/lifetime | 1000 allocate/release cycles, including over-alignment; zero live; existing 23 CORE-01 CTests pass on Linux, Linux ASan/UBSan, Windows and macOS |

## Exact implementation allowlist for packet -03

1. `src/stormline/core/memory/memory_block.hpp`
2. `src/stormline/core/memory/memory_block.cpp`
3. `tests/core/memory_block_tests.cpp`
4. `CMakeLists.txt` (additive memory target/tests only)
5. `.github/workflows/core01-internal-headless.yml` (additive CORE-02 path filters only)
6. `docs/evidence/NLE-PRPLAN-CORE-02-03.md`

`docs/work-orders/NLE-PRPLAN-CORE-02-03.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, missing capability evidence, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, global allocator override, third-party dependency, SDL call, public ABI/release claim or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or package installation. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0004 `PROPOSED`; ADR-0086/0087 bounded; G3 global `NOT_CLEARED`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -03 remains blocked until then.**
