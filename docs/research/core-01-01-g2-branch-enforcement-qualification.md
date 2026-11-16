# CORE-01-01 / G2 — Branch protection, required checks and zero-cost CI qualification

**Document type:** recommendation and future enforcement plan, **NOT A GITHUB SETTINGS CHANGE**. **Date:** 2026-11-16. **Status:** `PROPOSED_G2_ENFORCEMENT_CONFIG_NOT_AUTHORIZED / G2_BLOCKED_NOT_VERIFIED`. **Same stable Work Order:** [NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md), **owner issue:** [#387](https://github.com/KayzenRoot/stormline/issues/387), **base main:** `3cab84f0c9f346d82979b71ea67a5fd1047881aa`. [Evidence/Source Lock](../evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-QUALIFICATION.md).

## Authority and Source Check

The owner **already ratified the bounded G2 design direction** `C01-D12 OWNER_RATIFIED_G2G3_BOUNDED`: free CI, isolated untrusted PRs and eventual enforceable rules subject to explicit authorization/proof. The present request authorizes **QUALIFYING and documenting** a concrete settings proposal, and **expressly forbids changing branch settings** without a **separate, explicit authorization**. This proposal is not a newly ratified ruleset; no user/owner selection of any JSON options below is inferred by documentation, CI, or squash.

Canonical source hierarchy: checkpoint > Decisions Ledger / approved ADRs > Scope > DoD > Architecture > Requirements > subsidiary G2 gates/WO/evidence. Follow [G0–G8 global approval gates](../engineering/p00-technical-approval-gates.md), [CORE-01 gate matrix](../engineering/core-01-01-qualification-gates.md), [Ledger](../10-decisions-ledger.md), [Security](../05-security.md) and [QA-01 ADR-0075 PROPOSED](../adr/0075-qa-01-ci-matrix-security-policy.md). Preserve 23 existing bounded owner decisions and G1 `PARTIALLY_RATIFIED_NOT_CLEARED`, G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`, G4+ blocked.

## Observed GitHub account/repository settings (read-only)

| Evidence and inspected source | Actual result at base | Interpretation |
|---|---|---|
| `GET /repos/KayzenRoot/stormline` | `private=false`, `visibility=public`, `default_branch=main`, owner type User, `allow_squash_merge=true`, also merge/rebase permitted by repository | Standard GitHub-hosted Actions runners are free **while repo remains public**; repository merge settings alone do not enforce linear history |
| `GET /repos/KayzenRoot/stormline/branches/main` | exact base HEAD, `protected=false` | There is no confirmed branch-protection enforcement |
| `GET /repos/KayzenRoot/stormline/rulesets` | `[]` | No repository ruleset visible in this endpoint; do not infer another hidden effective policy |
| `GET /repos/KayzenRoot/stormline/branches/main/protection` | HTTP `403 Resource not accessible by integration` | Detailed branch protection readback **unavailable** with this connector; not proof of protections |
| Existing [`.github/workflows/docs.yml`](../../.github/workflows/docs.yml) | workflow **`Docs Validation`**, PR + push-main triggers, job key & name **`docs-validation`**, `ubuntu-latest`, `permissions: contents: read`, `actions/checkout@v7` with `persist-credentials: false`, timeout 5m, no path filters, no `pull_request_target` in this inspected workflow | This is the **only presently confirmed job-name candidate** for a required check. All other workflow names, native check jobs and check providers need inventory/verification |
| [Previous PR #399](https://github.com/KayzenRoot/stormline/pull/399) | [Docs Validation run #43901543824](https://github.com/KayzenRoot/stormline/actions/runs/43901543824), job `docs-validation` #133419176724 SUCCESS | Real check has run successfully on a PR; **not** proof it is required or resistant to bypass |

**G2 = `BLOCKED_NOT_VERIFIED`**. A green Docs Validation check is **not evidence that a red/absent check blocks merging**.

## Recommended minimum G2 settings proposal A (for a separate owner-authorized change)

Create **one repository-level active ruleset targeting only `refs/heads/main`** (not a template applied to every branch and not a change to this PR); do not create an overlapping second branch-protection rule without reconciling precedence. Proposed rule contents:

| G2 setting | A: preferred proposed value | Why, trade-off and activation guard |
|---|---|---|
| Scope and enforcement | Repository `KayzenRoot/stormline`, only branch `main`; `enforcement=active` **only after separate owner authorization** | Rulesets are auditable and can combine constraints. Do not activate by this document |
| Require pull request | **ON** for all main updates, with **zero required approvals** (`required_approving_review_count=0` if supported by chosen API/UI); no required code-owner review, last-push approval or external reviewer | Preserves solo owner + mandatory PR/evidence. Fewer human checks is a known risk offset by objective audit and CI |
| Required status checks | **One initially:** exact observed job `docs-validation`; verify unique check context/provider (GitHub Actions) in PR checks before binding; status must pass against current evaluated commit | Native Windows/Linux/macOS/GPU checks **do not yet exist as verified runnable jobs**. Never require invented or conditional job names |
| Up-to-date | **Strict** required check, feature `require branches to be up to date` | More reruns/rebases after base moves, but prevents stale test merges. A `git push --dry-run` alone cannot prove enforcement |
| Merge policy | **Require linear history**; continue documented normal **squash PR merges**; do not modify repository-wide allowed merge methods yet | Avoids merge commits on main. Check that bot/integration PR merge still functions under rules and **no bypass** |
| Force-push and deletion | **Block force pushes**; **restrict deletion** of main | Protects history and refs, but avoid disruptive/unsafe tests directly on main |
| Bypass | **No bypass actors, roles, apps or owner override** in the proposed ruleset; inspect all effective rules and privileges before declaring `NO_BYPASS_PROVEN` | A ruleset's bypass list is separate from admin/role permissions and other effective policies. Zero entries is a target, NOT proof until readback |
| Other requirements | Do **not** demand signed commits, merge queue, deployments, code owner approval, required last-push approval, paid security gates, speculative native jobs or strict code coverage in this increment | These can deadlock a solo repo or add cost, and have not been qualified. Future proposals need separate explicit owner choice |
| Safe rollout | Inventory actual workflows/check runs and authoritative `main` effective rules; validate owner credentials, required-check provider, restore/readback access, and reversal via separate approved order | Enabling rules is a privileged operation and may block automation, including the current GitHub connector. **No changes now** |

**Alternative B:** classic branch protection rule with required PR/zero reviews, strict `docs-validation`, no admin bypass and no force/deletion. Might fit supported permissions better but suffers from single matching protection rule precedence and requires equivalent readback. **Alternative C:** keep PR+CI voluntary without enforced checks: cheap, but **fails G2** and allows a bad merge. **Alternative D:** merge queue/mandatory reviewers/paid runners: higher sophistication/cost or unsatisfied required `merge_group` event, inconsistent with solo owner + current workflow.

### Important check-provider and event caveats
- A required check uses **the exact job/check name**, *not* the workflow label. Observed job name is `docs-validation`; `Docs Validation` is a display workflow name. Future native jobs should be required only after a genuine PR run yields their exact unique check names and trusted app/provider.
- Check source app must be verified from actual Check Runs (rather than presuming an app ID). Duplicate job names across multiple workflows can create ambiguous status and prevent merge.
- The required job must execute on **every relevant PR** and should not be skipped by `paths`, `paths-ignore`, branch filters, untrusted commit trailers or a conditional job that is reported as `skipped`; skipped jobs can appear successful. The inspected docs workflow has `pull_request:` and no path filters or per-job `if:`, but complete workflow/job inventory is still needed.
- **Do not enable merge queue** for this workflow as it lacks `merge_group:` trigger; a required queue check would never report, blocking merge.
- Strict up-to-date checks require rechecking the latest branch/test merge SHA after main changes. Intentionally missing/failing checks must be observed **blocked**, not simply assumed blocked from a green run.

## R$0 CI and fork trust-boundary

**Observed current baseline:** `Docs Validation` on a standard GitHub-hosted Ubuntu runner, public personal repository. GitHub currently documents standard hosted runners as free for public repositories, including Windows/Linux/macOS **standard sizes**; larger runners can incur charges and artifact/storage and abuse limits are distinct. Keep public-repo exposure and storage/visibility choices separate from the unresolved `NLE-D009` engine-source license. No engine code or commercial binary release authorized.

**Minimum trust-separated design:** `pull_request` event for untrusted content, `GITHUB_TOKEN` `contents: read`, `persist-credentials:false`, no secrets/production deployments for PR workflows; no pull_request_target checkout+execute of untrusted fork, no privileged `workflow_run` that consumes untrusted PR artifacts as executable code, no elevated packages/signing tokens, no PR-controlled path input to privileged jobs; resolve all actions to reviewed/pinned versions in a **separate, authorized CI-hardening WO** if necessary. Fork code can still abuse runner compute/deliver malicious test output: limit permissions, concurrency, timeouts, cache/artifact trust and approvals of new external contributors. Repo-wide workflow inventory and effective org settings are required before G2 close.

**Proposed future native matrix, NOT configured now:** after tech/ABI G3 qualifies, discover and separately approve true runnable `ubuntu-24.04`, `windows-2025`, `macos-15` Apple arm64 build/test jobs (runner images are **not identical** to the owner-ratified target OS release floors or physical hardware). Pin labels, toolchains, build inputs and job names via actual PR runs, then separately add **only proven jobs** to G2 mandatory checks. Do not pretend Docs Validation replaces C++/sanitizer/hardware tests.

## Future G2 proof obligations (not executed)

| Proof ID | Objective evidence required after separately authorized settings write | Status |
|---|---|---|
| G2-P01 | Base SHA/Source Lock and owner-accepted exact settings diff/ruleset version, no unapproved rule | `FUTURE_NOT_EXECUTED` |
| G2-P02 | Enabled ruleset targets only `refs/heads/main`, active enforcement, GitHub API/UI readback with sufficient permission | `FUTURE_NOT_EXECUTED` |
| G2-P03 | Required PR verified, `required_approving_review_count=0` and no codeowner/last-push approval requirement | `FUTURE_NOT_EXECUTED` |
| G2-P04 | Exact `docs-validation` required check/provider confirmed **unique, produced, up-to-date and not skipped** | `FUTURE_NOT_EXECUTED` |
| G2-P05 | Missing/failing check on safe, disposable **nonproduction PR** demonstrably blocks merge (no destructive direct push); re-run green then merge allowed | `FUTURE_NOT_EXECUTED` |
| G2-P06 | Direct main update without PR is denied, evidenced by non-destructive controlled test or permission-backed enforcement proof; **no actual destructive push on main** | `FUTURE_NOT_EXECUTED` |
| G2-P07 | Force-push and branch deletion disabled in effective config and via safe/non-destructive readback, never attempt actual destructive operation | `FUTURE_NOT_EXECUTED` |
| G2-P08 | Bypass actors/roles/apps empty and effective admin permissions/bypass independently checked; admin/bot cannot silently skip required check | `FUTURE_NOT_EXECUTED` |
| G2-P09 | Squash merge with strict checks still functions for actual authorized automation, and stale base requires new eligible check | `FUTURE_NOT_EXECUTED` |
| G2-P10 | Fork PR: token read-only, secrets withheld, no privileged PR-head execution or unsafe artifact promotion; prove via sanitized logs/policy | `FUTURE_NOT_EXECUTED` |
| G2-P11 | GitHub Actions public repo standard runner and billing/usage evidence consistent with R$0 policy; no larger/billable runners | `FUTURE_NOT_EXECUTED` |
| G2-P12 | Owner sees readback/rollback instructions for ruleset and separately audits the G2 gate; exact new HEAD + CI + checkpoint recorded | `FUTURE_NOT_EXECUTED` |

**Safe rollout/rollback design only:** separate explicitly approved and auditable GitHub-settings Work Order, read current effective rules, record JSON before/after and required check source; apply candidate in narrow scope; run safe negative tests, review result; if it blocks legitimate automation, **owner-authorized rollback to previously captured settings**, audit and restore G2 `BLOCKED_NOT_VERIFIED`. Never disable real protections merely for passing a documentary PR. Any missing evidence = G2 `BLOCKED_NOT_VERIFIED`.

## Risk analysis and blockers

| Risk | Severity if activated incorrectly | Controls and current disposition |
|---|---|---|
| Docs CI passes but is not required; red CI can merge | HIGH | Require concrete ruleset and negative merge denial, **not currently proven** |
| No bypass list but admin/app still bypasses or overlapping rule overrides | HIGH | Effective permission/UI+API readback and independent negative evidence, **pending** |
| Wrong/unavailable check name or merge queue without `merge_group` | STANDARD–ELEVATED (release blockage) | Require only observed `docs-validation`, strict context/app uniqueness check |
| Public fork secretly accesses privileged token/artifact or paid runner | HIGH | PR trust separation, no secrets/privileged PR execution, controls test to prove, **pending** |
| Required reviews introduced for single owner | STANDARD (deadlock) | `required_approving_review_count=0`; no external-review or CODEOWNERS requirement |
| Strict checks cause churn during concurrent merges | STANDARD | Update branch and re-run, keep small solo PRs; accept rerun overhead |
| GitHub public repo exposes unpublished intellectual property or private artifacts | ELEVATED | Separate NLE-D009/source-distribution decision, no code pushed as part of G2 qualification |
| Rule setup credential lacks readback (API 403) | ELEVATED | Ensure authorized token/UI readback BEFORE mutation; else BLOCKED |

**This document's change risk is LOW DOCUMENTARY. A future privileged settings mutation is an ELEVATED-risk task and needs an independent owner authorization, rollback and audit.**

## Same stable Work Order / next necessary increment

- **OBJECTIVE:** specify G2 minimum effective protection for `main`, required checks, solo-workflow, fork isolation and R$0 CI, with measurable proofs; preserve open gate.
- **CONTEXT:** Source Check main at fixed base, 23 previously ratified bounded G1/G2/G3 decisions, `C01-D12` accepts *desired design direction* but does not enable G2 settings.
- **SCOPE:** this technical choices + proof matrix and one independent Evidence/Context Lock Markdown only; later factual checkpoint separated after documentary PR approves.
- **OUT OF SCOPE:** ruleset/protection API mutations, other GitHub settings/workflows, code, native tests, ADR/Source license/queue/registry/manifest, CORE-01-02.
- **FILES/SOURCES TO READ:** checkpoint, Ledger/ADRs, Scope, DoD, Architecture, Requirements, Security, G0–G8 gates, current docs workflow, GitHub settings readback, official GitHub rule/Actions docs.
- **REQUIREMENTS:** PR-only proposal with exact existing job, zero external reviewers, no bypass, strict CI, no force/delete, no paid runners or unsafe forks, G2 blocked until proof.
- **ARCHITECTURE RULES:** CI job ≠ compiled engine; runner image ≠ target platform certified; separate QA-01 code CI future, no new DAG dependencies.
- **CONSTRAINTS:** same `NLE-PRPLAN-CORE-01-01` ID, no new coding WO nor approvals inferred, no external reviewer requirement, low-cost documentary.
- **ACCEPTANCE CRITERIA:** exactly 2 new Markdown, accurate negative branch evidence, named required check verified, 12 unexecuted proof obligations, 0 branch settings/code/ADR/registry changes, G2 still BLOCKED_NOT_VERIFIED.
- **TESTS:** on exact documentary PR HEAD, Docs Validation/links/DAG/registry/Zcode guard and PR-plan tests only, compare scope/Source Lock, independent objective pt-BR audit; no native or negative enforcement tests executed now.
- **DELIVERABLES:** G2 plan, Evidence Bundle, PR+CI+auditoria/squash/readback, separate factual checkpoint PR if documentary audit APPROVED.
- **REVIEW FORMAT:** APPROVED DOCUMENTARY ONLY / CORRECTION REQUIRED / BLOCKED, with base/head and tests, denial/readback gaps identified.
- **STOP CONDITION:** stale source, failed CI, high/critical issue, any unauthorized G2 settings, code, license, ADR, registry/manifest or package 02 advancement, any G2 gate promotion from docs.

## Official upstream reference URLs (verified 2026-11-16)
- [GitHub rulesets](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/available-rules-for-rulesets), [creating rulesets](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/creating-rulesets-for-a-repository), [branch protection](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/about-protected-branches).
- [GitHub status checks and skipped job limitations](https://docs.github.com/en/pull-requests/reference/status-checks), [troubleshoot required checks / merge_group](https://docs.github.com/en/pull-requests/how-tos/merge-and-close-pull-requests/troubleshooting-required-status-checks).
- [GitHub Actions billing](https://docs.github.com/en/actions/concepts/billing-and-usage), [standard public runners](https://docs.github.com/en/actions/how-tos/write-workflows/choose-where-workflows-run/choose-the-runner-for-a-job), [secure pull_request_target](https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target).

**STOP HERE:** Do NOT interpret these recommended settings or passing Docs CI as approval/implementation of branch protection. `G2=BLOCKED_NOT_VERIFIED`; G1 partial, G3 technical gate open, G4-G8 blocked; `NLE-D009 OPEN`, ADR-0003/0075 PROPOSED, 80 code WOs BLOCKED, CORE-01-02 PLANNED_BLOCKED, engine_implemented=false.
