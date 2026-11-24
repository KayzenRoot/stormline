# NLE-PRPLAN-WORLD-04-05 — Vegetation placement metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-04-05`. **Predecessor:** `WORLD-04-04` splat layers. **Issue:** #44. **Base:** `aa60d1b`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md).

## OBJECTIVE

Implement bounded logical vegetation placement metadata with stable group/instance identity, prototype references, density bounds, checked totals and collider intent.

## CONTEXT

WORLD-04-01..-04 are approved or completed. No instance buffer, vegetation renderer, batching, collider or physics integration exists.

## SCOPE

- `vegetation_plan.hpp` and VEG-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Terrain/splat changes, water, sky, weather, qualification, closeout; instance buffers, GPU instancing, colliders, physics, networking, editor, rendering, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0130, internal contract, governance contract, `terrain_types.hpp`, `terrain_patch_plan.hpp`, `splat_plan.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0130; VEG-01.

## ARCHITECTURE RULES

WORLD-04 owns authored placement/group metadata only; GFX-04 owns instancing/visibility, PHYS owns colliders, WORLD-05 owns procedural generation.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no GPU/instance/collider/physics/network/editor resource; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; VEG-01 valid/invalid fixtures.
- No instance buffer, renderer, collider or runtime vegetation.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

VEG-01 asset/revision/count validation, unique group keys, nonzero prototype/revision, instance/density bounds, checked totals, collider count, finite bounds, capacity, reset and determinism.

## DELIVERABLES

Header, VEG-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, VEG-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, instancing/collider/runtime selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `aa60d1b`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-04-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-04-05.md`.
