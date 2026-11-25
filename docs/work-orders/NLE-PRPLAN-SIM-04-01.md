# NLE-PRPLAN-SIM-04-01 — Internal skeletal animation metadata governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — no implementation authorized by this WO.** **Formal packet:** `NLE-PRPLAN-SIM-04-01`. **Issue:** #49. **Base:** `ebd5d0b7`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Architecture:** [sim-04-internal-skeletal-animation-metadata](../architecture/sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-governance-v0](../contracts/sim-04-governance-v0.md). **Planning policy:** [ADR-0034](../adr/0034-sim-04-animation-authority-retarget-ik-and-ragdoll.md) `PROPOSED`.

## OBJECTIVE

Record the owner-approved bounded internal governance for SIM-04 logical skeletal animation metadata.

## CONTEXT

SIM-04 follows the completed internal sequences of SIM-03 and DATA-03. No pose evaluator, graph runtime, IK solver, ragdoll activation, codec or sync runtime exists.

## SCOPE

- ADR-0135, internal architecture, governance contract and this WO.
- G6 activation evidence, activation JSON, checkpoint and manifest/validator bookkeeping.

## OUT OF SCOPE

All code: `src/stormline/animation/**`, tests, CMake, workflows. Pose evaluation, blend/IK execution, ragdoll runtime, codecs, root-motion application, ECS mutation, GPU, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0034, module catalog, SIM-04 plan, SIM-03 and DATA-03 evidence.

## REQUIREMENTS

GOV-001..007 of the governance contract; ADR-0135; oracles RET-01, BLEND-01, IK-01, RAG-01, CMP-01, SYNC-01 and QLF-S401..S404.

## ARCHITECTURE RULES

SIM-04 owns logical animation intent metadata only; no runtime handle, backend type, pointer or runtime behavior may cross the boundary.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no pose/solver/codec/ragdoll/root-motion/ECS/GPU; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents and activation are exact and internally consistent.
- No code, CMake or workflow change.
- Manifest root `SIM04_01_APPROVED_GOVERNANCE_ONLY`; `SIM-04-02` remains `PLANNED_BLOCKED`.
- pt-BR audit `APPROVED`.

## TESTS

Validator and documentation checks only; no executable test is authorized by this packet.

## DELIVERABLES

ADR, architecture, governance contract, WO, G6 evidence, activation JSON and validator updates.

## REVIEW FORMAT

pt-BR: base/head, files, manifest counts, security/rollback, no overclaim.

## STOP CONDITION

Stale base, missing owner authority, runtime/animation claim, allowlist violation, failed validator, HIGH/CRITICAL.

## CONTEXT LOCK

Base `ebd5d0b7`; governance contract and ADR blobs pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-04-01-G6-ACTIVATION.md`.
