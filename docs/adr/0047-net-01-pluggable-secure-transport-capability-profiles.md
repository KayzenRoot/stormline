# ADR-0047 — Pluggable authenticated transport with truthful capability profiles

**Status: PROPOSED / NOT OWNER-APPROVED / NOT ADOPTED** | 2026-11-15 | NET-01 research #228 | WO `NLE-P00-WO-002-NET-01` | future coding #62 OPEN/BLOCKED.

## Context
Stormline native 2D/3D/Web games require low latency and secure communication, but no single backend provides guaranteed native/desktop/browser/P2P/reliable/unreliable/partial reliability, NAT traversal, zero-cost relay, crossplay or DDoS resistance. Catalog NET-01 scope is reliable/unreliable, congestion, timeouts, discovery, encryption; acceptance needs **real latency/jitter/loss/disconnect tests**. Formal dependency CORE-01 is documentary only, and NET-02..06 have not been researched/implemented yet. Adopted UDP alone is not secure. IETF QUIC v1 (RFC9000) supplies TLS secured streams; RFC9221 adds optional unreliable datagrams, subject to congestion control and negotiated size. Native GameNetworkingSockets offers message orientation/reliable+unreliable and packet encryption, while Web APIs differ.

## Proposed decision (not a backend choice)
Create Stormline-owned, versioned **`TransportConnectionV1`** and **`TransportDeliveryProfileV1`** abstractions, with **backend capabilities explicitly negotiated and failed closed**. NET-01 is an adapter boundary over CORE-01 and platform/browser network API, not an invention of a new cryptographic or congestion protocol. Prioritize authenticated encryption on all remote connections, bounded channel queues with expiry/priority/backpressure, strict connection generation and identity/rebind controls, honest reliable/unreliable/ordered handling, normalized metrics and state machine. Prototype and benchmark at least two independent native families (game-oriented GNS candidate; standards-based QUIC candidate) before any mandatory runtime adoption; browser must be separately tested against WebTransport/WebRTC and actual secure context, with WebSocket only as declared reliable ordered fallback.

- **Reliable streams vs datagrams are semantically distinct**; QUIC datagram ACK is not gameplay commit, can expire under congestion and cannot be fragmented. No guarantee of reliable *unordered* message on a backend lacking it; per-stream independent ordering does not equal globally unordered guarantees.
- **Authenticated connection ≠ authorized gameplay session**. NET-02/05/06 own principal, session, abuse; GAME-04 owns game receipts. No in-game state change on QUIC 0-RTT. No automatic plaintext fallback, disabled certificate verification, internal raw UDP in browser or unauthorized arbitrary dial from MCP.
- **ICE/STUN/TURN capability optional**; STUN alone not traversal, TURN consumes infra. NET-05 discovers/provisions credentials; NET-01 reports path telemetry and candidate health. Privacy/SSRF protections and one authoritative connection epoch remain.
- **Bounded packet/queue/per-peer budget** with loss/congestion-aware pacing; least stale snapshots dropped before control; no unbounded reliable backlog. Reconnect uses backoff/jitter and explicit server session/epoch revalidation.
- **No version, numeric perf threshold, source license, crypto provider, binary ABI, selected library or protocol wire format approved by this decision draft**. The transport policy and API must remain testable with a virtual clock/network emulator without OS network hardware.

## Alternatives evaluated
| Alternative | Pros | Reject/defer conditions |
|---|---|---|
| Raw UDP + original reliability + encryption design | maximal flexibility | **reject** baseline: cryptography, congestion and fragmentation are security/correctness work, enormous attack surface |
| TCP/TLS + WebSocket only | ubiquitous, simple, encrypted reliable stream | not genuine unreliable/latest-only data, head-of-line blocking under loss; optional degraded reliable-only role, not gaming capability equivalent |
| Native **GameNetworkingSockets** everywhere | game messaging, channel priorities, encryption | browser/WebAssembly host and platform support not guaranteed; ICE/relay/service identities require review; candidate native lane only |
| Native **ENet** everywhere | tiny MIT C reliable UDP | encryption/auth/trust not supplied as full secure transport; require separate backend crypto approval, cannot silently adopt |
| QUIC **MsQuic/quiche/ngtcp2** everywhere | IETF TLS security, streams plus optional RFC9221 DATAGRAM, congestion | DATAGRAM implementation/target support must be tested, Web browser cannot just reuse native socket, Rust FFI/crypto and TLS backend overhead/rights |
| WebRTC DataChannel for all | P2P ICE/DTLS, reliable/partial reliability and browser support | signaling/relay costs, SCTP transport behavior, native library build/licensing, not fastest universal path |
| WebTransport only | browser HTTP/3 streams+datagrams with TLS | browser HTTPS/servers/policy, standards rollout, NAT P2P not provided, older browser fallback |
| **Pluggable transport, strict capability matrix** | portable policy, honest metrics, decoupled vendor choices | complexity/ABI/feature discovery; **leading proposal** requiring measured proof and limited starting slice |

## Consequences and objective decision gates
Pro: vendor portability, safe typed gameplay transport API, low coupling to engine, testable explicit fallback, meaningful native/Web split. Cost: multiple adapters, different QoS/MTU/metrics, SDK/crypto dependency review, capability UX, migration/reconnect testing and later operational relay costs. Blind abstraction across irreconcilable reliability semantics is forbidden.

**Before APPROVED** choose one secure native backend with exact pin/license/SBOM/security backlog, one Web path with real browser tests or explicit unsupported label, accepted identity/ALPN/trust/cert and 0-RTT default OFF, anti-DoS/retry, throughput/loss/RTT targets under reproducible harness, available license/rights/privacy/target versions, rollback/fallback policy, owner Scope/DoD + release class, proof of CORE-01 integration. Security HIGH/CRITICAL or licensing conflict -> BLOCKED. All 80 code packets remain blocked regardless of documentary merge.
