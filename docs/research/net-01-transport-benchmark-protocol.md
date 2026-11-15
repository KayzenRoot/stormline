# NET-01 — Secure Transport Benchmark, NAT and Impairment Reproducibility Protocol

**P00 PROPOSED ONLY: NO ENGINE, NO NETWORK HARNESS, NO RUNS, NO METRICS.** Future acceptance N01-T001..T128 defined, all NOT EXECUTED. This protocol cannot claim an implementation beats QUIC, GNS, WebRTC or an engine used in a commercial title.

## 1. Hypotheses and honest performance classes
H1: correct use of chosen native backend and strong authenticated encryption can deliver both a reliable control channel and true unreliable latest-only messages without unbounded queues on loss. H2: QUIC RFC9221 DATAGRAM and GNS native lane behave differently in congestion/reliability, yet semantic contract can report accurate capabilities. H3: TLS/ALPN identity, server auth, rebind, 0-RTT restrictions and quotas remain correct under attack. H4: browser WebTransport (when supported), WebRTC or WebSocket declared-degraded fallback remains honest; not all adapters are interchangeable. H5: NAT/relay and reconnect behavior can be observed and classified without promising all connectivity is guaranteed.

## 2. Every future run must include provenance
`NetBenchManifestV1`: project/CORE SHA+dirty state, source+approved ADR+exact dependency commit+TLS crypto provider/SPDX/SBOM, client/server binary and runtime ABI, browser version, OS/CPU/arch/RAM/NIC/link driver + governor and network network interface, emulation/container/vm type, UDP offload/GRO/GSO settings, test topology and firewall/NAT/relay config, IPv4/IPv6, target socket/MTU, secured channel/ALPN/ticket/certificate issuer reference but **never secrets**, identity/cert mode, cipher and 0-RTT policy, parallel connection count and message size/channel/rate, workload/reliability/deadlines, target budget, emulator seed and fault trace, raw client/server timestamps/packet captures redacted, execution commands, output hashes, warmup/repetitions, versioned findings. Code/backend unimplemented => mark `NOT RUN`.

## 3. Topology and scenario axes
| Fixture | Variables, no claimed performance | Evidence |
|---|---|---|
| `B01_LOOPBACK` | isolated native loopback secure handshake and 1/16/64/256 peers; warm/cold; reliable+unreliable lane | connection/handshake time p50/p95/p99, CPU, RSS, queued bytes and valid identity |
| `B02_LAN` | 1G/100M throttled LAN; IPv4/v6, RTT 1/10/30 ms, differing path MTU | throughput, application delivery p99, jitter and reordering, verified payload integrity |
| `B03_WAN` | controlled RTT 20/60/120/250 ms; jitter 0/5/20/50 ms; no real geography inference | loss/queue tail, RTT variance, application stale payload percent and priorities |
| `B04_LOSS` | iid and burst 0/0.1/1/5/10% packet loss, reorder 0/1/5%, duplicate/ECN where possible | retransmission vs expired/datagram drop, queue bounded, control survives |
| `B05_CONGESTION` | variable bottleneck 128kbps/1/10/100Mbps and competing flow; fairness | pacing, BBR/CUBIC/RFC9002-compatible selected algorithms, no unsafe bursts or starvation |
| `B06_MTU` | path max 576/1280/1500 and tunnel/relay overhead; DPLPMTUD black holes | no datagram fragmentation assumption; oversized denial; recovery |
| `B07_NAT` | full cone/restricted/symmetric/hairpin, single/double NAT, CGNAT and IPv6; provisioned ICE/STUN/TURN | candidate success/type, direct vs relay vs explicit failure, credential/privacy proof |
| `B08_REBIND` | NAT rebinding, 4G/Wi-Fi switch, IPv4/IPv6 candidate changes, migration during buffered send | real path validation, anti-hijack, epoch, session reauthorization, reconnect timings |
| `B09_FAILURE` | blackhole 1/5/30/120s, DNS failure, bogus ALPN/cert, token revoked, server restart | timeouts, retry caps, jitter backoff, false session recovery and repair |
| `B10_SECURITY` | spoofed UDP/reflection, 0-RTT replay, handshake flood, malformed packet length, oversize reassembly, certificate expiry | rejection, memory bound, secret redaction, fuzz/ASan/UBSan and no bypass |
| `B11_BROWSER` | latest browser versions and declared older support, WebTransport HTTP3 and RTCDataChannel vs WSS | real HTTPS/security context, DATAGRAM negotiation/support, success/fallback classification |
| `B12_INTEGRATE` | CORE scheduler/game tick server client load, NET-02 authority, GAME-04 receipts, NET-03 snapshot policy future | no transport ACK counted as gameplay commit; jitter/per tick CPU, workload integrity |

