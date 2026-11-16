# QA-04 — Future Fuzzing, Static Security, SBOM and Trusted Build Benchmark Protocol

**2026-11-16 | FUTURE PROTOCOL ONLY.** Research #353, future coding #93 OPEN/BLOCKED, base `04f9ff54875b46fad05941529e1c6719fe79c394`. No LLVM fuzz/ASan/UBSan/TSan run, CodeQL database, parser, network/AI authorization, SBOM artifact or signed provenance produced in this P00 document. All numeric budgets below are **protocol candidates** until owner selects exact resource envelope.

## Objective and source lock
Design objective measurement of security boundary robustness, coverage, resource consumption, CI false-green resistance and real artifact provenance under R$0, not “guaranteed secure.” Formal predecessors **QA-01, NET-06, AI-06 exactly**, their contracts still PROPOSED. Candidate future core must run real C++20 approved build with deterministic QA-01 CI, implement NET-06 actor trust/session and AI-06 grant/consent then isolate legitimate internal test targets.

## Future reproducible target/fuzzer matrix
| Future ID | Target and corpus, fully synthetic rights-cleared | Proof requirements |
|---|---|---|
| SEC-B01 | simple parser JSON binary frame header/size | Clang libFuzzer+ASan+UBSan actual source/OS/flags/corpus hash, crash and negative reject |
| SEC-B02 | image PNG/EXR metadata/chunks | decoder version, size/decompress caps, memory RSS/timeout, invalid inputs |
| SEC-B03 | glTF/GLB accessor and asset index paths | bounds/offset/stride and semantic AssetId/device generation, repeatable seed |
| SEC-B04 | audio WAV chunk/codec resource budget | CPU/time bytes/error class, no copyrighted media |
| SEC-B05 | scene/world/save version/migration parse | invalid schema/unknown field/transactional previous-good recovery |
| SEC-B06 | shader/preprocessor/import sandbox | include recursion/path and CPU bound, no actual GPU shader privilege |
| SEC-B07 | plugin/WASM host API capability | verified OS sandbox and denied FS/network/privileged calls |
| SEC-B08 | NET-06 message/session/actor ownership/rate | actual local server implementation with fake actor/transport not Internet DAST |
| SEC-B09 | AI-06 MCP typed arguments/grants | revoked consent/expired project path scope and audit denial |
| SEC-B10 | Linux ASan/UBSan + dedicated TSan where supported | injected fixable unsafe fixture/real instrumented target/independent lane |
| SEC-B11 | AFL++ persistent vs libFuzzer comparison after rights review | corpus stability/coverage/execution throughput, no AGPL copying |
| SEC-B12 | CodeQL `none/autobuild/manual` on real native build | generated-code mode diff, SARIF rules/coverage/source SHA |
| SEC-B13 | OSV/GHSA advisory match vs pinned native/runtime deps | exact versions/licenses/VEX evidence, stale feed handling |
| SEC-B14 | SPDX 3.0.1 vs CycloneDX 1.7 actual release build | schema/component/source/binary SHA/license notice reconciliation |
| SEC-B15 | SLSA 1.2 builder/signature/subject positive+tampered negative | trusted OIDC identity/source ref/in-toto subject verify, don't claim level on metadata |
| SEC-B16 | incident replay/rollback/readback under no HIGH/CRITICAL | private reproducer → patch/regression/owner verdict and audited recovery |

## Reproducible security run controls
- **Preflight** real Git BASE/HEAD + source dependency hashes/context lock, compiler/Clang/libFuzzer version/target OS/arch/SDK, approved scope and owner consent, original corpus rights and deterministic seed. Corpus minimization itself needs immutable digest before and after, retain records privately. No actual user/game data.
- **Coverage evidence**: sanitizer coverage edges, target-specific code functions reached, corpus size/valid-vs-invalid acceptance, unique crashes, timeouts/OOM, per-input runtime median/tail and wall seconds per worker, peak RSS/CPU, first unique crash stack signature redacted. Zero crash findings is not zero vulnerabilities. Distinguish target harness crash vs injected synthetic bug and measure target false negatives.
- **Long campaigns**: per-job runtime, `max_len`, RSS, disk/corpus bytes, single-seed/fixed deterministic repro and capped memory. Public standard hosted runners only where allowed R$0 compute, but storage/quota/paid larger runner require check. Local isolated long fuzz target possible after owner environment approval but never privileged on fork.
- **Static/SAST**: clang-tidy/Clang static analysis and CodeQL version/mode, true generated-code inclusion and SARIF severity; dependency SCA OSV/GHSA feed fetched/verified version and precise reachable component; independent license reviewer for legal obligations. No “scan complete” when no C++ code exists.
- **SBOM/provenance**: actual built binary archive SHA256 with full source-to-package dependency mapping including vendored and native tool runtime/third-party; schema validate SPDX 3.0.1 and CycloneDX 1.7, reconcile counts/licenses and NOTICE, compare signed real attestation's subject hash and trusted builder source, record verifier and SLSA track/level conditions. An unsigned doc JSON cannot pass.
- **Security governance**: earliest failure evidence preserved, privately minimize crash and reproduce on clean pinned baseline, new regression test and corrections same WO/PR. HIGH/CRITICAL unresolved blocks, cannot auto-grant policy override. Incident recovery only in authorized sandbox and no destructive real backups.
- **Stats and drift**: repeated independent campaigns compared with same corpus/flags/source and environment, report coverage-growth confidence and diminishing returns without cherry-picking. Different fuzz engine/sanitizer instrumentation is non-comparable unless explicitly qualified. Negative controls prove finding trigger and rejection; false negatives tracked. Sampling traces/derived metrics cannot establish complete exploitability. Time/resources measured only after implementation.
- **Review**: output future `SecBenchmarkReceiptV1` source/head, actual compiler+sanitizer version, isolated host, license/corpus digest, input budget, findings/repro, CodeQL coverage, dependency/SBOM builder digest, security gate and real CI run URL. Do not claim SLSA from a JSON stub.
- **Current truth**: 80 WOs blocked, ADR-0078 PROPOSED, engine_implemented=false, no native code or security finding. The only actual CI for P00 is Docs Validation (links/catalog/registry selector) and it cannot satisfy these benchmark cases.

[128 future tests](../testing/qa-04-acceptance-matrix.md) · [security architecture](../architecture/qa-04-security-fuzzing-supply-chain.md) · [tool/license matrix](qa-04-security-fuzz-tools-license-risk-matrix.md).
