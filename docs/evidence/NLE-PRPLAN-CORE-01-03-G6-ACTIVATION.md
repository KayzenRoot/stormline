# NLE-PRPLAN-CORE-01-03 — G6 one-packet activation Evidence (PROPOSED)

**Risk:** STANDARD first INTERNAL_ONLY CORE-01 slice. **Base main:** `c355de53bca5be1d64dedb4d7111bd40c8859e83`. This gate PR does **not** implement C++, approve global ADR-0003/G3 or distribute any binary.

## Authorization and predecessors
The user expressly ratified the narrow first CORE-01 code path in conversation. [PR #422](https://github.com/KayzenRoot/stormline/pull/422) ratification, [#423](https://github.com/KayzenRoot/stormline/pull/423) checkpoint, [#424](https://github.com/KayzenRoot/stormline/pull/424) bounded typed contract/ADR-0083 G4/G5, [#425](https://github.com/KayzenRoot/stormline/pull/425) checkpoint all squash merged and readback. [PR #421](https://github.com/KayzenRoot/stormline/pull/421) experimental native fixture 3/3 PASS only; not product proof.

## Gate claim and invariants to prove by CI
Exactly one packet `NLE-PRPLAN-CORE-01-03` may be individually selected after a green/approved G6 PR. Module-level registry of **all 80** WOs stays unchanged and BLOCKED. Manifest records 2 approved documentary predecessors, 1 READY packet and 745 PLANNED_BLOCKED, 748 total. All other module and packet selections exit blocked. A fail-closed activation JSON pins owner ratification, contract/ADR, class INTERNAL_ONLY, risk STANDARD, historical source fingerprints and fresh-lock requirement. No default approval of any other id.

## Deterministic tests to audit
- Existing `validate_wo_registry.py` still refuses any module-level activation and `select_wo.py CORE-01` exits 2.
- Updated `validate_pr_plans.py` requires exact G6 activation allowlist; missing/forged consent, toolchain, risk, fingerprint, or another packet READY are errors.
- Unit tests cover wrong packet, second readiness, false owner proof, altered SHA, wrong risk, wrong PR, wrong module registry status, missing docs/contract.
- `select_packet.py NLE-PRPLAN-CORE-01-03` is the ONLY allowed ready selector and itself reruns full validation. Other IDs exit 2.
- Docs Validation exact HEAD and audit pt-BR, all negative proof receipts. NO native product tests in this gate PR; those belong to code PR -03.

## Security, cost and recovery
Only source-controlled docs/scripts, no live workflow/settings, no secrets/payment/new dependency, no new CI runner. Selector fail-closed rather than bypass, ruleset 27393227 untouched. Future code PR requires fresh SHA-256 Source Lock, no HIGH/CRITICAL and standard public CI. If a validator regression occurs, CORRECTION REQUIRED same PR; if unmitigable, BLOCKED. On future revocation use normal PR, never force push.

## Gating outcome
**PENDING:** actual head SHA, Docs Validation and negative-tests pass, security audit, squash and main readback. No automatic G3/global ADR approval, NLE-D009 stays OPEN. After approved gate, first -03 PR may be opened only with fresh Source Check and final bounded executor review.
