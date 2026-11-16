# QA-01 — Exactly 128 FUTURE Build/CI Acceptance Tests (Q01-T001..Q01-T128)

**2026-11-16 | P00 DOCS ONLY | NO EXECUTABLE C++ or CI implementation.** Research [#341](https://github.com/KayzenRoot/stormline/issues/341) and future coding [#90](https://github.com/KayzenRoot/stormline/issues/90) OPEN/BLOCKED, source HEAD `9591ef730b3d0982f8370b7dfa29d58a0fbd288f`. Formal dependency **CORE-01 ONLY**, ADR-0003 and ADR-0075 PROPOSED, 80/80 future coding WOs BLOCKED. All **Q01-T001..Q01-T128 are unique, exactly 8 groups × 16, and FUTURE / NOT EXECUTED**; no test has passed or even been run.

## Future independent acceptance rules
1. Before code activation, actual CORE-01 owners/ADR approved, source hierarchy and baseline SHA256 Context Lock read, supported compiler/SDK/licenses and 1.0 release classes/DoD ratified; no CI implementation WOs automatically unlocked by documenting tests.
2. Actual GitHub Actions jobs on approved public standard runner Linux GCC/Clang, Windows MSVC/clang-cl, macOS AppleClang/native arm64 execute C++20 compile/link and CTest with expected nonzero test count. Floating runner label not compiler version lock; MSan and TSan coverage cannot be assumed across all OS.
3. Existing Docs Validation is independent of C++ jobs and does not demonstrate compiler/engine/game feature. Recorded source HEAD, runner image/SDK/ABI, logs, tested cases, JUnit/SARIF, artifact SHA and owner-approved policy determine PASS.
4. GitHub public standard runners' compute currently free per official policy; artifacts/cache/storage/paid larger runner or repo visibility can trigger costs. R$0 hard guard must account for all, never auto-spend or use privileged self-hosted public PR runner.
5. Untrusted PR `pull_request_target` and `workflow_run` risk, Actions pinned full SHA, cache poisoning, code signing secrets, public artifact uploads and branch ruleset names tested with intentional negative scenarios.
6. Sanitizer planned Linux ASan+UBSan and separate TSan, Windows/Mac ASan when supported, MSan Linux only with full instrumentation. Actual failure receipt required; unsupported means UNSUPPORTED, not success. QA-02 functional/visual and QA-04 specialized security remain separate ownership.
7. Actual provider/runner CI can be green but not certify physical GPU/thermal, macOS/Intel native machine, real source license or public app; no product build currently.
8. Every scenario requires actual future code and objective evidence; `NO_TESTS_EXECUTED`, infra fail, skip-all, flaky retries and over-budget conditions must block coding/release or explicitly remain not applicable only by approved owner/DoD.

## Group 1 — SOURCE-CONTEXT-TRUST

| Future ID | Objective future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q01-T001 | Source Pack and checkpoint SHA match approved Git BASE before any code CI | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T002 | Changed Scope/DoD/CORE-01 ADR marks CI context STALE | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T003 | PR from external fork receives GITHUB_TOKEN read-only scope | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T004 | Untrusted PR cannot read release OIDC or signing secrets | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T005 | pull_request_target never executes checked-out fork build scripts | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T006 | workflow_run downloaded untrusted artifact never auto-executes | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T007 | Action third-party reference pinned exact immutable full commit SHA | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T008 | Changing workflow Action SHA fails license/security provenance lock | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T009 | Runner job identifies exact source HEAD and merge ref semantics | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T010 | No C++ target exists yet gives NO_TESTS_EXECUTED not build PASS | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T011 | Expected code file/path allowlist prevents unintended release source modification | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T012 | Docs CI succeeds but does not promote engine_implemented or executor_ready | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T013 | Signed commits/rulesets not claimed when GitHub API finds zero active rulesets | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T014 | Required check name changed or missing fails gate instead of ignored | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T015 | CI step with continue-on-error on mandatory check fails aggregation | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |
| Q01-T016 | Manual bypass actor cannot silently approve HIGH or CRITICAL defect | GitHub exact SHA/source fingerprints, branch/fork token permissions, immutable workflow references and negative tests | FUTURE / NOT EXECUTED |

## Group 2 — LINUX-CXX-CMAKE-TEST

| Future ID | Objective future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q01-T017 | Ubuntu named runner image version/toolchain explicitly recorded | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T018 | C++20 GCC compiler build uses approved CMake configurePreset and Ninja | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T019 | Clang C++20 alternate build detects compiler-specific compatibility | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T020 | CMake detected CXX compiler ID/version and standard library ABI verified | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T021 | Host build architecture versus cross-compiled target distinguished | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T022 | Headless CORE-01 process compile startup without GPU/audio UI dependencies | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T023 | Linux CTest testPreset correctly selects build tree and test pattern | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T024 | CTest expected nonzero tests discovered/executed fail if none | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T025 | Linux unit test failure returns nonzero and stores JUnit failure | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T026 | Linux integration test with missing dependency returns BLOCKED not PASS | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T027 | C++20 strict language compile fails on unauthorized C++23 feature | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T028 | Link errors for missing SDL/CRT/GLIBC expected ABI fail closed | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T029 | Failing warning under approved -Werror policy returns typed error | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T030 | Linux debug and release configurations isolated by compiler/caches | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T031 | CTest timeout and signal termination not misclassified as success | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |
| Q01-T032 | Linux clean build without cache reproduces intended executable test outcome | actual pinned Ubuntu compiler/CMake/CTest native C++20 output, test count and JUnit, no GPU from hosted-only | FUTURE / NOT EXECUTED |

## Group 3 — WINDOWS-MSVC-CLANGCL

| Future ID | Objective future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q01-T033 | Windows named standard runner and MSVC toolset version recorded | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T034 | Windows SDK/CRT/redist dependency versions verified before build | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T035 | MSVC C++20 target configure/build/test using proper CMake preset | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T036 | clang-cl ABI and MSVC CRT configuration independently tested | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T037 | Windows x64 PE artifact arch and linked dependencies inspectable | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T038 | Optional Windows arm64 target only under approved SDK and device class | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T039 | Windows UTF-16 paths and unicode source test fixture compiles | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T040 | Windows long project paths with spaces handled safely by build commands | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T041 | Windows line-ending and source filename case collisions reported | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T042 | Windows CTest JUnit retains failed assertion and exit code | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T043 | Windows untrusted PR cannot invoke code signing or publish | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T044 | Windows static analysis selected warnings/CodeQL actual result documented | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T045 | Windows ASan only after compiler runtime support probe | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T046 | MSVC error code/warning differences mapped without blanket suppression | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T047 | Windows hosted build does not certify native GPU or signing trust | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |
| Q01-T048 | Windows mismatch between debug and release CRT/symbol mode rejected | actual Windows MSVC/clang-cl source/CRT/CMake CTest outputs and PE/WinSDK ABI metadata | FUTURE / NOT EXECUTED |

## Group 4 — MACOS-APPLECLANG-ABI

| Future ID | Objective future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q01-T049 | macOS named standard Apple Silicon runner image and Xcode pinned | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T050 | macOS Xcode27 Apple Silicon build host condition accurately checked | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T051 | AppleClang C++20 source and CMake/Ninja preset compile approved CORE | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T052 | macOS arm64 Mach-O artifact architecture actually inspected | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T053 | macOS Intel x86_64 conditional compile checked against proper SDK floor | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T054 | Intel hardware smoke not inferred from Apple Silicon Rosetta translation | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T055 | Universal2 nested Mach-O slice coverage only if owner approves | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T056 | macOS SDK and weak linking target compatibility diagnosed | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T057 | macOS libc++ ABI and SDL3 framework paths validate consistently | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T058 | macOS CTest headless target runs without window/audio/GPU | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T059 | macOS code-signing/notarization absent recorded NOT_EXECUTED | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T060 | macOS hosted runner not claimed real physical Metal/thermal evidence | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T061 | AppleClang ASan build/test works only under actual supported profile | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T062 | macOS TSan support probed not forced as generic universal requirement | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T063 | macOS test cancellation/runner shortage returns infra failure | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |
| Q01-T064 | macOS runner storage/image drift cannot silently upgrade compiler | actual named Apple Silicon macOS/AppleClang/Xcode toolchain and Mach-O, real hardware class separately | FUTURE / NOT EXECUTED |

## Group 5 — FORMAT-LINT-STATIC-CTEST

| Future ID | Objective future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q01-T065 | clang-format pinned version checks files without modifying working tree | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T066 | Formatter mismatch returns precise file/line and nonzero gate | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T067 | clang-tidy uses exact compile_commands for approved C++ targets | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T068 | clang-tidy warning baseline suppression requires justification and expiration | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T069 | cppcheck optional analyzer success requires exact policy and license pin | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T070 | Clang static analyzer reports findings independent of compiler warnings | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T071 | Public CodeQL C++ analysis configured in an actual code repository | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T072 | CodeQL none build mode generated-code limitations explicitly recorded | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T073 | CodeQL manual build mode database coverage compared when approved | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T074 | SARIF schema and issue severity reflect actual analyzer statuses | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T075 | C++20 type diagnostics originate from compile not fake TS typecheck | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T076 | Unit tests repeat with deterministic RNG/frozen fixtures and locale | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T077 | Expected tests failing skip-all or xfail-all cannot create green | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T078 | Flaky retry records original failure and owner quarantine decision | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T079 | CTest JUnit report SHA and runtime test IDs match run HEAD | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |
| Q01-T080 | QA-02 golden/audio/visual tests not falsely claimed by QA-01 unit checks | actual clang-format/clang-tidy/CodeQL/CMake/CTest/SARIF and deterministic fixture results from real code | FUTURE / NOT EXECUTED |

## Group 6 — SANITIZERS-COMPATIBILITY

| Future ID | Objective future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q01-T081 | Linux Clang ASan catches injected heap use-after-free test fixture | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T082 | Linux UBSan catches arithmetic/type undefined behavior when configured | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T083 | Linux ASan+UBSan combined lane actual runtime flags captured | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T084 | Linux TSan dedicated separate build catches a race fixture | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T085 | ASan and TSan incompatible runtime configurations never merged | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T086 | Linux TSan memory budget/timeout elevated overhead budget recorded | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T087 | MSan only Linux supported and full dependency instrumentation verified | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T088 | MSan cannot silently PASS on Windows or macOS unsupported hosts | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T089 | Windows MSVC/Clang ASan selected actual supported runtime profile | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T090 | macOS ASan selected supported AppleClang/Xcode runtime profile | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T091 | macOS TSan actual supported OS/runtime tested or UNSUPPORTED | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T092 | Sanitizer stderr/source lines preserved after redaction | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T093 | Invalid sanitizer flags fail and do not fall back uninstrumented | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T094 | Intentional sanitizer fixture missing detection flags gate fail | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T095 | Sanitizer instrumentation never packaged in public game executable | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |
| Q01-T096 | Sanitizer findings HIGH/CRITICAL block next implementation increment | actual LLVM sanitizer instrumentation compatibility and injected negative fixtures with resource limits | FUTURE / NOT EXECUTED |

## Group 7 — CACHE-RUNNER-COST-ROBUSTNESS

| Future ID | Objective future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q01-T097 | Public GitHub repository status checked before selecting free standard runner | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T098 | Private repo visibility change triggers COST_GUARD before compute | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T099 | Paid larger runner label rejected under R$0 hard rule | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T100 | Standard macOS label availability checked rather than assumed | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T101 | GitHub runner image changed compiler inventory detects lock drift | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T102 | Low-trust PR cannot poison protected branch cache namespace | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T103 | Restored cache digest mismatch discarded and clean build invoked | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T104 | Cache contains no private tokens/signing key/real user source | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T105 | Cache key includes OS/arch/toolchain/source/build flags/trust scope | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T106 | Artifact log and cache sizes stay within storage cost guard | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T107 | Artifact retention and compression minimize storage within plan | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T108 | macOS job concurrent fanout bounded and timeouts enforced | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T109 | Canceled superseded workflow never recorded test PASS | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T110 | Network/runner unavailable reports INFRA_FAIL distinct test regression | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T111 | Schedule/nightly does not run unsupported costly target accidentally | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |
| Q01-T112 | Self-hosted public PR runner with local network/credentials is denied | actual GitHub Actions standard runner/usage/cache trust cost receipts and fail-closed injection tests | FUTURE / NOT EXECUTED |

## Group 8 — EVIDENCE-SBOM-QUALITY-GATES

| Future ID | Objective future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q01-T113 | CI Evidence receipt captures base/head SHA workflow/run/job/attempt IDs | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T114 | Recorded toolchain versions compiler SDK linker Ninja CMake image exact | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T115 | Unit/CTest pass fail skip counts and artifact SHA tie to commit | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T116 | Static analyzer SARIF and sanitizer results have correct run origin | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T117 | Artifact digest verified after upload rather than trusting name alone | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T118 | Logs and SARIF redact credentials local private paths and tokens | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T119 | SBOM SPDX/CycloneDX only reported if actual generation+schema verification ran | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T120 | SLSA provenance only reported if trusted builder emits and verifies subject | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T121 | Attestation source/repo/commit/workflow identity validated independently | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T122 | SLSA L2/L3 never inferred merely from JSON or docs job | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T123 | Compile output on hosted runner not counted physical OS/GPU compatibility | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T124 | Future unit/build matrix must meet scope-specific DoD with no HIGH/CRITICAL | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T125 | CI quality gate reports CORRECTION REQUIRED on introduced regression | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T126 | Release/publish action refused before approved 1.0 DoD and license | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T127 | Future coding #90 remains BLOCKED pending ratified CORE-01 technology | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |
| Q01-T128 | Objective independent review updates checkpoint only after real evidence | actual immutable CI evidence, provenance/rights/source SHA, objective owner security & DoD audit | FUTURE / NOT EXECUTED |


## Catalog acceptance remains unverified
"CI verde em targets permitidos, builds e versões rastreáveis." All compiler/test/static/sanitizer jobs are hypothetical and absent from P00 code. **Docs Validation running in research PR is not QA-01 runtime CI.** No engine code, build or native export, no license approval or public MVP. All 80 code WOs BLOCKED, ADR-0075 PROPOSED.

[Architecture](../architecture/qa-01-build-ci-orchestration.md) · [benchmark](../research/qa-01-ci-benchmark-protocol.md) · [logical contract](../contracts/qa-01-ci-evidence-api.md).
