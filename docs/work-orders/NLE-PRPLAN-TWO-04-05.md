# NLE-PRPLAN-TWO-04-05 — Deterministic sort intent (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-04-05`. **Predecessor:** `TWO-04-04` layers. **Issue:** #40. **Base:** `8a118c7`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md).

## OBJECTIVE

Implement bounded deterministic logical sort intent over layer order, depth key and tie-breaker.

## CONTEXT

TWO-04-01..-04 are approved. No renderer, GPU sort or draw list exists.

## SCOPE

- `sort_plan.hpp` and SRT-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Effects, qualification, closeout; renderer, GPU sort, draw list, depth attachment, matrix, lighting, editor, audio, export, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0126, internal contract, layer boundary.

## REQUIREMENTS

GOV-001..007; ADR-0126; SRT-01.

## ARCHITECTURE RULES

TWO-04 owns logical sort intent; no GPU sort, draw submission or painter implementation is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no render/GPU/draw/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; SRT-01 valid/invalid fixtures.
- No renderer, GPU sort, effects or draw list.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SRT-01 stable order, layer/depth/tie precedence, duplicates, capacity, reset and determinism.

## DELIVERABLES

Header, SRT tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SRT-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, render/GPU/draw selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `8a118c7`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-04-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-04-05.md`.
