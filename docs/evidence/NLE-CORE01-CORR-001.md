# NLE-CORE01-CORR-001 — Evidence Bundle (in progress)

**Work Order:** [NLE-CORE01-CORR-001](../work-orders/NLE-CORE01-CORR-001.md)  
**PR:** [#477](https://github.com/KayzenRoot/stormline/pull/477), DRAFT / NOT MERGED  
**Base main:** `84c8e2f838c2d2ee80f2079c4f60da096ee8f1b3` (fresh source check 2026-11-18)  
**Risk:** ELEVATED (unsafe SDL video shutdown may invalidate SDL_Window pointer).  
**Authorization:** owner explicitly requested a single corrective WO and PR with tests-first, exact allowlist and pt-BR audit on 2026-11-18.

## Context Lock / source check
- Checkpoint Git blob `b1cbd30076eeabb21b67fa1d1c85ca39ee660630`.
- Ledger `01aa967790dc1ea5e72c2ebebae7b832ec579981`; Scope `0b65820507d946d2b2b4ed3a2b869e60cafaaf22`.
- DoD `e0b7c2466ebec9790a715e47490c015cfb502db4`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`.
- ADR-0003 `50d028c7a28acc25164256c5f4547c14ac7192d4`; ADR-0085 `e4ba773dadd33a4fa439a8da988eac02850c2d2a`.
- Manifest `dc01d3ccc62e857feeb61b3be599f66ae2c08c44`: 19 COMPLETED, 725 PLANNED_BLOCKED, 2 APPROVED_GOVERNANCE, 2 APPROVED_CONTRACT, 0 EXECUTOR_READY. Registry `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`: 80/80 module WOs BLOCKED and engine_implemented=false. Both are untouched.

## Test before fix / verified reproduced baseline
- Regression-only commit `e05b2fd9ec1aa3a1b6cfcbe2a9d64894b7596750` in same PR.
- Native Actions [run #44354723368](https://github.com/KayzenRoot/stormline/actions/runs/44354723368): on Linux, Windows and macOS new tests report:
  - `core01_sdl_basic`: duplicate SdlRuntime instance was permitted to initialize process-global SDL.
  - `core01_window_basic`: SDL_Quit succeeded while a Window was still alive. Test terminates its own process immediately to avoid UAF in reproduction.
  - `core01_native_handle`: forged value and foreign window's handle accepted.
  - `core01_native_lifetime`: stale native handle accepted after destroy/recreate (ABA).
- The red result is the **required proof of defect before repair**, not a passing baseline. Other existing CTests were retained.
- The original `window.cpp` also reset per-create `surface_generation=1`, so generation ABA risk is present; regression now covers original and resized surface tokens.
- A Source Check additionally found `core01_soak_tests.cpp` and `core01_qualification_tests.cpp` returning `true` after `NOT_QUALIFIED: cocoa runtime unavailable`. Scoped CD-01 adds them to the test allowlist; no module expansion.

## Correction Delta
- SDL runtime uses SDL-owned `SDL_WasInit` to reject a second owner and `SDL_GetWindows` to block explicit shutdown while any SDL window remains (typed `WindowsActive`); avoids SDL_Quit on an unsupported wrong-order destructor to prevent invalidation. `SDL_IsMainThread` ensures actual SDL video main-thread behavior. No new global mutable adapter state.
- Generate nonzero native and surface tokens from SDL-owned `SDL_GetWindowID` plus a persistent `Window` instance-local revision counter; cache issued native kind/value/generation to reject foreign/forged/obsolete tokens and same-object destroy/recreate ABA, without a new process-global registry.
- Tests make missing required Cocoa server a qualification failure, not a green CTest.
- Exactly allowed source/tests/WO/Evidence files; no CMake/workflow/manifest/registry/source license/ADR modifications.

## Tests and checks
- Documentation validator: [run #44356126944](https://github.com/KayzenRoot/stormline/actions/runs/44356126944) SUCCESS after correcting a first-pass missing final newline in the Work Order. The earlier docs failure was a formatting problem introduced in this PR, now fixed.
- Interim corrected CI [run #44356586024](https://github.com/KayzenRoot/stormline/actions/runs/44356586024) on superseded implementation: **92/92 CTest** on Linux, Linux ASan/UBSan, Windows, macOS. **That implementation was subsequently revised after architecture audit** and is no longer proof of the current branch. The newer architecture-compliant corrected HEAD requires **NEW EXACT-HEAD CI** before approval; do not claim PASS prematurely. Initial red reproduction remains [run #44354723368](https://github.com/KayzenRoot/stormline/actions/runs/44354723368).
- Check physical hardware, real Wayland runtime, IME/hotplug/long soak, distribution and release remain NOT_QUALIFIED.

## Risk, rollback and audit
- Unsafe teardown previously allowed lifetime invalidation of a `SDL_Window*`. Regression test deliberately exits before use of that pointer.
- No new mutable process-global Stormline adapter state remains, as the approved runtime/window contracts prohibit it. SDL-owned global state is queried on the main thread. Supported lifetime still requires Window teardown before SdlRuntime destruction; wrong destructor order fails safe by not calling SDL_Quit, but leaves an unsupported cleanup obligation, not a product guarantee.
- Rollback: close unmerged PR; after merge require a normal revert PR, no force-push.
- Exact-HEAD pt-BR audit: **PENDING** until this Evidence update's own Docs/native CI checks complete. The proof of current code is 92/92 CTest per OS on the immediately prior HEAD; validate again on the final PR head. Do not merge while CI red, tests skipped as PASS, or HIGH/CRITICAL is known.
- Proposed Checkpoint Delta: record this corrective PR and evidence only after APPROVED, in a separate authorized checkpoint PR if required; **not promoted**.

## Changed-file review / correction scope
12 total changed paths: 4 production files (`sdl_runtime.hpp/.cpp`, `window.hpp/.cpp`), 6 test files (`sdl_runtime_tests.cpp`, `window_tests.cpp`, `native_bridge_tests.cpp`, `display_tests.cpp`, `core01_soak_tests.cpp`, `core01_qualification_tests.cpp`) and this Evidence plus WO. No CMake, workflow, manifest, activation, registry, ledger, license, source hierarchy, or ADR mutation. A proposed checkpoint update is explicitly deferred to a separate audited PR if this correction is APPROVED and merged.

## Contract compliance check (CD-02)
The approved `core-01-sdl3-runtime-v0.md` and `core-01-window-lifecycle-v0.md` prohibit mutable global adapter state and require that SdlRuntime outlive Window. The first green attempt introduced a private global ProcessState to defer SDL_Quit and was **not approved** despite green tests. That architecture violation was corrected in the same PR. SDL `SDL_GetWindows` provides the authoritative window count; `SDL_GetWindowID` provides a native per-window identifier; the per-Window revision counter persists across recreation, without global mutable state. Unsupported destructor order does not produce a claim of full recovery. Exact-head CI and audit pending.
