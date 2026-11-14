# Research Work Order — NLE-P00-WO-002-DATA-05

**Research issue:** #120 | **Future code issue:** #28 BLOCKED | **Date:** 2026-11-14
**Status:** IN PROGRESS / RESEARCH DOCUMENTS ONLY | **ADR-0013:** PROPOSED.
**Base main / Context Lock:** 8659327e73e803dcf09345e95f14647375ce9fe5. DATA-04 research and checkpoint approved/merged via PRs #118/#119.
**Risk:** LOW documentation; future ELEVATED integrity, codecs, patching and target distribution.

## OBJECTIVE
Fully specify a safe cross-platform asset cooking, immutable bundle and incremental patching architecture for the future Stormline game engine. Prepare secure typed target profiles, bundle/index formats, streaming/recovery contracts, technology choices, golden acceptance matrix and Evidence Bundle so Zcode need not make speculative architecture decisions. This increment has **no engine code**.

## CONTEXT
P00 research program: 80 future implementation Work Orders in registry remain BLOCKED. Windows/Linux/macOS native Editor and exports, 2D/2.5D/3D, games for Web and manual+AI-native authoring; no public MVP prior to approved v1 DoD. Owner expects free public GitHub CI, solo objective audit and no CodeRabbit or external human reviewer. DATA-01 VFS, DATA-02 AssetId, DATA-03 import/intermediate and DATA-04 editable scene research documented only; future code predecessors aren't implemented.

## SCOPE
- Target-aware cook DAG from DATA-03 imported intermediate and DATA-04 SceneIR, DATA-02 stable asset references and source rights.
- Portability: graphics API/GPU texture/mesh/audio/shader capabilities, Web negotiation, local native/headless and optional acceleration adapters.
- Evaluate zstd/LZ4/Brotli compression, meshoptimizer geometry, KTX2/Basis texture transcode, scene binary encodings and license/SBOM notices.
- Versioned independent manifest, chunk descriptors, receipts, hash/tag algorithm, separate publisher trust semantics, content-addressed reuse.
- Bundle random seek / stream queue, dependency priorities, backpressure, low-memory IO/RAM/GPU budgets, cache and Web 206/200/416 offline and CORS.
- Incremental patch plan with verified unchanged chunk reuse, staged activation, rollback and journal across VFS/registry; fault recovery.
- Architecture, matrix, ADR-0013 PROPOSED, API, 28 future scenarios, Evidence Bundle, blocked packet links and readback.
- SASG adaptive derived hint is optional **prove-or-drop**, compared to static priorities/LRU.

## OUT OF SCOPE
No C++, GPU/renderer, asset packer, loader, shader compiler, signing keys, production CDN/network, actual bundle binaries, project mutation, installer, auto-update, confidential credentials, paid tooling, CodeRabbit, mandatory external reviewer, bypass, force-push or public release. No 80-WO activation.

