# NLE-PRPLAN-TWO-01-09 — Integrated canvas qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — qualification test authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-01-09`. **Predecessor:** `TWO-01-08` lights. **Issue:** #37. **Base:** `517f573`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md).

## OBJECTIVE

Execute integrated logical qualification QLF-T101..T104 across sprites, atlases, layers, camera, snapping and light requests.

## CONTEXT

TWO-01-01/-08 are approved/completed. No renderer, GPU, text/vector engine, lighting or visual output exists.

## SCOPE

- `tests/core/two01_canvas_qualification_tests.cpp`.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout; renderer, GPU, rasterization, text/vector, lighting execution, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0123, internal contract, all TWO-01 headers/tests.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0123; QLF-T101..T104.

## ARCHITECTURE RULES

Qualification is logical/CI-only; no pixel, sprite, text or lighting behavior is asserted.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/render/rasterization/text/vector/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-T101..T104 pass.
- No renderer/GPU/visual claim.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-T101 integrated pipeline; T102 deterministic repeat; T103 typed failure recovery; T104 10,000 bounded attempts.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-T101..T104, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, renderer/GPU/text/vector claim, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `517f573`; contract blob pinned in activation; TWO-01-08 merge `517f573`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-01-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-01-09.md`.
