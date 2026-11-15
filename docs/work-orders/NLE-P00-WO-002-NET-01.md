# NLE-P00-WO-002-NET-01 — Secure Transport & Connection Layer Research Work Order

**2026-11-15 | Research [#228](https://github.com/KayzenRoot/stormline/issues/228) | future code [#62](https://github.com/KayzenRoot/stormline/issues/62) OPEN/BLOCKED | catalog_order=44 | BASE main `9bc9d04006d3a13726a21cd43992561d663586c7`.** Documentary risk LOW, future networking security ELEVATED/HIGH_ASSURANCE if privileged infrastructure/secrets, **never auto-authorized**.

## OBJECTIVE
Research modern secure UDP/game-transport, reliable/unreliable semantics, IETF QUIC v1/v2/TLS1.3/RFC9221 DATAGRAM, GameNetworkingSockets/ENet, MsQuic/quiche/ngtcp2, native vs WebTransport/WebRTC/WSS target gaps, congestion/loss/PMTU/fault modeling, timeout/connect state machine, NAT ICE/STUN/TURN, cert trust/0-RTT replay, versioning/NET security and explicit licenses/rights. Deliver objective, safe, falsifiable architecture/ADR PROPOSED/API/128 tests/benchmarks for later owner review; do not select a backend for coding.

## CONTEXT
P00 Source Pack, code runtime zero, no backend/engine/SDK, license NLE-D009 OPEN. GAME-05 research+checkpoint+readback [#225](https://github.com/KayzenRoot/stormline/pull/225) / [#226](https://github.com/KayzenRoot/stormline/pull/226) / [#227](https://github.com/KayzenRoot/stormline/pull/227) APPROVED documentary, main `9bc9d04006d3a13726a21cd43992561d663586c7`, 43 researched, 37 pending, 80/80 code packets blocked. NET-01 depends **formally CORE-01**, document PROPOSED only; NET-02..06, GAME-04, DATA/CORE/PLAT external authority constraints.

## SCOPE
Exactly **eight NEW Markdown files** research PR:
1. [architecture](../architecture/net-01-transport-connection-layer.md)
2. [ADR-0047 PROPOSED](../adr/0047-net-01-pluggable-secure-transport-capability-profiles.md)
3. [primary standards and technology/license matrix](../research/net-01-transport-technology-license-matrix.md)
4. [semantic transport/connection API](../contracts/net-01-transport-connection-api.md)
5. [128 FUTURE tests N01-T001..N01-T128](../testing/net-01-acceptance-matrix.md)
6. [reproducible NAT/impairment benchmarks](../research/net-01-transport-benchmark-protocol.md)
7. this Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-NET-01.md).

Research PR branch `docs/NLE-P00-WO-002-NET-01-transport`: exactly eight added Markdown, exact final HEAD Docs Validation, objective pt-BR audit, normal squash and main readback. Then independent checkpoint PR exactly five files (checkpoint, backlog, registry **sole NET-01 research_status**, research WO, evidence) with its own exact-final-HEAD Docs Validation, audit, squash/readback; postmerge historical closeout may use four Markdown only with own gates. Close issue #228 only after checkpoint real readback. Expected **44/80 researched (55%), 36 pending, 0 runtime; all 80 blocked.**

## OUT OF SCOPE
No engine/native socket, QUIC/UDP implementation, certificate, real game server/client, browser integration, NAT relay subscription, TURN deployment, network testing tools invoked, code tests, runtime perf numbers, third-party SDK download, license adoption, cloud spending, router modifications, scanning third-party hosts, asset change, direct script network access, core/NET-02..06 implementation, release, technology pin, automatic code packet activation.

## FILES / SOURCES TO READ (canonical priority)
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/NET-01.md`; CORE-01 platform architecture/research, NET-02..06 scope, GAME-04 typed events `docs/contracts/game-04-gameplay-event-api.md`, DATA-04 source CAS, PLAT/Web requirements, specific RFC and upstream links in matrix. Freeze base/critical blob hashes.

## REQUIREMENTS
GOV-001..005, relevant CAP/NFR and NLE-D001..NLE-D020 as in Ledger, no invented user-approved 1.0 requirements. Catalog acceptance must eventually show real latency/jitter/loss/disconnect tests. Require peer authenticated encryption, explicit backend capability and no plaintext downgrade or unsafe 0-RTT game mutation; NET-02/05/06 authority boundaries, crypto/SBOM rights and confidentiality of credentials/IP.

## ARCHITECTURE RULES
NET-01 owns only connection/message QoS/crypto-verified backend adapter and transport-level stats. CORE-01 sockets/DNS/OS abstraction, CORE-03 schedule/04 tick, NET-02 authoritative server/game validation, NET-03 replication, NET-04 prediction, NET-05 lobby/ICE/relay credentials, NET-06 abuse, GAME-04 application commit, DATA secure config and PLAT/browser capability stay sole owners. No own encryption or congestion algorithm, unsigned self-certified production peer, unbounded fragmentation/reliability queue or other module's authority. Typed semantic Editor/CLI/MCP preview/validate/stage parity under scoped capabilities and consent, **no arbitrary external network dial**.

## CONSTRAINTS
Documentation only; no paid mandatory CI, CodeRabbit, external reviewer, force push, history rewrite/bypass, service deployment or assumed free relay. Performance/identity/cert backend runtime NOT TESTED. Network security HIGH/CRITICAL issues block future release and activation; code implementation #62 stays blocked. Distinguish IETF protocol standards vs embedded code licenses/3P dependencies, and QUIC vs WebTransport vs WebRTC vs raw UDP.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight new linked Markdown docs with official primary references; no other files, registry, code or CI altered in research PR.
- [ ] ADR-0047 PROPOSED with native GNS vs QUIC native and browser WebTransport/WebRTC alternatives; reliability/delivery/capability honesty; no library/backend adopted.
- [ ] Versioned connection, identity, session, message, profile, ACK/receipt, congestion/MTU/timeout/NAT/reconnect/path/metrics and Editor/CLI/MCP authorization contracts; backend-independent without pretending equivalent semantics.
- [ ] Correct QUIC v1/v2/RFC9221/TLS/0-RTT/IPv6/PMTU, no raw UDP crypto claims; STUN not complete traversal, TURN external bandwidth, optional Web fallback doesn't fabricate datagram.
- [ ] Official audited preliminary license matrix: GNS BSD-3-Clause, ENet MIT, MsQuic MIT, quiche BSD-2-Clause, ngtcp2 MIT, libdatachannel MPL2 since 0.18 + 3P; exact pins/SBOM deferred.
- [ ] Exactly 128 unique N01-T001..N01-T128 **FUTURE/NOT EXECUTED** covering all listed classes, reproducible impairment/benchmark protocol, unselected thresholds and zero invented results.
- [ ] Research PR **exact-final-HEAD** Docs Validation all steps SUCCESS, pt-BR objective audit APPROVED only documentary, normal squash/main readback.
- [ ] Separate checkpoint PR with **only NET-01 research_status** transition (RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED), exact-final-HEAD own Docs Validation/audit/squash/main readback. Result **44/80 research, 36 pending, 0 runtime**, coding #62 OPEN/BLOCKED, research #228 close only after checkpoint readback.
- [ ] **80/80** `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, **0** executor_ready, **0** approved_adr, all release_class UNDECIDED; no code activation/next NET-02 before final readback.

## TESTS
Run P00 **Docs Validation** GitHub Actions exact final PR HEAD, verify Source Pack and local links, DAG/module taxonomy, registry invariants and blocked Zcode selector. Acknowledge ALL 128 transport/game/network acceptance tests **FUTURE/NOT EXECUTED**, no C++/Rust/SSL security/packet/latency/loss/jitter/NAT/Web/OS/export/bench tests run. No claims of security proof.

## DELIVERABLES
Research issue and eight docs, research PR CI/audit/squash/main readback, separate checkpoint PR CI/audit/squash/readback and optional historical closeout, objective pt-BR review, Evidence Bundle with actual commands/links, proposed then verified checkpoint Delta. 80 implementation queue WOs unchanged other than NET-01 research_status in checkpoint PR.

## REVIEW FORMAT
Pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED, source base/final HEAD SHA and Git blob fingerprints, actual diff list/count, CI run/job/steps and gate results, security threat/rights/version/perf gaps, 128 future tests explicitly NOT RUN, risks/known HIGH/CRITICAL, fallback/rollback and checkpoint delta with status (proposed vs observed). No coding claims.

## STOP CONDITION
BLOCKED/CORRECTION REQUIRED on stale checkpoint/source, unverified upstream or license, unauthorized net connection/asset installation, wrong registry field/unblocked packet, failing docs CI, security HIGH/CRITICAL, unsafe 0-RTT/downgrade, accidental code change or unmergeable PR. Next module only after objective readback.

## CONTEXT LOCK (BASE Git blob IDs, NOT SHA256 file hashes)
Base `9bc9d04006d3a13726a21cd43992561d663586c7`; checkpoint `51f4baa3950d98b4aee86360decd4cfb591634e5`; Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; Backlog `4bafad0636825d46d18dc0df413db0b45a815484`; Registry `975471fb82c22e6b6863d3faa980e238f9ae2d08`; catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; future coding NET-01 `db47c691f7f069c25b211ac934dcca2812bd875a`; AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`; GAME-04 API `0f5f2edc888052f401ce1c2fe85828a299f43520`. Re-read on stale / owner decision change; no assumption that this is a binary implementation context lock.

## EVIDENCE
[NET-01 evidence bundle](../evidence/NLE-P00-WO-002-NET-01.md); initial PR/CI/merge/checkpoint pending, no invented result.
