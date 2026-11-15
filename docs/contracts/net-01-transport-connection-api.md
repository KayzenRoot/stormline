# NET-01 — Versioned Secure Connection, Message and Capability Semantic API v0.1

**Research #228 | WO NLE-P00-WO-002-NET-01 | coding issue #62 OPEN/BLOCKED | PROPOSED, NOT C++ HEADERS/WIRE ABI, NOT SHIPPED NETWORK API.** No actual connection exists; all operations below are prospective interfaces with typed receipts.

## 1. Core type semantics
| Versioned type | Fields / interpretation | Ownership + guard |
|---|---|---|
| `TransportBackendIdV1` | normalized engine-owned backend descriptor and pinned source/build digest | backend is internal detail, no untrusted user chosen dynamic native binary |
| `TransportEndpointV1` | hostname/IP/port or service identity, address family, requested protocol, privacy and capability flags | CORE-01 resolution, NET-05 discovery; no arbitrary file/host from MCP |
| `TransportPrincipalV1` | authenticated peer identity claim, issuer/expiry, permitted role/scope, binding to crypto context | NET-05/NET-02 validate, NET-01 only binds verified peer; no anonymous authority |
| `TransportConnectionIdV1` | opaque id + generation + backendEpoch, session binding only if verified | stale callbacks and cross-session reply rejected |
| `TransportCapabilityProfileV1` | reliable ordered, reliable independent streams, unreliable datagrams, partial reliability, server/browser, path migration/ICE, IPv4/v6, crypto/ALPN, max payload, status/reason | backend-advertised *observed*, UNKNOWN!=SUPPORTED; PLAT confirms target |
| `TransportDeliveryProfileV1` | RELIABLE_ORDERED / RELIABLE_INDEPENDENT / UNRELIABLE_LATEST / BOUNDED_EXPIRING / CONTROL_CRITICAL, channel, requested priority, expiry, size limit, ordering scope | no automatic strength upgrade/downgrade; explicit unsupported receipt |
| `TransportConnectionOptionsV1` | backend/target policy, trust policy, ALPN, DNS timeout, connect/handshake/idle deadlines, retry policy, budgets and privacy profile | valid safe defaults, no plaintext/insecure skip verify |
| `TransportConnectPlanV1` | resolved options, endpoint candidate set, role/identity, current capability and test report, no secrets, StageId | inspect/preview cannot dial network |
| `TransportSessionBindingV1` | NET-05 ticket id/issuer/epoch/expiry and NET-02 accepted principal/permissions | binding is not transport connectivity nor gameplay authorization |
| `TransportMessageEnvelopeV1` | schema version, connection epoch, sender role, channel, sequence, issue TickId where applicable, payload type/digest, length, flags, expiry, anti-replay nonce when needed | NET-01 transport packet + upper data type only; no raw gameplay mutation |
| `TransportSendRequestV1` | ConnectionId, DeliveryProfileId, payload view/ownership lifetime, deadline, correlation and idempotency key where relevant | per-channel size/quota/capability before allocation, no unbounded copy |
| `TransportSendReceiptV1` | REJECTED/QUEUED/SENT_TO_BACKEND/EXPIRED/DROPPED_CONGESTION/TRANSPORT_ACKED, reason, bytes/epoch/trace | NET-02/GAME-04 alone may emit APP_ACCEPTED or gameplay commit |
| `TransportReceiveReceiptV1` | validated decrypt/peer/epoch/schema/length, channel and tick metadata, arrival monotonic timestamp, receiver acceptance/rejection | NET-01 never directly writes ECS, event bus or save state |
| `TransportConnectionStateV1` | IDLE, RESOLVING, PROBING, HANDSHAKING, AUTHENTICATING, ACTIVE, SUSPECT, MIGRATING, RECONNECTING, DRAINING, CLOSED, FAILED | explicit generation/timeout/transition cause |
| `TransportPathV1` | candidate ID/IP family, network/relay type, validation state, PMTU/MTU, privacy/redaction flag, current measured RTT | endpoint/candidate leak limits, path validation, no blind IP trust |
| `TransportStatsSnapshotV1` | backend/version, ns monotonic window, RTT/srtt/variance, jitter/loss/reorder, p50/95/99 when enough samples, bytes/packets, queue/backpressure, expiry, energy/CPU attribution if measured | provisional metrics, zero-data means UNKNOWN not zero latency |
| `TransportReconnectIntentV1` | old ConnId+epoch, new trusted endpoint/session reference, retry attempt+budget, backoff and safe replay marker | NET-05/02 reauthorize, no blanket application retransmit or 0-RTT mutation |
| `TransportSecurityPolicyV1` | TLS/DTLS/QUIC acceptable identity, key/CA policy, replay/0-RTT OFF, redaction, rate/quota requirements | NET-06 threat owner and approved platform crypto provider |
| `TransportNetworkFaultProfileV1` | virtual link latency, jitter distribution, loss, duplicate, reorder, bandwidth, MTU, NAT/firewall/rebind, deterministic seed | benchmark/testing only; no nondeterministic hidden live-network state |

