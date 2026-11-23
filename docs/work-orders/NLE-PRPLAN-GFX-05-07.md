# NLE-PRPLAN-GFX-05-07 — Decal ordering (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-05-07`. **Predecessor:** `GFX-05-06` samplers. **Issue:** #33. **Base:** `a8aff19`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md).

## OBJECTIVE

Implement bounded deterministic decal validation and layer/id ordering.

## CONTEXT

GFX-05-01/-06 are approved/completed. No projection, blending, GPU or renderer exists.

## SCOPE

- `decal.hpp` and DEC-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Transparency, qualification; decal projection/blending, GPU, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0119, internal contract, material types.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0119; DEC-01.

## ARCHITECTURE RULES

GFX-05 owns logical decal metadata/order; no projection, blend or GPU operation.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/codec/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; DEC-01 valid/invalid fixtures.
- No projection/blend/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

DEC-01: duplicate/capacity/layer/position/radius/opacity, deterministic `(layer,id)` order.

## DELIVERABLES

Header, DEC tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, DEC-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, GPU/projection selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `a8aff19`; contract blob pinned in activation; GFX-05-06 merge `a8aff19`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-05-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-05-07.md`.
