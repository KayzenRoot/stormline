# NLE-PRPLAN-DATA-02-09 — integrated registry qualification evidence

**Status:** `INTERNAL_CI_QUALIFICATION / NOT_PHYSICAL_OR_RELEASE_QUALIFICATION / NO PERSISTENCE OR ABI CLAIM`. **Base:** `72c130e`. **Gate:** [NLE-PRPLAN-DATA-02-09-G6-ACTIVATION](NLE-PRPLAN-DATA-02-09-G6-ACTIVATION.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md). **WO:** [NLE-PRPLAN-DATA-02-09](../work-orders/NLE-PRPLAN-DATA-02-09.md).

## Scope delivered

- `tests/core/data02_registry_qualification_tests.cpp`: QLF-R01..04.
- Additive CMake target/four tests and workflow TSan target.
- This evidence file.

No production header, API, behavior, persistence, serialization, native I/O, dependency, ABI or release change.

## Qualification results

- **QLF-R01 integrated registry:** identity→path→tag→metadata→dependency→query→reference→rename→impact; tag query selects the expected ID, reference survives rename, impact reports the dependent.
- **QLF-R02 deterministic repeat:** two independent builds yield identical asset/dependency/unresolved counts, query IDs, impact IDs and rename visibility.
- **QLF-R03 failure recovery:** duplicate ID/path, missing rename, self-cycle, invalid tag/key/query, kind mismatch and tombstone-style errors are followed by valid operations.
- **QLF-R04 bounded overload:** 10,000 add attempts stop at 64 assets, 10,000 dependency attempts stop at 128 edges, 10,000 tag attempts stop at 8 per asset, 10,000 9-entry metadata sets return `CapacityFull`, and 10,000 queries keep a stable 64-ID page.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data02_registry_qualification_tests.cpp -o /tmp/data02_qlf
/tmp/data02_qlf qlf01
/tmp/data02_qlf qlf02
/tmp/data02_qlf qlf03
/tmp/data02_qlf qlf04
```

All exited 0. ASan/UBSan rebuild and all four modes exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run. This is qualification of internal logical behavior in CI, not of physical hardware, persistence, database durability, OS sandboxing, performance, ABI or release.

## Errors and corrections

- The initial snapshot used empty tag/metadata spans expecting success; corrected to real bounded arrays. Temporary `AssetRecord` arguments were replaced with locals. No production change.

## Security and architecture

- Test-only change using frozen internal headers; no host path, file, database, network, allocation or dependency.
- No persistence or confinement claim.

## Rollback

Revert normally; remove qualification test and additive CMake/workflow entries. No force push or history rewrite.

## Open risks / not claimed

- No persistence, serialization, SQLite, migration, crash recovery or native filesystem.
- No hardware, soak, performance, ABI or release qualification.
- `DATA-02-10` remains `PLANNED_BLOCKED`.
- CORE-01 not module-qualified; DATA-01 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-02-09` as `COMPLETED`, manifest `DATA02_09_COMPLETED_REST_BLOCKED`: **663 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 69 `COMPLETED`, 16 approved gates**. This is a proposal, not a self-promoted checkpoint.
