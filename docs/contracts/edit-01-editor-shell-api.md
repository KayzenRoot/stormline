# EDIT-01 — Versioned Editor Shell, Docking, Workspace and Command Semantic Contracts v0.1

**P00 research only | research #252 | WO NLE-P00-WO-002-EDIT-01 | coding #68 OPEN/BLOCKED.** All names are proposed semantic structs/enums/commands, NOT C++ headers/wire protocol or implemented OS GUI. Toolkit backend, actual ABI, license, quotas, target CPU/OS and a11y conformance TBD. No cross-module authority is assigned to EDIT-01 over scene editing, project migration or GFX rendering.

## 1. Proposed typed data
| Type V1 | Required fields and validation | Owner boundary |
|---|---|---|
| `EditorShellCapabilitiesV1` | host OS, toolkit backend/tag, DPI mode, window float support, per-monitor metrics, RHI surface availability, accessibility/IME/RTL capability, unsupported reason | EDIT-01 read-only probe from CORE-01/GFX, never pretend features |
| `EditorWindowRefV1` | opaque scoped window ID+generation, parent, native kind MAIN/FLOAT/DIALOG/VIEWPORT_HOST, active focus, screen ID only transient | CORE-01 creates/destroys OS handles, EDIT-01 leases references |
| `DisplayTopologySnapshotV1` | available screen rects DIP, scale, safe area, primary status, rotation, OS display generation, no user-identifiable serial | CORE-01 OS facts; no Wayland absolute positioning promise |
| `EditorPanelDescriptorV1` | stable namespaced PanelId, semantic role TOOL/INSPECTOR/HIERARCHY/VIEWPORT/LOG/PROJECT, allowed dock/float, accessible name and factory capability | EDIT-01 host; content owners other EDIT modules |
| `DockLayoutGraphV1` | bounded tree of split/tab nodes, stable panel refs, normalized ratio, min size, focus order, docking constraints, layout generation | EDIT-01 validates DAG no cycle/orphans or oversized restore |
| `DockOperationV1` | DOCK/UNDOCK/REORDER/SPLIT/MOVE/CLOSE/RESTORE, actor, expected generation, target window, source/destination | EDIT-01 host-only changes; no scene mutation |
| `WorkspaceSnapshotV1` | version, workspace ID/profile, panel graph, DIP geometry, monitor fallback mapping, theme/shortcut ref, origin, checksum, last-known-good | EDIT-01 schema; DATA-04 transaction/atomic CAS; never raw network Qt blob |
| `WorkspaceRestoreReceiptV1` | EXACT/CLAMPED/MIGRATED/FALLBACK/REJECTED, safe window count, errors, source revision and recovery ref | report clamping and no hidden essential panel |
| `EditorCommandIdV1` | namespaced stable command ID, label/description localization key, category, allowed origin, required context/role, undo domain, enabled predicate | EDIT-01 command registry, object action owner validates |
| `EditorCommandInvocationV1` | command ID, origin MENU/SHORTCUT/PALETTE/MCP/CLI, focus scope, selected object ref, expected source revision, user capability, normalized args | no arbitrary shell or direct engine private call |
| `EditorCommandReceiptV1` | accepted/rejected/cancelled, target owner, non-secret correlation, transaction ID if owner, updated focus/selection, reason | actual scene/data side effects owned by EDIT-03/DATA-04 |
| `EditorShortcutProfileV1` | per-OS key codes/layout, chord sequences, input language, remap ownership, conflict scope, OS-reserved disallow list | EDIT-01 user preferences; not gameplay mapping |
| `EditorFocusRouteV1` | target panel/accessible node/window, modal depth, keyboard/IME capture state, navigation origin and return-focus point | no lost focus on float/close, no hidden shortcut theft |
| `EditorSelectionHostV1` | selected opaque entity/asset refs + provenance, read-only inspector host tabs, focus, selection epoch | WORLD/EDIT-03 own canonical objects; no direct ECS mutation |
| `EditorUndoScopeV1` | UI_LAYOUT / TEXT_INPUT / SCENE_TRANSACTION / ASSET_OPERATION, owner, reversible state, expected CAS version | CTRL+Z goes to active owner, never undoes wrong project/game event |
| `EditorViewportSurfaceLeaseV1` | viewport opaque ID, CORE-01 window lease, GFX RHI texture/swapchain ref+device epoch, DIP/physical rect, capture/focus, present fence | GFX owns GPU memory/barriers; EDIT-01 host geometry and lease, EDIT-07 preview |
| `EditorViewportEventV1` | resized/moved/occluded/activated/recovered/device_lost, display generation, input coordinates and DPI transform | no stale resource ownership; asynchronous failure recovery |
| `EditorAccessibilityNodeV1` | stable accessible ID, role/name/description/localized text, parent-child/labels, state, actions, focus, bounds DIP and changes | toolkit adapter maps UIA/macOS AX/AT-SPI; no fake a11y support |
| `EditorThemeLocaleV1` | theme contrast, text scaling, reduced motion, locale/RTL, font fallback and emoji/IME capability report | UI typography owner shared with GFX-07; no bundled font/license claim |
| `EditorProjectLauncherV1` | recently opened URI sanitized, safe project metadata and permission, no direct modification | EDIT-02 owns actual create/open/convert, DATA-01 VFS validates path |
| `EditorPluginPanelCapabilityV1` | signed/verified manifest ref, allowlisted data scope/commands, sandbox type, lifetime, explicit user approval | plugin engine owner must ensure isolation, not native in-process pseudo-sandbox |
| `EditorAutomationPrincipalV1` | agent/user role, allowed command IDs, project scope, expected DATA-04 revision, privilege and cost consent | AI/MCP tools same semantic public permission checks |
| `EditorDiagnosticsV1` | CORE-06 trace refs, redacted UI frame/CPU/heap metrics, loaded panel state, OS/privacy | diagnostics shown by shell but emitted by CORE-06 |
| `EditorRecoveryPolicyV1` | save generation, last-good checkpoint, conflict strategy, missing screen fallback, crash report opt-in | DATA-04 durable CAS/backup, no silent state overwrite |
| `EditorPerformanceBudgetV1` | target OS/CPU/RAM/GPU tier, cold start/input-to-paint/dock/restore p50/p95/p99 and idle CPU budgets | numeric targets TBD owner, do not invent |

