# QA-01 — Future CI Build/Cache/Sanitizer Performance, Quality and R$0 Benchmark Protocol

**P00 DOCUMENTARY PROTOCOL ONLY, NOT MEASURED.** Work Order NLE-P00-WO-002-QA-01, research #341, future code #90 OPEN/BLOCKED. No C++ source, compiler jobs, SDK binaries, native application, actual CTest, CodeQL engine scan, sanitizer test or measured benchmark. This protocol must not be mistaken for a completed CI setup.

## Goal and source provenance
Measure reproducible native C++20 CI build, lint, test, static analysis and sanitizers under **R$0 public standard GitHub runners** with exact toolchain/image/artifact identifiers; detect performance/cost regressions, unsupported sanitizer and target capability, cache poisoning and zero-test green. Distinguish future QA-01 hosted compile/test evidence from QA-02 visual tests, QA-03 perf-lab, QA-04 supply chain, QA-05 physical device, PLAT-05 package and CORE-01 execution. Only formal QA-01 predecessor CORE-01.

## Proposed approved target matrix, not executed
| Matrix ID | Candidate host/target toolchain | Future acceptable output |
|---|---|---|
| CI-LNX-GCC | standard public `ubuntu-24.04`, GCC C++20, pinned CMake/Ninja/glibc | native headless CORE-01 build, unit/integration CTest nonzero, artifact and warning summary |
| CI-LNX-CLANG | same standard runner, LLVM Clang version pinned | alternate C++20 ABI/diagnostic, clang-tidy static, CodeQL mode compare |
| CI-LNX-ASAN | Ubuntu LLVM with ASan+UBSan instrumented | injected negative fixture, CTest, memory/time overhead and suppressed findings audit |
| CI-LNX-TSAN | Ubuntu LLVM TSan separate | data race fixture, high memory pressure and timeout, no production binaries |
| CI-LNX-MSAN | optional LLVM MSan when all deps instrumented | supported only with full controlled dependencies; otherwise UNSUPPORTED |
| CI-WIN-MSVC | standard `windows-2025`, MSVC Windows SDK pinned | native C++20 CORE-01 configure/build/link/CTest and Visual Studio compiler diagnostics |
| CI-WIN-CLANGCL | same standard Windows runner, clang-cl pinned | separate ABI/errors, ASan if actually available |
| CI-MAC-ARM | standard Apple Silicon `macos-26` / `xcode-27` if label exists | AppleClang arm64 CMake/Ninja, CTest and SDK/ABI; not physical Mac GPU evidence |
| CI-MAC-ASAN/TSAN | approved actual macOS runtime compatibility | sanitizer run or UNSUPPORTED, no blanket TSAN/MSAN guarantee |
| CI-MAC-INTEL | conditional `macos-26-intel` and physical Intel Mac test by PLAT-06 if owner approves | actual Intel x86_64 vs Rosetta separation, not mandatory QA-01 future gate without ratified release class |
| CI-WEB | pinned Emscripten LLVM wasm32 only after PLAT-03 approval | browser build smoke separate from native runtime and owner release class |
| CI-MOBILE | Android/iOS only if explicit owner Scope and cost selection | not included automatically in QA-01 formal DAG; no store submission |
| CI-DOCS | existing `docs-validation` Ubuntu docs check | Source Pack/relative links/catalog/blocked selector ONLY, cannot certify native compiler |

## Future measurement and receipt lock
- Each benchmark records exact Git base/head, source revision and raw SHA-256, CORE-01 approved contract and CMakePresets/CTestPresets hashes, toolchain compiler version/target triple/linker/SDK/sysroot and license, GitHub runner image version plus exact preinstalled software page, event trust source and token permissions.
- Record job runtime/cold vs warm from actual GitHub timestamps, checkout/bootstrap/configure/compile/link/CTest/static/sanitizer durations, peak memory/disk/output and IO bytes, cache restore/save bytes/hash/trust, artifacts logs/JUnit/SARIF SHA and 7-day proposed retention; no sensitive project files or tokens.
- Record actual public repository and runner SKU/price/plan, **compute free for public standard runners**, artifact and package/cache storage allocations/overage; if any action would incur nonzero R$ cost, mark BLOCKED and exclude it. No unchecked macOS larger-runner or self-hosted paid machine.
- Each compiler environment uses **actual** native C++20 source and a stable rights-cleared minimal CORE headless fixture when code exists. Use nonzero CTest count, actual skip/fail/xfail and original failure after retries. Build outputs can vary due to SDK/compiler: compare only identical pinned input/toolchain, and report different compiler builds as compatibility not bytewise reproducibility.
- Physical Windows/Linux/Mac hardware for GPU/UI/peripherals and Mac Intel native may require later QA-05/PLAT owner, never falsely certify from hosted ephemeral VM.

