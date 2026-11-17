# ADR-0086 — Capability-based L1 dependency admission

**Status:** `OWNER_DIRECTION_RATIFIED_L1_CAPABILITY_BASED / BOUNDED / NOT_GLOBAL_G3_CLEARANCE / CONDITIONAL_ON_AUDIT_AND_MERGE`.

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-02-03` (first and only application) | **Parent:** `NLE-PRPLAN-CORE-02-01` | **Issue:** #387 / implementation issue #19.

## Context and authority

The owner approved **capability-based L1 dependencies** together with a 3-4 PRs per response cadence (`STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments`). The 80-module catalog records `CORE-01` as the formal predecessor of every L1 module, including `CORE-02`. `CORE-01` has completed internal slices `-03`..`-08`, but the module as a whole is not merged or qualified: input/event queue, DPI, IME, hotplug, sleep/resume and qualification remain blocked.

A strict reading of `requires_modules_merged: ["CORE-01"]` would block every L1 module until all CORE-01 packets and product-level qualification close. The owner rejected that serialization in favor of **capability-based admission**: a dependent packet may start when its exact required CORE-01 capabilities are completed and evidenced, without claiming that CORE-01 or the dependent module is complete.

This ADR does **not** approve ADR-0003/0075, clear G3 globally, promote a module release class, change the registry, or unlock any packet other than the one named here.

## Bounded decision

A packet may use capability-based admission only when all of the following hold:

1. The packet keeps its formal module dependency in the manifest and registry; the dependency is not deleted or rewritten.
2. The packet and activation enumerate an exact `capability_admission` object: the ADR, the formal dependency, `module_completion_claimed: false`, the ordered capability IDs, and the completed packet IDs that satisfy each capability.
3. Every satisfying packet is `COMPLETED` with a merged code PR, CI evidence and a closed packet; a documentary, proposed or partially qualified packet cannot satisfy a capability.
4. The packet contract states which capabilities are **not** required and must not use them; the admission is not transitive.
5. The fail-closed validator rejects any extra capability, any unsatisfied or non-completed packet, any module-level promotion, and any second admitted packet.
6. The admission expires when the packet closes. It does not become a module-level waiver or a precedent for another packet.

The formal DAG and `engine_implemented=false` at module/product level remain true. This is one audited packet-scoped exception, not a global G3/G6 bypass.

## First application — `NLE-PRPLAN-CORE-02-03` Ownership

| Capability | Satisfied by completed packet | Why required |
|---|---|---|
| `CORE01_HEADLESS_BUILD_AND_TEST` | `NLE-PRPLAN-CORE-01-03` (PR #428) | CMake/C++20 static library and test-harness baseline |
| `CORE01_PORTABLE_PATHS` | `NLE-PRPLAN-CORE-01-06` (PR #432) | Existing portable internal-source/test conventions and CI regression |
| `CORE01_SDL3_BUILD_BASELINE` | `NLE-PRPLAN-CORE-01-07` (PR #435) | The shared CMake project fetches the pinned SDL3 baseline; CORE-02 does not call SDL |
| `CORE01_NATIVE_CI_MATRIX` | `NLE-PRPLAN-CORE-01-08` (PR #438) | Real Linux/Windows/macOS/ASan matrix used by the ownership tests |

**Not required:** window lifecycle runtime, input/event pump, DPI, IME, hotplug, sleep/resume, soak/qualification, renderer/GPU/audio, network, public ABI/plugin SDK, packaging/release. The ownership slice calls **no SDL API** and links no SDL target.

## Alternatives rejected

- **Wait for the complete CORE-01 module:** rejected by the owner's capability-based L1 direction; it would serialize all L1 work behind input/DPI/soak packets unrelated to ownership.
- **Rewrite the module DAG or mark CORE-01 merged:** rejected; it would falsify module status and `engine_implemented`.
- **Let CORE-02-03 use the window/input capabilities because they happen to exist:** rejected; the slice does not need them, and unused privileges widen the audit surface.
- **Treat this as a permanent or bulk waiver:** rejected; the validator pins one packet and expiry is explicit.

## Proof and consequences

- Gate proof: ADR-0086/0087, ownership contract v0, 13-field WO, activation with live source fingerprints, manifest state, validator negative tests and pt-BR audit.
- Code proof (separate PR): exactly the ownership allowlist, `OWN-01`..`OWN-08`, existing 23 CTests regression, Linux/Windows/macOS and Linux ASan/UBSan.
- No module completion, release, performance or allocator-selection claim is made. ADR-0004 remains `PROPOSED`; NLE-D009 `OPEN`; G3 global `NOT_CLEARED`; 80/80 module WOs remain `BLOCKED`.
- The admission is valid only for `NLE-PRPLAN-CORE-02-03` and expires at closeout. Any other L1 packet requires its own ADR, contract, activation and audit.

## Rollback

Unmerged: close the gate branch; `main` untouched. After merge: normal revert PR, never force push. Reverting the gate and code restores the prior blocked state; no G2, registry, license or release change is part of this ADR.
