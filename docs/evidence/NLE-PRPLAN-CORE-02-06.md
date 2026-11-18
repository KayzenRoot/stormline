# NLE-PRPLAN-CORE-02-06 — Memory budget

**Status:** `CODE_IMPLEMENTED / NATIVE_CI_PASS / AUDIT_PENDING`. **Formal packet:** `NLE-PRPLAN-CORE-02-06`. **ADR:** [ADR-0098](../adr/0098-core-02-memory-budget.md). **Contract:** [core-02-memory-budget-v0](../contracts/core-02-memory-budget-v0.md). **WO:** [NLE-PRPLAN-CORE-02-06](../work-orders/NLE-PRPLAN-CORE-02-06.md). **Issue:** [#19](https://github.com/KayzenRoot/stormline/issues/19).

First memory-budget accounting primitive: explicit per-instance soft/hard limits, typed non-mutating reserve/release, pressure status and owner-thread enforcement. No allocation interception, SMF/reclaim graph, telemetry, leak tracking, frame/job barrier, global budget, third-party dependency, public ABI or release.

## 1. Authorization and Context Lock

- **Gate:** [PR #471](https://github.com/KayzenRoot/stormline/pull/471) squash-merged as `d59dd8ba0e8e958d31446276ceb39e3786af6f51`; audit #6974359786 **APPROVED**.
- **Base:** `d59dd8ba0e8e958d31446276ceb39e3786af6f51`.
- **Code PR:** [PR #472](https://github.com/KayzenRoot/stormline/pull/472); implementation HEAD `dac7c89df3370a6b1bf233cd1a2d9246ba162065`; CI and audit pending at the final documentation head.
- **Selector:** after the gate merge, `select_packet.py NLE-PRPLAN-CORE-02-06 --json` → `EXECUTOR_READY`, exit 0; all other IDs exit 2.
- **Capability admission:** `CORE-01-03/-06/-07/-08` completed; formal CORE-01 dependency retained; no module completion claim.

## 2. Implemented behavior

- `MemoryBudget(soft_limit, hard_limit)`; nonzero limits with `soft <= hard`; invalid construction fails closed (`valid()==false`, status `HardLimit`, remaining 0).
- `try_reserve(bytes, status)`: owner-thread check, validity, zero-bytes rejection, non-mutating hard-limit rejection, otherwise increments `used` and reports `Within`, `SoftPressure` or `HardLimit`.
- `release(bytes)`: owner-thread check, validity, zero-bytes rejection, non-mutating underflow rejection, otherwise decrements `used`.
- Queries: used, soft/hard limit, remaining hard capacity, pressure status, validity.
- `BudgetError`: None, InvalidLimit, InvalidBytes, ExceededHardLimit, ReleaseUnderflow, WrongThread, NotInitialized, InternalFailure.
- No atomic/interlocked operations, thread synchronization, interception, SMF, reclaim hooks, telemetry or global budget.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/memory/memory_budget.hpp` | Internal budget API |
| `src/stormline/core/memory/memory_budget.cpp` | Soft/hard accounting, typed errors, owner-thread |
| `tests/core/memory_budget_tests.cpp` | basic/invalid/hard/underflow/lifetime/wrong-thread tests |
| `CMakeLists.txt` | Additive `stormline_core02_budget` target and six CTests |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-02-06 path filters |
| `docs/evidence/NLE-PRPLAN-CORE-02-06.md` | This Evidence Bundle |

No other path changed. Existing targets unchanged except additive budget wiring.

## 4. Tests and real results

### Local preflight (observed)

- CMake/Ninja build of `stormline_core02_budget_test`: **OK**, no warnings under the repository warning policy.
- `ctest -R core02_budget_`: **6/6 passed** on Windows/MSVC 14.44.
- Full local matrix: **86/86 CTests passed** (80 previous + 6 budget tests).
- BGT matrix: BGT-01 soft/hard transitions; BGT-02 invalid limits fail closed; BGT-03 exact hard reserve accepted and overflow rejected without mutation; BGT-04 zero-byte/underflow rejection without mutation; BGT-05 1,000 reserve/release cycles; BGT-06 wrong-thread reserve/release rejected without mutation.
- `python scripts/validate_pr_plans.py`: **PASS** (726 blocked, 1 ready, 17 completed, 4 approved gates).
- `python -m unittest scripts/test_validate_pr_plans.py`: **66/66 OK**.

### Native CI (authoritative, observed)

All jobs ran at implementation HEAD `dac7c89df3370a6b1bf233cd1a2d9246ba162065`; the only subsequent delta is this Evidence Bundle text, revalidated by the PR head checks.

| Job | Runner / toolchain | Result |
|---|---|---|
| `docs-validation` | required G2 check | [run 44276151259](https://github.com/KayzenRoot/stormline/actions/runs/44276151259) **SUCCESS** |
| `linux` | ubuntu-24.04, GCC, X11 via Xvfb/openbox | **86/86 CTest passed** |
| `linux-sanitizers` | ubuntu-24.04, ASan/UBSan | **86/86 CTest passed** |
| `windows` | windows-2025-vs2026, MSVC | **86/86 CTest passed** |
| `macos` | macos-15-arm64, Apple clang | **86/86 CTest passed** |

Native workflow run: [44276151253](https://github.com/KayzenRoot/stormline/actions/runs/44276151253) **SUCCESS**. Job IDs: Linux `134704683964`, sanitizers `134704683327`, Windows `134704683572`, macOS `134704682887`. All 6 budget tests executed; the 80 previous CTests continue passing. SonarCloud Code Analysis passed; Socket checks passed.

Docs validators: `validate_pr_plans.py` **PASS** (726 blocked, 1 ready, 17 completed, 4 approved gates), `validate_docs.py` **PASS** (42 required files, 976 Markdown), `validate_wo_registry.py` **PASS** (80 blocked packets), `test_validate_pr_plans.py` **66/66 OK**.

## 5. Security, licensing and limitations

- No new dependency, package, secret, upload, paid runner/service or runtime download.
- No allocation interception, SMF graph, reclaim hooks, telemetry, leak tracking, frame/job barrier, global budget, public ABI or release.
- The accounting is instance-local and not thread-safe by design; concurrent owners are rejected via `WrongThread`. It is not a synchronization primitive.
- ADR-0004/0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false`.
- No HIGH/CRITICAL known.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the budget target/tests/evidence restores the previous state.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the memory-budget primitive, exact PR/CI/audit/merge SHA, 6 `core02_budget_*` tests and 86 total CTests, with explicit no-interception/SMF/telemetry/global/ABI/release limitations. This evidence does not self-promote the checkpoint.

## 8. Actual closure

Pending pt-BR audit, squash merge and the independent closeout PR.
