# NLE-PRPLAN-CORE-04-03 — Monotonic ClockSource (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-04-03`. **Predecessor:** `CORE-04-02` contract. **Issue:** #21. **Base:** `67bbdfdcded5c2172c3773794fd45a85759082a8`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **Contract:** [core-04-timeline-v0](../contracts/core-04-timeline-v0.md).

## OBJECTIVE

Implement the first CORE-04 slice exactly as frozen: shared time types and an injectable monotonic `ClockSource` with `SteadyClockSource`, typed errors and tests. No Timeline, dependency, SDL/native adapter or public ABI is authorized.

## CONTEXT

CORE-04-01 governance and CORE-04-02 contract are approved. ADR-0107 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner instructed continuation on 2026-11-21. This packet activates only `CORE-04-03`.

## SCOPE

- `time_types.hpp`: `TimeError`, `TimelineState`, `DebtPolicy`, `TickId`, `Rational`, `ClockSample` and frozen timeline structs needed by later slices.
- `clock_source.hpp/.cpp`: abstract `ClockSource`, `SteadyClockSource`, checked monotonic sampling.
- `tests/core/clock_source_tests.cpp`: CLK-01..CLK-06.
- Additive CMake target/tests and workflow path filters.
- Evidence file.

## OUT OF SCOPE

`Timeline` implementation, fixed tick, interpolation, pause/step, debt, replay, SDL3/QPC/platform adapters, third-party timing libraries, allocator selection, public ABI, release, CORE-01 completion, CORE-04-04 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0006/0086/0107, core-04-timeline/governance contracts, CORE-04 architecture, CORE-01 capability evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0107; ADR-0086; contract semantics for `ClockSource`/`ClockSample`; no float time accumulation.

## ARCHITECTURE RULES

CORE-04 owns measured elapsed time; CORE-01 owns OS time acquisition. `SteadyClockSource` is an internal adapter over `std::chrono::steady_clock`; no SDL/QPC types escape. No timeline or graphics/audio dependency.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service; CORE-01 not module-qualified; CORE-02/03 NOT_QUALIFIED; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; `ClockSource` sample returns monotonic elapsed ns or typed error.
- Backward/duplicate/overflow/unavailable outcomes typed; no simulated negative time.
- CLK matrix passes on Linux/ASan/TSan/Windows/macOS.
- No Timeline/dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

CLK-01 basic monotonic samples; CLK-02 fake injection; CLK-03 unavailable/non-monotonic typed errors; CLK-04 overflow/near-max; CLK-05 lifetime/destructor; CLK-06 cross-platform. Existing full CTest suite.

## DELIVERABLES

`time_types.hpp`, `clock_source.hpp/.cpp`, clock tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CLK matrix, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/native type, Timeline code, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `67bbdfdcded5c2172c3773794fd45a85759082a8`; contract blob `1b669bd2b5f6ce02f4e6a4c469d1065177c27285`; CORE-04-02 gate PR #520.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-04-03-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-04-03.md` for implementation.
