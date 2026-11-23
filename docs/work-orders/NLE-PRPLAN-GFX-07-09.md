# NLE-PRPLAN-GFX-07-09 — Integrated post-processing qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — qualification test authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-07-09`. **Predecessor:** `GFX-07-08` upscale. **Issue:** #35. **Base:** `bac24a7`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md).

## OBJECTIVE

Execute integrated logical qualification QLF-G701..G704 across camera/exposure, color, output, reconstruction, motion blur and upscale plans.

## CONTEXT

GFX-07-01/-08 are approved/completed. No native GPU, swapchain, HDR signal, tone mapper, LUT/OCIO, TAA, upscaler, renderer or hardware path exists.

## SCOPE

- `tests/core/gfx07_post_qualification_tests.cpp`.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout; native GPU/swapchain/HDR signal/tone mapper/LUT/OCIO/TAA/upscaler, rendering, driver/hardware, visual golden, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0121, internal contract, all GFX-07 headers/tests.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0121; QLF-G701..G704.

## ARCHITECTURE RULES

Qualification is logical/CI-only; no native GPU/swapchain/HDR/tone-map/AA/upscale/hardware behavior is asserted.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/swapchain/HDR-signal/tone-mapper/LUT/OCIO/TAA/upscaler/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-G701..G704 pass.
- No native GPU/swapchain/HDR signal/tone mapper/LUT/OCIO/TAA/upscaler/render/hardware claim.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-G701 integrated pipeline; G702 deterministic repeat; G703 typed failure recovery; G704 10,000 bounded attempts.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-G701..G704, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/swapchain/HDR/tone-map/AA/upscale/hardware claim, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `bac24a7`; contract blob pinned in activation; GFX-07-08 merge `bac24a7`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-07-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-07-09.md`.
