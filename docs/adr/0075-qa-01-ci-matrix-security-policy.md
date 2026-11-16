# ADR-0075 — Zero-Cost, Trust-Separated C++20 Multi-OS CI Matrix and Evidence Policy

**2026-11-16 | P00 DOCUMENTARY RESEARCH ONLY | [research #341](https://github.com/KayzenRoot/stormline/issues/341) | NLE-P00-WO-002-QA-01 | [future code #90](https://github.com/KayzenRoot/stormline/issues/90) OPEN/BLOCKED | base main `9591ef730b3d0982f8370b7dfa29d58a0fbd288f`.** Catalog ordinal 72/80, formal dependency **CORE-01 ONLY** and [ADR-0003](../adr/0003-core-01-platform-technology.md) PROPOSED, not implemented. Baseline 71/80 researched, 9 pending, all 80 future implementation WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved ADR=0, release_class UNDECIDED all, engine_implemented=false, source license NLE-D009 OPEN, NLE-D013 no public MVP.


**STATUS: PROPOSED / NOT OWNER-RATIFIED / NO CODE OR GITHUB ACTIONS WORKFLOW ACTIVATION.**

## Problem
How can Stormline prove builds/tests on Windows/Linux/macOS with an affordable, reproducible and secure C++20 CI without confusing Docs Validation with compilation, making untrusted PRs privileged, silently paying for runners/storage or declaring a platform supported from an ephemeral VM? CORE-01's proposed SDL3/C++20/CMake+Ninja has no built engine or approved ABI.

## PROPOSED decisions
1. **Formal dependency only CORE-01**, source ADR-0003 PROPOSED. QA-01 builds/validates approved CORE-01 and later owned native integrations but **does not** alter catalog DAG to PLAT, QA-02, QA-04, QA-05, CORE-06, PLAT-05 or BIZ-03. QA-02/03/04/05 remain specialized owners (golden/perf/security/device qualification) and PLAT-05 owns exporter/delivery; QA-01 only orchestrates their future approved checks.
2. **Canonical C++20 baseline with pinned CMake Presets/CTest Presets + Ninja**, native GCC/Clang on Linux, MSVC/clang-cl on Windows and AppleClang on Apple Silicon macOS. Exact SDK/compiler versions, runner image/build SHA, toolchain/stdlib/arch, source HEAD, source lock and fixture hashes recorded for every future receipt; no C++23 feature relied on before matrix passes. No CMakeLists, binary or workflow written in P00.
3. **Public standard GitHub-hosted runners R$0 policy.** GitHub's [billing docs](https://docs.github.com/en/billing/concepts/product-billing/github-actions) say standard runners in public repo free for compute; repo actually public as Source Check, but larger runners and storage overages, private repo use and hosted ancillary services can be paid. Choose eligible standard Ubuntu/Windows/macOS labels by explicit supported images, collect runner/software metadata and preserve **hard cost guard** for artifact/cache usage, retention/fanout/runtime and any plan/visibility change. If 0-cost cannot be demonstrated => BLOCKED, not charge.
4. **Trust-boundary isolation**: untrusted fork PR jobs read-only token and no secrets/signing/OIDC deploy; **never** checkout fork PR code in a `pull_request_target` privileged context and execute it, nor trust `workflow_run` downloaded artifacts. Pin external Actions to full commit SHA after audit (existing Docs Validation `actions/checkout@v7` remains unchanged in P00; future tightening separate approved WO). Cache is untrusted input with branch/trust-scoped immutable keys and restore digest verification, never store secrets; branch rulesets and required checks adopted only after names/status appear stable, no blind modification (currently **0 repository rulesets observed**).
5. **Future gates**: formatting with pinned clang-format (nonmutating), CMake configure/build with -Werror/compiler-specific warning allowances and C++20 semantic/type diagnostics, clang-tidy/clang static analyzer, CodeQL public C++ when owner approves mode, `CTest` >0 runnable expected tests with fixture/result hashes, CTest JUnit, controlled integration. Never consider a job green when required tests skipped/zero/failed or `continue-on-error` concealed severity.
6. **Sanitizers selected by actual host/compiler**: Linux ASan+UBSan lane, separate TSan where supported and with higher resource budget; Linux MSan only if full instrumented dependencies available; Windows ASan where compiler/runtime supports, macOS ASan and TSan conditionally, never unconditional universal MSan. Separate tests across runtimes, no sanitizer binaries shipped, code/high-security issues block, no TSan reports suppressed globally.
7. **Evidence receipts**: versioned CI plan, per-job OS/arch/toolchain/image/commit, exact compiler commands/source SHA/diagnostic version, CTest count/skip/xfail, lint/static SARIF, sanitizer flags, warnings/config, artifacts SHA256/retention/cost, conclusion and actual run URL; capture failed/timeout/canceled jobs and fork trust classification. SHA/provenance files are not SLSA certificates, and Docs CI green is evidence only of docs checks. QA-04/PLAT-05 own actual SBOM/SLSA and final binary sign/deploy, future GitHub attestations conditional trusted workflow and verified digest.
8. **Solo governance**: prepare PR with stable job/check names, read-only free CI, merge only after actual checks and audit pt-BR. Existing docs-only workflow cannot prove C++ build; current zero rulesets observed means no enforced required checks claim. Do not modify CI/ruleset in research P00 and no public MVP before full v1.0 DoD.
9. **128 unique FUTURE Q01 tests and physical/cross-run benchmark**, eight groups 16; all NOT EXECUTED. Actual compilers/lints/sanitizers/hosted runner matrix absent today, no target compatibility/green build claim. 80 code WOs remain BLOCKED, approved ADR count 0, executor_ready 0 and source license OPEN.

## Alternatives explicitly declined until proven
| Alternative | Appeal | Why not automatic |
|---|---|---|
| Mark engine build green from Docs Validation | fast progress | docs workflow only validates Markdown/catalog/queue |
| Always use `ubuntu-latest/windows-latest/macos-latest` | convenience | installed images drift; pin named labels and record exact versions |
| Paid larger macOS runners | speed | violates GOV-003 zero-cost and requires user approval |
| Self-hosted VPS runner for public fork PRs | more cores | untrusted code exfil/local network persistence; isolation proof absent |
| Auto-install newest compiler from unpinned URL | easy updates | toolchain drift/supply-chain and license uncertainty |
| Require MSan/TSan on all OS | maximum coverage | impossible/unsupported combinations and memory/time costs |
| Fail open when test suite empty | quick green | no actual evidence of functionality |
| Silence warnings with global `-w` or `continue-on-error` | fewer red CI | hides regressions/high risk |
| Execute fork scripts with `pull_request_target` write token | easy privileged review | trust boundary violated |
| Share PR cache freely with protected main | fast compile | poisoning and credential leak |
| Always use CodeQL `none` mode as fully complete | simplest setup | generated code omitted, manual build often more complete |
| Auto-add required checks/rulesets before jobs exist | security appearance | missing/stale names can block all PRs; current source has zero active rulesets |
| Claim SLSA L3 from static JSON metadata | marketing | builder trust/isolation + signed/verified attestation required |
| Full 80-module build matrix on first CI | exhaustive | no code, cost/resource and unsupported SDK, use staged NECESSARY checks |
| Ship ASan/TSan binaries | test parity | sanitizer runtime not production-hardened |
| Build/upload signed release on every PR | convenience | private keys, source license OPEN, no public MVP, owner cost/approval |

## Future owner gates
Actual CORE-01 merged/approved code contracts and prerequisites, selected compiler/library/SDK and target architecture, source license, representative runtime fixtures, free storage budget and effective policy, approved branch rule requirements, security review and signed release gates. QA-01 P00 research accepted only as planning, not a pipeline deployment.

[Architecture](../architecture/qa-01-build-ci-orchestration.md) · [toolchain/cost matrix](../research/qa-01-toolchain-runner-license-cost-matrix.md) · [CI evidence API](../contracts/qa-01-ci-evidence-api.md).
