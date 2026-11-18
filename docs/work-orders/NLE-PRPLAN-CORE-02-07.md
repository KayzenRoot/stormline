# NLE-PRPLAN-CORE-02-07 — Leak tracking (INTERNAL_ONLY)

**STATUS: COMPLETED — implemented and merged via [PR #475](https://github.com/KayzenRoot/stormline/pull/475), merge `51af5bd2…`. This packet must not be re-executed; no next packet or module is authorized.** **Gate:** G6 individual + capability admission. **Formal packet:** `NLE-PRPLAN-CORE-02-07`. **Predecessor:** `-06` `COMPLETED` via PR #472. **Issue:** #19. **Base:** `74524e55237436a6b4501aab58b31e76cd1d5479`. **ADR:** [ADR-0099](../adr/0099-core-02-leak-tracking.md). **Contract:** [core-02-leak-tracking-v0](../contracts/core-02-leak-tracking-v0.md).

## OBJECTIVE

Implement deterministic, explicit leak tracking with generation-checked tokens, live/peak counters and owner-thread enforcement for caller-declared tracked allocations.

## CONTEXT

CORE-02-03/04/05/06 (ownership, system baseline, arena, budget) are completed. ADR-0004 requires leak detection in reproducible load, but early CORE-02 slices avoid process-global allocator interception. This slice is an opt-in bookkeeping primitive only, not instrumentation, pointer tracking or telemetry.

## SCOPE

- `LeakToken`, `LeakError`, `LeakTracker`; fixed capacity 128; explicit track/release; generation-checked stale/double-release rejection; live/peak counters; owner-thread.
- Tests LKT-01..LKT-06; existing 86 CTests; Linux ASan/UBSan.

## OUT OF SCOPE

Allocation interception, `new/delete`/`malloc` hooks, pointer-address maps, telemetry/export, reporting service, leak auto-diagnosis, SMF/reclaim, frame/job barriers, global tracker, public ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADRs 0004/0086/0098/0099, CORE-02 architecture/contracts, ownership/system/arena/budget code and tests, manifest/activation, CI evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-002/003/005; ADR-0004 proposed direction; ADR-0086 capability rule; ADR-0099 bounded slice.

## ARCHITECTURE RULES

Internal namespace/header; standard headers only; no SDL/third-party; explicit tracker instance; owner-thread; typed errors; no exception across API; no dynamic allocation inside the tracker; no pointer addresses; no global/telemetry/interception.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`; no dependency/package/secret/paid service; standard CI; ADR-0004 `PROPOSED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; engine=false.

## ACCEPTANCE CRITERIA

- Exact allowlist; selector only `-07`.
- LKT-01..LKT-06; capacity exhaustion/reuse; stale/forged/double-release rejection; lifetime/wrong-thread.
- Existing 86 CTests; four CI jobs + ASan/UBSan.
- No interception/pointer map/telemetry/global/ABI/release claim.
- Docs Validation + native CI; no HIGH/CRITICAL; pt-BR audit.

## TESTS

Docs validators + 66+ tests + selector. Native: `ctest -R core02_leak_`, full preset four jobs. Exact: `cmake --preset core01-internal-debug`, build, ctest, asan preset.

## DELIVERABLES

Exactly: `src/stormline/core/memory/leak_tracker.hpp`, `.cpp`, `tests/core/leak_tracker_tests.cpp`, additive `CMakeLists.txt`, additive workflow filters, `docs/evidence/NLE-PRPLAN-CORE-02-07.md`. PR, CI, Evidence, pt-BR audit, proposed checkpoint.

## REVIEW FORMAT

pt-BR: base/head, files, LKT matrix, capacity/token/reuse evidence, regression/sanitizer, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, gate not merged, selector blocked, regression, CI red, HIGH/CRITICAL, out-of-allowlist, interception/pointer-map/global/third-party/ABI/release overclaim, another packet. No bypass.

## CONTEXT LOCK

Gate base `74524e5…`; activation pins ADR/contract/source blobs and capability admission. Recompute after gate merge.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-02-07.md` with PR/CI/audit/merge SHAs, capacity/token/reuse, regression, sanitizer, limitations, rollback.
