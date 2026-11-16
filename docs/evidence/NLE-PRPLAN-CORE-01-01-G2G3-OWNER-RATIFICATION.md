# Evidence Bundle — NLE-PRPLAN-CORE-01-01 / bounded G2-G3 owner ratification

**Date:** 2026-11-16. **Status:** `OWNER_RATIFIED_G2G3_BOUNDED` (11 decisions), **G2 NOT VERIFIED; G3 NOT TECHNICALLY CLEARED**. [Issue #387](https://github.com/KayzenRoot/stormline/issues/387) OPEN. [Original research/options](../research/core-01-01-g2-g3-owner-decision-options.md). **Stable Work Order:** [NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md).

## Explicit authority and boundary

The owner directly stated in this conversation, referring to the known base and exact options: **“Como proprietário do Stormline, RATIFICO EXPRESSAMENTE as recomendações A das 11 decisões C01-D02, C01-D03, C01-D04, C01-D05, C01-D06, C01-D07, C01-D10, C01-D11, C01-D12, C01-D13 e C01-D15, exatamente conforme docs/research/core-01-01-g2-g3-owner-decision-options.md, a partir do HEAD 139a874c69e6a358777bc3356ba4e51eb4ae1253, incluindo todas as ressalvas, trade-offs e obrigações de prova.”** This is an accurate transcription of conversational authorization, **not an independently cryptographically signed GitHub statement**. Owner **expressly forbade** treating G2 as verified, approval of ADR-0003/0075, choice of engine-source license NLE-D009, changes to branch settings/registry/manifest, release of any of 80 code WOs or initiating CORE-01-02/code.

The eleven options were earlier recommendations in [PR #396](https://github.com/KayzenRoot/stormline/pull/396), with an independent factual checkpoint in [PR #397](https://github.com/KayzenRoot/stormline/pull/397). That earlier approval was only documentary; this subsequent owner statement is the *first explicit ratification of these eleven IDs*.

## Source Check / Context Lock, Git object fingerprints

**Git main exact base:** `139a874c69e6a358777bc3356ba4e51eb4ae1253`; verified via GitHub branch readback. The following are Git **blob SHA-1 object IDs**, not the SHA-256 of raw file bytes. Recompute fresh SHA-256 and source fingerprints before any future execution.
- `docs/11-checkpoint.md` `df711a13d24ce206dc7d289887a3a0d6c08540c8`
- `docs/10-decisions-ledger.md` `ce78ac20f575b1a7ac5111c5ea59126ecb22b09d`
- `docs/03-scope.md` `32bce8996dfc5174f70bf54d1c1088347ef6f14d`
- `docs/09-definition-of-done.md` `12a5661eaa6e7b73fce1b0c6605598dcf6543ee7`
- `docs/04-architecture.md` `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md` `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/research/core-01-01-g2-g3-owner-decision-options.md` `615f74f7c5104aae09421b82d2e8084676c89c38`
- `docs/research/core-01-01-owner-technical-decision-dossier.md` `c65183ae9c348d4d35ef947550c1a67f4ebe0846`
- `docs/engineering/core-01-01-qualification-gates.md` `08b942dca534702673d2048854194acd5d8211e3`
- `docs/work-orders/NLE-PRPLAN-CORE-01-01.md` `089a5ce7c92184cae70c3cca12a7e94ca957edbd`
- `docs/evidence/NLE-PRPLAN-CORE-01-01-G2G3-OPTIONS.md` `e8e44c295ffdc0c93550dabdb43036e5e0bf7fad`
- `docs/adr/0003-core-01-platform-technology.md` `2ee92dda5ab81ddcc446b9d5325d29257350e217`
- `docs/adr/0075-qa-01-ci-matrix-security-policy.md` `22e91a36c1e0a8121163fa4778abd0489fed86e5`
- `docs/queue/implementation-registry.json` `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`
- `docs/pr-plans/manifest.json` `95782386c59e5af8ac1a8c92a7a35c87992463db`

**STALE policy:** if main, checkpoint, Ledger, Scope, DoD, Architecture, Requirements or decisions/registry change before write, rerun Source Check and rebase. No approval bypass is authorized.

## Eleven ratifications and necessary future proof, without overclaiming

| ID | Selected option A ratified as *bounded design direction* | Still to prove or approve separately |
|---|---|---|
| C01-D02 | Internal **C++20**, no mandatory C++20 named modules / default C++23. | Exact MSVC/GCC/Clang/AppleClang and stdlib/SDK versions, native compilation x64/arm64, flags/features |
| C01-D03 | **Thin SDL3 host adapter**, no SDL types/headers in public engine interface. | Pin SDL3 version+SHA, verify official license/transitives and real IME/HiDPI/events/hotplug; compare fallback GLFW/native if inadequate |
| C01-D04 | SDL video init/quit on main thread, balanced subsystem ownership; headless no obligatory video/audio; normal main + isolated SDL entry shim as candidate. | OS-specific entrypoint, callback alternative, no-deadlock and failure-unwind tests |
| C01-D05 | CMake Presets + CTest Presets + Ninja default, native IDE fallbacks. | **CMake 3.27/Presets v6 only an evaluation candidate, not a pinned version**; verify schema, compiler/toolchain, deterministic builds on all targets |
| C01-D06 | Internal C++ RAII and opaque HostHandle, no universal C++ binary ABI promise. **Future conditional external plugin/SDK boundary** prefers a versioned opaque-handle C ABI only if external scope separately authorized. | ABI, ownership and exception boundary contracts, allocator/calling conventions; no SDK/plugin release approved |
| C01-D07 | Explicit lifecycle state machine with recoverable InitFailed, typed Result/Error and idempotent teardown. | Transition/negative/cancellation/failure injection and headless/window lifecycle tests |
| C01-D10 | Tri-state SUPPORTED/UNSUPPORTED/UNKNOWN with provenance/confidence; start with thin adapter; SAPL only for measured semantic/performance benefit. | Real capability/driver cases and measured overhead threshold **not yet owner-approved** |
| C01-D11 | Risk **framework**: STANDARD base candidate, ELEVATED native/privileged bridges candidate, HIGH_ASSURANCE only applicable sensitive/irreversible slice. | **No 80-module or specific WO risk classification approved**, registry stays UNCLASSIFIED; prove per-slice threats and tests |
| C01-D12 | R$0 standard GitHub Actions runner/PR isolation and preferred protected mandatory checks with explicit owner approval of any separate settings change. | **G2 IS NOT VERIFIED**: `main.protected=false`, `rulesets=[]`, detailed protection 403. No settings altered. Verify actual required checks, ruleset, merge denial and no-bypass once separately authorized |
| C01-D13 | Verify/pin **third-party** SDL3 zlib, CMake BSD-3-Clause, Ninja Apache-2.0 and SPDX/SBOM/notice obligations. | Actual release/tag/license SHA, transitive/audit/re-distribution review. **NLE-D009 engine-source license OPEN**. No LICENSE/publisher/binary distribution selected |
| C01-D15 | Conceptual stack direction separate from proven production tech; if experimental native code becomes essential, **separate proposed experimental WO requiring explicit authorization** before writing anything. | **No experimental WO/code authorized in this ratification; ADR-0003 PROPOSED and CORE-01-02 PLANNED_BLOCKED** |

## Source conflicts, negative proof and gates

Prior **12 bounded G1** ratifications (C01-D01/D08/D09/D14 + G1-M01..M08) are unaffected. Exactly **11/11 C01 G2/G3 option A directions now owner-ratified bounded**; this does not constitute an actual G3 technical acceptance, full G1 completion, or implementation readiness. G1 `PARTIALLY_RATIFIED_NOT_CLEARED` (physical OS/SDK tests, p95/RSS thresholds, full 1.0 Scope/DoD/release classes). G2 `BLOCKED_NOT_VERIFIED`. G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`, ADR-0003/0075 remain PROPOSED, third-party/legal/ABI/build evidence missing. G4–G8 not authorized.

**Fresh read-only G2 query:** `main.protected=false`; `GET /repos/KayzenRoot/stormline/rulesets` returned `[]`; `GET .../branches/main/protection` returned 403 ("Resource not accessible by integration"). Docs Validation job `docs-validation` passing is *not evidence that GitHub requires or enforces it*. No GitHub settings changed.

**All implementation invariants:** 80/80 coding WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, 0 executor_ready and 0 approved_adr, 80 `release_class=UNDECIDED`, 80 `risk=UNCLASSIFIED`, `engine_implemented=false`; CORE-01-01 and CORE-01-02 manifest `PLANNED_BLOCKED`. NLE-D009 OPEN, NLE-D010 OPEN; issue #387 stays OPEN. C01-Q001..Q032 `FUTURE_NOT_EXECUTED`. No C++/headless/window/physical CI, SDK/ABI, sanitizers or benchmarks actually executed.

## Change constraints, audit and acceptance
**Allowed this PR only:** UPDATE `docs/10-decisions-ledger.md`, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/research/core-01-01-g2-g3-owner-decision-options.md`, `docs/research/core-01-01-owner-technical-decision-dossier.md`, `docs/engineering/core-01-01-qualification-gates.md`, `docs/work-orders/NLE-PRPLAN-CORE-01-01.md`; ADD this Evidence Bundle (exactly 8 Markdown files). **NOT allowed:** edit ADR, Architecture, Requirements, registry/manifest, branch/settings, CI/workflows, license/third-party packages, code, experiment or packet 02.

**Documentary acceptance:** exact-head Docs Validation SUCCESS, objective pt-BR file diff/Source Pack/DoD/security audit, no known HIGH/CRITICAL defects, normal squash & main readback, separate factual checkpoint PR+CI/audit/readback only after actual events. Do not preclaim PR IDs, CI, tests or merge in this draft. No check in this documentary PR certifies runtime or platform.

## Actual PR #398 closure (checkpoint independent)
- [PR #398](https://github.com/KayzenRoot/stormline/pull/398), base `139a874c69e6a358777bc3356ba4e51eb4ae1253`, final audited HEAD `bca204941156f728a592c413a175f785decebe38`. Exactly **7 MODIFIED + 1 ADDED Markdown**, no ADR, registry/manifest, CI, code, license or branch settings changed.
- GitHub Actions Docs Validation [run #43900878855](https://github.com/KayzenRoot/stormline/actions/runs/43900878855) **SUCCESS**, job `docs-validation` **#133416812540**, all steps successful (including blocked WO guard). Independent objective pt-BR [audit #6921389198](https://github.com/KayzenRoot/stormline/pull/398#issuecomment-6921389198) APPROVED **documentary only**. Normal squash/main readback [`cb174e617e5aa2201e6674619f587e89f8963155`](https://github.com/KayzenRoot/stormline/commit/cb174e617e5aa2201e6674619f587e89f8963155).
- This factual checkpoint is to be created/CI-audited/read back **separately**; no result of its PR is claimed ahead of time. All eleven directions ratified bounded; G2 still unverified, G3 still technically not cleared, all 80 code WOs BLOCKED, no native tests/engine implementation.
