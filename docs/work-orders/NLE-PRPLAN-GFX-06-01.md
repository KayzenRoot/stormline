# NLE-PRPLAN-GFX-06-01 — Logical lighting governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation only.** **Formal packet:** `NLE-PRPLAN-GFX-06-01`. **Predecessor:** GFX-03 and GFX-05 internal sequences. **Issue:** #34. **Base:** `de396b2`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-governance-v0](../contracts/gfx-06-governance-v0.md).

## OBJECTIVE

Ratify a bounded internal GFX-06 direction: logical light validation, shadow split/page plans, GI/probe/reflection fallback metadata and volumetric budgets, with no native GPU/shadow map/ray tracing/GI bake/renderer/ABI/release.

## CONTEXT

GFX-03 and GFX-05 completed internal sequences as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0019 remains planning-only. GFX-06 implementation is blocked.

## SCOPE

- ADR-0120, internal architecture, governance contract, WO and G6 evidence.
- Manifest/validator/test/checkpoint updates for governance state only.

## OUT OF SCOPE

Contract -02, all implementation, native GPU/API, shadow map, ray tracing, GI/probe bake, SSR, volumetric buffer, rendering, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0019/0086, GFX-06 architecture/API, GFX-03 and GFX-05 closeouts.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0120; no native GPU/shadow/ray-tracing.

## ARCHITECTURE RULES

GFX-06 owns logical lighting plans; GFX/GFX-03/04/05/07 and DATA boundaries unchanged; no backend or visual resource.

## CONSTRAINTS

Risk `LOW` documentation / `ELEVATED` implementation; `INTERNAL_ONLY`; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents exact; manifest root `GFX06_01_APPROVED_GOVERNANCE_ONLY`.
- No code, dependency, native GPU/shadow/ray-tracing or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; no executable lighting test in this packet.

## DELIVERABLES

ADR-0120, architecture, governance contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, governance boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/shadow/ray-tracing selection, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `de396b2`; GFX-05 closeout `de396b2`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-06-01-G6-ACTIVATION.md`.
