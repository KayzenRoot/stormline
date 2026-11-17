# ADR-0091 — CORE-01 lifecycle request state machine

**Status:** `OWNER_DIRECTION_C01_D07_BOUNDED / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **This ADR is subordinate to and DOES NOT approve ADR-0003 or ADR-0075 as a whole, and does not clear G3 globally.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-01-12` | **Parent:** `NLE-PRPLAN-CORE-01-01` | **Issue:** #387 / implementation issue #18.

## Context and authority

C01-D07 requires an explicit lifecycle state machine, recoverable init failure, typed errors and idempotent cleanup. The `-07`..`-11` slices are completed. The next formal CORE-01 packet is `-12`: sleep/resume/shutdown requests.

This slice is bounded to a **host lifecycle request state machine**: running → suspend pending → suspended → resume pending → running, and running/suspended → shutdown pending → terminated. It consumes the existing `InputEvent` quit/window-close signals. It does not implement OS sleep/resume hooks, signal handlers, forced process termination, persistence, project saving, renderer device-loss recovery or a public ABI.

## Bounded technical decision

- New internal `LifecycleState`, `LifecycleError`, `LifecycleController` in `lifecycle.hpp/cpp`; no SDL/platform type in the header.
- Owner-thread state machine with explicit transitions and typed errors; no exceptions cross the boundary.
- States: `Running`, `SuspendPending`, `Suspended`, `ResumePending`, `ShutdownPending`, `Terminated`.
- Requests: `request_suspend`, `acknowledge_suspend`, `request_resume`, `acknowledge_resume`, `request_shutdown`, `acknowledge_shutdown`, `request_terminate`.
- `observe(const InputEvent&)` maps `Quit` and `WindowCloseRequested` to a shutdown request; other events are ignored. This is a host-event policy, not gameplay input mapping.
- `should_continue()` is false in `ShutdownPending`/`Terminated`; `state()` is read-only.
- Invalid transitions return `InvalidTransition` and leave the state unchanged. Repeated shutdown after termination returns `AlreadyTerminated`. `request_terminate` is the explicit forced transition.
- No OS sleep/resume signal, no process kill, no persistence, no window/renderer teardown and no public ABI.

## Alternatives rejected

- **Direct OS signal handlers/sleep hooks now:** rejected; platform-specific, hard to test deterministically and not required to establish the state contract.
- **Implicit shutdown on any input/window event:** rejected; only quit/close-requested are lifecycle signals; other events are ignored.
- **Unconditional idempotent transitions:** rejected; invalid transitions must be observable so corruption cannot be hidden.
- **Destructor-driven forced shutdown:** rejected; the caller owns the lifecycle and must acknowledge shutdown explicitly.
- **Persistence/save-on-suspend:** rejected; project/save ownership belongs to other modules.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: LCY-01..LCY-06, normal suspend/resume/shutdown, invalid transitions, event observation, wrong-thread, 100 recovery cycles, existing 53 CTests regression, Linux ASan/UBSan.
- Physical OS sleep/resume/termination, forced process kill, persistence and renderer/device-loss recovery remain `NOT_QUALIFIED / out of scope`.
- ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the lifecycle target/tests and evidence restores the previous state; no G2, registry or license change is part of this ADR.
