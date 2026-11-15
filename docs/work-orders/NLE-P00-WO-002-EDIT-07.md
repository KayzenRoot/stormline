# NLE-P00-WO-002-EDIT-07 — Debug, Profiling & Preview P00 Documentary Research Work Order

**2026-11-15 | Research [#276](https://github.com/KayzenRoot/stormline/issues/276) | catalog_order=56 | future implementation [#74](https://github.com/KayzenRoot/stormline/issues/74) OPEN/BLOCKED | BASE main `64c7ea06a547742209cd11f5d949ab9c8989aa66`.** Baseline 55/80 research documented (68.75%), 25 pending; zero engine, all 80/80 implementation WOs BLOCKED. Formal deps **EDIT-01 + CORE-06**, both only documentary/ADRs PROPOSED; code #68/#23 OPEN/BLOCKED. Research-doc risk LOW; future PIE/observability ELEVATED, raw memory dump/remote attach/export HIGH_ASSURANCE and OUT OF SCOPE.

## OBJECTIVE
Research professional isolated Play-in-Editor, breakpoints/step/watch, deterministic replay, CPU/GPU/render/memory/audio inspectors, CORE-06 diagnostic/tracing/crash/privacy, project->subsystem->asset traceability, EDIT-01 button conventions, Web/native/headless capability, typed owner contracts, security/license, exactly 128 FUTURE tests and reproducible benchmark. **NO engine code, dependency adoption or instrumentation implemented.**

## CONTEXT
Canonical priority checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > remaining docs. Actual baseline main `64c7ea06a547742209cd11f5d949ab9c8989aa66`, compare identical, no open PRs at Source Check. Registry 80 modules, 55 research documented, 25 pending; EDIT-07 `research_status=RESEARCH_PENDING`, code `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`. Research issues #252 EDIT-01 and #105 CORE-06 CLOSED after proof, but actual implementation #68/#23 still OPEN/BLOCKED. No runtime/debugger/toolkit/crash collector.

## SCOPE — exactly eight NEW Markdown files
1. [Architecture](../architecture/edit-07-debug-profiling-preview.md).
2. [ADR-0059 PROPOSED](../adr/0059-edit-07-isolated-debug-profile-preview.md).
3. [Technology/license/security/platform matrix](../research/edit-07-debug-profile-technology-license-matrix.md).
4. [Typed debug/session/asset correlation/command API](../contracts/edit-07-debug-profile-api.md).
5. [Exactly 128 E07-T001..E07-T128 FUTURE tests](../testing/edit-07-acceptance-matrix.md).
6. [Reproducible benchmark/fault protocol](../research/edit-07-debug-profile-benchmark-protocol.md).
7. This Work Order.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-EDIT-07.md).

Research PR adds exactly eight NEW Markdown only; no changes to checkpoint/backlog/registry/CI/SDK/code. After exact-final-HEAD Docs Validation + objective pt-BR audit, ordinary squash merge and main/API readback, make a **separate five-file checkpoint PR**: checkpoint, backlog, registry (SOLE EDIT-07 research_status), this research WO and Evidence. Target 56/80 researched (**70%**), 24 pending, zero engine, all 80 code WOs blocked; independent CI/audit/squash/readback. Close research issue #276 only after checkpoint readback. Optional independent four-Markdown historical closeout PR requires own CI/audit/squash/readback. Do not start EDIT-08 until readback if closeout used.

## OUT OF SCOPE
Native editor/runtime/SDK code; profiler/crash/GPU capture integration; new logging/trace/counter schema; alternate asset database; process attach; raw memory access/export; crash dump uploading; remote telemetry/listeners; arbitrary watch/conditional script evaluation; debugger injection; cloud crash/AI autonomous writes; toolkit/lib/codecs install; unrelated cleanup; paid CI, CodeRabbit, external reviewer mandate, bypass/force push; engine license/release class approval; fabricated security/performance/OS proof. Code issue #74 must remain OPEN/BLOCKED.

