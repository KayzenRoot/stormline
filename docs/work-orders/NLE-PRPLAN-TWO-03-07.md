# NLE-PRPLAN-TWO-03-07 — Rational timeline metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-03-07`. **Predecessor:** `TWO-03-06` cutscenes. **Issue:** #39. **Base:** `8878ee1`. **ADR:** [ADR-0125](../adr/0125-two-03-internal-animation-pipeline.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md).

## OBJECTIVE

Implement bounded logical timeline metadata: rational fps, checked frame/sample mapping, loop region and declared depth.

## CONTEXT

TWO-03-01..-06 are approved. No clock, playback, audio scheduling, export or GPU exists.

## SCOPE

- `timeline_plan.hpp` and TML-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; clock, playback, seek/reverse runtime, audio scheduling, export/codec, editor UI, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0125, internal contract, TWO-03-06 sequence boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0125; TML-01.

## ARCHITECTURE RULES

TWO-03 owns logical timeline metadata; no frame is sampled, no sample is scheduled and no clock is read.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no runtime/clock/audio/export/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; TML-01 valid/invalid fixtures.
- No clock/playback/audio/export/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

TML-01 fps/sample mapping, rational rates, loop validity, checked multiplication overflow, capacity and reset.

## DELIVERABLES

Header, TML tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TML-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, clock/playback/audio/export/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `8878ee1`; contract blob pinned in activation; TWO-03-06 merge `8878ee1`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-03-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-03-07.md`.
