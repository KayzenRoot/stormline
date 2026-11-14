# Research Work Order — NLE-P00-WO-002-SIM-07

**Date:** 2026-11-14 | **Research issue #192** | **Future coding issue #57 OPEN/BLOCKED** (issue #52 belongs to AUD-01).  
**BASE main:** `bf5d2fb497985344a8d1fea5dc1631d6f17505c4` | **P00 DOCUMENTATION ONLY, NO IMPLEMENTATION**.  
**Risk:** LOW research; future ELEVATED for physics/network, source inputs and replay. **Release class:** UNDECIDED. **No dependency is adopted.**

## OBJECTIVE
Research a high-quality Stormline-owned multivehicle physics and control contract covering 2D/3D wheeled/tracked ground vehicles, suspension/tires/drivetrain, simplified floating boats, 6DoF fixed-wing airplanes and rotorcraft, validated seat/game controls, SIM-02 one physical owner, SIM-03 passenger transition, NET authority/replay, GFX/AUD consumers, portability, security and reproducible future benchmarks.

## CONTEXT
At this WO start: SIM-06 research [PR #190](https://github.com/KayzenRoot/stormline/pull/190) and checkpoint [#191](https://github.com/KayzenRoot/stormline/pull/191) merged; verified main `bf5d2fb497985344a8d1fea5dc1631d6f17505c4`, **33/80 research documented (41.25%)**, 47 pending (historical CORE-04 gap), 0 engine runtime, all 80 code WOs blocked. SIM-07 catalog_order=34, deps SIM-02, SIM-03 and GAME-01; **GAME-01 research and NET-01..04 research are still pending**, runtime missing. Future code issue #57; no code branch allowed.

## SCOPE
Eight documentation-only deliverables: architecture, ADR-0037 PROPOSED, current official upstream technology/license matrix, semantic versioned vehicle/flight API, 144-case future test matrix, benchmark reproducibility protocol, this research WO and Evidence Bundle. Dedicated issue/branch, research PR exact-HEAD Docs Validation and pt-BR audit, normal squash/main readback; separate checkpoint reconciliation PR exact-HEAD CI/audit/squash/readback. Document risks and PROVE-OR-DROP, no unmeasured guarantees.

## OUT OF SCOPE
Engine code, build, shader, imported vendor SDK, sample proprietary cars/aircraft/boats, actual road/flight physics test, NET/GUI implementation, realtime autopilot/certified aircraft model, CFD/FSI/granular soil, flight controller on real hardware, asset redistribution, paid services, unrelated cleanup, release of whole SIM-07 implementation packet or bypass.

## FILES / SOURCES TO READ
Canonical priority: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md`/approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md`, `docs/product/module-catalog.md`, `docs/queue/implementation-registry.json`, `docs/queue/work-orders/SIM-07.md`. Module boundaries [SIM-02](../architecture/sim-02-physics-3d.md), [SIM-03](../architecture/sim-03-character-controller-movement.md), [SIM-06](../architecture/sim-06-destruction-environmental-response.md), WORLD-03/04, GAME-01 pending, NET-02/03/04 pending and CORE-04. Upstream official Jolt, Chrono, JSBSim, Bullet sources as linked in research matrix. Future actual code file set/CLI tests TBD; do not invent compiled sources.

## REQUIREMENTS
GOV-001..005, CAP-004 and graphics/audio/physics targets, original 2D/2.5D/3D/web and native Windows/Linux/macOS, headless server, AI-native shared authorized authoring kernel, user-requested drivable tank/truck/aircraft+rotor proofs and real timing, no public MVP/paid CI/mandatory human reviewer, original legal reference fixtures and reproducible measured evidence. Catalog acceptance remains UNMET.

## ARCHITECTURE RULES
SIM-02 **sole PHYS integrator**/contact authority; CORE-04 fixed tick and CORE-05 origin; SIM-03 occupant/motor transition; GAME-01 inputs/permissions; NET-02..04 authority/snapshots/rollback; WORLD-03/04 resident ground/water/wind; DATA-03/04/05 validated import/revision/cook; AUD/GFX nonauthoritative FX. No second JSBSim/Chrono integration on same BodyHandle. Bound forces/torques/wheels/rotors/lookup tables/telemetry, preserve source epochs and seat generations, typed errors/recovery, no vendor ABI in public types, CPU/headless first.

## CONSTRAINTS
P00 docs-only; exact 144 future cases **NOT EXECUTED**; no actual wheel/ship/flight, network client, benchmark, build, sanitizers, compiler or integrated vendor SDK. Licensed reference aircraft assets not distributed; JSBSim LGPL-2.1 distribution obligations and engine license NLE-D009 OPEN, other licenses/pins subject future review. No CodeRabbit, force push, destructive action, paid CI or false code readiness.

## ACCEPTANCE CRITERIA
- [ ] Eight scoped Markdown documents and local Source Pack links/DAG pass, ADR-0037 PROPOSED.
- [ ] Explicit wheeled/tires/drivetrain, tracked, marine hydrostatic, fixed-wing and rotorcraft model proposals, controls and NET/seat authority.
- [ ] Official source/version/license/ABI risk matrix without silently selecting vendor or shipping content.
- [ ] 144 FUTURE tests, benchmark fixtures/protocol and real certification disclaimer, **no runtime tests executed**.
- [ ] Research PR docs-only diff, exact final-head Docs Validation SUCCESS and pt-BR objective audit APPROVED with no known HIGH/CRITICAL documentary defect; normal squash/readback.
- [ ] Separate same-WO checkpoint PR with own exact-head CI/audit/squash/readback; count increases only when documented truth reconciled to **34/80 (42.5%)**.
- [ ] All 80 coding WOs remain `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`; SIM-07 coding issue #57 OPEN/BLOCKED; only after full checkpoint consider AUD-01 research.

## TESTS
Current GitHub **Docs Validation only**: Source Pack/local links, module catalog dependency DAG, WO registry, Zcode blocked-packet selector. Planned 144 future runtime cases, headless native/WASM physics, GRID/NET, security fuzz/ASan/TSan, GPU/VRAM and performance are all **NOT EXECUTED**. CI run/job details must be recorded from actual observed outputs on exact final HEAD.

## DELIVERABLES
Architecture, ADR-0037, technology/license matrix, typed API, prospective test matrix, benchmark protocol, WO, Evidence Bundle, research issue #192, research PR + separate checkpoint PR, observed CI/jobs and objective pt-BR audits, main readback. Coding issue #57 untouched.

## REVIEW FORMAT
pt-BR APPROVED / CORRECTION REQUIRED / BLOCKED with BASE/HEAD, list of files, exact checked CI SHA/run/jobs/results, upstream license/source uncertainty, Security/Architecture/NET/physics risk, future tests NOT EXECUTED, evidence diff and proposed Checkpoint Delta. Owner approval not inferred for technology.

## STOP CONDITION
STALE Context Lock/base, failed exact-head Docs Validation, unapproved library/license/role, duplicated SIM-02 solver, unexpected executable diff, known HIGH/CRITICAL issue, CI ambiguity or code readiness change => same-WO Correction Delta in PR or BLOCKED. No AUD-01 research until research AND checkpoint PRs valid and merged.

## CONTEXT LOCK
BASE main `bf5d2fb497985344a8d1fea5dc1631d6f17505c4`; preflight canonical blobs: checkpoint `fa59cadf8503ae8d5f079a3a4889d031e6bc7444`, Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`, Scope `4ef605c74632ece080b2650e37dd83a415b63310`, DoD `160b3054db9ea1961308934b401488b838d24c3e`, Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`, Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`, catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`, registry `c385ae6e813aa1c507edd38af15384614ad117e9`. If checkpoint/Scope/DoD/Architecture/ledger changes, mark STALE, rebase and revalidate before acting.

## EVIDENCE
See [Evidence Bundle](../evidence/NLE-P00-WO-002-SIM-07.md). Never claim prospective PR, CI, audit or merge results as fact before verified.
