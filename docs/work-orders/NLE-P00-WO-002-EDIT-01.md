# NLE-P00-WO-002-EDIT-01 — Editor Shell & Workspace Research Work Order

**2026-11-15 | research [#252](https://github.com/KayzenRoot/stormline/issues/252) | future coding [#68](https://github.com/KayzenRoot/stormline/issues/68) OPEN/BLOCKED | catalog_order=50 | BASE main `e35ef681e54bec467b4651da70787b6e78a17139`.** P00 DOCS ONLY, LOW documentary risk, future untrusted plugin/file/toolkit integration ELEVATED and privileged editor/AI/MCP HIGH_ASSURANCE where applicable. No code authorized.

## OBJECTIVE
Research original high-quality professional editor shell for Stormline on Windows/Linux/macOS including native windows, docking/panels/float/tear-off, safe persisted layouts/workspaces, monitor unplug/HiDPI, shortcuts/command palette/host undo, focus/selection/inspector host, project launcher, keyboard/IME/gamepad when relevant, accessibility/assistive technologies, integration of 2D/3D GFX render viewports, UI performance, plugin security and permitted AI/MCP. Compare Qt6, Dear ImGui, Slint, Tauri/WebView, wxWidgets, Nuklear and dependencies/license terms. Produce architecture, proposed ADR, versioned typed contracts, exactly 128 FUTURE tests and reproducible benchmark protocol, no runtime or toolkit adoption.

## CONTEXT
Predecessor NET-06 research/checkpoint/closeout PR #249/#250/#251 independently Docs Validation SUCCESS/objective pt-BR audit/normal squash/main readback, verified final main `e35ef681e54bec467b4651da70787b6e78a17139`. At base **49/80 research documented (61.25%), 31 pending, ZERO engine, all 80/80 coding WOs blocked**. EDIT-01's **only formal catalog prerequisite is CORE-01**, research/ADR PROPOSED, no actual window API implemented. GFX/CORE-06, EDIT-02/03/07, DATA-01/04, GAME-01/03, AI/MCP and QA-04 are distinct owner/integration contracts, NOT additional formal dependency graph edges. User-directed desktop Windows/Linux/macOS, no public MVP before full 1.0 DoD, manual editor with AI as optional authorized workflow.

## SCOPE
**Exactly eight NEW Markdown** in research branch `docs/NLE-P00-WO-002-EDIT-01-editor-shell`:
1. [Architecture](../architecture/edit-01-editor-shell-workspace.md)
2. [ADR-0053 PROPOSED](../adr/0053-edit-01-toolkit-neutral-editor-shell.md)
3. [Technology/license and OS matrix](../research/edit-01-editor-shell-technology-license-matrix.md)
4. [Typed semantic Editor Shell contracts](../contracts/edit-01-editor-shell-api.md)
5. [Exactly 128 FUTURE tests](../testing/edit-01-acceptance-matrix.md)
6. [Reproducible multi-OS benchmark protocol](../research/edit-01-editor-shell-benchmark-protocol.md)
7. This research Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-EDIT-01.md)

Research PR own **exact-final-HEAD Docs Validation**, objective pt-BR audit, ordinary squash/main+API readback. **Separate checkpoint PR** only checkpoint/backlog/implementation-registry sole EDIT-01 research_status/WO/Evidence, independent final HEAD CI/audit/squash/readback. Historical closeout four Markdown as necessary, own gates. After checkpoint **50/80 researched (62.5%), 30 pending, ZERO runtime**, all 80 coding WOs blocked, coding #68 OPEN/BLOCKED, research #252 closed only after checkpoint main proof. Do not plan next EDIT-02 until final audited closeout readback.

## OUT OF SCOPE
No engine/editor native code, Qt/ImGui/Slint/Tauri package/dependency, OS windows, GUI builds, compilers, plugin runtime, OS accessibility test, user project assets or personal data, copyright images/fonts, paid commercial license, test runner, WebView, GPU RHI creation, game simulation, 3D gizmo/terrain/scene editing, project file migration, automatic AI/MCP privileged action, release class selection. No CI bypass/force push, paid CodeRabbit/CI, external human review requirement. Future implementation coding issue #68 remains blocked.

