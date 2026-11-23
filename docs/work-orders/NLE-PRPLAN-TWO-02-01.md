# NLE-PRPLAN-TWO-02-01 — Internal tilemap governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation only.** **Formal packet:** `NLE-PRPLAN-TWO-02-01`. **Predecessor:** TWO-01 internal sequence. **Issue:** #38. **Base:** `035a3f9`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **Contract:** [two-02-governance-v0](../contracts/two-02-governance-v0.md).

## OBJECTIVE

Ratify a bounded internal TWO-02 direction: signed grid/chunk math, tile cells, collision-authoring metadata, parallax and streaming plans, with no tile renderer, persistence, chunk I/O, collision solver, physics, ABI or release.

## CONTEXT

TWO-01 completed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0023 remains planning-only. TWO-02 implementation is blocked.

## SCOPE

- ADR-0124, internal architecture, governance contract, WO and G6 evidence.
- Manifest/validator/test/checkpoint updates for governance state only.

## OUT OF SCOPE

Contract -02, all implementation, renderer/GPU, importer, persistence, chunk codec, streaming I/O, physics, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0023/0086, TWO-02 architecture/API, TWO-01 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0124; no native GPU/render/import/physics.

## ARCHITECTURE RULES

TWO-02 owns logical tilemap plans; TWO-01, DATA-04/05, GFX and PHYS boundaries unchanged; no backend, chunk file or collision solver.

## CONSTRAINTS

Risk `LOW` documentation / `ELEVATED` implementation; `INTERNAL_ONLY`; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents exact; manifest root `TWO02_01_APPROVED_GOVERNANCE_ONLY`.
- No code, dependency, renderer/importer/physics or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; no executable tilemap test in this packet.

## DELIVERABLES

ADR-0124, architecture, governance contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, governance boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, renderer/importer/physics/streaming I/O selection, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `035a3f9`; TWO-01 closeout `035a3f9`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-02-01-G6-ACTIVATION.md`.
