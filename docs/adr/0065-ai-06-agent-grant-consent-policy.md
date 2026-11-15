# ADR-0065 — Owner-Enforced Attenuated Agent Grants, Consent and Fail-Closed Policy

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #301 | NLE-P00-WO-002-AI-06 | future code #80 OPEN/BLOCKED | BASE 886f8c8687c4c79a18a3cb3b7e82a26a054eb656.** 61/80 researched baseline, 19 pending, all 80 implementation WOs BLOCKED, zero engine, NLE-D009 license OPEN. Formal dependencies **AI-04 + AI-01 ONLY**; predecessor ADR-0063/ADR-0060 PROPOSED.

**STATUS: PROPOSED / NOT OWNER-APPROVED / NOT ADOPTED / NO IMPLEMENTATION AUTHORIZATION.**

## Problem
Stormline's agent tools will eventually inspect, modify, delete, build and export real project data. AI-01 owner commands and AI-04 MCP transport are researched but not implemented. Host app names, prompt text, tool annotations and OAuth token presence are not adequate authoring permission. A stronger grant/policy/consent contract is needed without enabling AI-06 to become a second executor. Acceptance: **an agent must be unable to modify files/projects outside its approved scope**.

## Proposed decision
1. **Formal dependencies exactly AI-04 + AI-01.** AI-04 authenticates transports and supplies a verified per-request context; AI-01/owners remain the only semantic execution and commit authorities. AI-06 supplies policy/grant/consent services, never direct project mutations. AI-05, DATA-02, EDIT-02, GAME-02 and AI-07 are integration owners, not formal DAG edges.
2. **Deny-by-default and deny-overrides** effective permissions. Explicit principal+agent+project+CommandId+resource+target+time+quota scope, intersecting human user rights, project owner rules and current policy. Unknown/missing policy or identity returns DENY.
3. **Separate identity proof, capability grant and owner authorization.** Valid remote MCP OAuth resource bearer token proves access to this server only; it does not authorize all project files/commands. Local stdio verified OS peer and workspace selection use a distinct local trust model. Never use clientInfo, model message or tool metadata as a principal.
4. **Attenuating delegation only.** Child agents inherit subset of parent capabilities, shorter or equal TTL, bounded depth and per-child explicit instance ID. A child cannot mint broader permissions. Parent revoke cascades.
5. **Policy decision/owner PEP split.** AI-06 PDP computes a typed, traceable ALLOW/DENY/REQUIRE_CONSENT/UNAVAILABLE result from immutable policy version; AI-01 and downstream owner enforce resource authorization and source revision immediately before side effect. Decision is not a commit token. Never shortcut owner because PDP said allow.
6. **Consent bound to exact plan and context.** For destructive/export/irreversible or otherwise higher-risk operations, require owner-generated diff/plan digest and authenticated trusted UI approval receipt bound to actor/agent/project/CommandId+args/source revision/target/destination/expiry/nonce, single use and CAS/idempotency. MRTR answer, model "yes", cached approval or misleading UI text is not approval.
7. **Revocation takes effect at next owner-enforced boundary**, including ongoing operation before commit. In-flight or already committed effects are reported honestly by owner journal/receipt; no fictitious automatic rollback, especially for export/publication. Future AI-07 owns transaction-level undo.
8. **No unrestricted host authority.** For untrusted code, use OS sandbox as layered containment when implemented/verified per target, plus owner VFS and allowlisted IPC; if needed isolation unavailable, refuse untrusted execution. WASM sandbox ≠ native arbitrary-code sandbox.
9. **Security metadata not secrets:** stable and redacted per-request/decision/consent/owner receipt audit; no raw bearer/API keys, personal data or absolute paths. Tamper-evident storage is only a candidate requiring exact key management, retention and integrity proof.
10. **Protocol-aware without mixing eras:** AI-04 separately implements MCP 2026-07-28 stateless per-request auth and legacy 2025-11-25 compatibility if proven; no permanent session privilege or quiet fallback. Protected-resource metadata RFC 9728 and OAuth issuer/audience/scope validation remain AI-04 transport duties.
11. **Policy evaluator technology remains unselected.** Compare Cedar, OPA/Rego, policy DSL embedded in owner C++20 and ACL-only baseline using real conformance, correctness, packaging, SBOM, platform benchmarks and license evidence. Do not install or select an engine by this ADR.
12. No license, future code release class or auth SDK is approved; NLE-D009 remains OPEN; all 80 implementation WOs stay BLOCKED; exactly 128 future security tests will be specified, NOT EXECUTED.

