# Evidence Bundle — NLE-P00-WO-002-DATA-03

**Date:** 2026-11-14 | **Risk:** LOW docs, future ELEVATED hostile decoder/project integrity.  
**Research issue:** [#114](https://github.com/KayzenRoot/stormline/issues/114) | **Implementation:** [#26](https://github.com/KayzenRoot/stormline/issues/26) remains BLOCKED.  
**Evidence state:** PENDING FINAL CI/AUDIT / NO ENGINE CODE. ADR-0011 PROPOSED.

## BASE and Context Lock
- Git main baseline `b477dbecacc733a251666644ac05173f9390d159`.
- Branch `docs/NLE-P00-WO-002-DATA-03-import-research`.
- Critical source fingerprints below are **Git blob object hashes, NOT content SHA-256**:
  - Checkpoint `88c6f21a98e934a06a233fb79c9bfe2ce229133a`
  - Decisions Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
  - Scope `4ef605c74632ece080b2650e37dd83a415b63310`
  - DoD `160b3054db9ea1961308934b401488b838d24c3e`
  - Architecture `d3abf7c11256db8db9df095e71d4b4271d7da63a`
  - Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
  - DATA-02 ADR-0010 `c9465747dc6589ceed121e89bcdf211687021d00`
  - Module catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- Future implementation MUST capture fresh base SHA and SHA-256 hashes of relevant source files. If critical canonical input changes, mark STALE and rebase.

## Authored research and affected files
- `docs/architecture/data-03-import-conversion-pipeline.md`: source stages, security, glTF/texture/audio/animation semantics, importer receipts, stable subassets, idempotence and 3-way override recovery, SIRG conditional R&D.
- `docs/research/data-03-importer-technology-matrix.md`: fastgltf/cgltf MIT, Assimp BSD-3-Clause-based, OpenUSD conditional, KTX2/Basis, mixed KTX licensing, source codecs and evaluation criteria.
- `docs/adr/0011-data-03-import-policy.md`: PROPOSED, not a selected/installed production stack.
- `docs/contracts/data-03-import-api.md`: typed semantic ImportRequest/Plan/Artifact/Receipt/ReimportPlan, scoped Editor/CLI/MCP commands and errors; no generated C++/MCP API.
- `docs/testing/data-03-acceptance-matrix.md`: future IMP-001 through IMP-020, no tests executed.
- `docs/work-orders/NLE-P00-WO-002-DATA-03.md`: research scope, tests, outputs, review and stop; future implementation #26 remains BLOCKED.
- Links: Architecture/Backlog/future blocked implementation packet. No C++/shader/codec/engine executable files or build configuration changed.

## Main conclusions and major risk gates
- Primary 3D interchange baseline glTF2/GLB, **compare** fastgltf vs cgltf; no winner from marketing claims. Assimp and OpenUSD only as justified optional adapters.
- KTX-Software is **mixed licensed**: optional non-open-source ETC decoding module noted in upstream licensing; exclude `LIBKTX_FEATURE_ETC_UNPACK` by default unless approved, validate actual included file list/SBOM before redistribution. Basis Universal dependencies have transitive notices.
- DATA-01 secured VFS must bound source/external URIs; DATA-02 manages immutable identity/metadata, subasset stable mappings and staged project transactions. No guarantee file+DB commits atomically.
- Idempotent reimport, user-overrides preservation and loss/conflict diagnostics are **acceptance requirements**, not currently functioning features.
- File-parsing security ELEVATED: malformed buffers/images/audio, integer overflow, decode-bomb, plugin escapes, crash recovery, time/memory/IO limit, sandbox-specific semantics.
- Original SIRG research must prove practical benefit over DATA-02 receipts/graph and must not duplicate a second source of truth.
- Exact source tags/licenses/release schema, performance budgets and high-fidelity fixtures deferred for future approved implementation.

## Tests and checks
- GitHub Actions final research HEAD CI: **PENDING** at creation; record only after real run and objective audit.
- Objective audit: **PENDING**.
- glTF parser integration, Windows/Linux/macOS builds, simulated malicious inputs, fuzzers/ASan/TSan, 2D/3D/audio golden fixtures, GPU quality, import/reimport/fault injection, benchmark: **NOT RUN**. No engine runtime exists.
- No mandatory external reviewer, CodeRabbit, paid CI, bypass, force push or secret credentials.

## Proposed Checkpoint Delta after audited merge
Mark DATA-03 research documentation APPROVED / MERGED, retain ADR-0011 PROPOSED, `DATA-03.research_status=RESEARCH_DOCUMENTED_ADR_PROPOSED`, all 80 future implementation issues including #26 `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS` and `executor_ready=false`. In a separate audited PR for the SAME WO, reconcile CI/head/merge SHA and checkpoint before considering next module.
