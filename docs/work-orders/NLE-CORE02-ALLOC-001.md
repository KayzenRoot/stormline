# NLE-CORE02-ALLOC-001 — Isolated allocator benchmark harness (INTERNAL_ONLY)

**STATUS: OWNER-RATIFIED Q1/Q2/Q3/Q4/Q7 — implementation authorized only for the isolated harness. NO DEFAULT ALLOCATOR SELECTION, NO PRODUCTION INTEGRATION, NO RELEASE.** **Base:** `358bca21352df5a0ccf7380c2f40472e8e8f031e`. **ADR:** [ADR-0104](../adr/0104-core-02-allocator-benchmark.md). **Contract:** [core-02-allocator-benchmark-v0](../contracts/core-02-allocator-benchmark-v0.md). **Issue:** #19.

## OBJECTIVE

Implement and run an optional, isolated benchmark harness comparing baseline allocators with pinned mimalloc 3.7.0 and rpmalloc 2.0.1, preserving baseline defaults and producing report-only evidence.

## CONTEXT

Owner ratification 2026-11-19: Q1=A (ADR-0004 planning direction), Q2=B (baseline default; isolated mimalloc/rpmalloc harness), Q3=A (`REPORT_ONLY`), Q4=B (physical matrix G1-M04/M05), Q7=A (NLE-D009 OPEN). CORE-02 remains NOT_QUALIFIED. No allocator is selected.

## SCOPE

- Optional `stormline_core02_allocator_bench` target behind `STORMLINE_CORE02_ALLOC_BENCH=OFF`.
- Pinned mimalloc v3.7.0 commit and rpmalloc 2.0.1 commit; MIT notices; no override.
- Correctness, fixed-size, 4-thread and aligned comparisons; report-only output.
- Additive CMake preset and isolated CI job on Linux/Windows/macOS.
- Physical Q4 execution remains NOT_RUN until owner-provided machines are available.

## OUT OF SCOPE

Default/global allocator replacement, production integration, public API, thresholds/winner/speedup, RSS/p95/p99 physical claims, SMF, release, license decision, registry/manifest changes, CORE-03.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0004/0104, CORE-02 architecture/contracts/evidence, Q1/Q2/Q3/Q4/Q7 ratification, CMake/CI, allocator upstream licenses/CMake/API.

## REQUIREMENTS

Q1=A, Q2=B, Q3=A, Q4=B, Q7=A; ADR-0004 planning direction; ADR-0086 capability boundary; ADR-0104 contract; GOV-001..005/CAP-009/NFR-002/003.

## ARCHITECTURE RULES

Isolated benchmark executable; explicit allocator APIs; no global override; no third-party type in engine API; baseline default untouched; optional target only.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`; no paid service/secrets; pinned licenses/commits; CI report-only; no physical/performance PASS; no allocator selection; no manifest/registry change.

## ACCEPTANCE CRITERIA

- Exact allowlist; option OFF builds/tests unchanged.
- Correctness for all allocators/sizes/alignment; no null/alignment/read-write failure.
- Report-only output per allocator/size/threads; no threshold/winner.
- CI isolated job PASS on Linux/Windows/macOS; physical Q4 NOT_RUN.
- No HIGH/CRITICAL; pt-BR audit; Evidence Bundle.

## TESTS

Default 110/109 CTests unchanged with option OFF; isolated `ctest -R core02_allocator_bench -V` on three OS; correctness modes; benchmark output inspected.

## DELIVERABLES

ADR/contract/WO/benchmark source/CMake/preset/workflow/legal notice/Evidence. PR, CI, audit, squash merge, independent checkpoint/readback.

## REVIEW FORMAT

pt-BR: base/head, files, pinned deps/licenses, correctness, report-only outputs, regression, no selection/overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, missing ratification, global override, production integration, unpinned/unlicensed dependency, correctness failure, CI red, HIGH/CRITICAL, threshold/winner/physical claim, manifest/registry change. No merge without audit.

## CONTEXT LOCK

Base `358bca2…`; activation pins ADR/contract/source blobs and allocator commits.

## EVIDENCE BUNDLE

`docs/evidence/NLE-CORE02-ALLOC-001.md` with SHAs, dependency pins/licenses, commands, outputs, correctness, CI runs, limitations, physical matrix NOT_RUN, rollback.
