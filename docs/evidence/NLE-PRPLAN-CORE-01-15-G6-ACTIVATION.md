# NLE-PRPLAN-CORE-01-15 — G6 activation (integrated CI qualification)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `ee7f3188eee314b7f051ef39ce4c88ab74492fb1`. **Formal packet:** `NLE-PRPLAN-CORE-01-15`. **ADR:** [ADR-0094](../adr/0094-core-01-integrated-ci-qualification.md). **Contract:** [core-01-integrated-qualification-v0](../contracts/core-01-integrated-qualification-v0.md). **WO:** [NLE-PRPLAN-CORE-01-15](../work-orders/NLE-PRPLAN-CORE-01-15.md).

## Owner authorization

The owner authorized continuing on 2026-11-17 (`autorizo faça o que tem que fazer e continue`). C01-D09/D14 are ratified bounded directions. This gate activates only `NLE-PRPLAN-CORE-01-15` after Docs Validation, pt-BR audit and merge.

It does not certify physical hardware, security, performance, 32 scenarios, Wayland runtime, public ABI/release, or another packet.

## Predecessors

`-03`..`-14` and CORE-02-03 are `COMPLETED`; no predecessor reopened.

## Bounded technical slice

- `core01_qualification_test`: 200 headless, 10 SDL init/quit+window, 25 extra windows, 10,000 events, display/capability/lifecycle, zero live headless resources.
- Linux X11/Xvfb, Win32, Cocoa or NOT_QUALIFIED; Linux ASan/UBSan; 67 total CTests.
- No production API or timing threshold.
- Exact allowlist: `tests/core/core01_qualification_tests.cpp`, additive CMake, additive workflow filters, evidence.

## Gate state after merge

- Manifest root `CORE01_15_READY_PREDECESSORS_COMPLETED`: **730 `PLANNED_BLOCKED`, 13 `COMPLETED`, 4 approved gates, 1 `EXECUTOR_READY` (`CORE-01-15`)**.
- Selector `-15` exit 0; all other IDs exit 2; 80/80 WOs BLOCKED; registry unchanged.

## Proof obligations

QUAL-01..QUAL-06; 67 CTests; Linux/Windows/macOS and ASan/UBSan; explicit NOT_QUALIFIED; no physical/security/performance claim.

No code/native PASS is claimed by this gate.
