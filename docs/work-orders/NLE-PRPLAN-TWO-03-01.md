# NLE-PRPLAN-TWO-03-01 — Internal animation governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation only.** **Formal packet:** `NLE-PRPLAN-TWO-03-01`. **Predecessor:** TWO-02 internal sequence. **Issue:** #39. **Base:** `f093ce5`. **ADR:** [ADR-0125](../adr/0125-two-03-internal-animation-pipeline.md). **Contract:** [two-03-governance-v0](../contracts/two-03-governance-v0.md).

## OBJECTIVE

Ratify a bounded internal TWO-03 direction: flipbook frame metadata, 2D bone hierarchy, blending, cutscene tracks/cues and rational timeline plans, with no runtime, audio, export, renderer, ABI or release.

## CONTEXT

TWO-02 completed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0024 remains planning-only. TWO-03 implementation is blocked.

## SCOPE

- ADR-0125, internal architecture, governance contract, WO and G6 evidence.
- Manifest/validator/test/checkpoint updates for governance state only.

## OUT OF SCOPE

Contract -02, all implementation, runtime/pose/skinning, audio, export/codec, importer, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0024/0086, TWO-03 architecture/API, TWO-02 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0125; no runtime/audio/export.

## ARCHITECTURE RULES

TWO-03 owns logical animation plans; TWO-01, DATA, AUDIO, GFX and WORLD boundaries unchanged; no runtime, audio device or encoder.

## CONSTRAINTS

Risk `LOW` documentation / `ELEVATED` implementation; `INTERNAL_ONLY`; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents exact; manifest root `TWO03_01_APPROVED_GOVERNANCE_ONLY`.
- No code, dependency, runtime/audio/export or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; no executable animation test in this packet.

## DELIVERABLES

ADR-0125, architecture, governance contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, governance boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, runtime/audio/export/importer selection, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `f093ce5`; TWO-02 closeout `f093ce5`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-03-01-G6-ACTIVATION.md`.
