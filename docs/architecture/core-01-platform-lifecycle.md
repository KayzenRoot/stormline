# CORE-01 — Platform & Lifecycle: Technical Architecture v0.1

**Work Order:** NLE-P00-WO-002-CORE-01 | **Owner program:** NLE-P00-WO-002 | **Issue:** #6  
**Status:** PROPOSED TECHNOLOGY BASELINE / NOT IMPLEMENTED | **Risk:** STANDARD for future code; LOW for this documentation increment  
**Context Lock base main:** c5ef59c13e65db2a79a04d420cdfc9a9c10768d6 | **Date:** 2026-11-14

## 1. Mission and boundaries

Stormline must develop 2D, 2.5D and 3D games, through manual and AI-native workflows, and run its **Editor plus exported desktop games** on **Windows, Linux and macOS**. Web is a separate target (PLAT-03). This document specifies the planned host/platform contract and technology choices for CORE-01, **not** a graphics engine, C++ implementation, commercial release, or hardware compatibility claim.

*CORE-01 includes:* process lifecycle, capabilities enumeration, window surfaces, OS event dispatch, window/display changes, gamepad/keyboard/mouse integration handoff, basic system paths, native OS integration boundaries, recoverable init/quit, and headless lifecycle.  
*CORE-01 excludes:* GPU rendering/RHI (GFX-01), sound mixing (AUD-01), simulation tick (CORE-04), allocations and job scheduler internals (CORE-02/03), gameplay input mapping (GAME-01), complete export/packaging/signing (PLAT-01/02/05/06), MCP protocol (AI-04), and OS web target (PLAT-03).

## 2. Decision-oriented technology shortlist

| Candidate | Function and how it works | Recommendation | Maturity/licensing evidence | Key trade-offs and validation |
|---|---|---|---|---|
| **C++20** | Compiled native language for platform abstractions and deterministic resource ownership | **Provisional baseline for initial implementation research** | ISO language and major compilers; exact supported compiler versions pending | Prefer conservative C++20 common subset over premature C++23 library use, verify on 3 OS |
| **C++23** | Modern language features (e.g., richer library support) | TRIAL only after compiler/ABI portability | Compiler-specific support must be measured | Avoid unsupported standard library features or platform divergence |
| **SDL3** | Cross-platform native C library for windows, system events and device input; C++ calls its API through narrow adapter | **Primary bridge candidate** | Official SDL docs and zlib license; supported Windows/Linux/macOS | Native features and thread affinity; avoid duplicating SDL abstraction |
| **Direct Win32 API** | Native Windows window/process API | Localized extension, not primary application architecture | Windows SDK; toolchain/license review pending | Can expose OS-specific types; isolate behind bridge |
| **Wayland / X11** | Linux display server protocols | Prefer SDL3 adapters; native bridge only for proven missing use case | Linux ecosystem; per-distro behavior differs | Focus/clipboard/IME/HDR/fullscreen and display permission differences |
| **Cocoa + Objective-C++** | Native macOS application/window event integration using Apple's runtime | Isolated host bridge only when necessary | Apple docs; Apple Clang/Xcode toolchain matrix | macOS main-thread obligations, deployment target, sandbox, security and optional signing |
| **CMake Presets** | Source-controlled build/configure/test metadata across OS/toolchains | **Preferred cross-platform build orchestrator candidate** | Official CMake documentation | Pin minimum compatible version and preset schema; avoid latest-only features |
| **Ninja** | Fast incremental build executor driven by CMake | Preferred default build backend where available | Ninja Apache-2.0 repository; terms to verify before vendoring | Xcode/MSBuild generators stay options where needed |
| **MSVC / Clang-cl** | Windows native compilation | Required compiler matrix candidates | Vendor licenses/toolchain pinning pending | Windows MSVC runtime, exception/RTTI policy and ABI tests |
| **GCC / Clang** | Linux C++ compilers | Required compiler matrix candidates | OSS/commercial distribution implications to verify | glibc/libstdc++ floor and ABI compatibility |
| **Apple Clang** | Apple toolchain for macOS and Objective-C++ | Required macOS native toolchain candidate | Xcode SDK version/terms, target minimum pending | arm64 primary; x86_64 feasibility under review |
| **Metal / Vulkan / D3D12 / WebGPU** | GPU APIs (future renderer) | **No graphics API selection in CORE-01** | Evaluated under GFX-01; Apple Metal official | CORE-01 only supplies surface/capability metadata and OS resource handles |

**Baseline recommendation:** C++20 + SDL3 + CMake Presets/Ninja, isolated OS-specific bridges and multi-compiler CI. These are **chosen as preferred candidates for proofs**, not frozen dependencies or approved commercial performance results. Feature detection never replaces platform testing.

