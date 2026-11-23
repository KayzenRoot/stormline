# NLE-PRPLAN-GFX-02-08 — Logical shader pipeline qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-02-08`. **Predecessor:** `GFX-02-07` incremental. **Issue:** #30. **Base:** `378c7af`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md).

## OBJECTIVE

Add CI-only qualification QLF-S01..S04 over the complete logical SSCL-0 pipeline: integrated flow, deterministic repeat, failure recovery and bounded overload.

## CONTEXT

GFX-02-01..07 are approved/completed. No native compiler, GPU or artifact exists.

## SCOPE

- `tests/core/gfx02_shader_qualification_tests.cpp`: QLF-S01..S04.
- Additive CMake target/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout (`-09`); native compiler/GPU/hardware, rendering, performance, ABI or release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0116, contract, governance contract, GFX-02-07 evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0116; QLF-S01..S04.

## ARCHITECTURE RULES

GFX-02 owns logical qualification; no native compiler/GPU; qualification does not imply hardware or ABI.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no compiler/GPU/persistence/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-S01..S04 pass.
- 10,000 parse/reflection/variant/cache/incremental attempts keep capacities.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-S01 integrated source→IR→reflection→variants→cache→incremental; QLF-S02 deterministic snapshot; QLF-S03 typed failure followed by valid operation; QLF-S04 10,000 bounded attempts.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-S01..S04, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, native compiler/GPU/performance claim, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `378c7af`; contract blob pinned in activation; GFX-02-07 merge `378c7af`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-02-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-02-08.md`.
