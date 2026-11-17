# NLE-PRPLAN-CORE-01-08 — Native window lifecycle

**Status:** `CODE_IMPLEMENTED / NATIVE_CI_PASS / AUDIT_PENDING` · **Master program:** `STORM-CORE-01-IMPL-001` · **Formal packet:** `NLE-PRPLAN-CORE-01-08` · **ADR:** [ADR-0085](../adr/0085-core-01-window-lifecycle-slice.md) · **Contract:** [core-01-window-lifecycle-v0](../contracts/core-01-window-lifecycle-v0.md) · **WO:** [NLE-PRPLAN-CORE-01-08](../work-orders/NLE-PRPLAN-CORE-01-08.md) · **Issue:** [#18](https://github.com/KayzenRoot/stormline/issues/18).

First real native window lifecycle in Stormline: X11/Win32/Cocoa window create/resize/show/raise-focus/destroy with verified handle lifetime. No renderer, GPU, audio, input pump, DPI/IME/hotplug, public ABI or release.

## 1. Authorization and Context Lock

- **Gate:** [PR #437](https://github.com/KayzenRoot/stormline/pull/437) merged as `fcb0a74c10c01dff317703b21f8e72aaeec30803`; activated only `-08`.
- **Base:** `fcb0a74c10c01dff317703b21f8e72aaeec30803`.
- **Selector:** `select_packet.py NLE-PRPLAN-CORE-01-08 --json` → `EXECUTOR_READY`, exit 0; `-07`, `-09` and all others exit 2.
- **Installation:** owner-authorized Ubuntu packages (X11/Wayland dev libs + Xvfb/openbox) in CI; R$0; no paid runner/service.

| Source | Raw SHA-256 |
|---|---|
| `docs/11-checkpoint.md` | `242f7315d17a19e9af797c2ffff8a67a2eecd91e148d77122d3946d9d43e983d` |
| `docs/10-decisions-ledger.md` | `420220915e0600bb84167106d3384b28e27cd2f4375c1e16ccb8374d701e216c` |
| `docs/03-scope.md` | `39ad13b45738516904b767a8997551cccce2a9ff8ea8642c152bb815fa67c0c7` |
| `docs/09-definition-of-done.md` | `7fc04cc33aad22197b68bcda43fbd356726f11e401cf0e2b68c97f685b12778e` |
| `docs/adr/0003-core-01-platform-technology.md` | `475d8e3771ff72cc8d81fd2dd9b89f7795853f5223eca30bc1ebb3804249d226` |
| `docs/adr/0083-core-01-internal-headless-slice.md` | `c484fb10aec5a4b61919967b9026494484f6ae11461f90b94cb1e38fdbdc99a9` |
| `docs/adr/0084-core-01-sdl3-runtime-slice.md` | `0ef009b2c9719d6a501425e326ac744ad012c7ee33aad82cbc48ba2e0f5ed2eb` |
| `docs/adr/0085-core-01-window-lifecycle-slice.md` | `c6620d21e1c75c5ccf8ef90d2647eb293c3b10b92f2cbd9e5f7e8737d2c48bc2` |
| `docs/contracts/core-01-internal-headless-v0.md` | `b4457feaf74379b5ffd3f8e744727a48cc7673383cd5c259073b495dfd10f38b` |
| `docs/contracts/core-01-process-paths-v0.md` | `4a6cd9fb25f3b60d34fe91373400ebd04e32a0bfa809dd234171110784c3721d` |
| `docs/contracts/core-01-sdl3-runtime-v0.md` | `dec8d249c063a42191c9b367493806f9758759c195820296c5c682fc25f1f7e2` |
| `docs/contracts/core-01-window-lifecycle-v0.md` | `a4c715e98ec0aed7a7c7fb446b82cf8c56d8e615d0fb72ff80380fbbb4de770f` |

SDL3 remains `3.4.20`, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib, static build-time `FetchContent`.

## 2. Implemented behavior

- `WindowConfig` (width/height), `WindowError` (12 typed states), `Window` (`create`, `destroy`, `resize`, `show`, `focus`, `valid`), all `noexcept`; no exceptions across the boundary.
- Owner thread recorded at construction; worker create/destroy → `WrongThread` without SDL.
- `create`: hidden, resizable `SDL_CreateWindow`; duplicate → `AlreadyCreated`; non-positive size → `InvalidSize`; video not initialized → `VideoNotInitialized`; SDL failure → `CreateFailed`; allocation failure → `AllocationFailed`.
- `destroy`: idempotent; `resize`/`show`/`focus` use `SDL_SetWindowSize`/`SDL_ShowWindow`/`SDL_RaiseWindow` and map bool failures; `focus` is a raise/focus request (compositor decides actual focus).
- `SdlRuntime` must be initialized on the same thread and outlive the window; the header has no SDL type/macro/handle.
- No renderer/GPU/audio/network/input-pump call; SDL calls limited to window/video lifecycle.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/internal/window.hpp` | Internal API, no SDL types |
| `src/stormline/core/internal/window.cpp` | SDL3 window lifecycle, owner-thread checks, typed errors |
| `tests/core/window_tests.cpp` | WIN-01..WIN-08 tests + header leak guard |
| `CMakeLists.txt` | Window target/tests; X11/Wayland ON; Xvfb/openbox driver env |
| `.github/workflows/core01-internal-headless.yml` | Exact Linux install, Xvfb/openbox, real-driver tests |
| `docs/evidence/NLE-PRPLAN-CORE-01-08.md` | This Evidence Bundle |

No other path changed.

## 4. Tests and real results

### Local preflight

The official SDL3 3.4.20 tarball was re-extracted in temp (SHA-256 `f3bb06f55bed9557227a700af2ea62e49497ebdf58037732a731a5fb3ef8581f`). `window.cpp` (against exact SDL3 headers) and `window_tests.cpp` compiled with preinstalled MSVC 14.44 `/std:c++20 /W4 /WX /EHsc` → **OK**. This is a header/API compile check only; no local link/run/target qualification.

### Native CI (authoritative, observed)

The code-bearing head `98a8414aac2367a34af5307608baa06663968b81` passed the required Docs Validation and all native jobs. A later documentation-only evidence update re-runs Docs Validation; the code/native matrix is unchanged, and the final-head run is recorded in the PR audit.

| Job | Runner / toolchain | Result |
|---|---|---|
| `docs-validation` | required G2 check | [run 44149340397](https://github.com/KayzenRoot/stormline/actions/runs/44149340397) job `134273022272` **SUCCESS** |
| `linux` | ubuntu-24.04, GCC 13.3.0, CMake 3.31.6, Ninja 1.13.2; X11 via Xvfb/openbox | **23/23 CTest passed** |
| `linux-sanitizers` | ubuntu-24.04, ASan/UBSan, X11 via Xvfb/openbox | **23/23 CTest passed** |
| `windows` | windows-2025-vs2026, MSVC 14.51.36231, CMake 4.4.5; Win32 video | **23/23 CTest passed** |
| `macos` | macos-15-arm64, Apple clang 17.0.0, CMake 4.4.5; Cocoa video ON | **23/23 CTest passed** |

Native workflow run: [44149339941](https://github.com/KayzenRoot/stormline/actions/runs/44149339941) (`pull_request`, head `98a8414…`) **SUCCESS**. Job IDs: Linux `134273022298`, sanitizers `134273021691`, Windows `134273023827`, macOS `134273022263`. All 18 existing CTests and the five window CTests executed; none skipped. The Linux install step succeeded with the pinned Ubuntu packages (`libwayland-dev`, `openbox`, `libx11-dev`, etc.), and Xvfb/openbox started before CTest. macOS configured `SDL_COCOA ON` and the window tests passed without a `NOT_QUALIFIED` path.

### Corrections found by real CI (same PR)

1. **Linux/Clang warnings:** the test helper `note` was unused on non-Apple builds and `description` was unused on Apple; fixed with `[[maybe_unused]]` and `(void)description`.
2. **LSan third-party X11 leaks:** ASan reported leaks inside SDL3's `X11_InitIM` and `X11_GetGlobalContentScale`/XRandR paths, not our code. The sanitizer job uses a narrow suppression file (`leak:X11_`) for the SDL3 X11 driver only; ASan/UBSan remain active and leak detection remains on for our headless/paths/SDL-init tests and for non-X11 frames.

After these corrections, the full 23/23 matrix passed. No test was skipped and no PASS was claimed before the real run.

## 5. Security, licensing and limitations

- Linux installs only the pinned official Ubuntu packages from the activation; `sudo` is limited to apt install on the ephemeral runner; no secret, cache/upload, paid runner or runtime download.
- SDL3 zlib notice preserved for future distribution; `NLE-D009 OPEN`; no release/redistribution.
- Real X11 is virtual-display (Xvfb/openbox), not physical monitor certification. Wayland runtime is `NOT_QUALIFIED`; macOS Cocoa was configured and exercised on the hosted runner, but that is not physical hardware/driver certification. DPI/IME/hotplug/renderer/GPU/audio/public ABI are out of scope.
- The sanitizer job suppresses only `leak:X11_` frames from SDL3's X11 driver; ASan/UBSan and leak detection remain active for our code and non-X11 frames. This is a documented third-party limitation, not a blanket sanitizer disable.
- No HIGH/CRITICAL known; native CI passed at the code head and the result remains subject to the independent audit and final documentation-head Docs Validation.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the window target and the install/Xvfb step restores the previous state.

## 7. Proposed checkpoint delta (not promoted)

After an approved squash merge and readback, a separate checkpoint PR may record the fourth real CORE-01 slice, exact PR/CI/audit/merge SHA, X11/Xvfb/openbox and Win32/Cocoa results, 23 CTests, and the explicit statement that this is a window lifecycle slice, not renderer/GPU/audio/ABI/release. This evidence does not self-promote that checkpoint.
