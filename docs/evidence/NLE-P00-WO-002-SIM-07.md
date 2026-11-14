# Evidence Bundle — NLE-P00-WO-002-SIM-07 Vehicles & Flight Research

**STATUS: RESEARCH PR #193 APPROVED/SQUASH-MERGED; SEPARATE CHECKPOINT PR PENDING OWN CI/AUDIT. NO ENGINE IMPLEMENTATION.**  
**Date:** 2026-11-14 | Research [#192](https://github.com/KayzenRoot/stormline/issues/192) | Future implementation [#57](https://github.com/KayzenRoot/stormline/issues/57) OPEN/BLOCKED.  
**BASE main:** `bf5d2fb497985344a8d1fea5dc1631d6f17505c4` | Research branch `docs/NLE-P00-WO-002-SIM-07-vehicles-flight-research`.

## 1. Source check and Context Lock
SIM-06 research #189 and PR #190/#191 approved/merged, main readback verified; canonical 33/80 researched, 47 pending including historical CORE-04 research_status gap, zero engine executable modules. 80 coding WOs all BLOCKED, executor_ready=false, approved_adr=null. **Coding SIM-07 is #57**, checked registry+GitHub; #52 is AUD-01, avoid erroneous linkage. GAME-01 (#56) is RESEARCH_PENDING, NET-01..04 (#62..65) are RESEARCH_PENDING and no runtime. Source docs include SIM-02/03/06, catalogue, latest checkpoint, decisions, scope, DoD, architecture, requirements and AGENTS.
Preflight blobs: checkpoint `fa59cadf8503ae8d5f079a3a4889d031e6bc7444`; Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; registry `c385ae6e813aa1c507edd38af15384614ad117e9`.

## 2. Research deliverables (no engine)
- [Architecture](../architecture/sim-07-vehicles-flight-dynamics.md): single-owner SIM-02 forces/torques, car/truck/wheel suspension/tire/drivetrain, tracks, buoyancy, 6DoF wing and rotor, controls and seat transitions, NET authority, source epochs, headless and threats.
- [ADR-0037 PROPOSED](../adr/0037-sim-07-single-authority-vehicle-flight-dynamics.md), not approved for implementation.
- [Technology and license matrix](../research/sim-07-vehicle-flight-technologies-license-matrix.md): Jolt MIT wheeled/tracked leading candidate, Chrono BSD-3-Clause comparator, JSBSim LGPL-2.1 flight reference, Bullet zlib comparator, OpenVSP NOSA1.3 authoring-only reference; none integrated/adopted.
- [Typed API](../contracts/sim-07-vehicle-flight-api.md): Vehicle/Seat handles, ControlIntent, force plan/PHYS ACK, profiles, water/weather, NET state, VFX/audio events and typed errors.
- [144 FUTURE cases](../testing/sim-07-acceptance-matrix.md): all NOT EXECUTED.
- [Future benchmark protocol](../research/sim-07-vehicle-flight-benchmark-protocol.md): original reproducible fixture suite, CPU/NET/flight/marine/road/track and GPU independence, zero measured results.
- [Research WO](../work-orders/NLE-P00-WO-002-SIM-07.md) and this Evidence Bundle.

No SDK downloaded/compiled, Jolt/Chrono/JSBSim/Bullet code, flight scripts, test vehicle asset, game screenshots, UI, build, benchmark, real hardware or customer pilot. No safety certification, operating flight performance, physically validated or network test success claim.

## 3. Actual validation ledger (update only after observation)
| Gate | Observed |
|---|---|
| Research issue and branch | #192 created, branch from main base SHA |
| Research PR/base/final HEAD | [PR #193](https://github.com/KayzenRoot/stormline/pull/193) MERGED, base `bf5d2fb497985344a8d1fea5dc1631d6f17505c4`, final audited HEAD `623b20d1471d44067b2ec391b06bd57a2cfc1171`, eight new Markdown-only files, no runtime/registry edits. |
| Initial Docs Validation (NOT FINAL after this revision) | [Run #43654221241](https://github.com/KayzenRoot/stormline/actions/runs/43654221241) SUCCESS on initial HEAD `72f4b9bef4a9f4029e85bc9ad566df58c41a97f5`, job #132629091147: Source Pack/link, dependency DAG, WO registry and blocked Zcode selector all SUCCESS. This was initial CI; final exact-HEAD run also passed independently, as recorded below. |
| Final exact-HEAD Docs Validation | [Run #43654252714](https://github.com/KayzenRoot/stormline/actions/runs/43654252714) SUCCESS at `623b20d1471d44067b2ec391b06bd57a2cfc1171`, job #132629190633: Source Pack/link, taxonomy/dependency DAG, registry and Zcode selector all SUCCESS. | 
| Other SonarCloud/Socket/security checks at exact HEAD | NOT VERIFIED for final head (not PASS). |
| Build/runtime Windows/Linux/macOS/Web/headless | NOT EXECUTED |
| 144 prospect runtime tests, static/flight/NET/security fuzz/sanitizer | FUTURE / NOT EXECUTED |
| Objective pt-BR documentary audit | APPROVED documentary-only [comment #6886017641](https://github.com/KayzenRoot/stormline/pull/193#issuecomment-6886017641) after final-head CI, no known HIGH/CRITICAL documentary-scoped defect; no runtime tests. |
| Research PR normal squash/readback | PR #193 normal squash MERGED main `9617a05371b3426197eafde445460f2844b4c9cc`, main SHA readback verified. |
| Separate checkpoint PR CI/audit/squash/readback | PENDING at the time of this draft; required separate CI on exact head, audit and normal squash/main readback. |

## 4. Risk ledger and security caveats
FUTURE HIGH concerns: double-integration/PHYS divergence, untrusted input and seat replay, unbounded spring force/rotor torque, airfoil table NaN/oversize, XML external entities/DoS, stale ground-water-wind sampling/OriginEpoch, network client physics authority, hot reload UAF, wrong world status and LGPL packaging violation, unlicensed reference aircraft content. Proposed mitigation: immutable source schema, finite bounds/units, GAME role, net anti-cheat, SIM-02 sole authority, source/lease versioning, parser fuzz, ASan/TSan and repeatable numerical traces, legal review. None of these controls have been implemented or executed in Stormline.

## 5. Checkpoint Delta PROPOSED, not yet promoted
After research PR audited exact-head Docs Validation, squash and main readback, and separate checkpoint PR with its own CI/audit/merge, mark SIM-07 `research_status=RESEARCH_DOCUMENTED_ADR_PROPOSED` ONLY. New count **34/80 researched (42.5%)**, **46 research pending** including CORE-04 gap; **zero engine runtime**, all 80 coding packets `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`. Coding issue #57 remains OPEN/BLOCKED, ADR-0037 PROPOSED and release class UNDECIDED. Next catalog research AUD-01 Audio Device & Mixer, NOT a nonexistent SIM-08.

## 6. Audit contract
Evidence from actual linked CI runs and final SHA only; pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED with source/architecture, tests NOT RUN, license/NET/physics risks and proposed delta. No leap to AUD-01 if checkpoint not finalized.
