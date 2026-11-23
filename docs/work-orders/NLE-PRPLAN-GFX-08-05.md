# NLE-PRPLAN-GFX-08-05 — Trail geometry budget (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-08-05`. **Predecessor:** `GFX-08-04` ribbons. **Issue:** #36. **Base:** `ded41b4`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md).

## OBJECTIVE

Implement bounded logical trail sample/age/segment/vertex budget metadata.

## CONTEXT

GFX-08-01/-04 are approved/completed. No trail history, buffer, tessellation, GPU or render exists.

## SCOPE

- `trail_plan.hpp` and TRL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; trail history, strip/tessellation, GPU/compute, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0122, internal contract, GFX-08 headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0122; TRL-01.

## ARCHITECTURE RULES

GFX-08 owns logical trail plans; no history, vertex, buffer or GPU resource is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/compute/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; TRL-01 valid/invalid fixtures.
- No tessellation/history/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

TRL-01 sample range, ordered ages, widths, max age, segment/vertex caps.

## DELIVERABLES

Header, TRL tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TRL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, trail-history/GPU/SDK selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `ded41b4`; contract blob pinned in activation; GFX-08-04 merge `ded41b4`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-08-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-08-05.md`.
