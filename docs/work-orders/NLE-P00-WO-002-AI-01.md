# NLE-P00-WO-002-AI-01 — Headless Command Kernel P00 Documentary Research Work Order

**2026-11-15 | research [#281](https://github.com/KayzenRoot/stormline/issues/281) | catalog_order=57 | future code [#75](https://github.com/KayzenRoot/stormline/issues/75) OPEN/BLOCKED | BASE main `dd59a60d4280884dacbb2ec1834a4a5023d9b90c`.** 56/80 researches documented (70%) at Source Check, 24 pending, zero engine; 80/80 future implementation WOs BLOCKED. Formal deps **WORLD-02 + DATA-04 + GAME-02** (only documentary/ADRs PROPOSED, code issues #42/#27/#58 OPEN/BLOCKED). Risk LOW for docs; future source mutation/migration ELEVATED, privileged build/export/remote/irreversible actions HIGH_ASSURANCE separate approval.

## OBJECTIVE
Document a versioned Stormline-owned headless semantic command kernel for **create/open/edit/validate/build/export**, with identical source authority for Editor GUI buttons, CLI/headless, MCP/AI and tests, preserving WORLD-02 scene/prefab semantics, DATA-04 source CAS/journal/semantic digest and GAME-02 script/sandbox. Specify schema/command/receipt/authorization/idempotency/async jobs, current MCP 2026-07-28 vs legacy peer compatibility, security/license/platforms, 128 FUTURE tests and benchmark. **Catalog acceptance: "Mesma operação manual/CLI produz estado semanticamente igual."** No code or actual owner runtime exists.

## CONTEXT / SOURCE CHECK
Source Pack precedence: checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS > catalog/registry/blocked packet. Verified main identical `dd59a60d4280884dacbb2ec1834a4a5023d9b90c` before research; no open PRs. Registry 80 entries, 56 documented/24 pending; AI-01 RESEARCH_PENDING, code `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`. Formal predecessors' research documents and APIs read directly. Their code issues #42/#27/#58 still OPEN/BLOCKED. Engine license NLE-D009 OPEN, proposed technical choices not adopted. No actual command bus/CLI/MCP endpoints.

## SCOPE — exactly eight NEW Markdown docs
1. [Architecture](../architecture/ai-01-headless-command-kernel.md).
2. [ADR-0060 PROPOSED](../adr/0060-ai-01-shared-semantic-command-kernel.md).
3. [Technology/license/security/interop matrix](../research/ai-01-command-technology-license-matrix.md).
4. [Typed command/transaction/parity/job API](../contracts/ai-01-command-kernel-api.md).
5. [Exactly 128 unique A01-T001..A01-T128 future tests](../testing/ai-01-acceptance-matrix.md).
6. [Reproducible benchmark/crash/fault protocol](../research/ai-01-command-benchmark-protocol.md).
7. This Work Order.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-AI-01.md).

Research PR adds **only** these eight NEW Markdown; no code/CI/checkpoint/backlog/registry/SDK. After exact-final-HEAD Docs Validation success, objective pt-BR audit APPROVED, normal squash and main/API readback, independent **five-file checkpoint PR** updates checkpoint/backlog/registry (SOLE AI-01 research_status transition)/this WO/Evidence. Target 57/80 researched (71.25%), 23 pending, zero engine, all 80 coding WOs BLOCKED; separate exact-HEAD CI/audit/squash/readback. Research issue #281 closes only after factual checkpoint readback. Optional four-file historical closeout own gates, no advance to AI-02 until complete.

## OUT OF SCOPE
C++/Rust/TS source/runtime, compiled CLI/MCP server, code schema generator, scene/prefab engine, serializer or independent database, actual shell/build/export command, code deploy/signing, remote listener/cloud/LLM operation, granting all authoring capabilities, arbitrary script eval/OS paths, license selection, release class approval, paid CI, CodeRabbit, outside reviewers, force push/bypass, broad cleanup, and fabricated benchmark/platform/security results. Future implementation #75 and other 79 code issues remain blocked.

