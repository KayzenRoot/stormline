# NLE-PRPLAN-SIM-02-01 — Internal 3D physics metadata governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — no implementation authorized by this WO.** **Formal packet:** `NLE-PRPLAN-SIM-02-01`. **Issue:** #47. **Base:** `1c7a6880`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Architecture:** [sim-02-internal-physics-3d-metadata](../architecture/sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-governance-v0](../contracts/sim-02-governance-v0.md). **Planning policy:** [ADR-0032](../adr/0032-sim-02-engine-owned-3d-physics-and-collider-publication.md) `PROPOSED`.

## OBJECTIVE

Record the owner-approved bounded internal governance for SIM-02 logical 3D physics metadata, including scope, ownership, risk/release class and exact future slices.

## CONTEXT

SIM-02 follows the completed internal sequences of WORLD-02 and CORE-03. No 3D physics runtime, solver, broadphase, query execution or simulation exists.

## SCOPE

- ADR-0133, internal architecture, governance contract and this WO.
- G6 activation evidence, activation JSON, checkpoint and manifest/validator bookkeeping.

## OUT OF SCOPE

All code: `src/stormline/physics3d/**`, tests, CMake, workflows. Solver/backend selection, simulation, broadphase/narrowphase execution, queries, contacts, ECS mutation, GPU, editor, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0032, module catalog, SIM-02 plan, WORLD-02 and CORE-03 evidence.

## REQUIREMENTS

GOV-001..007 of the governance contract; ADR-0133; oracles BODY3-01, SHAPE3-01, BROAD3-01, QUERY3-01, CONSTRAINT3-01, INTEGRATION3-01 and QLF-S201..S204.

## ARCHITECTURE RULES

SIM-02 owns logical 3D physics intent metadata only; no solver handle, backend type, pointer or runtime behavior may cross the boundary.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no solver/backend/broadphase/query/contact/simulation/ECS/GPU/editor; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents and activation are exact and internally consistent.
- No code, CMake or workflow change.
- Manifest root `SIM02_01_APPROVED_GOVERNANCE_ONLY`; `SIM-02-02` remains `PLANNED_BLOCKED`.
- pt-BR audit `APPROVED`.

## TESTS

Validator and documentation checks only; no executable test is authorized by this packet.

## DELIVERABLES

ADR, architecture, governance contract, WO, G6 evidence, activation JSON and validator updates.

## REVIEW FORMAT

pt-BR: base/head, files, manifest counts, security/rollback, no overclaim.

## STOP CONDITION

Stale base, missing owner authority, runtime/physics claim, allowlist violation, failed validator, HIGH/CRITICAL.

## CONTEXT LOCK

Base `1c7a6880`; governance contract and ADR blobs pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-02-01-G6-ACTIVATION.md`.
