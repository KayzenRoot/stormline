# NLE-PRPLAN-WORLD-04-04 — Splat/material layer metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-04-04`. **Predecessor:** `WORLD-04-03` terrain patches. **Issue:** #44. **Base:** `9a4f237`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md).

## OBJECTIVE

Implement bounded logical splat/material layer metadata with normalized finite weights, channel and precedence intent, unique layer IDs and material counts.

## CONTEXT

WORLD-04-01/-02/-03 are approved or completed. No texture residency, material graph, PBR blending or terrain renderer exists.

## SCOPE

- `splat_plan.hpp` and SPL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Terrain patch changes, vegetation, water, sky, weather, qualification, closeout; textures, virtual residency, material graph, PBR/BRDF, rendering, GPU, physics, networking, editor, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0130, internal contract, governance contract, `terrain_types.hpp`, `terrain_patch_plan.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0130; SPL-01.

## ARCHITECTURE RULES

WORLD-04 owns authored weight/precedence metadata only; GFX-05 owns materials/textures/residency and GFX-07 owns color output.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no texture/material/renderer/GPU resource, no physics/network/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; SPL-01 valid/invalid fixtures.
- No texture residency, material graph, PBR implementation or renderer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SPL-01 asset/revision/count validation, unique layer IDs, nonzero material IDs/revisions, channel range, finite normalized weights and total, material count, capacity, reset and determinism.

## DELIVERABLES

Header, SPL-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SPL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, texture/material/renderer selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `9a4f237`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-04-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-04-04.md`.
