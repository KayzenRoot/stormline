# NLE-PRPLAN-GFX-06-02 — Logical lighting contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no code authorized.** **Formal packet:** `NLE-PRPLAN-GFX-06-02`. **Predecessor:** `GFX-06-01` governance. **Issue:** #34. **Base:** `533d983`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md).

## OBJECTIVE

Freeze the exact internal GFX-06 API, capacities, validation rules, deterministic ordering, fallback behavior, errors and per-slice allowlists for lights, shadows, GI, probes, reflections and volumetrics.

## CONTEXT

GFX-06-01 approved ADR-0120. GFX-03 and GFX-05 completed internal sequences. No native GPU, shadow map, ray tracing, GI/probe bake, SSR, volumetric renderer, dependency, ABI or release is authorized.

## SCOPE

- `docs/contracts/gfx-06-lighting-internal-v0.md`.
- WO, G6 evidence, activation JSON, manifest/validator/test/checkpoint updates.

## OUT OF SCOPE

Implementation `-03`..`-09`, closeout, native GPU/API, shadow map, ray tracing, GI/probe bake, SSR, froxel buffer, merging, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0019/0086/0120, GFX-06 architecture/API, GFX-06 governance contract, GFX-03 and GFX-05 closeouts.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0120; exact API and LGT/SHD/GI/PRB/REF/VOL/QLF-G6 oracles.

## ARCHITECTURE RULES

GFX-06 owns logical lighting plans only; GFX-03/04/05/07 and DATA boundaries unchanged; no native GPU/shadow/ray-tracing resource.

## CONSTRAINTS

Risk `LOW` contract; `INTERNAL_ONLY`; no GPU/shadow/ray-tracing/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract exact and complete; manifest root `GFX06_02_APPROVED_CONTRACT_ONLY`.
- No code, dependency, native GPU/shadow/ray-tracing or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; future oracles are declared but not executed in this packet.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/shadow/ray-tracing selection, incomplete API, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `533d983`; governance merge `533d983`; contract blob pinned after this gate.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-06-02-G6-ACTIVATION.md`.