## 2. Proposed semantic operations, no implementation
| Operation | Result and authority |
|---|---|
| `InspectTransportCapabilities(Target,BackendHint)` | read-only capability profile with SOURCE/UNKNOWN status, no forced backend |
| `PreviewTransportConfiguration(Project,Config,Principal)` | read-only validated plan, trust and privacy threat report; no network dial |
| `StageTransportConfig(Project,ExpectedRevision,Plan,Principal)` -> `ValidateTransportConfig(StageId)` -> `CommitTransportConfig(StageId,ExpectedRevision)` | role-scoped DATA-04 config CAS, secure secrets stored separately, never P00 actual mutation |
| `RequestTransportConnect(Endpoint,Options,Principal)` | async typed handshake/state events + actual observed connection receipt, requires engine runtime and explicit permissions |
| `RequestTransportListen(BindOptions,Principal)` | authorized server only, quotas, consent and restrict public address/port |
| `SendTransportMessage(ConnectionId,Profile,Envelope,Payload)` | bounded queue admission, then later transport disposition; no proof game applied |
| `ReceiveTransportMessage(ConnectionId,Channel,MaxBytes)` | validated typed immutable payload; backend lifetimes never cross unsafe engine barrier |
| `InspectTransportStats(ConnectionId,Window)` | redacted network stats, not precise other-user location or sensitive IP |
| `RequestReconnect/RequestPathValidation/RequestGracefulClose` | state machine with epoch and application authorization; no fraudulent seamless guarantee |
| `InjectVirtualNetworkFaults(TestHarness,Seed,Profile)` | restricted test-only, blocked in production; generates future reproducible fault traces |

There is **no** generic "open arbitrary socket" capability for GAME-02 scripts, Editor/CLI/MCP or third-party packs. Editor/CLI/MCP parity concerns authoring/inspect/test-plan, not external network access. NET-05 provides service discovery and relay allocation, not NET-01.

## 3. FSM legal transitions and ordering invariants
- `IDLE -> RESOLVING -> PROBING -> HANDSHAKING -> AUTHENTICATING -> ACTIVE` or any stage -> `FAILED/CLOSED` with typed cause. `ACTIVE -> SUSPECT -> MIGRATING/RECONNECTING or DRAINING -> CLOSED`; DRAINING is bounded. Rebind without new TCP/QUIC handshake may preserve connection id only after validated path/crypto context. Failed auth may not downgrade to anonymous ACTIVE.
- A packet/event from a stale `backendEpoch`/`ConnectionId.generation` is never consumed. A successful transport ACK cannot be interpreted as application durable commit, game authority or exact-once semantics. Upper-layer GAME-04 retries are idempotent only if future gameplay API declares and verifies idempotency.
- `UNRELIABLE_LATEST`: newest supersedes older message by tuple (channel, payload type, object revision), but arrival is not guaranteed; no reassembly or queue indefinite storage. Wraparound and epoch tests required. `RELIABLE_ORDERED` order only within channel/stream; independent stream order across channels undefined. `BOUNDED_EXPIRING` unsupported unless backend concretely offers tested semantics, no ad-hoc fake retry contract.
- QUIC DATAGRAM size limited by negotiated max_datagram_frame_size + path max_udp_payload_size + PMTU and headers; no UDP fragmentation or automatic split that silently changes reliability.
- `ConnectionId` is not secret/authentication. 0-RTT authenticated gameplay mutation rejected; even with safe future idempotent request, separate anti-replay threat model required. Server identity and session ticket checked independently.