## FILES / SOURCES TO READ
In order: `docs/11-checkpoint.md`, `docs/10-decisions-ledger.md` + approved ADRs, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/04-architecture.md`, `docs/02-requirements.md`, `AGENTS.md`, `docs/product/module-catalog.md`, `docs/queue/implementation-registry.json`, `docs/queue/work-orders/EDIT-07.md`.
Formal owner docs: `docs/architecture/edit-01-editor-shell-workspace.md`, `docs/adr/0053-edit-01-toolkit-neutral-editor-shell.md`, `docs/contracts/edit-01-editor-shell-api.md`, `docs/architecture/core-06-diagnostics-observability.md`, `docs/adr/0008-core-06-observability-policy.md`, `docs/research/core-06-technology-matrix.md`. Integration: EDIT-02/03/05/06, GAME-02, GFX-01/02/03/07, AUD-01/03, CORE-01/02/03/04, DATA-01/02/04/05, QA-03/04, AI/MCP. Official sources in matrix: Tracy, Perfetto, spdlog, RenderDoc, Vulkan Validation Layers, PIX, Xcode Metal, W3C WebGPU, Crashpad/Breakpad and CDP.

## REQUIREMENTS
GOV-001..005; CAP-008 Editor versioned assets, CAP-009 scalable performance, CAP-010 extensibility/diagnostics/tests, CAP-011 2D/2.5D, CAP-012 Web support, CAP-013 typed AI/MCP, CAP-014 complete 1.0 release DoD only, CAP-016 Windows/Linux/macOS, NFR-001..005, NLE-D013..020 as applicable. Catalog acceptance: **"Erro rastreável do projeto até subsistema e asset."** Requires real induced failure, project grant, subsystem owner, exact AssetId/revision and independent readback, not a mock path. Source license NLE-D009 OPEN.

## ARCHITECTURE RULES
EDIT-07 owns view/orchestration only; formal deps EDIT-01 (shell/CommandIds/accessibility) + CORE-06 (event/span/counter/crash/export/retention/privacy). No added DAG edge. CORE-06 currently lacks formal ProjectId/AssetId in CorrelationContextV1; propose **CORE-06/DATA-02-owned versioned typed extension** or bounded attributes, do not invent independent events. PIE runs same runtime evaluator on frozen source with proved isolation; no project writes or privileged side effects. GAME-02 owns script debug hooks, DATA-02 resolves AssetId, GFX owns capture/device/fence, AUD owns XRUN/sample clock and callback-safe stats. No arbitrary eval/process memory. All actions use EDIT-01 shared semantic commands with GUI/CLI/MCP authorization. Default local/offline/no telemetry/upload.

## CONSTRAINTS
Docs-only risk LOW. Canonical fingerprints below are **Git blob object SHA-1, not byte SHA-256**. If checkpoint, Scope, DoD, Architecture or approved ADR changes, lock STALE -> rebase/re-audit before write. No upgrade of proposed ADR into approved status, hidden listener, package install, benchmark result or engine code. All 80 implementation packets stay BLOCKED.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight new Markdown files and no unrequested existing-file changes.
- [ ] ADR-0059 PROPOSED; formal DAG EDIT-01 + CORE-06 unchanged; CORE-06 diagnostic owner not duplicated.
- [ ] Explicit owner-owned ProjectId/AssetId correlation gap, typed authorization/missing-state requirements.
- [ ] PIE isolation, same-owner runtime replay, breakpoint/watch safety and owner-specific CPU/GPU/memory/audio inspector contracts.
- [ ] EDIT-01 accessible button registry, disabled reasons, focus/IME, progress/cancel and GUI/CLI/MCP parity.
- [ ] Native/Web/headless/tool/license/privacy matrix with no false Metal/RenderDoc/WebGPU or Crashpad claims.
- [ ] 128 unique E07-T001..E07-T128 FUTURE/NOT EXECUTED tests and benchmark thresholds TBD.
- [ ] Research PR exact-final-HEAD Docs Validation SUCCESS; 8-file diff, pt-BR objective audit APPROVED, no HIGH/CRITICAL, normal squash/readback.
- [ ] Separate checkpoint PR exactly 5 files, **only EDIT-07.research_status** changes in registry, own exact-head CI/audit/merge/readback, all 80 code WOs blocked.
- [ ] Optional four-doc closeout own gates; #276 closes only after checkpoint readback, #74 stays OPEN/BLOCKED.

## TESTS
Existing Docs Validation on exact final PR HEAD: Source Pack/local link validation, module catalog/DAG, registry schema and blocked Zcode selector. Verify exact 8 new files, 128 unique E07 IDs and all FUTURE/NOT EXECUTED. No local test assertion without actual checkout/run. Future runtime tests/benchmarks are documented only.

## DELIVERABLES
Eight Markdown docs, research issue/branch/PR, exact Git base/head/diff, CI job evidence, pt-BR audit, risks, checkpoint delta proposal and readback. No runtime code, profiler/GPU trace/minidump or approved implementation WO.

## REVIEW FORMAT
Pt-BR verdict APPROVED/CORRECTION REQUIRED/BLOCKED; base/head; eight changed paths; 128 test IDs/count; exact CI run/steps; ownership/asset correlation/preview/privacy/license/OS/a11y audit; HIGH/CRITICAL; fixes; checkpoint delta and stop condition.

## STOP CONDITION
Stop for stale source, unexpected file diff, DAG inflation, duplicate CORE-06 schema, false AssetId provenance, unsecured preview, arbitrary eval/remote listener/raw dump, unsupported GPU/OS promise, missing license/consent, CI failure, count mismatch, HIGH/CRITICAL or any code unblock.

## CONTEXT LOCK — VERIFIED P00 BASE
Current main `64c7ea06a547742209cd11f5d949ab9c8989aa66`. Git blob SHAs (Git objects, **not SHA-256 bytes**):
- Source Hierarchy `58a377bc76cafdd3377d733d4f30ef53661bb034`
- Checkpoint `87e85e86448b6ea9f4142d50d771eca5458fda91`
- Decisions Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope `4ef605c74632ece080b2650e37dd83a415b63310`
- DoD `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`
- Module catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- Implementation registry `e87af86863eb5b461727e09130162bd90e92d829`
- EDIT-07 blocked implementation packet `690c0de8fd0916eaeb9d923da29f9f1d258d9fd8`
- CORE-06 architecture/ADR/matrix `12893dcb7bcd7c263f979a3b12202126e5791491` / `208f12cee3538c4d1471d8a2de937e9b9ed754b9` / `40e4022e6b4445ea587bb12ac6fa8994dd878aef`
- EDIT-01 architecture/ADR/API `d8eb653afb1734746775cd4133462976140bcd7c` / `6cc58d33531a5bd761fe0d61a4d11cf4329b2fb5` / `e2c713c6666f0521f44b1d0920b1a696391844d7`
- EDIT-06 architecture/API `6a5154b938e86b706b97334ff76bc865a58de413` / `7a3fe7babb6911930fc0603920bcb7d415d1b9c7`

Re-fetch critical inputs and compare current HEAD before any write. If changed, mark Context Lock STALE; no blind promotion.

## EVIDENCE BUNDLE
See [Evidence](../evidence/NLE-P00-WO-002-EDIT-07.md). Record only observed diff, hashes, CI, audit, merge and actual readback. A successful check suite is not a profiler/GPU/runtime benchmark.

## Research PR #277 APPROVED/MERGED and checkpoint PR initiated
- [Research PR #277](https://github.com/KayzenRoot/stormline/pull/277): BASE `64c7ea06a547742209cd11f5d949ab9c8989aa66`, audited final HEAD `e8a7ba59405d9e04eed809d584b3db1c050f0f2d`, exactly eight NEW Markdown. [Docs Validation #43745473379](https://github.com/KayzenRoot/stormline/actions/runs/43745473379) SUCCESS job #132907698119, all Source Pack/links, DAG, registry and blocked Zcode selector SUCCESS. [Pt-BR audit #6899000403](https://github.com/KayzenRoot/stormline/pull/277#issuecomment-6899000403) APPROVED documentary only; normal squash and factual main/API readback `432e561d526b7cf3044d3d26cf762fefe50ec1a1`. No engine, SDK, CI, checkpoint, backlog or registry mutation in research PR.
- E07 128 IDs unique FUTURE/NOT EXECUTED. ADR-0059 PROPOSED, NLE-D009 OPEN, #74 OPEN/BLOCKED. CORE-06 typed ProjectId/AssetId correlation is still owner extension request; no live asset tracing/PIE/debugger/runtime/benchmark.
- Independent checkpoint PR starts from main `432e561d526b7cf3044d3d26cf762fefe50ec1a1`, exactly checkpoint/backlog/registry/this WO/Evidence. Sole registry delta EDIT-07 research_status; own CI/audit/merge/readback before #276 closure. Target 56/80 (70%), 24 pending, all 80 code WOs BLOCKED.

## Checkpoint PR #278 approved/merged/read back; research #276 closed (factual)
- [PR #278](https://github.com/KayzenRoot/stormline/pull/278): BASE `432e561d526b7cf3044d3d26cf762fefe50ec1a1`, final HEAD `4c2650bc6df248fbe3d375d9e70940aadac40570`, exactly five-file checkpoint. [Docs Validation #43745783965](https://github.com/KayzenRoot/stormline/actions/runs/43745783965) SUCCESS job #132908644831; [pt-BR audit #6899038210](https://github.com/KayzenRoot/stormline/pull/278#issuecomment-6899038210) APPROVED DOCUMENTS ONLY. Normal squash + factual main readback `7131b47a7dd25e986816b8a0c7b8bfe5d813bd18`, actual registry 56/80 researched/24 pending/all 80 code WOs blocked; [readback #6899045549](https://github.com/KayzenRoot/stormline/pull/278#issuecomment-6899045549). Research issue #276 CLOSED after readback; future code #74 OPEN/BLOCKED.
- ADR-0059 PROPOSED, NLE-D009 OPEN, 128 E07 FUTURE/NOT EXECUTED, zero runtime/debugger/profiler/GPU/a11y benchmarks. CORE-06 typed ProjectId/AssetId asset-correlation owner extension remains future. Historical closeout changes only four Markdown; own CI/audit/squash/readback necessary.
