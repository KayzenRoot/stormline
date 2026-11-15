# NLE-P00-WO-002-GAME-04 — Gameplay Systems & Typed Event Bus Research Work Order

**Research issue #220. Future coding issue #60 remains OPEN/BLOCKED. BASE main:** `b64194591d761cd3e785337b10a524d085ec04d1` (after GAME-03 research #217, checkpoint #218 and closeout #219 squashed/read back). **Catalog position 42/80; research before this WO 41/80.** Status DOCUMENTATION ONLY; risk LOW for research, future runtime ELEVATED or HIGH_ASSURANCE for privileged irreversible operations. No executor authorization.

## OBJECTIVE
Research and specify genre-agnostic game state, scene-flow control, typed deterministic event bus, game systems scheduling boundaries, script/event bridging, data-defined abilities/cooldowns/damage/status, inventory, quests, save hooks, multiplayer/rollback and bounded security. Create evidence-rich technical proposal without engine code or third-party runtime installation.

## CONTEXT
Stormline is owner-governed original 2D/2.5D/3D/Web engine, Windows/Linux/macOS first-class, no public MVP, zero mandatory paid tools. GAME-02, GAME-01 and WORLD-02 are catalog prerequisites **research-only**, not implemented. CORE-03/04, WORLD-01, DATA and NET remain owned integration services. One complete generic API serving different genres without core forks is catalog acceptance, NOT yet achieved.

## SCOPE
Precisely eight new Markdown files:
1. [Architecture](../architecture/game-04-gameplay-systems-event-bus.md)
2. [ADR-0045 PROPOSED](../adr/0045-game-04-typed-deterministic-gameplay-event-bus.md)
3. [Technology/licenses with official links](../research/game-04-gameplay-technology-license-matrix.md)
4. [Typed versioned contracts](../contracts/game-04-gameplay-event-api.md)
5. [128 future acceptance tests](../testing/game-04-acceptance-matrix.md)
6. [Reproducible benchmark protocol](../research/game-04-gameplay-benchmark-protocol.md)
7. This Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-GAME-04.md)

Research PR: branch `docs/NLE-P00-WO-002-GAME-04-gameplay-event-bus` from exact main; validate Docs Validation **at final HEAD**, audit objective pt-BR, normal squash/main readback. Only after APPROVED may an **independent checkpoint PR** alter exactly `docs/11-checkpoint.md`, `docs/08-backlog.md`, `docs/queue/implementation-registry.json`, this WO and Evidence Bundle, with its own Docs Validation/audit/squash/readback and closure of research #220. Registry delta **ONLY** GAME-04 `research_status=RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`; 42/80 (52.5%) researched, 38 pending, zero runtime, 80/80 code packages remain blocked.

## OUT OF SCOPE
Any C++ source, game executable, script VM, ECS dispatcher, engine runtime, NET transport, save database, scene load, item/quest/ability simulator, imported dataset/SDK/license adoption, compiled tests, measured performance, deployment, commercial release, engine license decision, changing code issue #60 or any other of 80 coding WOs. No second clock/ECS/scene system and no paid CI or human review dependency.

## FILES / SOURCES TO READ (canonical order)
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` / approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md`, `docs/product/module-catalog.md`, `docs/queue/implementation-registry.json` and `docs/queue/work-orders/GAME-04.md`.
Required integration: `docs/architecture/game-01-input-control-mapping.md`, `docs/contracts/game-01-input-actions-api.md`, `docs/architecture/game-02-gameplay-scripting-api.md`, `docs/contracts/game-02-gameplay-scripting-api.md`, `docs/architecture/world-02-scene-prefab-hierarchy.md`, `docs/contracts/world-02-scene-prefab-api.md`, `docs/architecture/data-04-serialization-scene-format.md`, `docs/contracts/data-04-scene-api.md` and NET-01..06 catalog plans. Official external references and licenses in matrix.

## REQUIREMENTS
GOV-001..005, CAP-004, CAP-007/008/010/011/012/013/015/016, NFR-001..005, NLE-D002/003/004/005/009/013..020. Engine license NLE-D009 remains OPEN. All architecture/technology hypotheses PROPOSED. Support planned native OS and Web targets without claiming tested availability.

## ARCHITECTURE RULES
GAME-04 alone owns semantic game event queue and rules/ability/quest/game-state validation. CORE-04 TickId, CORE-03 scheduler, WORLD-01 ECS/commit, WORLD-02 hierarchy, GAME-01 actions, GAME-02 sandbox, DATA-02/04/05 stable IDs/CAS/cook, NET-02 authoritative server and NET-03/04 replication/prediction stay in their domains. Three lanes: authoritative bounded deferred tick events, cosmetic non-authoritative cues and transactional editor/authoring events. No hidden reentrant mutation. Deterministic canonical envelope/phase/sequence comparator with explicit world epoch, rejection/backpressure receipts, sanitized traces and generational subscriptions. Ability cost and cooldown commit atomically; damage/status bounded; inventory/quest rewards idempotent; save hook distinguishes staged/durable/activated, recovery/migrations; network never trusts clients.

## CONSTRAINTS
No new code/runtime/security claims; no adoption from an ADR PROPOSED; respect public-repository solo governance, no force push, no protection bypass, no CodeRabbit, no paid CI. No direct engine public API bound to library RTTI/EnTT/Flecs. Maintain Context Lock; if checkpoint/Scope/DoD/approved architecture changes mark STALE and rebase/research again.

