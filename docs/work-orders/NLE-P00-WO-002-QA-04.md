# NLE-P00-WO-002-QA-04 — Security, Fuzzing & Supply Chain: Research Work Order

**2026-11-16 | P00 DOCUMENTARY RESEARCH ONLY | [research #353](https://github.com/KayzenRoot/stormline/issues/353) OPEN pending independently verified checkpoint | future code [#93](https://github.com/KayzenRoot/stormline/issues/93) OPEN/BLOCKED | BASE main `04f9ff54875b46fad05941529e1c6719fe79c394`.** Catalog QA-04 order 75/80, **FORMAL dependencies QA-01 + NET-06 + AI-06 ONLY**, prior ADR-0075/0052/0065 PROPOSED. Baseline 74/80 researched 6 pending, all 80 coding WOs BLOCKED, zero ready/approved ADR, releases UNDECIDED all, engine=false, NLE-D009 license OPEN.


**Documentary risk LOW**, future C++ parser/security scanner STANDARD/ELEVATED, sensitive agent/network enforcement, signing/recovery/privileged operations **HIGH_ASSURANCE**.

## OBJECTIVE
Deep research source-backed 2026 threat model for native C++20 project/scene/asset/font/shader/audio/network parsers and script/plugin sandbox, memory/thread faults, libFuzzer/ASan+UBSan/AFL++ fuzz campaigns and reproducer triage, CodeQL/clang-tidy/SAST/DAST coverage, CVE/GHSA/OSV/SCA, SBOM SPDX-3.0.1/CycloneDX-1.7, SLSA-1.2 provenance and actual trusted release artifact verification, licensing/NOTICE, secrets and untrusted GitHub Actions/caches, AI-06 grants and NET-06 authority, risk HIGH/CRITICAL release stop, incidents and rollback with R$0 target and verifiable evidence. **No code, real scanner or security certification**.

## CONTEXT/SOURCE CHECK
Authoritative precedence checkpoint > Decisions Ledger/approved ADR > Scope > DoD > Architecture > Requirements > other. Requested GitHub main HEAD **04f9ff54875b46fad05941529e1c6719fe79c394** matched, no open PR, public repo, `main protected=false`, **zero current GitHub repository rulesets** via API, existing docs-only `.github/workflows/docs.yml` with `actions/checkout@v7` major mutable tag, no CodeQL or native fuzz/engine build. QA-04 #75/80 RESEARCH_PENDING with 74 researched and 6 pending, all 80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, 0 ready/approved ADR, release classes UNDECIDED, engine_implemented=false; NLE-D009 license OPEN, NLE-D013 no public MVP, D014 2D/2.5D/3D/Web, D017 Windows/Linux/macOS desktop Editor and exports required, D018 routine docs autonomy not money/admin/bypass, D019/020 implementation queue blocked. Formal deps **EXACT QA-01 + NET-06 + AI-06**, predecessor [QA-01 ADR-0075](../adr/0075-qa-01-ci-matrix-security-policy.md), [NET-06 ADR-0052](../adr/0052-net-06-defense-in-depth-authority-quotas-privacy.md) and [AI-06 ADR-0065](../adr/0065-ai-06-agent-grant-consent-policy.md) **PROPOSED**. Future code issue #93 OPEN/BLOCKED; next QA-05 #76/80 formal QA-02+PLAT-05, future code #94 OPEN/BLOCKED.

## CONTEXT LOCK — observed Git blob OIDs, not raw SHA-256
Base main SHA `04f9ff54875b46fad05941529e1c6719fe79c394`. These are immutable **Git blob SHA-1 IDs**, not SHA-256 of raw bytes; future executor must calculate raw SHA-256 before modification. Any checkpoint/approved Ledger/Scope/DoD/Architecture/Requirements/catalog/registry or QA-01/NET-06/AI-06 contract/source fingerprint changes mark **STALE** and force rebase/recompile.
- `AGENTS.md`: `3e57b719f8651407879ebb641707a048773ea4c2`
- `docs/00-source-hierarchy.md`: `58a377bc76cafdd3377d733d4f30ef53661bb034`
- `docs/11-checkpoint.md`: `24b6639ce92a0d23701dad632920785d386cae1c`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/product/module-catalog.md`: `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- `docs/queue/implementation-registry.json`: `b3400fd75763c981c1132b7b5112b653c2271755`
- `docs/queue/work-orders/QA-04.md`: `42ef28bc8f4bef4465ae187236d817ce7793c9f2`
- `.github/workflows/docs.yml`: `cbbaf5731de75f1de4bdf8cad6489e6d73681d71`
- `docs/adr/0075-qa-01-ci-matrix-security-policy.md`: `22e91a36c1e0a8121163fa4778abd0489fed86e5`
- `docs/adr/0052-net-06-defense-in-depth-authority-quotas-privacy.md`: `5dd8ed1dc51c36b8e7ef6f5df6691b5ed5c2e28b`
- `docs/adr/0065-ai-06-agent-grant-consent-policy.md`: `dcbf4f559abd9ecca704d469784e02916e68d2f2`
- `docs/contracts/qa-01-ci-evidence-api.md`: `ccaa79cfc34fff3e58b68fa7d2b1f594f5d8154f`
- `docs/contracts/net-06-security-abuse-api.md`: `5d2bbfb48ad76d3368984524a19d95160cf0bb03`
- `docs/contracts/ai-06-authorization-api.md`: `74b27624869c5032912b7b159f93d5d220dace6e`

## SCOPE — NECESSARY, exactly EIGHT NEW Markdown
1. [Architecture](../architecture/qa-04-security-fuzzing-supply-chain.md).
2. [ADR-0078 PROPOSED](../adr/0078-qa-04-security-gates-fuzz-sbom-provenance-policy.md).
3. [2026 security tools/license/threat/SBOM/cost matrix](../research/qa-04-security-fuzz-tools-license-risk-matrix.md).
4. [Versioned semantic security/fuzzer/provenance API](../contracts/qa-04-security-evidence-api.md).
5. [Exactly 128 FUTURE Q04-T001..Q04-T128 acceptance cases](../testing/qa-04-acceptance-matrix.md).
6. [Future fuzz/security benchmark and incident protocol](../research/qa-04-fuzz-security-benchmark-protocol.md).
7. This WO.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-QA-04.md).
Initial research PR only these eight ADDED Markdown; no existing checkpoint/backlog/registry/CI YAML/code/binaries/roles/rulesets/ADR predecessor modifications. Independent checkpoint and history each separate gated increments.

