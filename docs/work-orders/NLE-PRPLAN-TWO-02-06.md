# NLE-PRPLAN-TWO-02-06 — Parallax metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-02-06`. **Predecessor:** `TWO-02-05` collision shapes. **Issue:** #38. **Base:** `bd1fe04`. **ADR:** [ADR-0124](../adr/0124-two-02-internal-tilemap-pipeline.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md).

## OBJECTIVE

Implement bounded logical parallax factors/repeat metadata.

## CONTEXT

TWO-02-01/-05 are approved/completed. No parallax render transform, GPU or render exists.

## SCOPE

- `parallax_plan.hpp` and PRX-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; render transforms, scrolling, GPU, render, importer, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0124, internal contract, TWO-01 camera boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0124; PRX-01.

## ARCHITECTURE RULES

TWO-02 owns logical parallax metadata; no render transform or scroll is executed.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/render/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; PRX-01 valid/invalid fixtures.
- No transform/scroll/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

PRX-01 IDs, factors bounds/finitude, repeat flags.

## DELIVERABLES

Header, PRX tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, PRX-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, render/GPU/importer selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `bd1fe04`; contract blob pinned in activation; TWO-02-05 merge `bd1fe04`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-02-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-02-06.md`.
