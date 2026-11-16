# ADR-0071 — Capability-Gated Browser Execution, WebGPU/WebGL2 and Verified Streaming

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NO ENGINE | research [#325](https://github.com/KayzenRoot/stormline/issues/325) | NLE-P00-WO-002-PLAT-03 | future implementation [#86](https://github.com/KayzenRoot/stormline/issues/86) OPEN/BLOCKED | BASE `dc7404722c347419197d001a7d61de3d676264b0`.** Order 68/80; **formal deps TWO-01 + GFX-01 + DATA-05 ONLY** (ADR-0022/0014/0013 PROPOSED), 67/80 documented before research, 13 pending, 80/80 future coding WOs BLOCKED, executor_ready=0, approved_adr=0, release classes all UNDECIDED, engine=false, NLE-D009 license OPEN.


**STATUS: PROPOSED / NOT OWNER-RATIFIED / NOT IMPLEMENTED / NO CODING AUTHORIZATION.**

## Problem
Browser platform security and runtime limits differ from desktop: WebGPU secure-context, browser/driver feature gaps, WebGL2 precision and missing compute, Wasm memory and thread isolation, user-activation gates, tab suspension, HTTP delivery variability and origin storage eviction. Treating browser as identical to native or treating browser marketing version as a supported GPU tier would mislead releases and risk data loss.

## Proposed decision, subject to owner ratification
1. Formal dependencies **EXACT TWO-01 + GFX-01 + DATA-05** only, with ADR-0022/0014/0013 all PROPOSED. Do not change catalog DAG. Browser host bridges are PLAT-03-specific; CORE-01/time, GAME-01, audio, GFX-02/07, AI, QA, PLAT-05 and BIZ-03 are transitive/integration owners, not new formal dependencies.
2. Prefer **Wasm32 C++20 via pinned Emscripten/LLVM** and a minimal audited JS/TS browser host *as candidate*. No unsourced claim that compiled C++ or a WASI binary runs in all browsers; WASI is not a drop-in DOM/WebGPU host. Exact revisions, generated-code licenses and ABI must be inspected and reproduced before implementation.
3. **Conservative W0 browser tier:** single-thread wasm32 and functionally reduced TWO-01 2D plus representative 3D on actual WebGL2 when supported, with explicit `UNSUPPORTED` when unavailable. **W1** conditional WebGPU after real `navigator.gpu`, secure-context, adapter/device/limit probes. Advanced W2 optional, no implicit compute or native-quality parity on WebGL2. No WebGL1 substituting for 3D acceptance invisibly.
4. Threaded Wasm/SharedArrayBuffer is a **separate build artifact**, allowed only when crossOriginIsolated and CSP/COOP/COEP/Permissions-Policy/third-party resource constraints pass on the actual host. Pre-approved single-thread fallback remains. A browser Worker or OffscreenCanvas is not assumed available, and no blocking waits on DOM thread.
5. GFX-01 owns WebGPU/WebGL2 RHI device/context resource generations, shaders through GFX-02, fallback tier policy, canvas presentation. Device/context loss must invalidate handles; retry bounded or restart-required. Stable TWO-01 painter order/alpha/sRGB correctness is invariant even in reduced WebGL2 tier. No native WebGPU parity claim.
6. DATA-05 owns cooked immutable chunk manifests, target profile, integrity and recovery. PLAT-03 owns bounded HTTPS fetch, `application/wasm` streaming, optional Range 206/200 fallback, CORS errors, quota/eviction and origin-scoped cache staging. Content digests cannot substitute for publisher authenticity. Never auto-commit a partial Service Worker/IndexedDB/CacheStorage generation.
7. Permission/interaction: fullscreen, pointer lock, clipboard, WebAudio start and file saves require actual user activation or explicitly allowed browser scopes. On tab hidden/BFCache/focus loss, CORE-04 tick stops/catches up within budget; GAME-01 releases states; no secret logging or injected native input.
8. Security: HTTPS, restrictive CSP (avoid blanket unsafe-eval; wasm-unsafe-eval conditionally when valid), narrow COOP/COEP/cross-origin isolation profile, CORP/CORS/Permissions-Policy, provenance-verified bundles, sanitized URLs, untrusted JS/remote code blocked, storage sandbox and MCP capability scopes. Never expose private tokens, native paths or unchecked assets to third-party service workers.
9. Compatibility and measurements: explicitly freeze owner-selected browser versions, GPU/driver/OS, mobile only if later approved, W0/W1 required acceptance, UI/2D/3D fixtures and latency/memory/bytes budgets. Real browser tests, not only virtual headless CI or screenshots, required. 128 future tests and reproducible benchmark receipt defined, none executed.
10. No final tech/license/hosting decision: Emscripten/WebGPU/WebGL2/Flat buffer codecs/service worker/CDN are candidates; engine NLE-D009 source license OPEN. All 80 implementation packets remain BLOCKED, 0 executor_ready and 0 approved_adr; ADR PROPOSED is not permission to code.

## Alternatives considered
| Alternative | Potential advantage | Why rejected as an automatic default |
|---|---|---|
| WebGPU-only web export | high-level modern GPU API | not available on all named browsers/hardware; violates fallback and 2D/3D compatibility if no device |
| WebGL1 or Canvas2D-only export | very broad/simple path | cannot claim representative modern 3D parity or 2.5D feature tiers |
| WebGL2 conditional W0, WebGPU W1 | real degraded path plus advanced feature potential | requires dual backend conformance and hardware matrix, not a no-test guarantee |
| Assume WebGPU == native Vulkan | one shader/resource model | API, browser validation, timing, features and performance differ |
| Single threaded only forever | simple deployment/no COOP | may miss justified future CPU throughput; benchmark later |
| Pthreads single binary with optional runtime fallback | packaging convenience | Emscripten pthread module cannot automatically become non-threaded under missing SAB |
| Require COOP/COEP for all audiences | enables SAB | breaks cross-origin assets/embeds/popup auth unless deliberately planned and tested |
| Run all rendering in workers | less main-thread work | OffscreenCanvas/worker WebGPU availability and permissions vary; DOM APIs must remain main thread |
| Memory64 mandatory from launch | larger address space | browser feature/runtime/heap limits, tooling size and device constraints; choose after evidence |
| Unbounded streaming/preload/cache | simpler loading | quota exhaustion, stalled start, decode bombs and degraded low-memory usability |
| Service Worker update activates immediately | quick deployment | mixed asset generations, offline corruption and multi-tab races |
| Treat hashes as publisher identity | cheap check | integrity != authenticated signing/freshness/replay policy |
| Auto-public GitHub Pages/CDN | fast smoke | owner no-public-MVP rule and actual infrastructure/privacy/security gate |
| Browser unrestricted filesystem/MCP | powerful editing | violates origin sandbox, user consent and authorized Command Kernel |

## Consequences and proof obligations
Requires at least two separate browser renderer tiers and optionally two Wasm thread profiles, bounded async asset loader and secure origin/header compatibility; increases test matrix but preserves OS/backend truth. Future code must have approved release class/Scope/DoD, frozen browser+GPU fixtures, transitive owner implementation and signed/verified source provenance/rights, security negative tests, independent 128-case conformance with actual 2D+3D browser smoke and stats. Until then **PROPOSED / no implementation authorization**.

[Architecture](../architecture/plat-03-browser-runtime.md) · [contract](../contracts/plat-03-browser-target-api.md) · [license/security matrix](../research/plat-03-browser-technology-license-security-matrix.md).
