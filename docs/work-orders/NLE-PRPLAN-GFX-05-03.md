# NLE-PRPLAN-GFX-05-03 — Logical PBR material validation (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-05-03`. **Predecessor:** `GFX-05-02` contract. **Issue:** #33. **Base:** `6e51af6`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md).

## OBJECTIVE

Implement bounded PBR/material parameter validation and deterministic material-set insertion.

## CONTEXT

GFX-05-01/-02 are approved. No native GPU, texture upload, codec, submission or renderer exists.

## SCOPE

- `material_types.hpp`, `pbr_material.hpp` and PBR-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Textures/pages, mips, samplers, decals, transparency, qualification; native GPU/codec, upload, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0119, internal contract, governance contract.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0119; PBR-01.

## ARCHITECTURE RULES

GFX-05 owns logical PBR/material semantics; no native GPU/codec; no pixels or BRDF evaluation.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/texture codec/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; PBR-01 valid/invalid fixtures.
- No native GPU/codec/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

PBR-01: add/duplicate/capacity, finite/range/model/alpha/cutoff and atomic failure.

## DELIVERABLES

Headers, PBR tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, PBR-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/codec, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `6e51af6`; contract blob pinned in activation; GFX-05-02 merge `6e51af6`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-05-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-05-03.md`.
