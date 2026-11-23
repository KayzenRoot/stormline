# NLE-PRPLAN-GFX-08-07 — Volumetric density stamp (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-08-07`. **Predecessor:** `GFX-08-06` transparency. **Issue:** #36. **Base:** `71b27df`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md).

## OBJECTIVE

Implement bounded logical volumetric density-stamp metadata for the GFX-06-owned scattering path.

## CONTEXT

GFX-08-01/-06 are approved/completed. No volume, froxel, ray march, scattering, GPU or render exists.

## SCOPE

- `density_plan.hpp` and DEN-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; volume sampling, froxel grid, scattering, GPU/compute, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0122, internal contract, GFX-06 volumetric boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0122; DEN-01.

## ARCHITECTURE RULES

GFX-08 authors density intent only; GFX-06 owns scattering/fog and no volume is created here.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/compute/froxel/volume-render/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; DEN-01 valid/invalid fixtures.
- No volume/scattering/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

DEN-01 finite density/extinction, positive extents/lifetime/max density, clamp receipt.

## DELIVERABLES

Header, DEN tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, DEN-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, volume/froxel/GPU/SDK selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `71b27df`; contract blob pinned in activation; GFX-08-06 merge `71b27df`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-08-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-08-07.md`.
