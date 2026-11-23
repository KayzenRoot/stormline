# NLE-PRPLAN-GFX-05-06 — Sampler and filter profiles (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-05-06`. **Predecessor:** `GFX-05-05` mips. **Issue:** #33. **Base:** `2ee232b`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md).

## OBJECTIVE

Implement bounded logical sampler/filter profile validation.

## CONTEXT

GFX-05-01/-05 are approved/completed. No GPU sampler, driver, upload, rendering or hardware path exists.

## SCOPE

- `texture_sampler.hpp` and SMP-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Decals, transparency, qualification; GPU/driver, texture upload, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0119, internal contract, texture/mip headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0119; SMP-01.

## ARCHITECTURE RULES

GFX-05 owns logical sampler profiles; no GPU sampler object or driver behavior is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/driver/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; SMP-01 valid/invalid fixtures.
- No GPU/driver/upload/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SMP-01: filter/wrap enums, LOD range/order, anisotropy power/range, comparison format, invalid enums.

## DELIVERABLES

Header, SMP tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SMP-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, GPU/driver selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `2ee232b`; contract blob pinned in activation; GFX-05-05 merge `2ee232b`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-05-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-05-06.md`.
