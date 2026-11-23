# NLE-PRPLAN-GFX-05-04 — Texture metadata and virtual pages (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-05-04`. **Predecessor:** `GFX-05-03` PBR. **Issue:** #33. **Base:** `2dc4475`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md).

## OBJECTIVE

Implement bounded texture metadata validation and deterministic virtual-page request planning.

## CONTEXT

GFX-05-01/-03 are approved/completed. No native GPU, codec, upload, residency service, submission or renderer exists.

## SCOPE

- `virtual_texture.hpp` and VTX-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Mips, samplers, decals, transparency, qualification; native GPU/codec, upload, residency, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0119, internal contract, texture/PBR headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0119; VTX-01.

## ARCHITECTURE RULES

GFX-05 owns logical texture/page metadata; DATA-03 owns source import; no native GPU/codec/residency.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/texture codec/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; VTX-01 valid/invalid fixtures.
- No native GPU/codec/upload/residency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

VTX-01: add/duplicate/dimensions/levels/format/color use, page bounds/duplicates/resident skip/budget/truncation/overflow.

## DELIVERABLES

Header, VTX tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, VTX-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/codec, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `2dc4475`; contract blob pinned in activation; GFX-05-03 merge `2dc4475`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-05-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-05-04.md`.
