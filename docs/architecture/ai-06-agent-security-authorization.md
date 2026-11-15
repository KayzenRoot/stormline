# AI-06 — Agent Security & Authorization: Capability Grants, Consent and Isolation v0.1

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #301 | NLE-P00-WO-002-AI-06 | future code #80 OPEN/BLOCKED | BASE 886f8c8687c4c79a18a3cb3b7e82a26a054eb656.** 61/80 researched baseline, 19 pending, all 80 implementation WOs BLOCKED, zero engine, NLE-D009 license OPEN. Formal dependencies **AI-04 + AI-01 ONLY**; predecessor ADR-0063/ADR-0060 PROPOSED.

## 1. Product goal, proof and explicit trust boundary
AI-06 catalog acceptance is **"Agente não pode modificar arquivos/projetos fora do escopo."** Prove with independently constructed unauthorized read/write/delete/export/execute tests across workspace/project, actor, resource owner, target, revision and delegation chain. The oracle is the **canonical owner and OS filesystem state**, not a policy response alone. A denied call must produce zero unauthorized owner commits, opened paths, network connections, persisted secrets and privileged receipts.

AI-06 proposes a narrowly scoped **policy and grant lifecycle** around the *existing* AI-01 semantic command owner and AI-04 MCP protocol boundary. It owns grant issuance/attenuation/revocation, consent policy, decision evaluator port and audit event policy. It is **not** a new command bus, file manager, OAuth authorization server, raw OS shell executor, sandbox runtime, agent planner, auth identity provider or project database. Every operation is owner-enforced.

## 2. Formal dependency graph and distinct authorities
Only **AI-04 + AI-01** are formal DAG dependencies:
- **AI-04** establishes remote MCP transport identity from validated resource-scoped OAuth bearer token or local stdio verified OS peer/process launch; it verifies the protocol era and forwards a verified request context. It does **not** mint grants, trust clientInfo, or authorize engine modification. MCP 2026-07-28 is stateless, so every modern request is independently authenticated. The 2025-11-25 legacy path must not become a permanent session grant.
- **AI-01** owns CommandId/descriptor, validation, owner dispatch, preconditions, side-effect class, source revision, dry-run/intent/commit receipt, idempotency and owner permission enforcement. A successful AI-06 policy decision is **necessary but never sufficient** for mutation; owner revalidates just before commit and on each capability-relevant step.
- **AI-06** owns versioned authorization policy, bounded grant metadata, consent receipts and revocation epochs, deny-overrides decision, projected least-privilege scope and audit classification; it never writes canonical scene/asset/source on its own.
- AI-03 descriptions, AI-05 resource visibility, DATA-02 ProjectId/AssetId, DATA-01 VFS, DATA-04 scene commits, GAME-02 script sandbox, CORE-06 telemetry, EDIT-02 workspace picker and future AI-07 transactions are integration owners, **not new formal AI-06 dependencies**. No circular AI-04 -> AI-06 compile dependency is introduced; AI-04 consumes a narrow future policy port.
- Unknown owner API or authorization source ⇒ **DENY/UNAVAILABLE**, not optimistic permission. P00 has no compiled AI-01/04/06 interfaces; proposals are not live.

## 3. Principals, identities and delegation
Distinguish **human account**, local OS peer, client application instance, agent identity/session instance, active project/workspace, delegated on-behalf-of human, tool owner, and third-party authorization server. None is inferred from model output, agent name, MCP clientInfo/serverInfo, prompt text, receipt ID or a human-readable label.

A proposed VerifiedAgentContextV1 binds: subject UserId/verified OS peer, ClientInstanceId from authenticated transport, AgentInstanceId minted by Stormline, ProjectId/workspace owner-approved scope, verified GrantSetId/policy epoch, target OS/profile, issuer/audience for remote, delegation parent, request digest/trace and deadline. For stdio OS process identity and explicit workspace selection are required; process ancestry alone is insufficient if launcher can be spoofed. For HTTP, strict issuer/audience/signature/expiry/scope plus verified operator/project mapping are required every request. Client bearer token is **never forwarded downstream** or stored in project source.

Delegation is **attenuation only**: child ∩ parent ∩ human's present rights ∩ project/owner policy ∩ target; depth and duration bounded, independent child identity and revocation. No "agent can grant itself more permissions", hidden superuser, chained on-behalf-of self-promotion, credential sharing or privileged administrative approval via model chat.

## 4. Resource and action scope
Define grants by exact authoring command capability (AI-01 CommandId/major and side-effect class), ProjectId, workspace root(s), canonical stable asset/scene IDs, resource kind/field, export target and destination allowlist, allowed client/agent IDs, time window, max invocation count/budget, rate/concurrency ceilings and permitted delegation depth. Every relevant dimension must intersect, never union by accident.

