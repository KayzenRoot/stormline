# NLE-PRPLAN-WORLD-03-01 — Internal spatial/streaming metadata governance

**STATUS: G6 GOVERNANCE PACKET — documentation only; no code authorized.** **Formal packet:** `NLE-PRPLAN-WORLD-03-01`. **Issue:** #43. **Base:** `720f21b`. **Module:** WORLD-03 — Spatial Index & World Streaming. **Predecessors:** WORLD-02 and DATA-05 completed internal sequences (not qualified). **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Governance contract:** [world-03-governance-v0](../contracts/world-03-governance-v0.md).

## OBJECTIVE

Approve the bounded internal logical spatial/streaming metadata sequence and freeze its ownership, risk, release class and oracle names before any API or code is written.

## CONTEXT

WORLD-02 and DATA-05 completed their internal sequences. ADR-0028 remains planning-only; no streaming runtime is authorized or qualified. WORLD-03 must not duplicate DATA/CORE/PHYS/NET authorities.

## SCOPE

- ADR-0129, internal architecture, governance contract and this WO.
- Activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## OUT OF SCOPE

Contract/API freeze, code, tests, async tasks, I/O/decode/cache, origin rebase, spatial queries, physics/network coordination, renderer, editor, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0028, WORLD-03 architecture/API research, module catalog, WORLD-02 and DATA-05 closeout evidence.

## REQUIREMENTS

GOV-001..007; ADR-0129; CEL-01/INT-01/ORG-01/STR-01 definitions.

## ARCHITECTURE RULES

WORLD-03 owns logical cell/interest/origin/streaming intent only. DATA-05, CORE, WORLD-01/02, PHYS/AI/GAME/NET retain their authorities.

## CONSTRAINTS

Risk `LOW` for this documentation gate; future implementation risk `ELEVATED`. `INTERNAL_ONLY`; no runtime/I/O/threading/network/hardware; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact documentation allowlist and 13-field WO.
- No API/code/tests; ADR-0028 remains `PROPOSED`.
- docs-validation, SonarCloud and Socket pass; pt-BR audit `APPROVED`.

## TESTS

Documentation validation only; no executable test is introduced by this gate.

## DELIVERABLES

ADR-0129, internal architecture, governance contract, WO, activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## REVIEW FORMAT

pt-BR: base/head, files, scope boundaries, validator counts, CI, security/rollback, no overclaim.

## STOP CONDITION

Stale base, missing owner authorization, API/code introduced, ADR-0028 overwritten, allowlist violation, failed docs validation, HIGH/CRITICAL, runtime/I/O/release claim.

## CONTEXT LOCK

Base `720f21b`; ADR-0028 and WORLD-03 research blobs pinned in the activation record.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-03-01-G6-ACTIVATION.md`.
