# NLE-PRPLAN-GFX-01-09 — internal RHI qualification evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU OR HARDWARE QUALIFICATION`. **Base:** `4349936`. **Gate:** [NLE-PRPLAN-GFX-01-09-G6-ACTIVATION](NLE-PRPLAN-GFX-01-09-G6-ACTIVATION.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md). **WO:** [NLE-PRPLAN-GFX-01-09](../work-orders/NLE-PRPLAN-GFX-01-09.md).

## Scope delivered

- `tests/core/gfx01_rhi_qualification_tests.cpp`: QLF-G01..G04.
- Additive CMake target/tests and workflow TSan target.

No closeout; no native GPU, driver, hardware, rendering, shaders, performance, ABI or release.

## Qualification notes

- QLF-G01 integrates adapter selection, device init, all queue roles, buffer/texture creation, resource info, barriers, loss/recovery, stale-generation rejection and close.
- QLF-G02 repeats the same integrated sequence and compares generation, capabilities, queue mask, submit count, slots/generations and barrier result.
- QLF-G03 exercises typed failures — invalid adapter, unsupported feature, invalid descriptors, invalid submit count, unsupported queue role, invalid barrier, stale handle, device loss, stale generation and capacity — each followed by a valid operation.
- QLF-G04 performs 10,000 create/release cycles, 10,000 capacity attempts, 10,000 submits and 10,000 barriers while capacities remain bounded at 64 resources and submits remain correct.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx01_rhi_qualification_tests.cpp -o /tmp/gfx01_rhi_qual
/tmp/gfx01_rhi_qual qlf01
/tmp/gfx01_rhi_qual qlf02
/tmp/gfx01_rhi_qual qlf03
/tmp/gfx01_rhi_qual qlf04
```

All exited 0. ASan/UBSan rebuild exited 0 for all four modes. TSan rebuild ran with `setarch -R` and exited 0 for all four modes.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- QLF-G01 initially overwrote a live handle through a failed create on a lost device; a separate output handle corrected the fixture.
- QLF-G03 similarly used a live buffer as the output of an invalid texture create and expected compute rejection from a device that still advertises adapter compute capabilities. Both fixtures were corrected to match the frozen API semantics.
- Local TSan requires ASLR disabled through `setarch -R`; CI already applies this.

## Security and architecture

- Test-only C++20; no GPU, driver, allocator, file or network.
- Qualification is logical and CI-only; it does not assert physical hardware, driver or performance behavior.

## Rollback

Revert normally; remove the qualification test and additive CMake/workflow entries.

## Open risks / not claimed

- No native GPU, driver, swapchain, shader, rendering or hardware qualification.
- No performance, ABI, release or deployment claim.
- `GFX-01-10` closeout remains blocked until its gate.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-01-09` as `COMPLETED`, manifest `GFX01_09_COMPLETED_REST_BLOCKED`: **625 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 98 `COMPLETED`, 24 approved gates**.
