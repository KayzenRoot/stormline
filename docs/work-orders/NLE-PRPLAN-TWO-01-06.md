# NLE-PRPLAN-TWO-01-06 — Camera metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-01-06`. **Predecessor:** `TWO-01-05` layers. **Issue:** #37. **Base:** `573e031`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md).

## OBJECTIVE

Implement bounded logical orthographic 2D camera viewport/position/zoom/DPI metadata.

## CONTEXT

TWO-01-01/-05 are approved/completed. No projection matrix, GPU view, swapchain or render exists.

## SCOPE

- `camera_plan.hpp` and CAM-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; matrix generation, GPU view, swapchain, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0123, internal contract, GFX-07 camera boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0123; CAM-01.

## ARCHITECTURE RULES

TWO-01 owns logical 2D camera metadata; no matrix or GPU view is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/swapchain/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; CAM-01 valid/invalid fixtures.
- No matrix/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

CAM-01 viewport, position, zoom, DPI, effective zoom, letterbox.

## DELIVERABLES

Header, CAM tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CAM-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, matrix/GPU/swapchain selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `573e031`; contract blob pinned in activation; TWO-01-05 merge `573e031`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-01-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-01-06.md`.
