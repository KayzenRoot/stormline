# Evidence Bundle — EDIT-01 Editor Shell & Workspace Documentary Research

**2026-11-15 | [research issue #252](https://github.com/KayzenRoot/stormline/issues/252), Work Order NLE-P00-WO-002-EDIT-01 | future code [#68](https://github.com/KayzenRoot/stormline/issues/68) OPEN/BLOCKED.** Verified BASE main `e35ef681e54bec467b4651da70787b6e78a17139` following NET-06 research/checkpoint/closeout PR #249/#250/#251 CI/audit/normal squash/factual main readback. At initial writing **49/80 research documented (61.25%), 31 pending, zero game engine, all 80 coding WOs BLOCKED**. Research in review, no owner-approved toolkit.

## Eight NEW documentary artifacts
[Native editor shell architecture](../architecture/edit-01-editor-shell-workspace.md), [ADR-0053 PROPOSED](../adr/0053-edit-01-toolkit-neutral-editor-shell.md), [technology/license matrix](../research/edit-01-editor-shell-technology-license-matrix.md), [typed semantic Editor API](../contracts/edit-01-editor-shell-api.md), [128 FUTURE acceptance scenarios](../testing/edit-01-acceptance-matrix.md), [reproducible multi-OS benchmark protocol](../research/edit-01-editor-shell-benchmark-protocol.md), [research WO](../work-orders/NLE-P00-WO-002-EDIT-01.md), this Evidence Bundle. Research PR adds exactly eight Markdown, no registry/checkpoint, code/SDK/CI changes.

## Initial evidence status, not a statement of completed runtime
| Gate / concern | Status at drafting |
|---|---|
| Research PR exact final HEAD and files | PENDING |
| Research Docs Validation exact HEAD, Source Pack links/DAG/registry/Zcode selector | PENDING |
| Research objective pt-BR audit, normal squash/main+contract readback | PENDING |
| Separate checkpoint PR sole EDIT-01 research_status and own CI/audit/squash/readback | PENDING |
| Exactly 128 E01-T001..128 | **FUTURE/NOT EXECUTED**, zero actual passes/fails |
| Windows/Linux X11+Wayland/macOS native GUI/executable | **NOT IMPLEMENTED / NOT TESTED** |
| 2D/3D GFX RHI embedded viewport and device loss | NOT IMPLEMENTED / NOT TESTED |
| Real Qt Widgets/ImGui/Slint/Tauri toolkit dependencies or license acceptance | NONE |
| Dock/persist multi-monitor/HiDPI/IME/accessibility/keyboard and benchmark | NOT RUN / NOT MEASURED |
| AI/MCP authorized plugin, crash recovery/undo host | SPECIFIED ONLY, NO RUNTIME |
| Engine copyright licensing NLE-D009 and ADR-0053 | OPEN / PROPOSED, no adoption |

## Threat/architecture/license review
- Formal predecessor only CORE-01 research-only. GFX owns render device, CORE-01 OS handle/monitor, CORE-06 diagnostics, EDIT-02 project creation, EDIT-03 scene inspector/undo contents, EDIT-07 play/preview, DATA-04 atomic CAS, DATA-01 VFS, AI/MCP capabilities separate. Semantic Editor-01 shell host cannot become second renderer/game clock/project compiler or bypass authorizer.
- Threats: corrupted/untrusted recursive workspace binary state (Qt restoreState official warning), lost off-screen window after unplug, high-DPI mispointing, keyboard focus trap, screen reader invisible editor, plugin privilege escalation, Tauri capability union, malicious project path and SVG/font/WebView injections, AI/MCP unauthorized filesystem writes, GPU device loss/lifetime, misleading compatibility claims. They are **proposed guardrails, not deployed mitigations**.
- Qt open source LGPLv3/GPLv3/commercial; some Qt modules GPL-only, distribution obligations; Dear ImGui MIT and maintained **docking** branch/multi-viewports with accessibility caveat; Slint proprietary royalty-free attribution or GPL/commercial; Tauri MIT/Apache+OS WebView/security capabilities; wxWidgets wxWindows Library Licence, Nuklear MIT/public domain. No selected code or installed third-party packages. NLE-D009 engine source license OPEN.
- Future accessibility requires real UIA/AX/AT-SPI and keyboard tests, not a checklist assertion; future real OS/GFX builds and performance benchmark needed. Risk P00 docs LOW, future plug-ins/file restore ELEVATED and privileged MCP operations HIGH_ASSURANCE. Rollback is simply revert scoped documentation, no data migration/runtime occurred.

## Proposed checkpoint delta, not promoted without audit
After research PR exact-final-HEAD Docs Validation/audit/normal squash/main readback, independent checkpoint with exactly five scoped files `docs/11-checkpoint.md`, `docs/08-backlog.md`, `docs/queue/implementation-registry.json` changing **only EDIT-01 research_status from RESEARCH_PENDING to RESEARCH_DOCUMENTED_ADR_PROPOSED**, this research WO, this Evidence. Expected **50/80 research documented (62.5%), 30 pending, ZERO runtime**, all 80 `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`. Coding #68 remains OPEN/BLOCKED, research #252 closes only after factual checkpoint main readback. Historical four-doc closeout own CI/audit/squash/main readback then EDIT-02 research only.

## Audit and stop
Pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED with observed base/head/PR files and CI, license and accessibility caveats, GFX/plugin security, 128 FUTURE/NOT EXECUTED, no benchmark, HIGH/CRITICAL/documentary scope and checkpoint factual proof. Never claim functioning engine/editor by merely merging documentation.
