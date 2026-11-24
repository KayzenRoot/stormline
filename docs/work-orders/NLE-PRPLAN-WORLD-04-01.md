# NLE-PRPLAN-WORLD-04-01 — Terrain & Environment governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-04-01`. **Predecessor:** WORLD-03 and GFX-04 internal sequences completed. **Issue:** #44. **Base:** `7f7e153`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Governance contract:** [world-04-governance-v0](../contracts/world-04-governance-v0.md).

## OBJECTIVE

Approve a bounded internal WORLD-04 sequence for logical terrain/environment metadata only, with explicit ownership, risk, release class and later slice gates.

## CONTEXT

WORLD-03 and GFX-04 completed their internal sequences as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0029 remains `PROPOSED`; no terrain runtime, heightfield storage, renderer, simulation or benchmark exists.

## SCOPE

- ADR-0130, internal architecture and governance contract.
- WO, G6 evidence, activation JSON, checkpoint line and manifest/validator wiring.
- No code.

## OUT OF SCOPE

WORLD-04-02 contract and all implementation slices; heightfield/mesh storage, terrain/water rendering, GPU LOD, texture residency, vegetation instancing, atmosphere/weather simulation, physics, networking, editor, GPU, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0029, WORLD-04 architecture/API/plan, ADR-0086, WORLD-03 and GFX-04 evidence.

## REQUIREMENTS

GOV-001..007; ADR-0130; TER-01, SPL-01, VEG-01, WAT-01, SKY-01, CLI-01, QLF-W401..W404 definitions.

## ARCHITECTURE RULES

WORLD-04 owns only authored terrain/environment intent metadata; all runtime rendering, storage, simulation, collision and authority stay with their owners.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; ADR-0029 remains PROPOSED; no engine code, heightfield storage, renderer, GPU, physics/network, editor, performance, ABI or release. CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact documentation allowlist; no code.
- Governance contract freezes invariants, oracles and slice gates.
- Validators pass; pt-BR audit `APPROVED`.

## TESTS

Validator suite, docs validation and manifest counts only; no engine tests are introduced by this packet.

## DELIVERABLES

ADR, architecture, governance contract, WO, evidence, activation JSON, checkpoint and validator wiring, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, governance invariants, validators/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, missing owner authorization, ADR-0029 rewrite, scope expansion to runtime, allowlist violation, validator failure, HIGH/CRITICAL or release/ABI claim.

## CONTEXT LOCK

Base `7f7e153`; ADR-0130 and governance contract blobs pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-04-01-G6-ACTIVATION.md`.