- **READ**: inspect owner-approved source metadata and bounded excerpts, not arbitrary host filesystem scanning.
- **PREVIEW**: typed plan/diff with zero source/OS side effects and owner revision lock, bounded output; may show risk/required grants.
- **MUTATE**: explicit narrow writes to current owner-verified ProjectId and source revision; no raw path arguments or unscoped imports; requires owner commit receipt.
- **DELETE/EXPORT/EXTERNAL/IRREVERSIBLE**: strict higher-risk policy, plan, consent and additional owner/export gate; high-assurance review proof before implementation.
- No grant for "all_files", wildcard workspace-root /, unrestricted network, GPU driver pointers, arbitrary subprocess, dangerous native plugins, hidden tool or model-supplied shell string.

Use canonical owner IDs and path descriptors. Canonicalize symlink/junction/hardlink behavior, mount points, alternate path encodings, UNC, case-insensitivity and TOCTOU through owner openat/file-descriptor boundary, **not** a string prefix check. Never assume a Windows drive letter/path string or macOS alias equals owner ProjectId.

## 5. Policy decision and enforcement model
Proposed control flow:
1. **Transport authentication (AI-04)** establishes verified external identity. HTTP challenge vs local stdio credentials follow their different protocols. Missing auth fails closed.
2. **Admission (AI-06 policy decision point, PDP)** evaluates deny-overrides rules for operation, actor, project, effective grants, target and policy version, with deterministic input/evaluation digest. Owner policy may require owner-plan consent.
3. **Inspection (AI-01 + owner PEP)** validates CommandDescriptor version, schema, stable resource IDs, capability, source revision, side-effect class and budget; no raw OS access before this.
4. **Consent / planning** for high-risk action: owner creates plan digest and risk summary; trusted user-facing approval UI obtains explicit choice outside LLM text and returns one-use signed/bound consent record; updated input or revision forces new approval.
5. **Just-in-time recheck** at owner commit/side-effect boundary: actor/project/grant epoch, command+args digest, revision, approved plan, per-owner ACL, idempotency/expiration and resource rights. Commit journal/receipt remains AI-01/owner authority. AI-06 decision alone cannot commit.
6. **Audit/receipt** stores redacted *request/decision/consent/commit provenance*, including deny, cancellation, policy version and readback, never raw secrets/token/project content.

PDP timeout, bad policy schema, missing consent, revoked parent, unknown command, hidden target, owner unavailable or external authorization failure = DENY with safe errors; do not provide an "allow all offline" fallback. When a user makes a local manual edit through Editor, it still passes AI-01 owner ACL; no fake privilege equivalence via agent.

## 6. Consent design and anti-prompt-injection
A request for user input via MCP MRTR InputRequiredResult is **not authorization**. Neither a model-generated "yes", tool annotation, resource text nor a prompt is trusted approval. A trusted UI binds ApprovalIntentV1 to actor, project, CommandId, normalized typed args digest, owner snapshot/revision, affected resource IDs, side-effect/risk, purpose, target/destination, policy epoch, nonce, expiry and maximum use count=1. The owner verifies it atomically with the operation; replay/change of args/revision/destination/target invalidates it.

Risk tiers for future design: read-only, bounded preview, scoped reversible edit, destructive/irreversible delete/export/network/publishing; compare owner classification with actual effects and fallback to stricter class when uncertain. Human can revoke/decline, preview diff and inspect exact destinations. Informational UI must not coerce acceptance or hide a destructive action in a long plan.

Prompt injection defenses focus on **tool authority separation**, not relying on model instruction filtering. Treat docs, imported scenes/scripts, tool responses, MCP resources, issue descriptions, filenames and agent-to-agent messages as untrusted data. Typed commands and owner PEP block execution, export or privilege change even if model follows malicious text. Do not allow a prompt to amend policy, consent or trusted system context.

## 7. Multi-agent and lifecycle isolation
Each agent instance gets separate principal, grant set, task trace, project scope and resource budget; same human account does not mean same active project. Subagent rights are **subset** with depth TTL and explicit delegation provenance. Agent-to-agent messages are untrusted and never carry ambient owner capability or bearer credential. Delegated actions preserve originating human/agent chain in redacted audit.

A revoked grant/policy epoch invalidates future tool calls, resource reads, list/filter/cache/cursor/subscription delivery, job polls/updates/cancels, pending approvals and delegation children. For in-flight **mutation**, recheck owner at actual commit; cancellation does not retroactively undo committed work, so owner receipt and AI-07 future transaction/compensation govern recovery. Never promise remote client cache deletion or automatic rollback after irreversible external publish.

