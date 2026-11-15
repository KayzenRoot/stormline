# AI-05 — Reproducible Minimal-Context, Provenance, Freshness and Security Benchmark Protocol v0.1

**2026-11-15 | P00 FUTURE BENCHMARK ONLY | [research #297](https://github.com/KayzenRoot/stormline/issues/297) | NLE-P00-WO-002-AI-05 | code #79 OPEN/BLOCKED | BASE `ec1a8efc89de6e90d53f7b56fd31bc874335a2ff`.** Dependencies AI-02 + AI-04 research-only; zero engine, index, MCP server, host test or benchmark implemented; no numeric performance targets approved.

## 1. Acceptance question and falsifiable hypothesis
**Question:** Can an authorized agent find exact scene/asset/script/schema/document context needed for a task through a few paginated resources and typed URI templates without copying entire project/repository? Compare a progressive Context Capsule workflow against a **rights-equivalent baseline** that reads all relevant authorized source data. Report whether context content covers independently labeled ground truth with acceptable citation accuracy, latency, freshness, security and byte/token budgets. The design is a candidate, not a proven win.

Do not count ACL-excluded bytes as savings unless the comparator also excludes them; that would be an unfair and dangerous benchmark. No unverified superiority vs alternative game engines, indexers, SDKs or host models.

## 2. Required pinned environment
- Git base/head/branch, AI-05 contract and ADR SHA, AI-02 index generation/schema/tokenizer, owner committed ProjectId/AssetId/SceneRevision/source digest vectors; AI-04 protocol and transport, SDK exact tag/runtime/lockfile.
- MCP 2026-07-28 spec and official conformance suite version/commit. For 2025-11-25, separate negotiated-era report only if supported.
- Codex/Claude/other selected real host version and negotiated capabilities; no generic MCP client passed off as host certification.
- Windows x64, Linux x64 and macOS Apple Silicon OS/version, CPU cores, RAM, filesystem, CPU budget; remote profile network RTT/throughput/ingress and local stdio process packaging.
- Deterministic synthetic fixture seed, scene/asset/script schema counts, file sizes, character set, layout, source symbol map, graph edges, controlled grants and rights/provenance/PII labels.
- An independent owner truth catalog and expected answer set for each query, including hidden assets/cross-project distractors, tombstones and source revisions. AI-02's own index is not ground truth.
- Exact tokenizer ID if token exactness is claimed. Otherwise report `estimatedTokens` with approximation policy/version; actual UTF-8 bytes are authoritative.

## 3. Synthetic workload tiers
| Fixture | Size and content | Scenario |
|---|---|---|
| CX0 | 1 project, 10 scenes, 100 assets, 10 docs, 10 scripts, 1 schema | cold discover, template, read |
| CXS | 1 project, 100 scenes, 1k assets, 100 docs, 100 scripts, Unicode and 10% hidden data | normal browse, selected context, ACL filtering |
| CXM | 10 projects, 10k assets/refs, 1k scenes, 5k script symbols, 2k docs and 64 schemas | multi-project, freshness and exact-citation workloads |
| CXL | 100k source entries across project graphs, high churn, multiple owners, CJK/emoji | stress-only, not assumed normal product size |
| CXR | 10k entries with schema owner missing, AI-02 lag and ACL revocation | partial/stale rights correctness |
| CXP | 1k curated prompts/templates, safe Unicode and malicious injected documents | prompt arguments, safe serialization, completion |
| CXS-ATTACK | symlink/path traversal, encoded slash, bidi, XML/Markdown/HTML injection, hidden secrets, rights-restricted asset | negative security with zero unauthorized reads/network calls |
| CXHOST | same rights-cleared task set on pinned Codex, Claude and generic MCP SDK | negotiated host compatibility and UX |

## 4. Independent task corpus and baseline
Use 50+ labeled tasks spanning scene hierarchy, asset provenance/reference, script symbol locator, schema/property lookup, authoring doc excerpts, recipe selection, and unsupported/denied resources. Each task has fixed expected source IDs, revision/digests and valid excerpt ranges. Include distractors with similar names, renamed assets, deleted/tombstoned sources and restricted third-party material. Run:
- **BASELINE:** read all task-eligible *authorized* source material in a deterministic manner within the same project and owner revisions; measure its actual bytes and, where possible, model-specific tokens. Do not attempt forbidden export or breach quotas.
- **AI05 PROPOSAL:** resources/list + templates/list + one or more exact named resources/read + bounded AI-02 context pack; each read carries source revision, citations and budgets. Include discovery metadata, pagination overhead and error/partial responses in byte accounting.
- Both runs use the same principal, rights policies, source snapshots, tokenizer/ranking policy and task answer criteria. Do not hide source/index rebuild cost or LLM retrieval choice overhead; report cold/warm separately.
- If full dump exceeds safety/rights limits, report **BASELINE NOT RUN** and compare against a safe bounded surrogate, never substitute fabricated savings.

## 5. Benchmark matrix
| ID | Measurement / procedure | Oracle / metrics |
|---|---|---|
| CX-B01 | cold MCP resource inventory and first useful resource | time-to-first-context, bytes, p50/p95/p99 where sample size supports |
| CX-B02 | first and subsequent resource/template pages | rows/bytes/page, duplicate/omitted IDs, cursor validity, CPU/RSS |
| CX-B03 | exact scene/asset/script/schema read with citations | source ID/revision/digest match rate, owner read count, source age |
| CX-B04 | targeted context vs rights-equivalent full-project baseline | bytes transferred, estimated tokens, context reduction ratio when valid |
| CX-B05 | labeled semantic discovery task quality | recall@k, precision@k, MRR/nDCG@k, exact citation precision |
| CX-B06 | owner source edit and AI-02 incremental refresh | source commit-to-readable latency, unrelated reindex count, stale/error rates |
| CX-B07 | auth grant revoke during browse/read/completion | unauthorized read/bytes/count/suggestions = 0; stale cursor denial |
| CX-B08 | prompts/list and get with user-selected recipe | args validation, prompt bytes, user-selected proof, no tool dispatch |
| CX-B09 | completion/complete prefix probing under ACL | max 100 values, safe count, latency, hidden match leakage = 0 |
| CX-B10 | URI fuzz / traversal/SSRF and prompt injection corpus | zero file/network/command side effects, bounded error latency |
| CX-B11 | concurrent 1/8/32 callers across 10 projects | p50/p95/p99, RSS/CPU, private cache collision and policy isolation |
| CX-B12 | cache hints, source revision invalidation and subscription drop | ttlMs/cacheScope correctness, stale read rejection and authoritative re-read |
| CX-B13 | 2026-07-28 resources/templates/prompts conformance + optional 2025 | suite cases passed, exact suite SHA, negotiated feature matrix |
| CX-B14 | pinned Codex/Claude workflow on Windows/Linux/macOS | host/OS/transport compatibility, user recipe and resource read |
| CX-B15 | owner index missing/corrupt/stale and partial owners | honest coverage/partial error, no synthesized source, recovery |
| CX-B16 | model-agnostic versus pinned-tokenizer context accounting | exact UTF-8 byte count, tokenizer estimate error distribution |

## 6. Execution procedure and statistics
- Run cold and warm in controlled order, fixed fixture seed, immutable source snapshots and per-task rights. Clear only derived cache, never canonical DATA-02 assets. Record index build/reindex separately from read latency.
- At least 5 isolated repetitions per fixture and enough requests for meaningful p95/p99; do not show p99 from a tiny sample as precision. Keep raw timing samples, mean/stddev and max resource use.
- Collect per-request full wire bytes (not just text snippet), number of calls/pages, omitted/hidden/unsupported counts, committed owner revision and AI-02 generation. Pin scoring/ranking and Unicode policy.
- Profile cold start, CPU, peak RSS, disk/WAL if AI-02 uses SQLite, source owner hydration requests, auth checks and context formatting allocations. Do not conflate MCP transport overhead with AI-02 owner read latency.
- Use synthetic principals to exercise granted, denied, revoked mid-stream and cross-project impersonation. No real tokens, private repos, customer projects or licensed content in fixtures.
- Treat no unauthorized source material, no arbitrary network/host path access, no fake fresh citations and no prompt-driven tool execution as hard pass/fail security obligations regardless of performance.
- Before any numeric budget or library adoption, record target hardware tier, exact SDK/library version/license, target OS and evidence. If an SDK lacks a required 2026 feature, mark unsupported and do not claim compliance.

## 7. Future evidence receipt
```text
A05BenchmarkReceiptV1 {
  base_sha, head_sha, source_pack_fingerprints, ai05_contract_digest,
  ai02_index_generation, ai02_source_revision_vector, owner_source_digests,
  ai04_protocol_version, transport, conformance_suite_sha, sdk_version,
  host_name_version, negotiated_protocol, os_arch_cpu_ram_network,
  fixture_seed, labels_digest, project_principal_grant_policy_epoch,
  query_set_digest, ranking_tokenizer_version, freshness_mode,
  direct_source_reads, resource_calls, pages, authorized_rows,
  returned_bytes, baseline_bytes, context_reduction_basis,
  estimated_tokens, exact_tokenizer_id_if_any,
  citation_accuracy, recall_at_k, mrr, ndcg_at_k,
  p50_p95_p99_sample_digest, cold_start, peak_rss, cpu,
  unsupported_sources, stale_rejections, unauthorized_owner_reads,
  leaked_bytes, external_network_calls, unauthorized_command_dispatch,
  approval_violations, license_rights_violations, verdict
}
```
All numeric receipt values are **NOT MEASURED** for this planning phase. No provenance-free summary or invented benefit may pass. A green documentation CI does not execute these workloads.

[Architecture](../architecture/ai-05-context-resources-templates.md) · [Future tests](../testing/ai-05-acceptance-matrix.md) · [AI-02 benchmark](ai-02-semantic-index-benchmark-protocol.md).
