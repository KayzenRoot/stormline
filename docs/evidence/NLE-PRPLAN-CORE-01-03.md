# NLE-PRPLAN-CORE-01-03 — first internal C++20 headless host slice

**Status:** `CODE_PACKET_IMPLEMENTED / NATIVE_CI_PENDING / AUDIT_PENDING` · **Master program order:** `STORM-CORE-01-IMPL-001` (owner authorization 2026-11-17) · **Formal repository packet:** `NLE-PRPLAN-CORE-01-03` · **Work Order:** [NLE-PRPLAN-CORE-01-03](../work-orders/NLE-PRPLAN-CORE-01-03.md) · **Issue:** [#18](https://github.com/KayzenRoot/stormline/issues/18) · **Contract:** [CORE-01 internal headless v0](../contracts/core-01-internal-headless-v0.md) · **ADR:** [ADR-0083](../adr/0083-core-01-internal-headless-slice.md).

This is the first real Stormline engine code packet. It is **INTERNAL_ONLY**, CPU-only, headless, standard-library C++20, with no SDL3, window, GPU, display, audio, network, public ABI, plugin boundary, release or product certification.

## 1. Authorization and Context Lock

- **Owner authorization:** master program `STORM-CORE-01-IMPL-001`, granted 2026-11-17 for progressive real construction subject to individual gates. The formal repository packet remains `NLE-PRPLAN-CORE-01-03`; the master ID is an umbrella, not a second packet or a bulk module unlock.
- **G6 activation:** [PR #426](https://github.com/KayzenRoot/stormline/pull/426) merged by the owner as `aad8a0997fcce182bedb9fac8acdebdd6a8cda13`. The activation allowlist, selector and validator passed before this code was written.
- **Base SHA:** `aad8a0997fcce182bedb9fac8acdebdd6a8cda13` (current `main` at branch creation; the owner work-order reference `dfd3451…` was 5 commits behind and was therefore superseded by a fresh Context Lock).
- **Packet selector:** `python scripts/select_packet.py NLE-PRPLAN-CORE-01-03 --json` → `status=EXECUTOR_READY`, `executor_ready=true`, exit 0. `select_packet.py NLE-PRPLAN-CORE-01-02` and `select_wo.py CORE-01` both exit 2; the 80 module WOs remain locked.

### Fresh source fingerprints

| Source | Raw SHA-256 | Git blob SHA-1 |
|---|---|---|
| `docs/11-checkpoint.md` | `2ef1b3a2ca6fe52f53132cce6716f90eeb1d47d2ae5d3f80f9b8bea742796a22` | `5090dfa5fc39f3e26e5df038c6e23bce2ff1e26a` |
| `docs/10-decisions-ledger.md` | `420220915e0600bb84167106d3384b28e27cd2f4375c1e16ccb8374d701e216c` | `01aa967790dc1ea5e72c2ebebae7b832ec579981` |
| `docs/03-scope.md` | `39ad13b45738516904b767a8997551cccce2a9ff8ea8642c152bb815fa67c0c7` | `0b65820507d946d2b2b4ed3a2b869e60cafaaf22` |
| `docs/09-definition-of-done.md` | `7fc04cc33aad22197b68bcda43fbd356726f11e401cf0e2b68c97f685b12778e` | `e0b7c2466ebec9790a715e47490c015cfb502db4` |
| `docs/adr/0083-core-01-internal-headless-slice.md` | `c484fb10aec5a4b61919967b9026494484f6ae11461f90b94cb1e38fdbdc99a9` | `82d4968e37f0400f092e885d9fe201df772f4719` |
| `docs/contracts/core-01-internal-headless-v0.md` | `b4457feaf74379b5ffd3f8e744727a48cc7673383cd5c259073b495dfd10f38b` | `4ea41263bcfd412ca35df2abb32a158706b64e48` |

The six Git blob IDs match `docs/queue/packet-activations.json` exactly. Any change to these canonical sources invalidates the selector and requires a new authorized gate.

## 2. Implemented behavior

Namespace `stormline::core::internal`, no external ABI guarantee:

- `HostState { Stopped, Starting, Running, Stopping, Failed }`
- `HostError { None, AlreadyRunning, UnsupportedMode, InvalidState, InitFailed, CleanupFailed }`
- `HostConfig { bool headless{true}; }`
- Noncopyable/nonmovable `HeadlessHost` with `start(const HostConfig&) noexcept`, `stop() noexcept`, `state() const noexcept` and no-throw destructor.
- Three fixed, allocation-free lifecycle resources (leases) owned by the host; no heap, no native handles, no SDL types, no OS calls.
- `headless=false` returns `UnsupportedMode` with zero allocations and state unchanged.
- Injected init failure at stages 1–3 rolls back acquired leases exactly once; if rollback cleanup also fails, state becomes `Failed`, leases are retained and the error is `CleanupFailed`.
- `stop` is idempotent on `Stopped`; a cleanup fault enters `Failed`, and a successful retry returns to `Stopped` without double release.
- Start while `Running` returns `AlreadyRunning` with no second allocation; start from `Failed` or a transient state returns `InvalidState`.
- Destructor force-releases remaining leases without throwing, covering `Running` and `Failed` instances.
- Single-owner thread contract; concurrent/reentrant calls are unsupported by design.

The test-only seam `HeadlessHostTestAccess` exposes injected failures and resource counters. It is internal-only, not public API, not ABI and not used by production callers.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/internal/headless_host.hpp` | Internal typed contract and test seam |
| `src/stormline/core/internal/headless_host.cpp` | State machine, leases, rollback, no-throw cleanup |
| `tests/core/headless_host_tests.cpp` | Lifecycle, error, cleanup, destructor and invalid-transition tests |
| `CMakeLists.txt` | Static internal library, test executable, warnings-as-errors, optional sanitizers, CTest |
| `CMakePresets.json` | Schema 6, CMake ≥3.27, Ninja, Debug and ASan/UBSan presets |
| `.github/workflows/core01-internal-headless.yml` | Read-only native CI on standard public runners |
| `docs/evidence/NLE-PRPLAN-CORE-01-03.md` | This Evidence Bundle |

No other path is modified. The packet Work Order already existed and was not changed.

## 4. Tests and real results

### Local supplementary check (not a target qualification)

The local machine has no CMake/Ninja in `PATH`; installing new tooling is prohibited. The preinstalled **MSVC 14.44** was used directly with `/std:c++20 /W4 /WX /EHsc` to compile the library and tests and run every test mode. This is a real compile/link/run check, but MSVC 14.44 is **not** the approved provisional target (14.51) and is marked `NOT_QUALIFIED` as a target.

| Test mode | Result |
|---|---|
| `lifecycle` (200 start/stop cycles, duplicate start, idempotent stop, counters) | **PASS** |
| `errors` (unsupported mode, init failure stages 1–3, init+cleanup failure, recovery) | **PASS** |
| `cleanup` (cleanup failure, retry, no double release) | **PASS** |
| `destructor` (Running and Failed destruction) | **PASS** |
| `invalid` (repeated stop, duplicate start) | **PASS** |

Compiler output: `headless_host.cpp`, `headless_host_tests.cpp`, link success, 5/5 modes `PASS`.

### Native CI (authoritative, pending observation)

The code PR's exact head must run the new workflow on `ubuntu-24.04`, `windows-2025-vs2026` and `macos-15`, plus the Linux ASan/UBSan job when the preinstalled toolchain supports it. The PR remains Draft until these results and the exact-head `docs-validation` are observed and recorded here. No CI PASS is claimed before the runs exist.

### Test oracles covered

- 200/200 start/stop cycles per OS (C01-INT-01), no graphics/audio/display dependency.
- Duplicate start returns `AlreadyRunning` without extra allocation (C01-INT-02).
- Window mode returns `UnsupportedMode` and changes nothing (C01-INT-03).
- Controlled init failure at each stage with exactly-once rollback (C01-INT-04).
- Cleanup fault forces `Failed`; retry returns to `Stopped` with no double free (C01-INT-05).
- Destructor cleans `Running`/`Failed` instances without throwing (C01-INT-06).
- CMake/CTest with `--no-tests=error` on the three CI hosts (C01-INT-07).
- Warnings-as-errors and Linux sanitizers when supported (C01-INT-08).
- No SDL3/OS handles/secrets/network/paid runner (C01-INT-09).
- Clean build directory and no artifact upload (C01-INT-10).

## 5. CI security and cost

- `permissions: contents: read`; `persist-credentials: false`; no secrets, no cache, no artifact upload, no deployment, no PR-controlled privileged workflow.
- `actions/checkout` pinned to the reviewed commit `11bd71901bbe5b1630ceea73d27597364c9af683`.
- Standard public GitHub-hosted runners only; no larger runner, self-hosted runner, paid service or installation.
- The workflow is **not** added to the G2 required-check set; G2 remains the owner-approved `docs-validation` ruleset `27393227`. Native jobs are audit evidence for this packet, not a new gate.

## 6. Security, licensing and ownership

- Only the C++ standard library is used. No third-party dependency, vendored code, asset or license change.
- No SDL3, window, input, renderer, audio, filesystem persistence, network, telemetry, environment secret or raw OS handle.
- Engine source license `NLE-D009` remains `OPEN`; no redistribution, packaging or public release.
- ADR-0003 and ADR-0075 remain `PROPOSED`; G3 global remains `NOT_CLEARED`.
- Risk `STANDARD` and release class `INTERNAL_ONLY` only for this slice. The 80 module WOs remain `BLOCKED`; CORE-01-02 remains documentary; no next packet is unlocked.

## 7. Limitations and risks

- The resource leases are internal instrumentation, not proof of real OS handles or complete memory safety.
- Single-thread only; no concurrency, reentrancy, event loop, window, path or full CORE-01 lifecycle.
- Local native proof uses MSVC 14.44 and is supplementary; the provisional CI targets are GCC 13.3, MSVC 14.51 and AppleClang 17.
- No physical hardware, GPU, SDL3, ABI, packaging or release certification is claimed.
- `strict` G2 checks may require a rebase/rerun after `main` moves; normal PR flow applies.
- No HIGH/CRITICAL defect is known at the time of writing; this remains subject to exact-head native CI and independent audit.

## 8. Rollback

If unmerged: close the code branch/PR; `main` is untouched. If a future merge requires reversal: normal revert PR, never force push or history rewrite. No G2 ruleset, workflow permission, license or registry state is part of this packet's rollback surface.

## 9. Invariants preserved

G1 `PARTIALLY_RATIFIED_NOT_CLEARED`; G2 `CLEARED` only for ruleset `27393227`; G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`; ADR-0003/0075 `PROPOSED`; `NLE-D009 OPEN`; 80/80 module WOs `BLOCKED`; 748 packets with only `NLE-PRPLAN-CORE-01-03` ready in this wave; zero other `executor_ready`; `engine_implemented=false` for the module-level registry and product claim; CORE-01-02 documentary only. This packet implements one internal slice, not the CORE-01 module as a whole.

## 10. Proposed checkpoint delta (not promoted)

After an approved squash merge and main readback, a separate checkpoint PR may record: first real C++ source under `src/stormline/core/internal/`, exact PR/CI/audit/merge SHA, five CTest oracles passing on the qualified CI hosts, and the explicit statement that only the internal headless slice exists. It must not claim G3 clearance, full CORE-01, SDL3/window support, public ABI, release or engine_implemented=true at module/product level. This Evidence Bundle does not self-promote that checkpoint.
