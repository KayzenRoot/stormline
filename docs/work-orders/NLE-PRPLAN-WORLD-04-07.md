# NLE-PRPLAN-WORLD-04-07 — Sky/environment profile metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-04-07`. **Predecessor:** `WORLD-04-06` water. **Issue:** #44. **Base:** `214fe4c`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md).

## OBJECTIVE

Implement bounded logical sky/environment profile metadata with unique IDs, finite time/direction/range parameters and quality-tier counts.

## CONTEXT

WORLD-04-01..-06 are approved or completed. No atmospheric renderer, light solver, fog, exposure or post pipeline exists.

## SCOPE

- `sky_plan.hpp` and SKY-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Terrain/splat/vegetation/water changes, weather, qualification, closeout; atmosphere/light/fog rendering, HDR/post, GPU, physics, networking, editor, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0130, internal contract, governance contract, `terrain_types.hpp` and prior terrain headers.

## REQUIREMENTS

GOV-001..007; ADR-0130; SKY-01.

## ARCHITECTURE RULES

WORLD-04 owns authored sky profile parameters only; GFX-06 owns light/fog/atmosphere, GFX-07 owns HDR/post/color, GAME/NET own time authority.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no atmosphere renderer, light solver, GPU, physics/network, editor or post pipeline; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; SKY-01 valid/invalid fixtures.
- No atmosphere/light/fog renderer, GPU or post pipeline.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SKY-01 asset/revision/count validation, unique profile IDs, nonzero revisions, time range, finite nonzero sun/moon directions, cloud/fog ranges, tier allowlist and counts, capacity, reset and determinism.

## DELIVERABLES

Header, SKY-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SKY-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, atmosphere/renderer/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `214fe4c`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-04-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-04-07.md`.
