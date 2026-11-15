# GAME-01 — Acceptance Matrix: 128 FUTURE Tests, NONE EXECUTED

**Research issue #208 | WO NLE-P00-WO-002-GAME-01 | future coding #56 OPEN/BLOCKED.** This document specifies exactly **128 prospective tests (16 suites × 8)**, all **FUTURE / NOT EXECUTED**. The catalog acceptance "Mapeamentos consistentes entre editor, runtime e exports" is NOT achieved. No device backend, action-map interpreter, editor UI, cross-platform export, injected-input harness or benchmark has been implemented.

| Test ID | Future assertion / fixture | Status |
|---|---|---|
| GAME01-KEY-01 | Physical-scancode Move action remains on the same physical position under US QWERTY and Brazilian ABNT2 | FUTURE / NOT EXECUTED |
| GAME01-KEY-02 | Logical-key shortcut resolves according to configured locale and modifiers without changing physical binding | FUTURE / NOT EXECUTED |
| GAME01-KEY-03 | AltGr and dead-key composition generate text only through focused UI text owner | FUTURE / NOT EXECUTED |
| GAME01-KEY-04 | IME composing Japanese/Chinese/Korean text never generates gameplay Attack/Confirm actions | FUTURE / NOT EXECUTED |
| GAME01-KEY-05 | SDL3 StartTextInput explicit per-window enable/disable and focus transitions are honored | FUTURE / NOT EXECUTED |
| GAME01-KEY-06 | OS key auto-repeat does not retrigger single-edge action unless repeat mode is authored | FUTURE / NOT EXECUTED |
| GAME01-KEY-07 | Down/up in a single CORE-04 tick preserves BOTH ordered edges, including fast tap | FUTURE / NOT EXECUTED |
| GAME01-KEY-08 | Virtual accessibility keyboard fallback may lack physical code and reports logical/unknown capability | FUTURE / NOT EXECUTED |
| GAME01-MOU-01 | Relative mouse deltas accumulate under declared policy without changing click ordering | FUTURE / NOT EXECUTED |
| GAME01-MOU-02 | Absolute cursor coordinates are transformed by correct DPI and window revision | FUTURE / NOT EXECUTED |
| GAME01-MOU-03 | Mouse wheel reports normalized direction/units with finite scroll clipping | FUTURE / NOT EXECUTED |
| GAME01-MOU-04 | Focused GUI consumes click without triggering underlying gameplay action | FUTURE / NOT EXECUTED |
| GAME01-MOU-05 | Lost pointer capture/focus releases held mouse button and resets relative-mode state | FUTURE / NOT EXECUTED |
| GAME01-MOU-06 | Cursor return/ESC recovery restores visible pointer without OS-global lock | FUTURE / NOT EXECUTED |
| GAME01-MOU-07 | Multiple window input cannot move camera of an unfocused game window | FUTURE / NOT EXECUTED |
| GAME01-MOU-08 | Motion coalescing preserves final position, wheel events and press-release edges | FUTURE / NOT EXECUTED |
| GAME01-PAD-01 | SDL3 standard gamepad buttons map to Stormline ActionId independently of vendor name | FUTURE / NOT EXECUTED |
| GAME01-PAD-02 | Controller hotplug increments DeviceEpoch and rejects stale old device handle | FUTURE / NOT EXECUTED |
| GAME01-PAD-03 | Trigger range [0,1] normalizes backend numeric extremes with finite bounds | FUTURE / NOT EXECUTED |
| GAME01-PAD-04 | Radial stick deadzone rejects noise near center without diagonal angle bias | FUTURE / NOT EXECUTED |
| GAME01-PAD-05 | Opposite-direction button/axis composite applies deterministic cancel/priority | FUTURE / NOT EXECUTED |
| GAME01-PAD-06 | Unknown GUID uses bounded default/error rather than dangerous auto-remap | FUTURE / NOT EXECUTED |
| GAME01-PAD-07 | Gamepad mapping update requires exact version/rights and cannot access host paths | FUTURE / NOT EXECUTED |
| GAME01-PAD-08 | Missing gamepad leaves keyboard fallback active and records capability status | FUTURE / NOT EXECUTED |
| GAME01-TCH-01 | Two independent touch pointer IDs remain distinct through down/move/up | FUTURE / NOT EXECUTED |
| GAME01-TCH-02 | Cancelled touch immediately ends held action and gesture generation | FUTURE / NOT EXECUTED |
| GAME01-TCH-03 | One-finger tap exposes accessible equivalent of a menu click | FUTURE / NOT EXECUTED |
| GAME01-TCH-04 | Pinch/rotate gesture emits a semantic axis only when opted in and supported | FUTURE / NOT EXECUTED |
| GAME01-TCH-05 | Pointer pressure/tilt absence is reported UNKNOWN/UNSUPPORTED, not zero with false confidence | FUTURE / NOT EXECUTED |
| GAME01-TCH-06 | Multi-touch simultaneous interactions preserve player/target ownership | FUTURE / NOT EXECUTED |
| GAME01-TCH-07 | High-frequency coalesced pointer updates preserve click/cancel and final coordinates | FUTURE / NOT EXECUTED |
| GAME01-TCH-08 | Drag-only UI operation offers alternative single-pointer/keyboard method where applicable | FUTURE / NOT EXECUTED |
| GAME01-SEAT-01 | Two connected gamepads join separate local PlayerSeat IDs with no cross-action leakage | FUTURE / NOT EXECUTED |
| GAME01-SEAT-02 | One player uses keyboard+gamepad without double-applying combined movement | FUTURE / NOT EXECUTED |
| GAME01-SEAT-03 | Mid-session gamepad reassignment uses explicit seat CAS and releases prior actions | FUTURE / NOT EXECUTED |
| GAME01-SEAT-04 | Two devices cannot claim same exclusive seat without conflict receipt | FUTURE / NOT EXECUTED |
| GAME01-SEAT-05 | Disconnected pad fallback preserves other devices and never leaves stuck Attack | FUTURE / NOT EXECUTED |
| GAME01-SEAT-06 | Physical-keyboard separation is reported UNKNOWN on aggregated backend, not fabricated | FUTURE / NOT EXECUTED |
| GAME01-SEAT-07 | Seat rejoin increments epoch and rejects queued stale input | FUTURE / NOT EXECUTED |
| GAME01-SEAT-08 | Per-player profiles remain isolated across controller connect/disconnect | FUTURE / NOT EXECUTED |
| GAME01-ACT-01 | Digital action emits exactly one PRESSED and one RELEASED edge per physical cycle | FUTURE / NOT EXECUTED |
| GAME01-ACT-02 | Axis1D combines dual trigger values and clamps to configured range | FUTURE / NOT EXECUTED |
| GAME01-ACT-03 | Vector2 keyboard WASD diagonal normalization prevents velocity greater than configured magnitude | FUTURE / NOT EXECUTED |
| GAME01-ACT-04 | Bounded two-key chord obeys authored order/timeout and deterministic tie-break | FUTURE / NOT EXECUTED |
| GAME01-ACT-05 | Tap/hold/toggle actions obey CORE-04 tick-based thresholds under differing render FPS | FUTURE / NOT EXECUTED |
| GAME01-ACT-06 | Forbidden action type to control-source mismatch fails validation | FUTURE / NOT EXECUTED |
| GAME01-ACT-07 | Unknown required ActionId fails closed with clear missing-binding error | FUTURE / NOT EXECUTED |
| GAME01-ACT-08 | Action resolver state machine rejects recursive/unbounded instantaneous chords | FUTURE / NOT EXECUTED |
| GAME01-CTX-01 | Text editing context suppresses gameplay shortcuts while IME is active | FUTURE / NOT EXECUTED |
| GAME01-CTX-02 | Editor modal captures Confirm and leaves gameplay action unexecuted | FUTURE / NOT EXECUTED |
| GAME01-CTX-03 | Context stack push/pop at tick fence releases inherited held actions safely | FUTURE / NOT EXECUTED |
| GAME01-CTX-04 | Menu and gameplay reuse same button in mutually exclusive contexts by explicit rule | FUTURE / NOT EXECUTED |
| GAME01-CTX-05 | Focus loss, minimize, suspend and window destruction reset gameplay held state | FUTURE / NOT EXECUTED |
| GAME01-CTX-06 | Focus handoff across windows cannot deliver stale pointer/keyboard events | FUTURE / NOT EXECUTED |
| GAME01-CTX-07 | UI/Editor focus revision mismatch rejects routing and preserves prior stable plan | FUTURE / NOT EXECUTED |
| GAME01-CTX-08 | Keyboard+gamepad navigation can switch without losing visible UI focus | FUTURE / NOT EXECUTED |
| GAME01-MAP-01 | Focused remap capture records a new binding with user consent and timeout | FUTURE / NOT EXECUTED |
| GAME01-MAP-02 | Remap attempt in password or hidden text field is rejected | FUTURE / NOT EXECUTED |
| GAME01-MAP-03 | Conflict SWAP/REPLACE/KEEP/REJECT choices produce deterministic diff receipt | FUTURE / NOT EXECUTED |
| GAME01-MAP-04 | Protected Back/Cancel recovery bindings cannot be removed without accessible replacement | FUTURE / NOT EXECUTED |
| GAME01-MAP-05 | DATA-04 expected revision conflict leaves last-good map unchanged | FUTURE / NOT EXECUTED |
| GAME01-MAP-06 | Corrupt profile migration stages/aborts without partial user settings loss | FUTURE / NOT EXECUTED |
| GAME01-MAP-07 | Player-local user preferences override project defaults without changing authored source | FUTURE / NOT EXECUTED |
| GAME01-MAP-08 | Editor/CLI/MCP authoring produce identical semantic validation for same role and input | FUTURE / NOT EXECUTED |
| GAME01-ANA-01 | Radial deadzone center and edge behavior follow declared finite curve | FUTURE / NOT EXECUTED |
| GAME01-ANA-02 | Axial deadzone comparator is opt-in and has stable diagonal handling | FUTURE / NOT EXECUTED |
| GAME01-ANA-03 | Sensitivity/inversion transform preserves expected axis range with saturation | FUTURE / NOT EXECUTED |
| GAME01-ANA-04 | Non-monotonic curve, deadzone >= 1 and NaN values are rejected | FUTURE / NOT EXECUTED |
| GAME01-ANA-05 | Enter/exit hysteresis prevents noisy trigger from rapid digital flapping | FUTURE / NOT EXECUTED |
| GAME01-ANA-06 | Large-magnitude analog input is clamped without overflow or invalid frame | FUTURE / NOT EXECUTED |
| GAME01-ANA-07 | Sequential same-tick axis events are folded with explicit sample/last-value policy | FUTURE / NOT EXECUTED |
| GAME01-ANA-08 | Calibration reset restores safe authored defaults without controller lockout | FUTURE / NOT EXECUTED |
| GAME01-ACC-01 | One-handed preset can bind essential actions without mandatory simultaneous chord | FUTURE / NOT EXECUTED |
| GAME01-ACC-02 | Hold-to-toggle profile does not break pause/escape/back safety semantics | FUTURE / NOT EXECUTED |
| GAME01-ACC-03 | Adjustable double-tap and long-hold thresholds provide single-press alternative when possible | FUTURE / NOT EXECUTED |
| GAME01-ACC-04 | User can navigate critical menus by keyboard alone without timed key sequences | FUTURE / NOT EXECUTED |
| GAME01-ACC-05 | Gamepad switch and keyboard mode coexist without modality lock | FUTURE / NOT EXECUTED |
| GAME01-ACC-06 | Pointer cancellation and gesture/drag alternatives operate for applicable UI interactions | FUTURE / NOT EXECUTED |
| GAME01-ACC-07 | Adaptive controller/device feature absence is honestly reported as unverified | FUTURE / NOT EXECUTED |
| GAME01-ACC-08 | Accessible profile settings persist, reset and expose visible controls to UI owner | FUTURE / NOT EXECUTED |
| GAME01-TIM-01 | CORE-04 60Hz fixed tick and 30/120/240Hz render yield same normalized frame action sequence | FUTURE / NOT EXECUTED |
| GAME01-TIM-02 | Input timestamp monotonic regression returns typed anomaly rather than negative interval | FUTURE / NOT EXECUTED |
| GAME01-TIM-03 | Device events order is stable for equal-time events using source sequence and tie-break | FUTURE / NOT EXECUTED |
| GAME01-TIM-04 | Rapid down+up+down between ticks preserves all transitions, not only last held state | FUTURE / NOT EXECUTED |
| GAME01-TIM-05 | Event queue near capacity retains critical transitions or triggers explicit fail-safe reset | FUTURE / NOT EXECUTED |
| GAME01-TIM-06 | Motion coalescing under stress does not discard a key release or gamepad disconnect | FUTURE / NOT EXECUTED |
| GAME01-TIM-07 | CORE-04 pause/one-step produces declared action hold/reset semantics | FUTURE / NOT EXECUTED |
| GAME01-TIM-08 | Clock rebase/tick epoch rejects stale action frame and never silently injects action | FUTURE / NOT EXECUTED |
| GAME01-REP-01 | Recorded event journal replays identical ActionFrame digests with fixed map and tick schedule | FUTURE / NOT EXECUTED |
| GAME01-REP-02 | Replay with mismatched map revision fails or uses declared migration, not blind success | FUTURE / NOT EXECUTED |
| GAME01-REP-03 | Replay with different CPU/render FPS preserves semantic fixed tick action order | FUTURE / NOT EXECUTED |
| GAME01-REP-04 | Headless test harness runs with no window, audio, GPU or real device | FUTURE / NOT EXECUTED |
| GAME01-REP-05 | Seeded input trace does not assert whole-game deterministic simulation | FUTURE / NOT EXECUTED |
| GAME01-REP-06 | Captured personal text/IME data is omitted or redacted from replay journal | FUTURE / NOT EXECUTED |
| GAME01-REP-07 | Event loss/focus device disconnect is faithfully represented in test trace | FUTURE / NOT EXECUTED |
| GAME01-REP-08 | Replay interface cannot inject into a live client without separate privileged authorization | FUTURE / NOT EXECUTED |
| GAME01-WEB-01 | Web Gamepad unavailable before gesture produces explicit capability/pending state | FUTURE / NOT EXECUTED |
| GAME01-WEB-02 | Permissions-Policy denial returns SecurityError mapping without polling loop crash | FUTURE / NOT EXECUTED |
| GAME01-WEB-03 | Cross-origin iframe/sandbox restrictions do not get bypassed | FUTURE / NOT EXECUTED |
| GAME01-WEB-04 | Pointer lock denied/unavailable restores nonlocked mouse and alternative camera control | FUTURE / NOT EXECUTED |
| GAME01-WEB-05 | Web keyboard key/code disagreement follows physical/logical fallback policy | FUTURE / NOT EXECUTED |
| GAME01-WEB-06 | Pointer Events Level 3 unsupported raw/predicted features degrade to ordinary pointermove | FUTURE / NOT EXECUTED |
| GAME01-WEB-07 | User browser loses focus or page hidden and all held input resets | FUTURE / NOT EXECUTED |
| GAME01-WEB-08 | Browser touch/gamepad availability is tested by target browser matrix, not inferred universally | FUTURE / NOT EXECUTED |
| GAME01-SEC-01 | Unauthorized MCP principal cannot capture raw keyboard or inject physical live events | FUTURE / NOT EXECUTED |
| GAME01-SEC-02 | Gamepad serial/HID fingerprint cannot appear in public action/telemetry records | FUTURE / NOT EXECUTED |
| GAME01-SEC-03 | Input event journal excludes passwords, text composition and sensitive UI content | FUTURE / NOT EXECUTED |
| GAME01-SEC-04 | Client-supplied action frames are untrusted and GAME/NET validates ownership/rate | FUTURE / NOT EXECUTED |
| GAME01-SEC-05 | Malicious input profile with huge chord graph or binding count hits bounded quota | FUTURE / NOT EXECUTED |
| GAME01-SEC-06 | Broken UTF-8/JSON, unknown required enum and out-of-range durations fail closed | FUTURE / NOT EXECUTED |
| GAME01-SEC-07 | Stale window/device/seat generation is rejected without corrupting current device | FUTURE / NOT EXECUTED |
| GAME01-SEC-08 | Host OS global hook/keyboard capture capability is not requested by baseline engine | FUTURE / NOT EXECUTED |
| GAME01-PLT-01 | Windows native keyboard layouts and two controller models pass target smoke fixture | FUTURE / NOT EXECUTED |
| GAME01-PLT-02 | Linux Wayland and X11 focus/hotplug/relative pointer differences are reported | FUTURE / NOT EXECUTED |
| GAME01-PLT-03 | macOS arm64 controller connect, keyboard composition and focus loss follow contract | FUTURE / NOT EXECUTED |
| GAME01-PLT-04 | macOS Intel support remains explicitly target-dependent and is not silently claimed | FUTURE / NOT EXECUTED |
| GAME01-PLT-05 | SDL3 input source/main-thread event pump is unique under CORE-01 | FUTURE / NOT EXECUTED |
| GAME01-PLT-06 | Headless server initializes without physical input and accepts authorized fixture only | FUTURE / NOT EXECUTED |
| GAME01-PLT-07 | Unsupported haptics/gyro/wheel capabilities have explicit no-op/failure receipts | FUTURE / NOT EXECUTED |
| GAME01-PLT-08 | Platform changes do not alter stable ActionId or serialized input profile identity | FUTURE / NOT EXECUTED |
| GAME01-BEN-01 | Keyboard/mouse event ingress-to-action p50/p95/p99/max and latency uncertainty recorded | FUTURE / NOT EXECUTED |
| GAME01-BEN-02 | One/two/eight controllers and multi-seat routing CPU/memory measured | FUTURE / NOT EXECUTED |
| GAME01-BEN-03 | 1k/10k/100k synthetic input events per second exercise bounded queue/backpressure | FUTURE / NOT EXECUTED |
| GAME01-BEN-04 | Large action maps with 32/128/512 bindings show compile cost and bounded per-tick work | FUTURE / NOT EXECUTED |
| GAME01-BEN-05 | Gamepad polling and OS event pump compare SDL3 adapter vs optional native comparator | FUTURE / NOT EXECUTED |
| GAME01-BEN-06 | Rapid hotplug/focus changes in 60-minute soak show no leaked actions or stale handles | FUTURE / NOT EXECUTED |
| GAME01-BEN-07 | Cross-platform remap migration and replay digest checks record map/device revisions | FUTURE / NOT EXECUTED |
| GAME01-BEN-08 | Real-user accessibility tests check task completion and recovery under different modalities | FUTURE / NOT EXECUTED |

