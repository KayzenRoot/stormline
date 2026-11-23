# NLE-PRPLAN-GFX-07-08 — Render scale and upscale planning (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-07-08`. **Predecessor:** `GFX-07-07` motion blur. **Issue:** #35. **Base:** `145df17`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md).

## OBJECTIVE

Implement bounded logical render-scale fraction and upscale-strategy metadata.

## CONTEXT

GFX-07-01/-07 are approved/completed. No upscaler, sharpening kernel, vendor SDK, GPU or render exists.

## SCOPE

- `upscale_plan.hpp` and UPS-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; FSR/DLSS/XeSS, sharpening, GPU, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0121, internal contract, post headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0121; UPS-01.

## ARCHITECTURE RULES

GFX-07 owns logical scale metadata; no image, kernel or SDK is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/upscaler/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; UPS-01 valid/invalid fixtures.
- No upscale/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

UPS-01: reduced fraction, native mismatch, reconstructed flag, invalid dimensions/strategy.

## DELIVERABLES

Header, UPS tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, UPS-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, upscaler/SDK/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `145df17`; contract blob pinned in activation; GFX-07-07 merge `145df17`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-07-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-07-08.md`.
