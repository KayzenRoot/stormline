# NLE-P00-WO-002-NET-02 — Authoritative Dedicated, Headless Server Research Work Order

**2026-11-15 | Research [#232](https://github.com/KayzenRoot/stormline/issues/232) | future code [#63](https://github.com/KayzenRoot/stormline/issues/63) OPEN/BLOCKED | catalog_order 45 | BASE main `ef1eb35c8b11d239801e73c112b8c936835b9cdc`.** P00 research risk LOW, future server/security/persistence risk ELEVATED, privileged admin/deployment of paid infra risk HIGH_ASSURANCE and requires explicit authorization. No Zcode coding permitted.

## OBJECTIVE
Deep research and specify a native Stormline-owned authoritative dedicated server with headless no-GPU startup, CORE-04 fixed-tick/CORE-03 scheduler, NET-01 authenticated transport ingress, WORLD-01 single ECS authority, GAME-04 typed validated player action gateway, isolation per match/session, lifecycle, shutdown, durability/rollback boundaries, server security/anti-cheat, local deployment and optional cloud orchestration. Compare Agones, Nakama, Colyseus, Open Match, GameLift, PlayFab and relevant protocol/rights, provide 128 future acceptance test specifications and reproducible benchmarks. No final backend decision or implementation.

## CONTEXT
P00 no engine, CODE/SDK, exports, demo, server binary, game tick or actual tests. NET-01 research+checkpoint+closeout [#229](https://github.com/KayzenRoot/stormline/pull/229)/[#230](https://github.com/KayzenRoot/stormline/pull/230)/[#231](https://github.com/KayzenRoot/stormline/pull/231) passed Docs Validation objective audits and normal squash/readback to `ef1eb35c8b11d239801e73c112b8c936835b9cdc`. **44/80 researches documented (55%), 36 pending, 0 runtime, 80/80 implementation work orders BLOCKED**. NET-01/WORLD-01/CORE-04 catalog dependencies only documented, not coded. GAME-04, NET-03..06 and DATA-04 remain distinct owners.

## SCOPE
Research PR **EXACTLY EIGHT NEW Markdown files**:
1. [architecture](../architecture/net-02-authoritative-dedicated-server.md)
2. [ADR-0048 PROPOSED](../adr/0048-net-02-authoritative-headless-server-tick-command-gateway.md)
3. [official technology and license matrix](../research/net-02-server-technology-license-matrix.md)
4. [typed lifecycle/game server API](../contracts/net-02-dedicated-server-api.md)
5. [128 FUTURE test cases](../testing/net-02-acceptance-matrix.md)
6. [reproducible benchmark protocol](../research/net-02-server-benchmark-protocol.md)
7. this research Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-NET-02.md)

Research branch `docs/NLE-P00-WO-002-NET-02-dedicated-server`, exact-final-HEAD Docs Validation, objective pt-BR audit, normal squash/main readback. **Separate** checkpoint PR only five scoped files (checkpoint/backlog/registry NET-02 single research_status/this WO/Evidence), own CI/audit/squash/main readback. Historical closeout PR if necessary only four Markdown, own CI/audit/squash/readback. Target after checkpoint **45/80 documented (56.25%), 35 pending, 0 engine**, all 80 code WOs blocked, future code #63 OPEN/BLOCKED; research #232 close only after actual checkpoint main readback.

## OUT OF SCOPE
No C++/Rust/Go/JS source, network server, matchmaking/cloud management, Kubernetes/Agones install, credentials, exposed ports, user login, real players, downloads, SDK/engine library, Docker image, runtime test/cert/GPU test, benchmark numbers, automatic rollback, console/platform release, release class/license final adoption, changing non-NET-02 registry fields, changing coding issue #63 or using paid services. Do not create extra backlog implementation scope or enable Zcode.

## FILES / SOURCES TO READ (canonical priority)
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/NET-02.md`; prior NET-01 [architecture](../architecture/net-01-transport-connection-layer.md), [API](../contracts/net-01-transport-connection-api.md), GAME-04 [API](../contracts/game-04-gameplay-event-api.md), WORLD-01 and CORE-04 module research from Source Pack, DATA-04/WORLD-02/NET-03..06 and EDIT/AI-01 contracts, primary official tech docs in the license matrix.

## REQUIREMENTS
GOV-001..005, relevant CAP and NFR, owner NLE-D decisions as written in Ledger; catalog acceptance: **"Servidor executa sem GPU e rejeita estado cliente arbitrário."** Formal dependencies NET-01/WORLD-01/CORE-04 must be verified at actual implementation. No user-approved concrete C++ API/ABI, 1.0 release class or accepted numeric benchmarks. Native dedicated server security must never trust client player position/health/economy/quest or signed server identity merely via UDP handshakes.

## ARCHITECTURE RULES
NET-02 owns server process/match lifecycle and admission/authority gateway, but not sockets/crypto (NET-01), world ECS writes (WORLD-01), tick/scheduler (CORE-04/03), gameplay ability/loot/quest (GAME-04), snapshots/interest (NET-03), rollback/lag compensation (NET-04), identity/matchmaking/session/relay (NET-05), abuse/DDoS (NET-06), persistent journal (DATA-04), platform or editor. No raw gameplay mutation from network callback or MCP/AI tools; no unbounded queue, no duplicated irreversible rewards, no app ACK confusion. Preserve headless local process independent of optional provider account/Kubernetes. Preview/stage/validate authoring Editor/CLI/MCP parity scoped, no arbitrary shell/deploy.

## CONSTRAINTS
P00 DOCUMENTATION ONLY, mandatory CI costs R$0, solo governance (no mandatory external reviewer/CodeRabbit), no force push/bypass, no data/asset/license imports, no invented tests, no numeric performance claims. Cloud hosting/service may cost real money; optional only, no account/provider/port created. No native code Work Order activated by ADR PROPOSED or documentary CI.

## ACCEPTANCE CRITERIA
- [ ] Exactly 8 new linked Markdown docs, official primary sources and no code/registry/CI edits in research PR.
- [ ] ADR-0048 PROPOSED strictly engine-owned headless/authoritative/no-client-trust, tick/barrier, one-process-one-match first and optional scale/deployment; explicit cross-module ownership.
- [ ] Versioned lifecycle, actor principal/world tick, validated command, queue/resource budget, snapshots/game receipts, draining/recovery, optional rewind and deployment plan semantic API, typed error taxonomy and Editor/CLI/MCP permission rules.
- [ ] Rights/licensing matrix (Agones Apache-2, Nakama Apache-2, Open Match Apache-2, Colyseus MIT, Moby/containers, optional PlayFab/GameLift service terms, Source SDK 2013 restrictive, Unity/Unreal external terms) and no foreign SDK/software/assets copied.
- [ ] 128 **N02-T001..N02-T128 FUTURE/NOT EXECUTED** unique tests, detailed GPUless/fixed tick/security/session/isolation/recovery/benchmark plan, no numeric targets or executability fabricated.
- [ ] Research PR exact-final-HEAD Docs Validation SUCCESS (Source Pack links, DAG, queue and blocked Zcode selector), objective pt-BR APPROVED documentary, normal squash/main readback.
- [ ] Separate checkpoint PR own exact-final-HEAD CI/audit/squash/main readback, **sole registry field NET-02 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED**; 45/80 researched, 35 pending, runtime zero.
- [ ] All 80 implementation packets remain `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null` and `release_class=UNDECIDED`; future code #63 OPEN/BLOCKED, research #232 close only post-checkpoint.
- [ ] Next NET-03 research only after final readback of closeout (if present), no Zcode coding permission.

## TESTS
Run actual GitHub **Docs Validation at exact final HEAD** incl local link validation, catalog/DAG, registry and Zcode blocked selector, plus deterministic static ID count 128 unique. **NO dedicated server runtime tests**, headless build, unit/integration, sanitizer/fuzz, network/load or benchmark executable now. All N02 future cases NOT EXECUTED; docs CI is not proof of game security/performance.

## DELIVERABLES
Research issue #232 and eight new Markdown, research PR CI/audit/squash/readback, checkpoint separate PR own CI/audit/squash/readback, optional verified readback closeout PR, Evidence Bundle, objective pt-BR verdicts and fresh checkpoint state, future implementation issue #63 untouched.

## REVIEW FORMAT
Pt-BR objective APPROVED / CORRECTION REQUIRED / BLOCKED, base/head SHA and source blob context lock, changed files/diff, Docs Validation actual job/run/steps, architecture/security/rights, 128 FUTURE cases NOT RUN, benchmarks not measured, HIGH/CRITICAL risks, rollback/recovery, proposed vs verified Checkpoint Delta, no fake completed claims.

## STOP CONDITION
Stale canonical checkpoint/approved ADR, incorrect license/host assumption, client-authoritative state bypass, duplicate tick/ECS or missing world isolation, importing code/SDKS/paid cloud, production shell access, failing Docs Validation, wrong registry field or unblocking code, security HIGH/CRITICAL, merge not possible => CORRECTION REQUIRED/BLOCKED and do not advance.

## CONTEXT LOCK (Git blob IDs, NOT SHA256 file contents)
BASE main `ef1eb35c8b11d239801e73c112b8c936835b9cdc`; checkpoint `8ddab25b3539a0cb59bf8ec4816368ceba014672`; Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; Backlog `2641879792e3c2bc34dde0c9e2349838b38ab4b3`; registry `610cb2feb39de4a5411f57eef670a783f9b096d1`; catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; future code packet `4c6e63ac653d5e41e57d35c5d9def9488577a856`; AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`; NET-01 architecture `8d2a8713c88156fc9ead28578e4cf9ff3115d528`; NET-01 API `a41347d8cc0042d336598af2c5de8b533c91c428`; GAME-04 API `0f5f2edc888052f401ce1c2fe85828a299f43520`. Rebase if canonical sources changed; future activation context lock requires actual SHA256 and code sources.

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-NET-02.md); initial CI/PR/merge/checkpoint pending. Do not assert runnable server or implemented mitigations.


