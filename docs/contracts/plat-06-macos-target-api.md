# PLAT-06 — macOS Host/Surface/Input/Distribution Semantic API v0.1

**2026-11-15 | P00 RESEARCH ONLY | WO NLE-P00-WO-002-PLAT-06 | research #329 | code #87 OPEN/BLOCKED | base 109287f928b4436b31188c1dd8cf4f7a454ad989.** Formal deps CORE-01 + GFX-01 + GAME-01 only. ADR-0003/0014/0042 PROPOSED; all 80 code WOs BLOCKED, engine_implemented=false, no SDK/build or signed Mac binary.


**Proposed typed semantics ONLY; no real C++/Objective-C++/Swift header, AppKit object, actual MTLDevice, signature or compiled ABI.**

## Three formal owner contracts
| Owner | Existing proposed contract | PLAT-06 interface |
|---|---|---|
| **CORE-01 FORMAL** | [Platform lifecycle](../architecture/core-01-platform-lifecycle.md), ADR-0003 | app/process/window generation, SDL3 input/event pump, one NSApplication delegate and headless path |
| **GFX-01 FORMAL** | [RHI](gfx-01-rhi-api.md), ADR-0014 | Metal CAMetalLayer view/surface and display/backing proposal; GFX owns MTLDevice, queues, resource handles and loss |
| **GAME-01 FORMAL** | [Action API](game-01-input-actions-api.md), ADR-0042 | only normalized CORE events to semantic ActionMap/seat/focus; no raw NSEvent/GCController escaped |

Other integration owners PLAT-05/BIZ-03 packages/notarization, EDIT/ DATA source files and AUD audio are **transitive**, not new catalog dependencies.

## V1 candidate semantic data types
| Type | Fields | Invariant / failure |
|---|---|---|
| MacTargetProfileV1 | platform macOS; arch arm64/x86_64/universal2; min OS; SDK; release channel; owner Intel decision | actual Apple Silicon required; Intel conditional OS<=26 eligible, no macOS27 physical Intel |
| MacHostEnvironmentV1 | actual hw architecture, macOS build, process native vs Rosetta, GPU/Metal availability, privacy tier | native Intel hardware separate from translated Intel executable |
| MacBuildSliceReceiptV1 | root source/artifact hashes, CPU slice list, nested framework/helper Mach-O/ABI, LC_BUILD_VERSION, compiler | universal requires compatible per-slice C++ ABI and runtime API |
| MacProcessLifecycleV1 | process epoch, INIT/RUNNING/TERMINATING/EXITED, main thread, SDL owner, delegate forwarding, headless bool | only CORE has OS event pump, no quit after veto |
| MacWindowLeaseV1 | opaque WindowId/WindowEpoch, NSView token private, focus/occlusion/fullscreen Space, native display token | no raw NSWindow public handles or stale callbacks |
| MacDisplayMetricsV1 | view points, backing pixel geometry, display refresh, HDR/P3/sRGB capabilities, DPR/scaled mode, revision | use actual coordinate conversion, no assumed native pixels or 120Hz |
| MacMetalSurfaceOfferV1 | opaque CAMetalLayer/SDLMetalView token, WindowEpoch, drawable format/size, proposed GFX device association | SDL Metal view alone does NOT attach MTLDevice |
| MacMetalCapabilityV1 | GFX-01 MTLDevice family, OS/Metal/MSL supported features, memory advisory/actual, device epoch | actual feature probe, no Intel/Metal4 blanket assumption |
| MacDrawableEpochV1 | WindowEpoch, Metal surface generation, lost/retry/restart flag, display event id | stale drawable/resource never reused |
| MacNativeInputBridgeV1 | CORE event source+seq, GAME window/device epoch, keys physical/logical/IME, mouse/trackpad/gamepad, focused state | no double SDL+GameController input and no raw private keys |
| MacTCCPermissionV1 | ACCESSIBILITY/INPUT_MONITOR/FILES/MIC/CAMERA if needed, consent scope, DENIED/GRANTED, expiry | no silent consent bypass or private user data leak |
| MacFileGrantV1 | scoped bookmark id, project owner, user-selected path redacted, open/close count, revocation | no entire home directory access; use NSOpenPanel |
| MacDistributionPolicyV1 | INTERNAL_ONLY/DEVELOPER_ID/APP_STORE, entitlements allowlist, hardened flag, signer/notary required | PLAT-05 release channel approval, Apple Program cost not assumed |
| MacNotaryReceiptV1 | archive hash, valid Developer ID alias fingerprint, all nested signed slices, secure timestamp, ticket/stapling/Gatekeeper | cannot claim NOTARIZED from ad-hoc debug or docs CI |
| MacPlatformErrorV1 | ARCH_MISMATCH, SDK_UNAVAILABLE, OS_UNSUPPORTED, MAIN_THREAD, APPKIT_DELEGATE, NO_METAL, DRAWABLE_LOST, INPUT_DENIED, NOTARY_REQUIRED, RESTART_REQUIRED | typed result with owner, retryability and sanitized diagnostics |
| MacHardwareSmokeReceiptV1 | actual CPU hw+OS+GPU/driver+display + Editor build/open/close + export 2D/2.5D/3D cases, source hashes | headless/virtual results not physical GPU proof |
| MacBenchmarkReceiptV1 | source/build/hardware/GPU+power+thermals, raw frame/CPU/GPU sampling and uncertainty, p50/p95/p99 | no invented values and no GPU clock cross-domain subtraction |

