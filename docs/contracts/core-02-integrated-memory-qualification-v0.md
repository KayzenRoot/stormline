# CORE-02 INTERNAL_ONLY Integrated Memory Qualification Contract v0 (NLE-PRPLAN-CORE-02-09)

**Status:** `CONTRACT PROPOSAL / TEST-ONLY / NOT IMPLEMENTED / NO THRESHOLDS`. **Base:** `a20ff42cce2879657d357a52a9ba80052b9f7c02`. **ADR:** [ADR-0101](../adr/0101-core-02-integrated-memory-qualification.md). **WO:** [NLE-PRPLAN-CORE-02-09](../work-orders/NLE-PRPLAN-CORE-02-09.md).

## Objective and bounded scope

Qualify the approved CORE-02 internal memory primitives together under deterministic integrated load, stress, overflow/recovery and size churn, with report-only timing. No production API, threshold, allocator selection, global interception, export, public ABI or release qualification is added.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`.

## Test executable and modes

New test-only executable `core02_memory_qualification_test` with exactly five modes:

### QLF-01 `integrated`

Deterministic sequence using one `SystemMemoryResource`, one `MemoryTelemetry`, `MemoryBlock` in Persistent/Job/Streaming, one `MonotonicArena` (backing 64 KiB), one `MemoryBudget` (soft 4 KiB / hard 16 KiB), one `LeakTracker` and fresh tokens:

1. allocate/release blocks of 64/128/256 bytes with 8/16/64-byte alignment;
2. allocate arena slices with alignment, reset and reuse;
3. reserve to soft pressure, reserve to hard limit, reject one excess reserve, release everything;
4. track/release leak tokens, including slot reuse;
5. snapshot telemetry and assert per-domain/aggregate live/cumulative/peak invariants;
6. assert `telemetry.empty()`, `leak.empty()`, `budget.used()==0`, arena `used()==0`.

Any counter mismatch, underflow, wrong status or residual live state fails.

### QLF-02 `stress`

10,000 deterministic iterations mixing:

- block allocate/release (sizes cycling 32..4096, alignments 8/16/64);
- arena slice allocate, periodic reset and reuse;
- budget reserve/release inside hard limit;
- leak track/release with a bounded live set;
- telemetry allocation/release pairs.

After the loop: all blocks released, arena reset, budget used 0, leak empty, telemetry live 0; cumulative allocation/release counters balanced; no error observed. The test must finish within the existing 180 s CTest timeout and must not allocate unbounded memory.

### QLF-03 `recovery`

- Arena: fill to near capacity, force `OutOfMemory`, assert state unchanged, `reset`, allocate again successfully.
- Budget: reserve to hard, reject excess, assert non-mutation, release, reserve again.
- Leak: fill capacity, reject extra, release one, reuse slot with new generation, reject stale token.
- Telemetry: release without allocation and above live bytes returns `ReleaseUnderflow` without mutation, then valid operations resume.
No crash, corruption, silent clamp or counter drift.

### QLF-04 `size-churn`

Deterministic allocation/release of at least 2,000 `MemoryBlock`s with varied sizes (1..4096) and alignments, interleaved free patterns, using `SystemMemoryResource` and telemetry. Final state has zero live blocks and balanced counters. This is **size churn**, not a fragmentation measurement; no fragmentation estimate or threshold is claimed.

### QLF-05 `benchmark`

Fixed integrated loop (blocks + arena + budget + leak + telemetry), repeated enough for a stable local sample; prints `CORE02_QUAL_BENCH_NS_PER_ITER=<value> iterations=<n>` and validates final invariants. Timing is report-only; no CI gate or performance PASS.

## Test oracles

| ID | Oracle |
|---|---|
| QLF-01 | all counters/states exact after deterministic integrated sequence |
| QLF-02 | 10,000 mixed iterations complete; all live states drain; cumulative balanced |
| QLF-03 | OOM/overflow/capacity/stale/underflow recover without mutation or corruption |
| QLF-04 | 2,000+ size-churn allocations release to zero live telemetry state |
| QLF-05 | report-only timing printed; final invariants hold; no threshold |

No OS RSS, VRAM, fragmentation estimator, p95 threshold, sanitizer-free guarantee or process-wide leak claim.

## Exact implementation allowlist for packet -09

1. `tests/core/core02_memory_qualification_tests.cpp`
2. `CMakeLists.txt` (additive qualification target and five CTests only)
3. `.github/workflows/core01-internal-headless.yml` (additive CORE-02-09 path filters only)
4. `docs/evidence/NLE-PRPLAN-CORE-02-09.md`

`docs/work-orders/NLE-PRPLAN-CORE-02-09.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No production source, ADR, contract, manifest, registry, G2, license or other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, regression, CI red, HIGH/CRITICAL, out-of-allowlist change, performance threshold/fragmentation/OS-memory overclaim, or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or release. `NLE-D009 OPEN`.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0004 `PROPOSED`; ADR-0101 bounded; G3 global `NOT_CLEARED`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -09 remains blocked until then.**
