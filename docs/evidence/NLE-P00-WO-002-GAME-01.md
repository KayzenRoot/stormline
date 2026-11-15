# Evidence Bundle — NLE-P00-WO-002-GAME-01 Input & Control Mapping Research

**STATUS: RESEARCH PR #209 OPEN; initial Docs Validation PASS on pre-evidence HEAD `b0dc2193e794210ccc1c870808439b1fb17aaf1f`; final evidence update requires its own exact-head CI; audit/merge/checkpoint PENDING. DOCUMENTATION ONLY / NO GAME INPUT ENGINE.**  
**2026-11-15 | Research [#208](https://github.com/KayzenRoot/stormline/issues/208) | Future coding [#56](https://github.com/KayzenRoot/stormline/issues/56) OPEN/BLOCKED | BASE main `0a3aa77229f5663e55fdf9b8b99a786c9edb1cc9`.**

## 1. Canonical source and preflight
AUD-04 issue #204 closed after research PR #205, checkpoint PR #206 and readback closeout #207 all merged. Current preflight main base `0a3aa77229f5663e55fdf9b8b99a786c9edb1cc9`; checkpoint 38/80 research documented, 42 pending, 0 runtime. Future code #56 OPEN/BLOCKED. All 80 code packets remain BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null. Canonical hierarchy: checkpoint > Ledger and approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS > catalog/registry > CORE-01/04 and DATA-04. **Exact Git blob fingerprints** in [Work Order](../work-orders/NLE-P00-WO-002-GAME-01.md). CORE-01 research proposes SDL3 bridge; no platform/runtime engine is implemented.

## 2. Eight planned artifacts (all documentary)
1. [Architecture](../architecture/game-01-input-control-mapping.md): CORE-01 event boundary, Game-owned device/seat/context/action map, keyboard+IME, mouse/touch, gamepad/hotplug, accessible remap, tick/replay, Web fallback and privacy.
2. [ADR-0042 PROPOSED](../adr/0042-game-01-engine-owned-input-actions.md): engine-owned semantic actions and deterministic event-to-tick/focus policy; no middleware adopted.
3. [Official technology/license/standards matrix](../research/game-01-input-technology-license-matrix.md): SDL3 zlib, SDL_GameControllerDB zlib candidate/data rights, GLFW zlib comparator, HIDAPI multi-license, Windows GameInput/Apple Controller SDK terms, Web Gamepad 2026 WD, Pointer Events 2026 Recommendation, Pointer Lock, WCAG 2.2.
4. [Semantic contracts](../contracts/game-01-input-actions-api.md): InputDevice/Seat/ActionMap/Binding/Context/Focus/ActionFrame/Replay/Accessibility/Migration/Error v1.
5. [128 future cases](../testing/game-01-acceptance-matrix.md), **FUTURE / NOT EXECUTED**.
6. [Benchmark protocol](../research/game-01-input-benchmark-protocol.md): input-to-action p50/p95/p99, hardware provenance/clock uncertainty, event overflow/focus/hotplug, remap/memory, cross-platform and accessibility.
7. [Research Work Order](../work-orders/NLE-P00-WO-002-GAME-01.md).
8. This Evidence Bundle.

## 3. Official references consulted, research only
- [SDL3 zlib LICENSE](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt), [PollEvent main-thread policy](https://wiki.libsdl.org/SDL3/SDL_PollEvent), [StartTextInput/IME](https://wiki.libsdl.org/SDL3/SDL_StartTextInput), [AddGamepadMapping](https://wiki.libsdl.org/SDL3/SDL_AddGamepadMapping).
- [SDL_GameControllerDB and zlib license](https://github.com/mdqinc/SDL_GameControllerDB/blob/master/LICENSE); [GLFW zlib/license](https://www.glfw.org/license); [HIDAPI multi-license](https://github.com/libusb/hidapi/blob/master/LICENSE.txt).
- [Microsoft GameInput](https://learn.microsoft.com/en-us/gaming/gdk/docs/reference/input/gameinput/functions/gameinputcreate), [Apple Game Controller](https://developer.apple.com/documentation/gamecontroller/).
- [W3C Gamepad WD 2026-11-14](https://www.w3.org/TR/2026/WD-gamepad-20261114/), [W3C Pointer Events 3 REC 2026-06-30](https://www.w3.org/TR/2026/REC-pointerevents3-20260630/), [MDN Pointer Lock](https://developer.mozilla.org/en-US/docs/Web/API/Pointer_Lock_API), [Gamepad Permissions-Policy](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Permissions-Policy/gamepad), [WCAG 2.2](https://www.w3.org/TR/WCAG22/).
No code/vendor license has been incorporated, accepted for shipment or tested.

## 4. Verification ledger (actual observed only)
| Gate | Status |
|---|---|
| Research #208 and branch from exact main | OBSERVED |
| Exactly 8 scoped Markdown files and PR diff | PR #209 Draft inspected, exactly 8 added Markdown files, no runtime/source/SDK/CI changes |
| Initial Docs Validation on previous HEAD | [Run #43699839456](https://github.com/KayzenRoot/stormline/actions/runs/43699839456) SUCCESS on `b0dc2193e794210ccc1c870808439b1fb17aaf1f`, job #132768343537, Source Pack/local links, module DAG, Work Order registry and Zcode blocked selector all SUCCESS. This evidence revision changes the HEAD, so final-head revalidation is required. |
| Relevant extra security/CodeQL/third-party scans | NOT VERIFIED |
| Platform input event pump/device backend implemented | NO |
| Editor/client/export or Web/headless runtime built | NO |
| Device/peripheral/keyboard layout and assistive user tests | NOT EXECUTED |
| 128 prospective cases | ALL FUTURE / NOT EXECUTED |
| Input latency, p50/p95/p99, CPU/memory/event loss benchmarks | NOT RUN |
| Objective pt-BR documentary audit | PENDING |
| Research PR squash and main readback | PENDING |
| Separate checkpoint PR CI/audit/squash/readback | PENDING |

## 5. Risk register and negative evidence
- Inaccessible remapping locking users out of Back/Cancel/Menu; keyboard layout/IME gameplay leakage; focus capture security.
- Stuck held Attack/Move after hotplug/focus/queue overflow; duplicate physical device from native bridge.
- Device GUID/serial leakage, global logging/keylogging, untrusted MCP physical input, forged client action frames.
- High-frequency event storms, bad analog values, malformed controller mapping database, unsafe user profile migration and stale event generation.
- Browser gestures/Permissions Policy pointer lock denial; inconsistent OS controllers, Linux Wayland/X11 and macOS controllers; unverified adaptive hardware.
- Third-party SDL3/GLFW/HIDAPI/ControllerDB and platform SDK precise license/redistribution rights not frozen. NLE-D009 OPEN.
The architecture proposes controls, but **none is implemented**. No tests, real hardware trace, compatibility matrices, verified input latency/CPU/memory or accessibility certification exist. Documentation research risk LOW; future runtime ELEVATED.

## 6. Proposed checkpoint delta (DO NOT PROMOTE without separate PR)
After research PR exact-final-HEAD CI/audit/squash/main readback and distinct checkpoint PR exact-final-HEAD CI/audit/squash/main readback, change ONLY GAME-01 `research_status` from `RESEARCH_PENDING` to `RESEARCH_DOCUMENTED_ADR_PROPOSED`; counts **39/80 research documented (48.75%)**, **41 RESEARCH_PENDING**, **0 runtime modules implemented**. All 80 coding packets remain BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null; #56 OPEN/BLOCKED, ADR-0042 PROPOSED. Next GAME-02 #58 research only. No Zcode coding permission.

## 7. Audit format
Objective pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED with exact base/final HEAD, eight-file diff, canonical fingerprints, actual Docs Validation/other checks status, risk/license/security/privacy/accessibility/fallback, future tests NOT RUN, and registry checkpoint delta. No "completed" without evidence.
