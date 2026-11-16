# CORE-01-01 / G2 — Branch protection, required checks and zero-cost CI qualification

**Document type:** applied enforcement record plus the original authorization plan, **NOT A PENDING SETTINGS PROPOSAL**. **Date:** 2026-11-16. **Status:** `G2_CLEARED` — one active repository ruleset (`g2-main-enforcement`, id `27393227`) exclusively on `refs/heads/main`, with real negative and positive enforcement probes. **Same stable Work Order:** [NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md), **owner issue:** [#387](https://github.com/KayzenRoot/stormline/issues/387), **base main before the authorized write:** `0ef8eb69baac03b805f11af6c29a053185128b6f`, **main readback after evidence merge:** `80624f6320578f49a16030f8c42e03ddd49afbba`. [Applied Evidence Bundle](../evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-APPLIED.md). The historical proposal text below is preserved as the authorization record that was executed; it is not a set of pending actions.

> **APPLIED RESULT (2026-11-16):** the owner separately authorized the privileged write; the ruleset is active, `bypass_actors=[]`, `current_user_can_bypass="never"`, and the twelve proofs below were executed. `G2 CLEARED` is limited to this authorized scope: `docs-validation` is the only required check; native jobs do not exist and were not required. G1, G3, ADRs, implementation and release remain unchanged.

## Authority and Source Check

The owner **already ratified the bounded G2 design direction** `C01-D12 OWNER_RATIFIED_G2G3_BOUNDED`: free CI, isolated untrusted PRs and eventual enforceable rules subject to explicit authorization/proof. The present request authorizes **QUALIFYING and documenting** a concrete settings proposal, and **expressly forbids changing branch settings** without a **separate, explicit authorization**. This proposal is not a newly ratified ruleset; no user/owner selection of any JSON options below is inferred by documentation, CI, or squash.

Canonical source hierarchy: checkpoint > Decisions Ledger / approved ADRs > Scope > DoD > Architecture > Requirements > subsidiary G2 gates/WO/evidence. Follow [G0–G8 global approval gates](../engineering/p00-technical-approval-gates.md), [CORE-01 gate matrix](../engineering/core-01-01-qualification-gates.md), [Ledger](../10-decisions-ledger.md), [Security](../05-security.md) and [QA-01 ADR-0075 PROPOSED](../adr/0075-qa-01-ci-matrix-security-policy.md). Preserve 23 existing bounded owner decisions and G1 `PARTIALLY_RATIFIED_NOT_CLEARED`, G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`, G4+ blocked.

## Observed GitHub account/repository settings (read-only)

| Evidence and inspected source | Actual result at base | Interpretation |
|---|---|---|
| `GET /repos/KayzenRoot/stormline` | `private=false`, `visibility=public`, `default_branch=main`, owner type User, `allow_squash_merge=true`, also merge/rebase permitted by repository | Standard GitHub-hosted Actions runners are free **while repo remains public**; repository merge settings alone do not enforce linear history |
| `GET /repos/KayzenRoot/stormline/branches/main` | **Before:** exact base HEAD, `protected=false`. **After:** `protected=true`, HEAD `80624f6320578f49a16030f8c42e03ddd49afbba` | Ruleset enforcement confirmed; `protected` flag changed only after the authorized write |
| `GET /repos/KayzenRoot/stormline/rulesets` | **Before:** `[]`. **After:** exactly one `{id:27393227, name:g2-main-enforcement, enforcement:active, target:branch}` | Active repository-level ruleset on `refs/heads/main`; no overlapping classic protection |
| `GET /repos/KayzenRoot/stormline/branches/main/protection` | HTTP `404 Branch not protected` with the **admin** credential (the historical `403` came from a different connector) | No classic protection exists **by design**; ruleset readback is the authoritative enforcement source |
| Existing [`.github/workflows/docs.yml`](../../.github/workflows/docs.yml) | workflow **`Docs Validation`**, PR + push-main triggers, job key & name **`docs-validation`**, `ubuntu-latest`, `permissions: contents: read`, `actions/checkout@v7` with `persist-credentials: false`, timeout 5m, no path filters, no `pull_request_target` in this inspected workflow | This is the **only presently confirmed job-name candidate** for a required check. All other workflow names, native check jobs and check providers need inventory/verification |
| [Previous PR #399](https://github.com/KayzenRoot/stormline/pull/399) | [Docs Validation run #43901543824](https://github.com/KayzenRoot/stormline/actions/runs/43901543824), job `docs-validation` #133419176724 SUCCESS | Real check has run successfully on a PR; **not** proof it is required or resistant to bypass |

**G2 = `CLEARED` (2026-11-16).** The pre-write observation was `BLOCKED_NOT_VERIFIED`; the negative merge probes and the positive squash merge now prove enforcement. A green Docs Validation check alone was never treated as proof; the proof is the denied red/absent/stale merge plus the successful green merge.

## G2 settings A — authorized, applied and proven (2026-11-16)

**Executed:** exactly **one repository-level active ruleset targeting only `refs/heads/main`** (not a template applied to every branch, not a second overlapping rule); no classic protection was created. Applied rule contents (identical to the authorized payload):

| G2 setting | A: preferred proposed value | Why, trade-off and activation guard |
|---|---|---|
| Scope and enforcement | Repository `KayzenRoot/stormline`, only branch `main`; `enforcement=active` (executed 2026-11-16 after separate owner authorization) | Rulesets are auditable and combine constraints; readback confirmed id `27393227` with include `refs/heads/main` |
| Require pull request | **ON** for all main updates, with **zero required approvals** (`required_approving_review_count=0` if supported by chosen API/UI); no required code-owner review, last-push approval or external reviewer | Preserves solo owner + mandatory PR/evidence. Fewer human checks is a known risk offset by objective audit and CI |
| Required status checks | **One initially:** exact observed job `docs-validation`; verify unique check context/provider (GitHub Actions) in PR checks before binding; status must pass against current evaluated commit | Native Windows/Linux/macOS/GPU checks **do not yet exist as verified runnable jobs**. Never require invented or conditional job names |
| Up-to-date | **Strict** required check, feature `require branches to be up to date` | More reruns/rebases after base moves, but prevents stale test merges. A `git push --dry-run` alone cannot prove enforcement |
| Merge policy | **Require linear history**; continue documented normal **squash PR merges**; do not modify repository-wide allowed merge methods yet | Avoids merge commits on main. Check that bot/integration PR merge still functions under rules and **no bypass** |
| Force-push and deletion | **Block force pushes**; **restrict deletion** of main | Applied as `non_fast_forward` + `deletion`; confirmed by effective-rule readback, without any destructive test |
| Bypass | **No bypass actors, roles, apps or owner override** in the applied ruleset | Readback: `bypass_actors=[]` and `current_user_can_bypass="never"`; the admin credential itself was denied on red/absent/stale merges |
| Other requirements | Do **not** demand signed commits, merge queue, deployments, code owner approval, required last-push approval, paid security gates, speculative native jobs or strict code coverage in this increment | These can deadlock a solo repo or add cost, and have not been qualified. Future proposals need separate explicit owner choice |
| Safe rollout | Executed: inventory of the single workflow, check provider app `15368`, admin credential, pre-write snapshot, readback and reversal via `DELETE /rulesets/27393227` | Privileged operation performed under explicit authorization; rollback documented in the [Applied Evidence Bundle](../evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-APPLIED.md) |

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

## G2 proof obligations — executed results (2026-11-16)

| Proof ID | Objective evidence required | Status |
|---|---|---|
| G2-P01 | Base SHA/Source Lock and owner-accepted exact settings diff/ruleset version, no unapproved rule | **PASS** — base `0ef8eb6…`, payload `sha256=349f4b7d…`, snapshot prévio; único ruleset |
| G2-P02 | Enabled ruleset targets only `refs/heads/main`, active enforcement, GitHub API readback with sufficient permission | **PASS** — id `27393227`, `active`, include exato `refs/heads/main`, `protected=true` |
| G2-P03 | Required PR verified, `required_approving_review_count=0` and no codeowner/last-push approval requirement | **PASS** — 0 aprovações, `required_reviewers=[]`, codeowner/last-push `false` |
| G2-P04 | Exact `docs-validation` required check/provider confirmed **unique, produced, up-to-date and not skipped** | **PASS** — app `15368` (`github-actions`), único workflow, `pull_request`, strict, job completo |
| G2-P05 | Missing/failing check on safe disposable PR demonstrably blocks merge; re-run green then merge allowed | **PASS** — #402 `is failing` e #403 `is expected` (HTTP 405); #405 squash verde mergeada |
| G2-P06 | Direct main update without PR is denied, evidenced by non-destructive controlled test or permission-backed enforcement proof; no destructive push | **PASS (config proof)** — regra `pull_request` efetiva + `current_user_can_bypass=never`; nenhum push real na main tentado |
| G2-P07 | Force-push and branch deletion disabled in effective config and via safe readback, never attempt destructive operation | **PASS (readback)** — `non_fast_forward` + `deletion` efetivas; nenhuma operação destrutiva |
| G2-P08 | Bypass actors/roles/apps empty and effective admin permissions/bypass independently checked; admin/bot cannot silently skip required check | **PASS** — `bypass_actors=[]`, `never`; admin negado nos merges #402/#403/#404 |
| G2-P09 | Squash merge with strict checks still functions, and stale base requires new eligible check | **PASS** — #405 squash; #404 stale negada, update → novo run `43921953773` SUCCESS → `CLEAN` |
| G2-P10 | Fork PR: token read-only, secrets withheld, no privileged PR-head execution or unsafe artifact promotion; prove via policy | **PASS (policy)** — `pull_request`, `contents: read`, `persist-credentials:false`, zero segredos; nenhum fork externo executado |
| G2-P11 | Public repo standard runner and billing/usage evidence consistent with R$0; no larger/billable runners | **PASS** — repo público, `ubuntu-latest`, zero self-hosted/larger runners |
| G2-P12 | Owner sees readback/rollback instructions for ruleset and separately audits the G2 gate; exact new HEAD + CI + checkpoint recorded | **PASS** — [Applied Evidence](../evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-APPLIED.md), auditoria #6924316491, checkpoint independente com CI/audit/squash/readback |

**Rollback executed only if owner decides:** `gh api --method DELETE repos/KayzenRoot/stormline/rulesets/27393227` restores the captured prior state (zero rulesets, zero effective rules, no classic protection, `main.protected=false`). No rollback was needed; no destructive operation was performed.

## Risk analysis and blockers

| Risk | Severity if activated incorrectly | Controls and current disposition |
|---|---|---|
| Docs CI passes but is not required; red CI can merge | HIGH | **Mitigated:** `docs-validation` required; #402 red and #403 missing were denied HTTP 405 |
| No bypass list but admin/app still bypasses or overlapping rule overrides | HIGH | **Mitigated:** `bypass_actors=[]`, `current_user_can_bypass=never`; admin denied on #402/#403/#404 |
| Wrong/unavailable check name or merge queue without `merge_group` | STANDARD–ELEVATED (release blockage) | Only observed `docs-validation` (app 15368) required; no merge queue |
| Public fork secretly accesses privileged token/artifact or paid runner | HIGH | **Policy-verified:** `pull_request`, `contents: read`, `persist-credentials:false`, zero secrets; no external fork exercised |
| Required reviews introduced for single owner | STANDARD (deadlock) | `required_approving_review_count=0`; no external-review or CODEOWNERS requirement |
| Strict checks cause churn during concurrent merges | STANDARD | Accepted; update branch and re-run (#404 demonstrated the flow) |
| GitHub public repo exposes unpublished intellectual property or private artifacts | ELEVATED | Separate NLE-D009/source-distribution decision; no code pushed in G2 |
| Rule setup credential lacks readback (API 403) | ELEVATED | **Resolved:** admin readback succeeded; no 403 in this session |

**This document's change risk is LOW DOCUMENTARY. The privileged ruleset write was executed under explicit owner authorization, with snapshot, readback, negative/positive tests and documented rollback.**

## Historical authorization record (pre-execution; superseded by the applied results above)

- **OBJECTIVE:** specify G2 minimum effective protection for `main`, required checks, solo-workflow, fork isolation and R$0 CI, with measurable proofs; **achieved and applied on 2026-11-16.**
- **CONTEXT:** Source Check main at fixed base, 23 previously ratified bounded G1/G2/G3 decisions, `C01-D12` accepted the *desired design direction*; the privileged write required a **separate explicit owner authorization**, which was granted for this execution.
- **SCOPE:** this technical plan + proof matrix and the qualification Evidence; the applied Evidence and checkpoint are separate documents.
- **OUT OF SCOPE (initially):** ruleset/protection API mutations, other GitHub settings/workflows, code, native tests, ADR/Source license/queue/registry/manifest, CORE-01-02. The ruleset mutation was later separately authorized and executed; everything else remains out of scope.
- **FILES/SOURCES TO READ:** checkpoint, Ledger/ADRs, Scope, DoD, Architecture, Requirements, Security, G0–G8 gates, current docs workflow, GitHub settings readback, official GitHub rule/Actions docs.
- **REQUIREMENTS:** PR-only flow with the exact existing job, zero external reviewers, no bypass, strict CI, no force/delete, no paid runners or unsafe forks. **All applied as specified.**
- **ARCHITECTURE RULES:** CI job ≠ compiled engine; runner image ≠ target platform certified; separate QA-01 code CI future, no new DAG dependencies.
- **CONSTRAINTS:** same `NLE-PRPLAN-CORE-01-01` ID, no new coding WO nor approvals inferred, no external reviewer requirement.
- **ACCEPTANCE CRITERIA:** the qualification PR had exactly 2 new Markdown; the applied increment has exactly 1; 12 proof obligations are now executed; zero code/ADR/registry/manifest changes.
- **TESTS:** exact-head Docs Validation on both PRs, plus real negative/positive enforcement probes in the applied increment; no native tests.
- **DELIVERABLES:** G2 plan, qualification and applied Evidence Bundles, PR+CI+auditoria/squash/readback, checkpoint independente.
- **REVIEW FORMAT:** APPROVED DOCUMENTARY ONLY / CORRECTION REQUIRED / BLOCKED, with base/head and tests.
- **STOP CONDITION:** stale source, failed CI, high/critical issue, unauthorized settings, code/license/ADR/registry/manifest change or package 02 advancement.

## Official upstream reference URLs (verified 2026-11-16)
- [GitHub rulesets](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/available-rules-for-rulesets), [creating rulesets](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/creating-rulesets-for-a-repository), [branch protection](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches/about-protected-branches).
- [GitHub status checks and skipped job limitations](https://docs.github.com/en/pull-requests/reference/status-checks), [troubleshoot required checks / merge_group](https://docs.github.com/en/pull-requests/how-tos/merge-and-close-pull-requests/troubleshooting-required-status-checks).
- [GitHub Actions billing](https://docs.github.com/en/actions/concepts/billing-and-usage), [standard public runners](https://docs.github.com/en/actions/how-tos/write-workflows/choose-where-workflows-run/choose-the-runner-for-a-job), [secure pull_request_target](https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target).

**STOP HERE:** `G2 = CLEARED` only for the applied, proven scope above. Do NOT infer G1/G3 clearance, native CI, implementation, ADR approval or release authorization from this document. G1 `PARTIALLY_RATIFIED_NOT_CLEARED`; G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`; G4-G8 blocked; `NLE-D009 OPEN`, ADR-0003/0075 `PROPOSED`, 80 coding WOs `BLOCKED`, CORE-01-02 `PLANNED_BLOCKED`, `engine_implemented=false`. Future native checks require their own observed job names, provider verification and new owner authorization before being added to the required set.
