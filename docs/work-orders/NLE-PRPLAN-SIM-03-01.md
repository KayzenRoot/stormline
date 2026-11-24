# NLE-PRPLAN-SIM-03-01 — Internal character motor metadata governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — no implementation authorized by this WO.** **Formal packet:** `NLE-PRPLAN-SIM-03-01`. **Issue:** #48. **Base:** `7a868c02`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Architecture:** [sim-03-internal-character-motor-metadata](../architecture/sim-03-internal-character-motor-metadata.md). **Contract:** [sim-03-governance-v0](../contracts/sim-03-governance-v0.md). **Planning policy:** [ADR-0033](../adr/0033-sim-03-authoritative-character-motor-policy.md) `PROPOSED`.

## OBJECTIVE

Record the owner-approved bounded internal governance for SIM-03 logical character motor metadata.

## CONTEXT

SIM-03 follows the completed internal sequences of SIM-01 and SIM-02. No character motor, contact-gated movement, input layer or camera runtime exists.

## SCOPE

- ADR-0134, internal architecture, governance contract and this WO.
- G6 activation evidence, activation JSON, checkpoint and manifest/validator bookkeeping.

## OUT OF SCOPE

All code: `src/stormline/character/**`, tests, CMake, workflows. Motor/sweeper, contact execution, solver/backend, input devices, camera update, animation root motion, ECS mutation, GPU, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0033, module catalog, SIM-03 plan, SIM-01 and SIM-02 evidence.

## REQUIREMENTS

GOV-001..007 of the governance contract; ADR-0134; oracles CTRL-01, LOCO-01, INPUT-01, CAM-01 and QLF-S301..S304.

## ARCHITECTURE RULES

SIM-03 owns logical character motor intent metadata only; no motor handle, backend type, pointer or runtime behavior may cross the boundary.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no motor/sweeper/contact/input/camera/runtime/ECS/GPU; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents and activation are exact and internally consistent.
- No code, CMake or workflow change.
- Manifest root `SIM03_01_APPROVED_GOVERNANCE_ONLY`; `SIM-03-02` remains `PLANNED_BLOCKED`.
- pt-BR audit `APPROVED`.

## TESTS

Validator and documentation checks only; no executable test is authorized by this packet.

## DELIVERABLES

ADR, architecture, governance contract, WO, G6 evidence, activation JSON and validator updates.

## REVIEW FORMAT

pt-BR: base/head, files, manifest counts, security/rollback, no overclaim.

## STOP CONDITION

Stale base, missing owner authority, runtime/motor claim, allowlist violation, failed validator, HIGH/CRITICAL.

## CONTEXT LOCK

Base `7a868c02`; governance contract and ADR blobs pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-03-01-G6-ACTIVATION.md`.
