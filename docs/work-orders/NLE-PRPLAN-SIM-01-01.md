# NLE-PRPLAN-SIM-01-01 — Physics 2D governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-01-01`. **Predecessor:** WORLD-01 and TWO-01 internal sequences completed. **Issue:** #46. **Base:** `bd9c366`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Governance contract:** [sim-01-governance-v0](../contracts/sim-01-governance-v0.md).

## OBJECTIVE

Approve a bounded internal SIM-01 sequence for logical 2D physics metadata only, with explicit ownership, risk, release class and later slice gates.

## CONTEXT

WORLD-01 and TWO-01 completed their internal sequences as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0031 remains `PROPOSED`; no solver, backend, simulation, query or event system exists.

## SCOPE

- ADR-0132, internal architecture and governance contract.
- WO, G6 evidence, activation JSON, checkpoint line and manifest/validator wiring.
- No code.

## OUT OF SCOPE

SIM-01-02 contract and all implementation slices; solver/backend, simulation, collision, queries, joints, triggers, masks, ECS mutation, tilemap bridge, GPU, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0031, SIM-01 architecture/API/plan, ADR-0086, WORLD-01 and TWO-01 evidence.

## REQUIREMENTS

GOV-001..007; ADR-0132; BODY-01, COL-01, QRY-01, JNT-01, TRG-01, MSK-01, QLF-S101..S104 definitions.

## ARCHITECTURE RULES

SIM-01 owns only logical 2D physics intent metadata; simulation, entities, canvas, streaming, assets and runtime authority stay with their owners.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; ADR-0031 remains PROPOSED; no engine code, solver/backend, simulation, GPU, asset I/O, physics/network runtime, editor, performance, ABI or release. CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

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

Stale base, missing owner authorization, ADR-0031 rewrite, scope expansion to runtime, allowlist violation, validator failure, HIGH/CRITICAL or release/ABI claim.

## CONTEXT LOCK

Base `bd9c366`; ADR-0132 and governance contract blobs pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-01-01-G6-ACTIVATION.md`.
