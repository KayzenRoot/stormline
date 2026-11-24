# NLE-PRPLAN-TWO-03-02 — Animation internal contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no code authorized.** **Formal packet:** `NLE-PRPLAN-TWO-03-02`. **Predecessor:** `TWO-03-01` governance. **Issue:** #39. **Base:** `c534bbc`. **ADR:** [ADR-0125](../adr/0125-two-03-internal-animation-pipeline.md). **Contract:** [two-03-animation-internal-v0](../contracts/two-03-animation-internal-v0.md).

## OBJECTIVE

Freeze the exact internal TWO-03 API, capacities, time rules, deterministic fallbacks, errors and per-slice allowlists for flipbooks, bones, blend, cutscenes and timelines.

## CONTEXT

TWO-03-01 approved ADR-0125. No runtime, pose evaluation, skinning, audio, export, importer, dependency, ABI or release is authorized.

## SCOPE

- `docs/contracts/two-03-animation-internal-v0.md`.
- WO, G6 evidence, activation JSON, manifest/validator/test/checkpoint updates.

## OUT OF SCOPE

Implementation `-03`..`-08`, closeout, runtime/pose/skinning, audio, export, importer, assets, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0024/0086/0125, TWO-03 architecture/API, governance contract, TWO-02 closeout.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0125; exact API and FLB/BON/BLD/SEQ/TML/QLF-T3 oracles.

## ARCHITECTURE RULES

TWO-03 owns logical animation plans only; TWO-01, DATA, AUDIO, GFX and WORLD boundaries unchanged; no runtime, audio or encoder.

## CONSTRAINTS

Risk `LOW` contract; `INTERNAL_ONLY`; no runtime/audio/export/importer/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract exact and complete; manifest root `TWO03_02_APPROVED_CONTRACT_ONLY`.
- No code, dependency, runtime/audio/export or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; future oracles are declared but not executed.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, runtime/audio/export/importer selection, incomplete API, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `c534bbc`; governance merge `c534bbc`; contract blob pinned after this gate.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-03-02-G6-ACTIVATION.md`.
