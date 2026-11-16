# PLAT-03 — Browser Compatibility, 2D/3D WebGPU/WebGL2 and Streaming Benchmark Protocol

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NO ENGINE | research [#325](https://github.com/KayzenRoot/stormline/issues/325) | NLE-P00-WO-002-PLAT-03 | future implementation [#86](https://github.com/KayzenRoot/stormline/issues/86) OPEN/BLOCKED | BASE `dc7404722c347419197d001a7d61de3d676264b0`.** Order 68/80; **formal deps TWO-01 + GFX-01 + DATA-05 ONLY** (ADR-0022/0014/0013 PROPOSED), 67/80 documented before research, 13 pending, 80/80 future coding WOs BLOCKED, executor_ready=0, approved_adr=0, release classes all UNDECIDED, engine=false, NLE-D009 license OPEN.


**Future protocol only / NOT MEASURED.** No browser runtime/compiled wasm/deployed HTTPS server/screen capture/benchmark exists today. No invented FPS, memory, bandwidth or compatible browser version.

## Objective
Proof on **real named browser releases and physical hardware** that rights-cleared TWO-01 2D and a representative reduced 3D scene can render, respond to keyboard/pointer/gamepad if supported, fetch verified DATA-05 bundles and recover from common browser errors; WebGPU advanced tier only with evidence. A hosted headless Playwright pass or WebGL software renderer is supplementary; screenshots alone cannot certify timing, interaction, resources or API capability.

## Exact environment lock
| Parameter | Required future receipt |
|---|---|
| Source/build | base/head SHA, dependency revisions TWO-01/GFX-01/DATA-05, C++/LLVM/Emscripten compiler revision, JS glue and Wasm binary SHA-256, shader version, source maps/security |
| Browser | Chrome/Firefox/Safari real named version+channel/OS, physical GPU family/driver, ANGLE/backend or real WebGPU adapter if observable, headless/virtual flag, display resolution/DPR/refresh |
| Origin | actual HTTPS origin and effective response headers, `application/wasm`, COOP/COEP/CORP/CORS, Permissions-Policy/CSP, service worker revision, cookie/login/embed conditions |
| CPU/heap | wasm memory initial/max pages and growth/OM failures, JS heap if observable, worker count/crossOriginIsolated, main-thread long tasks, GC attribution where available |
| Graphics | WebGPU/WebGL2 capability/tier/limits/format/extensions, canvas scale/alpha/color, device/context generations, 2D sprite order and 3D scene hashes |
| Network | 2G/3G/4G/fast/fixed synthetic profiles as applicable, TCP/HTTP versions, CDN vs origin, cache primed/cold, response 206/200/416, bytes requested/received/decompressed |
| Assets | DATA-05 manifest ID/trusted origin/hash, codec, compressed/uncompressed limits, partial load/LOD, cache generation and last-good receipts |
| Interaction/audio | gesture/focus/visibility/BFCache, pointer lock/fullscreen permissions, IME/user accessibility, WebAudio resume authorization |
| Evidence | actual real browser vs hosted CI; raw samples, clock precision, confidence intervals, feature-denied cases, logs redacted, SBOM/NOTICE/copyright/source rights |

## Candidate future browser matrix (NOT owner-ratified)
- BROW-HW-A: current Chromium stable on physical Windows/Linux workstation, real GPU, secure origin, WebGPU where actually available; W0 WebGL2 separately.
- BROW-HW-B: named Firefox stable on physical desktop and real GPU; record WebGPU experimental/disabled status without claiming universal support, WebGL2 W0 if available.
- BROW-HW-C: named Safari stable on Apple Silicon macOS, verify WebGPU/WebGL2 and privacy/storage behavior on real device; no Safari-on-Windows fiction.
- BROW-HW-D: low-memory laptop/integrated graphics browser with simulated degraded network and actual RAM/texture limitations.
- BROW-CI: hosted browsers/headless/Xvfb/software GL, for deterministic smoke, CSP/HTTP/codec/offline failure emulation, **not** physical GPU benchmark.
- BROW-MOBILE: future separate owner approval with PLAT-04; browser support/wake/autoplay/power and install mode not promised now.

## Future measurement suite
| ID | Fixture and variable | Report, independent oracle |
|---|---|---|
| BROW-B01 | cold browser page start, clean cache | navigation+HTML+Wasm bytes, compile, first interactive and 2D first frame p50/p95 |
| BROW-B02 | warm stable cache, normal network | cache hit ratio/eviction, compile reuse/no false asset generation |
| BROW-B03 | reduced HTTP bandwidth/RTT/loss | progressive startup, peak in-flight requests and main-thread stall |
| BROW-B04 | header/CSP/secure origin isolation variants | `crossOriginIsolated`, user-facing failure and separate pthread artifact selection |
| BROW-B05 | WebGPU W1 and W0 WebGL2 on same licensed scene | visual parity under declared reduced tier, CPU/GPU frame p50/p95/p99 |
| BROW-B06 | 2D text/spites/alpha/clip and high DPR | independent pixel/glyph/interaction oracle, GPU and memory if observable |
| BROW-B07 | 3D constrained geometry material/lighting | actual semantic 3D scene and allowed degradation, no missing geometry |
| BROW-B08 | WebGPU device/context loss and rehydrate | generation, new resources, recovery/restart and leak count |
| BROW-B09 | hidden tab/background throttling/BFCache | time debt, CPU/energy, input action reset, safe resume |
| BROW-B10 | audio start/pointerlock/fullscreen consent | user gesture receipt, blocked/allowed behavior and accessible alternative |
| BROW-B11 | Range 206, ignored 200 and error 416 | header byte ranges and digest, retries, bandwidth overhead |
| BROW-B12 | malformed codec/manifest, partial release | no source/last-good mutation, bounded decompression |
| BROW-B13 | offline/serviceworker/storage quota | migration activation, eviction/recovery and multi-tab consistency |
| BROW-B14 | compressed Wasm/JS/content size and memory | download vs decoded, wasm+JS heap, copies, app memory estimate limits |
| BROW-B15 | security CSP/XSS/postMessage/worker denial | no untrusted JS/unauthorized capability/effects, no secrets |
| BROW-B16 | repeated 1000 restarts/resize/worker recreate | leak/stale-generation/last-good retention, full trace and audit |

## Sampling / data integrity
- Cold/warm conditions and browser cache/service worker generations separated and documented. At least five independent runs per condition, plus **enough per-frame/input observations** to estimate tails; five run-level observations do not justify p99.
- Time origin, main-thread PerformanceEntry, GPU query (only if feature supported), display scanout and input event clocks have separate domains. Privacy timing precision reductions are measured. Never subtract non-calibrated clocks or report fake physical GPU VRAM.
- Include experimental controls: same wasm/assets/shader/quality tier, browser flags, GPU power and thermal state, hardware; randomize backend A/B order and quantify confidence/uncertainty. Only compare WebGPU vs WebGL2 where same observable output contract applies.
- HTML/JS/Wasm compressed bytes, transfer size, decoded chunk bytes, first byte, first interactive and renderable frame separated. Trace cancellation, invalid samples, GC/long tasks and network waterfalls when permitted, never collect sensitive user data.
- Use synthetic safe uploads, consent actions, offline tests, no actual project/customer files or credentials; no public deployment without 1.0 readiness.

## Conceptual receipt
`BrowserBenchmarkReceiptV1`: source SHA, build toolchain+Wasm/JS digests, browser versions/OS/GPU+driver, real/headless classification, effective HTTPS/CSP/COOP/COEP/CORP/CORS/Permissions headers, Wasm variant/features/heap, GPU tier/devicelost events, licensed scene+assets manifest digests, fetch 200/206/416/ETag bytes, cache+SW generation, user activation/permissions, network/CPU/GPU/display clock domains+uncertainty, ordered raw launch/frame/input samples, memory/heap estimates, p50/p95/p99 bootstrap, long tasks, accessibility/quality results, independent security audit, NOT_SUPPORTED status, owner verdict.

[128 FUTURE tests](../testing/plat-03-acceptance-matrix.md) · [technology and licenses](plat-03-browser-technology-license-security-matrix.md) · [architecture](../architecture/plat-03-browser-runtime.md).
