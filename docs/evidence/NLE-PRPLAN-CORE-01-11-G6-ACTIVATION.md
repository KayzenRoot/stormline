# NLE-PRPLAN-CORE-01-11 — G6 activation (native window-handle bridge)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `44b37d4b6e67314e7317257707a3064bd69c6830`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-11`. **ADR:** [ADR-0090](../adr/0090-core-01-native-window-handle-bridge.md). **Contract:** [core-01-native-window-handle-v0](../contracts/core-01-native-window-handle-v0.md). **WO:** [NLE-PRPLAN-CORE-01-11](../work-orders/NLE-PRPLAN-CORE-01-11.md).

## Owner authorization

The owner explicitly authorized continuing and unlocking what is necessary on 2026-11-17 (`autorizo tudo que for preciso continue`). C01-D03 (narrow SDL native integration), C01-D04 (owner/main-thread video calls) and C01-D06 (opaque internal handles) are owner-ratified bounded directions. This gate activates **only** `NLE-PRPLAN-CORE-01-11` after exact-head Docs Validation, objective pt-BR audit and squash/readback.

It does not approve ADR-0003/0075 globally, clear G3, authorize a direct Win32/Cocoa/Wayland/X11 implementation, OS permission/sandbox bypass, renderer/GPU/VRAM, clipboard/DnD/IME/hotplug, public ABI/release, or another packet/module.

## Predecessors

`-03` headless host PR #428; `-04`/`-05` reconciled; `-06` paths PR #432; `-07` SDL3 runtime PR #435; `-08` window lifecycle PR #438; `-09` event queue PR #444; `-10` display/surface PR #447. All `COMPLETED`; no predecessor reopened. CORE-02-03 ownership is also `COMPLETED` via PR #441 and unaffected.

## Bounded technical slice

- `NativeWindowSystem`, `NativeHandleKind`, `NativeWindowHandle`, `current_native_window_system()`; no SDL types in headers.
- Additive `Window::query_native_handle`/`native_handle_valid`; maps Win32 HWND, Cocoa NSWindow, Wayland wl_surface and X11 window number from SDL window properties.
- Non-owning opaque token with kind/value/generation; destroy invalidates; resize does not; dummy driver → `NativeHandleUnavailable`.
- No direct OS headers/ABIs, permission model, renderer/VRAM, clipboard/DnD/IME/hotplug, public ABI or release.
- Exact code allowlist: `native_bridge.hpp`, `native_bridge.cpp`, additive `window.hpp`/`window.cpp`, `tests/core/native_bridge_tests.cpp`, additive `CMakeLists.txt`, additive workflow filters, `docs/evidence/NLE-PRPLAN-CORE-01-11.md`.

## Gate state after merge (expected, not yet promoted)

- Manifest root `CORE01_11_READY_PREDECESSORS_COMPLETED`: **734 `PLANNED_BLOCKED`, 9 `COMPLETED` (CORE-01 -03..-10 + CORE-02-03), 4 approved gate entries, 1 `EXECUTOR_READY` (`CORE-01-11`)**.
- `select_packet.py NLE-PRPLAN-CORE-01-11` → exit 0; every other ID, including `-12` and `CORE-02-04`, exit 2.
- 80/80 module WOs remain `BLOCKED`; registry unchanged; ADR-0003/0075 `PROPOSED`; ADR-0090 bounded; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; `engine_implemented=false` at module/product level.

## Proof obligations for the code PR

NBI-01..NBI-06: native system mapping; native handle kind/value/generation; dummy unavailable; wrong-thread/not-created; destroy invalidation; 50-cycle lifetime and existing 47 CTests regression. Real Linux X11, Win32, Cocoa where available; Linux ASan/UBSan; no SDL in headers; no ownership transfer or direct-OS/ABI/release claim; exact-head Docs Validation and pt-BR audit.

No code or native PASS is claimed by this gate.

## Security and rollback

No dependency, package installation, secret, upload, paid service or runtime download. The exposed handle is non-owning; the caller must not free/close it. Unmerged: close the gate branch; `main` untouched. After merge: normal revert PR, never force push. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
