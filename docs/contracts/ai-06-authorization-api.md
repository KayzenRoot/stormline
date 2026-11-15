# AI-06 — Proposed Typed Agent Grant, Policy, Consent, Revocation and Audit API v0.1

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #301 | NLE-P00-WO-002-AI-06 | future code #80 OPEN/BLOCKED | BASE 886f8c8687c4c79a18a3cb3b7e82a26a054eb656.** 61/80 researched baseline, 19 pending, all 80 implementation WOs BLOCKED, zero engine, NLE-D009 license OPEN. Formal dependencies **AI-04 + AI-01 ONLY**; predecessor ADR-0063/ADR-0060 PROPOSED.

**Logical proposals only. No compiled ABI, policy evaluator, auth service, OAuth provider, OS sandbox, grant database, signed approval, token, key, network listener or runtime.**

## 1. Formal upstream contracts, never duplicated
| Upstream | Owner-proposed types and responsibilities | AI-06 relationship |
|---|---|---|
| **AI-04** | McpRequestContextV1, ProtectedResourceProfileV1, verified transport OAuth/stdio admission, version, protocol errors | consume verified identity assertion; do not trust raw JSON-RPC metadata, HTTP headers or clientInfo |
| **AI-01** | CommandPrincipalV1, CommandId/CommandDescriptor, CommandInvocationV1, CommandDryRunPlanV1, CommandPlanApprovalV1, CommandReceiptV1, CommandJobHandleV1, idempotency/owner revision | supply policy, grant, approval and revocation decisions for owner PEP; owner retains commit control |

Formal dependencies **AI-04 + AI-01 only**. DATA-02/04, AI-03/05, EDIT-02, GAME-02, CORE-06 and AI-07 are integrations, not extra dependency edges. AI-06 must not invent new AssetId, ProjectId, command executor or OAuth issuer.

## 2. Proposed V1 logical types
| Type | Required fields | Invariant |
|---|---|---|
| AgentIdentityV1 | AgentInstanceId (opaque, server minted), ClientInstanceId, verified subject UserId/OS peer, parent agent, issuer context, key/profile reference | model/client name/role label is never identity |
| VerifiedAgentRequestV1 | transport attestation ref, actor+agent+delegation chain, ProjectId, command id/schema version, target/owner, nonce, deadline, source revision, trace ID, policy epoch | authenticated from AI-04 plus trusted owner context, not caller text |
| AgentGrantV1 | GrantId, issuer, subject actor+AgentId, parent GrantId, ProjectId, workspace roots, allowed CommandIds and side-effect classes, owner resource IDs/fields, target/destination, TTL, use-count, quota, delegation depth, version, state | never exceeds parent/human/current owner rights; default DENY |
| GrantAttenuationV1 | parent ID/epoch, child AgentInstanceId, requested subset, expiry, depth, nonce | subset/intersection only; no upward privilege |
| AgentPolicyBundleV1 | policy schema, policy generation/hash, issuer signature/profile, declarative rules, deny precedence, owner group ACL inputs, activation/rollback metadata | version pinned, validated, immutable generation; no model-generated rules activated |
| AuthorizationRequestV1 | authenticated request, proposed grant chain, CommandId and side-effect class, ProjectId/resources/fields, source revision, current policy epoch, required consent, budget | all inputs independently verified from owners |
| AuthorizationDecisionV1 | ALLOW/DENY/REQUIRE_CONSENT/UNAVAILABLE, allowed effective scope, policy hash/epoch, grant digest, reason class, decision ID, expiry, obligations, trace | ALLOW is advisory; owner PEP must independently recheck |
| ConsentIntentV1 | owner PlanId/digest, CommandId+normalized args digest, ProjectId, actor+AgentId, source revision, affected owner IDs, target/destination, risk, TTL, request nonce | generated from owner preview, not a prompt |
| ConsentReceiptV1 | intent digest, authenticated trusted UI approver, approved boolean, one-use nonce, grant/policy epoch, expiry, approval signature/MAC ref, issuance time | bound exactly to intended action, consumed atomically on owner commit |
| RevocationEventV1 | GrantId/AgentId, parent chain, ProjectId, new monotonic policy epoch, reason class, actor, event seq/digest, affected pending operations | no reissuance by a revoked child; invalidate cache/cursors/subscriptions |
| AgentAuditEventV1 | event schema+seq, prior hash/checkpoint ref, verified subject/agent/parent pseudo IDs, command/project pseudonym, policy/grant hash, decision/reason, approval ID, owner receipt/trace, source revision, stage/status, timestamp | redacted, access controlled, order and completeness checked |
| SandboxProfileV1 | OS+version, sandbox technology and supported ABI, process identity, allowed owner handles/FDs, filesystem roots, egress rules, CPU/mem/fuel, IPC channels, strict fallback policy | unsupported mandatory capability -> deny untrusted execution |
| AgentSecurityErrorV1 | POLICY_UNAVAILABLE/GRANT_REVOKED/SCOPE_DENIED/CONSENT_REQUIRED/APPROVAL_STALE/OWNER_UNAVAILABLE/SANDBOX_UNSUPPORTED/QUOTA_EXCEEDED, reason class, safe trace | no secret/existence leak |

