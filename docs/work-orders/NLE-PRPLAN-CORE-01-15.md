# NLE-PRPLAN-CORE-01-15 — Integrated CI qualification (QUALIFICATION)

**STATUS: EXECUTOR_READY ONLY AFTER THE GATE PR PASSES DOCS VALIDATION, PT-BR AUDIT AND SQUASH MERGE.** **Gate:** G6 individual. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-15`. **Predecessor:** `-14` `COMPLETED` via PR #459. **Issue:** #18. **Base:** `ee7f3188eee314b7f051ef39ce4c88ab74492fb1`. **ADR:** [ADR-0094](../adr/0094-core-01-integrated-ci-qualification.md). **Contract:** [core-01-integrated-qualification-v0](../contracts/core-01-integrated-qualification-v0.md).

## OBJECTIVE

Implement an integrated CI qualification harness over CORE-01 components: 200 headless cycles, 10 SDL init/quit+window cycles, 25 extra window cycles, 10,000 events, display/capability/lifecycle and zero-live-resource teardown.

## CONTEXT

`-03`..`-14` are completed. C01-D09/C01-D14 require integrated boot/teardown and bounded soak proof. This packet is the CI qualification only; physical hardware, 30+30 timing, 32 scenarios, long soak, Wayland runtime, security clearance, ABI and release remain NOT_QUALIFIED.

## SCOPE

- `core01_qualification_test` with QUAL-01..QUAL-06 counts/oracles.
- Headless resource counters via test instrumentation; zero live resources.
- Linux X11/Xvfb, Win32, Cocoa or NOT_QUALIFIED; Linux ASan/UBSan; existing 66 CTests regression.
- Evidence Bundle.

## OUT OF SCOPE

Physical hardware certification, 30+30 timing, p95/p99/RSS/FPS, 32 scenarios, long-duration soak, OS suspend/resume, Wayland runtime, IME/DPI/hotplug, security clearance, public ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`; checkpoint; ADRs 0003/0075/0083..0094; Scope/DoD/Architecture/Requirements; C01-D09/D14; completed contracts/code/tests; gate ADR/contract/activation. Inspect Git.

## REQUIREMENTS

GOV-001..005, CAP-010/014, NFR-002/003/005; C01-D09/D14 bounded; CORE-01 acceptance. No new technology decision.

## ARCHITECTURE RULES

Harness only; use existing internal APIs and test instrumentation; no production API/global state; no timing threshold; no physical/security/release claim; existing targets preserved.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`. Standard public CI, existing packages/Xvfb; no paid runner/secret/upload/release. ADR-0003/0075 `PROPOSED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; `engine_implemented=false`.

## ACCEPTANCE CRITERIA

- Exact allowlist; selector only `-15`.
- 200/10+1/25/10,000 counts; zero live headless resources; display/video/lifecycle; `CORE01_QUALIFICATION_OK`.
- Linux/Windows/macOS or NOT_QUALIFIED; Linux ASan/UBSan; existing 66 CTests.
- No physical/security/performance/32-scenario/ABI/release overclaim.
- Docs Validation + native CI PASS; no HIGH/CRITICAL; pt-BR audit.

## TESTS

Docs validators + selector. Native: `ctest -R core01_qualification_`, full preset four jobs. Exact commands: `cmake --preset core01-internal-debug`, `cmake --build --preset core01-internal-debug`, `ctest --preset core01-internal-debug --output-on-failure`, plus asan preset.

## DELIVERABLES

Exactly: `tests/core/core01_qualification_tests.cpp`, additive `CMakeLists.txt`, additive workflow filters, `docs/evidence/NLE-PRPLAN-CORE-01-15.md`. PR, CI, Evidence, pt-BR audit, proposed checkpoint.

## REVIEW FORMAT

Portuguese Brazil: base/head, files, counts/resources, native/sanitizer evidence, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, gate not merged, selector blocked, count/resource mismatch, regression, CI red, HIGH/CRITICAL, out-of-allowlist, physical/security/performance/next packet overclaim, destructive operation. Never bypass G2/force push.

## CONTEXT LOCK

Gate base `ee7f3188eee314b7f051ef39ce4c88ab74492fb1`; activation pins ADR/contract/source blobs. Recompute fresh SHA-256 after gate merge.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-01-15.md` with PR/CI/audit/merge SHAs, counts, resource counters, regression, sanitizer, limitations, rollback.
