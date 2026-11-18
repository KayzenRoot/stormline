# NLE-PRPLAN-CORE-02-06 — Memory budget (INTERNAL_ONLY)

**STATUS: COMPLETED — implemented and merged via [PR #472](https://github.com/KayzenRoot/stormline/pull/472), merge `10ceaaeb…`. This packet must not be re-executed; no next packet or module is authorized.** **Gate:** G6 individual + capability admission. **Formal packet:** `NLE-PRPLAN-CORE-02-06`. **Predecessor:** `-05` `COMPLETED` via PR #469. **Issue:** #19. **Base:** `42ab4b74b686e9856c150101895a9e6182c964b5`. **ADR:** [ADR-0098](../adr/0098-core-02-memory-budget.md). **Contract:** [core-02-memory-budget-v0](../contracts/core-02-memory-budget-v0.md).

## OBJECTIVE

Implement deterministic soft/hard memory budget accounting with typed reserve/release, pressure status and owner-thread enforcement.

## CONTEXT

CORE-02-03/04/05 (ownership, system baseline, arena) are completed. ADR-0004 proposes soft/hard watermarks and reclaim hooks; SMF is research. This slice is the accounting primitive only, not allocation interception or telemetry.

## SCOPE

- `BudgetStatus`, `BudgetError`, `MemoryBudget`; soft/hard limits; atomic reserve/release; non-mutating hard rejection/underflow; owner-thread.
- Tests BGT-01..BGT-06; existing 80 CTests; Linux ASan/UBSan.

## OUT OF SCOPE

Allocation interception, SMF graph, reclaim hooks, telemetry, leak tracking, frame/job barriers, global budget, public ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADRs 0004/0086/0097/0098, CORE-02 architecture/contracts, arena/system/ownership code/tests, manifest/activation, CI evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-002/003/005; ADR-0004 proposed direction; ADR-0086 capability rule; ADR-0098 bounded slice.

## ARCHITECTURE RULES

Internal namespace/header; standard headers; no SDL/third-party; explicit budget instance; owner-thread; typed errors; no exception across API; no global/telemetry/interception.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`; no dependency/package/secret/paid service; standard CI; ADR-0004 `PROPOSED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; engine=false.

## ACCEPTANCE CRITERIA

- Exact allowlist; selector only `-06`.
- BGT-01..BGT-06; soft/hard transitions; non-mutating rejection/underflow; lifetime/wrong-thread.
- Existing 80 CTests; four CI jobs + ASan/UBSan.
- No interception/SMF/telemetry/global/ABI/release claim.
- Docs Validation + native CI; no HIGH/CRITICAL; pt-BR audit.

## TESTS

Docs validators + 64+ tests + selector. Native: `ctest -R core02_budget_`, full preset four jobs. Exact: `cmake --preset core01-internal-debug`, build, ctest, asan preset.

## DELIVERABLES

Exactly: `src/stormline/core/memory/memory_budget.hpp`, `.cpp`, `tests/core/memory_budget_tests.cpp`, additive `CMakeLists.txt`, additive workflow filters, `docs/evidence/NLE-PRPLAN-CORE-02-06.md`. PR, CI, Evidence, pt-BR audit, proposed checkpoint.

## REVIEW FORMAT

pt-BR: base/head, files, BGT matrix, limit/underflow/resource evidence, regression/sanitizer, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, gate not merged, selector blocked, regression, CI red, HIGH/CRITICAL, out-of-allowlist, interception/SMF/global/third-party/ABI/release overclaim, another packet. No bypass.

## CONTEXT LOCK

Gate base `42ab4b7…`; activation pins ADR/contract/source blobs and capability admission. Recompute after gate merge.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-02-06.md` with PR/CI/audit/merge SHAs, limit/underflow, regression, sanitizer, limitations, rollback.
