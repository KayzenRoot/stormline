# CORE-03 INTERNAL_ONLY Qualification Contract v0 (NLE-PRPLAN-CORE-03-09)

**Status:** `CONTRACT PROPOSAL / TEST-ONLY / NO PRODUCTION CODE AUTHORIZED`. **Base:** `6a3f245b3647b4b708b239147ec3c666fa5fef2c`. **ADR:** [ADR-0105](../adr/0105-core-03-limited-capability-admission.md). **WO:** [NLE-PRPLAN-CORE-03-09](../work-orders/NLE-PRPLAN-CORE-03-09.md).

## Objective

Qualify the already implemented CORE-03 task graph and executor together under deterministic integrated load, stress, recovery/overload and report-only timing. This contract authorizes a test-only executable and no production change.

## Admission and boundaries

- Formal `CORE-02` dependency remains; admission is limited to completed `CORE-02-03..09` capabilities under NLE-D022/D2. CORE-02 module completion is **not** claimed.
- CORE-03-03 remains the production implementation; this contract adds no API, type, dependency, ABI or release.
- No third-party scheduler appears in the qualification matrix.

## Qualification matrix

| ID | Scenario | Oracle |
|---|---|---|
| QLF-01 | Integrated functionality | mixed priorities, dependencies, MainThread, cancellation and commits across multiple jobs; all waits and stats balanced |
| QLF-02 | Stress | at least 10,000 tasks across at least 100 bounded jobs on 8 workers; every fence completes; no deadlock or lost task |
| QLF-03 | Recovery | cancellation storm, invalid graphs, queue overflow and executor replacement after stop; typed errors and no hang |
| QLF-04 | Overload/backpressure | bounded queue rejects with `QueueFull` without mutation; smaller work succeeds afterwards |
| QLF-05 | Benchmark/report-only | enqueue-to-completion timing and throughput printed; no threshold, ranking or speedup claim |

## Exact implementation allowlist

1. `tests/core/core03_jobs_qualification_tests.cpp`
2. `CMakeLists.txt` (additive CORE-03 qualification target/tests)
3. `.github/workflows/core01-internal-headless.yml` (additive CORE-03 qualification filters/target)
4. `docs/evidence/NLE-PRPLAN-CORE-03-09.md`

No production source, dependency, public ABI, release, allocator or technology change is authorized.

## Semantics

- All tests use only the public CORE-03 API and standard library.
- The stress matrix may reuse a finalized graph; each submission is independent.
- Invalid graphs and queue overflow must return typed errors without executing tasks.
- A stopped executor is not restarted; recovery creates a fresh executor.
- Benchmark numbers are observations, not thresholds.

## Stop / rollback / security

Stop on stale source, missing D2 admission, production change outside allowlist, test-only violation, deadlock, race, leak, unbounded queue, release/ABI/threshold overclaim, HIGH/CRITICAL. Unmerged: close the branch; after merge: normal revert PR, never force push.

`CORE-03-09` remains `PLANNED_BLOCKED` until its individual G6 activation. `CORE-03-10` remains blocked.
