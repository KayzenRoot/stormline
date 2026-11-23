# NLE-PRPLAN-GFX-07-07 — Optional motion blur planning (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-07-07`. **Predecessor:** `GFX-07-06` reconstruction. **Issue:** #35. **Base:** `f272c66`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md).

## OBJECTIVE

Implement bounded logical motion-blur enable/shutter policy with reduced-motion opt-out.

## CONTEXT

GFX-07-01/-06 are approved/completed. No motion vectors, blur shader, GPU or render exists.

## SCOPE

- `motion_blur.hpp` and MBL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Upscale, qualification; blur/velocity sampling, GPU, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0121, internal contract, post headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0121; MBL-01.

## ARCHITECTURE RULES

GFX-07 owns logical blur policy; no motion vector is generated or sampled.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/velocity/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; MBL-01 valid/invalid fixtures.
- No blur/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

MBL-01: enable/disable, reduced motion, shutter/velocity bounds, unsupported enable.

## DELIVERABLES

Header, MBL tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, MBL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, GPU/blur selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `f272c66`; contract blob pinned in activation; GFX-07-06 merge `f272c66`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-07-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-07-07.md`.
