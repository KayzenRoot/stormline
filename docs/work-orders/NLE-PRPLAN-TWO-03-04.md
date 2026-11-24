# NLE-PRPLAN-TWO-03-04 — 2D bone hierarchy metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-03-04`. **Predecessor:** `TWO-03-03` flipbooks. **Issue:** #39. **Base:** `73569c2`. **ADR:** [ADR-0125](../adr/0125-two-03-internal-animation-pipeline.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md).

## OBJECTIVE

Implement bounded logical 2D bone hierarchy metadata: unique bone identities, parent DAG validation, cycle/depth limits and finite local transforms.

## CONTEXT

TWO-03-01..-03 are approved. No pose evaluation, skinning, playback, sampling, audio, export or GPU exists.

## SCOPE

- `skeleton_plan.hpp` and BON-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; pose evaluation, skinning, IK, runtime hierarchy, playback, rendering, audio, export, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0125, internal contract, TWO-03-03 flipbook boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0125; BON-01.

## ARCHITECTURE RULES

TWO-03 owns logical bone metadata; no transform is composed, evaluated or applied.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no runtime/pose/skinning/audio/export/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; BON-01 valid/invalid fixtures.
- No pose/skinning/playback/sampling/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

BON-01 unique IDs, parent DAG, self-parent/cycle, depth limit, finite transforms, capacity.

## DELIVERABLES

Header, BON tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, BON-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, pose/skinning/audio/export/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `73569c2`; contract blob pinned in activation; TWO-03-03 merge `73569c2`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-03-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-03-04.md`.
