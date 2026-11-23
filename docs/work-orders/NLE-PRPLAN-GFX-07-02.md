# NLE-PRPLAN-GFX-07-02 — Camera/color/post contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no code authorized.** **Formal packet:** `NLE-PRPLAN-GFX-07-02`. **Predecessor:** `GFX-07-01` governance. **Issue:** #35. **Base:** `d049446`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Contract:** [gfx-07-post-processing-internal-v0](../contracts/gfx-07-post-processing-internal-v0.md).

## OBJECTIVE

Freeze the exact internal GFX-07 API, capacities, validation rules, deterministic fallbacks, errors and per-slice allowlists for camera/exposure, tone/color, HDR output, reconstruction, motion blur and upscale.

## CONTEXT

GFX-07-01 approved ADR-0121. GFX-06 completed its internal sequence. No native GPU, swapchain, HDR signal, tone mapper, LUT/OCIO runtime, TAA, vendor SDK, dependency, ABI or release is authorized.

## SCOPE

- `docs/contracts/gfx-07-post-processing-internal-v0.md`.
- WO, G6 evidence, activation JSON, manifest/validator/test/checkpoint updates.

## OUT OF SCOPE

Implementation `-03`..`-09`, closeout, native GPU/display/SDK, tone mapping, AA, blur, upscale, rendering, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0020/0086/0121, GFX-07 architecture/API, GFX-07 governance contract, GFX-06 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0121; exact API and CAM/EXP/COL/HDR/RCN/MBL/UPS/QLF-G7 oracles.

## ARCHITECTURE RULES

GFX-07 owns logical post plans only; GFX-01/02/03/04/05/06 and DATA boundaries unchanged; no backend/display/SDK resource.

## CONSTRAINTS

Risk `LOW` contract; `INTERNAL_ONLY`; no GPU/display/SDK/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract exact and complete; manifest root `GFX07_02_APPROVED_CONTRACT_ONLY`.
- No code, dependency, native GPU/display/SDK or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; future oracles are declared but not executed in this packet.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/display/SDK selection, incomplete API, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `d049446`; governance merge `d049446`; contract blob pinned after this gate.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-07-02-G6-ACTIVATION.md`.