## Proposed calls, non-executable
| Procedure | Owner | Outcome |
|---|---|---|
| probe_mac_host(policy) | CORE-01/PLAT | MacHostEnvironmentV1 / ARCH_MISMATCH |
| start_mac_application(headless, delegate) | CORE-01 | MacProcessLifecycleV1 / MAIN_THREAD |
| create_mac_window(window_scope) | CORE-01 | MacWindowLeaseV1 / WINDOW_UNAVAILABLE |
| request_mac_window_close(epoch, unsaved_state) | CORE-01/EDIT | CLOSED or VETOED preserving data |
| offer_mac_metal_layer(window) | PLAT bridge -> GFX-01 | MacMetalSurfaceOfferV1; only main thread |
| query_native_metal_features(gfx_token) | GFX-01 | MacMetalCapabilityV1 / UNSUPPORTED |
| invalidate_metal_device_surface(event) | GFX-01 | MacDrawableEpochV1 / RESTART_REQUIRED |
| publish_backing_rect_metrics(rect) | PLAT bridge | MacDisplayMetricsV1 / ZERO_EXTENT |
| normalize_mac_input(core_event) | CORE-01 -> GAME-01 | MacNativeInputBridgeV1 / FOCUS_LOST |
| request_scoped_project_file(user_dialog) | PLAT -> EDIT/DATA | MacFileGrantV1 / TCC_DENIED |
| validate_mac_distribution(archive) | PLAT-05/BIZ-03 | MacDistributionPolicyV1 and verified MacNotaryReceiptV1, else SIGNING_REQUIRED |
| produce_actual_mac_smoke_receipt(real_device) | QA/CORE-06 | MacHardwareSmokeReceiptV1 / HARDWARE_NOT_VERIFIED |

## Nonnegotiable invariants
- Introspect architecture/OS/translation state, never infer from universal2 filename or marketing OS; physical Intel on selected supported macOS <=26 only if owner approves, and x86_64 under Rosetta on arm64 is separate.
- CORE-01 event loop single authority; AppKit/NSWindow/SDL Metal view main thread, no worker UI calls, and source project may veto window close. Event WindowEpoch and GFX SurfaceEpoch serialized; stale notifications ignored.
- PLAT-06 **cannot** own MTLDevice, renderer or GameInput resolver. GFX-01 device generation and GAME-01 semantic actions are authoritative. Pixel/backing metrics and drawable life cycle exact, no 2x universal Retina claim.
- Editor source/asset paths need user granted security-scoped tokens and consent; no TCC API permission shortcuts, Full Disk Access or shell/MCP escalations.
- A signed/ad-hoc build, notarized Developer ID build and App Store Sandbox distribution are independent states; signing key never in public diagnostics; actual approved notary ticket and Gatekeeper readback required.
- All schema majors must be version-validated; denial never silently degrades to privileged behavior. Engine source license still OPEN; no code release.

[Architecture](../architecture/plat-06-macos-desktop-target.md) · [128 future tests](../testing/plat-06-acceptance-matrix.md) · [ADR-0072](../adr/0072-plat-06-macos-apple-silicon-compatibility-policy.md).
