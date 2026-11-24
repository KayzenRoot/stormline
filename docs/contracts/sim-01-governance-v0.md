# SIM-01 governance contract v0 — internal logical 2D physics metadata

**Status:** `APPROVED GOVERNANCE / INTERNAL_ONLY / NO PHYSICS RUNTIME`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Architecture:** [sim-01-internal-physics-2d-metadata](../architecture/sim-01-internal-physics-2d-metadata.md). **Planning-only policy:** [ADR-0031](../adr/0031-sim-01-physics-2d-fixedstep-backend-policy.md) remains `PROPOSED`.

## 1. Scope

This contract governs the internal SIM-01 sequence: logical rigid-body descriptors, collision-shape descriptors, query intents, joint descriptors, trigger/sensor metadata and collision masks. It does not authorize a solver, backend adoption, simulation, contact generation, query execution, event dispatch, ECS mutation, tilemap bridge, editor UI or public ABI.

## 2. Invariants

1. **GOV-001 Fail closed:** invalid identities, types, dimensions, scales, masks or budgets produce a typed error and zeroed output; no silent fallback.
2. **GOV-002 Single authority:** WORLD-01/02 own entities/scenes, TWO-01/02/04 own canvas/tilemaps, CORE-05/06 own math/tick, WORLD-03 streaming, DATA-02..05 assets/journal/cook, GAME/NET runtime authority.
3. **GOV-003 Identity separation:** body/shape/joint metadata is not a solver handle and never exposes backend types or raw pointers.
4. **GOV-004 Determinism:** fixed-capacity plans, stable ordering where required, no allocation, exception, file, network, audio, GPU, clock, thread or global state.
5. **GOV-005 No runtime claim:** no solver, simulation, broadphase, narrowphase, query result, contact, event dispatch, replay or benchmark.
6. **GOV-006 Diagnostics:** every error carries a typed code, source ID and bounded index; output plans are reset before validation.
7. **GOV-007 Traceability:** one stable Work Order ID across issue, branch, PR, evidence and corrections; exact allowlists per slice.

## 3. Planned API areas (frozen only in `-02`)

- Body intent: type, pose, damping, mass flags, entity reference.
- Shape intent: kind, finite dimensions, density, material reference.
- Query intent: ray/overlap/cast descriptors and result limits.
- Joint intent: kind, anchors, limits, break policy.
- Trigger intent: sensor descriptor and event enablement.
- Mask intent: category/mask/group bits and symmetric checks.
- Common diagnostic and capacity types under `src/stormline/physics2d/`.

Exact type names, capacities, error enums and allowlists are frozen by `SIM-01-02` before implementation. No code may be created from this governance contract alone.

## 4. Slice oracles

| ID | Scenario | Oracle |
|---|---|---|
| BODY-01 | bodies | unique IDs, type allowlist, finite pose/damping, entity refs |
| COL-01 | shapes | kind/dimension/density validity, material refs |
| QRY-01 | queries | descriptors, finite regions, bounded limits |
| JNT-01 | joints | body refs, anchors, limits, break policy |
| TRG-01 | triggers | sensor descriptors, event flags, uniqueness |
| MSK-01 | masks | bit ranges, symmetric compatibility, group rules |
| QLF-S101 | integrated | body -> shape -> query -> joint -> trigger -> mask |
| QLF-S102 | deterministic repeat | identical plans/counts |
| QLF-S103 | failure recovery | typed error followed by valid operation |
| QLF-S104 | bounded overload | 10,000 attempts keep caps |

## 5. Out of scope

Solver/backend, simulation, broadphase/narrowphase, contacts, query execution, event dispatch, ECS mutation, replay/snapshot, tilemap and 2.5D bridges, editor, GPU, audio, export, performance, ABI, release and production readiness.

## 6. Qualification statement

Passing internal CI qualification is not the catalog's 2D collision/stability/stress suite, determinism, replay, security, soak or performance qualification. SIM-01 may close only as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
