# NLE-PRPLAN-WORLD-05-01 — Procedural generation governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-05-01`. **Predecessor:** WORLD-04 and DATA-03 internal sequences completed. **Issue:** #45. **Base:** `479123b`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Governance contract:** [world-05-governance-v0](../contracts/world-05-governance-v0.md).

## OBJECTIVE

Approve a bounded internal WORLD-05 sequence for logical procedural-generation metadata only, with explicit ownership, risk, release class and later slice gates.

## CONTEXT

WORLD-04 and DATA-03 completed their internal sequences as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0030 remains `PROPOSED`; no generator, graph evaluator, noise, WFC, asset I/O or artifact producer exists.

## SCOPE

- ADR-0131, internal architecture and governance contract.
- WO, G6 evidence, activation JSON, checkpoint line and manifest/validator wiring.
- No code.

## OUT OF SCOPE

WORLD-05-02 contract and all implementation slices; graph evaluation, RNG/noise, WFC, asset import, cook/cache, scene/source writes, mesh generation, GPU preview, editor, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0030, WORLD-05 architecture/API/plan, ADR-0086, WORLD-04 and DATA-03 evidence.

## REQUIREMENTS

GOV-001..007; ADR-0131; SEED-01, GRAPH-01, RULE-01, BIOME-01, GEO-01, GEN-01, QLF-W501..W504 definitions.

## ARCHITECTURE RULES

WORLD-05 owns only logical generation intent metadata; evaluation, assets, persistence, streaming, rendering and authority stay with their owners.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; ADR-0030 remains PROPOSED; no engine code, evaluation, GPU, asset I/O, physics/network, editor, performance, ABI or release. CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

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

Stale base, missing owner authorization, ADR-0030 rewrite, scope expansion to runtime, allowlist violation, validator failure, HIGH/CRITICAL or release/ABI claim.

## CONTEXT LOCK

Base `479123b`; ADR-0131 and governance contract blobs pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-05-01-G6-ACTIVATION.md`.
