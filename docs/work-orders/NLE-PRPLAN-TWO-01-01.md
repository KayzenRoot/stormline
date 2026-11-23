# NLE-PRPLAN-TWO-01-01 — Internal 2D canvas governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation only.** **Formal packet:** `NLE-PRPLAN-TWO-01-01`. **Predecessor:** GFX-08 internal sequence. **Issue:** #37. **Base:** `74e7256`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **Contract:** [two-01-governance-v0](../contracts/two-01-governance-v0.md).

## OBJECTIVE

Ratify a bounded internal TWO-01 direction: logical sprite, atlas, layer, orthographic camera, pixel-snapping and 2D light-request metadata, with no GPU renderer, atlas upload, text/vector engine, lighting, renderer, ABI or release.

## CONTEXT

GFX-08 completed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0022 remains planning-only. TWO-01 implementation is blocked.

## SCOPE

- ADR-0123, internal architecture, governance contract, WO and G6 evidence.
- Manifest/validator/test/checkpoint updates for governance state only.

## OUT OF SCOPE

Contract -02, all implementation, native GPU, sprite/atlas draw, text/vector/font engine, 2D lighting, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0022/0086, TWO-01 architecture/API, GFX-08 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0123; no native GPU/render/text/vector/SDK.

## ARCHITECTURE RULES

TWO-01 owns logical canvas plans; GFX-01/02/03/05/06/07 and DATA boundaries unchanged; no backend, sprite instance or visual resource.

## CONSTRAINTS

Risk `LOW` documentation / `ELEVATED` implementation; `INTERNAL_ONLY`; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents exact; manifest root `TWO01_01_APPROVED_GOVERNANCE_ONLY`.
- No code, dependency, native GPU/render/text/SDK or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; no executable canvas test in this packet.

## DELIVERABLES

ADR-0123, architecture, governance contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, governance boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/render/text/vector/SDK selection, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `74e7256`; GFX-08 closeout `74e7256`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-01-01-G6-ACTIVATION.md`.
