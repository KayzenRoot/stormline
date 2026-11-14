# Work Order — NLE-P00-WO-002-DATA-01

**Issue:** #108 | **Module:** DATA-01 Virtual File System | **Risk:** LOW documentation; later implementation ELEVATED due to filesystem security/data loss.  
**Status:** PROPOSED RESEARCH / NOT IMPLEMENTED | **Context Lock main SHA:** `3befddfb0df42ee5a8a749fb39116bfbd36fb01a`.

## OBJECTIVE
Research the full cross-platform secure Virtual File System architecture, technology stack, licensing and security/performance test plan. Minimize future Zcode decisions; this WO writes only reviewed planning documents.

## CONTEXT
Stormline has 80 module candidates and blocked future implementation issues #18–#97, CORE-01..CORE-06 research/checkpoints approved, no C++ engine. DATA-01 implementation issue #24 is separately BLOCKED. Owner mandates Windows/Linux/macOS native, Web later, 2D/2.5D/3D, AI/MCP-authoring, no public MVP, zero mandatory paid CI and no outside human reviewer.

## SCOPE
- Typed namespace/mount/overlay/capability, handle lifecycle, logical path errors, read/write transaction/cache interfaces.
- Compare C++20 std::filesystem, owned native backend, PhysicsFS zlib, libzip BSD-3-Clause and optional archive alternatives, exact version TBD.
- Document path traversal/TOCTOU/symlink/reparse/junction, zip-slip/bomb, Unicode, OS and Web risks.
- Define secure default RO mounts, scoped writes, rollback/recovery/quotas, Editor/CLI/MCP semantics and SAMG R&D hypothesis.
- ADR-0009 PROPOSED, security/benchmark/tests plan, Source Pack links, Evidence Bundle and audited GitHub PR/checkpoint.

## OUT OF SCOPE
No VFS engine implementation, C++ or archive dependencies, security promises without tests, filesystem access to user machine, remote storage/network, paid services, mandatory external human review, CodeRabbit, bypass, renderer/asset registry implementation or release.

## FILES / SOURCES TO READ
In order: `docs/11-checkpoint.md`, `docs/10-decisions-ledger.md`/approved ADRs, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/04-architecture.md`, `docs/02-requirements.md`; then `docs/product/module-catalog.md`, `docs/queue/work-orders/DATA-01.md`, AGENTS.md, CORE-01/02/03/06 research, official upstream licenses/docs and `docs/engineering/zcode-handoff.md`. Inspect base/branches/PR first.

## REQUIREMENTS
GOV-001..005; CAP-005/008/009/010/012/013/014/016 as relevant, NFR-001..005 and owner decisions NLE-D013..020; DATA-01 catalog acceptance and dependency CORE-01.

## ARCHITECTURE RULES
- VFS namespace distinct from OS path and stable AssetId; no third-party types in public ABI.
- Deny path traversal/junction/symlink escape using handle-based OS bridge; lexical check never sufficient.
- Scoped explicit mounts and writes; no ambient home dirs/MCP file read; transactional durability subject to verified OS semantics.
- Bounded parsers, checks, memory and storage; no untrusted archive extraction by default.
- Zero privileged telemetry network/cloud; tests need platform identity and build SHA for evidence.
- Platform adapters must not force GPU/display in headless server.

## CONSTRAINTS
P00 documentation only; free public GitHub Actions; no CodeRabbit or outside reviewer; no force push, bypass, destructive changes or mandatory paid features. Do not claim library integrated, sandbox enforced or tests passed unless run evidence exists.

## ACCEPTANCE CRITERIA
- [ ] Architecture includes typed contracts, mount precedence/permission/rollback and stable error model.
- [ ] Matrix covers candidates, official licenses, alternatives, supply chain/maintenance and selection gates.
- [ ] Threat model includes TOCTOU, symlinks/reparse, path traversal, malformed archives, case/Unicode, data corruption and recovery.
- [ ] Windows/Linux/macOS/Web/headless distinctions and actual OS API tests are planned.
- [ ] p50/p95/p99 lookup/IO memory/bandwidth, failure injection and parser fuzzing plan published, no fabricated results.
- [ ] ADR-0009 remains PROPOSED for future code; implementation issue #24 and 80-WO registry BLOCKED.
- [ ] Docs Validation PASS on PR exact HEAD, scoped patch audit and no HIGH/CRITICAL in documentation.
- [ ] Evidence Bundle, pt-BR audit, normal squash merge and readback; post-merge checkpoint in SAME WO.

## TESTS
Current: GitHub Actions Docs Validation (Source Pack, module DAG, 80 WO registry and blocked selector), exact run ID required. Future: Windows/Linux/macOS VFS security tests, C++ fuzzing, crash/recovery, perf/storage hardware benchmarks **NOT RUN**.

## DELIVERABLES
DATA-01 detailed architecture, candidate matrix, ADR-0009, WO, Backlog/Architecture/blocked-issue links, Evidence Bundle, PR and proposed checkpoint delta. No code.

## REVIEW FORMAT
Português brasileiro: `APPROVED / CORRECTION REQUIRED / BLOCKED`, SHA base/head, actual CI, changed files, source hierarchy/risk/security, tests actually run/unrun, issues #108/#24 and checkpoint proposal.

## STOP CONDITION
Stale sources, unsupported library license asserted as approved, file escape design flaw, failed CI, unapproved payment or native code, HIGH/CRITICAL security risk, data-integrity scope ambiguity. Remediate within same WO/PR.

## CONTEXT LOCK
Baseline `3befddfb0df42ee5a8a749fb39116bfbd36fb01a`. Critical Git blob fingerprints in Evidence Bundle, labeled as SHA-1 object IDs (not SHA-256 content hashes), and revalidate if any checkpoint/Scope/DoD/Architecture/ADR changes.
