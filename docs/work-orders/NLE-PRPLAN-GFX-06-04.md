# NLE-PRPLAN-GFX-06-04 — Logical shadow planning (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-06-04`. **Predecessor:** `GFX-06-03` lights. **Issue:** #34. **Base:** `2dbc8ee`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md).

## OBJECTIVE

Implement bounded cascade split planning and deterministic shadow-page request prefixes.

## CONTEXT

GFX-06-01/-03 are approved/completed. No shadow map, depth texture, page table, GPU resource or render exists.

## SCOPE

- `shadow_plan.hpp` and SHD-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

GI, probes, reflections, volumetrics, qualification; shadow map/PCF/PCSS, GPU, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0120, internal contract, lighting headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0120; SHD-01.

## ARCHITECTURE RULES

GFX-06 owns logical cascade/page plans; no shadow map, GPU texture or page table is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/shadow/resource/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; SHD-01 valid/invalid fixtures.
- No shadow map/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SHD-01: cascade math/order/invalid requests, page identity/light/distance/resident/budget/order/fallback.

## DELIVERABLES

Header, SHD tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SHD-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, shadow-map/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `2dbc8ee`; contract blob pinned in activation; GFX-06-03 merge `2dbc8ee`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-06-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-06-04.md`.