## OUT OF SCOPE
No actual security scanner/fuzz binary, Clang compiler flags, enabled CodeQL workflow, C++ code change, security risk exploit in production, DAST against live services, git secrets/trusted private data, network server/MCP grant implementation, signed release/provenance, actual SBOM, paid scanning/OSS-Fuzz enrollment, GitHub ruleset/branch protection/admin settings changes, unapproved source licensing, PR merges of code, automatic HIGH/CRITICAL waiver, broad cleanup, credential/key rotation without incident approval, public MVP.

## FILES/SOURCES TO READ
All Context Lock paths, Git HEAD and next/future code issue #93 and #94. Official references: [LLVM libFuzzer](https://llvm.org/docs/LibFuzzer.html), [ASan](https://clang.llvm.org/docs/AddressSanitizer.html), [TSan](https://clang.llvm.org/docs/ThreadSanitizer.html), [AFL++ licensing](https://github.com/AFLplusplus/AFLplusplus/blob/stable/LICENSING.md), [CodeQL C++](https://docs.github.com/en/code-security/how-tos/find-and-fix-code-vulnerabilities/manage-your-configuration/codeql-for-compiled-languages), [GitHub untrusted PR](https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target), [Actions security](https://docs.github.com/en/actions/reference/security/secure-use), [SPDX 3.0.1](https://spdx.github.io/spdx-spec/), [CycloneDX 1.7](https://cyclonedx.org/specification/overview/), [SLSA 1.2](https://slsa.dev/spec/v1.2/), [artifact attestation](https://docs.github.com/en/actions/how-tos/secure-your-work/use-artifact-attestations), [rulesets](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/available-rules-for-rulesets), [GitHub billing](https://docs.github.com/en/billing/concepts/product-billing/github-actions), [OSV schema](https://ossf.github.io/osv-schema/), [OSS-Fuzz](https://google.github.io/oss-fuzz/getting-started/new-project-guide/). Reverify exact versions/licenses on code activation.

## REQUIREMENTS
Catalog: **"Fuzzing e auditoria de riscos HIGH/CRITICAL antes de release."** C++ memory, bounds, thread, parser hostility and ownership; NET-06 network trust/quotas server authority; AI-06 agent grant/consent/revocation; CI branch trust, downstream native dependencies and licenses; actual SPDX/CycloneDX/SLSA verified provenance future; no known unresolved HIGH/CRITICAL advancing release. GOV-001..005, owner source license/DoD, zero paid tools.

