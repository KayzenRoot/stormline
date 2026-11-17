# ADR-0088 — CORE-01 event queue and replay slice

**Status:** `OWNER_DIRECTION_C01_D03_C01_D04_BOUNDED / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **This ADR is subordinate to and DOES NOT approve ADR-0003 or ADR-0075 as a whole, and does not clear G3 globally.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-01-09` | **Parent:** `NLE-PRPLAN-CORE-01-01` | **Issue:** #387 / implementation issue #18.

## Context and authority

C01-D03 (SDL3 thin host adapter, events hidden from the API) and C01-D04 (SDL video/events on the main thread with balanced init/quit) were explicitly owner-ratified. The `-07` SDL3 runtime and `-08` window lifecycle are completed and merged. The next formal CORE-01 packet is `-09`: input/event queue and replay.

This slice is bounded to **host event normalization, a fixed-capacity queue and deterministic replay of captured events**. It does not implement gameplay input mapping, physical-device certification, gamepad hotplug, IME, DPI, text editing, fullscreen, or a blocking application loop.

## Bounded technical decision

- Internal `stormline::core::internal::InputEventType`, `InputEvent`, `EventError`, `EventQueue`; no SDL type/macro/handle in the header.
- `EventQueue` has a fixed capacity of **256** events and no dynamic allocation. Operations are owner-thread only.
- `poll()` checks `SDL_WasInit(SDL_INIT_EVENTS)`, consumes pending SDL events through `SDL_PollEvent`, and normalizes only: quit, key down/up, mouse motion, mouse button down/up, window resized, window focus gained/lost and window close requested. Other SDL event types are skipped.
- Each live event receives a monotonically increasing internal `sequence`; `timestamp_ns` comes from SDL's event timestamp.
- If the queue is already full, `poll()` returns `Overflow` **before** consuming SDL events. If it fills while draining, remaining SDL events stay in SDL's queue; nothing is silently dropped. The caller drains and polls again.
- `replay(events, count)` accepts already-captured `InputEvent` values, validates strictly increasing sequence and non-decreasing timestamp against the current queue tail, preserves the original sequence/timestamp, and appends atomically only after full validation. It rejects `None` events, non-monotonic input, null arrays with non-zero count, and insufficient capacity with typed errors.
- `pop()` removes one event or returns `Empty`; `clear()` resets the internal queue but not the sequence counter.
- No global mutable state, singleton, blocking loop, hidden thread, SDL event filter, or public ABI.

## Alternatives rejected

- **Unbounded `std::vector` queue:** rejected; allocation in the event path and no deterministic overflow behavior.
- **Silent drop-oldest/drop-newest:** rejected; gameplay-critical input must not be silently lost, and overflow must be surfaced to the caller.
- **Raw SDL event in the API:** rejected; C01-D03 requires SDL hidden behind the adapter.
- **Gameplay input mapping or action bindings:** rejected; GAME-01 owns mapping.
- **Physical keyboard/mouse/gamepad/IME/DPI/hotplug certification:** rejected as out of this slice; synthetic SDL events prove queue semantics, not physical-device coverage.
- **Blocking event loop:** rejected; the queue is polled by the caller and CORE-04 owns frame/tick boundaries.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: EVT-01..EVT-08, real SDL3 event normalization using `SDL_PushEvent`, replay/overflow/wrong-thread/sequence/lifetime tests, 40 total CTests on Linux, Linux ASan/UBSan, Windows and macOS, no SDL in the header.
- Synthetic events are explicitly **not** physical input certification; gamepad/IME/DPI/hotplug/real input and gameplay mapping remain `NOT_QUALIFIED / out of scope`.
- ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the event-queue target/tests restores the previous state; no G2, registry or license change is part of this ADR.
