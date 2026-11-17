# NLE-PRPLAN-CORE-01-09 — G6 activation (event queue and replay)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `27cd592ec235a63def60f04757ac27700babd334`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-09`. **ADR:** [ADR-0088](../adr/0088-core-01-event-queue-slice.md). **Contract:** [core-01-event-queue-v0](../contracts/core-01-event-queue-v0.md). **WO:** [NLE-PRPLAN-CORE-01-09](../work-orders/NLE-PRPLAN-CORE-01-09.md).

## Owner authorization

The owner approved capability-based increments and the 3-4 PRs per response cadence on 2026-11-17 (`STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments`). C01-D03 (SDL3 thin adapter, events hidden) and C01-D04 (video/events on the main thread) are owner-ratified bounded directions. This gate activates **only** `NLE-PRPLAN-CORE-01-09`: the internal event queue/replay slice, after exact-head Docs Validation, objective pt-BR audit and squash/readback.

It does not approve ADR-0003/0075 globally, clear G3, authorize gamepad/IME/DPI/hotplug/physical-input qualification, gameplay input mapping, a renderer/audio/public ABI/release, or another packet/module.

## Predecessors

`-03` headless host PR #428; `-04`/`-05` reconciled; `-06` paths PR #432; `-07` SDL3 runtime PR #435; `-08` window lifecycle PR #438. All `COMPLETED`; no predecessor reopened. The independent CORE-02-03 ownership packet is also `COMPLETED` via PR #441 and is unaffected.

## Bounded technical slice

- Internal `InputEventType`, `InputEvent`, `EventError`, `EventQueue`; fixed capacity 256; no SDL type/macro/handle in the header.
- Owner-thread `poll()` requires `SDL_WasInit(SDL_INIT_EVENTS)` and normalizes only quit, key down/up, mouse motion/button, window resized/focus/close. Other SDL events are consumed and skipped.
- Monotonic internal sequence; SDL event timestamp; full queue returns `Overflow` before consuming SDL events, leaving remaining events in SDL's queue.
- `replay()` preserves captured sequence/timestamp and validates type/monotonicity/capacity atomically.
- `pop()`, `clear()`, `size()`, `empty()`, `next_sequence()`.
- No gameplay mapping, gamepad, IME, DPI, hotplug, blocking loop, allocation, global state or public ABI.
- Exact code allowlist: `event_queue.hpp`, `event_queue.cpp`, `tests/core/event_queue_tests.cpp`, additive `CMakeLists.txt`, additive workflow path filters, `docs/evidence/NLE-PRPLAN-CORE-01-09.md`.

## Gate state after merge (expected, not yet promoted)

- Manifest root `CORE01_09_READY_PREDECESSORS_COMPLETED`: **736 `PLANNED_BLOCKED`, 7 `COMPLETED` (CORE-01 -03..-08 + CORE-02-03), 4 approved gate entries, 1 `EXECUTOR_READY` (`CORE-01-09`)**.
- `select_packet.py NLE-PRPLAN-CORE-01-09` → exit 0; every other ID, including `-10` and `CORE-02-04`, exit 2.
- 80/80 module WOs remain `BLOCKED`; registry unchanged; ADR-0003/0075 `PROPOSED`; ADR-0088 bounded; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; `engine_implemented=false` at module/product level.

## Proof obligations for the code PR

EVT-01..EVT-08: live synthetic SDL normalization; sequence/timestamp order; overflow without silent drop; replay preservation; replay rejection/atomicity; wrong-thread; runtime/empty/clear; 1000-cycle lifetime and existing 32 CTests regression. Real Linux, Linux ASan/UBSan, Windows and macOS; no leak; no SDL in the header; no physical-input/gamepad/IME/DPI/hotplug/ABI/release claim; exact-head Docs Validation and pt-BR audit.

No code or native PASS is claimed by this gate.

## Security and rollback

No dependency, package installation, secret, upload, paid service or runtime download. Unmerged: close the gate branch; `main` untouched. After merge: normal revert PR, never force push. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
