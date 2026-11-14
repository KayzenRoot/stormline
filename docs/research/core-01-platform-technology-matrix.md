# CORE-01 — Technology Evaluation Matrix
Status: PROPOSED RESEARCH | Work Order NLE-P00-WO-002-CORE-01

## 1. Criteria and selection method
Weights are planning hypotheses, not statistical results. Review after experiments:
- **Cross-platform coverage and maintenance 25%**
- **Latency/resource footprint 20%**
- **License/IP/commercial suitability 15%**
- **Debuggability/toolchain 15%**
- **Interoperability and separation 15%**
- **Build reproducibility/operational cost 10%**

No numeric grade is assigned without primary evidence and reproducible tests. Do not conflate library "high-performance" marketing with benchmark proof.

## 2. Finalist comparison

| Responsibility | Primary candidate | Alternative | Evidence to gather before selecting |
|---|---|---|---|
| Language standard | C++20 | C++23 | Build all targets, ABI and standard library feature set |
| Cross-platform windows/input/events | SDL3 (zlib) | GLFW, direct OS API | SDL3 licensing, support policy, event latency and file dialogs/IME/multiple windows |
| Cross-platform configure | CMake Presets | Meson/Bazel | Reproducible builds, CI maintenance, toolchain support, cache invalidation |
| Build executor | Ninja (Apache-2.0) | Xcode/MSBuild native generators | Build latency, debuggability, integrated IDE support |
| Windows bridge | SDL3 + narrow Win32 hooks | Direct Win32 | Per-feature necessity, correctness and platform-specific header isolation |
| Linux bridge | SDL3 + Wayland/X11 modes | Direct protocol abstraction | Focus/DPI/input/clipboard/IME and packaging compatibility |
| macOS bridge | SDL3 + Cocoa/ObjC++ when necessary | Fully native Cocoa | Main-thread requirements, Apple Silicon/Intel, build and distribution |
| Capabilities API | Native SDL queries + thin schema | Proprietary SAPL capability graph | Cost of abstraction, unknown state, failure behavior and measurable benefits |
| Event replay | Deterministic capture/replay adapter (SAPL candidate) | Test harness around SDL events | Completeness, CPU/memory cost and multi-OS failure reproduction |
| Renderer interface | Opaque presentation request (no GPU API) | Direct Vulkan/Metal surface | API stability and no graphics dependency in CORE-01 |

## 3. License & provenance matrix (initial)
| Library/tool | Observed license / basis | Commercial risk / follow-up |
|---|---|---|
| SDL3 | zlib (official SDL repository license) | Low restriction for normal use; confirm exact vendored revision, notices and transitive dependencies |
| Ninja | Apache-2.0 repository | Capture notices, revision pin, patents/third-party pieces and distribution packaging |
| CMake | License to verify against exact distributed release | Do not declare approved without exact tool distribution/notice audit |
| MSVC/Windows SDK | Vendor tool terms | Verify redistribution rules, toolchain version and runtime redistributables |
| Apple Clang/Xcode/SDK | Apple SDK terms | Verify macOS targets, signing/notarization and Apple Developer membership costs |
| GCC/Clang | OSS with respective toolchain runtime/exception conditions | Verify link/runtime redistribution and ABI floor |
| Proprietary SAPL | Original Stormline implementation to be designed | Confirm clean-room IP, provenance, no borrowed source/assets |

Official docs (as consulted in 2026-11):
- SDL platform support: https://wiki.libsdl.org/SDL3/README-platforms
- SDL licensing: https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt
- SDL macOS notes: https://wiki.libsdl.org/SDL3/README-macos
- SDL threading: https://wiki.libsdl.org/SDL3/SDL_IsMainThread
- CMake Presets: https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
- Ninja license: https://github.com/ninja-build/ninja
- GitHub standard runners: https://docs.github.com/en/actions/reference/runners/github-hosted-runners
- Apple Metal: https://developer.apple.com/documentation/metal
- Vulkan Apple drivers: https://github.com/KhronosGroup/MoltenVK

## 4. Explicit exclusions and unknowns
- Vulkan/Metal/D3D12 API selection is **GFX-01**, not this Work Order.
- Window/input API selection is not the final gameplay input mapping (GAME-01).
- Web target platform lifecycle is PLAT-03.
- Performance claims need real hardware and scenario definitions.
- macOS minimum version, Intel sunset policy, Windows ARM, Linux distro floor, signing and distribution are open.
- Paid services, account registration and mandatory external reviews are prohibited unless explicitly approved.

## 5. Recommended disposition
- **RECOMMENDED FOR FUTURE PROTOTYPE:** C++20, SDL3, CMake Presets + Ninja, OS-specific native bridges behind narrow contracts.
- **TRIAL / BENCHMARK:** SAPL capability graph + event journal against unmodified SDL3 baseline.
- **HOLD:** C++23 as baseline until portability measured.
- **DEFER:** graphics backend policy to GFX-01; minimum supported OS targets to platform ADR; Mac distribution cost to commercial plan.
- **REJECT FOR CORE-01:** adopting renderer-specific types directly in the common OS/platform API.

**No software stack has been installed or benchmarked in this research.**
