# P00 → Technical Decision Qualification: 80-Module Approval Gates and Dependency Waves

**Source Lock:** `379f875e10bb255cedc5c80755625ccd15a6ff17` (main confirmado); 2026-11-16; research P00 **80/80 DOCUMENTED** e **0/80 aprovados para implementação**. ID estável `NLE-P00-GOV-001`, [issue #375](https://github.com/KayzenRoot/stormline/issues/375). Auditoria documental, não validação de produto nem autorização de licença.

**Status deste documento: PROPOSED GOVERNANCE PROCESS, NOT AN ADR APPROVAL, NOT A ROADMAP COMMITMENT, NOT WORK ORDER ACTIVATION.** Source truth: [audit](../research/p00-global-research-closure-audit.md), [Decisions Ledger](../10-decisions-ledger.md), [Scope](../03-scope.md), [DoD](../09-definition-of-done.md), [80-module registry](../queue/implementation-registry.json). Existing solo governance ADR-0002 owner direction applies. Each approval needs owner authority and objective proof, not just inclusion in a Markdown.

## Invariants / forbidden transitions
- `RESEARCH_DOCUMENTED_ADR_PROPOSED` is a **research** label, not decision `APPROVED`, not engine runtime, not `executor_ready=true` or a passed CI.
- All **80/80 future implementation WOs remain `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`** until a later separate explicitly authorized, audited promotion. Zero approved_adr; risk/class UNDECIDED; engine=false.
- NLE-D009 source license OPEN and NLE-D010 brand clearance OPEN remain untouched. Do not decide engine license, royalties, trademark, end-user terms, signing fees or public distribution by default. NLE-D013 no public MVP; internal test builds only after authorized code path and DoD.
- No cross-DAG jumps, no CodeRabbit, mandatory external reviewer, paid CI or force push. Owner must approve actions carrying risk, financial cost, license, access privileges or irreversible data changes.

## Proposal-only governance gate states
| Gate | Inputs | Decision / evidence required | At completion; still NOT auto-executor |
|---|---|---|---|
| G0 Research proof | Main, all 80 indexed ADR/architecture/evidence WOs, Git blob fingerprints, real CI references | Confirm 80 documentary, exact source and legacy exceptions; no unsafe claims | Research audit APPROVED, all code BLOCKED |
| G1 1.0 Scope/DoD design | NLE-D013..017, intended capability matrix 2D/2.5D/3D/Web + Win/Linux/macOS, unknown mobile and specialized features | **Propose** per-module release depth MANDATORY_1_0, ADVANCED_RESEARCH or PLATFORM_CONDITIONAL with acceptance scenario, min OS/hardware, fallback, exclusion and traceability; owner ratification required | None assigned by this document; 80 remain UNDECIDED |
| G2 Repository enforcement | NLE-D005/011/018, current protected/rulesets API and docs CI, future real code CI evidence | Verify PR required checks, branch protection/rulesets enforcement without external approvals; propose least privilege and safe public PR handling | No settings mutation or bypass by research |
| G3 Cross-cutting architectural decisions | CORE-01, QA-01, Code/App platform matrix, proposed ADR-0003, 0075, NLE-D008 OPEN | Owner choose exact toolchain/API ABI/platform loader/CI ownership and **pinned versions/license files** backed by comparisons; no automatic vendor adoption | APPROVED **only if** separate ratification recorded; today PROPOSED |
| G4 Per-module technical promotion proposal | Module ADR PROPOSED, exact catalog formal prerequisites and their already adopted contracts, risks and interfaces | Formal compare proposed alternatives, explicit owner decisions, ABI version/hash, typed errors, rights, stability/rollback, perf baselines/targets, target OS/GPU/capability matrix, hazards, threat model | **Owner may ratify** module ADR; not synonymous with executing code |
| G5 Acceptance & risk proof plan | DoD/Scope ratified by module, fresh Git Context Lock SHA256, boundary owners, original fixtures and golden oracles, benchmark target hardware | Classify LOW/STANDARD/ELEVATED/HIGH_ASSURANCE, fill test oracles and CI commands, failure injection, migration/recovery proof and whether code artifacts are realistically testable at R$0 | Future coding WO may be compiled only when all predecessor gates satisfied |
| G6 Individual executor readiness | Owner-approved ADR/risk/release class + API/ABI + exact files/tests + formal deps approved/merged + Git SHA lock + budget/licensing authorization | Independent objective audit of a **specific** WO and `executor_ready` transition in a **future separate PR**, with rollback and stoppage rules | Only that WO can become ready; not remaining 79 |
| G7 CODE / CI / functional proof | Authorized executor scope + versioned locked plan | Native/unit/integration/regression, compiler matrix, sanitizer/fuzz as risk, benchmark/hardware, recoverability, exact build/run artifacts, security/license and signed evidence where needed | Audit APPROVED/CORRECTION REQUIRED/BLOCKED; no next module while failure |
| G8 Public launch qualification (strict later) | Full v1.0 DoD all mandatory, BIZ-01 rights/license & trademark approvals, QA-05 actual device qualification, PLAT-05 signed artifact, BIZ-03 installer/update/rollback/support evidence | Owner explicit release authorization, real legal counsel if applicable, privacy/consent, backup, emergency stop/incident channels, secure signing/notarization | No public product until full 1.0 approved; never implicit from P00 green |

**G1, G2 and G3 may be researched independently as documents, but promoting any implementation WO requires ordered successful gates and source freshness.** Never retroactively adopt one of the 80 PROPOSED ADRs through a bulk checkbox.

## Exactly what constitutes ADR adoption
1. **Decision record** names prior PROPOSED ADR (e.g. CORE-01 ADR-0003), owner, exact version/hash/target, rejected alternatives and trade-offs including R$0 costs/licensing. State becomes APPROVED **only** after explicit owner consent and independent pt-BR audit; maintain original history and supersession if revised.
2. **Compatibility contract** has public owner, wire/ABI/data layout and errors, thread/phase and auth scopes, failure and recovery; real schema/headers at implementation gate; no raw vendor types escaping public API.
3. **Narrow scope** traceable to accepted release-class and DoD; first code slice NECESSARY only, no expansions automatically.
4. **Risk decision** per WO with strongest applicable proof and irreversible/security/financial classification; no auto-LOW for trivial first code.
5. **Environment and legal decision** exact compiler/GitHub CI/platform hardware availability, third-party SPDX + transitive notices; NLE-D009 OPEN blocks public license grant, even if internal experimental code later permitted after approvals.
6. **Executable Work Order proof** concrete files, test commands/expected outputs, base/head SHA with SHA256 critical source fingerprints, threat/rollback plan and stop conditions; executor must inspect actual Git before changes.
7. **Review evidence** real CI native builds/tests, no HIGH/CRITICAL, objective audit, squash, checkpoint and readback. Source code doesn't move to main merely because documentation has an ADR.

## Candidate decision fronts, NOT approved as global implementation order
| Priority for DECISION preparation | Formal basis / module family | Why this gate first | What remains prohibited |
|---|---|---|---|
| P0 A | **CORE-01** (only level-0 DAG root), ADR-0003 | Platform/lifecycle, Windows/Linux/macOS/headless/Web boundaries, C++20/SDL/CMake proposals and R$0 CI contract | No C++ project code until a separate WO passes every gate |
| P0 B | **QA-01** planned alongside CORE-01, but formally depends on CORE-01 | Real compiler/test CI design before judging product implementation; not code-ready until CORE-01 contracts adopted | Don't claim multi-OS native CI from current docs workflow |
| P1 | **CORE-02, CORE-04, CORE-05, CORE-06, DATA-01** after CORE-01 (DAG level 1) | Allocation, clock, coordinate/math, diagnostics and VFS/security foundations; seven legacy API/test formats become future per-WO contracts | Do not create seven retroactive research/ADR copies |
| P2 | **CORE-03, DATA-02, GFX-01, EDIT-02, EDIT-07** and other level-2 only when actual own formal predecessors satisfied | Task execution, asset handles, RHI feature detection, editor projects, diagnostics UI contract | No API/UI claims without owner ABI and target evidence |
| P3-P11 | Remaining DAG levels **3 through 11**, topological partial order from audit | Incremental dependency owner integration; QA-/PLAT-/BIZ proofs get stricter | No dependency edge inferred from informal integration list |

**Complete future DAG wave order** (not permission to execute):
- Level 0 (1): CORE-01
- Level 1 (9): CORE-02, CORE-04, CORE-05, CORE-06, DATA-01, GAME-01, NET-01, EDIT-01, QA-01
- Level 2 (5): CORE-03, DATA-02, GFX-01, EDIT-02, EDIT-07
- Level 3 (8): DATA-03, DATA-04, GFX-03, AUD-01, PLAT-01, PLAT-02, PLAT-06, PLAT-04
- Level 4 (6): DATA-05, GFX-02, TWO-01, WORLD-01, AUD-03, QA-02
- Level 5 (9): GFX-04, GFX-05, TWO-02, TWO-03, WORLD-02, SIM-01, GAME-02, NET-02, PLAT-03
- Level 6 (13): GFX-06, GFX-08, TWO-04, WORLD-03, SIM-02, AUD-02, GAME-04, NET-03, NET-05, EDIT-04, EDIT-05, AI-01, PLAT-05
- Level 7 (12): GFX-07, WORLD-04, SIM-03, SIM-05, SIM-06, AUD-04, NET-06, AI-02, AI-03, QA-03, QA-05, BIZ-02
- Level 8 (8): WORLD-05, SIM-04, SIM-07, GAME-03, NET-04, EDIT-03, AI-04, BIZ-01
- Level 9 (4): GAME-05, EDIT-06, AI-05, AI-06
- Level 10 (2): AI-07, QA-04
- Level 11 (3): AI-08, AI-09, BIZ-03

## Release 1.0 classification proposals, not assignments
Provide a candidate owner-review table for each module with columns `module_id, formal_dependencies, capability_tier, proposed release_class, user-facing end-to-end proof, required 1.0 acceptance, platform minima, fallback, confidence, budget, owner_decision_date`. Classify against NLE-D013 full 1.0; retain every registry `release_class=UNDECIDED` until separate owner approval. **Do not** automatically label PLAT-04 mobile MANDATORY just because catalog includes it; no exception to mandatory Windows/Linux/macOS desktop and intended Web without owner change.

## Risk and test policy (per WO, future)
- LOW: deterministic directed checks for purely localized docs/noncritical changes, no privileged side effects.
- STANDARD: unit + integration + lint/typecheck/native build, negative/error tests and source/ABI ownership.
- ELEVATED: all STANDARD plus broad regressions, real data/persistence/recovery, sanitizer/security/transport/driver and hardware evidence, failure injection.
- HIGH_ASSURANCE: app/code signing, financial commitments, privileged auth/update/root, third-party plugin sandbox, irreversible schema/migrations or major data-loss risk. Demand explicit proof obligations, independent evidence, rollback or roll-forward and owner consent. Do not relax on R$0 constraints; mark BLOCKED if inaccessible.
- The 73 standalone test matrices and early embedded acceptance tests remain FUTURE. Number of scenarios varies and must follow **risk and explicit DoD**, not a retroactive universal 128-case mandate.

## Owner decision queue (draft only)
| Decision gate | Owner question for a later separate approval | Current |
|---|---|---|
| D-GOV-01 | Versioned mandatory complete v1.0 feature depth/targets and optional mobile/advanced class | UNDECIDED |
| D-GOV-02 | First CORE-01 toolchain/platform/ABI candidate; exact pins and license/CI matrix | PROPOSED ADR-0003 |
| D-GOV-03 | QA-01 real native test harness and target runner/CI strategy, preserving R$0 | PROPOSED ADR-0075 |
| D-GOV-04 | GitHub PR protection ruleset actual enforcement, zero human reviewers, least-privilege Actions | NOT VERIFIED |
| D-GOV-05 | NLE-D009 engine source license and reusable SDK/export runtime rights, royalties if any, legal review when relevant | OPEN; **not decided here** |
| D-GOV-06 | GPU/OS/CPU minima and available QA-05 hardware vs NOT_QUALIFIED targets | UNDECIDED |
| D-GOV-07 | Risk classification per module and HIGH_ASSURANCE sign/privilege/storage obligations | UNCLASSIFIED |
| D-GOV-08 | Required product signing/telemetry/privacy and recovery, only after real implementation and BIZ-01 evidence | OPEN |

## STOP / STALE / incremental strategy
On change of checkpoint, Ledger/approved ADR, Scope, DoD, Architecture, catalog/relevant contract, base Git or security policy mark pending WO STALE and reconstruct Context Lock. Only generate **the next necessary decision module** and audit before another; not 80 ready WOs. Never perform an owner decision or mutate registry as an effect of viewing this document. Final status of this plan remains **PROPOSED** until owner acceptance of its process; source/hierarchy already approved govern.

[Global audit](../research/p00-global-research-closure-audit.md) · [evidence](../evidence/NLE-P00-GOV-001.md) · [Work Order](../work-orders/NLE-P00-GOV-001.md).
