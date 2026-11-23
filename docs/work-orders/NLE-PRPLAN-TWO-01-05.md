# NLE-PRPLAN-TWO-01-05 — Layer order metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-01-05`. **Predecessor:** `TWO-01-04` atlases. **Issue:** #37. **Base:** `0bdf65d`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md).

## OBJECTIVE

Implement bounded logical layer identity/order/opacity/blend/clip metadata with preserved painter order.

## CONTEXT

TWO-01-01/-04 are approved/completed. No compositing, sorting, clipping execution or GPU exists.

## SCOPE

- `layer_plan.hpp` and LAY-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; compositing, reordering for batching, clip execution, GPU, render, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0123, internal contract, GFX-05/07 boundaries.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0123; LAY-01.

## ARCHITECTURE RULES

TWO-01 owns logical layer order; declared painter order is never reordered; no layer is composited.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/compositing/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; LAY-01 valid/invalid fixtures.
- No compositing/reordering/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

LAY-01 unique IDs/orders, opacity/blend/clip bounds, painter order.

## DELIVERABLES

Header, LAY tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, LAY-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, compositing/GPU/SDK selection, painter-order violation, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `0bdf65d`; contract blob pinned in activation; TWO-01-04 merge `0bdf65d`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-01-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-01-05.md`.
