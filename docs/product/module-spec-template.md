# Stormline — Module Specification Template
Work Order: NLE-P00-WO-001-EXT-002 | Status: TEMPLATE / PROPOSED

> Instantiate once per approved module ID when its detailed planning Work Order becomes NECESSARY. The module catalog is a candidate inventory, not 79 completed specifications.

## 1. Identity
Module ID / name / category / status / release class / accountable owner / dependencies / interfaces.

## 2. Objective
Explain what value and which supported game creation scenarios the module enables. Describe measurable non-goals.

## 3. Functional requirements
Owner-approved requirements with ID, testable behavior, failure handling, edge cases and error codes.

## 4. Public and internal contracts
Input/output types, lifecycle, state ownership, memory/thread safety, security boundaries, serialization, compatibility/versioning, and interoperability.

## 5. Editor / CLI / MCP coverage
For each authoring operation: command ID, typed schema, read/write permission, editor action, CLI mapping, MCP tool/resource/prompt, preview/undo, deterministic test and compatibility target. Document internal-only operations explicitly, with rationale.

## 6. Data model & migration
Stable IDs, schema, validation, migration, backup, transaction, constraints, limits, loss recovery and asset provenance.

## 7. Performance & resource budgets
CPU timing, GPU timing, memory, VRAM, I/O, latency, density and load profile. Identify scenes, hardware tiers, methods, thresholds, percentiles and instrumentation. Do not invent benchmark results.

## 8. Security & abuse
Threats, trust boundaries, input limits, sandbox, permissions, fuzzing, integrity, logging and privacy.

## 9. Dependencies & alternatives
Approved ADRs, third-party licensing, constraints, replacement costs, fallback and platform feature tiers.

## 10. Tests, evidence & benchmarks
Unit, integration, golden data, visual/audio, load, stress, failures, multi-platform, MCP conformance, recovery; evidence with commit SHA.

## 11. Deliverables
What exists in code, editor, SDK, tests, docs, examples, profiling and troubleshooting.

## 12. Risks, open questions & decisions
Risk register with severity, mitigations, unresolved ADRs and explicit scope decisions.

## 13. Acceptance & DoD
Owner-approved criteria; fail CLOSED when required tests fail, defects HIGH/CRITICAL remain, or required support/compatibility is missing.

## 14. State changes
PROPOSED -> OWNER-APPROVED (plan only) -> IMPLEMENTING -> TESTED -> AUDITED -> APPROVED / CORRECTION REQUIRED / BLOCKED. No promotion based on self-reported completion.
