# NLE-PRPLAN-CORE-01-12 — Lifecycle request state machine

**Status:** `CODE_IMPLEMENTED / NATIVE_CI_PASS / AWAITING_AUDIT`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-12`. **ADR:** [ADR-0091](../adr/0091-core-01-lifecycle-request-state-machine.md). **Contract:** [core-01-lifecycle-requests-v0](../contracts/core-01-lifecycle-requests-v0.md). **WO:** [NLE-PRPLAN-CORE-01-12](../work-orders/NLE-PRPLAN-CORE-01-12.md). **Issue:** [#18](https://github.com/KayzenRoot/stormline/issues/18).

First CORE-01 lifecycle request state machine: owner-thread suspend/resume/shutdown/terminate transitions with typed errors and observation of quit/window-close host events. No OS signal handlers, forced process kill, persistence, renderer teardown, public ABI or release.

## 1. Authorization and Context Lock

- **Gate:** [PR #452](https://github.com/KayzenRoot/stormline/pull/452) squash-merged as `3223fb771312a0f6a80de656361b0cfa42b3a711`; audit #6960639796 **APPROVED**.
- **Code PR:** [PR #453](https://github.com/KayzenRoot/stormline/pull/453), HEAD auditado `30a0cbe5b8ccb959fa72a2a1b897b05485b3a910`.
- **Base:** `3223fb771312a0f6a80de656361b0cfa42b3a711`.
- **Selector:** `select_packet.py NLE-PRPLAN-CORE-01-12 --json` → `EXECUTOR_READY`, exit 0; `-13`, `CORE-02-04` and every other ID exit 2.
- **Predecessors:** `-03`..`-11` completed; CORE-02-03 ownership completed via PR #441.

## 2. Implemented behavior

- `LifecycleState`: `Running`, `SuspendPending`, `Suspended`, `ResumePending`, `ShutdownPending`, `Terminated`.
- `LifecycleError`: `None`, `WrongThread`, `InvalidTransition`, `AlreadyTerminated`, `InternalFailure`.
- Normal path: Running → SuspendPending → Suspended → ResumePending → Running.
- Shutdown path from Running/SuspendPending/Suspended/ResumePending → ShutdownPending → Terminated; repeated shutdown in ShutdownPending is idempotent; terminated repeats return `AlreadyTerminated`.
- Explicit `request_terminate` forces Terminated; repeated terminate returns `AlreadyTerminated`.
- `observe(InputEvent)`: Quit/WindowCloseRequested → shutdown; other event types ignored; no event-queue ownership.
- Invalid transitions leave the state unchanged and return `InvalidTransition`; all mutating calls are owner-thread only; no exception crosses the boundary.
- `should_continue()` false only for ShutdownPending/Terminated; destructor performs no forced transition.
- No OS signal handler, sleep hook, process kill, persistence/save, renderer teardown or public ABI.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/internal/lifecycle.hpp` | Internal state/error/controller API |
| `src/stormline/core/internal/lifecycle.cpp` | Transition table, event observation, owner-thread checks |
| `tests/core/lifecycle_tests.cpp` | normal/shutdown/events/invalid/wrong-thread/recovery tests |
| `CMakeLists.txt` | Additive `stormline_core01_lifecycle` target and six CTests |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-01-12 path filters |
| `docs/evidence/NLE-PRPLAN-CORE-01-12.md` | This Evidence Bundle |

No other path changed. Existing CORE-01/CORE-02 targets are unchanged except additive lifecycle wiring.

## 4. Tests and real results

### Local preflight (observed)

- CMake/Ninja configure/build `stormline_core01_lifecycle_test`: **OK**.
- `ctest -R core01_lifecycle_`: **6/6 passed** on Windows/MSVC 14.44.
- Full local matrix: **59/59 CTests passed** (53 previous + 6 lifecycle tests).
- Tests cover normal transitions, shutdown from every allowed state, quit/close observation, invalid transitions, wrong-thread rejection and 100 suspend/resume cycles.

### Native CI (authoritative, observed)

All jobs ran at the exact HEAD `30a0cbe5b8ccb959fa72a2a1b897b05485b3a910`:

| Job | Runner / toolchain | Result |
|---|---|---|
| `docs-validation` | required G2 check | [run 44173938010](https://github.com/KayzenRoot/stormline/actions/runs/44173938010) **SUCCESS** |
| `linux` | ubuntu-24.04, GCC, X11 via Xvfb/openbox | **59/59 CTest passed** |
| `linux-sanitizers` | ubuntu-24.04, ASan/UBSan, X11 via Xvfb/openbox | **59/59 CTest passed** |
| `windows` | windows-2025-vs2026, MSVC | **59/59 CTest passed** |
| `macos` | macos-15-arm64, Apple clang | **59/59 CTest passed** |

Native workflow run: [44173938232](https://github.com/KayzenRoot/stormline/actions/runs/44173938232) **SUCCESS**. Job IDs: Linux `134360125295`, sanitizers `134360124695`, Windows `134360125097`, macOS `134360125071`. The six `core01_lifecycle_*` tests executed in every job in addition to the existing 53 CTests; none skipped.

No correction was required by the native matrix.

## 5. Security, licensing and limitations

- Standard library only; no third-party dependency, package installation, secret, upload, paid runner/service or runtime download.
- No OS signal handler, forced process kill, sleep/resume hook, persistence/save, renderer device-loss recovery or public ABI.
- Physical OS suspend/resume/termination remains **NOT_QUALIFIED**; the slice proves the internal transition contract and host-event policy only.
- ADR-0003/0075 remain `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.
- No HIGH/CRITICAL known; native CI passed at the code head and the result remains subject to the independent pt-BR audit.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the lifecycle target/tests and this evidence restores the previous state.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the eighth real CORE-01 slice, exact PR/CI/audit/merge SHA, 6 `core01_lifecycle_*` tests and 59 total CTests across Linux, Linux ASan/UBSan, Windows and macOS, and the explicit statement that this is an internal request state machine only — not OS signal/termination, persistence, renderer recovery, public ABI or release. This evidence does not self-promote the checkpoint.
