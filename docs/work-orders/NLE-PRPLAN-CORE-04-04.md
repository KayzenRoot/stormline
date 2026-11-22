# NLE-PRPLAN-CORE-04-04 — Rational fixed-step Timeline (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges; CD-01 adds `start_at` and `replay_schedule_compatible`.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-04-04`. **Predecessor:** `CORE-04-03` ClockSource. **Issue:** #21. **Base:** `60cd2dfbaf38ee43b332f0b2274816a9b739736e`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **Contract:** [core-04-timeline-v0](../contracts/core-04-timeline-v0.md).

## OBJECTIVE

Implement the frozen CORE-04 Timeline: exact rational fixed step with carried remainder, pause/resume, single-step, interpolation alpha, debt/clamp policy, replay header, typed errors and TICK-03..TICK-12. No third-party timing library or public ABI.

## CONTEXT

CORE-04-03 delivered `ClockSource`/`SteadyClockSource` and shared time types. CORE-04-01/02 are approved; CORE-01 is not module-qualified and selected capabilities are admitted. The owner instructed continuation on 2026-11-21/22. This packet activates only `CORE-04-04`.

## SCOPE

- `timeline.hpp/.cpp`: `Timeline`, start/start_at/pump/pump_elapsed/pause/resume/step_once/stop/state/stats/current_tick and `replay_schedule_compatible`.
- Exact integer/rational tick accumulator with carried remainder; no float accumulation.
- Interpolation alpha, clamp, DropExcess/Carry debt, replay header/compatibility, typed lifecycle errors.
- `tests/core/timeline_tests.cpp` for TICK-03..TICK-12.
- Additive CMake/workflow and evidence.

## OUT OF SCOPE

Third-party timing libraries, SDL/QPC adapters, public ABI, release, allocator selection, physics/network determinism, snapshot/rollback, resource policy, CORE-04-05..-10 activation.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0006/0086/0107, timeline contract, CORE-04 architecture, CORE-04-03 code/evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0107; contract semantics TICK-03..12; exact rational arithmetic; no silent authoritative tick loss.

## ARCHITECTURE RULES

CORE-04 owns tick timeline/debt/interpolation; CORE-01 owns OS time; CORE-03 consumes tick IDs; SIM/GFX/NET/AUD boundaries unchanged. `Timeline` does not depend on CORE-03 or graphics/audio.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service; CORE-01 not module-qualified; CORE-02/03 NOT_QUALIFIED or sequence-not-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; rational 60 Hz/24 h exact; no float accumulation.
- Pause/resume/step, interpolation alpha, clamp, debt policies and typed errors.
- `start_at` near-max tick overflow and `replay_schedule_compatible` mismatch are exercised.
- TICK-03..TICK-12 pass on Linux/ASan/UBSan/TSan/Windows/macOS; no HIGH/CRITICAL.
- No Timeline dependency/ABI/release; pt-BR audit `APPROVED`.

## TESTS

TICK-03 FPS partitions 30/60/144; TICK-04 24 h exact; TICK-05 pause; TICK-06 single-step; TICK-07 catch-up/drop; TICK-08 debt carry; TICK-09 time scale; TICK-10 start_at near-max TickOverflow/duration overflow; TICK-11 lifecycle/thread; TICK-12 determinism/replay compatibility. Full existing CTest suite.

## DELIVERABLES

`timeline.hpp/.cpp`, timeline tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TICK matrix, rational/determinism evidence, sanitizers/CI, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, float accumulation, unbounded catch-up, silent tick loss, third-party type, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `60cd2dfbaf38ee43b332f0b2274816a9b739736e`; contract blob `1b669bd2b5f6ce02f4e6a4c469d1065177c27285`; CORE-04-03 merge `185d29c`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-04-04-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-04-04.md` for implementation.