## Alternatives
| Alternative | Reason rejected or deferred |
|---|---|
| Let MCP OAuth token or clientInfo authorize everything | OAuth audience/scope and client metadata do not grant per-ProjectId owner mutation; risk cross-project leakage |
| AI-06 owns direct command handlers or raw filesystem | duplicate command authority and bypass of AI-01 owner source transactions |
| Role-only RBAC of "agent" = admin | misses actor/project/command/resource/revision and source rights, excessive agency |
| Trust prompt instructions or tool annotations | attacker-controlled natural language and metadata; no privileged security semantics |
| Session-wide permanent grant cached by MCP transport | modern stateless MCP, revocation and cross-client isolation break |
| Broad inherited parent credentials for subagents | privilege laundering, no child attribution, long-lived stolen token |
| Consent inferred from MCP input_required or model "yes" | MRTR user-input exchange not cryptographically bound trusted approval |
| Policy ALLOW without per-owner recheck | time-of-check/time-of-use race, stale source revision and symlink/junction escape |
| Sandboxing only, skip semantic ACL | OS container cannot decide ProjectId/CommandId/license/consent semantics |
| Semantic ACL only, skip OS sandbox for untrusted native code | plugin exploit can bypass entire application API |
| External cloud policy decision service mandatory | network/privacy/availability bottleneck, offline/editor dependency and cost |
| Fixed Cedar/OPA library now | ADR must defer choice until exact tag/platform/license and correctness/performance proof |
| Auto-rollback irreversible action after cancel | cancellation and external publication are not guaranteed reversible |

## Consequences, risks and mitigation
Benefits: one owner execution authority, explicit least-privilege agent delegation, auditability, good user consent UX, local/remote separation and measurable negative security oracles. Costs: per-call evaluation, owner policy enforcement, revocation propagation, trusted approval flow, OS-specific sandbox testing, audit retention/clock and policy upgrade rules. Riskiest failures are confused deputy, prompt injection→tool misuse, cross-project path escape, stale grant at commit, consent replay, agent delegation chain abuse and hidden authorization fallback.

## Owner ratification gate
- Exact policy schema, denial precedence, grant issuer and authenticated local/remote principal mapping approved.
- Strong owner side-effect boundary and path/AssetId ownership implemented and independently tested.
- Explicit consent UI UX, one-use approval receipt and immutable owner plan/source revision linked.
- ACL fuzz + symlink/TOCTOU, cross-project/actor, prompt injection, revocation/expiry, OAuth token audience/issuer and agent delegation property tests pass.
- Windows/Linux/macOS sandbox availability and fallback verified, not assumed.
- Exact Cedar/OPA/custom candidate version/license and SBOM/CVE/NOTICE, correctness and benchmarks accepted.
- All 128 A06 future scenarios implemented and passed, suitable independent High-Assurance review proof and rollback/readback.
- Pt-BR audit and approved separate owner ADR after evidence. Until then this ADR is **PROPOSED** and future issue #80 stays OPEN/BLOCKED.

[Architecture](../architecture/ai-06-agent-security-authorization.md) · [Policy API](../contracts/ai-06-authorization-api.md) · [Security matrix](../research/ai-06-auth-technology-license-threat-matrix.md).
