# Research Work Order — NLE-P00-WO-002-DATA-04

**Research issue:** #117 | **Future implementation issue:** #27 (BLOCKED) | **Date:** 2026-11-14
**Status:** APPROVED / MERGED FOR RESEARCH DOCUMENTS ONLY (PR #118) | **ADR-0012:** PROPOSED, NOT IMPLEMENTED
**Context Lock base main:** 3f03773cf5ca9cba0d2ebda4b6c142f0fc93e45d; last approved research DATA-03/PR #116.
**Risk:** LOW docs; future ELEVATED persistence/migration/data loss.

## OBJECTIVE
Specify a practical, innovation-conscious yet safe DATA-04 scene/project serialization architecture with stable identity, schema evolution, semantic ID-aware diff/merge, safe rollback and Editor/CLI/MCP parity so the future Zcode executor can code approved contracts rather than decide the architecture.

## CONTEXT
No engine code exists. Approved owner directions: source pack, 80 module blocked implementation packets, Windows/Linux/macOS editor/exports, Web target, manual editor + native AI/MCP authoring, free public CI, no public MVP until 1.0 DoD, solo audit with no mandatory human reviewer/CodeRabbit. CORE-05 and DATA-01..03 research done only as docs. Their future executable dependencies remain blocked.

## SCOPE
- Detailed model of SceneDocument, SceneIR, stable SceneId/EntityId/ComponentInstanceId and DATA-02 AssetRef.
- Textual JSON/JSON Schema vs JSON5/TOML/YAML, nlohmann/simdjson; compare FlatBuffers/Protobuf/Cap'n Proto and owned chunked DATA-05 outputs without selecting an untested runtime binary stack.
- Versioned schema and unknown plugin optional/required handling, numeric/Unicode/canonical hash policies, format changes and compatibility.
- Stable typed semantic patch/diff/three-way merge with revision preconditions and scoped permissions for Editor/CLI/MCP.
- Safe staged migrations, explicit rollback/restore, journal across VFS+registry, fault recovery and no silent downgrade.
- ADR-0012 PROPOSED, semantic contract, 20 future tests, licensing matrix, evidence and links, objective pt-BR audit.
- SSD proprietary innovation hypothesis must be prove-or-drop, no duplicate source of truth.

## OUT OF SCOPE
No C++ serializer, migration, runtime schema compiler, external codec, CMake edits, import of user projects, databases, cloud, deployment, auth settings, paid services, CodeRabbit, mandatory external reviewer or release. Do not flip any of the 80 implementation WOs to READY.

## FILES / SOURCES TO READ
In order: docs/11-checkpoint.md; docs/10-decisions-ledger.md + approved ADRs; docs/03-scope.md; docs/09-definition-of-done.md; docs/04-architecture.md; docs/02-requirements.md; docs/00-source-hierarchy.md; AGENTS.md; docs/product/module-catalog.md; DATA-01/02/03 architecture, contracts, ADRs and DATA-04 blocked future WO; official library/standard source/license pages.

## REQUIREMENTS
GOV-001..005; CAP-008,009,010,011,012,013,014,016; NFR-001..005; owner NLE-D013..020; catalog DATA-04 acceptance round-trip equivalence, structured diff and tested migration (future proof, not existing).

## ARCHITECTURE RULES
- DATA-01 VFS only; DATA-02 AssetId/registry authority; DATA-03 import receipts; CORE-05 precision; DATA-05 runtime packaging; WORLD/EDIT/AI consumers.
- Native third-party types must not become engine public ABI or imply locked schema.
- Explicit unknown optional preservation, unknown required failure, IDs, order semantics and safe numeric representation.
- No filesystem+SQLite ACID assumption; versioned staged recovery receipts/backup before migration.
- MCP typed, capability-scoped, preview-before-write; no unrestricted raw scene editing, scripts, host path or SQL.
- Source and runtime binary format needs different requirements and benchmarking.

## CONSTRAINTS
Document-only P00; free GitHub Actions checks; correct citations/licensing; do not override approved owner decisions; no secrets; no destructive project operations; no force-push or protected rules bypass. Stop for STALE context or HIGH/CRITICAL unresolved.

## ACCEPTANCE CRITERIA
- [ ] Architecture specifies scene source of truth, ID/reference and order semantics for 2D/2.5D/3D.
- [ ] Technology matrix compares readable formats/JSON validation and FlatBuffers/Protobuf/Cap'n Proto, with license/safety gates and no fake measured ranking.
- [ ] Semantic API defines read/validate/diff/patch preview+commit/migration plan+commit/recovery with typed errors/authorization.
- [ ] Threat model addresses malicious documents, plugin unknowns, stale revisions, race, data loss, staged migration and rollback.
- [ ] At least 20 future tests include golden roundtrip, Web/macOS, MCP denial, migration crashes and p95/p99 measurement plan.
- [ ] ADR-0012 PROPOSED and issue #27/80 queue entries remain BLOCKED and executor_ready=false.
- [ ] Docs-only diff/links pass real GitHub Actions docs-validation on exact final PR HEAD; objective pt-BR audit and Evidence Bundle.
- [ ] After approval: normal squash merge, readback, separate same-WO checkpoint reconciliation before DATA-05.

## TESTS
Now: public free docs-validation, links/source pack, module dependency DAG, 80-WO registry and blocked-selector. Future SER-001..020 are NOT RUN; no C++ build, fuzz, numeric fixture, platform or runtime benchmark exists.

## DELIVERABLES
docs/architecture/data-04-serialization-scene-format.md; docs/research/data-04-scene-technology-matrix.md; docs/adr/0012-data-04-scene-schema-policy.md; docs/contracts/data-04-scene-api.md; docs/testing/data-04-acceptance-matrix.md; research WO, queue-context links, Architecture/Backlog references, Evidence Bundle, PR with audit and same-WO checkpoint delta proposal.

## REVIEW FORMAT
Audit in Brazilian Portuguese, explicit APPROVED/CORRECTION REQUIRED/BLOCKED, SHA base/head, files/CI commands and outcomes, licensing/security/data-integrity concerns, untested gates, and Checkpoint Delta. No claims of installed dependency or engine functionality.

## STOP CONDITION
Invalid canonical context, unapproved ADR promotion, partial/lossy migration or unsafe external input plan, missing required evidence, HIGH/CRITICAL, paid/secret/destructive action, failed CI or code outside docs. Corrections only same WO/PR.

## CONTEXT LOCK
Base main: 3f03773cf5ca9cba0d2ebda4b6c142f0fc93e45d. Critical Git blob object IDs (not SHA-256) to be listed in Evidence Bundle. Before future implementation, recompute base and actual SHA-256 file fingerprints, exact tests/paths, approvals and architecture.

## CHECKPOINT
Executor can propose, not promote. Following audit and squash merge, reconcile checkpoint/registry/evidence for DATA-04 under this same WO in a separately checked docs-only PR. Only then consider DATA-05.
