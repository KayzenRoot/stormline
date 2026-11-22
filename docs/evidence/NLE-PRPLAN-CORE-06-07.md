# NLE-PRPLAN-CORE-06-07 — profile samples evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO PROFILER OR PERFORMANCE CLAIM`. **Base:** `1522d80`. **Implementation head:** `e3f9080`. **Gate:** [NLE-PRPLAN-CORE-06-07-G6-ACTIVATION](NLE-PRPLAN-CORE-06-07-G6-ACTIVATION.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md). **WO:** [NLE-PRPLAN-CORE-06-07](../work-orders/NLE-PRPLAN-CORE-06-07.md).

## Scope delivered

- `src/stormline/core/diag/profile.hpp`: `ProfileSample` and fixed 64-sample `ProfileAccumulator`.
- `tests/core/core06_profile_tests.cpp`: PROF-01 count/total/min/max/reset/full.
- Additive CMake target/test and workflow TSan target list.

No Tracy/Perfetto, timer adapter, sampling thread, export, telemetry, network/file I/O, dependency, ABI or release.

## Implementation notes

- `make_profile_sample` requires valid build and nonzero scope ID; zero elapsed is allowed.
- `ProfileAccumulator` keeps count/total/min/max over at most 64 samples, drops with `BufferFull` and supports explicit reset.
- No allocation, lock, timer, thread, file or network call exists; no performance result is claimed.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/core06_profile_tests.cpp -o /tmp/core06_profile_test
/tmp/core06_profile_test prof01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI on implementation head `e3f9080`: [run 45028933777](https://github.com/KayzenRoot/stormline/actions/runs/45028933777) SUCCESS — Linux **170/170**, ASan/UBSan **170/170**, TSan **53/53**, Windows **171/171**, macOS **169/169**. Docs [45028933745](https://github.com/KayzenRoot/stormline/actions/runs/45028933745) SUCCESS; SonarCloud e Socket SUCCESS. No profiler, benchmark, sampling or performance result exists.

## Errors and corrections

- Initial PROF-01 called `add` with an already-valid sample while expecting `InvalidArgument`; corrected to add a zero-build `ProfileSample`. Production code unchanged.

## Security and architecture

- Header-only internal C++20; no exception, dynamic allocation, platform API, file I/O, network or dependency.
- CORE-06 owns profile values/accumulator; CORE-01/02/03/04 and GFX/AUD/DATA/EDIT boundaries unchanged.
- No secret, paid service or mutable global state.

## Rollback

Revert this PR normally; remove `profile.hpp`, the profile test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No Tracy/Perfetto adapter, timer source, sampling thread, trace export, serialization, GPU profiling or overhead measurement.
- No ABI, release or performance guarantee.
- TEL remains the last functional packet; `CORE-06-08`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 is not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04/CORE-05 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `CORE-06-07` as `COMPLETED`, manifest `CORE06_07_COMPLETED_REST_BLOCKED`: **685 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 51 `COMPLETED`, 12 approved gates**, and keep every later packet blocked. This is a proposal, not a self-promoted checkpoint.

## Completion (2026-11-22)

- Code PR [#572](https://github.com/KayzenRoot/stormline/pull/572) squash-merged as `07caee3493de5744c9933ea82090d4774a459825`.
- Final implementation head `6af3c3f`; exact-head native run [45029255533](https://github.com/KayzenRoot/stormline/actions/runs/45029255533) SUCCESS: Linux 170/170, ASan/UBSan 170/170, TSan 53/53, Windows 171/171, macOS 169/169.
- pt-BR audit [APPROVED](https://github.com/KayzenRoot/stormline/pull/572#issuecomment-7080085505).
- Manifest after closeout: `CORE06_07_COMPLETED_REST_BLOCKED` — 685 blocked, 0 ready, 51 completed, 12 approved gates.
- Local samples only; no profiler/timer/thread/export/network/ABI/release.
