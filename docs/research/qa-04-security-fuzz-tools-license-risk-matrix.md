# QA-04 — 2026 Security Tools, Fuzzers, SBOM/SLSA, Licenses, Cost and Risk Matrix

**2026-11-16 | P00 DOCUMENTARY RESEARCH ONLY | [research #353](https://github.com/KayzenRoot/stormline/issues/353) | NLE-P00-WO-002-QA-04 | future code [#93](https://github.com/KayzenRoot/stormline/issues/93) OPEN/BLOCKED | BASE main `04f9ff54875b46fad05941529e1c6719fe79c394`.** Formal deps **QA-01 + NET-06 + AI-06 ONLY**, ADR-0075/0052/0065 PROPOSED. Initial 74/80 researched, six pending, 80/80 future coding WOs BLOCKED, 0 ready/approved_adr, all release classes UNDECIDED, engine=false.


**Candidate technology and legal research only**. The repository does not contain a compiled game engine. None of these tools has been installed or executed through this P00 Work Order. Neither SPDX SBOM nor CycloneDX, signed provenance, vulnerability exploitability scoring, DAST scan or signed binary can exist as evidence before actual outputs/verified dependency closure.

## Authoritative 2026 sources and precise limitations
| Primary reference | What the authority establishes | Stormline consequence |
|---|---|---|
| [LLVM libFuzzer](https://llvm.org/docs/LibFuzzer.html) | in-process coverage-guided fuzz with Clang matching version; project developers moved to Centipede for new features, libFuzzer *maintenance only* | native C++20 small deterministic harness under ASan/UBSan, arbitrary target corpus not by itself proof |
| [LLVM AddressSanitizer](https://clang.llvm.org/docs/AddressSanitizer.html), [UBSan](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html), [TSan](https://clang.llvm.org/docs/ThreadSanitizer.html), [MSan](https://clang.llvm.org/docs/MemorySanitizer.html) | distinct compiler-runtime availability; MSan requires instrumentation of dependencies and supported operating systems, TSan resource overhead and incompatible combined ASan instrumentation | align QA-01 OS/compiler lanes, classify unsupported, never ship sanitizer binaries |
| [AFL++ official licensing](https://github.com/AFLplusplus/AFLplusplus/blob/stable/LICENSING.md) | core `afl-fuzz` **AGPL-3.0-or-later**; individual files may be Apache-2.0, other bundled licenses, optional commercial terms | using executable on local/hosted isolated runner under license ≠ copying/embedding engine code; any redistribution/modified service requires obligation review, no purchase |
| [OSS-Fuzz project eligibility](https://google.github.io/oss-fuzz/getting-started/new-project-guide/) | public continuous fuzzing primarily for qualifying open source projects | engine source license OPEN; do not assume proprietary Stormline eligible for free hosted OSS-Fuzz |
| [CMake CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html) | CTest test discovery/JUnit and runtime statuses | QA-01 owns CI, QA-04 supplies future parser harness+corpus and failure evidence; test count nonzero |
| [CodeQL compiled C/C++](https://docs.github.com/en/code-security/how-tos/find-and-fix-code-vulnerabilities/manage-your-configuration/codeql-for-compiled-languages) | public GitHub code scanning available; `none` mode excludes generated sources, `autobuild` varies, `manual` controls build and is best completeness when implemented | do not claim CodeQL scan ran; eventually choose manual mode after real source/build and cost/trust |
| [GitHub `pull_request_target` security](https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target) | executing fork code under trusted workflow secrets/write permissions is a “pwn request”; `workflow_run` artifacts can be hostile | no privileged checkout/execution of PR head, distrust caches/artifacts, keep forks read-only |
| [GitHub secure use](https://docs.github.com/en/actions/reference/security/secure-use) | workflow dependency lockfile best, otherwise full immutable action SHA pin when trusted; tag pin risk | *current* docs.yml `actions/checkout@v7` mutable major tag remains unchanged during P00; future separate approved hardening |
| [GitHub rulesets](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/available-rules-for-rulesets) | required checks/rulesets enforce status policy if enabled with proper app origin | baseline API **zero rulesets**, `main protected=false`; no claim checks enforced, admin WO later |
| [SPDX 3.0.1](https://spdx.github.io/spdx-spec/) | SPDX specification model files/packages/build relationships and license identification | schema version, source component license expressions and root engine license ambiguity recorded |
| [CycloneDX 1.7](https://cyclonedx.org/specification/overview/) | ECMA-424 1.7 supports SBOM, crypto asset/inventory, declarations, vulnerability metadata and dependency relationships | candidate alternate/interchange, validate schema, don't invent vulnerability-free inventory |
| [SLSA 1.2](https://slsa.dev/spec/v1.2/) | supply-chain tracks/levels and provenance expectation, trusted subject+builder | no self-proclaimed SLSA certification merely from an unsigned static JSON |
| [GitHub artifact attestation](https://docs.github.com/en/actions/how-tos/secure-your-work/use-artifact-attestations) | OIDC-backed artifact provenance/signatures and verifier workflow for genuine build output | future PLAT-05 release owner, QA-04 checks actual signed digest/source/workflow/trust |
| [OpenSSF Scorecard](https://securityscorecards.dev/) | project health/security heuristic checks, not a formal code audit | do not score project without actual run and treat score as a vulnerability proof |
| [OSV schema/database](https://ossf.github.io/osv-schema/) | vulnerability ID, affected version ranges and package ecosystem | compare to exact pinned version/commit, report unfixed/withdrawn and false positives |
| [GitHub advisory API](https://docs.github.com/en/rest/security-advisories) | GHSA and repo security advisories with affected package/version/fix metadata | private reporting and CVE triage only when real findings sourced |
| [GitHub Actions billing](https://docs.github.com/en/billing/concepts/product-billing/github-actions) | public standard hosted runner compute free; storage/cache/private/larger can incur charges | R$0 hard guard for CI fuzz budgets, no runaway artifact uploads |

## Proposed tool and SPDX/license verification, not selected
| Tool / version candidate | Upstream license / obligation (validate pinned version and transitive) | Role | Security/performance constraints |
|---|---|---|---|
| LLVM clang/libFuzzer | Apache-2.0 WITH LLVM-exception, exact LLVM tag/Clang match | deterministic in-process C++20 parser fuzz and coverage | maintained bugfix only, not feature innovation; memory/corpus limits |
| LLVM SanitizerCoverage/ASan/UBSan | LLVM runtime Apache-2.0 WITH LLVM-exception plus third-party notices | reproducible memory/UB crash detection | supports vary by OS/SDK; runtime not released to end-user |
| LLVM TSan/MSan | LLVM runtime and dependencies by compiler build | concurrency race/uninitialized-memory separate target | cannot combine TSan with ASan; MSan Linux-family with full instrumentation |
| AFL++ (external binary) | **AGPL-3.0-or-later overall**; per-file Apache-2.0 / some GPL/LLVM-Exception; [official file map](https://github.com/AFLplusplus/AFLplusplus/blob/stable/LICENSING.md) | coverage-guided fast mutation/forkserver/persistent mode | AGPL service/distribution obligations; no copy into engine, external tool only if approved |
| Centipede | Apache-2.0 for Google upstream project subject exact source tag/third-party | alternative newer coverage-guided fuzzer | integration/maintainer/runtime and deterministic coverage unverified |
| clang-tidy/Clang static analyzer | LLVM Apache-2.0 WITH LLVM-exception | C++ ownership/correctness/taint static analysis | compile_commands completeness, false positives; QA-01 integrates |
| cppcheck | GPL-3.0-or-later family depending actual release | independent static candidate | process-only vs redistribution legal obligations, timeout and quality |
| CodeQL engine/actions | GitHub service terms; action source license and SHA pin verify | C/C++ interprocedural code scanning | public repo eligible, mode none incomplete generated code, no scanning configured today |
| OSV-Scanner | Apache-2.0 upstream, exact release tag and database licensing verify | ecosystem CVEs, transitive package scan, artifact linkage | source version/commit and resolution evidence; not every native dependency ecosystem supported |
| OpenSSF Scorecard | Apache-2.0 upstream, check container image/transitives | upstream supply-chain score heuristics | heuristic not gate by score alone, GitHub rate/permissions |
| Syft | Apache-2.0 upstream [Syft](https://github.com/anchore/syft) | future C++ filesystem/container SBOM generator | supported native binaries and artifacts coverage; schema/source/version proof |
| Grype | Apache-2.0 upstream [Grype](https://github.com/anchore/grype) | future vulnerability correlator for generated SBOM | stale feeds/offline DB, unresolved version/vex false positive |
| Dependency-Track (optional) | Apache-2.0 [OWASP Dependency-Track](https://github.com/DependencyTrack/dependency-track) | server-side SBOM processing | requires DB/cloud/network persistent operations, NOT automatically cost R$0 |
| Gitleaks (optional) | MIT [upstream](https://github.com/gitleaks/gitleaks) verify tag | prevent secret exposures in PR and histories | scans could discover sensitive findings, never print secrets; no mandatory hosted license |
| TruffleHog (optional) | AGPL-3.0 license under upstream variants, exact tag verify | optional secret detection | avoid assuming MIT, consider tool-usage vs redistribute, permissions |
| SPDX 3.0.1 schema/spec | Linux Foundation/open SPDX materials, tool generation license separately | machine bill of materials/packages/license relationships | SBOM != signature/security clear/license approval |
| CycloneDX 1.7 schema/spec | OWASP/ECMA spec Apache-2.0, official [spec](https://github.com/CycloneDX/specification) | alternate SBOM, VEX/CBOM and relevant AI ML components | schema and source/target components must match actual compiled release |
| GitHub attestations + in-toto/Sigstore | GitHub service terms and individual client open-source component licenses | future PLAT-05 trusted artifact provenance | no attestation before actual signed build subject and verification |
| SLSA build provenance policy | SLSA 1.2 specification/open standard terms | verified tracks/requirements | no automatic level assignment, no L3 without real builder trust |
| CMake/CTest + GitHub-hosted Actions | CMake BSD-3, GitHub SaaS service terms | CI worker and fuzz replay job | only *public standard hosted* compute free subject limits, no code exists |
| Original seed corpus/assets | Stormline-owned rights/provenance to approve | valid/invalid shader/project/asset serialization | no proprietary commercial game media, no player PII |
| Sandbox runtimes and WASM | WASI runtimes various Apache-2.0/MIT (e.g. Wasmtime Apache-2.0 WITH LLVM-exception) | future plugin untrusted code isolated host functions | no universal OS guarantee; allowlists and host capabilities key, source license unresolved |
| External DAST proxy/security lab | various FOSS/proprietary depending exact choice | only future isolated server from NET owner with permission | no third-party endpoint unauthorized probe, no paid cloud |

## Threat scenarios and negative audit gates (future, not executed)
| Boundary | Candidate defensible tests | Owner, caveat |
|---|---|---|
| Asset import | byte length/bounds, malformed nested structures and decompression quotas, signed overflow/alias, traversal/symlink | DATA/GAME owners implement; QA-04 fuzz harness and regression |
| Native C++ memory | ASan+UBSan, UAF/OOB/heap overflows, separate TSan + applicable MSan | no claim completeness or compiled target today |
| Network parser/session | malformed framing/replay/nonce/actor ownership, quotas and threat privacy | NET-06 enforces; QA-04 regression verifies, no public DAST |
| AI MCP tools | stale/attenuated grant, exfil path/writing outside project, user consent and revocation | AI-06 enforces; QA-04 only simulates authorized test scenarios |
| Plugins/WASM scripts | process/user namespace/allowlisted syscalls/host capabilities/FS/network quota | OS-specific proof and sandbox integrator, not blanket WASM promise |
| CI and releases | fork token read-only, signed artifact boundary, cache digest, action immutable pin, secret redaction | QA-01/PLAT-05 owners, no P00 workflow edit |
| SBOM provenance | missing deps/unknown license and invalid SHA/signer identity fail closed | QA-04 verifies; BIZ-01/PLAT-05 final approvals |
| Incident response | keep reproducer private, classify threat, patch and rollback/rerelease, no known HIGH/CRITICAL accepted | owner HIGH_ASSURANCE when privileged or irreversible |

## R$0 evidence constraints
Current GitHub repository public, **zero rulesets** and main not protected (Source Check). This is a *security governance gap*, not evidence it has been fixed. Admin required-check adoption is IMPORTANT future separate approved WO after actual checks; documentation cannot assert future enforcements. Running small future security checks on public standard runner may be no-cost in compute, but long fuzz campaigns/artifacts/cache/storage and private repo plan require explicit caps; cannot promise unbounded free resources. OSS-Fuzz may not accept private unreleased engine. Engine source license NLE-D009 OPEN; review all transitive redistribution notices before public shipping.

[Architecture](../architecture/qa-04-security-fuzzing-supply-chain.md) · [ADR-0078](../adr/0078-qa-04-security-gates-fuzz-sbom-provenance-policy.md) · [future benchmark](qa-04-fuzz-security-benchmark-protocol.md).
