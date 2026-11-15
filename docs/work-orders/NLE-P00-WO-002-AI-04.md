# NLE-P00-WO-002-AI-04 — MCP Server & Protocol Adapter P00 Research Work Order

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | research #293 | NLE-P00-WO-002-AI-04 | code #78 OPEN/BLOCKED | BASE 0cdcef6ae19ba1105667404ed5749ad5155fef0f.** 59/80 researches documented, 21 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency AI-03 ONLY; ADR-0062 PROPOSED; NLE-D009 OPEN; NLE-D015 OWNER-DIRECTED.
Research issue #293; catalog order 60/80; future code #78 OPEN/BLOCKED; base main 0cdcef6ae19ba1105667404ed5749ad5155fef0f; prior research 59/80, 21 pending, zero engine, all 80 code WOs blocked. Formal dependency AI-03 ONLY (ADR-0062 PROPOSED, code #77 OPEN/BLOCKED). AI-05/06/07 are future integrations, not formal edges.

## OBJECTIVE
Deeply research and document a secure model-neutral MCP adapter with 2026-07-28 stateless primary protocol, bounded 2025-11-25 compatibility, local stdio, opt-in remote Streamable HTTP, tools/resources/prompts projections, authorization and owner-only dispatch. Define conformance and selected-host proof. Research only; no code.

## CONTEXT / SOURCE CHECK
Precedence: approved checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS > catalog/registry > module specs. Main exact user SHA 0cdcef6ae19ba1105667404ed5749ad5155fef0f; no open PRs. AI-04 catalog 60/80, dependency AI-03 only; code #78 OPEN/BLOCKED. AI-03 ADR-0062 PROPOSED; AI-01 ADR-0060 PROPOSED. NLE-D015 OWNER-DIRECTED; NLE-D009 engine license OPEN.
Context Lock Git blob OIDs (SHA-1, not byte SHA-256): Source Hierarchy 58a377bc76cafdd3377d733d4f30ef53661bb034; checkpoint f8b8fd663363dacf46c9908f5a2842ac7b41df02; Ledger d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e; Scope 4ef605c74632ece080b2650e37dd83a415b63310; DoD 160b3054db9ea1961308934b401488b838d24c3e; Architecture df62574cb3956c3ac9881631a4cf66be4e1abff1; Requirements 14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b; catalog 18d69bca439831d65982cb0f8acbca1dbaa2eee9; AI/MCP contract 161183078034162ca458212e65a47cd17a112394; registry c5c546efdbc5d92e8315c67db0c35b1175317604; AI-04 queue WO 3fc6d785e96f4bfaed2f6ccf3770d8f4c82b2871; AI-03 architecture df8e08df6653ea85796fa25e1e0ffe4fd61c289a; AI-03 API e424f6023a92f4b9a47f8bbc4cd0f6470f0e3487; ADR-0062 282df7cccdeb9fba2aff1a1bf6195807c1c17fc8; AGENTS 3e57b719f8651407879ebb641707a048773ea4c2. Re-read critical sources before PR/checkpoint; STALE means stop.

## SCOPE — EXACTLY EIGHT NEW MARKDOWN
1. [Architecture](../architecture/ai-04-mcp-server-protocol-adapter.md)
2. [ADR-0063 PROPOSED](../adr/0063-ai-04-stateless-mcp-adapter.md)
3. [Protocol/SDK/license/security matrix](../research/ai-04-mcp-technology-license-security-matrix.md)
4. [Typed contracts](../contracts/ai-04-mcp-server-contracts.md)
5. [128 future tests](../testing/ai-04-acceptance-matrix.md)
6. [Benchmark](../research/ai-04-mcp-benchmark-protocol.md)
7. This WO
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-AI-04.md)

Research PR changes exactly these eight new Markdown; no registry/checkpoint/backlog/CI/code.

## OUT OF SCOPE
C++/Rust/TypeScript/Python code, SDK install/runtime packaging, OAuth authorization server, production listener, remote deployment, AI-05 resource DB, AI-06 grant issuer, AI-07 transaction planner, durable job engine, arbitrary shell/filesystem/network tool, LLM provider, MCP Apps/Skills, automatic prompt execution, Tasks without owner JobHandle, 2024-11-05 HTTP+SSE, license adoption, engine release class, CodeRabbit, paid CI, broad cleanup, force-push or bypass.

