# NLE-PRPLAN-CORE-04-08 — Replay slice satisfaction evidence

**Status:** `SATISFIED BY CORE-04-04/CD-01 / NO NEW CODE`. **Base:** `21d5d03`. **Packet:** `NLE-PRPLAN-CORE-04-08`. **Contract:** [core-04-timeline-v0](../contracts/core-04-timeline-v0.md).

## Traceability

| Requirement | Evidence |
|---|---|
| Deterministic tick schedule | TICK-12: 10 s at 30 FPS and 144 FPS → same 600-tick count |
| Rational fixed step | `TickPlan.fixed_step` = 1/60 for both; no float accumulation |
| Replay header | `ReplayScheduleHeader` schema/rate/initial tick/fingerprint |
| Compatibility accept | exact header → `None`; fingerprint 0 → `None` |
| Compatibility reject | schema, rate, initial tick or nonzero fingerprint mismatch → `ReplayIncompatible` |
| Bounded claim | only tick IDs/rational dt; no physics/network/cross-machine determinism |

## Exact evidence

PR #525 merge `e6456ed`, audited head `284c329`; CD-01 PR #526 merge `e72fc1f`; CI 44990404237 Linux 142/142, ASan/UBSan 142/142, TSan 32/32, Windows 143/143, macOS 141/141; audit APPROVED #7074911571.

## Manifest effect

`CORE-04-08` `PLANNED_BLOCKED` → `COMPLETED`; root `CORE04_08_COMPLETED_REST_BLOCKED`: **704 blocked, 0 ready, 36 completed, 8 approved gates**.

## Limits

No bit-exact physics, multi-thread numerical, compiler floating-point, network rollback, snapshot/state hash or cross-machine replay guarantee; `build_fingerprint=0` means unknown. CORE-01 not qualified; CORE-02 NOT_QUALIFIED; CORE-03 INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED; full Q4 BLOCKED.

## Proposed checkpoint delta

`CORE-04-08` satisfied; `CORE-04-09` qualification is next and is not satisfied by unit tests alone.
