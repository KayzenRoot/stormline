# NLE-PRPLAN-CORE-01-14 — Multi-OS soak harness

**Status:** `CODE_IMPLEMENTED / NATIVE_CI_PASS / MERGED`. **Formal packet:** `NLE-PRPLAN-CORE-01-14`. **ADR:** [ADR-0093](../adr/0093-core-01-multi-os-soak-harness.md). **Contract:** [core-01-multi-os-soak-v0](../contracts/core-01-multi-os-soak-v0.md). **WO:** [NLE-PRPLAN-CORE-01-14](../work-orders/NLE-PRPLAN-CORE-01-14.md). **Issue:** [#18](https://github.com/KayzenRoot/stormline/issues/18).

Bounded CI soak harness: 200 headless cycles, 100 native window cycles, 10,000 synthetic events, display/lifecycle checks and teardown. No physical-hardware certification, 30+30 timing, 32 scenarios, performance budget or release.

## 1. Authorization and Context Lock

- **Gate:** [PR #458](https://github.com/KayzenRoot/stormline/pull/458) squash-merged as `9d323a154ba8160bc13afe6afbb3b4f7e62cb48b`; audit #6961559495 **APPROVED**.
- **Code PR:** [PR #459](https://github.com/KayzenRoot/stormline/pull/459), HEAD auditado `39ab209…`, [auditoria pt-BR #6961796302](https://github.com/KayzenRoot/stormline/pull/459#issuecomment-6961796302) **APPROVED**; squash-merged as `562290a…`.
- **Base:** `9d323a154ba8160bc13afe6afbb3b4f7e62cb48b`.
- **Selector:** `select_packet.py NLE-PRPLAN-CORE-01-14 --json` → `EXECUTOR_READY`, exit 0; `-15`, `CORE-02-04` and every other ID exit 2.

## 2. Harness behavior

- 200 `HeadlessHost` start/stop cycles, checking `None`/`Running`/`Stopped`.
- 100 window create/show/resize/surface/native-handle/destroy cycles; surface generation valid, native handle invalid after destroy.
- 10,000 `SDL_EVENT_KEY_DOWN` synthetic events pushed, queued and drained; produced/pushed/consumed all 10,000.
- Display enumerate/primary; 100 lifecycle suspend/resume cycles + shutdown; capability probe reports video supported.
- Runtime shutdown; prints `SOAK_OK headless=200 window=100 events=10000`; exit 0.
- Linux X11/Xvfb, Windows Win32, macOS Cocoa or explicit `NOT_QUALIFIED` if no window server.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `tests/core/core01_soak_tests.cpp` | Soak harness with the exact counts |
| `CMakeLists.txt` | Additive `stormline_core01_soak_test` and one CTest |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-01-14 path filters |
| `docs/evidence/NLE-PRPLAN-CORE-01-14.md` | This Evidence Bundle |

No production engine code changed.

## 4. Tests and real results

### Local preflight (observed)

- CMake/Ninja build of `stormline_core01_soak_test`: **OK**.
- Direct run: `SOAK_EVENTS produced=10000 pushed=10000 consumed=10000` and `SOAK_OK headless=200 window=100 events=10000`, exit 0.
- `ctest -R core01_soak`: **1/1 passed** on Windows/MSVC 14.44.
- Full local matrix: **66/66 CTests passed** (65 previous + soak).

The initial batched push/poll version lost events after 33 batches; the harness was corrected to push the full 10,000 then drain, and the final run consumed all 10,000. This was a harness defect, not an engine defect.

### Native CI (authoritative, observed)

All jobs ran at the exact HEAD `65baba8157fe3abcee6d9418af17b277905b4a8f`:

| Job | Runner / toolchain | Result |
|---|---|---|
| `docs-validation` | required G2 check | [run 44181450664](https://github.com/KayzenRoot/stormline/actions/runs/44181450664) **SUCCESS** |
| `linux` | ubuntu-24.04, GCC, X11 via Xvfb/openbox | **66/66 CTest passed** |
| `linux-sanitizers` | ubuntu-24.04, ASan/UBSan | **66/66 CTest passed** |
| `windows` | windows-2025-vs2026, MSVC | **66/66 CTest passed** |
| `macos` | macos-15-arm64, Apple clang | **66/66 CTest passed** |

Native workflow run: [44181450631](https://github.com/KayzenRoot/stormline/actions/runs/44181450631) **SUCCESS**. Job IDs: Linux `134386533797`, sanitizers `134386534384`, Windows `134386534455`, macOS `134386534190`. The soak test executed in every job; 65 CTests anteriores continuam passando. No correction was required.

## 5. Security, licensing and limitations

- No new dependency, package, secret, upload, paid runner/service or runtime download.
- No production API/ABI, renderer/GPU/audio, physical hardware, 30 cold + 30 warm timing, 32 scenarios, long-duration soak, OS suspend/resume signals, Wayland runtime or performance claim.
- Linux X11 is virtual-display evidence under Xvfb/openbox, not physical hardware; macOS window-server absence yields explicit `NOT_QUALIFIED`.
- ADR-0003/0075 remain `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.
- No HIGH/CRITICAL known; native CI passed at the code head and the result remains subject to the independent pt-BR audit.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the soak target/workflow/evidence restores the previous state.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the tenth real CORE-01 increment, exact PR/CI/audit/merge SHA, the soak counts, `SOAK_OK`, 66 total CTests and the explicit statement that physical hardware, 30+30 timing, 32 scenarios, Wayland runtime and performance remain `NOT_QUALIFIED`. This evidence does not self-promote the checkpoint.

## 8. Actual closure

- [PR #459](https://github.com/KayzenRoot/stormline/pull/459) **squash-merged** at `2026-11-17T21:40:13Z`, merge `562290a…`; audit #6961796302 **APPROVED**.
- Final-head Docs Validation [44181985518](https://github.com/KayzenRoot/stormline/actions/runs/44181985518) **SUCCESS**; native [44181985330](https://github.com/KayzenRoot/stormline/actions/runs/44181985330) **SUCCESS**, **66/66 CTest** on Linux, Linux ASan/UBSan, Windows and macOS.
- Packet `CORE-01-14` becomes `COMPLETED` with `github_pr=459`; manifest **731 `PLANNED_BLOCKED`, 13 `COMPLETED`, 4 approved gates, 0 `EXECUTOR_READY`**; selector denies every ID. Physical hardware, 30+30 timing, 32 scenarios, Wayland runtime and performance remain **NOT_QUALIFIED**. No next packet/module authorized.
