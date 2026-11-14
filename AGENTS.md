# Stormline AI agent operating contract

Applies to Codex, Zcode, DeepSeek and every automated executor. **Read before proposing any edits.**

1. Source order: checkpoint > Decisions Ledger/ADRs > Scope > Definition of Done > Architecture > Requirements > remaining documents. Git and test evidence supersede conversational recollection.
2. Inspect repository state, base/head SHA, changed files, open PR and relevant documents **before** editing. Stop on an unexpected or stale baseline. Never silently rewrite an approved decision.
3. Follow ANALYZE -> SOURCE CHECK -> NEXT NECESSARY INCREMENT -> WORK ORDER -> CONTEXT LOCK -> PREFLIGHT -> EXECUTOR -> TESTS/EVIDENCE -> PR -> AUDIT -> APPROVED / CORRECTION REQUIRED / BLOCKED -> CHECKPOINT DELTA -> MERGE -> NEXT.
4. Work Orders require OBJECTIVE; CONTEXT; SCOPE; OUT OF SCOPE; FILES/SOURCES TO READ; REQUIREMENTS; ARCHITECTURE RULES; CONSTRAINTS; ACCEPTANCE CRITERIA; TESTS; DELIVERABLES; REVIEW FORMAT; STOP CONDITION.
5. One stable WO ID across issue, branch, PR, evidence and corrections. No unrelated refactor, feature creep, new paid tools, or engine code in a documentation-only WO.
6. Execute only scoped instructions. Prefer reproducible deterministic tools over LLM speculation; use no secrets or paid subscriptions. Run tests, fix introduced regressions, commit/push and open/update PR when authorized.
7. Provide Evidence Bundle: base/head SHA, scope/file diff, commands/results, errors and corrections, security/architecture concerns, rollback, licensing, open risks and **proposed** checkpoint delta. Never self-promote a proposed checkpoint.
8. Final audit review in **pt-BR**. Verdict only: APPROVED (evidence suffices), CORRECTION REQUIRED (same WO/PR), BLOCKED (resolve prerequisites). Never advance with known HIGH/CRITICAL defects.
9. Solo governance: owner approves decisions; no external human reviewer, no CodeRabbit, no mandatory outside approval. Automatic checks and objective audit remain required. Do not bypass protections; configure PR requirement with zero human approvals where supported.
10. Do not claim engine features, produced logos, trademark availability, code builds, CI success, security clearance, or deployment unless evidence exists.
11. Never force push, rewrite history, disable security checks or merge an unvalidated change. Escalate unfulfillable controls as BLOCKED.
12. The owner decides publication and brand clearance. Public repo is not an open-source license.

For planned engine implementation, inspect [Zcode handoff](docs/engineering/zcode-handoff.md) and the [80-module queue](docs/queue/README.md). **All queue packets are blocked**, not permission to code. Planner must approve exact architecture, API, source files and tests first.

See [checkpoint](docs/11-checkpoint.md), [governance](docs/engineering/solo-governance.md), [agent runbook](docs/engineering/agent-execution.md) and [WO template](docs/engineering/wo-template.md).
