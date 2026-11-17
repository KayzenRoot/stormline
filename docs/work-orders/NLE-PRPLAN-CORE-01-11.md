# NLE-PRPLAN-CORE-01-11 — Opaque native window-handle bridge (INTERNAL_ONLY)

**STATUS: COMPLETED — implemented and merged via [PR #450](https://github.com/KayzenRoot/stormline/pull/450), merge `b062053a2d1513c39ac49d101e6eb189570b51f6`. This packet must not be re-executed; no next packet or module is authorized.** **Gate:** G6 individual, granted by [PR #449](https://github.com/KayzenRoot/stormline/pull/449). **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-11`. **Predecessor:** `-10` `COMPLETED` via PR #447. **Issue:** #18. **Base:** `44b37d4b6e67314e7317257707a3064bd69c6830`. **ADR:** [ADR-0090](../adr/0090-core-01-native-window-handle-bridge.md). **Contract:** [core-01-native-window-handle-v0](../contracts/core-01-native-window-handle-v0.md).

## OBJECTIVE

Implement the first internal platform-native window-handle bridge: identify the active window system, obtain the SDL-owned native window handle as an opaque non-owning token, and validate it against the live window lifetime.

## CONTEXT

`-07`..`-10` delivered SDL runtime, window, event queue and display/surface metadata. C01-D03 includes native OS integration through the thin SDL adapter, C01-D04 requires owner-thread calls, and C01-D06 requires opaque internal handles. This packet is the handle bridge only; direct Win32/Cocoa/Wayland/X11 code, renderer/VRAM, permissions, clipboard, DnD, IME and hotplug remain out of scope.

## SCOPE

- `NativeWindowSystem`, `NativeHandleKind`, `NativeWindowHandle`, `current_native_window_system()`; no SDL types in header.
- Additive `Window::query_native_handle`/`native_handle_valid`; Win32 HWND, Cocoa NSWindow, Wayland wl_surface, X11 window number mapped from SDL window properties.
- Non-owning opaque token with kind/value/generation; destroy invalidates; resize does not.
- Tests NBI-01..NBI-06, existing 47 CTests regression, Linux ASan/UBSan, Evidence Bundle.

## OUT OF SCOPE

Direct Win32/Cocoa/Wayland/X11 API implementation, renderer/swapchain/GPU/VRAM, OS permission/sandbox model, multiple native windows, clipboard, drag-and-drop, IME, hotplug, public ABI/plugin SDK, packaging/release, other modules or packets.

## FILES / SOURCES TO READ

`AGENTS.md`; checkpoint; Ledger/ADRs 0003/0075/0083..0090; Scope/DoD/Architecture/Requirements; CORE-01 architecture and C01-D03/D04/D06; SDL3 runtime/window/event/display contracts; this gate's ADR/contract/activation; completed CORE-01 code/tests/CMake/CI evidence; SDL3 3.4.20 native window properties at the pinned commit. Inspect Git before editing.

## REQUIREMENTS

GOV-001..005, CAP-010/014, NFR-002/003/005; C01-D03/D04/D06 bounded; CORE-01 catalog acceptance. No new owner technology decision beyond the authorized SDL3 native-property bridge and existing CI; no direct OS ABI/dependency.

## ARCHITECTURE RULES

Internal namespace/header only; SDL hidden in `.cpp`; no SDL type/macro/handle in headers; owner-thread window query; opaque non-owning token; explicit generation/lifetime; typed errors; no exception across the boundary; no global state/singleton/hidden thread; no ownership transfer of OS handles. Existing headless/paths/SDL/window/event/display/memory targets preserved.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`. SDL3 3.4.20 static build-time fetch; no package installation, paid runner, secret, upload, runtime download or release. Standard public CI on `ubuntu-24.04`, `windows-2025-vs2026`, `macos-15`; Linux ASan/UBSan. ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## ACCEPTANCE CRITERIA

- Exact allowlist; fresh Context Lock; selector ready only for `NLE-PRPLAN-CORE-01-11`.
- Native system mapping and handle query implemented; no SDL types in headers; non-owning token; generation invalidated on destroy; wrong-thread/not-created/unavailable typed.
- NBI-01..NBI-06 on Linux, Linux ASan/UBSan, Windows and macOS; dummy-driver unavailable path; existing 47 CTests regression; no direct-OS/permission/renderer/ABI/release overclaim.
- Docs Validation + native CI PASS at exact PR HEAD; no HIGH/CRITICAL; pt-BR audit; squash/readback.

## TESTS

Docs: `validate_docs.py`, `validate_wo_registry.py`, `validate_pr_plans.py`, unit tests, packet selector. Native: `NBI-01` system, `NBI-02` handle, `NBI-03` dummy/unavailable, `NBI-04` wrong-thread/errors, `NBI-05` destroy invalidation, `NBI-06` lifetime/regression; CMake Presets; ASan/UBSan on Linux. Exact commands: `cmake --preset core01-internal-debug`, `cmake --build --preset core01-internal-debug`, `ctest --preset core01-internal-debug --output-on-failure`, plus the asan preset.

## DELIVERABLES

Exactly: `src/stormline/core/internal/native_bridge.hpp`, `native_bridge.cpp`, additive `window.hpp`/`window.cpp`, `tests/core/native_bridge_tests.cpp`, `CMakeLists.txt` (additive), `.github/workflows/core01-internal-headless.yml` (additive CORE-01-11 path filters), `docs/evidence/NLE-PRPLAN-CORE-01-11.md`. GitHub PR, exact CI receipts, Evidence, pt-BR audit, proposed checkpoint. Gate files separate.

## REVIEW FORMAT

Portuguese Brazil: base/head, exact files, contract compliance, NBI matrix, native handle kind/lifetime/destroy evidence, dummy path, existing regression, sanitizer, no SDL leak, no direct-OS/permission/renderer/ABI/release overclaim, risk/security. Verdict `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`. Corrections only in the same WO/PR.

## STOP CONDITION

STALE context, gate not merged, selector blocked, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, SDL type in a header, OS-handle ownership/double-free, direct-OS/permission/renderer/ABI/release overclaim, another packet/module unlock, or destructive operation. Never bypass G2 or force push.

## CONTEXT LOCK

Gate base `44b37d4b6e67314e7317257707a3064bd69c6830`; activation pins the exact ADR/contract/source blobs and SDL3 commit. Executor must recompute fresh raw SHA-256 after the gate merge and stop/rebase on substantive change.

## EVIDENCE BUNDLE

Separate `docs/evidence/NLE-PRPLAN-CORE-01-11.md` with PR/CI/audit/merge SHAs, exact files, system/handle/dummy/wrong-thread/destroy/lifetime results, NBI-01..06, regression, sanitizer, limitations and rollback. Gate evidence never masquerades as implemented code.
