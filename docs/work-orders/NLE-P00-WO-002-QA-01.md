# NLE-P00-WO-002-QA-01 — Cross-Platform C++20 Build & CI Research Work Order

**2026-11-16 | P00 DOCUMENTARY RESEARCH ONLY | [research issue #341](https://github.com/KayzenRoot/stormline/issues/341) OPEN pending independent checkpoint | [future coding #90](https://github.com/KayzenRoot/stormline/issues/90) OPEN/BLOCKED | BASE main `9591ef730b3d0982f8370b7dfa29d58a0fbd288f`.** Documentary risk LOW, future build runners/security and native ABI STANDARD/ELEVATED, signing/release/publishing and privileged execution HIGH_ASSURANCE.

## OBJECTIVE
Research real 2026 GitHub Actions Free public standard hosted Ubuntu/Windows/macOS runner plans and cost limits, C++20 native compiler/toolchain/SDK compatibility under CORE-01, CMake+Ninja/CTest Presets, reliable unit and integration CTest, format/lint/type diagnostics/static CodeQL, sanitizer matrix, cache and PR fork/OIDC trust, evidence/artifacts/provenance/SBOM integration, reproducible diagnostics, affordable CI time/bytes, GitHub rulesets and versioned contracts. Produce eight NEW markdown P00 artifacts and exactly 128 future acceptance tests without creating/modifying native engine code or CI workflow. Catalog acceptance **"CI verde em targets permitidos, builds e versões rastreáveis"**, **NOT demonstrated by existing docs CI**.

## CONTEXT + SOURCE CHECK
Hierarchy checkpoint > Ledger/approved ADR > Scope > Definition of Done > Architecture > Requirements > remaining, AGENTS contract. GitHub main exact requested **9591ef730b3d0982f8370b7dfa29d58a0fbd288f**, no open PRs, **public repository** and **zero observed rulesets**. Only existing workflow `.github/workflows/docs.yml` **Docs Validation** PR+main, ubuntu-latest, Source Pack/local links, module DAG, 80 WO registry, blocked selector; no C++ compiler/test suite or CodeQL workflow. Registry **80 total, 71 researched, 9 pending, QA-01 72/80 RESEARCH_PENDING, all 80/80 coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release class UNDECIDED all, engine_implemented=false**. Owner GOV-003 R$0 CI, NLE-D013 no public MVP before full 1.0 DoD, NLE-D009 source license OPEN, NLE-D014 2D/2.5D/3D/Web, NLE-D017 Windows/Linux/macOS Editor/game exports, NLE-D018 safe autonomy not fees/security bypass, NLE-D019/020 blocked future WOs. Formal dependency **CORE-01 ONLY**, predecessor [ADR-0003](../adr/0003-core-01-platform-technology.md) C++20/SDL3/CMake Presets+Ninja PROPOSED, not built/approved. QA-02/03/04/05, PLAT-05, BIZ-03, CORE-06, GFX/GAME etc are **integration owners not additional formal DAG edges**. Next catalog QA-02 order 73 deps QA-01+GFX-03, future issue #91 OPEN/BLOCKED.

## CONTEXT LOCK — Git blob SHA-1 OIDs, not raw-file SHA-256
The following are real Git blob object IDs from the exact BASE readback. They are **not byte-level SHA-256 digests** and must not be described as such. Before any future implementation, calculate raw content SHA-256 and compare source/branch with Context Lock. If checkpoint, Ledger approved ADR, Scope, DoD, Architecture, Requirements, catalog/registry, CORE-01 predecessor or CI workflow changes, mark STALE and stop until recompiled.
- `AGENTS.md` — `3e57b719f8651407879ebb641707a048773ea4c2`
- `docs/00-source-hierarchy.md` — `58a377bc76cafdd3377d733d4f30ef53661bb034`
- `docs/11-checkpoint.md` — `67eae12e6f41e22808f3e813a4a33742fd94612c`
- `docs/10-decisions-ledger.md` — `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md` — `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md` — `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md` — `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md` — `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/product/module-catalog.md` — `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- `docs/queue/implementation-registry.json` — `5de2c1ac27ca7d4a5051a78daed7bd0c5f501448`
- `docs/queue/work-orders/QA-01.md` — `fbebfc64b60276228f5ce8bd16bc5792a06c3aa6`
- `docs/adr/0003-core-01-platform-technology.md` — `2ee92dda5ab81ddcc446b9d5325d29257350e217`
- `docs/architecture/core-01-platform-lifecycle.md` — `11c7ec4125f40cf0172aa552a1e9835e84d2c172`
- `.github/workflows/docs.yml` — `cbbaf5731de75f1de4bdf8cad6489e6d73681d71`

## SCOPE — exactly eight NEW Markdown, NECESSARY
1. [Architecture](../architecture/qa-01-build-ci-orchestration.md).
2. [ADR-0075 PROPOSED](../adr/0075-qa-01-ci-matrix-security-policy.md).
3. [2026 toolchain/runner/licenses/cost/security matrix](../research/qa-01-toolchain-runner-license-cost-matrix.md).
4. [Versioned CI evidence/plan semantic API](../contracts/qa-01-ci-evidence-api.md).
5. [128 future Q01-T001..Q01-T128 acceptance tests](../testing/qa-01-acceptance-matrix.md).
6. [Future CI benchmark and cost measurement protocol](../research/qa-01-ci-benchmark-protocol.md).
7. This Work Order.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-QA-01.md).

All eight ADDED .md only in research PR; no modifications to existing source/docs, registry/checkpoint/backlog, `.github/workflows/docs.yml`, actions, rulesets, source code or future coding issue.

## OUT OF SCOPE
No C++ engine CMakeLists or headers, .github workflow YAML changes, CMakePresets creation, Linux GCC/Clang compiled targets, actual Windows MSVC/macOS AppleClang binary, sanitizers, CodeQL workflows enabled, artifact upload, new protected branch ruleset or required checks, real cache, private/paid runner or developer account, off-branch/Git history destructive changes, version 1.0 public release or mobile app CI, formal QA-02/QA-04 tests implementation, forced toolchain/SDK/license/security decisions.

## FILES/SOURCES TO READ
All Context Lock OIDs and Git paths above; original source hierarchy, CORE-01 ADR-0003 + lifecycle, catalog/queue, NLE-D013..020, proposed QA-01 code issue #90, next QA-02 for catalog position. Current [GitHub Actions billing](https://docs.github.com/en/billing/concepts/product-billing/github-actions), [GitHub runner reference](https://docs.github.com/en/actions/reference/runners/github-hosted-runners), [runner images](https://github.com/actions/runner-images), [cache security](https://docs.github.com/en/actions/concepts/workflows-and-actions/dependency-caching), [secure pull_request_target](https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target), [public CodeQL C++](https://docs.github.com/en/code-security/how-tos/find-and-fix-code-vulnerabilities/manage-your-configuration/codeql-for-compiled-languages), [CMake toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html), [CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html), [LLVM ASan](https://clang.llvm.org/docs/AddressSanitizer.html), [TSan](https://clang.llvm.org/docs/ThreadSanitizer.html), [MSan](https://clang.llvm.org/docs/MemorySanitizer.html), [GitHub attestations](https://docs.github.com/en/actions/how-tos/secure-your-work/use-artifact-attestations) and [ruleset controls](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/available-rules-for-rulesets).

## REQUIREMENTS
GOV-001..005, R$0 public CI, no CodeRabbit/paid tool or external mandatory reviewer, owner safety/permission gates. Later C++20 native CORE-01 build/CTest semantics on selected Windows/Linux/macOS and headless without GPU. Compile/type diagnostics real, format and static analysis, compatible sanitizers, verified artifact hashes and evidence/CI. No automatic releases. QA-01 formal CORE-01 only, no platform dependency expansion.

## ARCHITECTURE RULES
- Future native C++20 CMake Presets + Ninja and CTest Presets with actual nonzero fixture tests, OS compiler/SDK pinned, CODE/runner image source fingerprint, host-vs-target ABI and applicable compile flags; `CMAKE_CXX_STANDARD=20` no implicit C++23.
- Linux GCC+Clang, Windows MSVC+clang-cl, macOS AppleClang/Apple Silicon pinned Xcode; conditional Apple Intel if supported owner. Ubuntu/Windows/macOS **standard GitHub public hosted** only subject availability/cost. Runner images update weekly, collect exact immutable versions; repo public currently but cost needs storage and overage checks, private/large runner refused.
- Format pinned clang-format, clang-tidy/Clang Static Analyzer/CodeQL public C++ capability, warnings-as-errors and unit/CTest JUnit; no faux separate TS "typecheck" for C++, C++ semantic checking via compiler. QA-02 owns golden functional/visual, QA-04 specialized security, QA-05 physical hardware, PLAT-05 packaging.
- Linux Clang ASan+UBSan and separate TSan lane; MSan only Linux when full deps instrumented; Windows/macOS ASan/TSan only with real runtime support and resources, no MSan universal and no instrumented shipping binaries.
- Trust: untrusted fork PR token read-only/no secrets, no `pull_request_target` untrusted code under elevated token or `workflow_run` artifact execution; pinned full action SHA future, cache integrity and trust separation, no self-hosted public PR privileged runner. Existing Docs workflow unchanged in P00.
- Actual CI receipts/source SHA/runner image/compile commands/CTest count/SARIF/security findings/cache bytes/cost and artifacts. Docs green NOT native C++ green. GitHub currently **zero rulesets**; future required checks only after actual stable job names, separate approved WO.
- SBOM/SPDX/CycloneDX/SLSA provenance integration owners QA-04/PLAT-05; no claimed SLSA grade or GitHub attestation without real trusted build. NLE-D009 license OPEN and owner NLE-D013 no public MVP.

## CONSTRAINTS
LOW documentary scope, no paid runners/CodeRabbit, no admin secrets/action/ruleset changes, no Git history rewrite/force push. Source drift -> STALE; HIGH/CRITICAL blocks progression, no early unlock. ELEVATED/HIGH_ASSURANCE future activity separate; no false claim test/engine ready.

## ACCEPTANCE CRITERIA
- [ ] Research PR exactly **eight ADDED Markdown** only, proper relative links, no code/.github/workflows/CI edit, source files/registry/checkpoint unaffected.
- [ ] ADR-0075 **PROPOSED**, CORE-01 **single formal DAG prerequisite**, C++20/SDL3/CMake+Ninja baseline only proposed.
- [ ] Deep official 2026 OS runners/pricing/R$0 storage, image drift, C++ compiler/SDK ABI, CTest/lint/CodeQL/static/SARIF, sanitizer limitations, fork/cache trust and ruleset requirements, cost and privacy without invented future results.
- [ ] Exactly **128 unique Q01-T001..Q01-T128**, eight groups x16 all FUTURE/NOT EXECUTED, benchmark explicit future, no false C++ build pass.
- [ ] Research exact-head GitHub Docs Validation SUCCESS, objective pt-BR audit APPROVED, normal squash/main readback.
- [ ] Independent checkpoint PR exactly **5 MODIFIED files** docs/11-checkpoint.md, docs/08-backlog.md, registry JSON, this WO, Evidence. Sole semantic registry QA-01 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, all 79 other module objects and root flags identical. Target **72/80 research (90%), 8 pending, 80/80 coding WOs BLOCKED, 0 ready, 0 approved_adr, all release_class UNDECIDED, engine=false**, ADR-0075 remains PROPOSED and tests FUTURE.
- [ ] Checkpoint own Docs Validation, objective pt-BR audit, squash, main readback **before** closing research #341; code issue #90 remains OPEN/BLOCKED.
- [ ] Final separate **four Markdown** history PR checkpoint/backlog/WO/Evidence, own Docs Validation/audit/squash/main readback. Next REAL catalog **QA-02 Automated Functional & Visual Tests**, ordinal 73/80, formal QA-01+GFX-03, code issue #91 blocked.

## TESTS
P00 only GitHub existing Docs Validation (Source Pack & links, module catalog DAG, 80 WO registry, Zcode selector rejection), PR change file statuses, test ID uniqueness, later JSON sole semantic delta and audit/merge SHA. **All Q01 tests FUTURE/NOT EXECUTED; no C++ compiler/CTest/analyzer/sanitizer/CodeQL/new Actions workflow or code coverage actually ran**. Future code test plan explicitly calls supported OS/compiler/SDK pinned exact version, compiler correctness, unit and relevant integration, static/SARIF, real supported sanitizer separate lanes, trust negative tests, costs and artifact provenance.

## DELIVERABLES
Research issue #341, 8 Markdown with Work Order/ADR/Evidence and 128 future tests, research CI and objective review links/readback, independent checkpoint and issue closure only after own evidence, separate historical closeout own evidence, next module CTA. No executor coding release.

## REVIEW FORMAT
Português brasileiro, base/head/changed files and blob/source fingerprints, catalog DAG and approved owner decisions, compiler matrix/cost/security/trust and evidence truth, exact Docs CI run/job, test count/status, separate 128 NOT_EXECUTED, vulnerabilities and risk, checkpoint delta and verdict **APPROVED / CORRECTION REQUIRED / BLOCKED**. Never approve code based on docs.

## STOP CONDITION
STALE critical source, changed approved decision, wrong formal dep/8 Markdown/128 IDs, CI fail, secret/cost/security/ruleset change, public unapproved release, HIGH/CRITICAL or missing evidence -> BLOCKED or CORRECTION REQUIRED same WO/PR, no next module or implementation unlock until resolved.

## CHECKPOINT DELTA (PROPOSAL ONLY)
After research exact-head CI/audit/squash/readback, independent five-file checkpoint with ONLY QA-01 research_status registry delta; own CI/audit/squash/readback then close research #341, future code #90 OPEN/BLOCKED. Final independent four-Markdown factual history own CI/audit/squash/readback, next QA-02. No new CI tool is installed in P00.


## Research PR #342 results and independent checkpoint proposal
- [Research PR #342](https://github.com/KayzenRoot/stormline/pull/342): BASE `9591ef730b3d0982f8370b7dfa29d58a0fbd288f`, HEAD `dfc1d45dd7979253f8da855ce80c1ac5315a4721`, **exactly EIGHT ADDED Markdown** (architecture, ADR-0075 PROPOSED, runner/toolchain/licenses/cost, typed CI API, 128 Q01 future tests, benchmark protocol, WO, Evidence). [Docs Validation run #43797331139](https://github.com/KayzenRoot/stormline/actions/runs/43797331139) **SUCCESS** job #133069011014, all steps Source Pack/local links, DAG, registry, Zcode selector rejecting all future blocked code packets. [Objective pt-BR audit #6906327226](https://github.com/KayzenRoot/stormline/pull/342#issuecomment-6906327226) **APPROVED documentary**; normal squash/main readback `6d348f02ad08e46e3c39d6a6d4128c5d45dec8a2`. Research merge left registry at 71/80.
- Independent checkpoint proposed **SOLE semantic registry QA-01 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`**, all other 79 module objects and root fields unchanged. Target main **72/80 researches documented (90%), 8 pending, ALL 80/80 future coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, all release classes UNDECIDED, engine_implemented=false**. Formal DAG **CORE-01 ONLY**, predecessor ADR-0003 PROPOSED; ADR-0075 PROPOSED; source license NLE-D009 OPEN; Q01-T001..Q01-T128 FUTURE/NOT EXECUTED. No C++ engine compile, native build, CMake, compiler-lint/static/CodeQL/sanitizer job, signed artifact, SBOM/SLSA, R$0 actual future storage budget or protected ruleset. GitHub Source Check observed **public repo, zero rulesets, single docs-only workflow**, so no claim C++ CI is green.
- [Research issue #341](https://github.com/KayzenRoot/stormline/issues/341) must stay OPEN until independent checkpoint CI/audit/squash/readback; future coding [#90](https://github.com/KayzenRoot/stormline/issues/90) stays OPEN/BLOCKED. After checkpoint proof only close research #341, then separate historical PR exactly **four Markdown** (checkpoint, backlog, WO, Evidence), its own Docs CI/audit/squash/readback. Next actual catalog **QA-02 Automated Functional & Visual Tests** 73/80 formal **QA-01 + GFX-03**, future code [#91](https://github.com/KayzenRoot/stormline/issues/91) OPEN/BLOCKED.
- Full source/context contract remains unchanged and future C++ code #90 BLOCKED; this checkpoint requires its own CI/audit/merge/readback.
