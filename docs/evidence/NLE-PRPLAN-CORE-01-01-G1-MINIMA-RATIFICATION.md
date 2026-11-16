# Evidence Bundle — NLE-PRPLAN-CORE-01-01 / owner ratification G1 minima

**Status:** `OWNER_RATIFICATION_DOCUMENTARY_EVIDENCE_ONLY`, G1 `PARTIALLY_RATIFIED_NOT_CLEARED`. **Date:** 2026-11-16. **Work Order:** [NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md). [Owner decision issue #387](https://github.com/KayzenRoot/stormline/issues/387). Prior proposal [PR #392](https://github.com/KayzenRoot/stormline/pull/392) / checkpoint [PR #393](https://github.com/KayzenRoot/stormline/pull/393).

## Explicit owner authority, not inferred
The user directly declared in the active conversation:
> Como proprietário do Stormline, RATIFICO EXPRESSAMENTE as oito seleções técnicas G1-M01..G1-M08 do documento docs/research/core-01-01-g1-delegated-selection.md, no HEAD 709bcaaab9f4d1a95546ff62a4dceaeaf4935cf0, exatamente nos termos e limites apresentados: M01 Windows 11 25H2 provisório/26H2 compatível; M02 Ubuntu 24.04 LTS x64/glibc 2.39; M03 macOS 15 ARM64 e 26 compatível, com mínimo Xcode separado; M04 x86_64 sem AVX/AVX2 obrigatório com dispatch; M05 hardware de prova headless 2 lógicos/4 GiB e janela 4 lógicos/8 GiB; M06 núcleo mínimo CORE-01 obrigatório e avançados condicionais; M07 protocolo 200/100/10000/30+30 com zero perda crítica silenciosa, testes negativos, erro tipado até 5s sem display, p95 e RSS ainda sujeitos a calibração/ratificação; M08 requalificação 90 dias antes de release pública.

The declaration further explicitly prohibits automatic ADR-0003 approval, changes to engine licensing NLE-D009 and main branch protection, release of coding WOs, or starting CORE-01-02, and prohibits declaring tests/platforms certified without objective evidence. This is a truthful transcript of conversational authorization, **not independent cryptographic GitHub owner signature**.

## Verified Source Check and Context Lock
**Exact GitHub main base SHA:** `709bcaaab9f4d1a95546ff62a4dceaeaf4935cf0`.

**Critical Git object blob SHA-1 fingerprints**, verified by direct GitHub fetch on the base (they are **not** raw-file SHA-256 and do not substitute for an executor's fresh SHA-256 context lock):
- checkpoint `docs/11-checkpoint.md`: `c71e9141f19830b3efc4399d896f36ade4a3a606`
- Ledger `docs/10-decisions-ledger.md`: `7194a7e0d122b3f0f4d20c4707f8b83728958e02`
- Scope `docs/03-scope.md`: `b7597e900116b0594dd2c87fffe93fe3a1f9e2ce`
- DoD `docs/09-definition-of-done.md`: `5514e876b09973054db4c3b8a031ba34b5fc9222`
- Architecture `docs/04-architecture.md`: `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- Requirements `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- Source Hierarchy `docs/00-source-hierarchy.md`: `58a377bc76cafdd3377d733d4f30ef53661bb034`
- Security `docs/05-security.md`: `eaa02b711f62498e41c82b6cb6615a94c375881c`
- Test Plan `docs/06-test-benchmark-plan.md`: `4c0be969744af6dd747cc828fbacc58662b06f40`
- Deployment `docs/07-deployment.md`: `23d851be6a55826de269b3141109a772935a9f2d`
- qualified proposals `docs/research/core-01-01-g1-minima-qualification.md`: `f1bb6702956a2b270a1e684570516f146b0d98b3`
- owner-delimited selection `docs/research/core-01-01-g1-delegated-selection.md`: `9ea9d98f7f96703451616a2d73178ba7731a8a16`
- G1 gates `docs/engineering/core-01-01-qualification-gates.md`: `46f0e7f4e6583654d574e14fb53ec25d9ba11fd6`
- WO `docs/work-orders/NLE-PRPLAN-CORE-01-01.md`: `72d0661f9d354a84733d991afc60cdee94d56fca`
- prior delegated evidence `docs/evidence/NLE-PRPLAN-CORE-01-01-G1-DELEGATED-SELECTION.md`: `90cfaa79170e65c8c766d2bfc790517934a51c19`
- implementation registry `docs/queue/implementation-registry.json`: `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`
- PR plan manifest `docs/pr-plans/manifest.json`: `95782386c59e5af8ac1a8c92a7a35c87992463db`
- ADR-0003 `docs/adr/0003-core-01-platform-technology.md`: `2ee92dda5ab81ddcc446b9d5325d29257350e217`
- ADR-0075 `docs/adr/0075-qa-01-ci-matrix-security-policy.md`: `22e91a36c1e0a8121163fa4778abd0489fed86e5`.

**STALE policy:** if Git HEAD or any canonical source changes before writing/merge, refresh source snapshots and rebase Context Lock. No codesigning, native toolchain, platform deployment targets, CPU/ISA, performance or hardware tests were run here.

## Exactly eight bounded ratifications, no more
| ID | Owner ratified requirement | Remaining proof / no-release caveat |
|---|---|---|
| G1-M01 | Windows 11 25H2 x64 *provisional floor*, 26H2 compatibility | Revalidate Microsoft lifecycle and OS requirements before release, physical Windows 11 smoke; no EOL platform support promise |
| G1-M02 | Ubuntu 24.04 LTS x64 with glibc 2.39 as reference | Verify ELF/GLIBC symbol floor, kernel/loader, native Wayland/X11/headless; no all-Linux claim |
| G1-M03 | macOS 15 ARM64 M1+ deployment target candidate, 26 compatible; separate Xcode host minima | Pin Xcode/SDK/deployment patch and physical target; macOS Intel conditional |
| G1-M04 | x86_64 host without mandatory AVX/AVX2, optimized runtime dispatch and native ARM64 | CPUID negative, no SIGILL and compiler flags, OS-supported CPU qualification |
| G1-M05 | Test hardware fixtures headless 2 logical CPU/4 GiB and window 4 logical CPU/8 GiB | GPU-less headless native proof, window driver; NOT commercial Editor/game minimum |
| G1-M06 | Minimal CORE-01 lifecycle/window/headless 1.0 mandatory intent, advanced extras conditional | per-feature acceptance and all-module release-class map/DoD pending, registry still UNDECIDED |
| G1-M07 | 200/100/10000/30+30 future protocol, zero silent critical loss, negative tests, no-display typed error <=5s | Zero sanitizer-detected UAF/leaks, actual CI/hardware; p95 and RSS thresholds require calibration and another explicit approval |
| G1-M08 | Vendor/OS/security lifecycle re-evaluation 90 days before any public release | Only release on full global product DoD and separate authorization, no public MVP |

## Negative and conflict verification
- Earlier ratified `C01-D01/D08/D09/D14` remain `OWNER_RATIFIED_G1_BOUNDED`. Eleven original decisions `C01-D02..D07/D10..D13/D15` remain `AWAITING_OWNER`; this explicit decision covers *only* eight `G1-M` subquestions.
- No conflict in bounded intent with NLE-D013 (no public MVP), D014 (2D/2.5D/3D/Web), D017 (Windows/Linux/macOS mandatory) or D018 solo documentary governance. No guarantee of physical OS support or full 1.0 DoD is claimed.
- G1 `PARTIALLY_RATIFIED_NOT_CLEARED`: still missing minimum OS patches/SDK, real tests/hardware, p95/RSS calibration and ratification, 80-module release classes, full 1.0 Scope/DoD. G2 main branch enforcement `NOT_VERIFIED`; G3 architecture C++20/SDL3/CMake/ABI/third-party licensing `OPEN`. ADR-0003/0075 PROPOSED, NLE-D009 OPEN.
- `docs/queue/implementation-registry.json` **80/80** code WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false` for 80, `approved_adr=false` for 80, `release_class=UNDECIDED` and `risk=UNCLASSIFIED` for 80, `engine_implemented=false`. `docs/pr-plans/manifest.json`: CORE-01-01 and CORE-01-02 `PLANNED_BLOCKED`; issue #18 open/blocked. `C01-Q001..Q032 FUTURE_NOT_EXECUTED`.
- GitHub Docs Validation is a documentation/control-guard gate, not evidence of native, ABI or performance tests.

## PR exact change scope and completion obligations
Allowed modifications: `docs/10-decisions-ledger.md`, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/research/core-01-01-g1-delegated-selection.md`, `docs/engineering/core-01-01-qualification-gates.md`, `docs/work-orders/NLE-PRPLAN-CORE-01-01.md` and ADD **this** Evidence file; nothing else. Must inspect GitHub diff, exact HEAD Docs Validation SUCCESS, objective pt-BR audit and no known HIGH/CRITICAL, then squash main and readback. Record actual PR/CI/audit/merge SHA **only when observed** in independent checkpoint PR, not preclaim here.

**STOP:** owner authority expanded beyond M01..M08, any ADR approval, release class/registry/manifest/security/CI or branch settings write, license selection, code/C++/engine test claims, or activation of package 02.

## Closure evidence of PR #394 (updated after actual merge, before independent checkpoint)
- [PR #394](https://github.com/KayzenRoot/stormline/pull/394), base `709bcaaab9f4d1a95546ff62a4dceaeaf4935cf0`, final audited HEAD `83caac2beff303059d37ed1653fe8d8250ecf328`, exactly six Markdown MODIFIED and one Evidence Markdown ADDED. GitHub Docs Validation [run #43880470785](https://github.com/KayzenRoot/stormline/actions/runs/43880470785) SUCCESS, job `docs-validation` #133344682949 (all steps successful, including reject blocked coding WOs). Objective pt-BR documentary audit [#6918454030](https://github.com/KayzenRoot/stormline/pull/394#issuecomment-6918454030) APPROVED only for bounded owner ratification; normal squash + main readback [`db2c82994622a68b5350941f534f7c247bb47c73`](https://github.com/KayzenRoot/stormline/commit/db2c82994622a68b5350941f534f7c247bb47c73).
- **Separate checkpoint PR/CI/audit:** distinct steps to be recorded in that PR after they occur. These are not prematurely claimed here. All eight G1-M requirements ratified **as bounded plans** only, not tests. G1 not cleared, G2/G3 open, 11 C01 owner decisions open, NLE-D009 OPEN, ADR-0003 PROPOSED, 80 code WOs blocked, engine false.
