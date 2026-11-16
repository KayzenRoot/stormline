# ADR-0078 — Risk-Gated Fuzzing, Capability Boundaries and Verifiable Supply Chain

**2026-11-16 | P00 DOCUMENTARY RESEARCH ONLY | [research #353](https://github.com/KayzenRoot/stormline/issues/353) | NLE-P00-WO-002-QA-04 | future coding [#93](https://github.com/KayzenRoot/stormline/issues/93) OPEN/BLOCKED | BASE main `04f9ff54875b46fad05941529e1c6719fe79c394`.** QA-04 catalog 75/80, formal dependencies **QA-01 + NET-06 + AI-06 ONLY** (ADR-0075/0052/0065 all PROPOSED), baseline 74/80 documented, 6 pending, all 80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class UNDECIDED all, engine_implemented=false, source license NLE-D009 OPEN, no public MVP NLE-D013.


**STATUS: PROPOSED / NOT OWNER-APPROVED / NOT IMPLEMENTED / NO SECURITY SCAN OR FUZZ TEST EXECUTED.**

## Context and threat model
Stormline will parse hostile game/project/assets and receive network/agent commands. Memory unsafe C++ code, compromised dependencies/CI artifacts, plugin permissions and elevated AI tool access can undermine both editor and exported runtime. Source license NLE-D009 OPEN, no runnable engine; current CI validates docs only. Planning must not assert security certifications, code findings, signed release or working sandbox.

## PROPOSED policy decisions
1. **Only formal prerequisites QA-01 + NET-06 + AI-06**, current ADR-0075/0052/0065 PROPOSED. QA-01 orchestrates actual future C++20 test runners and CI evidence; NET-06 owns typed multiplayer admission/quotas/privacy; AI-06 owns verified attenuated grants, consent and revocation; QA-04 owns tests/security audit/evidence reconciliation, never duplicates their runtime controls or silently adds PLAT/CORE/GAME/etc to formal catalog DAG.
2. **Risk-based boundary inventory** (not a certified current risk assessment) covering imported media/scene/project formats, decompression and parsers, runtime C++ allocators, network/session actors, plugin/script/effect runtime, MCP/AI tools, build actions/dependencies and shipped exports. Authoritative owner and input provenance must remain explicit; no untrusted bytes promoted into executable policy, privileged command or validator exception.
3. **Fuzz-then-replay, not fuzz-to-green:** future hardened isolated test harnesses with libFuzzer Clang-compatible ASan+UBSan and separate supported TSan/MSan; explore AFL++ as alternative **AGPL-3.0-or-later overall with individually Apache-2.0 and other files** rather than imply universal MIT or licensing of engine. Corpus source/rights/size, budgeted seeds, coverage, timeout/RSS, crash signature+minimization, exact rebuild+replay and new deterministic regression tests. Keep fuzz schedule cost bounded. LLVM [libFuzzer](https://llvm.org/docs/LibFuzzer.html) is maintenance mode (no new major features); selection remains owner PROPOSED.
4. **No false complete scans**: CodeQL C++ public repo available but `none` mode excludes generated code, `autobuild` variable and `manual` best controlled coverage after compiling real code; clang-tidy/static analyzer, clang-format and compiler warnings/ASan/UBSan/TSan are complementary, not substitutes. SAST/SCA findings map to actual source files/locks; no test PASS from Docs Validation. DAST only when approved isolated real server exists, never scan public endpoints without authorization.
5. **Artifact and dependency inventory**: future SBOM per actual release candidate and build/dependency closure using [SPDX 3.0.1](https://spdx.github.io/spdx-spec/) / [CycloneDX 1.7](https://cyclonedx.org/specification/overview/) schema validation, source commits, file and package hashes/relationships, transitive runtime/build components, license SPDX expression + notices, dependency CVE/GHSA/OSV matching and owner-reviewed false positives. SBOM is inventory, not proof of no vulnerabilities or license rights.
6. **SLSA provenance means verified builders**: [SLSA v1.2](https://slsa.dev/spec/v1.2/) build/source track and in-toto/Sigstore/GitHub artifact attestation only when trusted workflow creates a real subject binary digest, identities and predicates verified. Do not invent levels or claim SLSA L3 from JSON/static file. PLAT-05 owns trusted packaging/signing/publishing, QA-04 verifies independently and records provenance gap, BIZ-03 governs release. Current Docs CI cannot attest engine.
7. **CI protection baseline**: currently GitHub API reported **no rulesets**, main unprotected, docs-only GitHub Actions workflow with mutable major action tag; no untrusted privileged code. Future workflow dependency **lockfile** preferred when supported, otherwise complete immutable commit SHA with provenance review, read-only fork PR, cache trust separation, no `pull_request_target` executing fork, no `workflow_run` artifact promotion, OIDC/token least privilege, secrets and artifact redaction. Required checks and rulesets introduced only under **separate approved admin WO after real checks exist**, not silently during QA-04 P00; proof is absent now.
8. **Fail-closed authorization/sandbox**: NET-06 server-side actor/session/quota proof not client declarations, AI-06 grants with project path/action/resource limits, expiry, revocation and dry-run/owner approval, plugin/script sandbox process or capability escape protected by owner OS runtime (availability to be tested per platform), no unrestricted filesystem/network or shell from untrusted project material. QA-04 tests negative boundaries only, no new permission authority.
9. **Severity and incident policy**: HIGH/CRITICAL unresolved => no merge/next implementation/release; code issue correction in same PR when safe, evidence reproducer private and verified patch/negative test, coordinate GHSA/private report, credential/key rotation/rollback/roll-forward with owner signoff and confidentiality. CVSS score and exploited-in-wild not assumed from name alone; publish only verified security claims. Severity process and exceptions subject owner and legal compliance.
10. **Free first and future tests truly future**: only public standard GitHub-hosted CI compute assumed R$0 conditional on storage/cache/visibility; no expensive dependency scanner, profiler service, paid CodeRabbit, cloud fuzzing, GPU security lab, bounty program or obligatory external auditor. Exactly 128 test intentions Q04-T001..Q04-T128 FUTURE/NOT EXECUTED; all 80 code WOs remain BLOCKED, ADR remains PROPOSED, no license/product release.

## Alternatives not automatically adopted
| Alternative | Rejection or proof needed |
|---|---|
| Declare secure because docs-validation passes | docs workflow has no C++/fuzzer/static analyzer/security controls |
| Depend exclusively on sanitizer pass | runtime support limits and undetected logical/authorization bugs |
| Treat fuzz “24h no crash” as security proof | corpus/target depth and semantic oracles vary, coverage needed |
| Copy AFL++ AGPL program into proprietary engine | legal compatibility not approved; external tool usage distinct from redistribution |
| Automatically mark CodeQL `none` mode complete | generated sources not analyzed |
| Auto-accept all transitive dependencies as safe | need pinned version, CVE/VEX and license evidence |
| Add `slsaLevel:3` field to SBOM and call attested | requires real trusted builder/subject signature verification |
| Trust same public PR artifact as release candidate | privilege boundary/cache poisoning and supply-chain manipulation |
| Run fork code under `pull_request_target` write token | untrusted code execution with secrets |
| Enable all required rulesets before checks exist | may block merges and is separate admin approval |
| Assume WASM sandbox ensures no host file/network access | host-granted capabilities and runtime vulnerable surface remain |
| Use global network WAF/AI prompt regex as sole auth | true principal/session/grant validation remains owner contract |
| Upload user assets/seed crashes into public CI logs | privacy, exploit detail, original license and leakage |
| Buy cloud fuzzing/security scanner automatically | GOV-003 R$0 and owner authorization absent |
| Release beta despite HIGH/CRITICAL outstanding | violates DoD and explicit NLE-D013 no public MVP |
| Merge on unverified “completed” executor status | independent Evidence Bundle, CI and audit mandatory |

## Future owner gates and audit
Approve exact parser/harness inventory, ABI/OS sanitizer support, original corpora and artifact/privacy policy, fuzzer/toolchain versions/licensing, static scanner coverage and severity, formal NET/AI trust flows, platform plugin sandbox, chosen SBOM dialect and provenance builder, current rule sets and free cost controls, rollback and disclosure operators. Only after actual code is built/tested and approved may meaningful security claims be made. No owner approval in P00.

[Architecture](../architecture/qa-04-security-fuzzing-supply-chain.md) · [tool/legal matrix](../research/qa-04-security-fuzz-tools-license-risk-matrix.md) · [semantic API](../contracts/qa-04-security-evidence-api.md).
