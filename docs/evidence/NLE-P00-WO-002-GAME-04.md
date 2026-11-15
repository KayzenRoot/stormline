# Evidence Bundle — NLE-P00-WO-002-GAME-04 Gameplay Systems & Event Bus

**Created 2026-11-15.** Documentary research baseline; **status at creation: IN REVIEW, NOT YET APPROVED**. Research issue [#220](https://github.com/KayzenRoot/stormline/issues/220), future coding [#60](https://github.com/KayzenRoot/stormline/issues/60) **OPEN/BLOCKED**.

## Objective / base / Context Lock
Base main `b64194591d761cd3e785337b10a524d085ec04d1` after GAME-03 #219 closeout squash/readback. Source and canonical Git blob fingerprints documented in [WO](../work-orders/NLE-P00-WO-002-GAME-04.md); current critical docs remain unchanged in this research PR. Branch `docs/NLE-P00-WO-002-GAME-04-gameplay-event-bus`.

## Exact eight new files (research PR only)
1. [Architecture](../architecture/game-04-gameplay-systems-event-bus.md)
2. [ADR-0045 PROPOSED](../adr/0045-game-04-typed-deterministic-gameplay-event-bus.md)
3. [Technology and licenses](../research/game-04-gameplay-technology-license-matrix.md)
4. [Semantic contracts](../contracts/game-04-gameplay-event-api.md)
5. [128 future tests](../testing/game-04-acceptance-matrix.md)
6. [Benchmark protocol](../research/game-04-gameplay-benchmark-protocol.md)
7. [Work Order](../work-orders/NLE-P00-WO-002-GAME-04.md)
8. This Evidence Bundle.

**Audit targets:** no C++, no manifests/dependency installation, no binary assets/data; zero changes to checkpoint/ledger/backlog/registry/code packets in research PR. Confirm diff/tree via GitHub. Validate canonical links and safety boundaries. Research-only intended risk LOW; future runtime ELEVATED. No engine license choice (NLE-D009 OPEN), no external library adopted.

## Observed vs proposed evidence (MUST UPDATE ONLY AFTER VERIFYING)
| Gate | State at creation |
|---|---|
| Research final HEAD SHA | PENDING observed GitHub push |
| Docs Validation at exact final HEAD | NOT RUN at document creation; see later PR check/job for actual result |
| pt-BR objective scoped audit | PENDING |
| Normal squash research PR + main readback | PENDING |
| Independent checkpoint PR CI / audit / squash / main readback | PENDING, not self-promoted |
| 128 GAME-04 gameplay tests | **FUTURE / NOT EXECUTED (0/128)** |
| Runtime, sanitizers, fuzz, Windows/Linux/macOS/Web builds | **NOT EXECUTED / NOT IMPLEMENTED** |
| CPU/GPU/net benchmarks, latency and tail percentiles | **NOT MEASURED** |
| Dependency installation / adopted library / product release | **NONE** |

## Architecture/security risks
- P00 planned typed schemas cannot yet prove cross-target bitwise determinism, tick-order behavior, memory bounds or race safety.
- Script/NET untrusted intents, poison/quest/loot reward duplication, event storms, overflow, scene epoch mismatch and partial save durability demand runtime adversarial proof.
- Production no-code state: GAME-01/02/WORLD-02/CORE-03/04/WORLD-01/NET/DATA services do not yet exist; no integration performed.
- License upstream links are candidate references, pins and complete SBOM/NOTICE remain future gates.
- Rollback is revert of new documentary research commits/PR only, with no runtime or persisted data side effects.

## Checkpoint Delta — PROPOSED, not yet promoted
Only after research audited/squashed/readback, create separate checkpoint PR editing checkpoint, backlog, registry **GAME-04.research_status only**, and GAME-04 WO/evidence. Target counts **42/80 researched (52.5%), 38 research pending, 0 implemented**. Every one of 80 coding packets stays `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false` and `approved_adr=null`, release class UNDECIDED; coding #60 remains OPEN/BLOCKED. Close research #220 only after checkpoint PR own exact-final-HEAD Docs Validation, pt-BR audit, normal squash, main readback. Next GAME-05 research only after closeout.

## Review format
Pt-BR audit: BASE, final HEAD, changed files, Docs Validation run/job and exact SHA, source fingerprints, source/ADR/API ownership, rights, threat model, FUTURE tests not run, risks, proposed delta, HIGH/CRITICAL count, objective APPROVED / CORRECTION REQUIRED / BLOCKED. PR comments record external evidence instead of speculative pre-populating this file.


## Observed research evidence and separate checkpoint delta (2026-11-15)
**Research PR #221 final HEAD** `4ee8839c93f5e1782993f40178a8f71b2321073d`, base `b64194591d761cd3e785337b10a524d085ec04d1`; GitHub readback precisely eight new Markdown and no modified files, 554 additions, zero deletions; deterministic count 128 unique G04-T001..G04-T128 cases FUTURE/NOT EXECUTED. [Docs Validation run #43706155959](https://github.com/KayzenRoot/stormline/actions/runs/43706155959), job #132787563990: **SUCCESS on exact HEAD** including Source Pack/local links, module DAG, registry and Zcode selector blocked. Same SHA SonarCloud/Socket checks success, but neither tests gameplay runtime. [pt-BR audit comment #6893260379](https://github.com/KayzenRoot/stormline/pull/221#issuecomment-6893260379) APPROVED for docs ONLY; no known HIGH/CRITICAL defect in scoped docs. PR marked ready and **normal squash merged** main `a85b49b184354a3aa7d1420a40dbfd78cec5f309`; main HEAD, merged PR metadata and GAME-04 contract read back from main.

**Separate checkpoint PR base:** `a85b49b184354a3aa7d1420a40dbfd78cec5f309`. Five affected files ONLY: checkpoint, backlog, registry, GAME-04 WO and Evidence Bundle. Registry semantic diff is exactly `modules[GAME-04].research_status=RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`. Research 42/80 (52.5%), pending 38/80, 0/80 code implemented. All 80 coding WOs retain BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class=UNDECIDED; #60 OPEN/BLOCKED. **Checkpoint PR exact-head CI, audit, squash, final main readback and research #220 closure PENDING at document creation** and must be independently verified. No game code or dependency installed and no runtime/benchmark/128 tests executed.

**Correction policy:** if checkpoint diff expands or Docs Validation fails, CORRECTION REQUIRED same PR; otherwise objective pt-BR APPROVED before normal squash. No rollback or data migrations needed: only reversible documentation and one status field. No inferred adoption of ADR-0045.
