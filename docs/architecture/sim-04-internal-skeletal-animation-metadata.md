# SIM-04 — Internal logical skeletal animation metadata

**Status:** `APPROVED INTERNAL ARCHITECTURE / LOGICAL METADATA ONLY`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Planning policy remains:** [ADR-0034](../adr/0034-sim-04-animation-authority-retarget-ik-and-ragdoll.md) `PROPOSED`. **Runtime animation claims:** none.

## 1. Purpose

Define a bounded, deterministic metadata layer for retarget profiles, blend trees, IK chains, ragdoll profiles, compression profiles and sync groups. It answers what an animation author requested, not how poses are evaluated, solved, compressed or synchronized.

## 2. Logical model

- **Retarget intent:** source/target joint mapping pairs, bind-basis scale and semantic references.
- **Blend tree intent:** node kinds, finite weights, thresholds and graph shape.
- **IK intent:** chain lengths, iteration budgets and tolerances.
- **Ragdoll intent:** body/joint mapping references and activation intent; SIM-02 owns physics lifetime.
- **Compression intent:** bit widths, keyframe intervals and quality flags.
- **Sync intent:** phase offsets, markers and group references.
- **Diagnostics:** typed error plus source ID and index; outputs reset on failure.

## 3. Runtime non-goals

No pose evaluator, graph runtime, IK solver, ragdoll activation, codec, root-motion application, ECS mutation, network prediction, GPU, I/O or public ABI. Those remain future decisions under ADR-0034 and other module owners.

## 4. Ownership boundaries

- SIM-03 owns character motion and applied-motion receipts; SIM-02 owns physics/ragdoll lifetime.
- CORE-03/04/06 own jobs, tick and scheduling.
- DATA-02..05 own clips, assets, journal, cook and streaming data.
- GAME/NET own runtime authority.
- SIM-04 owns only logical animation intent metadata.

## 5. Determinism and bounds

All plans are fixed-capacity, header-only, `noexcept` and allocation-free. Capacities are frozen in `-02`; validation and overload behavior must be deterministic across compilers. No clock, random source, file, network, audio, GPU, thread, RTTI hash or global state is allowed.

## 6. Planned slices

| Slice | Logical deliverable | Oracle |
|---|---|---|
| `-03` | retarget profile metadata | RET-01 |
| `-04` | blend tree metadata | BLEND-01 |
| `-05` | IK chain metadata | IK-01 |
| `-06` | ragdoll profile metadata | RAG-01 |
| `-07` | compression profile metadata | CMP-01 |
| `-08` | sync group metadata | SYNC-01 |
| `-09` | integrated qualification | QLF-S401..S404 |
| `-10` | closeout | evidence/audit |

`-02` must freeze exact types, capacities, error codes, allowlists and test fixtures before `-03` is activated.

## 7. Explicit non-goals

No pose evaluator, solver, codec, ragdoll runtime, root-motion application, replay, ECS mutation, GPU, hardware measurement or public ABI. ADR-0034 remains the separate planning authority for those future runtime decisions.
