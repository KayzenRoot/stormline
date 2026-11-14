# ADR-0035 — Engine-Owned Navigation, Tiled World Validity and Bounded Agent Decisions

**STATUS: PROPOSED / NOT APPROVED FOR CODE**  
**Date:** 2026-11-14 | Research #186 | WO NLE-P00-WO-002-SIM-05 | Future coding #50 OPEN/BLOCKED.

## Context
SIM-05 must supply navigation and NPC decisions for moving worlds while WORLD-03 owns cells, SIM-02 collision authority, SIM-03 actual character motion, GAME/NET actual combat/client authority and CORE-04 tick. Third-party Recast/Detour and BehaviorTree.CPP can accelerate specialized algorithms but should not own Stormline public schema or permission policy. An outdated tile can look reachable after unloading a collision mesh; an AI graph may flood motion queues or leak hidden opponent data. P00 docs are the only authorized current activity.

## Proposed decisions
1. **Owner and replaceability:** Stormline owns NavWorld/Tile/Agent/Path/Query/BehaviorGraph/Blackboard/Perception semantically versioned contracts, generational handles and typed receipts; vendor C++ references and internal allocators remain private. All SDK/license decisions remain pending.
2. **World authority:** WORLD-03 cell residency/leases and SIM-02 collider source readiness gate nav tile activation; tile and topology epochs and source revision must match for a path or agent route to be authoritative. Partial coverage returns NAV_PENDING/PATH_PARTIAL, never ground success.
3. **Algorithm:** tiled Recast build + Detour runtime are **leading candidates**, not adopted; DetourTileCache for selected obstacle/tile updates and DetourCrowd for planar crowd steering require real evaluation and explicit dynamic-world limits. 2D navigation has an independent grid/polygon candidate policy, not forced into Recast 3D.
4. **No movement authority:** global path/crowd outputs propose desired velocity and link intents for SIM-03; only SIM-03/PHYS/GAME accept and publish actual actions. Failed/blocked move receipt triggers bounded replan and explicit failure, not teleport.
5. **Behavior owner:** Stormline declarative versioned BT/statechart and typed blackboard, with bounded graph, tick, action count, loops, async lifecycle and explicit queues; BehaviorTree.CPP MIT and Boost::ext.SML BSL-1.0 are comparators, neither unqualified production selection. Editor authoring via DATA-04 shared kernel, not vendor GUI runtime. Script/plugin nodes disabled by default unless separately approved.
6. **Perception and authority:** WORLD candidate query + SIM-02 line-of-sight and GAME/AUDIO stimuli build **incomplete-able** observations; no client-visible hidden-agent blackboard data; AI actor and NET roles govern intents. Unknown/corrupt/streaming terrain leads to conservative vision/path completeness and behavior fallbacks.
7. **Fixed tick replay:** CORE-04 owns TickId and time debt, snapshots/logs/stable order; asynchronous requests bind WorldEpoch/TopologyEpoch/AgentGeneration and cancel/revalidate on completion. Cross-platform bit-exact replay requires future measured proof.
8. **Security/performance:** strict quota for nav tiles, polygon vertices, A* nodes, path queue, agent count, avoidance neighbors, BT cycles/depth, event emission and perceptual rays. Future ASan/UBSan/TSan/fuzz, P95/P99 and stress evidence; no automatic GPU or cloud inference requirement.

## Rejected
- Publishing raw Detour poly refs, BT.CPP pointers, an XML parser or a new state engine as Stormline ABI.
- Assuming global 3D tile navigation solves 2D platformer ladders/flying agents without specific domain constraints.
- Treating dynamic obstacle avoidance as physical collision validation or tile cache as instantaneous arbitrary terrain rebuild.
- Direct world transforms, physics mutation or damage from AI/LLM outputs; open-ended untrusted code or privileged MCP execution.
- Mandating proprietary paid behavior editor or remote NPC inference without owner scope, budget and security approval.

## Consequences and gates
Extra versioned adapters, tile publication barriers, staged task acknowledgments and typed errors impose implementation cost but preserve safety, headless operation and replaceable algorithms. Proposed A*/off-mesh/streaming complexity must be proven under large world tests. **No backend selected, licenses/tags pinned, code built, runtime benchmark or visual/AI behavior test executed.** Release class UNDECIDED; #50 and all implementation WOs remain BLOCKED and executor_ready=false. Reconsider ADR only after approved upstream code/contract prerequisites, explicit NECESSARY slice, security/license/ABI review, target budget/rollback and test evidence.
