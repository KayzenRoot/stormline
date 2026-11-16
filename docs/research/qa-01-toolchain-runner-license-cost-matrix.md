# QA-01 — 2026 CI Runner, Toolchain, License, Pricing and Supply-Chain Research

**2026-11-16 | P00 RESEARCH ONLY | [research #341](https://github.com/KayzenRoot/stormline/issues/341) | NLE-P00-WO-002-QA-01 | future code [#90](https://github.com/KayzenRoot/stormline/issues/90) OPEN/BLOCKED | source main `9591ef730b3d0982f8370b7dfa29d58a0fbd288f`.** Catalog ordinal 72/80, **CORE-01 sole formal dependency**, predecessor ADR-0003 PROPOSED. Baseline 71/80 researched, 9 pending, 80/80 coding WOs BLOCKED, 0 ready/approved ADR, all release classes UNDECIDED, engine_implemented=false, NLE-D009 engine license OPEN.


**Technology proposals, not installed, executed, tested or adopted.** The repository was confirmed public with *zero* GitHub rulesets and existing **docs-only** `.github/workflows/docs.yml`; no C++ engine build sources or tests. Reconfirm GitHub policies/pricing and runner images prior to approved code implementation, plus exact dependency tags/licenses/cost before running any new tool.

## Current GitHub pricing, runner and trust sources
| Decision point | Primary official source | Grounded 2026 engineering rule |
|---|---|---|
| Zero compute for public standard runners | [GitHub Actions billing](https://docs.github.com/en/billing/concepts/product-billing/github-actions) | **standard GitHub-hosted runner compute free for public repos**; larger runners billed even public, private repos quotas with overage, storage/artifacts/cache/package included limits and possible billing. GOV-003 R$0 requires cost/visibility/usage guard, not unconditional all-service free |
| Public standard runner choices | [GitHub-hosted runners reference](https://docs.github.com/en/actions/reference/runners/github-hosted-runners) | `ubuntu-24.04`, `windows-2025`, `macos-26` Apple Silicon M1, conditional `macos-26-intel` / `xcode-27` preview labels subject availability; runner architectures/memory/disk differ, no hardware GPU certification |
| Image toolchain drift | [GitHub runner images](https://github.com/actions/runner-images), [runner reference](https://docs.github.com/en/actions/reference/runners/github-hosted-runners) | software images updated weekly; record exact `Runner Image`, included software list, SDK compiler/stdlib version, do not claim OS label makes tool versions immutable |
| Untrusted pull_request_target | [GitHub secure trigger](https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target) | no `pull_request_target` privileged token coupled with checkout/run of fork code; no `workflow_run` ingest untrusted artifact as executable |
| Dependency cache security | [GitHub dependency caching](https://docs.github.com/en/actions/concepts/workflows-and-actions/dependency-caching) | caches are not verified code, default branch cache fork visibility and cache-poisoning; trust-scoped keys, digest verification, no secrets, PR cannot write protected main cache |
| Artifacts/provenance | [GitHub attestations](https://docs.github.com/en/actions/how-tos/secure-your-work/use-artifact-attestations), [artifact metadata](https://docs.github.com/en/actions/concepts/security/artifact-attestations) | OIDC-backed signed provenance only when actual artifact and privileged trusted build workflow; docs job does not emit provenance or SLSA evidence |
| Public CodeQL | [CodeQL for compiled languages](https://docs.github.com/en/code-security/how-tos/find-and-fix-code-vulnerabilities/manage-your-configuration/codeql-for-compiled-languages) | public repositories qualify for code scanning, C/C++ `none/autobuild/manual` differs generated-code completeness; exact CodeQL action/pin and output policy later |
| Repository rulesets | [Available rules for rulesets](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/available-rules-for-rulesets) | rule enforce PR/required checks/linear history; **actual GitHub API readback ZERO rulesets currently**, cannot assert enforced or change them in this docs-only WO |
| CMake cross/presets | [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html), [CTest CLI](https://cmake.org/cmake/help/latest/manual/ctest.1.html) | C++20 CMakePresets/TestPresets/Ninja native and cross; compiler/SDK source revisions, CTest JUnit and actual nonzero execution gating |
| Clang AddressSanitizer | [LLVM ASan](https://clang.llvm.org/docs/AddressSanitizer.html) | Linux, macOS, Windows supported with differing feature/runtime caveats; separate instrumented builds, not production shipped |
| Clang ThreadSanitizer | [LLVM TSan](https://clang.llvm.org/docs/ThreadSanitizer.html) | Linux/Darwin relevant supported platforms, high 5-15x CPU and 5-10x memory overhead, cannot pair with ASan same instrumented binary; 64-bit only, branch support dependent |
| Clang MemorySanitizer | [LLVM MSan](https://clang.llvm.org/docs/MemorySanitizer.html) | Linux/NetBSD/FreeBSD only; dependencies must be instrumented, NOT generic macOS/Windows gate |
| GitHub artifact storage | [GitHub billing and limits](https://docs.github.com/en/billing/concepts/product-billing/github-actions), [Actions limits](https://docs.github.com/en/actions/reference/limits) | Free public compute does not mean unlimited artifact/package storage or cache, enforce retention/digest and cost fail-closed |
| Hosted Mac runtime vs physical | [GitHub-hosted runners](https://docs.github.com/en/actions/reference/runners/github-hosted-runners), [CORE-01 prior research](../architecture/core-01-platform-lifecycle.md) | macOS Apple Silicon hosted supports compile/check, physical Retina/GPU/input/thermal and notarization require separate hardware/PLAT evidence |

## Candidate compiler, analyzer and license matrix (no adoption)
| Candidate | License/rights at exact pinned version (VERIFY) | Proposed role | Capability, constraints and cost |
|---|---|---|---|
| GCC/G++ on Ubuntu | GCC GPLv3+runtime/exception components, libstdc++ runtime exception, verify exact version and sysroot | Linux C++20 compile/codegen, debug/release | compatible glibc, ABI + flags and compiler diagnostics; zero cost in standard public runner |
| LLVM Clang/clang-cl/lld, clang-format, clang-tidy, clang static analyzer | Apache-2.0 WITH LLVM-exception for LLVM upstream, version/pack exact | C++20 alternate compilers, format/lint/SARIF/analysis, ASan/UBSan/TSan | LLVM installed version may drift on runner, pin toolchain/revision; compiler differs from AppleClang/MSVC |
| Windows MSVC/MSBuild + Windows SDK | Microsoft proprietary Visual Studio/Windows SDK license and redistribution terms, verify runner image and project use | Windows x64/optional ARM64 compile/link and type diagnostics, CRT | public standard Windows hosted cost zero compute; no supported/signed product from compile alone |
| Apple Xcode/AppleClang/macOS SDK | Apple proprietary developer SDK / installer/developer license | native Apple Silicon arm64 C++20, optional Intel x86_64 target builds | macOS VM may have Xcode27 preview or other pinned version, no guaranteed real GPU/macOS Intel machine test |
| CMake + CTest + CMake Presets | CMake BSD-3-Clause by source version | configure/build/test matrix, JUnit/CTest output | pin minimum CMake version, `CMakePresets.json` and CTest test name/counter, zero actual configs yet |
| Ninja build system | Apache-2.0 | fast deterministic C++ build backend | source code generated tools/ABI and incremental cache integrity, pin version and hash |
| clang-format | LLVM license | deterministic nonmutating style check | future `--dry-run --Werror` with pinned file selection/style config |
| clang-tidy | LLVM license | static warnings, selected C++ security/correctness check profile | `compile_commands.json` completeness and false positives, suppressions review |
| cppcheck | GPL-3.0-or-later family (verify exact version) | optional independent static analyzer | analyze tool redistribution/licensing vs source license, machine output and timeouts |
| Microsoft / Clang ASan | bundled compiler runtime/proprietary MSVC vs LLVM exceptions | Windows ASan test lane | runtime compatibility/unsupported features, time limits, not production |
| LLVM UBSan/ASan/TSan/MSan | LLVM runtime Apache-2.0 LLVM exceptions/other component notices | Linux Clang selected sanitizers and Mac ASan/TSan where supported | separate incompatible sanitizer variants, MSan dependencies instrumentation, 0-cost limits/time |
| CodeQL engine and CodeQL Action | GitHub service terms, action repository license and full SHA pin verify; public scans available | C/C++ source analysis, SARIF alerts | manual/autobuild/none coverage; cannot equate public CodeQL access with general free commercial security service |
| GitHub Actions hosted standard | GitHub service terms | public PR and main CI runners | public standard compute free; artifacts/caches/shared storage overage potentially paid; no larger runners |
| Third-party Actions like checkout/upload-artifact/cache | per-action license/release tags and full commit digest | secure checkout/evidence/cache | existing Docs `actions/checkout@v7` **not modified** here; pin future actions full SHA after verification |
| Python3 small validators/JUnit converters | Python PSF license, user scripts source license separate | docs/catalog/CI evidence checks | Python version preinstalled may vary, deterministic input and no sudo |
| SARIF 2.1.0, CTest JUnit XML, JSON schema | open interchange standards, libraries/tool licenses by exact tag | standard test/lint/code-scan outputs | validate against schema, redact secrets, test names, skip and clock source |
| SPDX 3.0, CycloneDX 1.7 generator | spec governance/open standards; scanner generator license by source tag | later QA-04/PLAT-05 SBOM inventory | formats are candidates; no license adoption or actual SBOM in docs-only |
| SLSA v1.2/in-toto/GitHub attestations | SLSA specifications and GitHub platform terms; signer/publisher permissions | future trusted supply-chain receipt | presence of metadata does not certify SLSA L3 or clean binaries |
| sccache/ccache cache compiler | Apache-2.0 for sccache, GPL3+ for ccache (verify exact tag) | optional compilation acceleration on trusted main | cache poisoning, filesystem/credential scope, isolate low-trust PR, R$0 artifact/cache caps |
| External Mac/self-hosted hardware | license/owner costs unknown | conditional physical Mac validation by QA-05 | NOT free by assumption; self-hosted on public PR highly sensitive and unapproved |
| Google/Apple store, signing/hosting | service licenses/account cost unknown | PLAT-05/BIZ-03 later only | no package sign, notarization or publication under QA-01 |

## Proposed zero-cost budget and failure triggers
- **Compute**: GitHub standard hosted public Ubuntu/Windows/macOS only with repository visibility readback. Explicitly prohibit large runners and paid GPU, paid actions, runner image purchases, vendor test cloud, package publishing/storage beyond included limits. If private/visibility changes, BLOCK for owner budget review.
- **Storage**: propose CI JUnit/SARIF/summary gzipped evidence small, retention **7 days for debug CI** (policy to approve and compare needs), no full build tree, SDK, cache or private PDB/DSYM publicly uploaded. SHA256 files/tar only after actual binary exists. Cache size/digest/eviction monitored against 10GB repo included cache and shared plan artifact limits; nonzero overage must never happen silently.
- **Concurrence**: bounded matrix 3 OS for approved basic C++20, nightly sanitizer only if justified cost and not before code; cancel superseded PR jobs without masking missing checks, timeout each job, log exact run outcome. Do not automatically run full expensive 80-module matrix.
- **Trigger**: untrusted PR builds use read-only token, no secrets/attest/write, trusted main future may produce test artifacts but not publish; release env gated by owner and QA-04/PLAT-05. No fork content executed under privileged base workflow; no self-hosted public PR.
- **Governance**: no current rule sets, required checks only after job names and reliability independently verified, no changes to docs.yml here. If CodeQL is introduced later, scan latency/cost/permission and private repo status re-evaluate. NLE-D013 blocks public MVP regardless of CI green.

## Threat model and negative proof requirements
| Threat | Future fail-closed oracle |
|---|---|
| Untrusted PR checks out fork under privileged `pull_request_target` | reject privileged PR execution; no secrets, immutable workflow trust source |
| `workflow_run` handles untrusted uploaded zip as executable | reject untrusted artifact side effects, input validation and explicit trust transfer |
| Cache key collision/poisoning from fork into protected main | trust-scoped cache keys, read-only low-trust main, validate digest before execute |
| Mutable Action tag updated maliciously | future 40-hex full SHA and source/license review; no unpinned external action |
| SDK/compiler auto-updates silently across runner images | fail toolchain lock or produce STALE new profile, no invisible green |
| Missing tests or all `SKIP` reported CI success | enforce selected expected test count, skipped/xfail thresholds and owner's exceptions |
| `continue-on-error` hides severe CTest/static-scan failure | aggregator fails required status and audit reads raw statuses |
| Runner fails network, timeout or cancellation but tests marked PASS | classify INFRA_FAIL/TIMEOUT/CANCELED separately, never PASS |
| Windows/Mac false sanitizer coverage | enforce actual compiler+runtime feature matrix; MSan Linux-only |
| Toolchain/install action asks for sudo/private key in fork PR | stop before execution, no root/privileged runner policy |
| ANSI/log content leaks local paths/tokens/user project data | secret scanning, redaction, artifact size limits, safe logs |
| Unauthenticated binary archive mistaken as verified build | SHA/digest verification, artifact provenance from trusted job, no code-sign claim |
| Public CI standard runner cost becomes paid due to repo change | guard visibility/runner SKU/storage plan, BLOCK not automatic spend |
| macOS hosted VM marked physical GPU/thermal evidence | classify VM/hosted runner, QA-05 hardware proof separate |
| Branch rules required check name points to nonexistent job | preflight names/CI before applying ruleset; do not change current zero rulesets |
| CodeQL scan only `none` misrepresented as complete coverage | identify generated code excluded; manual build path if needed |
| MSan partial instrumentation falsely green | require all dependent instrumented libs, explicit SKIP/UNSUPPORTED |
| ASan/TSan binary accidentally shipped | release packager excludes instrumentation, separate debug output identities |
| Flaky tests silently retried to green | store first-failure evidence/flaky classification and quarantine expiration |
| CI public Release action executes without owner DoD | impossible in PR; protected release actor under PLAT-05/BIZ-03 approval |

## Future evaluation method
Candidate scoring once code exists: 25% platform compile and ABI truth, 25% security/trust/cost, 20% test/sanitizer coverage and diagnostics, 15% build time/cache efficiency, 15% reproducibility/owner operational cost. No invented scores or compiler ABI equivalence currently. Source license NLE-D009 OPEN; product engine not built.

[Architecture](../architecture/qa-01-build-ci-orchestration.md) · [benchmark](qa-01-ci-benchmark-protocol.md) · [ADR-0075](../adr/0075-qa-01-ci-matrix-security-policy.md).
