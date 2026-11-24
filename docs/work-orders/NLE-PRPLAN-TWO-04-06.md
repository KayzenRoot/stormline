# NLE-PRPLAN-TWO-04-06 — Hybrid effect bridge intent (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-04-06`. **Predecessor:** `TWO-04-05` sorting. **Issue:** #40. **Base:** `156c857`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md).

## OBJECTIVE

Implement bounded logical hybrid effect bridge metadata: lit/shadow intent, subview extents/recursion and fallback receipts.

## CONTEXT

TWO-04-01..-05 are approved. No renderer, GPU, lights, shadows, subview execution or editor exists.

## SCOPE

- `effect_plan.hpp` and EFE-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; renderer, GPU, lighting/shadow evaluation, subview execution, editor, audio, export, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0126, internal contract, sort boundary.

## REQUIREMENTS

GOV-001..007; ADR-0126; EFE-01.

## ARCHITECTURE RULES

TWO-04 owns logical effect bridge intent; GFX-06 lighting/shadows and GFX-03/07 subview execution remain authoritative.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no render/GPU/lighting/subview/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; EFE-01 valid/invalid fixtures.
- No renderer, lighting, shadow or subview execution.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

EFE-01 lit/shadow counts, unique IDs, fallback enum, subview extent/depth bounds, capacity, reset and determinism.

## DELIVERABLES

Header, EFE tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, EFE-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, render/lighting/shadow/subview selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `156c857`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-04-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-04-06.md`.
