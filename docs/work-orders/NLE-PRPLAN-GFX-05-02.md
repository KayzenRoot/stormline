# NLE-PRPLAN-GFX-05-02 — Logical material/texture contract (INTERNAL_ONLY)

**STATUS: G6 CONTRACT PACKET — no code authorized.** **Formal packet:** `NLE-PRPLAN-GFX-05-02`. **Predecessor:** `GFX-05-01` governance. **Issue:** #33. **Base:** `11d658e`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md).

## OBJECTIVE

Freeze the exact internal GFX-05 API, capacities, validation rules, deterministic ordering, errors and per-slice allowlists for logical materials, textures, mips, samplers, virtual pages, decals and transparency.

## CONTEXT

GFX-05-01 approved ADR-0119 and the internal direction. GFX-02 and DATA-03 completed internal sequences. No native GPU, codec/decoder, shader compiler, texture upload, submission, renderer, dependency, ABI or release is authorized.

## SCOPE

- `docs/contracts/gfx-05-material-internal-v0.md`.
- WO, G6 evidence, activation JSON, manifest/validator/test/checkpoint updates.

## OUT OF SCOPE

Implementation `-03`..`-09`, closeout, native GPU/codec/decoder, texture upload, BRDF evaluation, rendering, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0018/0086/0119, GFX-05 architecture/API/matrix, GFX-05 governance contract, GFX-02 and DATA-03 closeouts.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0119; exact API and PBR/VTX/MIP/SMP/DEC/TRN/QLF-G5 oracles.

## ARCHITECTURE RULES

GFX-05 owns logical material/texture semantics; DATA-03 owns source texture validation; GFX-02 owns shaders; GFX-01/GFX-03 keep RHI/graph boundaries; no native GPU/codec.

## CONSTRAINTS

Risk `LOW` contract; `INTERNAL_ONLY`; no GPU/codec/decoder/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Contract exact and complete; manifest root `GFX05_02_APPROVED_CONTRACT_ONLY`.
- No code, dependency, native GPU/codec or release claim.
- Docs Validation and pt-BR audit `APPROVED`.

## TESTS

Document validation only; future oracles are declared but not executed in this packet.

## DELIVERABLES

Contract, WO, G6 evidence, activation JSON, manifest/validator/checkpoint updates, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, API completeness, boundaries, CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, native GPU/codec selection, incomplete API, code inclusion, allowlist violation, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `11d658e`; governance merge `11d658e`; contract blob pinned after this gate.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-05-02-G6-ACTIVATION.md`.
