# CORE-05 INTERNAL_ONLY Governance Contract v0 (NLE-PRPLAN-CORE-05-01)

**Status:** `GOVERNANCE PROPOSAL / NO CODE AUTHORIZED`. **Base:** `0e5d6e5ae0b418823d667aa7e67d0e82154d532c`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md), [ADR-0007](../adr/0007-core-05-coordinate-policy.md) planning-only. **WO:** [NLE-PRPLAN-CORE-05-01](../work-orders/NLE-PRPLAN-CORE-05-01.md).

## Objective

Define the bounded governance envelope for CORE-05 math/coordinates/types before any contract or code: ownership, conventions, risk/release, capability admission and gates.

## Ownership boundaries

- CORE-05 owns scalar/vector/matrix/quaternion types and explicit coordinate/unit/identifier contracts.
- CORE-01 owns platform/CPU capabilities; CORE-02 memory/alignment; CORE-03 scheduling; CORE-04 tick time.
- SIM/WORLD/GFX/DATA/NET/editor/MCP consume typed math APIs but do not silently change conventions.
- GFX-01 owns backend projection/clip-space conversion; physics chooses solver precision in its own ADR.

## Planning conventions

- 3D right-handed world: +X right, +Y up, -Z forward; 2D uses explicit XY plane; 2D pixel/UI/Web adapters are named.
- Meters for world distance, seconds from CORE-04, radians for angles; explicit degree/radian conversion.
- Column-vector transforms, world = parent * local; points w=1, directions w=0.
- Column-major storage is a candidate declared separately from composition order; no implicit backend assumption.
- Quaternion normalized at public boundaries; q and -q canonicalization for serialized equality.
- f32 local/render; f64 global-origin candidate; signed-cell alternative not selected.
- Persistent opaque IDs vs generational runtime handles.

## Capability admission

Formal dependency `CORE-01` remains. Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph. `module_completion_claimed=false`. Window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release are not used.

## Gates before code

1. `CORE-05-02` contract: exact logical types, error model, file allowlist, golden tests.
2. Individual `CORE-05-03` G6 activation and explicit owner authorization.
3. No third-party math dependency/type without separate license/security decision.
4. Golden tests for basis/transforms/inverse/quaternion/units/precision/overflow/ID/origin rebase.
5. MSVC/GCC/Clang/AppleClang CI; no HIGH/CRITICAL; no public ABI/release.

## Stop / rollback / security

Stop on stale source, missing admission, third-party type in core, silent narrowing/non-finite propagation, public ABI/release claim, unresolved license, HIGH/CRITICAL. Unmerged: close the branch; after merge: normal revert PR, never force push.

No implementation packet becomes `EXECUTOR_READY` by this contract. `CORE-05-02`..`-10` remain `PLANNED_BLOCKED`.
