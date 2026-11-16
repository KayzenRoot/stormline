# CORE-01 / G3 — Exact-version candidate matrix, ABI, lifecycle, licenses and technical proof gates

**STATUS:** `G3_OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`. **ALL VERSIONS BELOW ARE CANDIDATE EVALUATIONS, NOT PINNED PROJECT DEPENDENCIES OR APPROVED ADRs.** Date 2026-11-16. **Stable Work Order** [NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md) · [issue #387](https://github.com/KayzenRoot/stormline/issues/387) OPEN · pinned base main `66f09f30d20c8bff2b326d9d8aebdee82da49b8b` · [G3 Evidence Bundle](../evidence/NLE-PRPLAN-CORE-01-01-G3-TOOLCHAIN-ABI-QUALIFICATION.md).

## 1. Authority, gates and non-goals

The owner has explicitly ratified **23 bounded directions**: C01-D01/D08/D09/D14; G1-M01..M08; and G2/G3 option A C01-D02/D03/D04/D05/D06/D07/D10/D11/D12/D13/D15. Those ratifications **do not authorize an untested stack as approved, pin exact compiler/SDK versions automatically, choose the engine-source license NLE-D009, mark ADR-0003/0075 APPROVED or write experimental host code**. This G3 step documents *version candidates, compatibility hypotheses, typed contract questions, test oracles and precise owner decisions required next*.

**G2 stays `CLEARED` only for its implemented scope**: repository ruleset `27393227`, only `refs/heads/main`, PR/zero reviews, real `docs-validation` strict, linear/squash, non-fast-forward/deletion blocked, no bypass; validated in #402–#406. **Do not touch this ruleset, required checks, workflows, repository settings or security controls**. G1 `PARTIALLY_RATIFIED_NOT_CLEARED`; G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`; G4–G8 BLOCKED. No code in this Work Order.

## 2. Source date and three distinct version states

Research sources were inspected on **2026-11-16**. Never merge these levels:

1. **Upstream published:** version/tag exists as a public stable release. This is a fact about the publisher, **not** a tested or ratified Stormline version.
2. **Runner installed:** a version appears in a published GitHub runner-image inventory or local `--version`; mutable hosted images may differ. Requires a dated image receipt.
3. **Stormline proven and approved:** an owner-approved version candidate with immutable artifact digest, native builds, error/ABI/security tests and owner sign-off in a later Work Order. **CURRENT COUNT: ZERO.**

Version syntax, patch and build IDs are separate; using `latest` in a release build destroys the baseline. A public CI image is not a physical hardware certification, signing entitlement, or a paid Apple release pipeline.

### 2.1 Platform / toolchain evaluation matrix (proposed, not adopted)

| Target / purpose | PRIMARY EVALUATION candidate | SECONDARY / compatibility challenge | Exact open proof obligation |
|---|---|---|---|
| **C++ language** | ISO C++20 internal; MSVC `/std:c++20 /permissive-`, GCC/Clang/AppleClang `-std=c++20` | C++23 only experimental, named modules not required | Define supported C++20 features/library subset; `__cplusplus`, feature-test macros, exceptions/RTTI/threading policy and reproducible compiler output; no public C++ ABI guarantee |
| **Windows compiler** | **Visual Studio 2026 Build Tools 18.12.0** (released 2026-11-10) and **MSVC toolset 14.50** (documented long-term compiler series) as **separately pinned candidate components**, *NOT assumed bundled together* | **MSVC 14.51** standard candidate; Clang-cl alternative after CRT/toolchain proof | `vswhere`, `cl /Bv`, `_MSC_VER/_MSC_FULL_VER`, `link /? `, selected MSVC/Windows SDK/CRT versions, clean x64 build; test toolset availability on `windows-2025-vs2026` runner |
| **Windows SDK** | **10.0.26100.9457** (Microsoft, September 2026) as a candidate for Windows 11 OS floors | 10.0.28000.2957 September 2026 evaluation; not an automatic OS minimum bump | Installed `WindowsSdkDir/Version`, headers vs import libs, runtime minimum Windows 11 25H2 x64/26H2 compatibility (G1), dynamic CRT redistribution, no privileged installer |
| **Linux compiler** | **GCC 16.2** (2026-08-07) research candidate using a verifiable, reproducible installation distinct from runner default | **LLVM/Clang 23.1.5** (2026-11-03) candidate cross-compiler, **GCC 15.3** compatibility fallback; do not assume any preinstalled in Ubuntu 24.04 | `g++ --version`, `clang++ --version`, `ldd --version`, `readelf`, libstdc++/libc++ and GLIBCXX symbol requirements, apt/release provenance, binary hash, pinned toolchain image; CPU x64 AVX/AVX2 optional dispatch |
| **Linux OS/ABI floor** | Ubuntu **24.04 LTS x64** + glibc **2.39** reference baseline already owner-ratified G1 | X11/Wayland loader, different distro and newer kernel without overclaiming cross-distro support | Build/link on glibc baseline (new compiler may introduce too-new `GLIBCXX` symbols), ELF `NEEDED`/RPATH/`RUNPATH`, no accidental distro floor escalation, no GPU required in headless |
| **macOS host/compiler** | **macos-15** standard GitHub Apple ARM64 runner with **Xcode 26.3**, build **17C529**, macOS SDK **26.2**, selected via `DEVELOPER_DIR`; AppleClang nominal `17.0.0` appears in dated image inventory | Xcode **16.4** + macOS SDK 15.5 fallback compatibility challenge; Xcode 26.6 needs host macOS 26.2+ and cannot be presumed supported on macOS 15 host | `xcodebuild -version`, `xcrun clang --version` **full AppleClang build currently UNKNOWN**, `xcrun --show-sdk-version`, `otool -L`, deployment target **macOS 15 arm64** separate from build host/SDK, `lipo -info`, no Intel Mac support implied |
| **GitHub CI host labels** | `ubuntu-24.04` x64; `windows-2025-vs2026` x64 *subject to verified availability*; `macos-15` ARM64, **standard public GitHub-hosted only** | `windows-2025` x64 for older MSVC baseline, macOS 26 arm64 for compatibility rather than deployment-floor test | Explicit runner availability/images as of run, OS/arch/toolchain dump and xcode-select; no workflow activation, paid runners, secrets or extra required checks in this PR |
| **Portable native dep / SDL3** | **SDL3 3.4.20**, release archive date **2026-11-03**, source archive/tag+SHA to be obtained during separate pinning; zlib | SDL3 3.4.18 regression comparator, GLFW/native OS backend if evidence requires | SDL license snapshot, build/install/import runtime, strict thread/main APIs, version+digest provenance and zero SDL exposure across public engine contracts |
| **Build orchestrator** | **CMake 4.4.5**, released 2026-10-27, conservative candidate; `CMakePresets.json` + `ctest --preset`, schema to be decided | **CMake 4.5.0**, released 2026-11-12, as canary; historic minimum **3.27 / Presets schema 6** remains a *separate non-final candidate*, not elevated | Owner selects **minimum CMake version and Presets schema** after proof; `cmake --version`, preset listing/JSON schema, Ninja generator, Windows/macOS native IDE fallback, configure/build/test failures and deterministic reconfigure |
| **Ninja** | **Ninja 1.13.2**, upstream stable release **2025-11-20** | Ninja 1.13.1 regression comparison only | Freeze per-OS official asset SHA-256 (upstream API publishes digests), `ninja --version`, parallel build reproducibility, interruption/failure propagation, license/NOTICE |

**Version selection recommendation**: use the conservative CMake 4.4.5 primary versus 4.5.0 canary; prioritize an available macOS 15 host/Xcode pairing over the newest Xcode requiring macOS 26; test GCC 16.2 and Clang 23.1.5 as independently provisioned compilers, **not invented default contents of Ubuntu 24.04**. MSVC 14.50 is a long-term compiler family; VS 18.12.0 is a different IDE/Build Tools product version. Never equate them.

**Critical unresolved AppleClang pin:** published `macos-15-arm64` image inventory lists a nominal `Clang/LLVM 17.0.0` and Xcode 26.3 build 17C529, but **the exact AppleClang vendor patch/build string for that selected Xcode was NOT obtained from a live runner**. Do NOT invent it or claim AppleClang `17.0.0` fully pinned; evidence must capture full `xcrun clang --version` under `DEVELOPER_DIR=/Applications/Xcode_26.3.app/Contents/Developer`. Image inventory is mutable and may change before execution.

### 2.2 Hard distinctions carried from owner G1 choices
- Win11 **25H2 x64** provisional runtime floor; Win11 **26H2** compatibility candidate, subject to Microsoft lifecycle and vendor CPU; *not* GPU minimum/certification.
- Ubuntu 24.04 x64/glibc2.39 reference floor; no promise of all distributions.
- macOS **15 Apple Silicon ARM64** runtime floor and macOS **26** compatibility; build host **may be newer than runtime target**.
- x86_64 portable baseline **without mandatory AVX/AVX2**; optional feature-detected dispatch only. Apple ARM64 uses native ISA.
- HEADLESS fixture: CPU-only 2 logical cores/4 GiB RAM; window fixture: 4 logical cores/8 GiB; **test fixtures, not commercial product minimums**.
- G1 runtime/evidence design 200 headless cycles, 100 windows per OS, 10,000 events, 30 cold+30 warm, zero lost critical events, negative no-display error <=5 seconds; p95/RSS acceptance **numeric thresholds still unratified**. Do not pretend p99 justified by 30 samples.

## 3. Proposed architecture/proof boundaries (typed draft, not implementation)

### 3.1 Minimal lifecycle and ownership contracts to ratify separately
**Host states** `UNINITIALIZED → INITIALIZING → RUNNING ↔ SUSPENDED → STOPPING → TERMINATED`, plus explicit `INIT_FAILED` with cleanup/terminal transition. Reentrancy/duplicate init, partial errors and stop during init must be deterministic. Invariants: no SDL init/quit calls from unauthorized thread; windowed SDL video/input startup/teardown on main thread, balanced subsystem refcounts, `SDL_RunOnMainThread(..., wait_complete=true)` must not form a main-thread cycle. Headless path has **zero mandatory SDL video/audio/GPU calls** and does not require a dummy display.

**Host interface candidate (pseudocontract only):** `HostConfig{mode: Windowed|Headless, features, budget, error_policy}`, `HostHandle{opaque id, generation}`, `HostError{category, platform_code, retryable, UTF8 message}`, `Capability{SUPPORTED|UNSUPPORTED|UNKNOWN, source, confidence, observed_at}`, `HostEvent{type, monotonic_tick, severity, payload}`. No field layout is approved. Define memory lifetime, callback threading, error ownership, destructor order, nonblocking cancellation, no leaks/double-free and bounded queue behavior **before** approval. `SDL_Window*`, `std::string`, exceptions and STL allocator types must NOT leak into a potential binary SDK ABI.

### 3.2 ABI policy and optional extension interface
- Internal C++20 modules: typed RAII ownership, explicitly defined error transport and versioning at source/API boundaries; compiler, stdlib and CRT ABI interoperability **not assumed**.
- A future **external** plugin/SDK interface requires **separate owner Scope approval**, not automatic from this research; then prefer versioned **C ABI** table, `uint32_t size` + `abi_version`, opaque handles with generation counters, explicit allocator/free and host/device errors, UTF-8 lengths, calling-convention/export annotations and no exceptions crossing DLL boundaries.
- Prove ABI compatibility with C and C++ consumers, MSVC/Clang-cl, GCC/Clang, AppleClang separately; allocator/mismatched-runtime, alignment, symbol visibility and version negotiation fixtures. C ABI **not required for every internal core module**.
- Serializer/endian format, networking, savegame binary contracts and plugin sandbox owned by their modules; CORE-01 must not claim them.

### 3.3 Runtime feature policy
Capabilities are tri-state `SUPPORTED | UNSUPPORTED | UNKNOWN` with provenance; UNKNOWN is not false. Prefer SDL3/platform bridge and proven adapters. Any **SAPL** extra graph or cache requires measurable semantic correctness and CPU/RSS benefit versus thin adapter, threshold pre-approved by owner. This is not permission to implement a proprietary platform layer.

## 4. Security/rights, costs and version pinning

| Component/class | Official upstream license or contract candidate | Must verify before adoption/distribution |
|---|---|---|
| SDL3 **3.4.20** | zlib upstream source LICENSE; *library license only* | Archived LICENSE at tag, third-party notices/dependency transitives, static vs dynamic deployment and release asset SHA-256 |
| CMake 4.4.5 / canary 4.5.0 | BSD 3-Clause, contains third-party components | Release checksums/signatures, copyright/third-party clauses, build-tool redistribution only if bundled |
| Ninja 1.13.2 | Apache-2.0 project source | Archive hash, license/NOTICE, packaged binary origin and whether actually redistributed |
| GCC/GNU runtime | GNU GPL-family source licenses with specific **GCC Runtime Library Exception** relevant where applicable | Exact libstdc++/libgcc linkage and exception terms, no assumption GPL automatically applies to Stormline binaries |
| LLVM/Clang | Apache-2.0 WITH LLVM-exception for LLVM components | Exact release LICENSE + third-party components, libc++ and sanitizer runtime redistribution |
| MSVC/Windows SDK | Microsoft product terms; **not equivalent to an open-source license** | CRT redistribution, SDK headers/lib/license terms, support, signing/release rights and tooling availability |
| AppleClang/Xcode/SDK | Apple Developer/Xcode contractual terms; **not automatically covered by zero-cost CI** | Build host, redistribution, Apple developer signing/notarization fees and entitlement in later release gate |

Generate an **SPDX SBOM** with pinned component version, license declared/concluded, source URL, SHA256, transitive dep graph, build option and NOTICE/attribution; security advisories/vulnerability/SBOM attestations must be evaluated against the exact package digest. The **Stormline engine-source license NLE-D009 remains OPEN**, independent of third-party tool licenses; no new LICENSE file or signing costs authorized.

**R$0 CI**: standard GitHub hosted runners free for **public** repos, but a private repo switch, larger/self-hosted runners, storage/egress and third-party services demand separate cost checks. Only existing `docs-validation` is required by active G2 ruleset; do not inject native jobs into workflows, branch protection or the paid Apple signing pipeline. Future C++ matrix requires a separate approved Work Order, threat separation for forks (`pull_request` read-only token, no privileged `pull_request_target` execution), runner-image digest and exact check name captured before any G2 settings amendment.

## 5. G3 proof obligations (ALL `FUTURE_NOT_EXECUTED`)

| G3 proof | Acceptance oracle and required evidence, under a later *separately authorized* execution | Now |
|---|---|---|
| **G3-P01** | Owner explicitly selects proposed version pins and acceptable fallback with official release references and license implications, not inferred from documentary merge | `FUTURE_NOT_EXECUTED` |
| **G3-P02** | Immutable per-OS source/binary archive SHA256, signature/attestation, exact tag/release date, SBOM and CVE snapshot for SDL3/CMake/Ninja + third parties | `FUTURE_NOT_EXECUTED` |
| **G3-P03** | `cl /Bv`, `_MSC_FULL_VER`, VS version, Windows SDK and CRT redist independently captured; C++20 compile/link evidence Windows x64 | `FUTURE_NOT_EXECUTED` |
| **G3-P04** | `g++`, `clang++` actual versions/digests and GNU/LLVM runtimes, flags, C++20 compile/link on ubuntu-24.04 x64, glibc/GLIBCXX floor symbols | `FUTURE_NOT_EXECUTED` |
| **G3-P05** | macOS 15 ARM64 xcodebuild/Xcode build/SDK/`xcrun clang --version` **full AppleClang string**, deployment target 15, Mach-O symbols/loader and native compile/link | `FUTURE_NOT_EXECUTED` |
| **G3-P06** | `cmake --version`, Presets schema/minimum version, `cmake --list-presets`, `ctest --preset`, Ninja runtime, CMakeUserPresets ignored, clean+incremental repro all 3 OS | `FUTURE_NOT_EXECUTED` |
| **G3-P07** | No stale Git Context Lock, pinned OCI/toolchain/runner image and compiler/library flags, provenance/readback of build metadata, no `latest` in released builds | `FUTURE_NOT_EXECUTED` |
| **G3-P08** | SDL3 windowed main-thread init/quit, event ordering/input/IME/HiDPI/hotplug, SDL adapter API isolation, handling SDL init failures and alternate backend rationale | `FUTURE_NOT_EXECUTED` |
| **G3-P09** | True headless no DISPLAY/Wayland/GPU/audio, typed error if requested video without display <=5 seconds; no dummy driver masking missing paths | `FUTURE_NOT_EXECUTED` |
| **G3-P10** | Lifecycle finite-state model, illegal transition/error injection, duplicate init/release, suspend/resume, concurrency/deadlock and balanced refcount fixtures | `FUTURE_NOT_EXECUTED` |
| **G3-P11** | HostHandle generation/lifetime, no cross-binary STL/SDL types, ABI version/allocator exception-safety test; if optional external plugin scope rejected, document explicit N/A | `FUTURE_NOT_EXECUTED` |
| **G3-P12** | Tri-state capability with UNKNOWN handling, provenance and disabled device cases; SAPL vs thin adapter overhead test with numeric owner-approved threshold | `FUTURE_NOT_EXECUTED` |
| **G3-P13** | 200/200 headless, 100/100 windowed per actual OS, >=10k event sequence, 30+30 cold/warm timings, zero silently lost critical events, sanitizer memory defects =0; p95/RSS thresholds **separate owner ratification** | `FUTURE_NOT_EXECUTED` |
| **G3-P14** | Security/fork trust controls, Windows/Linux/macOS standard public runners and complete real job names; no paid runner, no secret exposure, no required check changed from `docs-validation` | `FUTURE_NOT_EXECUTED` |
| **G3-P15** | Risk classification **per future authorized slice**, error recovery, device failure, unsupported CPU and portability regression plan; original 80 registry risks stay UNCLASSIFIED | `FUTURE_NOT_EXECUTED` |
| **G3-P16** | Independent technical audit: exact build evidence, license, code contracts and owner vote on ADR-0003/0075; **still PROPOSED** until separate decision; no code WOs released automatically | `FUTURE_NOT_EXECUTED` |

### Staged decisions still needed from the owner
- **G3-V01:** Select a *trial baseline* (compiler versions per OS, SDL3/CMake/Ninja exact versions, Windows SDK, Xcode, CMake Presets schema) from this matrix or revise. **Not authorized merely by request to research**.
- **G3-V02:** Explicitly choose whether experimental native build probes are needed before ADR approval and whether a separate **bounded, disposable, security-reviewed experimental WO** may be created. Current code remains forbidden.
- **G3-V03:** Define CPU/perf/RSS numerical thresholds, ABI guarantee extent and minimum redistributable artifacts with test apparatus; no assumption product DoD 1.0 finished.
- **G3-V04:** Legal/licensing of *components* vs independent NLE-D009 engine-source-license choice. Future distribution requires separate rights decision, not bundled with G3 technical qualification.
- **G3-V05:** Separate owner decision on ADR-0003/0075 only after credible evidence, without automatically reclassifying release/risk for the 80 coding WOs.

## 6. Same stable Work Order: one NECESSARY documentary increment

- **OBJECTIVE:** qualify exact candidate versions/SDKs and typed lifecycle/ABI boundaries, rights/SBOM, free CI and 16 measurable G3 proof obligations; do NOT ratify new versions.
- **CONTEXT:** main BASE `66f09f30d20c8bff2b326d9d8aebdee82da49b8b`, 23 owner-ratified bounded directions, G2 CLEARED ruleset `27393227`.
- **SCOPE:** this matrix + [G3 Evidence/Context Lock](../evidence/NLE-PRPLAN-CORE-01-01-G3-TOOLCHAIN-ABI-QUALIFICATION.md), **exactly 2 new Markdown**; checkpoint separate if documentary PR APPROVED.
- **OUT OF SCOPE:** modifying Ledger/Scope/DoD/Architecture/Requirements/ADR, C++ or build files, GitHub settings/workflows/ruleset, NLE-D009, 80 registry/manifest, CORE-01-02 and test execution.
- **FILES/SOURCES TO READ:** checkpoint > Ledger/ADRs > Scope > DoD > Architecture > Requirements; existing D02..D15 options, G2 applied Evidence, CORE-01 gate matrix, Work Order, registry/manifest, GitHub official upstream licenses and toolchain/runner inventory.
- **REQUIREMENTS:** OS floors and headless fixture from G1, no release before DoD, G2 actual protections intact, no required human reviewers, R$0 public CI and no untrusted fork privilege escalation.
- **ARCHITECTURE RULES:** SDL hidden in host, renderer GFX-01 owner, C++20 internal + opaque host handles, conditional future versioned C ABI, no UI/audio/GPU headless requirement.
- **CONSTRAINTS:** all version choices `PROPOSED_EVALUATION`, no new ratification, native code or speculative version assurance; no current platform certification.
- **ACCEPTANCE CRITERIA:** 2 ADDED Markdown; precise published vs installed vs proven distinctions, 16 G3-P items `FUTURE_NOT_EXECUTED`, intact Source Pack and registry, G3 technically open, no new approved ADR or engine-source license.
- **TESTS:** Github Docs Validation on exact PR HEAD, links/source hierarchy, DAG, registry, blocked Zcode selector, future PR plans; **native C++/hardware not run**. Objective pt-BR audit, squash only after CI, independent checkpoint PR audited.
- **DELIVERABLES:** research matrix, Evidence Bundle with Git blob object IDs/official sources, PR, CI, auditoria, readback, independent checkpoint if due.
- **REVIEW FORMAT:** APPROVED DOC ONLY / CORRECTION REQUIRED / BLOCKED; list base/head, risks, build proof gaps, owner questions and preserved gates.
- **STOP CONDITION:** stale HEAD/critical canonical source, CI red, HIGH/CRITICAL defect, implicit ADR/license/version approval, changed G2 rules/settings, any code or implementation packet work.

## 7. Verified official upstream references (2026-11-16)
- [Microsoft VS 2026 release history](https://learn.microsoft.com/en-us/visualstudio/releases/2026/release-history); [MSVC versioning (14.50 long term)](https://learn.microsoft.com/en-us/cpp/overview/compiler-versions); [Windows SDK downloads](https://learn.microsoft.com/en-us/windows/apps/windows-sdk/downloads).
- [GCC 16.2 release](https://gcc.gnu.org/gcc-16/); [LLVM 23.1.5 published assets](https://github.com/llvm/llvm-project/releases/tag/llvmorg-23.1.5).
- [SDL3 3.4.20 official release archive index](https://libsdl.org/release/); [SDL init main-thread](https://wiki.libsdl.org/SDL3/SDL_InitSubSystem); [SDL_RunOnMainThread deadlock warning](https://wiki.libsdl.org/SDL3/SDL_RunOnMainThread); [SDL main modes](https://wiki.libsdl.org/SDL3/README-main-functions); [SDL License](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt).
- [CMake 4.4.5 release](https://github.com/Kitware/CMake/releases/tag/v4.4.5), [CMake 4.5.0](https://github.com/Kitware/CMake/releases/tag/v4.5.0), [CMake Presets](https://cmake.org/cmake/help/v4.4/manual/cmake-presets.7.html), [CMake licensing](https://cmake.org/licensing/).
- [Ninja v1.13.2 upstream release (2025-11-20)](https://github.com/ninja-build/ninja/releases/tag/v1.13.2); [Ninja license repository](https://github.com/ninja-build/ninja/blob/master/COPYING), [LLVM release license](https://github.com/llvm/llvm-project/blob/main/LICENSE.TXT).
- [Apple Xcode 26.3 release notes / macOS 15.6 host](https://developer.apple.com/documentation/xcode-release-notes/xcode-26_3-release-notes), [Apple Xcode SDK and host matrix](https://developer.apple.com/xcode/system-requirements), [macos-15 ARM runner image inventory](https://github.com/actions/runner-images/blob/main/images/macos/macos-15-arm64-Readme.md), [GitHub standard public runners R$0](https://docs.github.com/en/actions/reference/runners/github-hosted-runners).

**Final invariants:** 23 prior bounded owner ratifications unchanged; G2 `CLEARED` in applied scope; **G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`**; G1 PARTIAL, G4–G8 blocked; ADR-0003/0075 PROPOSED, NLE-D009 OPEN; all 80 code WOs BLOCKED, zero ready/approved ADR, release/risk undecided, CORE-01-01/02 PLANNED_BLOCKED, `engine_implemented=false`. This document is a **version and ABI evaluation dossier, not an authorization to code**.
