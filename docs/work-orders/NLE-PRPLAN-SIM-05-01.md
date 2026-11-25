# NLE-PRPLAN-SIM-05-01 — Internal navigation/behavior metadata governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — no implementation authorized by this WO.** **Formal packet:** `NLE-PRPLAN-SIM-05-01`. **Issue:** #50. **Base:** `84b0064a`. **ADR:** [ADR-0136](../adr/0136-sim-05-internal-navigation-behavior-metadata.md). **Architecture:** [sim-05-internal-navigation-behavior-metadata](../architecture/sim-05-internal-navigation-behavior-metadata.md). **Contract:** [sim-05-governance-v0](../contracts/sim-05-governance-v0.md). **Planning policy:** [ADR-0035](../adr/0035-sim-05-engine-owned-navigation-and-behavior-authority.md) `PROPOSED`.

## OBJECTIVE

Record the owner-approved bounded internal governance for SIM-05 logical navigation and behavior metadata.

## CONTEXT

SIM-05 follows the completed internal sequences of WORLD-03 and SIM-02. No navmesh build, pathfinding, steering, behavior runtime or perception exists.

## SCOPE

- ADR-0136, internal architecture, governance contract and this WO.
- G6 activation evidence, activation JSON, checkpoint and manifest/validator bookkeeping.

## OUT OF SCOPE

All code: `src/stormline/navigation/**`, tests, CMake, workflows. Recast/Detour, navmesh build, pathfinding, steering execution, behavior runtime, perception polling, ECS mutation, GPU, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0035, module catalog, SIM-05 plan, WORLD-03 and SIM-02 evidence.

## REQUIREMENTS

GOV-001..007 of the governance contract; ADR-0136; oracles NAV-01, STEER-01, BT-01, PERC-01 and QLF-S501..S504.

## ARCHITECTURE RULES

SIM-05 owns logical navigation/behavior intent metadata only; no runtime handle, backend type, pointer or runtime behavior may cross the boundary.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no navmesh/pathfinder/steering/behavior/perception runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents and activation are exact and internally consistent.
- No code, CMake or workflow change.
- Manifest root `SIM05_01_APPROVED_GOVERNANCE_ONLY`; `SIM-05-02` remains `PLANNED_BLOCKED`.
- pt-BR audit `APPROVED`.

## TESTS

Validator and documentation checks only; no executable test is authorized by this packet.

## DELIVERABLES

ADR, architecture, governance contract, WO, G6 evidence, activation JSON and validator updates.

## REVIEW FORMAT

pt-BR: base/head, files, manifest counts, security/rollback, no overclaim.

## STOP CONDITION

Stale base, missing owner authority, runtime/navigation claim, allowlist violation, failed validator, HIGH/CRITICAL.

## CONTEXT LOCK

Base `84b0064a`; governance contract and ADR blobs pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-05-01-G6-ACTIVATION.md`.
