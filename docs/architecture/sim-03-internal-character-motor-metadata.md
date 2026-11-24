# SIM-03 — Internal logical character motor metadata

**Status:** `APPROVED INTERNAL ARCHITECTURE / LOGICAL METADATA ONLY`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Planning policy remains:** [ADR-0033](../adr/0033-sim-03-authoritative-character-motor-policy.md) `PROPOSED`. **Runtime character claims:** none.

## 1. Purpose

Define a bounded, deterministic metadata layer for 2D/3D character controller profiles, locomotion, input response intent and decoupled camera intent. It answers what a character author requested, not how movement is executed, how contacts gate it or which backend is used.

## 2. Logical model

- **Controller profile intent:** dimension, kinematic/dynamic mode, finite extents, up axis and ground/step/slope policy flags.
- **Locomotion intent:** walk/run/air speeds, acceleration, jump/dash descriptors and tick-based grace/buffer windows.
- **Input response intent:** bounded action/axis descriptors with tick-indexed buffering metadata.
- **Decoupled camera intent:** follow/look/damping descriptors and explicit authority-independence flags.
- **Diagnostics:** typed error plus source ID and index; outputs reset on failure.

## 3. Runtime non-goals

No motor, sweeper, contact query, solver, input polling, camera update, animation root motion, ECS mutation, network prediction, GPU, I/O or public ABI. Those remain future decisions under ADR-0033 and other module owners.

## 4. Ownership boundaries

- SIM-01/02 own collision metadata and future physics runtime.
- CORE-03/04/06 own jobs, fixed tick and scheduling.
- WORLD-01/02 own entity and scene identity.
- GAME/NET own input authority, prediction and reconciliation.
- SIM-04 owns animation/root motion; GFX/editor own camera rendering.
- SIM-03 owns only logical character motor intent metadata.

## 5. Determinism and bounds

All plans are fixed-capacity, header-only, `noexcept` and allocation-free. Capacities are frozen in `-02`; validation and overload behavior must be deterministic across compilers. No clock, random source, file, network, audio, GPU, thread, RTTI hash or global state is allowed. Tick windows are integer ticks, never wall-clock seconds.

## 6. Planned slices

| Slice | Logical deliverable | Oracle |
|---|---|---|
| `-03` | controller profile metadata | CTRL-01 |
| `-04` | locomotion metadata | LOCO-01 |
| `-05` | input response metadata | INPUT-01 |
| `-06` | decoupled camera metadata | CAM-01 |
| `-07` | integrated qualification | QLF-S301..S304 |
| `-08` | closeout | evidence/audit |

`-02` must freeze exact types, capacities, error codes, allowlists and test fixtures before `-03` is activated.

## 7. Explicit non-goals

No motor, backend dependency, contact-gated movement, gameplay-feel benchmark, replay/snapshot, ECS mutation, input device layer, camera transform, animation root motion, GPU, hardware measurement or public ABI. ADR-0033 remains the separate planning authority for those future runtime decisions.
