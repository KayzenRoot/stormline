# AI-04 — MCP Server & Protocol Adapter Architecture v0.1

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #293 | NLE-P00-WO-002-AI-04 | code #78 OPEN/BLOCKED | BASE 0cdcef6ae19ba1105667404ed5749ad5155fef0f.** 59/80 researches documented, 21 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency AI-03 ONLY; ADR-0062 PROPOSED; NLE-D009 OPEN; NLE-D015 OWNER-DIRECTED.

## Goal and boundary
AI-04 is the model-neutral MCP protocol edge for Codex, Claude and compatible hosts. It owns protocol lifecycle, JSON-RPC mapping, transport, version negotiation, tools/resources/prompts projection, request validation, safe errors and host conformance evidence. Catalog acceptance: MCP conformance tests and interaction with selected hosts. This is research only; no server, SDK, listener, OAuth provider or host integration exists.

## Ownership graph
MCP hosts -> AI-04 protocol adapter -> AI-03 capability descriptors/schemas -> AI-01 command kernel -> engine module owners.

**Formal predecessor: AI-03 only.** AI-03 already depends on AI-01. AI-05 resources/templates, AI-06 agent authorization, AI-07 transaction planning and CORE-06 observability are future integrations, not new formal edges.
- AI-01 owns CommandId, invocation, owner dispatch, transaction preconditions, permissions and receipts.
- AI-03 owns public capability descriptors, schemas, versions and permission projections.
- AI-04 owns MCP wire names, transports, protocol lifecycle, compatibility and client-facing errors. It must never create a second executor, registry or permission root.
- AI-05 may later supply resource/prompt providers; AI-04 defines bounded ports only.
- AI-06 may later supply grant lifecycle; until then missing/stale identity or policy context fails closed.
- AI-07 may later supply durable changesets and undo. MCP request/task IDs are not transaction IDs or approval receipts.

## Protocol baseline
Latest dated specification found on 2026-11-15: **MCP 2026-07-28**. Proposed support:
1. Modern 2026-07-28 stateless path as primary.
2. 2025-11-25 handshake-era compatibility only where pinned conformance and selected-host evidence proves value.
3. 2024-11-05 HTTP+SSE, drafts and unspecified old versions unsupported by default.

Modern path uses server/discover and per-request metadata, not an initialize handshake or connection-scoped session. clientInfo/serverInfo are display/debug metadata, never security identity. Modern unsupported-version errors trigger supported-version negotiation, never silent legacy downgrade. Legacy lifecycle is isolated from modern lifecycle.

| Surface | Modern 2026-07-28 | Legacy 2025-11-25 | Proposed policy |
|---|---|---|---|
| stdio | server/discover; per-request metadata | initialize handshake | probe modern, fallback only on unrecognized legacy response |
| Streamable HTTP | POST endpoint; no protocol session; request-scoped JSON/SSE; subscriptions/listen | POST + GET stream, optional session ID | separate protocol-era paths |
| HTTP+SSE 2024-11-05 | deprecated | legacy transport | disabled by default |

## Transport topology
### Local stdio
Host launches a dedicated Stormline MCP process. stdin/stdout carry only valid UTF-8 JSON-RPC frames; logs and diagnostics go to stderr. No network listener or internet access is assumed. The adapter reaches the command gateway through a narrow typed local port. IPC choice (in-process, named pipe, Unix socket or other authenticated local channel) is not selected. Bind to active OS user/project context; no arbitrary paths, shell or engine pointers.

### Remote Streamable HTTP
Explicitly enabled by owner/operator. For modern 2026, POST only; request-scoped JSON or SSE; long-lived opted-in notifications through subscriptions/listen. For 2025 compatibility, exact legacy session/GET/SSE behavior is separate. Validate Origin on every incoming request, return 403 for invalid Origin, strict CORS allowlist, no credentialed wildcard, local bind loopback, remote HTTPS/TLS ingress and explicit authentication. MCP-Protocol-Version must match body protocol metadata; Mcp-Method and applicable Mcp-Name mirror headers must match parsed JSON-RPC. No sticky session for stateless path.

## Tools
tools/list projects only AI-03 descriptors visible to verified principal/project/target. Stable tool name maps to one AI-01 CommandId and version; deterministic pagination/cursors. inputSchema derives from AI-03 and is an object schema. outputSchema and structuredContent must agree. Tool annotations are untrusted hints, never grants or policy. tools/call validates schema, binds verified context, dispatches through AI-01, and returns owner receipt. Owner rechecks authorization, project, revision and idempotency. No direct handler bypass or automatic retry of unsafe mutation.

