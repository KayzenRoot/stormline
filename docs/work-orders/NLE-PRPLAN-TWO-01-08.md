# NLE-PRPLAN-TWO-01-08 — 2D light requests (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-01-08`. **Predecessor:** `TWO-01-07` pixel snapping. **Issue:** #37. **Base:** `9f8015f`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md). **Contract:** [two-01-canvas-internal-v0](../contracts/two-01-canvas-internal-v0.md).

## OBJECTIVE

Implement bounded logical 2D light-request metadata for the GFX-06-owned lighting path.

## CONTEXT

TWO-01-01/-07 are approved/completed. No light, shadow, normal map, scissor mask, GPU or render exists.

## SCOPE

- `light_plan.hpp` and LGT-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; lighting/shadows execution, GPU, render, text/vector, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0123, internal contract, GFX-06 lighting boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0123; LGT-01.

## ARCHITECTURE RULES

TWO-01 authors light requests only; GFX-06 owns lights/shadows and no light is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/lighting/shadow/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; LGT-01 valid/invalid fixtures.
- No lighting/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

LGT-01 IDs, intensity/radius/color bounds, falloff, budget clamp.

## DELIVERABLES

Header, LGT tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, LGT-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, lighting/shadow/GPU/SDK selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `9f8015f`; contract blob pinned in activation; TWO-01-07 merge `9f8015f`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-01-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-01-08.md`.