## ACCEPTANCE CRITERIA
- [ ] Exactly 8 correct Markdown docs, links and official sources/notice matrix, no code, SDK or undocumented dependencies.
- [ ] ADR-0045 PROPOSED, explicit EnTT/Flecs/owned queue + Unreal/Unity/Godot comparisons and licensing constraints; no dependency adopted.
- [ ] Typed versioned event/command/state/scene/ability/damage/status/inventory/quest/save/NET contracts, ownership and fail-closed budget/replay rules.
- [ ] State that GAME-01/02/WORLD-02 are **only proposals**, NET/data integrations are not engine-ready; no duplicate authority.
- [ ] Exactly 128 IDs G04-T001..T128, all FUTURE/NOT EXECUTED and benchmark plan with p50/p95/p99, native OS/Web, deterministic same-target replay and no invented results.
- [ ] Research PR exact-final-HEAD Docs Validation SUCCESS + audit pt-BR APPROVED + normal squash/main readback, no HIGH/CRITICAL.
- [ ] Separate checkpoint PR exact-final-HEAD Docs Validation SUCCESS + audit pt-BR APPROVED + normal squash/main readback, exactly 1 registry delta (GAME-04 research status only).
- [ ] Final registry 42/80 documented, 38 pending, zero runtime; all 80 `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`; #60 OPEN/BLOCKED; #220 close only after checkpoint readback.

## TESTS
Only `Docs Validation` GitHub Actions, link/taxonomy/DAG/registry validator and read-only Zcode blocked-selector validation are actual research checks. The **128 gameplay tests are FUTURE/NOT EXECUTED**; no compiler, sanitizer, benchmark, scripted replay or multiplayer simulation to run in P00.

## DELIVERABLES
Eight Markdown research docs, GitHub issue #220, scoped research PR and documented CI/audit/squash/main readback, separate checkpoint PR and Evidence Bundle. Not executable implementation.

## REVIEW FORMAT
pt-BR verdict **APPROVED / CORRECTION REQUIRED / BLOCKED**; exact base/final SHA, eight paths/diff, source fingerprints, licensing/architecture/permissions/NET/save recovery, 128 tests NOT RUN, measured actual Docs Validation run/job, high/critical list, risks, rollback and **proposed** registry delta. Failures corrected in same WO/PR, no next increment before readback.

## STOP CONDITION
Any stale base/source, missing source license, failing Docs Validation, unsafe event authorization, invented test/performance proof, unexpected registry/code changes, HIGH/CRITICAL known issue or non-mergeable PR => CORRECTION REQUIRED / BLOCKED. Do not unlock or modify any coding packet.

## CONTEXT LOCK (Git blob SHA at initial base, not SHA-256)
BASE `b64194591d761cd3e785337b10a524d085ec04d1`. Checkpoint `00b761597da9d10970f03548ca147a7b40b5661f`; Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; Backlog `276e80cc8615bbc565cb96e6bb76cff5717deb08`; Catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; Registry `5ee7215c16f7b26d62c74a857a7f29787ae2857e`; code draft GAME-04 `4c359f8dcc4c9d40a9f0a4f5aaf1123342fcfa82`; AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`; GAME-01 arch `5f86d817a26a7142496788963453caf247dbfa50` and API `cc2598fe117ae4a60d7746028df084d7be229426`; GAME-02 arch `c5429cabdf14bc1e7dc8b3eac11e77274dc51776` and API `3dd5ad89e25e7fd39779eded236f26ab2d4a282b`; WORLD-02 arch `e04b640df6e3741d324c33d5dd9735696ed69d98` and API `c98ea5d49e3b792057c1d14706b9e2f4cfca9550`; DATA-04 arch `7e88d4fecaa83c9922f255087df9f97f6300b61f` and API `33b096149df35d20b3fe9e9d21e4bc6f22d71d5c`. Re-verify all critical changes before merge.

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-GAME-04.md). Initial state: no CI, no runtime tests, checkpoint not yet updated; source of truth is final GitHub CI/PR evidence, not this draft.


## Research PR APPROVED; separate checkpoint reconciliation (evidence as of 2026-11-15)
- Research [PR #221](https://github.com/KayzenRoot/stormline/pull/221) final HEAD `4ee8839c93f5e1782993f40178a8f71b2321073d` from base `b64194591d761cd3e785337b10a524d085ec04d1`: exactly eight added docs; [Docs Validation run #43706155959](https://github.com/KayzenRoot/stormline/actions/runs/43706155959) SUCCESS, job #132787563990 (links, DAG, registry, Zcode selector) and [objective pt-BR audit #6893260379](https://github.com/KayzenRoot/stormline/pull/221#issuecomment-6893260379) APPROVED documentary-only, normal squash/readback main `a85b49b184354a3aa7d1420a40dbfd78cec5f309`.
- This **separate** checkpoint PR from main `a85b49b184354a3aa7d1420a40dbfd78cec5f309` updates only checkpoint, backlog, **single registry field for GAME-04 research_status**, this WO and Evidence Bundle. Research 42/80, pending 38/80, runtime 0/80; ALL 80 coding packets blocked and #60 remains OPEN/BLOCKED. Checkpoint CI/audit/merge/readback pending at document write time, no fabricated success. Repo Source Pack base fingerprints in initial Context Lock unchanged apart from explicit this PR files. Next GAME-05 is documentation only after checkpoint approval.
