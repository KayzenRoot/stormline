# Evidence Bundle — NLE-P00-WO-002-SIM-03 Character Controller Research

**Status: DOCUMENTARY DRAFT / PR AND CI AUDIT PENDING. NOT APPROVED OR MERGED.**  
**Date:** 2026-11-14 | **Issue:** #180 | **Future coding issue:** #48 OPEN/BLOCKED.  
**BASE main:** `c8ee0cd07ab30cd207f7ea9b7aedfe06b09b3d64`.  
**Research branch:** `docs/NLE-P00-WO-002-SIM-03-character-controller-research`.  
**Initial docs head before this bundle:** `9f14331833dbd34e94b70273b73a211c0cedf46d`.  
**PR final HEAD/CI:** PENDING exact-head readback. No test/benchmark success claimed.

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
| Original GitHub issue and branch created | #180 and research branch created via connected GitHub; commits received for authored docs |
| Source precedence | Reviewed checkpoint, Ledger, Scope, DoD, current SIM-01/02 boundary and blocked SIM-03 queue |
| Technology research | Official Jolt CharacterVirtual and architecture; Box2D experimental mover; Rapier character control; Godot documentation consulted |
| Documentation links/registry validation | **PENDING CI**, not a passing claim |
| Source/doc tests at exact final PR HEAD | **PENDING** |
| SonarCloud/Socket checks | **PENDING; do not infer PASS** |
| Independent visual/CPU/device motion tests | **NOT RUN**, future only |
| Native/Web/headless engine build, ASan/TSan, benchmarks | **NOT RUN**, future only |
| Exact-head audit in pt-BR | **PENDING** |
| Normal squash merge / main readback / checkpoint | **NOT DONE** |

## 4. Risks and constraints
Potential HIGH if unbounded sweep loop, stale platform/contact UAF, missing collision ground marked traversable, spoofed TickId/authority, cross-dimension physics corruption, overflow/NaN, unsafe actor origin change or rollback/bitwise guarantee fabricated. Architectural mitigations are proposed, not tested. Third-party version and licenses must be pinned and audited prior to integration. No secrets, paid SaaS, proprietary code or game assets in research artifacts. Research-only changes do not satisfy any future production Definition of Done.

## 5. Proposed checkpoint delta, NOT promoted
After objective exact-head documentation CI, review, owner-allowed normal squash merge and git readback, record SIM-03 research approved as documentation only; change research tally from 29 to 30 of 80 (37.5%) and pending to 50, with historical CORE-04 gap explicitly unresolved; ADR-0033 PROPOSED; all 80 implementation WOs still BLOCKED/executor_ready=false, future code #48 remains blocked. Next candidate documentary work SIM-04 after confirmed checkpoint. Do not change registry/Checkpoint or unlock Zcode merely because the draft exists.

## 6. Review format and stop condition
Audit verdict in Brazilian Portuguese: APPROVED / CORRECTION REQUIRED / BLOCKED with exact base/head SHA, changed files, CI outputs, link/ABI/license/security issues and severity. Any failed check or HIGH/CRITICAL requires same-WO correction; no progressing to SIM-04 before SIM-03 approval and checkpoint reconciliation.