## Future benchmarks and oracles
| ID | Planned scenario | Raw evidence requirement |
|---|---|---|
| Q01-B01 | cold Linux GCC C++20 configure/build/test | per-stage wall+CPU/memory, source SHA, nonzero CTest |
| Q01-B02 | warm Linux GCC identical source and toolchain | cache hit/miss/compilation delta, source/flags identical |
| Q01-B03 | Linux Clang C++20 vs GCC | warning/ABI/CTest compatibility, not byte identical outputs |
| Q01-B04 | Windows MSVC debug build CTest | SDK/CRT and PE symbols, per-stage resource, actual native runner |
| Q01-B05 | Windows clang-cl alternate profile | compile error matrix, link runtime/ASan support |
| Q01-B06 | macOS Apple Silicon AppleClang arm64 build | Xcode SDK/image exact and CTest/ABI smoke, no physical GPU certification |
| Q01-B07 | clang-format / clang-tidy / clang Static Analyzer | findings/false positives and SARIF/JUnit validation against source |
| Q01-B08 | CodeQL none vs manual build when code exists | generated code coverage and cost/latency, public repo eligible |
| Q01-B09 | ASan/UBSan separate TSan with injected bug corpus | detection, CPU/RSS/time overhead and supported profile flags |
| Q01-B10 | MSan Linux fully instrumented optional | actual instrumented libs and initialized-memory fixture or UNSUPPORTED |
| Q01-B11 | cache poisoning and untrusted fork PR | restricted GITHUB_TOKEN, no CI secrets and code/caches integrity |
| Q01-B12 | Action/toolchain image drift | lock mismatch and typed STALE instead of green |
| Q01-B13 | no test/skip-all/timeout/cancel and flaky suite | fail aggregation and persisted first-failure JUnit |
| Q01-B14 | artifact/cache budget and manual concurrent PRs | actual 0-cost status, storage usage, bounded retention and fanout |
| Q01-B15 | branch rules/required checks when real jobs exist | status name stable, missing check blocked, no bypass/silent approval |
| Q01-B16 | full C++20 CI evidence and owner 1.0 release gate | per job source/SDK/CTest/sanitizer/SBOM handoff and DoD, no public release from CI alone |

## Statistics, comparison and security
- For cold/warm job timings, ≥5 independent runs per profile *after code exists* with raw per-stage durations, environment and cache state, median/p95 and valid uncertainty; never claim p99 from five run summary samples. For fast repeated CTest cases, use actual thousands of samples if p99 needed; QA-03 performance lab owns engine frame benchmarks.
- Separate compile time, config, CTest, CodeQL, sanitizer, upload, macOS VM startup, cache hit ratio; acknowledge toolchain and SDK drift. No absolute “fastest” compiler/runner without hardware and identical fixtures.
- Sample sensitivity: secrets/paths redacted; static analyzer outputs sanitized SARIF; GNU/LLVM/compiler licenses and build rights remain unresolved until owner source license; no private code/shared signing material in public logs.
- Report failure and unsupported explicitly: `COST_GUARD`, `SOURCE_STALE`, `TOOLCHAIN_MISMATCH`, `NO_TESTS_EXECUTED`, `SANITIZER_UNSUPPORTED`, `FLAKY`, `INFRA_FAIL`, `TIMED_OUT`, `CANCELED`, `SECURITY_BLOCKED`. Two successful doc CI runs do not make compiler tests PASS.
- Future `CiBenchmarkReceiptV1`: source SHA/critical hashes, actual run/job/attempt, image/OS/arch/SDK, toolchain lock, per-stage raw timing/CPU/RAM/bytes, cache namespace and integrity, test counts, sanitizer warnings, SARIF/output artifact hashes, GitHub billing/retention/cost quote and actual, scope/DoD/owner verdict.

[128 future tests](../testing/qa-01-acceptance-matrix.md) · [architecture](../architecture/qa-01-build-ci-orchestration.md) · [runner/license/cost matrix](qa-01-toolchain-runner-license-cost-matrix.md).
