# NLE-PRPLAN-GFX-08-01 — Internal VFX graph governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation only.** **Formal packet:** `NLE-PRPLAN-GFX-08-01`. **Predecessor:** GFX-07 internal sequence. **Issue:** #36. **Base:** `eb81362`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-governance-v0](../contracts/gfx-08-governance-v0.md).

## OBJECTIVE

Ratify a bounded internal GFX-08 direction: logical VFX graph shape, particle emitter/spawn budgets, ribbon and trail geometry budgets, transparency/blend policy, volumetric density-stamp metadata and pooling/quality budgets, with no CPU/GPU simulation, compute, sorting, OIT, volumetric rendering, shader, renderer, ABI or release.

## CONTEXT

GFX-07 completed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0021 remains planning-only. GFX-08 implementation is blocked.

## SCOPE

- ADR-0122, internal architecture, governance contract, WO and G6 evidence.
- Manifest/validator/test/checkpoint updates for governance state only.

## OUT OF SCOPE

Contract -02, all implementation, native GPU/compute, particle simulation, sorting/OIT, volumetric renderer, shader compiler, SDK, assets, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0021/0086, GFX-08 architecture/API, GFX-07 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0122; no native GPU/compute/sort/SDK.

## ARCHITECTURE RULES

GFX-08 owns logical VFX plans; GFX-01/02/03/04/05/06/07 and DATA boundaries unchanged; no backend, particle state or visual resource.

## CONSTRAINTS

Risk `LOW` documentation / `ELEVATED` implementation; `INTERNAL_ONLY`; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents exact; manifest root `GFX08_01_APPROVED_GOVERNANCE_ONLY`.
- No code, dependency, native GPU/compute/sort/SDK or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; no executable VFX test in this packet.

## DELIVERABLES

ADR-0122, architecture, governance contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, governance boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/compute/sort/SDK selection, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `eb81362`; GFX-07 closeout `eb81362`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-08-01-G6-ACTIVATION.md`.
