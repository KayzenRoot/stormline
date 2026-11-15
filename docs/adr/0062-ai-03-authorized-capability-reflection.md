# ADR-0062 — Authorized, Versioned Capability Reflection from AI-01

**2026-11-15 | P00 RESEARCH ONLY, NOT IMPLEMENTED | [research #289](https://github.com/KayzenRoot/stormline/issues/289) | NLE-P00-WO-002-AI-03 | [future code #77](https://github.com/KayzenRoot/stormline/issues/77) OPEN/BLOCKED | BASE `1db368aa555f7a8eb2fa1a1eb3a38744a23ef6bb`.** 58/80 researched at baseline, 22 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency **AI-01 ONLY**; ADR-0060 PROPOSED and code #75 OPEN/BLOCKED. NLE-D009 engine license OPEN.

**STATUS: PROPOSED / NOT OWNER-APPROVED / NOT ADOPTED / NO CODE AUTHORIZATION.**

## Context
The AI-native platform requires a discoverable exhaustive registry of approved public authoring actions and their schemas, error taxonomy, permission envelopes and deprecation rules. AI-01's ADR-0060 (PROPOSED) already owns command IDs, dispatch, authorization and receipts. A second independently editable registry would split truth, permit ghost routes and increase attack surface. Future AI-04 MCP transport must remain an adapter.

## Decision PROPOSED
1. **Build-time validated reflection plus immutable runtime read views** derived from AI-01 owner-declared CommandDescriptorV1. Never independently allocate/execute new capabilities in AI-03.
2. Exactly one formal predecessor: **AI-01**. No new dependency on AI-02/04/06/07 or editor/engine owners; only integration contracts and future conformance.
3. Public capability is identified by stable namespaced **AI-01 CommandId**; descriptor carries schema/contract major-minor, owner ModuleId, origin UI/CLI bindings, scope, side effects, feature/target, required grant/consent and supported error/receipt contracts.
4. **JSON Schema Draft 2020-12** is preferred protocol schema candidate; compile only pinned allowed dialects/vocabularies, offline local `$ref` references and bounded graph. Validate schema compilation AND instances, including required object-root input for MCP tools. Guard formats, regex, recursive evaluation, unknown keywords and numeric/UTF-8 precision separately.
5. A registry generation becomes visible **only when complete, validated, atomic and reversible**; prior valid generation remains usable until safely replaced. Plugin/feature additions require owner provenance, compatibility and authorization review, not auto-export.
6. Discovery is least-privilege filtered per project/actor/target/grant/policy revocation epoch and immutable snapshot. Visibility does not grant invocation. Owner rechecks grants/revisions at invoke.
7. External inventory oracle: **all independently observed public authoring operations**, with explicit reason/owner for excluded actions, must map bijectively or many-to-one by an approved alias to valid descriptors. No '100%' based only on self-generated registry count.
8. Compatibility checks run on input, output, errors, side-effects, required permissions, target and deprecation; breaking change requires explicit major version/new capability plus transition and tests.
9. MCP 2026-07-28 tool projections inherit authoritative IDs/schemas and scope, use deterministic sorted listings and per-request permissions. Tool annotations are descriptive and untrusted. Do not create remote listener, new auth provider or MCP server here.
10. Current result is **research only**. Future code #77 remains BLOCKED alongside all 80 code packets; no implementation, approved stack/license, release class, performance claim or future test completion.

## Alternatives
- **Hand-maintained second JSON registry:** rejected as proposal because drift creates privilege/identity divergence and self-attested coverage.
- **Live runtime reflection by unrestricted language/RTTI introspection:** rejected because it leaks private methods, ABI internals and entangles C++ runtime with MCP.
- **Generate schemas from TypeScript/Zod/OpenAPI-only DSL:** not selected; additional runtime/source-of-truth, version portability and non-HTTP command mismatch; may be used as optional generated views after conformance.
- **Protobuf-first canonical command schema:** future option; typed compatibility strengths but JSON Schema/MCP dialect transport conversion and field-presence/capability constraints require proofs.
- **No registry, expose AI-01 descriptors dynamically:** insufficient independent inventory, staged publishing, provenance, schema validation and compatibility report.
- **JSON Schema 2020-12 + jsoncons Boost-1.0** as validation candidate: needs pinned tag, test suite and security fuzz/benchmark; NOT adopted. nlohmann json-schema-validator is Draft 7 not equivalent to 2020-12.

## Consequences / risks
Benefits: discoverability, consistent Editor/CLI/MCP, versioned migrations, reduced agent context and audited 100% eligibility. Costs: build-time schema tooling, compatibility gates, dependable revocation/filtering, offline immutable generations and quality of owner-supplied contracts. Risks: nested schema explosion, Unicode/parsing divergence, dynamic $ref, metadata spoofing, changes that older clients perceive as breaking, stable cursor privacy, over-eager plugin exposure. Mitigate via caps/fuzz/policy and independent route inventory. No license inferred; NLE-D009 remains OPEN.

## Acceptance/ratification gate
Owner review of ABI/schema/licensing/version/security/target and future code WO, full AI-01 dependency approval+implementation, 128 future tests with measured conformance, 100% independent public action coverage per approved eligible action manifest, native platform proof, CI, independent audit and checkpoint. This ADR remains PROPOSED until separate owner acceptance. No approved decision is overwritten.

[Architecture](../architecture/ai-03-capability-registry-schemas.md) · [Technology matrix](../research/ai-03-schema-technology-license-matrix.md) · [API](../contracts/ai-03-capability-registry-api.md).
