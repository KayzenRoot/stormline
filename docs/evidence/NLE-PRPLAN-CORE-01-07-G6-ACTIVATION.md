# NLE-PRPLAN-CORE-01-07 — G6 activation (SDL3 runtime init/quit)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `80a6fdafb2cc0f1f923af83367f21e9260e53323`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-07`. **ADR:** [ADR-0084](../adr/0084-core-01-sdl3-runtime-slice.md). **Contract:** [core-01-sdl3-runtime-v0](../contracts/core-01-sdl3-runtime-v0.md). **WO:** [NLE-PRPLAN-CORE-01-07](../work-orders/NLE-PRPLAN-CORE-01-07.md).

## Owner authorization and scope

The owner directed continuation of the next repository increments on 2026-11-17 (`STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments`). C01-D03 (SDL3 thin host adapter) and C01-D04 (SDL video/main-thread, headless independent) were already explicitly ratified as bounded directions; G3-V01 selected SDL3 3.4.20 as a candidate. This gate authorizes **only** packet `-07`: SDL3 video/events init and shutdown on the owner thread, after exact-head Docs Validation, objective pt-BR audit and squash/readback.

It does **not** approve ADR-0003/0075 as a whole, clear G3 globally, authorize a window/renderer/audio/public ABI/release, or unlock any other packet or module.

## Predecessors

`-03` (headless host) `COMPLETED` via PR #428; `-04`/`-05` objectively reconciled as covered by `-03`; `-06` (portable paths) `COMPLETED` via PR #432. All four are ordered before `-07` in the manifest and have real code/tests/CI evidence. No predecessor is reopened.

## Verified dependency pin

| Item | Observed value |
|---|---|
| Release tag | `release-3.4.20` |
| Commit | `f00dc919ca35b9756316e86c4777392de442f9b2` (tag object type commit) |
| License | zlib-style SDL license, Copyright (C) 1997-2026 Sam Lantinga; three notice clauses |
| Static target | `SDL3::SDL3-static` (`SDL_SHARED=OFF`, `SDL_STATIC=ON`) |
| Acquisition | CMake `FetchContent` from `https://github.com/libsdl-org/SDL.git` at the full commit, **build time only** |
| Runtime | no download/install/package manager; no audio/joystick/HIDAPI/X11/Wayland in this slice; dummy video driver in CI |

The full commit is immutable. If the fetch/build or license verification fails, the code PR is `BLOCKED`; there is no fallback to an unpinned system package.

## Bounded technical slice

- Internal `SdlRuntime` with `initialize`, `shutdown`, `initialized`, typed `SdlError`, owner-thread check and `linked_version`.
- Only `SDL_SetMainReady`, `SDL_Init(VIDEO|EVENTS)`, `SDL_Quit` and `SDL_GetVersion` are used. **No window, input pump, renderer, GPU, audio, gamepad, dialog, VFS or network call.**
- No SDL type/macro/handle in the internal header; SDL is included only by `sdl_runtime.cpp`.
- One active instance per process; sequential init/quit cycles; no global adapter singleton; no exceptions across the boundary.
- Exact allowlist: `sdl_runtime.hpp`, `sdl_runtime.cpp`, `tests/core/sdl_runtime_tests.cpp`, additive `CMakeLists.txt`, workflow timeout-only change if needed, `docs/evidence/NLE-PRPLAN-CORE-01-07.md`.

## Gate state after merge (expected, not yet promoted)

- Manifest root `CORE01_07_READY_PREDECESSORS_COMPLETED`: **741 `PLANNED_BLOCKED`, 4 `COMPLETED` (`-03`..`-06`), 1 `EXECUTOR_READY` (`-07`)**.
- `select_packet.py NLE-PRPLAN-CORE-01-07` → exit 0 after merge; `-06` and every other ID exit 2.
- 80/80 module WOs remain `BLOCKED`; registry unchanged; ADR-0003/0075 `PROPOSED`; ADR-0083/0084 bounded; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; `engine_implemented=false` at module/product level.

## Proof obligations for the future code PR

SDL-01..SDL-08: 20 init/quit cycles on dummy video; duplicate init/repeated shutdown; wrong-thread rejection; invalid-driver failure and recovery; linked version 3.4.20; header-isolation compile without SDL include dirs; no window/renderer/audio/network usage; existing 12 CTests regression. Plus build/link on Linux/Windows/macOS, Linux ASan/UBSan when supported, exact-head Docs Validation, objective pt-BR audit, squash/readback. Real window/display/driver qualification is **NOT_QUALIFIED** and deferred to `-08`/PLAT.

No code or native PASS is claimed by this gate.

## Security, cost, rollback

No secret, paid runner, upload, cache, system install or workflow permission change. The only network use is the pinned build-time SDL3 source fetch on standard public runners, R$0. If unmerged, close the gate branch; `main` untouched. After a future merge, normal revert PR only, never force push. No release/distribution; SDL3 zlib notice must be preserved in any future distribution.
