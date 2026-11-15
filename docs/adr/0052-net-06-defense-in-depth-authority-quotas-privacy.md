# ADR-0052 — Multiplayer Defense in Depth, Authority, Quotas and Privacy

**Status PROPOSED, NOT OWNER APPROVED, NOT ADOPTED**, 2026-11-15. Research #248, WO NLE-P00-WO-002-NET-06, coding #67 OPEN/BLOCKED, baseline `53ccaec7e60996e0e594415a261c3a3e4c7c54f0`; engine license NLE-D009 OPEN.

## Context
Engine intends secure multiplayer with native/Web clients, but NET-02 and NET-05 formal dependencies only have research/ADR PROPOSED, no executable server or authentication. Transport encryption cannot stop legitimate but malicious player commands. Rate limiting solely by IP punishes NAT-shared players. Network parsers, retry logic, lobby presence, input prediction and privileged editor/MCP must be hostile-input aware. Perfect anti-cheat and zero-cost volumetric DDoS defense are not attainable promises.

## Proposed architectural decision
Use an original **typed SecurityDecisionV1 policy plane** layered across existing module-owned boundaries rather than duplicate protocol encryption/issuer/game validation. The NET-01 secure transport owner performs address/path validation and correct cryptographic security. NET-05 owns identity, issuer, token nonce/jti and ban/expiry. NET-02 independently checks current game actor, match and every command; GAME-04 owns actual game-rule and idempotent rewards. NET-03 only emits authorized per-recipient field projections. NET-04 optional lag query remains read-only bounded. NET-06 supplies threat register, resource quotas, replay-risk decision, privacy and abuse signals, redacted incident evidence and future protocol-specific fuzz/security tests. QA-04 owns broad secure SDLC/SBOM/fuzz infrastructure, DATA-04 owns retention/schema/CAS.

Security check sequence: cheap valid transport/path -> current session/ticket -> bounded parse/alloc and multi-level budget -> server actor capability -> game rule commit -> authorized egress -> redacted audit. Unknown policy or unavailable security store fails closed, not unauthenticated fallback. **ALLOW is never permission to mutate world by itself**.

Replay protection requires different domains for QUIC packet number, NET-05 ticket nonce, NET-02 game command sequence, GAME-04 event id and DATA-04 durable transaction. No derived client clock/position/loot trusted. Resource budgets include malformed message CPU and heap, queue and telemetry caps, not only request count. QUIC pre-address-validation 3× amplification limit is transport-specific per RFC9000; other protocols need own vetted policy. Upstream volumetric DDoS requires optional edge/provider/operational mitigation and cannot be claimed solved by game code.

Use risk-scored, explainable **staged** abuse response, not client kernel driver or unreviewed permanent automated bans. Measure false positives across high RTT/NAT/assistive input. Preserve hidden world and user data confidentiality by field-level egress and retention policy. Runtime security changes are HIGH_ASSURANCE and demand strong negative tests/rollback/independent objective reasoning (not necessarily outside human reviewer for solo repo).

## Alternatives
| Alternative | Benefit | Defect / outcome |
|---|---|---|
| Trust encrypted connection and signed token | cheap | authenticated cheaters can send invalid world commands; reject |
| Custom game cryptography | bespoke control | error-prone downgrade/key design, duplicates NET-01; reject |
| Single IP global limiter | easy | botnet evasion/NAT unfairness, does not cap expensive commands; reject alone |
| Security module replicates GAME-04 rule authority | clear interface initially | drift and bypass to second authority; reject |
| Original typed deny-first checks with NET-01/02/05 sole owners | auditable and local-first | performance/availability and false-positive proof needed; **leading PROPOSAL** |
| Mandatory paid anti-cheat/DDoS SaaS | optional edge capacity | cost/privacy/platform lock-in; not approved |
| Assume zero fuzz crashes proves secure | concise metric | coverage incomplete; reject |

## Adoption and stop gates
Actual owner-approved threat model, privacy/retention and cryptography/backend, verified real NET-02/05 predecessor implementations, native/Web OS targets, exact per-action quotas/DoD, game authority/decoded wire negative tests, version/keys/license SBOM, fuzz with sanitizer evidence and incident rollback. Known HIGH/CRITICAL auth bypass, data leak, corruption, unbounded resource drain blocks future code progression. No target rate/latency/attacker detection efficacy or code technology is chosen here. 128 test cases FUTURE/NOT EXECUTED. All 80 coding packets remain BLOCKED. Merging this document **does not** approve ADR-0052 or executor readiness.
