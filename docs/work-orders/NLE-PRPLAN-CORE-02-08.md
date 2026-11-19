# NLE-PRPLAN-CORE-02-08 — Memory telemetry (INTERNAL_ONLY)

**STATUS: EXECUTOR_READY ONLY AFTER THE GATE PR PASSES DOCS VALIDATION, PT-BR AUDIT AND SQUASH MERGE.** **Gate:** G6 individual + capability admission. **Formal packet:** `NLE-PRPLAN-CORE-02-08`. **Predecessor:** `-07` `COMPLETED` via PR #475. **Issue:** #19. **Base:** `dd76fceb6b9e835dd505c24a3c89065317528440`. **ADR:** [ADR-0100](../adr/0100-core-02-memory-telemetry.md). **Contract:** [core-02-memory-telemetry-v0](../contracts/core-02-memory-telemetry-v0.md).

## OBJECTIVE

Implement deterministic in-process memory telemetry with per-domain allocation/release counters, live/peak/cumulative accounting, typed underflow rejection and optional integration with the existing block, arena, budget and leak primitives.

## CONTEXT

CORE-02-03/04/05/06/07 delivered ownership, system baseline, arena, budget and explicit leak tokens. ADR-0004/architecture describe future memory snapshots but no global interception or export is approved. This slice is a bounded counter/hook primitive only. A CORE-01 gaps audit found no NECESSARY code increment executable without physical hardware, owner ratification or release decisions; CORE-02 capability admission remains valid.

## SCOPE

- `MemoryTelemetry`, `TelemetryError`, per-domain and aggregate snapshots; atomics; peak/cumulative counters; typed zero/invalid-domain/underflow rejection.
- Optional default-null hooks in `MemoryBlock`, `MonotonicArena`, `MemoryBudget` and `LeakTracker`.
- Tests TLM-01..TLM-06, including concurrency and report-only benchmark; existing 99 Linux / 98 Windows/macOS CTests; Linux ASan/UBSan.

## OUT OF SCOPE

Global allocation interception, `new/delete`/`malloc` hooks, pointer/call-site capture, timestamps/frame IDs, sampling thread, I/O/export/HTTP/Tracy, SMF/reclaim, frame/job barriers, budgets/leaks redesign, public ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADRs 0004/0086/0099/0100, CORE-02 architecture/contracts, ownership/system/arena/budget/leak code and tests, manifest/activation, CI evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-002/003/005; ADR-0004 proposed direction; ADR-0086 capability rule; ADR-0100 bounded slice.

## ARCHITECTURE RULES

Internal namespace/header; standard headers only; no SDL/third-party; explicit telemetry instance; atomics for counters; no dynamic allocation; no pointer addresses; no global/export/interception; instrumentation opt-in and default-off.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`; no dependency/package/secret/paid service; standard CI; ADR-0004 `PROPOSED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; engine=false; no latency threshold ratified.

## ACCEPTANCE CRITERIA

- Exact allowlist; selector only `-08`.
- TLM-01..TLM-06; per-domain and aggregate invariants; underflow/invalid input; integration hooks; concurrency final invariants; benchmark report-only.
- Existing CTests; four CI jobs + ASan/UBSan.
- No interception/export/pointer/global/ABI/release claim.
- Docs Validation + native CI; no HIGH/CRITICAL; pt-BR audit.

## TESTS

Docs validators + 68+ tests + selector. Native: `ctest -R core02_telemetry_`, full preset four jobs. Exact: `cmake --preset core01-internal-debug`, build, ctest, asan preset.

## DELIVERABLES

Exactly: new telemetry header/cpp/tests, additive hooks in existing memory files, additive `CMakeLists.txt`, additive workflow filters, `docs/evidence/NLE-PRPLAN-CORE-02-08.md`. PR, CI, Evidence, pt-BR audit, proposed checkpoint.

## REVIEW FORMAT

pt-BR: base/head, files, TLM matrix, concurrency/benchmark evidence, regression/sanitizer, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, gate not merged, selector blocked, regression, CI red, HIGH/CRITICAL, out-of-allowlist, interception/export/pointer/global/third-party/ABI/release overclaim, another packet. No bypass.

## CONTEXT LOCK

Gate base `dd76fce…`; activation pins ADR/contract/source blobs and capability admission. Recompute after gate merge.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-02-08.md` with PR/CI/audit/merge SHAs, TLM matrix, concurrency/benchmark data, regression, sanitizer, limitations, rollback.
