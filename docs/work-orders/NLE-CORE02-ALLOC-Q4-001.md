# NLE-CORE02-ALLOC-Q4-001 — Physical Q4 qualification attempt

**STATUS: BLOCKED FOR FULL Q4 MATRIX / PARTIAL WINDOWS PHYSICAL-INFERRED EVIDENCE / NO ALLOCATOR SELECTION.** **Base:** `28b6105cb0d194e6dee81910e744093bb843324d`. **Parent WO:** [NLE-CORE02-ALLOC-001](NLE-CORE02-ALLOC-001.md). **ADR:** [ADR-0104](../adr/0104-core-02-allocator-benchmark.md). **Ratification:** Q1=A, Q2=B, Q3=A, Q4=B, Q7=A (2026-11-19). **Issue:** #19.

## OBJECTIVE

Attempt the physical Q4 matrix for the approved CORE-02 allocator harness on genuinely available hosts, recording real hardware/OS/compiler evidence without selecting an allocator or changing production behavior.

## CONTEXT

The harness and CI report-only baseline are merged (`#495`, `#496`). Q4 requires Windows 11 x64, Ubuntu 24.04 x64 and macOS 15 arm64, with 2 vCPU/4 GiB and 4 vCPU/8 GiB profiles. The owner authorized only this physical qualification stage.

## SCOPE

- Source Check and host inventory.
- Available-host execution of the existing harness (no production code change).
- Windows 11 physical-inferred host: actual host, plus 2-CPU and 4-CPU affinity-constrained profiles.
- Evidence Bundle with coverage matrix, commands, hashes, results, stability, gaps and BLOCKED status.
- Independent checkpoint/readback if evidence is merged.

## OUT OF SCOPE

Allocator selection/default/integration, thresholds/ranking/winner, code changes beyond this WO, Linux/macOS virtualization presented as physical, CORE-03, manifest/registry changes, ADR ratification, release/license.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0004/0104, Q1/Q2/Q3/Q4/Q7 ratification, allocator benchmark WO/contract/evidence, G1-M04/M05, DoD, host inventory, merged harness source.

## REQUIREMENTS

Q4=B; Q3=A; Q7=A; no physical claim without receipts; no allocator selection; no production change; no registry/manifest change.

## ARCHITECTURE RULES

Use the merged harness unchanged; explicit allocator APIs; no override; baseline remains default; no third-party type in engine API.

## CONSTRAINTS

Only available hosts; no external host access assumed; no software installation on external hosts; no paid service; no virtualization presented as physical; no threshold/winner.

## ACCEPTANCE CRITERIA

- Source Check and host inventory documented.
- Matrix marks every required OS/profile as PASS, PARTIAL or BLOCKED with reason.
- Windows runs include CPU/RAM/OS/compiler, executable SHA256, exact commands, 3 repetitions, correctness/exit and report-only values.
- Linux/macOS rows BLOCKED if no physical hosts.
- Exact 2 vCPU/4 GiB and 4 vCPU/8 GiB machines distinguished from affinity-constrained reproduction.
- No allocator selected; CORE-02 remains NOT_QUALIFIED.

## TESTS

Windows harness `correctness`/`full` three times per available profile; no thresholds; report-only timing. No tests executed on unavailable hosts.

## DELIVERABLES

This WO, Evidence Bundle, raw log, coverage matrix and checkpoint/readback (separate PR). No code, manifest or registry change.

## REVIEW FORMAT

pt-BR: Source Check, host authenticity caveat, matrix coverage, commands/hashes, results/stability, gaps, BLOCKED status, no overclaim.

## STOP CONDITION

STOP/BLOCKED if any required OS or exact profile host is unavailable, physical status cannot be honestly established, access/installation permission is missing, or evidence would be incomplete. Do not substitute CI or virtualization for physical evidence.

## CONTEXT LOCK

Base `28b6105…`; merged harness `#495`; no uncommitted source changes.

## EVIDENCE BUNDLE

`docs/evidence/NLE-CORE02-ALLOC-Q4-001.md` plus `docs/evidence/NLE-CORE02-ALLOC-Q4-raw.txt`.

## CORRECTION DELTA CD-01 — fail-closed, affinity and provenance

**Base:** `0fc1733781a3658df54bb429b7439bf1d4fda172`. **Audit:** PR #497 comment #7015868526. **Status:** correction only; Q4 remains BLOCKED.

- CD-01: `run_physical_profile.ps1` validates exit code, stderr, exact markers, result count and completed runs; any failure exits non-zero. Negative tests cover exit≠0, missing `ALLOC_BENCH_OK`, missing `ALLOC_BENCH_CORRECTNESS=PASS`, short results, invalid CPU/runs and missing executable.
- CD-02: affinity is applied after `Process.Start` and the effective mask is read back; measurements are labeled `affinity_coverage=post_start_readback` and classified as approximations, not affinity-from-start proof.
- CD-03: historical raw output is preserved byte-for-byte; old/new helper and log hashes are recorded. The original temporary helper that emitted `peak_working_set_mib=0` is not reconstructable; that field is not a memory measurement. No historical result was rewritten.
- Deliverables: modified helper, test script, fake negative fixture, CMake test wiring and `docs/evidence/NLE-CORE02-ALLOC-Q4-001-CD-01.md`. No allocator default, manifest, registry, G3, license, release or CORE-03 change.

## CONSTRAINED-PROFILE CAMPAIGN CD-02 — owner-ratified Q4 option B

**Base:** `6de186a64cebbdbc14026d24d04ceb7f6cbae7b2`. **Ratification:** NLE-D021 / ADR-0106 (2026-11-21). **Scope:** Windows-only launcher and campaign; Ubuntu/macOS remain BLOCKED.

- `benchmarks/core02/q4_profile_runner.cpp`: suspended process, Job Object `ProcessMemoryLimit` + kill-on-close, affinity before resume, mask/limit readback, fail-closed markers/exit/run count, `CONSTRAINED_PROFILE_NOT_EXACT_HARDWARE` labeling through `affinity_coverage=before_resume`.
- Tests: `test_q4_profile_runner.ps1` with 9 cases (success, exit 7, missing OK/correctness, short results, invalid CPU/memory/runs, missing exe); Windows CTest.
- Campaign: Windows 11 x64 host, 2 CPUs/4 GiB and 4 CPUs/8 GiB constrained profiles, 3 runs each, report-only.
- Evidence: `docs/evidence/NLE-CORE02-ALLOC-Q4-CONSTRAINED-001.md` + raw output.
- No exact hardware, no Ubuntu/macOS physical, no allocator selection/threshold/ranking, no production integration; full Q4 remains BLOCKED.