## 4. Trust, budgets, and error taxonomy
Proposed **all-fail-closed** errors: `BACKEND_NOT_SELECTED, CAPABILITY_UNAVAILABLE, TARGET_UNSUPPORTED, WEB_SECURE_CONTEXT_REQUIRED, WEB_DATAGRAM_UNSUPPORTED, RELIABILITY_UNSUPPORTED, PEER_IDENTITY_INVALID, CERTIFICATE_UNTRUSTED, TLS_NEGOTIATION_FAILED, ALPN_MISMATCH, PROTOCOL_VERSION_UNSUPPORTED, EARLY_DATA_REPLAY_RISK, SESSION_BINDING_EXPIRED, SESSION_AUTHORITY_DENIED, NETWORK_CONNECT_DEADLINE, HANDSHAKE_DEADLINE, IDLE_TIMEOUT, NETWORK_UNREACHABLE, DNS_REBIND_BLOCKED, ADDRESS_FAMILY_UNAVAILABLE, NAT_CANDIDATE_FAILED, TURN_RELAY_NOT_PROVISIONED, PATH_VALIDATION_FAILED, CONNECTION_EPOCH_STALE, CONNECTION_ALREADY_CLOSED, MTU_EXCEEDED, DATAGRAM_NOT_NEGOTIATED, MESSAGE_TOO_LARGE, QUEUE_CAP_EXCEEDED, CONGESTION_BACKPRESSURE, MESSAGE_EXPIRED, REASSEMBLY_BUDGET_EXCEEDED, PACKET_MALFORMED, PACKET_REPLAY_REJECTED, INVALID_SEQUENCE, RATE_LIMITED, AMPLIFICATION_LIMIT, PRIVACY_CONSENT_REQUIRED, UNAUTHORIZED_ENDPOINT, UNTRUSTED_SCRIPT_DIAL, SOURCE_REVISION_CONFLICT, CONFIG_MIGRATION_REQUIRED, SHUTDOWN_IN_PROGRESS, TEST_ONLY_API_DENIED`.
Each error has reason, retryability, layer, correlation, no cert/private IP/token/packet plaintext in logs. Library-specific undocumented errors must map to honest `UNKNOWN_BACKEND_ERROR` with redacted diagnostic hash and backend version.

**Mandatory limits:** project/role endpoint allowlist, max concurrent connections, handshakes per IP and /prefix, candidate count, DNS attempts, per-channel queued bytes/messages, in-flight reliable bytes, receive bytes/message, per-peer fragment/reassembly memory and timeout, message age and transport timer/backoff attempts, parallel ICE probes and relay use; all numeric defaults **TBD in reviewed performance/security ADR**. No unbounded recursion or actor run-to-completion while holding network callback lock. No synchronous blocking in gameplay tick.

## 5. Compatibility, credential and rollout contract
`TransportConfigRevisionV1` is a versioned source asset with zero plaintext secrets; trust identity material is managed by a separate secure credential provider, accessed by opaque key refs. Version negotiation and ALPN fail closed; capability fallback only with explicit user/admin policy and equivalent security, NEVER plaintext. Config staged/validated/committed through DATA-04 semantics; current active sessions pin old epoch until orderly drain/migration and rollback is documented. NET-02/NET-05 may reject reconnect even if TLS/QUIC session resumes.

**Future proof:** at least one secure native loopback path with profile parity and loss emulator, optional alternative native backend and real browser server/browser path; Windows/Linux/macOS x64/ARM targets only when actually tested. All 128 [future scenarios](../testing/net-01-acceptance-matrix.md) **NOT EXECUTED**.
