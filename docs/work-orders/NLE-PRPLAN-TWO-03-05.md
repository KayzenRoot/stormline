# NLE-PRPLAN-TWO-03-05 — Clip blend metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-03-05`. **Predecessor:** `TWO-03-04` bones. **Issue:** #39. **Base:** `8b7c76f`. **ADR:** [ADR-0125](../adr/0125-two-03-internal-animation-pipeline.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md).

## OBJECTIVE

Implement bounded logical clip blend metadata: unique clip identities, finite nonnegative weights, deterministic normalization and additive/discrete policy validation.

## CONTEXT

TWO-03-01..-04 are approved. No runtime blend tree, pose mixing, sampling, audio, export or GPU exists.

## SCOPE

- `blend_plan.hpp` and BLD-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; runtime blend trees, pose mixing, additive evaluation, skinning, playback, rendering, audio, export, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0125, internal contract, TWO-03-04 skeleton boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0125; BLD-01.

## ARCHITECTURE RULES

TWO-03 owns logical blend metadata; no clip is evaluated, composited or applied.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no runtime/pose/mixing/skinning/audio/export/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; BLD-01 valid/invalid fixtures.
- No runtime/mixing/pose/playback/sampling/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

BLD-01 unique IDs, finite nonnegative weights, positive sum, deterministic normalization, additive/discrete policy, capacity.

## DELIVERABLES

Header, BLD tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, BLD-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, runtime/mixing/audio/export/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `8b7c76f`; contract blob pinned in activation; TWO-03-04 merge `8b7c76f`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-03-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-03-05.md`.
