# PLAT-03 — Proposed Browser Target Capability, Wasm, Render, Input and Delivery API v0.1

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NO ENGINE | research [#325](https://github.com/KayzenRoot/stormline/issues/325) | NLE-P00-WO-002-PLAT-03 | future implementation [#86](https://github.com/KayzenRoot/stormline/issues/86) OPEN/BLOCKED | BASE `dc7404722c347419197d001a7d61de3d676264b0`.** Order 68/80; **formal deps TWO-01 + GFX-01 + DATA-05 ONLY** (ADR-0022/0014/0013 PROPOSED), 67/80 documented before research, 13 pending, 80/80 future coding WOs BLOCKED, executor_ready=0, approved_adr=0, release classes all UNDECIDED, engine=false, NLE-D009 license OPEN.


**Types are semantic drafts only. No TypeScript/WIT/C++ ABI, generated Wasm, JS glue, service worker, shader or live browser test exists.**

## Owner contracts and interface control
| Owner | Existing semantic fields | PLAT adapter responsibility |
|---|---|---|
| TWO-01 **FORMAL** | Canvas2D scene/layer/sprite/text/clip order | browser framebuffer, logical/pixel scaling and capability warning only |
| GFX-01 **FORMAL** | GPU device capability/generation/PresentSurface | browser-safe adapter/context probe, canvas lease, WebGPU/WebGL2 status, context/device loss |
| DATA-05 **FORMAL** | TargetProfile, immutable BundleManifest, chunk/patch receipt | fetch/cache generation, byte integrity and quota status; cannot rewrite cooked bundle |
| CORE-01/04, GAME-01, AUD, AI, PLAT-05 transitive | lifecycle/tick/input/audio/authorized commands/export | no duplicate authority or new catalog dependency |

## Candidate V1 semantic data types
| Type | Proposed fields | Strict invariants |
|---|---|---|
| BrowserTargetProfileV1 | source/build SHA, wasm32/memory64 family, supported feature tier, allowed browser/OS profile, release_state, role Editor/Game | no inference from user agent; UNKNOWN != supported |
| BrowserOriginPolicyV1 | origin opaque, secure_context, CSP/COOP/COEP/CORP/CORS/Permissions-Policy statuses, trusted manifest origin, cross_origin_isolated status | effective deployed response headers + policy, not assumptions |
| BrowserCapabilityProbeV1 | browser engine/version redacted, GPU API enum WEBGPU/WEBGL2/NONE, wasm SIMD/threads/memory64 detection, Web Workers/OffscreenCanvas availability, privacy class | actual feature probes, not browser name |
| BrowserWasmVariantV1 | artifact revision/SHA, wasm32/w64, SIMD/threads flags, initial/max pages, imports/exports schema, CSP requirement, fallback variant | thread module never runs when not isolated; bounded memory |
| BrowserBootStateV1 | state INIT/FETCH/VERIFY/COMPILE/DEVICE/LOAD/INTERACTIVE/FAILED, load epoch, abort id, error, receipt time | impossible to mark INTERACTIVE before own 2D/3D fixture checks |
| BrowserRendererOfferV1 | opaque canvas token, backing extent, display scale, requested quality tier, WebGPU adapter features/limits or WebGL2 extensions, context generation | no public GPU object, every feature explicit |
| BrowserDeviceEpochV1 | instance/context generation, device lost reason, recreate policy, resource-rehydrate owner receipt | stale texture/buffer handle rejected |
| BrowserCanvasMetricsV1 | CSS px, DPR, backing px, scaling tier, color-space hint, viewport/focus/orientation state, revision | GPU max texture dimension and typed 0x0 handling |
| BrowserFrameLifecycleV1 | rAF frame index, monotonic timestamp precision, visibility/freeze/BFCache epoch, fixed-tick debt, ack sequence | background rAF throttling cannot change game time authority |
| BrowserInputOfferV1 | focused gesture/pointer/keyboard/gamepad permission states, layout/IME routing, source sequence/DeviceEpoch, game action owner | no synthetic activation, no password logging |
| BrowserAudioCapabilityV1 | suspended/running/unavailable, user gesture id, sample format/latency reported, endpoint permission | AUD owns actual audio, no autoplay guarantee |
| BrowserBundleManifestRefV1 | DATA-05 manifest id/hash/source trust, revision, profile, codec, chunk DAG, total quotas | digest != signer; untrusted manifest rejected |
| BrowserFetchChunkV1 | URL origin allowlist, requested range, 206/200 code, Content-Range/ETag, encoded+decoded limits, received bytes/hash, retry count | 206 offset checks, 200 bounded fallback, no wrong-generation bytes |
| BrowserStorageGenerationV1 | immutable generation id, staged vs active, cache origin/scope, quota estimate, evicted flag, last-good manifest, activation receipt | no atomic CacheStorage+IndexedDB assertion |
| BrowserPermissionRequestV1 | fullscreen/pointerlock/clipboard/file/audio request id, user gesture evidence, purpose, expiration and status | denial without privilege escalation |
| BrowserPlatformErrorV1 | error type UNSUPPORTED/DENIED/CSP_BLOCKED/CORS_BLOCKED/OUT_OF_BUDGET/CORRUPT/DEVICE_LOST/STALE_GENERATION/RESTART_REQUIRED, retryability, owner | sanitized, bounded, no secret origin tokens |
| BrowserSmokeReceiptV1 | browser engine+build, OS/hardware provenance, secure origin headers, wasm/gfx tier, 2D+3D fixture hashes, input/audio if declared, launch/exit, errors | real browser vs headless/simulator clearly marked |
| BrowserBenchmarkReceiptV1 | source/build artifacts, network/cache profile, raw launch/frames/input samples, CPU/GPU/display clock precision, JS/wasm heap and quota, p50/p95/p99+confidence | no measured FPS without actual run |

## Proposed semantic procedures (NOT executable methods)
| Procedure | Caller/owner | Failure/result |
|---|---|---|
| inspect_browser_origin(policy) | PLAT host | BrowserOriginPolicyV1 / INSECURE_CONTEXT / POLICY_DENIED |
| probe_browser_capabilities(scope) | PLAT host -> GFX-01 | BrowserCapabilityProbeV1 with explicit UNKNOWN |
| select_wasm_variant(candidates, origin_caps) | loader | BrowserWasmVariantV1 / THREADS_DENIED / MEMORY_UNSUPPORTED |
| bootstrap_game(verified_manifest, feature_tier) | PLAT host | BrowserBootStateV1 / MANIFEST_UNTRUSTED |
| request_renderer(canvas, required_features) | GFX-01 | BrowserRendererOfferV1 / WEBGPU_UNAVAILABLE / WEBGL2_UNAVAILABLE |
| observe_device_lost(renderer_token) | GFX-01/PLAT | BrowserDeviceEpochV1 / STALE_DEVICE |
| publish_canvas_metrics(canvas_token) | PLAT -> TWO-01/GFX-01 | BrowserCanvasMetricsV1 / ZERO_EXTENT |
| publish_lifecycle(event) | CORE-01/04 transitive | BrowserFrameLifecycleV1 / STALE_EPOCH |
| normalize_browser_input(focused_event) | PLAT -> GAME-01 | BrowserInputOfferV1 / GESTURE_DENIED |
| request_audio_start(user_activation) | PLAT -> AUD | BrowserAudioCapabilityV1 / NOT_ALLOWED |
| fetch_immutable_chunk(bundle_ref, range, abort) | PLAT -> DATA-05 | BrowserFetchChunkV1 / RANGE_INCONSISTENT / HASH_MISMATCH |
| stage_offline_generation(verified_chunks) | PLAT adapter + DATA-05 | BrowserStorageGenerationV1 / QUOTA_EXCEEDED |
| activate_generation_if_complete(stage) | DATA-05 trust + PLAT cache | last-good activation receipt / INCOMPLETE |
| request_browser_permission(gesture, purpose) | focused user scope | allowed limited token / DENIED |
| emit_browser_smoke_receipt(evidence) | QA + CORE-06 | BrowserSmokeReceiptV1 / HARDWARE_UNVERIFIED |

## Semantic invariants and negative edge cases
- `navigator.gpu` property presence does NOT mean device request succeeds; WebGPU adapter/device limits and WebGL2 context creation must be actually observed. W0 WebGL2 cannot pretend compute or native RT. Optional unsupported feature explicitly degrades with owner-signed provenance.
- WebGPU device lost and WebGL context lost invalidate all previous RHI resources; no race between a late async device negotiation response and a new SurfaceEpoch. All stale async callbacks contain load epoch and abort id.
- A pthread variant cannot load without effective `crossOriginIsolated` and WASM thread feature; serve unthreaded variant separately. No worker block on DOM thread or uncontrolled memory growth.
- Data integrity: trust-controlled manifest first, then streamed chunk length/hash + codec + budget; Range 200 fallback is allowed only when total body within budget and response validated. 206 mismatched Content-Range/ETag rejected, 416 handled without corrupting last-good.
- Offline best effort: storage quota and SW cache may evict. Split CacheStorage+IndexedDB is **NOT** a single ACID transaction. Staged version becomes active only after all target chunks validated and version-lock published; multi-tab need explicit ack/retry/last-good, no overwriting authored source.
- Input key/code/IME/text separated, browser focus and user gesture route into GAME-01; on blur/hidden/permission denied, held keys/pointer lock released. No synthetic gamepad or keyboard injection from AI.
- UI/API externally receives semantic redacted status, never GPUDevice raw references, JS Function objects, private origins/tokens, filesystem handles, source maps exposing secrets, raw device IDs or unrestricted DOM.
- Permission denied never triggers `window.open`, `eval`, shell, service worker patch, iframe bypass or auto upload. Browser deployment security headers must be checked on the *real origin*, not only localhost.
- Browser profiles and payload schema evolve by major version with incompatible major rejection and explicitly preserved benign optional fields.
- Source and binary licenses remain unresolved: NLE-D009 OPEN, ADR PROPOSED and #86 code blocked.

[Architecture](../architecture/plat-03-browser-runtime.md) · [ADR-0071](../adr/0071-plat-03-browser-runtime-capability-policy.md) · [128 future tests](../testing/plat-03-acceptance-matrix.md).
