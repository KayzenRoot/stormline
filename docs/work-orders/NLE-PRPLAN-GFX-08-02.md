# NLE-PRPLAN-GFX-08-02 — VFX internal contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no code authorized.** **Formal packet:** `NLE-PRPLAN-GFX-08-02`. **Predecessor:** `GFX-08-01` governance. **Issue:** #36. **Base:** `65d3f7b`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md).

## OBJECTIVE

Freeze the exact internal GFX-08 API, capacities, validation rules, deterministic fallbacks, errors and per-slice allowlists for graph validation, emitter/spawn, ribbons, trails, transparency, density stamps and pooling.

## CONTEXT

GFX-08-01 approved ADR-0122. No CPU/GPU simulation, compute, sorting, OIT, volumetric renderer, shader, SDK, dependency, ABI or release is authorized.

## SCOPE

- `docs/contracts/gfx-08-vfx-internal-v0.md`.
- WO, G6 evidence, activation JSON, manifest/validator/test/checkpoint updates.

## OUT OF SCOPE

Implementation `-03`..`-09`, closeout, native GPU/compute, particle simulation, sorting/OIT, volumetric rendering, assets, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0021/0086/0122, GFX-08 architecture/API, governance contract, GFX-07 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0122; exact API and VFX/SPAWN/RIB/TRL/BLD/DEN/POOL/QLF-G8 oracles.

## ARCHITECTURE RULES

GFX-08 owns logical VFX plans only; GFX-01/02/03/04/05/06/07 and DATA boundaries unchanged; no backend/particle state/visual resource.

## CONSTRAINTS

Risk `LOW` contract; `INTERNAL_ONLY`; no GPU/compute/sort/OIT/SDK/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract exact and complete; manifest root `GFX08_02_APPROVED_CONTRACT_ONLY`.
- No code, dependency, native GPU/compute/sort/SDK or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; future oracles are declared but not executed in this packet.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/compute/sort/SDK selection, incomplete API, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `65d3f7b`; governance merge `65d3f7b`; contract blob pinned after this gate.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-08-02-G6-ACTIVATION.md`.
