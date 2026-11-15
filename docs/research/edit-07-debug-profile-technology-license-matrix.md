# EDIT-07 — Debug/Profiling/Preview Technology, License, Security and Platform Matrix

**2026-11-15 | P00 research only | [#276](https://github.com/KayzenRoot/stormline/issues/276) | BASE `64c7ea06a547742209cd11f5d949ab9c8989aa66`.** All references are candidates/developer tools; **no SDK, profiler, debugger, crash handler, dependency or license adopted**. Exact version, file-level SPDX, transitive SBOM, notices and OS security must be audited before implementation. NLE-D009 remains OPEN.

## 1. Observability/CPU tracing: CORE-06 sole authority
| Candidate | Verified fit | License/limitations |
|---|---|---|
| [CORE-06 architecture](../architecture/core-06-diagnostics-observability.md) / [ADR-0008](../adr/0008-core-06-observability-policy.md) | Stormline-owned event/span/counter/crash/export contracts, bounded sinks/consent | canonical backend owner; EDIT-07 only display |
| [spdlog](https://github.com/gabime/spdlog) | native local logging/rotating/async candidate vs minimal stdlib sink | MIT; fmt MIT candidate; bound sinks/drops, no audio callback logging |
| [Tracy](https://github.com/wolfpld/tracy) | frame/CPU/GPU/memory/locks/threads tracing and developer UI | BSD-3-Clause upstream; exact tag/per-file review, remote profiler listener OFF by default |
| [Perfetto C++ SDK](https://github.com/google/perfetto/blob/main/docs/instrumentation/tracing-sdk.md) | C++17 app spans/counters, offline trace UI/SQL, Windows/macOS client SDK and Linux/Android system integrations | Apache-2.0 project with per-file exceptions; system tracing may need elevated permissions |
| [OpenTelemetry C++](https://github.com/open-telemetry/opentelemetry-cpp) | optional server-side/service trace interchange | Apache-2.0, **no required cloud/remote exporter** |
| [Stormline Diagnostic Fabric](../architecture/core-06-diagnostics-observability.md) | potential bounded frame-aware incident correlation | PROPOSED hypothesis; prove-or-drop versus ordinary Tracy/Perfetto |

None can be claimed low-overhead, universal or secure without A/B fixtures and privacy/network tests. Compare OFF/MINIMAL/SAMPLED/DEEP CPU/heap/disk costs, dropped events and diagnostic quality.

## 2. GPU/frame developer tools and target mismatch
| Candidate / source | Genuine capability | Limits |
|---|---|---|
| [RenderDoc](https://github.com/baldurk/renderdoc) | MIT standalone frame capture for Vulkan, D3D11/12, OpenGL/ES on Windows/Linux/Android | **NO Metal**; no universal macOS/WebGPU capture, not an approved embedded library; only user-owned content |
| [Khronos Vulkan tools](https://docs.vulkan.org/guide/latest/development_tools.html) / [debug_utils](https://docs.vulkan.org/samples/latest/samples/extensions/debug_utils/README.html) | validation, synchronization diagnostics, named objects, optional shader debug | dev-only and overhead, capabilities must be checked |
| [Microsoft PIX](https://learn.microsoft.com/en-us/windows/pix/) | Windows DirectX12 GPU/timing/debug captures | Microsoft tooling/terms, Windows-only, no redistributed SDK approved |
| [Apple Xcode Metal debugger](https://developer.apple.com/documentation/xcode/metal-debugger) | Metal frame/GPU trace and profiling | Apple toolchain/entitlements; development tool only |
| [W3C WebGPU](https://www.w3.org/TR/webgpu/) | optional timestamp-query feature | availability/precision privacy-gated; cannot invent GPU timings |
| [Chrome DevTools Protocol](https://chromedevtools.github.io/devtools-protocol/) | Chromium developer/debug/tracing privileged protocol | not stable for unsupported third-party direct integration; never automatic remote listener |

## 3. Crash/local diagnostics
| Candidate | Capability | License/security |
|---|---|---|
| [Crashpad design](https://chromium.googlesource.com/crashpad/crashpad/+/HEAD/doc/overview_design.md) | native handler + local crash database/minidump, optional upload | Chromium source + transitive per-file license review; **raw dumps may contain credentials/private memory**, upload OFF/default and explicit consent |
| [Breakpad](https://github.com/google/breakpad) | minidump/symbolication predecessor reference | BSD-family with extensive mixed per-file third-party licenses; not all-files BSD |
| OS native Windows ETW/PDB, Linux perf/eBPF/core, macOS Instruments/LLDB | performance and symbolication oracles | platform/entitlement/privilege/redistribution vary; no root or process attach mandate |
| Browser Performance/DevTools | Web JS/Wasm metrics and debug reference | browser/version and origin sandbox only, not native parity |

## 4. Threat and license matrix
| Threat | Failure | Gate |
|---|---|---|
| Crash dump/frame capture | raw memory, secrets, private art, third-party content | separate HIGH_ASSURANCE authorization, local retention/permissions, redacted summary and explicit preview |
| Profiling/metric flood | cardinality/CPU/disk exhaustion, recursive logging, RT callback deadline | CORE-06 bounded typed labels/sinks/drop counters, sampling and nonblocking callback |
| Preview process | plugin/script network/filesystem side effects and state corruption | sandbox/process policy, VFS grants, frozen asset revision, COW, owner receipts |
| Breakpoint/watch | arbitrary eval, code execution, stale line and private locals | GAME-02 typed owner hook, read-only allowlist, depth/time quotas, revision checks |
| Remote listener/CDP | unauthorized process access or telemetry upload | OFF, separate owner security decision |
| WebGPU high-res clock | cross-origin side channel | feature detection and browser privacy precision constraints |
| AI/MCP/export | cross-project data leak, path traversal, hostile log prompt injection | owner-side scope checks, escape content, CORE-06 redacted pagination, DATA-01 grant |
| License | proprietary SDK/tool redistribution, mixed transitive files | exact tag, SPDX, SBOM, NOTICE and owner/legal approval |

## 5. Primary sources and unresolved decisions
[Tracy](https://github.com/wolfpld/tracy), [Perfetto SDK](https://perfetto.dev/docs/instrumentation/tracing-sdk), [Perfetto license](https://github.com/google/perfetto/blob/main/LICENSE), [spdlog](https://github.com/gabime/spdlog), [RenderDoc](https://github.com/baldurk/renderdoc), [Vulkan tools](https://docs.vulkan.org/guide/latest/development_tools.html), [PIX](https://learn.microsoft.com/en-us/windows/pix/), [Metal debugger](https://developer.apple.com/documentation/xcode/metal-debugger), [WebGPU](https://www.w3.org/TR/webgpu/), [Crashpad](https://chromium.googlesource.com/crashpad/crashpad/+/HEAD/doc/overview_design.md), [Chrome DevTools Protocol](https://chromedevtools.github.io/devtools-protocol/).

Unresolved: CORE-06 correlation extension, preview sandbox/owner debugger hooks, exact profiler/renderer/native tools, symbolication pipeline, raw dump security/retention, OS/Web targets, numerical CPU/GPU/memory/audio budgets, release class and NLE-D009. **No adoption/approval.**
