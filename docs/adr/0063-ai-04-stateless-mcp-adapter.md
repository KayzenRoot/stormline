# ADR-0063 — AI-04 Stateless MCP Adapter, Dual-Era Compatibility and Owner-Only Dispatch

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #293 | NLE-P00-WO-002-AI-04 | code #78 OPEN/BLOCKED | BASE 0cdcef6ae19ba1105667404ed5749ad5155fef0f.** 59/80 researches documented, 21 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency AI-03 ONLY; ADR-0062 PROPOSED; NLE-D009 OPEN; NLE-D015 OWNER-DIRECTED.

**STATUS: PROPOSED / NOT OWNER-APPROVED / NOT ADOPTED / NO CODE AUTHORIZATION.**

## Context
Stormline requires Codex, Claude and compatible hosts to access the same approved public authoring operations as Editor/CLI through a versioned adapter. AI-03 derives validated capability descriptors from AI-01. MCP 2026-07-28 changes transport, lifecycle, discovery and server/client interaction compared with 2025-11-25. Older stateful tutorials must not define the new primary architecture.

## Proposed decision
1. AI-04 is a protocol-only adapter over AI-03 projections and AI-01 owner dispatch. It never becomes a second command bus, authorization root, project database or handler registry.
2. MCP 2026-07-28 is modern/stateless baseline: server/discover, per-request metadata/version validation, request-scoped transport, subscriptions/listen and MRTR.
3. Local default is stdio through a dedicated process with protocol-clean stdout. The exact local IPC and implementation language remain unselected.
4. Remote Streamable HTTP is opt-in only. Origin validation, strict CORS, TLS ingress, Protected Resource Metadata and per-request token audience/issuer/scope checks are mandatory.
5. 2025-11-25 compatibility is separate and evidence-backed. Never silently downgrade on recognized modern errors. 2024-11-05 HTTP+SSE is not enabled by default.
6. MCP tools derive from AI-03 descriptors; every call dispatches the same AI-01 CommandId with owner-side permission, revision and idempotency checks. Annotations and client identity metadata are untrusted.
7. Resource/template and prompt provider ports may later be supplied by AI-05; no new formal dependency and no duplicated content catalog. Prompt use remains user-controlled.
8. MRTR is missing-input exchange, not consent. High-risk approval remains owner-bound and separately validated.
9. Tasks is optional. Expose only with durable owner JobHandle, per-request client extension capability and per-operation authorization. No task list.
10. SDK selection is deferred. Compare official Tier 1 TypeScript/Python SDKs, exact versions, licenses, CVEs, runtime footprint, packaging and conformance. TypeScript v2 has a separate Tasks package; current Python v2 roadmap reports Tasks extension not implemented.
11. Roots, sampling and logging remain deprecated in modern 2026 design. Use request metadata and OpenTelemetry.
12. No implementation, release class, SDK, license, OAuth provider or network topology is approved. NLE-D009 remains OPEN; all 80 code packets remain BLOCKED.

## Alternatives
- **2025-11-25 stateful MCP primary:** rejected because latest spec removes protocol sessions, GET event stream and server-initiated requests. Keep only proven compatibility.
- **2024-11-05 HTTP+SSE:** rejected by default because deprecated and adds separate lifecycle.
- **SDK linked into C++ engine core:** rejected because it couples engine core to third-party protocol/runtime/auth and violates core/editor/server separation.
- **Custom MCP implementation:** not selected due conformance/security/version drift risk; reconsider only if official SDKs fail measured requirements.
- **TypeScript SDK v2 now:** not adopted; official Tier 1/current but runtime, license transition, packaging and Tasks integration need proof.
- **Python SDK v2 now:** not adopted; official Tier 1/MIT but runtime footprint and current Tasks gap need proof.
- **Sticky session per project:** rejected for modern stateless HTTP.
- **Trust client name, annotation or prompt to authorize:** rejected.
- **Expose engine functions as generic shell/filesystem tools:** rejected.

## Consequences and risks
Benefits: model-neutral access, protocol isolation, no engine-core MCP dependency, stateless remote scaling, shared semantic authority and measurable interoperability. Costs: dual-era adapters, secure resource-server configuration, local process packaging, provider ports, host matrix and conformance maintenance. Risks: SDK lag, host variance, Origin/OAuth errors, prompt injection, downgrade, task durability, cache/subscription leakage. Mitigate with version-specific conformance, fail-closed fallback, least privilege, owner validation, security fuzzing and exact license/SBOM.

## Acceptance / ratification gate
- AI-03 and AI-01 descriptors/dispatch approved and implemented separately.
- Exact 2026-07-28 conformance passes for each claimed transport; 2025-11-25 only if claimed.
- Pinned Codex/Claude matrix proves actual negotiated version and tools/resources/prompts behavior.
- Origin/DNS-rebinding/OAuth audience/issuer/token-passthrough and cross-project tests pass.
- 128 future A04 tests implemented and passed.
- Exact SDK tag/license/SBOM/CVE, runtime distribution and Windows/Linux/macOS evidence approved.
- Benchmarks measured and thresholds approved; independent audit/evidence/rollback/checkpoint accepted.

Until those gates and owner decision, ADR remains **PROPOSED** and code #78 remains **OPEN/BLOCKED**.

[Architecture](../architecture/ai-04-mcp-server-protocol-adapter.md) · [Technology matrix](../research/ai-04-mcp-technology-license-security-matrix.md) · [Contracts](../contracts/ai-04-mcp-server-contracts.md).
