# ADR-0092 — CORE-01 capability graph prototype and comparative measurement

**Status:** `OWNER_DIRECTION_C01_D10_BOUNDED_PROTOTYPE / NOT A SAPL ADOPTION / NO PERFORMANCE PASS / CONDITIONAL_ON_AUDIT_AND_MERGE`. **Subordinate to ADR-0003/0075, which remain PROPOSED; does not clear G3 globally.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-01-13` | **Parent:** `NLE-PRPLAN-CORE-01-01` | **Issue:** #387 / implementation issue #18.

## Context and authority

C01-D10 requires `SUPPORTED`/`UNSUPPORTED`/`UNKNOWN` capabilities with source/confidence, a thin adapter first and SAPL only after proof. The `-07`..`-12` slices are completed. The next formal packet `-13` is a comparative proof: unknown vs unsupported and capability-graph overhead vs thin SDL3.

No SAPL implementation exists, no owner-approved performance budget/hardware exists, and standard CI runners are noisy. This ADR therefore authorizes only a **report-only prototype measurement**; it does not adopt SAPL, does not set a performance threshold and does not decide the product architecture.

## Bounded technical decision

- New internal `CapabilityId`, `CapabilityState`, `CapabilitySource`, `CapabilityRecord`, `CapabilityGraph` in `capability_graph.hpp/cpp`.
- `CapabilityGraph` is a fixed-capacity, owner-thread data structure with explicit `Unknown`/`Supported`/`Unsupported` states and source metadata; no dynamic allocation, no hidden global.
- `CapabilityProbe` maps the active SDL3 runtime to a small capability set:
  - video/events: `Unknown` before runtime init, `Supported` after;
  - window/displays: `Unknown` before video init, `Supported` after;
  - Wayland runtime: `Unknown` without a driver, `Supported` on Wayland, `Unsupported` on other real drivers; dummy/offscreen remains `Unknown`.
- A deterministic benchmark compares **capability-graph lookup** with a **direct `SDL_WasInit` query** at a fixed iteration count and prints ns/op plus ratio. It asserts only correctness, never a performance threshold. Values are reported in the Evidence Bundle; no PASS/FAIL performance claim.
- No direct OS API, no SAPL production layer, no public ABI, no renderer/GPU/audio, no release.

## Alternatives rejected

- **Adopt SAPL now:** rejected; no proof, no approved budget/hardware, and C01-D10 requires thin adapter first.
- **Claim a performance PASS from CI:** rejected; shared runners are noisy and no owner-approved threshold exists.
- **Benchmark only synthetic graph operations:** rejected; the comparison must include the thin SDL3 query baseline.
- **Dynamic graph allocation:** rejected; fixed capacity keeps the prototype deterministic and allocation-free.
- **Treat Unknown as Unsupported:** rejected; the distinction is the core acceptance obligation.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: CAP-01..CAP-06, unknown/supported/unsupported, probe before/after runtime init, real-driver Wayland unsupported, wrong-thread, deterministic benchmark output, existing 59 CTests regression, Linux ASan/UBSan.
- The benchmark is **report-only**: no speedup claim, no SAPL adoption, no decision on product architecture. A future owner-approved benchmark WO with named hardware/thresholds is required for any performance verdict.
- ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the capability-graph target/tests/benchmark and evidence restores the previous state; no G2, registry or license change is part of this ADR.
