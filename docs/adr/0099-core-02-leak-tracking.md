# ADR-0099 — CORE-02 explicit leak-tracking slice

**Status:** `OWNER_DIRECTION_CAPABILITY_BASED_L1 / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **Subordinate to ADR-0004, which remains `PROPOSED`; does not approve allocation interception, a release class or G3 globally.**

**Date:** 2026-11-18 | **WO:** `NLE-PRPLAN-CORE-02-07` | **Parent:** `NLE-PRPLAN-CORE-02-01` | **Issue:** #19.

## Context and authority

CORE-02-03/04/05/06 delivered ownership, the system allocator baseline, a monotonic arena and soft/hard budget accounting. The next planned packet `-07` is leak tracking. ADR-0004 requires leak detection in reproducible load, but early CORE-02 slices explicitly avoid process-global allocator interception. This slice therefore provides an explicit, opt-in bookkeeping primitive rather than allocator instrumentation.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`; no window/input/DPI/IME/hotplug/soak capability used. Admission expires at closeout.

## Bounded technical decision

- New internal `LeakToken`, `LeakError` and fixed-capacity `LeakTracker`:
  - caller explicitly tracks a byte count and receives a generation-checked token;
  - releasing the token removes exactly that tracked entry; double release, stale generation and out-of-range tokens are typed non-mutating failures;
  - capacity exhaustion is typed and non-mutating; releasing an entry frees a slot for reuse with a new generation;
  - live allocation/byte counters and monotonic peak counters are queryable; `empty()` reports no outstanding tracked entries;
  - owner-thread mutation; no dynamic allocation, no pointer capture, no exceptions across the API.
- A "leak" in this slice means an outstanding tracked token at a checkpoint. It is not proof of process-wide or third-party leaks.
- No `new/delete`/`malloc` interception, no global registry, no pointer map, no telemetry export, no I/O, no frame/job barrier, no SMF integration, no public ABI.
- Tests use deterministic counter/token oracles, not timing.

## Alternatives rejected

- **Global allocation hook:** rejected; it would intercept all process allocations before ownership, arena and budget integration are qualified.
- **Pointer-address map:** rejected; stores addresses, complicates privacy/diagnostics, and requires interception to be useful.
- **Size-only counters:** rejected; they cannot detect double release, stale tokens or capacity reuse.
- **Dynamic slot container:** rejected; the tracker must not allocate memory while tracking memory.
- **Automatic destructor leak report:** rejected; reporting/telemetry ownership belongs to a later approved slice.
- **Integrate with `MemoryBlock`/`MonotonicArena` immediately:** rejected; an explicit token primitive first, wiring later with an approved contract.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: LKT-01..LKT-06, basic accounting, invalid bytes, capacity exhaustion/reuse, stale/forged/double-release tokens, 1000 cycles, wrong-thread, existing 86 CTests regression, Linux ASan/UBSan.
- Allocation interception/wiring, pointer tracking, telemetry, reporting, SMF, frame/job barriers, ABI and release remain `NOT_QUALIFIED`.
- ADR-0004 `PROPOSED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the leak-tracker target/tests/evidence restores the previous state; no G2, registry or license change.
