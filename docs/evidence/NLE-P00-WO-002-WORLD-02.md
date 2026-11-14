# Evidence Bundle — NLE-P00-WO-002-WORLD-02 Prefab Research

**State:** RESEARCH DOCUMENTATION APPROVED/MERGED AFTER CORRECTION; CHECKPOINT PR PENDING INDEPENDENT EXACT-HEAD CI/AUDIT | Research issue #162 | Future code #42 OPEN/BLOCKED.  
**BASE main:** 1871b4adc99eb82e79890af5e7a423d8db202daa. Branch docs/NLE-P00-WO-002-WORLD-02-prefab-research. No engine/editor/runtime/source assets, actual scene save/reopen, prefab propagation or performance test executed.

## Source and dependency context
- Canonical hierarchy checked: Checkpoint > Decisions/approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS/catalog/registry/blocked #42 packet; WORLD-01 research #159 and PR #160+checkpoint #161 integrated. At baseline **23/80 research documented, 57 pending**, including historical CORE-04 gap, and all 80 code WOs BLOCKED/executor_ready=false.
- Future code WORLD-02 deps WORLD-01+DATA-02 are NOT implemented; DATA-04 journaling/runtime not proven. No premature code branch or scope expansion.
- Official references: Godot 4.6 PackedScene/Node.owner and MIT license; Unity 6 nested/variants/Apply-Revert under proprietary editor terms; OpenUSD public composition graphs/strength, upstream source LICENSE = **Tomorrow Open Source Technology License 1.0 (not plain Apache2)** plus third-party notices; O3DE core Apache-2.0 OR MIT and independent third parties. These are design/license references only, no third-party package/asset installed.
- Research design: stable NodeGuid/PrefabId/InstanceId and WORLD-01 EntityGuid/Handle separation; source scene tree + prefab DAG; nested/variant sparse overrides and field-level base/ours/theirs 3-way merge, deterministic propagation, DATA-04 CAS undo/redo+crash recovery and separate runtime publish, CORE-05 transform semantics, scoped Editor/CLI/MCP. SIOP optional PROVE-OR-DROP only.

## Canonical BASE Git blob fingerprints (NOT raw file SHA-256)
- Checkpoint docs/11-checkpoint.md: `61cb5373ed25f8dbbf02cb14c34b0b9c5392275d`
- Ledger docs/10-decisions-ledger.md: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope docs/03-scope.md: `4ef605c74632ece080b2650e37dd83a415b63310`
- DoD docs/09-definition-of-done.md: `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture docs/04-architecture.md: `70bafe80f9f8d3c0fa949ce0077d2f83e65e91a8`
- Future packet docs/queue/work-orders/WORLD-02.md: `a9b49f9fbdf81a504de7bf3fc6704ee57ad01eb3`
These are version control Git object hashes, not SHA-256 of source contents. Executor must compute raw SHA-256 after future code approvals and re-lock when canonical sources change.

## Research evidence truth
- Expected 11 docs-only research files: 8 new architecture, matrix, ADR-0027, typed API, 122 future cases, benchmark, WO and Evidence; 3 additive Architecture/Backlog/future #42 packet. **Registry/checkpoint NOT touched in research PR**.
- [Research PR #163](https://github.com/KayzenRoot/stormline/pull/163) initial HEAD `5c8fc2ce357f8ebef885f0dcb57a84199893f7f8` had [Docs Validation #43635576110](https://github.com/KayzenRoot/stormline/actions/runs/43635576110) **FAILURE** due to 22 escaped Markdown backticks in `docs/work-orders/NLE-P00-WO-002-WORLD-02.md`; fetched job #132571515546 log proves `escaped Markdown code-fence marker`. **Correction Delta:** replace escaped markers with valid Markdown inline code markers, same WO/PR, no scope/architecture change. After correction, NEW exact final HEAD CI required, not yet claimed success.
- [Research PR #163](https://github.com/KayzenRoot/stormline/pull/163) final audited HEAD 07045d868d96088c9897a78391fe92f2ef4fd1ca, [Docs Validation #43635712447](https://github.com/KayzenRoot/stormline/actions/runs/43635712447) SUCCESS on exact final HEAD with Socket/SonarCloud PASS. First failed [Docs Validation #43635576110](https://github.com/KayzenRoot/stormline/actions/runs/43635576110) corrected 22 escaped Markdown markers on SAME WO/PR, no bypass. Pt-BR objective audit APPROVED doc-only no known HIGH/CRITICAL; normal squash main f278b46d6bf67f3751125e81af9e4346e7eced76. Checkpoint requires its own new PR/CI/audit.
- **All 122 tests FUTURE NOT EXECUTED**, no real save/reopen, scripted merge, undo, serializer, graph code, C++ memory, native/Web build, performance p50/p95/p99 or security fuzz. No claim of lossless prefab propagation achieved. ADR-0027 PROPOSED, release class UNDECIDED and approved_adr=null.
- Risk LOW docs; future ELEVATED authoring loss, link/cycle fraud, buffer exhaustion, source/runtime publication race, metadata security, external dependency license compliance.

## Proposed checkpoint delta — NOT APPLIED
Only after exact-final-HEAD Docs Validation and scope/security/license audit APPROVED plus squash research PR/main readback, open separate **same-WO** checkpoint PR: change ONLY WORLD-02.research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED, canonical checkpoint/backlog/WO/EB receipts; all 80 coding WOs BLOCKED, 0 executor-ready, #42 coding OPEN/BLOCKED, ADR-0027 PROPOSED, historical CORE-04 still pending. WORLD-03 only after independent checkpoint CI/audit/normal squash/readback.

## Checkpoint reconciliation proposal, separate same-WO PR
Only WORLD-02.research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED; registry research total 24/80 documented = 30%, remaining 56 pending incl old CORE-04. Preserve all 80 work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null and release_class UNDECIDED, code #42 OPEN/BLOCKED and ADR-0027 PROPOSED. 122 future tests NOT EXECUTED, no actual scene runtime, undo/redo, native/Web test or benchmark. Exact HEAD Docs Validation/audit and main readback separate before WORLD-03.
