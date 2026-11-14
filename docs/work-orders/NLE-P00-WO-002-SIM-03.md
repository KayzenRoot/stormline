# Research Work Order — NLE-P00-WO-002-SIM-03

**2026-11-14 | Research issue #180 | Future implementation issue #48 OPEN/BLOCKED**  
**BASE main:** `c8ee0cd07ab30cd207f7ea9b7aedfe06b09b3d64`. Research documentation only; no engine build and no Zcode coding unlock.

## OBJECTIVE
Plan portable engine-owned 2D and 3D character motion, authoritative fixed-tick input/motor/physics collision, responsive movement policies, Web/native/headless tiers and verifiable replay/performance/security.

## CONTEXT
Prior documentary approvals: SIM-01/02 physics only, WORLD-01/03 and TWO-01/02 graphics/scene, CORE-04 clocks and CORE-05 coordinates as proposed contract. Currently 29/80 research modules documented, all 80 implementation WOs BLOCKED, coding prerequisites SIM-01 and SIM-02 not built. CORE-04 historical research gap recorded. No public MVP; Windows/Linux/macOS editor/export and web-game target, AI-native via validated common authoring kernel.

## SCOPE
Research architecture, source ownership, ABI-neutral typed contract, candidate technology/license matrix, actionable future 72-case acceptance plan, independent benchmark, risk/security and proposed ADR-0033. Preserve implementation #48 BLOCKED.

## OUT OF SCOPE
C++/WASM backend code, GPU shader/editor/player, vendor install, actual test/benchmark, game art, scripts/plugins, network prediction/rollback system, pathfinding, animation or ragdoll graph, gameplay ability system, paid CI, CodeRabbit, external human reviewer, force push, bypass, public release, enabling coding.

## FILES / SOURCES TO READ
Canonical hierarchy: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`; `AGENTS.md`; `docs/product/module-catalog.md`; `docs/queue/implementation-registry.json`; `docs/queue/work-orders/SIM-03.md`; SIM-01/02 and WORLD/CORE/TWO previous docs, official links in [technology matrix](../research/sim-03-character-controller-technology-license-matrix.md).

## REQUIREMENTS
- RQ-01 Owner: SIM-03 semantically owns character locomotion, collision query delegated to SIM-01/02.
- RQ-02 Fixed TickId, authoritative intent receipt, bounded sweeps/slides/steps and post-step immutable state.
- RQ-03 Typed profile, units, permissions, handles, revisions and stale epoch rejection.
- RQ-04 2D, 2.5D and 3D distinction; collision-ready streamed terrain and moving platform lifecycle.
- RQ-05 Jump/coyote/buffer/stop/dash policy and camera decoupling as profiles, not hardcoded gameplay.
- RQ-06 Native/headless and conditional web portability; security/fuzz, memory and performance proof future.
- RQ-07 CLI/MCP parity for authorized authoring, not privileged runtime authority.
- RQ-08 No release/implementation/benchmark claims without evidence.

## ARCHITECTURE RULES
No secondary ECS, physics solver, streaming engine, clock, rendering camera, input device manager, game rules or NET reconciliation. Rebase only at safe tick boundary. No backend native ID in public interface or direct unknown file access.

## CONSTRAINTS
No mandatory paid service. Solo admin auditing in pt-BR. Research ADR PROPOSED; future implementation #48 and `executor_ready=false` unchanged. Context must be refreshed if core Source Pack/HEAD moves.

## ACCEPTANCE CRITERIA
- [ ] Documents present and links valid; design has no contradictory owner claims
- [ ] Research proposed ADR and technology/license/portability status explicit
- [ ] Typed contract covers intent/motion/contact/epoch/security/failure receipt
- [ ] 72 future cases and benchmark protocol explicit as NOT EXECUTED
- [ ] Docs CI SUCCESS on exact final HEAD and objective audit APPROVED no HIGH/CRITICAL
- [ ] Normal squash PR merge, readback and separate checkpoint reconciliation; if not done remain PENDING

## TESTS
Documentation link/Source Pack validation and registry/blocked-selector tests by existing repo CI; current turn does NOT demonstrate these ran. All engine-specific unit/replay/fuzz/perf/cross-OS acceptance tests are FUTURE.

## DELIVERABLES
Architecture, ADR-0033, tech/license matrix, typed API, 72-case matrix, benchmark, this WO, Evidence Bundle, research #180 and PR. Implementation #48 untouched.

## REVIEW FORMAT
Brazilian Portuguese; base/head SHA and changed files, CI run URLs and exact SHA, output/failures, risks/license/source rights, docs-only diff, security and clear APPROVED/CORRECTION REQUIRED/BLOCKED; propose checkpoint delta, do not promote it before audit.

## STOP CONDITION
If CI fails, unapproved technology is promoted, changes touch runtime/registry executor readiness, source lock is stale, or a HIGH/CRITICAL issue arises: CORRECTION REQUIRED in same WO/PR or BLOCKED. Never start SIM-04 while SIM-03 research is unresolved.

## CONTEXT LOCK
Base `c8ee0cd07ab30cd207f7ea9b7aedfe06b09b3d64`. Critical source fingerprints require per-file blob SHA check and refreshed main before merger; latest checkpoint blob at preflight `64f16740be507b55a490f9b0a45c48e2aa709cb9` (subject to readback). Research commits are on distinct docs branch.

## EVIDENCE BUNDLE
See [Evidence Bundle](../evidence/NLE-P00-WO-002-SIM-03.md). A PR and green checks cannot be presumed prior to actual verification.
