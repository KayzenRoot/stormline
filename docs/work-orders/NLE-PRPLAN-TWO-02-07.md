# NLE-PRPLAN-TWO-02-07 — Streaming plan metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-02-07`. **Predecessor:** `TWO-02-06` parallax. **Issue:** #38. **Base:** `fa66e50`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md).

## OBJECTIVE

Implement bounded logical chunk streaming admission metadata with visible/prefetch/request/byte budgets.

## CONTEXT

TWO-02-01/-06 are approved/completed. No file, cache, async job, residency mutation, GPU or render exists.

## SCOPE

- `streaming_plan.hpp` and STR-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; streaming I/O, cache, async jobs, residency, GPU, render, physics, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0124, internal contract, DATA-05/GFX-03 boundaries.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0124; STR-01.

## ARCHITECTURE RULES

TWO-02 owns logical streaming admission; DATA-05/GFX-03 own I/O/cache/resources; no residency mutation.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no I/O/cache/async/GPU/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; STR-01 valid/invalid fixtures.
- No I/O/cache/async/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

STR-01 IDs, budget clamps, failed count, degraded receipt.

## DELIVERABLES

Header, STR tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, STR-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, I/O/cache/GPU/physics selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `fa66e50`; contract blob pinned in activation; TWO-02-06 merge `fa66e50`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-02-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-02-07.md`.