## FILES / SOURCES TO READ
Source hierarchy: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` / approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/EDIT-01.md`. Read CORE-01 platform contracts and GFX viewport, CORE-06 diagnostics, EDIT-02 project manager, EDIT-07 preview, DATA-01/04 storage and AI/MCP capability plans where available. Official vendor Qt (QMainWindow/QAccessible/LGPL), Dear ImGui MIT+docking, Slint Royalty-free/GPL/commercial, Tauri MIT/Apache capabilities, wxWidgets wxWindows and Nuklear MIT/PD sources linked in technology matrix.

## REQUIREMENTS
GOV-001..005, NLE-D013..020, Scope/DoD/CAP/NFR as documented. Catalog acceptance **"Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis."** Means a **future real desktop editor demo and OS test**, not accepted by documents. No toolkit/legal license, OS implementation baseline, numeric frame/CPU p99, WCAG/a11y compliance, release class or risk approved. NLE-D009 engine license OPEN; ADR-0053 stays PROPOSED.

## ARCHITECTURE RULES
EDIT-01 owns only semantic shell/panel graph/keyboard commands/focus/accessibility/workspace UI state and viewport host lifecycle; CORE-01 real window/events/monitor OS, GFX real RHI/GPU, EDIT-02 project creation/conversion, EDIT-03 scene/inspector edits and undo transactions, EDIT-07 debug/play-in-editor, DATA-04 persistence CAS and last-known-good, DATA-01 VFS, CORE-06 diagnostics, AI/MCP same permissioned public command API. Never duplicate game clock/renderer/editable asset authority or rely on unsupported Wayland window position. Qt binary restoreState only if trusted compatible own state, no raw untrusted data. Strong keyboard/screen-reader path required for backend decision. No automatic selected toolkit or GPL obligations assumed compatible with unknown engine license.

## CONSTRAINTS
Document P00 only, no source/SDK/CI modification in research, zero proprietary paid license/service/CodeRabbit requirement, no mandatory external reviewer, no force/bypass/destructive changes. No UI claim without native build and actual assistive tests. No Windows/Linux/macOS portability conclusion from docs. All plugin/workspace assets untrusted with bounded decode and capabilities, AI/MCP no arbitrary shell/project writes, unsupported toolkit features explicit.

