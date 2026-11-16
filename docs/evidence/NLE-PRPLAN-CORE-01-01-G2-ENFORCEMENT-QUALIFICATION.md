# Evidence Bundle — G2 repository protection qualification (proposal only)

**DATE:** 2026-11-16 · **STATUS:** `DOCUMENTARY_PROPOSAL_ONLY / G2_BLOCKED_NOT_VERIFIED` · **STABLE WO:** [NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md) · [Issue #387](https://github.com/KayzenRoot/stormline/issues/387) **OPEN** · [G2 technical plan](../research/core-01-01-g2-branch-enforcement-qualification.md).

## Authority and Source Check (read-only)
Owner request: continue Stormline from exact HEAD `3cab84f0c9f346d82979b71ea67a5fd1047881aa` to **QUALIFY** the next NECESSARY G2 increment, with an explicit prohibition on modifying GitHub branch settings without a separate, explicit owner authorization. In this increment **NO protection rules/settings have been applied**, no state transition to G2 cleared, no ADR/license/code promotion. The already-owner-ratified `C01-D12` design direction is not evidence of authorization to enact the detailed new policy. Source hierarchy checked: checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > G2 gates/Security/WO.

**Git main BASE:** `3cab84f0c9f346d82979b71ea67a5fd1047881aa` verified using GitHub branch endpoint.

**Git blob SHA-1 (Git objects, not file SHA-256, from the pinned base):**
- `docs/00-source-hierarchy.md` `58a377bc76cafdd3377d733d4f30ef53661bb034`
- `docs/11-checkpoint.md` `e3cfa7766f22cabc8a02c4b2f982f29f1347105c`
- `docs/10-decisions-ledger.md` `98845bdaab2666cac2c48e89bc0f908d90145a7f`
- `docs/03-scope.md` `a6c213fac1514d721c5e212e87887eea81de18ef`
- `docs/09-definition-of-done.md` `082f8383b47f2bdc69d8d7c80812f3a94b0b96d1`
- `docs/04-architecture.md` `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md` `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/05-security.md` `eaa02b711f62498e41c82b6cb6615a94c375881c`
- `docs/06-test-benchmark-plan.md` `4c0be969744af6dd747cc828fbacc58662b06f40`
- `docs/adr/0003-core-01-platform-technology.md` `2ee92dda5ab81ddcc446b9d5325d29257350e217`
- `docs/adr/0075-qa-01-ci-matrix-security-policy.md` `22e91a36c1e0a8121163fa4778abd0489fed86e5`
- `docs/engineering/p00-technical-approval-gates.md` `7b144db5b51b24959f02aa1f1c4082bba4ec070c`
- `docs/engineering/core-01-01-qualification-gates.md` `5eea5015c5b41947b7446b0fba93a26c315ed4e2`
- `docs/work-orders/NLE-PRPLAN-CORE-01-01.md` `7c8147f2ef31a344eb8d6b5d41cd93a094eab71f`
- `docs/evidence/NLE-PRPLAN-CORE-01-01-G2G3-OWNER-RATIFICATION.md` `da9eeea9e2e9d2595dc426f4c0d313a891ef4d1f`
- `docs/08-backlog.md` `99a7471b33fd1bb9d08f8b295a7be1672900b4a3`
- `docs/pr-plans/CORE-01.md` `83c99b434fcca508913de2ddef5386a430065048`
- `.github/workflows/docs.yml` `c9d7b6688ed9484ecaf9968c9134bfaa70f73dc1`
- `docs/queue/implementation-registry.json` `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`
- `docs/pr-plans/manifest.json` `95782386c59e5af8ac1a8c92a7a35c87992463db`

**Context Lock stale rule:** checkpoint/Scope/DoD/Architecture/ADR/registry SHA changes => `STALE`, refresh/rebase before any merge. A future code executor must calculate raw SHA-256 and compare physical runtime evidence; above SHA-1 values should never be advertised as SHA-256.

## Read-only live GitHub data (not enforcement proof)

- `GET /repos/KayzenRoot/stormline` reports `private=false`, `visibility=public`, default `main`, owner type `User`, `allow_squash_merge=true`, `allow_merge_commit=true`, `allow_rebase_merge=true`. No repository-wide merge settings changed.
- `GET /repos/KayzenRoot/stormline/branches/main`: pinned SHA and `protected=false`.
- `GET /repos/KayzenRoot/stormline/rulesets`: `[]`.
- `GET /repos/KayzenRoot/stormline/branches/main/protection`: **403**, `Resource not accessible by integration`.
- Workflow `.github/workflows/docs.yml` read at pinned SHA: `name: Docs Validation`; `on: pull_request` and `push: main`; job `docs-validation`, `runs-on: ubuntu-latest`, `permissions: contents: read`, `actions/checkout@v7`, `persist-credentials: false`. No `pull_request_target`, path filters, job `if:` or merge_group event in that workflow.
- [PR #399](https://github.com/KayzenRoot/stormline/pull/399), [Docs CI #43901543824](https://github.com/KayzenRoot/stormline/actions/runs/43901543824), real `docs-validation` job #133419176724 SUCCESS. This proves **run availability**, not that it is required or enforced.
- GitHub official sources (verified via web 2026-11-16): [ruleset available rules](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/available-rules-for-rulesets), [ruleset creation](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/creating-rulesets-for-a-repository), [protected branches](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/about-protected-branches), [status checks](https://docs.github.com/en/pull-requests/reference/status-checks), [required-check troubleshooting](https://docs.github.com/en/pull-requests/how-tos/merge-and-close-pull-requests/troubleshooting-required-status-checks), [Actions billing](https://docs.github.com/en/actions/concepts/billing-and-usage), [public runners](https://docs.github.com/en/actions/how-tos/write-workflows/choose-where-workflows-run/choose-the-runner-for-a-job), [fork/PR security](https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target).

## Proposed G2 configuration, not enacted

**A preferred for separate owner selection:** active repository ruleset branch `main` requiring PR with zero external approvals, `docs-validation` successful and strict/up-to-date, linear history/squash, no force/delete, empty bypass list, no merge queue now, no unverified native check; fork isolation/read-only tokens and public standard GitHub runners R$0. **No settings mutation performed; not owner-ratified settings**. Alternative B classic protection with equivalent verified control; C voluntary PR+CI fails G2; D paid runners/reviewers/merge queue lacks scope and `merge_group`.

**Required future proof (all `FUTURE_NOT_EXECUTED`):** G2-P01 through G2-P12 enumerated in [G2 plan](../research/core-01-01-g2-branch-enforcement-qualification.md), including owner-authorized ruleset+privileged readback, exact required check/provider, red/missing check **denies merge** on safe PR, cannot bypass, restricted direct pushes/force/delete by safe policy proof, green squash allowed, no privilege/secrets in forks, free-runner billing and rollback/roll-forward evidence. **No negative enforcement probes, destructive push/merge, admin bypass tests or settings writes performed**.

## Negative proof and preserved critical invariants
- G1 `PARTIALLY_RATIFIED_NOT_CLEARED`, G2 `BLOCKED_NOT_VERIFIED`, G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`, G4-G8 blocked; 23 bounded owner technical directions **unchanged**, G2-P01..P12 and C01-Q001..Q032 not executed.
- ADR-0003 and ADR-0075 remain `PROPOSED`; engine source license `NLE-D009 OPEN`. No source LICENSE file/paid account / package/API configuration selected.
- 80/80 coding WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, 0 `executor_ready`, 0 `approved_adr`, 80 `release_class=UNDECIDED`, 80 `risk=UNCLASSIFIED`, `engine_implemented=false`; manifest CORE-01-01 and CORE-01-02 both `PLANNED_BLOCKED`, `github_pr=null` (field refers to future implementation packet, NOT documentation proposal PR).
- No native C++/SDL3/Windows/macOS/Linux/ABI/driver/GPU/compiler benchmark or runtime tests claimed.
- The only allowed new artifacts in this documentary proposal PR are this Evidence and the linked G2 plan (two ADDED Markdown). Any canonical docs, issue title/status, branch rules, workflow changes, registry/manifest/ADR/WO, code or version promotion are forbidden by scope.

## Evidence Bundle completion contract
- **Preflight:** only 2 ADDED Markdown; compare base/PR HEAD and immutable Git blob IDs; G2 state not promoted.
- **CI:** run observed `docs-validation` at **exact PR HEAD**, check whole job/steps and blocked-selector guard; no native CI claims.
- **Audit:** objective pt-BR review against Source Pack, C01-D12 bounded design, G2 proof gate, scope diff, CI statuses, trust boundaries and zero known HIGH/CRITICAL in doc diff. Veredict `APPROVED DOCUMENTARY ONLY` / `CORRECTION REQUIRED` / `BLOCKED`.
- **PR/merge:** squash normal with expected SHA after CI and audit; main readback. Then independently scoped **factual checkpoint PR** with its own CI/audit/squash/readback if due. Do not preclaim work not yet observed.
- **STOP:** stale HEAD, failed CI, unauthorized settings/write, license/ADR/queue promotion, claims of enforced G2 or release, or CORE-01-02/code start.
