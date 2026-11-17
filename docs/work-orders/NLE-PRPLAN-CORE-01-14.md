# NLE-PRPLAN-CORE-01-14 — Multi-OS soak harness (INTERNAL_ONLY)

**STATUS: COMPLETED — implemented and merged via [PR #459](https://github.com/KayzenRoot/stormline/pull/459), merge `562290a…`. This packet must not be re-executed; no next packet or module is authorized.** **Gate:** G6 individual. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-14`. **Predecessor:** `-13` `COMPLETED` via PR #456. **Issue:** #18. **Base:** `9bfbed5901947a3073b2910a48b4c9873702d37f`. **ADR:** [ADR-0093](../adr/0093-core-01-multi-os-soak-harness.md). **Contract:** [core-01-multi-os-soak-v0](../contracts/core-01-multi-os-soak-v0.md).

## OBJECTIVE

Implement a bounded multi-OS CI soak harness over existing CORE-01 APIs: 200 headless cycles, 100 native window cycles, 10,000 synthetic events, display/lifecycle checks and clean teardown.

## CONTEXT

`-03`..`-13` are completed. C01-D14 ratified 200 headless cycles, 100 window cycles per OS, 10,000 events, 30 cold + 30 warm samples and 32 future scenarios. This packet executes only the first three counts in CI; the remaining qualification stays NOT_QUALIFIED.

## SCOPE

- `core01_soak_test` executable with the exact counts and oracles SOAK-01..SOAK-05.
- Linux X11 under Xvfb/openbox, Windows Win32, macOS Cocoa or explicit NOT_QUALIFIED.
- Linux ASan/UBSan same harness; existing 65 CTests regression.
- Evidence Bundle with local/direct SOAK_OK output and CI results.

## OUT OF SCOPE

Physical hardware certification, 30+30 timing samples, p95/p99/RSS/FPS, 32 future scenarios, long-duration soak, OS suspend/resume signals, Wayland runtime, IME/DPI/hotplug, public ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`; checkpoint; ADRs 0003/0075/0083..0093; Scope/DoD/Architecture/Requirements; C01-D14; all completed CORE-01 contracts/code/tests; this gate's ADR/contract/activation. Inspect Git before editing.

## REQUIREMENTS

GOV-001..005, CAP-010/014, NFR-002/003/005; C01-D14 bounded counts; CORE-01 catalog acceptance. No new technology decision.

## ARCHITECTURE RULES

Harness only, no production API; use existing owner-thread APIs; no timing threshold; no physical-hardware/performance claim; no global state; no new dependency. Existing targets preserved.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`. Standard public CI, existing Linux packages/Xvfb, no paid runner/secret/upload/release. ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

## ACCEPTANCE CRITERIA

- Exact allowlist; selector only `-14`.
- 200 headless, 100 window, 10,000 events, display/lifecycle, teardown all pass.
- Linux X11, Win32, Cocoa (or NOT_QUALIFIED) and Linux ASan/UBSan; existing 65 CTests regression.
- No physical-hardware/30+30/32-scenario/performance/ABI/release overclaim.
- Docs Validation + native CI PASS; no HIGH/CRITICAL; pt-BR audit.

## TESTS

Docs validators + unit tests + selector. Native: `ctest -R core01_soak_`, full preset on four jobs. Exact commands: `cmake --preset core01-internal-debug`, `cmake --build --preset core01-internal-debug`, `ctest --preset core01-internal-debug --output-on-failure`, plus asan preset.

## DELIVERABLES

Exactly: `tests/core/core01_soak_tests.cpp`, additive `CMakeLists.txt`, additive workflow path filters, `docs/evidence/NLE-PRPLAN-CORE-01-14.md`. GitHub PR, CI receipts, Evidence, pt-BR audit, proposed checkpoint.

## REVIEW FORMAT

Portuguese Brazil: base/head, exact files, counts/oracles, native evidence, sanitizer, no overclaim. Verdict APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, gate not merged, selector blocked, count mismatch, regression, CI red, HIGH/CRITICAL, out-of-allowlist, physical/performance/next-packet overclaim, destructive operation. Never bypass G2/force push.

## CONTEXT LOCK

Gate base `9bfbed5901947a3073b2910a48b4c9873702d37f`; activation pins ADR/contract/source blobs. Recompute fresh SHA-256 after gate merge.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-01-14.md` with PR/CI/audit/merge SHAs, counts, SOAK_OK, regression, sanitizer, limitations, rollback.
