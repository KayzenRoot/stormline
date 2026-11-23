# NLE-PRPLAN-TWO-02-04 — Tile cell metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-02-04`. **Predecessor:** `TWO-02-03` grid. **Issue:** #38. **Base:** `6144d4f`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md).

## OBJECTIVE

Implement bounded logical tile-cell identity, empty sentinel, orientation and transform metadata.

## CONTEXT

TWO-02-01/-03 are approved/completed. No tile instance, sprite, buffer, GPU or draw exists.

## SCOPE

- `tile_plan.hpp` and TIL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; tile rendering, batching, importer, GPU, physics, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0124, internal contract, TWO-01 sprite boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0124; TIL-01.

## ARCHITECTURE RULES

TWO-02 owns logical tile cells; TWO-01 owns sprite draw; no tile instance or GPU resource.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no renderer/GPU/import/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; TIL-01 valid/invalid fixtures.
- No rendering/GPU/importer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

TIL-01 IDs, empty sentinel, orientation/transform, invalid flags.

## DELIVERABLES

Header, TIL tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TIL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, renderer/importer/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `6144d4f`; contract blob pinned in activation; TWO-02-03 merge `6144d4f`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-02-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-02-04.md`.
