# CORE-01 Internal Sequence Closeout Contract v0 (NLE-PRPLAN-CORE-01-16)

**Status:** `CLOSEOUT CONTRACT / DOCUMENTARY / NOT MODULE QUALIFICATION`. **Base:** `30e254716b127b1a5ceb33c7527c3dd413c75665`. **ADR:** [ADR-0095](../adr/0095-core-01-internal-sequence-closeout.md).

## Closeout checklist

1. CORE-01 `-03`..`-15` are `COMPLETED` with merged PRs and evidence.
2. CORE-02-03 ownership is `COMPLETED` and unaffected.
3. Latest native matrix: Linux, Linux ASan/UBSan, Windows and macOS; 67 CTests.
4. No HIGH/CRITICAL known; all code PRs audited `APPROVED`.
5. Registry byte-identical; 80/80 module WOs `BLOCKED`.
6. Manifest root `CORE01_16_COMPLETED_REST_BLOCKED`; no `EXECUTOR_READY`.
7. Checkpoint/evidence record the closeout and the explicit `NOT_QUALIFIED` list.

## Not qualified (must remain explicit)

Physical hardware, 30+30 timing, p95/p99/RSS/FPS, 32 scenarios, long soak, OS suspend/resume, Wayland runtime, IME/DPI/hotplug, security clearance, public ABI, NLE-D009 license, release, full CORE-01 module acceptance.

## Exact allowlist

1. `docs/adr/0095-core-01-internal-sequence-closeout.md`
2. `docs/contracts/core-01-internal-sequence-closeout-v0.md`
3. `docs/work-orders/NLE-PRPLAN-CORE-01-16.md`
4. `docs/evidence/NLE-PRPLAN-CORE-01-16-G6-ACTIVATION.md`
5. `docs/evidence/NLE-PRPLAN-CORE-01-16.md`
6. `docs/queue/packet-activation-core-01-16.json`
7. `docs/pr-plans/manifest.json`
8. `docs/11-checkpoint.md`
9. `scripts/validate_pr_plans.py`
10. `scripts/test_validate_pr_plans.py`

No engine code, registry, G2, workflow, dependency or license change.

## Stop / rollback

Stop on stale source, missing precedent, count mismatch, ready packet, HIGH/CRITICAL, module/product/release overclaim or registry change. Unmerged: close branch; after merge: normal revert PR, never force push.
