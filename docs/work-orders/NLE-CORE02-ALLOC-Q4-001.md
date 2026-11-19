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

`docs/evidence/NLE-CORE02-ALLOC-Q4-001.md` plus `docs/evidence/NLE-CORE02-ALLOC-Q4-raw.log`.
