# Contributing to Stormline

Thank you for your interest in Stormline. This is an **owner-directed, solo engineering program in its planning phase**. This file documents how work is organized; it is **not** an invitation to submit unrequested code or an open-source license grant.

## Current contribution policy
- The project owner authorizes all architectural decisions, scope changes, releases, and merges.
- There are **no required external human reviewers** and no CodeRabbit.
- Unsolicited pull requests may not be reviewed or merged. Please open a scoped proposal first, when appropriate.
- External reports may be considered, but no response time or acceptance is guaranteed.
- Do not include copyrighted assets, game content, secrets, vulnerabilities, third-party branding, or unlicensed code in public issues/PRs.

## For the owner and authorized AI executors
1. Read [AGENTS.md](AGENTS.md), [Source Hierarchy](docs/00-source-hierarchy.md), [Checkpoint](docs/11-checkpoint.md), [Decisions Ledger](docs/10-decisions-ledger.md), [Scope](docs/03-scope.md), and [Definition of Done](docs/09-definition-of-done.md).
2. Confirm the current Work Order ID, branch, base SHA, source fingerprints and acceptance criteria.
3. Edit **only** what is NECESSARY for that Work Order.
4. Run relevant tests and record real output; never claim unexecuted checks passed.
5. Push changes to an isolated branch, create a PR and provide an [Evidence Bundle](docs/engineering/agent-execution.md).
6. Obtain objective audit and owner authorization. Merge only when checks and rulesets permit; never bypass or force-push.
7. Reconcile affected canonical documents and the checkpoint **after** approval/merge, with evidence.

For the expected issue structure see the [Work Order template](docs/engineering/wo-template.md). For delivery and tags see [Versioning](docs/engineering/versioning.md).

## Filing issues
Use the [issue templates](.github/ISSUE_TEMPLATE). For reproducible defects include the commit SHA, impact, environment, steps, expected/actual behavior and evidence. Security vulnerabilities must **not** be disclosed in public issues; see [SECURITY.md](SECURITY.md).

## Technical baseline
The repository currently contains documentation and a documentation-validation script. There is no engine build process to run. To check Source Pack links locally:

```bash
python3 scripts/validate_docs.py
```

## License
No software license has been selected. Public visibility alone provides no permission to reuse the code or brand. Do not assume external contributions can be integrated under a particular license until the owner adopts a licensing policy.
