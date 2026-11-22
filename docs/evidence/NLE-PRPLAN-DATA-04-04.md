# NLE-PRPLAN-DATA-04-04 — declarative document evidence

**Status:** `IMPLEMENTATION EVIDENCE / INTERNAL_ONLY / NO CODEC OR ABI CLAIM`. **Base:** `327122f`. **Gate:** [NLE-PRPLAN-DATA-04-04-G6-ACTIVATION](NLE-PRPLAN-DATA-04-04-G6-ACTIVATION.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md). **WO:** [NLE-PRPLAN-DATA-04-04](../work-orders/NLE-PRPLAN-DATA-04-04.md).

## Scope delivered

- `src/stormline/data/scene/scene_document.hpp`: `SceneDocument`, entity/component/asset-ref methods, remove/set-enabled/revision helpers.
- `tests/core/data04_document_tests.cpp`: DOC-01.
- Additive CMake/workflow entries.

No patch, diff, codec, persistence, native I/O, network, ABI or release.

## Implementation notes

- Init requires valid scene/project/schema and sets revision 1.
- Entity names 1..32 printable ASCII excluding `/`, `:`, backslash and control; duplicate IDs, missing parents and self-parent cycles are typed.
- Components require existing entity and nonzero type/version; asset refs require valid DATA-02 AssetId and entity; duplicate asset+role is rejected.
- Remove cascades components and refs; capacity 64/128/64 is fixed.

## Commands and results

WSL Ubuntu 24.04 GCC 13.3.0:

```text
g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/core/data04_document_tests.cpp -o /tmp/data04_doc
/tmp/data04_doc doc01
```

Exited 0. ASan/UBSan rebuild exited 0.

Native CI is executed by the PR workflow; no result is claimed before the exact-head run.

## Errors and corrections

- A generated test contained a non-ASCII comparison token; corrected to `==`. No production change.

## Security and architecture

- Header-only internal C++20; fixed arrays, no allocation, codec, file, database or network.

## Rollback

Revert normally; remove the document header/test and additive CMake/workflow entries.

## Open risks / not claimed

- No patch/diff yet; no JSON/CBOR/persistence/native I/O.
- `DATA-04-05`..`-08` remain `PLANNED_BLOCKED`.
- CORE-05/DATA-02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## Proposed checkpoint delta

After merge, record `DATA-04-04` as `COMPLETED`, manifest `DATA04_04_COMPLETED_REST_BLOCKED`: **648 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 80 `COMPLETED`, 20 approved gates**.
