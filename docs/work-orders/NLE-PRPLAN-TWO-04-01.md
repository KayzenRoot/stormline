# NLE-PRPLAN-TWO-04-01 — Internal hybrid composition governance

**STATUS: G6 GOVERNANCE PACKET — documentation only; no code authorized.** **Formal packet:** `NLE-PRPLAN-TWO-04-01`. **Issue:** #40. **Base:** `60187a1`. **Module:** TWO-04 — 2.5D Hybrid Composition. **Predecessors:** TWO-01 and GFX-04 completed internal sequences (not qualified). **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Governance contract:** [two-04-governance-v0](../contracts/two-04-governance-v0.md).

## OBJECTIVE

Approve the bounded internal logical hybrid-composition sequence and freeze its ownership, risk, release class and oracle names before any API or code is written.

## CONTEXT

TWO-01 and GFX-04 completed their internal metadata sequences. ADR-0025 remains planning-only; no runtime rendering is authorized or qualified. TWO-04 must not duplicate GFX/TWO renderer ownership.

## SCOPE

- ADR-0126, internal architecture, governance contract and this WO.
- Activation evidence, activation JSON, manifest/validator/tests and checkpoint entry.

## OUT OF SCOPE

Contract/API freeze, code, tests, renderer, GPU, depth attachments, shaders, lighting, subview execution, editor, export, hardware, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0025, TWO-04 architecture/API research, module catalog, TWO-01 and GFX-04 closeout evidence.

## REQUIREMENTS

GOV-001..007; ADR-0126; CAM-01/LAY-01/SRT-01/EFE-01 definitions.

## ARCHITECTURE RULES

TWO-04 owns logical composition intent only. GFX-03/04/05/06/07, TWO-01, DATA-04 and PHYS/WORLD retain their authorities.

## CONSTRAINTS

Risk `LOW` for this documentation gate; future implementation risk `ELEVATED`. `INTERNAL_ONLY`; no rendering/audio/export/GPU/dependency/native I/O/network/hardware; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact documentation allowlist and 13-field WO.
- No API/code/tests; ADR-0025 remains `PROPOSED`.
- docs-validation, SonarCloud and Socket pass; pt-BR audit `APPROVED`.

## TESTS

Documentation validation only; no executable test is introduced by this gate.

## DELIVERABLES

ADR-0126, internal architecture, governance contract, WO, activation evidence/JSON, manifest/validator/tests and checkpoint entry.

## REVIEW FORMAT

pt-BR: base/head, files, scope boundaries, validator counts, CI, security/rollback, no overclaim.

## STOP CONDITION

Stale base, missing owner authorization, API/code introduced, ADR-0025 overwritten, allowlist violation, failed docs validation, HIGH/CRITICAL, runtime/release claim.

## CONTEXT LOCK

Base `60187a1`; ADR-0025 and TWO-04 research blobs pinned in the activation record.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-04-01-G6-ACTIVATION.md`.