## ACCEPTANCE CRITERIA
- [ ] Exactly 8 **NEW Markdown** docs, internal links and official sources, no code/SDK/CI/registry/checkpoint changed in research PR.
- [ ] ADR-0053 **PROPOSED**, own semantic editor command/panel layout contract and comparative Qt6 vs Dear ImGui prototypes, neither adopted. Slint/Tauri/wxWidgets/Nuklear rights and OS constraints accurately described.
- [ ] Typed window/panel/dock/versioned workspace/focus/shortcut/undo/selection/a11y/viewport/extension/automation contracts, durable fallback, monitor hotplug and fail-closed untrusted restore.
- [ ] Licensed candidate matrix: Qt LGPLv3/GPLv3/commercial and module exceptions, Dear ImGui MIT+docking branch, Slint royalty-free attribution and alternatives, Tauri MIT/Apache+WebView, wxWidgets wxWindows 3.1, Nuklear MIT/PD; no engine code license selected and no distributed source.
- [ ] Exactly **128 unique E01-T001..E01-T128 FUTURE/NOT EXECUTED** cases, protocol for native Windows/Linux X11/Wayland/macOS monitors, DPI/IME/a11y/GPU and UI performance/format/security. All numbers candidate axes, no measured p99.
- [ ] Research PR exact-final-HEAD Docs Validation SUCCESS (Source Pack links, DAG, registry, Zcode selector rejects blocked), objective pt-BR audit APPROVED DOCS ONLY, normal squash/main+API readback.
- [ ] Separate checkpoint PR own exact-final-HEAD Docs Validation/audit/squash/main+registry readback, sole EDIT-01 `research_status=RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, target **50/80 research (62.5%), 30 pending, 0 runtime**.
- [ ] All 80 implementation packets `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`, coding #68 OPEN/BLOCKED, research #252 closed only after checkpoint actual main.
- [ ] Historical four-doc readback closeout with independent gates if used, no HIGH/CRITICAL introduced, no next code increment.

## TESTS
Only Docs Validation for each PR's final Git HEAD, Source Pack local link, DAG and registry/blocked selector plus **static 128 unique future IDs**. No native build, OS GUI, accessibility, docking, device loss, performance/security or actual test executed; benchmarks FUTURE.

## DELIVERABLES
Research issue #252, eight Markdown docs, research PR CI/audit/squash/main readback, separate checkpoint PR sole semantic registry state/own gates, optional historical four-doc closeout, Evidence Bundle and factual proposed/actual checkpoint delta. Future code #68 untouched.

## REVIEW FORMAT
Pt-BR `APPROVED / CORRECTION REQUIRED / BLOCKED`, exact base/head SHA and relevant Git blob fingerprints, scope and eight-file diff, CI run/job/steps, primary technical/license/accessibility and privacy risks, actual vs future 128 tests, GFX and OS targets not tested, HIGH/CRITICAL, rollback and checkpoint delta, all 80 locks. If correction, only same WO/PR scope.

## STOP CONDITION
Critical Source Pack/Scope/DoD/Architecture or approved ADR changed => STALE and rebase. Any selected toolkit without legal/accessibility/OS evidence, untrusted workspace deserialize, loss of accessible controls, unauthorized AI/MCP privilege, unplanned paid side effect, code edits, registry diff beyond status, 80 coding unlock, failed CI/audit or known HIGH/CRITICAL -> BLOCKED/CORRECTION REQUIRED, no next increment.

## CONTEXT LOCK (Git blob object hashes, not SHA256)
BASE main `e35ef681e54bec467b4651da70787b6e78a17139`; checkpoint `67554b247f96effb76f62383081dd5bbb7b47a86`; Decisions Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; Backlog `8252bfc23789d238473c2f42a58135e9968c2e`; registry `04d94c079772fca2698089c291aa8d5af98a9848`; catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; future coding WO `a364fe1a9ec15613bbc2ebad84aa2a5ad82276cb`; AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`. More dependency/target code hashes to be established after actual repo implementation; any approved canon change invalidates this lock.

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-EDIT-01.md) tracks actual PR CI/merge only after observation, no fabricated native editor.

## EDIT-01 research PR #253 APPROVED/MERGED, independent checkpoint proposal
- [Research PR #253](https://github.com/KayzenRoot/stormline/pull/253), BASE `e35ef681e54bec467b4651da70787b6e78a17139`, audited final HEAD `ad86001c654128c35685049d51ce07bc9fe662e0`, eight new Markdown (480 additions, no deletions), [Docs Validation #43722213338](https://github.com/KayzenRoot/stormline/actions/runs/43722213338) **SUCCESS** job #132836443890 (Source Pack links, DAG, registry and blocked Zcode selector), [pt-BR audit #6895542612](https://github.com/KayzenRoot/stormline/pull/253#issuecomment-6895542612) **APPROVED DOCUMENTARY ONLY**, normal squash/main/PR/API readback `45c1b342600961cdcbb548e81fc22f67346147cc`. Exactly E01-T001..E01-T128 unique and FUTURE/NOT EXECUTED; zero editor/OS/GFX/accessibility/benchmark runtime.
- Independent checkpoint PR BASE `45c1b342600961cdcbb548e81fc22f67346147cc`, exactly five files checkpoint/backlog/registry/this WO/Evidence, **sole EDIT-01 research_status** change. Target **50/80 research documented (62.5%), 30 pending, 0 engine**, all 80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class UNDECIDED. Coding #68 OPEN/BLOCKED, research #252 OPEN until actual checkpoint main readback. ADR-0053 PROPOSED, NLE-D009 engine license OPEN, toolkit not selected or installed. Independent checkpoint exact-final-HEAD CI/audit/squash/readback PENDING at creation; no Zcode coding.
