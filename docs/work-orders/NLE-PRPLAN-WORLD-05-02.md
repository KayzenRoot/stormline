# NLE-PRPLAN-WORLD-05-02 — Procedural generation internal contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-05-02`. **Predecessor:** `WORLD-05-01` governance. **Issue:** #45. **Base:** `6e4bd10`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Contract:** [world-05-procedural-internal-v0](../contracts/world-05-procedural-internal-v0.md).

## OBJECTIVE

Freeze the exact header-only logical API, capacities, error model, test oracles and per-slice allowlists for WORLD-05 implementation.

## CONTEXT

WORLD-05-01 governance is approved. ADR-0030 remains `PROPOSED`; no generator, evaluator or artifact exists.

## SCOPE

- `docs/contracts/world-05-procedural-internal-v0.md`.
- WO, G6 evidence, activation JSON, checkpoint line and manifest/validator wiring.
- No code.

## OUT OF SCOPE

All implementation slices `-03`..`-09`; graph evaluation, RNG/noise, WFC, asset I/O, cook/cache, source writes, mesh generation, GPU preview, physics, networking, editor, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0131, governance contract, WORLD-05 architecture/API/plan.

## REQUIREMENTS

GOV-001..007; ADR-0131; SEED-01, GRAPH-01, RULE-01, BIOME-01, GEO-01, GEN-01, QLF-W501..W504.

## ARCHITECTURE RULES

Header-only metadata under `src/stormline/procedural/`; no runtime owner is duplicated and no generation execution is introduced.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; ADR-0030 remains PROPOSED; no engine code/runtime/evaluation/GPU/assets/physics/network/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact contract; no code.
- Fixed capacities, typed errors, deterministic oracles and exact allowlists per slice.
- Validators pass; pt-BR audit `APPROVED`.

## TESTS

Validator suite, docs validation and manifest counts only; implementation tests are defined for later gates.

## DELIVERABLES

Frozen contract, WO, evidence, activation JSON, checkpoint and validator wiring, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, contract exactness, validators/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift beyond governance, runtime scope expansion, allowlist violation, validator failure, HIGH/CRITICAL or release/ABI claim.

## CONTEXT LOCK

Base `6e4bd10`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-05-02-G6-ACTIVATION.md`.
