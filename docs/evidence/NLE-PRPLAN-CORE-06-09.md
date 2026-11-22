# NLE-PRPLAN-CORE-06-09 — integrated diagnostics qualification evidence

**Status:** `INTERNAL QUALIFICATION / NO NETWORK, CRASH-HANDLER OR RELEASE CLAIM`. **Base:** `29bf653`. **Implementation head:** `6bffce3`. **Gate:** [NLE-PRPLAN-CORE-06-09-G6-ACTIVATION](NLE-PRPLAN-CORE-06-09-G6-ACTIVATION.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md). **WO:** [NLE-PRPLAN-CORE-06-09](../work-orders/NLE-PRPLAN-CORE-06-09.md).

## Scope delivered

- `tests/core/core06_diagnostics_qualification_tests.cpp`: QLF-D01 integrated, QLF-D02 repeatability, QLF-D03 recovery, QLF-D04 10,000-attempt bounded overload.
- Additive `CMakeLists.txt` target/CTest entries and workflow TSan target list.
- No production source, dependency, network, crash handler, profiler adapter, serialization, ABI or release change.

## Qualification matrix

- **QLF-D01:** log → trace → counter → profile → crash envelope → opt-in telemetry flow; sizes/values verified.
- **QLF-D02:** repeated log/counter sequence preserves per-producer order and values.
- **QLF-D03:** typed log/span/telemetry/counter errors followed by successful valid operations.
- **QLF-D04:** 10,000 log and telemetry attempts keep fixed capacities and count every drop.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core06_diagnostics_qualification_tests.cpp -o /tmp/core06_qual_test
/tmp/core06_qual_test qlfd01
/tmp/core06_qual_test qlfd02
/tmp/core06_qual_test qlfd03
/tmp/core06_qual_test qlfd04
```

All four modes exited 0. ASan/UBSan rebuild exited 0.

Native CI on implementation head `6bffce3`: [run 45031173662](https://github.com/KayzenRoot/stormline/actions/runs/45031173662) SUCCESS — Linux **175/175**, ASan/UBSan **175/175**, TSan **53/53**, Windows **176/176**, macOS **174/174**. Docs [45031173657](https://github.com/KayzenRoot/stormline/actions/runs/45031173657) SUCCESS; SonarCloud e Socket SUCCESS. No network/privacy/crash/profiler/performance/hardware result exists.

## Errors and corrections

No production or test correction was needed after local compile/test.

## Security and architecture

- Test-only translation unit over all CORE-06 headers; no production API, exception, dynamic allocation, platform API, file I/O, network or dependency.
- CORE-06 owns local values/buffers; CORE-01/02/03/04 and GFX/AUD/DATA/EDIT boundaries unchanged.
- No secret, paid service or mutable global state.

## Rollback

Revert this PR normally; remove the qualification test and additive CMake/workflow entries. No force push or history rewrite.

## Not qualified / open risks

- No real network/upload/privacy/consent, crash handler/dump/symbolication, profiler backend, sampling thread, serialization, ABI or release.
- No physical hardware, soak, suspend/resume, performance or cross-compiler determinism.
- The qualification is internal/CI-only and does not declare CORE-06 or CORE-01 module-qualified.
- `CORE-06-10` remains the final closeout and must record the module as not fully qualified.
- CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04/CORE-05 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-06-09` as `COMPLETED`, manifest `CORE06_09_COMPLETED_REST_BLOCKED`: **683 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 53 `COMPLETED`, 12 approved gates**, and keep `CORE-06-10` blocked. This is a proposal, not a self-promoted checkpoint.
