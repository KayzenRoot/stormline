# NLE-PRPLAN-TWO-01-07 — Pixel snapping metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-01-07`. **Predecessor:** `TWO-01-06` camera. **Issue:** #37. **Base:** `7d0b638`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md).

## OBJECTIVE

Implement bounded logical integer/continuous pixel-snapping policy metadata.

## CONTEXT

TWO-01-01/-06 are approved/completed. No pixel sampling, rasterization, GPU or render exists.

## SCOPE

- `snap_plan.hpp` and SNP-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; pixel sampling, rasterization, GPU, render, text/vector, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0123, internal contract, camera boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0123; SNP-01.

## ARCHITECTURE RULES

TWO-01 owns logical snap policy; no pixel is sampled or rasterized.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/rasterizer/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; SNP-01 valid/invalid fixtures.
- No sampling/rasterization/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SNP-01 modes/scales/offsets, integer degradation, snapped offsets.

## DELIVERABLES

Header, SNP tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SNP-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, rasterizer/GPU/SDK selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `7d0b638`; contract blob pinned in activation; TWO-01-06 merge `7d0b638`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-01-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-01-07.md`.