## 8. OS sandbox is defense in depth, not authorization
Policy control does not isolate malicious native code. If running untrusted script/plugin/agent executable in future:
- **Linux** candidate: separate unprivileged process, Landlock on supported kernels, seccomp, namespaces/cgroup/rlimits, closed inherited FDs, readonly/narrow mounts, explicit egress deny; probe actual kernel feature ABI and test fallback. Landlock cannot grant permissions or replace VFS owner ACL.
- **macOS** candidate: hardened helper process, App Sandbox entitlements, security-scoped bookmarks with explicit user grant, process peer verification and OS packaging. Host signed/notarized app sandbox support must be actually proven.
- **Windows** candidate: AppContainer/low-privilege token, restricted Job Objects, ACLs, controlled broker handles and explicit filesystem grants; UAC or a normal user token alone is not a sandbox.
- **Cross-platform WASI/Wasmtime** may isolate untrusted WebAssembly by controlling imported host functions, preopens, memory/fuel/epoch budgets. It **does not** safely contain arbitrary native C++ plugins or a model running as host with full privileges. Exact platform/SDK/license/security benchmark gate separate.
- If a required isolation primitive is unavailable, reject the untrusted-execution feature and report UNSUPPORTED, do not silently run unsandboxed. No sandbox/OS confinement is implemented in P00.

## 9. Secrets, audit, privacy and rollback
Store no long-lived bearer token or API key in prompts, command args logs, project files, source index, MCP tool responses or Git. Future credential broker/OS vault handles are separate, narrowly scoped and not exposed to agents. Short-lived resource-specific tokens, issuer-binding and no token passthrough prevent confused-deputy attacks. Browser/login flows, PKCE, CIMD/DCR are authorization-server/client side; AI-06 cannot pretend to be an OAuth IdP.

Audit is append-only/tamper-evident **candidate** with sequence, prior-event digest or signed checkpoints, event schema version, actor/agent/delegation chain, project pseudonym, command, policy/grant epoch, decision reason *class*, plan digest, approval ID, owner commit receipt/trace, source revision and outcome. Redact PII, source snippets, credentials, host absolute paths and raw prompts; audit proof not token leak. Audit storage/signer/retention and privacy policy remain UNDECIDED, and no claim of cryptographic non-repudiation without actual keys/verification. Denied actions require audit too. Replays, crash gap, clock rollback, log exhaustion and partial journal recovery are future tests.

## 10. Threat-model matrix
| Adversarial action | Protection / future independent oracle |
|---|---|
| Tool description or prompt says "ignore policy" | AI-01 owner PEP treats text as data, zero command bypass |
| Agent reads/writes another project using relative path or symlink | canonical owner ProjectId/IDs + OS containment; zero outside filesystem delta |
| Parent delegates more rights to child | formal attenuation, independent chain verification; deny privilege increase |
| OAuth token wrong issuer/audience/scope/expired | AI-04 resource server auth rejects before dispatch |
| Credential forwarded to external API | strict token audience, secrets broker, no passthrough |
| Consent spoof via MRTR or prompt | trusted UI receipt and owner atomic plan/revision validation |
| Plan/args/destination edited after approval | digest mismatch and one-use nonce deny |
| Project switch during multi-step action | owner policy/epoch/source revision recheck at commit |
| Forged task/URL/cursor reused in another project | per-request grant and token binding; safe generic denial |
| Hidden command discovery/count timing oracle | filter before list/rank/count, uniform safe denied result |
| Local stdio proxy connects to arbitrary TCP port | verify OS peer and restrict transport + sandbox egress |
| Unsupported OS sandbox quietly skipped | deny untrusted execution, explicit reason, no downgrade |
| Revoked identity stale in cache | epoch invalidation and owner recheck; no false retroactive client erasure |
| Malicious extension reads host secrets | OS sandbox and zero ambient credentials, safe fail-closed |
| Audit tamper/delete/drop | indexed receipts, integrity chain and drop alerts, no false completeness |
| Denial-of-service to policy engine | quotas, timeouts, fail closed and bounded recovery |

## 11. Acceptance and release evidence
Target Windows/Linux/macOS Apple Silicon editor/headless; remote MCP opt-in HTTPS. Future tests must cover owner source AND OS filesystem reconciliation, 128 unique A06-T001..A06-T128 FUTURE/NOT EXECUTED, threat corpus, source revision/consent/revocation races, protocol-version matrix and measured performance/false-denial rates. No benchmark targets, SDK selection, grants, license, auth provider, sandbox, host compatibility, runtime security audit or code exists today.

[ADR-0065](../adr/0065-ai-06-agent-grant-consent-policy.md) · [Technology/security/license](../research/ai-06-auth-technology-license-threat-matrix.md) · [API contracts](../contracts/ai-06-authorization-api.md) · [128 tests](../testing/ai-06-acceptance-matrix.md) · [Benchmark](../research/ai-06-security-benchmark-protocol.md).
