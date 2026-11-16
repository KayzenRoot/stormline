# BIZ-02 — 2026 SDK, ABI, Plugin, WASI and Developer Tooling Technology Matrix

**Research 2026-11-16, NLE-P00-WO-002-BIZ-02, issue #366; only formal GAME-02 + AI-01.** All versions, licenses, support claims must be pinned to **exact future release/tag/file** before code adoption. The cited upstream release/docs describe external technology, not Stormline implementation. NLE-D009 source license OPEN, all 80 code WOs blocked.

## Runtime/ABI architecture alternatives
| Candidate | Scope + value | Risk/gate and preliminary stance |
|---|---|---|
| Stormline-owned C99-compatible ABI and function table | stable named entry, explicit size+version, language FFI, no STL across compiler | **PROPOSED**, not universal binary compatibility; verify calling convention, data layout, struct size, allocator, endianness, OS/arch and 32/64-bit |
| Native C++ headers and templates | convenient source wrappers | C++ convenience layer only; avoid binary plugin interface and lifetime objects crossing CRT/stdlib |
| COM-style vtables | versioned interface tables familiar on Windows | vendor/OS complexity, portability unproven, not default |
| Out-of-process RPC | crash containment for untrusted native extension, narrow interface | IPC authentication, OS sandbox, rate/budget/timeout, cross-target cost and data exfiltration risk |
| GAME-02 Luau MIT candidate | text/game scripts and graph under existing host | no duplicate VM; native Luau VM ABI not exposed, Luau dialect not Lua 5.4 equivalence |
| WIT / WebAssembly Component Model | typed multi-language guest imports/exports, canonical ABI | WIT schema and tools depend on actual runtime target; **optional R&D**; WASI guest is not unrestricted OS access |
| WASI 0.2 (Preview 2) | broadly supported mature component model baseline candidate | verify language toolchain, browser adapters, host security import whitelist |
| WASI 0.3 | June 2026 native async futures/streams, Wasmtime >=46 support | current spec but fewer guest/browser toolchains; do not make mandatory Web+desktop baseline yet |
| JS/ESM Web plugin | web-native loader and dev ergonomics | CSP, workers, origin permissions, cross-origin caching and isolation; no native DLL or automatic WASI |
| Wasmtime | mature component runtime, security knobs and embedding | upstream Apache-2.0 **with LLVM exception in LICENSE**, exact crate/CDN/transitive licenses and VM behavior later validated; no runtime chosen |
| WAMR/Wasm3 | smaller embedded guest alternatives | check exact tag/license/feature completeness and async/WIT support; no claims without bench |

