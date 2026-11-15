# NLE-P00-WO-002-NET-05 — Sessions & Lobby Interfaces Research Work Order

**2026-11-15 | [Research #244](https://github.com/KayzenRoot/stormline/issues/244) | future coding [#66](https://github.com/KayzenRoot/stormline/issues/66) OPEN/BLOCKED | catalog_order=48 | BASE main `cfcc290fe93d21c2cb558a0d09dd2ea51f0eadce`.** Risk P00 docs LOW, future identity/authentication and privileged issuance HIGH_ASSURANCE. No Zcode coding allowed.

## OBJECTIVE
Deep research for local-first secure lobby/session identity, create/join/leave, parties/invites/presence/discovery, matchmaking optional, independent NET-02 server allocation and game join ticket, secure provider integration, reconnect/ban/expiry/revocation, NAT/relay via NET-01, privacy/abuse and optional cloud/provider license/cost comparisons. Provide typed semantics and exactly 128 future acceptance tests plus reproducible benchmark methodology. No backend or provider permanently selected or installed.

## CONTEXT
Canonical checkpoint of NET-04 is research/checkpoint/closeout PR #241/#242/#243 merged with docs CI/pt-BR objective audits/normal squash/main readback, HEAD `cfcc290fe93d21c2cb558a0d09dd2ea51f0eadce`. **47/80 research documented, 33 pending, zero engine, 80/80 code packets blocked**. Formal catalog dependencies **NET-01 · NET-02**, both research-only. Integration boundaries NET-03/04/06, GAME-04, WORLD-01, CORE-04, DATA-04, PLAT/EDIT/CLI/MCP. Source Pack NLE-D009 engine license OPEN and per-module tech ADR unapproved.

## SCOPE
**Exactly eight new Markdown research artifacts**, in independent research PR branch `docs/NLE-P00-WO-002-NET-05-sessions-lobby`:
1. [Architecture](../architecture/net-05-sessions-lobby-interfaces.md)
2. [ADR-0051 PROPOSED](../adr/0051-net-05-local-first-session-lobby-ticket-contracts.md)
3. [Technology & license matrix](../research/net-05-session-lobby-technology-license-matrix.md)
4. [Versioned semantic contracts](../contracts/net-05-session-lobby-api.md)
5. [128 FUTURE tests](../testing/net-05-acceptance-matrix.md)
6. [Benchmark protocol](../research/net-05-session-lobby-benchmark-protocol.md)
7. This research Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-NET-05.md)

Research PR final-HEAD Docs Validation, objective pt-BR audit, normal squash/main readback. **Separate checkpoint PR** exactly checkpoint/backlog/registry/this WO/Evidence, only NET-05 research_status field change, its own exact-final-HEAD CI/audit/squash/readback. Factual closeout PR four Markdown if needed, own gates. Target after checkpoint **48/80 research documented (60%), 32 pending, 0 executable engine**, all 80 coding WOs unchanged BLOCKED, coding #66 OPEN/BLOCKED; research #244 close only after checkpoint readback. Do not start NET-06 research until final audited closeout.

## OUT OF SCOPE
No auth/session backend source code, password service, SDK, provider account/keys, public socket, game server, lobby UI engine, executable test, browser/desktop binary, third-party SDK import, platform sign-in integration, cloud deployment/Agones/Matchmaking payments, billing, real users/PII, actual IP geolocation, auto TURN credits or secret storage in repo. No library/backend/engine code license adopted; no Zcode implementation or enabling #66.

## FILES / SOURCES TO READ (Source Hierarchy)
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` / approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/NET-05.md`. Read NET-01 [architecture](../architecture/net-01-transport-connection-layer.md) and [contracts](../contracts/net-01-transport-connection-api.md), NET-02 [architecture](../architecture/net-02-authoritative-dedicated-server.md) and [contracts](../contracts/net-02-dedicated-server-api.md), NET-03 and NET-04 research contracts, NET-06 anticipated abuse requirements, GAME-04/WORLD-01/CORE-04 and DATA-04 contract ownership. Primary standards/provider official links in matrix.

## REQUIREMENTS
GOV-001..005, NLE-D013..020 and current CAP/NFR Scope/DoD. Catalog acceptance **"Criar/join/leave, reconexão e falhas previsíveis sem SaaS obrigatório."** Meaning of "without SaaS": future local self-hosted functional path with securely isolated test provider; no automatic insecure guest profile for public. No actual numerical TTL/p95/queue bandwidth/hardware/price or release class selected.

## ARCHITECTURE RULES
NET-05 controls session/lobby/party/invite/presence, tickets and matchmaking/discovery interfaces, **not** NET-01 sockets/TLS/NAT/relay, NET-02 gameplay actor/match simulation or server process authority, NET-03 snapshot field visibility, NET-04 prediction, NET-06 abuse system, GAME-04 rewards, WORLD-01 ECS, CORE-04 tick or DATA-04 durable save/schema. Clearly separate authenticated identity, lobby membership, server reservation, independent NET-02 game admit, transport ACK and GAME-04 commit. No client-chosen role/token issuer, no signing without key pin, no indefinite rejoin/role grants, no silent cloud expense; Editor/CLI/MCP profile authoring requires admin scope/CAS and does not impersonate players or mint game tokens.

