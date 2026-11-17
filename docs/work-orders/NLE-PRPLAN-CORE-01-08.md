# NLE-PRPLAN-CORE-01-08 — Native window lifecycle (INTERNAL_ONLY)

**STATUS: COMPLETED — implemented and merged via [PR #438](https://github.com/KayzenRoot/stormline/pull/438), merge `69d1f96eb9df36a56eb4a0d34cc452bf11095cb1`. This packet must not be re-executed; no next packet or module is authorized.**

**Gate:** G6 individual, conditional on gate PR audit/merge and executor fresh Source Check. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-08`. **Predecessor:** `-07` `COMPLETED` via PR #435. **Issue:** #18. **Base:** `b54f19c252fda9c06a7d7289a853bd4cf957cf53`. **ADR:** [ADR-0085](../adr/0085-core-01-window-lifecycle-slice.md). **Contract:** [core-01-window-lifecycle-v0](../contracts/core-01-window-lifecycle-v0.md).

## OBJECTIVE

Implement the first real native window lifecycle through SDL3: create/resize/show/raise-focus/destroy with verified handle lifetime, typed errors, main-thread ownership and no SDL types in the internal header.

## CONTEXT

`-03`..`-06` delivered the headless host, typed lifecycle and paths; `-07` delivered SDL3 init/quit with a dummy/offscreen-only build. The owner authorized real installation for the window slice and capability-based L1 dependencies. This packet is the window lifecycle only; renderer/GPU/audio/input pump/DPI/IME/hotplug remain out of scope.

## SCOPE

- X11 + Wayland video drivers built on Linux; Win32 on Windows; Cocoa on macOS; real window create/resize/show/focus-request/destroy.
- Internal `WindowConfig`, `WindowError`, `Window`; owner thread; `SdlRuntime` must be initialized and outlive the window; no SDL types in the header.
- Linux CI installs the exact X11/Wayland dev packages and runs Xvfb + openbox; Windows/macOS use native drivers; Wayland runtime `NOT_QUALIFIED`.
- Tests WIN-01..WIN-08, existing 18 CTests regression, ASan/UBSan Linux, evidence/checkpoint.

## OUT OF SCOPE

Renderer/swapchain, GPU/Vulkan/Metal/OpenGL, audio, event pump/replay, multi-monitor/DPI, IME, hotplug, OS-specific bridges, sleep/resume, public C ABI/plugin/SDK, physical display/driver certification, packaging/release, other modules, next packet.

## FILES / SOURCES TO READ

`AGENTS.md`; checkpoint; Ledger/ADRs 0003/0075/0083/0084/0085; Scope/DoD/Architecture/Requirements; CORE-01 gates and C01-D03/D04; SDL3 runtime/window contracts; PR-plan manifest/activation; merged `-03`/`-06`/`-07` code/tests/CMake/CI evidence; SDL3 3.4.20 official window headers and license at the pinned commit. Inspect Git before editing.

## REQUIREMENTS

GOV-001..005, CAP-010/014, NFR-002/003/005; C01-D03/D04 bounded; CORE-01 catalog acceptance for window lifecycle. No new owner technology decision beyond the authorized SDL3/X11/Win32/Cocoa direction and Linux package installation.

## ARCHITECTURE RULES

Internal namespace/header only; SDL hidden in `window.cpp`; no SDL type/macro/handle in the header; main-thread ownership; typed errors; no exceptions across the boundary; no global window/singleton; no renderer/GPU/audio/network call; `SdlRuntime` separate and must outlive the window. Existing headless/paths/SDL-init targets preserved.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`. SDL3 3.4.20 static build-time fetch; exact Linux package list from the contract; no paid runner, secret, upload, runtime download or release. Standard public CI on `ubuntu-24.04`, `windows-2025-vs2026`, `macos-15`; Linux ASan/UBSan. ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80 module WOs `BLOCKED`.

## ACCEPTANCE CRITERIA

- Exact allowlist; fresh Context Lock; selector ready only for `-08`.
- `Window` contract implemented; no SDL types in header; owner-thread rejection; duplicate create/invalid sizes/idempotent destroy; `VideoNotInitialized` when runtime absent.
- WIN-01..WIN-08 executed with real X11 (Xvfb/openbox), Win32 and Cocoa where available; Wayland build-only `NOT_QUALIFIED`; 50 lifecycle cycles; existing 18 CTests regression.
- Docs Validation + native CI PASS at exact PR HEAD; no HIGH/CRITICAL; pt-BR audit; squash/readback; no renderer/GPU/audio/release/ABI claim.

## TESTS

Docs: `validate_docs.py`, `validate_wo_registry.py`, `validate_pr_plans.py`, unit tests, packet selector. Native: window lifecycle modes, invalid/duplicate/wrong-thread/video-not-initialized, 50 cycles, existing 18 CTests; CMake Presets; Linux ASan/UBSan when supported. Real macOS window may be `NOT_QUALIFIED` if no window server; Wayland runtime `NOT_QUALIFIED`.

## DELIVERABLES

Exactly: `src/stormline/core/internal/window.hpp`, `window.cpp`, `tests/core/window_tests.cpp`, `CMakeLists.txt` (additive), `.github/workflows/core01-internal-headless.yml` (exact install/Xvfb/timeout), `docs/evidence/NLE-PRPLAN-CORE-01-08.md`. GitHub PR, exact CI receipts, Evidence, pt-BR audit, proposed checkpoint. Gate files separate.

## REVIEW FORMAT

Portuguese Brazil: base/head, exact files, contract compliance, WIN matrix, install/package provenance, real driver evidence, existing regression, sanitizer, no SDL leak, no renderer/GPU/audio overclaim, risk/security. Verdict `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`. Corrections only in the same WO/PR.

## STOP CONDITION

STALE context, gate not merged, selector blocked, install failure, SDL3 fetch/build mismatch, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, renderer/GPU/audio/release/ABI overclaim, another packet/module unlock, or destructive operation. Never bypass G2 or force push.

## CONTEXT LOCK

Gate base `b54f19c252fda9c06a7d7289a853bd4cf957cf53`; activation pins the exact ADR/contract/source blobs, SDL3 commit and window/install matrix. Executor must recompute fresh raw SHA-256 after the gate merge and stop/rebase on substantive change.

## EVIDENCE BUNDLE

Separate `docs/evidence/NLE-PRPLAN-CORE-01-08.md` with PR/CI/audit/merge SHAs, exact packages, X11/Xvfb/openbox evidence, Win32/Cocoa results, WIN-01..08, regression, sanitizer, no-SDL-leak proof, limitations and rollback. Gate evidence never masquerades as implemented code.
