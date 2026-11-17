# CORE-01 INTERNAL_ONLY Multi-OS Soak Contract v0 (NLE-PRPLAN-CORE-01-14)

**Status:** `QUALIFICATION HARNESS CONTRACT / NOT IMPLEMENTED / NO PHYSICAL HARDWARE CERTIFICATION`. **Base:** `9bfbed5901947a3073b2910a48b4c9873702d37f`. **ADR:** [ADR-0093](../adr/0093-core-01-multi-os-soak-harness.md). **WO:** [NLE-PRPLAN-CORE-01-14](../work-orders/NLE-PRPLAN-CORE-01-14.md).

## Objective and bounded scope

Provide a bounded CI soak harness for existing CORE-01 internal APIs: 200 headless host cycles, 100 native window cycles, 10,000 synthetic events, display/lifecycle checks and clean teardown. It is not a physical-hardware, 30+30 timing, 32-scenario or long-duration qualification.

## Dependency and build profile

- Existing CORE-01 internal APIs from `-03`..`-13`: `HeadlessHost`, `SdlRuntime`, `Window`, `EventQueue`, `DisplayService`, `CapabilityProbe`, `LifecycleController`.
- Linux: `SDL_VIDEODRIVER=x11`, Xvfb/openbox (existing workflow); Windows: `windows`; macOS: `cocoa`.
- Sanitizers: Linux ASan/UBSan job runs the same harness.
- No package installation beyond the existing authorized Linux window packages; no paid runner/secret/runtime download.

## Harness behavior (exact counts)

| Phase | Count | Oracle |
|---|---|---|
| Headless host | 200 start/stop cycles | every start `None`/`Running`; every stop `None`/`Stopped` |
| Native window | 100 create/show/resize/query-surface/native-handle/destroy cycles | every step `None`; surface generation advances; native handle valid then invalid after destroy |
| Synthetic events | 10,000 SDL events | all accepted/normalized; no overflow loss; event count equals produced count |
| Display | 1 enumerate + 1 primary query | at least one display; primary marked |
| Lifecycle | 100 suspend/resume + final shutdown | transitions `None`; final `Terminated` |
| Teardown | 1 runtime shutdown and process exit | `None`, exit 0, no leak in sanitizer job |

The executable prints `SOAK_OK headless=200 window=100 events=10000` on success. CTest suppresses stdout on success; the count is recorded in the Evidence Bundle from local/direct invocation and from the test oracle.

## Explicitly not qualified

- Physical Windows/Linux/macOS hardware and GPU/driver certification.
- 30 cold + 30 warm timing samples, p50/p95/p99, RSS/VRAM budgets and FPS.
- 32 future scenarios, long-duration soak (hours/days), suspend/resume OS signals, Wayland runtime, IME/DPI/hotplug.
- Any claim of release readiness, performance PASS or full CORE-01 completion.

## Test oracles and expected result

| ID | Scenario | Oracle |
|---|---|---|
| SOAK-01 | 200 headless cycles | all start/stop/state checks pass |
| SOAK-02 | 100 native window cycles | create/show/resize/surface/native/destroy all pass |
| SOAK-03 | 10,000 events | event queue drains all produced events; no overflow |
| SOAK-04 | display/lifecycle | display primary valid; 100 resume cycles; terminated |
| SOAK-05 | regression/teardown | existing 65 CTests pass; exit 0; no sanitizer leak |

macOS may report `NOT_QUALIFIED` when no window server exists; the final result must be explicit, never a false PASS. Linux X11 is virtual-display evidence, not physical hardware.

## Exact implementation allowlist for packet -14

1. `tests/core/core01_soak_tests.cpp`
2. `CMakeLists.txt` (additive soak target/test only)
3. `.github/workflows/core01-internal-headless.yml` (additive CORE-01-14 path filters only)
4. `docs/evidence/NLE-PRPLAN-CORE-01-14.md`

`docs/work-orders/NLE-PRPLAN-CORE-01-14.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, existing regression, count mismatch, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, physical-hardware/performance/32-scenario overclaim, or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or release. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0003/0075 `PROPOSED`; ADR-0093 bounded; G3 global `NOT_CLEARED`; 80/80 module WOs `BLOCKED`; `engine_implemented=false`.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -14 remains blocked until then.**
