# Evidence Bundle / Context Lock — CORE-01 G3 exact version and ABI qualification

**Date:** 2026-11-16. **STATUS:** `DOCUMENTARY_CANDIDATES_ONLY / G3_OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`. Stable [WO NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md); [issue #387](https://github.com/KayzenRoot/stormline/issues/387) OPEN; [technical G3 matrix](../research/core-01-01-g3-toolchain-abi-qualification.md). No code/tech adoption/ADR approval is authorized by this PR.

## 1. Explicit authority and scope

Owner request: "Continue o Stormline a partir do HEAD 66f09f30d20c8bff2b326d9d8aebdee82da49b8b" and qualify the *next NECESSARY G3 documentary increment* for C++20, MSVC/GCC/Clang/AppleClang, SDL3, CMake/CTest/Ninja, SDK, ABI/HostHandle, lifecycle/headless, licenses/SBOM, R$0 CI, risks and objective proofs, with PR/CI/pt-BR audit/checkpoint if needed. Owner specifically **forbade automatic ADR-0003/0075 approval, NLE-D009 choice, G2 ruleset/workflows/registry/manifest alterations, any 80 code-WO promotion or CORE-01-02/implementation start**.

23 bounded owner-ratified design directions (4 C01 G1 + 8 G1-M + 11 C01 G2/G3) are **not an explicit selection of the exact new version numbers in this dossier**. These numbers are engineering candidates only. Any G3 future proof that requires native C++ test code must use **a separate explicitly owner-authorized experimental WO** (C01-D15) before executor work; this PR creates none.

## 2. Git Source Check / Context Lock

**main HEAD verified:** `66f09f30d20c8bff2b326d9d8aebdee82da49b8b`. `main.protected=true`. `GET /rulesets/27393227` readback: `active`, only `refs/heads/main`, mandatory check `docs-validation` from app `15368`, no bypass, zero required human review; G2 continues `CLEARED` with P06/P07 readback (not destructive attempts) and P10 policy proof (not external fork). Owner issue #387 OPEN. This G3 change **must not** write or modify rule 27393227.

Git blob SHA-1 object IDs, **not** SHA-256 of source bytes:

| Git source / authoritative input | Git blob object ID at pinned main |
|---|---|
| `docs/11-checkpoint.md` | `5688997b7e88580bac42f70ea33ac3bdd3bd1edc` |
| `docs/10-decisions-ledger.md` | `98845bdaab2666cac2c48e89bc0f908d90145a7f` |
| `docs/03-scope.md` | `a6c213fac1514d721c5e212e87887eea81de18ef` |
| `docs/09-definition-of-done.md` | `082f8383b47f2bdc69d8d7c80812f3a94b0b96d1` |
| `docs/04-architecture.md` | `df62574cb3956c3ac9881631a4cf66be4e1abff1` |
| `docs/02-requirements.md` | `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b` |
| `docs/adr/0003-core-01-platform-technology.md` | `2ee92dda5ab81ddcc446b9d5325d29257350e217` |
| `docs/adr/0075-qa-01-ci-matrix-security-policy.md` | `22e91a36c1e0a8121163fa4778abd0489fed86e5` |
| `docs/engineering/core-01-01-qualification-gates.md` | `cbb8ae3baee923c27c83494e354bd757595fcf9f` |
| `docs/work-orders/NLE-PRPLAN-CORE-01-01.md` | `7c8147f2ef31a344eb8d6b5d41cd93a094eab71f` |
| `docs/research/core-01-01-g2-g3-owner-decision-options.md` | `34ee9e09a53fdad0e91fa8bf84932d49fffbf5c5` |
| `docs/research/core-01-01-owner-technical-decision-dossier.md` | `0c328dfada9f946f9525fc4aff5887f6b0bc36ac` |
| `docs/05-security.md` | `eaa02b711f62498e41c82b6cb6615a94c375881c` |
| `docs/queue/implementation-registry.json` | `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024` |
| `docs/pr-plans/manifest.json` | `95782386c59e5af8ac1a8c92a7a35c87992463db` |
| `docs/evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-APPLIED.md` | `15a04dd50365d185099c0ddfe6df9c2bd1f7fdc6` |
| `.github/workflows/docs.yml` | `c9d7b6688ed9484ecaf9968c9134bfaa70f73dc1` |

**STALENESS RULE:** if checkpoint, Ledger/ADR, Scope, DoD, Architecture, Requirements, active G2 ruleset or registry/manifest changes, re-read Git data before merge; do NOT auto-rebase authorizations. Recompute raw SHA-256 fingerprints for an actually authorized executor/benchmark later; the Git blob IDs here do **not** substitute for artifact hashes.

## 3. External original facts and separated hypotheses (official primary sources)

| Claim confirmed via publisher on 2026-11-16 | Evidence source | Boundary/caveat |
|---|---|---|
| SDL3 source archives `3.4.20` published 2026-11-03 | [libsdl.org release archive](https://libsdl.org/release/) | No SDL binary/source SHA is pinned in Stormline yet |
| CMake `4.4.5` released Oct 27, `4.5.0` Nov 12, 2026 | [Kitware official releases 4.4.5](https://github.com/Kitware/CMake/releases/tag/v4.4.5), [4.5.0](https://github.com/Kitware/CMake/releases/tag/v4.5.0) | Both available, neither adopted; historic proposed 3.27/schema6 minimum still unresolved |
| Ninja `v1.13.2` published **2025-11-20** | [Ninja release](https://github.com/ninja-build/ninja/releases/tag/v1.13.2) | Per-platform releases have SHA digests; no Stormline pin/redistribution yet |
| GCC `16.2` released 2026-08-07; compatibility fallback `15.3` | [GCC 16 release](https://gcc.gnu.org/gcc-16/), [GNU release history](https://gcc.gnu.org/releases.html) | Actual version **not known** on `ubuntu-24.04` runner; install provenance needed |
| LLVM/Clang `23.1.5` published 2026-11-03 | [LLVM release](https://github.com/llvm/llvm-project/releases/tag/llvmorg-23.1.5) | No runner installation, ABI/glibc runtime or official binary cache claimed |
| VS Build Tools `18.12.0` stable released 2026-11-10; MSVC family `14.50` long-term | [VS history](https://learn.microsoft.com/en-us/visualstudio/releases/2026/release-history), [MSVC compiler versions](https://learn.microsoft.com/en-us/cpp/overview/compiler-versions) | **Different product version numbers**; cannot claim MSVC 14.50 bundled with VS18.12 without real cl /Bv |
| Windows SDK `10.0.26100.9457` released Sep 2026 | [Microsoft SDK releases](https://learn.microsoft.com/en-us/windows/apps/windows-sdk/downloads) | SDK not OS floor/certification; check installed SDK/CRT |
| Xcode `26.3` build 17C529 on macOS 15 arm64 runner image, SDK macOS26.2; Xcode requires macOS15.6+ | [Apple system requirements](https://developer.apple.com/xcode/system-requirements), [Apple Xcode 26.3 release notes](https://developer.apple.com/documentation/xcode-release-notes/xcode-26_3-release-notes), [runner image inventory](https://github.com/actions/runner-images/blob/main/images/macos/macos-15-arm64-Readme.md) | Full **AppleClang build unknown** until `xcrun clang --version` under selected DEVELOPER_DIR; mutable image versions |
| Standard GitHub-hosted `ubuntu-24.04`, `windows-2025-vs2026`, `macos-15` are listed for public repos, usage free | [GitHub runner docs](https://docs.github.com/en/actions/reference/runners/github-hosted-runners) | Does not authorize workflows or paid services, nor certify actual target OS/driver/device |
| SDL init main-thread and callbacks, deadlock caveats | [SDL_InitSubSystem](https://wiki.libsdl.org/SDL3/SDL_InitSubSystem), [SDL_RunOnMainThread](https://wiki.libsdl.org/SDL3/SDL_RunOnMainThread), [SDL main functions](https://wiki.libsdl.org/SDL3/README-main-functions) | Contract proposals only; no code or synthetic SDL testing |
| CMake BSD-3 license and third-party components | [Kitware licensing](https://cmake.org/licensing/) | License audit at exact release+transitive versions still open |
| SDL zlib, Ninja Apache-2.0, LLVM Apache-2.0 with LLVM exception, GCC runtime exception, MSVC/Xcode product terms | [SDL license](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt), [Ninja COPYING](https://github.com/ninja-build/ninja/blob/master/COPYING), [LLVM License](https://github.com/llvm/llvm-project/blob/main/LICENSE.TXT) | Snapshot each exact version and verify notices/runtime redistributables. **Engine-source license NLE-D009 remains OPEN** |

**Negative proof:** official publisher data and runner-image READMEs are not `--version` receipts from a Stormline CI job. **NO native Windows/Linux/macOS build or runtime test was performed; no ABI, SDK, CPU/GPU performance or headless claim is certified.** Zero runtime evidence is not transmuted by Docs Validation into technical approval.

## 4. Future proof obligations, no executed tests

[G3 matrix](../research/core-01-01-g3-toolchain-abi-qualification.md) enumerates **exactly sixteen G3-P01..P16**, each `FUTURE_NOT_EXECUTED`: owner versions, SHA/attestations, Windows compiler+CRT, Linux glibc/GLIBCXX ABI, macOS AppleClang full build+deployment floor, CMake/CTest/Ninja, Context Lock, SDL video/input, true headless, lifecycle, ABI, tri-state, G1 200/100/10k/30+30/sanitizers plus numeric p95/RSS owner constraints, fork/free native CI, per-slice risk and independent ADR technical audit. Not all can be satisfied in docs alone; work requiring code **must have separately authorized WO**.

Owner decision subjects **G3-V01..V05** are **open**. In particular Xcode 26.3+AppleClang full version, compiler+stdlib ABI, CMake Presets schema, exact SDK, SBOM/license digest, optional plugin ABI scope and G1 p95/RSS are not currently owner-approved. No future pilot code or install is authorized here.

## 5. Hard invariants, acceptance and negative changes

- 23 prior bounded owner technical directions preserved, no new exact-version ratification. G1 `PARTIALLY_RATIFIED_NOT_CLEARED`, G2 `CLEARED` in already-proven **ruleset 27393227** scope, G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`, G4–G8 BLOCKED.
- ADR-0003/0075 `PROPOSED`, NLE-D009 engine-source license `OPEN`, zero selected release signing/royalties/paid SDK.
- Registry remains 80/80 code WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, 0 `executor_ready`, 0 `approved_adr`, 80 `release_class=UNDECIDED`, 80 `risk=UNCLASSIFIED`, `engine_implemented=false`.
- Manifest CORE-01-01 and CORE-01-02 `PLANNED_BLOCKED` (these are **future implementation packets**, not documentary PRs). Issue #387 must stay OPEN.
- **Only allowed diff** in proposal PR: two ADDED Markdown, this Evidence Bundle and its linked G3 research. No edits to ruleset GitHub/settings, workflow, code, ADR, Ledger, Scope, DoD, Architecture/Requirements, registry/manifest, license or WO itself.

**Review and complete only with observed results:** (1) GitHub compare confirms exact two additions; (2) `docs-validation` SUCCESS on HEAD exact and all steps green; (3) objective auditor in pt-BR validates provenance, technical gaps, risk and no HIGH/CRITICAL in documentary scope; (4) squash/HEAD readback without bypass, then independent factual checkpoint PR with own CI/audit/readback. No PR ID/CI/merge is presumed before it happens. **STOP** if stale main/source, CI failure, unauthorized version or ADR promotion, G2 rule change, new code, paid CI, NLE-D009 adoption or CORE-01-02 start.
