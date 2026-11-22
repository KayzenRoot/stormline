# NLE-PRPLAN-CORE-06-05 — counters evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `dead9f9`. **Gate:** [NLE-PRPLAN-CORE-06-05-G6-ACTIVATION](NLE-PRPLAN-CORE-06-05-G6-ACTIVATION.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md). **WO:** [NLE-PRPLAN-CORE-06-05](../work-orders/NLE-PRPLAN-CORE-06-05.md).

## Scope delivered

- `src/stormline/core/diag/counter.hpp`: `CounterUnit`, `CounterSample`, finite/nonzero validation, fixed 64-slot `CounterSet`.
- `tests/core/core06_counter_tests.cpp`: COUNTER-01.
- Additive CMake target/test and workflow TSan target list.

No crash, profiling, telemetry, network/file I/O, third-party metrics, serialization, ABI or release.

## Implementation notes

- `make_counter_sample` rejects invalid build, negative time, zero counter ID and non-finite value.
- `CounterSet::record` updates an existing ID in place, otherwise appends; capacity 64 with `dropped` and `BufferFull`.
- `find` returns false for absent IDs; no allocation, file or network.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core06_counter_tests.cpp -o /tmp/core06_counter_test
/tmp/core06_counter_test counter01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed here before the exact-head run. No benchmark, hardware, metrics backend or performance result exists.

## Errors and corrections

No production or test correction was needed after local compile/test.

## Security and architecture

- Header-only internal C++20; no exception, dynamic allocation, platform API, file I/O, network or dependency.
- CORE-06 owns counter values/local set; CORE-01/02/03/04 and GFX/AUD/DATA/EDIT boundaries unchanged.
- No secret, paid service or mutable global state.

## Rollback

Revert this PR normally; remove `counter.hpp`, the counter test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No metrics backend, export, serialization, cardinality policy, sampling, aggregation window or cross-process metrics.
- No ABI, release or performance guarantee.
- CRASH/PROF/TEL remain future packets; `CORE-06-06`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04/CORE-05 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-06-05` as `COMPLETED`, manifest `CORE06_05_COMPLETED_REST_BLOCKED`: **687 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 49 `COMPLETED`, 12 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.
