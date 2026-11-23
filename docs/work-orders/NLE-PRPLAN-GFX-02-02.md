# NLE-PRPLAN-GFX-02-02 — Logical shader pipeline contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no code authorized.** **Formal packet:** `NLE-PRPLAN-GFX-02-02`. **Predecessor:** `GFX-02-01` governance. **Issue:** #30. **Base:** `c1f0b89`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md).

## OBJECTIVE

Freeze the exact internal GFX-02 API, semantics, capacities, errors, deterministic rules and per-slice allowlists for the SSCL-0 logical shader pipeline.

## CONTEXT

GFX-02-01 approved ADR-0116 and the internal-only direction. No native compiler, GPU artifact, driver, renderer, dependency, ABI or release is authorized.

## SCOPE

- `docs/contracts/gfx-02-shader-internal-v0.md`.
- WO, G6 evidence, activation JSON, manifest/validator/test/checkpoint updates.

## OUT OF SCOPE

Implementation `-03`..`-08`, closeout, native compiler/GPU, material/PBR, renderer, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0015/0116/0086, GFX-02 architecture/API/matrix, GFX-02 governance contract, GFX-01 and DATA-03 closeouts.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0116; exact SSCL-0 API and oracles PAR/REF/VAR/CAC/INC/QLF-S.

## ARCHITECTURE RULES

GFX-02 owns logical shader pipeline; no native compiler or GPU; DATA/GFX boundaries unchanged.

## CONSTRAINTS

Risk `LOW` contract; `INTERNAL_ONLY`; no compiler/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract exact and complete; manifest root `GFX02_02_APPROVED_CONTRACT_ONLY`.
- No code, dependency, native compiler/GPU or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; future oracles are declared but not executed in this packet.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native compiler/GPU selection, incomplete API, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `c1f0b89`; governance merge `c1f0b89`; contract blob to be pinned after this gate.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-02-02-G6-ACTIVATION.md`.
