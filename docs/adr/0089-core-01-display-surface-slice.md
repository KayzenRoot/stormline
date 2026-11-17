# ADR-0089 — CORE-01 display, DPI and surface validity slice

**Status:** `OWNER_DIRECTION_C01_D03_C01_D04_BOUNDED / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **This ADR is subordinate to and DOES NOT approve ADR-0003 or ADR-0075 as a whole, and does not clear G3 globally.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-01-10` | **Parent:** `NLE-PRPLAN-CORE-01-01` | **Issue:** #387 / implementation issue #18.

## Context and authority

The owner explicitly authorized unlocking the next planned packet on 2026-11-17. C01-D03 includes display capability/event integration through the thin SDL3 adapter, and C01-D04 requires main/owner-thread video calls. The `-07` SDL3 runtime, `-08` window lifecycle and `-09` event queue are completed and merged.

The next formal CORE-01 packet is `-10`: multi-monitor, DPI and surface validity. This slice is bounded to **display enumeration, content scale, window surface metrics and generation-based invalidation**. It does not implement renderer/swapchain/GPU, physical hotplug certification, IME, fullscreen, HDR or a public ABI.

## Bounded technical decision

- New internal `DisplayInfo`, `DisplayError`, `DisplayService` in `display.hpp/cpp`; SDL hidden in the `.cpp`.
- `DisplayService` enumerates displays with `SDL_GetDisplays`, copies ID/primary/bounds/usable bounds/content scale into fixed caller storage, and frees the SDL-owned array. No display name/string, no ambient allocation in the result path.
- Additive `SurfaceMetrics` and `Window::query_surface`/`Window::surface_valid` in the existing window API.
- `SurfaceMetrics` records display ID, content scale, logical size, pixel size and a monotonic `generation`.
- `Window::resize` invalidates the current surface generation after a successful resize. `query_surface` re-reads the display ID and pixel size; if either changed, it increments the generation before returning new metrics. A borrowed `SurfaceMetrics`/generation becomes stale and `surface_valid` returns false.
- Owner-thread enforcement for display enumeration and surface queries; typed errors; no exceptions across the boundary; no SDL type/macro/handle in headers.
- Physical hotplug/display removal and real DPI changes are **NOT_QUALIFIED**: CI has a virtual/single display. The code path observes the current display/pixel state on query, but no physical hotplug PASS is claimed.

## Alternatives rejected

- **Renderer/swapchain/VRAM query:** rejected; GFX-03/GFX-01 own it and this slice has no GPU backend.
- **Display names/localized strings:** rejected; unnecessary allocation and locale surface for a bounded metrics slice.
- **Physical multi-monitor/hotplug certification in CI:** rejected as unverifiable on standard runners; mark `NOT_QUALIFIED`.
- **Pointer-based surface handles:** rejected; generation tokens avoid dangling renderer/surface ownership and are testable without a GPU.
- **Silent resize/DPI acceptance:** rejected; stale generations must be observable by the consumer.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: DPY-01..DPY-08, real display enumeration on Linux/Windows/macOS, surface metrics, resize invalidation, stale generation, wrong-thread, errors, stability and lifetime; existing 40 CTests regression; Linux ASan/UBSan.
- Real physical hotplug/DPI/multi-monitor remains `NOT_QUALIFIED`; no renderer/GPU/audio/public ABI/release.
- ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the display target, additive window methods/tests and evidence restores the previous state; no G2, registry or license change is part of this ADR.
