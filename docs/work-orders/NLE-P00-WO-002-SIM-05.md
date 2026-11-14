# Research Work Order — NLE-P00-WO-002-SIM-05

**2026-11-14 | Research #186 | Coding #50 OPEN/BLOCKED**  
**BASE main:** e6838dbdb5911acf4f0b67ce744a6c23a9396a22. **P00 docs-only, no library adopted, no code, executor not ready.** Risk LOW documentary; FUTURE ELEVATED for parser/streaming/concurrency/NET/Game authority. Release class UNDECIDED.

## OBJECTIVE
Specify original engine-owned 2D/2.5D/3D Navigation & Behavior with streaming-safe navmesh/pathfinding, dynamic topology and obstacle avoidance, behavior trees/statecharts, typed blackboard, perception/LOS and authoritative SIM-03 movement, plus measurable runtime acceptance and security plans.

## CONTEXT
SIM-04 research and checkpoint completed PR #184/#185; base 31/80 researches documented (38.75%), 49 pending including historical CORE-04 research-status gap, 0 runtime modules, all 80 coding WOs BLOCKED. Catalog SIM-05 deps WORLD-03 and SIM-02; these are only research docs, actual code missing. Future code #50 remains BLOCKED.

## SCOPE
Eight research-only documents: architecture, ADR-0035 PROPOSED, technology/license matrix, typed semantic API, 112 FUTURE cases, reproducible benchmark protocol, this complete WO and Evidence Bundle. Dedicated issue/branch/PR, exact-head Docs Validation and pt-BR objective audit; separate minimal-diff checkpoint PR after research merge. Preserve zero coding readiness.

## OUT OF SCOPE
C++/Rust/navmesh implementation, shader/GPU/engine/Editor build, package installs, dependency adoption, third-party GUI, licensing selection, cloud/LLM NPC inference, game AI combat mechanics, hidden-game knowledge exploit, network client authority, unrelated code or cleanup, deployment, guaranteed AAA or superior FPS claims.

## FILES / SOURCES TO READ
Priority: docs/11-checkpoint.md > docs/10-decisions-ledger.md and approved ADRs > docs/03-scope.md > docs/09-definition-of-done.md > docs/04-architecture.md > docs/02-requirements.md > AGENTS.md > docs/product/module-catalog.md > docs/queue/implementation-registry.json > docs/queue/work-orders/SIM-05.md. Module boundaries: [WORLD-03](../architecture/world-03-spatial-index-streaming.md), [SIM-02](../architecture/sim-02-physics-3d.md), [SIM-03](../architecture/sim-03-character-controller-movement.md), [SIM-04](../architecture/sim-04-skeletal-animation-motion.md), [DATA-03](../architecture/data-03-import-conversion-pipeline.md), [CORE-04](../architecture/core-04-time-simulation.md) proposed documents. Future exact code files TBD after approvals.

## REQUIREMENTS
GOV-001..005, CAP-related NPC/AI and gameplay capabilities, consistent 2D/2.5D/3D native Web potential and headless, owned public ABI, mandatory zero-paid CI, solo governance, no public MVP, Editor/CLI/MCP common authorized authoring schema, original/licensed benchmark scene. Catalog acceptance NPCs navigate dynamic world under streaming is future.

## ARCHITECTURE RULES
WORLD-03 owns cell leases/coverage; SIM-02 owns physics collider readiness/contact; SIM-03 owns motor actual motion; CORE-04 owns TickId, CORE-05 origin, CORE memory/jobs/log diagnostics; DATA-03/05 cook/rights and DATA-04 source CAS; GAME/NET own combat and secret visibility; SIM-04 animation/rig; original Stormline owned nav/BT/blackboard typed semantics. Bounded path nodes/events/graph depth, generation/epoch validation, fail closed when streaming coverage missing or LOS unknown, no raw Detour or BT vendor pointers/public GUI reliance.

## CONSTRAINTS
No dependencies/vendors installed, no unlicensed content, no paid external reviewer/CodeRabbit, no force-push or ruleset bypass, no code WOs executor readiness changed, no secrets. Numeric thresholds not approved; 112 future cases NOT EXECUTED; release class UNDECIDED and ADR PROPOSED.

## ACCEPTANCE CRITERIA
- [ ] Eight P00 research docs versioned with coherent links and 112 cases NOT RUN.
- [ ] ADR-0035 is PROPOSED, candidates/licenses/limitations explicit without adoption.
- [ ] Safe tile streaming/collider and path completeness, no unauthorized movement/LOS or blackboard data leak.
- [ ] Existing GitHub Docs Validation SUCCESS on final exact research PR head and docs-only diff audited in pt-BR APPROVED no known HIGH/CRITICAL.
- [ ] Normal squash merge and main readback of research PR.
- [ ] Separate same-WO checkpoint PR CI/audit/squash/readback, research tally becomes 32/80 only after validated reconciliation.
- [ ] All 80 coding WOs still BLOCKED/executor_ready=false/approved_adr=null; issue #50 OPEN/BLOCKED, next research SIM-06 only after checkpoint.

## TESTS
P00: only existing Docs Validation (local links/source pack, catalog DAG, WO registry, Zcode blocked selector) can run. Future tests: 112 planned path/mesh/crowd/streaming/BT/perception/security/portability cases plus future actual native/WASM/headless, fuzz/sanitizer, benchmarks; all NOT RUN.

## DELIVERABLES
Architecture, ADR-0035, technology/license matrix, semantic API contract, 112-case matrix, benchmark protocol, research WO, Evidence Bundle, #186 issue, PR(s), actual exact-head CI and audit receipts. #50 code issue untouched.

## REVIEW FORMAT
In pt-BR: base/head, diff paths, CI run/job statuses for exact HEAD, canonical fingerprints, rights/ABI/security, measured vs proposed evidence, issue and deferred risk, verdict APPROVED / CORRECTION REQUIRED / BLOCKED, proposed checkpoint delta. No fake engine claims, no unverified security check labeled PASS.

## STOP CONDITION
On stale source/HEAD, failed CI, HIGH/CRITICAL issue, insufficient evidence, unauthorized vendor adoption, scope creep or accidental coding unlock, stop and perform **same WO/PR Correction Delta**, or BLOCKED. Never advance to SIM-06 before checkpoint exact-head CI/audit/merge and readback.

## CONTEXT LOCK
BASE main e6838dbdb5911acf4f0b67ce744a6c23a9396a22. Critical blob fingerprints at preflight: checkpoint 87bd0d98b748ae77ea895bdf1c9fe8373af15a5a, decisions d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e, scope 4ef605c74632ece080b2650e37dd83a415b63310, DoD 160b3054db9ea1961308934b401488b838d24c3e, architecture df62574cb3956c3ac9881631a4cf66be4e1abff1, requirements 14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b, catalog 18d69bca439831d65982cb0f8acbca1dbaa2eee9, registry aa2a1c040ce9c87fae1d2de6f2566c991cfcb267. Refresh on critical change.

## EVIDENCE
See [Evidence Bundle](../evidence/NLE-P00-WO-002-SIM-05.md). CI/PR/merge results must only be written after independently observed, not anticipated.
