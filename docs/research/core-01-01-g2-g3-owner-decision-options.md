# CORE-01 / G2–G3 — Eleven owner decisions, technology qualification and proof gates

**STATUS: ALL 11 `AWAITING_OWNER`; PROPOSAL ONLY.** Date: 2026-11-16. **Stable WO:** [NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md) · **Issue:** [#387](https://github.com/KayzenRoot/stormline/issues/387) · **BASE main:** `2c88ac3ba88c3c0dde639fbf3969c24860c9de3f` · [Evidence + Context Lock](../evidence/NLE-PRPLAN-CORE-01-01-G2G3-OPTIONS.md).

## Objective and authority boundary
Qualify 11 questions `C01-D02..D07/D10..D13/D15`, select **provisional technical recommendation A** per question, document B/C alternatives, explicit risk, measurable exit proofs and dependency on G2/G3. **No owner ratification is inferred from request to continue or from the proposal's eventual documentary merge.** The four existing `C01-D01/D08/D09/D14` and eight `G1-M01..M08` are owner-ratified bounded; their source decisions must not be altered. Current gate state: G1 PARTIALLY_RATIFIED_NOT_CLEARED, G2 BLOCKED_NOT_VERIFIED, G3 OPEN_OWNER_DECISION, G4-G8 not started/blocked.

## Eleven independent owner options (A is preferred, NOT OWNER-RATIFIED)

### C01-D02 · Language baseline and toolchain [G3]
- **A | recommended:** internal C++20, no mandatory named C++ modules and no default C++23/preview; **compiler+stdlib+runtime versions are separate future sign-offs**. MSVC `/std:c++20 /permissive-`, GCC/Clang `-std=c++20` (not executable tests here).
- **B:** C++23 first: newer APIs but greater compiler/standard-library support fragmentation. **C:** C++17: mature but forfeits C++20 concepts, coroutines and other capabilities without proven overall portability advantage for this engine.
- **Exit proof:** owner states allowed C++20 features; lock MSVC/GCC/Clang/AppleClang versions/SDK and language flags; compile minimal host in Windows x64/Linux x64/macOS ARM64; warnings and stdlib feature-test matrix; reproducible build metadata. No claim of C++20 support proven until native builds.

### C01-D03 · OS platform adapter [G3]
- **A | recommended:** **thin SDL3** abstraction for window/input/timing/events; SDL types/headers stay out of external engine API. Pin future SDL release archive digest and evaluate license/transitives.
- **B:** GLFW for window/input, simpler but possibly separate adapters for additional devices/events. **C:** native Win32/Cocoa/Wayland/X11: control and lower-level specialization but substantially higher cross-OS maintenance.
- **Exit proof:** benchmark basic init/focus/IME/HiDPI/hotplug/keyboard/mouse and window lifecycle on each real OS; compare alternative against SDL3 with same functional matrix. No permanent SDL3 adoption or ADR approval at this documentary stage.

### C01-D04 · SDL init and event loop thread ownership [G3]
- **A | recommended:** windowed host owns all SDL video startup/teardown on **main thread**, subsystem lease/refcounts balanced; headless never initializes video/audio as mandatory; baseline **standard main with isolated SDL3 entrypoint shim**, subject to platform compile proof. Avoid blocking wait on main thread via `SDL_RunOnMainThread`.
- **B:** SDL3 `SDL_MAIN_USE_CALLBACKS` lifecycle; natural platform integration, but callbacks and event threading require separate contract/validation. **C:** wholly custom native loop; less SDL-specific coupling but more per-OS maintenance.
- **Exit proof:** run main-thread assertions, paired `SDL_InitSubSystem/SDL_QuitSubSystem`, unwind after partial failure, no deadlock, entrypoint handling for all three OS targets. This is a candidate, not adopted code.

### C01-D05 · Build/test system [G3]
- **A | recommended:** CMake project-wide `CMakePresets.json` and `ctest --preset` with Ninja default; **propose minimum CMake 3.27 and Presets schema 6 only for owner evaluation** (support verified before fixing). Preserve `CMakeUserPresets.json` as untracked local config and platform/toolchain fallback (Xcode/Visual Studio generator when required).
- **B:** Meson + Ninja: coherent smaller model, but changes future contributors' ecosystem and integration. **C:** Bazel: hermetic potential but high workspace/toolchain complexity for initial host. Native IDE builds alone lead to divergent CI.
- **Exit proof:** owner approves exact CMake minimum/schema/version, toolchain matrix and Ninja version; `cmake --preset`, build/test presets, clean reproducibility + configure failures, CTest negative cases and artifact/SDK hash receipts for Win/Linux/macOS. No build files created by this PR.

### C01-D06 · ABI/public API [G3/G4]
- **A | recommended:** C++20 types internally, RAII ownership and error model behind an opaque host abstraction; **defer public ABI guarantee**. For a future externally loaded plugin/SDK boundary, prefer **versioned C ABI** with opaque handles, explicit allocator and destroy operations, UTF-8 length parameters, stable calling convention and error codes; **only if actual plugin/SDK scope is owner-approved**.
- **B:** directly expose STL/SDL_Window*/templates across binary boundary: less glue but compiler/runtime/layout ABI instability. **C:** universal C ABI for every internal module: unnecessary boilerplate and allocations in engine core.
- **Exit proof:** contract for ownership/lifetime of `HostHandle`, immutable version query, handle generation invalidation, symbol exports, cross-DLL allocation/exception escape prohibition, layout/alignment and multi-toolchain conformance; dedicated API review later. Do not assume C++ ABI portability.

### C01-D07 · Host state machine and typed errors [G3]
- **A | recommended:** explicit `Uninitialized → Initializing → Running → Suspending → Running → ShuttingDown → Terminated` with recoverable `InitFailed` transition and typed `Result/Error`. Idempotent cleanup; one lifecycle owner; callbacks may signal cancel/stop without process-wide abort.
- **B:** implicit global singleton startup: lower initial code volume but testing/reentrancy difficult. **C:** process abort/exit on init failure: superficially simple, unacceptable in editor/headless host.
- **Exit proof:** transition matrix (valid/invalid), duplicate startup/teardown behavior, partial init unwind, timeout/cancel errors, no resource leaks, 200/200 headless and 100/100 window cycles for approved OS, injected device loss and recovery. State machine contracts only; no implementation now.

### C01-D10 · Capability detection / SAPL [G3]
- **A | recommended:** capability returns **SUPPORTED / UNSUPPORTED / UNKNOWN**, evidence source and confidence; start with a thin SDL3/platform capability adapter. Do not build an additional proprietary `SAPL` layer unless identical-case benchmark proves material improvement or fixes a required semantic gap.
- **B:** proprietary capability graph immediately: higher abstraction but cost/complexity without evidence. **C:** boolean supported only: cheap, but misclassifies unknown driver/environment states as unsupported.
- **Exit proof:** fixtures for permission denied, missing display, unsupported drivers, unsupported CPU instruction, stale cache; no confusion of UNKNOWN vs UNSUPPORTED; count and benchmark CPU/memory/call overhead vs thin adapter, documented accept/reject threshold approved by owner. Renderer feature arbitration stays with GFX-01.

### C01-D11 · Risk classification by slice [G3/G5]
- **A | recommended:** **STANDARD candidate** for isolated host/init/pure adapters; **ELEVATED candidate** for native OS/privileged paths, plugin/lifetime bridges, loader and persistent integration; **HIGH_ASSURANCE only for actual future irreversible/signing/privileged-security operations**, assessed individually.
- **B:** mark all LOW: insufficient regression/security coverage. **C:** mark all HIGH_ASSURANCE: consumes resources and causes blocked progress unrelated to actual threats.
- **Exit proof:** owner signs risk justification for **each eventual implementation slice**, threat boundary and proof obligations, unit/integration/sanitizer/migration/rollback scope; no bulk mutation of 80 registry entries. Main code registry risk remains `UNCLASSIFIED`.

### C01-D12 · Free CI + verified G2 protections [G2]
- **A | recommended (proposal only):** public repository standard GitHub-hosted runners `ubuntu-24.04`, `windows-2025` and `macos-15` arm64 for **future** native CI, no paid runner; current PR/docs check is actually named **`docs-validation`**. Read-only token on untrusted PRs, no repository secrets, pin action versions/digests where possible, retain exact job names and require owner-approved *enforced* PR/merge checks via ruleset/protection.
- **B:** larger/paid runner: capacity and special Apple tooling but violates R$0 goal without new authority. **C:** CI only on main: fewer PR runs, insufficient gate against bad code merging.
- **G2 hard reality (2026-11-16):** GitHub API `main.protected=false`, `GET /rulesets=[]`, detailed `GET /branches/main/protection` returns **403 Resource not accessible by integration**. Therefore **NO ENFORCEMENT PROOF**, regardless of successful CI. No settings mutation authorized in this WO.
- **Exit proof:** owner explicitly approves desired branch rules (PR required, strict required checks by exact real job name, restrict bypass/deletion/force push, single-maintainer workflow without external reviewers), separate authorized settings change, then **GET ruleset/protection/enforcement readback** + negative test of merge denial on red check and no-bypass evidence. Docs success alone cannot satisfy G2. Untrusted `pull_request_target`/fork execution with secrets forbidden.

### C01-D13 · Licenses, provenance, redistribution [G3]
- **A | recommended:** candidate SDL3 **zlib**, CMake **BSD-3-Clause**, Ninja **Apache-2.0**; maintain SBOM/SPDX per pinned release, source hashes and NOTICE/attribution where required. Check component/transitive licenses and redistribution separately; avoid choosing any **Stormline engine-source license** by association.
- **B:** bundle dependencies and simply assume licenses: unacceptable compliance risk. **C:** select engine license now as part of stack: violates independent `NLE-D009 OPEN` owner decision.
- **Exit proof:** tag+sha256 for each version, official license snapshot and notices, dependency tree, static/dynamic distribution mode and compatibility review, platform-specific packaging rights. **No LICENSE file, brand/copyright policy or redistribution authorized here.**

### C01-D15 · Avoid circular “approved before proof” [G3/G4]
- **A | recommended:** **two-stage evidence policy**: (1) owner accepts provisional stack *candidate* without approving ADR-0003; (2) when empirical native proof is truly prerequisite, propose **separately scoped experimental Work Order with explicit owner authorization and bounded cleanup**, outside code WOs and CORE-01-02. Until gates are authorized, no code is written.
- **B:** approve ADR-0003 from Docs Validation alone: conflates text checks with platform proofs. **C:** allow Zcode to write code from BLOCKED WO to “prove” architecture: violates queue and Source Pack constraints.
- **Exit proof:** explicit decision as to whether an experiment is required, risk class and owner authorization for its *own* WO, disposable artifacts, nonproduction isolation, audit, C++ three-OS smoke/benchmark proof; only a **separate future owner vote** may promote or supersede ADR-0003. No automatic next packet.

## Proof matrix / dependency graph
| Gate | Required deliverable | Current state |
|---|---|---|
| **G1** | Existing 12 bounded ratifications + exact OS patches/SDKs, full 1.0 release Scope/DoD, p95/RSS later ratification and actual validation | `PARTIALLY_RATIFIED_NOT_CLEARED` |
| **G2** | Actual enforceable `main` PR/CI ruleset and negative checks proof, without external reviewer requirement; zero secrets in untrusted forks | `BLOCKED_NOT_VERIFIED` |
| **G3** | **11 owner decisions** D02/D03/D04/D05/D06/D07/D10/D11/D12/D13/D15, technology/license/risk qualifications | `OPEN_OWNER_DECISION` |
| **G4** | Independent audited owner decision on ADR-0003 (or superseding ADR), only when evidence/approval path satisfied | `NOT_STARTED` |
| **G5–G6** | Per-slice risk and build/ABI contracts, fresh SHA-256 context lock, authorized work packet | `BLOCKED` |
| **G7** | Actual C++ compilation/test/sanitizer/physical hardware receipts | `NOT_EXECUTED` |
| **G8** | All 1.0 DoD, security, compatibility, license, distribution and release authorization | `NOT_AUTHORIZED` |

**Owner choice contract:** For each ID reply **`C01-Dxx: RATIFICAR A`**, **`MODIFICAR: ...`**, or **`ADIAR`**; the document itself and its documentary PR/CI never records a user approval for any of the 11 IDs. Explicit itemized approval is required before any canonical Ledger ratification change. Partial responses keep other IDs `AWAITING_OWNER`.

## Work Order increment contract (same stable ID)
- **OBJECTIVE:** independently qualify 11 pending G2/G3 technical/proof decisions; no implementation.
- **CONTEXT:** Git `main` base above, approved prior 12 G1 bounded decisions; issue #387 open.
- **SCOPE:** technical options A/B/C, 11 owner-decision rows, observable G2 blockers, proof matrix, official sources and Context Lock.
- **OUT OF SCOPE:** actual owner ratification, ADR promotion, NLE-D009 license, branch-settings writes, CI config, registry/manifest, code or CORE-01-02.
- **FILES/SOURCES TO READ:** checkpoint, Ledger, Scope, DoD, Architecture, Requirements, ADR-0003/0075, source hierarchy, issue #387, G1 dossier/WO, registry/manifest, external official standards.
- **REQUIREMENTS:** governance gates 0–8, 80/80 BLOCKED, C++ cross-OS and CPU-only headless accepted G1, public no-MVP.
- **ARCHITECTURE RULES:** keep SDL hidden, headless not dependent on video/audio, engine ABI not exposed, GFX/NET ownership boundaries.
- **CONSTRAINTS:** no paid required CI, no required external reviewers, no bypass/destructive writes, no false test evidence.
- **ACCEPTANCE CRITERIA:** exactly eleven non-ratified decision options, alternatives and exit proofs, two ADDED Markdown only, all canonical/queue files byte-identical.
- **TESTS:** GitHub Docs Validation exact PR head (links, dependencies, selector guard, skills and packet plan tests), objective pt-BR audit; native and physical tests **NOT RUN**.
- **DELIVERABLES:** this board, evidence file, documentary PR, CI/audit/readback, independent factual checkpoint if approved and necessary, issue #387 pointer.
- **REVIEW FORMAT:** APPROVED DOCUMENTARY / CORRECTION REQUIRED / BLOCKED with scope and negative evidence in pt-BR.
- **STOP CONDITION:** stale critical SHA, inferred approval, CI failure, HIGH/CRITICAL known defect, unauthorized code/CI settings/branch/license/ADR/reg/manifest write, CORE-01-02 progress.

## Official upstream references verified 2026-11-16
- [MSVC C++ /std:c++20 and conformance](https://learn.microsoft.com/en-us/cpp/build/reference/std-specify-language-standard-version) · [SDL3 SDL_InitSubSystem main-thread/refcounts](https://wiki.libsdl.org/SDL3/SDL_InitSubSystem) · [SDL_RunOnMainThread deadlock warning](https://wiki.libsdl.org/SDL3/SDL_RunOnMainThread) · [SDL_main callbacks/entrypoints](https://wiki.libsdl.org/SDL3/README-main-functions).
- [CMake Presets schema and CTest](https://cmake.org/cmake/help/v3.27/manual/cmake-presets.7.html) · [CMake official BSD-3 licensing](https://cmake.org/licensing/) · [Ninja official Apache-2.0 repository](https://github.com/ninja-build/ninja) · [SDL official zlib license](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt).
- [GitHub standard public runners (free)](https://docs.github.com/en/actions/reference/workflows-and-actions/workflow-syntax) · [GitHub rulesets/required checks](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/available-rules-for-rulesets) · [GitHub untrusted PR security](https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target).

## FINAL INVARIANTS
`C01-D02..D07/D10..D13/D15` = **11/11 AWAITING_OWNER**. `C01-D01/D08/D09/D14` and `G1-M01..M08` remain only 12 bounded owner ratifications. `G1 PARTIALLY_RATIFIED_NOT_CLEARED`, `G2 BLOCKED_NOT_VERIFIED`, `G3 OPEN_OWNER_DECISION`, ADR-0003/0075 PROPOSED, engine-source license NLE-D009 OPEN. 80 code WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, 0 executor_ready/approved_adr, 80 release_class UNDECIDED, 80 risk UNCLASSIFIED, `engine_implemented=false`. CORE-01-01 and CORE-01-02 both `PLANNED_BLOCKED`. No C++/runtime/engine tests executed. This document is an options dossier only.
