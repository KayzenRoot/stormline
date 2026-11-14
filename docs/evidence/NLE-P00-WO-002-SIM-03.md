# Evidence Bundle — NLE-P00-WO-002-SIM-03 Character Controller Research

**Status: RESEARCH DOCUMENTATION APPROVED/MERGED; CHECKPOINT RECONCILIATION PR PENDING OWN CI/AUDIT. NO CODE.**  
**Date:** 2026-11-14 | **Issue:** #180 | **Future coding issue:** #48 OPEN/BLOCKED.  
**BASE main:** `c8ee0cd07ab30cd207f7ea9b7aedfe06b09b3d64`.  
**Research branch:** `docs/NLE-P00-WO-002-SIM-03-character-controller-research`.  
**Initial docs head before this bundle:** `9f14331833dbd34e94b70273b73a211c0cedf46d`.  
**PR #181 initial head verified:** `e356952489fec55907e50c005baa60e849798235`; **Docs Validation run #43645409527 SUCCESS**. **Final audited exact HEAD:** `c0cafa09ad29ed9fc5ed9ffad0fec33ba26b14d6`, [Docs Validation run #43645494686](https://github.com/KayzenRoot/stormline/actions/runs/43645494686) **SUCCESS**, job #132602207124 (Source Pack/links, catalog DAG, registry, Zcode blocked selector). Objective pt-BR audit APPROVED documentary-only in [PR #181](https://github.com/KayzenRoot/stormline/pull/181), normal squash main `b1eef0a603683d1b876ac9d029b7d05e3d2b9a58` verified. No runtime test/benchmark claim.

## 1. Source Check and Context Lock
Canonical order: `docs/11-checkpoint.md` > Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS/catalog/registry/queue. Previous SIM-02 research approved/merged and checkpoint reconciled, latest main commit at research preflight `c8ee0cd07ab30cd207f7ea9b7aedfe06b09b3d64`. Source checkpoint blob observed `64f16740be507b55a490f9b0a45c48e2aa709cb9`. Mandatory SIM-01+SIM-02 executable runtimes missing; all 80 coding WOs BLOCKED and `executor_ready=false`. Research tally at base: 29/80 docs complete; 51 pending, including historical CORE-04 research gap recorded by checkpoint.

## 2. Scope and delivered proposed artifacts
- [Architecture](../architecture/sim-03-character-controller-movement.md): motor ownership, fixed-tick pipeline, movement quality, safety and headless boundaries.
- [ADR-0033 PROPOSED](../adr/0033-sim-03-authoritative-character-motor-policy.md): Stormline-owned typed controller, backend replaceability and physics authority.
- [Technology/license matrix](../research/sim-03-character-controller-technology-license-matrix.md): Jolt `CharacterVirtual` leading 3D candidate; Box2D 3.1+ mover experimental 2D candidate; Rapier and Godot documented comparisons only.
- [Semantic API v0.1](../contracts/sim-03-character-motor-api.md): profile, intent, state, epoch, support, motion receipt, failures.
- [72 future acceptance cases](../testing/sim-03-acceptance-matrix.md): all NOT EXECUTED.
- [Future benchmark protocol](../research/sim-03-character-motion-benchmark-protocol.md): clean-room synthetic fixtures, replay/physics/CPU/security and portability.
- [Research Work Order](../work-orders/NLE-P00-WO-002-SIM-03.md): full scope/constraints/stop condition and context lock.
- This Evidence Bundle.

**No executable files or dependencies intended.** No change to implementation #48, no licensing decision, no ADR approved for coding, no available backend and no output/demo produced.

## 3. Verification ledger: honest results
| Gate | Observed result |
|---|---|
| Original GitHub issue, branch and PR | #180, dedicated research branch, PR #181 merged; base `c8ee0cd07ab30cd207f7ea9b7aedfe06b09b3d64`; eight added docs files only |
| Source precedence | Reviewed checkpoint, Ledger, Scope, DoD, current SIM-01/02 boundary and blocked SIM-03 queue |
| Technology research | Official Jolt CharacterVirtual and architecture; Box2D experimental mover; Rapier character control; Godot documentation consulted |
| Documentation links/registry validation | **INITIAL PASS**: Docs Validation run #43645409527, exact initial HEAD `e356952489fec55907e50c005baa60e849798235` |
| Source/doc tests at exact final research PR HEAD | **PASS:** Docs Validation #43645494686 on exact HEAD `c0cafa09ad29ed9fc5ed9ffad0fec33ba26b14d6` |
| SonarCloud/Socket checks | **NOT VERIFIED** at this research HEAD; no new executable/dependency paths |
| Independent visual/CPU/device motion tests | **NOT RUN**, future only |
| Native/Web/headless engine build, ASan/TSan, benchmarks | **NOT RUN**, future only |
| Exact-head audit in pt-BR | **APPROVED research-only**, comment #6884822968 on PR #181 after exact-head CI; 8 docs files, no runtime changes, no known HIGH/CRITICAL in documentary scope |
| Normal squash merge / main readback / checkpoint | PR #181 **MERGED** squash `b1eef0a603683d1b876ac9d029b7d05e3d2b9a58`, main readback confirmed; **checkpoint separate PR PENDING** |

## 4. Risks and constraints
Potential HIGH if unbounded sweep loop, stale platform/contact UAF, missing collision ground marked traversable, spoofed TickId/authority, cross-dimension physics corruption, overflow/NaN, unsafe actor origin change or rollback/bitwise guarantee fabricated. Architectural mitigations are proposed, not tested. Third-party version and licenses must be pinned and audited prior to integration. No secrets, paid SaaS, proprietary code or game assets in research artifacts. Research-only changes do not satisfy any future production Definition of Done.

## 5. Proposed checkpoint delta, promoted only by separate audited PR
After the recorded successful exact-head documentation CI, review, normal squash merge and git readback of #181, this separate checkpoint reconciliation proposes recording SIM-03 research approved as documentation only; change research tally from 29 to 30 of 80 (37.5%) and pending to 50, with historical CORE-04 gap explicitly unresolved; ADR-0033 PROPOSED; all 80 implementation WOs still BLOCKED/executor_ready=false, future code #48 remains blocked. Next candidate documentary work SIM-04 after confirmed checkpoint. Change only the SIM-03 research_status, not any coding execution flags, and promote the checkpoint only after its separate CI/audit/merge. Zcode coding remains blocked.

## 6. Review format and stop condition
Audit verdict in Brazilian Portuguese: APPROVED / CORRECTION REQUIRED / BLOCKED with exact base/head SHA, changed files, CI outputs, link/ABI/license/security issues and severity. Any failed check or HIGH/CRITICAL requires same-WO correction; no progressing to SIM-04 before SIM-03 approval and checkpoint reconciliation.