## Resources and prompts
resources/list, resources/templates/list, resources/read and subscriptions project bounded provider ports; AI-05 owns future content. Use opaque stormline:// IDs bound to project/asset/revision, never file://, arbitrary paths or remote fetch. Authorize before list, counts, cursors, hydration and cache. Cache keys bind actor/project/policy epoch/revision; private by default. Resource bytes, MIME, TTL and page sizes are bounded.
prompts/list/get project curated recipes. Prompt use is user-controlled and explicitly selected. Prompt text, descriptions and examples are untrusted context, not authority; no automatic privileged execution or permission widening.

## MRTR, subscriptions and Tasks
2026 MRTR returns InputRequiredResult with inputRequests; client returns inputResponses on retry. This is missing-input exchange, not consent. High-risk action still requires owner-bound approval receipt bound to actor/project/command/revision/expiry and revalidated by AI-01.
subscriptions/listen is client-opted; send only requested notification types/URIs. Disconnect may lose in-flight notifications; client re-reads authoritative revision.
Tasks extension io.modelcontextprotocol/tasks is optional. Client must advertise it per request; server may return a durable task handle only when owner JobHandle is persistent, queryable, cancellable and ACL-bound. Methods get/update/cancel; no list. Every task request reauthorizes; high-entropy task IDs. Without durable owner job support, do not advertise Tasks.

## Authorization and trust
For protected HTTP, publish RFC 9728 Protected Resource Metadata and validate token signature, issuer, expiry, audience/resource and scopes on every request. Never pass client bearer tokens downstream. Authorization-server discovery uses RFC 8414/OIDC; CIMD is current registration direction, DCR deprecated fallback. AI-04 is not an OAuth authorization server. Local stdio still enforces OS user/project boundaries. Never trust clientInfo, serverInfo, tool annotations, prompt text or request IDs as identity/permission.

## Reliability, errors and observability
JSON-RPC errors for protocol failures; typed tool results for owner failures. Stable codes, correlation IDs, safe diagnostics. Bound JSON depth, bytes, pages, concurrency, rate, deadlines, subscriptions, task count and queue. Cancellation is best-effort and does not imply rollback. Retry only safe reads/idempotent operations; mutation idempotency belongs to AI-01. Trace protocol version, transport, method, owner command, pseudonymous project, decision class, duration and bytes. Redact tokens, secrets, arguments and paths. Use OpenTelemetry-compatible traces/metrics. Roots, sampling and logging are deprecated in 2026-07-28.

## Threat model
| Threat | Control |
|---|---|
| DNS rebinding / malicious Origin | strict Origin validation, 403, loopback local bind, explicit remote |
| token audience confusion / passthrough | resource audience/issuer validation; never forward bearer token |
| cross-project enumeration | actor/project/target filtering before counts, cursors, cache and hydration |
| prompt/tool poisoning | metadata untrusted; policy owner-side |
| path traversal / local exfiltration | opaque project URI; VFS owner reads only |
| SSRF | no arbitrary fetch; allowlisted schemes/origins |
| stdio framing injection | JSON-RPC-only stdout, stderr logs, bounded UTF-8 |
| replay / duplicate mutation | owner idempotency and revision CAS |
| task ID theft | entropy, no list, auth on every operation |
| resource exhaustion | parser, bytes, deadlines, concurrency and response caps |
| downgrade/header spoof | validate header/body; modern errors never trigger fallback |
| cache/subscription leak | per-principal scope and policy epoch invalidation |

## Platform and non-goals
Windows x64, Linux x64 and macOS Apple Silicon desktop/headless hosts; remote deployment separate. No GPU dependency. No model provider, prompt orchestration engine, OAuth authorization server, generic shell/filesystem/network tool, project resource database, durable job engine, transaction planner, raw GPU/VM/driver interface or production endpoint. No Codex/Claude certification without exact host evidence.

[ADR-0063](../adr/0063-ai-04-stateless-mcp-adapter.md) · [Contracts](../contracts/ai-04-mcp-server-contracts.md) · [128 tests](../testing/ai-04-acceptance-matrix.md) · [Benchmark](../research/ai-04-mcp-benchmark-protocol.md).
