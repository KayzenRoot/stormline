# NLE-PRPLAN-WORLD-02-01 — Internal scene/prefab metadata governance

**STATUS: G6 GOVERNANCE PACKET — documentation only; no code authorized.** **Formal packet:** `NLE-PRPLAN-WORLD-02-01`. **Issue:** #42. **Base:** `711cb9e`. **Module:** WORLD-02 — Scene & Prefab Hierarchy. **Predecessors:** WORLD-01 and DATA-02 completed internal sequences (not qualified). **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Governance contract:** [world-02-governance-v0](../contracts/world-02-governance-v0.md).

## OBJECTIVE

Approve the bounded internal logical scene/prefab metadata sequence and freeze its ownership, risk, release class and oracle names before any API or code is written.

## CONTEXT

WORLD-01 and DATA-02 completed their internal sequences. ADR-0027 remains planning-only; no scene runtime is authorized or qualified. WORLD-02 must not duplicate DATA/WORLD/CORE authorities.

## SCOPE

- ADR-0128, internal architecture, governance contract and this WO.
- Activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## OUT OF SCOPE

Contract/API freeze, code, tests, scene runtime, prefab expansion, override merge, serializer, persistence, journal, transform math, spatial, physics, networking, editor, GPU, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0027, WORLD-02 architecture/API research, module catalog, WORLD-01 and DATA-02 closeout evidence.

## REQUIREMENTS

GOV-001..007; ADR-0128; HIR-01/PFC-01/VAR-01/INS-01/TRS-01 definitions.

## ARCHITECTURE RULES

WORLD-02 owns logical graph/prefab/override/instance/transform intent only. DATA-02/04, WORLD-01/03, CORE-05, PHYS and GAME retain their authorities.

## CONSTRAINTS

Risk `LOW` for this documentation gate; future implementation risk `ELEVATED`. `INTERNAL_ONLY`; no runtime/storage/serialization/threading/network/hardware; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact documentation allowlist and 13-field WO.
- No API/code/tests; ADR-0027 remains `PROPOSED`.
- docs-validation, SonarCloud and Socket pass; pt-BR audit `APPROVED`.

## TESTS

Documentation validation only; no executable test is introduced by this gate.

## DELIVERABLES

ADR-0128, internal architecture, governance contract, WO, activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## REVIEW FORMAT

pt-BR: base/head, files, scope boundaries, validator counts, CI, security/rollback, no overclaim.

## STOP CONDITION

Stale base, missing owner authorization, API/code introduced, ADR-0027 overwritten, allowlist violation, failed docs validation, HIGH/CRITICAL, runtime/storage/release claim.

## CONTEXT LOCK

Base `711cb9e`; ADR-0027 and WORLD-02 research blobs pinned in the activation record.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-02-01-G6-ACTIVATION.md`.
