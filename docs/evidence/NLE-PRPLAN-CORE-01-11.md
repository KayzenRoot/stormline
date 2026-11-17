# NLE-PRPLAN-CORE-01-11 — Opaque native window-handle bridge

**Status:** `CODE_IMPLEMENTED / NATIVE_CI_PASS / MERGED`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-11`. **ADR:** [ADR-0090](../adr/0090-core-01-native-window-handle-bridge.md). **Contract:** [core-01-native-window-handle-v0](../contracts/core-01-native-window-handle-v0.md). **WO:** [NLE-PRPLAN-CORE-01-11](../work-orders/NLE-PRPLAN-CORE-01-11.md). **Issue:** [#18](https://github.com/KayzenRoot/stormline/issues/18).

First internal native window-handle bridge: identify the active window system, expose the SDL-owned platform window handle as an opaque non-owning token (kind/value/generation), and invalidate it on window destroy. No direct OS implementation, permissions, renderer/VRAM, clipboard/DnD/IME/hotplug, public ABI or release.

## 1. Authorization and Context Lock

- **Gate:** [PR #449](https://github.com/KayzenRoot/stormline/pull/449) squash-merged as `c77a55a70d79dd3cec23b46ba252bbb97138ba9b`; audit #6960180269 **APPROVED**.
- **Code PR:** [PR #450](https://github.com/KayzenRoot/stormline/pull/450), HEAD auditado `08b65afe2f064862f0d5085b41919814b10b16dd`, [auditoria pt-BR #6960412059](https://github.com/KayzenRoot/stormline/pull/450#issuecomment-6960412059) **APPROVED**; squash-merged as `b062053a2d1513c39ac49d101e6eb189570b51f6`.
- **Base:** `c77a55a70d79dd3cec23b46ba252bbb97138ba9b`.
- **Selector:** during execution, `select_packet.py NLE-PRPLAN-CORE-01-11 --json` → `EXECUTOR_READY`, exit 0; after closeout every ID exits 2.
- **Predecessors:** `-03`..`-10` completed; CORE-02-03 ownership completed via PR #441.

SDL3 remains `3.4.20`, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib, static build-time `FetchContent`.

## 2. Implemented behavior

- `NativeWindowSystem`: `Unknown`, `X11`, `Wayland`, `Win32`, `Cocoa`; mapped from `SDL_GetCurrentVideoDriver` (`dummy`/unknown → `Unknown`).
- `NativeHandleKind`: `None`, `X11Window`, `WaylandSurface`, `Win32Hwnd`, `CocoaWindow`.
- `NativeWindowHandle`: opaque non-owning kind/value/generation; no pointer/string in the header.
- `Window::query_native_handle`: owner-thread; no window → `NotCreated`; reads SDL window properties for Win32 HWND, Cocoa NSWindow, Wayland wl_surface and X11 window number; no matching property → `NativeHandleUnavailable`; success returns the handle and generation.
- `Window::native_handle_valid`: true only for a live window and matching non-zero kind/value/generation; destroy invalidates.
- Resize does not invalidate the native-handle generation.
- No direct Win32/Cocoa/Wayland/X11 header/API in the engine code; SDL remains confined to `.cpp`.
- No OS-handle ownership transfer, permission model, renderer/GPU/VRAM, clipboard/DnD/IME/hotplug or public ABI.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/internal/native_bridge.hpp` | Internal native system/handle types |
| `src/stormline/core/internal/native_bridge.cpp` | SDL video-driver mapping |
| `src/stormline/core/internal/window.hpp` | Additive native-handle API/error |
| `src/stormline/core/internal/window.cpp` | Native property query and lifetime token |
| `tests/core/native_bridge_tests.cpp` | system/handle/unavailable/errors/thread/lifetime tests |
| `CMakeLists.txt` | Additive `stormline_core01_native_bridge` target and six CTests |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-01-11 path filters |
| `docs/evidence/NLE-PRPLAN-CORE-01-11.md` | This Evidence Bundle |

No other path changed. Existing CORE-01/CORE-02 targets are unchanged except additive native-bridge wiring.

## 4. Tests and real results

### Local preflight (observed)

