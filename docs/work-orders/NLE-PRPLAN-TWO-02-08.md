# NLE-PRPLAN-TWO-02-08 — Integrated tilemap qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — qualification test authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-02-08`. **Predecessor:** `TWO-02-07` streaming. **Issue:** #38. **Base:** `bc90d00`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md).

## OBJECTIVE

Execute integrated logical qualification QLF-T201..T204 across grid, tiles, collision authoring, parallax and streaming plans.

## CONTEXT

TWO-02-01/-07 are approved/completed. No renderer, importer, persistence, streaming I/O, collision solver, physics or visual output exists.

## SCOPE

- `tests/core/two02_tilemap_qualification_tests.cpp`.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout; renderer, GPU, importer, streaming I/O, physics, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0124, internal contract, all TWO-02 headers/tests.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0124; QLF-T201..T204.

## ARCHITECTURE RULES

Qualification is logical/CI-only; no tile, collision or streaming I/O behavior is asserted.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/render/import/streaming I/O/physics/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-T201..T204 pass.
- No renderer/GPU/physics/I/O claim.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-T201 integrated pipeline; T202 deterministic repeat; T203 typed failure recovery; T204 10,000 bounded attempts.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-T201..T204, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, renderer/GPU/physics/I/O claim, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `bc90d00`; contract blob pinned in activation; TWO-02-07 merge `bc90d00`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-02-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-02-08.md`.
