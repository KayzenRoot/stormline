# CORE-01-01 — Owner approval gates, target matrix & future proof obligations

**Source Check:** `main=27ad407bbf0f66d1938c403bf32c28b0ebf1e910`, Git tree `56b27016ed092be5297a63dabd6b6884144da40a`, 2026-11-16. [Issue de qualificação #384](https://github.com/KayzenRoot/stormline/issues/384). CORE-01 tem zero predecessores formais; [issue de código #18](https://github.com/KayzenRoot/stormline/issues/18) permanece OPEN/BLOCKED. **A versão original deste pacote era proposta documental; decisões expressas posteriores estão refletidas no estado corrente abaixo, sem aprovar ADR ou liberar execução.** `NLE-D009` licença da engine OPEN, `NLE-D010` marca OPEN, `ADR-0003` e `ADR-0075` PROPOSED, 80/80 WOs de código BLOCKED, zero `approved_adr`, zero `executor_ready`, `engine_implemented=false`.

**Status:** This document establishes **proposed** acceptance criteria, not executed tests or assigned module risk. The [CORE-01 decision dossier](../research/core-01-01-owner-technical-decision-dossier.md) now records all 15 C01 choice directions explicitly owner-ratified **bounded**, including the 11 G2/G3 option-A choices under a separate later declaration. Eight G1-M choices were also previously ratified. **This is not technical gate clearance or a release.** Existing [global G0..G8](p00-technical-approval-gates.md) and [queue guard](../queue/work-orders/CORE-01.md) prevail.

## Gates in strict decision order (nothing self-promoted)
| Gate | Proposed completion proof | CURRENT |
|---|---|---|
| G0 research | 80/80 documented + catalog DAG, ADR proposal, evidence links | COVERAGE DOCUMENTED; research ≠ owner approval |
| G1 scope/DoD/release | Owner ratifies CORE-01 minimum desktop/headless requirements, version 1.0 mandatory vs conditional features, support matrix and full product DoD | `PARTIALLY_RATIFIED_NOT_CLEARED`: four bounded C01 G1 directions plus eight bounded G1-M minima; SDK/physical tests, p95/RSS and complete product 1.0 DoD still open; registry UNDECIDED |
| G2 repository | Confirm protected PR flow, required checks by **actual job name**, zero external reviewers, no bypass, no public-fork secret access, R$0 | `CLEARED` (2026-11-16): ruleset `27393227` active only on main, PR required/0 approvals, `docs-validation` (app 15368) strict, linear/squash, no force/delete/bypass; real negative probes and green squash `80624f6`; ver [Evidence aplicado](../evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-APPLIED.md) |
| G3 architecture/stack | Owner chooses C++ standard, host adapter, CMake Presets schema/toolchains, ABI ownership/third party terms and explicit cost/scope | `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`: 11 bounded option-A directions, compiler/SDK/version/ABI, OS tests/licensing and ADR-0003/0075 PROPOSED |
| G4 CORE-01 technical approval | Signed/traceable owner decision + objective comparison evidence to approve revised or superseding ADR-0003; preserve historical PROPOSED text until separate decision PR | `NOT_STARTED` |
| G5 execution proof plan | Risk classification per slice, pin versions/checksums, numerical acceptance and actual hardware matrix, full typed API/version/rollback spec | `NOT_STARTED` |
| G6 individual WO activation | Exact files, fresh Git SHA-256 Context Lock, merged formal predecessors (CORE-01 has none), native CI and no HIGH/CRITICAL, independent audit | `BLOCKED`: #18 original WO remains blocked, no ready status |
| G7 C++ implementation/test | Actual native compile/headless/windowed tests, sanitizers, performance and security receipts | `NOT_EXECUTED` |
| G8 full public release | Full 1.0 DoD and BIZ-01/PLAT-05/QA-05 security/license/installer approvals | `NOT_AUTHORIZED`, NLE-D009 OPEN |

**Dependency caveat:** QA-01 is a downstream owner that formally depends only on CORE-01. Its ADR-0075 is a CI research source, not an extra formal CORE-01 predecessor. QA-01 actual jobs will require an approved native baseline from CORE-01 first.

## Candidate support matrix, not supported product claim
| Profile | Compiler/build candidate | Hosted CI feasibility | Physical test / owner disposition |
|---|---|---|---|
| Linux x86_64 | GCC + Clang C++20, CMake+Ninja; ubuntu-24.04 | Standard public runner candidate R$0 | Wayland, X11 and true headless real distro/glibc floors to decide |
| Windows x86_64 | MSVC C++20, optional clang-cl; windows-2025 | Standard public runner candidate R$0 | Win10 vs Win11 and minimum supported SDK/runtime to decide |
| macOS arm64 | AppleClang with CMake+Ninja / Xcode; macos-15 | Standard public ARM runner candidate R$0 | Apple Silicon real window/HiDPI/device and minimum macOS to decide |
| macOS x86_64 | AppleClang candidate, Intel runner availability | Possible hosted Intel but no physical proof here | **CONDITIONAL / OWNER DECISION**, PLAT-06 has Intel feasibility open |
| Windows arm64 | MSVC/clang-cl candidates | Possible public runner after toolchain qualification | **CONDITIONAL**, no automatic supported claim |
| Browser | Wasm/Emscripten/WebGPU separate PLAT-03 | Browser build future | **NOT in CORE-01 direct host acceptance**; no invented desktop parity |
| Headless server | CPU-only Windows/Linux/macOS host | Event/clock stub/no display devices | May pass runtime independently of GPU/windowed constraints once code exists |

**CI policy:** Linux/Windows/macOS runner labels and public standard execution appear in [GitHub official docs](https://docs.github.com/en/actions/reference/runners/github-hosted-runners). The actual future CI must pin compiler/OS/arch, environment, source SHA, dependency hashes and exact cost/retention; windowed VM tests are smoke, **not GPU physics/driver qualification**. Do not add QA-01 native workflow before authorized code.

## 32 future test and benchmark cases: 31 NOT RUN; C01-Q031 executed via G2 proofs
These are *negotiation-ready test oracles*. The test case count does not retroactively change historical CORE-01 research nor create an approved contract. C01-Q001..Q030 and C01-Q032 remain `FUTURE_NOT_EXECUTED`; only C01-Q031 (governance) is `PASS` via the real G2 enforcement proofs. Native tests still require CI logs and physical target evidence.

| ID | Area | Future scenario | Proposed numeric / pass oracle | Result |
|---|---|---|---|---|
| C01-Q001 | Research | Compare recorded CORE-01 formal predecessor list against catalog/registry; exactly [] | No added upstream formal dependency | `FUTURE_NOT_EXECUTED` |
| C01-Q002 | Research | Confirm status of ADR-0003 / ADR-0075 in Git exact HEAD | Both PROPOSED; no auto-approval | `FUTURE_NOT_EXECUTED` |
| C01-Q003 | Research | Confirm module original code issue #18 and planned packet state | OPEN/BLOCKED, PLANNED_BLOCKED, github_pr=null | `FUTURE_NOT_EXECUTED` |
| C01-Q004 | Research | Validate research vs implementation claims/engine license/DoD | 80 research documented, zero code approved and NLE-D009 OPEN | `FUTURE_NOT_EXECUTED` |
| C01-Q005 | Lifecycle | 200 headless start/stop cycles per approved OS target | 200/200 successful, no GPU/video/audio requirement and no sanitizer leak (proposal) | `FUTURE_NOT_EXECUTED` |
| C01-Q006 | Lifecycle | 200 duplicate init/quit attempts, including init error | Typed failure/recovery, no double-free or native resource leakage (proposal) | `FUTURE_NOT_EXECUTED` |
| C01-Q007 | Lifecycle | Inject failure at every startup stage with cleanup | Every injected point returns controlled error, no lingering handles (proposal) | `FUTURE_NOT_EXECUTED` |
| C01-Q008 | Lifecycle | Run headless without DISPLAY/WAYLAND_DISPLAY/GPU/audio device | Process exits 0 after controlled lifecycle; no hidden fallback window (proposal) | `FUTURE_NOT_EXECUTED` |
| C01-Q009 | Window | 100 window create-resize-focus-destroy iterations per platform | Zero invalid handle/use-after-free, window count back to baseline (proposal) | `FUTURE_NOT_EXECUTED` |
| C01-Q010 | Window | Wrong-thread SDL_Init/SDL_Quit and video operations | Operation denied or marshalled via approved main-thread policy; no deadlock | `FUTURE_NOT_EXECUTED` |
| C01-Q011 | Window | DPI/multimonitor hotplug with transient surface tokens | Derived token becomes invalid deterministically; viewport state recoverable | `FUTURE_NOT_EXECUTED` |
| C01-Q012 | Window | Missing display session in windowed mode | Typed WINDOW_UNAVAILABLE within proposed 5s rather than hang (proposal) | `FUTURE_NOT_EXECUTED` |
| C01-Q013 | Events | Replay 10,000 ordered synthetic OS events | Monotonic sequence and no unreported lost critical events (proposal) | `FUTURE_NOT_EXECUTED` |
| C01-Q014 | Events | Bounded queue with sustained overload | Dropped/coalesced event count explicit and no memory growth beyond approved cap | `FUTURE_NOT_EXECUTED` |
| C01-Q015 | Events | Hotplug/focus/suspend/resume sequence replay | Consistent event lifecycle under deterministic input, not physics determinism | `FUTURE_NOT_EXECUTED` |
| C01-Q016 | Events | Invalid/corrupted event payload and stale device | Safe typed error, no read beyond bounds | `FUTURE_NOT_EXECUTED` |
| C01-Q017 | OS & Security | Paths: Unicode normalization, symlinks, traversal, denied permission | No sandbox-root escape; private path redacted in logs | `FUTURE_NOT_EXECUTED` |
| C01-Q018 | OS & Security | Native Win32/Wayland-X11/Cocoa adapter failure cases | Each unsupported capability yields UNKNOWN or UNSUPPORTED, never fake supported | `FUTURE_NOT_EXECUTED` |
| C01-Q019 | OS & Security | Window/session teardown during app suspend/terminate | Recoverable defined state, correct dispatch thread, no privileged command | `FUTURE_NOT_EXECUTED` |
| C01-Q020 | OS & Security | No telemetry consent and sandboxed AI command caller | Zero external diagnostic upload/ambient privilege access | `FUTURE_NOT_EXECUTED` |
| C01-Q021 | Build | Pinned CMake+Ninja compiler build Linux GCC/Clang | Reproducible build receipt and unit tests actually run; no compiler selected yet | `FUTURE_NOT_EXECUTED` |
| C01-Q022 | Build | Windows MSVC and clang-cl C++20 binary and test suite | Build target and CRT metadata logged; ABI errors detected | `FUTURE_NOT_EXECUTED` |
| C01-Q023 | Build | macOS AppleClang arm64 and optional x86_64 decision matrix | Native compile and headless/window smoke verified; x86_64 stays NOT_QUALIFIED if not run | `FUTURE_NOT_EXECUTED` |
| C01-Q024 | Build | CMake Presets schema compatibility and offline reproducible dependencies | Exact versions, locks, digests and license notices recorded; no surprise network | `FUTURE_NOT_EXECUTED` |
| C01-Q025 | Reliability | 30 warm and 30 cold init samples per approved target | p50/p95/p99, compiler/hardware/OS and variability reported, no fabricated threshold | `FUTURE_NOT_EXECUTED` |
| C01-Q026 | Reliability | Headless steady-memory growth after warmup over 200 cycles | Proposed delta ≤1 MiB; owner must approve measurement method and baseline | `FUTURE_NOT_EXECUTED` |
| C01-Q027 | Reliability | Thin SDL3 versus SAPL capability/event overhead | Proposed ≤5% p95 CPU overhead at equal workload, no lost semantics; reject otherwise | `FUTURE_NOT_EXECUTED` |
| C01-Q028 | Reliability | Physical OS/display/driver/graphics fallback qualification | NOT_QUALIFIED until real device matrix and test artifacts; CI VM not GPU certification | `FUTURE_NOT_EXECUTED` |
| C01-Q029 | Governance | Pin SDL3/SDL3 third-party license, Ninja/CMake/vendor toolchain rights | SPDX/provenance/version/sha256/redistribution scope; source license remains OPEN | `FUTURE_NOT_EXECUTED` |
| C01-Q030 | Governance | Verify public CI R$0, 3 OS standard-runner labels and artifact retention | No paid larger runner/secret-bearing workflow; owner-approved quota and evidence | `FUTURE_NOT_EXECUTED` |
| C01-Q031 | Governance | Verify GitHub main branch protection/rulesets/required check enforcement | Actual enforcement not verified; configuration action separate and authorized | `PASS` — G2-P01..P12, 2026-11-16 ([Evidence aplicado](../evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-APPLIED.md)) |
| C01-Q032 | Governance | Owner ratifies 1.0 Scope/DoD/risk/release/ABI/ADR and no HIGH/CRITICAL | Explicit approval with traceable record, not approval by this documentary PR | `FUTURE_NOT_EXECUTED` |

### Numerical gates are **candidates**, not requirements or PASS
- **200/200 headless cycles** per owner-approved OS/arch: no display/GPU/audio linked or invoked unnecessarily, exit status 0, zero reported leaks under supported sanitizer; **100/100 window create/destroy** cycles with no surviving invalid resource handles. Choose runners/hardware and sanitizer interpretation before accepting.
- **10,000 synthetic event replay** with no *unreported* critical-event loss and bounded queue. This is input/event determinism only, not cross-CPU physics determinism.
- **30 warm + 30 cold measurements** per selected profile, report p50/p95/p99 in ms and confidence; **proposed memory growth ≤1 MiB** after warmup in 200 cycles (platform noise baseline to approve). Do not promise globally fixed warm startup without actually sampling hardware.
- Optional SAPL comparison at identical load: **proposed p95 CPU cost ≤5% above direct thin SDL3** and measurable functional benefit; otherwise delete candidate, not force innovation. Numeric overhead threshold requires owner approval before implementation.
- Typed window missing display timeout **proposed ≤5 seconds**, not a verified guarantee. QA should record concrete target CPU/OS/driver, toolchain, environment, run SHA, binary hash, initial seed, number of samples and method.
- For unavailable physical Mac, Linux desktop variants or proprietary GPU, label `NOT_QUALIFIED`, not PASS.

## Proof obligations & source-of-truth integrity
1. No public header/ABI direct SDL pointer, renderer backend or native OS handle without owner-granted encapsulation; no cross-CRT new/delete, no arbitrary C++ ABI compatibility claim.
2. Negative tests: partial-init rollback, wrong-thread SDL, stale window tokens, symlink/traversal, permission denied, event saturation, device unplug, missing display, malformed capabilities, unauthorized MCP host command. Zero implicit privileged access.
3. Third-party SPDX/license+notice matrix for exact committed SDL3, Ninja, toolchains and redistribution scope. License of **Stormline engine** remains `OPEN`; SDK/public exports forbidden until separate BIZ-01 rights clearance.
4. Future native CI must be fork-safe, read-only token without privileged workflow trigger, no signing/telemetry secrets or automatic model networking.
5. Every approved actual slice requires new Context Lock with source blob and **raw SHA-256**, exact file list, unit+integration+error tests, benchmark/hardware when applicable, Evidence Bundle, correction in same PR, pt-BR independent audit, squash/readback.
6. **Never progress to packet 02** until G1/G2/G3 and owner qualification gate 01 are actually satisfied; a proposal-only CI approval is insufficient.

[Decision dossier](../research/core-01-01-owner-technical-decision-dossier.md) · [Work Order](../work-orders/NLE-PRPLAN-CORE-01-01.md) · [Evidence](../evidence/NLE-PRPLAN-CORE-01-01.md).

## G1 owner ratification delta (2026-11-16)
The owner expressly ratified C01-D01/D08/D09/D14 with limitations and future proof obligations; see [Ledger](../10-decisions-ledger.md), [Scope](../03-scope.md), [DoD](../09-definition-of-done.md), [Evidence G1](../evidence/NLE-PRPLAN-CORE-01-01-G1-RATIFICATION.md). **G1 remains NOT CLEARED** until full Scope/DoD, minimum OS/CPU/runtime and approved hardware/threshold matrix. C01-Q001..Q030 and C01-Q032 stay `FUTURE_NOT_EXECUTED`; C01-Q031 is `PASS` via G2 (2026-11-16). **G2 is CLEARED**; **G3 stays open**; ADR-0003 PROPOSED, registry/manifest unchanged and packet 02 PLANNED_BLOCKED.

## Gate G1 after explicit owner ratification of minima (2026-11-16; newest status)

**C01-D01/D08/D09/D14:** remain `OWNER_RATIFIED_G1_BOUNDED`. **G1-M01..M08:** each was explicitly ratified as a **bounded future requirement** by the owner after [delegated selection](../research/core-01-01-g1-delegated-selection.md), with detailed limits in the [Ledger](../10-decisions-ledger.md) and [Evidence Bundle](../evidence/NLE-PRPLAN-CORE-01-01-G1-MINIMA-RATIFICATION.md). The historical table above is the original qualified proposal and is not an override of this newer status.

**G1 remains `PARTIALLY_RATIFIED_NOT_CLEARED`, not `APPROVED`:** Windows 11 25H2 floor is provisional and requires lifecycle revalidation; Ubuntu 24.04/glibc 2.39 and macOS 15 arm64 are future support reference constraints, not passed native tests. Physical target/driver/kernel/SO patch/Xcode/CRT, x86 ISA dispatch, 2/4 GiB headless fixture, 4/8 GiB windowed fixture, negative/display-failure in ≤5 s, 200/100/10k/30+30, event delivery, sanitizer leaks/UAF, and release-date 90 day requalification are obligations **NOT EXECUTED**. Final p95/RSS thresholds still unratified, product 1.0 Scope/DoD unclosed and other 11 C01-Dxx await owner.
 
**G2** branch enforcement `CLEARED` (ruleset `27393227` ativo, provas reais; [Evidence aplicado](../evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-APPLIED.md)), **G3** stack/ABI/licensing `OPEN`, **G4-G8** still blocked. ADR-0003 and ADR-0075 PROPOSED, NLE-D009 OPEN, 80/80 code WOs BLOCKED, CORE-01-01/02 PLANNED_BLOCKED, release classes/risk registry undecided/unclassified, engine_implemented=false. No native CI, build, release, editor or server test performed.

## G2/G3 after explicit ratification of eleven C01 option-A directions (2026-11-16, newest status)

The owner **expressly ratified** C01-D02/D03/D04/D05/D06/D07/D10/D11/D12/D13/D15 exactly as qualified, preserving alternatives as unselected and all proof obligations. [Decision Ledger](../10-decisions-ledger.md) · [owner-options matrix](../research/core-01-01-g2-g3-owner-decision-options.md) · [Evidence Bundle](../evidence/NLE-PRPLAN-CORE-01-01-G2G3-OWNER-RATIFICATION.md). Earlier source-check/board sections above are historical research inputs, not live approvals.

- **G2: `CLEARED` (2026-11-16)**. O proprietário autorizou separadamente a escrita administrativa; ruleset `g2-main-enforcement` id `27393227`, `active`, apenas `refs/heads/main`, `bypass_actors=[]`, `current_user_can_bypass="never"`. `docs-validation` (app 15368) é o único check obrigatório, strict; PR obrigatória com 0 aprovações; linear/squash; force-push e deletion proibidos. Provas reais: #402 (falha) e #403 (ausente) negadas, #404 (stale) negada até nova qualificação, #405 squash verde com CI exata e auditoria. [Evidence aplicado](../evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-APPLIED.md). Checks nativos futuros continuam não exigidos e exigirão nova qualificação.
- **G3: `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`**. Eleven design directions are accepted conceptually. Pin versions/digests/third-party SPDX, verify supported C++20 toolchains, SDL3 main-thread/headless, CMake Presets/CTest, ABI/HostHandle lifecycle, capabilities, risk per slice and future runner requirements before considering the technical gate. ADR-0003 and ADR-0075 remain `PROPOSED`. No plugin/SDK or engine license chosen.
- **G1: `PARTIALLY_RATIFIED_NOT_CLEARED`**. Previous 12 bounded decisions still require hardware/patch/SDK/testing proof, p95/RSS explicit thresholds, release classes and complete global DoD. **G4–G8 not approved**. D15 does NOT authorize creating a test-code WO or starting implementation; such an experiment requires a new express owner authorization and separate gate assessment.
- **Guardrails:** NLE-D009 engine license OPEN; registry 80/80 coding WOs BLOCKED, 0 ready/approved ADR, release_class UNDECIDED, risk UNCLASSIFIED; CORE-01-01/02 PLANNED_BLOCKED; C01-Q001..Q030/Q032 FUTURE_NOT_EXECUTED e Q031 PASS via G2; `engine_implemented=false`.

## CORE-01 G3-V05 — ratificacao de fatia interna — interpretacao dos gates sem autopromocao

**Autoridade:** ratificacao explicitamente limitada pelo owner em 2026-11-17, retomando [proposta da issue #387](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6954081280). A fixture da [PR #421](https://github.com/KayzenRoot/stormline/pull/421), [CI nativa #44124073355](https://github.com/KayzenRoot/stormline/actions/runs/44124073355) 3/3 jobs e [docs-validation #44124073329](https://github.com/KayzenRoot/stormline/actions/runs/44124073329) PASS provam **somente prototipo experimental**.

| Gate | Estado SOMENTE da fatia CORE-01 interna | Condicao de avancar |
|---|---|---|
| G1 | `OWNER_RATIFIED_INTERNAL_DIRECTION`; G1 global ainda `PARTIAL` | Tracar release `MANDATORY_1_0` futuro versus codigo `INTERNAL_ONLY`, aceites e exclusoes para esta fatia |
| G2 | `CLEARED_BOUNDED` ruleset 27393227 | Nao modificar protecao/required docs check |
| G3 | `OWNER_RATIFIED_PROVISIONAL_CI`; G3 global `NOT_CLEARED` | Nunca promover 14.51/GCC13.3/AppleClang17 a candidatos de release; preservar 14.50/14.52, .9457, GCC16.2/Clang23.1.5 |
| G4 | `PENDING_SLICE_TECHNICAL_AUDIT` | Decisao registrada, delta da ADR-0003 e interfaces comparadas e auditadas sem aprovar ADR geral |
| G5 | `PENDING_CONTRACT_AND_PROOF_PLAN` | Contratos -02, risco STANDARD, testes por OS, falhas/rollback, custo/licencas, arquivos e fingerprints |
| G6 | `BLOCKED` | Ativacao individual -03 somente apos G1/G3/G4/G5 suficientes para fatia, auditoria objetiva e registro delimitado |
| G7 | `NOT_STARTED` | PR codigo -03 somente quando G6 estiver validamente liberado |

**STOP:** Nenhum codigo de producao novo, nao aprovar ADR integral, nao declarar G3 global CLEARED; 80 code WOs e 748 PR packets continuam BLOCKED/PLANNED_BLOCKED, 0 executor-ready, `engine_implemented=false`. A PR de decisao registra apenas a ratificacao ja expressa; ela nao constitui aprovacao de G4/G5/G6.

## CORE-01 packet -02 — contract-level qualification candidate (G3-V05, 2026-11-17)

A ratificacao limitada foi integrada nas [PRs #422](https://github.com/KayzenRoot/stormline/pull/422) e [#423](https://github.com/KayzenRoot/stormline/pull/423). [ADR-0083](../adr/0083-core-01-internal-headless-slice.md) e [contrato v0](../contracts/core-01-internal-headless-v0.md) estao PROPOSTOS para qualificacao **somente** da fatia `INTERNAL_ONLY`. O gate G4-slice fica `CONDITIONAL_UNTIL_OBJECTIVE_AUDIT_AND_MERGE`; G5-slice igualmente, exigindo todos C01-INT-01..10 como oraculos futuros, status STANDARD para a fatia, e testes CI por plataforma. O protocolo nao equivale a PASS do modulo ou G3 global. **G6 permanece BLOCKED** enquanto nao houver aprovacao independente de ativacao especifica; `scripts/validate_wo_registry.py` obriga os 80 bloqueados e nao pode ser burlado. Uma futura mudanca de selecao por pacote deve provar 79 outros ainda bloqueados, sem alterar G2/ruleset.

Status global preservado: G1 PARTIAL, G2 CLEARED limitado, G3 NOT_CLEARED, ADR-0003/0075 PROPOSED, NLE-D009 OPEN, 80 blocked WOs, 748 PLANNED_BLOCKED, 0 ready, engine=false. Nenhuma PR -03 de codigo permitida a partir da mera aprovacão deste contrato.
