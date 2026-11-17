# ADR-0085 — CORE-01 native window lifecycle slice

**Status:** `OWNER_DIRECTION_C01_D03_C01_D04_BOUNDED / INSTALL_AND_CI_AUTHORIZED / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **This ADR is subordinate to and DOES NOT approve ADR-0003 or ADR-0075 as a whole, and does not clear G3 globally.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-01-08` | **Parent:** `NLE-PRPLAN-CORE-01-01` | **Issue:** #387 / implementation issue #18.

## Context and authority

C01-D03 (SDL3 thin host adapter) and C01-D04 (SDL video/main-thread, balanced init/quit) were explicitly owner-ratified. The owner then authorized the next increments with **capability-based dependencies** for L1, a **3-4 PRs per response** cadence, and **real installation** for the window slice. This ADR records only the first real window lifecycle: create/resize/show/focus/destroy with verified handle lifetime, no renderer/GPU/audio/public ABI/release.

## Bounded technical decision

- **Dependency:** SDL3 3.4.20, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib, static `SDL3::SDL3-static`, build-time `FetchContent`.
- **Build profile:** X11 and Wayland video drivers built on Linux; Win32 video on Windows; Cocoa video on macOS. Render/GPU/Vulkan/Metal/OpenGL/GLES/D3D and audio remain disabled. `SDL_KMSDRM=OFF`.
- **Linux CI installation (owner-authorized, R$0):** install the exact X11/Wayland development packages and a virtual display stack (`Xvfb` + `openbox`) before CMake, then run the X11 window tests with `DISPLAY=:99` and `SDL_VIDEODRIVER=x11`. Packages are listed in the contract/activation and must match exactly.
- **Windows CI:** native Win32 video driver, `SDL_VIDEODRIVER=windows`, no installation.
- **macOS CI:** Cocoa video driver, `SDL_VIDEODRIVER=cocoa`; if the hosted runner has no usable window server, real window cases are `NOT_QUALIFIED` with explicit evidence, never a false PASS.
- **Wayland:** built but **runtime NOT_QUALIFIED** because the CI has no compositor; no claim of Wayland runtime support.
- **API:** internal `WindowConfig`, `WindowError`, `Window` (`create`, `destroy`, `resize`, `show`, `focus`, `valid`) in `stormline::core::internal`; no SDL types/macros/handles in the header. A `SdlRuntime` must be initialized on the same owner thread and outlive the window. Exact contract: [core-01-window-lifecycle-v0](../contracts/core-01-window-lifecycle-v0.md).
- **Ownership:** noncopyable/nonmovable, single-owner thread, idempotent destroy, no-throw destructor on the owner thread, no hidden global window, no public ABI.

## Alternatives rejected

- **Offscreen/dummy-only window:** rejected by owner; the goal is a real X11/Win32/Cocoa window lifecycle.
- **Installing system SDL3 packages:** rejected; the source remains pinned via FetchContent.
- **Enabling renderer/GPU/audio:** rejected; not needed for lifecycle and outside this slice.
- **Wayland runtime qualification without a compositor:** rejected as unverifiable; build-only, `NOT_QUALIFIED`.
- **Skipping Linux dev packages:** rejected; without them SDL3 cannot build X11/Wayland support.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: real window create/resize/show/focus/destroy and 50 lifecycle cycles on X11 (Xvfb/openbox), Win32, and Cocoa where available; no SDL types in headers; no renderer/GPU/audio calls; existing 18 CTests regression; Linux ASan/UBSan.
- Real physical monitor/DPI/IME/hotplug, Wayland runtime, renderer/GPU/audio, public ABI, release and redistribution remain **NOT_QUALIFIED / out of scope**.
- SDL3 zlib notice must be preserved in future distribution; `NLE-D009 OPEN`; no release.
- ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; 80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the window target/CMake install step restores the previous state; no G2, registry or license change is part of this ADR.
