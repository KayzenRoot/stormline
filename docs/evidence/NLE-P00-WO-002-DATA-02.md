# Evidence Bundle — NLE-P00-WO-002-DATA-02

**Date:** 2026-11-14 | **Risk:** LOW documentary research; future persistent registry/migrations and cross-file operations ELEVATED.
**Research issue:** [#111](https://github.com/KayzenRoot/stormline/issues/111) | **Future implementation issue:** [#25](https://github.com/KayzenRoot/stormline/issues/25) remains BLOCKED.
**Current evidence status:** APPROVED / MERGED for research documentation ONLY; no engine software, ADR-0010 remains PROPOSED.

## Baseline and Context Lock
- Main before research: `7924f0eaf1eaf711e2316da7f4ee3dc7521afddb` (DATA-01/checkpoint completed).
- Branch: `docs/NLE-P00-WO-002-DATA-02-asset-registry-research`.
- Exact critical source **Git blob object IDs** at base (not SHA-256 content fingerprints):
  - Checkpoint `c02a2d759e43fbed589c8c5e347579e48951f7e8`
  - Decisions Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
  - Scope `4ef605c74632ece080b2650e37dd83a415b63310`
  - DoD `160b3054db9ea1961308934b401488b838d24c3e`
  - Architecture `2bb7683837c492013efa8e434bd1e38352e4a22d`
  - Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
  - DATA-01 ADR-0009 `a2e14b249f2b65d774da4ec23855285f884bfc36`
  - Module catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- A future executor must capture fresh SHA-256 source fingerprints and base/head SHAs on authorization, not treat these blob IDs as SHA-256 hashes.

## Change scope
- `docs/architecture/data-02-asset-registry.md`: immutable logical AssetId, independent VfsPath/digest/runtime handle; canonical metadata alternatives; index/graph/provenance, migration/failure/security model and SAPG research.
- `docs/research/data-02-asset-registry-technology-matrix.md`: SQLite public-domain, UUIDv7 RFC 9562, BLAKE3 CC0/Apache alternatives, SHA-256, minimal baselines and tradeoffs.
- `docs/adr/0010-data-02-asset-identity.md`: PROPOSED decision; no SQLite/ID/backend locked for implementation.
- `docs/contracts/data-02-registry-api.md`: proposed typed Editor/CLI/MCP transaction API and recovery states, no generated headers.
- `docs/testing/data-02-acceptance-matrix.md`: 16 future scenarios for identity, damage recovery, OS, security and performance.
- `docs/work-orders/NLE-P00-WO-002-DATA-02.md`: complete research-only WO.
- Architecture, Backlog and future blocked packet `docs/queue/work-orders/DATA-02.md` linked. No engine C++, database, cloud, runtime or project-file migration added.

## Technical and safety conclusions (research proposals, NOT validated)
- Evaluate portable authoritative project metadata + **derived/rebuildable SQLite index** vs authoritative SQLite vs manifest-only; none final without crash and source-control proofs.
- A file move and a SQLite transaction are not one atomic operation; staged journal/recovery and explicit consistency rules essential.
- Stable AssetId survives rename/reimport; content hash identifies a revision, not the asset or publisher authenticity. UUIDv7 is a standard candidate, not a permission token.
- SQLite WAL permits concurrent readers but one writer and requires local filesystem; foreign keys require explicit enabling. `synchronous=NORMAL` WAL may lose committed data under power failure; compare FULL under project safety needs.
- BLAKE3/SHA-256 source fingerprint algorithms subject to exact version/license/security evaluation.
- SAPG is optional experimental provenance and impact graph with prove-or-drop criterion; no uniqueness/throughput claim.
- MCP contracts must be scope-limited, previewable, transaction-safe and redacted. No arbitrary SQL or host path exposure.

## Final research PR audit and merge
- [PR #112](https://github.com/KayzenRoot/stormline/pull/112), BASE main `7924f0eaf1eaf711e2316da7f4ee3dc7521afddb`, final audited HEAD `99076f7df0e63e12e082329830bbac49cd241143`.
- [GitHub Actions run 43601883375](https://github.com/KayzenRoot/stormline/actions/runs/43601883375): `docs-validation` SUCCESS for final research HEAD; Source Pack/links, module DAG, 80-WO registry and blocked-selector smoke PASS.
- Objective pt-BR audit on PR #112: APPROVED for documentation only. Diff: 10 Markdown docs/ files, no runtime code or obvious secrets in patch (not full secret scanning).
- Squash merge `a5664bfccf011dc3300c54a18d6ae846ee0926d8` confirmed by main readback and actual architecture file; implementation issue #25 and full queue still BLOCKED.

## Actual tests
- GitHub Actions docs-validation: **SUCCESS on final audited HEAD** per run above; separate checkpoint PR needs independent CI.
- GitHub objective audit pt-BR: **APPROVED for research documentation**, recorded on PR #112.
- C++ native build, SQLite WAL/integrity/recovery, project file migration, VFS integration, UUID generation, hash throughput, asset ID reference correctness, 1m-asset benchmark, OS/AI/security test: **NOT RUN**.
- No paid tools, CodeRabbit, mandatory outside reviewer, force-push or bypass.

## Proposed checkpoint delta
Once this research passes objective CI/audit/merge and main readback, set DATA-02 `research_status=RESEARCH_DOCUMENTED_ADR_PROPOSED`; preserve implementation issue #25 and every one of the 80 registry WOs as BLOCKED/`executor_ready=false`. Keep ADR-0010 PROPOSED. Reconcile Evidence Bundle and canonical Checkpoint in a post-merge PR of the **same WO**, and only then advance to DATA-03 planning.
