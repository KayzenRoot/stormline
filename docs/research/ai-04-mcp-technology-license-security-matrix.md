# AI-04 — MCP Protocol, SDK, Transport, Authorization, Security and License Research

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #293 | NLE-P00-WO-002-AI-04 | code #78 OPEN/BLOCKED | BASE 0cdcef6ae19ba1105667404ed5749ad5155fef0f.** 59/80 researches documented, 21 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency AI-03 ONLY; ADR-0062 PROPOSED; NLE-D009 OPEN; NLE-D015 OWNER-DIRECTED.

## 1. Protocol baseline
| Area | Evidence | Conclusion |
|---|---|---|
| Latest dated spec | [MCP 2026-07-28](https://modelcontextprotocol.io/specification/2026-07-28) and [changelog](https://github.com/modelcontextprotocol/modelcontextprotocol/blob/main/docs/specification/2026-07-28/changelog.mdx) | Proposed modern baseline |
| Protocol core | [Base protocol](https://modelcontextprotocol.io/specification/2026-07-28/basic) | JSON-RPC, server/discover, per-request metadata, MRTR and subscriptions |
| Streamable HTTP | [Transport](https://modelcontextprotocol.io/specification/2026-07-28/basic/transports/streamable-http) | Modern POST-only endpoint; no protocol sessions, GET stream or Last-Event-ID |
| Legacy compatibility | [Versioning](https://modelcontextprotocol.io/specification/2026-07-28/basic/versioning) | 2025-11-25 is a separate handshake-era path |
| Authorization | [Authorization](https://modelcontextprotocol.io/specification/2026-07-28/basic/authorization) | OAuth 2.1 resource-server model, RFC 9728, RFC 8414/OIDC and audience/resource checks |
| Tools | [Tools](https://modelcontextprotocol.io/specification/2026-07-28/server/tools) | object-root input schema, output schema/structured content, untrusted annotations |
| Resources | [Resources](https://modelcontextprotocol.io/specification/2026-07-28/server/resources) | list/read/templates/subscriptions and scoped cache TTL |
| Prompts | [Prompts](https://modelcontextprotocol.io/specification/2026-07-28/server/prompts) | user-controlled prompt selection |
| Tasks | [Tasks extension](https://modelcontextprotocol.github.io/ext-tasks/specification/2026-07-28/tasks.html) | optional durable task handles; get/update/cancel; no list |
| Security | [Security guidance](https://modelcontextprotocol.io/docs/tutorials/security/security_best_practices) | confused deputy, token passthrough, SSRF, local server and metadata threats |
| Conformance | [Official suite](https://github.com/modelcontextprotocol/conformance) | version-specific client/server conformance |

## 2. SDK and runtime candidates (not selected)
| Candidate | Official status | License evidence | Strength | Gap / disposition |
|---|---|---|---|---|
| [TypeScript SDK v2](https://github.com/modelcontextprotocol/typescript-sdk) | Official Tier 1; stable v2 for 2026-07-28; split server/client packages | New code/spec contributions Apache-2.0; some older contributions remain MIT; docs CC-BY-4.0 | current spec, stdio/HTTP, Node/Bun/Deno, middleware | exact tag, file-level SPDX, runtime and Tasks proof required |
| [TypeScript Tasks extension](https://github.com/modelcontextprotocol/ext-tasks) | official optional package for SDK v2 | exact tag/transitives must be checked | Tasks client lifecycle | does not supply Stormline durable owner job or ACL |
| [Python SDK v2](https://github.com/modelcontextprotocol/python-sdk) | Official Tier 1; v2.0.0 supports 2026-07-28 and earlier era | MIT | stdio/HTTP, client/server and fixtures | current roadmap says Tasks extension not implemented; runtime footprint |
| [Official SDK index](https://modelcontextprotocol.io/docs/sdk) | TypeScript, Python, C# and Go Tier 1; Java Tier 2 | each SDK separate | maintained protocol implementations | C++ is not listed Tier 1 in current table |
| [Rust SDK](https://github.com/modelcontextprotocol/rust-sdk) | official project | repository license transition; exact file/tag audit needed | async server and modern/legacy support | tier/host/platform maturity not established for Stormline |
| Custom server | no SDK | project-owned | control | reject unless measured SDK gap justifies maintenance/security burden |

TypeScript SDK v1 is the maintenance line for older protocol and is not the 2026 implementation. Python SDK v2 current roadmap explicitly reports missing Tasks extension. Recheck tags, license and feature support before adoption.

## 3. Transport and protocol differences
| Behavior | 2026-07-28 | 2025-11-25 | Test |
|---|---|---|---|
| Discovery | server/discover | initialize | recognized fallback |
| Version | per-request metadata | handshake-negotiated | no silent downgrade |
| HTTP | POST only | POST + GET stream | version-specific behavior |
| Session | none | optional session ID | no state bleed |
| Notifications | subscriptions/listen | legacy notification/session model | no unrequested events |
| Server asks client | MRTR input_required | server-initiated request | no spontaneous modern request |
| Tasks | optional extension | older experimental form differs | negotiate and pin wire version |
| 2024-11-05 HTTP+SSE | deprecated | old transport | no accidental fallback |

Modern HTTP requires MCP-Protocol-Version to match request metadata; Mcp-Method and applicable Mcp-Name mirror headers must match the JSON-RPC body.

## 4. Authorization and security standards
| Standard/control | Application |
|---|---|
| OAuth 2.1 | HTTP resource-server model |
| RFC 9728 | publish Protected Resource Metadata |
| RFC 8414 / OIDC | discover and validate authorization-server issuer |
| RFC 8707 | token audience/resource must be this MCP server |
| RFC 9207 | issuer identification for client auth response |
| PKCE S256 | required for any future built-in public client flow |
| CIMD | preferred current client registration direction |
| RFC 7591 DCR | deprecated fallback only |
| Origin/CORS | strict allowlist, reject invalid Origin, no wildcard credentials |
| OWASP SSRF | no arbitrary remote URI fetch or external credential forwarding |
| OpenTelemetry | trace/metric correlation with secret redaction |

Never accept a bearer token intended for another resource, forward it unchanged downstream, or authorize from client name, prompt or tool annotation. Each HTTP request validates issuer, signature, expiry, audience/resource, scopes and current project/owner policy. Local stdio also enforces OS user/project boundaries.

## 5. Semantic pitfalls
- Tool inputSchema is a JSON object schema; AI-03 remains source of truth.
- outputSchema and structuredContent must agree; text serialization may be needed for compatibility.
- Tool annotations are untrusted hints, not authority.
- Resource ttlMs/cacheScope are modern cache fields; private by default and scoped by actor/project/policy epoch/revision.
- Prompt selection is user-controlled; prompt contents cannot execute or authorize.
- Resource URIs are opaque Stormline IDs, never arbitrary file paths/URLs.
- MRTR is input, not permission receipt.
- Task IDs must be unguessable and checked every request; no tasks/list.

## 6. Reliability and performance
Modern stateless HTTP can scale without sticky protocol sessions, but project and job consistency remain owner responsibilities. Request IDs are correlation only. Broken SSE response may lose in-flight request; reissue with a new ID. Mutation retries require AI-01 idempotency and revision CAS. Cancellation is best effort and does not imply rollback. Bound JSON depth, frames, body/output bytes, concurrency, rate, pagination, resources, subscription duration, tasks, queue and deadlines. Measure startup, list/call, throughput, tail latency, memory, context bytes, cache and recovery.

## 7. License register
MCP specification, SDK code, conformance harness and extension packages have separate license/notice obligations. TypeScript SDK repository documents MIT-to-Apache-2.0 transition; do not label all files under one license without exact file-level SBOM. Python SDK currently declares MIT. Tasks package and Rust SDK require exact tag/license/transitive audit. No candidate installed or selected; NLE-D009 remains OPEN.

## 8. Sources
[MCP spec](https://modelcontextprotocol.io/specification/2026-07-28) · [Authorization](https://modelcontextprotocol.io/specification/2026-07-28/basic/authorization) · [Streamable HTTP](https://modelcontextprotocol.io/specification/2026-07-28/basic/transports/streamable-http) · [Tasks](https://modelcontextprotocol.github.io/ext-tasks/specification/2026-07-28/tasks.html) · [SDK index](https://modelcontextprotocol.io/docs/sdk) · [Conformance](https://github.com/modelcontextprotocol/conformance).