## ARCHITECTURE RULES
1. Formal QA-01+NET-06+AI-06 only, others transitive/integration. QA-04 owns security-test and evidence classification, not network/AI runtime authority or CI runner.
2. Future bounded libFuzzer Clang-matched per parser + ASan/UBSan, separate TSan/MSan compatible lanes; record actual deterministic small seed/corpus rights SHA, coverage, timeout/RSS/crash reproduction and negative regression, don't make no-crash secure claim.
3. AFL++ overall **AGPL-3.0-or-later** external tool and per-file Apache2+other; licensure/version/source for any linked/reused code individually approve. LibFuzzer maintenance mode supported bug fixes only. No unapproved paid/commercial license.
4. Use C++ static/SARIF CodeQL C++ public manual-vs-none generated code coverage, dependency CVEs OSV/GHSA, scan unknown/not-supported classifications. Threat model untrusted assets/network/tools/plugins/agent and local privacy; sandbox capabilities/FS/network allowlist and expiry.
5. SBOM SPDX-3.0.1 / CycloneDX-1.7 actual artifact dep closure, versions/hashes/license notices; verify real trusted SLSA1.2 build/source tracks/subject/signatures, not JSON claim. PLAT-05 owns release signing/packaging, BIZ-01 source licensing, QA-04 verifies.
6. GitHub current main **unprotected and zero rulesets**; future required checks and Action full SHA/lockfile, fork PR read-only no secrets, cache trust, `pull_request_target` never executes fork code under privileges; no P00 admin/ruleset/CI edit.
7. Known HIGH/CRITICAL blocker, private vulnerability channel and owner incident rollback/roll-forward/key handling. No public malicious exploit corpus/PII, no upload user project data in public artifacts.
8. R$0 public standard runner conditional free compute; bounded job/resource/storage/caches, refuse paid cloud/hardware/security SaaS; no continuous public telemetry or hidden privileges.

## CONSTRAINTS
P00 LOW doc-only, all 80 code WOs frozen, zero approval for root, private telemetry, source license or paid tools; no force push/history rewriting or unsafe repo policy change. Future code ELEVATED/HIGH_ASSURANCE requires actual approval, independent review and recovery. Stop on STALE and defects known HIGH/CRITICAL.