### Official reference links
- SDL3 platforms: https://wiki.libsdl.org/SDL3/README-platforms
- SDL3 macOS: https://wiki.libsdl.org/SDL3/README-macos
- SDL3 main-thread semantics: https://wiki.libsdl.org/SDL3/SDL_IsMainThread
- SDL3 licence: https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt
- CMake Presets: https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
- Ninja: https://github.com/ninja-build/ninja
- GitHub standard CI runners: https://docs.github.com/en/actions/reference/runners/github-hosted-runners
- Apple Metal: https://developer.apple.com/documentation/metal
- MoltenVK deprecation: https://github.com/KhronosGroup/MoltenVK

## 3. Layering model

```text
Stormline Editor / Game Client / Headless Dedicated Server
                |
       Host Contract (CORE-01)
                |
      Platform Lifecycle Services
  Capability Graph | Events | Window/Display | NativeBridge
                |
  Platform Backends: SDL3 + optional Win32/Cocoa/Linux
                |
       Windows / Linux / macOS
```

- **Editor** may create multiple windows and retain project state; a GUI error must not corrupt project data.
- **Game Client** uses the same host contract, possibly different quality/feature tiers.
- **Dedicated Server** must start and run without GPU, audio device, display server or editor UI.
- **CLI / MCP** may control the project command kernel, but must not inherit ambient OS authority from the host. Agent auth belongs to AI-06.

## 4. Contract drafts (design, not C++ API)

### HostConfig and lifecycle state machine
`HostConfig { host_type: Editor|Client|Server|Test; run_mode: Windowed|Headless; requested_capabilities; project_root_id; locale; diagnostics_level }`

States: `Uninitialized -> Initializing -> Running -> Suspending -> Running -> ShuttingDown -> Terminated`, with recoverable `InitializationFailed` and `DeviceLost/WindowUnavailable` conditions **reported** rather than silently accepted.

- Initialization must be idempotent or reject duplicate starts with typed error; cleanup works after partial failure.
- Shutdown must drain/destroy owned platform resources in reverse ownership order; avoid deadlocks and wrong-thread SDL calls.
- OS shutdown requests flow through an authorized lifecycle handler that can save/deny with a bounded deadline where the OS permits.
- No uncontrolled "kill process" command exposed through MCP; privileged actions require authorization.

### PlatformCapabilities v1 (proposed logical schema)
`{ os_family, os_version, cpu_arch, process_arch, cpu_features, window_system, display_modes, dpi_scale, hdr_signal, input_devices, available_graphics_apis, power_state_confidence, feature_flags, probes_version }`

- Capability probing must be incremental and optionally lazy, with **unknown** distinguished from **unsupported**.
- No hardware fingerprinting or network telemetry by default; privacy minimization and explicit opt-in for diagnostics.
- Feature tiers for performance/graphics belong to GFX-01/QA-03, CORE-01 only conveys observed capabilities and confidence/source.

### PlatformEvent v1 (proposed logical schema)
`{ event_type, monotonic_timestamp, ordered_sequence, window_id?, device_id?, normalized_payload, origin, replay_seed? }`

- Bounded queue with overflow policy; input loss/overflow surfaced to the consumer.
- OS event ordering/monotonic timestamps and pause/resume semantics documented per OS.
- Replay is deterministic **for captured host events**, not proof full game simulation is deterministic across systems.
- High-frequency events may coalesce for presentation, but gameplay-critical input must not be silently dropped.

### WindowService and NativeBridge
- Lifecycle operations: create / destroy / resize / focus / maximize / fullscreen / move / enumerate displays / DPI change.
- Native OS handles are opaque, short-lived capability handles; explicit thread/lifecycle validity.
- Renderer requests presentable surfaces through a contract without CORE-01 depending on Vulkan or Metal types.
- File dialogs, drag-and-drop, clipboard, accessibility and IME may need native adapters; test each platform and use capability fallbacks rather than silent feature omission.

### Error model
Every operation returns structured status, recovery action, code and diagnostic ID; distinguish `PERMISSION_DENIED`, `UNSUPPORTED`, `UNKNOWN_CAPABILITY`, `RESOURCE_EXHAUSTED`, `OS_FAILURE`, `WRONG_THREAD`, `CANCELLED`, `TIMEOUT`, `DEVICE_GONE`. Logs must not expose secrets or private paths by default.

## 5. In-house R&D candidate: Stormline Adaptive Platform Layer (SAPL)

**Purpose:** use a small proprietary **capability graph + event journal** to expose the best verified features per host without hard-coding OS-specific conditionals throughout the engine.

