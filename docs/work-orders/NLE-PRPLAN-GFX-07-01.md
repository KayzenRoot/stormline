# NLE-PRPLAN-GFX-07-01 — Internal camera/color/post governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation only.** **Formal packet:** `NLE-PRPLAN-GFX-07-01`. **Predecessor:** GFX-06 internal sequence. **Issue:** #35. **Base:** `a2a0154`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-governance-v0](../contracts/gfx-07-governance-v0.md).

## OBJECTIVE

Ratify a bounded internal GFX-07 direction: logical camera/projection/exposure, tone/color and SDR/HDR output planning, reconstruction/AA strategy, optional motion blur and render-scale/upscale metadata, with no native GPU/display/SDK/renderer/ABI/release.

## CONTEXT

GFX-06 completed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0020 remains planning-only. GFX-07 implementation is blocked.

## SCOPE

- ADR-0121, internal architecture, governance contract, WO and G6 evidence.
- Manifest/validator/test/checkpoint updates for governance state only.

## OUT OF SCOPE

Contract -02, all implementation, native GPU/API, swapchain/HDR, tone mapper, LUT/OCIO, TAA, vendor SDK, rendering, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0020/0086, GFX-07 architecture/API, GFX-06 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0121; no native GPU/display/SDK.

## ARCHITECTURE RULES

GFX-07 owns logical post plans; GFX-01/02/03/04/05/06 and DATA boundaries unchanged; no backend or visual resource.

## CONSTRAINTS

Risk `LOW` documentation / `ELEVATED` implementation; `INTERNAL_ONLY`; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents exact; manifest root `GFX07_01_APPROVED_GOVERNANCE_ONLY`.
- No code, dependency, native GPU/display/SDK or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; no executable post-processing test in this packet.

## DELIVERABLES

ADR-0121, architecture, governance contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, governance boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/display/SDK selection, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `a2a0154`; GFX-06 closeout `a2a0154`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-07-01-G6-ACTIVATION.md`.
