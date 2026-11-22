# NLE-PRPLAN-CORE-05-06 — Explicit units (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-05-06`. **Predecessor:** `CORE-05-05` completed. **Issue:** #22. **Base:** `e2277fd6710c7db4b1c9c1cf709d39f1d3030574`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md).

## OBJECTIVE

Implement explicit meter/centimeter/millimeter, second/millisecond, radian/degree unit tags and `Quantity<T,Unit>`, same-unit arithmetic and named conversions. No precision/origin, IDs, backend conversion, SIMD, third-party math, serialization, ABI or release is authorized.

## CONTEXT

CORE-05-01/02/03/04/05 are approved/completed. ADR-0108 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner instructed continuation on 2026-11-22. This packet activates only `CORE-05-06`.

## SCOPE

- `units.hpp`: tags, `Quantity<T,Unit>`, add/subtract/scale, degrees/radians, centimeters/meters, millimeters/meters, seconds/milliseconds conversions.
- `tests/core/core05_unit_tests.cpp`: MATH-07, typed non-finite/overflow, compile-time mismatch.
- Additive CMake target/tests and TSan target list.
- Evidence file.

## OUT OF SCOPE

`precision.hpp`, `ids.hpp`, world origin, stable IDs, backend conversion, SIMD, third-party math, serialization, public ABI/release, CORE-01 completion, CORE-05-07 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0007/0086/0108, `core-05-math-v0`, CORE-05 architecture, CORE-05-05 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0108; ADR-0086; MATH-07; explicit conversions only; no implicit narrowing.

## ARCHITECTURE RULES

CORE-05 owns unit-bearing values; CORE-04 owns time ticks; SIM/PHYS/GFX/NET/DATA boundaries unchanged. Header-only internal C++20; scalar reference path only; no third-party include or intrinsic.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; `Quantity<T,Unit>` prevents implicit unit mixing; same-unit add/subtract/scale compile.
- MATH-07: 180° = π rad, 100 cm = 1 m, 1000 mm = 1 m, 1 s = 1000 ms, 250 ms = 0.25 s.
- Non-finite conversion → `NonFinite`; overflow → `Overflow`; no implicit f32/f64 narrowing.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

MATH-07 plus `static_assert` unit-type separation and typed conversion failures. Existing full CTest suite remains required.

## DELIVERABLES

`units.hpp`, unit tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, MATH-07, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/intrinsic, precision/ID code, implicit conversion, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `e2277fd6710c7db4b1c9c1cf709d39f1d3030574`; contract blob `e6fb5f8a4f9934848d71be9d535018b0b99531e2`; CORE-05-05 code PR #545 and closeout #546 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-05-06-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-05-06.md` for implementation.
