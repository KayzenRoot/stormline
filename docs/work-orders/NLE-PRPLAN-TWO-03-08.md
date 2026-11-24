# NLE-PRPLAN-TWO-03-08 — Integrated animation qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-03-08`. **Predecessor:** `TWO-03-07` timelines. **Issue:** #39. **Base:** `1bfd3ec`. **ADR:** [ADR-0125](../adr/0125-two-03-internal-animation-pipeline.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md).

## OBJECTIVE

Qualify the integrated internal animation planners with deterministic repeat, failure recovery and bounded overload fixtures.

## CONTEXT

TWO-03-01..-07 are approved. No runtime playback, pose evaluation, audio, export or GPU exists.

## SCOPE

- `two03_animation_qualification_tests.cpp` with QLF-T301..T304.
- Additive CMake targets/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout; runtime, pose, skinning, playback, audio, export, GPU, hardware, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0125, internal contract, TWO-03-03..-07 headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0125; QLF-T301..T304.

## ARCHITECTURE RULES

Qualification exercises planner contracts only; no runtime or engine behavior is claimed.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no runtime/audio/export/GPU/dependency/native I/O/network/hardware; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-T301..T304 pass.
- 10,000 bounded attempts stay within caps.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-T301 integrated planners; QLF-T302 deterministic repeat; QLF-T303 failure recovery; QLF-T304 bounded overload.

## DELIVERABLES

Qualification tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-T301..T304, sanitizers/CI, errors/corrections, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, runtime/audio/export/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `1bfd3ec`; contract blob pinned in activation; TWO-03-07 merge `1bfd3ec`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-03-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-03-08.md`.
