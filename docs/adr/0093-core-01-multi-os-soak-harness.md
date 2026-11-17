# ADR-0093 — CORE-01 multi-OS soak harness

**Status:** `OWNER_DIRECTION_C01_D14_BOUNDED_QUALIFICATION / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **Subordinate to ADR-0003/0075, which remain PROPOSED; does not clear G3 or certify physical hardware.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-01-14` | **Parent:** `NLE-PRPLAN-CORE-01-01` | **Issue:** #387 / implementation issue #18.

## Context and authority

C01-D14 ratified a future protocol with **200 headless cycles, 100 window cycles per OS, 10,000 events, 30 cold + 30 warm samples and 32 future scenarios**, with no PASS/FPS/p99 claim. The `-03`..`-13` slices are completed. The next formal packet `-14` is native multi-OS soak qualification.

Standard hosted runners are not physical hardware certification. This ADR authorizes a **bounded CI soak harness** for the ratified cycle/event counts, with sanitizer and native build coverage; the 30+30 timing samples, 32 scenarios, physical hardware, long-duration soak and performance thresholds remain `NOT_QUALIFIED`.

## Bounded technical decision

- New test executable `core01_soak_test` (no production API) that runs:
  - 200 headless host start/stop cycles;
  - 100 SDL window create/show/resize/query-surface/native-handle/destroy cycles on the native driver;
  - 10,000 synthetic SDL events through the bounded event queue;
  - display enumeration/primary and lifecycle suspend/resume/shutdown transitions;
  - a final shutdown/teardown check.
- Linux uses X11 under Xvfb/openbox; Windows uses the Win32 driver; macOS uses Cocoa or reports `NOT_QUALIFIED` if no window server.
- Linux ASan/UBSan runs the same harness.
- No timing threshold, FPS/p99/RSS budget or physical-hardware claim. The harness exits non-zero on any functional regression.
- Exact code allowlist: `tests/core/core01_soak_tests.cpp`, additive `CMakeLists.txt`, additive workflow path filters, `docs/evidence/NLE-PRPLAN-CORE-01-14.md`.

## Alternatives rejected

- **Claim full C01-D14 qualification from CI:** rejected; no physical hardware, 30+30 timing samples or 32 scenarios are executed.
- **Run only headless cycles:** rejected; C01-D14 explicitly includes window cycles per OS.
- **Add a production soak API:** rejected; this is a qualification harness over existing internal APIs.
- **Use shared-runner timing as a performance result:** rejected; no thresholds/hardware and no performance claim.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: 200/100/10,000 counts on Linux/X11, Win32 and Cocoa; Linux ASan/UBSan; existing 65 CTests regression; teardown/no-leak evidence.
- Physical hardware, 30 cold + 30 warm timing samples, 32 scenarios, long-duration soak, Wayland runtime and performance thresholds remain `NOT_QUALIFIED`.
- ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the soak target/workflow/evidence restores the previous state; no G2, registry or license change is part of this ADR.
