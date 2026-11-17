# NLE-G3-V02-EXP-001 — Disposable C++20 Toolchain Probe (SCOPED EXPERIMENTAL EXECUTION ONLY)
**CURRENT STATUS (2026-11-17): EXPERIMENT_EXECUTION_AUTHORIZED_SCOPED. Scope limited strictly to seven enumerated files. Native fixture/CTest allowed only with exact preinstalled candidates, standard public runners, zero secrets and zero paid services. No production engine implementation, ADR/G3 approval or 80-WO promotion.**
**Parent governance WO:** [`NLE-PRPLAN-CORE-01-01`](NLE-PRPLAN-CORE-01-01.md) | **Issue:** [#387](https://github.com/KayzenRoot/stormline/issues/387) | **Owner document-only authorization:** [#6945990286](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6945990286), 2026-11-17 | **Source baseline:** `29f3a440433b5f53dcf75a24a2fd8e0bc98195d6`.
This experimental WO is now **owner-authorized only for one bounded disposable toolchain probe**. It is NOT an active CORE-01 module implementation packet, not a registry entry, and does not authorize any later coding WO or technical adoption. Historic draft language below about awaiting execution permission is superseded **only for this exactly enumerated probe**.

## CURRENT OWNER AUTHORITY, PRE-FLIGHT AND EXACT SEVEN-FILE ALLOWLIST (2026-11-17)
**Authority:** [owner's explicit bounded execution vote in issue #387, #6949434774](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6949434774), referring to main `f360ff021021b54bbb0697c39c6a70cd37961e01`, not an inferred approval. **Risk:** `ELEVATED` approved only for this isolated experiment; 80 module risk/release classifications remain unchanged. **Source Check:** fresh checkpoint > Ledger/ADRs > Scope > DoD > Architecture > Requirements; G2 active ruleset `27393227`, required docs-validation unchanged, 0 engine implementation WOs ready, G3-V01 candidate only, ADR-0003/0075 PROPOSED, NLE-D009 OPEN. Main and source fingerprints must be rechecked before merge.

**Only repository paths permitted:** `experiments/g3-v02/main.cpp`, `experiments/g3-v02/CMakeLists.txt`, `experiments/g3-v02/CMakePresets.json`, `experiments/g3-v02/README.md`, `.github/workflows/g3-v02-probe.yml`, this WO `docs/work-orders/NLE-G3-V02-EXP-001-PROPOSED.md`, and `docs/evidence/NLE-G3-V02-EXP-001-EXECUTION.md`. No other repository file may be created or changed, including checkpoint, ADRs, registry, manifest, G2, workflows/docs.yml or product source.

**Only experimental operations permitted:** one C++20 portable no-engine/no-third-party fixture, five candidate compiler checks on standard GitHub-hosted public Windows/Linux/macOS runners via a single PR-only, branch-guarded workflow; no installer or substitutions. For an exact preinstalled toolchain with CMake **4.4.5** and Ninja **1.13.2**, configure, compile/link/run through **>=1 CTest**, repeat incremental build, hash output and inspect PE/ELF/Mach-O as supported. If any exact candidate is absent, record `NOT_QUALIFIED` with **0 tests** for that candidate, not `PASS` or a substituted version; continue independently qualified configurations only. CMake 4.5.0 comparator, CMake3.27 minimum/schema6, SDL3 3.4.20 provenance are candidates only and not automatically qualified by this smoke. No download, self-hosted or paid larger runner, secrets, deployment, code signing, bin artifact/cache upload or checkout from untrusted forks. `actions/checkout` commit pinned to reviewed SHA `11bd71901bbe5b1630ceea73d27597364c9af683` (v4.2.2).

**Proof limit:** actual partial G3-P02..P07/P14 observations only when evidence exists. P08..P13 continue FUTURE_NOT_EXECUTED, and P01/P15/P16 and final G3 remain pending; do not change canonical proof table or ADR. **Audit/STOP:** exact-head Docs Validation and native job readbacks, security/cost analysis and pt-BR audit; no automatic merge on failing required check or HIGH/CRITICAL. If no supported version qualifies, stop with an honest NOT_QUALIFIED evidence bundle; no new tool installation. After this bounded PR's audit and closeout, **STOP** until a new express owner decision for any next stage. Engine remains `engine_implemented=false`.

## OBJECTIVE
Specify, without implementing, a later minimal disposable C++20 fixture that would qualify compiler/build availability, compile/link execution and supply-chain provenance for G3-V01 candidate toolchains on Windows, Linux and macOS; report limitations and failures. Do NOT implement CORE-01 or claim engine/ABI compatibility.

## CONTEXT
G3-V01 `OWNER_RATIFIED_OPTION_A_ADJUSTED_CANDIDATE_ONLY`, G3 technically NOT CLEARED, G3-P01..P16 `FUTURE_NOT_EXECUTED`; G1 PARTIAL, G2 CLEARED only by docs ruleset `27393227`. Owner explicitly authorized **document preparation only** for G3-V02. G3-V02 experimental execution `NOT_AUTHORIZED`. ADR-0003/0075 `PROPOSED`, NLE-D009 `OPEN`; 80/80 coding WOs BLOCKED, 0 ready/approved ADR, CORE-01-01/02 PLANNED_BLOCKED, engine=false. Do not mistake this proposed new WO for promotion of implementation #18 or any packet.

## SCOPE
**Stage A (authorized now):** document fixture specification, per-OS candidate comparisons, licensing/SBOM, future test oracles, permission isolation, zero-paid-cost target, failure/rollback, evidence and separate decision text. Only documentation PR under parent `NLE-PRPLAN-CORE-01-01`.
**Stage B (NOW AUTHORIZED ONLY BY THE NEW BOUNDED VOTE ABOVE):** a single tiny original C++20 console program with deterministic exit status, portable standard library subset and no Stormline source; future CMake configure/build/CTest with at least one executed test on each approved OS and toolchain candidate. Under the explicit 2026-11-17 vote only, with seven-file allowlist, exact toolchain and cost/security controls; no expansion.
**Stage C (NOW AUTHORIZED ONLY FOR RECEIPTS, INDEPENDENT AUDIT AND DISPOSAL):** collect logs and PE/ELF/Mach-O runtime/linkage evidence, repeat controlled builds, audit, discard binaries, and obtain a separate owner decision on technical adoption. A successful smoke fixture cannot certify SDL3, HostHandle, ABI, gameplay, 1.0 support or release readiness.

## OUT OF SCOPE
No real engine C++, SDK/plugin, renderer, host lifecycle, SDL3 windowed or actual true-headless application, API/ABI release, signing/notarization, paid dependencies/runners, workflows or G2 changes, registry/manifest/80 WOs, CORE-01-02, release classes/risks, licensing NLE-D009, ADR approval or G3 technical clearance. **This separate experimental increment permits only the original seven-file fixture/native workflow and corresponding CI tests. Installing SDKs, paid operations, secrets, product code and out-of-scope changes remain prohibited.** Future scope increases require explicit owner vote.

## FILES/SOURCES TO READ
Checkpoint > Ledger/ADRs > Scope > DoD > Architecture > Requirements > [AGENTS.md](../../AGENTS.md) > parent [WO](NLE-PRPLAN-CORE-01-01.md) > [G3 matrix](../research/core-01-01-g3-toolchain-abi-qualification.md), [CORE-01 gates](../engineering/core-01-01-qualification-gates.md), [P00 gates](../engineering/p00-technical-approval-gates.md), [ADR-0003](../adr/0003-core-01-platform-technology.md) and [ADR-0075](../adr/0075-qa-01-ci-matrix-security-policy.md), [registry](../queue/implementation-registry.json), [manifest](../pr-plans/manifest.json), skills manifest/skill instructions, official toolchain and runner/billing/security sources. Future executable WO must run fresh Source Check before any modification.

## REQUIREMENTS
**G3-V01 candidate matrix (NOT installed/pinned product tools):**
| Target | Ratified future evaluation candidates | Evidence future probe should capture |
|---|---|---|
| Windows x64 | C++20; MSVC **14.50 reference**, **14.52 comparator**, Windows SDK **10.0.26100.9457** | `cl /Bv`, `_MSC_FULL_VER`, VS build tools, linker, SDK, CRT/redist, executable compile/link/exit |
| Ubuntu 24.04 x64 | GCC **16.2** reference, Clang **23.1.5** comparator | `g++`/`clang++` full versions, stdlib, glibc/GLIBCXX symbols, ELF dependencies |
| macOS 15 arm64 | **Xcode 26.3** candidate, full AppleClang **UNKNOWN** | `xcodebuild -version`, selected `DEVELOPER_DIR`, `xcrun clang --version`, SDK, deployment target, Mach-O |
| Build | CMake **4.4.5 reference**, **4.5.0 comparator**, Ninja **1.13.2** | CMake/CTest/Ninja full versions; configure/build/`ctest --preset`, zero-test fail, clean/incremental |
| Candidate compatibility floor | CMake minimum **3.27** and CMakePresets **schema 6**, candidates only | Future separate compatibility check; no promotion to product minimum |
| SDK provenance only | SDL3 **3.4.20** | Exact source tag, license/notice/sha256 for future use, NOT linked or tested initially |

For each future OS/configuration produce an environment receipt with original source SHA/fixture hash, runner image version, OS/arch, compiler FULL build/linker/stdlib/CRT, SDK, flags, exact downloaded archive digests, dependency SPDX/licenses/transitives/NOTICE, test count + exit code, executable checksum and binary dependencies. Do not silently substitute a missing candidate with a newer version, claim `latest` reproducible or compare binary hashes across different OS as proof of equivalence.

## ARCHITECTURE RULES
Fixture stays isolated and disposable, without real CORE-01 module imports, product architecture decisions or exposed C++/C ABI. No cross-CRT allocations or mixing incompatible MSVC LTCG objects, no plugin/SDK and no actual HostHandle implementation. All normal Win/Linux/macOS ownership and ABI claims remain future obligations. No remote data/tracking or networked runtime. Provenance of installed tools must be distinguished from published versions and actual validated builds.

## CONSTRAINTS
Prior documentary stage risk LOW; **current bounded experimental execution risk ELEVATED OWNER-AUTHORIZED ONLY FOR THIS FIXTURE** (third-party toolchains, supply chain, host execution, runners, ABI and secret-boundary risks). Do NOT alter the 80 module risk=UNCLASSIFIED/release_class=UNDECIDED values.
Current budget ceiling **R$0 incremental charges, only standard public runners, no artifact/cache uploads; billing must be rechecked and execution stops on any paid requirement**: confirm repository public/runner standard eligibility, billing, artifact/cache allowances, retention, concurrent jobs and timeouts before authorizing. No larger paid runners, privileged self-hosted workers, vendor services, signing/notarization or secrets. Future workflows only under separately approved scope. If authorized later: `permissions: contents: read`, untrusted forks never get secrets; no privileged `pull_request_target` build of fork code nor `workflow_run` execution of untrusted artifacts; pin third-party Actions full SHA, verify archives/signatures, no unverified `curl | bash`, avoid upload of secrets. Bound CPU/time/network/log outputs. Insufficient safeguards => BLOCKED.

## ACCEPTANCE CRITERIA
**Original Stage A documentary acceptance (already audited):** complete 13-field proposal; P02..P14 table with honest out-of-scope partials; provenance, threat/cost, non-executable STOP clearly documented; only scoped Markdown in PR, docs-validation SUCCESS exact HEAD, objective pt-BR audit, squash/readback, separate checkpoint if owner authority materially changes canonical truth. No G3 test marked PASS.
**CURRENT bounded native acceptance (only exact preinstalled candidates, no engine adoption):** exact approved candidate tool installed with verified receipt or target NOT_QUALIFIED; compile/link/run original tiny C++20 app; >=1 real CTest per approved target (zero tests = FAIL); nonzero build/test exit = FAIL; one clean-run and repeat-run evidence with traceable artifacts/digests/flags; no silently substituted toolchain, secret/cost breaches or release claims. Probes are **not** product certification. Actual acceptable p95/RSS and stress remain subject to separate decisions.

## TESTS
**ORIGINAL Stage A:** documentation validation and Git/registry/readback only; no native tests were performed by the previous PR. This current experiment authorizes only the bounded native C++20 smoke and evidence named above.
**NOW, only to the extent of the 2026-11-17 owner vote:** compiler/version receipts and C++20 smoke fixture, CMake/CTest/Ninja, inspect binary dependencies for each platform, compare fallback failure behavior, verify SHA/signature, rerun build; zero selected tests explicit FAIL, unknown compiler/runner/SDK as NOT_QUALIFIED. Full SDL3/window/headless, lifecycle/HostHandle, tri-state, soak, sanitizers and 200/100/10k remain OUT OF SCOPE of first proposed fixture.

## G3-P02..P14 proof mapping: none executed
| G3 ID | Stage A documentary output | Stage B/C future scope limit |
|---|---|---|
| P02 | Source URLs, hash/signature/SBOM and license receipt format | Verify exact used artifacts only |
| P03 | Windows toolset/SDK/CRT receipt + smoke oracle | Does not certify entire Windows ABI |
| P04 | Linux compiler/stdlib/glibc receipt + smoke oracle | Does not certify all Linux deployments |
| P05 | macOS Xcode/AppleClang/SDK/deployment receipt | Does not certify macOS hardware behavior |
| P06 | CMake 4.4.5/4.5.0, CTest/presets/Ninja oracle | CMake3.27/schema6 still candidates |
| P07 | Environment lock/image digest/build provenance fields | Actual reproducibility later |
| P08 | Specify SDL3 main-thread/window/IME/hotplug test plan | EXCLUDED FROM FIRST FIXTURE |
| P09 | Specify displayless true-headless/<=5s negative scenario | EXCLUDED FROM FIRST FIXTURE |
| P10 | Specify lifecycle/error/fault-injection tests | EXCLUDED FROM FIRST FIXTURE |
| P11 | Specify HostHandle/generation/allocator/ABI tests | EXCLUDED FROM FIRST FIXTURE |
| P12 | Specify tri-state capability/SAPL threshold dependency | EXCLUDED FROM FIRST FIXTURE |
| P13 | Specify 200/100/10k, 30+30, sanitizers and p95/RSS approvals | EXCLUDED FROM FIRST FIXTURE |
| P14 | Define fork/security/runner/cost receipt | Native CI verification future |
**G3-P01, P15, P16 are also FUTURE_NOT_EXECUTED in the canonical matrix.** No proof is promoted to PASS by a documentary PR or fixture alone.

## DELIVERABLES
This PROPOSED WO, a [document-only evidence bundle](../evidence/NLE-PRPLAN-CORE-01-01-G3-V02-DOCUMENTARY-PREPARATION.md), explicit permission-bound Ledger/Scope and parent WO readback, GitHub Docs Validation and pt-BR audit, normal squash/HEAD readback and independent checkpoint if due. **CURRENT bounded experiment:** the seven allowed paths above, exact native check readback and an audit. No automatic promotion of original CORE-01 packets or G3.

## REVIEW FORMAT
This experimental PR: `APPROVED EXPERIMENTAL ONLY` / `CORRECTION REQUIRED` / `BLOCKED` with exact base/head, files, security/license/budget, tests truly performed, risks, CI receipt and proposed checkpoint delta. The separate owner vote is now present only for this experiment; an EXPERIMENTAL ONLY audit never grants engine-G3/ADR implementation authorization.

## STOP CONDITION
Unexpected change in checkpoint/Ledger/Scope/DoD/Architecture/Requirements, main SHA, G2/ruleset/workflows, registry/manifest or scope; unavailable/paid tools, attempted code/fixture/tests/installation, privileged CI, missing owner consent, CI red or known HIGH/CRITICAL => BLOCKED. **After this experimental PR is audited, STOP / AWAITING_OWNER** before any additional probe or module. This WO is executable ONLY for its enumerated experimental fixture and none of 80 coding WOs is unlocked.

## Historical proposed owner execution decision (SUPERSEDED only for bounded 2026-11-17 experiment)
"After an independently audited documentary proposal, I explicitly authorize a separately scoped, disposable C++20 smoke fixture and the exact native checks, budgets, security and cleanup defined in a NEW approved execution order. This does NOT release CORE-01-02, engine code, licensing, ADRs or other gates." This example is not a vote.

## Official documentary references, not executed proof
- https://docs.github.com/en/billing/concepts/product-billing/github-actions
- https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target
- https://github.com/actions/runner-images/blob/main/README.md
- https://github.com/actions/runner-images/blob/main/images/macos/macos-15-arm64-Readme.md
- [G3 version/ABI research](../research/core-01-01-g3-toolchain-abi-qualification.md), [G3 owner vote](../evidence/NLE-PRPLAN-CORE-01-01-G3-V01-OWNER-RATIFICATION.md).
