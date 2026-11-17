# ADR-0095 — CORE-01 internal packet-sequence closeout

**Status:** `INTERNAL_SEQUENCE_CLOSEOUT / NOT MODULE QUALIFICATION / NOT RELEASE`. **Subordinate to ADR-0003/0075; does not clear G3, license, physical hardware or product release.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-01-16` | **Parent:** `NLE-PRPLAN-CORE-01-01` | **Issue:** #387 / implementation issue #18.

## Decision

Close the **internal CORE-01 packet sequence** `-03`..`-15` in the PR-plan manifest. This is a documentary closeout of the bounded internal increments, not a claim that CORE-01 is fully qualified as a module/product.

The sequence delivered: headless host, portable paths, SDL3 runtime, native window, event queue/replay, display/surface, native window-handle bridge, lifecycle request state machine, capability-graph prototype/report-only measurement, multi-OS soak harness and integrated CI qualification.

## Evidence basis

- `-03`..`-15` are `COMPLETED` and CORE-02-03 is `COMPLETED`; 67 CTests pass on Linux, Linux ASan/UBSan, Windows and macOS at the latest heads.
- `-14` ran 200 headless / 100 window / 10,000 events; `-15` ran 200 headless / 10 init-quit+window / 25 window / 10,000 events with zero live headless resources.
- All code PRs have exact-head Docs Validation, native CI, pt-BR audit and squash/readback; no HIGH/CRITICAL known.
- Registry remains byte-identical; 80/80 module implementation WOs remain `BLOCKED`.

## Explicitly not closed / not qualified

- Physical Windows/Linux/macOS hardware, GPU/driver/display certification.
- 30 cold + 30 warm timing, p50/p95/p99, RSS/VRAM/FPS budgets.
- 32 future scenarios, long-duration soak, OS suspend/resume signals, Wayland runtime, IME/DPI/hotplug.
- Security clearance, public ABI/plugin SDK, NLE-D009 license, distribution/release.
- CORE-01 module acceptance as a whole; `engine_implemented=false` at module/product level.

## Consequence

- Manifest root becomes `CORE01_16_COMPLETED_REST_BLOCKED`: the internal sequence is closed; every other module/packet remains blocked.
- No next module/packet is authorized. CORE-02-04 (allocators) and other L1 work require a new gate/contract/owner technology decision.
- No product release, brand, license or physical-platform claim follows from this closeout.

## Rollback

Unmerged: close the branch. After merge: normal revert PR, never force push. This ADR changes only planning/evidence/checkpoint state; no engine code, registry, G2 or license change.