## 3. Logical API operations (not implemented)
```text
verify_agent_request(AI04VerifiedTransport, OwnerWorkspaceContext)
  -> VerifiedAgentRequestV1 | AUTH_UNAVAILABLE

authorize_command(VerifiedAgentRequestV1, CommandDescriptorV1, OwnerResourceSnapshot)
  -> AuthorizationDecisionV1 | DENY

issue_scoped_grant(TrustedIssuerContext, ExistingActorGrant, RequestedScope)
  -> AgentGrantV1 | DENY

attenuate_grant(VerifiedParentAgent, ParentGrant, ChildAgent, RequestedSubset)
  -> AgentGrantV1 | DENY

revoke_grant(VerifiedOwner, GrantId, ExpectedPolicyEpoch)
  -> RevocationEventV1 | CONFLICT

prepare_consent(OwnerDryRunPlan, VerifiedAgentRequest, riskPolicy)
  -> ConsentIntentV1 | DENY

record_trusted_approval(VerifiedHumanInteraction, ConsentIntentV1)
  -> ConsentReceiptV1 | DENY

consume_consent_at_owner_commit(OwnerCommandPreconditions, ConsentReceiptV1)
  -> oneUseApprovalDecision | DENY

audit_security_event(TypedDecisionOrOwnerReceipt, MinimalRedactedContext)
  -> AuditWriteReceiptV1 | auditFailurePolicy
```

No API above implies AI-06 writes canonical project source, runs scripts, calls shell, forwards OAuth tokens or invokes tools by prompt. Owner source commits remain AI-01/owner actions.

## 4. Authorization and attenuation invariants
**Effective grant** is the intersection of current verified human rights, verified child/parent grant chain, project owner ACL, command/side-effect policy, targeted resource/field, target/destination scope and remaining budget. Any explicit deny or unavailable critical fact overrides allow. Grantee cannot issue or extend their own rights. Only trusted issuer can create a child subset; parent revoke, expiry or policy epoch change invalidates children.

Policy must be **deterministic for fixed verified inputs and version**, with no network dependency for a local offline READ operation. Public metadata must not leak hidden CommandIds/resources before filtering. The policy decision has a short TTL and never authorizes a later stale source revision. Owner must re-evaluate by bound policy epoch before actual read/commit/export and after a change in project selection or ACL.

## 5. Consent binding and lifecycle
```text
OWNER_DRY_RUN -> CONSENT_REQUIRED -> TRUSTED_UI_REVIEW
   -> APPROVED_ONCE or DECLINED -> OWNER_REVALIDATE
   -> OWNER_COMMIT/JOURNAL/READBACK -> audit owner receipt
```
- ConsentIntent includes exact normalized command args digest and owner plan hash, actor/agent/project/resources, revision, side effect, destination, risk class, expiry and nonce. Owner not model creates plan.
- Trusted UI approver must see affected resources, diff, destination and risk. The model cannot call record_trusted_approval or approve itself. MCP MRTR InputRequiredResult only supplies typed missing input and does not replace trusted approval.
- On changed args, target, source revision, risk, grant, policy epoch, owner availability, expiry or replay, fail DENY and require a new owner plan. Approvals are single-use with atomic consume by owner.
- Consent cancellation and task cancellation do not undo committed external side effects. Owner/AI-07 future reconciliation controls recovery; no lie about rollback.

## 6. OS guard and filesystem scope
The VFS/owner resolves ProjectId/AssetId to safe canonical handles, not a string prefix. Agent's raw path argument never directly selects host source file. Future OS sandbox enforces restricted process and narrow I/O broker handles; symlink/junction/mount/hardlink/UNC/case-fold and time-of-check/time-of-use require independent negative tests. If mandatory containment missing on target OS, deny launch; trusted Editor source read is not an exception to untrusted agent executable.

## 7. Audit privacy and policy epoch
Audit must correlate AI-04 transport trace, AI-06 decision and AI-01 owner receipt without copying tokens, source contents or private paths. Per-agent/tenant read ACL for audit. Tamper-evidence (hash chain or signed checkpoints) is hypothetical until keys, persistence, flush and independent readback are implemented and tested. Policy epoch monotonicity and durable revoke should survive restart/crash; if persistent policy cannot be verified, fail closed.

## 8. Failure mapping
| Cause | Expected policy/owner status | Security oracle |
|---|---|---|
| Invalid OAuth issuer/audience/signature | AI-04 HTTP 401/403 as applicable | zero owner dispatch |
| Local stdio unknown OS peer/workspace | AUTH_UNAVAILABLE | no command/URI read |
| No valid grant, wrong project, hidden resource | SCOPE_DENIED safe generic | no unauthorized existence/count/diff |
| Policy engine timeout/invalid bundle | POLICY_UNAVAILABLE / deny | zero privileged side effects |
| Parent grant revoke/expiry | GRANT_REVOKED | child and queued actions denied |
| High-risk command without trusted UI consent | CONSENT_REQUIRED | no owner commit |
| Stale/replayed approval or changed args/destination | APPROVAL_STALE / DENY | no owner commit |
| Project switch/source revision mismatch | SCOPE_DENIED / CONFLICT | no stale commit |
| Unsupported mandatory sandbox primitive | SANDBOX_UNSUPPORTED | no untrusted process launch |
| Audit backend unavailable under strict record-before-commit policy | fail-safe blocking/typed recovery per approved policy | never silently drop required audit and mark PASS |
| Owner unavailable/target unsupported | OWNER_UNAVAILABLE | no fallback raw file/shell |

## 9. Future acceptance
Cross-project and out-of-scope **file and owner state diffs must remain empty** under attacker fixtures; valid bounded authorized operations must still work; no false success on denied tool calls. Measure policy decisions and owner authorization under load without selecting Cedar/OPA/custom yet. Exact 128 future A06 tests and benchmark protocol; no runtime, native API, token or sandbox exists.

[Architecture](../architecture/ai-06-agent-security-authorization.md) · [ADR-0065](../adr/0065-ai-06-agent-grant-consent-policy.md) · [Tests](../testing/ai-06-acceptance-matrix.md).
