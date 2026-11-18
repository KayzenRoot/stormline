# ADR-0098 — CORE-02 memory budget slice

**Status:** `OWNER_DIRECTION_CAPABILITY_BASED_L1 / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **Subordinate to ADR-0004, which remains `PROPOSED`; does not approve SMF, a release class or G3 globally.**

**Date:** 2026-11-18 | **WO:** `NLE-PRPLAN-CORE-02-06` | **Parent:** `NLE-PRPLAN-CORE-02-01` | **Issue:** #19.

## Context and authority

CORE-02-03/04/05 delivered ownership, the system allocator baseline and a monotonic arena. The next planned packet `-06` is budgets. ADR-0004 proposes soft/hard watermarks, pressure events and optional reclaim hooks; the Stormline Memory Fabric is a research hypothesis. This slice is the deterministic **budget accounting primitive** only.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`; no window/input/DPI/IME/hotplug/soak capability used. Admission expires at closeout.

## Bounded technical decision

- New internal `BudgetStatus` (`Within`, `SoftPressure`, `HardLimit`), `BudgetError` and `MemoryBudget`:
  - fixed soft/hard limits with `hard >= soft > 0`; invalid construction is typed and invalid;
  - `try_reserve(bytes)` atomically checks the hard limit, reserves bytes, and reports `SoftPressure` when usage crosses the soft limit;
  - hard-limit rejection is non-mutating; zero bytes/invalid state are typed;
  - `release(bytes)` is non-mutating on underflow; exact accounting; no implicit clamp;
  - owner-thread mutation; queries used/limits/remaining/status/valid; no exceptions across the API.
- No actual allocation interception, no SMF budget graph, no reclaim hooks, no telemetry, no leak tracking, no frame/job barriers, no global budget, no public ABI.
- Tests use a deterministic accounting oracle, not timing.

## Alternatives rejected

- **Soft limit as a hard rejection:** rejected; soft pressure must be observable while reserving up to the hard limit.
- **Automatic clamp/underflow recovery:** rejected; silent corruption of accounting is forbidden.
- **Global budget:** rejected; explicit instance/lifetime only.
- **Integrate arena/system allocations immediately:** rejected; accounting primitive first, wiring later with an approved contract.
- **SMF/reclaim first:** rejected; research hypothesis without measured evidence.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: BGT-01..BGT-06, limits/soft/hard, non-mutating rejection, release underflow, 1000 cycles, wrong-thread, existing 80 CTests regression, Linux ASan/UBSan.
- Allocation wiring, reclaim/telemetry/leak integration, SMF, frame/job barriers, ABI and release remain `NOT_QUALIFIED`.
- ADR-0004 `PROPOSED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the budget target/tests/evidence restores the previous state; no G2, registry or license change.
