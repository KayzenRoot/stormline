# NLE-PRPLAN-GFX-07-06 — Logical reconstruction/AA strategy (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-07-06`. **Predecessor:** `GFX-07-05` HDR output. **Issue:** #35. **Base:** `d3a49d6`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md).

## OBJECTIVE

Implement bounded native/spatial/TAA/vendor reconstruction strategy selection with safe fallbacks.

## CONTEXT

GFX-07-01/-05 are approved/completed. No TAA, FXAA/SMAA, FSR/DLSS/XeSS, history texture, GPU or render exists.

## SCOPE

- `reconstruction_plan.hpp` and RCN-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Motion blur, upscale, qualification; TAA/AA/SDK, GPU, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0121, internal contract, post headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0121; RCN-01.

## ARCHITECTURE RULES

GFX-07 owns logical strategy selection; no temporal accumulator, vendor SDK or GPU shader is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/SDK/history texture/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; RCN-01 valid/invalid fixtures.
- No TAA/AA/SDK/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

RCN-01: native/spatial, TAA prerequisites/fallback, vendor prerequisites/fallback, unknown strategy.

## DELIVERABLES

Header, RCN tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, RCN-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, TAA/SDK/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `d3a49d6`; contract blob pinned in activation; GFX-07-05 merge `d3a49d6`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-07-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-07-06.md`.
