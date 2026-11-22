# NLE-PRPLAN-DATA-04-05 — Atomic compatible changes (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-DATA-04-05`. **Predecessor:** `DATA-04-04` document. **Issue:** #27. **Base:** `d024bef5d9140b34d4ec92e4426eb85893ffd80b`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md).

## OBJECTIVE

Implement bounded atomic patches over a scene document: add/remove entity and set-enabled, base-revision fencing, scene match and rollback on failure. No codec, persistence, network or ABI.

## CONTEXT

DATA-04-01..04 are approved/completed. Declarative documents exist. CORE-05/DATA-02 are not qualified.

## SCOPE

- `scene_patch.hpp`.
- `tests/core/data04_patch_tests.cpp`: PATCH-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Diffs/qualification; JSON/CBOR, persistence, migration, native I/O, network, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0012/0086/0113, `data-04-scene-v0`, DATA-04-04 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0113; PATCH-01; atomicity, stale revision, bounded ops.

## ARCHITECTURE RULES

DATA-04 owns patches; CORE-05 typed IDs; DATA-01/02/03 boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no codec/dependency/native I/O/network/persistence; CORE-05/DATA-02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; PATCH-01 add/remove/enable/stale/failure atomicity.
- No codec/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

PATCH-01: successful add/remove/set-enabled and revision bump; stale base; wrong scene; invalid op; failed patch unchanged. Existing suite required.

## DELIVERABLES

Header, PATCH tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, PATCH-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, codec/native I/O, non-atomic failure, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `d024bef5d9140b34d4ec92e4426eb85893ffd80b`; contract blob `99962b6a800d5219db46ce42cf4abb34f6d0ac57`; DATA-04-04 code PR #634 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-04-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-04-05.md`.
