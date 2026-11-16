# NLE-PRPLAN-CORE-01-01 — CORE-01 Technical & Owner Decision Qualification Work Order

**Source Check:** `main=27ad407bbf0f66d1938c403bf32c28b0ebf1e910`, Git tree `56b27016ed092be5297a63dabd6b6884144da40a`, 2026-11-16. [Issue de qualificação #384](https://github.com/KayzenRoot/stormline/issues/384). CORE-01 tem zero predecessores formais; [issue de código #18](https://github.com/KayzenRoot/stormline/issues/18) permanece OPEN/BLOCKED. **Todo este pacote é proposta documental, não deliberação do proprietário.** `NLE-D009` licença da engine OPEN, `NLE-D010` marca OPEN, `ADR-0003` e `ADR-0075` PROPOSED, 80/80 WOs de código BLOCKED, zero `approved_adr`, zero `executor_ready`, `engine_implemented=false`.

**STATUS: DOCUMENTARY INCREMENT REQUESTED; OWNER TECHNICAL RATIFICATION AWAITING.** Existing [ADR-0003](../adr/0003-core-01-platform-technology.md) stays PROPOSED, and the [748-packet manifest](../pr-plans/manifest.json) stays unchanged with packet 01 `PLANNED_BLOCKED` / `github_pr=null`. This research PR is not an implementation PR and cannot imply G1/G2/G3 approval. This is the first packet only. Future packet 02 stays blocked.

## OBJECTIVE
Review core host/lifecycle architecture in depth and produce a decision-ready, measured, security-aware owner dossier: C++20, SDL3, CMake/Ninja, ABI, explicit lifecycle and headless, Win/Linux/macOS/Web boundaries, software rights, cost-free CI, platform/risk/release class, tests, performance and branch protection. Do **not** sign off decisions automatically. The acceptance result is proposal quality and objective documentary evidence, not owner ratification.

## CONTEXT and source hierarchy
Checkpoint > Decisions Ledger/approved ADRs > Scope > Definition of Done > Architecture > Requirements > module proposals/registry/skills. Git main source `27ad407bbf0f66d1938c403bf32c28b0ebf1e910`, tree `56b27016ed092be5297a63dabd6b6884144da40a`, no open PR before branch; 80/80 research documented and 80/80 code WOs BLOCKED, 0 approved_adr/ready, 80 risks UNCLASSIFIED, 80 release classes UNDECIDED, engine_implemented=false. CORE-01 module index 0, formal dependencies **NONE**. Existing code issue #18 remains OPEN/BLOCKED. QA-01 is a **downstream** module with formal dependency CORE-01; its ADR-0075 is only integration evidence.

## CONTEXT LOCK / critical source fingerprints
The following values are **Git blob object SHA-1 IDs**, **not raw SHA-256 file hashes**. A future executor recomputes raw SHA-256 for the actual files at its own selected Git commit; **STALE** if relevant checkpoint/decision/Scope/DoD/source SHA changes before writing.

| Canonical source | Git blob SHA-1 at BASE |
|---|---|
| `docs/11-checkpoint.md` | `7a5b2ba0f318b5adabe0338f6cdf720aaa0d69e2` |
| `docs/10-decisions-ledger.md` | `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e` |
| `docs/03-scope.md` | `4ef605c74632ece080b2650e37dd83a415b63310` |
| `docs/09-definition-of-done.md` | `160b3054db9ea1961308934b401488b838d24c3e` |
| `docs/04-architecture.md` | `df62574cb3956c3ac9881631a4cf66be4e1abff1` |
| `docs/02-requirements.md` | `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b` |
| `docs/pr-plans/CORE-01.md` | `83c99b434fcca508913de2ddef5386a430065048` |
| `docs/adr/0003-core-01-platform-technology.md` | `2ee92dda5ab81ddcc446b9d5325d29257350e217` |
| `docs/architecture/core-01-platform-lifecycle.md` | `11c7ec4125f40cf0172aa552a1e9835e84d2c172` |
| `docs/queue/work-orders/CORE-01.md` | `61c3a4d161fbdda653e0c4d58dd1df406bc11827` |
| `docs/adr/0075-qa-01-ci-matrix-security-policy.md` | `22e91a36c1e0a8121163fa4778abd0489fed86e5` |
| `docs/engineering/p00-technical-approval-gates.md` | `7b144db5b51b24959f02aa1f1c4082bba4ec070c` |
| `docs/engineering/pr-decomposition-policy.md` | `ac21d8861e63024d0b45f2f94e6e87f3fd2ba186` |
| `docs/queue/implementation-registry.json` | `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024` |
| `.github/workflows/docs.yml` | `c9d7b6688ed9484ecaf9968c9134bfaa70f73dc1` |
| `AGENTS.md` | `3e57b719f8651407879ebb641707a048773ea4c2` |

## SCOPE: NECESSARY only
Create **exactly FOUR new Markdown** in one research PR: [owner decision dossier](../research/core-01-01-owner-technical-decision-dossier.md) (15 open decision keys C01-D01..D15, alternatives/official sources), [gate & 32-future-test matrix](../engineering/core-01-01-qualification-gates.md), this WO and [Evidence Bundle](../evidence/NLE-PRPLAN-CORE-01-01.md). Do not edit existing Source Pack, ADR-0003, QA-01, license, manifest, registry, skill pack, original CORE-01 code packet, CI, GitHub branch settings or native code. After independent exact-head CI/audit/squash/main readback, factual checkpoint only if justified and independently validated.

## OUT OF SCOPE
No owner approval for any stack, ABI/contract selection, risks, release class, royalty/license/trademark, public MVP, signing/notary, paid subscription, security settings, machine tests, source code, gfx, SDL3 installations, editor/GUI, actual CORE-01-02 docs, application API implementation or CodeRabbit. Do not open a CODE PR or any future packet while current gate is still awaiting explicit owner decisions.

## FILES/SOURCES TO READ
[Checkpoint](../11-checkpoint.md), [Ledger](../10-decisions-ledger.md), [Scope](../03-scope.md), [DoD](../09-definition-of-done.md), [Architecture](../04-architecture.md), [Requirements](../02-requirements.md), [CORE-01 plan](../pr-plans/CORE-01.md), [ADR-0003](../adr/0003-core-01-platform-technology.md), [CORE-01 architecture](../architecture/core-01-platform-lifecycle.md), [original blocked WO](../queue/work-orders/CORE-01.md), [QA-01 ADR-0075](../adr/0075-qa-01-ci-matrix-security-policy.md), [gates G0–G8](../engineering/p00-technical-approval-gates.md), [policy](../engineering/pr-decomposition-policy.md), [Docs CI](../../.github/workflows/docs.yml), [AGENTS.md](../../AGENTS.md), official sources listed in dossier.

## REQUIREMENTS
GOV-001..005, CAP-009/010/014/016, NFR-001..005; owner NLE-D002/003/004/005/008 PROPOSED /009 OPEN /010 OPEN /011 NOT VERIFIED /013..020. CORE-01 catalog acceptance: `Inicializar e desligar headless e com janela, sem leaks detectáveis.` Distinguish proposal acceptance of **this documentary WO** from actual future native module DoD.

## ARCHITECTURE RULES
CORE-01 host/facade isolated from editor renderer, physics, networking, gameplay and AI/MCP grants. Headless no GPU/display/audio required; windows main thread, no SDL types or raw OS pointers in public cross-boundary API, typed errors, explicit ownership, no hidden global admin authority, no unmanaged telemetry, C ABI only as future candidate. Avoid artificial dependency on downstream QA-01/PLAT/GFX. Preserve approved owner intentions and never silently replace ADR-0003/0075.

## CONSTRAINTS
Public standard GitHub Actions, R$0, no paid runner/Apple signing; no forced external human reviewer, no CodeRabbit, no force push/protection bypass, no secret, no unscoped asset copyright. `main.protected=false`, rule list `[]`, protection detailed 403: **enforcement not proven** and remains a blocker for future implementation governance; this WO does not change settings. Any target hardware unavailable = NOT_QUALIFIED.

## ACCEPTANCE CRITERIA
- [ ] Fifteen discrete owner decisions with explicit alternatives, required evidence and status **AWAITING_OWNER**; no automatic adoption. Formal predecessor CORE-01 **[]**, QA-01 consumer only.
- [ ] Owner review-ready proposal covers C++20/23, SDL3/GLFW/native, CMake Presets/Ninja vs alternatives, C++/C ABI boundary, host state/errors, headless, Win/Linux/macOS/Web separation, riskiest OS bridges, provenance/licensing, costs and GitHub enforcement.
- [ ] Transparent future gates G1..G8 and 32 **FUTURE_NOT_EXECUTED** technical scenarios, numeric candidates and hardware/CI proof rules. Zero native tests claimed PASS.
- [ ] New PR is **exactly four ADDED Markdown**, no existing-file modifications, registry and manifest byte-identical; no new implementation/permissions/ADR/license/risk/release changes.
- [ ] Exact-head GitHub Docs Validation SUCCESS, objective pt-BR independent audit, no HIGH/CRITICAL known defect in documentary scope; normal squash and main readback.
- [ ] Independent checkpoint records **proposal delivered, owner decisions OPEN**, if created, with own exact-head CI/audit/squash/readback. The *TECHNICAL GATE packet 01* remains `PLANNED_BLOCKED` until explicit owner ratification. Do not advance packet 02.

## TESTS
**Documentary now:** existing `python3 scripts/validate_docs.py`, `validate_module_catalog.py`, `validate_wo_registry.py`, `select_wo.py CORE-01 --json` must deny blocked packet, `validate_skills.py`, `validate_pr_plans.py` and both suites, as executed by exact-head [Docs Validation](../../.github/workflows/docs.yml). No local run falsely asserted. **Future only:** 32 Q-cases in gate matrix, per-OS native CMake/CTest + compiler/sanitizer, hardware/device, negative tests and benchmarks; `NOT_EXECUTED`.

## DELIVERABLES
Issue #384, exact four Markdown, one research/qualifying PR, CI with job+steps, Evidence Bundle (base/head SHA, files, refs, risks, privacy/licenses, limitations), objective pt-BR audit, normal squash main readback and independent factual checkpoint if safe. Owner decision board remains open.

## REVIEW FORMAT
Auditoria em português brasileiro: baseline HEAD, touched files (exact ADDED only), 80/80 blocked state and CORE-01 formal DAG, external research sufficiency, conflicting owner decisions, rights/privacy/security, CI exact run/job and note NOT RUN, audit `APPROVED / CORRECTION REQUIRED / BLOCKED` for **documentary** increment only. If correction needed, patch same branch/PR. Draft factual checkpoint, not self-promoted.

## STOP CONDITION
STALE source/HEAD, unknown library licenses declared approved, owner/ADR/Scope/DoD/risk/release class mutated, unauthorized GitHub settings or paid resource, missing 32 cases/15 open decisions, fail Docs CI, HIGH/CRITICAL, false native test claims, any CODE WO activation, next packet attempted while owner gate pending, forced merge/bypass or destructive Git operation.

## CHECKPOINT DELTA PROPOSED (not promoted until independently audited)
State that `CORE-01-01` **documentary decision dossier** was reviewed/merged, with actual PR/CI/audit/main SHA only after observed. Explicitly preserve **C01-D01..D15 AWAITING_OWNER**, ADR-0003 PROPOSED, release/risk UNDECIDED/UNCLASSIFIED, G2 branch enforcement not proven, future packet 02 BLOCKED, 80 code WOs BLOCKED, NLE-D009 OPEN, engine false.
