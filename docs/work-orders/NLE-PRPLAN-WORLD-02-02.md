# NLE-PRPLAN-WORLD-02-02 — Internal scene/prefab metadata contract

**STATUS: G6 CONTRACT PACKET — documentation only; no code authorized.** **Formal packet:** `NLE-PRPLAN-WORLD-02-02`. **Issue:** #42. **Base:** `4eaebbc`. **Predecessor:** `WORLD-02-01` governance. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Contract:** [world-02-scene-internal-v0](../contracts/world-02-scene-internal-v0.md).

## OBJECTIVE

Freeze the exact logical API, capacities, error model, test oracles and file allowlists for the internal WORLD-02 implementation slices.

## CONTEXT

WORLD-02-01 is approved. ADR-0027 remains planning-only. No scene runtime, prefab expansion or serializer exists.

## SCOPE

- Internal contract and this WO.
- Activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## OUT OF SCOPE

Code, tests, CMake, scene runtime, prefab expansion, override merge, serializer, persistence, journal, transform math, spatial, physics, networking, editor, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0127/0128, governance contract, WORLD-02 architecture/API research.

## REQUIREMENTS

GOV-001..007; HIR-01/PFC-01/VAR-01/INS-01/TRS-01; QLF-S201..S204 definitions.

## ARCHITECTURE RULES

The contract is header-only logical metadata. WORLD-01, DATA-02/04, CORE-05, WORLD-03, SIM/PHYS/GAME/NET retain runtime authority.

## CONSTRAINTS

Risk `LOW` for this documentation gate; `INTERNAL_ONLY`; no code/runtime/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact API names, capacities, errors and allowlists; no implementation.
- ADR-0027 remains `PROPOSED`.
- docs-validation, SonarCloud and Socket pass; pt-BR audit `APPROVED`.

## TESTS

No executable test in this gate; oracles are frozen for -03..-08.

## DELIVERABLES

Internal contract, WO, activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## REVIEW FORMAT

pt-BR: base/head, API/allowlist review, validator counts, CI, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift after freeze, code introduced, allowlist violation, failed docs validation, HIGH/CRITICAL, runtime/release claim.

## CONTEXT LOCK

Base `4eaebbc`; ADR-0128 and governance contract blobs pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-02-02-G6-ACTIVATION.md`.
