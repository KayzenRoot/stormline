# NLE-PRPLAN-CORE-01-15 — Integrated CI qualification

**Status:** `CODE_IMPLEMENTED / NATIVE_CI_PASS / MERGED`. **Formal packet:** `NLE-PRPLAN-CORE-01-15`. **ADR:** [ADR-0094](../adr/0094-core-01-integrated-ci-qualification.md). **Contract:** [core-01-integrated-qualification-v0](../contracts/core-01-integrated-qualification-v0.md). **WO:** [NLE-PRPLAN-CORE-01-15](../work-orders/NLE-PRPLAN-CORE-01-15.md). **Issue:** [#18](https://github.com/KayzenRoot/stormline/issues/18).

Integrated CI qualification: 200 headless cycles with zero live resources, 10 SDL init/quit + window cycles, 25 extra window cycles, 10,000 key events, display/capability/lifecycle and teardown. No physical-hardware, 30+30 timing, 32-scenario, security, performance or release claim.

## 1. Authorization and Context Lock

- **Gate:** [PR #461](https://github.com/KayzenRoot/stormline/pull/461) squash-merged as `022ec54218e08489a30e3cb01f9fd00e5f4217ec`; audit #6961979730 **APPROVED**.
- **Base:** `022ec54218e08489a30e3cb01f9fd00e5f4217ec`.
- **Code PR:** [PR #462](https://github.com/KayzenRoot/stormline/pull/462), HEAD auditado `ec1c02f…`, [auditoria pt-BR #6962148641](https://github.com/KayzenRoot/stormline/pull/462#issuecomment-6962148641) **APPROVED**; squash-merged as `0286171…`.
- **Selector:** during execution, `select_packet.py NLE-PRPLAN-CORE-01-15 --json` → `EXECUTOR_READY`, exit 0; after closeout every ID exits 2.

## 2. Harness behavior and real counts

- 200 `HeadlessHost` start/stop cycles; `HeadlessHostTestAccess::live_resources()==0`; acquire/release counts balanced.
- 10 `SdlRuntime` init/quit cycles, each with window create/show/resize/surface/native/destroy.
- 25 extra native window cycles.
- 10,000 `SDL_EVENT_KEY_DOWN` produced/pushed; all 10,000 key events consumed after draining (window/background events are ignored for the count).
- Display enumerate/primary; capability probe Video Supported; 50 lifecycle suspend/resume cycles; shutdown Terminated.
- Runtime shutdown; output: `CORE01_QUALIFICATION_OK headless=200 sdl_cycles=10 window_cycles=25 events=10000 lifecycle_cycles=50`; exit 0.
- macOS may report `NOT_QUALIFIED` without a window server.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `tests/core/core01_qualification_tests.cpp` | Integrated qualification harness |
| `CMakeLists.txt` | Additive `stormline_core01_qualification_test` and one CTest |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-01-15 path filters |
| `docs/evidence/NLE-PRPLAN-CORE-01-15.md` | This Evidence Bundle |

No production engine code changed.

## 4. Tests and real results

### Local preflight (observed)

- CMake/Ninja build `stormline_core01_qualification_test`: **OK**.
- Direct run: `QUAL_EVENTS produced=10000 pushed=10000 consumed=10000` and `CORE01_QUALIFICATION_OK ...`, exit 0.
- `ctest -R core01_qualification`: **1/1 passed** on Windows/MSVC 14.44.
- Full local matrix: **67/67 CTests passed** (66 previous + qualification).

An initial count included window/background events (10,075 total popped); the harness now counts only normalized `KeyDown` events and confirms exactly 10,000. This was a harness counting defect, not an engine defect.

### Native CI (authoritative, observed)

All jobs ran at the exact HEAD `52ab4f84fa19ba35bcb744e6cef4fa5c514abed3`:

| Job | Runner / toolchain | Result |
|---|---|---|
| `docs-validation` | required G2 check | [run 44184279547](https://github.com/KayzenRoot/stormline/actions/runs/44184279547) **SUCCESS** |
| `linux` | ubuntu-24.04, GCC, X11 via Xvfb/openbox | **67/67 CTest passed** |
| `linux-sanitizers` | ubuntu-24.04, ASan/UBSan | **67/67 CTest passed** |
| `windows` | windows-2025-vs2026, MSVC | **67/67 CTest passed** |
| `macos` | macos-15-arm64, Apple clang | **67/67 CTest passed** |

Native workflow run: [44184279556](https://github.com/KayzenRoot/stormline/actions/runs/44184279556) **SUCCESS**. Job IDs: Linux `134396499003`, sanitizers `134396498931`, Windows `134396498261`, macOS `134396498922`. The qualification test executed in every job; 66 CTests anteriores continuam passando. No correction was required.

## 5. Security, licensing and limitations

- No new dependency, package, secret, upload, paid runner/service or runtime download.
- No production API/ABI, physical hardware, 30+30 timing, 32 scenarios, long soak, OS suspend/resume, Wayland runtime, security clearance, performance or release.
- Linux X11 is virtual-display evidence under Xvfb/openbox; macOS without a window server yields explicit `NOT_QUALIFIED`.
- ASan/UBSan-clean is a defect signal, not security certification.
- ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.
- No HIGH/CRITICAL known; final status subject to exact-head CI and independent pt-BR audit.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the qualification target/workflow/evidence restores the previous state.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the integrated CI qualification, exact PR/CI/audit/merge SHA, the counts/output, 67 total CTests, and the explicit statement that physical hardware, 30+30 timing, 32 scenarios, Wayland runtime, security clearance, performance and release remain `NOT_QUALIFIED`. This evidence does not self-promote the checkpoint.

## 8. Actual closure

- [PR #462](https://github.com/KayzenRoot/stormline/pull/462) **squash-merged** at `2026-11-17T21:56:19Z`, merge `0286171…`; auditoria #6962148641 **APPROVED**.
- Final-head Docs Validation [44184687788](https://github.com/KayzenRoot/stormline/actions/runs/44184687788) **SUCCESS**; native [44184687710](https://github.com/KayzenRoot/stormline/actions/runs/44184687710) **SUCCESS**, **67/67 CTest** on Linux, Linux ASan/UBSan, Windows and macOS.
- Packet `CORE-01-15` becomes `COMPLETED` with `github_pr=462`; manifest **730 `PLANNED_BLOCKED`, 14 `COMPLETED`, 4 approved gates, 0 `EXECUTOR_READY`**; selector denies every ID. Physical hardware, 30+30 timing, 32 scenarios, Wayland runtime, security clearance, performance and release remain **NOT_QUALIFIED**; `CORE-01-16` closeout remains blocked.
