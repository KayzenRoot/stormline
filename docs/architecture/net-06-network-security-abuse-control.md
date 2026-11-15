# NET-06 — Network Security & Abuse Control Architecture

**2026-11-15 | P00 RESEARCH ONLY.** WO `NLE-P00-WO-002-NET-06`, research [#248](https://github.com/KayzenRoot/stormline/issues/248), coding [#67](https://github.com/KayzenRoot/stormline/issues/67) OPEN/BLOCKED. Baseline `53ccaec7e60996e0e594415a261c3a3e4c7c54f0`, catalog #49/80. Formal prerequisites **NET-02 and NET-05** documented/PROPOSED only. No engine, keys, crypto stack, multiplayer server, fuzz tests or protection exists.

## Goal and security claims
Catalog acceptance: **Testes adversariais e ausência de bypass de autoridade**. This is a future proof obligation, NOT a verified claim. Assets: authoritative world/combat/rewards, secure session and server role, private player/hidden actor information, CPU/heap/network availability, keys/credentials and safe audit records. Attackers may be unauthenticated Internet senders, malicious authenticated clients, stolen-token holders, compromised clients/plugins, bot swarms, privileged but misconfigured tools, unsafe dependencies or malicious insiders. **Transport encryption and a signed token are necessary, not sufficient, for authorization.** No perfect anti-cheat or volumetric-DDoS immunity is possible to promise.

## Architecture ownership
| Module | Sole owner of truth | NET-06 role |
|---|---|---|
| **NET-01** | encrypted transport TLS/QUIC/DTLS, path validation, protocol anti-amplification, congestion and reconnection | audit transport posture and deny-rate policy; no custom encryption |
| **NET-02 (formal)** | authoritative dedicated server, game actor/match/command admission and commit | recommend and enforce policy hooks; cannot replace actual game rules |
| NET-03 | per-recipient field authorization, snapshot schema and relevance | adversarial wire privacy tests, no duplicate codec or disclosure authority |
| NET-04 | client prediction and optional read-only bounded server hit history | attack/fairness signals, cannot rewind game economy |
| **NET-05 (formal)** | session tickets, issuer/role, revocation, admission claims and identity | replay/rate checks; cannot mint independent identity |
| GAME-04 | authoritative rules, rewards, currency, quest and idempotent receipts | validate abuse obligations, never commit rewards |
| WORLD-01 / CORE-04 | canonical ECS EntityId+generation and server TickId | protect invalid/stale inputs; cannot modify world/clock |
| DATA-04 | schema, persistent source CAS, data retention and recovery | classify/redact sensitive events; no shadow datastore |
| QA-04 (downstream) | platform-wide secure SDLC, scanners, SBOM, fuzz CI, incident standards | NET-06 owns game-network-specific threats and evidence, QA-04 broader infrastructure |
| Editor/CLI/MCP/AI | permitted scoped authoring, operator consent and audit | no arbitrary server command, secret export, player impersonation or paid vendor action |

Formal catalog edges remain NET-02 and NET-05 only; all others are interface ownership, **not new dependency edges**.

## STRIDE and gameplay-specific threat map
| Threat | Boundary | Proposed mitigations and future observations |
|---|---|---|
| UDP spoof/reflection, preauth amplification | Internet to NET-01 | QUIC RFC9000 address validation, **unvalidated path outgoing bytes <= 3× received bytes**, bounded pre-auth state and path migration checks; this is QUIC-specific, not generic UDP or upstream DDoS mitigation |
| CPU/memory denial, parsing bombs | network to decoder and tick | size/length/recursion/decompression limits before allocation, expensive operation budgets, bounded queues/telemetry |
| authentic client forged hit/movement/reward | NET-02/GAME-04 authority | server-side actor ownership, tick/range/ammo/cooldown/LOS, nonmutating typed denials and durable idempotency |
| expired/stolen/replayed JWT/ticket | NET-05 to NET-02 | issuer/audience/type/alg/key allowlist, current revocation+ban, jti/nonce and match-world lease epoch recheck |
| replay across reconnect or server crash | NET-01/05/02/GAME-04/DATA-04 | separate anti-replay domains: transport PN, token jti, game input cursor, game event and durable commit; no global magic sequence |
| private entity, presence, inventory leak | NET-03/05 recipient | field ACL before interest/cache/compression; test decoded client wire, response and error size/timing; revoke future sends without promising to erase already leaked data |
| forged RTT/lag, predicted hit, low latency cheating | NET-04 to NET-02 | server-observed timing and clamped optional read-only hit historical query, never client time as authority |
| invite spam, lobby enumeration, shadow user access | NET-05 | scope/role/privacy filters, bounded fanout, anti-enumeration, ban and block precedence |
| privileged agent/tool misuse | Editor/CLI/MCP | operator capability+expected source CAS; no unchecked key, token or paid services |
| supply chain or telemetry disclosure | QA-04/DATA-04 | SBOM/license/security patch pin, no default raw IP/JWT/secret/private world logs |

## Proposed layered admission (not executable)
```text
untrusted bytes
 -> NET-01 authenticated path and crypto, bounded cheap pre-auth
 -> NET-05 current principal/session issuer/role/ban/nonce
 -> NET-06 coarse scoped quotas / replay and cost cap
 -> bounded decoder/typed schema, then NET-02 actor+world generation
 -> GAME-04 game-rule validation and idempotent canonical commit
 -> NET-03 field-authorized recipient projection
 -> NET-01 encrypted bounded send
 -> NET-06 redacted audit under DATA-04 retention and QA-04 evidence
```
A NET-06 ALLOW outcome is **necessary but never sufficient** for gameplay mutation. Unknown policy/role/epoch/schema/provider => deny. Avoid expensive hidden-world lookup or large denial response before cheap admission. No client claim of trusted clock, server actor, game value, connection security or admin role.

## Rate, anti-amplification, DDoS and fairness
Define typed hierarchical budgets (amounts TBD): unvalidated path/IP, secure connection, authenticated account, actor/game action class, lobby/match, host-wide CPU, memory, bytes, packets and queue, expensive codec and log writes. Token-bucket or work-queue scheduling candidates need real evidence. IP-only blocking penalizes NAT-shared players and fails against distributed botnets. Stage warnings/throttles and appeal for likely false positives; automatic irrevocable bans are NOT recommended based on sparse signals. Under overload drop stale cosmetic traffic before critical control while preserving fail-closed identity/game authority.
QUIC RFC9000 `8 imposes **3× anti-amplification** before peer address validation on QUIC endpoint, with path migration and exact bytes accounting owned by NET-01. TURN/STUN relay security and cost separate. **Application code cannot absorb volumetric attacks that saturate upstream links**; edge protection may cost money and requires later explicit operator approval.

## Replay, confidentiality and secure coding
NET-01 owns standards TLS1.3/QUIC/DTLS, key rotation and authenticated channel, no insecure/plaintext fallback. NET-05 owns typed short-lived JWT/ticket/issuer/current revocation. Scope replay windows per key, session, world, match and action domain; a signed valid ticket may still be revoked or wrong audience. NET-02 verifies a valid player actor and all rules even under a secure channel. No custom cipher, hardcoded client signing keys, authorization by client input hash, data compression as encryption, or secure-by-obscurity assumptions.
Harden parsers with exact length/version, bounded varint/list/nesting, finite float validation, allocation and decompression quotas, schema evolution refusal for unsupported required fields, safe lifetime across reconnect. Fuzz semantic state machines, memory bugs and races in **owned isolated fixtures only**. Zero crashes is not a security proof.

## Privacy and incident handling
Telemetry policy: classified PUBLIC/PRIVATE/SECRET with default REDACT prior to log, scoped pseudonymous correlation, limited TTL, retained raw packets only by explicit privileged process, no bearer tokens, raw secrets, complete IP, private lobby presence or hidden player inventories in routine logs. Avoid log injection and unbounded error content. Security incident states DETECTED/TRIAGED/CONTAINED/RECOVERED, with bounded key/ticket revocation, operator-approved response and DATA-04 retention, QA-04 cross-system evidence and rollback. LGPD legal compliance requires future review, not asserted.

## Scope and proof gates
NECESSARY after actual implementation approval: one local NET-01/05/02 chain and two separate authenticated players, simulated hostile client, actor/role/command and replay/expiry rejection, bounded bytes/memory/CPU, decoded NET-03 privacy, log redaction, isolated fuzz+sanitizers, high assurance evidence and recovery. IMPORTANT: multi-game fairness/false positives, cross-target platforms and optional provider outage. FUTURE: distributed reputation, paid upstream anti-DDoS and optional anti-cheat SDK after separate privacy/license evaluation. No release risk/DoD or numeric ceiling approved. See [ADR-0052](../adr/0052-net-06-defense-in-depth-authority-quotas-privacy.md), [technology and threat matrix](../research/net-06-security-technology-threat-license-matrix.md), [semantic API](../contracts/net-06-security-abuse-api.md), [128 future tests](../testing/net-06-acceptance-matrix.md), and [isolated benchmark protocol](../research/net-06-security-benchmark-protocol.md).
