# NLE-PRPLAN-CORE-01-07 — SDL3 runtime init/quit (INTERNAL_ONLY)

**Gate:** G6 individual, conditional on gate PR audit/merge and executor fresh Source Check. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-07`. **Predecessor:** `-06` `COMPLETED` via PR #432. **Issue:** #18. **Base:** `80a6fdafb2cc0f1f923af83367f21e9260e53323`. **ADR:** [ADR-0084](../adr/0084-core-01-sdl3-runtime-slice.md). **Contract:** [core-01-sdl3-runtime-v0](../contracts/core-01-sdl3-runtime-v0.md).

## OBJECTIVE

Integrate the first real SDL3 slice: initialize and shut down SDL video/events on the owner/main thread through an internal, typed, no-throw `SdlRuntime`, with no SDL types in the header and no window/input/renderer/audio/network behavior.

## CONTEXT

`-03` delivered the internal headless host, `-04`/`-05` are objectively covered by it, and `-06` delivered read-only portable paths. All four are `COMPLETED`. C01-D03/D04 already ratified SDL3 as a thin host adapter with main-thread video and headless independence; G3-V01 selected SDL3 3.4.20 as a candidate. ADR-0003/0075 remain `PROPOSED` and G3 global `NOT_CLEARED`; this packet is a bounded internal slice, not their approval.

## SCOPE

- Pinned SDL3 3.4.20 static build, official commit, CMake `FetchContent` at build time only.
- Internal `SdlRuntime`: `initialize`, `shutdown`, `initialized`, owner-thread check, typed `SdlError`, linked version query.
- Dummy-video CI tests: init/quit cycles, duplicate init, wrong thread, invalid driver failure/recovery, version, header isolation, existing CTest regression.
- Minimal evidence and checkpoint delta after observed results.

## OUT OF SCOPE

Window creation/lifecycle, input/event pumping, HiDPI/IME/hotplug, renderer/RHI, audio, gamepad, dialogs, clipboard, VFS, public C ABI/plugin/SDK, SDL headers in any engine header, real display-driver qualification, packaging/release, other modules, next packet.

## FILES / SOURCES TO READ

`AGENTS.md`; checkpoint; Ledger/ADRs (0003, 0075, 0083, 0084); Scope/DoD/Architecture/Requirements; CORE-01 gates and C01-D03/D04; both existing contracts; PR-plan manifest/activation; merged `-03`/`-06` source, tests, CMake, CI evidence; SDL3 3.4.20 official license/CMake at the pinned commit. Inspect Git before editing.

## REQUIREMENTS

GOV-001..005, CAP-010/014, NFR-002/003/005; C01-D03/D04 bounded; CORE-01 catalog "inicializar e desligar headless e com janela" only for the init/quit portion here. No new owner technology decision; the SDL3 direction and 3.4.20 candidate are already ratified.

## ARCHITECTURE RULES

Internal namespace/header only; SDL3 hidden in `sdl_runtime.cpp`; no SDL type/macro/handle in the header; main-thread ownership; typed errors; no exceptions across the boundary; no global adapter singleton; no window/renderer/audio/network call; existing headless and paths libraries remain independent. Pinned dependency only; no system install or vendor copy.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`. Build-time FetchContent from the exact official commit; no runtime download, package manager, secret, paid runner, cache/upload or deployment. Standard public CI on `ubuntu-24.04`, `windows-2025-vs2026`, `macos-15`; Linux sanitizers when preinstalled. ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80 module WOs `BLOCKED`. No next packet/module.

## ACCEPTANCE CRITERIA

- Exact allowlist; fresh Context Lock; selector ready only for `-07`.
- `SdlRuntime` contract implemented; no SDL types in header; wrong-thread and duplicate-init rejection; failed init cleans partial state; idempotent shutdown; no-throw destructor on owner thread.
- SDL-01..SDL-08 executed with dummy video on 3 OS and sanitizers; linked version 3.4.20; existing 12 CTests regression; no HIGH/CRITICAL.
- Docs Validation + native CI PASS at exact PR HEAD; objective pt-BR audit; squash/readback; no real-window/release/ABI claim.

## TESTS

Docs: `validate_docs.py`, `validate_wo_registry.py`, `validate_pr_plans.py`, unit tests, packet selector. Native: 20 SDL init/quit cycles, duplicate, wrong-thread, invalid-driver failure/recovery, version, header-isolation compile, existing 12 CTests; CMake Presets; ASan/UBSan when supported. Real window/display is `NOT_QUALIFIED` in this slice.

## DELIVERABLES

Exactly: `src/stormline/core/internal/sdl_runtime.hpp`, `sdl_runtime.cpp`, `tests/core/sdl_runtime_tests.cpp`, `CMakeLists.txt` (additive), `.github/workflows/core01-internal-headless.yml` (timeout only if needed), `docs/evidence/NLE-PRPLAN-CORE-01-07.md`. GitHub PR, exact CI receipts, Evidence, objective pt-BR audit, proposed checkpoint. Gate files separate.

## REVIEW FORMAT

Portuguese Brazil: base/head, exact files, contract compliance, SDL-01..08 + sanitizer, existing regression, dependency pin/license/SBOM, no SDL leak, no window overclaim, risk/security. Verdict `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`. Corrections only in the same WO/PR.

## STOP CONDITION

STALE context, gate not merged, selector blocked, SDL3 fetch/commit/license mismatch, existing test regression, CI red, HIGH/CRITICAL, unapproved dependency, out-of-allowlist change, real-window/release/ABI overclaim, another packet/module unlock, or any destructive operation. Never bypass G2 or force push.

## CONTEXT LOCK

Gate base `80a6fdafb2cc0f1f923af83367f21e9260e53323`; activation pins the exact ADR/contract/source blobs and SDL3 commit. Executor must recompute fresh raw SHA-256 after the gate merge and stop/rebase on substantive change.

## EVIDENCE BUNDLE

Separate `docs/evidence/NLE-PRPLAN-CORE-01-07.md` with PR/CI/audit/merge SHAs, exact toolchains, SDL3 commit/license, SDL-01..08 results, existing regression, sanitizer, no-SDL-leak proof, limitations and rollback. Gate evidence never masquerades as implemented code.
