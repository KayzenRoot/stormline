# NLE-PRPLAN-CORE-01-02 — Typed Internal Headless Contract Evidence (PROPOSED)

**Base:** `13b316153d817b7a49fd1d82ccd7193faa5a50f0`. **Scope:** contract-only for owner-ratified first CORE-01 slice. **No new native test and no implementation** in this PR.

## Authorization and precedence
- Owner's explicit 2026-11-17 Option A vote is recorded by [PR #422](https://github.com/KayzenRoot/stormline/pull/422), [audit](https://github.com/KayzenRoot/stormline/pull/422#issuecomment-6954281523), [checkpoint PR #423](https://github.com/KayzenRoot/stormline/pull/423). Prior issue [proposal #6954081280](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6954081280) was a recommendation, not the vote.
- Source Check main SHA fixed; Ledger, Scope and DoD have bounded ratification, ADR-0003/0075 overall PROPOSED, no NLE-D009.
- Existing native experiment [PR #421](https://github.com/KayzenRoot/stormline/pull/421) remains Draft; [run #44124073355](https://github.com/KayzenRoot/stormline/actions/runs/44124073355): 3/3 C++20 fixture native 1/1 CTest per OS, but no integrated host, target toolchain pin, SDK qualification or public ABI.

## Specific technical review criteria
- Simple internal design without unnecessary SDL/OS dependencies, ownership leaks, privilege or network; no external release claim.
- `HostState`/`HostError`/`HostConfig`/`HeadlessHost` interface and state table, no-copy/no-move RAII, no-throw destructor, injected rollback failures and repeat stop idempotence are specified.
- Exactly C01-INT-01..10 future test obligations with per-runner logs and sanitizer rule.
- Risk STANDARD explicitly limited to first internal slice, no paid service/secret or vendor code; proposed use of standard library only.
- Future code files allowlisted, no product implementation claimed in contract PR; G6 promotion requires an explicitly safe gate-aware change because current `scripts/validate_wo_registry.py` deliberately enforces all 80 WOs BLOCKED and `scripts/select_wo.py` denies selection. These safeguards MUST NOT be bypassed or turned off for 79 others. Future gate PR needs authorized, positive per-packet proof and negative regression checks.

## Source/gate status
G1 global PARTIAL; G2 CLEARED bounded ruleset 27393227; G3 global NOT_CLEARED; G4 only the proposed bounded ADR-0083 pending review/merge; G5 only proposed accepted proof plan pending review/merge; G6 BLOCKED; G7 NOT_EXECUTED; ADR-0003/0075 PROPOSED; NLE-D009 OPEN, 80 blocked code WOs, 748 planned blocked, 0 ready, engine=false.

## CI / audit / readiness
PENDING this PR exact-head Docs Validation, files/scope/contract audit pt-BR and merge/readback. On approval, record bounded G4/G5 contract accepted for INTERNAL_ONLY scope only; do NOT set global G3 CLEARED or activate -03. Reviewer is same assistant context; do not claim independent reviewer. Checkpoint Delta PROPOSED, separate only after actual merge.
