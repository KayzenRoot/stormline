# NLE-PRPLAN-TWO-02-02 — Tilemap internal contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no code authorized.** **Formal packet:** `NLE-PRPLAN-TWO-02-02`. **Predecessor:** `TWO-02-01` governance. **Issue:** #38. **Base:** `fa7f2bd`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md).

## OBJECTIVE

Freeze the exact internal TWO-02 API, capacities, signed coordinate rules, deterministic fallbacks, errors and per-slice allowlists for grid, tiles, collision authoring, parallax and streaming.

## CONTEXT

TWO-02-01 approved ADR-0124. No renderer, importer, persistence, chunk I/O, collision solver, physics, dependency, ABI or release is authorized.

## SCOPE

- `docs/contracts/two-02-tilemap-internal-v0.md`.
- WO, G6 evidence, activation JSON, manifest/validator/test/checkpoint updates.

## OUT OF SCOPE

Implementation `-03`..`-08`, closeout, renderer/GPU, importer, persistence, streaming I/O, physics, assets, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0023/0086/0124, TWO-02 architecture/API, governance contract, TWO-01 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0124; exact API and GRD/TIL/COL/PRX/STR/QLF-T2 oracles.

## ARCHITECTURE RULES

TWO-02 owns logical tilemap plans only; TWO-01, DATA-04/05, GFX and PHYS boundaries unchanged; no backend/chunk file/collision solver.

## CONSTRAINTS

Risk `LOW` contract; `INTERNAL_ONLY`; no renderer/importer/physics/streaming I/O/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract exact and complete; manifest root `TWO02_02_APPROVED_CONTRACT_ONLY`.
- No code, dependency, renderer/importer/physics or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; future oracles are declared but not executed.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, renderer/importer/physics/streaming I/O selection, incomplete API, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `fa7f2bd`; governance merge `fa7f2bd`; contract blob pinned after this gate.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-02-02-G6-ACTIVATION.md`.
