# NLE-PRPLAN-GFX-02-01 — Logical shader pipeline governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation only.** **Formal packet:** `NLE-PRPLAN-GFX-02-01`. **Predecessor:** GFX-01 and DATA-03 internal sequences. **Issue:** #30. **Base:** `a4c37e3`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-governance-v0](../contracts/gfx-02-governance-v0.md).

## OBJECTIVE

Ratify a bounded internal GFX-02 direction: logical SSCL-0 shader pipeline with no native compiler, external dependency, GPU artifact, driver, renderer, ABI or release.

## CONTEXT

GFX-01 and DATA-03 completed internal sequences as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0015 defers native compiler selection and hardware proof. GFX-02 implementation is blocked.

## SCOPE

- ADR-0116, internal pipeline architecture, governance contract, this WO and G6 evidence.
- Manifest/validator/test/checkpoint updates for governance state only.

## OUT OF SCOPE

Contract -02, all implementation, native shaders/compilers/GPU, material/PBR, renderer, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0015/0086, GFX-02 architecture/API/matrix, GFX-01 closeout, DATA-03 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0116; no native compiler/GPU.

## ARCHITECTURE RULES

GFX-02 owns logical SSCL-0 pipeline; DATA-02/03 and GFX-01 retain their boundaries; no native compiler or GPU.

## CONSTRAINTS

Risk `LOW` documentation / `ELEVATED` implementation; `INTERNAL_ONLY`; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents exact; manifest root `GFX02_01_APPROVED_GOVERNANCE_ONLY`.
- No code, dependency, native compiler/GPU or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; no executable shader test in this packet.

## DELIVERABLES

ADR-0116, architecture, governance contract, WO, G6 evidence, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, governance boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native compiler/GPU selection, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `a4c37e3`; GFX-01 closeout `a4c37e3`; DATA-03 closeout `a26e463`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-02-01-G6-ACTIVATION.md`.
