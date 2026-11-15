# NET-01 — Secure Transport & Connection Layer Architecture v0.1

**NLE-P00-WO-002-NET-01 | research issue #228 | implementation [#62](https://github.com/KayzenRoot/stormline/issues/62) OPEN/BLOCKED | baseline `9bc9d04006d3a13726a21cd43992561d663586c7` | 2026-11-15 | P00 PROPOSED / DOCUMENTATION ONLY.** No UDP socket, packet, cert, QUIC runtime, WebTransport backend, NAT service, connection, encrypted payload, export, game server, real security test or benchmark exists. License NLE-D009 OPEN, production backend **UNSELECTED**.

## 1. Mission, catalog acceptance and nonclaims
Catalog scope: **"Reliable/unreliable, congestion, timeouts, discovery, encryption conforme threat model."** Catalog acceptance: **"Testes com latência, jitter, perda e desconexão."** NET-01 provides a single semantic reliable/unreliable **message and connection** interface across authorized native/client/server/browser capabilities, not a replication subsystem or networked game. Decisions on transport profiles, wire formats and libraries remain **PROPOSED**, subject to future security review and real measurements. UDP is neither encryption nor reliability, QUIC datagrams are not assured delivery, TCP/WebSocket reliable ordered streams may produce head-of-line latency, and QUIC v2 is a wire version/anti-ossification update rather than a faster-than-v1 benchmark promise ([RFC 9369](https://www.rfc-editor.org/rfc/rfc9369.html)).

### Basic architecture proposal
```text
GAME-04 authenticated commands     NET-02 server validation   NET-03 snapshots   NET-05 session/lobby
                        ^                  ^                     ^
                 versioned NET-01 semantic message/connection envelope
                          + policy: reliability / ordering / expiry / priority
                          + Connect, Accept, Close, ReconnectIntent, Stats
                       adapter capability resolver, no silent security downgrade
             +---------------------+-----------------------+----------------------+
         NATIVE game transport  native QUIC stream+RFC9221     BROWSER WebTransport/
         e.g. GNS (candidate)   DATAGRAM (candidate)          WebRTC candidate
             +---------------------+-----------------------+----------------------+
         CORE-01 owned socket, timer, DNS, OS event loop + PLAT target capability
             TLS/QUIC/DTLS or approved native authenticated crypto; no homegrown cipher
```

**Critical separation:** net transport can authenticate a peer/handshake identity or session binding; it does not authenticate *in-game* authority, owns no hit/loot permission, and does not replace anti-cheat (NET-06), server simulation (NET-02), replication delta (NET-03), prediction/rollback (NET-04), matchmaking/lobby (NET-05), or DATA save/persistence.

## 2. Source-of-truth ownership
| Subsystem | Owns / supplies to NET-01 | NET-01 forbidden to own |
|---|---|---|
| **CORE-01** sole platform abstraction | socket/UDP/TCP/BSD/Winsock/browser I/O boundary, DNS resolver interface, monotonic timers, event pump integration; no direct platform API leakage above boundary | parallel portability shim, direct privileges beyond adopted CORE-01 |
| **CORE-03/04/06** | scheduler, fixed TickId for gameplay context, monotonic latency clock/telemetry and trace ownership | transport handlers directly mutate ECS; wallclock-derived gameplay TickId; ad-hoc global logger |
| **NET-01** | typed connection state machine, secure backend capability and transport policies, bounded queues, packet/send receipts, connection-level reachability/metrics, migration/rebind probes | replication, authoritative game command, simulation/world save, gameplay ACK, identity provisioning, store/relay infrastructure |
| **NET-02** | authenticated authoritative server accepts gameplay commands and validates/expels; server session principal | client NAT handshake mistaken for game authority |
| **NET-03/04** | replication stream selection, snapshot/delta, interest, rollback/prediction and tick validation | entity delta serialization/rollback inside NET-01 |
| **NET-05** | service discovery/session and lobby identity, invitation tokens, relay provisioning/credentials | binding lobby matchmaking to one transport vendor; assuming STUN creates session |
| **NET-06** | abuse control, anti-replay and security posture, quotas and protocol fuzzing | calling TLS encryption enough to prevent cheating/DoS |
| **GAME-04** | game command events/receipts, durable/authoritative state through NET-02 | transport packet acceptance = gameplay command commit |
| **DATA-02/04** | signed/versioned session config/trust anchors/approved asset metadata and durable revision as applicable | storing credential files or gameplay progression by socket callback |
| **PLAT/EDIT/CLI/MCP/AI-01** | export capabilities/browser permission, validated transport preview/config lifecycle, role-scoped authoring actions | network dial to arbitrary URL from MCP/tool by default; raw socket access in scripts |
| **WORLD/SIM/GAME-02** | ECS/physics/sandboxed script-generated intents | permit untrusted scripts to open arbitrary ports, connect to LAN or forge server identity |

**Formal catalog predecessor only CORE-01**; all other NET/GAME/CORE/DATA/PLAT integrations are dependencies of operational interfaces without falsely rewriting catalog DAG. CORE-01 is documented/PROPOSED, not implemented. No socket project is ready.

## 3. Delivery semantic profiles and order
| Profile (proposed) | Transport guarantee vs application semantics | Appropriate content |
|---|---|---|
| `UNRELIABLE_LATEST` | authenticated encrypted best-effort datagram, independently droppable, no automatic retransmission or reassembly and no guaranteed delivery; sequence/epoch indicates supersession | high-frequency snapshots/input hints, transient cosmetics |
| `RELIABLE_ORDERED` | reliable byte stream or bounded reliable-message channel; order scoped to **channel/stream**, not all gameplay; transport acknowledgment ≠ gameplay commit | initial handshake/config, validated inventory/quest control envelope |
| `RELIABLE_INDEPENDENT` | independent streams or equivalent reliable message lanes, with cross-channel order **undefined**; not a universal unordered-message guarantee | loading assets/config messages independent of gameplay state |
| `BOUNDED_EXPIRING` | candidate on selected backends with explicit deadline/retransmission limits; unsupported backend returns CAPABILITY_UNAVAILABLE, **not** pretend partial-reliable | time-sensitive one-shot updates with expiration |
| `CONTROL_CRITICAL` | authenticated reliable channel high priority, bounded messages/backpressure, never infinite queue | close, consent, ticket update, authoritative control |

All profiles require semantic receipts: `QUEUED, SENT_TO_BACKEND, DROPPED_EXPIRED, DROPPED_CONGESTION, REJECTED, PEER_TRANSPORT_ACKED, APP_ACCEPTED` (only NET-02/GAME-04 may produce application acceptance). For QUIC, DATAGRAM RFC9221 is unreliable, congestion-controlled, does not provide explicit receiver flow control or fragmentation; negotiated limits and path MTU bound payload. Implement sender-side expiration/drop instead of stale retransmit. Reliable QUIC streams have per-stream ordering and may still create application-level congestion; backpressure and prioritization must be explicit. For GNS channels, verify lane ordering/semantics against exact pinned SDK source at adoption, not assume QUIC wire compatibility.

## 4. Connection FSM, reconnect, migration and liveness
`IDLE -> RESOLVING -> PROBING -> HANDSHAKING -> AUTHENTICATING -> ACTIVE -> SUSPECT -> (MIGRATING / RECONNECTING / DRAINING) -> CLOSED` with explicit `FAILED/DEADLINE/SECURITY_REJECTED` transitions. Endpoint names and conditions are illustrative; exact machine requires implementation. Every connection has `ConnectionIdV1` plus generation/epoch to discard stale callbacks and obsolete candidate paths. Establishment phases have separate monotonic deadlines, bounded DNS/ICE parallel fanout, scoped exponential backoff + full jitter and retry budget. No infinite retries, reconnect storms or silently reopening auth-banned sessions.

- A **connection** is transport reachability and crypto identity, not a durable authorized game session. NET-05 ticket + NET-02 principal/epoch must re-validate on reconnect; allow application replay of idempotent safe messages only with GAME-04/NET-02 receipts; do **not** blindly replay queued damage, loot, financial or irreversible operations.
- **NAT rebinding vs reconnect** differs: QUIC connection IDs and path validation may permit path migration/rebind (RFC9000), not promised on every proxy/router; native GNS has separate ICE/relay capabilities. A peer address change alone is not authenticated identity. Validate path, rotate/reset path congestion state per backend protocol, avoid hijack.
- Timeout configurable policy separates handshake deadline, idle timeout, silent vs suspect vs lost heartbeat. Heartbeats are authenticated low-rate and may be intentionally disabled under traffic; application-level liveness requires own semantics. Close flush bounded control messages and zeroize key/session material via backend, not raw print.
- **Service discovery** belongs NET-05, though NET-01 exposes limited local endpoint resolution and candidate diagnostics with user permissions. LAN broadcast/mDNS are opt-in/privacy-sensitive. No free relay service or public matchmaking is assumed.
- **NAT:** ICE (RFC8445) candidate gathering/checks uses STUN (RFC8489), which alone is **not** a NAT traversal solution, and TURN (RFC8656) relay requires provisioned infrastructure/bandwidth/credentials, often nonzero cost. Candidate path fallback direct -> consented relay -> typed failure; prevent IP/candidate leaks in untrusted scripts/MCP/telemetry. QUIC client/server direct/connection migration must **not** be conflated with automatic P2P ICE/TURN.
- **IPv4/IPv6:** dual-stack/Happy Eyeballs-style controlled races only with deduplicated connection generation and no credential leak; DNS rebinding and address class filters for tool-origin connections. No silent fallback from encrypted/authenticated channel to plaintext TCP/UDP.

## 5. Cryptography and trust threat model
- Native QUIC adapters **must** use validated vendor TLS 1.3 QUIC integration (RFC9001, RFC8446) including peer identity/trust anchors, ALPN/hostname as applicable, key updates/rotation and secure RNG. DTLS 1.3 (RFC9147) over UDP and WebRTC DTLS/SCTP ICE are distinct candidates requiring verification of library and threat model.
- GNS crypto as documented uses AES-GCM-256/Curve25519 for packet security, but identity binding, certificates/trust roots, anonymous mode, application tokens and MITM risk must be reviewed; **encryption without authenticated identity is insufficient**. No homegrown cryptographic algorithms, no disable-verify/silent self-signed in production.
- **0-RTT early game state write FORBIDDEN in the baseline** (damage, loot, join/leave, inventory, purchases, admin actions). RFC9001 states 0-RTT application data can be replayed; if future safe idempotent discovery requests allowed, require separate 0-RTT ADR, server anti-replay and exact allowlist. No permanent disable of protocol's handshake protections.
- Anti-amplification before address validation (QUIC RFC9000), rate limiting, cookie/retry and aggregate per-prefix/AS controls owned with NET-06. Treat input bytes as untrusted, lengths/endian/varint/version/epoch verified before allocation; reject decompression bombs, reassembly storms, slow/idle sessions, fragment spam, invalid certificates or revoked tickets.
- Opaque identifiers, redacted metrics, sensitive IP treatment and credential rotation; no plaintext secrets, session token leaks, PII logging or unsafe packet capture by default. DDoS/BGP/failure at provider cannot be solved entirely by engine API.
- Untrusted Editor/CLI/MCP requests require explicit allowlisted endpoint/port/host, principal/capability, consent, no local metadata/private address SSRF and no arbitrary network egress.

## 6. Congestion/pacing/PMTU and QoS
- Never ignore network congestion. The backend implementing QUIC must honor RFC9002 congestion/loss detection and pacing; native candidates must publish comparable congestion/window/rate/queue/backpressure stats without claiming same algorithms. API `priority` is request only; not a route to starve lower-priority control or bypass anti-DoS.
- Per-connection and per-channel packet/byte/time budgets, max in-flight and queue depth; bounded producer behavior (drop stale latest-state first, then deny admission). A blocked reliable stream cannot grow indefinitely; starvation and priority inversion must be tested.
- PMTUD / DPLPMTUD candidate RFC8899, initial conservative payload and tested path adaptation, IPv6 1280 MTU and QUIC min UDP datagram 1200 considerations; do not set user payload = 1200 without subtracting IP/UDP/QUIC encryption/other headers. Reassembly per peer/timeout bounded; fragmented messages only through adopted backend features, not untrusted giant allocs. NAT/relay path can reduce MTU; black-hole detection and safe fallback.
- Latency policy: distinguish network RTT (smoothed/variance/tail), arrival jitter, transit delay and application queue wait. No magic smoothing using game ticks as network timer; CORE-01 monotonic clock for transport, CORE-04 TickId only game event context. NTP/clock skew means one-way timing needs synchronized capture; otherwise measure RTT/loopback.
- Adaptive rate and feedback belong transport; NET-03 interest/snapshot size, NET-04 prediction, NET-02 tick rate and game protocol framing are *outside* NET-01. Compression/replication data policy not implemented here.

## 7. Backend candidates and capability honesty
1. **Native message transport lane:** Valve GameNetworkingSockets (BSD-3-Clause) candidate for independent reliable/unreliable game messages, encryption and ICE integration in appropriate builds; **no assumption free Steam matchmaking/relay or Web binary compatibility**. ENet MIT is lighter but requires distinct authenticated encryption/trust solution and feature-by-feature tests, cannot be declared secure as-is.
2. **IETF QUIC lane:** MsQuic MIT (native C), quiche BSD-2-Clause (Rust with FFI), ngtcp2 MIT (C with chosen TLS adapter) for secure streams + RFC9221 DATAGRAM if target implementation supports it. **QUIC v2 RFC9369** may be tested but is not inherently lower latency or universally enabled. Explicit flow/congestion/MTU/0-RTT gates.
3. **Browser lane:** WebTransport (HTTPS/HTTP3 secure contexts, latest-browser compatibility/capability verification; draft HTTP/3 WG implementation differences) can carry reliable streams and unreliable datagrams; WebRTC DataChannel (SCTP over DTLS/ICE) has partial-reliability semantics and P2P NAT but needs signaling/TURN. Browser raw UDP sockets are generally unavailable: no shipping raw GNS/ENet browser adapter without validated WebAssembly/browser host API. WebSocket/TLS fallback is reliable-ordered only, **does not claim unreliable datagrams** or equivalent latency.
4. **Network/provider dependencies:** TURN self-hosted optional (coturn and license pinned later), never mandatory paid CDN/Steamworks/proprietary service. No backend selected, built, tested, pinned or adopted; platform matrix is a set of proof targets.

## 8. Authoring, operations, instrumentation
A single versioned `TransportProfileV1` and staged `TransportConfigPlanV1` is available via Editor/CLI/MCP **only** with nonsecret read/validate/test-plan ops; privileged certificate/relay-credential and external-dial operations require narrowly authorized backend operations and redacted receipts, not an open socket or arbitrary request from AI. Config updates use typed CAS/rollback via DATA-04 or secure secrets owner, never storing PEM private keys in public game assets. Export profiles request PLAT capability proof. Metrics include handshake/connect/ICE path/crypto validation percentiles, in/out per-class bytes/packets, RTT distribution, jitter/loss/reordering, queue overflow, backpressure, recovery/rebind/reconnect, MTU probe failure, CPU/mem/syscall, security rejection and exact backend build/pins; trace sampling/privacy policy separate.

## 9. Future implementation slices and stop gates
**NECESSARY after approved ADR and implemented CORE-01:** minimal secure native client/server connection adapter on loopback under selected library; two honest profiles reliable ordered and unreliable latest (when supported), type/expiry/queue/metrics, deterministic virtual-network test harness and security validations; no gameplay or cloud service. **IMPORTANT:** QUIC DATAGRAM cross-lane comparison, browser WebTransport real support and NAT diagnostics/relay, reconnect/rebind, IPv6, integration with NET-02 future server. **FUTURE:** P2P full ICE/TURN managed service, multipath/failover across ISPs, multi-region routing, FEC, optimized zero-copy and console exports. New SDK and backend adopted only after owner-approved architecture/license, pinned versions/cryptographic threat review and evidence; all code packages currently blocked.

See [ADR-0047](../adr/0047-net-01-pluggable-secure-transport-capability-profiles.md), [technology-license matrix](../research/net-01-transport-technology-license-matrix.md), [semantic API](../contracts/net-01-transport-connection-api.md), [128 future cases](../testing/net-01-acceptance-matrix.md), [benchmark protocol](../research/net-01-transport-benchmark-protocol.md).
