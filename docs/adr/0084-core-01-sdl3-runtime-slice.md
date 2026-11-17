# ADR-0084 — CORE-01 internal SDL3 runtime slice (init/quit only)

**Status:** `OWNER_DIRECTION_C01_D03_C01_D04_BOUNDED / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **This ADR is subordinate to and DOES NOT approve ADR-0003 or ADR-0075 as a whole, and does not clear G3 globally.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-01-07` | **Parent:** `NLE-PRPLAN-CORE-01-01` | **Issue:** #387 / implementation issue #18.

## Context and authority

The owner ratified C01-D03 (SDL3 as a thin host adapter, SDL hidden from any public API) and C01-D04 (SDL3 video on the main thread, balanced init/quit, headless independent of video/audio), and selected SDL3 **3.4.20** as a candidate in G3-V01. The owner then directed continuation of the next repository increments on 2026-11-17. The next formal packet is `-07`, which depends on `-06` (completed).

This ADR records only the first, minimal SDL3 integration: **main-thread SDL video/events initialization and shutdown**. It does not create a window, input loop, renderer, audio device, GPU resource, public ABI or release.

## Bounded technical decision

- **Dependency:** official SDL3 `release-3.4.20`, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib license, static link.
- **Acquisition:** CMake `FetchContent` from the official repository at the pinned full commit, at **build time only**. No system installation, no vendored source tree, no runtime download, no package manager and no paid service. The exact commit is immutable; the build fails if it cannot be fetched.
- **Build profile:** `SDL_SHARED=OFF`, `SDL_STATIC=ON`, tests/examples/install/test-library off; audio/joystick/haptic/HIDAPI/sensor/power/camera off; X11/Wayland/KMSDRM off for this slice; dummy video driver used for CI. Real window drivers are deferred to `-08`/PLAT qualification.
- **API:** internal `SdlRuntime` with typed `SdlError`, main-thread owner check, `initialize`, `shutdown`, `initialized`, and `linked_version`; no SDL headers/types in the internal header. Exact contract: [core-01-sdl3-runtime-v0](../contracts/core-01-sdl3-runtime-v0.md).
- **Ownership:** noncopyable/nonmovable, one active instance per process, no global mutable state in the adapter, no exceptions across the boundary, idempotent shutdown on the owner thread and no-throw destructor on the owner thread.
- **Errors:** `AlreadyInitialized`, `WrongThread`, `InitFailed`, `InternalFailure`; failed init calls `SDL_Quit` to clean partial state and leaves the adapter uninitialized.

## Alternatives considered and rejected

- **Fake/mock SDL backend:** rejected; it would not prove real integration.
- **System package installation (`apt`/Homebrew/vcpkg):** rejected for this slice; non-portable, privileged and not pinned.
- **Dynamic/shared SDL3:** rejected for the first slice; static linking is simpler and avoids runtime loader/path issues.
- **Full window/input/renderer integration now:** rejected; that is `-08` onward and needs real driver/display proof, not a CI dummy driver.
- **Vendoring SDL3 source:** rejected; unnecessary repository bloat and license/notice churn for a build-time pinned dependency.

## Proof and consequence

- This slice can reach G4/G5 **bounded internal** eligibility only after exact-head Docs Validation, objective pt-BR audit and merge of its gate PR.
- G6 activation is separate; code packet `-07` remains blocked until that gate is merged and a fresh Context Lock is recorded.
- Code proof must include build/link on Linux, Windows and macOS; dummy-video init/quit cycles; duplicate init; wrong-thread rejection; invalid-driver failure and recovery; linked version 3.4.20; no SDL include/type in the internal header/test translation unit; no window/renderer/audio/network use; existing 12 CTests regression.
- Real window creation, HiDPI, IME, hotplug, GPU/audio, public ABI, release and redistribution remain **NOT_QUALIFIED / out of scope**.
- SDL3 is zlib-licensed third-party software; its notice must be preserved in any future distribution. The Stormline engine license `NLE-D009` remains `OPEN`; no packaging or release is authorized.
- ADR-0003 and ADR-0075 remain `PROPOSED`; G3 global remains `NOT_CLEARED`; 80 module WOs remain `BLOCKED`; `engine_implemented=false` at module/product level.

## Rollback

Unmerged: close the gate/code branch; `main` untouched. After a future merge: normal revert PR, never force push. No G2, registry, workflow permission or license state is changed by this ADR.