## FILES / SOURCES TO READ
Canonical hierarchy, checkpoint, Ledger, Scope, DoD, Architecture, Requirements, AGENTS, module catalog, AI/MCP contract, implementation registry and AI-04 queue WO. Predecessor AI-03 architecture/API/ADR-0062/128 tests. External MCP 2026-07-28 spec/changelog/versioning/transports/authorization/tools/resources/prompts, Tasks extension, SDK index, TypeScript/Python SDK license/release docs, official conformance suite, security guidance and OpenTelemetry.

## REQUIREMENTS
GOV-001..005; CAP-010, CAP-013, CAP-014, CAP-016; NFR-002..005; NLE-D015. Catalog acceptance: MCP conformance and interaction with selected hosts. 100% public approved authoring coverage is inherited from AI-03 independent inventory. NLE-D009 remains OPEN.

## ARCHITECTURE RULES
Formal dependency AI-03 only; AI-03 owns projection, AI-01 owns command execution/authorization/receipt. 2026-07-28 modern primary; 2025-11-25 compatibility only if conformance and host proof; no blind downgrade. stdio local default; remote Streamable HTTP explicit; Origin validation, loopback local, TLS and OAuth resource-server validation. Per-request identity/policy; never trust clientInfo, annotations, prompt content or request ID. Tools route through AI-03 to AI-01. Resources/prompts via future provider ports; AI-05 not a new dependency. MRTR is input, not consent. Tasks opt-in only with durable owner JobHandle and per-request auth. No raw filesystem, shell, network, GPU, engine pointers or secrets. Version-specific errors, bounded payload/concurrency, cache/cursor/subscription scope and redacted telemetry. No SDK/license adoption without separate approved ADR and SBOM/CVE evidence.

## CONSTRAINTS
Documentation-only LOW. Future remote auth/cross-project/token processing ELEVATED or HIGH_ASSURANCE. No invented host compatibility, benchmark, SDK support, license or conformance. 128 tests future only. All 80 code packets remain BLOCKED.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight new Markdown, valid links, no code or registry/checkpoint change in research PR.
- [ ] ADR-0063 PROPOSED; formal DAG unchanged; #78 OPEN/BLOCKED.
- [ ] Research covers 2026/2025 protocol, transports, authorization, tools/resources/prompts, MRTR, subscriptions, Tasks, security, SDK/license and conformance.
- [ ] Exactly 128 unique A04-T001..A04-T128, all FUTURE/NOT EXECUTED.
- [ ] Independent test mapping and benchmark; no invented thresholds.
- [ ] Exact-final-HEAD Docs Validation SUCCESS; diff and objective pt-BR audit APPROVED, no HIGH/CRITICAL.
- [ ] Normal squash and main readback.
- [ ] Independent five-file checkpoint PR, sole AI-04 research_status transition, own CI/audit/squash/readback; target 60/80 documented, 20 pending, all 80 code WOs blocked.
- [ ] Close #293 only after factual readback; separate four-Markdown historical closeout with own gates.

## TESTS
P00: python3 scripts/validate_docs.py; python3 scripts/validate_module_catalog.py; python3 scripts/validate_wo_registry.py; python3 scripts/select_wo.py CORE-01 --json must reject status 2; GitHub Docs Validation exact HEAD. Future official MCP conformance server suite pinned to 2026-07-28; legacy 2025-11-25 only if advertised. All 128 A04 tests FUTURE, not executed.

## DELIVERABLES
Eight research Markdown, ADR-0063 PROPOSED, typed contracts, 128 future tests, reproducible benchmark, research PR, Evidence Bundle, pt-BR audit, squash/readback, independent checkpoint and optional historical closeout.

## REVIEW FORMAT
Português brasileiro: APPROVED / CORRECTION REQUIRED / BLOCKED; base/head, exact files, CI run/job/steps, 128 ID count/status, protocol/transport/auth/security/license/host coverage, risks, checkpoint delta and postmerge readback.

## STOP CONDITION
Stale source, wrong DAG, unapproved scope, protocol downgrade, unsafe auth, leaked data, hidden listener, missing test IDs, unpinned dependency/license, CI failure, HIGH/CRITICAL, invented conformance or any code unlock. Do not start AI-05 while this increment requires correction/validation.
