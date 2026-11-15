# NET-06 — Versioned Network Security Decision and Abuse-Prevention Semantic API v0.1

**Research #248 | Work Order NLE-P00-WO-002-NET-06 | coding #67 OPEN/BLOCKED | PROPOSED / NOT COMPILED.** All types/methods are design-only, not runtime headers, SDK, actual key handling, anti-cheat implementation or privacy compliance.

## Typed structures and trust domains
| Proposed V1 type | Important fields (all typed/validated) | Security owner and invariant |
|---|---|---|
| `SecurityPrincipalContextV1` | NET-05 issuer/account/session generation, NET-02 match actor+world epoch, role, current ban/revocation | client-supplied principal, actor, clock or role cannot elevate authority |
| `SecurityTrustBoundaryV1` | UNTRUSTED_PATH, VERIFIED_TRANSPORT, VERIFIED_SESSION, ADMITTED_ACTOR, SERVER, ADMIN_OPERATOR; revision | trust only increases upon explicit owner validation |
| `SecurityConnectionPostureV1` | NET-01 secure backend, TLS/QUIC/DTLS and key/path epochs, path address validated flag | actual crypto/path integrity NET-01 sole responsibility |
| `SecurityValidationEnvelopeV1` | protocol version, byte bounds, message type/schema, world generation, parse/decompression budget | cheap fail-closed malformed input before costly allocation |
| `SecurityCommandAdmissionV1` | NET-02 match/actor ownership/tick/causal input and GAME-04 receipt policy | only server/game rule owners can commit gameplay |
| `SecurityReplayDomainV1` | NET01_PACKET, NET05_TICKET, NET02_COMMAND, GAME04_EVENT, DATA04_DURABLE | independent keys/windows, never use one ACK as another permission |
| `SecurityReplayWindowV1` | issuer/session/match/world/key epoch, nonce/jti or wrap-safe seq, last+bitmap, expiry/capacity | no stale/replayed game command or ticket grant |
| `SecurityRateBudgetV1` | PATH, IP, CONNECTION, SUBJECT, MATCH, COMMAND_CLASS, HOST; burst/refill/work/bytes/CPU/heap | multi-layered and fair under shared NAT; numeric amounts TBD |
| `SecurityRateDecisionV1` | ALLOW, DROP, DELAY, DENY, OBSERVE, REPORT; retry hint and sanitized reason | ALLOW never alone grants server actor or loot permission |
| `SecurityResourceCountersV1` | preauth RX/TX bytes, parse work, decoder CPU, memory, queue, logs, inflight sessions | NET-01 QUIC 3x rule only before path validated, no claim full DDoS immunity |
| `SecurityPolicySnapshotV1` | policy ID/version/capability, approved issuer and schema keys, rollback target | stale/unknown policy fails closed |
| `SecurityPermissionCheckV1` | operation, game actor/role/capability, match, recipient, privacy class and revision | deny unauthorized player info, NET-03 remains egress field owner |
| `SecurityTransportAmplificationV1` | NET-01 path validation status, uniquely attributed bytes, QUIC control response accounting | NET-01 implements actual transport, not NET-06 sending |
| `SecurityAbuseSignalV1` | event (replay/flood/role/lag/interest scrape), confidence, redacted evidence digest | anomaly signals are not proof cheater guilt |
| `SecuritySanctionReviewV1` | OBSERVE, WARN, THROTTLE, TEMP_BLOCK, MANUAL_REVIEW, TTL/appeal | no automatic permanent/irreversible ban on weak heuristic |
| `SecurityRedactionPolicyV1` | PUBLIC, PRIVATE, SECRET, restricted diag, data retention and allowed operator role | no raw JWT/IP/full hidden actor/contact in ordinary logs |
| `SecurityAuditEventV1` | correlation, policy revision, trust level, pseudonymous scope, result and sanitized reason | bounded retention and injection-safe structured fields |
| `SecurityIncidentEventV1` | DETECTED/TRIAGED/CONTAINED/RECOVERED, severity, owner and rollback proof | no auto destructive incident action |
| `SecurityFuzzFixtureV1` | synthetic corpus seed, target schema and exact Git SHA, CPU/heap/packet/time cap | isolated test harness ONLY, never external host |
| `SecurityFuzzFindingV1` | CWE, sanitizer trace, minimized seed+artifact hash, severity, reproducible CI | zero observed crashes does not imply secure |
| `SecurityEvidenceBundleV1` | source base/head/OS/backend, negative owner proof, decoded egress, corpus runs and residual risk | evidence, not self-certification or DoD completion |
| `SecurityOperatorPrincipalV1` | separate trusted admin capability, expected DATA-04 CAS, explicit irreversible/cost approvals | Editor/CLI/MCP authoring only, no key export/player impersonation |

