# NLE-PRPLAN-GFX-07-05 — Logical HDR output negotiation (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-07-05`. **Predecessor:** `GFX-07-04` tone/color. **Issue:** #35. **Base:** `c5872c6`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md).

## OBJECTIVE

Implement logical SDR/HDR output selection with explicit capability flags and safe SDR fallback.

## CONTEXT

GFX-07-01/-04 are approved/completed. No swapchain, HDR monitor, PQ signal, OS negotiation or GPU exists.

## SCOPE

- `output_plan.hpp` and HDR-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Reconstruction, motion blur, upscale, qualification; swapchain/HDR display, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0121, internal contract, post headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0121; HDR-01.

## ARCHITECTURE RULES

GFX-07 owns logical output fallback; GFX-01 owns actual swapchain/display HDR capability.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/display/swapchain/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; HDR-01 valid/invalid fixtures.
- No HDR signal/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

HDR-01: SDR preference, all HDR capabilities, partial capability fallback, degraded flag.

## DELIVERABLES

Header, HDR tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, HDR-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, GPU/display selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `c5872c6`; contract blob pinned in activation; GFX-07-04 merge `c5872c6`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-07-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-07-05.md`.
