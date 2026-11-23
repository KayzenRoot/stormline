# NLE-PRPLAN-TWO-01-02 — Canvas internal contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no code authorized.** **Formal packet:** `NLE-PRPLAN-TWO-01-02`. **Predecessor:** `TWO-01-01` governance. **Issue:** #37. **Base:** `40020ae`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md).

## OBJECTIVE

Freeze the exact internal TWO-01 API, capacities, validation rules, deterministic ordering, errors and per-slice allowlists for sprites, atlases, layers, camera, pixel snapping and 2D lights.

## CONTEXT

TWO-01-01 approved ADR-0123. No GPU renderer, sprite draw, atlas upload, text/vector/font engine, lighting, dependency, ABI or release is authorized.

## SCOPE

- `docs/contracts/two-01-canvas-internal-v0.md`.
- WO, G6 evidence, activation JSON, manifest/validator/test/checkpoint updates.

## OUT OF SCOPE

Implementation `-03`..`-09`, closeout, native GPU, render, text/vector engine, lighting, assets, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0022/0086/0123, TWO-01 architecture/API, governance contract, GFX-08 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0123; exact API and SPR/ATL/LAY/CAM/SNP/LGT/QLF-T1 oracles.

## ARCHITECTURE RULES

TWO-01 owns logical canvas plans only; GFX-01/02/03/05/06/07 and DATA boundaries unchanged; no backend/sprite instance/visual resource.

## CONSTRAINTS

Risk `LOW` contract; `INTERNAL_ONLY`; no GPU/render/text/vector/SDK/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract exact and complete; manifest root `TWO01_02_APPROVED_CONTRACT_ONLY`.
- No code, dependency, native GPU/render/text/SDK or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; future oracles are declared but not executed.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/render/text/vector/SDK selection, incomplete API, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `40020ae`; governance merge `40020ae`; contract blob pinned after this gate.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-01-02-G6-ACTIVATION.md`.
