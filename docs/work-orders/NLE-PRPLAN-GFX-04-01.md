# NLE-PRPLAN-GFX-04-01 — Logical geometry pipeline governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation only.** **Formal packet:** `NLE-PRPLAN-GFX-04-01`. **Predecessor:** GFX-03 and DATA-05 internal sequences. **Issue:** #32. **Base:** `07c8a92`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md). **Contract:** [gfx-04-governance-v0](../contracts/gfx-04-governance-v0.md).

## OBJECTIVE

Ratify a bounded internal GFX-04 direction: logical instancing, conservative culling, LOD/HLOD, verified-chunk stream planning, vegetation classification and geometry budget validation, with no native GPU, mesh library, submission, renderer, ABI or release.

## CONTEXT

GFX-03 and DATA-05 completed internal sequences as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0017 defers native backend/library/hardware proof. GFX-04 implementation is blocked.

## SCOPE

- ADR-0118, internal architecture, governance contract, WO and G6 evidence.
- Manifest/validator/test/checkpoint updates for governance state only.

## OUT OF SCOPE

Contract -02, all implementation, native GPU/mesh library/API, submission, rendering, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0017/0086, GFX-04 architecture/API/matrix, GFX-03 and DATA-05 closeouts.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0118; no native GPU/mesh library/submission.

## ARCHITECTURE RULES

GFX-04 owns logical geometry visibility; GFX-03/DATA/CORE boundaries unchanged; no native mesh codec.

## CONSTRAINTS

Risk `LOW` documentation / `ELEVATED` implementation; `INTERNAL_ONLY`; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents exact; manifest root `GFX04_01_APPROVED_GOVERNANCE_ONLY`.
- No code, dependency, native GPU/mesh library or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; no executable geometry test in this packet.

## DELIVERABLES

ADR-0118, architecture, governance contract, WO, G6 evidence, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, governance boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/mesh library selection, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `07c8a92`; GFX-03 closeout `07c8a92`; DATA-05 closeout `c87e9f7`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-04-01-G6-ACTIVATION.md`.
