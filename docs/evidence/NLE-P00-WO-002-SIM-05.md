# Evidence Bundle — NLE-P00-WO-002-SIM-05 Navigation & Behavior Research

**STATUS: RESEARCH BRANCH IN PROGRESS; PR/CI/AUDIT/MERGE/CHECKPOINT PENDING. NO ENGINE CODE.**  
**2026-11-14 | Research [#186](https://github.com/KayzenRoot/stormline/issues/186) | future coding [#50](https://github.com/KayzenRoot/stormline/issues/50) OPEN/BLOCKED.**  
**BASE main:** e6838dbdb5911acf4f0b67ce744a6c23a9396a22. **Research branch:** docs/NLE-P00-WO-002-SIM-05-navigation-behavior-research.

## 1. Canonical source lock and work classification
Prior SIM-04 research PR #184 merged and checkpoint PR #185 merged, main SHA base as above. Exactly 31/80 research status documented, 49 pending including CORE-04 historical research status gap, 0 engine code modules implemented. All 80 code packets BLOCKED and executor_ready=false, approved_adr=null. SIM-05 future coding #50 remains OPEN/BLOCKED. Source Pack snapshot:
- Checkpoint blob 87bd0d98b748ae77ea895bdf1c9fe8373af15a5a.
- Ledger d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e.
- Scope 4ef605c74632ece080b2650e37dd83a415b63310; DoD 160b3054db9ea1961308934b401488b838d24c3e.
- Architecture df62574cb3956c3ac9881631a4cf66be4e1abff1; Requirements 14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b.
- Catalog 18d69bca439831d65982cb0f8acbca1dbaa2eee9; registry aa2a1c040ce9c87fae1d2de6f2566c991cfcb267. Relevant WORLD-03, SIM-02/03 and CORE-04 research docs checked; no runtime present.

## 2. Research deliverables
- [Architecture](../architecture/sim-05-navigation-behavior.md): 2D/3D nav, topo/barriers, crowd, behavior, perception, security.
- [ADR-0035 PROPOSED](../adr/0035-sim-05-engine-owned-navigation-and-behavior-authority.md).
- [Technology and license matrix](../research/sim-05-navigation-behavior-technology-license-matrix.md): Recast/Detour zlib leading candidate; DetourTileCache/Crowd options; RVO2 Apache-2.0, BT.CPP MIT, SML BSL-1.0 comparators. All NOT ADOPTED.
- [Semantic API v0.1](../contracts/sim-05-navigation-behavior-api.md): typed NavWorld/Tile/Agent/Query/Path/Steering/Behavior/Blackboard/Perception/Action receipts and errors.
- [112 FUTURE acceptance cases](../testing/sim-05-acceptance-matrix.md): all NOT EXECUTED.
- [Future benchmark protocol](../research/sim-05-navigation-benchmark-protocol.md): original maps/crowd and dynamic streaming, no performance measured.
- [Research Work Order](../work-orders/NLE-P00-WO-002-SIM-05.md) and this Evidence Bundle.

## 3. Actual observed verification ledger (amend only after observation)
| Gate | Result |
|---|---|
| Issue and branch | #186 opened, dedicated research branch from e6838dbd |
| Source hierarchy and upstream modules | README/Scope/DoD/Ledger/Architecture/Requirements, WORLD-03, SIM-02/03, CORE-04 read |
| PR, exact final HEAD and changed files | PENDING |
| Docs Validation (exact final HEAD) | NOT VERIFIED |
| Sonar/Socket other security CI | NOT VERIFIED |
| Technical/C++/WASM/headless build, nav/AI unit/integration tests | NOT RUN |
| 112 future acceptance cases, security fuzz, ASan/TSan, benchmarks | NOT EXECUTED |
| pt-BR objective review | PENDING |
| Research PR squash/main readback | PENDING |
| Separate checkpoint PR exact-head CI/audit/merge | PENDING |

## 4. Risk register and actual scope
Potential future HIGH: stale/revoked nav tiles treated as ground; hidden-information leak from client blackboard; actor/tool spoofed motor/damage orders; malformed polygon/parser UAF; unbounded A*/BT/LOS query DoS; unsafe path completion after world unload; conflicting collider epochs. **Proposed mitigations**: fail-closed PATH_PARTIAL/UNKNOWN; leases/generational handles/epoch-bound jobs; SIM-03 action ACK and GAME authority; bounds, sandbox and fuzz; permissioned/redacted view. No runtime controls implemented or tested here. No vendor code, third-party assets, dependency lockfile or credentials imported. Open engine license not decided.

## 5. Checkpoint Delta proposal (NOT YET PROMOTED)
After approved research PR exact-head Docs Validation, objective audit, normal squash and main readback, propose separate checkpoint PR recording **32 of 80 researched (40%)**, **48 pending** (including historical CORE-04), ZERO implemented; SIM-05 changes **research_status only** to RESEARCH_DOCUMENTED_ADR_PROPOSED. All 80 future coding packets remain BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false and approved_adr=null; future code issue #50 open and ADR-0035 PROPOSED. Next research SIM-06 Destruction & Environmental Response only after checkpoint merge verified.

## 6. Verdict contract
pt-BR APPROVED / CORRECTION REQUIRED / BLOCKED, exact BASE/HEAD and observed tests and risks; never treat future 112 tests as PASS or advance on failing CI.
