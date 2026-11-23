# NLE-PRPLAN-GFX-05-01 — Logical material/texture governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation only.** **Formal packet:** `NLE-PRPLAN-GFX-05-01`. **Predecessor:** GFX-02 and DATA-03 internal sequences. **Issue:** #33. **Base:** `eafb62a`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-governance-v0](../contracts/gfx-05-governance-v0.md).

## OBJECTIVE

Ratify a bounded internal GFX-05 direction: logical PBR/material parameters, texture/mip metadata, virtual-page requests, samplers, decals and transparency budgets, with no native GPU/codec/submission/renderer/ABI/release.

## CONTEXT

GFX-02 and DATA-03 completed internal sequences as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0018 defers codec/backend/hardware proof. GFX-05 implementation is blocked.

## SCOPE

- ADR-0119, internal architecture, governance contract, WO and G6 evidence.
- Manifest/validator/test/checkpoint updates for governance state only.

## OUT OF SCOPE

Contract -02, all implementation, native GPU/codec/API, submission, rendering, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0018/0086, GFX-05 architecture/API/matrix, GFX-02 and DATA-03 closeouts.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0119; no native GPU/codec/submission.

## ARCHITECTURE RULES

GFX-05 owns logical material/texture semantics; GFX-02/DATA/CORE boundaries unchanged; no native codec.

## CONSTRAINTS

Risk `LOW` documentation / `ELEVATED` implementation; `INTERNAL_ONLY`; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents exact; manifest root `GFX05_01_APPROVED_GOVERNANCE_ONLY`.
- No code, dependency, native GPU/codec or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; no executable material/texture test in this packet.

## DELIVERABLES

ADR-0119, architecture, governance contract, WO, G6 evidence, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, governance boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/codec selection, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `eafb62a`; GFX-04 closeout `eafb62a`; DATA-03 closeout `a26e463`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-05-01-G6-ACTIVATION.md`.
