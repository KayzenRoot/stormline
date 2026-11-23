# NLE-PRPLAN-GFX-03-02 — Logical render graph contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no code authorized.** **Formal packet:** `NLE-PRPLAN-GFX-03-02`. **Predecessor:** `GFX-03-01` governance. **Issue:** #31. **Base:** `2686632`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Contract:** [gfx-03-render-graph-internal-v0](../contracts/gfx-03-render-graph-internal-v0.md).

## OBJECTIVE

Freeze the exact internal GFX-03 API, capacities, errors, deterministic rules, hazard semantics and per-slice allowlists for logical render graph compilation.

## CONTEXT

GFX-03-01 approved ADR-0117. No native GPU, allocator, submission, renderer, dependency, ABI or release is authorized.

## SCOPE

- `docs/contracts/gfx-03-render-graph-internal-v0.md`.
- WO, G6 evidence, activation JSON, manifest/validator/test/checkpoint updates.

## OUT OF SCOPE

Implementation `-03`..`-08`, closeout, native GPU/allocator, submission, rendering, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0016/0117/0086, GFX-03 architecture/API/matrix, GFX-03 governance contract, GFX-01/02 and CORE-03 closeouts.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0117; exact API and DEF/DEP/SYN/TRA/BUD/QLF-G3 oracles.

## ARCHITECTURE RULES

GFX-03 owns logical graph compilation; no native GPU/submission; GFX/CORE/DATA boundaries unchanged.

## CONSTRAINTS

Risk `LOW` contract; `INTERNAL_ONLY`; no GPU/allocator/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract exact and complete; manifest root `GFX03_02_APPROVED_CONTRACT_ONLY`.
- No code, dependency, native GPU/submission or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; future oracles are declared but not executed in this packet.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/allocator selection, incomplete API, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `2686632`; governance merge `2686632`; contract blob pinned after this gate.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-03-02-G6-ACTIVATION.md`.
