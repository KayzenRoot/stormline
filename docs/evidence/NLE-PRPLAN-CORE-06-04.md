# NLE-PRPLAN-CORE-06-04 — traces evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO ABI OR RELEASE CLAIM`. **Base:** `fd2feac`. **Implementation head:** `cdef7ee`. **Gate:** [NLE-PRPLAN-CORE-06-04-G6-ACTIVATION](NLE-PRPLAN-CORE-06-04-G6-ACTIVATION.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md). **WO:** [NLE-PRPLAN-CORE-06-04](../work-orders/NLE-PRPLAN-CORE-06-04.md).

## Scope delivered

- `src/stormline/core/diag/trace.hpp`: `SpanRecord`, `make_span`, `complete_span`, fixed `TraceBuffer`.
- `tests/core/core06_trace_tests.cpp`: TRACE-01 covering root/child, completion, invalid inputs and buffer overflow.
- Additive CMake target/test and workflow TSan target list.

No counters, crash handler/envelope, profile, telemetry, network/file I/O, third-party tracing, serialization, ABI or release.

## Implementation notes

- Root spans use `parent.value == 0`; self-parent is rejected.
- `complete_span` requires `!completed` and `end >= start`; double completion and backwards end are typed errors.
- `TraceBuffer` accepts only completed spans and drops with `BufferFull` when its fixed 128-record capacity is exhausted.
- No allocation, lock, file or network; per-producer sequence is caller-supplied.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core06_trace_tests.cpp -o /tmp/core06_trace_test
/tmp/core06_trace_test trace01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI on implementation head `cdef7ee`: [run 45026117728](https://github.com/KayzenRoot/stormline/actions/runs/45026117728) SUCCESS — Linux **167/167**, ASan/UBSan **167/167**, TSan **53/53**, Windows **168/168**, macOS **166/166**; allocator 1/1 per target. Docs [45026117627](https://github.com/KayzenRoot/stormline/actions/runs/45026117627) SUCCESS; SonarCloud and Socket SUCCESS. No benchmark, profiling, crash or performance result exists.

## Errors and corrections

No production or test correction was needed after local compile/test.

## Security and architecture

- Header-only internal C++20; no exception, dynamic allocation, platform API, file I/O, network or dependency.
- CORE-06 owns span values/local buffer; CORE-01/02/03/04 and GFX/AUD/DATA/EDIT boundaries unchanged.
- No secret, paid service or mutable global state.

## Rollback

Revert this PR normally; remove `trace.hpp`, the trace test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No profiler integration, trace export, serialization, sampling, GPU/thread instrumentation or cross-process ordering.
- No ABI, release or performance guarantee.
- COUNTER/CRASH/PROF/TEL remain future packets; `CORE-06-05`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04/CORE-05 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-06-04` as `COMPLETED`, manifest `CORE06_04_COMPLETED_REST_BLOCKED`: **688 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 48 `COMPLETED`, 12 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.

## Completion (2026-11-22)

- Code PR [#566](https://github.com/KayzenRoot/stormline/pull/566) squash-merged as `2b4283c9b73196d23282c8b9b55c7cf27aa7660c`.
- Final implementation head `b7cdf4c`; exact-head native run [45026403835](https://github.com/KayzenRoot/stormline/actions/runs/45026403835) SUCCESS: Linux 167/167, ASan/UBSan 167/167, TSan 53/53, Windows 168/168, macOS 166/166.
- pt-BR audit [APPROVED](https://github.com/KayzenRoot/stormline/pull/566#issuecomment-7079702029).
- Manifest after closeout: `CORE06_04_COMPLETED_REST_BLOCKED` — 688 blocked, 0 ready, 48 completed, 12 approved gates.
- Internal traces only; no profiler/network/file/ABI/release.
