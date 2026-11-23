# NLE-PRPLAN-GFX-03-01 — Logical render graph governance (INTERNAL_ONLY)

**STATUS: G6 GOVERNANCE PACKET — documentation only.** **Formal packet:** `NLE-PRPLAN-GFX-03-01`. **Predecessor:** GFX-01 and CORE-03 internal sequences. **Issue:** #31. **Base:** `4abac08`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-governance-v0](../contracts/gfx-03-governance-v0.md).

## OBJECTIVE

Ratify a bounded internal GFX-03 direction: logical pass/resource graph compilation, hazards, sync transitions, transient alias planning and VRAM admission, with no native GPU, allocator, submission, renderer, ABI or release.

## CONTEXT

GFX-01/02 and CORE-03 completed internal sequences as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. ADR-0016 defers native backend and hardware proof. GFX-03 implementation is blocked.

## SCOPE

- ADR-0117, internal architecture, governance contract, WO and G6 evidence.
- Manifest/validator/test/checkpoint updates for governance state only.

## OUT OF SCOPE

Contract -02, all implementation, native GPU/allocator/API, submission, rendering, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0016/0086, GFX-03 architecture/API/matrix, GFX-01/02 closeouts, CORE-03 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0117; no native GPU/submission.

## ARCHITECTURE RULES

GFX-03 owns logical graph planning; GFX-01/02, CORE and DATA boundaries unchanged; no native allocator.

## CONSTRAINTS

Risk `LOW` documentation / `ELEVATED` implementation; `INTERNAL_ONLY`; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Governance documents exact; manifest root `GFX03_01_APPROVED_GOVERNANCE_ONLY`.
- No code, dependency, native GPU/allocator or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; no executable graph test in this packet.

## DELIVERABLES

ADR-0117, architecture, governance contract, WO, G6 evidence, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, governance boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/allocator selection, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `4abac08`; GFX-02 closeout `4abac08`; CORE-03 closeout `518` line history.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-03-01-G6-ACTIVATION.md`.
