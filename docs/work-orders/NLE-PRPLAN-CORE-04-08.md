# NLE-PRPLAN-CORE-04-08 — Replay slice satisfaction (INTERNAL_ONLY)

**STATUS: SATISFACTION CLOSEOUT — documentary only; no new code.** **Gate:** continuation after CORE-04-07. **Formal packet:** `NLE-PRPLAN-CORE-04-08`. **Predecessor:** `CORE-04-04` Timeline. **Issue:** #21. **Base:** `21d5d03`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **Contract:** [core-04-timeline-v0](../contracts/core-04-timeline-v0.md).

## OBJECTIVE

Record that `CORE-04-08` (“replay determinístico onde exigido”) is satisfied by `CORE-04-04`/CD-01 within the bounded clock envelope: same admitted elapsed/input schedule and config yields the same `TickId` sequence and rational step; `ReplayScheduleHeader`/`replay_schedule_compatible` reject schema/rate/initial-tick/fingerprint mismatch. No physics/network/snapshot determinism claim.

## CONTEXT

TICK-12 proves identical 600-tick schedules for 30/144 FPS partitions and compatibility accept/reject. CD-01 added `start_at`/`replay_schedule_compatible`. CORE-04 owns tick scheduling only; SIM/NET own physics/network replay. CORE-01/02/03 statuses unchanged.

## SCOPE

Documentary satisfaction and manifest advance only.

## OUT OF SCOPE

Bit-exact physics, multi-thread numerical determinism, compiler floating-point parity, network rollback, snapshot/state hashing, stable input stream ownership, cross-machine replay, new API, CORE-04-09/-10.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0107/0006, timeline contract, CORE-04-04 evidence/PR #525, CD-01 PR #526, TICK-12.

## REQUIREMENTS

GOV-001..005; ADR-0107; bounded tick-schedule determinism only.

## ARCHITECTURE RULES

CORE-04 defines tick IDs/fixed step; SIM-01/02 own physics determinism; NET-02/03/04 own network clocks/rollback; no cross-owner promise.

## CONSTRAINTS

`INTERNAL_ONLY`; risk `ELEVATED`; no new code/dependency/ABI/release.

## ACCEPTANCE CRITERIA

- TICK-12 evidence covers identical schedules and compatibility rejection.
- `CORE-04-08` completed; manifest **704 blocked, 0 ready, 36 completed, 8 approved gates**.
- Docs/audit clean; registry byte-identical.

## TESTS

No new test; evidence cites TICK-12 and CD-01.

## DELIVERABLES

WO, evidence, checkpoint, manifest/validator/tests.

## REVIEW FORMAT

pt-BR: base/head, evidence, bounded replay scope, manifest, blocked packets. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Physics/network/cross-machine determinism overclaim, new API, drift, HIGH/CRITICAL.

## CONTEXT LOCK

Base `21d5d03`; CORE-04-04 merge `e6456ed`; CD-01 merge `e72fc1f`; contract blob `7137e433f13b564ba4171d59750346e4a8815c47`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-04-08.md`.
