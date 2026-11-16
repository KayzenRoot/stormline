# Evidence Bundle — NLE-P00-WO-002-QA-01 Build & CI Research

**2026-11-16 | P00 DOCUMENTARY ONLY | [research #341](https://github.com/KayzenRoot/stormline/issues/341) OPEN pending independently verified checkpoint | [future code #90](https://github.com/KayzenRoot/stormline/issues/90) OPEN/BLOCKED.** No Stormline engine code, CMake, native compiler test/benchmark, sanitizer, new CodeQL/Actions workflow, installed toolchain, artifact, SBOM or SLSA attestation.

## 1. Source Check PRE-WRITE OBSERVED from GitHub API
- Main requested SHA **9591ef730b3d0982f8370b7dfa29d58a0fbd288f**, **no open PR**, repo **public**, GitHub API **zero active rulesets** at baseline. Existing CI file [`.github/workflows/docs.yml`](../../.github/workflows/docs.yml) observed: `Docs Validation`, `pull_request` and `push/main`, `permissions contents: read`, Ubuntu runner, four steps Source Pack/links, catalog dependency DAG, registry, Zcode selector that rejects blocked WOs. **It does NOT compile C++/run unit tests/analyzers.**
- Source hierarchy actual checkpoint > Ledger/approved ADR > Scope > DoD > Architecture > Requirements. 80-module registry **71 researched, 9 pending, QA-01 ordinal 72 RESEARCH_PENDING, 80/80 implementation WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, all release_class UNDECIDED, engine_implemented=false**. No public MVP per NLE-D013; engine source license NLE-D009 OPEN.
- Formal sole prerequisite **CORE-01** from [ADR-0003](../adr/0003-core-01-platform-technology.md) PROPOSED and [lifecycle architecture](../architecture/core-01-platform-lifecycle.md) proposed C++20 SDL3 CMake Presets/Ninja only, NO native engine code. QA-02/03/04/05, PLAT-05, CI/AI owners are transitive; future QA-01 code issue #90 OPEN/BLOCKED. Next actual catalog QA-02 73/80, formal QA-01+GFX-03.
- Work Order [Context Lock](../work-orders/NLE-P00-WO-002-QA-01.md) has exact baseline **Git blob SHA-1 object IDs, not raw file SHA-256**. Future code actor must calculate raw SHA-256 and abort STALE source.

## 2. 2026 official research sources vs unverified runtime
- [GitHub billing](https://docs.github.com/en/billing/concepts/product-billing/github-actions): **public repository standard hosted runners free compute**; larger runners billed and shared artifact/package/cache storage may be charged after quotas, repository private change alters cost. **No future R$0 budget receipt or actual storage usage tested**, cost guard candidate.
- [Hosted runners](https://docs.github.com/en/actions/reference/runners/github-hosted-runners) Linux/Windows/macOS standard labels, Apple Silicon, optional Intel; [runner images](https://github.com/actions/runner-images) version tools change with updates, no toolchain pin guaranteed merely from `*-latest`.
- [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html) / [CTest CLI](https://cmake.org/cmake/help/latest/manual/ctest.1.html): future C++20 CMakePresets/CTestPresets/Ninja and positive unit count; **NO CMake compiled target or JUnit output exists**. C++ type diagnostics via compiler; no irrelevant TS typecheck.
- [LLVM ASan](https://clang.llvm.org/docs/AddressSanitizer.html), [TSan](https://clang.llvm.org/docs/ThreadSanitizer.html), [MSan](https://clang.llvm.org/docs/MemorySanitizer.html): OS/compiler/ABI restrictions, TSan separate high resource overhead, MSan Linux-only full instrumentation, no runtime passed.
- [Public CodeQL C++](https://docs.github.com/en/code-security/how-tos/find-and-fix-code-vulnerabilities/manage-your-configuration/codeql-for-compiled-languages) modes none/autobuild/manual differ generated-code coverage; **no CodeQL job configured/executed**.
- [GitHub secure pull_request_target](https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target), [cache isolation](https://docs.github.com/en/actions/concepts/workflows-and-actions/dependency-caching), [attestations](https://docs.github.com/en/actions/how-tos/secure-your-work/use-artifact-attestations), [branch rulesets](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/available-rules-for-rulesets) researched as security/cost candidate, **no workflow/ruleset/certificate update**.

## 3. EXACTLY eight new Markdown of this research PR
1. [Architecture](../architecture/qa-01-build-ci-orchestration.md).
2. [ADR-0075 PROPOSED](../adr/0075-qa-01-ci-matrix-security-policy.md).
3. [Technology/runner/license/cost/trust matrix](../research/qa-01-toolchain-runner-license-cost-matrix.md).
4. [Versioned CI plan and evidence semantic API](../contracts/qa-01-ci-evidence-api.md).
5. [128 future Q01-T001..Q01-T128 tests](../testing/qa-01-acceptance-matrix.md).
6. [Benchmark future protocol](../research/qa-01-ci-benchmark-protocol.md).
7. [This research Work Order](../work-orders/NLE-P00-WO-002-QA-01.md).
8. This Evidence Bundle.

## 4. Evidence and NOT proven
| Documentary fact/proposed contract | NOT demonstrated today |
|---|---|
| Github repo public, zero rulesets, existing Docs Validation only | no enforced branch protection/ruleset or native compilation |
| Core C++20/SDL3/CMake/CTest policy proposed, one formal dep CORE-01 | no compiler/SDK/real target/source or header, no C++ typecheck |
| Ubuntu/Windows/macOS standard runner and costs researched | no actual multi-OS build or R$0 actual storage/budget receipt |
| clang-format/tidy/cppcheck/CodeQL, sanitizers scoped per OS | no lints/static analysis/sanitizer TEST PASSES |
| Untrusted PR/cache/secret threat model, artifact and SBOM plan | no actual secret isolation tested/real artifact/SLSA signed/verified |
| 8×16 future acceptance cases | all Q01-T001..Q01-T128 FUTURE/NOT_EXECUTED |
| GitHub Docs Validation only | not same as native QA-01 CI or implemented engine |

## 5. Research PR exact-head CI/audit/merge PENDING until observed
Research branch `docs/NLE-P00-WO-002-QA-01-ci-research`, BASE **9591ef730b3d0982f8370b7dfa29d58a0fbd288f**. Research PR number/HEAD, changed statuses, actual Docs Validation run/job SUCCESS, objective independent audit in pt-BR and normal squash/readback must be observed and recorded later in checkpoint/history, not pre-claimed. Scope limited eight NEW Markdown, zero code/CI/registry/other issue changes. Documentary risk LOW, future runner/cache security STANDARD/ELEVATED, signing/private credentials/production release HIGH_ASSURANCE. No actual tests, costs or external services.

## 6. Independent checkpoint delta PROPOSAL, not self-promotion
After research exact-head Docs Validation SUCCESS, objective pt-BR audit APPROVED, normal squash/main readback, prepare independent **five MODIFIED files** checkpoint/backlog/registry JSON/this WO/Evidence with **only semantic registry QA-01 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`**, other 79 complete module objects and root fields identical. Expected **72/80 research documented (90%), 8 pending, ALL 80 future code WOs BLOCKED, executor_ready=0, approved_adr=0, release class UNDECIDED all, engine_implemented=false**; ADR-0075 stays PROPOSED and 128 tests FUTURE/NOT EXECUTED. Own Docs Validation/audit/normal squash/readback before research issue #341 CLOSED. Future code #90 remains OPEN/BLOCKED.
After checkpoint, separate **FOUR Markdown-only historical closeout** checkpoint/backlog/WO/Evidence, own exact-head Docs Validation, objective pt-BR audit, squash/main readback. Next real catalog **QA-02 Automated Functional & Visual Tests**, ordinal 73/80, formal QA-01+GFX-03, future code [#91](https://github.com/KayzenRoot/stormline/issues/91) OPEN/BLOCKED.
