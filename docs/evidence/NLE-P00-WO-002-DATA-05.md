# Evidence Bundle — NLE-P00-WO-002-DATA-05

**Date:** 2026-11-14 | **Research issue:** #120 | **Future implementation:** #28 BLOCKED.
**Evidence state:** IN PROGRESS / DOCUMENTATION RESEARCH ONLY; no C++/asset bundle/cooker/patcher/export/deployment.
**Baseline main:** `8659327e73e803dcf09345e95f14647375ce9fe5`; branch `docs/NLE-P00-WO-002-DATA-05-cooking-research`. Risk LOW docs, future ELEVATED integrity, untrusted codec, recoverable updates.

## Context Lock and authoritative sources
SHA baseline is the DATA-04 checkpoint-merged main. Critical source fingerprints **MUST be labeled Git blob object hashes, NOT SHA-256 of file bytes**. At code activation capture actual SHA-256 hashes freshly and mark STALE if any critical canonical source changes.
- Checkpoint `docs/11-checkpoint.md` = `b27caae45b498abff23fef95a3a46246ef22da7d`
- Decisions `docs/10-decisions-ledger.md` = `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope `docs/03-scope.md` = `4ef605c74632ece080b2650e37dd83a415b63310`
- DoD `docs/09-definition-of-done.md` = `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture `docs/04-architecture.md` = `5d4586bdc4ecb0249520dc97a30c525219e2e057`
- Requirements `docs/02-requirements.md` = `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- Future blocked DATA-05 packet `docs/queue/work-orders/DATA-05.md` = `d50fb175455341e57437509f5dc65d7d8685a581`
- Registry `docs/queue/implementation-registry.json` = `b8e235382f9c423774d51d3f26b6a8d49c69e5fb`

## Scope and authored documents
- DATA-05 architecture: cooking DAG/target profile, immutable chunked bundles, semantic integrity vs publisher trust, streaming/backpressure, reliable Web fallback and patch activation/recovery.
- Technology matrix: zstd, LZ4, Brotli, meshoptimizer, KTX2/Basis, typed binary schema options, integrity/authenticity and platform APIs with license gates.
- ADR-0013: PROPOSED only, no libraries or codecs installed, source license OPEN.
- Typed API: CookRequest/Plan/Receipt, Chunk/BundleManifest, StreamRequest, PatchPlan/Receipt, semantic Editor/CLI/MCP scope and error contracts.
- COOK-001..028 future tests: golden target formats, memory budgets, Web, macOS, malicious input, patent/license/SBOM, patch/resume/recovery, human/AI permissions.
- Research WO, links in canonical Architecture/Backlog and future blocked queue packet.
- SASG is an unimplemented prove-or-drop hypothesis; no proprietary performance superiority assumed.

## Security / license gates / residual risks
A bundle digest is a bit-integrity check, **not** a signature or publisher authenticity. Remote delivery requires trustworthy source/signature/rollback policy, deferred PLAT-05 authorization. VFS and DATA-02 registry cannot be treated as one ACID transaction, so journal+prior-good recovery is a future proof obligation. Potential decompression bomb/offset overflow, source rights and mixed-license KTX/etcdec have future ELEVATED implications. Native Windows/Linux/macOS and Web range 200/206 fallback still unverified.

## Evidence and audit (actual results only)
- Documentation validation at final research HEAD: PENDING actual CI.
- 80 WOs status and selector: future verified CI; code executor still BLOCKED.
- Scoped diff/secret scan, objective pt-BR audit, final research HEAD and PR: PENDING.
- Tests COOK-001..028, C++ compilation/build, GPU and native OS benchmarks, fuzzing, runtime codec, Web app, uploads, cloud releases and SHA-256 runtime proof: **NOT RUN**.
- Normal squash merge, main readback and same-WO checkpoint reconciliation: PENDING.

## Proposed Checkpoint Delta (not active until audited merge)
After independent docs CI and scope/security review APPROVED and research PR normal squash merge, record DATA-05 research as DOCUMENTED_ADR_PROPOSED, ADR-0013 still PROPOSED, implementation #28 + 80 WOs BLOCKED with `executor_ready=false`, no engine code. Reconcile in separate approved docs-only PR for this same WO before further research.
