# NLE-PRPLAN-WORLD-04-03 — Terrain patch metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-04-03`. **Predecessor:** `WORLD-04-02` contract. **Issue:** #44. **Base:** `d5295ff`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md).

## OBJECTIVE

Implement bounded logical terrain-patch metadata with stable keys, unique signed tiles, LOD limits, neighbor references and a deterministic patch plan.

## CONTEXT

WORLD-04-01/-02 are approved. No heightfield storage, mesh generation, terrain renderer, streamer or editor exists.

## SCOPE

- `terrain_types.hpp`, `terrain_patch_plan.hpp` and TER-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Splat, vegetation, water, sky, weather, qualification, closeout; heightfield/mesh storage, mesh generation, rendering, GPU LOD, texture residency, physics, networking, editor, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0130, internal contract, governance contract, WORLD-04 architecture.

## REQUIREMENTS

GOV-001..007; ADR-0130; TER-01.

## ARCHITECTURE RULES

WORLD-04 owns authored terrain intent metadata only; GFX-04 owns geometry/LOD/visibility, WORLD-03 owns cells/streaming, DATA-04/05 own source/cook.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no heightfield/mesh storage, renderer, GPU, physics/network, editor, dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; TER-01 valid/invalid fixtures.
- No heightfield storage, mesh generation, renderer or runtime terrain.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

TER-01 asset/revision/count validation, unique keys and signed tiles, patch revisions, LOD bounds, topology allowlist, neighbor existence/uniqueness/self-rejection, capacity, reset and determinism.

## DELIVERABLES

Headers, TER-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TER-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, heightfield/mesh/runtime selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `d5295ff`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-04-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-04-03.md`.
