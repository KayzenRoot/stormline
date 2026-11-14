# Work Order — NLE-P00-WO-002-CORE-05

**Issue:** #102 | **Risk:** LOW documentation; future implementation ELEVATED for world precision/persistence/network coupling.  
**Status:** APPROVED / MERGED (research documentation only; PR #103). ADR-0007 remains PROPOSED; code NOT IMPLEMENTED | **Base SHA:** c96fcc0d5e5094c84cd1e0af9085fba6849bcecb

## OBJECTIVE
Select mathematical/type/coordinate technology research direction and publish an auditable typed contract, licensing matrix and test plan before Zcode implementation.

## CONTEXT
80 candidate modules prepared as blocked packages. CORE-01/02/03/04 research and checkpoints approved as docs only; no native engine. CORE-05 implementation issue #22 is separately BLOCKED.

## SCOPE
Math conventions + scalar/GLM/Eigen/DirectXMath/MathFu comparative study; 2D/3D/UI space conversions; matrices/quaternions; strong units; world/floating origin precision; stable persistence IDs; error model; Windows/Linux/macOS/Web/headless and golden tests; ADR-0007 PROPOSED; update Architecture/Backlog and link blocked packet; audit/CI/Evidence.

## OUT OF SCOPE
C++ code; vendoring/installing math libraries; shipping binaries; deciding GPU API, actual physics solver, network schemas or runtime ECS; public MVP, paid CI, CodeRabbit, external human reviewer, unapproved license or silent interface break.

## FILES / SOURCES TO READ
Checkpoint > Ledger and approved ADRs > Scope > DoD > Architecture > Requirements > module catalog > CORE-01/04 research > docs/queue/work-orders/CORE-05.md > AGENTS.md, Zcode handoff and official source links. Read Git base/branch/PR state first.

## REQUIREMENTS
GOV-001..005, CAP-001/004/005/006/009/010/011/013/016 as relevant, NFR-001..005, NLE-D013..020 and Module Catalog CORE-05. Cross-target/native headless and future AI validated authoring.

## ARCHITECTURE RULES
No third-party math types in public SDK; explicit units/axes/handedness/matrix order; stable persistent IDs vs generational handles; no numeric precision guarantee without target tests. CORE-04 determines safe tick barriers; GPU clip conversion belongs GFX, physics and net remain downstream.

## CONSTRAINTS
P00 documentation only, no implementation #22 promotion; free public CI; no secrets, destructive Git, bypass, paid dependencies or mandatory external reviewer. Proposals are not approved production technology.

## ACCEPTANCE CRITERIA
- [ ] Document matrix of core candidate math libraries, sources, license, support and alternatives.
- [ ] Propose typed math/units and fixed axis conventions including 2D/UI/backend conversion, errors and serialization.
- [ ] Define large-world f64/cell precision, floating origin, epoch boundaries, persistent-vs-runtime identity and downstream boundaries.
- [ ] Write golden test matrix, error/overflow cases, cross-platform/SIMD differential and measurable precision budgets to be frozen in later implementation.
- [ ] ADR-0007 remains PROPOSED for implementation, issue #22 stays BLOCKED.
- [ ] Actual GitHub Docs Validation PASS on exact PR HEAD; Evidence Bundle SHA/tests/risks; pt-BR objective audit.
- [ ] After audited merge, reconcile checkpoint within SAME WO via separate validated delta, no next increment before completion.

## TESTS
Now: python3 scripts/validate_docs.py, validate_module_catalog.py, validate_wo_registry.py, select_wo.py CORE-05 must return BLOCKED, GitHub Actions docs-validation. Future C++ golden precision tests not run.

## DELIVERABLES
docs/architecture/core-05-math-coordinate-types.md; docs/research/core-05-technology-matrix.md; docs/adr/0007-core-05-coordinate-policy.md; this WO; linked Architecture/Backlog/CORE-05 implementation packet; Evidence Bundle; PR, audited checkpoint delta.

## REVIEW FORMAT
pt-BR, SHA base/HEAD, changed files, CI run ID/conclusions, source consistency, license/security/precision risks, regressions, verdict APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION
Stale canonical docs, contradictory coordinate/matrix assumptions, unverified security/license, missing CI, type-correctness defect HIGH/CRITICAL, unauthorized cost/implementation or changed issue #22 status. Fix in same WO/PR.

## CONTEXT LOCK
BASE c96fcc0d5e5094c84cd1e0af9085fba6849bcecb. Critical fingerprints to be recorded in Evidence Bundle and revalidated if checkpoint/Scope/DoD/Architecture/ADR changes. No executor-ready state.
