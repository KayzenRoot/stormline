# NLE-PRPLAN-GFX-05-08 — Transparency sort and overdraw budget (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-05-08`. **Predecessor:** `GFX-05-07` decals. **Issue:** #33. **Base:** `63836fa`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md).

## OBJECTIVE

Implement bounded deterministic transparency sorting and overdraw budget validation.

## CONTEXT

GFX-05-01/-07 are approved/completed. No blending, GPU, render or frame timing exists.

## SCOPE

- `transparency.hpp` and TRN-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; blending, GPU, render, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0119, internal contract, material types.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0119; TRN-01.

## ARCHITECTURE RULES

GFX-05 owns logical transparency ordering/overdraw metadata; no blend or GPU operation.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/codec/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; TRN-01 valid/invalid fixtures.
- No blending/GPU/render/performance claim.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

TRN-01: alpha/blend/depth-write validity, back-to-front order, stable tie, budget/overdraw and capacity.

## DELIVERABLES

Header, TRN tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TRN-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, GPU/blending selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `63836fa`; contract blob pinned in activation; GFX-05-07 merge `63836fa`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-05-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-05-08.md`.
