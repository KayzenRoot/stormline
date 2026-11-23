# NLE-PRPLAN-GFX-06-03 — Logical light validation (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-06-03`. **Predecessor:** `GFX-06-02` contract. **Issue:** #34. **Base:** `4b49b09`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md).

## OBJECTIVE

Implement bounded logical light validation: identities, kinds/units, finite color/intensity, geometry and shadow policy.

## CONTEXT

GFX-06-01/-02 are approved. No native GPU, shadow map, ray tracing, shader, renderer or visual exists.

## SCOPE

- `lighting_types.hpp`, `light.hpp` and LGT-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Shadows, GI, probes, reflections, volumetrics, qualification; native GPU/shadow/ray tracing, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0120, internal contract.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0120; LGT-01.

## ARCHITECTURE RULES

GFX-06 owns logical lights; no GPU light, shadow map or shader resource is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/shadow/ray-tracing/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; LGT-01 valid/invalid fixtures.
- No GPU/shadow/ray-tracing/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

LGT-01: add/duplicate/capacity, kinds/units, finite/range, spot/area, shadow policy.

## DELIVERABLES

Headers, LGT tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, LGT-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, GPU/shadow/ray-tracing selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `4b49b09`; contract blob pinned in activation; GFX-06-02 merge `4b49b09`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-06-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-06-03.md`.
