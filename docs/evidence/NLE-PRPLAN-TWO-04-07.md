# NLE-PRPLAN-TWO-04-07 — Integrated hybrid qualification evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / QUALIFICATION IS CI-ONLY`. **Base:** `5cb9f94`. **Gate:** [NLE-PRPLAN-TWO-04-07-G6-ACTIVATION](NLE-PRPLAN-TWO-04-07-G6-ACTIVATION.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md). **WO:** [NLE-PRPLAN-TWO-04-07](../work-orders/NLE-PRPLAN-TWO-04-07.md). **PR:** #847.

## Scope delivered

- `tests/core/two04_hybrid_qualification_tests.cpp`: QLF-T401..T404.
- Additive CMake executable/tests and TSan target.
- No runtime, renderer, GPU, lighting, shadow, subview execution, editor, dependency, ABI, release, hardware or performance qualification.

## Qualification fixtures

- **QLF-T401 integrated:** valid camera, layers, sort and effects plans; projection, counts, stable order and subview depth verified.
- **QLF-T402 deterministic repeat:** each planner is called twice; projection, extents, counts and sort order match exactly.
- **QLF-T403 failure recovery:** each planner receives one typed-invalid descriptor, then a valid descriptor; failure code is exact and recovery returns `None`.
- **QLF-T404 bounded overload:** 10,000 iterations call all four planners; periodic failures are injected for camera, sort and effects, and a layer variation is validated; every plan remains within layer, object, effect and subview-depth caps with stable sort order.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0: strict GCC flags, ASan/UBSan and TSan all passed for QLF-T401..T404. CMake is unavailable locally; additive wiring is validated by exact-head native CI.

## Errors and corrections

- No defect after the first strict compile.

## Security and architecture

- Test-only change; no production file altered.
- No allocation, exception, file, network, audio, GPU, thread or global state introduced.
- Qualification exercises planner contracts only; it is not physical, OS, security, soak, visual or performance qualification.

## Rollback

Revert normally; remove the test and additive CMake/workflow/evidence entries. No state or migration.

## Open risks / not claimed

- No runtime, renderer, GPU, lighting, shadows, subview execution, editor, export, ABI, release, hardware or performance.
- `TWO-04-08` remains blocked until its gate.
- TWO-01/GFX-04 not module-qualified; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

After merge, record `TWO-04-07` as `COMPLETED`, manifest `TWO04_07_COMPLETED_REST_BLOCKED`: **522 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 180 `COMPLETED`, 46 approved gates**. Checkpoint promotion remains owner-only.