- **Capability Graph:** records features, dependencies, confidence, failure reasons and quality-tier signals as structured data.
- **Adaptive Event Journal:** opt-in event capture for reproducing cross-platform focus, hotplug and lifecycle bugs with minimal CPU overhead.
- **Policy Handoff:** offers validated signals (supported, unknown, low-power, display changes) to future Quality Manager; policy itself remains outside CORE-01.
- **NativeBridge Contract:** versioned, narrow OS feature hooks that may be independently disabled when unavailable.
- **Proprietary status:** original architecture proposal; **not demonstrated unique, patented, faster or implemented**. SDL3 already solves much of the platform problem; SAPL must be justified against the simpler SDL3-only baseline.

### Innovation proof obligations
1. No functional regressions against direct SDL3 for lifecycle/windows.
2. Measured additional platform-event CPU overhead and memory footprint within an **approved** budget.
3. Reduced cross-OS branching/bug recurrence shown by test coverage, not assumption.
4. Graceful downgrade when capability unknown or permission denied.
5. Zero GPU dependency in headless mode and no sensitive telemetry without opt-in.
6. No extra abstraction layer retained solely for branding if not justified by evidence.

## 6. Platform compatibility and CI requirements

| Matrix | Initial research target | Items needing ADR |
|---|---|---|
| Windows | x64 editor/client, MSVC + Clang-cl; Windows desktop native window lifecycle | Windows minimum 10/11; ARM64 first-class or future |
| Linux | x64 editor/client, Clang + GCC; Wayland and X11; headless with no display | Minimum glibc/distro, package type, Vulkan requirements |
| macOS | Apple Silicon arm64 editor/client, native Cocoa integration; Apple Clang | Minimum macOS release, Intel x86_64 support scope, Metal vs Vulkan strategy |
| macOS Intel | Feasibility and sunset-risk assessment; no omission without explicit owner decision | Whether mandatory in 1.0, supported OS/GPU generations |
| Web | Separate PLAT-03 under WebAssembly/WebGPU and fallback study | Browser/device/version matrix and capability tiers |

**Test lab:** standard public GitHub Actions runners are documented as free for public repositories, with Linux, Windows, macOS arm64 and Intel labels; CI success verifies compilation and host APIs, **not real-world GPU performance**. Run graphics benchmarks on real approved hardware later. CI may be subject to platform policy, concurrency, resource limitations and runner changes.

**Apple costs:** Apple Developer Program fee, notarization and signing requirements depend on distribution channel. No subscription has been authorized. Distinguish local development/testing vs signed/notarized public distribution; a cost conflict must be surfaced as a release blocker rather than silently paid.

## 7. Performance and reliability experiments required at implementation

- Cold/warm initialization and shutdown p50/p95/p99 across 100+ runs on each approved OS/hardware tier.
- Event handling: 1,000/10,000 input events and device hotplug under controlled replay, CPU cost and queue overflow.
- Compare SDL3 direct baseline vs SAPL under identical scenarios, build flags and hardware; keep the simpler design if SAPL offers no demonstrable value.
- Idle host CPU/RAM/GPU wake-ups, editor multiwindow/HiDPI impact, controller connect/disconnect and OS sleep/resume.
- Headless server launching without graphical/audio subsystem or GPU.
- Memory sanitizer/leak checks where supported, wrong-thread checks, crash/abort cleanup and process exit codes.
- OS-specific failure injection: absent display, unsupported HDR, permission denial, removable device, interrupted initialization, out-of-date driver.
- Security tests: path normalization, native handles lifetime, OS permission boundaries, no ambient privilege propagation to scripts/agents.

**No numeric performance claims or benchmark results are currently available.** Thresholds must be owner-approved together with named hardware/OS versions before acceptance.

## 8. Dependencies, governance and gates

- Must not import rendering backends into CORE-01 public interfaces; depends logically on CORE-02 memory/CORE-03 jobs/CORE-04 timing contracts only where necessary, without circular compile dependencies.
- Source Pack, NLE-D017 platform requirement and NLE-D018 delegated planning authority apply. No MVP, no paid tools, no CodeRabbit and no external human reviewers.
- This document is **technology research only**, not a work order to implement binaries.
- Final technology choices require ADR status promotion after independent license/maintenance/benchmark/platform evidence, with automatic review gates and source changes.
- Following research: next module CORE-02 on memory/allocators, **only after this increment's audit and checkpoint reconciliation**.

## 9. Acceptance status

| Obligation | State |
|---|---|
| Three desktop OS plus Web separation documented | PROPOSED DESIGN |
| Technology matrix and alternatives | DOCUMENTED |
| Threat boundaries, thread constraints and errors | DOCUMENTED |
| Benchmark/test plan | DOCUMENTED |
| C++/SDL3 build & multios test | NOT EXECUTED |
| New SAPL performance advantage | NOT PROVEN |
| Final stack decision | PROPOSED ADR ONLY |
| Engine implementation / launch | NOT STARTED |