## Tooling, packaging and documentation
| Tool/pattern | License/source status | Risk and future gate |
|---|---|---|
| CMake Config package, `install(EXPORT)`, relocatable paths | [official CMake import/export guide](https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html), tool licensed BSD-3-Clause generally with third-party components | source-only generated docs in P00; future packaged SDK must pass clean consumer install with no developer paths |
| CMakePresets/Ninja/CTest | pin actual toolchains, tests and install modes | no hidden dependency download; Windows/MSVC vs clang/gcc/AppleClang exact compile matrix |
| Doxygen or Sphinx/MkDocs or custom docs | evaluate per-version license, maintenance and output reproducibility | docs generators not equivalent to public API correctness; offline and accessible modes |
| ABI compliance checking (libabigail, abidiff or alternative) | GPL/LGPL/other transitive constraints to audit exact version | internal developer tool vs redistributable SDK distinction, ABI false positives |
| SPDX/REUSE/ORT/SBOM | [SPDX](https://spdx.org/licenses/), [REUSE](https://reuse.software/spec-3.3/), [ORT](https://github.com/oss-review-toolkit/ort) | scanner not legal advice; BIZ-01 real packaged file closure and owner grant needed |
| Deterministic schema bindings | generate C/C++ wrappers, typed language shims, WIT/JSON definitions from same descriptors | validate type ownership/nullable/UTF-8/arrays and error mapping, no shell exec |
| GitHub public standard Actions CI | docs-only workflow currently exists | code-build CI, cache/artifact billing limits, macOS runner/physical GPU costs need later approved review |

## Binding and compatibility matrix for future qualification
| Target | Native trusted extension | Sandboxed guest | API/packaging constraints |
|---|---|---|---|
| Windows x86_64 (ARM64 optional) | DLL with explicit exported C entrypoint | WASM guest or approved sandbox process | MSVC runtime/CRT and calling convention, loader lock, signing/digest, terminal paths, Unicode, OS min TBD |
| Linux x86_64 (ARM64 optional) | `.so` ELF with symbol/version policy | WASM guest or sandbox with seccomp/namespaces as appropriate, evidence needed | glibc/libstdc++ ABI, compiler/libc baseline, rpath/runpath, Wayland/X11 independent; no all-distro support claim |
| macOS Apple Silicon native (Intel conditional) | `.dylib` / signed bundle under app policy | WASM guest or hardened sandbox with entitlements | arm64 signing/notarization, hardened runtime/library validation/entitlements; Intel target and exact OS minima undecided |
| Web browser games | **NO native DLL/.so/.dylib** | JS ES module / worker or WASM component only if browser toolchain qualifies | CSP/permissions, secure context, WASI != browser OS API, cooperative cancellation and memory quota. Browser support actual feature probes |
| Headless server | platform-native trusted only after policy | Wasm/out-process with capability grants | no GPU required; deterministic tick and uptime/memory budget, no unapproved shell/network |

## Platform technical risks and official sources
- [MSVC 2015-2026 binary compatibility](https://learn.microsoft.com/en-us/cpp/porting/binary-compat-2015-2017?view=msvc-170) has **restrictions**, particularly latest linker/CRT dependencies; do **not** interpret as arbitrary ABI compatibility. [Microsoft DLL loader best practices](https://learn.microsoft.com/en-us/windows/desktop/dlls/dynamic-link-library-best-practices) documents loader-lock hazards and minimal `DllMain`.
- [CMake importing/exporting guide](https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html) prefers relocatable imported targets and `Config` package; pin compiler/sysroot and optional dependencies.
- [SemVer specification 2.0.0](https://semver.org/spec/v2.0.0.html) requires declared public API, public 1.0.0 contract, major incompatible/minor additive/patch compatible semantics, 0.y.z instability.
- [WASI releases](https://wasi.dev/releases), [Component Model FAQ](https://component-model.bytecodealliance.org/reference/faq.html), [WASI adopted feature list](https://github.com/WebAssembly/WASI/blob/main/docs/ComponentModelFeatures.md) document 0.2 stable and 0.3 2026 async adoption; tools/browser may lag.
- [Wasmtime Component Model](https://component-model.bytecodealliance.org/running-components/wasmtime.html) provides WASI 0.3 capabilities on Wasmtime >=46, **not** a guarantee that all language SDKs/JS browser tools do. [Wasmtime upstream LICENSE](https://github.com/bytecodealliance/wasmtime/blob/main/LICENSE) includes Apache-2.0 with LLVM exception; transitive runtime licenses require independent audit.
- [OWASP API Security](https://owasp.org/API-Security/) and [OWASP cheat sheets](https://cheatsheetseries.owasp.org/) for least privilege, untrusted packages, trust boundaries and input resource limits. Third-party marketplace, network fetch and payments **not** in current P00 scope.

## Risk and licensing notes
- A native plugin is arbitrary code within a process: **manifest permissions are advisory unless enforced by OS/process isolation**. Code signature assures integrity/trust signer, not confinement or absence of vulnerabilities.
- Plugins can contain separately licensed code, assets and fonts. Creator's game owns its independently authored assets, **embedded engine/runtime/third-party files still retain licenses**. Until BIZ-01 owner chooses license, do not publish a real SDK, template or plugin binary.
- Packages must guard directory traversal, zip bombs, archive symlinks, dependency confusion, unsigned downloads, path spoofing, dynamic library hijack, input deserialization, stale handles, denial-of-service, credential leaks and sandbox escape. Security claims require threat modeling and real red-team tests, not notes.
- No OS support claim is proven by Linux-hosted docs CI, Xvfb, emulation or software renderer. QA-05 future actual hardware/OS qualifies release targets; missing actual device => NOT_QUALIFIED.
- Native code (future): ELEVATED/HIGH_ASSURANCE for untrusted extension injection, filesystem writes or network/financial effects. Docs-only risk LOW. R$0 is a target constraint, not a claim that legal review or physical device fleets are free.
