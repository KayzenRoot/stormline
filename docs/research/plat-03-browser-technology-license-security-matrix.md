# PLAT-03 — Browser Runtime 2026 Technology, License, Compatibility and Threat Matrix

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NO ENGINE | research [#325](https://github.com/KayzenRoot/stormline/issues/325) | NLE-P00-WO-002-PLAT-03 | future implementation [#86](https://github.com/KayzenRoot/stormline/issues/86) OPEN/BLOCKED | BASE `dc7404722c347419197d001a7d61de3d676264b0`.** Order 68/80; **formal deps TWO-01 + GFX-01 + DATA-05 ONLY** (ADR-0022/0014/0013 PROPOSED), 67/80 documented before research, 13 pending, 80/80 future coding WOs BLOCKED, executor_ready=0, approved_adr=0, release classes all UNDECIDED, engine=false, NLE-D009 license OPEN.


**Research candidates with primary references; no current browser/hardware performance ranking, accepted licensing, exact toolchain versions or engine executable.** Browser versions, GPU support and deployment policy require later live testing.

## Primary upstream references and verified constraints
| Subject | Authoritative source | Engineering implication |
|---|---|---|
| WebGPU secure context and device | [W3C WebGPU living draft](https://www.w3.org/TR/webgpu/), [MDN WebGPU](https://developer.mozilla.org/en-US/docs/Web/API/WebGPU_API) | secure-context only; navigator/worker GPU, requestAdapter/requestDevice and feature/limit query, no universal WebGPU |
| Device loss | [MDN GPUDevice.lost](https://developer.mozilla.org/en-US/docs/Web/API/GPUDevice/lost) | loss may occur at any time; previous device resources must be recreated |
| WebGPU shader language | [W3C WGSL spec](https://www.w3.org/TR/WGSL/) | browser shaders validated under WGSL; native shader compiler GFX-02 owns translation |
| WebGL2 | [MDN WebGL2RenderingContext](https://developer.mozilla.org/en-US/docs/Web/API/WebGL2RenderingContext) | OpenGL ES 3.0 class; browser/GPU extensions still require probing |
| WebGL context loss | [MDN WEBGL_lose_context](https://developer.mozilla.org/en-US/docs/Web/API/WEBGL_lose_context) | simulated loss/restoration oracle, recreate resources |
| Wasm instantiateStreaming | [MDN WebAssembly.instantiateStreaming](https://developer.mozilla.org/en-US/docs/WebAssembly/Reference/JavaScript_interface/instantiateStreaming_static) | `application/wasm` MIME, CSP compile policy, streaming/fallback |
| Wasm memory | [MDN WebAssembly.Memory](https://developer.mozilla.org/en-US/docs/WebAssembly/Reference/JavaScript_interface/Memory/Memory) | wasm32 max address range 4GiB not usable-memory promise; memory64 optional/probe |
| Emscripten Pthreads | [Emscripten pthreads](https://emscripten.org/docs/porting/pthreads.html) | SharedArrayBuffer + COOP/COEP, separate build for thread vs nonthread; main thread blocking hazard |
| Emscripten browser build | [Emscripten docs](https://emscripten.org/docs/) | C++ to Wasm/JS glue, version/toolchain/ports/NOTICE gate |
| Cross-origin isolation | [MDN crossOriginIsolated](https://developer.mozilla.org/en-US/docs/Web/API/Window/crossOriginIsolated), [COEP](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Cross-Origin-Embedder-Policy), [COOP](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Cross-Origin-Opener-Policy) | headers effective on deployed document and resources; ads/embeds/popups may fail |
| Permissions policy | [MDN cross-origin-isolated directive](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Permissions-Policy/cross-origin-isolated) | browser may block SAB despite other headers |
| CSP | [MDN Content Security Policy](https://developer.mozilla.org/en-US/docs/Web/HTTP/CSP) | no generic unsafe-eval; script-src/wasm-unsafe-eval deployment capability review |
| Storage and quotas | [MDN Storage quotas/eviction](https://developer.mozilla.org/en-US/docs/Web/API/Storage_API/Storage_quotas_and_eviction_criteria) | caching/offline best effort, per-browser private/eviction differences |
| CacheStorage | [MDN CacheStorage](https://developer.mozilla.org/en-US/docs/Web/API/CacheStorage) | origin-scoped cached Request/Response, no guaranteed atomic cross-store upgrade |
| Service Worker | [MDN Service Worker API](https://developer.mozilla.org/en-US/docs/Web/API/Service_Worker_API) | controls origin scope and offline network behavior, requires trust/versioning |
| Fetch/Range | [MDN HTTP Range requests](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Range_requests), [Fetch](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API) | support 206 with Content-Range, safe 200 fallback; CORS/caching/416 |
| Browser timing | [W3C Performance APIs](https://www.w3.org/TR/hr-time-3/) | process/user-agent precision restrictions; no ungrounded GPU/display scanout assumption |

## Candidate evaluation matrix, exact-tag licensing unresolved
| Candidate | Potential license/redistribution | Benefit | Approval gate / alternative |
|---|---|---|---|
| Emscripten + Clang LLVM | Emscripten generally MIT/University-of-Illinois style portions, LLVM Apache-2.0 with LLVM exception; verify selected tags/components/ports/generated JS | C++20 engine interop with browser | pin revision, wasm32 ABI, JS glue CSP requirements, generated loader and dependency SBOM |
| wasi-sdk / Clang WASI | LLVM/WebAssembly libraries varied, verify exact release | portable pure WASI modules | WASI alone lacks DOM/WebGPU/Fetch/JS host and worker bridges |
| Browser WebAssembly32 | W3C standard API; generated binary derives engine/library licenses | portable constrained CPU runtime | browsers, memory policy/exception/SIMD features must be tested |
| WebAssembly memory64/GC/threads/SIMD | web standards, no bundled library by themselves | future performance/heap upgrades | feature detection, browser cost/availability, exact target packages |
| WebGPU/WGSL | W3C standards, native browser code not bundled | modern GPU capability negotiation | secure context, adapter/device, losses, WGSL binding limits, no universal compatibility |
| WebGL2 GLSL ES | web standard API; wrappers/toolchains may have separate license | broad graphics fallback | precision, extensions, shader variants, real 3D degradation tests |
| Dawn/wgpu native C++ | Chromium Dawn BSD-3-Clause family; wgpu Rust MIT/Apache-2.0 (verify exact repo/tag) | optional native RHI comparator | not equivalent to browser WebGPU, transitive license/integration complexity |
| SDL3 browser/Emscripten port | SDL3 zlib root, third-party dependencies by tag | reusable some host input/window glue | browser DOM gesture lifecycle and Worker execution still require PLAT host |
| Basis Universal/KTX2 | Basis Universal Apache-2.0/MIT-like parts, KTX-Software mixed components; inspect files | compressed target textures | formats vary by WebGPU/WebGL2/browser GPU; DATA-05 owns cook |
| Brotli, zstd, LZ4 | Brotli MIT, Zstd dual BSD/GPL, LZ4 BSD library/GPL CLI; verify exact transitive and wasm decoder | efficient chunks/HTTP delivery | codec speed/memory/decode bombs, no universally available streaming decompressor |
| Service Worker / CacheStorage / IndexedDB | browser APIs, no shipped JS library license; host code licensing still open | cached immutable bundles / offline | quota eviction, stale SW, malicious origin, cross-store atomicity impossible to assume |
| fetch HTTP/2/3 / CDN | browser HTTP APIs with provider terms TBD | progressive network | CORS/CORP, 200 vs 206, ETag, proxies, quotas, no assumed free hosting |
| Web Audio | Web standards; third-party player/codec licenses vary | optional interactive sound | autoplay user gesture, suspend/resume, device permission, AUD owns |
| WebXR, mobile browser, WebCodecs | standards with uneven availability/permissions | advanced experiences | conditional FUTURE, no automatic browser 1.0 guarantee |
| Browser tooling Playwright / WPT | Playwright Apache-2.0, WPT 3-Clause BSD/other test fixture rights by component | reproducible CI browser tests | browser distribution license, artifact/hardware profile, headless != physical device |
| Canvas fonts/text | HarfBuzz MIT-style, FreeType FTL/GPL and font file rights separately | Unicode/shaping | TWO/UI owns glyph output and authoring, no unlicensed font bundling |

## Explicit threat model and fail-closed requirements
| Threat | Future independent oracle |
|---|---|
| XSS/unsafe eval malicious project imports | strict CSP, sanitized URLs, no executing authored script, denied unauthorized engine/host effects |
| COOP/COEP silently breaking third-party assets | preflight CORP/CORS compatibility, explicit single-thread fallback if isolation absent |
| Forged cross-origin manifest/asset hash | trusted-source manifest and per-chunk digest/length/codec check, no false publisher identity |
| WASM/asset decompression bomb, integer overflow | maximum bytes/recursion/time/memory and worker cancellation, no script executing |
| Dangling WebGPU/WebGL resources after loss | generation invalidation, device recreate or restart-required |
| Browser storage eviction/partial SW update | atomic-generation intention, last-good candidate, multi-tab consistency/readback |
| Range mismatch 206/200/416/Content-Encoding | bounded fallback, Content-Range verification, ETag and retry journal |
| Offline delivery of stale vulnerable binary | trusted version policy and rollback/expiry, never silently force unsafe update |
| Cross-site token/credential leakage | no API secrets in bundle/log/source map, strict origin/referrer/privacy scope |
| Malicious Service Worker scope upgrade | versioned same-origin SW, restrict install/activation/update, origin-specific tests |
| Malicious DOM input/postMessage | typed origin/source/schema/nonce checks and event seq, no global keylogger |
| Unauthorized clipboard/file/fullscreen/pointer lock | explicit gesture, denial without fallback privilege, GAME-01 focus resets |
| Browser fingerprinting GPU/device IDs | coarse capability tiers, redacted device markers; no persistent raw serial telemetry |
| GPU/CPU/memory unbounded worker jobs | CPU/bytes/wasm heap/network/VRAM resource budgets and cancellation |
| CSP or MIME mismatch fail-open | typed failure, no unsafe-eval or arbitrary fetched JS |
| Sandbox bypass by AI/MCP authored content | AI permission scope and Web host cap tokens with audit receipt |
| Supply-chain unlicensed wasm JS libs | exact pinned tag, SPDX/NOTICE/SBOM, hash CI and vulnerability gates |

## Comparative scorecard proposal (not measured)
Compare, only after future fixture and owner budgets, **functional/browser conformance 30%**, security+license 25%, quality+fallback 20%, startup/bytes/memory/latency 15%, accessibility/maintainability 10%. No numeric candidate score awarded now. Per-browser support and actual GPU results **NOT MEASURED**.

[Architecture](../architecture/plat-03-browser-runtime.md) · [benchmark](plat-03-browser-benchmark-protocol.md) · [ADR](../adr/0071-plat-03-browser-runtime-capability-policy.md).
