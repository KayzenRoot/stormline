# ADR-0094 — CORE-01 integrated CI qualification harness

**Status:** `OWNER_DIRECTION_C01_D09_C01_D14_BOUNDED_QUALIFICATION / TECHNICAL_SLICE_PROPOSED / CONDITIONAL_ON_AUDIT_AND_MERGE`. **Subordinate to ADR-0003/0075, which remain PROPOSED; does not certify physical hardware, release readiness or full CORE-01 completion.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-01-15` | **Parent:** `NLE-PRPLAN-CORE-01-01` | **Issue:** #387 / implementation issue #18.

## Context and authority

C01-D09 requires headless boot/teardown without GPU/display/audio/session, and C01-D14 ratified bounded soak counts. `-03`..`-14` are completed. The next formal packet `-15` is integrated functionality/OS/security/soak qualification.

This slice is a **CI qualification harness** over the completed CORE-01 internal components. It proves integrated init/teardown, component interaction, resource counters and sanitizer-clean execution on hosted runners. It does not prove physical Windows/Linux/macOS hardware, 30 cold + 30 warm timing, 32 scenarios, long-duration soak, OS suspend/resume, Wayland runtime, performance, security clearance, public ABI or release.

## Bounded technical decision

- New test executable `core01_qualification_test` (no production API) that runs:
  - 200 headless host start/stop cycles with resource-acquire/release counters balanced and zero live resources;
  - 10 SDL runtime init/quit cycles, each with a window create/show/resize/surface/native-handle/destroy cycle;
  - 25 additional native window cycles;
  - 10,000 synthetic events through the bounded queue;
  - display enumeration/primary, capability probe, and 50 lifecycle suspend/resume cycles + shutdown;
  - final runtime shutdown and explicit `CORE01_QUALIFICATION_OK` output.
- Linux X11 under Xvfb/openbox; Windows Win32; macOS Cocoa or explicit `NOT_QUALIFIED` if no window server.
- Linux ASan/UBSan runs the same harness; leak detection remains active for our code.
- No timing threshold, FPS/p95/RSS budget, physical-hardware claim, security clearance or release.
- Exact allowlist: `tests/core/core01_qualification_tests.cpp`, additive `CMakeLists.txt`, additive workflow path filters, `docs/evidence/NLE-PRPLAN-CORE-01-15.md`.

## Alternatives rejected

- **Declare full CORE-01 qualified from CI:** rejected; physical hardware, 30+30 timing, 32 scenarios, Wayland runtime and long soak are absent.
- **Reuse only the -14 soak harness:** rejected; -15 must integrate headless/SDL init-quit/event/display/lifecycle and resource-counter checks in one qualification.
- **Add production qualification API:** rejected; the harness uses existing internal APIs only.
- **Treat sanitizer-clean as security clearance:** rejected; ASan/LSan is a defect detector, not a security certification.

## Proof and consequence

- G4/G5 bounded eligibility after gate Docs Validation, pt-BR audit and merge; G6 activation separate.
- Code proof: QUAL-01..QUAL-06 on Linux, Linux ASan/UBSan, Windows and macOS; 67 total CTests; zero live headless resources; `CORE01_QUALIFICATION_OK`.
- CORE-01 remains incomplete: physical hardware, 30+30 timing, 32 scenarios, long-duration soak, Wayland runtime, release/security clearance and `-16` closeout remain blocked/not qualified.
- ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the qualification target/workflow/evidence restores the previous state; no G2, registry or license change is part of this ADR.
