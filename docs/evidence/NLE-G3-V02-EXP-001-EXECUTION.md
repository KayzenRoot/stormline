# G3-V02 EXP-001 — Native C++20 toolchain smoke Evidence Bundle
**STABLE WO:** [NLE-G3-V02-EXP-001](../work-orders/NLE-G3-V02-EXP-001-PROPOSED.md) | **Parent qualification WO:** `NLE-PRPLAN-CORE-01-01` | **Issue:** [#387](https://github.com/KayzenRoot/stormline/issues/387) | **Owner's explicit bounded experimental authorization:** [comment #6949434774](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6949434774) on 2026-11-17. **Context BASE/main:** `f360ff021021b54bbb0697c39c6a70cd37961e01`. **HEAD/PR/CI:** PENDING at creation; fill with actual readback before objective audit.
**Risk:** `ELEVATED` only for this experimental WO. Never classify the 80 engine coding WOs or release class via this result. **Scope:** EXACTLY seven files. No native result means `NOT_RUN`, not PASS.

## Source Check / Context Lock
Checkpoint > Decisions Ledger/ADRs > Scope > DoD > Architecture > Requirements > G3 qualification and this scoped WO. Git blobs from readback at `f360ff021021b54bbb0697c39c6a70cd37961e01`, not external SHA-256 toolchain hashes:
| Path | Base Git blob |
|---|---|
| `AGENTS.md` | `3e57b719f8651407879ebb641707a048773ea4c2` |
| `docs/11-checkpoint.md` | `a6bed80465a937f71d4247aac9500c22d09dccd1` |
| `docs/10-decisions-ledger.md` | `d58d6a772fa6b1b9d63e6adc43476c7dadbf0c21` |
| `docs/03-scope.md` | `7463efffef6c8f91096be3b70cf2f7f36ca264ea` |
| `docs/09-definition-of-done.md` | `082f8383b47f2bdc69d8d7c80812f3a94b0b96d1` |
| `docs/04-architecture.md` | `df62574cb3956c3ac9881631a4cf66be4e1abff1` |
| `docs/02-requirements.md` | `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b` |
| `docs/research/core-01-01-g3-toolchain-abi-qualification.md` | `78d58559d36b934b472edddc89c2333855952ebb` |
| `docs/queue/implementation-registry.json` | `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024` |
| `docs/pr-plans/manifest.json` | `95782386c59e5af8ac1a8c92a7a35c87992463db` |
| `ADR-0003` | `2ee92dda5ab81ddcc446b9d5325d29257350e217` |
| `ADR-0075` | `22e91a36c1e0a8121163fa4778abd0489fed86e5` |
| `G3-V02 prior WO proposal` | `bb1ae60be5683ae4757328f3b542d22c7b3439c1` |

## Exact allowed changed repository paths (7)
1. `experiments/g3-v02/main.cpp` : tiny original C++20 test, no engine imports.
2. `experiments/g3-v02/CMakeLists.txt` : one binary + one CTest.
3. `experiments/g3-v02/CMakePresets.json` : CMakePresets schema 6 and strict no-tests-error.
4. `experiments/g3-v02/README.md` : bounded scope/provenance and stop.
5. `.github/workflows/g3-v02-probe.yml` : PR-only, owner-branch guard, 3 standard runners, first-party checkout pinned to `11bd71901bbe5b1630ceea73d27597364c9af683`.
6. `docs/work-orders/NLE-G3-V02-EXP-001-PROPOSED.md` : new current bounded owner execution authority and restrictions.
7. This evidence file. **No code elsewhere, no existing docs CI modification, G2 rule/settings or registry/manifest/ADR writes.**

## Skills used, verified repository versions
- `stormline-source-check` `169cd933a19a044115d3e7a2404f69e1c44a9ac2`: Source hierarchy/Context Lock.
- `stormline-work-orders` `01ca364e0ff98589e052c5b45a726e2dcd59058f`: stable 13-field WO + execution delta.
- `stormline-platform-build` `1f4e5294ba76d5deae861299f33e02f485d03e6c`: isolated C++20/Ninja/CMake OS contracts.
- `stormline-ci-quality-gates` `e981e33266290b637ec9553f835c754f42c46579`: standard public runners, trust separation and actual job results.
- `stormline-test-planning` `e442e23979b708db7eeb9ed8b31fecd24c767fcc`: test count, failure/NOT_QUALIFIED oracles and G3 mapping.
- `stormline-security-review` `1171cb1d1f58f1f3c0e4086174b551b471483085`: fork isolation, secret/privilege avoidance.
- `stormline-license-compliance` `a31c9b5e8bbfc069271af978e9cc88bc7956012a`: use existing preinstalled compilers/build tools, no redistributed vendor assets and NLE-D009 OPEN.
- `stormline-evidence-audit` `a03e91662432e163f04b826a6d345449028fa54e`: exact-head CI verification and pt-BR verdict.

## Preflight target matrix: ACTUAL GITHUB JOB RESULTS PENDING
| Target | Ratified evaluation candidate | Status | Actual tests | Qualification scope |
|---|---|---|---|---|
| Linux x64 GCC | GCC 16.2, CMake 4.4.5, Ninja 1.13.2 | `PENDING_NATIVE_RUN` | 0 until readback | P03 Linux not applicable; P04/P06/P07 partial only |
| Linux x64 Clang | Clang 23.1.5, CMake 4.4.5, Ninja 1.13.2 | `PENDING_NATIVE_RUN` | 0 until readback | P04/P06/P07 partial only |
| Windows x64 MSVC | MSVC 14.50, SDK 10.0.26100.9457, CMake 4.4.5, Ninja 1.13.2 | `PENDING_NATIVE_RUN` | 0 until readback | P03/P06/P07 partial only |
| Windows x64 MSVC | MSVC 14.52 comparator, same SDK/build | `PENDING_NATIVE_RUN` | 0 until readback | P03/P06/P07 partial only |
| macOS 15 arm64 | Xcode 26.3, AppleClang full build UNKNOWN, CMake 4.4.5, Ninja 1.13.2 | `PENDING_NATIVE_RUN` | 0 until readback | P05/P06/P07 partial only |

**Status definitions:** `SMOKE_PASS` requires real exact-head C++20 compile/link, >=1 CTest pass, binary SHA; `NOT_QUALIFIED` means unavailable/mismatched preinstalled toolchain or SDK and **0 tests** (workflow job may still conclude `success` for accurate inventory, which is NOT native PASS); `FAIL` means qualified toolchain's build/CTest fails; `BLOCKED` for security/cost/scope; `PENDING_NATIVE_RUN` means no recorded CI evidence. No silent fallback or install.

## Proof obligations: narrowly interpreted
- `G3-P02`: source SHA-256 for fixture plus installed tool version strings, but complete third-party signed archives, transitive SPDX, SBOM/CVEs NOT proved by this experiment.
- `G3-P03/P04/P05`: only target combinations truly built on exact runner may receive a fixture-limited pass; unmatched variants remain NOT_QUALIFIED.
- `G3-P06`: Ninja/CMake and Presets/CTest only for matching preinstalled tools; CMake 4.5.0 comparator and min3.27 floor not automatically qualified.
- `G3-P07`: exact PR HEAD, runner/image version, compiler/build flags and SHA logged; repeat build is incremental, not a deterministic binary-reproducibility certificate.
- `G3-P14`: workflow only `pull_request`, `contents: read`, same-repo + exact-branch guard, no artifact/cache, no scripts downloaded, 3 standard public runner labels (Ubuntu 24.04, Windows 2025 VS2026, macOS 15 ARM64). Account-specific billing not inspected; target no incremental charges.
- `G3-P08..P13` FUTURE_NOT_EXECUTED; product SDL3, headless, HostHandle/ABI and benchmarks explicitly outside fixture. `G3-P01/P15/P16` not promoted and G3 not technically CLEARED.

## Security / rights / cost / rollback
Source fixture uses only C++20 standard-library headers and original test logic; no SDL3 or proprietary dependency linked/redistributed. GitHub-hosted standard runners used in public repo are documented free for compute; no larger runner/self-hosted/installer, secrets, upload-artifact, cache, signing or published binary. Exact owner-account monetary readback NOT_AVAILABLE; if a paid resource or privilege is required, stop. First-party `actions/checkout@11bd71901bbe5b1630ceea73d27597364c9af683` was verified as v4.2.2 from GitHub tag metadata before use. Binaries are ephemeral runner-local files; preserve only logs and SHA, not binaries. No G2 ruleset/required job modifications. Security risks HIGH/CRITICAL cause BLOCKED. Errors in this experiment are corrected on SAME branch/PR only.

## CI / audit / verdict (pending actual readback)
- Experiment PR and exact HEAD: `PENDING`; native job IDs and results: `PENDING`; `docs-validation`: `PENDING`; objective pt-BR audit: `PENDING`.
- DO NOT infer `SMOKE_PASS` from green docs validation or from a runner doing only preflight.
- Stop after this PR's objective audit; any next experimental setup/installs/PRs or engine development requires another explicit owner authorization. No checkpoint outside the allowlist; propose a factual delta only, do NOT apply it autonomously.