## CONSTRAINTS
P00 only DOCS. No mandatory paid CI, external human reviewer, CodeRabbit, force push/history rewrite/ruleset bypass. No real account creation, provider keys, game tests, users' data, hidden IP, source/license import or invented success/benchmark. Future token auth/admin needs HIGH_ASSURANCE review, negative replay and rollback proof. Never allow HIGH/CRITICAL known defect to advance.

## ACCEPTANCE CRITERIA
- [ ] Exactly 8 **new** linked Markdown files in research PR, no code/registry/CI/SDK/dependency edits.
- [ ] ADR-0051 **PROPOSED** with self-host/local-first coordinator, separate auth/lobby/party/match admission, short-lived audience-bound ticket, reauth on reconnect, no automatic production guest, no global game authority migration.
- [ ] Typed contracts for session/party/presence/invite/lobby/matchmaking/alloc/ticket/lease/revocation/discovery/NAT relay/policy/CI/operator and all predictable failures and permission boundaries.
- [ ] Primary-source matrix compares Nakama Apache2, Colyseus MIT, Open Match Apache2, Agones Apache2, Keycloak/Hydra Apache2 and optional Steamworks/EOS/PlayFab/GameLift proprietary/service terms; RFC 9700/8725/9449 and ICE/STUN/TURN; no source/service adopted.
- [ ] Exactly **128 N05-T001..N05-T128 FUTURE/NOT EXECUTED**, future reproducible failure/security/2-user functional and 8/16/32/64 load axes. No support/latency claim.
- [ ] Exact research final HEAD Docs Validation SUCCESS (Source Pack links/DAG/registry/Zcode selector), objective pt-BR audit APPROVED documentary-only, normal squash/main readback.
- [ ] Separate checkpoint PR sole NET-05 `research_status=RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, own CI/audit/squash/main readback, expected **48/80 researched (60%), 32 pending, no runtime**.
- [ ] All **80/80** coding WOs `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED` and future coding #66 OPEN/BLOCKED; research #244 CLOSED only after checkpoint actual proof.
- [ ] Final readback closeout if used before next NET-06 research, no old PENDING text misrepresented as current.

## TESTS
Only Docs Validation GitHub at **exact final HEAD** for each PR, Source Pack local links, taxonomy/dependency DAG, registry/blocked Zcode selector plus deterministic 128 unique IDs. **NO** auth/lobby/server runtime, cryptographic test, native/Web build, NAT/relay, p95/p99 load, crash/recovery or real user tests executed. All N05 cases FUTURE/NOT EXECUTED.

## DELIVERABLES
Issue #244, eight docs, research PR actual CI/pt-BR audit/squash/readback, separate checkpoint PR sole registry status with own gates, optional 4-doc closeout/history, complete Evidence Bundle and checkpoint update, code issue #66 untouched.

## REVIEW FORMAT
Pt-BR **APPROVED / CORRECTION REQUIRED / BLOCKED**, exact Git base/head and relevant Git blob context, file diff/count, actual CI run/job/steps, privacy/auth issuer/key/abuse and license/operating costs, 128 future tests **NOT RUN**, benchmark **NOT MEASURED**, HIGH/CRITICAL, recovery/rollback, proposed vs actual Checkpoint Delta, 80 blocking status proof.

## STOP CONDITION
Canonical source STALE or policy change, license uncertainty treated as approval, auth bypass/privilege escalation, ticket replay/unencrypted secrets, NET-02 authority duplicated, SaaS mandatory/paid auto provisioning, incorrect registry diff, any code packet ready, failed CI or missing objective audit/merge, HIGH/CRITICAL security concern -> **BLOCKED/CORRECTION REQUIRED**, do not advance or implement.

## CONTEXT LOCK (Git blob object IDs at base, NOT file SHA256)
BASE main `cfcc290fe93d21c2cb558a0d09dd2ea51f0eadce`; checkpoint `8153827d4d0aabd1a1861c411e9562a2c35aeed6`; Decisions Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; Backlog `4c07df44ea57ac45b248de4bae79d9d48b97fb33`; Registry `ae74a603c7c1ca58c5dd2b1634da0bb452bcb319`; Catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; NET-05 future code WO `e65dca6b9e2a312768f59b806ba10c0707c50459`; AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`; NET-01 architecture `8d2a8713c88156fc9ead28578e4cf9ff3115d528`; NET-02 architecture `56f42dfa24a3868b3061ba177f45b4242fdcf26d`; NET-01 API `a41347d8cc0042d336598af2c5de8b533c91c428`; NET-02 API `5e3a5bca27620248bee8f1a9658a760bf728940e`; NET-03 API `686339e0dd32527a878908b093b13a5a1862f498`. Any critical canonical change => STALE, rebase/recompile. Runtime implementation lock later must verify **real source** fingerprints.

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-NET-05.md). Research/CI/merge/checkpoint all PENDING at initial authoring, do not assert auth security or engine functional.