- CMake/Ninja configure with local SDL3 3.4.20 source override (CI uses the exact pinned commit), `stormline_core01_native_bridge_test` build: **OK**.
- `ctest -R core01_native_`: **6/6 passed** on Windows/MSVC 14.44 (real `windows` driver; dummy for `unavailable`).
- Full local matrix after rebuild: **53/53 CTests passed** (47 previous + 6 native bridge tests).
- Tests cover system mapping, native handle kind/value/generation, dummy unavailable path, wrong-thread, before/after destroy, and 50 create/query/destroy cycles.

### Native CI (authoritative, observed)

All jobs ran at the exact HEAD `4d383612252baa3e8cf565890d042d8d3d3fe0b1`:

| Job | Runner / toolchain | Result |
|---|---|---|
| `docs-validation` | required G2 check | [run 44170903359](https://github.com/KayzenRoot/stormline/actions/runs/44170903359) **SUCCESS** |
| `linux` | ubuntu-24.04, GCC, X11 via Xvfb/openbox | **53/53 CTest passed** |
| `linux-sanitizers` | ubuntu-24.04, ASan/UBSan, X11 via Xvfb/openbox | **53/53 CTest passed** |
| `windows` | windows-2025-vs2026, MSVC | **53/53 CTest passed** |
| `macos` | macos-15-arm64, Apple clang | **53/53 CTest passed** |

Native workflow run: [44170903412](https://github.com/KayzenRoot/stormline/actions/runs/44170903412) **SUCCESS**. Job IDs: Linux `134349389678`, sanitizers `134349390177`, Windows `134349390196`, macOS `134349390137`. The six `core01_native_*` tests executed in every job in addition to the existing 47 CTests; none skipped. The macOS job completed without a `NOT_QUALIFIED` skip.

No correction was required by the native matrix.

## 5. Security, licensing and limitations

- No third-party dependency beyond the already pinned SDL3 baseline; no package installation, secret, upload, paid runner/service or runtime download.
- The handle is explicitly **non-owning**: the caller must not free, close or take ownership of the HWND/NSWindow/wl_surface/X11 window. SDL/the OS/the window retain ownership.
- No direct OS permission/sandbox model, multiple native windows, renderer surface/VRAM, clipboard/DnD/IME/hotplug, public ABI or release.
- macOS window-server availability may make the native handle tests `NOT_QUALIFIED`; the final matrix records the real result.
- ADR-0003/0075 remain `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.
- No HIGH/CRITICAL known; native CI passed at the code head and the result remains subject to the independent pt-BR audit.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the native-bridge target, additive window methods/tests and this evidence restores the previous state.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the seventh real CORE-01 slice, exact PR/CI/audit/merge SHA, 6 `core01_native_*` tests and 53 total CTests across Linux, Linux ASan/UBSan, Windows and macOS, and the explicit statement that this is an opaque non-owning handle bridge only — not direct OS APIs, permissions, renderer/GPU/VRAM, IME, hotplug, public ABI or release. This evidence does not self-promote the checkpoint.

## 8. Actual closure

- [PR #450](https://github.com/KayzenRoot/stormline/pull/450) **squash-merged** at `2026-11-17T20:42:11Z`, merge `b062053a2d1513c39ac49d101e6eb189570b51f6`; [auditoria pt-BR #6960412059](https://github.com/KayzenRoot/stormline/pull/450#issuecomment-6960412059) **APPROVED**.
- Final-head Docs Validation [44171487097](https://github.com/KayzenRoot/stormline/actions/runs/44171487097) **SUCCESS**; native [44171487124](https://github.com/KayzenRoot/stormline/actions/runs/44171487124) **SUCCESS**, **53/53 CTest** on Linux, Linux ASan/UBSan, Windows and macOS.
- Packet `CORE-01-11` becomes `COMPLETED` with `github_pr=450`; the manifest has **734 `PLANNED_BLOCKED`, 10 `COMPLETED`, 4 approved gates, 0 `EXECUTOR_READY`**; `select_packet.py` denies every ID. No next packet or module is authorized. CORE-01 remains incomplete; `-12`..`-16` are blocked.
