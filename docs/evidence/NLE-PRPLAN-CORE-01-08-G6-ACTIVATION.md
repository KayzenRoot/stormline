# NLE-PRPLAN-CORE-01-08 — G6 activation (native window lifecycle)

**Status:** `G6 PROPOSAL / INSTALL AUTHORIZED / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `b54f19c252fda9c06a7d7289a853bd4cf957cf53`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-08`. **ADR:** [ADR-0085](../adr/0085-core-01-window-lifecycle-slice.md). **Contract:** [core-01-window-lifecycle-v0](../contracts/core-01-window-lifecycle-v0.md). **WO:** [NLE-PRPLAN-CORE-01-08](../work-orders/NLE-PRPLAN-CORE-01-08.md).

## Owner authorization

The owner authorized the next increments with **capability-based L1 dependencies**, a **3-4 PRs per response** cadence, and **real installation** for the window slice on 2026-11-17 (`STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments`). This gate activates **only** `-08`: real X11/Win32/Cocoa window lifecycle, after exact-head Docs Validation, objective pt-BR audit and squash/readback.

It does not approve ADR-0003/0075 globally, clear G3, authorize a renderer/GPU/audio/public ABI/release, or unlock another packet/module.

## Predecessors

`-03` (headless host) PR #428; `-04`/`-05` reconciled; `-06` (paths) PR #432; `-07` (SDL3 init/quit) PR #435. All `COMPLETED`; no predecessor reopened.

## Dependency and installation matrix

| Item | Value |
|---|---|
| SDL3 | `3.4.20`, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib |
| Linkage | static `SDL3::SDL3-static`, build-time `FetchContent` |
| Linux video | X11 + Wayland **built**; X11 runtime tested; Wayland runtime `NOT_QUALIFIED` |
| Linux install | exact packages in the contract: X11/XKB/Wayland/GL dev libs + `xvfb`, `x11-utils`, `openbox` |
| Linux display | `Xvfb :99 -screen 0 1280x720x24`, `openbox --sm-disable`, `DISPLAY=:99` |
| Windows | Win32 video, `SDL_VIDEODRIVER=windows`, no install |
| macOS | Cocoa video, `SDL_VIDEODRIVER=cocoa`; real window `NOT_QUALIFIED` if no window server |
| Disabled | render/GPU/Vulkan/Metal/OpenGL/GLES/D3D, audio, joystick/HIDAPI/sensor/power/camera, KMSDRM |
| Cost | Ubuntu packages + standard public runners; **R$0**; no paid runner/service |

The installation is ephemeral CI provisioning from official Ubuntu repositories; it is not a runtime dependency, vendored source or system SDL3 package.

## Bounded technical slice

- Internal `WindowConfig`, `WindowError`, `Window` (`create`, `destroy`, `resize`, `show`, `focus`, `valid`).
- `SdlRuntime` must be initialized on the same owner thread and outlive the window; `Window` checks `SDL_WasInit(SDL_INIT_VIDEO)`.
- `create` produces a hidden, resizable window; `show` maps it; `focus` is a raise/focus request; `destroy` is idempotent; destructor is no-throw on the owner thread.
- No SDL type/macro/handle in the header; SDL only in `window.cpp`.
- Exact code allowlist: `window.hpp`, `window.cpp`, `tests/core/window_tests.cpp`, additive `CMakeLists.txt`, workflow install/Xvfb/timeout, `docs/evidence/NLE-PRPLAN-CORE-01-08.md`.

## Gate state after merge (expected, not yet promoted)

- Manifest root `CORE01_08_READY_PREDECESSORS_COMPLETED`: **740 `PLANNED_BLOCKED`, 5 `COMPLETED` (`-03`..`-07`), 1 `EXECUTOR_READY` (`-08`)**.
- `select_packet.py NLE-PRPLAN-CORE-01-08` → exit 0; `-07` and every other ID exit 2.
- 80/80 module WOs remain `BLOCKED`; registry unchanged; ADR-0003/0075 `PROPOSED`; ADR-0083/0084/0085 bounded; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; `engine_implemented=false` at module/product level.

## Proof obligations for the code PR

WIN-01..WIN-08: create/resize/show/focus/destroy; duplicate create/repeated destroy; invalid sizes; pre-create operations; wrong-thread rejection; video-not-initialized; 50 lifecycle cycles; existing 18 CTests regression. Real X11 under Xvfb/openbox; Win32 on Windows; Cocoa on macOS or `NOT_QUALIFIED`; Linux ASan/UBSan; no SDL leak; no renderer/GPU/audio call; exact-head Docs Validation and pt-BR audit.

No code or native PASS is claimed by this gate.

## Security and rollback

Only official Ubuntu packages, standard public runners, no secret/upload/paid service. SDL3 zlib notice preserved for future distribution; `NLE-D009 OPEN`; no release. Unmerged: close the gate branch; `main` untouched. After merge: normal revert PR, never force push.
