# NLE-PRPLAN-CORE-02-07 — Leak tracking

**Status:** `CODE_IMPLEMENTED / LOCAL_PASS / CI_PENDING`. **Formal packet:** `NLE-PRPLAN-CORE-02-07`. **ADR:** [ADR-0099](../adr/0099-core-02-leak-tracking.md). **Contract:** [core-02-leak-tracking-v0](../contracts/core-02-leak-tracking-v0.md). **WO:** [NLE-PRPLAN-CORE-02-07](../work-orders/NLE-PRPLAN-CORE-02-07.md). **Issue:** [#19](https://github.com/KayzenRoot/stormline/issues/19).

First explicit leak-tracking primitive: fixed-capacity generation-checked tokens, non-mutating capacity/stale/double-release rejection, live/peak counters and owner-thread enforcement for caller-declared allocations. A leak is an outstanding tracked token, not proof of process-wide or third-party leaks. No allocation interception, pointer capture, telemetry export, reporting service, global tracker, third-party dependency, public ABI or release.

## 1. Authorization and Context Lock

- **Gate:** [PR #474](https://github.com/KayzenRoot/stormline/pull/474) squash-merged as `0dbaef69e961b7d9a68e3fb965f4a7468d1005bb`; audit #6976903866 **APPROVED** (Sonar duplication debt noted).
- **Base:** `0dbaef69e961b7d9a68e3fb965f4a7468d1005bb`.
- **Code PR:** pending.
- **Selector:** during execution, `select_packet.py NLE-PRPLAN-CORE-02-07 --json` → `EXECUTOR_READY`, exit 0; all other IDs exit 2.
- **Capability admission:** `CORE-01-03/-06/-07/-08` completed; formal CORE-01 dependency retained; no module completion claim.

## 2. Implemented behavior

- `LeakTracker` fixed capacity 128; constructor records the owner thread; no dynamic allocation, no pointer addresses.
- `track(bytes, token)`: owner-thread check, zero-bytes rejection, capacity scan, generation increment (skipping 0 on wrap), token issuance, live counter/byte updates and monotonic peak updates.
- `release(token)`: owner-thread check, index/active/generation validation, live counter/byte decrement; stale, forged, out-of-range and double releases are non-mutating `InvalidToken`.
- Queries: live allocations, live bytes, peak allocations, peak bytes, `empty()`.
- `LeakError`: None, InvalidBytes, CapacityExceeded, InvalidToken, WrongThread, InternalFailure.
- No allocation interception, pointer map, telemetry/export, reporting, global tracker, SMF integration or public ABI.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/memory/leak_tracker.hpp` | Internal token/tracker API |
| `src/stormline/core/memory/leak_tracker.cpp` | Track/release, generations, counters, owner-thread |
| `tests/core/leak_tracker_tests.cpp` | basic/invalid/capacity/token/lifetime/wrong-thread tests |
| `CMakeLists.txt` | Additive `stormline_core02_leak` target and six CTests |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-02-07 path filters |
| `docs/evidence/NLE-PRPLAN-CORE-02-07.md` | This Evidence Bundle |

No other path changed. Existing targets unchanged except additive leak-tracker wiring.

## 4. Tests and real results

### Local preflight (observed)

- CMake/Ninja build of `stormline_core02_leak_test`: **OK**, no warnings under the repository warning policy.
- `ctest -R core02_leak_`: **6/6 passed** on Windows/MSVC 14.44.
- Full local matrix: **92/92 CTests passed** (86 previous + 6 leak tests).
- LKT matrix: LKT-01 basic accounting/peak retention; LKT-02 zero-byte rejection without mutation; LKT-03 capacity exhaustion, slot reuse and generation advance; LKT-04 default/forged/out-of-range/double-release rejection without mutation; LKT-05 1,000 track/release cycles; LKT-06 wrong-thread rejection without mutation.
- `python scripts/validate_pr_plans.py`: **PASS** (725 blocked, 1 ready, 18 completed, 4 approved gates).
- `python -m unittest scripts/test_validate_pr_plans.py`: **68/68 OK**.

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
- No allocation interception, pointer/address exposure, telemetry/export, reporting, global tracker, SMF integration, public ABI or release.
- The tracker is instance-local and not thread-safe by design; foreign owners are rejected via `WrongThread`. It is not a synchronization primitive.
- Only caller-declared tracked entries are observed; untracked allocations and third-party leaks are invisible. No claim of process-wide leak detection.
- ADR-0004/0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false`.
- No HIGH/CRITICAL known.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the leak-tracker target/tests/evidence restores the previous state.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the leak-tracking primitive, exact PR/CI/audit/merge SHA, 6 `core02_leak_*` tests and 92 total CTests, with explicit no-interception/pointer-map/telemetry/reporting/global/ABI/release limitations. This evidence does not self-promote the checkpoint.

## 8. Actual closure

Pending code PR CI, pt-BR audit, squash merge and the independent closeout PR.
