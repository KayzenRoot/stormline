# AI-04 — Proposed MCP Adapter Profiles, Projection and Transport Contracts v0.1

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #293 | NLE-P00-WO-002-AI-04 | code #78 OPEN/BLOCKED | BASE 0cdcef6ae19ba1105667404ed5749ad5155fef0f.** 59/80 researches documented, 21 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency AI-03 ONLY; ADR-0062 PROPOSED; NLE-D009 OPEN; NLE-D015 OWNER-DIRECTED.

**Logical contracts only; not compiled headers, active endpoints or an adopted SDK.**

## 1. Proposed types
| Type | Fields | Invariant |
|---|---|---|
| McpAdapterProfileV1 | adapter ID/semver, supported protocol versions, default version, enabled transports, AI-03 registry ref, AI-01 dispatch ref, optional resource/prompt ports, policy port, telemetry profile | advertise only versions passed by pinned conformance |
| McpTransportConfigV1 | transport, explicit enabled flag, bind profile, endpoint ID, Origin allowlist, TLS profile, body/response caps, concurrency/deadline, allowed versions, optional auth profile | STDIO opens no network endpoint; remote HTTP opt-in |
| McpRequestContextV1 | JSON-RPC ID, protocol version, transport, verified OS peer, principal/project/grant, policy epoch, target, deadline, trace ID, untrusted client metadata and declared capabilities | clientInfo never fills identity or permission |
| McpToolProjectionV1 | stable tool name, AI-01 CommandId, owner module, command version, AI-03 input/output schema refs, safe description, untrusted annotations, visibility, targets, deprecation | one tool name maps to one stable owner descriptor |
| McpToolCallV1 | tool name, JSON arguments, verified request context, negotiated version | validate then dispatch only through AI-01 |
| McpResourceProviderPortV1 | authorized list/templates/read/subscribe with cursor and byte/page budgets | AI-05 may implement later; no arbitrary path/URL |
| McpPromptProviderPortV1 | authorized list/get with stable prompt ID and typed args | user-controlled content, no authority |
| ProtectedResourceProfileV1 | canonical MCP origin, RFC 9728 metadata URI, trusted issuers, scopes per operation, audience, Origin allowlist | bearer token is for this resource and revalidated each request |

## 2. Discovery and era negotiation
Modern server implements server/discover and returns supported versions, server info, capabilities and explicitly supported extensions. Every modern request carries protocol version and required client capabilities in request metadata. Legacy initialize is a separate 2025-era path.

For modern HTTP, MCP-Protocol-Version must match request metadata; required Mcp-Method and applicable Mcp-Name mirror headers are validated against parsed body. Header mismatch is rejected. A recognized modern unsupported-version error triggers supported-version negotiation, not legacy fallback.

## 3. Tool projection and dispatch invariants
- Tool name resolves to exactly one AI-03 CommandId/major version under current generation.
- Adapter validates MCP input schema; owner validates again before execution.
- AI-01 rechecks actor, project, grant, policy epoch, source revision, preconditions and idempotency.
- MCP request ID is not idempotency key; no mutation retry without owner idempotency.
- InputRequiredResult is typed missing input, not grant or consent.
- Task result only if client declared Tasks extension and owner job is durable/queryable/authorized.

## 4. Resource and prompt ports
Resource URIs are opaque Stormline IDs; no raw host path/URL. AI-04 maps provider outcomes to MCP resources/templates/prompts. AI-05 may implement provider later. Cache key binds project, actor, policy epoch, content revision and representation. Private by default. Prompt content is user-controlled and non-authoritative.

## 5. Authorization and error mapping
Each protected HTTP request validates token issuer, signature, expiry, audience/resource and scopes. Publish RFC 9728 metadata. Never pass incoming bearer token downstream. Local stdio derives peer context from controlled process launch and owner workspace policy, not client name.

| Condition | Wire behavior | Recovery |
|---|---|---|
| malformed JSON-RPC/metadata | invalid request/params; HTTP 400 where applicable | correct request; no handler |
| unsupported modern version | spec error and supported list | retry supported version only |
| header/body mismatch | protocol mismatch error, HTTP 400 | correct header/body |
| unknown method | method-not-found | use negotiated methods |
| missing/invalid token | HTTP 401 with metadata challenge | authenticate to this resource |
| insufficient scope | HTTP 403 with scope challenge | least-privilege additional scope |
| capability not visible | safe generic denial | no command-existence leak |
| invalid schema | stable validation error | correct typed arguments |
| owner conflict/stale revision | typed conflict/receipt | refresh and preview |
| owner unavailable/target unsupported | typed unavailable | no fake fallback |
| deadline/quota | bounded backpressure/timeout | retry only safe/idempotent |
| task missing/revoked | generic not-found/denied | no task enumeration |

Never return stack traces, tokens, private paths, internal handler addresses or secret arguments.

## 6. Version, cancellation and idempotency
Modern and legacy eras are separate protocol implementations sharing one owner port. No downgrade on recognized modern error. Cancellation is best-effort and owner receipt determines whether work committed. Retry only safe reads or owner-declared idempotent operations. Reauthorize subscriptions and task polling/delivery; invalidate cache/cursor/task on policy epoch change.

[Architecture](../architecture/ai-04-mcp-server-protocol-adapter.md) · [ADR-0063](../adr/0063-ai-04-stateless-mcp-adapter.md) · [128 tests](../testing/ai-04-acceptance-matrix.md).
