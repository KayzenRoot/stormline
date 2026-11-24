# NLE-PRPLAN-WORLD-04-08 — Weather visual intent metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-04-08`. **Predecessor:** `WORLD-04-07` sky. **Issue:** #44. **Base:** `761f837`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md).

## OBJECTIVE

Implement bounded logical weather visual-intent metadata with stable zone IDs, authoritative source tick/revision, finite intensities, acknowledgement counts and maxima.

## CONTEXT

WORLD-04-01..-07 are approved or completed. No climate simulation, weather authority, particles, wetness or gameplay weather exists.

## SCOPE

- `weather_plan.hpp` and CLI-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Terrain/splat/vegetation/water/sky changes, qualification, closeout; climate simulation, weather authority, VFX, wetness, physics, networking, editor, rendering, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0130, internal contract, governance contract, `terrain_types.hpp` and prior terrain headers.

## REQUIREMENTS

GOV-001..007; ADR-0130; CLI-01.

## ARCHITECTURE RULES

WORLD-04 owns authored weather visual intent only; GAME/NET own authoritative weather, CORE-06 owns clocks, GFX-08 owns particles, GFX-05/06/07 own materials/lighting/post.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no climate simulation, weather authority, particles, GPI, physics/network, editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; CLI-01 valid/invalid fixtures.
- No climate simulation, weather authority, particles or gameplay weather.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

CLI-01 asset/revision/count validation, unique zone IDs, nonzero revisions/tick/source revision, finite intensity ranges, acknowledgement counts, maxima, capacity, reset and determinism.

## DELIVERABLES

Header, CLI-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CLI-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, climate/authority/VFX selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `761f837`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-04-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-04-08.md`.
