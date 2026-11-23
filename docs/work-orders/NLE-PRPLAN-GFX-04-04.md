# NLE-PRPLAN-GFX-04-04 — Conservative geometry culling (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-04-04`. **Predecessor:** `GFX-04-03` instancing. **Issue:** #32. **Base:** `41d325c`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md).

## OBJECTIVE

Implement conservative sphere/frustum/distance culling with unknown bounds visible, deterministic output and typed camera/generation failures.

## CONTEXT

GFX-04-01..03 are approved/completed. No native GPU, occlusion query, mesh library, submission or renderer exists.

## SCOPE

- `geometry_cull.hpp` and CUL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

LOD/HLOD, stream, vegetation, budget, qualification; native GPU/occlusion, mesh library, submission, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0118, internal contract, instancing evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0118; CUL-01 and conservative rules.

## ARCHITECTURE RULES

Unknown bounds visible; cull only when the full sphere is outside a plane or distance limit; no false-negative by construction.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/occlusion query/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; CUL-01 valid/invalid fixtures.
- No native GPU/occlusion/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

CUL-01: visible/unknown-bounds/distance/plane cull, generation mismatch, invalid camera/normals and capacity boundary.

## DELIVERABLES

Header, CUL tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CUL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/occlusion query, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `41d325c`; contract blob pinned in activation; GFX-04-03 merge `41d325c`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-04-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-04-04.md`.
