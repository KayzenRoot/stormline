# NLE-PRPLAN-TWO-01-04 — Atlas metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-01-04`. **Predecessor:** `TWO-01-03` sprites. **Issue:** #37. **Base:** `62308a1`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md).

## OBJECTIVE

Implement bounded logical atlas region/gutter/mip metadata validation.

## CONTEXT

TWO-01-01/-03 are approved/completed. No atlas packing, upload, sampler, GPU or render exists.

## SCOPE

- `atlas_plan.hpp` and ATL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; atlas packing, upload, sampling, GPU, text/vector, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0123, internal contract, GFX-05 texture boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0123; ATL-01.

## ARCHITECTURE RULES

TWO-01 owns logical atlas metadata; no atlas is packed, uploaded or sampled.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/atlas cooker/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; ATL-01 valid/invalid fixtures.
- No packing/upload/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

ATL-01 dimensions/gutter/mips, region bounds, duplicate IDs, capacity.

## DELIVERABLES

Header, ATL tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, ATL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, atlas packer/GPU/SDK selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `62308a1`; contract blob pinned in activation; TWO-01-03 merge `62308a1`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-01-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-01-04.md`.
