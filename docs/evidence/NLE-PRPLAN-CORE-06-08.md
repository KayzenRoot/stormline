# NLE-PRPLAN-CORE-06-08 — local opt-in telemetry evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NETWORK OR RELEASE CLAIM`. **Base:** `eeb9225`. **Implementation head:** `3b1fdb1`. **Gate:** [NLE-PRPLAN-CORE-06-08-G6-ACTIVATION](NLE-PRPLAN-CORE-06-08-G6-ACTIVATION.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md). **WO:** [NLE-PRPLAN-CORE-06-08](../work-orders/NLE-PRPLAN-CORE-06-08.md).

## Scope delivered

- `src/stormline/core/diag/telemetry.hpp`: `TelemetryPolicy`, `TelemetryEvent`, validation and fixed 64-event local `TelemetryBuffer`.
- `tests/core/core06_telemetry_tests.cpp`: TEL-01.
- Additive CMake target/test and workflow TSan target list.

No network, upload, cloud/analytics service, consent UI, persistence, serialization, external SDK, ABI or release.

## Implementation notes

- Default is disabled; `record` returns `NotEnabled` until explicit local enable.
- A policy with `local_only=false` cannot be enabled and returns `Unsupported`.
- Events require valid build, nonnegative time, nonzero event ID, finite value and bounded name.
- Buffer capacity 64 with `dropped`/`BufferFull`; no file, socket, DNS, HTTP or process spawn exists.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core06_telemetry_tests.cpp -o /tmp/core06_telemetry_test
/tmp/core06_telemetry_test tel01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI on implementation head `3b1fdb1`: [run 45030048569](https://github.com/KayzenRoot/stormline/actions/runs/45030048569) SUCCESS — Linux **171/171**, ASan/UBSan **171/171**, TSan **53/53**, Windows **172/172**, macOS **170/170**. Docs [45030048462](https://github.com/KayzenRoot/stormline/actions/runs/45030048462) SUCCESS; SonarCloud e Socket SUCCESS. No network/upload/privacy/consent result exists.

## Errors and corrections

- Initial TEL-01 ignored the `[[nodiscard]]` result of `set_enabled(false)`, failing `-Werror`; corrected with an explicit `expect`. Production code unchanged.

## Security and architecture

- Header-only internal C++20; no exception, dynamic allocation, platform API, file I/O, network, DNS or dependency.
- CORE-06 owns the local buffer/policy; DATA/EDIT/QA/AI retain consent/privacy ownership; no cloud.
- No secret, paid service or mutable global state.

## Rollback

Revert this PR normally; remove `telemetry.hpp`, the telemetry test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No network/upload/cloud/analytics, consent UI, retention, encryption, anonymization or privacy qualification.
- No persistence, serialization, ABI or release.
- Qualification/closeout remain `CORE-06-09`/`-10`, both blocked.
- CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04/CORE-05 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-06-08` as `COMPLETED`, manifest `CORE06_08_COMPLETED_REST_BLOCKED`: **684 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 52 `COMPLETED`, 12 approved gates**, and keep `CORE-06-09`/`-10` blocked. This is a proposal, not a self-promoted checkpoint.