## FILES / SOURCES TO READ
Canonical: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md`/approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `docs/00-source-hierarchy.md`, `AGENTS.md`, module catalog/queue, DATA-01/02/03/04 architectural docs/ADRs/contracts, future #28 blocked packet, official codec/license/spec/HTTP sources.

## REQUIREMENTS
GOV-001..005; CAP-001/002/003/004/005/008/009/010/011/012/013/014/016; NFR-001..005; owner NLE-D013..020. Catalog DATA-05 acceptance: bundle hash verification and bounded-memory progressive load (future test, not functionality now). Future implementation needs concrete new requirement IDs and release classification, not invented by Zcode.

## ARCHITECTURE RULES
- DATA-02 AssetId and DATA-04 project authoring remain authoritative; generated bundle is derived, signed policy separate from content hash.
- Cook target based on explicit capabilities, not only OS, maintain fidelity/quality/preservation and format versioning.
- DATA-01 VFS scoped immutable staging, explicit journal/rollback, no false cross DB/filesystem atomicity.
- Pin all DAG source versions, codecs, dictionaries, encoder tools, schema and platform; deterministic outputs only where proven.
- Avoid invoking shell/URLs/signing keys from MCP; every mutation requires typed scopes and approved intent.
- Progressive streaming must respect core memory/jobs/IO/VRAM limits with backpressure and explicit CPU/GPU-ready status.
- Distributable rights and SPDX/SBOM requirements per source asset + library; KTX proprietary option excluded unless separately cleared.

## CONSTRAINTS
P00 docs only; branch PR scoped, free GitHub docs CI; no migration, vendor installation, cloud cost or external review; no false benchmark/build/decoder claim. Any STALE Context Lock or HIGH/CRITICAL prevents advancing. Future implementation requires approved ADR, commands/files, risk and dependency merge evidence.

## ACCEPTANCE CRITERIA
- [ ] Architectural boundary and target cooker pipeline specify stable IDs, quality/fallback and trusted manifest/generation semantics.
- [ ] Candidate technologies + licensing matrix precise on zstd dual license, LZ4 library vs CLI license, KTX optional nonopen ETC decoder, Web HTTP Range optional.
- [ ] Semantic API covers target profile, CookPlan/Receipt, bundle index/chunks, StreamRequest, PatchPlan/Receipt, typed errors and MCP scopes.
- [ ] Threat model handles malicious offsets/dictionaries/codec, content authenticity confusion, decompression bombs, stale/mixed generation, crash and data loss; rollback policy explicit.
- [ ] At least 20 (specified 28) future tests covering golden 2D/2.5D/3D/audio, Web and macOS, progressive budgets, patches/faults, copyright/license and denied unauthorized MCP.
- [ ] ADR-0013 PROPOSED, future #28 remains BLOCKED, all 80 registry entries executor_ready=false, no engine code.
- [ ] Real docs-validation on exact final PR HEAD SUCCESS; scoped diff, objective pt-BR audit and Evidence Bundle.
- [ ] After approval, normal squash merge, main readback, same-WO checkpoint reconciliation in separate docs PR before next research.

## TESTS
Current: Source Pack/local link validator, module catalog/DAG, registry 80 blocked WOs, Zcode selector refuses BLOCKED, via actual GitHub Actions. Future COOK-001..028 are **NOT EXECUTED**. No C++ build, importer, bundle, signature, testing on real machines or benchmark.

## DELIVERABLES
`docs/architecture/data-05-cooking-streaming-bundles.md`; `docs/research/data-05-cooking-technology-matrix.md`; `docs/adr/0013-data-05-cooking-policy.md`; `docs/contracts/data-05-cook-bundle-api.md`; `docs/testing/data-05-acceptance-matrix.md`; this research WO; referenced canonical docs and future packet; Evidence Bundle; reviewed PR; checkpoint delta (proposed, never self-promoted pre-audit).

## REVIEW FORMAT
Brazilian Portuguese; verdict APPROVED / CORRECTION REQUIRED / BLOCKED; base/head SHA, exact diff, CI run/results, security/license/recovery/quality/performance risks, tested vs untested, approved scope, suggested checkpoint delta.

## STOP CONDITION
Immediately block upon STALE canonical checkpoint/ADR, unapproved source/license, unsafe unsigned distribution or unbounded decompression, failed CI, unapproved runtime code, known HIGH/CRITICAL, secret, paid action, destructive patch or mandatory reviewer. Fix only same WO and PR; do not advance when blocked.

## CONTEXT LOCK
Base main `8659327e73e803dcf09345e95f14647375ce9fe5`. Record Git blob fingerprints of critical sources in Evidence Bundle (NOT actual SHA-256), refresh SHA-256 at future implementation. No independent code execution until source and approved requirements fixed.

## CHECKPOINT
After PR/CI/audit/merge readback only, separately reconcile approved research state, backlog, registry and Evidence Bundle in **same WO**; preserve ADR-0013 PROPOSED and #28 BLOCKED. Do not consider the next research increment before checkpoint complete.
