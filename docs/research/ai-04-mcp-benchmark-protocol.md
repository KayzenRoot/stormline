# AI-04 — Reproducible MCP Conformance, Host Interoperability, Latency and Resource Benchmark

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #293 | NLE-P00-WO-002-AI-04 | code #78 OPEN/BLOCKED | BASE 0cdcef6ae19ba1105667404ed5749ad5155fef0f.** 59/80 researches documented, 21 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency AI-03 ONLY; ADR-0062 PROPOSED; NLE-D009 OPEN; NLE-D015 OWNER-DIRECTED.

**FUTURE protocol only. 0 server builds, 0 conformance runs, 0 host certifications, 0 measurements.** Thresholds TBD until exact implementation, target hardware and workload are measured and owner-approved.

## Baseline evidence to pin
Git base/head; AI-03 generation/schema digest; AI-01 owner API revision; MCP version per run (2026-07-28 modern, 2025-11-25 only if claimed); official conformance suite commit/package and suite mode; SDK/tag/runtime/lockfile/SBOM/SPDX/license/CVE; transport profile, response mode, Origin, TLS and OAuth fixtures; host name/version and negotiated protocol; OS/arch/CPU/RAM/network RTT; synthetic action inventory and actor/project/grant/policy epoch. No real credentials or user project data.

## Future workload matrix
| Workload | Dataset | Purpose |
|---|---|---|
| MCP-C0 | 10 tools, 5 resources, 3 prompts | cold start/discovery |
| MCP-S | 100 tools, 20 schemas, 100 resources, 20 prompts, 3 principals, 2 projects | baseline |
| MCP-M | 1,000 tools, 2,000 schemas/resources, 32 principals, 16 projects, 8 hosts | realistic scale |
| MCP-L | 10,000 tools/resources and high concurrency | stress only |
| MCP-P | large prompt/resource payloads and many cursors | context bytes/cache |
| MCP-H | malformed JSON-RPC, recursive schema, oversized frames, malicious Origin/URI, token/prompt injection | adversarial limits |
| MCP-R | 2025/2026 versions and extension combinations | compatibility/downgrade |
| MCP-T | concurrent calls, subscriptions, optional durable tasks, cancellation/recovery | throughput/reliability |

All fixtures synthetic, rights-cleared and deterministic, with independent ACL oracle and negative controls for hidden commands/resources.

## Future measurements
| Benchmark | Procedure | Metrics |
|---|---|---|
| B01 startup | cold/warm stdio launch, discovery and first list | startup p50/p95, time-to-ready, CPU, peak RSS |
| B02 discovery | discover, tools/list, resources/list, prompts/list | p50/p95/p99, bytes, allocations, pages |
| B03 tool call | read-only and owner-approved idempotent mutation | adapter overhead vs direct AI-01, end-to-end tails |
| B04 auth | token validation, filtering, denied/revoked calls | latency, cache hit/miss, unauthorized dispatch = 0 |
| B05 HTTP | JSON/SSE under controlled RTT/concurrency | throughput, tail latency, connections, RSS |
| B06 subscriptions | multiple listeners and bounded fanout | delay, queue depth, drops, memory/listener |
| B07 Tasks | durable create/poll/update/cancel/restart, only if implemented | handle durability, poll rate, recovery, ACL |
| B08 resources | public/private cache and policy/source revision invalidation | cache hit/miss, stale reads, bytes, ACL leaks = 0 |
| B09 compatibility | same scenarios modern and legacy | conformance, fallback decisions, result equivalence |
| B10 hosts | pinned Codex/Claude real workflows | negotiation, visibility, errors, cancellation, UX |
| B11 stress | burst/steady traffic and malformed flood | p50/p95/p99, CPU/RSS, rejection, queue |
| B12 recovery | kill process, sever stream, restart owner, rotate policy | recovery, lost notifications, duplicate mutation, stale cache |

## Procedure
At least five clean repetitions per environment after documented warmup; cold/warm separately. Capture raw samples; report p50/p95/p99 only when sample count supports resolution. Compare adapter latency with direct AI-01 owner call. Fix payload/page/schema/auth fixtures. Mutations use unique request IDs and stable owner idempotency IDs. HTTP runs record RTT/TLS/Origin/response mode/worker count. Tasks honor server poll interval. Approve numeric budgets only after target-tier baseline. Fast but insecure/incorrect fails; conformance does not prove Stormline authorization or host usability.

## Receipt
Record base/head, AI-03 digest, AI-01 revision, spec version, conformance commit/suite mode, SDK/runtime/license SBOM, host and negotiated version, transport, OS/arch/CPU/RAM/network, fixture seed, principal scope/policy epoch, request/success/denied counts, unauthorized owner dispatch, duplicate mutations, latency samples, peak RSS, CPU, bytes, cache hit/miss, subscription drops, task recovery, trace digest and verdict. No values invented in P00.

[Conformance suite](https://github.com/modelcontextprotocol/conformance) · [MCP spec](https://modelcontextprotocol.io/specification/2026-07-28) · [TypeScript SDK](https://ts.sdk.modelcontextprotocol.io/v2/) · [Python SDK](https://py.sdk.modelcontextprotocol.io/) · [Tasks extension](https://modelcontextprotocol.github.io/ext-tasks/specification/2026-07-28/tasks.html).
