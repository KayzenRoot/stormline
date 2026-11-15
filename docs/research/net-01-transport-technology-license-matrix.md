# NET-01 — Transport/QUIC/Game-Network Technology, Standards and Licensing Matrix

**Primary-source research | 2026-11-15 | ALL CANDIDATES, NONE INSTALLED OR ADOPTED.** License summary is not a redistribution or legal clearance: verify exact file-level SPDX/NOTICE, TLS provider/crypto export rules, native/Web binaries, patents, security advisories and transitive packages *at pinning*. Stormline code license NLE-D009 OPEN, approved backend NONE.

## 1. Standards and required distinctions
| Standard (primary source) | Scope | Correctness/security constraint |
|---|---|---|
| [RFC 768 UDP](https://www.rfc-editor.org/rfc/rfc768.html) | datagram transport | no delivery, order, confidentiality, connection or congestion guarantees by itself |
| [RFC 9000 QUIC v1](https://www.rfc-editor.org/rfc/rfc9000.html) | UDP secure multiplexed transport/migration | streams reliable, per-stream ordered; path validation/anti-amplification; no default DATAGRAM without extension |
| [RFC 9001 QUIC TLS](https://www.rfc-editor.org/rfc/rfc9001.html), [RFC 8446 TLS1.3](https://www.rfc-editor.org/rfc/rfc8446.html) | authenticated encryption and key update | 0-RTT app data replayable, disable game mutations on 0-RTT; strong identity verification required |
| [RFC 9002 QUIC loss/congestion](https://www.rfc-editor.org/rfc/rfc9002.html) | detection, cwnd, pacing | no arbitrary UDP flood or unbounded reliable backlog |
| [RFC 9221 QUIC DATAGRAM](https://www.rfc-editor.org/rfc/rfc9221.html) | optional unreliable QUIC frames | requires negotiation, no retransmission/fragmentation/receiver flow control; datagram still congestion controlled; ACK not game receipt |
| [RFC 9369 QUIC v2](https://www.rfc-editor.org/rfc/rfc9369.html) | version negotiation / anti-ossification | v2 does not alter application capabilities or guarantee more speed |
| [RFC 8899 DPLPMTUD](https://www.rfc-editor.org/rfc/rfc8899.html) | packetization layer MTU discovery | account for headers/relay/caps; avoid large UDP fragmentation and black holes |
| [RFC 8445 ICE](https://www.rfc-editor.org/rfc/rfc8445.html) | NAT traversal candidate checks | separate signaling and user privacy; not equivalent to QUIC migration |
| [RFC 8489 STUN](https://www.rfc-editor.org/rfc/rfc8489.html) | discover mapped address/connectivity probe | **not NAT traversal standalone** |
| [RFC 8656 TURN](https://www.rfc-editor.org/rfc/rfc8656.html) | permissioned relay allocations | real server, bandwidth, credentials and cost; optional/self-host candidate |
| [RFC 9147 DTLS1.3](https://www.rfc-editor.org/rfc/rfc9147.html) | datagram encryption | DTLS does not itself guarantee reliable/ordered messages, replay policies need audit |
| [RFC 8831 WebRTC DataChannel](https://www.rfc-editor.org/rfc/rfc8831.html) | SCTP over DTLS over ICE/UDP | reliable and partial reliable profiles, signaling/relay P2P requirements and browser permissions |
| [W3C WebTransport](https://www.w3.org/TR/webtransport/) + [MDN WebTransport](https://developer.mozilla.org/en-US/docs/Web/API/WebTransport_API) | browser reliable streams and unreliable datagrams via secure context | MDN Baseline 2026 for latest modern browsers, older browsers and some features vary; no raw socket / automatic P2P |
| [IETF draft WebTransport HTTP/3](https://datatracker.ietf.org/doc/draft-ietf-webtrans-http3/) | H3 mapping, datagrams and settings | draft status and version/implementation interoperability require checking at selection |

**Protocol standards are not code licenses**; implementation licensing is distinct from standards copyright/IETF Trust Code Components. No source code from IETF RFC copied here.

## 2. Native/browser/server implementations
| Candidate + upstream official source | Stated upstream code license | Delivery + likely fit | Risks and adoption gate |
|---|---|---|---|
| [Valve GameNetworkingSockets](https://github.com/ValveSoftware/GameNetworkingSockets), [license](https://github.com/ValveSoftware/GameNetworkingSockets/blob/master/LICENSE) | **BSD-3-Clause** | native UDP game-oriented reliable/unreliable messages, priority lanes, encrypted packets, IPv6 and ICE P2P in supported builds | not Steamworks/Steam relay entitlement, no generic browser raw UDP; identity trust configuration, dependencies/build and target matrix |
| [ENet original](https://github.com/lsalzman/enet), [license](https://github.com/lsalzman/enet/blob/master/LICENSE) | **MIT** | minimal C library for UDP reliable/ordered/unreliable channels | **not secure just because reliable**; authenticated crypto/TLS or DTLS layering requires separate audited design, DoS and IPv6 verification |
| [Microsoft MsQuic](https://github.com/microsoft/msquic), [LICENSE](https://github.com/microsoft/msquic/blob/main/LICENSE) | **MIT** | native C/C++ QUIC (TLS1.3), platform backend, streams, conditional datagrams | exact OS/CPU/platform capabilities, TLS providers/ABI/security, message mapping, rebind/0-RTT policy |
| [Cloudflare quiche](https://github.com/cloudflare/quiche), [LICENSE](https://github.com/cloudflare/quiche/blob/master/LICENSE) | **BSD-2-Clause** | Rust QUIC+HTTP/3 with C FFI, RFC9221 and congestion/loss | Rust/C bridge ABI, BoringSSL/build dependencies/attribution/target Web actual support, queue/future-proof pin |
| [ngtcp2](https://github.com/ngtcp2/ngtcp2), [COPYING](https://github.com/ngtcp2/ngtcp2/blob/main/COPYING) | **MIT** | native C QUIC transport with pluggable TLS backend/crypto helpers, RFC9221 profile candidate | crypto library license/pins important; examples vs core dependencies differ; FFI/ALPN/version gates |
| [picoquic](https://github.com/private-octopus/picoquic) | verify exact release license/3P before adoption (**not relied upon**) | experimental native QUIC comparison | must prove releases, TLS provider and security, no unverified license claim |
| [libdatachannel](https://github.com/paullouisageneau/libdatachannel), [LICENSE](https://github.com/paullouisageneau/libdatachannel/blob/master/LICENSE) | **MPL-2.0 since 0.18**, earlier LGPL-2.1-or-later; transitive varying licenses | C/C++ WebRTC datachannel, ICE/WebSocket, browser interop candidate | MPL file-level obligations if modified/distributed, usrsctp/libjuice/DTLS/TLS/3P SBOM; security/trust |
| [coturn](https://github.com/coturn/coturn), [LICENSE](https://github.com/coturn/coturn/blob/master/LICENSE) | **verify exact bundled license and dependencies at adoption (not pinned here)** | self-hosted optional TURN relay/service | deployment/security/privacy/real operating bandwidth, no fake zero-cost cloud relay, credentials and abusive consumption |
| Browser [WebTransport](https://developer.mozilla.org/en-US/docs/Web/API/WebTransport_API) | browser platform API, **not an embeddable MIT library** | HTTP/3 secure-context stream/datagram | feature detect, server support, HTTPS cert/ALPN, deploy restrictions, older browser fallback |
| Browser [WebRTC RTCDataChannel](https://developer.mozilla.org/en-US/docs/Web/API/RTCDataChannel) | browser API, not a redistribution license | P2P reliable + partial-reliable when requested, SCTP/DTLS/ICE | signaling/TURN, candidate privacy and SCTP channel details; do not blindly claim unreliable datagram equivalent |
| Browser [WebSocket](https://developer.mozilla.org/en-US/docs/Web/API/WebSocket) | browser API | optional secure reliable/ordered fallback | **no unreliable mode**, backpressure/queue bound, head-of-line; explicit degraded capability report |

## 3. Functional capability matrix (hypotheses, not tested)
| Transport family | Native server/client | Web client | Reliable | Unreliable | Encryption | NAT P2P | STATUS |
|---|---|---|---|---|---|---|---|
| GameNetworkingSockets | candidate | **not assumed** | message lanes | message lanes | built-in crypto, verify peer identity | optional ICE, needs signaling/relay | UNTESTED |
| QUIC MsQuic/quiche/ngtcp2 | candidate | browser via **different WebTransport adapter**, not raw library | independent streams | **RFC9221 if negotiated** | TLS 1.3 | direct QUIC migration/rebind ≠ full ICE | UNTESTED |
| ENet | candidate | **not assumed** | channels | channels | **not supplied as complete secure authenticated protocol** | not automatic | NOT SAFE BASELINE |
| WebTransport | native H3 server implementation required | modern browser secure context | streams | H3 datagrams (when supported) | HTTPS/TLS | not P2P ICE | UNTESTED |
| WebRTC | native optional via libdatachannel | browser supported | SCTP channel | partial reliability, **not raw QUIC DATAGRAM** | DTLS/ICE | ICE/STUN/TURN with service | UNTESTED |
| WSS | server candidate | browser supported | ordered stream | **NO** | TLS | client to server via proxies | DEGRADED-RELIABLE ONLY |

There is **NO** chosen backend or guaranteed interoperability, latency advantage, Web parity, zero-cost hosting or multi-region service.

## 4. Adoption due diligence, licenses and explicit selection gates
- Exact upstream repository commit/tag + SPDX/license file path, transitive crypto/ICE/TLS/codec licenses (including MPL/LGPL, BoringSSL/OpenSSL obligations), NOTICE and attribution, SBOM, build reproducibility, EOL/security advisories, protocol CVE fixes, export compliance, static/dynamic linking requirements.
- Desktop Windows/Linux/macOS including target architectures and native C++ runtime link/ABI proof; actual Web browser support matrix and real server H3/WebRTC. No assigning a shared native UDP library to browser without actual WASM host capabilities.
- Security: authenticated server identity/cert trust, key rotation and revocation, 0-RTT mutation forbid, amplification control, consented P2P/relay, SSRF/PII.
- Measure on agreed hardware networks and adversarial loss/jitter/reorder/NAT; document quotas and standard deviation/tail; select by use case and acceptance, not star count or marketing.
- Only OWNER APPROVED future ADR + license/NLE-D009 + Scope/DoD can authorize installation/coding. No implementation packet may unlock because this research landed.
