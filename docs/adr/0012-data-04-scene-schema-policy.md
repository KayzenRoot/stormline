# ADR-0012 — DATA-04 Authoritative Scene Schema, Semantic Delta and Migrations

**Status:** PROPOSED / NOT APPROVED FOR IMPLEMENTATION
**Date:** 2026-11-14 | **WO:** NLE-P00-WO-002-DATA-04 | **Research issue:** #117 | **Future code:** #27 (BLOCKED)

## Problem
A multi-platform 2D/2.5D/3D engine needs durable editable scenes whose references, component data and user customizations survive schema evolution. Native/AI workflows must be explainable and conflict-safe, and large/runtime binary data must not corrupt or replace the authoritative authoring representation.

## Proposed decisions
1. Use a **Stormline-owned, versioned semantic schema** as the authority for scene/project authoring. Explore strict UTF-8 JSON as portable Git-reviewable initial source, with stable-order pretty writer; JSON Schema Draft 2020-12 for structural validation and independent graph/capability validators.
2. Separate typed SceneIR and editor source from DATA-05 cooked/packed runtime scenes. Evaluate FlatBuffers/Protobuf/Cap'n Proto for runtime only after workload/license/build benchmarks.
3. Use durable string SceneId/EntityId/ComponentInstanceId, references to DATA-02 AssetId, namespaced ComponentTypeId and explicit hierarchy/order fields. Reject identity based on array indexes, display paths and filenames.
4. Require exact schema/version and plugin requirement negotiation. Preserve bounded unknown **optional** fields; deny unsafe read-write activation of unknown **required** features. Unknown extension payload never executes code.
5. Treat lexical byte preservation, structural semantic equivalence and exact canonical digest equality as **different claims**. Prefer readable source; if RFC 8785 JCS is used for hashes, enforce UTF-16 key ordering, I-JSON/no duplicate keys, IEEE-754 restrictions, IDs encoded as strings and cross-platform vectors.
6. Expose typed, idempotent semantic scene changes with expected_revision/expected_value, preview/diff and three-way conflicts. No silent last-writer-wins for concurrent Editor/AI authors or unreviewed destructive MCP operation.
7. Migrate via inspect/plan/dry-run/stage/verify/journal/commit/reconcile/receipt and retain prior-good backups. DATA-01 + DATA-02 are **not one ACID transaction**; crash recovery proof is mandatory. No unsupported downgrade claim.
8. Limit recursion, entity count, strings, plugin payload, decompression and compute; reject nonfinite floats, invalid UTF-8, duplicate keys and unintended executable type loading.
9. Stormline Semantic Scene Delta (SSD) is PROPOSED R&D, accepted only with demonstrated correctness/cost benefit vs ordinary typed ID-aware AST diff and JSON Patch; otherwise drop.
10. Keep Windows/Linux/macOS/Apple Silicon and Web/headless interop as actual future test gates, no assumption of 1:1 runtime binary codec support.

## Alternatives and trade-offs
- Binary-only editor source: compact, but discourages human diffs/merge and mandates tools to recover content; reject as default without proof.
- JSON5/TOML/YAML as canonical scene: may improve comments/preferences but normalization, nested graph handling and unsafe tags/aliases add complexity. Optional configuration/import, not baseline.
- Protobuf/FlatBuffers as universal schema and editor source: generated tooling may simplify some contracts but locks authoring to runtime wire semantics; defer.
- Generic JSON Patch on raw arrays: insufficient semantic identity/order/conflict validation; use as comparator only.
- Always-on proprietary SSD: reject unless measured benefit without duplicate data authority.
- Silent migration on open or destructive downgrade: reject data loss. Explicit preview and backup/recovery.
- Storing secrets or raw paths in scenes: reject privacy and portable project constraints.

## Deliberately deferred
Exact schema dialect subset, field/type registry, library tag/license/SBOM, engine source license, editor filename extensions, target component set, binary runtime encoder, reversible migration subset, numeric tolerances and performance budgets. These need approved technical/implementation evidence.

## Future proof obligations
Roundtrip golden corpus, unknown-field extension and hierarchy/order tests; compare JSON library/bytewise JCS conformance; entity and asset reference integrity; 3-way merge collisions; migration to newer then open old, unsupported downgrade; crash/disk-full/kill/rollback; hostile payload/fuzz/caps; actual Windows/Linux/macOS/Web/headless runs, OS/hardware real benchmark. Identify sources, hashes, compiler flags and fixtures. No code/benchmark currently exists.

## Consequences
Every DATA-04 executable WO requires predecessors (CORE-05, DATA-01/02 as contracts), architecture/Scope/DoD review, approved ADR, exact files/commands, risk ELEVATED, real CI/security and fresh Context Lock. This proposal does not unblock issue #27 or any of the 80 implementation WOs.

See [architecture](../architecture/data-04-serialization-scene-format.md), [tech matrix](../research/data-04-scene-technology-matrix.md), [API](../contracts/data-04-scene-api.md), [tests](../testing/data-04-acceptance-matrix.md).
