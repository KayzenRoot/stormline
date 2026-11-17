# NLE-PRPLAN-CORE-01-12 — Lifecycle request state machine (INTERNAL_ONLY)

**STATUS: COMPLETED — implemented and merged via [PR #453](https://github.com/KayzenRoot/stormline/pull/453), merge `5ef63600fb42ae6f1f65c095e92c5fba7d87f89f`. This packet must not be re-executed; no next packet or module is authorized.** **Gate:** G6 individual, granted by [PR #452](https://github.com/KayzenRoot/stormline/pull/452). **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-12`. **Predecessor:** `-11` `COMPLETED` via PR #450. **Issue:** #18. **Base:** `df551006982868e616d867c7daaa3fc5a7c51ee8`. **ADR:** [ADR-0091](../adr/0091-core-01-lifecycle-request-state-machine.md). **Contract:** [core-01-lifecycle-requests-v0](../contracts/core-01-lifecycle-requests-v0.md).

## OBJECTIVE

Implement an owner-thread lifecycle request state machine for suspend/resume/shutdown/terminate, with typed transitions and observation of quit/window-close host events, without OS signal handlers, forced process kill or persistence.

## CONTEXT

`-07`..`-11` delivered SDL runtime, window, event queue, display/surface and native handle bridge. C01-D07 requires an explicit lifecycle state machine, typed errors and idempotent cleanup. This packet is the request/transition contract only; physical OS sleep/resume, termination, save/persistence and renderer device-loss recovery remain out of scope.

## SCOPE

- `LifecycleState`, `LifecycleError`, `LifecycleController`; owner-thread typed transitions.
- Running → SuspendPending → Suspended → ResumePending → Running; shutdown from running/suspended states → ShutdownPending → Terminated; explicit `request_terminate`.
- `observe(InputEvent)` maps Quit/WindowCloseRequested to shutdown; other events ignored.
- `should_continue()` and `state()` queries; no forced transition in destructor.
- Tests LCY-01..LCY-06, existing 53 CTests regression, Linux ASan/UBSan, Evidence Bundle.

## OUT OF SCOPE

OS sleep/resume hooks, signal handlers, forced process kill, persistence/save, renderer/device-loss recovery, window teardown, clipboard/IME/hotplug, public ABI/plugin SDK, packaging/release, other modules or packets.

## FILES / SOURCES TO READ

`AGENTS.md`; checkpoint; Ledger/ADRs 0003/0075/0083..0091; Scope/DoD/Architecture/Requirements; CORE-01 architecture and C01-D07; SDL3 runtime/window/event/display/native contracts; this gate's ADR/contract/activation; completed CORE-01 code/tests/CMake/CI evidence. Inspect Git before editing.

## REQUIREMENTS

GOV-001..005, CAP-010/014, NFR-002/003/005; C01-D07 bounded; CORE-01 catalog acceptance. No new owner technology decision beyond the bounded internal state machine and existing CI; no OS signal/termination/persistence.

## ARCHITECTURE RULES

Internal namespace/header only; standard/event-queue headers only; owner-thread mutation; explicit transition table; typed errors; no exception across the boundary; no global state/singleton/signal handler/hidden thread; no forced transition in destructor; no persistence or process control. Existing headless/paths/SDL/window/event/display/native/memory targets preserved.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`. C++20/CMake/CTest only; no package installation, paid runner, secret, upload, runtime download or release. Standard public CI on `ubuntu-24.04`, `windows-2025-vs2026`, `macos-15`; Linux ASan/UBSan. ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## ACCEPTANCE CRITERIA

- Exact allowlist; fresh Context Lock; selector ready only for `NLE-PRPLAN-CORE-01-12`.
- Transition table implemented exactly; invalid transitions leave state unchanged; idempotent shutdown; terminated repeats typed.
- Quit/WindowCloseRequested drive shutdown; other events ignored; wrong-thread rejected.
- LCY-01..LCY-06 on Linux, Linux ASan/UBSan, Windows and macOS; existing 53 CTests regression; no OS signal/termination/persistence/ABI/release overclaim.
- Docs Validation + native CI PASS at exact PR HEAD; no HIGH/CRITICAL; pt-BR audit; squash/readback.

## TESTS

Docs: `validate_docs.py`, `validate_wo_registry.py`, `validate_pr_plans.py`, unit tests, packet selector. Native: `LCY-01` normal, `LCY-02` shutdown, `LCY-03` events, `LCY-04` invalid, `LCY-05` wrong-thread, `LCY-06` recovery/regression; CMake Presets; ASan/UBSan on Linux. Exact commands: `cmake --preset core01-internal-debug`, `cmake --build --preset core01-internal-debug`, `ctest --preset core01-internal-debug --output-on-failure`, plus the asan preset.

## DELIVERABLES

Exactly: `src/stormline/core/internal/lifecycle.hpp`, `lifecycle.cpp`, `tests/core/lifecycle_tests.cpp`, `CMakeLists.txt` (additive), `.github/workflows/core01-internal-headless.yml` (additive CORE-01-12 path filters), `docs/evidence/NLE-PRPLAN-CORE-01-12.md`. GitHub PR, exact CI receipts, Evidence, pt-BR audit, proposed checkpoint. Gate files separate.

## REVIEW FORMAT

Portuguese Brazil: base/head, exact files, contract compliance, LCY matrix, transition/event/wrong-thread/recovery evidence, existing regression, sanitizer, no OS signal/termination/persistence/ABI/release overclaim, risk/security. Verdict `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`. Corrections only in the same WO/PR.

## STOP CONDITION

STALE context, gate not merged, selector blocked, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, OS signal/termination/persistence/ABI/release overclaim, another packet/module unlock, or destructive operation. Never bypass G2 or force push.

## CONTEXT LOCK

Gate base `df551006982868e616d867c7daaa3fc5a7c51ee8`; activation pins the exact ADR/contract/source blobs. Executor must recompute fresh raw SHA-256 after the gate merge and stop/rebase on substantive change.

## EVIDENCE BUNDLE

Separate `docs/evidence/NLE-PRPLAN-CORE-01-12.md` with PR/CI/audit/merge SHAs, exact files, transition/event/wrong-thread/recovery results, LCY-01..06, regression, sanitizer, limitations and rollback. Gate evidence never masquerades as implemented code.
