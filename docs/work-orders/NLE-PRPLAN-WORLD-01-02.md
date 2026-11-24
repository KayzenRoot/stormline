# NLE-PRPLAN-WORLD-01-02 — Internal entity metadata contract

**STATUS: G6 CONTRACT PACKET — documentation only; no code authorized.** **Formal packet:** `NLE-PRPLAN-WORLD-01-02`. **Issue:** #41. **Base:** `76d89dc`. **Predecessor:** `WORLD-01-01` governance. **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Contract:** [world-01-entity-internal-v0](../contracts/world-01-entity-internal-v0.md).

## OBJECTIVE

Freeze the exact logical API, capacities, error model, test oracles and file allowlists for the internal WORLD-01 implementation slices.

## CONTEXT

WORLD-01-01 is approved. ADR-0026 remains planning-only. No ECS runtime, storage, allocator or serializer exists.

## SCOPE

- Internal contract and this WO.
- Activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## OUT OF SCOPE

Code, tests, CMake, ECS storage, allocator, threading, serialization, persistence, hierarchy, spatial index, physics, networking, editor, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0126/0127, governance contract, WORLD-01 architecture/API research.

## REQUIREMENTS

GOV-001..007; ENT-01/CMP-01/LIF-01/QRY-01/REF-01; QLF-W101..W104 definitions.

## ARCHITECTURE RULES

The contract is header-only logical metadata. DATA-02/04, WORLD-02/03, CORE, SIM/PHYS/GAME/NET retain runtime authority.

## CONSTRAINTS

Risk `LOW` for this documentation gate; `INTERNAL_ONLY`; no code/runtime/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact API names, capacities, errors and allowlists; no implementation.
- ADR-0026 remains `PROPOSED`.
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

Base `76d89dc`; ADR-0127 and governance contract blobs pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-01-02-G6-ACTIVATION.md`.
