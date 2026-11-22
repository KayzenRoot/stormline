# NLE-PRPLAN-CORE-05-09 — Integrated internal qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — code authorized only after this gate merges.** **Gate:** G6 qualification + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-05-09`. **Predecessor:** `CORE-05-08` completed. **Issue:** #22. **Base:** `5553af9434fdc86fde801a727432fc54d692cefc`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md).

## OBJECTIVE

Add an integrated internal qualification test over the completed CORE-05 headers: vectors, matrices, quaternions, coordinate spaces, units, precision/origin and IDs together. Exercise MATH-12-style repeatability and typed failure recovery. No production API, hardware, SIMD, serialization, ABI or release is authorized.

## CONTEXT

CORE-05-01..08 are approved/completed. ADR-0108 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner instructed continuation on 2026-11-22. This packet activates only the test/qualification slice.

## SCOPE

- `tests/core/core05_qualification_tests.cpp`: integrated transform/unit/precision/ID workflow, repeated-run consistency, typed-error recovery and bounded coordinate fixtures.
- Additive CMake target/CTest entries and workflow TSan target list.
- Evidence file.
- No production source change.

## OUT OF SCOPE

New math API, third-party math, SIMD, serialization, backend clip/projection, physics/GFX/WORLD/NET/DATA integration, public ABI/release, CORE-01 completion, CORE-05-10 or hardware qualification.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0007/0086/0108, `core-05-math-v0`, all CORE-05 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0108; ADR-0086; MATH-01..MATH-11 integrated; MATH-12 repeatability envelope; no bit-exact cross-compiler claim.

## ARCHITECTURE RULES

CORE-05 owns math values; CORE-01/02/03/04 and GFX/SIM/DATA/WORLD/NET boundaries unchanged. Test-only header include; scalar reference path; no third-party include, intrinsic or production edit.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; test builds against all CORE-05 headers.
- QLF-01 integrated workflow: vector → quaternion/matrix transform → coordinate spaces → units → world/local origin → stable IDs.
- QLF-02 repeated runs produce identical scalar fixtures; no nondeterministic global state.
- QLF-03 invalid input returns typed errors and a subsequent valid operation succeeds.
- QLF-04 bounded large-coordinate/rebase fixture passes within documented budget.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no production/dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

QLF-01..04 integrated qualification; existing full CTest suite remains required. The result is internal qualification only, not hardware/OS/soak/performance qualification.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-01..04, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, production API/code change, third-party/intrinsic, hardware/ABI/release claim, allowlist violation, failed test, HIGH/CRITICAL. Stop and report.

## CONTEXT LOCK

Base `5553af9434fdc86fde801a727432fc54d692cefc`; contract blob `e6fb5f8a4f9934848d71be9d535018b0b99531e2`; CORE-05-08 code PR #554 and closeout #555 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-05-09-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-05-09.md` for qualification results.
