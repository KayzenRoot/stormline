# NLE-PRPLAN-GFX-06-08 — Volumetric metadata and budget (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-06-08`. **Predecessor:** `GFX-06-07` reflections. **Issue:** #34. **Base:** `0925f30`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md).

## OBJECTIVE

Implement bounded volumetric metadata validation, deterministic ordering and step-budget admission.

## CONTEXT

GFX-06-01/-07 are approved/completed. No froxel buffer, shadowed fog, particle system, GPU or render exists.

## SCOPE

- `volumetric_plan.hpp` and VOL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; froxel/shadowed fog, particles, GPU, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0120, internal contract, lighting headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0120; VOL-01.

## ARCHITECTURE RULES

GFX-06 owns logical volumetric metadata; no froxel buffer, particle spawn or GPU resource is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/froxel/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; VOL-01 valid/invalid fixtures.
- No froxel/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

VOL-01: finite/nonnegative, anisotropy/tier/steps/budget/order/capacity.

## DELIVERABLES

Header, VOL tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, VOL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, froxel/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `0925f30`; contract blob pinned in activation; GFX-06-07 merge `0925f30`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-06-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-06-08.md`.
