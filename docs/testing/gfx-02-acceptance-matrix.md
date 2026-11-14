# GFX-02 — Future Shader Compiler, Reflection and Material Acceptance Matrix

**WO:** NLE-P00-WO-002-GFX-02 | **Issue:** #126 | **Current:** TEST PLAN ONLY, **NOT EXECUTED**.
Every test needs a rights-cleared golden fixture with source/revision digest, compiler binary/flag/SDK hash, target OS/API/GPU driver/browser and real command/run log. Real GPU rendering tests are distinct from syntactic validation.

| ID | Risk | Proposed test | Future objective proof |
|---|---|---|---|
| SHD-001 | STANDARD | simple 2D sprite/atlas shader on Vulkan and D3D12 | typed reflection layout and pixel golden, color/alpha mapping |
| SHD-002 | STANDARD | layered 2.5D shader depth/alpha/UV | correct hybrid draw order under GFX-01 orientation rules |
| SHD-003 | STANDARD | 3D PBR shader with normal map and multiple material bindings | validated reflect/binding/precision and golden target outcomes |
| SHD-004 | STANDARD | glslang GLSL->SPIR-V source; spirv-val | matching target version/extensions, source diagnostic span |
| SHD-005 | STANDARD | DXC HLSL->DXIL D3D12 | shader model validated, reflection stage/bindings correct |
| SHD-006 | STANDARD | DXC HLSL->SPIR-V Vulkan | compare reference shader Vulkan output and binding remaps to GLSL |
| SHD-007 | STANDARD | Slang module/generic specialization Vulkan/D3D12 | pinned frontend target, reflection vs fallback compiler and compile size |
| SHD-008 | ELEVATED | Slang Metal target experimental -> native MSL validation | either proven native Apple Silicon MSL/metallib or clear UNSUPPORTED_TARGET, no fake parity |
| SHD-009 | ELEVATED | Slang WGSL experimental/incomplete -> native WGSL path | browser validates WGSL; reject unproved translator feature |
| SHD-010 | STANDARD | direct WGSL + Tint/Naga validator in browser WebGPU | WGSL binding/type compatibility on exact browser+GPU |
| SHD-011 | STANDARD | WebGL2 GLSL ES degraded subset | explicit unsupported compute features, fallback effect quality and limits |
| SHD-012 | ELEVATED | native Metal shader build on macOS arm64 | actual Apple tooling GPU draw, resource mapping and diagnostics |
| SHD-013 | ELEVATED | reflection mismatch set/binding/space/array/format | hard error before GFX-01 pipeline, no silent remap |
| SHD-014 | ELEVATED | vertex-fragment interface/location and precision mismatch | clear stage/source diagnostics, no native GPU hang |
| SHD-015 | STANDARD | parameter instance scalar changes under stable layout | dynamic uniform update, no shader recompile, stable MaterialAssetId |
| SHD-016 | STANDARD | reachable variants with many static switches | deterministic variant keys and hard cap, no full Cartesian explosion |
| SHD-017 | ELEVATED | incompatible material shader layout during hot reload | preview conflict, last-good pipeline and user overrides preserved |
| SHD-018 | ELEVATED | compile error / compiler crash during reload | active generation remains, correct typed diagnostic and retry |
| SHD-019 | ELEVATED | device loss during candidate pipeline build/fence wait | GFX-01 old generation invalidated, no stale handle, safe recovery/restart-required |
| SHD-020 | ELEVATED | change transitive include + recompilation cache | correct dependent invalidation, unrelated target cache retained only if valid |
| SHD-021 | ELEVATED | malicious include path traversal / symlink race / remote URI | DATA-01 capability scoped open denies, zero external data leak |
| SHD-022 | ELEVATED | include cycle, macro recursion, shader bomb, huge variants | bounded parser/memory/CPU/job/cancel and error, no unbounded compiler |
| SHD-023 | ELEVATED | poisoned cached artifact/native driver cache | verify hash/provenance/profile; reject stale/device mismatch and safe recompile |
| SHD-024 | ELEVATED | unsanctioned MCP shader/host binary command/flag/native pointer | deny with no compiler, GPU or filesystem side effect |
| SHD-025 | STANDARD | diagnostic multi-file includes and graph source-map | editor project-relative file/line/column match, no absolute path |
| SHD-026 | ELEVATED | confidential shader source, compiler logs/crash report | redaction/telemetry OFF by default, no source/assets IP exfiltration |
| SHD-027 | STANDARD | same pinned recipe/source on two hosts | bytewise identical where proven, otherwise explicit semantic tolerance/nonreproducibility report |
| SHD-028 | STANDARD | cold/warm cache, incremental compile, hot reload latency | p50/p95/p99 CPU time, peak RSS/disk/cache hit and frame-time on named low-end GPU |
| SHD-029 | ELEVATED | exact dependency licenses and third-party source rights | Slang LLVM exception and deps, DXC UIUC and notices, SPIRV-Cross file SPDX, asset redistribution checked |
| SHD-030 | STANDARD | SSVF graph-pruning against reachable-only baseline | conformance/fidelity, compiled variant count, latency and bytes; drop if no proved gain |

## Future execution protocol
- **Fixtures:** independently authored 2D/2.5D/3D shader and material corpus; licensed source, exact versions and golden pixels. Avoid third-party protected games/assets.
- **Stage correctness:** direct frontend compile, target IR validation, independent reflection compare, link GFX-01 resource layout, then GPU on hardware. A semantic check or mock cannot prove device pipeline conformance.
- **Platform:** Windows x64 D3D12+Vulkan, Linux x64 Vulkan with driver matrix, macOS Apple Silicon native Metal, browser WebGPU secure contexts + WebGL2 degradation. Intel macOS v1 coverage separate ADR. Public docs CI alone is not GPU evidence.
- **Security:** compiler subprocess isolation/allowlist/quotas, malformed shader/fuzz, VFS include path and archive policy, read-only preview and MCP denial, driver crashes/downgrade.
- **Metrics:** compile/read/translate/refl/pipeline creation, frame stalls, p50/p95/p99, peak CPU/RAM/disk/VRAM, shader bytes and hot reload rollback. Record cold and warm baselines, exact source/ABI/driver/hardware and target capability set.
- **Supply chain:** pin compiler executable hash and exact source tag + file-level third-party notices, SBOM, bundled runtime-only pieces vs Editor-only compilers, license of authored shader sources.
- **CI:** current GitHub free `docs-validation` checks Source Pack/links, module DAG and 80 blocked WOs only; no native build/sanitizers/Mac/GPU shader tests have run.

**SHD-001..SHD-030 have NOT BEEN RUN.** They are acceptance specifications for future implementation.
