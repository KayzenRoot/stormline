# TWO-02 INTERNAL_ONLY Tilemap Governance Contract v0 (NLE-PRPLAN-TWO-02-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `035a3f9`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md), [ADR-0023](../adr/0023-two-02-sparse-chunk-tilemap-policy.md) planning-only. **WO:** [NLE-PRPLAN-TWO-02-01](../work-orders/NLE-PRPLAN-TWO-02-01.md).

## Objective

Record ownership, trust boundaries, release/risk classes and gates before TWO-02 implementation. No tile renderer, map persistence, chunk codec, streaming I/O, collision solver, physics activation, dependency, public ABI or release is authorized.

## Admission and boundaries

- Formal dependencies are `TWO-01` and `DATA-04`; neither is module-qualified.
- TWO-02 owns logical grid/chunk math, tile cells, collision-authoring metadata, parallax and streaming plans.
- TWO-01 Canvas; DATA-02/03/04/05 identity/import/authoring/cook; GFX GPU; PHYS/WORLD collision/entities.
- No renderer, import format, codec, cache, physics engine, navigation system or hardware driver is selected.

## Policy invariants

1. **No renderer or I/O.** Metadata/planning only; no tile instance, buffer, texture, draw, file, cache or async job.
2. **Signed floor math.** Negative cells use mathematical floor division; truncation and overflow fail closed.
3. **Bounded and finite.** Fixed capacities; NaN/Inf, zero/negative dimensions, overflow and out-of-bounds cells are rejected.
4. **Collision metadata is not physics.** PHYS owns contacts/solver/activation; TWO-02 authors bounded shapes only.
5. **Deterministic.** Stable IDs, signed coordinates and declared order determine output.
6. **Fail closed.** Unknown modes/states, stale revisions and budget exhaustion are typed errors or declared safe degradation.
7. **No visual/performance claim.** Plans are not frames, maps, collision behavior, streaming speed or 60 FPS.
8. **Release boundary.** `INTERNAL_ONLY`; no ABI, hardware, driver, performance, security or production claim.

## First-slice scope (future, blocked)

- `-03` signed grid/chunk math.
- `-04` tile cell metadata.
- `-05` collision-authoring shapes.
- `-06` parallax metadata.
- `-07` streaming plan states/budgets.
- `-08` integrated qualification and `-09` closeout remain blocked.

## Gate state after merge

- Manifest root `TWO02_01_APPROVED_GOVERNANCE_ONLY`: **546 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 161 `COMPLETED`, 41 approved gates**.
- `TWO-02-01` becomes `APPROVED_GOVERNANCE`; `TWO-02-02`..`-09` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, renderer/import/physics/streaming I/O selection, unbounded world, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
