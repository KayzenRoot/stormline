# NLE-PRPLAN-CORE-02-09 — Integrated memory qualification (INTERNAL_ONLY)

**STATUS: EXECUTOR_READY ONLY AFTER THE GATE PR PASSES DOCS VALIDATION, PT-BR AUDIT AND SQUASH MERGE.** **Gate:** G6 individual + capability admission. **Formal packet:** `NLE-PRPLAN-CORE-02-09`. **Predecessor:** `-08` `COMPLETED` via PR #484. **Issue:** #19. **Base:** `a20ff42cce2879657d357a52a9ba80052b9f7c02`. **ADR:** [ADR-0101](../adr/0101-core-02-integrated-memory-qualification.md). **Contract:** [core-02-integrated-memory-qualification-v0](../contracts/core-02-integrated-memory-qualification-v0.md).

## OBJECTIVE

Qualify the approved CORE-02 memory primitives together under deterministic integrated load, stress, overflow/recovery and size churn, with report-only timing and no invented thresholds.

## CONTEXT

CORE-02-03..08 delivered ownership, system baseline, arena, budget, leak tokens and opt-in telemetry. `-09` is the planned integrated qualification of this internal scope. The owner authorized CORE-02-08/-09/-10 sequentially, each requiring its own gate. This packet is test-only.

## SCOPE

- New test executable with QLF-01 integrated, QLF-02 stress 10,000, QLF-03 recovery, QLF-04 size-churn 2,000+, QLF-05 report-only benchmark.
- Integration of `SystemMemoryResource`, `MemoryBlock`, `MonotonicArena`, `MemoryBudget`, `LeakTracker` and `MemoryTelemetry`.
- Existing 105 Linux / 104 Windows/macOS CTests; Linux ASan/UBSan.

## OUT OF SCOPE

Production code changes, performance thresholds, p95/RSS/VRAM/fragmentation metrics, OS memory scanning, allocator comparison/selection, global interception, export, public ABI, release, physical hardware qualification.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADRs 0004/0086/0100/0101, CORE-02 architecture/contracts, all CORE-02 source/tests, manifest/activation, CI evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-002/003/005; ADR-0004 proposed direction; ADR-0086 capability rule; ADR-0101 test-only slice.

## ARCHITECTURE RULES

Test-only; standard headers; no SDL/third-party; explicit instances; deterministic oracles; no production API; no threshold; no global/export/interception.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`; no dependency/package/secret/paid service; standard CI; ADR-0004 `PROPOSED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; engine=false.

## ACCEPTANCE CRITERIA

- Exact allowlist; selector only `-09`.
- QLF-01..QLF-05; stress and recovery invariants; size churn; report-only benchmark.
- Existing CTests; four CI jobs + ASan/UBSan.
- No production-code/threshold/fragmentation/OS-memory/ABI/release claim.
- Docs Validation + native CI; no HIGH/CRITICAL; pt-BR audit.

## TESTS

Docs validators + 70+ tests + selector. Native: `ctest -R core02_qualification_`, full preset four jobs. Exact: `cmake --preset core01-internal-debug`, build, ctest, asan preset.

## DELIVERABLES

Exactly: `tests/core/core02_memory_qualification_tests.cpp`, additive `CMakeLists.txt`, additive workflow filters, `docs/evidence/NLE-PRPLAN-CORE-02-09.md`. PR, CI, Evidence, pt-BR audit, proposed checkpoint.

## REVIEW FORMAT

pt-BR: base/head, files, QLF matrix, stress/recovery evidence, report-only benchmark, regression/sanitizer, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, gate not merged, selector blocked, regression, CI red, HIGH/CRITICAL, out-of-allowlist, threshold/fragmentation/OS-memory/ABI/release overclaim, production change, another packet. No bypass.

## CONTEXT LOCK

Gate base `a20ff42…`; activation pins ADR/contract/source blobs and capability admission. Recompute after gate merge.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-02-09.md` with PR/CI/audit/merge SHAs, QLF matrix, stress/recovery data, benchmark, regression, sanitizer, limitations, rollback.
