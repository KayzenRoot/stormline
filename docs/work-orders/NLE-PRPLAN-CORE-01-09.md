# NLE-PRPLAN-CORE-01-09 — Event queue and replay (INTERNAL_ONLY)

**STATUS: EXECUTOR_READY ONLY AFTER THE GATE PR PASSES DOCS VALIDATION, PT-BR AUDIT AND SQUASH MERGE; not executable while the manifest is in a blocked state.** **Gate:** G6 individual, conditional on that merge and a fresh executor Source Check. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-09`. **Predecessor:** `-08` `COMPLETED` via PR #438. **Issue:** #18. **Base:** `27cd592ec235a63def60f04757ac27700babd334`. **ADR:** [ADR-0088](../adr/0088-core-01-event-queue-slice.md). **Contract:** [core-01-event-queue-v0](../contracts/core-01-event-queue-v0.md).

## OBJECTIVE

Implement the first real CORE-01 host-event path: normalize selected SDL3 events into internal values, enqueue them in a fixed-capacity queue with monotonic sequence/timestamps, surface overflow without silent loss, and replay captured events deterministically.

## CONTEXT

`-07` delivered SDL3 runtime init/quit and `-08` the native window lifecycle; both are completed and merged. C01-D03 includes system events through the thin SDL adapter, and C01-D04 requires the main/owner thread. This packet is the event queue/replay only; gameplay input mapping, physical-device qualification, gamepad, IME, DPI and hotplug remain out of scope.

## SCOPE

- Internal `InputEventType`, `InputEvent`, `EventError`, `EventQueue` (fixed capacity 256, no dynamic allocation).
- `poll()` normalizes quit, key down/up, mouse motion/button, window resized/focus/close; skips other SDL events; owner-thread only; `SDL_WasInit(SDL_INIT_EVENTS)` required.
- Monotonic internal sequence; SDL event timestamp; full queue returns `Overflow` before consuming SDL events; remaining SDL events stay queued.
- `replay()` preserves captured sequence/timestamp, validates monotonicity/type/capacity atomically, and rejects invalid input.
- `pop()`, `clear()`, `size()`, `empty()`, `next_sequence()`.
- Tests EVT-01..EVT-08, existing 32 CTests regression, Linux ASan/UBSan, Evidence Bundle.

## OUT OF SCOPE

Gameplay input mapping/action bindings, gamepad/joystick, text input/IME, DPI, hotplug, fullscreen, clipboard, drag-and-drop, blocking event loop, frame/tick scheduling, physical keyboard/mouse/gamepad certification, public ABI/plugin SDK, packaging/release, other modules or packets.

## FILES / SOURCES TO READ

`AGENTS.md`; checkpoint; Ledger/ADRs 0003/0075/0083..0088; Scope/DoD/Architecture/Requirements; CORE-01 architecture and C01-D03/D04; SDL3 runtime/window contracts; this gate's ADR/contract/activation; completed CORE-01 code/tests/CMake/CI evidence; SDL3 3.4.20 event headers at the pinned commit. Inspect Git before editing.

## REQUIREMENTS

GOV-001..005, CAP-010/014, NFR-002/003/005; C01-D03/D04 bounded; CORE-01 catalog acceptance. No new owner technology decision beyond the already authorized SDL3 adapter and synthetic event testing; no gameplay mapping or third-party dependency.

## ARCHITECTURE RULES

Internal namespace/header only; SDL hidden in `event_queue.cpp`; no SDL type/macro/handle in the header; owner-thread mutation; typed errors; no exception across the boundary; fixed capacity and no allocation in the event path; no silent drop; no global state/singleton/filter/thread; `SdlRuntime` separate and must outlive the queue. Existing headless/paths/SDL/window/memory targets preserved.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`. SDL3 3.4.20 static build-time fetch; no package installation, paid runner, secret, upload, runtime download or release. Standard public CI on `ubuntu-24.04`, `windows-2025-vs2026`, `macos-15`; Linux ASan/UBSan. ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## ACCEPTANCE CRITERIA

- Exact allowlist; fresh Context Lock; selector ready only for `NLE-PRPLAN-CORE-01-09`.
- `EventQueue` contract implemented; no SDL types in header; owner-thread rejection; fixed capacity; overflow surfaced; replay atomic and deterministic; no silent drop.
- EVT-01..EVT-08 executed on Linux, Linux ASan/UBSan, Windows and macOS; existing 32 CTests regression; synthetic SDL events; no physical-input/gamepad/IME/DPI/hotplug overclaim.
- Docs Validation + native CI PASS at exact PR HEAD; no HIGH/CRITICAL; pt-BR audit; squash/readback; no public ABI/release claim.

## TESTS

Docs: `validate_docs.py`, `validate_wo_registry.py`, `validate_pr_plans.py`, unit tests, packet selector. Native: `EVT-01` basic, `EVT-02` sequence, `EVT-03` overflow, `EVT-04` replay, `EVT-05` rejection, `EVT-06` wrong-thread, `EVT-07` runtime/empty/clear, `EVT-08` lifetime/regression; CMake Presets; ASan/UBSan on Linux. Exact commands: `cmake --preset core01-internal-debug`, `cmake --build --preset core01-internal-debug`, `ctest --preset core01-internal-debug --output-on-failure`, plus the asan preset.

## DELIVERABLES

Exactly: `src/stormline/core/internal/event_queue.hpp`, `event_queue.cpp`, `tests/core/event_queue_tests.cpp`, `CMakeLists.txt` (additive), `.github/workflows/core01-internal-headless.yml` (additive CORE-01-09 path filters), `docs/evidence/NLE-PRPLAN-CORE-01-09.md`. GitHub PR, exact CI receipts, Evidence, pt-BR audit, proposed checkpoint. Gate files separate.

## REVIEW FORMAT

Portuguese Brazil: base/head, exact files, contract compliance, EVT matrix, real SDL event injection, overflow/replay/wrong-thread/sequence evidence, existing regression, sanitizer, no SDL leak, no physical-input/gamepad/IME/DPI/hotplug overclaim, risk/security. Verdict `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`. Corrections only in the same WO/PR.

## STOP CONDITION

STALE context, gate not merged, selector blocked, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, SDL type in the header, silent event drop, physical-input/gamepad/IME/DPI/hotplug overclaim, public ABI/release, another packet/module unlock, or destructive operation. Never bypass G2 or force push.

## CONTEXT LOCK

Gate base `27cd592ec235a63def60f04757ac27700babd334`; activation pins the exact ADR/contract/source blobs and SDL3 commit. Executor must recompute fresh raw SHA-256 after the gate merge and stop/rebase on substantive change.

## EVIDENCE BUNDLE

Separate `docs/evidence/NLE-PRPLAN-CORE-01-09.md` with PR/CI/audit/merge SHAs, exact files, normalization/sequence/overflow/replay/wrong-thread results, EVT-01..08, regression, sanitizer, limitations and rollback. Gate evidence never masquerades as implemented code.
