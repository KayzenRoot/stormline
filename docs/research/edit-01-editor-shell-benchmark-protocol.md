# EDIT-01 — Reproducible Editor Shell, Docking, Multi-Monitor and Accessibility Benchmark Protocol

**2026-11-15 | P00 RESEARCH ONLY.** No editor executable/toolkit, OS native UI session, GPU viewport, screen reader test, memory capture or measured benchmark. All 128 E01-T001..T128 are FUTURE / NOT EXECUTED. No p95/p99, toolkit winner, screen-reader certification or CPU baseline is asserted.

## 1. Hypotheses and gates
H1: a toolkit-neutral typed editor shell can open and retain two dock panels, perform undo in host scope and recover workspace across restart with immutable stable IDs. H2: a lost/moved monitor, per-monitor DPI change and corruption of workspace state never strand indispensable controls or overwrite project changes. H3: screen-reader/keyboard-only alternatives expose real role/name/action/focus, and plugin/AI/MCP commands do not bypass permissions. H4: host stays responsive under viewport resize/device lost without taking over render device/simulation time. H5: Qt 6 Widgets and Dear ImGui docking prototypes can be compared on the **same semantic shell** before selecting a toolkit after license/legal gates, with Slint/Tauri/wxWidgets additional comparison if justified. These hypotheses are not tested in P00.

## 2. Future manifest
`EditorBenchmarkManifestV1`: Git base/head, approved ADR/DoD/risk, per-toolkit tag/license/SBOM and compiled ABI, OS version Windows/Linux X11+Wayland/macOS (compositor/window manager), screen count/resolution/rotation/origin/scale 100/125/150/200%, GPU/API/driver/RHI/device epoch, CPU RAM/storage tier, input keyboard/IME/locale, OS accessibility service/screen reader (NVDA/VoiceOver/Orca), backend-specific native handles permissions, loaded panel count/size, serialized workspace schema/checksum/revision and last-known-good, deterministic command sequence/fixture project, renderer/asset tasks and expected errors, warmup/repeats, GUI input-to-present sampling, CPU idle/p95/p99, GPU frame/present/VRAM, memory peak/retained after panel close, telemetry redaction, command and CI artifacts and operator-signed recovery/audit. No personal monitor serial or private project paths in public logs.

## 3. Controlled comparison table
| Fixture | Candidate axes (NOT release thresholds) | Objective output |
|---|---|---|
| E01_BASE | native empty shell, status+two panels | cold/warm start, nonblocking menu/command palette, process memory |
| E01_DOCK | 2/8/24/64 placeholder panels, tab/split/float cycles | input-to-dock/paint p50/p95/p99, allocations, no orphan panels |
| E01_LAYOUT | 1/2/3 monitor workspace, restart 50 iterations | lossless stable semantic panel tree, DATA-04 atomic CAS and restored defaults |
| E01_DPI | monitor scale 100/125/150/200%, portrait and negative origins | DIP/pixel mapping error, text clarity, hit target accuracy |
| E01_HOTPLUG | disconnect primary/secondary during drag, switch screen orientation | essential windows visible and focus accessible, typed failure receipts |
| E01_A11Y | UIA + NVDA Windows, AX + VoiceOver macOS, AT-SPI + Orca Linux | accessible tree role/name/action, keyboard-only reachability and focus |
| E01_TEXT | CJK IME composition, RTL, emoji, diacritics, locale theme/text zoom | correct cursor candidate/selection, no accidental shortcut |
| E01_GPU | GFX viewport 2D/3D placeholder then real RHI, resize/device loss/occlusion | frame swapchain safety, nonblocking shell and recovery |
| E01_LOAD | project scanning/diagnostics loading while docking/typing | main-thread responsiveness, input latency and thread/cancel state |
| E01_SECURITY | malformed/cyclic/deep layout, untrusted Qt restore blob, fake plugin manifest/AI command | reject/recover without code exec/PII or project data loss |
| E01_PLATFORM | Windows, Linux X11+Wayland, macOS on equal fixture | actual OS difference documented, no unsupported absolute Wayland position claim |
| E01_LICENSE | Qt LGPLv3-compliant distribution prototype versus ImGui MIT and other candidates | versioned legal checklist and NOTICE/relinking/artifact rights evidence |

All pane counts and monitor scaling percentages are **bench axes, not max supported counts**. Numeric frame/CPU/latency budgets and accessibility acceptance threshold require explicit owner approval after pilot. No invented p95/p99. CI runners without physical monitor/assistive tech cannot count as complete accessibility verification.

## 4. Measurement/failure protocol
1. First baseline genuine OS integration and display topology: capture DPI metrics and known screen geometry with consent, then run same deterministic input event fixture across candidates. Verify Wayland capability limitation instead of forcing off-screen absolute placement.
2. Time separate command dispatch, input-to-present, layout rebuild, repaint vs GFX viewport render/present fence, project I/O and OS window create. Choose calibrated timers/clock and repeats before p99; do not compare cold first run with warm cache silently.
3. Change active monitor, unplug/plug, scale, minimize/fullscreen/desktop switching and force crash during atomic workspace write. Compare semantic graph and visible essential panels after recovery. No QMainWindow::restoreState on arbitrary external bytes.
4. Test real keyboard with IME and accessibility APIs in OS and screen readers; focus/accessible roles, keyboard-only dock and undo context, reduced motion and high contrast. Mock widget metadata alone not pass.
5. RHI viewport test after GFX actually implemented: resize/occlusion/device loss and selection preview separately, ensure UI/main thread and GPU lifetime are not controlled by plugin/untrusted panel; no fake game simulation performance claim.
6. Sandbox fake plugin/script and malicious workspace in controlled test only: no real customer file, no arbitrary code execution or production secrets. Editor/CLI/MCP same command permission and expected CAS.
7. Audit Qt/Slint/Tauri/ImGui tagged source license and transitive dep, NOTICE/attribution, dynamically linked/relink/installation info if LGPL case, webview engine provisions. Any ambiguous legal compliance => BLOCKED, don't select automatically.
8. Stop on unrecoverable lost controls, project data corruption, a11y baseline failure relative to approved DoD, untrusted deserialize/code execution, broken OS integration, HIGH/CRITICAL or unapproved code license. Exact fix+regression and pt-BR objective audit required.

## 5. Reporting status
At P00 **zero test results, zero measurements, no selected renderer/toolkit**, no desktop build, no screen reader testing or functional GFX viewport, all 128 cases FUTURE/NOT EXECUTED. Benchmark failure/claims only become factual after real target build and evidence. Reference [Qt QMainWindow/restoreState security](https://doc.qt.io/qt-6/qmainwindow.html), [Qt accessibility](https://doc.qt.io/qt-6/accessible-qwidget.html), [Dear ImGui docking](https://github.com/ocornut/imgui/wiki/Docking), [Tauri capability rules](https://tauri.app/security/capabilities/).
