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
- SDL runtime process-local owner and live-window accounting. Reject a second owner, reject video initialization off SDL main thread, block explicit shutdown with live Window (typed `WindowsActive`), and defer no-throw destructor SDL_Quit until the last live Window is destroyed.
- Generate process-unique nonzero native and surface tokens; cache issued native kind/value/generation; reject foreign/forged/obsolete tokens and generation reuse.
- Tests make missing required Cocoa server a qualification failure, not a green CTest.
- Exactly allowed source/tests/WO/Evidence files; no CMake/workflow/manifest/registry/source license/ADR modifications.

## Tests and checks
- Documentation validator: [run #44356126944](https://github.com/KayzenRoot/stormline/actions/runs/44356126944) SUCCESS after correcting a first-pass missing final newline in the Work Order. The earlier docs failure was a formatting problem introduced in this PR, now fixed.
- Corrected native Linux, Linux ASan/UBSan, Windows, macOS: **PENDING**, [run #44356127049](https://github.com/KayzenRoot/stormline/actions/runs/44356127049) in progress. Do not mark PASS until exact HEAD receipts are read.
- Check physical hardware, real Wayland runtime, IME/hotplug/long soak, distribution and release remain NOT_QUALIFIED.

## Risk, rollback and audit
- Unsafe teardown previously allowed lifetime invalidation of a `SDL_Window*`. Regression test deliberately exits before use of that pointer.
- New SDL process-state is restricted to main-thread adapter internals; not a public engine singleton or ABI. Its deferred-quit branch must pass ASan/UBSan, native CI and audit.
- Rollback: close unmerged PR; after merge require a normal revert PR, no force-push.
- Exact-HEAD pt-BR audit: **PENDING**. Do not merge while CI red, tests skipped as PASS, or HIGH/CRITICAL is known.
- Proposed Checkpoint Delta: record this corrective PR and evidence only after APPROVED, in a separate authorized checkpoint PR if required; **not promoted**.
