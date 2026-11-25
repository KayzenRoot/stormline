# ADR-0135 — Internal logical skeletal animation metadata

**Status: APPROVED for bounded internal logical metadata only.** **Date:** 2026-11-24. **Module:** `SIM-04` — Skeletal Animation & Motion. **Issue:** #49. **Keeps planning-only:** [ADR-0034](0034-sim-04-animation-authority-retarget-ik-and-ragdoll.md), which remains `PROPOSED / NOT APPROVED FOR ENGINE CODE`.

## Context

SIM-04 must eventually provide retargeting, blend trees, IK, ragdoll requests, clip compression and sync groups over authoritative character motion. The full problem includes runtime pose evaluation, root-motion request/ack against SIM-03, ragdoll lifetime delegated to SIM-02, imported animation assets, deterministic replay and multi-platform qualification. Those runtime capabilities are not qualified and must not be claimed.

The module's formal predecessors, SIM-03 and DATA-03, have completed their internal sequences and are available as capability sources. Their status is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## Decision

Approve a bounded internal sequence that produces **logical skeletal animation metadata only** under `src/stormline/animation/`:

1. Retarget profile metadata: joint mapping pairs, bind-basis scales and semantic references; no pose conversion.
2. Blend tree metadata: node kinds, weights, thresholds and graph shape; no evaluation.
3. IK chain metadata: chain lengths, iteration budgets and tolerances; no solver.
4. Ragdoll profile metadata: body/joint mapping references and activation intent; no physics lifetime ownership.
5. Compression profile metadata: bit widths, keyframe intervals and quality flags; no codec.
6. Sync group metadata: phase offsets, markers and group references; no runtime synchronization.
7. Integrated deterministic validation, failure-recovery and bounded-overload qualification.

The sequence must not implement a pose evaluator, graph runtime, IK solver, ragdoll activation, codec, root-motion application, ECS mutation or network prediction. SIM-01/02 own collision and physics runtime; SIM-03 owns character motion and applied-motion receipts; CORE-03/04/06 own jobs/tick; DATA-02..05 own clips/assets/journal/cook; GAME/NET own authority.

## Ownership and boundaries

| Concern | Authority | SIM-04 may produce |
|---|---|---|
| Entity identity/lifecycle | WORLD-01 | optional entity references |
| Character motor/root motion | SIM-03 | request/reference descriptors only |
| Physics bodies/constraints | SIM-02 | ragdoll mapping intent only |
| Clip import and rights | DATA-02/03 | asset references and revisions |
| Jobs, tick, scheduling | CORE-03/04/06 | iteration/tick-window descriptors |
| Camera and rendering | GFX/editor | none |
| Runtime authority | GAME/NET | proposals; owners decide |

## Risk and release class

- Planning risk: `LOW` for documentation and logical metadata.
- Future runtime animation risk: `ELEVATED`, explicitly out of scope for this sequence.
- Release class: `INTERNAL_ONLY`. No public ABI, release, hardware, performance, gameplay-feel or production-readiness claim.

## Rejected alternatives

- Exposing ozz-animation/ACL/glTF runtime types as the contract; rejected because backend choice, license/SBOM and ABI are unqualified.
- Implementing a pose evaluator, IK solver or codec; rejected because determinism and quality obligations are unexecuted.
- Owning ragdoll physics lifetime; rejected because SIM-02 authority and transition proofs are not implemented.
- Applying root motion directly to transforms; rejected because SIM-03 request/ack authority is required.
- Approving ADR-0034 wholesale for engine code; rejected because its proof obligations are not executed.

## Consequences

- Slice `-02` must freeze an exact header-only logical API, allowlist and test oracles before any code.
- Each implementation slice requires its own G6 activation gate.
- The module can close as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; it cannot claim animation quality, retarget fidelity, IK stability, ragdoll safety, compression ratios, determinism or performance.
- Any future runtime animation implementation requires a new owner-approved decision that resolves ADR-0034's proof obligations.
