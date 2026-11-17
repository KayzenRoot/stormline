# CORE-01 INTERNAL_ONLY Integrated Qualification Contract v0 (NLE-PRPLAN-CORE-01-15)

**Status:** `QUALIFICATION HARNESS CONTRACT / NOT IMPLEMENTED / NO PHYSICAL HARDWARE OR SECURITY CLEARANCE`. **Base:** `ee7f3188eee314b7f051ef39ce4c88ab74492fb1`. **ADR:** [ADR-0094](../adr/0094-core-01-integrated-ci-qualification.md). **WO:** [NLE-PRPLAN-CORE-01-15](../work-orders/NLE-PRPLAN-CORE-01-15.md).

## Objective and bounded scope

Provide an integrated CI qualification harness over completed CORE-01 internal components: headless lifecycle, SDL init/quit and window cycles, event queue, display/capability, lifecycle transitions, resource-counter balance and teardown. It is not physical-hardware, 30+30 timing, 32-scenario, long-duration, Wayland-runtime or security-release qualification.

## Harness behavior (exact counts)

| Phase | Count | Oracle |
|---|---|---|
| Headless host | 200 start/stop cycles | every transition succeeds; `live_resources()==0`; acquire/release counts balance |
| SDL runtime + window | 10 init/quit cycles, each with one window create/show/resize/surface/native/destroy | all steps succeed; runtime shutdown `None` |
| Extra native window | 25 create/show/resize/surface/native/destroy cycles | all steps succeed; native handle invalid after destroy |
| Events | 10,000 synthetic SDL events | produced=pushed=consumed=10,000 |
| Display/capability | enumerate/primary + cap probe | display exists; video Supported |
| Lifecycle | 50 suspend/resume + final shutdown | transitions succeed; `Terminated` |
| Teardown | process exit | exit 0; `CORE01_QUALIFICATION_OK`; sanitizer-clean |

`HeadlessHostTestAccess` counters are used only as test instrumentation; no production dependency/API is added.

## Explicitly not qualified

- Physical Windows/Linux/macOS hardware, GPU/driver or display certification.
- 30 cold + 30 warm timing samples, p50/p95/p99, RSS/VRAM/FPS budgets.
- 32 future scenarios, long-duration soak, OS suspend/resume signals, Wayland runtime, IME/DPI/hotplug.
- Security clearance, public ABI, release readiness or full CORE-01 completion.
- CI sanitizer-clean is a defect signal, not a security certification.

## Test oracles

| ID | Scenario | Oracle |
|---|---|---|
| QUAL-01 | headless integration | 200 cycles; zero live resources; counters balanced |
| QUAL-02 | SDL/window integration | 10 init/quit + 1 window each; 25 extra window cycles |
| QUAL-03 | events | 10,000 produced/pushed/consumed |
| QUAL-04 | display/capability/lifecycle | display+video supported; 50 resume cycles; terminated |
| QUAL-05 | teardown | runtime shutdown `None`; exit 0; `CORE01_QUALIFICATION_OK` |
| QUAL-06 | regression/sanitizer | existing 66 CTests; Linux ASan/UBSan; no leak in our code |

macOS without a window server → explicit `NOT_QUALIFIED`, never false PASS. Linux X11 is virtual-display evidence.

## Exact implementation allowlist for packet -15

1. `tests/core/core01_qualification_tests.cpp`
2. `CMakeLists.txt` (additive qualification target/test only)
3. `.github/workflows/core01-internal-headless.yml` (additive CORE-01-15 path filters only)
4. `docs/evidence/NLE-PRPLAN-CORE-01-15.md`

`docs/work-orders/NLE-PRPLAN-CORE-01-15.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale source, gate not merged, selector blocked, count mismatch, resource counter imbalance, existing regression, CI red, HIGH/CRITICAL, out-of-allowlist change, physical/security/performance/32-scenario/release overclaim, or another packet/module unlock.
- Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.
- No secret, paid runner/service, upload, runtime download or release. SDL3 zlib notice preserved; `NLE-D009 OPEN`.
- Risk `STANDARD`, release `INTERNAL_ONLY`. ADR-0003/0075 `PROPOSED`; ADR-0094 bounded; G3 global `NOT_CLEARED`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -15 remains blocked until then.**
