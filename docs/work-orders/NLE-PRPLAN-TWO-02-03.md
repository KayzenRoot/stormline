# NLE-PRPLAN-TWO-02-03 — Signed grid/chunk math (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-02-03`. **Predecessor:** `TWO-02-02` contract. **Issue:** #38. **Base:** `b56ae04`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md).

## OBJECTIVE

Implement bounded signed 64-bit grid/chunk floor math and local-coordinate metadata.

## CONTEXT

TWO-02-01/-02 are approved. No renderer, grid GPU coordinate, map I/O or streaming exists.

## SCOPE

- `tilemap_types.hpp`, `grid_plan.hpp` and GRD-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; renderer, map I/O, streaming, GPU coordinates, physics, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0124, internal contract, TWO-01 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0124; GRD-01.

## ARCHITECTURE RULES

TWO-02 owns logical signed grid math; no GPU coordinate, chunk file or renderer is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no renderer/GPU/import/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; GRD-01 valid/invalid fixtures, including negative cells.
- No renderer/GPU/I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

GRD-01 dimensions/bounds, negative floor division, local coordinates, overflow.

## DELIVERABLES

Headers, GRD tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, GRD-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, renderer/GPU/import selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `b56ae04`; contract blob pinned in activation; TWO-02-02 merge `b56ae04`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-02-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-02-03.md`.
