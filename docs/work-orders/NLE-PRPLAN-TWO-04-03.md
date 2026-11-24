# NLE-PRPLAN-TWO-04-03 — Camera projection intent (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-04-03`. **Predecessor:** `TWO-04-02` contract. **Issue:** #40. **Base:** `3c4f030`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md).

## OBJECTIVE

Implement bounded logical orthographic/perspective camera intent metadata with finite positive parameters.

## CONTEXT

TWO-04-01/-02 are approved. No camera matrix, trigonometry, frustum, renderer or GPU exists.

## SCOPE

- `hybrid_types.hpp`, `camera_plan.hpp` and CAM-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Layers, sorting, effects, qualification, closeout; matrix evaluation, trigonometry, frustum culling, rendering, GPU, audio, export, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0126, internal contract, TWO-04 governance contract.

## REQUIREMENTS

GOV-001..007; ADR-0126; CAM-01.

## ARCHITECTURE RULES

TWO-04 owns logical camera intent; GFX-07 owns future camera matrices/views/output.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no matrix/trig/frustum/render/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; CAM-01 valid/invalid fixtures.
- No matrix, trigonometry, frustum, layer, sort, render or GPU.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

CAM-01 orthographic/perspective kinds, positive/finite near/far, fov bounds, aspect, capacity/reset and determinism.

## DELIVERABLES

Headers, CAM tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CAM-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, matrix/trig/render/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `3c4f030`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-04-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-04-03.md`.