## 2. Non-executable proposed interfaces and permission boundaries
- `ProbeEditorShellCapabilities` collects truthful CORE-01/GFX OS/backend/monitor and screen-reader availability, reports unsupported/partial.
- `RegisterPanelFactory` / `OpenPanel` / `ClosePanel` / `DockPanel` / `MovePanelToWindow`: only stable registered IDs and expected workspace generation, explicit result if float unsupported or monitor gone; no arbitrary plugin class load.
- `PreviewWorkspaceLayout` / `ValidateWorkspaceSnapshot` / `SaveWorkspace` / `RestoreWorkspace`: schema/version/depth/checksum/allowlisted panel factory plus safe screen clamping, DATA-04 atomic CAS and last-known-good. Unknown shared/synced binary native toolkit state => reject. No untrusted QMainWindow::restoreState.
- `RegisterEditorCommand` / `InvokeEditorCommand` / `ResolveShortcutConflict` / `FocusEditorNode`: target capability and active focus with semantic receipts, no bypass for CLI/MCP; route Ctrl+Z to text/layout/scene owner by scope, preview/stage/validate/commit for mutating operations.
- `SetEditorSelection` / `InspectSelectionHost`: display opaque refs only, actual scene/inspector mutation goes to EDIT-03/WORLD owner. `OpenProjectLauncher` delegates all file operations to EDIT-02/DATA-01.
- `AcquireViewportSurfaceLease` / `UpdateViewportRect` / `ReleaseViewportLease`: GFX/CORE-01 handle lifetime; no raw stale GPU pointers or child-process borrowed native handles, fail placeholder on device lost and allow shell to remain usable.
- `PublishAccessibleTreeUpdate` / `NavigateKeyboardDockAlternative`: real toolkit/OS assistive bridge and keyboard-only equivalent to pointer docking, no promise of certification from metadata alone.
- `InspectPerformance/Diagnostics`: read-only CORE-06 sanitized counters, not hidden GPU/device keys. `RegisterPluginPanel` denies unreviewed native arbitrary code and checks isolated capability manifest.

