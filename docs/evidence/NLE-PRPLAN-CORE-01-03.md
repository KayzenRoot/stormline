# NLE-PRPLAN-CORE-01-03 — First real internal CORE-01 C++20 Evidence Bundle (IN PROGRESS)

**Base main:** `50b3775d02047a9c3480cc1a2ff7585d8ea056d3` | **Work Order:** `NLE-PRPLAN-CORE-01-03` | **Issue:** #18.
**G6:** [PR #426](https://github.com/KayzenRoot/stormline/pull/426) and checkpoint [#427](https://github.com/KayzenRoot/stormline/pull/427) merged. Only this implementation packet individually EXECUTOR_READY. The 80 original broad module WOs remain BLOCKED, 745 other planned packets BLOCKED, two documentary/contract prerequisites complete. G3 global NOT_CLEARED, ADR-0003/0075 PROPOSED, ADR-0083 scoped only, NLE-D009 OPEN.

## Exact tested-source baseline SHA-256 (verified content at BASE, no canonical mutation)
| Canonical source | SHA-256 |
|---|---|
| Checkpoint | `9eb7d26856712ffdfc35e97d820d2ae0b8633631b7b2880fc7ee7ac45e56bff1` |
| Decisions Ledger | `420220915e0600bb84167106d3384b28e27cd2f4375c1e16ccb8374d701e216c` |
| Scope | `39ad13b45738516904b767a8997551cccce2a9ff8ea8642c152bb815fa67c0c7` |
| DoD | `7fc04cc33aad22197b68bcda43fbd356726f11e401cf0e2b68c97f685b12778e` |
| Architecture | `be7f687c7f6db2154536c92426f9c4fd469bb92c3f4896476831437bdaad5930` |
| Requirements | `6e19ad35c7e08f54756eff6372a57def673fd6da9166d91da29770196db3fed0` |
| ADR-0083 | `c484fb10aec5a4b61919967b9026494484f6ae11461f90b94cb1e38fdbdc99a9` |
| Headless contract | `b4457feaf74379b5ffd3f8e744727a48cc7673383cd5c259073b495dfd10f38b` |
| G6 activation | `d82745800ebd7a935ab6ba88a42410d7ae0363964619cf03ad44f0b2d96b498a` |
| PR manifest | `d73dabb5b9759d0bc3aac736c3cd1ba9aeaa49e0f72c2e556c0c1a7303d85c4b` |
| NLE-PRPLAN-CORE-01-03 WO at base | `4c8577044ad01469843b6a5186e4c67db1c2147d9f28770e197f65592bc16623` |
| Original 80 module registry | `2e1d594a8e4bf28c51a1cc5c9672434f78a52485e69a04dc0a97ba5f2ee7a9c2` |

Digests are computed from exact UTF-8 fetched at BASE using a SHA-256 implementation self-tested against the official SHA-256 `abc` vector. Git blob SHA-1 are not substituted for raw SHA-256.

## Implemented scope (test results pending)
Original internal C++20 typed HostConfig/HostState/HostError/HeadlessHost, RAII leases and no-throw destructor, partial init/cleanup injection and retry; CMake Presets and clean CTest, Windows/Linux/macOS + Linux sanitizer workflow. No SDL3, OS native handles, UI/window/GPU/audio/network, SDK public ABI, third-party library or distribution.

## Future proof and receipts
Required: 200 cycles per OS, duplicate start/stop, unsupported-mode rejection, failures stages 1..3, rollback and retry, destructor cleanup; compile warnings as errors, Linux sanitizer, exact PR head Docs Validation and native build/CTest logs, no zero-test. **NOT YET EXECUTED ON CODE PR** at initial evidence commit.

## Security, legal, cost, rollback
STANDARD risk limited to first internal slice; PR-only branch guard, pinned checkout with no persisted credentials, contents:read, standard public runners only, no toolchain install, artifact upload, cache, new secrets or paid services. Billing-specific charge verification unavailable; R$0 is policy and expected use of standard runners, not a verified invoice. NLE-D009 engine license OPEN; do not package/distribute. Rollback: unmerged branch close or later normal revert PR, no force push.

## Review and checkpoint delta PROPOSED
Audit pt-BR against Scope/DoD/Architecture, acceptance C01-INT-01..10, actual tests, sanitizer, regressions, no HIGH/CRITICAL and source integrity. Checkpoint proposal can record first INTERNAL_ONLY source after proven native CI/audit/merge; never imply full engine, G3/global ADR approval or next packet unlocked. Keep Draft until evidence verified.

## Real CI run on code PR #429: initial tested head b9637b7 (2026-11-17)

**Docs Validation:** [run #44132870459](https://github.com/KayzenRoot/stormline/actions/runs/44132870459), `docs-validation` completed/success for initial source HEAD.

**Native and sanitizer CI:** [run #44132870268](https://github.com/KayzenRoot/stormline/actions/runs/44132870268), all 4 jobs completed/success at initial source HEAD, with compiled/linked genuine `src/stormline/core/internal` code and one registered CTest in each job:

| Platform / job | Image and toolchain observed | Test |
|---|---|---|
| [Windows #134214413743](https://github.com/KayzenRoot/stormline/actions/runs/44132870268/job/134214413743) | image `20261103.298.1`, MSVC toolset `14.51.36231`, `cl.exe 19.51.36260.0`, CMake `4.4.5`, Ninja preinstalled | **1/1 CTest PASS**, warnings as errors |
| [Ubuntu #134214414084](https://github.com/KayzenRoot/stormline/actions/runs/44132870268/job/134214414084) | image `20261111.370.1`, GCC `13.3.0`, CMake `3.31.6`, Ninja preinstalled | **1/1 CTest PASS** |
| [macOS #134214414059](https://github.com/KayzenRoot/stormline/actions/runs/44132870268/job/134214414059) | image `20261104.0514.1`, AppleClang `17.0.0.17000013`, CMake `4.4.5` | **1/1 CTest PASS** |
| [Linux ASan+UBSan #134214414038](https://github.com/KayzenRoot/stormline/actions/runs/44132870268/job/134214414038) | GCC `13.3.0`, sanitized preset `STORMLINE_ENABLE_SANITIZERS=ON` | **1/1 CTest PASS**, zero sanitizer errors reported in job |

The one CTest executable on each OS runs 200 full start/stop loops (400 acquired/400 released simulated internal leases), duplicate start and idempotent stop, non-headless rejection, three controlled partial init failures with rollback/recovery, injected cleanup failures, failed state and recovery, destructor RAII cleanup. This verifies only an internal resource model, **not** OS-level handles, real GPU/display/audio independence, leak-free general runtime or product ABI.

**Audit boundaries:** Windows/MSVC14.51 and Linux/GCC13.3 are provisional internal CI as owner ratified, **not** qualified global G3 candidates MSVC14.50/14.52, SDK10.0.26100.9457, GCC16.2/Clang23.1.5. SDL3 absent. Global G3 NOT_CLEARED; ADR-0003/0075 PROPOSED; license NLE-D009 OPEN; 80 module WOs BLOCKED; 745 other planned packets BLOCKED.

**Receipt revision note:** this append changes only the Evidence Markdown, so the final PR HEAD differs from the initial tested source HEAD. The final exact-HEAD Docs Validation and native jobs MUST be rerun and audited. Do not mark final HEAD APPROVED until confirmed.
