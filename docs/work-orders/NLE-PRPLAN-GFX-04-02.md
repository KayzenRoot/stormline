# NLE-PRPLAN-GFX-04-02 — Logical geometry pipeline contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no code authorized.** **Formal packet:** `NLE-PRPLAN-GFX-04-02`. **Predecessor:** `GFX-04-01` governance. **Issue:** #32. **Base:** `35d6b31`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md).

## OBJECTIVE

Freeze the exact internal GFX-04 API, capacities, conservative rules, errors and per-slice allowlists for logical geometry visibility/detail planning.

## CONTEXT

GFX-04-01 approved ADR-0118. No native GPU, mesh library, submission, renderer, dependency, ABI or release is authorized.

## SCOPE

- `docs/contracts/gfx-04-geometry-internal-v0.md`.
- WO, G6 evidence, activation JSON, manifest/validator/test/checkpoint updates.

## OUT OF SCOPE

Implementation `-03`..`-09`, closeout, native GPU/mesh library, submission, rendering, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0017/0118/0086, GFX-04 architecture/API/matrix, GFX-04 governance contract, GFX-03/DATA-05 closeouts.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0118; exact API and INS/CUL/LOD/STR/VEG/GEO/QLF-G4 oracles.

## ARCHITECTURE RULES

GFX-04 owns logical geometry visibility; no native GPU/mesh library; GFX/CORE/DATA boundaries unchanged.

## CONSTRAINTS

Risk `LOW` contract; `INTERNAL_ONLY`; no GPU/mesh codec/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract exact and complete; manifest root `GFX04_02_APPROVED_CONTRACT_ONLY`.
- No code, dependency, native GPU/mesh library or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; future oracles are declared but not executed in this packet.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/mesh library selection, incomplete API, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `35d6b31`; governance merge `35d6b31`; contract blob pinned after this gate.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-04-02-G6-ACTIVATION.md`.
