# NLE-PRPLAN-CORE-01-16 — G6 activation (internal sequence closeout)

**Status:** `G6 CLOSEOUT PROPOSAL / DOCUMENTARY / PENDING AUDIT`. **Base main:** `30e254716b127b1a5ceb33c7527c3dd413c75665`. **Formal packet:** `NLE-PRPLAN-CORE-01-16`. **ADR:** [ADR-0095](../adr/0095-core-01-internal-sequence-closeout.md). **Contract:** [core-01-internal-sequence-closeout-v0](../contracts/core-01-internal-sequence-closeout-v0.md). **WO:** [NLE-PRPLAN-CORE-01-16](../work-orders/NLE-PRPLAN-CORE-01-16.md).

## Authorization

The owner authorized continuing on 2026-11-17 (`pode continuar autorizo`). This closeout is documentary: it closes the internal CORE-01 packet sequence `-03`..`-15`; it does **not** qualify the module/product, physical hardware, security, performance or release.

## Precedents

CORE-01 `-03`..`-15` and CORE-02-03 are `COMPLETED`. Latest matrix: 67 CTests on Linux, Linux ASan/UBSan, Windows and macOS; no HIGH/CRITICAL known; registry byte-identical; 80/80 module WOs BLOCKED.

## Bounded scope

Manifest root `CORE01_16_COMPLETED_REST_BLOCKED`; 15 completed, 4 approved, 0 ready, 729 blocked. Consolidated evidence/checkpoint. No engine code, new feature, dependency, license, G2 or registry change.

## Remaining NOT_QUALIFIED

Physical hardware, 30+30 timing, p95/p99/RSS/FPS, 32 scenarios, long soak, OS suspend/resume, Wayland runtime, IME/DPI/hotplug, security clearance, public ABI, NLE-D009 license, release, full CORE-01 module acceptance.

No code/native/performance PASS is claimed by this activation; only documentary closeout.