## Required proof categories and evidence
- **Unit & property:** physical-vs-logical key tokens, touch pointer generation, action graph validation/complexity, same-tick digital edges, analog deadzone/curves/hysteresis, precedence/contexts and replay digest. Seeded fuzz invalid binding graphs/UTF-8/JSON and counter limits.
- **Integration:** CORE-01 SDL3 single event pump, CORE-04 fixed-tick mapping, CORE-03 off-tick compile, DATA-01/02/04 persistence, UI/Editor focus/IME and GAME/NET trusted execution boundary.
- **Native hardware matrix:** Windows x64 and OS version to be approved; Linux Wayland/X11 (and distro/glibc floor TBD); macOS arm64 plus Intel feasibility; keyboard QWERTY, ABNT2, non-Latin/IME, two controller families, multi-seat and mouse DPI. Real hardware and baseline driver/hash mandatory.
- **Web matrix:** actual Chromium/Firefox/WebKit versions; focus/user gesture, Gamepad Permissions Policy, pointer events and Pointer Lock denied/unavailable behavior; browsers are not interchangeable without evidence.
- **Headless:** deterministic replay of original synthetic event traces, no device or GUI; disabled unauthorized live injection.
- **Accessibility:** keyboard-only tasks, one-handed, alternate gestures/drag, hold-to-toggle, focus visible, adaptive-controller feasibility, assistive tech interaction and real user tests where feasible. WCAG 2.2 is reference, not certification.
- **Privacy/security:** not logging text/IME/serials, no background global capture, authenticated authoring, malformed mapping/queue/gesture, stale seat/epoch and client anti-spoof boundary. No anti-cheat claim.
- **Performance:** event-to-action observed latency with hardware/clock caveats, p50/p95/p99/max CPU and queue delay, per-device memory, dropped/coalesced event count, worst-case compile/update, long-run leak/focus/hotplug and input-frame digest.
- **Future Evidence Bundle:** BASE/HEAD SHA, exact imported original fixture and hardware/license provenance, compiler/SDL tag, actual commands, CI, target configs, logs, p95/p99 distributions, failure cases, sanitizer/fuzz checks, recovery/readback. None exists today.

All tests in this file are NOT RUN. No pass/fail measurements, latency numbers, controller compatibility, assistive accessibility certification, Web support guarantee or future benchmark superiority may be inferred.
