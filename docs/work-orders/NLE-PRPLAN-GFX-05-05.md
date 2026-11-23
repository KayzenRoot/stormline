# NLE-PRPLAN-GFX-05-05 — Texture mip metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-05-05`. **Predecessor:** `GFX-05-04` texture metadata. **Issue:** #33. **Base:** `bd28227`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md).

## OBJECTIVE

Implement bounded mip-chain metadata derivation with checked dimensions and byte sizes.

## CONTEXT

GFX-05-01/-04 are approved/completed. No image decoder, mip generator, upload, GPU or renderer exists.

## SCOPE

- `texture_mip.hpp` and MIP-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Samplers, decals, transparency, qualification; image decode/mip generation, GPU/codec, upload, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0119, internal contract, texture header.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0119; MIP-01.

## ARCHITECTURE RULES

GFX-05 owns logical mip metadata; no image decode or mip generation; no native GPU/codec.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/image codec/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; MIP-01 valid/invalid fixtures.
- No image codec/generation/upload.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

MIP-01: derived dimensions/bytes per format, capped max levels, invalid levels/format and checked overflow.

## DELIVERABLES

Header, MIP tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, MIP-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/codec, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `bd28227`; contract blob pinned in activation; GFX-05-04 merge `bd28227`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-05-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-05-05.md`.
