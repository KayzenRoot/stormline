# SIM-03 — Future Character Movement & Replay Acceptance Matrix

**NLE-P00-WO-002-SIM-03 | Research #180 | Code #48 BLOCKED.**  
**ALL 72 CASES ARE FUTURE / NOT EXECUTED.** No engine, character controller, native/Web build, physics backend, golden replay, benchmark or user playtest exists.

Tests are prospective obligations, not pass claims. Each requires independent authored rights-cleared fixtures, seed, exact backend/profile SHA, platform/compiler, measured thresholds agreed in versioned DoD, and attached raw outputs before unlocking coding.

| Case ID | Objective / fixture | Evidence to capture | Status |
|---|---|---|---|
| IDN-001 | Handle stale after motor destroyed and slot recycled | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| IDN-002 | Foreign WorldEpoch and project motor rejected | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| IDN-003 | Cross dimension 2D/3D handle rejected | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| IDN-004 | Deleted EntityGuid does not crash or resurrect motor | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| IDN-005 | Concurrent detach and contact batch safe after barrier | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| IDN-006 | Profile revision CAS mismatch leaves last-good source | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| INT-007 | Input normalized and diagonal speed policy explicit | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| INT-008 | Duplicate identical TickId/sequence is idempotent | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| INT-009 | Conflicting sequence within same TickId rejected | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| INT-010 | Out-of-order or expired TickId rejected | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| INT-011 | Unauthorized gameplay/MCP input rejected | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| INT-012 | Missing input tick uses documented zero/hold behavior | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| NUM-013 | NaN/Inf input and profile rejected without mutation | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| NUM-014 | Zero/negative radius or mass rejected | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| NUM-015 | Excessive speed/gravity/step/snap clamped or rejected by policy | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| NUM-016 | Origin-rebase epoch checked at tick barrier | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| NUM-017 | Negative and far global coordinates preserve local precision bounds | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| NUM-018 | 2D signed axis and pixel/meter conversion invertible | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| GRD-019 | Grounded normal vs wall/ceiling threshold independent | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| GRD-020 | Steep slope blocked or controlled slide with stable contact | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| GRD-021 | Snap downhill preserves contact but no upward-jump snap | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| GRD-022 | One-way platform filters follow explicit authored rule | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| GRD-023 | Slope transition at shared mesh seams stable | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| GRD-024 | Missing or corrupt streamed ground returns COLLIDER_PENDING | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| COL-025 | Continuous capsule sweep stops at thin wall under velocity caps | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| COL-026 | Corner collision projection limited and no infinite iteration | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| COL-027 | Skin width avoids tunneling or pathological penetration | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| COL-028 | Moving static collider source revision invalidates contacts | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| COL-029 | Crouch ceiling clearance denies unsafe stand-up | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| COL-030 | Collision layer/mask applies to casts and contacts | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| MOV-031 | Move zero input decelerates according to profile | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| MOV-032 | Jump buffered for bounded integer ticks and consumed once | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| MOV-033 | Coyote-time window uses tick counts not wall time | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| MOV-034 | Variable jump hold/release policy yields reproducible apex | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| MOV-035 | Dash request applied only if GAME permission/profile allows | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| MOV-036 | Top-down planar heading vs FPS camera pitch isolated | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| PLT-037 | Moving platform linear carry uses authoritative platform tick | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| PLT-038 | Rotating platform motion includes angular contribution | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| PLT-039 | Platform detach preserves or drops velocity per versioned policy | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| PLT-040 | Platform deallocation invalidates support without UAF | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| PLT-041 | Platform teleports and origin shifts handled without ghost carry | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| PLT-042 | Chunk eviction cannot retire live supported platform unsafely | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| 2DT-043 | Pure 2D world uses 2D collision backend not 3D adapter | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| 2DT-044 | 2.5D presentation leaves 2D physics plane invariant | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| 2DT-045 | Rectangular world units and sprite pixels-per-meter isolated | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| 2DT-046 | Tile corner collision normal/shape revision matches TWO-02 | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| 2DT-047 | 2D sloped chain edge crossing stable | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| 2DT-048 | Web/WASM 2D fallback feature receipt truthful | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| 3DT-049 | 3D capsule on stairs with head clearance checks | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| 3DT-050 | 3D crouch capsule resize preserves center/feet policy | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| 3DT-051 | 3D terrain + cave collider revision consistent | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| 3DT-052 | 3D high vertical velocity hits ceiling and settles | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| 3DT-053 | 3D support normal orientation correct after local-origin shift | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| 3DT-054 | 3D Jolt CharacterVirtual state captured separately if selected | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| REP-055 | Same pinned input/backend world replay produces bounded divergence | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| REP-056 | Presentation frame rate 24/30/60/120/240 does not change fixed ticks | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| REP-057 | Input commands are sorted by stable actor/sequence keys | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| REP-058 | Platform/contact event ordering canonical after physics step | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| REP-059 | Restored snapshot without solver contact state rejected for rollback | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| REP-060 | Replay manifest contains backend/shape/profile/epoch/build hashes | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| SEC-061 | Malformed untrusted profile/collision shape fuzz does not hang | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| SEC-062 | Unbounded callbacks/events truncated with explicit overflow receipt | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| SEC-063 | MCP cannot inject privileged teleport into running authoritative world | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| SEC-064 | Per-character sweep budget prevents denial of service | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| SEC-065 | Partial network/world unload does not expose stale handles | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| SEC-066 | Cross-project source profile rights checked before stage | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| BEN-067 | Headless 100 characters measured CPU tick p50/p95/p99/worst | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| BEN-068 | Headless 1000 characters measured CPU tick p50/p95/p99/worst | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| BEN-069 | Character mass under moving-platform and terrain stream stress | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| BEN-070 | CPU memory peak and allocation count at 1/2/8 workers | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| BEN-071 | Windows/Linux/macOS build+ASan/UBSan where supported | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |
| BEN-072 | Web/WASM single-thread fallback measured or transparently unsupported | Future: unit/integration/golden/fuzz/perf evidence as applicable | NOT EXECUTED |

## Required gates and failure interpretation
- **Data safety:** corrupt/partial source state must not be silently recovered as complete. Test DATA-04 CAS/undo, shape revisions, contact ACK, stream fence and last-good source.
- **Safety:** no remote arbitrary world edits, command admission confusion, infinite sweeps, unbounded event collection, use-after-free or stale cross-world ID.
- **Numerical:** define error tolerances and profile-specific baselines before measuring. Do not equate replay intent-order determinism with bitwise cross-platform physics determinism.
- **Performance:** report percentile CPU tick, physics query count and memory separately from GPU presentation; workload profiles and threshold remain TBD.
- **Quality:** player-feel usability studies using original scenes and explicit repeatable tasks are required beyond automated geometric correctness; no claim of superior feel without experiments.
- **Cross-platform:** verify native Windows/Linux/macOS and Web tier where feasible; an unavailable or degraded feature must be declared, not counted as PASS.

No case here authorizes starting coding #48. The project must satisfy its Source Hierarchy, predecessor code, approved release class/ADR, DoD and exact-head CI/audit first.
