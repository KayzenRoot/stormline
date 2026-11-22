# NLE-PRPLAN-CORE-05-08 — Stable IDs and runtime handles (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-05-08`. **Predecessor:** `CORE-05-07` completed. **Issue:** #22. **Base:** `4fea483465cdbc54aec7a3ba52533842236c6a33`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md).

## OBJECTIVE

Implement opaque 128-bit `PersistentId`, `RuntimeHandle{index, generation}`, validity, generation matching, big-endian ID encode/decode and typed invalid-ID failure. No world ECS, asset pipeline, serialization format, public ABI or release is authorized.

## CONTEXT

CORE-05-01..07 are approved/completed. ADR-0108 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner instructed continuation on 2026-11-22. This packet activates only `CORE-05-08`.

## SCOPE

- `ids.hpp`: `PersistentId`, `RuntimeHandle`, `IdBytes`, validity, `handle_is_current`, encode/decode.
- `tests/core/core05_id_tests.cpp`: MATH-10/MATH-11, zero-ID, generation mismatch, recycling and byte fixtures.
- Additive CMake target/tests and TSan target list.
- Evidence file.

## OUT OF SCOPE

WORLD/ECS, asset pipeline, DATA serialization, persistent storage, public ABI/release, CORE-01 completion, CORE-05-09 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0007/0086/0108, `core-05-math-v0`, CORE-05 architecture, CORE-05-07 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0108; ADR-0086; MATH-10/MATH-11; no address/index-as-identity.

## ARCHITECTURE RULES

CORE-05 owns the ID value contracts; WORLD owns ECS lifecycle, DATA owns persistence, NET owns replication. Volatile addresses/indices are never persisted as identity. Header-only internal C++20; no third-party include or intrinsic.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; zero persistent ID and zero index/generation invalid.
- MATH-10: big-endian encode/decode round-trip incl. max values; all-zero decode → `InvalidId`; stable equality.
- MATH-11: generation mismatch/old handle after slot recycling rejected; valid current handle accepted.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

MATH-10/11 plus `static_assert`/byte fixture and typed invalid-ID tests. Existing full CTest suite remains required.

## DELIVERABLES

`ids.hpp`, ID tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, MATH-10/11, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, third-party/intrinsic, ECS/persistence code, pointer identity, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `4fea483465cdbc54aec7a3ba52533842236c6a33`; contract blob `e6fb5f8a4f9934848d71be9d535018b0b99531e2`; CORE-05-07 code PR #551 and closeout #552 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-05-08-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-CORE-05-08.md` for implementation.
