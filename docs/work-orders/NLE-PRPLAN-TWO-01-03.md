# NLE-PRPLAN-TWO-01-03 — Sprite draw metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-01-03`. **Predecessor:** `TWO-01-02` contract. **Issue:** #37. **Base:** `4946fa6`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md).

## OBJECTIVE

Implement bounded logical sprite draw metadata validation.

## CONTEXT

TWO-01-01/-02 are approved. No sprite instance, buffer, atlas, GPU or draw exists.

## SCOPE

- `canvas_types.hpp`, `sprite_plan.hpp` and SPR-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; sprite draw, batching, atlas upload, GPU, text/vector, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0123, internal contract, GFX-08 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0123; SPR-01.

## ARCHITECTURE RULES

TWO-01 owns logical sprite metadata; no instance, vertex, buffer, sampler or GPU resource.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/render/text/vector/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; SPR-01 valid/invalid fixtures.
- No draw/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SPR-01 IDs/revisions, region, pivot/tint bounds, layer reference.

## DELIVERABLES

Headers, SPR tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SPR-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, draw/GPU/text/vector/SDK selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `4946fa6`; contract blob pinned in activation; TWO-01-02 merge `4946fa6`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-01-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-01-03.md`.