**Network impairments must be reproduced with an approved tool**: Linux `tc netem` or Toxiproxy/Mininet/emulator under isolated test permission; Windows/macOS impairment tools verified later. No unprivileged automation running destructive system-wide shaping on an active host. Use a virtual deterministic network harness for unit tests; use real 2-machine or controlled WAN link for interoperable realism, distinguishing each result. Do not generate public DDoS/port scanning or unsolicited traffic.

## 4. Measurement definitions / counterfactuals
- **Handshake:** client connect attempt time to verified peer identity + application ACTIVE; compare resumed/full/0-RTT* separately, *0-RTT gameplay writes prohibited*. Log address path/QUIC version, not credentials.
- **RTT, loss and jitter:** smoothed RTT, RTT sample distribution and ACK delay on sender; precisely define lost packet denominator, reorder and duplicate windows; jitter per chosen estimator and packet-to-packet variation. One-way latency only with synchronized clocks and recorded uncertainty; otherwise use RTT and echoed timestamps.
- **Application receipt latency:** frame arrival vs consumer validation vs gameplay action commit **separate**, cannot infer server game state from transport ACK.
- **Tail stats:** raw samples sufficient for p95/p99 (not ten runs for p99), repetitions, bootstrap CI and sample sizes, p99.9 only with enough independent observations. Report cold/warm, confidence bounds and failures, not average alone.
- **Congestion and queues:** actual sent/acked/dropped/expired, pacing rate, packets in flight, current cwnd/backpressure, per-class queued bytes, packet/CPU syscalls, steady-state and reconnect storms; saturating bandwidth does not imply good game latency.
- **Security correctness:** reject fake certs, replay/0-RTT game state, bogus version/ALPN downgrade, amplification and protocol fuzz; DoS resilience requires NET-06 and infra provider defenses and cannot be certified by this P00 document.
- **Migrations:** server restart, client path switch, NAT rebinding, firewall and TURN unavailable; record success/failure and retry budget, never claim seamless always-on session.

## 5. Method, acceptance and stop
1. Freeze code+config/dependencies/toolchains+cert/trust and OS versions per run; instrument backend and semantic contract, collect both peers and measured clocks. Missing REAL RUNNER => no performance claim.
2. Compare GNS vs one pinned QUIC implementation vs WebTransport/WebRTC only under **matching** encryption/auth, topology, packet size and delivery semantics; do not compare reliable with unreliable throughput as equivalent. Unsupported features reported UNAVAILABLE not zero score.
3. Warm up/steady state, repeated trials and cold-start separately. Preserve raw trace/digests without personal IP/secret. Re-run after changed algorithm/SDK, TLS/OS platform or API.
4. Resource budgets and target numbers determined AFTER baseline and owner scope/DoD approval. Security HIGH/CRITICAL, plaintext fallback, memory amplification or replay of gameplay mutation -> BLOCKED regardless of speed.
5. Include legal/operational costs: TURN relay bandwidth/hosting, optional service access, SDK redistributability; **no mandatory paid services** in baseline.
6. Report verdict per target and capability: APPROVED / CORRECTION REQUIRED / BLOCKED, hardware and tool logs, source pins, errors/rollback/recovery/Checkpoint Delta. Exactly [128 future cases](../testing/net-01-acceptance-matrix.md), 0 executed now.

## 6. Sources and comparator caveats
[RFC9000](https://www.rfc-editor.org/rfc/rfc9000.html), [RFC9001](https://www.rfc-editor.org/rfc/rfc9001.html), [RFC9002](https://www.rfc-editor.org/rfc/rfc9002.html), [RFC9221](https://www.rfc-editor.org/rfc/rfc9221.html), [RFC8445 ICE](https://www.rfc-editor.org/rfc/rfc8445.html), [RFC8656 TURN](https://www.rfc-editor.org/rfc/rfc8656.html), [GNS](https://github.com/ValveSoftware/GameNetworkingSockets), [MsQuic](https://github.com/microsoft/msquic), [quiche](https://github.com/cloudflare/quiche), [MDN WebTransport](https://developer.mozilla.org/en-US/docs/Web/API/WebTransport_API). These are documentation/protocol comparisons, not executed Stormline experiments or third-party benchmarks adopted.
