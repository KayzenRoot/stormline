# NLE-PRPLAN-CORE-04-02 — Contract correction CD-01

**Status:** `AUDITED CONTRACT CORRECTION / NO PRODUCTION CODE`. **Base main:** `99e59b0`. **Packet:** `CORE-04-02`. **Contract:** [core-04-timeline-v0](../contracts/core-04-timeline-v0.md). **Related code packet:** `CORE-04-04`.

## Reason

The first CORE-04-04 implementation audit found that two frozen TICK oracles were not exercisable through the v0 public API:

- TICK-10: `TickOverflow` could not be reached because `start` always began at tick 0 and no bounded initial-tick path existed.
- TICK-12: `ReplayIncompatible` had no compatibility function; only the `ReplayScheduleHeader` fields existed.

The code was not merged with partial coverage. This correction adds the minimal API needed to exercise both oracles.

## Delta

1. `Timeline::start_at(ClockSource*, TimelineConfig, TickId initial_tick)`.
   - `start(source, config)` remains equivalent to `start_at(source, config, TickId{0})`.
   - The initial tick is only a starting counter; no new simulation semantics.
2. `replay_schedule_compatible(header, config, initial_tick, current_build_fingerprint)`.
   - Returns `None` on exact schema/rate/initial-tick match and on `build_fingerprint == 0`.
   - Returns `ReplayIncompatible` on schema, rate, initial-tick or nonzero fingerprint mismatch.
   - Never asserts cross-machine physics/network determinism.

No other API, file allowlist, dependency, ABI, release or production behavior changes.

## Proof obligations

- TICK-10: `start_at(max-1)` plus two `step_once` calls → second returns `TickOverflow`; duration/config overflow remains typed.
- TICK-12: compatibility accepts exact match and rejects schema/rate/initial/fingerprint mismatch with `ReplayIncompatible`.
- Same exact-head CI and sanitizer matrix as CORE-04-04.

## Security and rollback

Documentary correction only; no code/dependency. Unmerged: close the branch; after merge: normal revert PR. No release/ABI claim.
