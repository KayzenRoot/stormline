# NLE-PRPLAN-GFX-05-09 — Integrated material qualification evidence

**Status:** `QUALIFICATION EVIDENCE / INTERNAL_ONLY / NO NATIVE GPU, CODEC OR HARDWARE`. **Base:** `65816a3`. **Gate:** [NLE-PRPLAN-GFX-05-09-G6-ACTIVATION](NLE-PRPLAN-GFX-05-09-G6-ACTIVATION.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-05-09](../work-orders/NLE-PRPLAN-GFX-05-09.md).

## Scope delivered

- `tests/core/gfx05_material_qualification_tests.cpp`: QLF-G501..G504.
- Additive CMake target/tests and workflow TSan target.
- No closeout, native GPU, codec, upload, rendering, driver/hardware, visual golden, performance, ABI or release.

## Qualification notes

- QLF-G501 integrates materials, texture metadata, mips, sampler, pages, decals and transparency; asserts counts, mip bytes, page prefix/truncation, decal order and back-to-front transparency.
- QLF-G502 repeats the integrated pipeline and compares every output field.
- QLF-G503 exercises duplicate material, invalid texture/pages/mips/sampler/decal/transparency, each followed by a valid operation.
- QLF-G504 performs 10,000 integrated pipelines and 10,000 invalid material rejects under fixed capacities.

These are logical/CI oracles; they do not qualify a GPU, driver, hardware, visual output or performance.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/gfx05_material_qualification_tests.cpp -o /tmp/gfx05_qual
/tmp/gfx05_qual qlf01
/tmp/gfx05_qual qlf02
/tmp/gfx05_qual qlf03
/tmp/gfx05_qual qlf04
```

All exited 0. CMake is unavailable locally; additive wiring is validated by exact-head native CI. No CI result is claimed before that run.

## Errors and corrections

- The draft helper used a dynamically allocated diagnostic for the first mip chain; it was replaced with a stack diagnostic before the first compile, removing the leak risk.
- QLF-G501 initially expected `truncated=false`; the request/budget fixture has three nonresident pages for two slots, so the oracle was corrected to `truncated=true`.
- No sanitizer defect was observed after the corrections.

## Security and architecture

- Test-only C++20; no GPU, codec, I/O, file or network.
- Qualification is logical and CI-only; no hardware, driver, visual or performance behavior is asserted.

## Rollback

Revert normally; remove the qualification test and additive CMake/workflow/evidence entries.

## Open risks / not claimed

- No native GPU, codec, upload, rendering, hardware, performance or visual golden.
- `GFX-05-10` closeout remains blocked until its gate.
- CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `GFX-05-09` as `COMPLETED`, manifest `GFX05_09_COMPLETED_REST_BLOCKED`: **588 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 128 `COMPLETED`, 32 approved gates**.
