# NLE-PRPLAN-GFX-04-05 — LOD and HLOD selection (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-04-05`. **Predecessor:** `GFX-04-04` culling. **Issue:** #32. **Base:** `b6767c3`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md).

## OBJECTIVE

Implement bounded LOD chains, projected-error selection with hysteresis and acyclic HLOD hierarchy selection.

## CONTEXT

GFX-04-01..04 are approved/completed. No native GPU, mesh library, submission or renderer exists.

## SCOPE

- `geometry_lod.hpp` and LOD-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Streaming, vegetation, budget, qualification; native GPU/mesh library, submission, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0118, internal contract, culling evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0118; LOD-01 and hierarchy rules.

## ARCHITECTURE RULES

LOD/HLOD are logical metadata; unknown bounds select full detail; hierarchy must be acyclic.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/mesh codec/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; LOD-01 valid/invalid fixtures.
- No native GPU/mesh library/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

LOD-01: chain ordering, projected selection/hysteresis, unknown bounds, HLOD subtree selection, missing parent and cycle.

## DELIVERABLES

Header, LOD tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, LOD-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/mesh library, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `b6767c3`; contract blob pinned in activation; GFX-04-04 merge `b6767c3`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-04-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-04-05.md`.
