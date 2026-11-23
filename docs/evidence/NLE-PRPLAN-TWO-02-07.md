# NLE-PRPLAN-TWO-02-07 — Streaming plan evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO STREAMING I/O`. **Base:** `8259d4d`. **Gate:** [NLE-PRPLAN-TWO-02-07-G6-ACTIVATION](NLE-PRPLAN-TWO-02-07-G6-ACTIVATION.md). **Contract:** [two-02-tilemap-internal-v0](../contracts/two-02-tilemap-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-02-07](../work-orders/NLE-PRPLAN-TWO-02-07.md). **PR:** #817.

## Scope delivered

- `src/stormline/tilemap/streaming_plan.hpp`: budget/request/plan and `plan_streaming`.
- `tests/core/two02_streaming_tests.cpp`: STR-01.
- Additive CMake test and TSan target.
- No streaming I/O, cache, async job, residency mutation, GPU, renderer, dependency, ABI, release, hardware or performance claim.

## Implementation notes

- Map/revision must be nonzero; budget caps must be positive.
- Failed chunks may not exceed requested chunks.
- Visible/prefetch/request/byte budgets clamp with `degraded=true`; no I/O or residency mutation occurs.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/two02_streaming_tests.cpp -o /tmp/two02_str
/tmp/two02_str str01
g++ ... -fsanitize=address,undefined ... -o /tmp/two02_str_san
/tmp/two02_str_san str01
g++ ... -fsanitize=thread ... -o /tmp/two02_str_tsan
setarch "$(uname -m)" -R /tmp/two02_str_tsan str01
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Header-only internal C++20; no allocation, exception, file, network, GPU or global state.
- Metadata only; no streaming result is claimed.

## Rollback

Revert normally; remove the header/test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No streaming I/O/cache/async/residency, GPU, render, hardware, performance, ABI or release.
- `TWO-02-08`/`-09` remain blocked until their gates.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `TWO-02-07` as `COMPLETED`, manifest `TWO02_07_COMPLETED_REST_BLOCKED`: **540 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 166 `COMPLETED`, 42 approved gates**.