## FILES / SOURCES TO READ
Canonical:
`docs/11-checkpoint.md`, `docs/10-decisions-ledger.md`, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/04-architecture.md`, `docs/02-requirements.md`, `AGENTS.md`, `docs/product/module-catalog.md`, `docs/queue/implementation-registry.json`, `docs/queue/work-orders/AI-01.md`, `docs/product/ai-mcp-contract.md`.
Formal owners: `docs/architecture/world-02-scene-prefab-hierarchy.md`, `docs/contracts/world-02-scene-prefab-api.md`, `docs/adr/0027-world-02-prefab-override-rebase-policy.md`; `docs/architecture/data-04-serialization-scene-format.md`, `docs/contracts/data-04-scene-api.md`, `docs/adr/0012-data-04-scene-schema-policy.md`; `docs/architecture/game-02-gameplay-scripting-api.md`, `docs/contracts/game-02-gameplay-scripting-api.md`, `docs/adr/0043-game-02-engine-owned-capability-script-host.md`.
Integration: EDIT-01 API, EDIT-02/03, DATA-01/02/05, PLAT-01..06, AI-02..09, CORE-06 and QA. External official sources: JSON Schema Draft 2020-12, RFC8785 JCS, JSON-RPC2, MCP 2026-07-28 official release/TS v2 migration, CLI11, nlohmann-json, simdjson, Protobuf, FlatBuffers and per-file licenses.

## REQUIREMENTS
GOV-001..005; NLE-D013..020, especially NLE-D015 AI-native CLI/MCP and NLE-D018 delegated docs only; CAP-008 versioned asset authoring, CAP-009 performance tiers, CAP-010 extensibility/tests, CAP-011 2D/2.5D, CAP-012 Web, CAP-013 typed MCP for approved public authors, CAP-014 no public MVP until full 1.0 DoD, CAP-016 Windows/Linux/macOS, NFR-001..005. Catalog acceptance explicitly requires **actual GUI vs CLI same semantic authoring operation** on equal baseline state, owner validate/readback and reference integrity, not screenshots or successful JSONRPC response.

## ARCHITECTURE RULES
AI-01 is a bootstrap typed operation/router layer, not source/runtime authority. Formal DAG remains **WORLD-02 + DATA-04 + GAME-02**; no new dependency on AI-03/04/06/07 (downstream/circular). WORLD-02 owns stable scene/prefab IDs, 3-way overrides and source/runtime receipts. DATA-04 owns strict source SceneRevision/diff/CAS/journal/undo/recovery/canonicalization/digest. GAME-02 owns script API, VM sandbox/host grants and runtime receipts. EDIT-01 owns button command/focus, AI-03 future reflection must derive from same descriptor, AI-04 MCP adapter, AI-06 advanced policy, PLAT/DATA-05 build/export owner. Deny-by-default minimal owner-verified capability always required. No arbitrary eval, file/network/process, unapproved remote listener, shell or new parser of canonical source.

## CONSTRAINTS
Documentary risk LOW. Source fingerprints below are **Git blob object SHAs (SHA-1), NOT computed byte SHA-256**. If checkpoint, approved ADR, Scope, DoD or Architecture changes: Context Lock STALE, recompile/rebase, no blind writes. External MCP 2026-07-28 is **adapter-only**, do not assume every real host supports it; modern stateless vs 2025 handshake must be negotiated. No new enum or schema implies owner adoption, no truth claim of exactly-once network delivery. NLE-D009 OPEN, all 80 code WOs BLOCKED.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight NEW Markdown, scoped diff, no accidental code/CI/registry change in research PR.
- [ ] ADR-0060 **PROPOSED**, formal deps exactly WORLD-02/DATA-04/GAME-02, no alternate owner source.
- [ ] Typed CommandId/schema/Invocation/Receipt/Job, version/capability/actor/grant/rate/expected-revision/digest/cancel/error contracts.
- [ ] GUI/CLI/MCP thin adapters and EDIT-01 accessible button/shortcut/IME/disabled reason parity.
- [ ] DATA-04 durable CAS/idempotency/recovery, WORLD-02 stable-ID/3-way conflicts, GAME-02 script sandbox with no eval/shell; separate source and runtime publish receipts.
- [ ] Same-semantic-state oracle includes exact DATA-04 normalized graph/owner receipts, explicit ID remapping if allocated IDs differ, excludes only declared volatile fields.
- [ ] MCP 2026/legacy compatibility, optional Tasks and no implicit remote listener, privacy/security and versioned license matrix.
- [ ] Exactly **128 unique A01-T001..T128 FUTURE/NOT EXECUTED** tests and reproducible benchmark protocol with thresholds TBD.
- [ ] Research PR exact-final-HEAD Docs Validation SUCCESS (Source Pack/links, module DAG, registry and blocked Zcode selector), objective pt-BR audit APPROVED with no HIGH/CRITICAL, normal squash and main readback.
- [ ] Separate checkpoint PR only 5 modified files and sole AI-01 research_status transition, own exact-head CI/audit/squash/readback, all 80 code WOs blocked; close #281 only after main readback.
- [ ] Optional four-file historical closeout own gates; no AI-02 until current complete.

## TESTS
Docs Validation of Source Pack/local links, DAG, registry and Zcode selector on **exact PR HEAD**. Verify exactly eight new Markdown and 128 unique IDs. All runtime C++/CLI/MCP/OS/UI/source parity/benchmarks FUTURE/NOT EXECUTED. Never equate Docs CI with tested engine.

## DELIVERABLES
Eight Markdown documents, research issue/branch/PR, base/head/diff/CI job, pt-BR objective audit, risk and actual readback, proposed independent five-file checkpoint; no code, binary, build/export artifact or license selection.

## REVIEW FORMAT
Português brasileiro: APPROVED / CORRECTION REQUIRED / BLOCKED; base/head SHA; 8 file paths and 128 unique tests; CI run/job/steps, owner authority/schema/parity/idempotency/security/license audit; HIGH/CRITICAL, fixes, checkpoint delta and stop condition.

## STOP CONDITION
Stop on stale sources, unapproved library/license/ADR, DAG inflation/circular AI deps, duplicated serializer/script/world authority, auth bypass, shell/eval, cross-project leak, loss of source data, false semantic equality, implicit atomic multi-owner, runtime/build/export implementation claim, CI failure, 128 count mismatch, unexpected diff, HIGH/CRITICAL or code unblocking.

## CONTEXT LOCK — BASELINE RESEARCH, NOT CODE ACTIVATION
Verified main `dd59a60d4280884dacbb2ec1834a4a5023d9b90c`; critical Git blob object SHAs **SHA-1 object IDs, not SHA-256 file hashes**:
- Source Hierarchy `58a377bc76cafdd3377d733d4f30ef53661bb034`
- Checkpoint `93021721785eb64d7568ff7a4424c4cab4151213`
- Decisions Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope `4ef605c74632ece080b2650e37dd83a415b63310`
- DoD `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`
- Catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- Registry `44996b08005e7b7c2d26511612a08b17082db61b`
- AI-01 blocked code packet `4a6a28d6c4dfef1bbde37adef06d209f9e57025b`
- WORLD-02 architecture/API/ADR `e04b640df6e3741d324c33d5dd9735696ed69d98` / `c98ea5d49e3b792057c1d14706b9e2f4cfca9550` / `4207fc37a000b71bde17bb1ae92dafcaffeaffbe`
- DATA-04 architecture/API/ADR `7e88d4fecaa83c9922f255087df9f97f6300b61f` / `33b096149df35d20b3fe9e9d21e4bc6f22d71d5c` / `de48e3e586505c153d7240745da365ea28ab7f03`
- GAME-02 architecture/API/ADR `c5429cabdf14bc1e7dc8b3eac11e77274dc51776` / `3dd5ad89e25e7fd39779eded236f26ab2d4a282b` / `8e5750b1ff608fcdf66980206d011d93ffd1efce`
- Product AI/MCP contract `161183078034162ca458212e65a47cd17a112394`
- EDIT-01 API `e2c713c6666f0521f44b1d0920b1a696391844d7`

At every mutation refresh main and critical sources, mark STALE if drift. At code activation only, actual SHA-256 file fingerprints and full owner-approved implementations/DoD must be collected.

## EVIDENCE BUNDLE
See [Evidence](../evidence/NLE-P00-WO-002-AI-01.md), update solely from actual Git/CI/audit/readback. No suggested checkpoint is canonical until approved.

## Research PR #282 APPROVED/MERGED and checkpoint PR initiated
- [Research PR #282](https://github.com/KayzenRoot/stormline/pull/282): BASE `dd59a60d4280884dacbb2ec1834a4a5023d9b90c`, final HEAD `05372546a5342d830ed219f028d86b2d3f52c464`, exactly eight NEW Markdown. [Docs Validation #43756174999](https://github.com/KayzenRoot/stormline/actions/runs/43756174999) SUCCESS job #132940644361 (Source Pack/links, 80-module DAG, registry and Zcode blocked-selector checks all SUCCESS). [Pt-BR objective audit #6900529035](https://github.com/KayzenRoot/stormline/pull/282#issuecomment-6900529035) APPROVED documentary only; normal squash and factual main/API readback `70ecfab2fe1a82b5e7bdd38c256fd5564fd0c68f`. No code/SDK/CI/checkpoint/backlog/registry mutation in research PR.
- 128 A01 IDs unique FUTURE/NOT EXECUTED. ADR-0060 PROPOSED, NLE-D009 OPEN, future code #75 OPEN/BLOCKED. No running command kernel, CLI, MCP, GUI/CLI semantic parity, scene transactions, build/export, native/Web or benchmark tests.
- Independent checkpoint PR from main `70ecfab2fe1a82b5e7bdd38c256fd5564fd0c68f`, exactly checkpoint/backlog/registry/this WO/Evidence. Sole registry semantic delta AI-01 research_status to RESEARCH_DOCUMENTED_ADR_PROPOSED. Own CI/audit/merge/readback required before issue #281 closure. Target 57/80, 23 pending, zero engine, all 80 coding WOs BLOCKED.

## Checkpoint PR #283 APPROVED/MERGED and issue #281 CLOSED (factual)
- [PR #283](https://github.com/KayzenRoot/stormline/pull/283) BASE `70ecfab2fe1a82b5e7bdd38c256fd5564fd0c68f`, final HEAD `da3fe5a0ab6e81155e748e5c178ee74a929698a6`, exactly five-file checkpoint, sole AI-01 research_status delta. [Docs Validation #43756443653](https://github.com/KayzenRoot/stormline/actions/runs/43756443653) SUCCESS job #132941474062; [pt-BR audit #6900563971](https://github.com/KayzenRoot/stormline/pull/283#issuecomment-6900563971) APPROVED documentary only; normal squash/main readback `7a66be30e463be752328cb6808e8510d0851a732`, registry 57/80 researched/23 pending/all 80 code WOs blocked; [readback #6900570729](https://github.com/KayzenRoot/stormline/pull/283#issuecomment-6900570729). Research #281 CLOSED only after readback, future code #75 OPEN/BLOCKED.
- ADR-0060 PROPOSED, NLE-D009 OPEN, 128 A01 FUTURE/NOT EXECUTED, no actual kernel/CLI/MCP/GUI parity/build/export/native/Web/benchmark. Historical four-Markdown closeout PR has own CI/audit/squash/readback. Next catalog module after completed closeout is AI-02 Project Semantic Index (58/80), formal deps AI-01/DATA-02, no code unlock.
