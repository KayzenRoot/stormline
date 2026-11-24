# NLE-PRPLAN-TWO-04-02 — Internal hybrid composition contract

**STATUS: G6 CONTRACT PACKET — documentation only; no code authorized.** **Formal packet:** `NLE-PRPLAN-TWO-04-02`. **Issue:** #40. **Base:** `dfb0953`. **Predecessor:** `TWO-04-01` governance. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md).

## OBJECTIVE

Freeze the exact logical API, capacities, error model, test oracles and file allowlists for the internal TWO-04 implementation slices.

## CONTEXT

TWO-04-01 is approved. ADR-0025 remains planning-only. No runtime renderer, GPU or depth attachment exists.

## SCOPE

- Internal contract and this WO.
- Activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## OUT OF SCOPE

Code, tests, CMake, renderer, GPU, shaders, matrices, lighting, subviews, editor, export, hardware, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0125/0126, governance contract, TWO-04 architecture/API research.

## REQUIREMENTS

GOV-001..007; CAM-01/LAY-01/SRT-01/EFE-01; QLF-T401..T404 definitions.

## ARCHITECTURE RULES

The contract is header-only logical metadata. GFX-03/04/05/06/07, TWO-01, DATA-04 and PHYS/WORLD retain runtime authority.

## CONSTRAINTS

Risk `LOW` for this documentation gate; `INTERNAL_ONLY`; no code/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact API names, capacities, errors and allowlists; no implementation.
- ADR-0025 remains `PROPOSED`.
- docs-validation, SonarCloud and Socket pass; pt-BR audit `APPROVED`.

## TESTS

No executable test in this gate; oracles are frozen for -03..-07.

## DELIVERABLES

Internal contract, WO, activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## REVIEW FORMAT

pt-BR: base/head, API/allowlist review, validator counts, CI, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift after freeze, code introduced, allowlist violation, failed docs validation, HIGH/CRITICAL, runtime/release claim.

## CONTEXT LOCK

Base `dfb0953`; ADR-0126 and governance contract blobs pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-04-02-G6-ACTIVATION.md`.
