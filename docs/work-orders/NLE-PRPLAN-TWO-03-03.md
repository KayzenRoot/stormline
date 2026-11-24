# NLE-PRPLAN-TWO-03-03 — Flipbook metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-03-03`. **Predecessor:** `TWO-03-02` contract. **Issue:** #39. **Base:** `9c1c57f`. **ADR:** [ADR-0125](../adr/0125-two-03-internal-animation-pipeline.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md).

## OBJECTIVE

Implement bounded logical flipbook frame metadata (frame IDs, sprite/atlas refs, holds, total).

## CONTEXT

TWO-03-01/-02 are approved. No frame playback, sampling, audio, export or GPU exists.

## SCOPE

- `animation_types.hpp`, `flipbook_plan.hpp` and FLB-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; playback, sampling, rendering, audio, export, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0125, internal contract, TWO-01 sprite boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0125; FLB-01.

## ARCHITECTURE RULES

TWO-03 owns logical frame metadata; no frame is sampled, played or drawn.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no runtime/audio/export/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; FLB-01 valid/invalid fixtures.
- No playback/sampling/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

FLB-01 IDs, holds, timebase, capacity, total overflow.

## DELIVERABLES

Headers, FLB tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, FLB-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, playback/audio/export/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `9c1c57f`; contract blob pinned in activation; TWO-03-02 merge `9c1c57f`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-03-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-03-03.md`.
