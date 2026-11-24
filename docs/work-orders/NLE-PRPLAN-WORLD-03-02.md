# NLE-PRPLAN-WORLD-03-02 — Internal spatial/streaming metadata contract

**STATUS: G6 CONTRACT PACKET — documentation only; no code authorized.** **Formal packet:** `NLE-PRPLAN-WORLD-03-02`. **Issue:** #43. **Base:** `ac9e864`. **Predecessor:** `WORLD-03-01` governance. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md).

## OBJECTIVE

Freeze the exact logical API, capacities, error model, test oracles and file allowlists for the internal WORLD-03 implementation slices.

## CONTEXT

WORLD-03-01 is approved. ADR-0028 remains planning-only. No streaming runtime, I/O, async task or spatial index exists.

## SCOPE

- Internal contract and this WO.
- Activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## OUT OF SCOPE

Code, tests, CMake, async tasks, I/O/decode/cache, origin rebase, spatial queries, physics/network coordination, renderer, editor, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0128/0129, governance contract, WORLD-03 architecture/API research.

## REQUIREMENTS

GOV-001..007; CEL-01/INT-01/ORG-01/STR-01; QLF-W301..W304 definitions.

## ARCHITECTURE RULES

The contract is header-only logical metadata. DATA-05, CORE, WORLD-01/02, PHYS/AI/GAME/NET retain runtime authority.

## CONSTRAINTS

Risk `LOW` for this documentation gate; `INTERNAL_ONLY`; no code/runtime/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact API names, capacities, errors and allowlists; no implementation.
- ADR-0028 remains `PROPOSED`.
- docs-validation, SonarCloud and Socket pass; pt-BR audit `APPROVED`.

## TESTS

No executable test in this gate; oracles are frozen for -03..-07.

## DELIVERABLES

Internal contract, WO, activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## REVIEW FORMAT

pt-BR: base/head, API/allowlist review, validator counts, CI, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift after freeze, code introduced, allowlist violation, failed docs validation, HIGH/CRITICAL, runtime/I/O/release claim.

## CONTEXT LOCK

Base `ac9e864`; ADR-0129 and governance contract blobs pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-03-02-G6-ACTIVATION.md`.
