# NLE-PRPLAN-TWO-03-06 — Cutscene sequence metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-03-06`. **Predecessor:** `TWO-03-05` blend. **Issue:** #39. **Base:** `d3dfe26`. **ADR:** [ADR-0125](../adr/0125-two-03-internal-animation-pipeline.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md).

## OBJECTIVE

Implement bounded logical cutscene sequence metadata: tracks, cues, allowlisted kinds, in-duration timing and nesting depth.

## CONTEXT

TWO-03-01..-05 are approved. No runtime sequence playback, cue dispatch, audio, export or GPU exists.

## SCOPE

- `sequence_plan.hpp` and SEQ-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; runtime playback, cue dispatch, event execution, camera/audio behavior, editing UI, rendering, export, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0125, internal contract, TWO-03-05 blend boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0125; SEQ-01.

## ARCHITECTURE RULES

TWO-03 owns logical sequence metadata; no cue is dispatched, played or applied.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no runtime/dispatch/event execution/audio/export/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; SEQ-01 valid/invalid fixtures.
- No runtime/dispatch/playback/audio/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SEQ-01 tracks/cues, allowed and invalid kinds, timing within duration, unique IDs, nesting depth, capacity, overflow-safe tick arithmetic.

## DELIVERABLES

Header, SEQ tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SEQ-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, runtime/dispatch/audio/export/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `d3dfe26`; contract blob pinned in activation; TWO-03-05 merge `d3dfe26`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-03-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-03-06.md`.
