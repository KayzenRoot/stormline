# ADR-0100 — CORE-02 memory telemetry slice

**Status:** `OWNER_DIRECTION_CAPABILITY_BASED_L1 / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **Subordinate to ADR-0004, which remains `PROPOSED`; does not approve SMF, export/telemetry pipelines, a release class or G3 globally.**

**Date:** 2026-11-18 | **WO:** `NLE-PRPLAN-CORE-02-08` | **Parent:** `NLE-PRPLAN-CORE-02-01` | **Issue:** #19.

## Context and authority

CORE-02-03/04/05/06/07 delivered ownership, the system allocator baseline, a monotonic arena, soft/hard budgets and explicit leak tokens. The next planned packet `-08` is memory telemetry. ADR-0004 and the CORE-02 architecture describe future snapshots, domains and optional sampling, but no process-global interception or export pipeline is approved.

This slice implements a bounded, explicit, in-process counter primitive with real instrumentation hooks for the existing memory primitives. It is not a profiler, exporter, frame tracer, pointer tracker or global allocator hook.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`; no window/input/DPI/IME/hotplug/soak capability used. Admission expires at closeout.

## Bounded technical decision

- New internal `MemoryTelemetry`, `TelemetryError`, per-domain counters and snapshot structures:
  - `record_allocate`/`record_release` count events, live allocations/bytes, peaks, cumulative allocated/released bytes and per-`MemoryDomain` categories;
  - thread-safe counters using C++20 atomics; no mutex, no blocking wait, no dynamic allocation;
  - release underflow is typed and non-mutating; zero bytes and invalid domain are typed failures;
  - snapshot is a non-transactional, per-counter read; after quiescence the invariant `allocated - released == live` holds.
- Explicit optional integration, defaulting to no telemetry:
  - `MemoryBlock::allocate` records the real allocation and `release` the real free;
  - `MonotonicArena` passes telemetry to its backing block and records successful slice events/high-water;
  - `MemoryBudget` records accepted reservations, releases, soft-pressure events and hard rejections;
  - `LeakTracker` records tracked/released token events and peak tracked bytes.
- Telemetry is never global, never intercepts `new/delete/malloc`, never stores pointers/addresses, and performs no I/O, export, sampling thread, timestamp or call-site capture.
- Tests include positive/negative/integration paths, concurrent updates and a report-only overhead benchmark; no latency threshold is ratified.

## Alternatives rejected

- **Global allocator interception:** rejected before ownership and instrumentation scope are qualified.
- **Mutex-protected counters:** rejected for the allocation path; atomics avoid locks and keep the primitive non-blocking.
- **Transactional snapshot:** rejected for this slice; a consistent global view would require a lock or epoch protocol and is deferred.
- **Pointer/call-site capture:** rejected; privacy, lifetime and overhead require a separate approved design.
- **Telemetry export/HTTP/Tracy integration:** rejected; export pipelines and third-party tooling are out of scope.
- **Mandatory telemetry in every allocation:** rejected; instrumentation is explicit and opt-in to preserve baseline behavior.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: TLM-01..TLM-06, per-domain accounting, underflow, integration with block/arena/budget/leak, concurrent final invariants, report-only benchmark, existing 99 Linux / 98 Windows/macOS CTests regression, Linux ASan/UBSan.
- Global export, sampling threads, call-site capture, pointer maps, SMF, frame/job barriers, ABI and release remain `NOT_QUALIFIED`.
- ADR-0004 `PROPOSED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the telemetry target/tests and the optional hooks restores prior behavior; no G2, registry or license change.
