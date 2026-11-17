# NLE-PRPLAN-CORE-01-06 — G6 activation and predecessor reconciliation

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `b3638de6c6918e36b49726af63abeb09bd35f140`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-06`. **Contract:** [core-01-process-paths-v0](../contracts/core-01-process-paths-v0.md). **WO:** [NLE-PRPLAN-CORE-01-06](../work-orders/NLE-PRPLAN-CORE-01-06.md).

## Owner authorization and scope

The owner expressly authorized continuing real CORE-01 construction on 2026-11-17 (`STORM-CORE-01-IMPL-001`), limited to the next NECESSARY increment, with code first and only the minimal governance needed to activate it. This gate authorizes **only** `NLE-PRPLAN-CORE-01-03` remains COMPLETED, `-04`/`-05` are reconciled, and `-06` becomes the single ready packet **after** this PR passes exact-head Docs Validation, objective pt-BR audit and squash/readback. It does not approve ADR-0003/0075 globally, G3, NLE-D009, another packet or module, or a public ABI.

## Predecessor reconciliation — `-04` and `-05` are objectively covered by `-03`

This is not a scope-similarity claim. The merged `-03` code and tests are the implementation of both predecessor acceptances; no new code is required, and neither packet is re-executed.

| Packet | Acceptance | Objective evidence in the merged `-03` slice |
|---|---|---|
| `-04` Typed HostConfig, states and errors | Reject wrong transitions and duplicate init without side effects | `headless_host.hpp` defines `HostConfig`, `HostState`, `HostError`; `headless_host.cpp` rejects `Running`→`AlreadyRunning`, `Failed`/transient→`InvalidState`, `Stopped` stop idempotent, `headless=false`→`UnsupportedMode` with no lease; tests `run_lifecycle`, `run_errors`, `run_invalid`; CI run `44133192612` 5/5 on Linux/Windows/macOS + ASan/UBSan |
| `-05` Partial init teardown and resource ownership | Injected faults leave no leaked resources on repeated start/stop | `headless_host.cpp` injects failure after stages 1–3, rolls back exactly once, retains leases on cleanup failure, retries to `Stopped`, no double release, destructor force-cleans `Running`/`Failed`; tests `run_errors`, `run_cleanup`, `run_destructor`, `run_lifecycle` (600 acquire/release); ASan/UBSan 5/5 |

Both packets are recorded `COMPLETED` with `github_pr=428` and the bounded `INTERNAL_ONLY` metadata. This reconciliation is the minimum governance action needed to respect the formal dependency chain; it does not claim a new implementation or a new test run.

## `-06` bounded technical scope

Read-only internal process-path queries: current working directory, system temporary directory, absolute normalization, containment inside an explicit root, and validated UTF-8 representation. Exact API, error enum, semantics, Unicode policy, no-write guarantee, symlink/traversal rules and PATH-01..PATH-12 oracles are in the [contract](../contracts/core-01-process-paths-v0.md).

- Risk `STANDARD`, release `INTERNAL_ONLY`, C++20 standard library, no new dependency.
- No VFS, file creation/write/delete/rename, permission changes, logging/telemetry/network, SDL3/window/GPU/audio, public ABI or next module.
- Exact code allowlist: `src/stormline/core/internal/process_paths.hpp`, `process_paths.cpp`, `tests/core/process_paths_tests.cpp`, additive `CMakeLists.txt`, `docs/evidence/NLE-PRPLAN-CORE-01-06.md`.

## Gate state after merge (expected, not yet promoted)

- Manifest root: `CORE01_06_READY_PREDECESSORS_RECONCILED`.
- `-01`/`-02` approved documentary/contract; `-03`/`-04`/`-05` `COMPLETED`; `-06` **the only** `EXECUTOR_READY`; remaining 742 packets `PLANNED_BLOCKED`; 80 module WOs still `BLOCKED`.
- `select_packet.py NLE-PRPLAN-CORE-01-06` → exit 0 after merge; every other ID, including `-03`/`-04`/`-05`, exits 2.
- Activation file pins exact owner authorization reference, contract/WO/evidence, risk/release class, ADR-0083 and live source blobs (checkpoint, Ledger, Scope, DoD, ADR-0083, both contracts). The validator verifies actual Git blob SHA-1s, not only declared constants.
- `-03` activation file remains historical; it is not reused to authorize `-06`.

## Proof obligations for the future code PR

PATH-01..PATH-12 from the contract, exact native CI on Linux/Windows/macOS, existing 5 headless CTests regression, warnings-as-errors, Linux ASan/UBSan when supported, no unexpected writes, no exception escape, no HIGH/CRITICAL, objective pt-BR audit and squash/readback. Real POSIX ACL denial is attempted; Windows real ACL denial is environment-dependent and must be `NOT_QUALIFIED` if not reproducible, never a false PASS. No code or native PASS is claimed by this gate.

## Security, cost, rollback

No secret, paid runner, upload, install, workflow permission change or G2 ruleset change. Standard public runners only, R$0. If unmerged, close the gate branch; no main change. After future merge, normal revert PR only, never force push. ADR-0003/0075 stay `PROPOSED`; ADR-0083 stays bounded; NLE-D009 `OPEN`; G3 global `NOT_CLEARED`; `engine_implemented=false` at module/product level; no next packet.
