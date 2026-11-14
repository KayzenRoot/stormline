# Research Work Order — NLE-P00-WO-002-DATA-03

**Research issue:** #114 | **Future code issue:** #26 (BLOCKED) | **Date:** 2026-11-14  
**State:** RESEARCH PROPOSED / AUDIT PENDING, **NOT IMPLEMENTED**  
**Base main:** `b477dbecacc733a251666644ac05173f9390d159`.  
**Risk:** LOW for documentation, ELEVATED for future decoder security/asset preservation/distribution.

## OBJECTIVE
Design complete initial DATA-03 asset importer/converter and reimport technology/contract strategy so future Zcode implementation can be scoped with minimal architecture decisions while preserving safety/fidelity.

## CONTEXT
CORE-01..06 and DATA-01/02 technology research are documentation-approved and checkpointed. No native engine code. Catalog requires stable `AssetId`, idempotent reimport without losing derived/user edits, Windows/Linux/macOS editor/exports and Web target, 2D/2.5D/3D, manual+AI authoring, no public MVP. Owner mandates zero-cost public CI and solo review.

## SCOPE
- glTF/GLB, 2D/HDR/KTX2 textures, WAV/other audio, rig/animation import requirements and extension fidelity.
- Candidate libraries: fastgltf, cgltf, Assimp, OpenUSD, KTX-Software/Basis, future codec-by-codec candidates, license/mixed-source and supply-chain review.
- Typed `ImporterDescriptor`, `ImportPlan`, `ImportRequest`, `ImportReceipt`, artifacts, stable subasset keys, semantic reimport and merge overrides; state/error model.
- Strict DATA-01 VFS containment, DATA-02 identity/recovery contract, CORE-05 transforms and CORE-06 diagnostics, no circular dependencies with DATA-04/05.
- 20 future acceptance fixtures, threat model, platform/performance test matrix, optional SIRG prove-or-drop and ADR-0011 PROPOSED.
- Research PR, docs-validation/evidence, pt-BR objective audit, post-merge checkpoint delta same WO.

## OUT OF SCOPE
No C++/shader/editor/importer package installed, no asset conversion run, no migration, no untrusted file processing, no project source mutation, no cloud, paid CI, CodeRabbit, mandatory external reviewer or bypass. No future implementation status change to ready.

## FILES / SOURCES TO READ
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md`/ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`, then module catalog and dependency DAG, CORE-05 coordinate proposal, DATA-01/02 docs/ADR/contracts, `docs/queue/work-orders/DATA-03.md`, `AGENTS.md`, source release/license docs.

## REQUIREMENTS
GOV-001..005, CAP-001/002/003/004/008/009/010/011/012/013/014/016 and relevant NFRs, owner decisions NLE-D013..020, catalog DATA-03 verification: reimport idempotent without losing derived edits.

## ARCHITECTURE RULES
- Identity stays DATA-02; VFS and disk confinement DATA-01. No native/vendor types leaking into public contract.
- DATA-03 converts source to intermediate; DATA-04 scene serialization, DATA-05 target cooking/runtime bundles.
- Importer plugins require sandbox/capability proof, no arbitrary host path/network/subprocess/MCP execution.
- Provenance, exact versions, receipts, stable subasset mapping and authored override safety are non-negotiable.
- Codec licensing verified per file and build; KTX-Software optional non-open ETC decoder excluded unless expressly cleared.
- Honor CPU/RAM/frame budgets and headless, Windows/Linux/macOS/Web target constraints.

## CONSTRAINTS
No versioned C++ file or runtime state in P00 docs; free GitHub Actions for public repository, no paid dependency or required human reviewer, no CodeRabbit, bypass, force push, secret or trademarked external game model copying. Only current necessary research WO.

## ACCEPTANCE CRITERIA
- [ ] Docs detail conversion fidelity policies and glTF `extensionsRequired` handling.
- [ ] Tech/license matrix compares at least fastgltf, cgltf, Assimp, KTX/Basis and USD, with mixed-license ETC decoder caveat.
- [ ] Public semantic API typed with receipts, source/options digests, stable subassets and import/reimport preview/commit.
- [ ] Security threat model covers hostile URIs and parsers, worker isolation, quota, staged writes and fault recovery.
- [ ] 20 future scenarios include 2D/3D/texture/animation/audio, idempotence/override conflicts, macOS/Web, low-end perf and MCP denial.
- [ ] ADR-0011 remains PROPOSED; issue #26 and 80-WO registry not executable.
- [ ] Real docs-validation PASS on exact HEAD; Evidence Bundle, full diff and pt-BR independent objective audit.
- [ ] Squash merge normal and checkpoint reconciliation via same WO before next research.

## TESTS
Current: documentation links and Source Pack validation, 80-module dependency DAG, 80 WOs validator and read-only blocked selector via free GitHub CI. No code, GPU, compiler, decoder, fuzzing or benchmark executed. Future IMP-001..020 are specifications only.

## DELIVERABLES
Detailed architecture, matrix, ADR-0011, semantic import API, 20-test plan, this WO, docs/Architecture/Backlog/blocked issue links, Evidence Bundle, reviewed PR and post-merge checkpoint proposal.

## REVIEW FORMAT
Final audit in pt-BR: APPROVED / CORRECTION REQUIRED / BLOCKED; base/head SHA and source fingerprints, diffs/tests run/unrun, license/third-party rights, security/privacy/performance/regression risks and proposed checkpoint delta.

## STOP CONDITION
Current sources STALE, unauthorized C++/dependency, missing license caveats, unsafe plugin/network plan, silent data loss, known HIGH/CRITICAL, failed CI, unreviewed scope/ADR change or user payment. Correct only the same WO/PR.

## CONTEXT LOCK
BASE `b477dbecacc733a251666644ac05173f9390d159`. Capture critical Git blob fingerprints in Evidence Bundle (do not misstate them as SHA-256). Future executable WO must refresh base and SHA-256 source fingerprints.
