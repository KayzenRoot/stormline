# SIM-04 governance contract v0 — internal logical skeletal animation metadata

**Status:** `APPROVED GOVERNANCE / INTERNAL_ONLY / NO ANIMATION RUNTIME`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Architecture:** [sim-04-internal-skeletal-animation-metadata](../architecture/sim-04-internal-skeletal-animation-metadata.md). **Planning-only policy:** [ADR-0034](../adr/0034-sim-04-animation-authority-retarget-ik-and-ragdoll.md) remains `PROPOSED`.

## 1. Scope

This contract governs the internal SIM-04 sequence: retarget profile descriptors, blend tree descriptors, IK chain descriptors, ragdoll profile descriptors, compression profile descriptors and sync group descriptors. It does not authorize a pose evaluator, graph runtime, IK solver, ragdoll activation, codec, root-motion application, ECS mutation, editor UI or public ABI.

## 2. Invariants

1. **GOV-001 Fail closed:** invalid joint mappings, node kinds, weights, chain lengths, bit widths, phases or references produce a typed error and zeroed output; no silent fallback.
2. **GOV-002 Single authority:** SIM-03 owns motion/root-motion receipts, SIM-02 owns physics/ragdoll lifetime, CORE-03/04/06 own jobs/tick, DATA-02..05 own clips/assets, GAME/NET own authority.
3. **GOV-003 Identity separation:** retarget/blend/IK/ragdoll metadata is not a runtime handle and never exposes backend types or raw pointers.
4. **GOV-004 Determinism:** fixed-capacity plans, stable ordering where required, no allocation, exception, file, network, audio, GPU, clock, thread or global state.
5. **GOV-005 No runtime claim:** no pose evaluation, blend execution, IK solve, ragdoll activation, codec, sync execution, root-motion application or benchmark.
6. **GOV-006 Diagnostics:** every error carries a typed code, source ID and bounded index; output plans are reset before validation.
7. **GOV-007 Traceability:** one stable Work Order ID across issue, branch, PR, evidence and corrections; exact allowlists per slice.

## 3. Planned API areas (frozen only in `-02`)

- Retarget intent: joint mapping pairs, bind-basis scale, semantic references.
- Blend intent: node kinds, weights, thresholds, graph shape.
- IK intent: chain lengths, iteration budgets, tolerances.
- Ragdoll intent: body/joint mapping references and activation flags.
- Compression intent: bit widths, keyframe intervals, quality flags.
- Sync intent: phase offsets, markers and group references.
- Common diagnostic and capacity types under `src/stormline/animation/`.

Exact type names, capacities, error enums and allowlists are frozen by `SIM-04-02` before implementation. No code may be created from this governance contract alone.

## 4. Slice oracles

| ID | Scenario | Oracle |
|---|---|---|
| RET-01 | retarget | unique source/target joints, finite scale, semantic refs |
| BLEND-01 | blend trees | kind allowlist, finite weights, thresholds, acyclicity |
| IK-01 | IK chains | chain length, iteration budget, finite tolerances |
| RAG-01 | ragdoll | body/joint mapping refs, activation flags |
| CMP-01 | compression | bit widths, keyframe intervals, quality flags |
| SYNC-01 | sync groups | phase bounds, marker ordering, group refs |
| QLF-S401 | integrated | retarget -> blend -> IK -> ragdoll -> compression -> sync |
| QLF-S402 | deterministic repeat | identical plans/counts |
| QLF-S403 | failure recovery | typed error followed by valid operation |
| QLF-S404 | bounded overload | 10,000 attempts keep caps |

## 5. Out of scope

Pose evaluation, blend/IK execution, ragdoll runtime, codecs, root-motion application, replay/snapshot, ECS mutation, editor, GPU, audio, export, performance, ABI, release and production readiness.

## 6. Qualification statement

Passing internal CI qualification is not the catalog's animation retarget/blend/IK/ragdoll/compression/sync suite, quality, determinism, security, soak or performance qualification. SIM-04 may close only as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