## Proposed operation semantics, NOT actual callable functions
- `InspectSecurityCapability(Target,Transport,AuthProvider)`, `PreviewSecurityPolicy(Project,Version,Operator)` -> read-only redacted supported/unsupported status; `Stage/Validate/CommitSecurityPolicy` -> capability check and DATA-04 expected-revision CAS, explicit audit. Cannot mint keys, user tickets, approve paid cloud, issue server shell.
- `EvaluateCheapPreAuthBudget(NET01Path,BoundedMetadata)` -> cheap deny before expensive decoder. `ReadNET01TransportPosture` -> verified protocol facts, never user-supplied flag. NET-01 enforces actual anti-amplification/path validation.
- `EvaluateSessionReplay(NET05IssuerClaims,RevocationState,ConnectionEpoch)` -> risk decision; NET-05+NET-02 still independently validate ticket and actor. `CheckScopedSequence(Domain,Epoch,Nonce)` -> separate transport/game/event/durable replay.
- `EvaluateGameCommandBudget(VerifiedPrincipal,NET02Actor,Class,EstimatedWork)` -> bounded rate; `RecordGameRuleDenial` consumes NET-02/GAME-04 verdict, never overrides it.
- `EvaluateAuthorizedEgress(NET03FieldPolicy,RecipientWorldEpoch)` -> privacy assertion, cannot allow secrets to untrusted peer. `FlagLagFairnessRisk(NET04ServerObservedTiming)` -> signal only, no automatic hit rewrite or ban.
- `EmitRedactedSecurityAudit` and `ExportIncidentEvidence` require least-privilege support principal, data classification and retention. `RunSyntheticAdversarialFixture` DENIED in production, future test harness only.

## Hard invariants
1. No security ALLOW bypasses **server-side NET-02 game command validation** or GAME-04 authenticated idempotent commit.
2. NET-05 JWT signature/audience/expiry + current revocation/actor lease and NET-01 secure channel are **both necessary but insufficient** for game authority.
3. Replay windows are scoped to ticket, transport packet, game command, event and durable transaction; no interchangeability, and server restart/reconnect invalidates epochs safely.
4. Unknown/unavailable policy, wrong type/length/role/schema/epoch, invalid crypto or unsupported native/Web feature fail closed with **bounded inexpensive denial**.
5. QUIC 3x unvalidated-path byte limit is protocol specific and must be implemented by NET-01; NET-06 cannot claim to shield an ISP link from DDoS.
6. No default logs with token, password, full IP/contact, hidden actor fields or raw decrypted payload. Violations need sanitized typed audit and limited retention.
7. No client packet/user timing is trusted to pick historical hit window or world state. No arbitrary client authority.
8. Future fuzz/attack fixtures require isolated authorized environment; no public targets or vulnerable external hosts.

## Fail-closed typed errors
`SECURITY_NOT_IMPLEMENTED, SECURITY_POLICY_UNAPPROVED, SECURITY_TRUST_BOUNDARY_UNVERIFIED, SECURITY_TRANSPORT_DOWNGRADE_DENIED, SECURITY_TRANSPORT_INTEGRITY_INVALID, SECURITY_PATH_UNVALIDATED, SECURITY_QUIC_ANTI_AMPLIFICATION_LIMIT, SECURITY_PREAUTH_RATE_EXCEEDED, SECURITY_HANDSHAKE_WORK_CAP, SECURITY_TOKEN_INVALID_ISSUER, SECURITY_TOKEN_WRONG_AUDIENCE, SECURITY_TOKEN_ALGORITHM_DENIED, SECURITY_TOKEN_EXPIRED, SECURITY_SESSION_REVOKED, SECURITY_TICKET_REPLAYED, SECURITY_TICKET_KEY_ROTATED, SECURITY_ACTOR_OWNER_DENIED, SECURITY_MATCH_EPOCH_STALE, SECURITY_COMMAND_DUPLICATE, SECURITY_COMMAND_LIMIT, SECURITY_GAME_RULE_DENIED, SECURITY_PACKET_SIZE_REJECTED, SECURITY_PARSE_INVALID, SECURITY_VERSION_UNKNOWN, SECURITY_DECOMPRESSION_BOMB, SECURITY_ALLOCATION_BUDGET, SECURITY_FLOAT_INVALID, SECURITY_PRIVATE_EGRESS_DENIED, SECURITY_LOBBY_ENUMERATION_DENIED, SECURITY_INTEREST_SCRAPING, SECURITY_LAG_TIMESTAMP_UNTRUSTED, SECURITY_REPLAY_WINDOW_INVALID, SECURITY_HOST_RESOURCE_EXHAUSTED, SECURITY_UNFAIR_AUTOBAN_REVIEW, SECURITY_PRIVACY_LOG_REDACTED, SECURITY_DIAGNOSTIC_PERMISSION_DENIED, SECURITY_MCP_ROLE_IMPERSONATION_DENIED, SECURITY_MCP_COST_APPROVAL_REQUIRED, SECURITY_PROVIDER_FAILURE_DENY, SECURITY_INCIDENT_OPERATOR_REVIEW_REQUIRED, SECURITY_FUZZ_PRODUCTION_DENIED`.

All errors include typed reason, policy version/correlation, retry class and protected account scope **without** leaking hidden object or personal details. All NET-06 test assertions FUTURE/NOT EXECUTED.
