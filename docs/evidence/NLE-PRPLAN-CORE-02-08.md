# NLE-PRPLAN-CORE-02-08 — Memory telemetry

**Status:** `CODE_IMPLEMENTED / LOCAL_PASS / CI_PENDING`. **Formal packet:** `NLE-PRPLAN-CORE-02-08`. **ADR:** [ADR-0100](../adr/0100-core-02-memory-telemetry.md). **Contract:** [core-02-memory-telemetry-v0](../contracts/core-02-memory-telemetry-v0.md). **WO:** [NLE-PRPLAN-CORE-02-08](../work-orders/NLE-PRPLAN-CORE-02-08.md). **Issue:** [#19](https://github.com/KayzenRoot/stormline/issues/19).

First internal memory-telemetry primitive: atomic per-domain and aggregate allocation/release/live/peak/cumulative counters, typed zero/invalid-domain/underflow rejection, and optional default-null hooks in the existing block, arena, budget and leak primitives. No global interception, pointer/call-site capture, timestamps, sampling thread, I/O/export, third-party tooling, public ABI or release.

## 1. Authorization and Context Lock

- **Gate:** [PR #483](https://github.com/KayzenRoot/stormline/pull/483) squash-merged as `21913c4029aa02a4ca991bc9e21e16aabbaf72dc`; audit #6995750093 **APPROVED** (Sonar duplication debt noted).
- **Base:** `21913c4029aa02a4ca991bc9e21e16aabbaf72dc`.
- **Code PR:** pending.
- **Selector:** during execution, `select_packet.py NLE-PRPLAN-CORE-02-08 --json` → `EXECUTOR_READY`, exit 0; all other IDs exit 2.
- **Capability admission:** `CORE-01-03/-06/-07/-08` completed; formal CORE-01 dependency retained; no module completion claim.
- **CORE-01 gap audit:** no NECESSARY executable code increment identified; remaining items require physical hardware, owner ratification of thresholds/versions, independent security/release decisions. QUAL-001/002 were not repeated.

## 2. Implemented behavior

- `MemoryTelemetry` with per-`MemoryDomain` and aggregate counters for allocations, releases, live allocations, live bytes, peak live bytes, total allocated/released bytes.
- `record_allocate`: zero-byte/invalid-domain rejection; atomic counter/peak updates.
- `record_release`: zero-byte/invalid-domain rejection; atomic compare-exchange underflow check with non-mutating `ReleaseUnderflow`; balanced release accounting.
- Budget/leak/arena records: reservations, releases, reserved/released bytes, peak reserved, soft-pressure events, hard rejections; tracked/released leak tokens and peak tracked bytes; arena slice count/bytes/high-water.
- `snapshot` loads per-counter relaxed atomics; `empty()` reflects live real allocations/bytes.
- Optional hooks, all default-null: `MemoryBlock::allocate(..., telemetry)`, `MonotonicArena(..., telemetry)`, `MemoryBudget(..., telemetry)`, `LeakTracker(telemetry)`.
- No global allocation interception, pointer/address storage, timestamps, sampling thread, I/O, export, third-party tooling or public ABI.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/memory/memory_telemetry.hpp` | Internal telemetry API and snapshots |
| `src/stormline/core/memory/memory_telemetry.cpp` | Atomic counters, peaks, underflow, snapshot |
| `tests/core/memory_telemetry_tests.cpp` | basic/invalid/underflow/integration/concurrent/benchmark |
| `src/stormline/core/memory/memory_block.hpp/.cpp` | Optional allocation/free hook |
| `src/stormline/core/memory/monotonic_arena.hpp/.cpp` | Optional backing/slice hook |
| `src/stormline/core/memory/memory_budget.hpp/.cpp` | Optional reserve/release/rejection hook |
| `src/stormline/core/memory/leak_tracker.hpp/.cpp` | Optional track/release hook |
| `CMakeLists.txt` | Additive telemetry target, links and six CTests |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-02-08 path filters |
| `docs/evidence/NLE-PRPLAN-CORE-02-08.md` | This Evidence Bundle |

No other path changed. Existing call sites remain source-compatible because every new parameter defaults to `nullptr`; behavior without telemetry is unchanged.

## 4. Tests and real results

### Local preflight (observed)

- CMake/Ninja build of the full tree: **OK**, no compiler warnings observed under the repository warning policy.
- `ctest -R core02_telemetry_`: **6/6 passed** on Windows/MSVC 14.44.
- Full local matrix: **104/104 CTests passed** (98 previous + 6 telemetry; Linux CI includes one additional ABI test).
- TLM matrix: TLM-01 per-domain/aggregate accounting and peak retention; TLM-02 zero-byte/invalid-domain non-mutation; TLM-03 underflow and double-release non-mutation; TLM-04 block/arena/budget/leak integration and null-hook compatibility; TLM-05 four threads × 10,000 allocate/release pairs with exact final counters; TLM-06 report-only benchmark and regression.
- Benchmark observed: `TELEMETRY_BENCH_NS_PER_PAIR=251.183 iterations=500000` (Windows Debug/MSVC local, one run; **not** a performance PASS or threshold).
- `python scripts/validate_pr_plans.py`: **PASS** (724 blocked, 1 ready, 19 completed, 4 approved gates).
- `python -m unittest scripts/test_validate_pr_plans.py`: **70/70 OK**.

### Native CI (authoritative, pending)

To be completed at the exact PR HEAD after push:

| Job | Runner / toolchain | Result |
|---|---|---|
| `docs-validation` | required G2 check | pending |
| `linux` | ubuntu-24.04, GCC, X11 via Xvfb/openbox | pending |
| `linux-sanitizers` | ubuntu-24.04, ASan/UBSan | pending |
| `windows` | windows-2025-vs2026, MSVC | pending |
| `macos` | macos-15-arm64, Apple clang | pending |

## 5. Security, licensing and limitations

- No new dependency, package, secret, upload, paid runner/service or runtime download.
- No global allocation interception, pointer/address exposure, timestamps, sampling thread, telemetry export, third-party profiler, public ABI or release.
- Counters are atomic and data-race free; a concurrent snapshot is non-transactional. After quiescence the allocation/release/live and cumulative invariants hold.
- Telemetry is opt-in and explicit; untracked allocations and the base image/OS allocator are invisible. No process-wide or third-party leak/usage claim.
- The telemetry instance must outlive instrumented blocks/arenas/budgets/leak trackers; ownership is not transferred.
- ADR-0004/0003/0075 `PROPOSED`; ADR-0100 bounded; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false`.
- No HIGH/CRITICAL known.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the telemetry target/tests and the default-null hooks restores prior behavior.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the telemetry primitive, exact PR/CI/audit/merge SHA, 6 `core02_telemetry_*` tests and total CTests, with explicit no-interception/export/pointer/global/ABI/release limitations. This evidence does not self-promote the checkpoint.

## 8. Actual closure

Pending code PR CI, pt-BR audit, squash merge and the independent closeout PR.
