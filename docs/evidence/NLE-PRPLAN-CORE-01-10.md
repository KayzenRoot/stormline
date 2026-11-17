# NLE-PRPLAN-CORE-01-10 — Display, DPI and surface validity

**Status:** `CODE_IMPLEMENTED / LOCAL_PREFLIGHT_PASS / NATIVE_CI_PENDING / AWAITING_AUDIT`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-10`. **ADR:** [ADR-0089](../adr/0089-core-01-display-surface-slice.md). **Contract:** [core-01-display-surface-v0](../contracts/core-01-display-surface-v0.md). **WO:** [NLE-PRPLAN-CORE-01-10](../work-orders/NLE-PRPLAN-CORE-01-10.md). **Issue:** [#18](https://github.com/KayzenRoot/stormline/issues/18).

First real CORE-01 display/surface metadata path: owner-thread display enumeration, bounds/usable bounds/content scale, additive window surface metrics and generation-based invalidation on resize or observed display/pixel-size change. No renderer/GPU/VRAM, physical hotplug/DPI certification, IME/fullscreen/HDR, public ABI or release.

## 1. Authorization and Context Lock

- **Gate:** [PR #446](https://github.com/KayzenRoot/stormline/pull/446) squash-merged as `2cba52ba439a631249dba7d1e1aaf49ac9e9d93d`; audit #6959494877 **APPROVED**.
- **Base:** `2cba52ba439a631249dba7d1e1aaf49ac9e9d93d`.
- **Selector:** `select_packet.py NLE-PRPLAN-CORE-01-10 --json` → `EXECUTOR_READY`, exit 0; `-11`, `CORE-02-04` and every other ID exit 2.
- **Predecessors:** `-03`..`-09` completed; CORE-02-03 ownership completed via PR #441.

SDL3 remains `3.4.20`, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib, static build-time `FetchContent`.

## 2. Implemented behavior

- `DisplayInfo`: ID, primary flag, bounds, usable bounds, content scale; no strings or SDL pointers.
- `DisplayService`: owner-thread `enumerate` and `primary`; `SDL_GetDisplays` result copied to caller storage and freed; typed `DisplayError`; no partial write on undersized buffer; `count` reports total.
- `SurfaceMetrics`: display ID, display scale, logical/pixel size, monotonic generation.
- `Window::query_surface`: owner-thread; queries display, scale, logical size and pixel size; any failure → `SurfaceQueryFailed`; increments generation when display ID or pixel size changes from the cached value.
- `Window::resize`: on success increments the surface generation and refreshes cached pixel size.
- `Window::surface_valid`: returns true only for the current non-zero generation; false after resize/destroy.
- Additive `WindowError::SurfaceQueryFailed`; existing error values and methods unchanged.
- Header includes only C++ standard headers; SDL is confined to `.cpp` files.
- No renderer/GPU/swapchain/VRAM, physical hotplug/DPI certification, IME, fullscreen, HDR or public ABI.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/internal/display.hpp` | Internal display API; standard headers only |
| `src/stormline/core/internal/display.cpp` | SDL3 display enumeration/primary, bounds/scale |
| `src/stormline/core/internal/window.hpp` | Additive `SurfaceMetrics`/surface methods |
| `src/stormline/core/internal/window.cpp` | Surface query and generation invalidation |
| `tests/core/display_tests.cpp` | display/errors/thread/surface/stability/lifetime tests |
| `CMakeLists.txt` | Additive `stormline_core01_display` target and seven CTests |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-01-10 path filters |
| `docs/evidence/NLE-PRPLAN-CORE-01-10.md` | This Evidence Bundle |

No other path changed. Existing CORE-01/CORE-02 targets are unchanged except additive display/surface wiring.

## 4. Tests and real results

### Local preflight (observed)

- CMake/Ninja configure with local SDL3 3.4.20 source override (CI uses the exact pinned commit), `stormline_core01_display_test` build: **OK**.
- `ctest -R core01_display_`: **7/7 passed** on Windows/MSVC 14.44 with `SDL_VIDEODRIVER=dummy`.
- Full local matrix after rebuild: **47/47 CTests passed** (40 previous + 7 display tests).
- Display tests exercise a dummy display, surface metrics, resize generation invalidation, wrong-thread rejection, argument/buffer errors, stability and 100 resize/query cycles.

### Native CI (authoritative, pending)

Pending exact-head Docs Validation and native Linux/Linux-sanitizers/Windows/macOS runs. This document will be updated with run IDs and observed CTest counts only after they complete; no native PASS is claimed yet.

Expected matrix: existing 40 CTests plus 7 display tests = **47 CTests** per native job, with Linux ASan/UBSan.

## 5. Security, licensing and limitations

- No third-party dependency beyond the already pinned SDL3 baseline; no package installation, secret, upload, paid runner/service or runtime download.
- No SDL type/macro/handle in headers; no renderer/GPU/VRAM/swapchain, physical hotplug/DPI certification, IME/fullscreen/HDR, public ABI or release.
- `SDL_GetDisplays` returns SDL-owned memory; it is copied to caller storage and freed before return. `DisplayInfo` contains no pointer/string.
- Physical multi-monitor/hotplug/DPI changes remain **NOT_QUALIFIED**: the test driver exposes a single dummy display. `query_surface` re-reads display/pixel state on every call, but this is not a physical hotplug PASS.
- ADR-0003/0075 remain `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.
- No HIGH/CRITICAL known; final status subject to exact-head CI and independent pt-BR audit.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the display target, additive window surface methods/tests and this evidence restores the previous state.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the sixth real CORE-01 slice, exact PR/CI/audit/merge SHA, 7 `core01_display_*` tests and 47 total CTests across Linux, Linux ASan/UBSan, Windows and macOS, and the explicit statement that this is display/surface metadata only — not renderer/GPU/VRAM, physical hotplug/DPI, IME, fullscreen, HDR, public ABI or release. This evidence does not self-promote the checkpoint.
