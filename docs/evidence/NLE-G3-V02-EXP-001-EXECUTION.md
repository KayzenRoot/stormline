# G3-V02 EXP-001 — Native C++20 toolchain smoke Evidence Bundle
**STABLE WO:** [NLE-G3-V02-EXP-001](../work-orders/NLE-G3-V02-EXP-001-PROPOSED.md) | **Parent qualification WO:** `NLE-PRPLAN-CORE-01-01` | **Issue:** [#387](https://github.com/KayzenRoot/stormline/issues/387) | **Owner's explicit bounded experimental authorization:** [comment #6949434774](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6949434774) on 2026-11-17. **Context BASE/main:** `f360ff021021b54bbb0697c39c6a70cd37961e01`. **PR:** [#419](https://github.com/KayzenRoot/stormline/pull/419). **First observed native workflow HEAD:** `a254f0ca39fd41f63afe379db7444e64a537dcfc`, run [#44093744034](https://github.com/KayzenRoot/stormline/actions/runs/44093744034), `completed/success` for all 3 OS jobs; **Docs Validation** [run #44093743880](https://github.com/KayzenRoot/stormline/actions/runs/44093743880), `completed/success`. The final HEAD changes only this evidence document and requires a new exact-HEAD CI readback and objective audit before merge.
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
| Linux x64 GCC | GCC 16.2, CMake 4.4.5, Ninja 1.13.2 | `NOT_QUALIFIED` | 0 | P03 Linux not applicable; P04/P06/P07 partial only |
| Linux x64 Clang | Clang 23.1.5, CMake 4.4.5, Ninja 1.13.2 | `NOT_QUALIFIED` | 0 | P04/P06/P07 partial only |
| Windows x64 MSVC | MSVC 14.50, SDK 10.0.26100.9457, CMake 4.4.5, Ninja 1.13.2 | `NOT_QUALIFIED` | 0 | P03/P06/P07 partial only |
| Windows x64 MSVC | MSVC 14.52 comparator, same SDK/build | `NOT_QUALIFIED` | 0 | P03/P06/P07 partial only |
| macOS 15 arm64 | Xcode 26.3, AppleClang exact build captured, CMake 4.4.5, Ninja 1.13.2 | `SMOKE_PASS` limited to fixture | 1/1 CTest | P05/P06/P07 partial only |

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

## OBSERVED NATIVE RECEIPT, FIRST EXACT TESTED HEAD a254f0ca39fd41f63afe379db7444e64a537dcfc (2026-11-17)
**Runs:** [native workflow #44093744034](https://github.com/KayzenRoot/stormline/actions/runs/44093744034), [docs workflow #44093743880](https://github.com/KayzenRoot/stormline/actions/runs/44093743880). Three native jobs show `completed/success` for preflight/conditional tests. This means OS workflow ran successfully; it does **NOT** mean all five candidate toolchains passed. `docs-validation` `completed/success`. **Objective pt-BR audit, final PR HEAD and merge: PENDING at this evidence edit.**

| GitHub job | Runner image / actual observations | Native truth and log |
|---|---|---|
| [Linux #134075331128](https://github.com/KayzenRoot/stormline/actions/runs/44093744034/job/134075331128) | Ubuntu 24.04 x64, image `20261111.370.1`, glibc `2.39-0ubuntu8.9`, GCC `13.3.0`, Ubuntu Clang `18.1.3`, CMake `3.31.6`, Ninja `1.13.2` | Both exact GCC16.2 and Clang23.1.5 `NOT_QUALIFIED`; **0 native tests** |
| [Windows #134075330689](https://github.com/KayzenRoot/stormline/actions/runs/44093744034/job/134075330689) | Image `20261103.298.1`, MSVC directories `14.29.30133`, `14.44.35207`, `14.51.36231`; exact SDK `10.0.26100.9457` check FALSE; CMake `4.4.5`, Ninja `1.13.2` | MSVC14.50 and MSVC14.52 `NOT_QUALIFIED`; **0 native tests**. Did not substitute 14.51 or install SDK |
| [macOS #134075331342](https://github.com/KayzenRoot/stormline/actions/runs/44093744034/job/134075331342) | macOS `15.8.2` ARM64, image `20261112.0539.3`; Xcode `26.3`; `Apple clang version 17.0.0 (clang-1700.6.4.2)`, CMake compiler identity `AppleClang 17.0.0.17000604`; macOS SDK `26.2`; CMake `4.4.5`, Ninja `1.13.2` | **`SMOKE_PASS`**, C++20 compiled + linked, `g3_v02_cpp20_smoke` **1/1 CTest PASS**, second incremental Ninja build `no work to do`; Mach-O linkage inspected via `otool -L` |

**macOS executable SHA-256:** `b0cff092deb5b9b8cc18e2909f1b591539b400d15f783465ec0ad8dd61afcdfc`. Linked `/usr/lib/libc++.1.dylib` and `/usr/lib/libSystem.B.dylib`. Fixture source SHA-256 on Linux/macOS: `main.cpp ba6df43a13737ed5d434fc491f74a3107ffcb294f57ff9d28e163a40cc2ffbbe`; `CMakeLists.txt 3021afac500574b19496c80b7fa9f3ebe383dedb7a51cc628a26cf8f34665649`; `CMakePresets.json d2858e86e0c38148d541ba1ff887ef80837dff0e77a93526966388dea354727d`. Windows checked-out file hashes printed differently in PowerShell output, so do not infer cross-OS bit-for-bit source identity without examining line-ending normalization.

**Interpretation:** the first fixture gives limited evidence for `G3-P05` (macOS compiler/SDK smoke), `G3-P06` (macOS CMake/CTest/Ninja) and `G3-P07` (runner provenance; only incremental rebuild), plus a narrow implementation check relevant to `G3-P14` (three public standard jobs, least privilege and fork guard). It does NOT prove full P02 SBOM/signatures/CVE state, Windows P03 or Linux P04, compatible CMake 4.5.0 comparator/floor, deterministic independent clean rebuild, SDL3, true headless, ABI/HostHandle, lifecycle, SAPL, benchmarks or final G3 approval. **No canonical G3-P status is promoted to PASS by this bundle.** Report missing toolchains as NOT_QUALIFIED, not FAIL or PASS. No paid runner, cache, artifact upload or secrets used in these workflow steps. GitHub account billing readback not obtained.

## CI / audit / verdict (final audit pending)
- PR #419, initial tested HEAD `a254f0ca39fd41f63afe379db7444e64a537dcfc`; observed native job results and IDs above; initial docs-validation SUCCESS. **Final HEAD checks, audit and merge are still pending** after this evidence update.
- DO NOT infer `SMOKE_PASS` from green docs validation or from a runner doing only preflight.
- Stop after this PR's objective audit; any next experimental setup/installs/PRs or engine development requires another explicit owner authorization. No checkpoint outside the allowlist; propose a factual delta only, do NOT apply it autonomously.