## ACCEPTANCE CRITERIA
- [ ] Research exactly EIGHT ADDED .md and no existing code/CI/registry/checkpoint/backlog edits.
- [ ] ADR-0078 **PROPOSED**, formal deps EXACT QA-01+NET-06+AI-06, predecessor ADR-0075/0052/0065 unchanged.
- [ ] Deep 2026 official source-backed C++20/parser fuzz/libFuzzer maintenance/AFL++ AGPL, compatible ASan/UBSan/TSan/MSan, NET/AI access, plugin sandbox, SAST/DAST CodeQL modes, SBOM SPDX3.0.1/CycloneDX1.7, SLSA1.2 actual artifact, license/NOTICE and supply chain, GitHub branch current zero rulesets, R$0/security privacy, incident proof.
- [ ] EXACT **128 unique sequential Q04-T001..Q04-T128**, eight groups ×16, all FUTURE/NOT EXECUTED, benchmark future no false security PASS.
- [ ] Research PR exact HEAD Docs Validation SUCCESS, objective pt-BR audit APPROVED, normal squash/main readback.
- [ ] Independent checkpoint PR exactly **FIVE MODIFIED files** checkpoint/backlog/registry/this WO/Evidence, **sole semantic registry QA-04 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`**, all 79 other modules+root identical. Target **75/80 documented (93.75%), 5 pending, all 80 code WOs BLOCKED, 0 ready/approved_adr, all release classes UNDECIDED, engine=false**. Own CI/audit/squash/readback BEFORE close research #353; future coding #93 OPEN/BLOCKED.
- [ ] Final **FOUR Markdown-only historical** PR checkpoint/backlog/WO/Evidence, own exact HEAD CI/pt-BR audit/squash/readback, next REAL catalog **QA-05 Compatibility & Release Qualification**, 76/80 formal QA-02+PLAT-05, future #94 OPEN/BLOCKED.

## TESTS
P00 only **actual GitHub Docs Validation** Source Pack/local links/catalog DAG/80 registry/blocked selector, PR exact statuses and Q04 128 ID uniqueness, checkpoint JSON one-field diff, GitHub auditable CI/job/merge/readback. **NO real C++/CodeQL/clang-tidy/ASan/AFL++/libFuzzer/MCP/network/sandbox/DAST/SBOM/SLSA/incident tests actually executed.** All 128 security tests FUTURE/NOT_EXECUTED.

## DELIVERABLES
Issue #353 research, 8 Markdown ADR/architecture/matrix/API/tests/bench/WO/evidence, research PR own CI/audit/squash/main readback, independent checkpoint five-file PR own gate then close #353, historical four-Markdown PR own CI/audit/squash/readback, next CTA to QA-05. Future #93 stays blocked and no GitHub policy changes.

## REVIEW FORMAT
Brazilian Portuguese objective audit: exact BASE/HEAD/changed statuses, current canonical authority and Context Lock Git blob SHA-1 vs future raw SHA256, formal QA-01+NET-06+AI-06 only, license/fuzzer/SBOM/SLSA/cost/security/CI threat evidence, test IDs all FUTURE, Docs CI actual run/job, changed registry semantic delta and remaining risk, approve document only via **APPROVED / CORRECTION REQUIRED / BLOCKED**, no implementation authorized.

## STOP CONDITION
Source/critical decision STALE, incorrect 8/128, wrong DAG, failed CI, copyright/AGPL unnoticed, unapproved credential/secret/policy/spend, privacy disclosure, fake security tests/SBOM/certification, known HIGH/CRITICAL, required audit absent => CORRECTION REQUIRED same WO/PR when safe or BLOCKED. No next increment until fully audited history; no code unlock.

## CHECKPOINT DELTA PROPOSED ONLY
After research exact-head Docs Validation and objective APPROVED, squash/main readback, independent five-file checkpoint sole QA-04 research_status change 74 ->75 researched and 6->5 pending, unchanged other 79/root, all 80 coding WOs blocked. Own CI/audit/squash/readback **then** close research issue #353, coding #93 OPEN/BLOCKED. Independent four-Markdown historical PR own gates then QA-05 catalog 76/80.


## Research PR #354 factual approval and independent checkpoint proposal
- [Research PR #354](https://github.com/KayzenRoot/stormline/pull/354): BASE `04f9ff54875b46fad05941529e1c6719fe79c394`, HEAD `38994e9603df603201222adc9bacff274ef66f63`, **exactly EIGHT ADDED Markdown**: architecture, ADR-0078 PROPOSED, security/fuzzer/SBOM/license-cost matrix, typed security evidence API, exactly 128 future Q04 tests, future security benchmark, WO, Evidence. [Docs Validation run #43830836983](https://github.com/KayzenRoot/stormline/actions/runs/43830836983) **SUCCESS** job #133175521023, checks Source Pack/links, catalog DAG, 80-registry, Zcode selector rejects blocked code packets. [Objective pt-BR audit #6911255236](https://github.com/KayzenRoot/stormline/pull/354#issuecomment-6911255236) **APPROVED documentary**, normal squash/main readback **`5e3b18ac5b17eebcc68d9b32af31f0f01f5df8c8`**; registry stayed 74/80 at research merge.
- **Independent checkpoint sole semantic registry mutation QA-04 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`**, all 79 other module objects and registry root fields unchanged. Proposed target **75/80 researches documented (93.75%), 5 pending, ALL 80/80 implementation code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, all release classes UNDECIDED, engine_implemented=false**. EXACT formal dependencies **QA-01 + NET-06 + AI-06 ONLY**; predecessor ADR-0075/0052/0065 PROPOSED, new ADR-0078 PROPOSED, NLE-D009 source license OPEN, D013 no public MVP. 128 Q04-T001..Q04-T128 FUTURE/NOT_EXECUTED. No C++ engine, libFuzzer/AFL++/ASan/CodeQL/static/DAST/SCA executed, no SBOM built, no signed SLSA provenance, no policy runtime/incident or release; only documentation CI actually ran.
- Source Check observed GitHub repository PUBLIC, main `protected=false`, **zero repository rulesets** and existing docs-only `.github/workflows/docs.yml` with mutable `actions/checkout@v7` major tag. Documented gap not fixed or represented as enforced. Action lock/full SHA, read-only forks, privilege-free cache, true incident disclosures and R$0 storage cost guards are future subject approval. AFL++ external tool **AGPL-3.0-or-later overall**, per-file Apache-2.0 as applicable; no copying/redistribution.
- [Research issue #353](https://github.com/KayzenRoot/stormline/issues/353) remains OPEN until independent checkpoint own CI/audit/squash/main readback; future coding [#93](https://github.com/KayzenRoot/stormline/issues/93) OPEN/BLOCKED. After independent checkpoint proof close research #353, then separate **FOUR Markdown historical** PR checkpoint/backlog/WO/Evidence with independent CI/audit/squash/readback. Next REAL module **QA-05 Compatibility & Release Qualification** catalog 76/80, formal **QA-02 + PLAT-05**, coding [#94](https://github.com/KayzenRoot/stormline/issues/94) OPEN/BLOCKED.
- This checkpoint gate needs own CI/audit/merge/readback, only then historical closeout.
