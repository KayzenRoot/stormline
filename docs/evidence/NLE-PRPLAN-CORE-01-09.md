# NLE-PRPLAN-CORE-01-09 — Event queue and replay

**Status:** `CODE_IMPLEMENTED / LOCAL_PREFLIGHT_PASS / NATIVE_CI_PENDING / AWAITING_AUDIT`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-09`. **ADR:** [ADR-0088](../adr/0088-core-01-event-queue-slice.md). **Contract:** [core-01-event-queue-v0](../contracts/core-01-event-queue-v0.md). **WO:** [NLE-PRPLAN-CORE-01-09](../work-orders/NLE-PRPLAN-CORE-01-09.md). **Issue:** [#18](https://github.com/KayzenRoot/stormline/issues/18).

First real CORE-01 host-event path: normalize selected SDL3 events into internal values, enqueue them in a fixed-capacity queue with monotonic sequence/timestamps, surface overflow without silent loss, and replay captured events deterministically. No gamepad, IME, DPI, hotplug, gameplay mapping, public ABI or release.

## 1. Authorization and Context Lock

- **Gate:** [PR #443](https://github.com/KayzenRoot/stormline/pull/443) squash-merged as `a4de0bc1aebda7e32e3db149cdd8e968a9733506`; audit #6958755709 **APPROVED**.
- **Base:** `a4de0bc1aebda7e32e3db149cdd8e968a9733506`.
- **Selector:** `select_packet.py NLE-PRPLAN-CORE-01-09 --json` → `EXECUTOR_READY`, exit 0; `-10`, `CORE-02-04` and every other ID exit 2.
- **Predecessors:** `-03`..`-08` completed; CORE-02-03 ownership completed via PR #441.

SDL3 remains `3.4.20`, commit `f00dc919ca35b9756316e86c4777392de442f9b2`, zlib, static build-time `FetchContent`.

## 2. Implemented behavior

- `InputEventType`: quit, key down/up, mouse motion, mouse button down/up, window resized, window focus gained/lost, window close requested; `None` default.
- `EventError`: `None`, `Empty`, `Full`, `Overflow`, `WrongThread`, `RuntimeNotInitialized`, `InvalidReplay`, `InternalFailure`.
- `EventQueue`: fixed capacity **256**, no dynamic allocation, noncopyable/nonmovable, owner thread recorded at construction.
- `poll()`: owner-thread only; requires `SDL_WasInit(SDL_INIT_EVENTS)`; returns `Overflow` before consuming SDL events when the queue is full; drains SDL events into normalized values; skips unhandled types; assigns `sequence = next_sequence_++` and preserves the SDL timestamp. Remaining SDL events stay queued if capacity is reached.
- `replay()`: validates type, sequence, timestamp and capacity **before** mutating; preserves captured sequence/timestamp; advances `next_sequence`; rejects null+count, `None`, descending sequence/timestamp and insufficient capacity atomically.
- `pop()`: owner-thread only; removes one event or returns `Empty`; clears the slot.
- `clear()`: owner-thread only; empties the queue without resetting the sequence counter or flushing SDL.
- Header includes only C++ standard headers; SDL is confined to `event_queue.cpp`. No global state/singleton/filter/thread.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/internal/event_queue.hpp` | Internal API; standard headers only |
| `src/stormline/core/internal/event_queue.cpp` | SDL3 normalization, bounded queue and replay |
| `tests/core/event_queue_tests.cpp` | EVT-01..EVT-08 modes |
| `CMakeLists.txt` | Additive `stormline_core01_event_queue` target and eight CTests |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-01-09 path filters |
| `docs/evidence/NLE-PRPLAN-CORE-01-09.md` | This Evidence Bundle |

No other path changed. Existing CORE-01/CORE-02 targets are unchanged except additive test wiring.

## 4. Tests and real results

### Local preflight (observed)

- CMake/Ninja configure with local SDL3 3.4.20 source override (CI uses the exact pinned commit), `stormline_core01_event_queue_test` build: **OK**.
- `ctest -R core01_events_`: **8/8 passed** on Windows/MSVC 14.44.
- Modes: `basic`, `sequence`, `overflow`, `replay`, `wrong_thread`, `not_initialized`, `empty_clear`, `lifetime`.
- The local test binary uses `SDL_VIDEODRIVER=dummy` and synthetic `SDL_PushEvent` events; no physical input is claimed.

### Native CI (authoritative, pending)

Pending exact-head Docs Validation and native Linux/Linux-sanitizers/Windows/macOS runs. This document will be updated with run IDs and observed CTest counts only after they complete; no native PASS is claimed yet.

Expected matrix: existing 32 CTests plus 8 event tests = **40 CTests** per native job, with Linux ASan/UBSan.

## 5. Security, licensing and limitations

- No third-party dependency beyond the already pinned SDL3 baseline; no package installation, secret, upload, paid runner/service or runtime download.
- No SDL type/macro/handle in the header; no gameplay mapping, gamepad, IME, DPI, hotplug, blocking loop, public ABI or release.
- Synthetic events prove queue/normalization/replay semantics, not physical keyboard/mouse/gamepad behavior or focus/IPC/OS edge cases.
- The event queue is not thread-safe for concurrent access; only the owner thread may mutate it. `SdlRuntime` must outlive the queue.
- ADR-0003/0075 remain `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.
- No HIGH/CRITICAL known; final status subject to exact-head CI and independent pt-BR audit.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the event-queue target/tests, the additive workflow paths and this evidence restores the previous state.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the fifth real CORE-01 slice, exact PR/CI/audit/merge SHA, 8 `core01_events_*` tests and 40 total CTests across Linux, Linux ASan/UBSan, Windows and macOS, and the explicit statement that this is event queue/replay only — not physical input, gamepad, IME, DPI, hotplug, gameplay mapping, public ABI or release. This evidence does not self-promote the checkpoint.
