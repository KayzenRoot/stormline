# NLE-PRPLAN-CORE-04-07 — Stepping slice satisfaction (INTERNAL_ONLY)

**STATUS: SATISFACTION CLOSEOUT — documentary only; no new code.** **Gate:** continuation after CORE-04-06. **Formal packet:** `NLE-PRPLAN-CORE-04-07`. **Predecessor:** `CORE-04-04` Timeline. **Issue:** #21. **Base:** `ede9f16`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **Contract:** [core-04-timeline-v0](../contracts/core-04-timeline-v0.md).

## OBJECTIVE

Record that `CORE-04-07` (“stepping”) is satisfied by `CORE-04-04`: `step_once` while paused emits exactly one tick, keeps the timeline Paused, does not sample the clock, and guards tick overflow. No editor UI or new API.

## CONTEXT

TICK-06 proves one-tick stepping and paused state; TICK-10 proves the near-max `TickOverflow` guard via `start_at`. CORE-04 owns simulation stepping, not editor command UI. CORE-01/02/03 statuses unchanged.

## SCOPE

Documentary satisfaction and manifest advance only.

## OUT OF SCOPE

Editor stepping UI, frame-by-frame rendering, audio scrubbing, OS debugger integration, new state/API, CORE-04-08..-10.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0107, timeline contract, CORE-04-04 evidence/PR #525, TICK-06/10.

## REQUIREMENTS

GOV-001..005; ADR-0107; step remains one logical tick while Paused.

## ARCHITECTURE RULES

CORE-04 owns tick stepping; editor commands remain in EDIT/AI modules; no renderer/audio side effect.

## CONSTRAINTS

`INTERNAL_ONLY`; risk `ELEVATED`; no new code/dependency/ABI/release.

## ACCEPTANCE CRITERIA

- TICK-06/10 evidence covers one tick, paused state and overflow.
- `CORE-04-07` completed; manifest **705 blocked, 0 ready, 35 completed, 8 approved gates**.
- Docs/audit clean; registry byte-identical.

## TESTS

No new test; evidence cites TICK-06/10.

## DELIVERABLES

WO, evidence, checkpoint, manifest/validator/tests.

## REVIEW FORMAT

pt-BR: base/head, evidence, stepping scope, manifest, blocked packets. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Editor/render overclaim, new API, drift, HIGH/CRITICAL.

## CONTEXT LOCK

Base `ede9f16`; CORE-04-04 merge `e6456ed`; contract blob `7137e433f13b564ba4171d59750346e4a8815c47`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-04-07.md`.
