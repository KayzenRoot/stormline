# QA-01 — Proposed CI Plan, Build Matrix, Test and Evidence Semantic API v0.1

**2026-11-16 | P00 RESEARCH ONLY | [research #341](https://github.com/KayzenRoot/stormline/issues/341) | NLE-P00-WO-002-QA-01 | future code [#90](https://github.com/KayzenRoot/stormline/issues/90) OPEN/BLOCKED | source main `9591ef730b3d0982f8370b7dfa29d58a0fbd288f`.** Catalog ordinal 72/80, **CORE-01 sole formal dependency**, predecessor ADR-0003 PROPOSED. Baseline 71/80 researched, 9 pending, 80/80 coding WOs BLOCKED, 0 ready/approved ADR, all release classes UNDECIDED, engine_implemented=false, NLE-D009 engine license OPEN.


**Non-executable logical contract only.** No real CI/YAML workflow, CMake project, C++ classes, compiler, unit tests, binaries, release artifact, SARIF report or code coverage exists in current P00 research. Planned receipt fields are not observations.

## Exactly one formal predecessor
| Authority | Prior proposed contract | QA-01 output |
|---|---|---|
| **CORE-01 only** | [ADR-0003 C++20/SDL3/CMake+Ninja](../adr/0003-core-01-platform-technology.md), [platform lifecycle](../architecture/core-01-platform-lifecycle.md) | future checked C++20 compile/link, CTest lifecycle/headless smoke, OS/arch/compiler capabilities and real CI run evidence |

QA-02 automated functional/golden tests, QA-03 perf, QA-04 security, QA-05 physical device, PLAT-01/02/03/06 target, PLAT-05 package/SBOM, BIZ-03 release and CORE-06 metrics remain transitive/integration owners only; no new formal dependency edges.

## Proposed typed semantic contracts
| Entity | Proposed mandatory fields | Validation and failure |
|---|---|---|
| `CiSourceLockV1` | repo owner/name/ref, BASE/HEAD SHA, canonical source hierarchy fingerprint, critical Git blob OIDs and future raw SHA256, action/preset digest, expected owner-approved ADR | baseline mismatch => SOURCE_STALE before commands |
| `CiTrustContextV1` | event PR/internal/main/release, fork status, actor permission, workflow source ref, token scope, secrets presence = false for PR, cache trust tier | untrusted fork cannot use write/OIDC/sign/deploy |
| `CiTargetProfileV1` | host runner label/image SHA, target OS+arch+ABI/runtime, selected C++20 compiler/stdlib SDK, headless/GPU optional, release class, cost SKU | UNKNOWN/UNDECIDED => compiler code job blocked, not fake PASS |
| `CiToolchainLockV1` | compiler version SHA, linker, SDK/sysroot, Xcode/WinSDK/glibc, CMake/Ninja, clang format/tidy, CodeQL release and action full SHA | fail if runner image preinstalled tools mismatch lock |
| `CiMatrixPlanV1` | base/head commit, platform rows, approved job name, compiler config, test group, timeouts, cost policy, concurrency and trusted cache namespace | no costly runner or missing formally approved target |
| `CiCostPolicyV1` | R$0 goal, public repo flag, allowed standard runner labels, artifact/cache storage quotas & budget, timeout, retention, account billing visibility | repository private/paid SKU/storage overage => COST_GUARD |
| `CiBuildJobReceiptV1` | job ID/run attempt/workflow id/immutable HEAD, OS arch image version, toolchain, configure/build/link exit and logs, warning count, elapsed/bytes | no engine build receipt from Docs Validation |
| `CiCTestReceiptV1` | preset, expected/discovered/executed/pass/fail/skip/xfail counts, junit artifact SHA, fixture/clock/seed and timeout | zero tests executed or skip-all => NO_TESTS_EXECUTED |
| `CiStaticAnalysisReceiptV1` | clang-format/tidy/cppcheck/CodeQL exact config/hash/exec scope, findings by severity, SARIF URI/content digest, exclusions justification | unknown quality coverage not PASS |
| `CiSanitizerReceiptV1` | ASAN/UBSAN/TSAN/MSAN profile+compiler/runtime+OS, support matrix, instrumented code extent, test cases, stderr findings, terminal reason | unsupported => UNSUPPORTED, no invented PASS |
| `CiCacheReceiptV1` | trust namespace, key source/SDK/preset digest, owner, cache content SHA, hit/miss/eviction/bytes, validation status | untrusted or corrupt cache => discard, rebuild |
| `CiArtifactEvidenceV1` | artifact immutable hash, size, type CTestJUnit/SARIF/BinaryDebug/Summary, retention/privacy classification, permissions and source ref | no secrets/private paths, no signed release conflation |
| `CiAttestationHandoffV1` | actual verified release candidate artifact SHA, builder/ref/OIDC/subject and SPDX/SLSA verifiers result or NOT_APPLICABLE | QA-04/PLAT-05 own SBOM/provenance/release; docs workflow can't satisfy |
| `CiGateDecisionV1` | required target list, all job conclusions vs expected, flaky/skip/infra classifications, risks by severity, source/DoD owner approval, cost receipt | APPROVED only for actual mandated checks; no blanket code approve |
| `CiArchitectureErrorV1` | SOURCE_STALE, RUNNER_UNAVAILABLE, TOOLCHAIN_MISMATCH, CACHE_UNTRUSTED, TESTS_MISSING, FORMAT_FAIL, COMPILER_FAIL, STATIC_ANALYSIS_FAIL, SANITIZER_FINDING, TIMEOUT, CANCELED, COST_GUARD, UNAUTHORIZED_RELEASE | typed nonzero failure, no silent fallback or token leak |
| `CiBenchmarkReceiptV1` | source/runner/SDK images and actual job timing compile/link/CTest/cache, memory/io/network/log bytes, multiple raw samples p50/p95/p99 uncertainty | benchmark only from actual source+run, no invented measurements |

## Candidate procedure boundaries (NOT IMPLEMENTED)
| Operation | Proposed owner | Return/side effects |
|---|---|---|
| `inspect_ci_source(ref)` | QA-01 + governance | SourceLock or STALE, no code execution before |
| `classify_ci_trust(event)` | GitHub policy integration | TrustContext, least privileges |
| `resolve_ci_matrix(source, target)` | QA-01 CORE-01 | scoped MatrixPlan/COST_GUARD, no mobile by default |
| `pin_ci_toolchains(plan)` | QA-01 | Lock/TOOLCHAIN_MISMATCH |
| `verify_ci_cache(scope, key)` | QA-01 | usable verified cache or safe miss/rebuild |
| `run_ci_format_checks()` | QA-01 | non-mutating style receipt |
| `run_ci_compiler_preset()` | QA-01 | actual CMake configure/build/link receipt after code approved |
| `run_ci_ctest_preset()` | QA-01 | CTest JUnit counts incl zero/skip fail |
| `run_ci_static_analysis()` | QA-01; QA-04 deeper security | clang-tidy/SARIF/CodeQL report |
| `run_ci_sanitizer_suite()` | QA-01 | per-compatible-runtime result, unsupported explicit |
| `assemble_ci_evidence()` | QA-01 | immutable source/job/toolchain/test/log/status file hashes |
| `calculate_ci_cost_receipt()` | QA-01 budget | R$0 quote/actual or COST_GUARD, storage inspected |
| `audit_ci_gate()` | QA-01 + independent objective review | APPROVED/CORRECTION REQUIRED/BLOCKED for actual evidence |
| `request_release_attestation()` | QA-04 + PLAT-05 future trusted release job only | signed/verified subject digest OR NOT_PERMITTED |
| `deploy_engine_release()` | BIZ-03 only | **not part QA-01 and not permitted during P00** |

## Core invariants and future acceptance gates
- **`docs-validation SUCCESS` is documentary evidence only**, cannot be renamed/mapped to engine C++ compile, clang-tidy or sanitizer. All claims require explicit executable tests and actual runner/result.
- Free compute on public standard GitHub-hosted is conditional; artifact/cache/shared storage/cost budget independently checked. Rule/safety changes to repo requires separate approved WO, not sneaked into docs research.
- C++20 compiler diagnostics are meaningful type/semantic check. Not an independent `tsc` job by default. `compile_commands.json` for lint static coverage must reflect exact target, no silently skipped C++ generated sources.
- Use CTest actual *nonzero* executed suite and inspect skip/xfail; filter/order/run attempts deterministic, failure and cancellation explicit. Sanitizers unsupported profile not PASS; all untrusted tokens/cache/artifacts fail closed.
- CI jobs must not access private tokens/signing keys or automatically publish. SLSA attestation only actual trusted release subject and verifier, never self-labeled. No public engine release until full owner DoD and license resolution. QA-01 does not own desktop GPU hardware confirmation nor QA-02 golden test design.
- No implementation approved now; future 128 acceptance cases remain UNEXECUTED, all 80 code WOs BLOCKED, ADR-0075 PROPOSED.

[Architecture](../architecture/qa-01-build-ci-orchestration.md) · [128 future cases](../testing/qa-01-acceptance-matrix.md) · [ADR](../adr/0075-qa-01-ci-matrix-security-policy.md).
