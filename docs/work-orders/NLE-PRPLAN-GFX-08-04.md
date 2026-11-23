# NLE-PRPLAN-GFX-08-04 — Ribbon geometry budget (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-08-04`. **Predecessor:** `GFX-08-03` particles. **Issue:** #36. **Base:** `b8fd0c4`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md).

## OBJECTIVE

Implement bounded logical ribbon sample/segment/vertex budget metadata.

## CONTEXT

GFX-08-01/-03 are approved/completed. No ribbon tessellation, buffer, GPU or render exists.

## SCOPE

- `ribbon_plan.hpp` and RIB-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; tessellation, spline, GPU/compute, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0122, internal contract, GFX-08 headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0122; RIB-01.

## ARCHITECTURE RULES

GFX-08 owns logical ribbon plans; no vertex, strip, buffer or GPU resource is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/compute/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; RIB-01 valid/invalid fixtures.
- No tessellation/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

RIB-01 sample range, width/distance, segment/vertex caps, checked arithmetic.

## DELIVERABLES

Header, RIB tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, RIB-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, tessellation/GPU/SDK selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `b8fd0c4`; contract blob pinned in activation; GFX-08-03 merge `b8fd0c4`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-08-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-08-04.md`.
