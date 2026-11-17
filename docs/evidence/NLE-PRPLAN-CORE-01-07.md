# NLE-PRPLAN-CORE-01-07 — SDL3 runtime init/quit

**Status:** `CODE_IMPLEMENTED / NATIVE_CI_PENDING / AUDIT_PENDING` · **Master program:** `STORM-CORE-01-IMPL-001` · **Formal packet:** `NLE-PRPLAN-CORE-01-07` · **ADR:** [ADR-0084](../adr/0084-core-01-sdl3-runtime-slice.md) · **Contract:** [core-01-sdl3-runtime-v0](../contracts/core-01-sdl3-runtime-v0.md) · **WO:** [NLE-PRPLAN-CORE-01-07](../work-orders/NLE-PRPLAN-CORE-01-07.md) · **Issue:** [#18](https://github.com/KayzenRoot/stormline/issues/18).

First real SDL3 integration in Stormline: a bounded internal runtime that initializes and shuts down SDL video/events on the owner thread. No window, input, renderer, GPU, audio, network, public ABI or release.

## 1. Authorization and Context Lock

- **Gate:** [PR #434](https://github.com/KayzenRoot/stormline/pull/434) merged as `062631ae17507c7a85a67a3d211b321ff3b54a65`; activated only `-07` after objective audit.
- **Base:** `062631ae17507c7a85a67a3d211b321ff3b54a65`.
- **Selector:** `python scripts/select_packet.py NLE-PRPLAN-CORE-01-07 --json` → `EXECUTOR_READY`, exit 0; `-06`, `-08` and every other ID exit 2.
- **SDL3 pin:** official `release-3.4.20`, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib license, static link.

| Source | Raw SHA-256 |
|---|---|
| `docs/11-checkpoint.md` | `12a15be3c4a00cfa10d3b576b0015e385371b743c1a07dda3816ff222e7fa29e` |
| `docs/10-decisions-ledger.md` | `420220915e0600bb84167106d3384b28e27cd2f4375c1e16ccb8374d701e216c` |
| `docs/03-scope.md` | `39ad13b45738516904b767a8997551cccce2a9ff8ea8642c152bb815fa67c0c7` |
| `docs/09-definition-of-done.md` | `7fc04cc33aad22197b68bcda43fbd356726f11e401cf0e2b68c97f685b12778e` |
| `docs/adr/0003-core-01-platform-technology.md` | `475d8e3771ff72cc8d81fd2dd9b89f7795853f5223eca30bc1ebb3804249d226` |
| `docs/adr/0083-core-01-internal-headless-slice.md` | `c484fb10aec5a4b61919967b9026494484f6ae11461f90b94cb1e38fdbdc99a9` |
| `docs/adr/0084-core-01-sdl3-runtime-slice.md` | `0ef009b2c9719d6a501425e326ac744ad012c7ee33aad82cbc48ba2e0f5ed2eb` |
| `docs/contracts/core-01-internal-headless-v0.md` | `b4457feaf74379b5ffd3f8e744727a48cc7673383cd5c259073b495dfd10f38b` |
| `docs/contracts/core-01-process-paths-v0.md` | `4a6cd9fb25f3b60d34fe91373400ebd04e32a0bfa809dd234171110784c3721d` |
| `docs/contracts/core-01-sdl3-runtime-v0.md` | `dec8d249c063a42191c9b367493806f9758759c195820296c5c682fc25f1f7e2` |

SDL3 API signatures were read from the pinned commit before coding: `SDL_Init` returns `bool` (true on success), `SDL_GetVersion` returns an `int` version number, and `SDL_SetMainReady` is declared in `SDL_main.h`. This avoids the SDL2-to-SDL3 return-type trap.

## 2. Implemented behavior

- `SdlError` `None/AlreadyInitialized/WrongThread/InitFailed/InternalFailure`; `SdlRuntime` noncopyable/nonmovable; `initialize`, `shutdown`, `initialized`; all `noexcept`; no exceptions cross the boundary.
- Owner thread recorded at construction; worker-thread init/shutdown returns `WrongThread` without calling SDL.
- Duplicate initialize returns `AlreadyInitialized`; shutdown on uninitialized returns `None` (idempotent).
- Failed `SDL_Init` calls `SDL_Quit()` to clean partial state, remains uninitialized and returns `InitFailed`.
- Destructor calls `SDL_Quit()` only when initialized and on the owner thread; no throw.
- `linked_version()` returns the linked SDL version via `SDL_GetVersion` and `SDL_VERSIONNUM_*`.
- Header includes no SDL header/type/macro; only `sdl_runtime.cpp` includes `<SDL3/SDL.h>` and `<SDL3/SDL_main.h>`. The test TU has `#if defined(SDL_h_) #error` leak guard.
- SDL calls limited to `SDL_SetMainReady`, `SDL_Init(VIDEO|EVENTS)`, `SDL_Quit`, `SDL_GetVersion`. No window/input/renderer/audio/network call.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/internal/sdl_runtime.hpp` | Internal API, no SDL types |
| `src/stormline/core/internal/sdl_runtime.cpp` | Pinned SDL3 init/quit/version implementation |
| `tests/core/sdl_runtime_tests.cpp` | SDL-01..SDL-07 tests + header leak guard |
| `CMakeLists.txt` | Pinned FetchContent, SDL target, 6 new CTests; existing 12 preserved |
| `.github/workflows/core01-internal-headless.yml` | Timeout increase for the SDL3 build only |
| `docs/evidence/NLE-PRPLAN-CORE-01-07.md` | This Evidence Bundle |

No other path changed.

## 4. Tests and real results

### Local preflight

No CMake/Ninja is installed locally; installing is not authorized. The official SDL3 3.4.20 release tarball was downloaded to a temporary directory (SHA-256 `f3bb06f55bed9557227a700af2ea62e49497ebdf58037732a731a5fb3ef8581f`), and `sdl_runtime.cpp` was compiled against its exact headers with preinstalled MSVC 14.44 `/std:c++20 /W4 /WX /EHsc` → **OK**. This is a header/API compile check only, not a link/run or target qualification. The real SDL3 build/link/test evidence is the native CI below. No local runtime PASS is claimed.

### Native CI (authoritative, pending)

The code PR must build/link SDL3 from the pinned commit and run on `ubuntu-24.04`, `windows-2025-vs2026` and `macos-15`, plus Linux ASan/UBSan when supported. It must execute the existing 12 CTests and the six new SDL CTests: basic 20 cycles, wrong thread, invalid-driver failure/recovery, destructor, version 3.4.20, header isolation. The dummy video driver is set via `SDL_VIDEODRIVER=dummy`. The PR remains Draft until exact-head Docs Validation and native results are observed and recorded here.

## 5. Security, licensing and limitations

- SDL3 is fetched at **build time only** from the official repository at the full pinned commit; no system install, vendor copy, package manager, runtime download or paid service. zlib notice must be preserved in any future distribution; `NLE-D009` remains `OPEN`.
- No window/renderer/audio/GPU/network/public ABI; real display/driver proof is `NOT_QUALIFIED` and deferred to `-08`/PLAT.
- No secret, cache/upload, paid runner or workflow permission change; standard public runners R$0.
- No HIGH/CRITICAL known; subject to exact-head CI and audit.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After a merge: normal revert PR, never force push. SDL3 is a build-time subproject, not a vendored source tree; reverting CMake/target removes it.

## 7. Proposed checkpoint delta (not promoted)

After an approved squash merge and readback, a separate checkpoint PR may record the third real CORE-01 slice, exact PR/CI/audit/merge SHA, SDL3 pin/license, 18 CTests including SDL init/quit, and the explicit statement that this is still an internal init/quit adapter, not window/renderer/audio/ABI/release. This evidence does not self-promote that checkpoint.
