# NLE-PRPLAN-CORE-02-05 — Monotonic arena

**Status:** `CODE_IMPLEMENTED / LOCAL_PREFLIGHT_PASS / NATIVE_CI_PENDING / AWAITING_AUDIT`. **Formal packet:** `NLE-PRPLAN-CORE-02-05`. **ADR:** [ADR-0097](../adr/0097-core-02-monotonic-arena.md). **Contract:** [core-02-monotonic-arena-v0](../contracts/core-02-monotonic-arena-v0.md). **WO:** [NLE-PRPLAN-CORE-02-05](../work-orders/NLE-PRPLAN-CORE-02-05.md). **Issue:** [#19](https://github.com/KayzenRoot/stormline/issues/19).

First monotonic arena: one fixed-capacity backing `MemoryBlock`, bump allocation with alignment, explicit reset, high-water accounting, typed overflow and owner-thread enforcement. No per-slice free, pools, budgets, leak tracking, telemetry, global/static arena, third-party dependency, public ABI or release.

## 1. Authorization and Context Lock

- **Gate:** [PR #468](https://github.com/KayzenRoot/stormline/pull/468) squash-merged as `fdf04debc3a25e6f48b3aaa69aae116f28a11404`; audit #6965580258 **APPROVED** (Sonar duplication debt noted).
- **Base:** `fdf04debc3a25e6f48b3aaa69aae116f28a11404`.
- **Selector:** `select_packet.py NLE-PRPLAN-CORE-02-05 --json` → `EXECUTOR_READY`, exit 0; `-06`, `CORE-01-16` and every other ID exit 2.
- **Capability admission:** `CORE-01-03/-06/-07/-08` completed; formal CORE-01 dependency retained; no module completion claim.

## 2. Implemented behavior

- `MonotonicArena(capacity, backing_alignment, resource)`; one `MemoryBlock` backing allocation, owner thread recorded.
- `allocate(bytes, alignment, out)`: zero/alignment/backing-alignment validation, alignment padding, capacity check, bump offset, high-water update; `OutOfMemory` leaves state unchanged.
- `reset()`: rewinds offset to 0, preserves high-water and backing memory.
- Queries: capacity/used/remaining/high-water/valid.
- `ArenaError`: None, InvalidCapacity, InvalidSize, InvalidAlignment, AlignmentExceedsBacking, OutOfMemory, NotInitialized, WrongThread, InternalFailure.
- No per-slice free, global/static arena, pool/budget/leak/telemetry or exception across the API.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/memory/monotonic_arena.hpp` | Internal arena API |
| `src/stormline/core/memory/monotonic_arena.cpp` | Bump allocation/reset/high-water |
| `tests/core/monotonic_arena_tests.cpp` | basic/alignment/overflow/invalid/resource/lifetime/thread tests |
| `CMakeLists.txt` | Additive `stormline_core02_arena` target and seven CTests |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-02-05 path filters |
| `docs/evidence/NLE-PRPLAN-CORE-02-05.md` | This Evidence Bundle |

No other path changed. Existing targets unchanged except additive arena wiring.

## 4. Tests and real results

### Local preflight (observed)

- CMake/Ninja build of `stormline_core02_arena_test`: **OK**.
- `ctest -R core02_arena_`: **7/7 passed** on Windows/MSVC 14.44.
- Full local matrix: **80/80 CTests passed** (73 previous + 7 arena tests).
- Tests cover alignment 1/8/16/32/64, overflow/state preservation, reset/high-water, invalid capacity/alignment/bytes, counting backing resource (one alloc/free), 1000 allocate/reset cycles and wrong-thread rejection.

### Native CI (authoritative, pending)

Pending exact-head Docs Validation and native Linux/Linux-sanitizers/Windows/macOS runs. This document will be updated with run IDs and observed CTest counts after they complete; no native PASS is claimed yet.

Expected matrix: existing 73 CTests plus 7 arena tests = **80 CTests** per native job, with Linux ASan/UBSan.

## 5. Security, licensing and limitations

- No new dependency, package, secret, upload, paid runner/service or runtime download.
- No per-slice free, pools, budgets, leak tracking, telemetry, frame/job barriers, global/static arena, public ABI or release.
- CORE-04 owns frame/tick reset barriers; reset here is not a synchronization primitive.
- ADR-0004/0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false`.
- No HIGH/CRITICAL known; Sonar duplication debt on the validator remains a non-required quality follow-up from the gate.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the arena target/tests/evidence restores the previous state.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the monotonic arena, exact PR/CI/audit/merge SHA, 7 `core02_arena_*` tests and 80 total CTests, with explicit no-pool/budget/leak/telemetry/ABI/release limitations. This evidence does not self-promote the checkpoint.
