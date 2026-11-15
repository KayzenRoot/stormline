# NLE-P00-WO-002-NET-04 — Prediction, Reconciliation & Lag Research Work Order

**2026-11-15 | Research [#240](https://github.com/KayzenRoot/stormline/issues/240) | future coding [#65](https://github.com/KayzenRoot/stormline/issues/65) OPEN/BLOCKED | catalog order 47 | BASE main `6701b8f6e99654112a6bf792c8b33d565ad71b42`.** P00 documentary risk LOW, future networking/game fairness/security ELEVATED; privileged hit history/irreversible or financial game rewards HIGH_ASSURANCE if applicable. No Zcode executor coding authorized.

## OBJECTIVE
Deep research and specify bounded owner client-side prediction, canonical SIM-03 motor replay, NET-03 authoritative snapshot+input cursor correction, CORE-04 TickId and clock estimates, remote interpolation/extrapolation and jitter buffer, optional read-only server hit rewind, attack/fairness bounds, predicted spawn/partial-snapshot collision hazards, protected GAME-04 irreversible effects, formal typed contracts, technologies/rights, reproducible performance protocol and exactly 128 FUTURE acceptance cases. No definitive backend, rate, codec, performance budget or license choice.

## CONTEXT
P00 no game engine/binary/client/server, no native/Web packet tests, no prediction or fairness measurements. NET-03 research/checkpoint/readback [PR #237](https://github.com/KayzenRoot/stormline/pull/237)/[#238](https://github.com/KayzenRoot/stormline/pull/238)/[#239](https://github.com/KayzenRoot/stormline/pull/239) CI, audit, squash/readback final main `6701b8f6e99654112a6bf792c8b33d565ad71b42`. Current **46/80 researched (57.5%), 34 pending, zero runtime, 80/80 coding packets blocked**. Formal dependencies **NET-03, SIM-03** researched/PROPOSED only; NET-01,02,05,06, GAME-04, CORE-04, WORLD-01 and DATA-04 own separate functions.

## SCOPE
Research PR **EXACTLY EIGHT NEW Markdown**:
1. [architecture](../architecture/net-04-prediction-reconciliation-lag.md)
2. [ADR-0050 PROPOSED](../adr/0050-net-04-bounded-client-prediction-authoritative-reconciliation.md)
3. [official technology/license matrix](../research/net-04-prediction-technology-license-matrix.md)
4. [typed semantic API](../contracts/net-04-prediction-reconciliation-api.md)
5. [128 future N04 tests](../testing/net-04-acceptance-matrix.md)
6. [reproducible benchmark/fairness protocol](../research/net-04-prediction-benchmark-protocol.md)
7. this research Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-NET-04.md)

Research PR branch `docs/NLE-P00-WO-002-NET-04-prediction-lag`, own exact-final-HEAD Docs Validation, objective pt-BR audit, normal squash/main readback. AFTER research closure create **separate checkpoint PR** only five files checkpoint/backlog/registry sole NET-04 research_status/this WO/Evidence, own exact HEAD CI/audit/squash/main readback. Historical 4-file closeout PR when required, own gates. Expected **47/80 researched (58.75%), 33 pending, 0 runtime**; all **80** code packets stay BLOCKED. Research #240 closed only after checkpoint objective readback; code #65 OPEN/BLOCKED. Do not begin NET-05 until completed final closeout.

## OUT OF SCOPE
No engine/source C++/Rust, SIM-03 motor code, multiplayer server/client/physics, native WebTransport/RTC backend, proprietary UE/Unity/Valve code/asset import, telemetry capture, real hit validation, security/anti-cheat agent, durable replay/saving, arbitrary rollback of game economy, native/browser builds, real loss/jitter benchmark, CI logic update, enabling Zcode, licensing/SDK adoption, billable cloud service, player data.

## FILES / SOURCES TO READ (canonical priority)
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` / approved ADR > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/NET-04.md`; NET-03 [API](../contracts/net-03-replication-interest-api.md), NET-02 [API](../contracts/net-02-dedicated-server-api.md), NET-01 [API](../contracts/net-01-transport-connection-api.md), GAME-04 prior contracts, SIM-03 and CORE-04 research/architecture, NET-05/06 and DATA-04 ownership. Primary official links inside license matrix. Freeze base + critical Git blob fingerprints, mark STALE on approved source change.

## REQUIREMENTS
GOV-001..005 and relevant CAP/NFR/NLE-D from Ledger; catalog acceptance **"Replay de entrada gera estados toleráveis e métricas de correção."** Measurable tolerances/game profiles/time/CPU budgets not decided or owner-approved. Server NET-02 is only authority. Client supplies input intent, never world position/hit results, crypto or server TickId.

## ARCHITECTURE RULES
NET-04 owns **only** disposable client prediction and replay ring, reconciliation to authorized NET-03 snapshots and restricted read-only server historical hit query policy if game-mode approved. NET-01 connection/cwnd/time samples; NET-02 match actor authority/command admission; NET-03 snapshots/baseline/permission; NET-05 session; NET-06 security/abuse; SIM-03 motor; CORE-04 server clock/ticks; WORLD-01 ECS; GAME-04 gameplay/economy; DATA-04 durable source/save. No new ECS/physics/clock/serialization/hit judge. Client prediction replay never commits GAME-04 events, smoothing never changes gameplay, old epochs invalidated; optional server rewind read-only collider history and server clamped time/LOS with irreversible effects excluded. Editor/CLI/MCP only scoped profile inspect/preview/stage/validate/commit CAS, not live admin rewind.

## CONSTRAINTS
Documentation only, 0 mandatory paid CI/cloud/external reviewer/CodeRabbit; no force push/history rewrite/bypass. No invented runtime tests, hardware tail latency, 1.0 release class or supported client count. Exact source rights not adopted. Security/fairness HIGH/CRITICAL flaws block future executor. Preserve all 80 blocking status fields throughout.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight new linked Markdown in research PR, no code/registry/CI/dependency changes and verified 128 unique test IDs.
- [ ] ADR-0050 PROPOSED: bounded owner prediction, remote interpolation, server authority, uncertain time-sync, replay caps and optional **read-only** server hit history with fairness/NET-06 controls, no global economy rollback.
- [ ] Versioned contracts for time/tick estimation, input history/sequence/processed cursor, partial snapshot cohort, predicted-spawn identity, server correction/visual smoothing, replay side-effect dedup, remote interpolation/jitter buffer, optional hit history, typed error and Editor/CLI/MCP authorization.
- [ ] Research matrix includes Unity Netcode terms, Unreal EULA, Valve Source SDK restricted non-MIT, Godot MIT, Gaffer articles not code library, optional test harness licenses/pins, no imported code/assets or release class adoption.
- [ ] Exactly N04-T001..N04-T128 **FUTURE/NOT EXECUTED**, future metrics CPU/visual correction/error/lag fairness/latency loss/partial-physics, repeatable benchmark protocol; no performance/retention target asserted without owner baseline.
- [ ] Research PR own exact-final-HEAD Docs Validation success (links, DAG, registry/Zcode blocked selector), pt-BR audit APPROVED only documentary, normal squash and main/contract readback.
- [ ] Separate checkpoint PR own final-HEAD CI/audit/squash/main readback with only NET-04 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`; final 47/80 research (58.75%), 33 pending, 0 engine.
- [ ] All 80 WOs `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`; future code #65 OPEN/BLOCKED, research #240 closed only after checkpoint readback; no coding permission.
- [ ] Final checkpoint and optional closeout PR readback before next NET-05 documentary research, no previous pending statements misrepresented as final.

## TESTS
Only real GitHub Docs Validation exact final HEAD for research/checkpoint/closeout + static check of exactly 128 IDs, Source Pack/local links/DAG/registry, blocked Zcode selector. **No runtime engine, headless/game/client, unit/integration/fuzz/security, native/Web cross-platform, loss/jitter time sync, p95/p99 CPU, player fairness or hit tests run**. 128 tests all FUTURE/NOT EXECUTED.

## DELIVERABLES
Research issue #240, eight docs, research PR evidence, Docs Validation CI/audit/squash/main readback, separate checkpoint own gates and sole registry semantic change, historical closeout if needed, pt-BR objective review and Evidence Bundle, proposed and then verified Checkpoint Delta. Do not alter coding issue #65.

## REVIEW FORMAT
Pt-BR `APPROVED / CORRECTION REQUIRED / BLOCKED`, exact base/HEAD/blobs, changed file list/diff, actual CI run/job/step results, license/security/fairness/CPU and rollback risk, 128 FUTURE tests NOT EXECUTED, no bench measurements, HIGH/CRITICAL, evidence+proposed/observed checkpoint and graceful rollback. Failure needs Correction Delta within same PR/WO.

## STOP CONDITION
Source lock STALE/approved ADR changed, client trust escalation, cross-module double physics/time/authority, unbounded replay, speculative irreversible effects or unsafe server rewind, illegal source/assets, paid service or unapproved code, CI fail, HIGH/CRITICAL known flaw, wrong registry field, any code executor_ready or forbidden bypass => BLOCKED/CORRECTION REQUIRED, no next module.

## CONTEXT LOCK (Git blob identifiers, NOT source SHA256)
BASE main `6701b8f6e99654112a6bf792c8b33d565ad71b42`; checkpoint `8b54d45112e89c39a03d54ca7ecc471569d7b37c`; Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; Backlog `676b44109268212cb762baca41914f130b0ad0f5`; registry `d25317a7d63a5f5f088095b6135565913fa3cc8e`; catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; future code packet `f41ee68588499cee75c86584b6cd819a1286fef8`; AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`; NET-03 contract `686339e0dd32527a878908b093b13a5a1862f498`; NET-02 contract `5e3a5bca27620248bee8f1a9658a760bf728940e`; NET-01 contract `a41347d8cc0042d336598af2c5de8b533c91c428`. Rebase if any critical approved source changes. Implementation context lock with code hashes only at future activation.

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-NET-04.md); PR/CI/checkpoint pending at drafting; no runtime or code security proof.


