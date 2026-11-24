# NLE-PRPLAN-TWO-04-04 — 2D/3D layer intent (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-04-04`. **Predecessor:** `TWO-04-03` camera. **Issue:** #40. **Base:** `922fb85`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md).

## OBJECTIVE

Implement bounded logical 2D/3D layer intent with explicit composition mode, stable order and depth/alpha policy validation.

## CONTEXT

TWO-04-01..-03 are approved. No renderer, depth attachment, sorting or GPU exists.

## SCOPE

- `layer_plan.hpp` and LAY-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Sorting, effects, qualification, closeout; renderer, GPU, depth attachment, matrix, lighting, editor, audio, export, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0126, internal contract, camera boundary.

## REQUIREMENTS

GOV-001..007; ADR-0126; LAY-01.

## ARCHITECTURE RULES

TWO-04 owns logical layer intent; TWO-01 painter order, GFX-03 depth attachments and GFX-05 alpha remain authoritative.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no render/depth attachment/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; LAY-01 valid/invalid fixtures.
- No renderer, depth attachment, sort, effect or GPU.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

LAY-01 unique IDs/orders, modes, alpha/depth policy combinations, capacity, reset and determinism.

## DELIVERABLES

Header, LAY tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, LAY-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, render/depth/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `922fb85`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-04-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-04-04.md`.
