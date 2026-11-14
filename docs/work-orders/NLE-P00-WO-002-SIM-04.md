# Research Work Order — NLE-P00-WO-002-SIM-04

**Date:** 2026-11-14 | **Research issue #183** | **Future coding issue #49 OPEN/BLOCKED**  
**BASE main:** `4dc7060fc0de16c036364a7363755a9ec4ea9144` | P00 documentation-only. No library selection for code and no Zcode implementation unlock.  
**Risk:** LOW research; future ELEVATED runtime/parsing/physics/rights. **Release class:** UNDECIDED.

## OBJECTIVE
Plan a first-class, engine-owned animation graph and skeletal motion pipeline with versioned Skeleton/Clip/Graph/Retarget/RootMotion/Ragdoll contracts, CPU/headless sampling and bounded performance/security/quality acceptance.

## CONTEXT
After SIM-03 research and separate checkpoint were merged, main base `4dc7060fc0de16c036364a7363755a9ec4ea9144`; 30/80 researched and 50 pending including historic CORE-04 research gap. 0 engine modules implemented, all 80 coding packets BLOCKED. SIM-03 and DATA-03 dependencies are research only. Coding #49 is untouched.

## SCOPE
Architecture doc, ADR-0034 PROPOSED, official-library/license/format comparison, typed semantic API, retarget/IK/root/ragdoll and graph consistency, proposed 96-case acceptance matrix, reproducible benchmark protocol, this WO, Evidence Bundle; dedicated research issue/branch/PR, exact-HEAD Docs Validation and objective audit, checkpoint reconciliation via second audited PR.

## OUT OF SCOPE
C++ implementation, vendor checkout/SDK import, actual assets/animations, licensing decision, production ABI, engine/editor/runtime tests, perf superiority claims, FBX SDK bundling, motion AI training, game/NET/AUDIO/renderer implementations, source-wide cleanup, deployment and release.

## FILES / SOURCES TO READ
Source hierarchy: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md`, `docs/product/module-catalog.md`, `docs/queue/implementation-registry.json`, `docs/queue/work-orders/SIM-04.md`, SIM-03 [architecture](../architecture/sim-03-character-controller-movement.md) and [contract](../contracts/sim-03-character-motor-api.md), SIM-02 [architecture](../architecture/sim-02-physics-3d.md), TWO-03 [architecture](../architecture/two-03-animation-sequencing.md). Source import/versioning DATA-03 must be respected even though runtime absent; no invented existing document path.

## REQUIREMENTS
GOV-001..005, CAP-004, native Windows/Linux/macOS+Web target concept, original 2D/2.5D/3D, headless server, human/CLI/MCP parity, no paid CI, no public MVP before future complete DoD. Module catalog dependencies SIM-03/DATA-03; preserve all owner-approved ledger decisions, especially NLE-D002/003/004/005/009/013.

## ARCHITECTURE RULES
Only CORE-04 owns fixed tick; DATA-03 import, DATA-04 source CAS, DATA-05 cook, WORLD ECS/revisions, SIM-03 movement/root ACK, SIM-02 ragdoll physics, GFX skinning, TWO-03 2D timeline, GAME/AUDIO events and NET authority. Bounded and typed API, generation/revision/WorldEpoch/OriginEpoch checks, immutable post-tick pose receipts, fail closed, no vendor native IDs in public schema, GPU interpolation nonauthoritative, explicit security/rights and fallback.

## CONSTRAINTS
Docs-only; prior research completed before opening; all future 96 cases `NOT_EXECUTED`; no actual benchmark or toolchain evaluation claim. Backend and license PROPOSED/UNDECIDED. No CodeRabbit, external human reviewer, paid CI, force push, bypass, secret, unlicensed assets or unrelated changes.

## ACCEPTANCE CRITERIA
- [ ] All eight research docs created, coherent, link/Source Pack checks pass.
- [ ] ADR-0034 clearly PROPOSED; technology and license candidates not adopted.
- [ ] Root-motion, physics contact, ragdoll safe barrier and asset/AI authoring security resolved at contract level.
- [ ] 96 prospective tests and measured protocol explicitly NOT RUN, no quality/performance claims.
- [ ] Exact-HEAD GitHub Docs Validation SUCCESS, diff verified docs-only, objective audit `APPROVED` with no known HIGH/CRITICAL in scope.
- [ ] Normal squash merge and main readback. Separate same-WO checkpoint PR with exact-HEAD CI/audit and unchanged coding readiness.
- [ ] Research issue closed only after checkpoint reconciled. Next SIM-05 only then.

## TESTS
Existing GitHub Docs Validation gates: Source Pack/link validation, module catalog/dependencies, registry, blocked Zcode selector. Runtime/unit/animation/GPU/Web/ASan/fuzz/replay/perf tests are FUTURE and **NOT EXECUTED**.

## DELIVERABLES
Architecture, ADR-0034, technology/licensing matrix, semantic API, 96-case future test matrix, benchmark protocol, WO, Evidence Bundle, research #183, research PR + checkpoint PR with verifiable CI/audits. Coding #49 stays BLOCKED.

## REVIEW FORMAT
pt-BR, base/head SHAs, changed files and exact CI/jobs URLs/conclusions, source fingerprints, security/assets/license, errors corrected, risk register, tests NOT RUN, proposed checkpoint delta and verdict APPROVED / CORRECTION REQUIRED / BLOCKED. No self-promotion of checkpoint before audit.

## STOP CONDITION
Stop on SHA drift, missing dependent contracts, CI failure, runtime/executor flag change, unverified library assertion, loss of rights proof, HIGH/CRITICAL or pre-existing checkpoint contradiction. Use same-WO Correction Delta in PR, then re-run exact-HEAD checks. Never advance with pending correction.

## CONTEXT LOCK
Research base `4dc7060fc0de16c036364a7363755a9ec4ea9144`; preflight checkpoint blob `8d526251d2766db97bc23ebedb7cb76fde7e0184`, ledger blob `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`, architecture blob `df62574cb3956c3ac9881631a4cf66be4e1abff1`, catalog blob `18d69bca439831d65982cb0f8acbca1dbaa2eee9`. Refresh if canonical sources changed.

## EVIDENCE
See [Evidence Bundle](../evidence/NLE-P00-WO-002-SIM-04.md). Initial PR/checkpoint status must be added only after observations, not anticipated.
