# NLE-PRPLAN-CORE-01-10 — Display, DPI and surface validity (INTERNAL_ONLY)

**STATUS: EXECUTOR_READY ONLY AFTER THE GATE PR PASSES DOCS VALIDATION, PT-BR AUDIT AND SQUASH MERGE; not executable while the manifest is in a blocked state.** **Gate:** G6 individual, conditional on that merge and a fresh executor Source Check. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-10`. **Predecessor:** `-09` `COMPLETED` via PR #444. **Issue:** #18. **Base:** `7e42b48f19272498c732d75f2051704f5b82311f`. **ADR:** [ADR-0089](../adr/0089-core-01-display-surface-slice.md). **Contract:** [core-01-display-surface-v0](../contracts/core-01-display-surface-v0.md).

## OBJECTIVE

Implement the first real CORE-01 display/surface metadata path: enumerate displays, report bounds/usable bounds/content scale, query a window's display/scale/logical/pixel metrics, and invalidate a borrowed surface generation after resize or an observed display/pixel-size change.

## CONTEXT

`-07` delivered SDL3 runtime, `-08` window lifecycle and `-09` the bounded event queue; all are completed and merged. C01-D03 includes display change integration and C01-D04 requires owner-thread video calls. This packet is display/DPI/surface metadata only; renderer/GPU/VRAM and physical hotplug certification remain out of scope.

## SCOPE

- `DisplayInfo`/`DisplayError`/`DisplayService`: owner-thread enumeration, primary display, bounds, usable bounds, content scale; no strings.
- Additive `SurfaceMetrics`, `Window::query_surface`, `Window::surface_valid`; generation invalidation on successful resize and observed display/pixel-size change.
- Fixed caller storage for displays; SDL-owned display array freed; no SDL types in headers.
- Tests DPY-01..DPY-08, existing 40 CTests regression, Linux ASan/UBSan, Evidence Bundle.

## OUT OF SCOPE

Renderer/swapchain/GPU/VRAM, physical hotplug/display-removal certification, real DPI transition qualification, multi-monitor movement certification, IME, text editing, fullscreen, HDR, clipboard, drag-and-drop, gameplay mapping, public ABI/plugin SDK, packaging/release, other modules or packets.

## FILES / SOURCES TO READ

`AGENTS.md`; checkpoint; Ledger/ADRs 0003/0075/0083..0089; Scope/DoD/Architecture/Requirements; CORE-01 architecture and C01-D03/D04; SDL3 runtime/window/event contracts; this gate's ADR/contract/activation; completed CORE-01 code/tests/CMake/CI evidence; SDL3 3.4.20 display/window headers at the pinned commit. Inspect Git before editing.

## REQUIREMENTS

GOV-001..005, CAP-010/014, NFR-002/003/005; C01-D03/D04 bounded; CORE-01 catalog acceptance. No new owner technology decision beyond the authorized SDL3 display adapter and existing CI; no renderer/GPU/public ABI.

## ARCHITECTURE RULES

Internal namespace/header only; SDL hidden in `.cpp`; no SDL type/macro/handle in headers; owner-thread display/surface calls; typed errors; no exception across the boundary; no global state/singleton; caller-owned fixed display storage; no SDL pointer in `DisplayInfo`; surface generations are opaque tokens, not renderer handles. Existing headless/paths/SDL/window/event/memory targets preserved.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`. SDL3 3.4.20 static build-time fetch; no package installation, paid runner, secret, upload, runtime download or release. Standard public CI on `ubuntu-24.04`, `windows-2025-vs2026`, `macos-15`; Linux ASan/UBSan. ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## ACCEPTANCE CRITERIA

- Exact allowlist; fresh Context Lock; selector ready only for `NLE-PRPLAN-CORE-01-10`.
- Display enumeration/primary with typed errors; no SDL pointer/string leak; caller buffer semantics.
- Surface metrics and generation invalidation on resize; stale generation rejected; query errors before create/after destroy/wrong thread.
- DPY-01..DPY-08 on Linux, Linux ASan/UBSan, Windows and macOS; existing 40 CTests regression; no physical hotplug/DPI/renderer/GPU/ABI/release overclaim.
- Docs Validation + native CI PASS at exact PR HEAD; no HIGH/CRITICAL; pt-BR audit; squash/readback.

## TESTS

Docs: `validate_docs.py`, `validate_wo_registry.py`, `validate_pr_plans.py`, unit tests, packet selector. Native: `DPY-01` displays, `DPY-02` primary, `DPY-03` buffer/argument, `DPY-04` runtime/thread, `DPY-05` surface metrics, `DPY-06` resize invalidation, `DPY-07` surface errors, `DPY-08` stability/lifetime/regression; CMake Presets; ASan/UBSan on Linux. Exact commands: `cmake --preset core01-internal-debug`, `cmake --build --preset core01-internal-debug`, `ctest --preset core01-internal-debug --output-on-failure`, plus the asan preset.

## DELIVERABLES

Exactly: `src/stormline/core/internal/display.hpp`, `display.cpp`, additive `window.hpp`/`window.cpp` surface API, `tests/core/display_tests.cpp`, `CMakeLists.txt` (additive), `.github/workflows/core01-internal-headless.yml` (additive CORE-01-10 path filters), `docs/evidence/NLE-PRPLAN-CORE-01-10.md`. GitHub PR, exact CI receipts, Evidence, pt-BR audit, proposed checkpoint. Gate files separate.

## REVIEW FORMAT

Portuguese Brazil: base/head, exact files, contract compliance, DPY matrix, display/surface evidence, resize/stale generation, existing regression, sanitizer, no SDL leak, no physical hotplug/DPI/renderer/GPU/ABI/release overclaim, risk/security. Verdict `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`. Corrections only in the same WO/PR.

## STOP CONDITION

STALE context, gate not merged, selector blocked, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, SDL type in a header, physical hotplug/DPI/renderer/GPU/ABI/release overclaim, another packet/module unlock, or destructive operation. Never bypass G2 or force push.

## CONTEXT LOCK

Gate base `7e42b48f19272498c732d75f2051704f5b82311f`; activation pins the exact ADR/contract/source blobs and SDL3 commit. Executor must recompute fresh raw SHA-256 after the gate merge and stop/rebase on substantive change.

## EVIDENCE BUNDLE

Separate `docs/evidence/NLE-PRPLAN-CORE-01-10.md` with PR/CI/audit/merge SHAs, exact files, display/surface/resize/stale-generation results, DPY-01..08, regression, sanitizer, limitations and rollback. Gate evidence never masquerades as implemented code.
