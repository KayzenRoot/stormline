# QA-04 — Exactly 128 FUTURE Security, Fuzzing and Supply-Chain Acceptance Cases (Q04-T001..Q04-T128)

**2026-11-16 | P00 DOCUMENTARY RESEARCH; NO REAL C++/SANITIZER/FUZZ/STATIC/DAST/DEPENDENCY SCANS OR BUILDS.** [Research #353](https://github.com/KayzenRoot/stormline/issues/353), future coding [#93](https://github.com/KayzenRoot/stormline/issues/93) OPEN/BLOCKED; source HEAD `04f9ff54875b46fad05941529e1c6719fe79c394`. Formal dependencies **QA-01 + NET-06 + AI-06 ONLY**, their prior ADR-0075/0052/0065 and QA-04 ADR-0078 PROPOSED. **EXACTLY 8 groups × 16 = Q04-T001..Q04-T128 unique, ALL FUTURE / NOT EXECUTED, NO PASS.** Repo initial 74/80 researched and all 80/80 implementation WOs BLOCKED.

## Future acceptance and proof criteria
1. Before executing any case, validate actual approved source and license, checkpoint, SHA256 Context Lock and QA-01 C++20 build plus NET-06/AI-06 owner contracts. A docs-only PR cannot substitute for executable parser and policy.
2. C++ parser fuzz harnesses must accept bounded bytes, deterministic state/side effects and target the actual decoder/server/AI boundary, run with compatible Clang libFuzzer+ASan+UBSan and separate supported TSan/MSan; explain fuzzer maintenance limitations and alternative AFL++ licensing. Detect real counters/coverage/crashes, not absence-of-crash claims.
3. Corrupt original rights-cleared project/media/font/shader/GLTF/packet input and bounded resource consumption must be isolated from public servers/secrets. Untrusted origin, plugin capability or agent prompt cannot elevate owner privileges; NET-06/AI-06 perform actual enforcement.
4. Public CodeQL C++/`none` generated-code gap and optional `manual` build mode must be measured from real code; clang-tidy and dependency scanner advisories linked to source, no fabricated CVE/critical status.
5. SPDX 3.0.1/CycloneDX 1.7 SBOMs require actual compiled artifact and closure, exact source/rights/NOTICE, checked advisory match, signed SLSA v1.2 trusted subject only for real release. A static JSON/schema PASS is not an attested binary.
6. Security issue HIGH/CRITICAL known unresolved blocks next code/release; crash reproduction remains private, patch regression and owner incident decision required. Baseline repo rulesets zero and unprotected main **observed**, not corrected by these tests/proposals.
7. CI public standard runner compute free conditional, storage and privileged runners can cost; no paid cloud, secrets, active public DAST, self-hosted untrusted fork or dangerous permissions. No external copyright corpus.
8. Every future PASS includes exact HEAD/test ID, fixture rights, actual QA-01 job+sanitizer/scan result, type of policy decision, affected component/SBOM/attestation if relevant, severity and objective audit evidence; missing/unsupported tests => BLOCKED/NOT_EXECUTED.

## Group 1 — CPP20-MEMORY-SANITIZERS

| Future ID | Measurable future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q04-T001 | C++20 span parser rejects length overflow before allocation | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T002 | Import buffer out-of-bounds read causes sanitizer gate rather than silent PASS | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T003 | Use-after-free fixture under ASan yields minimized private reproducer | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T004 | Unaligned pointer/read lifetime abuse detected by compatible sanitizer setup | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T005 | Signed integer overflow and bad shift trigger UBSan in proper profile | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T006 | Network object ownership invalid after session epoch change is rejected | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T007 | Async job resource lifetime cancellation never dereferences stale data | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T008 | Stack recursion/memory exhaustion capped by parser depth and RSS quota | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T009 | Double-free and inconsistent allocator ownership caught by ASan or checks | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T010 | Release profile excludes sanitizer instrumentation and nonredistributable runtime | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T011 | ThreadSanitizer dedicated supported lane flags injected data race | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T012 | AddressSanitizer and ThreadSanitizer never incorrectly combined as one lane | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T013 | MemorySanitizer requires platform support and fully instrumented dependencies | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T014 | An unsupported MSan Windows/macOS lane reports UNSUPPORTED, not PASS | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T015 | Compiler diagnostic warning/clang-tidy finding cannot be marked suppressed by default | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |
| Q04-T016 | Unknown generated C++ source coverage returns incomplete rather than green | future compiled C++20 negative fixtures, exact clang/sanitizer job and reproducible crash | FUTURE / NOT EXECUTED |

## Group 2 — PARSERS-FUZZ-BOUNDARIES

| Future ID | Measurable future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q04-T017 | Binary asset parser zero-length input rejects deterministically | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T018 | Image PNG/EXR/GIF malformed header and oversized dimensions bounded | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T019 | GLB/glTF accessor offset and component stride overflow fail closed | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T020 | Scene JSON nested depth/exponential entities limited without CPU exhaustion | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T021 | Archive decompression ratio/total uncompressed size and recursion capped | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T022 | Zip-slip paths and symlinks cannot escape approved test sandbox root | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T023 | Unicode invalid UTF-8 path and normalization conflict rejected safely | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T024 | Shader source preprocessor recursion and includes constrained to asset scope | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T025 | Font glyph offsets and composite cycles bounded by target parser contract | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T026 | Audio WAV chunk lengths and compressed stream malformed input bounded | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T027 | Savegame deserialize unknown versions and schema mismatch fail non-destructively | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T028 | Network frame declared length exceeds size cap gives typed validation failure | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T029 | AI MCP tool-parameter JSON arbitrary large values bounded before policy | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T030 | libFuzzer corpus target shares correct Clang instrumentation+ASan UBSan | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T031 | AFL++ candidate persistent mode restores parser state each iteration | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |
| Q04-T032 | Minimized crash seed replays on clean pinned build with exact error signature | future isolated bounded fuzz campaign corpus/source/counterexample and real parser reject | FUTURE / NOT EXECUTED |

## Group 3 — NETWORK-SECURITY-AUTHORITY

| Future ID | Measurable future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q04-T033 | NET-06 untrusted connection never inherits verified-session trust by request text | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T034 | Client claimed server role or actor ownership fails server authoritative check | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T035 | Invalid session generation/nonce/replay cannot repeat privileged command | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T036 | Payload decompression cap prevents resource exhaustion before semantics | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T037 | Rate quota applies to verified principal plus target class, NAT fairness measured | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T038 | Connection churn and duplicate join requests bounded with idempotent outcomes | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T039 | Unverified transport/path state cannot mutate world or player inventory | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T040 | Revoked or expired account token denies further event/actions | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T041 | Malformed framing yields typed deny without leaking private state | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T042 | Game client sim-tick or clock falsification cannot elevate server authority | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T043 | Cross-room actor or world epoch access denied and audited | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T044 | Server/private data never included in rejection/log leakage | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T045 | Unauthorized in-game asset import outside project scope rejected | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T046 | Flood/resource exhaustion simulation bounded by CPU/RAM/time on local fixture | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T047 | NET-06 SecurityDecisionV1 actual enforcement receipt ties source and session | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |
| Q04-T048 | Network negative security case produces deterministic replay/CTest nonzero | future NET-06 server enforcement test against typed principal/trust/session/capability | FUTURE / NOT EXECUTED |

## Group 4 — AI-MCP-PLUGIN-SANDBOX

| Future ID | Measurable future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q04-T049 | AI-06 grant scope project-bound denies file writes to neighboring project | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T050 | Agent expired grant cannot be renewed through untrusted prompt text | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T051 | Owner consent required for destructive irreversible tool execution | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T052 | Revoked grant invalidates in-flight and repeated command when policy requires | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T053 | Dry-run plan cannot be promoted to execution without fresh approval | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T054 | AI tool result prompt injection cannot override system permission model | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T055 | Untrusted project README/asset text cannot expand agent tool capabilities | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T056 | MCP caller identity derived from verified transport context not clientInfo label | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T057 | File path traversal/symlink across project root denied by policy evaluator | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T058 | Plugin host function allowlist blocks arbitrary filesystem/network access | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T059 | Native plugin cannot claim sandbox safety merely by in-process ABI boundary | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T060 | WASM guest cannot access ungranted host filesystem/network by embedding import | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T061 | OS-specific sandbox capability unavailable returns UNSUPPORTED and blocks trust claim | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T062 | Agent audit receipt captures action grant epoch and consent without secrets | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T063 | Malicious plugin resource utilization bounded in isolated testing process | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |
| Q04-T064 | Independent AI-06 runtime deny outcome matches QA-04 security expectations | future AI-06 owner-enforced grants/consent/revocation sandbox negative receipts | FUTURE / NOT EXECUTED |

## Group 5 — CI-SAST-SCA-CACHE-SECRETS

| Future ID | Measurable future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q04-T065 | Public fork PR token read-only/no secrets/OIDC write or signing privilege | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T066 | pull_request_target cannot check out/run fork-controlled build scripts | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T067 | workflow_run artifacts treated untrusted data and never auto-executed | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T068 | Action dependency lockfile or verified full SHA pin required in future secure CI | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T069 | Current docs.yml mutable checkout major tag recorded as future hardening gap | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T070 | Cache key trust namespace prevents malicious PR poisoning protected build | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T071 | Stale cache source/toolchain digest mismatch triggers safe rebuild | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T072 | CodeQL public C++ none mode discloses generated-code coverage gap | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T073 | CodeQL manual mode source/database scan receipt matches actual compiler inputs | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T074 | clang-tidy compilation DB exact target and analyzer version are recorded | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T075 | Static/SARIF findings linked to source revision and nonzero failing policy | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T076 | Dependency scanner matches exact pinned version and withdrawn advisory correctly | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T077 | Unknown transitive dependency or vendored native library is visible | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T078 | Secret detector hides actual tokens/keys from public reports and artifacts | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T079 | Untrusted PR cannot upload/retrieve privileged release signing material | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |
| Q04-T080 | Missing or renamed required status check causes block not automatic approval | future QA-01 trusted CI CodeQL/static/SARIF/lockfile/action/cache/secret evidence | FUTURE / NOT EXECUTED |

## Group 6 — SBOM-SLSA-PROVENANCE-LICENSE

| Future ID | Measurable future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q04-T081 | SPDX 3.0.1 output validates format only after actual build subject exists | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T082 | CycloneDX 1.7 output validates dependency relations and hashes | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T083 | Transitive build/runtime dependencies represented with correct hierarchy | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T084 | Source code commit and binary artifact subject digest agree in SBOM | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T085 | License SPDX expression plus copyright/NOTICE obligations recorded for each package | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T086 | Engine source license OPEN prevents false public redistribution clearance | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T087 | AFL++ main AGPL-3.0-or-later and Apache file exception correctly represented | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T088 | SBOM unknown version/license represented as UNKNOWN not fabricated MIT | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T089 | OSV/GHSA affected version ranges matched to exact source component | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T090 | Advisory reachability/VEX claim supported by evidence and reviewer | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T091 | SLSA 1.2 track/level not inferred from plain unsigned JSON | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T092 | Trusted builder attestation subject SHA matches verified download bytes | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T093 | Attestation source/repo workflow identity signer and trusted provenance validated | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T094 | Tampered artifact or untrusted attestation identity triggers deny | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T095 | PLAT-05 owns actual signed publish; QA-04 only independently verifies | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |
| Q04-T096 | False SLSA/certification label blocked even when docs CI green | future real build SBOM/license/SLSA subject digest/signer and independent verification | FUTURE / NOT EXECUTED |

## Group 7 — INCIDENT-RESPONSE-RISK-PRIVACY

| Future ID | Measurable future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q04-T097 | High or critical known security finding blocks code and release gate | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T098 | Reproducer crash corpus private storage prevents public exploit leakage | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T099 | Incident owner acknowledges report and timestamps with scope and uncertainty | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T100 | Vulnerability classification distinguishes risk score from verified exploitation | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T101 | Private advisory report pathway avoids premature public disclosure | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T102 | Patch repair test replays original crash and proves regression no longer occurs | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T103 | Dependency emergency update checks ABI/license and introduced regressions | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T104 | Compromised artifact/signing key requires owner authorized revocation and rotation | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T105 | Rollback verifies signed trusted last-good subject and data migration safety | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T106 | Recovery drill includes reproducible offline restore without destructive bypass | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T107 | Telemetry consent revoked stops collection and purges permitted private data | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T108 | Log redaction strips PII project paths tokens from security evidence | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T109 | Confidential user projects never used as public fuzz or screenshot corpus | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T110 | GitHub rulesets zero observed is documented not claimed active protection | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T111 | R$0 budget guard halts unlimited security CI artifacts or paid runners | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |
| Q04-T112 | Incident review maintains immutable evidence timeline and independent audit | future private security case/incident workflow and authorized recovery evidence | FUTURE / NOT EXECUTED |

## Group 8 — EVIDENCE-GOVERNANCE-QUALITY-GATES

| Future ID | Measurable future acceptance scenario | Independent oracle | Status |
|---|---|---|---|
| Q04-T113 | Security evidence receipt includes base/head immutable SHA and source locks | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T114 | QA-01 actual scanner/fuzz CI job and toolchain hash verifiable | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T115 | NET-06 authoritative deny decision source and session epoch verified | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T116 | AI-06 grant scope consent/revocation actual deny evidence verified | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T117 | Fuzz campaign captures runs corpus coverage crashes and resource limits | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T118 | Crash minimization and deterministic replay attached with private access | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T119 | ASan UBSan TSan supported coverage and exceptions individually explicit | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T120 | CodeQL/C++ mode and generated-code missing scope reported | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T121 | SBOM signed subject/verifier and SPDX license notices reconciled | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T122 | Critical open advisory cannot be waived through missing scanner jobs | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T123 | Unapproved P00 document ADR status remains PROPOSED after merge | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T124 | Existing Docs Validation not mistaken for compiled security tests PASS | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T125 | Source Pack precedence or context change marks test work order STALE | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T126 | Observed CI failures or security HIGH/CRITICAL require correction before next | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T127 | All eighty implementation WOs stay blocked after documentation checkpoint | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q04-T128 | Release security approval requires actual owner DoD and no HIGH/CRITICAL | future cross-source QA-01/NET-06/AI-06 actual reports and pt-BR objective audit | FUTURE / NOT EXECUTED |


## Current truth
The catalog acceptance "Fuzzing e auditoria de riscos HIGH/CRITICAL antes de release" is **NOT IMPLEMENTED or TESTED**. No product build, memory sanitizer result, CodeQL report, fuzzer corpus, SBOM/provenance, privileged plugin sandbox, incident recovery drill or signed release exists from QA-04 P00. Q04-T001..Q04-T128 remain FUTURE/NOT EXECUTED. Existing GitHub Docs Validation may be green for these Markdown files, but is not an engine security test. Keep all 80 coding WOs BLOCKED and ADR-0078 PROPOSED.

[Architecture](../architecture/qa-04-security-fuzzing-supply-chain.md) · [benchmark](../research/qa-04-fuzz-security-benchmark-protocol.md) · [semantic API](../contracts/qa-04-security-evidence-api.md).
