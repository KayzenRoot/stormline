# NLE-G3-V02-EXP-001 — Disposable C++20 Toolchain Probe (PROPOSED / NOT EXECUTABLE)
**STATUS: PROPOSED_NOT_AUTHORIZED_FOR_EXECUTION. No code, toolchain installation, native build, workflow or test is authorized.**
**Parent governance WO:** [`NLE-PRPLAN-CORE-01-01`](NLE-PRPLAN-CORE-01-01.md) | **Issue:** [#387](https://github.com/KayzenRoot/stormline/issues/387) | **Owner document-only authorization:** [#6945990286](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6945990286), 2026-11-17 | **Source baseline:** `29f3a440433b5f53dcf75a24a2fd8e0bc98195d6`.
This future candidate WO is NOT a CORE-01 planned packet, not an executable active WO and not a registry entry. Its ID is reserved for a possible later separately voted probe. **No decision on future experimental execution has been made.**

## OBJECTIVE
Specify, without implementing, a later minimal disposable C++20 fixture that would qualify compiler/build availability, compile/link execution and supply-chain provenance for G3-V01 candidate toolchains on Windows, Linux and macOS; report limitations and failures. Do NOT implement CORE-01 or claim engine/ABI compatibility.

## CONTEXT
G3-V01 `OWNER_RATIFIED_OPTION_A_ADJUSTED_CANDIDATE_ONLY`, G3 technically NOT CLEARED, G3-P01..P16 `FUTURE_NOT_EXECUTED`; G1 PARTIAL, G2 CLEARED only by docs ruleset `27393227`. Owner explicitly authorized **document preparation only** for G3-V02. G3-V02 experimental execution `NOT_AUTHORIZED`. ADR-0003/0075 `PROPOSED`, NLE-D009 `OPEN`; 80/80 coding WOs BLOCKED, 0 ready/approved ADR, CORE-01-01/02 PLANNED_BLOCKED, engine=false. Do not mistake this proposed new WO for promotion of implementation #18 or any packet.

## SCOPE
**Stage A (authorized now):** document fixture specification, per-OS candidate comparisons, licensing/SBOM, future test oracles, permission isolation, zero-paid-cost target, failure/rollback, evidence and separate decision text. Only documentation PR under parent `NLE-PRPLAN-CORE-01-01`.
**Stage B (future, NOT authorized):** a single tiny original C++20 console program with deterministic exit status, portable standard library subset and no Stormline source; future CMake configure/build/CTest with at least one executed test on each approved OS and toolchain candidate. Only after explicit new owner vote and separate contextual authorization.
**Stage C (future, NOT authorized):** collect logs and PE/ELF/Mach-O runtime/linkage evidence, repeat controlled builds, audit, discard binaries, and obtain a separate owner decision on technical adoption. A successful smoke fixture cannot certify SDL3, HostHandle, ABI, gameplay, 1.0 support or release readiness.

## OUT OF SCOPE
No real engine C++, SDK/plugin, renderer, host lifecycle, SDL3 windowed or actual true-headless application, API/ABI release, signing/notarization, paid dependencies/runners, workflows or G2 changes, registry/manifest/80 WOs, CORE-01-02, release classes/risks, licensing NLE-D009, ADR approval or G3 technical clearance. **No command, installation, compilation, source fixture, test, binary, native workflow, secrets or cost in this documentary increment.** Future scope increases require explicit owner vote.

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
Current documentary risk LOW; **future experimental execution risk ELEVATED PROPOSED ONLY** (third-party toolchains, supply chain, host execution, runners, ABI and secret-boundary risks). Do NOT alter the 80 module risk=UNCLASSIFIED/release_class=UNDECIDED values.
Future budget target **R$0, NOT GUARANTEED**: confirm repository public/runner standard eligibility, billing, artifact/cache allowances, retention, concurrent jobs and timeouts before authorizing. No larger paid runners, privileged self-hosted workers, vendor services, signing/notarization or secrets. Future workflows only under separately approved scope. If authorized later: `permissions: contents: read`, untrusted forks never get secrets; no privileged `pull_request_target` build of fork code nor `workflow_run` execution of untrusted artifacts; pin third-party Actions full SHA, verify archives/signatures, no unverified `curl | bash`, avoid upload of secrets. Bound CPU/time/network/log outputs. Insufficient safeguards => BLOCKED.

## ACCEPTANCE CRITERIA
**NOW (document-only):** complete 13-field proposal; P02..P14 table with honest out-of-scope partials; provenance, threat/cost, non-executable STOP clearly documented; only scoped Markdown in PR, docs-validation SUCCESS exact HEAD, objective pt-BR audit, squash/readback, separate checkpoint if owner authority materially changes canonical truth. No G3 test marked PASS.
**FUTURE hypothetical native acceptance (requires another owner authorization):** exact approved candidate tool installed with verified receipt or target NOT_QUALIFIED; compile/link/run original tiny C++20 app; >=1 real CTest per approved target (zero tests = FAIL); nonzero build/test exit = FAIL; one clean-run and repeat-run evidence with traceable artifacts/digests/flags; no silently substituted toolchain, secret/cost breaches or release claims. Probes are **not** product certification. Actual acceptable p95/RSS and stress remain subject to separate decisions.

## TESTS
**NOW:** documentation validation and Git/registry/readback only, no CMake/CTest, C++, SDL3, native Windows/Linux/macOS, sanitizers, installed SDK, artifact downloads or benchmark executed.
**FUTURE ONLY if owner separately authorizes:** compiler/version receipts and C++20 smoke fixture, CMake/CTest/Ninja, inspect binary dependencies for each platform, compare fallback failure behavior, verify SHA/signature, rerun build; zero selected tests explicit FAIL, unknown compiler/runner/SDK as NOT_QUALIFIED. Full SDL3/window/headless, lifecycle/HostHandle, tri-state, soak, sanitizers and 200/100/10k remain OUT OF SCOPE of first proposed fixture.

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
This PROPOSED WO, a [document-only evidence bundle](../evidence/NLE-PRPLAN-CORE-01-01-G3-V02-DOCUMENTARY-PREPARATION.md), explicit permission-bound Ledger/Scope and parent WO readback, GitHub Docs Validation and pt-BR audit, normal squash/HEAD readback and independent checkpoint if due. **FUTURE ONLY:** executable fixture and code/workflow proposal with fresh Context Lock and separate owner consent, no automatic promotion of original CORE-01 packets.

## REVIEW FORMAT
Documentary PR: `APPROVED DOCUMENTARY ONLY` / `CORRECTION REQUIRED` / `BLOCKED` with exact base/head, files, security/license/budget, tests truly performed, risks, CI receipt and proposed checkpoint delta. No `APPROVED EXPERIMENTAL EXECUTION` verdict is possible from this document.

## STOP CONDITION
Unexpected change in checkpoint/Ledger/Scope/DoD/Architecture/Requirements, main SHA, G2/ruleset/workflows, registry/manifest or scope; unavailable/paid tools, attempted code/fixture/tests/installation, privileged CI, missing owner consent, CI red or known HIGH/CRITICAL => BLOCKED. **After the documentary PR/checkpoint, STOP / AWAITING_OWNER** for an independent explicit execution vote. The experimental WO is not active, and none of 80 coding WOs is unlocked.

## Proposed future owner execution decision (NOT an approval today)
"After an independently audited documentary proposal, I explicitly authorize a separately scoped, disposable C++20 smoke fixture and the exact native checks, budgets, security and cleanup defined in a NEW approved execution order. This does NOT release CORE-01-02, engine code, licensing, ADRs or other gates." This example is not a vote.

## Official documentary references, not executed proof
- https://docs.github.com/en/billing/concepts/product-billing/github-actions
- https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target
- https://github.com/actions/runner-images/blob/main/README.md
- https://github.com/actions/runner-images/blob/main/images/macos/macos-15-arm64-Readme.md
- [G3 version/ABI research](../research/core-01-01-g3-toolchain-abi-qualification.md), [G3 owner vote](../evidence/NLE-PRPLAN-CORE-01-01-G3-V01-OWNER-RATIFICATION.md).
