# GAME-01 — Reproducible Input Responsiveness, Compatibility and Accessibility Benchmark Protocol

**P00 RESEARCH ONLY | 2026-11-15 | issue #208 | WO NLE-P00-WO-002-GAME-01.** No event listener, device registry, remap UI, input frame, controller fixture, native/Web/headless build or measured benchmark exists. All proposed workload values are future test design, **NOT CURRENT RESULTS**.

## Questions requiring experimental proof
1. Does CORE-01's single native SDL3 event pump deliver sufficiently bounded event-to-action latency without duplicate device streams or blocking gameplay?
2. Can a Stormline-owned ActionMap compile/freeze and resolve context, remaps, chords and analog composites identically in Editor/client/export for each platform?
3. Are all physical press+release edges preserved at fixed tick fences independent of render FPS, with deterministic headless replay and typed queue overflow?
4. Does focus loss, gamepad disconnect, browser permission/activation denial or migration failure safely reset held actions and preserve local/user settings?
5. Are keyboard layout/IME, pointer/touch, multiple gamepads/player seats and accessibility alternatives actually usable by real target devices and people?
6. Is input privacy preserved (no text/IME/serials in telemetry), and does the gameplay/network authority reject forged action frames?

## Original and legally permitted fixtures (FUTURE, not produced)
- **KEY-REF:** documented US QWERTY and Brazilian ABNT2 physical layouts; dead key, AltGr and CJK IME fixtures with only synthetic nonpersonal text.
- **DEV-REF:** transient synthetic two-gamepad/one-keyboard/mouse/touch event traces with connection/seat epochs; real hardware model, firmware and VID/PID may be noted only in a restricted lab record if justified/consented.
- **ACT-REF:** original ActionMap with 32/128/512 bindings, contexts MENU/GAMEPLAY/TEXT_EDIT and Digital/Axis1D/Vector2 controls; synthetic burst/queue overflow fixture and exact oracle action digest.
- **ACC-REF:** task scripts for one-handed/hold-toggle, keyboard-only menus, alternative to dragging/gesture, reduced stick drift and recovery from remap lockout; user feedback with consent.
- **WEB-REF:** browser/iframe fixture with Gamepad API exposure after gesture, Permissions-Policy denial, Pointer Events fallback and Pointer Lock denial/ESC; no cross-origin permission bypass.
- Fixtures must have source hash, license/consent, exact schema revision, generated expected oracle and safe redacted logs. No outside SDL_GameControllerDB entries or personal keystrokes are included without explicit approved rights/privacy checks.

## Protocol matrix
| Workload | Future configurations | Measure and failure detection |
|---|---|---|
| Native input latency | 1/2/8 controllers, 125/500/1000Hz synthetic event source where hardware supports; 60Hz tick plus variable 30/60/144/240 render FPS | CORE-01 event accepted to GAME-01 frame/consumer p50/p95/p99/max; pipeline stages, sample timestamps, time uncertainty; not physical switch-to-photon without external capture |
| Event burst and overflow | 1k/10k/100k events/s synthetic; key down/up and pointer motion interleaved | dropped/coalesced event count, fail-safe releases, queue high-water and CPU/memory; critical button edge must never vanish silently |
| Action-map size | 32/128/512 actions/bindings and 1/8/32 contexts; bounded 2-4 key chords | graph compile time, peak memory, per-tick resolution CPU worst/p95/p99, conflicts and result digest |
| Analog and touch | 1/2/8 concurrent sticks, 1/2/5 touch pointers, different deadzones/transform curves | jitter, hysteresis, drift, normalization, same-tick edge preservation, gesture accessibility fallback |
| Seat/hotplug and focus | 1/2/4 players, frequent disconnect/reassign, window focus/Alt-Tab/IME/suspend | stale epoch rejects, stuck input count, release latency, device rejoin, user settings preservation |
| Cross-platform parity | Windows x64, Linux Wayland/X11, macOS arm64/Intel feasibility, Web browsers and headless | semantic golden ActionFrame digest for supported capabilities and explicit unsupported/fallback matrix |
| Remap and accessibility | conflict/rollback/swap, hold-toggle/one-handed, keyboard-only and pointer alternatives | completion/failure/recovery rates, user task timing, lost focus, inaccessible flow reports |
| Endurance | 60-minute mixed-event soak and 1000 connect/disconnect/focus cycles synthetic | leak/high-water, inconsistent action frames, CPU/memory drift, unauthorized input event count |

## Instrumentation and rigor
- Build matrix: exact Git SHA, compiler, OS version, runtime/config, SDL3 tag/SBOM and optional native platform SDK/hash, device class and provenance, input/profile revisions, browser version, screen/DPI/focus, CORE-04 tick rate, render cadence, target CPU/power state.
- Separate **synthetic injection through test harness only** from actual device measurements. Do not claim hardware latency from event timestamp or synthetic replay alone. If measuring real device input-to-photon, add external camera/photodiode/logic analyzer with calibration and clock error bounds; these are distinct metrics.
- Record stage timestamps only where trusted monotonic clock mapping exists; otherwise report latency uncertainty, jitter and lost events. Distinguish OS/browser batching, USB polling, device firmware delay, display refresh and human reaction variability.
- Repeated cold/warm runs, randomized order, distributions (median/p50, p95, p99, maximum), confidence intervals where appropriate, CPU cycles/time, memory high-water, queue overflow, action-frame digest, privacy redaction and reproducible artifacts.
- **Quantitative acceptance thresholds** for max events/tick, bound queue, action CPU, latency, supported gamepads/browsers, focus recovery and accessibility task success are UNDECIDED until baseline and actual target hardware are specified. Avoid marketing "zero input lag", "all controllers work" or "accessible everywhere".
- Gate release on real per-target smoke, adversarial malformed profile/permissions, fuzz/property/regression and independent pt-BR objective audit. No test or benchmark has yet been run.
