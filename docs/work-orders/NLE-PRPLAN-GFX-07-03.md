# NLE-PRPLAN-GFX-07-03 — Logical camera and exposure (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-07-03`. **Predecessor:** `GFX-07-02` contract. **Issue:** #35. **Base:** `6ad7a83`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md).

## OBJECTIVE

Implement bounded logical camera/projection and exposure validation/planning.

## CONTEXT

GFX-07-01/-02 are approved. No GPU, swapchain, projection matrix, histogram or renderer exists.

## SCOPE

- `post_types.hpp`, `camera_exposure.hpp` and CAM-01/EXP-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Tone/color, HDR output, reconstruction, motion blur, upscale, qualification; GPU/display, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0121, internal contract, GFX-06 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0121; CAM-01/EXP-01.

## ARCHITECTURE RULES

GFX-07 owns logical camera/exposure plans; no matrix inversion, image histogram or GPU resource is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/display/histogram/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; CAM-01/EXP-01 valid/invalid fixtures.
- No GPU/projection matrix/histogram/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

CAM-01: add/duplicate/capacity, perspective/ortho, near/far/aspect/dims/jitter/generation.
EXP-01: manual/auto, EV range, adapt times, percentiles, flash.

## DELIVERABLES

Headers, tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CAM-01/EXP-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, GPU/display selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `6ad7a83`; contract blob pinned in activation; GFX-07-02 merge `6ad7a83`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-07-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-07-03.md`.