## Research PR #233 objectively APPROVED/MERGED and proposed separate checkpoint
- [Research PR #233](https://github.com/KayzenRoot/stormline/pull/233), BASE `ef1eb35c8b11d239801e73c112b8c936835b9cdc`, audited final HEAD `e810c0063ae209e475285fdd58668bbcb3e45435`, eight NEW Markdown docs (531 additions, zero deletions), [Docs Validation #43712085692](https://github.com/KayzenRoot/stormline/actions/runs/43712085692) **SUCCESS** job #132805649089 incl Source Pack/local links, DAG, registry and blocked Zcode selector; objective [pt-BR audit #6894059027](https://github.com/KayzenRoot/stormline/pull/233#issuecomment-6894059027) **APPROVED documentary-only**. Normal squash main `f0eb9cf8d02c7ce2d5e8a83314e638eb4bc457a0`, main/PR/contract readback confirmed. Exactly 128 unique N02-T001..N02-T128 FUTURE/NOT EXECUTED, no server runtime.
- This separate checkpoint PR BASE `f0eb9cf8d02c7ce2d5e8a83314e638eb4bc457a0` changes exactly 5 files checkpoint/backlog/registry/this research WO/Evidence; registry **sole NET-02 research_status** transition. Expected 45/80 researched (56.25%), 35 pending, 0 executable engine, all 80/80 code packets BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class=UNDECIDED. Future code #63 remains OPEN/BLOCKED, ADR-0048 PROPOSED. Independent checkpoint exact HEAD Docs Validation, audit, squash/main readback PENDING at this writing. No source or SDK imported, no GameLift/PlayFab billing/Agones deployed.


## NET-02 checkpoint #234 actual merge/readback verified (historical closeout)
- Research [PR #233](https://github.com/KayzenRoot/stormline/pull/233) final audited HEAD `e810c0063ae209e475285fdd58668bbcb3e45435`, [Docs Validation #43712085692](https://github.com/KayzenRoot/stormline/actions/runs/43712085692) SUCCESS job #132805649089 and pt-BR audit #6894059027 APPROVED documentary-only, normal squash/readback research main `f0eb9cf8d02c7ce2d5e8a83314e638eb4bc457a0`.
- Independent checkpoint [PR #234](https://github.com/KayzenRoot/stormline/pull/234) final HEAD `1fb87a888aff0f9d29e73b8d05c1657bc1f303af`, [Docs Validation #43712307674](https://github.com/KayzenRoot/stormline/actions/runs/43712307674) **SUCCESS** job #132806329013, [pt-BR objective audit #6894088168](https://github.com/KayzenRoot/stormline/pull/234#issuecomment-6894088168) **APPROVED documentary-only**; normal squash main `56bcf317f5d5cc24a286f99a9f9bd1faf6e78cd6` and [actual readback #6894095820](https://github.com/KayzenRoot/stormline/pull/234#issuecomment-6894095820) verified PR/main/registry; research #232 CLOSED after proof, future coding #63 OPEN/BLOCKED.
- Real registry **45/80 researched (56.25%), 35 pending, zero runtime, 80/80 code packets blocked**, zero executor_ready, zero approved_adr, all release_class UNDECIDED; only NET-02 research_status changed. ADR-0048 PROPOSED, engine license OPEN, 128 N02-T001..T128 FUTURE/NOT EXECUTED. No GPUless headless server, gameplay simulation or attack tests, container, SDK or cloud. This readback-closeout PR changes only 4 Markdown, registry/code/CI untouched, requires own exact-HEAD Docs Validation, objective audit, squash and final main readback. Earlier PENDING statements describe state when written, superseded by this verified historical evidence.
