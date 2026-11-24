# NLE-PRPLAN-WORLD-04-06 — Water body metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-04-06`. **Predecessor:** `WORLD-04-05` vegetation. **Issue:** #44. **Base:** `794cf42`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md).

## OBJECTIVE

Implement bounded logical water-body metadata with stable IDs, allowlisted classes, finite ordered regions, surface/wave ranges and shore completeness reporting.

## CONTEXT

WORLD-04-01..-05 are approved or completed. No water simulation, buoyancy, surface renderer or physics volume exists.

## SCOPE

- `water_plan.hpp` and WAT-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Terrain/splat/vegetation changes, sky, weather, qualification, closeout; water simulation, buoyancy, rendering, physics, networking, editor, GPU, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0130, internal contract, governance contract, `terrain_types.hpp` and prior terrain headers.

## REQUIREMENTS

GOV-001..007; ADR-0130; WAT-01.

## ARCHITECTURE RULES

WORLD-04 owns authored water visual intent only; PHYS owns buoyancy/collision/flow, GAME/NET own gameplay authority, GFX-05/06/07 own shading/lighting/color.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no simulation, renderer, physics volume, network, editor or GPU resource; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; WAT-01 valid/invalid fixtures.
- No water simulation, rendering, buoyancy or physics volume.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

WAT-01 asset/revision/count validation, unique body keys, nonzero revisions, class allowlist, finite ordered bounds, finite surface/amplitude/frequency, class counts, shore completeness, surface bounds, capacity, reset and determinism.

## DELIVERABLES

Header, WAT-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, WAT-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, simulation/renderer/physics selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `794cf42`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-04-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-04-06.md`.
