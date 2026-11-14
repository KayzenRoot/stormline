# Stormline — Full Commercial Release Readiness (No MVP)
Work Order: NLE-P00-WO-001-EXT-002 | Status: PROPOSED; NO SHIPPED RELEASE.

## Owner-directed principle
The owner explicitly does **not** want an MVP or any public use before the engine is **fully ready for its defined 1.0 commercial scope**, even if development takes years. Internal prototypes, instrumented builds, unit tests and integrated sample projects still exist as **engineering verification**; these are not public, paid or finished products.

## Define the 1.0 contract before freezing scope
No commercial software can provide literally all possible technologies or game genres forever. Freeze a **complete 1.0 capability matrix** that includes all approved must-have authoring paths and excludes explicit future research. This matrix requires an owner-approved ADR, module IDs, acceptance evidence and compatibility targets.

Candidate minimum contracted capability:
1. Full creation and export of original **2D**, **2.5D** and **3D** games; independent 2D workflow.
2. Desktop builds for Windows/Linux, and browser/WebAssembly target with documented feature tiers/fallback.
3. Complete visual editor with assets, scenes, animation, material, VFX, audio, gameplay, debug, export and profiling.
4. Scriptable gameplay and extensibility, source/project format stability and migration.
5. Performance-aware rendering/lighting, VFX and audio with reproducible scenes/hardware.
6. Headless simulation and multiplayer architecture with defined acceptance load and security gates.
7. Full AI-assisted authoring via core commands and versioned MCP transport with explicit safeguards, host conformance and parity tests.
8. Professional docs, tutorials, original demo projects, distribution, software license, compliance and support process.
9. QA matrix for security, compatibility, integrity, recovery, CI, installers and production-like validation.
10. No unapproved paid infrastructure, outside mandatory human reviewer, or proprietary asset reuse.

### Web target guardrails
WebGPU can deliver advanced rendering but remains limited across some browser/OS combinations, requires secure contexts and selected adapter features. Browser threads/shared memory can need cross-origin isolation. Define WebGPU and fallback path(s) as a platform-specific ADR. Do not promise feature/performance parity with native.

### Specialized targets
Mobile platform selection, console SDKs, storefronts and external proprietary integrations are conditional, depending on rights, budgets, certification and hardware. They are not automatically required for a full desktop+web 1.0 unless explicitly approved.

## No 'feature complete' without coverage
### Technical completeness
- Every MANDATORY module has API contract, tests and integration evidence.
- Editor/CLI/MCP capability matrix reaches approved completeness target.
- Reproducible builds, project export, upgrade and data migration.
- Benchmark scenarios meet approved budgets on all **target** hardware tiers.
- Stable frame timing (including p95/p99), crash recovery and soak tests.
- No HIGH/CRITICAL security, correctness, data loss or integrity findings.
- Clear license/IP chain for engine and third-party dependencies.
- Comprehensive starter projects and usable documentation.

### End-to-end game creation matrix
- 2D platform game or top-down game.
- 2.5D action RPG with skills, VFX, camera and audio.
- 3D combined-arms test world with infantry, at least one land/air vehicle where committed, terrain, streaming and multiplayer.
- Web game of approved complexity with compatible browser/device matrix.
- Creation of all these by visual tools and AI workflows, verifying semantic equivalence of project operations.

### Operability and support
- Import/export and project backup/restore.
- Installer/package checksum, updates, rollback and migration tests.
- Security advisories, issue triage, bugfix SLA if the owner chooses one, versioning policy.
- License and trademark clearance, product description and rights management.
- Onboarding and developer guides in English, localized materials per approved scope.

## Performance research is not a numerical promise
The target is to **reduce cost per achieved quality**, not merely to maximize FPS with reduced effects. Every comparison must record:
`scene | engine commit | hardware | driver | CPU/GPU frame p50/p95/p99 | VRAM/RAM | quality tier | resolution | energy if relevant | visual/audio scoring rubric`.
The benchmark plan will determine hard limits; none are currently approved.

## Release gates
`MODULE_CATALOG_APPROVED -> ARCHITECTURE_AND_STACK_APPROVED -> INTERNAL_BUILDS -> INTEGRATION_SUITES -> FEATURE_COMPLETE_INTERNALLY -> RC_TESTING -> LEGAL_AND_SECURITY -> OWNER_APPROVAL -> GA_1.0`.

Do not label the engine complete, usable or commercial before every applicable gate has real evidence. No pressure to publish an MVP.

## Risks and honest boundaries
An original general-purpose engine is a multi-year high-complexity effort; AI can accelerate implementation but does not replace GPU/OS validation, subject expertise, testing, usability studies, support or licensing. A strong 1.0 specification may still need scope trade-offs by explicit owner decision to remain achievable, without releasing an inferior partial product.
