# Zcode Handoff — Stormline Execution Contract

**State:** Versioned pre-execution process, not authorization to implement the engine.  
**Audience:** Zcode, Codex, OpenCode and future execution agents.  
**Owner role:** Architecture, specification, approved technological decisions, Objective audit and merge authorization. No external human reviewer requirement.

## Purpose
When development begins, the executor should **code, test, document changes, and open the PR**, not invent product architecture, discover module scope from scratch or choose an unapproved game-engine stack. This is achieved by preparing complete Work Orders, not by launching 80 parallel coding agents.

## Sources in strict order
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md`/approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > applicable module spec > Work Order > rest. Git state/test evidence outrank conversation memory.

## Queue
[80-module catalog](../product/module-catalog.md) -> [versioned registry](../queue/implementation-registry.json) -> [individual packet](../queue/work-orders/) -> [issue] (pending creation) -> activated executable WO.

### Draft vs executor-ready
- Every `NLE-EXEC-WO-<MODULE>-001` starts **BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**. Drafts are a planning queue only.
- Release 1.0 classes, technologies, exact paths, APIs, data formats, migrations, hardware budgets, test commands and license/security must be agreed and documented **by the planning/audit process** before activation.
- Public 2D/2.5D/3D/Web support, Windows/Linux/macOS, authoring Editor/CLI/MCP parity and no MVP remain program-level requirements.
- Do **not** confuse an initial module work packet with the only eventual development increment. A large module must be divided by its owner into small necessary WOs, following requirements and dependency order, without destructive renaming of approved IDs.
- Issue creation does not confer executable status. **Never code solely because a ticket is open**.

## Preflight instructions for an activated WO
1. Clone/open the approved repo (no branch outside owner authorization), check `git status --porcelain`, current `main` HEAD, current branch and any related PR.
2. Read the exact WO and the minimal canonical sources in priority order.
3. Recheck the approved Context Lock (base SHA, SHA-256 fingerprints of Checkpoint, Scope, DoD, Architecture and related ADR); if any changed, mark **STALE**, stop and request regenerated delta in the same WO.
4. Confirm required dependencies are approved/merged, no HIGH/CRITICAL defect, current public CI gate and correct target OS/compiler/hardware matrix.
5. Verify the WO has **no TBD** for approved technologies, file paths, interface methods, acceptance criteria, tests or release classification. A draft packet with TBD is **not** executable.
6. Validate the permitted third-party dependencies: pinned exact versions, license/provenance, CVEs, no subscriptions/payments/secret leaks.
7. Classify risk. HIGH_ASSURANCE work (money/signing/privileged auth/irreversible action) requires explicit evidence and authorization; never turn off protection to pass.

## Execution (only after READY gate)
1. Create `work/<WO_ID>-<short-topic>` from the validated base; do not force push.
2. Modify **only** listed file paths and NECESSARY scope. Before adding code, inspect existing implementation and contracts. Prefer deterministic static tools/hashes/AST to LLM speculation.
3. Implement tests with code; use `CMake/CTest`, format, lint, sanitizer, platform smoke, image/audio benchmark and integration checks exactly when required by the approved Work Order.
4. Fix introduced failures; never edit baseline tests to hide defects or claim a test ran on unsupported hardware. For graphics/VFX/audio, record machine/GPU/driver, p95/p99 frame/latency and quality rubric.
5. Commit, push and open/update a PR on the exact branch, using stable WO ID in issue, branch, PR, diff/evidence and checkpoint proposal.
6. Produce Evidence Bundle (base/head SHA, exact commands/outputs, changed files, tests, CI run links, errors/corrections, security/license, regression, benchmarks and risks).
7. Review in **pt-BR**, audit against Scope, Architecture, Requirements, DoD and user-approved decisions. Verdict: APPROVED, CORRECTION REQUIRED or BLOCKED.
8. If CORRECTION REQUIRED, patch the **same WO/PR**. No new work order until the prior one is APPROVED.
9. Approved PR may squash merge only with fixed HEAD, required checks and rulesets satisfied, no bypass. Read main after merge, reconcile Checkpoint/other canonical docs in a validated post-merge delta, then allow next.

## Hardware and release reality
GitHub-hosted CI can validate builds, lint and many tests but does not substitute real GPU/gameplay performance, audio devices, native Mac compatibility, security and playability under load. Internal prototypes are part of the testing process, **never a public MVP**. Engine 1.0 launch requires all approved must-have capabilities and full release DoD.

## Local read-only selection commands
```bash
python3 scripts/validate_docs.py
python3 scripts/validate_module_catalog.py
python3 scripts/validate_wo_registry.py
python3 scripts/select_wo.py --list
python3 scripts/select_wo.py CORE-01
```
`select_wo.py` returns non-zero for BLOCKED packets. Do not circumvent that gate to begin programming. No API credentials or paid AI provider is required for reading the queue.
