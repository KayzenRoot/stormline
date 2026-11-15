# EDIT-01 — Exactly 128 FUTURE Editor Shell & Workspace Acceptance Tests

**Research [#252](https://github.com/KayzenRoot/stormline/issues/252) | NLE-P00-WO-002-EDIT-01 | code [#68](https://github.com/KayzenRoot/stormline/issues/68) OPEN/BLOCKED.** Exactly **E01-T001..E01-T128**, all **FUTURE / NOT EXECUTED**, executed=0, passed=0, failed=0. The repository currently contains **no editor executable, GFX runtime, native window adapter, test harness or selected Qt/ImGui/Tauri toolkit**. Docs Validation does not test a real UI.

## Future test evidence format
Every test requires exact Git base/head and compiled artifacts, owner-approved ADR/backend choice and license, OS version/desktop environment and hardware tier, physical/virtual monitor topology with logical and backing pixel sizes, DPI settings, accessibility software name/version where relevant, input locale/IME, project fixture and workspace schema, actual command/action/CI log, baseline vs outcome screenshots or redacted accessibility tree only when consented, invalid state recovery, CPU/RAM/frametime/p95/p99 for measurable tests, failure classification, objective pt-BR audit and rollback proof. Numeric thresholds **TBD** by owner after baseline.

Only actually passing native Windows/Linux X11/Linux Wayland/macOS and accessible OS tests may substantiate compatibility. 8/16/32/64 client counts are NET-03 scalability axes, **not relevant to editor docking performance**. Toolkit feature claims without installed app/test evidence must stay hypotheses. The benchmark protocol uses controlled pane numbers, monitors and IPC/device-loss stress instead.

| ID | Area | Future assertion | Current state |
|---|---|---|---|
## Startup and shell lifecycle
| E01-T001 | Startup and shell lifecycle | Windows starts editor shell with no project and visible menu future | FUTURE / NOT EXECUTED |
| E01-T002 | Startup and shell lifecycle | Linux X11 starts editor and status panel future | FUTURE / NOT EXECUTED |
| E01-T003 | Startup and shell lifecycle | Linux Wayland starts editor and reports placement limits future | FUTURE / NOT EXECUTED |
| E01-T004 | Startup and shell lifecycle | macOS starts editor and activates correct native window future | FUTURE / NOT EXECUTED |
| E01-T005 | Startup and shell lifecycle | headless NET-02 starts without GUI dependency future | FUTURE / NOT EXECUTED |
| E01-T006 | Startup and shell lifecycle | CORE-01 lost window event yields safe shell recovery future | FUTURE / NOT EXECUTED |
| E01-T007 | Startup and shell lifecycle | shell exit cancels unsaved workspace mutation explicitly future | FUTURE / NOT EXECUTED |
| E01-T008 | Startup and shell lifecycle | launch without GPU keeps project shell and unavailable viewport future | FUTURE / NOT EXECUTED |
## Docking and panel graph
| E01-T009 | Docking and panel graph | two registered panels dock left/right future | FUTURE / NOT EXECUTED |
| E01-T010 | Docking and panel graph | split and tab nesting bounded deterministic future | FUTURE / NOT EXECUTED |
| E01-T011 | Docking and panel graph | drag panel across tab groups retains stable ID future | FUTURE / NOT EXECUTED |
| E01-T012 | Docking and panel graph | float/detach recreates valid native window lease future | FUTURE / NOT EXECUTED |
| E01-T013 | Docking and panel graph | dock panel into window after detach restores focus future | FUTURE / NOT EXECUTED |
| E01-T014 | Docking and panel graph | close last essential panel leaves command palette recovery future | FUTURE / NOT EXECUTED |
| E01-T015 | Docking and panel graph | cycle or duplicate DockNodeRef rejected future | FUTURE / NOT EXECUTED |
| E01-T016 | Docking and panel graph | panel min-size collision clamps or denies with typed error future | FUTURE / NOT EXECUTED |
## Workspace save and restore
| E01-T017 | Workspace save and restore | workspace save uses DATA-04 atomic CAS future | FUTURE / NOT EXECUTED |
| E01-T018 | Workspace save and restore | reopen restores multi-pane arrangement by stable PanelId future | FUTURE / NOT EXECUTED |
| E01-T019 | Workspace save and restore | corrupt snapshot falls back last-known-good future | FUTURE / NOT EXECUTED |
| E01-T020 | Workspace save and restore | future schema version rejected safely without data loss future | FUTURE / NOT EXECUTED |
| E01-T021 | Workspace save and restore | migration older schema reversible with recorded version future | FUTURE / NOT EXECUTED |
| E01-T022 | Workspace save and restore | oversized/deep dock tree rejected before recursive allocation future | FUTURE / NOT EXECUTED |
| E01-T023 | Workspace save and restore | untrusted Qt binary restoreState blob is never deserialized future | FUTURE / NOT EXECUTED |
| E01-T024 | Workspace save and restore | two concurrent editor instances avoid last-writer overwrite future | FUTURE / NOT EXECUTED |
## Multi monitor topology
| E01-T025 | Multi monitor topology | two-monitor layout restore survives monitor removal future | FUTURE / NOT EXECUTED |
| E01-T026 | Multi monitor topology | negative OS screen origin normalized and visible future | FUTURE / NOT EXECUTED |
| E01-T027 | Multi monitor topology | portrait external monitor preserves panel reachability future | FUTURE / NOT EXECUTED |
| E01-T028 | Multi monitor topology | primary monitor changes and floats rehome future | FUTURE / NOT EXECUTED |
| E01-T029 | Multi monitor topology | three-monitor mixed logical geometry restoration future | FUTURE / NOT EXECUTED |
| E01-T030 | Multi monitor topology | Wayland denies unsupported absolute-position assumption future | FUTURE / NOT EXECUTED |
| E01-T031 | Multi monitor topology | external monitor unplug during drag cancels safely future | FUTURE / NOT EXECUTED |
| E01-T032 | Multi monitor topology | reconnected monitor restores without losing existing project edits future | FUTURE / NOT EXECUTED |
## DPI and visual scaling
| E01-T033 | DPI and visual scaling | 100 percent DPI renders text and hitboxes aligned future | FUTURE / NOT EXECUTED |
| E01-T034 | DPI and visual scaling | 125 percent mixed-scale move updates logical pixels future | FUTURE / NOT EXECUTED |
| E01-T035 | DPI and visual scaling | 150 percent display move recalculates swapchain dimensions future | FUTURE / NOT EXECUTED |
| E01-T036 | DPI and visual scaling | 200 percent retina pixel ratio avoids double scaling future | FUTURE / NOT EXECUTED |
| E01-T037 | DPI and visual scaling | fractional Wayland scale report degraded if unsupported future | FUTURE / NOT EXECUTED |
| E01-T038 | DPI and visual scaling | font size user scaling does not clip essential controls future | FUTURE / NOT EXECUTED |
| E01-T039 | DPI and visual scaling | pointer click target map DIP to physical accurately future | FUTURE / NOT EXECUTED |
| E01-T040 | DPI and visual scaling | DPI change during animation avoids layout corruption future | FUTURE / NOT EXECUTED |
## Keyboard shortcuts focus and IME
| E01-T041 | Keyboard shortcuts focus and IME | Ctrl or Cmd command mapped per platform future | FUTURE / NOT EXECUTED |
| E01-T042 | Keyboard shortcuts focus and IME | reserved OS accelerator not intercepted future | FUTURE / NOT EXECUTED |
| E01-T043 | Keyboard shortcuts focus and IME | text-edit Ctrl+Z not routed to scene undo future | FUTURE / NOT EXECUTED |
| E01-T044 | Keyboard shortcuts focus and IME | global command disabled when modal dialog active future | FUTURE / NOT EXECUTED |
| E01-T045 | Keyboard shortcuts focus and IME | shortcut collision resolves deterministically and visibly future | FUTURE / NOT EXECUTED |
| E01-T046 | Keyboard shortcuts focus and IME | IME composition cannot trigger editor global command future | FUTURE / NOT EXECUTED |
| E01-T047 | Keyboard shortcuts focus and IME | focus returns to originating panel after dialog close future | FUTURE / NOT EXECUTED |
| E01-T048 | Keyboard shortcuts focus and IME | keyboard-only dock and undock alternative available future | FUTURE / NOT EXECUTED |
## Selection inspector and undo
| E01-T049 | Selection inspector and undo | selection host displays opaque valid entity reference future | FUTURE / NOT EXECUTED |
| E01-T050 | Selection inspector and undo | stale WORLD generation selection safely cleared future | FUTURE / NOT EXECUTED |
| E01-T051 | Selection inspector and undo | inspector contents delegated to EDIT-03 future | FUTURE / NOT EXECUTED |
| E01-T052 | Selection inspector and undo | shell undo modifies layout only in correct scope future | FUTURE / NOT EXECUTED |
| E01-T053 | Selection inspector and undo | scene transaction undo delegated to scene owner future | FUTURE / NOT EXECUTED |
| E01-T054 | Selection inspector and undo | redo stack invalidated by conflicting revision future | FUTURE / NOT EXECUTED |
| E01-T055 | Selection inspector and undo | project save not conflated with workspace save future | FUTURE / NOT EXECUTED |
| E01-T056 | Selection inspector and undo | selection changes never mutate canonical ECS directly future | FUTURE / NOT EXECUTED |
## Project management host
| E01-T057 | Project management host | project manager panel opens without filesystem write future | FUTURE / NOT EXECUTED |
| E01-T058 | Project management host | EDIT-02 handles actual project create flow future | FUTURE / NOT EXECUTED |
| E01-T059 | Project management host | recent project URI sanitized through DATA-01 future | FUTURE / NOT EXECUTED |
| E01-T060 | Project management host | invalid external project path rejected safely future | FUTURE / NOT EXECUTED |
| E01-T061 | Project management host | project migration delegated to EDIT-02 DATA-04 future | FUTURE / NOT EXECUTED |
| E01-T062 | Project management host | two-project panel scope cannot mix asset refs future | FUTURE / NOT EXECUTED |
| E01-T063 | Project management host | new project wizard cancellation leaves no files future | FUTURE / NOT EXECUTED |
| E01-T064 | Project management host | MCP project open requires correct scoped capability future | FUTURE / NOT EXECUTED |
## Accessibility roles and input
| E01-T065 | Accessibility roles and input | Windows UIA exposes role name and actions future | FUTURE / NOT EXECUTED |
| E01-T066 | Accessibility roles and input | macOS VoiceOver announces panel and focus future | FUTURE / NOT EXECUTED |
| E01-T067 | Accessibility roles and input | Linux AT-SPI Orca traverses menus and tabs future | FUTURE / NOT EXECUTED |
| E01-T068 | Accessibility roles and input | keyboard-only reaches every core editor menu action future | FUTURE / NOT EXECUTED |
| E01-T069 | Accessibility roles and input | focus indicator visible with high contrast future | FUTURE / NOT EXECUTED |
| E01-T070 | Accessibility roles and input | reduced-motion preference respected future | FUTURE / NOT EXECUTED |
| E01-T071 | Accessibility roles and input | screen reader hears progress and recovery errors future | FUTURE / NOT EXECUTED |
| E01-T072 | Accessibility roles and input | custom viewport exposes accessible fallback/description future | FUTURE / NOT EXECUTED |
## Text RTL localization and gamepad
| E01-T073 | Text RTL localization and gamepad | Unicode combining character input and selection future | FUTURE / NOT EXECUTED |
| E01-T074 | Text RTL localization and gamepad | RTL labels layout without reversed shortcut semantics future | FUTURE / NOT EXECUTED |
| E01-T075 | Text RTL localization and gamepad | locale change updates labels without losing panel IDs future | FUTURE / NOT EXECUTED |
| E01-T076 | Text RTL localization and gamepad | font fallback supports non-Latin localized UI future | FUTURE / NOT EXECUTED |
| E01-T077 | Text RTL localization and gamepad | CJK IME candidate and composition window positions future | FUTURE / NOT EXECUTED |
| E01-T078 | Text RTL localization and gamepad | emoji/surrogate handling avoids corrupted saved text future | FUTURE / NOT EXECUTED |
| E01-T079 | Text RTL localization and gamepad | optional gamepad navigation doesn't steal typing focus future | FUTURE / NOT EXECUTED |
| E01-T080 | Text RTL localization and gamepad | locale changes preserve workspace schema IDs future | FUTURE / NOT EXECUTED |
## Viewport and GFX integration
| E01-T081 | Viewport and GFX integration | 2D viewport host reports RHI surface capability future | FUTURE / NOT EXECUTED |
| E01-T082 | Viewport and GFX integration | 3D viewport host texture ref lifecycle guarded future | FUTURE / NOT EXECUTED |
| E01-T083 | Viewport and GFX integration | viewport resized under drag without GPU use-after-free future | FUTURE / NOT EXECUTED |
| E01-T084 | Viewport and GFX integration | GPU device loss preserves editor shell future | FUTURE / NOT EXECUTED |
| E01-T085 | Viewport and GFX integration | hidden viewport throttles redraw by policy future | FUTURE / NOT EXECUTED |
| E01-T086 | Viewport and GFX integration | GFX viewport color space not rewritten by UI toolkit future | FUTURE / NOT EXECUTED |
| E01-T087 | Viewport and GFX integration | editor camera separate from GAME-04 game camera future | FUTURE / NOT EXECUTED |
| E01-T088 | Viewport and GFX integration | simulation tick independent of editor UI frame pacing future | FUTURE / NOT EXECUTED |
## Performance and responsiveness
| E01-T089 | Performance and responsiveness | cold startup measured on Windows defined tier future | FUTURE / NOT EXECUTED |
| E01-T090 | Performance and responsiveness | cold startup measured on Linux defined tier future | FUTURE / NOT EXECUTED |
| E01-T091 | Performance and responsiveness | cold startup measured on macOS defined tier future | FUTURE / NOT EXECUTED |
| E01-T092 | Performance and responsiveness | UI idle CPU and memory measured future | FUTURE / NOT EXECUTED |
| E01-T093 | Performance and responsiveness | rapid panel drag input latency p95 p99 measured future | FUTURE / NOT EXECUTED |
| E01-T094 | Performance and responsiveness | viewport resize plus asset loading keeps UI responsive future | FUTURE / NOT EXECUTED |
| E01-T095 | Performance and responsiveness | large hierarchy virtualized inspector future | FUTURE / NOT EXECUTED |
| E01-T096 | Performance and responsiveness | 100 repeated workspace restores no memory growth future | FUTURE / NOT EXECUTED |
## Plugin and security boundaries
| E01-T097 | Plugin and security boundaries | untrusted layout JSON depth bounded future | FUTURE / NOT EXECUTED |
| E01-T098 | Plugin and security boundaries | malicious plugin pane cannot open arbitrary file future | FUTURE / NOT EXECUTED |
| E01-T099 | Plugin and security boundaries | plugin cannot register privileged command without permission future | FUTURE / NOT EXECUTED |
| E01-T100 | Plugin and security boundaries | webview HTML sanitized before DOM injection future | FUTURE / NOT EXECUTED |
| E01-T101 | Plugin and security boundaries | Tauri capability union privilege escalation fixture denied future | FUTURE / NOT EXECUTED |
| E01-T102 | Plugin and security boundaries | untrusted SVG/font/asset preview isolated appropriately future | FUTURE / NOT EXECUTED |
| E01-T103 | Plugin and security boundaries | AI/MCP cannot impersonate user for destructive editor edit future | FUTURE / NOT EXECUTED |
| E01-T104 | Plugin and security boundaries | clipboard and network grants require explicit scoped permission future | FUTURE / NOT EXECUTED |
## Crash recovery and persistence
| E01-T105 | Crash recovery and persistence | kill editor during workspace save preserves last-good future | FUTURE / NOT EXECUTED |
| E01-T106 | Crash recovery and persistence | restore from corrupt state visibly explains fallback future | FUTURE / NOT EXECUTED |
| E01-T107 | Crash recovery and persistence | panel factory removed during upgrade recover missing pane future | FUTURE / NOT EXECUTED |
| E01-T108 | Crash recovery and persistence | window crash does not destroy project document future | FUTURE / NOT EXECUTED |
| E01-T109 | Crash recovery and persistence | DATA-04 transaction version conflict preserves user state future | FUTURE / NOT EXECUTED |
| E01-T110 | Crash recovery and persistence | viewport process crash isolated from editor host future | FUTURE / NOT EXECUTED |
| E01-T111 | Crash recovery and persistence | async save cancellation prevents half-written state future | FUTURE / NOT EXECUTED |
| E01-T112 | Crash recovery and persistence | restart after software upgrade logs migration failure redacted future | FUTURE / NOT EXECUTED |
## OS integration and error cases
| E01-T113 | OS integration and error cases | Windows UI activation Alt Tab and modal handling future | FUTURE / NOT EXECUTED |
| E01-T114 | OS integration and error cases | macOS full-screen Spaces window dock restoration future | FUTURE / NOT EXECUTED |
| E01-T115 | OS integration and error cases | X11 compositor frame decoration geometry future | FUTURE / NOT EXECUTED |
| E01-T116 | OS integration and error cases | Wayland fractional scaling and permissions future | FUTURE / NOT EXECUTED |
| E01-T117 | OS integration and error cases | file dialog path permission boundary validated future | FUTURE / NOT EXECUTED |
| E01-T118 | OS integration and error cases | OS sleep wake avoids stale window and surface lease future | FUTURE / NOT EXECUTED |
| E01-T119 | OS integration and error cases | plug USB input during drag does not corrupt focus future | FUTURE / NOT EXECUTED |
| E01-T120 | OS integration and error cases | native OS accessibility service absence has honest fallback future | FUTURE / NOT EXECUTED |
## Governance and release gates
| E01-T121 | Governance and release gates | exactly 128 E01 tests remain FUTURE and unique | FUTURE / NOT EXECUTED |
| E01-T122 | Governance and release gates | Core-01 dependency remains documentary PROPOSED until approved | FUTURE / NOT EXECUTED |
| E01-T123 | Governance and release gates | ADR-0053 stays PROPOSED without toolkit selection | FUTURE / NOT EXECUTED |
| E01-T124 | Governance and release gates | engine code license NLE-D009 stays OPEN | FUTURE / NOT EXECUTED |
| E01-T125 | Governance and release gates | no source toolkit SDK or runtime tests at P00 | FUTURE / NOT EXECUTED |
| E01-T126 | Governance and release gates | all 80 implementation packets remain blocked | FUTURE / NOT EXECUTED |
| E01-T127 | Governance and release gates | no fabricated cross-platform or WCAG certification claim | FUTURE / NOT EXECUTED |
| E01-T128 | Governance and release gates | EDIT-02 research only after EDIT-01 final verified readback | FUTURE / NOT EXECUTED |

## Future run criteria
- First smoke must open editor shell headless-unrelated with two panes, keyboard command registry, workspace save/reopen and fallback when display missing. Verify real UI geometry/accessible tree, not only mocked serialization.
- Test security for malformed/unknown workspace state, file traversal and untrusted plugin, never execute uploaded code. Qt restoreState must receive only trusted own blobs or app-level normalized safe format; if not, fail closed.
- Test RHI surface device loss and editor responsiveness under GPU load, but do not pretend GFX is implemented today; dependency ADRs and actual source evidence must be approved before code.
- Future fail if panel impossible to reach, keyboard focus trap, wrong scene transaction undo, file corruption, leaked secrets via MCP/AI, unreviewed toolkit/copyleft license, or reproducible HIGH/CRITICAL.
- P00: all **128 FUTURE/NOT EXECUTED**, no UI, test harness, accessibility tool, benchmark or actual build executed; all 80 Work Orders remain blocked.
