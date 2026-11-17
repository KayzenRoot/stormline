# NLE-PRPLAN-CORE-01-14 — G6 activation (multi-OS soak harness)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `9bfbed5901947a3073b2910a48b4c9873702d37f`. **Formal packet:** `NLE-PRPLAN-CORE-01-14`. **ADR:** [ADR-0093](../adr/0093-core-01-multi-os-soak-harness.md). **Contract:** [core-01-multi-os-soak-v0](../contracts/core-01-multi-os-soak-v0.md). **WO:** [NLE-PRPLAN-CORE-01-14](../work-orders/NLE-PRPLAN-CORE-01-14.md).

## Owner authorization

The owner authorized continuing on 2026-11-17 (`continue evoluindo`). C01-D14 ratified the bounded soak counts. This gate activates only `NLE-PRPLAN-CORE-01-14` after exact-head Docs Validation, pt-BR audit and merge.

It does not certify physical hardware, 30+30 timing samples, 32 scenarios, long-duration soak, Wayland runtime, performance thresholds, public ABI/release, or another packet.

## Predecessors

`-03`..`-13` and CORE-02-03 are `COMPLETED`; no predecessor reopened.

## Bounded technical slice

- `core01_soak_test`: 200 headless cycles, 100 window cycles, 10,000 synthetic events, display/lifecycle, teardown.
- Linux X11/Xvfb, Win32, Cocoa or NOT_QUALIFIED; Linux ASan/UBSan.
- No production API, timing threshold or physical-hardware claim.
- Exact allowlist: `tests/core/core01_soak_tests.cpp`, additive CMake, additive workflow filters, evidence.

## Gate state after merge

- Manifest root `CORE01_14_READY_PREDECESSORS_COMPLETED`: **731 `PLANNED_BLOCKED`, 12 `COMPLETED`, 4 approved gates, 1 `EXECUTOR_READY` (`CORE-01-14`)**.
- Selector `-14` exit 0; all other IDs exit 2; 80/80 WOs BLOCKED; registry unchanged.

## Proof obligations

SOAK-01..SOAK-05; existing 65 CTests; Linux/Windows/macOS and ASan/UBSan; explicit NOT_QUALIFIED where applicable; no performance/physical claim.

No code or native PASS is claimed by this gate.
