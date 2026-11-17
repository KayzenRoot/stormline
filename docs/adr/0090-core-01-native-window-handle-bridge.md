# ADR-0090 — CORE-01 opaque native window-handle bridge

**Status:** `OWNER_DIRECTION_C01_D03_C01_D04_C01_D06_BOUNDED / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **This ADR is subordinate to and DOES NOT approve ADR-0003 or ADR-0075 as a whole, and does not clear G3 globally.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-01-11` | **Parent:** `NLE-PRPLAN-CORE-01-01` | **Issue:** #387 / implementation issue #18.

## Context and authority

C01-D03 includes native OS integration through a narrow SDL adapter, C01-D04 requires main/owner-thread video calls, and C01-D06 requires opaque internal handles/RAII rather than a universal C++ ABI. The `-07`..`-10` slices are completed. The next formal CORE-01 packet is `-11`: platform-specific OS bridges.

This slice is bounded to an **opaque native window-handle bridge**: identify the active window system, obtain the platform window handle that SDL already exposes, and validate it against the current window lifetime. It does not implement a direct Win32/Cocoa/Wayland/X11 API layer, renderer surface creation, permission model, clipboard, drag-and-drop, IME, hotplug or public ABI.

## Bounded technical decision

- New internal `NativeWindowSystem`, `NativeHandleKind`, `NativeWindowHandle` types and `current_native_window_system()` in `native_bridge.hpp/cpp`; no SDL type/macro/handle in the header.
- `NativeWindowHandle` is an **opaque non-owning token**: kind, numeric value and generation. The caller must not free or reinterpret-own the platform handle; ownership remains with SDL/the OS/window.
- Additive `Window::query_native_handle` and `Window::native_handle_valid`:
  - owner-thread only; no window → `NotCreated`;
  - read `SDL_GetWindowProperties` and the platform properties: Win32 `HWND`, Cocoa `NSWindow`, Wayland `wl_surface`, X11 window number;
  - no matching property → `NativeHandleUnavailable`;
  - success returns the kind/value and the window's native-handle generation.
- `native_handle_valid` returns true only while the window exists and the token's generation matches. Destroy invalidates it.
- `current_native_window_system()` maps the active SDL video driver (`x11`, `wayland`, `windows`, `cocoa`) to the enum; `dummy`/unknown → `Unknown`.
- No direct OS header, platform macro or ABI surface in the header; no renderer/GPU/VRAM; no public SDK/plugin promise.

## Alternatives rejected

- **Direct Win32/Cocoa/Wayland/X11 implementation now:** rejected; multiplies platform code and testing without a measured need; SDL already exposes the native handles.
- **Raw `void*`/integer handle without generation:** rejected; callers cannot detect a stale/destroyed window.
- **Owning handle wrapper:** rejected; SDL/the window owns the handle, and a second owner would create double-free risk.
- **Public C ABI/plugin handle:** rejected; NLE-D009 and SDK scope remain open.
- **Renderer surface/VRAM handle:** rejected; GFX-01/GFX-03 own it.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: NBI-01..NBI-06, real X11/Win32/Cocoa window handle on native runners (or explicit `NOT_QUALIFIED` if no window server), dummy-driver `NativeHandleUnavailable`, wrong-thread, destroy invalidation, lifetime, existing 47 CTests regression, Linux ASan/UBSan.
- Physical OS permission/sandbox, multiple native windows, renderer integration, IME/hotplug and public ABI remain `NOT_QUALIFIED / out of scope`.
- ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the native-bridge target, additive window methods/tests and evidence restores the previous state; no G2, registry or license change is part of this ADR.
