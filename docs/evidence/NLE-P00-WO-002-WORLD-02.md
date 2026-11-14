# Evidence Bundle — NLE-P00-WO-002-WORLD-02 Prefab Research

**State:** DRAFT RESEARCH PR/CI/AUDIT PENDING | Research issue #162 | Future code #42 OPEN/BLOCKED.  
**BASE main:** 1871b4adc99eb82e79890af5e7a423d8db202daa. Branch docs/NLE-P00-WO-002-WORLD-02-prefab-research. No engine/editor/runtime/source assets, actual scene save/reopen, prefab propagation or performance test executed.

## Source and dependency context
- Canonical hierarchy checked: Checkpoint > Decisions/approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS/catalog/registry/blocked #42 packet; WORLD-01 research #159 and PR #160+checkpoint #161 integrated. At baseline **23/80 research documented, 57 pending**, including historical CORE-04 gap, and all 80 code WOs BLOCKED/executor_ready=false.
- Future code WORLD-02 deps WORLD-01+DATA-02 are NOT implemented; DATA-04 journaling/runtime not proven. No premature code branch or scope expansion.
- Official references: Godot 4.6 PackedScene/Node.owner and MIT license; Unity 6 nested/variants/Apply-Revert under proprietary editor terms; OpenUSD public composition graphs/strength, upstream source LICENSE = **Tomorrow Open Source Technology License 1.0 (not plain Apache2)** plus third-party notices; O3DE core Apache-2.0 OR MIT and independent third parties. These are design/license references only, no third-party package/asset installed.
- Research design: stable NodeGuid/PrefabId/InstanceId and WORLD-01 EntityGuid/Handle separation; source scene tree + prefab DAG; nested/variant sparse overrides and field-level base/ours/theirs 3-way merge, deterministic propagation, DATA-04 CAS undo/redo+crash recovery and separate runtime publish, CORE-05 transform semantics, scoped Editor/CLI/MCP. SIOP optional PROVE-OR-DROP only.

## Research evidence truth
- Expected 11 docs-only research files: 8 new architecture, matrix, ADR-0027, typed API, 122 future cases, benchmark, WO and Evidence; 3 additive Architecture/Backlog/future #42 packet. **Registry/checkpoint NOT touched in research PR**.
- Research PR exact HEAD CI and security checks: **PENDING**.
- Objective pt-BR documentary audit/normal merge and readback: **PENDING**.
- **All 122 tests FUTURE NOT EXECUTED**, no real save/reopen, scripted merge, undo, serializer, graph code, C++ memory, native/Web build, performance p50/p95/p99 or security fuzz. No claim of lossless prefab propagation achieved. ADR-0027 PROPOSED, release class UNDECIDED and approved_adr=null.
- Risk LOW docs; future ELEVATED authoring loss, link/cycle fraud, buffer exhaustion, source/runtime publication race, metadata security, external dependency license compliance.

## Proposed checkpoint delta — NOT APPLIED
Only after exact-final-HEAD Docs Validation and scope/security/license audit APPROVED plus squash research PR/main readback, open separate **same-WO** checkpoint PR: change ONLY WORLD-02.research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED, canonical checkpoint/backlog/WO/EB receipts; all 80 coding WOs BLOCKED, 0 executor-ready, #42 coding OPEN/BLOCKED, ADR-0027 PROPOSED, historical CORE-04 still pending. WORLD-03 only after independent checkpoint CI/audit/normal squash/readback.