## 3. Invariants and failure taxonomy
1. **No duplicate simulation/renderer authority:** EDIT-01 hosts UI surfaces and semantic commands; only GFX owns render state, EDIT-02 project creation, EDIT-03 scene edits, EDIT-07 preview/debug and DATA-04 persistence.
2. **UI host undo != scene edit undo != game rollback:** always scope actual owner and expected data revision. Keyboard input/IME focus outranks global shortcut; OS reserved shortcut never stolen.
3. **Workspace restore is non-destructive:** a bad/corrupt/oversized file or missing monitor yields last-known-good/visible primary default, no arbitrary code, infinite recursion, out-of-bounds or lost critical project changes. Relative/physical DPI and Wayland restrictions handled, never assume stable OS coordinates.
4. **Accessibility is measured:** semantic role/name/action/focus/keyboard-only docking, screen readers on supported OS; Dear ImGui metadata alone is not proof of native accessible tree.
5. **Privileges:** project file path VFS sandbox, plugin manifest and AI/MCP user capabilities; public semantic API cannot export secrets, write arbitrary files or trigger paid operations.
6. **No claims of compatibility:** Windows/Linux X11/Wayland/macOS targets require actual native builds, monitors and assistive tools. No GUI code exists at P00.

Error kinds: `EDITOR_NOT_IMPLEMENTED, EDITOR_BACKEND_NOT_APPROVED, EDITOR_BACKEND_UNSUPPORTED, EDITOR_OS_CAPABILITY_MISSING, EDITOR_WINDOW_HANDLE_EXPIRED, EDITOR_MONITOR_REMOVED, EDITOR_FLOATING_UNAVAILABLE, EDITOR_WORKSPACE_SCHEMA_UNSUPPORTED, EDITOR_WORKSPACE_UNTRUSTED, EDITOR_WORKSPACE_CORRUPT, EDITOR_WORKSPACE_TOO_DEEP, EDITOR_WORKSPACE_RECOVERED_DEFAULT, EDITOR_WORKSPACE_CAS_CONFLICT, EDITOR_PANEL_FACTORY_UNKNOWN, EDITOR_DOCK_GRAPH_INVALID, EDITOR_PANEL_MIN_SIZE_CONFLICT, EDITOR_FOCUS_CONTEXT_LOST, EDITOR_SHORTCUT_CONFLICT, EDITOR_OS_RESERVED_SHORTCUT, EDITOR_IME_COMPOSITION_ACTIVE, EDITOR_UNDO_SCOPE_MISMATCH, EDITOR_SELECTION_ENTITY_STALE, EDITOR_VIEWPORT_SURFACE_UNAVAILABLE, EDITOR_GPU_DEVICE_LOST, EDITOR_VIEWPORT_EPOCH_STALE, EDITOR_DPI_CONVERSION_INVALID, EDITOR_ACCESSIBILITY_BRIDGE_UNSUPPORTED, EDITOR_ACCESSIBILITY_NODE_MISSING, EDITOR_PLUGIN_CAPABILITY_DENIED, EDITOR_MCP_SCOPE_DENIED, EDITOR_PROJECT_PATH_UNTRUSTED, EDITOR_IO_BACKPRESSURE, EDITOR_DIAGNOSTICS_REDACTED, EDITOR_RESOURCE_BUDGET_EXCEEDED, EDITOR_REQUIRES_USER_APPROVAL`.
All return typed bounded redacted diagnostics and retriable/recovery hints, no leaked file tokens or project private data. **128 E01 future tests NOT EXECUTED**, no native/UI/viewport runtime.