## Observed research PR #241 and separate checkpoint proposal
- [Research PR #241](https://github.com/KayzenRoot/stormline/pull/241), BASE `6701b8f6e99654112a6bf792c8b33d565ad71b42`, audited final HEAD `7ae14978fb71dcf6809b608f493276be214655fb`, exactly eight NEW Markdown (506 adds, 0 deletes), [Docs Validation #43715830922](https://github.com/KayzenRoot/stormline/actions/runs/43715830922) **SUCCESS** job #132817045630 all Source Pack/local links/DAG/registry/Zcode blocked selector SUCCESS, [pt-BR objective audit #6894577101](https://github.com/KayzenRoot/stormline/pull/241#issuecomment-6894577101) **APPROVED documentary-only**, normal squash main `2cc7228cffe56d2e73d26e9af78ed998127a1366` and main/PR/contract readback. 128 N04-T001..128 unique specified **FUTURE/NOT EXECUTED**; no runtime/build/security/fairness/bench proof.
- This independent checkpoint PR base `2cc7228cffe56d2e73d26e9af78ed998127a1366` changes exactly five files checkpoint/backlog/registry/research WO/Evidence and **only NET-04 research_status** field. Proposed **47/80 researched (58.75%), 33 pending, zero executable engine**, all 80 coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class UNDECIDED. Coding #65 OPEN/BLOCKED, research #240 OPEN until checkpoint readback, ADR-0050 PROPOSED, NLE-D009 OPEN. Own exact-final-HEAD Docs Validation/audit/squash/main readback PENDING at writing. No code/library/cloud adoption.


## NET-04 checkpoint #242 actual merge/CI and factual main readback (historical closeout)
- [Research PR #241](https://github.com/KayzenRoot/stormline/pull/241) final audited HEAD `7ae14978fb71dcf6809b608f493276be214655fb`, [Docs Validation #43715830922](https://github.com/KayzenRoot/stormline/actions/runs/43715830922) SUCCESS job #132817045630, [pt-BR audit #6894577101](https://github.com/KayzenRoot/stormline/pull/241#issuecomment-6894577101) APPROVED documentary-only, normal squash/readback research main `2cc7228cffe56d2e73d26e9af78ed998127a1366`.
- Independent checkpoint [PR #242](https://github.com/KayzenRoot/stormline/pull/242) exact final HEAD `527da17c76d83dc926dfda767f48b5bebbe9ea23`, [Docs Validation #43716030443](https://github.com/KayzenRoot/stormline/actions/runs/43716030443) **SUCCESS** job #132817643060 (Source Pack local links, DAG, registry, blocked Zcode selector), [objective pt-BR audit #6894603128](https://github.com/KayzenRoot/stormline/pull/242#issuecomment-6894603128) APPROVED documentary-only, normal squash main `b26853ed5d61237cfb99a0dca7f5028cc1fc82cc`; [factual readback #6894609864](https://github.com/KayzenRoot/stormline/pull/242#issuecomment-6894609864) verified main/PR/registry and coding issue #65 OPEN/BLOCKED; research issue #240 CLOSED after readback.
- Actual main registry **47/80 research documented (58.75%), 33 pending, 0 engine**, all **80/80** code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, zero executor_ready, zero approved_adr, release_class UNDECIDED. ADR-0050 PROPOSED, NLE-D009 OPEN; 128 N04 tests FUTURE/NOT EXECUTED, no runtime replay/server/anti-cheat/fairness benchmark. This historical closeout changes only 4 Markdown and NO registry/source/CI/dependency/SDK, and requires own final-HEAD CI, objective pt-BR audit, ordinary squash and main readback. Earlier PENDING statements reflect creation-time status, superseded by this observed evidence.
