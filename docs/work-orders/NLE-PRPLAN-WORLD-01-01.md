# NLE-PRPLAN-WORLD-01-01 — Internal entity metadata governance

**STATUS: G6 GOVERNANCE PACKET — documentation only; no code authorized.** **Formal packet:** `NLE-PRPLAN-WORLD-01-01`. **Issue:** #41. **Base:** `40aeb6e`. **Module:** WORLD-01 — Entity Component Model. **Predecessors:** CORE-05 and DATA-04 completed internal sequences (not qualified). **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Governance contract:** [world-01-governance-v0](../contracts/world-01-governance-v0.md).

## OBJECTIVE

Approve the bounded internal logical entity/component metadata sequence and freeze its ownership, risk, release class and oracle names before any API or code is written.

## CONTEXT

CORE-05 and DATA-04 completed their internal metadata sequences. ADR-0026 remains planning-only; no ECS runtime is authorized or qualified. WORLD-01 must not duplicate DATA/WORLD/PHYS authorities.

## SCOPE

- ADR-0127, internal architecture, governance contract and this WO.
- Activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## OUT OF SCOPE

Contract/API freeze, code, tests, ECS storage, allocators, threading, serialization, persistence, hierarchy, spatial indexing, physics, networking, editor, GPU, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0026, WORLD-01 architecture/API research, module catalog, CORE-05 and DATA-04 closeout evidence.

## REQUIREMENTS

GOV-001..007; ADR-0127; ENT-01/CMP-01/LIF-01/QRY-01/REF-01 definitions.

## ARCHITECTURE RULES

WORLD-01 owns logical identity/schema/lifecycle/query/reflection intent only. DATA-04, WORLD-02/03, CORE, PHYS and GAME retain their authorities.

## CONSTRAINTS

Risk `LOW` for this documentation gate; future implementation risk `ELEVATED`. `INTERNAL_ONLY`; no runtime/storage/threading/serialization/network/hardware; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact documentation allowlist and 13-field WO.
- No API/code/tests; ADR-0026 remains `PROPOSED`.
- docs-validation, SonarCloud and Socket pass; pt-BR audit `APPROVED`.

## TESTS

Documentation validation only; no executable test is introduced by this gate.

## DELIVERABLES

ADR-0127, internal architecture, governance contract, WO, activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## REVIEW FORMAT

pt-BR: base/head, files, scope boundaries, validator counts, CI, security/rollback, no overclaim.

## STOP CONDITION

Stale base, missing owner authorization, API/code introduced, ADR-0026 overwritten, allowlist violation, failed docs validation, HIGH/CRITICAL, runtime/storage/release claim.

## CONTEXT LOCK

Base `40aeb6e`; ADR-0026 and WORLD-01 research blobs pinned in the activation record.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-01-01-G6-ACTIVATION.md`.
