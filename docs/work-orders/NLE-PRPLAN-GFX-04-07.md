# NLE-PRPLAN-GFX-04-07 — Vegetation render classification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-04-07`. **Predecessor:** `GFX-04-06` stream. **Issue:** #32. **Base:** `6ccb0f5`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md).

## OBJECTIVE

Implement bounded vegetation classification between Mesh and Billboard, preserving double-sided/alpha-cutout flags and conservative unknown-bounds behavior.

## CONTEXT

GFX-04-01..06 are approved/completed. No native GPU, vegetation physics, mesh library, submission or renderer exists.

## SCOPE

- `geometry_vegetation.hpp` and VEG-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Geometry budget, qualification; vegetation placement/physics, native GPU/mesh library, submission, render, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0118, internal contract, stream evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0118; VEG-01.

## ARCHITECTURE RULES

Only Grass/Bush/Tree; unknown bounds remain Mesh; flags preserved; no silent skip.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/vegetation simulation/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; VEG-01 valid/invalid fixtures.
- No native GPU/vegetation physics/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

VEG-01: near Mesh, far Billboard when allowed, far Mesh when not allowed, unknown bounds, invalid category/distance.

## DELIVERABLES

Header, VEG tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, VEG-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, vegetation physics/GPU, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `6ccb0f5`; contract blob pinned in activation; GFX-04-06 merge `6ccb0f5`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-04-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-04-07.md`.
