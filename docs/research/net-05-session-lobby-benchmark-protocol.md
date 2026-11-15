# NET-05 — Reproducible Session, Lobby, Match Allocation, Reconnect and Security Benchmark Protocol

**P00 DOCUMENTARY ONLY, no runtime benchmark or paid resources.** All N05-T001..N05-T128 FUTURE/NOT EXECUTED. No measured create/join/leave latency, lobby size limit, authentication provider, reconnection SLA, 64-player support, NAT outcome or monetary spend.

## 1. Hypotheses and future acceptance policy
H1: one local NET-05 coordination process and one NET-02 ready headless server, with two independently authenticated client identities, can create/join/leave lobby and join actual game with separate receipts without SaaS. H2: forged invite/ticket, wrong audience/actor, expired/revoked session and concurrent join pressure fail closed without slot leakage or PII exposure. H3: disconnect/reconnect keeps intended match membership only within approved grace, never bypasses reauth/NET-02 lease. H4: users can self-host identity/discovery and handle offline/provider failure with explicit typed errors and bounded resources. H5: matchmaking/Agones/Steam/EOS adapters are optional and can be compared with local baseline without claiming free hosting. H6: conditional NAT/relay discovery succeeds or fails honestly with privacy and metered relay requirements.

## 2. Reproducibility manifest (future)
`SessionBenchmarkManifestV1`: Git base/head, approved ADR/Scope/DoD/risk/release class, NET-01 transport/TLS/ICE/reconnect revisions, NET-02 headless/health/game logic, NET-05 auth provider/config/key rotation, NET-06 security controls, DATA-04 CAS/idempotent store, original test fixture and anonymized principals, target Windows/Linux/macOS/Web architecture, CPU/RAM/container/build digest, network RTT/jitter/loss/NAT type and clock skew/drift, provider availability and mock/live label, identity session TTL/invite TTL/jti replay store, lobby/party sizes, match queue behavior, process/server/lease generation, warmup/repeats/sample counts, P50/P95/P99 raw data, memory/CPU/DB I/O/retry/403/timeout/jitter, security denial redacted trace, billable platform/relay bandwidth cost and clear consent, exact commands and CI URLs. No tokens/passwords/player data in logs.

## 3. Bench matrix (axis examples NOT shipping targets)
| Fixture | Conditions / variables to control | Future output and correctness evidence |
|---|---|---|
| `S01_LOCAL` | local test provider loopback-only, two identity subjects, one NET-02 server | create, lobby join, leave and NET-02 independent match admit, no SaaS |
| `S02_SECURITY` | invalid issuer/audience/typ/alg/kid, expired/revoked signature, rotated key | denial without user enumeration, finite CPU and no gateway bypass |
| `S03_INVITE` | 2/8/16/64 concurrent one-time invites/redeems and block list changes | exactly-once join/capacity, no brute-force token oracle or PII |
| `S04_LOBBY` | 1/8/16/32/64 concurrent clients, public/invite/private, 10/100/1k lobby listings | latency, clean privacy projection, authorized counts, memory/CPU |
| `S05_PARTY` | 2/4/8-party sizes with leader departure, split and simultaneous join | no two leaders, capacity fairness, group ticket remains atomic |
| `S06_MATCH` | manual local allocation vs optional matchmaker, queue cancellations and server fail | wait/assignment rate, failed allocation return, no auto-game-join |
| `S07_RECON` | RTT 1/20/60/120/250ms, 0/1/5/10% loss, jitter 0/5/20/50ms, disconnect 1/10/60s | actual time to regain NET-02 admit, refresh security, no stale ticket |
| `S08_NAT` | IPv4/IPv6, NAT mapping variants, direct/ICE/STUN and optional TURN relay | connection outcome, IP privacy and cost per GB, no STUN universal claim |
| `S09_PROVIDER` | OIDC issuer outage, stale JWKS, DNS failure, revocation store offline, partial recovery | explicit fail closed/retry, no silent production guest fallback |
| `S10_DATA` | CAS conflict/duplicate callback/partial leave/session expiration/bad storage | no double seat/reward, revocation and lease fencing correctly reconciled |
| `S11_ADAPTER` | optional Nakama/Colyseus/Open Match/Agones/EOS/Steam sandbox with explicit consent | feature/OS/version/license/cost matrix, no cloud implicit account |
| `S12_ABUSE` | invite spam, 100x join requests, malformed metadata/URL, privacy probing, callback replay | rate budget, redaction, bounded memory/CPU, no HIGH/CRITICAL auth defect |

All client counts, RTT/jitter and traffic figures are **test dimensions only**. Real hardware targets, max CCU, latency p99, cost and session TTL require approved owner numeric budgets after pilot.

## 4. Measurement and security protocol
1. **Identity before performance:** test token signatures/audience/typ/alg, ban/revocation, reauth and one-use jti under concurrent replay; verify actual NET-02 join receipt and secret absence from redacted logs. Lobby "joined" or network TLS ACK is not sufficient.
2. Use approved reproducible local harness for two real clients and one NET-02 server. Record warm/cold starts, independent state machines and generated match/world epoch; no game engine exists yet so no benchmarks executable in P00.
3. Establish synthetic isolated network impairment, never send unsolicited DoS to public hosts. Distinguish provider search time, party queue time, server allocation latency, NET-01 secure channel setup, lobby commit and NET-02 admission; p50/p95/p99 samples and confidence intervals only from enough real runs.
4. Mutate identities and privacy during disconnect: block member, close lobby, expire ticket, rotate issuer key, restart server, change world epoch. Ensure no rejoining with old permissions and no cross-match role/actor/PII leakage; check timing and response content for hidden lobby enumeration.
5. Test at-least-once callbacks / exactly-once logical idempotency via per-operation tokens and CAS; no promise of atomic external DB/host changes without durable evidence. Simulate power loss/SIGKILL and lease expiry/reconciliation; persistent store availability and behavior recorded.
6. Compare CPU per operation and RAM, session/slot/TTL cardinality, revoked nonce memory, DB queries and queue lag. Add rate/abuse and table-scan pressure; measure per-principal fairness and recovery.
7. Compare local-only, self-host OIDC/Nakama/Colyseus and optional managed adapters only when explicitly approved, including hardware+storage+relay transfer and cloud/service recurring fees. Open-source license does not imply $0 managed hosting; do not provision paid resource automatically.
8. **Stop criteria:** any auth bypass, replay, role escalation, secret log, cross-lobby data, double allocation, real-money automation, license incompatibility or known HIGH/CRITICAL => BLOCKED/CORRECTION REQUIRED. Documentation CI must never be reported as a real server test.

## 5. Reporting status
At research creation **zero measured metrics, zero actual tests, zero software/services installed**, all cases FUTURE/NOT EXECUTED. Report exact commands, raw data and hardware, risk, regression and pt-BR audit only in a later independently approved implementation. Primary references: [RFC 9700](https://www.rfc-editor.org/rfc/rfc9700.html), [RFC 8725](https://www.rfc-editor.org/rfc/rfc8725.html), [Nakama matchmaker](https://heroiclabs.com/docs/nakama/concepts/multiplayer/matchmaker/), [Agones allocation](https://agones.dev/site/docs/reference/gameserverallocation/), [Steam lobbies](https://partner.steamgames.com/doc/features/multiplayer/matchmaking).
