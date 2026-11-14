# Research Work Order — NLE-P00-WO-002-SIM-06

**2026-11-14 | Research issue #189 | Future coding #51 OPEN/BLOCKED**  
**BASE main:** `1a0fd10dde4f9fa119732d445fbce8499bec29f6`. **Phase:** P00 DOCUMENTATION ONLY, no code or SDK adoption. **Risk:** LOW research; future ELEVATED for mesh/IO/stream/physics/NET and recovery. **Release class:** UNDECIDED.

**RESEARCH RESULT APPROVED/MERGED:** [PR #190](https://github.com/KayzenRoot/stormline/pull/190), audited final HEAD `294533f67a163b82d68493b715c13744b041a3a0`, [Docs Validation #43653162383](https://github.com/KayzenRoot/stormline/actions/runs/43653162383) SUCCESS job #132625841915, objective pt-BR audit comment #6885868456, normal squash main `74d66e793e2ddeb5f42884f75f657a4ede551ff0` and readback. Checkpoint PR separately must pass own exact-head CI/audit. 120 engine tests NOT RUN, coding #51 BLOCKED.

## OBJECTIVE
Specify high-quality but safely bounded original Stormline destruction and environmental impact: versioned destructible chunk/bond assets, material-dependent fracture, SIM-02 rigid body activation, GFX-08 cosmetic debris and dust, persistent decals, WORLD-03/04 streaming/terrain edits and SIM-05 nav/character support coherence, along with future independent quality/CPU/GPU/VRAM/security proof.

## CONTEXT
Previous SIM-05 research PR #187 and checkpoint PR #188 audited/merged/readback, at main `1a0fd10dde4f9fa119732d445fbce8499bec29f6`; 32/80 research documented (40%), 48 pending incl historical CORE-04 research gap, zero engine runtimes; all 80 implementation packets BLOCKED. Mandatory catalog dependencies SIM-02/GFX-08/WORLD-03 researched conceptually only, not compiled. Coding #51 remains OPEN/BLOCKED.

## SCOPE
Eight new documentary artifacts: original architecture with streaming/collision/nav damage staging; ADR-0036 PROPOSED; license/technical comparison (NVIDIA Blast, Voro++, OpenVDB, libigl, Jolt, optional Houdini reference); typed API/source and error/receipt contracts; 120 future test matrix; reproducible headless/cook/crowd/VFX/terrain/performance benchmark protocol; this Work Order; Evidence Bundle. Create dedicated research issue/branch/PR with exact-head CI/audit and separate same-WO checkpoint PR/reconciliation. No implementation or dependency changes.

## OUT OF SCOPE
C++ runtime, mesh/particle shader, imported vendor SDK and executable tests, full dynamic GPU fracture/voxel terraforming, water/soft-body simulation, third-party game assets, mandatory Houdini/paid tools, public release, underlying PHYS/WORLD/VFX implementations, codec/commercial redistribution decision, arbitrary MCP privileged damage, unrelated cleanup.

## FILES / SOURCES TO READ
Precedence: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/SIM-06.md`. Contract boundaries: [SIM-02](../architecture/sim-02-physics-3d.md), [GFX-08](../architecture/gfx-08-vfx-particle-graph.md), [WORLD-03](../architecture/world-03-spatial-index-streaming.md), [WORLD-04](../architecture/world-04-terrain-environment.md), [SIM-05](../architecture/sim-05-navigation-behavior.md), [GFX-04](../architecture/gfx-04-geometry-visibility-lod.md), [DATA-05](../architecture/data-05-cooking-streaming-bundles.md). Future implementation files and exact commands TBD after owners/coding prerequisites.

## REQUIREMENTS
GOV-001..005, relevant CAP-001/002/004 and future environmental gameplay needs, 2D/2.5D/3D and Windows/Linux/macOS/Web capability tiers, CPU/headless and no mandatory paid CI, solo approved governance, original rights/provenance, Editor/CLI/MCP parity, no public MVP until full v1.0 DoD. Catalog acceptance **Degradação controlada, orçamento de fragmentos e sincronização** is a FUTURE test, not satisfied by docs.

## ARCHITECTURE RULES
SIM-02 owns bodies, contacts and PHYS barriers; GAME/NET own damage authority; WORLD-03 stream leases, WORLD-04 terrain source, SIM-05 nav, SIM-03 support, GFX-08 particle VFX (cosmetic only), GFX-04/05/06/07 render/material/light, DATA-02/03/04/05 rights/cook/journal. Use fixed CORE-04 TickId and CORE-05 OriginEpoch. Stormline owns typed generation/epoch/revision-safe external contract with rollback, bounded chunks/debris, immutable structural receipts and headless CPU fallback. No raw vendor native pointers or direct renderer/physics writes.

## CONSTRAINTS
Docs-only, no vendor library/version adopted, no unverified legal/license assertion, paid service, CodeRabbit, external human reviewer, force push, bypass or high-risk destructive action. 120 test cases FUTURE/NOT EXECUTED, no benchmark/feature superiority claim, no numerical performance budgets until proof. ADR-0036 PROPOSED, all 80 coding WOs and issue #51 remain blocked/executor_ready=false.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight scoped docs versioned and local links/Source Pack/DAG valid.
- [ ] ADR-0036 PROPOSED, tech/license/source-right and licensing caveats accurate, no integrated library.
- [ ] Typed structural source/event/PHYS/VFX/world/nav/terrain error contract, safe publication and idempotent recovery.
- [ ] 120 cases FUTURE NOT EXECUTED and reproducible benchmark protocols, no fabricated thresholds/success.
- [ ] GitHub Docs Validation SUCCESS on final exact research HEAD, objective auditoria pt-BR APPROVED, no known HIGH/CRITICAL in documental diff.
- [ ] Normal squash research PR + main readback; distinct checkpoint PR with independent exact-head CI/audit/merge/readback; count 33/80 only after reconciliation.
- [ ] All 80 implementation WOs remain BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, #51 OPEN/BLOCKED, next SIM-07 only after this WO approved.

## TESTS
In P00 only repository existing Docs Validation (Source Pack/local links, module DAG, registry and blocked Zcode selector); technical animation/physics/mesh/CPU/GPU/headless/native/WASM/fuzz/sanitizer/perceptual and benchmark cases **NOT EXECUTED**. Planned matrix describes future explicit evidence. CI must verify final exact HEAD after updating Evidence Bundle.

## DELIVERABLES
Architecture, ADR-0036, license/tech matrix, API, 120-case matrix, benchmark, this WO and Evidence Bundle; research #189, research PR + checkpoint PR, CI run/job link/HEAD and pt-BR objective audit. Code #51 untouched.

## REVIEW FORMAT
pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED, BASE/HEAD, changed files, actual GitHub CI run/jobs, source fingerprints, licensing/asset rights, threat/quality/rollback issues, tests NOT RUN, proposed checkpoint delta (no self-promotion).

## STOP CONDITION
STALE base/source, unexpected diff, license/rights mistake, exact-head CI failure, known HIGH/CRITICAL, false code readiness, inaccessible physics/World owner, destructive unknown commit or interrupted PR => same WO/PR Correction Delta or BLOCKED, no next SIM-07 until checkpoint reconciled.

## CONTEXT LOCK
BASE main `1a0fd10dde4f9fa119732d445fbce8499bec29f6`; checkpoint blob `6dfac9ee8d48ffaf408baae0de2180b31161261e`; ledger blob `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; registry `ad2472be447f16ed38ae54aa22982999fe63ddc1`; GFX-08 `33bf971654f557b7ad6d969eb68573e495ef7759`. Recheck if main/source changes.

## EVIDENCE
See [Evidence Bundle](../evidence/NLE-P00-WO-002-SIM-06.md). PR and CI statuses recorded as observed only, update after checks.
