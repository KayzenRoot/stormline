# ADR-0053 — Toolkit-Neutral Editor Shell with Native Backend Qualification and Safe Workspace State

**Status PROPOSED / NOT ADOPTED / NOT OWNER APPROVED** | 2026-11-15 | research #252 | Work Order NLE-P00-WO-002-EDIT-01 | future code #68 OPEN/BLOCKED | BASE main `e35ef681e54bec467b4651da70787b6e78a17139` | engine license NLE-D009 OPEN.

## Context
Stormline must provide manual Windows/Linux/macOS editor for 2D/2.5D/3D/Web game authoring while retaining a separate headless engine/server. The codebase is still documentary, CORE-01 OS primitives and GFX runtime are only proposals. Native shell's docking, persistent state, high-DPI multi-monitor layouts, accessibility and 2D/3D RHI surface interop have security, licensing and availability consequences. No technology can honestly be called compatible until actual cross-platform prototypes and licensing obligations are tested.

## Proposed decision
Define a **Stormline-owned versioned semantic editor shell**, separating commands, focus/selection/inspector host, panel/dock graph, window/workspace persistence/recovery, accessibility tree and viewport surface ownership from **pluggable toolkit-specific rendering/widget and OS adapters**. Evaluate **Qt Widgets and Dear ImGui docking as initial primary candidates**, with Slint, Tauri/WebView and wxWidgets as credible alternatives. **Do not select any toolkit or claim the first release uses two simultaneously**. Backend choice is a future owner-approved ADR amendment/decision after measurable spikes.

- Stable panel factories, command IDs, capability-based Editor/CLI/MCP parity, typed typed errors and transactional workspace snapshot saved through DATA-04; no duplicate project save/scene undo/editor runtime physics.
- CORE-01 owns OS window/event/screen; GFX owns device/render targets, EDIT-01 owns host/viewport geometry/focus and can degrade to placeholder when GPU unavailable. EDIT-02 owns real project creation; EDIT-07 owns preview/debugger; EDIT-03 owns scene/inspector/undo actions, shell only hosts UI controls.
- Saved layout includes schema/version, checked stable panel IDs, bounded structure and normalized monitor-relative coordinates, atomic write with last-known-good restore, remap missing-monitor floats to visible primary. **Never restore unknown/untrusted Qt QMainWindow serialized blobs**, particularly synced/shared project files; documented Qt risk is critical.
- Screen reader/semantic tree and keyboard-only paths first-class. Immediate-mode GUI backend must demonstrate actual UIA/macOS AX/AT-SPI accessibility bridge, no assumption that Dear ImGui's MIT license implies accessibility. Native UI toolkit has plugin/privilege isolation limits; no uncontrolled C++ plugin in privileged editor process.
- Security boundary: untrusted workspace/theme/plugin/asset/HTML content cannot execute code, gain clipboard/network/write permission, call privileged AI/MCP or escape VFS; no automatic paid SDK/tool purchase. Privileged operations require explicit operator and DATA-04 CAS.

## Tradeoff decision matrix (proposed study, not approved selection)
| Option | Strength | Cost/weakness | Status |
|---|---|---|---|
| Qt 6 Widgets with QMainWindow/QDockWidget | mature docking, native accessibility via Qt QAccessible, desktop OS, rich text/input | Qt LGPLv3 compliance or commercial licensing, GPL-only add-ons, SDK/package size, scene viewport integration and Qt restoreState trust constraints | **primary prototype candidate only** |
| Dear ImGui MIT docking+multi-viewports | C++ immediate-mode, engine RHI integration, rapid debug tooling, small library | docking branch/version pin, screen-reader/IME/bidi fidelity and multi-window Linux/macOS behavior require tests; layout persistence must be sanitized | **primary prototype candidate only** |
| Slint | declarative native UI C++/Rust with cross-platform including Web | Royalty-free proprietary desktop has usage attribution/notice conditions and embedded exclusion; GPL/commercial variants, docking gaps require proof | optional comparison |
| Tauri 2/WebView | HTML/CSS accessible semantic tree, responsive UI, Rust capability model, native OS WebViews | OS WebView/runtime differences and GPU viewport embedding/IPC/attack surface, plugin permission union risk, Rust+Web stack | optional comparison |
| wxWidgets AUI | mature native desktop widgets, permissive-like wxWindows license exception | less unified modern style/renderer-specific integration, accessibility/Wayland and DPI require test | optional comparison |
| Nuklear | MIT/public-domain dual, tiny immediate UI | no owned platform/render backends, docking and accessibility major engineering load | research comparison only |
| Write custom UI toolkit from scratch now | full ownership | massive accessibility, locale/IME, OS integration and undo burden before verified graphics core | **reject as initial unproven scope** |

## Approval obligations
Before choosing toolkit: exact tagged package/source/license/NOTICE and transitive SBOM, Qt LGPLv3 replacement/relinking/installation information vs commercial choice, Slint royalty-free attribution, Windows/Linux X11+Wayland/macOS viability, DPI/screen reader/IME gamepad scope, renderer embed/device-loss tests, live memory/perf start/resize, attack-safe workspace restore, keyboard-only docking, CI/test evidence with deterministic fixture, owner Scope/DoD and risk. No arbitrary numeric latency, accessibility certification or OS compatibility claim. **Future implementation remains BLOCKED**, 80/80 registry flags unchanged and code #68 OPEN/BLOCKED. Merging a PROPOSED ADR is NOT approval.
