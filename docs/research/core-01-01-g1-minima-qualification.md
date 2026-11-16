# CORE-01-01 / G1 — Qualificação de mínimos e aceite 1.0 (PROPOSTA PARA OWNER)

**Status:** `QUALIFIED_PROPOSALS_AWAITING_OWNER`. **Stable Work Order:** [NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md), **issue:** [#387](https://github.com/KayzenRoot/stormline/issues/387). **Date:** 2026-11-16. **Base main:** `06edd79c9627fac0eb94d4d85130e09bc6034fa6`.
**Explicit previous ratifications remain immutable:** C01-D01, D08, D09, D14 = `OWNER_RATIFIED_G1_BOUNDED`, per [Ledger](../10-decisions-ledger.md). The **following eight qualification questions are NOT RATIFIED**, and do not amend those four decisions.

## Objective, limits, ownership
Qualify only unresolved G1 parameters: minimum OS/CPU/runtime, physical target availability, release depth, global Scope/DoD distinction, quantitative acceptance and requalification policy. No option may be read as adopted until a new, identified, explicit owner statement. Do not turn this document into a new ADR, new coding packet, code branch, license, required GitHub check or approved release class.

## Context / source hierarchy
Checkpoint > Ledger/approved ADR > Scope > DoD > Architecture > Requirements > original CORE-01 dossier/gates > this proposal. The original module has **no formal predecessor**. QA-01 depends on CORE-01 downstream; PLAT-03 owns Web, NET-02 owns server authority, GFX-01 owns GPU backend selection. Current Source Pack documents P00/no code, 80 code WOs BLOCKED, 0 executor_ready and 0 approved ADR.

## Owner qualification decision board (eight open subquestions)
These `G1-M0x` IDs are **question IDs under the same stable Work Order**, not new approved ADRs or mandatory work packages. A=preferred for discussion, B/C=alternatives, D=defer. **All eight: `AWAITING_OWNER`.**

| ID | Question and recommended option A (NOT APPROVED) | Alternative B/C & trade-offs | Exit condition |
|---|---|---|---|
| `G1-M01` | **Windows**: propose Windows 11 **25H2 x64** as launch-floor candidate; validate **26H2** as compatibility target. Prefer supported channel over Windows 10/11 24H2. | B: require 26H2 only, shorter matrix but newer machines; C: include 24H2 or Windows 10 legacy tier (higher security/maintenance burden, lifecycle exemptions and explicit risk waiver). | Owner approves edition/version/service policy, CPU/TPM compatibility and a release-time support recheck; actual hardware tests. |
| `G1-M02` | **Linux**: propose Ubuntu **24.04 LTS x86_64** as reference runtime; glibc **2.39** on reference image, X11/Wayland by **tested** capability. No claim of all Linux distributions. | B: 22.04 LTS/GLIBC 2.35 tier for broader device support (more distro variants, CI and symbol-floor validation); C: 26.04 LTS floor (newer stack, narrower installed base). | Record compiler, glibc symbol floor, kernel, packaging dependencies, loader and real X11/Wayland/headless environment; tests per advertised distro. |
| `G1-M03` | **macOS**: propose **macOS Sequoia 15 arm64** as runtime minimum candidate and Tahoe 26 compatibility; Xcode 26 host needs its **own** minimum OS (15.6 per Apple), not necessarily game's minimum deployment target. | B: 26 only reduces deployment matrix, excludes older Apple Silicon; C: macOS 14 additional tier requires separate physical tests because standard hosted macOS 14 runner retired. Intel remains CONDITIONAL. | Pin deployment target and minimum macOS patch, SDK/Xcode version, M1+ physical device, window/focus/HiDPI tests; don't infer runtime deployment from Xcode host minima. |
| `G1-M04` | **CPU architecture**: baseline portable x86_64 **without mandatory AVX/AVX2** or x86_64-v3, with optimized dispatch only when CPUID proves capability; Apple arm64 baseline, no Rosetta dependency. | B: require x86-64-v2/SSE4.2 to simplify optimized paths, excluding older Linux CPUs; C: x86-64-v3/AVX2 would exclude more accessible hardware. For Windows, Microsoft's supported CPU/platform list remains a separate OS requirement. | Specify compiler ISA flags, CPUID negative fixtures, SIGILL prevention, Windows 11 supported CPU/TPM rules, macOS arm64 ABI tests; performance must be measured, not presumed. |
| `G1-M05` | **Hardware proof tiers**: propose reference low-cost headless **2 logical cores, 4 GiB RAM, no display/GPU/audio**; windowed CORE-01 smoke **4 logical cores, 8 GiB RAM** on qualified native display/driver; treat as **test fixture**, not published minimum requirements for entire Editor/game. | B: single 4-core/8 GiB fixture simplifies coverage but misses low-memory headless; C: demand more minimum RAM/cores, potentially violating accessible-hardware goal. GPU minima belong to GFX/PLAT qualification. | Actual owned/accessible physical machine IDs (non-sensitive), CPU model/OS/RAM/driver and budget proof. Missing platform => `NOT_QUALIFIED`, not PASS. |
| `G1-M06` | **Release depth**: propose `MANDATORY_1_0_MINIMUM` only for CORE-01 host init/teardown, typed lifecycle/error, bounded events, portable startup paths when necessary, windowed basic host and genuine headless. Advanced native bridges/capability graph/specialized diagnostics remain separately CONDITIONAL until specific DoD. | B: whole CORE-01 MANDATORY_1_0 inflates release burden and contradicts scope slicing; C: only headless would not prove editor/client windowed acceptance. All 80 modules must still receive separate future release classification. | Owner itemizes each minimum feature, dependencies and exclusions; map to DoD and dedicated acceptance fixtures; registry stays `UNDECIDED` until authorized canonical update. |
| `G1-M07` | **Numerical acceptance**: preserve ratified **200/200** headless cycles, **100/100** window cycles per approved OS, replay **10,000** events, **30 cold + 30 warm** timings. Propose **0 unreported critical-event loss**, 0 sanitizer-detected leaks/UAF, 0 hangs; missing window/display must return typed error within **5 s** (prior Q012 candidate). Report p50/p95; p99 from 30 samples is not statistically reliable. | B: add explicit p95 host-start/stop thresholds **only after baseline calibration** and owner ratification; C: prescriptive speculative cold-start <1 s risks meaningless failures on hosted/macOS CI. Functional pass is not performance certification. | Approve test OS/hardware, allowed event coalescing, memory/leak methodology, timeout, CI time budget, and **separate p95/RSS thresholds after empirical calibration**; C01-Q001..Q032 all NOT_EXECUTED. |
| `G1-M08` | **DoD and support policy**: keep CORE-01 G1 **PARTIAL** pending exact minimum OS/SDK, test hardware, full 1.0 product DoD and per-module release classes. Propose recheck OS support/vendor lifecycle **90 days before public release**, no public MVP. | B: freeze support floors now without revisiting risks supported-OS retirement before product ships; C: broaden support matrix now raises cost/coverage risk. | Ratify policy, trace Scope→Requirement→DoD→test receipt; do not declare G1 cleared or market launch until full product gates G1..G8 and owner's separate authorization. |

## Proposed support & evidence matrix, not product support claim
| Profile | Candidate runtime minimum | CI proof candidate (no native CI exists yet) | Essential physical proof |
|---|---|---|---|
| Windows x86_64 | Win 11 25H2 Home/Pro, supported CPU/driver per Microsoft | Standard `windows-2025` MSVC compile and unit/headless smoke later | Windows 11 real x64 25H2; optional 26H2; basic HWND/focus/resize/teardown |
| Linux x86_64 | Ubuntu 24.04 LTS, glibc 2.39 baseline, X11/Wayland tested separately | `ubuntu-24.04` GCC/Clang later; no display for headless | 24.04 physical bare metal/VM with identified display stack; no claim about generic distros |
| macOS arm64 | macOS 15 on M1+; macOS 26 regression target | `macos-15` ARM64 standard runner candidate, actual availability/cost confirm at setup | Apple Silicon hardware macOS 15 and 26 if available; Cocoa/HiDPI/focus paths |
| Headless cross-OS | Genuine CPU-only no mandatory GPU/display/audio | Cross-OS native harness future **only after separate G3 & execution gates** | 200 cycles per OS, no injected virtual display as false substitute |
| Conditional | macOS Intel, Windows ARM64, older Linux distro, Web PLAT-03 | Future independent feasibility | Mark `NOT_QUALIFIED` unless separately demonstrated |

**Support vs builds:** a Linux GitHub runner does not certify graphics drivers or glibc floor for arbitrary distros; macOS VM smoke does not certify physical Apple devices; Windows Server runner is not Windows 11 physical qualification. Physical devices may be borrowed, not mandatory paid procurement. R$0 CI goal remains.

## Proof obligations and invalid claims
1. **Lifecycle**: startup/shutdown 200/200, window create/resize/focus/destroy 100/100, error paths and partial teardown, resource handles baseline, sanitizers where supported; no crashes/leaks known. Windowed tests without display return typed failure, not hang.
2. **Events**: 10,000 synthetic events preserve sequence for critical events, bounded queue with explicit overflow/coalescing counters; no silent critical loss; exhaustive negative payload tests.
3. **Performance**: report p50/p95 with 30 cold + 30 warm, exact warm-up protocol, variance and CPU/OS/runner, pre-approved target budgets after first native measurement. Do not claim p99 significance or blanket 60FPS/AAA for CORE-01.
4. **ABI/rights**: no implicit C ABI/C++20/SDL3 approval through OS policy. Real compiled ownership/versioned APIs, audit third-party SPDX notices and license NLE-D009 separate.
5. **Release and recovery**: application/profile minimums must not silently become system-wide 1.0 minimum. All mandatory full-version capabilities remain to be classified with end-to-end DoD, backup/recovery and QA/PLAT/BIZ release gates.
6. **CI**: `docs-validation` can validate proposals only. All native tests `FUTURE_NOT_EXECUTED`. Never claim paid Apple signing or free physical hardware.
7. **Owner authority**: each G1-M01..M08 requires `RATIFICAR A`, `ALTERNATIVA B/C [detalhe]` or `ADIAR`. Only exact stated selections may be promoted after fresh source check/audit; this document is not their acceptance.

## Current Source Check and Context Lock
At base main `06edd79c9627fac0eb94d4d85130e09bc6034fa6`; original Git blob object hashes (**SHA-1 for Git, NOT raw SHA-256**) are recorded in [G1 minima evidence](../evidence/NLE-PRPLAN-CORE-01-01-G1-MINIMA-QUALIFICATION.md). **STALE** if checkpoint, Ledger/ADR, Scope, DoD, Architecture, Requirements or registry/manifest changes before write/decision; require source revalidation. No fingerprint here certifies full native code or test result.

## Work Order clarification (same ID; proposal-only documentary increment)
- **OBJECTIVE:** qualify G1 minima and proof obligations for owner decision, without ratification by inference.
- **CONTEXT:** prior PRs #388/#389 integrated; 4 bounded G1 owner decisions; 11 CORE-01 decisions pending.
- **SCOPE NECESSARY:** this options matrix, source-linked evidence and issue #387 discussion only; separate factual checkpoint after approved documentary integration if due.
- **OUT OF SCOPE:** G2 changes, G3 stack approval, ADR/registry/manifest/Scope/DoD edits, 80 code WOs, CORE-01-02, licenses, runtime tests/builds.
- **FILES/SOURCES TO READ:** checkpoint, Ledger, Scope, DoD, Architecture, Requirements, ADR-0003, G1 dossier/gates, PR plan, WO, registry, manifest and official OS/CI sources.
- **REQUIREMENTS:** GOV-001..005, CAP-010/014/016, prior C01-D01/D08/D09/D14 bounded and NLE-D013..017.
- **ARCHITECTURE RULES:** headless OS/GFX/AUD isolation, WEB/NET/GFX ownership boundaries, no public vendor types in unapproved ABI.
- **CONSTRAINTS:** R$0, solo review, zero settings/code/ADR changes, owner signoff, no fake CI/hardware results.
- **ACCEPTANCE CRITERIA:** eight discrete unanswered questions, trade-offs and measurable proof, no new binding choices, exactly 2 ADDED Markdown, original registry/manifest/ADR byte-identical.
- **TESTS:** GitHub Docs Validation at exact PR HEAD, registry BLOCKED guard, links/catalog/skills, objective pt-BR audit; native tests NOT RUN.
- **DELIVERABLES:** G1 minima proposal + evidence, PR CI/audit/readback, issue discussion and independent checkpoint if factual state needs documenting.
- **REVIEW FORMAT:** APPROVED documentary proposal / CORRECTION REQUIRED / BLOCKED, identify residual gates and invariants; pt-BR.
- **STOP CONDITION:** stale source, any approval inferred, expanded implementation/release, unauthorized setting or license change, failed CI, HIGH/CRITICAL, packet 02 started.

## Official research references checked 2026-11-16
- [Microsoft Windows 11 Home/Pro lifecycle](https://learn.microsoft.com/en-us/lifecycle/products/windows-11-home-and-pro): 24H2 Home/Pro out of service Oct 2026; 25H2 Oct 2027; 26H2 Oct 2028, **do not confuse Win Server runner with desktop runtime**.
- [Microsoft supported Windows 11 CPUs](https://learn.microsoft.com/en-us/windows-hardware/design/minimum/supported/windows-11-25h2-supported-intel-processors): Windows 11 CPU/platform support is separate from Stormline instruction-set policy.
- [Ubuntu release cycle](https://ubuntu.com/about/release-cycle): 24.04 LTS standard maintenance through May 2029; [Ubuntu glibc packaging](https://packages.ubuntu.com/search?keywords=glibc) 24.04 glibc 2.39 vs 22.04 glibc 2.35.
- [Apple Xcode SDK and system requirements](https://developer.apple.com/xcode/system-requirements): distinguish Xcode host minimum from application runtime deployment target; [Apple Tahoe device compatibility](https://support.apple.com/pt-br/122867).
- [GitHub Actions runner images](https://github.com/actions/runner-images/blob/main/README.md): Ubuntu 24.04, Windows 2025, macOS 15 arm64; macOS 14 hosted GitHub runner retired Nov 2026.

## Final status
**Eight proposals awaiting owner, NO DECISIONS RECORDED FROM THEM.** Four existing owner ratifications unchanged. G1 `PARTIALLY_RATIFIED_NOT_CLEARED`, G2 branch enforcement NOT VERIFIED, G3 OPEN, ADR-0003/0075 PROPOSED, NLE-D009 OPEN; 80 code WOs BLOCKED, 0 ready/approved ADR, release_class UNDECIDED, risk UNCLASSIFIED, `engine_implemented=false`, CORE-01-01/02 `PLANNED_BLOCKED`. No code/next packet.
