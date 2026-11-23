# NLE-PRPLAN-GFX-07-04 — Logical tone/color plan (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-07-04`. **Predecessor:** `GFX-07-03` camera/exposure. **Issue:** #35. **Base:** `c6e4aa9`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md).

## OBJECTIVE

Implement bounded logical tone/color validation and double-transfer/tone guards.

## CONTEXT

GFX-07-01/-03 are approved/completed. No tone mapper, LUT, OCIO/ACES runtime, color transform or GPU exists.

## SCOPE

- `tone_color.hpp` and COL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

HDR output, reconstruction, motion blur, upscale, qualification; tone mapping, LUT/OCIO, GPU, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0121, internal contract, post headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0121; COL-01.

## ARCHITECTURE RULES

GFX-07 owns logical color/tone policy; no pixel transform, LUT or shader is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/LUT/OCIO/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; COL-01 valid/invalid fixtures.
- No tone mapping/LUT/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

COL-01: transfers/tone curve, stops, white point, double transfer/tone guard.

## DELIVERABLES

Header, COL tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, COL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, tone/LUT/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `c6e4aa9`; contract blob pinned in activation; GFX-07-03 merge `c6e4aa9`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-07-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-07-04.md`.
