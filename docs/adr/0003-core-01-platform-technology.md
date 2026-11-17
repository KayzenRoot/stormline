# ADR-0003 — CORE-01 Cross-Platform Host and Build System

**Status:** PROPOSED TECHNOLOGY SELECTION (NOT FROZEN)  
**Date:** 2026-11-14 | **Work Order:** NLE-P00-WO-002-CORE-01 | **Issue:** #6

## Context
Stormline must deliver editor and exported games for **Windows, Linux and macOS**, while preserving a separate Web target and headless servers. The project is a proprietary original engine using specialist libraries; no release may be distributed before complete 1.0 DoD. We require reproducible builds and free public CI without mandatory external human reviewers.

## Proposed decision
1. Adopt **C++20 as lowest common initial standard**; evaluate C++23 only after proven full toolchain compatibility.
2. Use **SDL3 as preferred host adapter** for windowing, OS events and device discovery, keeping direct OS APIs in narrow Windows/Linux/macOS bridge modules only where necessary.
3. Use **CMake Presets + Ninja** as preferred build strategy; allow Xcode/MSBuild when justified by native debugging/packaging.
4. Keep the **renderer API policy separate**: macOS native Metal vs alternative Vulkan portability belongs in GFX-01, with Apple Silicon minimum architecture coverage and Intel compatibility to decide in an ADR.
5. Explore **Stormline Adaptive Platform Layer** only if it proves value beyond thin SDL3 wrappers. Keep capability schema, event replay and deterministic error reporting small and inspectable.
6. Dedicated headless server startup must work without display, audio device or GPU.
7. Documentation and design can be accepted; **do not promote implementation dependencies or performance claims to APPROVED** until compiler matrices, license reviews, benchmark and platform tests pass.

## Alternatives considered
- **All-platform native window/input systems:** more direct OS control but multiplies code/maintenance/security surface for no measured benefit; hold as selective bridges.
- **GLFW:** lean and viable alternative; requires comparable tool and feature investigation. SDL3 currently preferred for broader device/window/event integration.
- **C++23 first:** newer language library features but could constrain CI toolchain versions; evaluate after baseline proven.
- **CMake vs Meson/Bazel:** standardization and maintenance preference favors CMake; measure build reliability instead of asserting universal superiority.
- **Cross-platform Vulkan-only for entire engine:** rejected as premature and poor layering; macOS Apple Silicon/Intel require explicit backend evaluation and Khronos now marks MoltenVK deprecated for Apple Silicon.
- **Unconditional SAPL proprietary rewrite:** rejected; any new layer needs proven gains or capability correctness versus simpler baseline.

## Why this is technically reasonable
It minimizes custom OS/platform plumbing and concentrates unique Stormline R&D on lighting, VFX, audio, performance and AI authoring. A native OS escape hatch retains control where the library cannot meet requirements. The core capability contract avoids exposing SDL or platform types in gameplay and MCP APIs.

## Consequences
- Version pinning, compliance notices and compiler CI are mandatory.
- Platform ownership and main-thread rules must be part of public module contract.
- Xcode signing/notarization and Apple distribution channel are **unresolved** and may incur costs beyond zero-cost CI; no payment is authorized.
- Windows/Linux/macOS editor and exports must be validated on real hardware before claiming support; CI does not replace GPU/driver testing.
- Platform capabilities are advisory; no collection of identifiable telemetry without consent.
- If SDL3 or SAPL fail acceptance tests, reopen ADR and evaluate an alternative; no sunk-cost lock-in.

## Proof obligations to promote ADR to APPROVED IMPLEMENTATION
- License review of exact SDL3 and build-tool versions and all transitive deps.
- Build matrix passing on Windows x64, Linux x64 (Wayland/X11 where real environment available), macOS arm64; Intel feasibility decisions from owner.
- Headless mode with zero GPU/display requirements and no leaks across repeated start/stop.
- CPU/memory baseline and event latency measured versus direct SDL3.
- Error/edge-case suite for sleep/resume, hotplug, DPI, focus and multi-window.
- Security for native bridges, path handling and agent isolation.
- Explicit owner-approved support matrix and documented cost/legal limitations.
- Objective independent audit with Evidence Bundle and no HIGH/CRITICAL defect.

## Current result
**APPROVED FOR PLANNING ONLY if this document PR is audited and merged.**  
Not code, not a compiler proof, not a license legal opinion, not a finished platform module.

## References
- https://wiki.libsdl.org/SDL3/README-platforms
- https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt
- https://wiki.libsdl.org/SDL3/SDL_IsMainThread
- https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
- https://github.com/ninja-build/ninja
- https://developer.apple.com/documentation/metal
- https://docs.github.com/en/actions/reference/runners/github-hosted-runners

## CORE-01 G3-V05 — ratificacao de fatia interna (ratificacao limitada, SEM promocao da ADR integral)

Em 2026-11-17 o proprietario ratificou **apenas** a direcao para a primeira fatia interna CORE-01: C++20 `CPU_ONLY_HEADLESS` sem SDL3, `INTERNAL_ONLY`, futura capacidade minima `MANDATORY_1_0` do CORE-01, risco `STANDARD` limitado ao primeiro incremento, estados/erros tipados, RAII e rollback, CI provisoria conforme [PR #421](https://github.com/KayzenRoot/stormline/pull/421). A proposta anterior encontra-se na [issue #387 #6954081280](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6954081280); o voto expresso foi dado nesta conversa, nao presumido a partir do comentario de proposta.

**A ADR-0003 continua `PROPOSED TECHNOLOGY SELECTION (NOT FROZEN)` no conjunto.** SDL3 3.4.20, ABI HostHandle externa, API de janelas/input, instalacao e pin de SDKs/candidatos, distribuicao, perf e macOS hardware nao foram aprovados por este voto. A decisao limitada necessita contratos concretos e qualificação G4/G5/G6 por PRs auditadas antes de virar implementacao; nao altera ADR-0075, NLE-D009, registry ou 80 WOs. Candidatos globais G3-V01 permanecem inalterados.
