# NLE-PRPLAN-CORE-01-01 / G1 owner-delegated recommendation evidence

**Status:** `AGENT_SELECTED_PENDING_EXPLICIT_OWNER_RATIFICATION` (2026-11-16). **Work Order:** [NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md), **Issue:** [#387](https://github.com/KayzenRoot/stormline/issues/387), [selection](../research/core-01-01-g1-delegated-selection.md). This is NOT an implementation Evidence Bundle, tested platform support or owner sign-off.

## Origin and authority
Owner said in conversation: “Continue vc deve escolher as manifestações que achar melhor”. That explicitly delegates **selecting** the technical recommendations, not signing specific eight item-by-item `OWNER_RATIFIED_G1` entries. AI selected A for eight questions G1-M01..M08, with lifecycle/date guard for Windows and calibration guard for performance. **All eight remain PENDING explicit technical owner ratification**, and four prior C01-D01/D08/D09/D14 remain OWNER_RATIFIED_G1_BOUNDED. No other owner intent is inferred.

## Full Source Check / Context Lock
Base `main=3fa9c59aaa971c8fbd99983b6a6656520dea8c5c` checked via connected GitHub.
Verified Git *blob SHA-1* fingerprints (Git object hashes, **not** raw file SHA-256):
- `docs/11-checkpoint.md`: `eecbabb5f3506b16590fafcbd74c13f2c0557a25`
- `docs/10-decisions-ledger.md`: `7194a7e0d122b3f0f4d20c4707f8b83728958e02`
- `docs/03-scope.md`: `b7597e900116b0594dd2c87fffe93fe3a1f9e2ce`
- `docs/09-definition-of-done.md`: `5514e876b09973054db4c3b8a031ba34b5fc9222`
- `docs/04-architecture.md`: `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/research/core-01-01-g1-minima-qualification.md`: `f1bb6702956a2b270a1e684570516f146b0d98b3`
- `docs/evidence/NLE-PRPLAN-CORE-01-01-G1-MINIMA-QUALIFICATION.md`: `10f4408f3d875e7f2c4085ec2caf86de33606e1c`
- `docs/work-orders/NLE-PRPLAN-CORE-01-01.md`: `72d0661f9d354a84733d991afc60cdee94d56fca`
- `docs/research/core-01-01-owner-technical-decision-dossier.md`: `c65183ae9c348d4d35ef947550c1a67f4ebe0846`
- `docs/engineering/core-01-01-qualification-gates.md`: `46f0e7f4e6583654d574e14fb53ec25d9ba11fd6`
- `docs/queue/implementation-registry.json`: `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`
- `docs/pr-plans/manifest.json`: `95782386c59e5af8ac1a8c92a7a35c87992463db`
- `docs/adr/0003-core-01-platform-technology.md`: `2ee92dda5ab81ddcc446b9d5325d29257350e217`.
**STALE** if a critical source or main changes; re-evaluate before owner ratification. For a future executor fresh SHA-256 on raw critical sources required.

## Decisions / measures and remaining evidence
| G1 ID | Selection and required proof | Status |
|---|---|---|
| M01 | Windows 11 25H2 x64 provisional minimum, 26H2 compatibility; verify OS support + physical smoke and reassess before 25H2 end of servicing | AGENT_SELECTED_PENDING_OWNER |
| M02 | Ubuntu 24.04 LTS x64/glibc 2.39 reference; validate symbol-floor, packaging and both Wayland/X11 by real fixtures | AGENT_SELECTED_PENDING_OWNER |
| M03 | macOS 15 ARM64 app floor candidate, macOS 26 compatibility, Xcode host minimum distinct; physical M1+ proof | AGENT_SELECTED_PENDING_OWNER |
| M04 | No mandatory AVX/AVX2 in CORE-01 baseline; runtime ISA dispatch + negative-SIGILL fixtures; honor Windows 11 processor/OS requirements | AGENT_SELECTED_PENDING_OWNER |
| M05 | Headless target fixture 2 logical CPUs / 4 GiB; window 4 logical CPUs / 8 GiB, not whole Editor/game requirements; actual hardware proof | AGENT_SELECTED_PENDING_OWNER |
| M06 | CORE-01 minimal 1.0 mandatory intent and advanced capabilities conditional; Scope/DoD and registry classes remain unresolved | AGENT_SELECTED_PENDING_OWNER |
| M07 | Preserve 200/100/10k/30+30; zero silent critical-event loss / sanitizer issues; typed no-display error within 5s candidate, p95/RSS after calibration | AGENT_SELECTED_PENDING_OWNER |
| M08 | OS/vendor lifecycle recheck within 90d of future public release, full Scope/DoD and per-module classes still to approve; no public MVP | AGENT_SELECTED_PENDING_OWNER |

## Negative verification and proof obligations
- `G1 PARTIALLY_RATIFIED_NOT_CLEARED`, `G2 NOT_VERIFIED` (main reported protected=false), `G3 OPEN`.
- `ADR-0003` and `ADR-0075` remain PROPOSED; `NLE-D009` engine code license OPEN; no library/build/toolchain/ABI approved.
- 80/80 original code WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, zero `approved_adr`, zero `executor_ready`, 80 `release_class=UNDECIDED`, 80 `risk=UNCLASSIFIED`, `engine_implemented=false`.
- CORE-01-01 and CORE-01-02 remain `PLANNED_BLOCKED`; issue #18 open/blocked, #387 open, no next packet or code.
- C01-Q001..Q032 remain `FUTURE_NOT_EXECUTED`; no actual compiler/headless/windowed/hardware benchmarks. Existing Docs Validation must not be described as native/hardware success.
- Windows and macOS source lifecycle information is public documentation (Microsoft/Apple); prospective numbers are not certified Stormline limits.

## Documentary PR audit contract
**Allowed:** two new Markdown files, this Evidence and [selection](../research/core-01-01-g1-delegated-selection.md). **Forbidden:** changing pre-existing docs (especially Ledger, Scope, DoD and ADR), registry/manifest/queue, CI configuration, settings, license, code, native tests or release claim.

**Tests:** GitHub Docs Validation at exact PR HEAD (source links, registry/blocked selector, DAG and unit tests). Objective pt-BR audit of owner-delegation boundary, hashes, choices and no HIGH/CRITICAL defects; squash/readback and independently audited factual checkpoint if due. No completed PR/CI/audit is asserted before it exists.

**STOP:** treating selection as owner ratification, any unsupported performance/compatibility claim, code or packet 02, stale base, failed CI, missing verified authority for canonical change.
