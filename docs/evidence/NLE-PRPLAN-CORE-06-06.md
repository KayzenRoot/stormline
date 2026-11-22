# NLE-PRPLAN-CORE-06-06 — local crash envelope evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO HANDLER OR RELEASE CLAIM`. **Base:** `c80c6a8`. **Implementation head:** `424fcb6`. **Gate:** [NLE-PRPLAN-CORE-06-06-G6-ACTIVATION](NLE-PRPLAN-CORE-06-06-G6-ACTIVATION.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md). **WO:** [NLE-PRPLAN-CORE-06-06](../work-orders/NLE-PRPLAN-CORE-06-06.md).

## Scope delivered

- `src/stormline/core/diag/crash.hpp`: `CrashEnvelope` and bounded preceding-record copy.
- `tests/core/core06_crash_tests.cpp`: CRASH-01.
- Additive CMake target/test and workflow TSan target list.

No signal handler, minidump, parser, symbolication, upload, network/file I/O, third-party crash library, profile, telemetry, ABI or release.

## Implementation notes

- `CrashEnvelope` holds build, session, platform tag, time, reason and at most 16 preceding `LogRecord` values.
- `make_crash_envelope` rejects invalid build/session, negative time, more than 16 records, and null preceding with nonzero count.
- The API only copies values; it does not install a handler, catch a signal, read process memory, write a file or upload.
- No allocation, lock, platform API or dependency is present.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core06_crash_tests.cpp -o /tmp/core06_crash_test
/tmp/core06_crash_test crash01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI on implementation head `424fcb6`: [run 45028041447](https://github.com/KayzenRoot/stormline/actions/runs/45028041447) SUCCESS — Linux **169/169**, ASan/UBSan **169/169**, TSan **53/53**, Windows **170/170**, macOS **168/168**. Docs [45028041448](https://github.com/KayzenRoot/stormline/actions/runs/45028041448) SUCCESS; SonarCloud e Socket SUCCESS. No real crash capture, dump, symbol or upload result exists.

## Errors and corrections

No production or test correction was needed after local compile/test.

## Security and architecture

- Header-only internal C++20; no exception, dynamic allocation, platform API, file I/O, network or dependency.
- CORE-06 owns the local envelope value; CORE-01 owns OS crash/process lifecycle; no signal context is used.
- No secret, paid service or mutable global state.

## Rollback

Revert this PR normally; remove `crash.hpp`, the crash test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No crash handler, minidump, stack trace, symbolication, retention, consent, upload, network or real fault injection.
- No universal crash capture or dump safety; crash dumps would be sensitive and require separate authorization.
- PROF/TEL remain future packets; `CORE-06-07`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04/CORE-05 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-06-06` as `COMPLETED`, manifest `CORE06_06_COMPLETED_REST_BLOCKED`: **686 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 50 `COMPLETED`, 12 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.
