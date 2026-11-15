# AI-08 — Exactly 128 Future Agent Authoring Workflow Acceptance Tests

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | [research #309](https://github.com/KayzenRoot/stormline/issues/309) | NLE-P00-WO-002-AI-08 | [future code #82](https://github.com/KayzenRoot/stormline/issues/82) OPEN/BLOCKED | BASE `55250c21f834067524014bdb70eedcdddbf6949e`.** Formal deps AI-05 + AI-07 only; ADR-0067 PROPOSED; 63/80 research at baseline; 80/80 future code packets BLOCKED; engine false, NLE-D009 license OPEN.

**128 unique A08-T001..A08-T128 tests, eight groups of sixteen, all FUTURE / NOT EXECUTED. 0 executable tests, 0 PASS, 0 FAIL.** This matrix is a future specification, not code or a claim that a game engine, workflow service, renderer, AI agent, SDK or export exists.

## Mandatory independent test oracles
1. Pin actual Source Pack/owner command/schema versions, AI-05 context source owner revision+rights, AI-07 plan and receipt, AI-06 policy/consent epoch (transitive), target OS/arch/Web profile, recipe ID/version, seed and fixture digest. No self-scored AI output as oracle.
2. Use entirely **synthetic rights-cleared** assets, material graphs, scripts, localization, sounds and prefabs. Independent owner source reopen plus scene graph, media and license manifests; no proprietary game references.
3. For negative tests require zero unauthorized filesystem/network/owner effects, not merely an error string. A skipped owner capability must yield UNSUPPORTED and cannot count toward a complete workflow.
4. A qualified "complete" means all recipe-declared **mandatory** nodes produce valid typed owner receipts, source readback, applicable shader/script/VFX/audio/UI validations and actual target cook/export output when requested. Partial or pending stages are nonterminal.
5. "Zero manual editing" means 0 human operations placing/editing authored scene elements; trusted consent/refusal and human task selection are separately recorded and do **not** require eliminating user control.
6. Compare *pinned deterministic* offline recipe runs against independent semantic source digest, not just textual similarity; LLM/image/audio output repeatability requires captured immutable output bytes and rights, never seed alone.
7. Model-generated content, untrusted tool metadata and imported prompt injections cannot directly execute shell/network or approve any operation. AI-05+AI-07 owner boundaries are independent.
8. Future source/host/cook tests require real Windows/Linux/macOS/Web where supported, official MCP 2026-07-28 conformance and pinned Codex/Claude versions, not merely documentation CI.

## Eight balanced groups
| Group | IDs | Count | Area |
|---|---|---:|---|
| RECIPE-CAPABILITY | A08-T001..A08-T016 | 16 | typed DAG, versions, model neutrality, capability gating |
| CONTEXT-SECURITY | A08-T017..A08-T032 | 16 | AI-05 privacy, source freshness, hostile context |
| 2D-3D-SCENE | A08-T033..A08-T048 | 16 | owner scene/asset/UI/prefab source integrity |
| MATERIAL-VFX-AUDIO | A08-T049..A08-T064 | 16 | typed shader/VFX/audio graphs and rights |
| SCRIPT-BEHAVIOR-UI | A08-T065..A08-T080 | 16 | gameplay API sandbox, localization/accessibility |
| TRANSACTION-CONSENT-RECOVERY | A08-T081..A08-T096 | 16 | AI-07 owner CAS/undo/partial and AI-06 consent |
| EXPORT-PROVENANCE-TARGET | A08-T097..A08-T112 | 16 | source/cook/target rights and package readback |
| E2E-QUALITY-PERF | A08-T113..A08-T128 | 16 | three complete fixtures, host proof and benchmark |

## Complete future scenario matrix
| Test ID | Group | Scenario / assertion | Required independent evidence | Status |
|---|---|---|---|---|
| A08-T001 | RECIPE-CAPABILITY | Recipe list shows only user-selected project-authorized manifests and versions | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T002 | RECIPE-CAPABILITY | Untrusted recipe publisher not allowlisted cannot register executable recipe | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T003 | RECIPE-CAPABILITY | Recipe schema rejects unknown mandatory version and incompatible required fields | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T004 | RECIPE-CAPABILITY | Recipe input validates typed units coordinate frame numeric ranges and locale | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T005 | RECIPE-CAPABILITY | Recipe DAG rejects cycle before any owner dispatch or source mutation | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T006 | RECIPE-CAPABILITY | Duplicate operation node IDs fail deterministic schema validation | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T007 | RECIPE-CAPABILITY | Bounded maximum steps depth fanout and graph edges prevents recursive loops | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T008 | RECIPE-CAPABILITY | Recipe output roles are checked against target owner capability signatures | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T009 | RECIPE-CAPABILITY | Missing mandatory source owner returns UNSUPPORTED not fabricated completion | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T010 | RECIPE-CAPABILITY | Optional step skip requires declared optional semantics and receipt | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T011 | RECIPE-CAPABILITY | Opaque ProjectId/AssetId references resolve only through canonical owners | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T012 | RECIPE-CAPABILITY | Same recipe version seed context and owner profiles yields same typed plan hash | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T013 | RECIPE-CAPABILITY | New incompatible recipe semver requires explicit migration or rejection | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T014 | RECIPE-CAPABILITY | Unknown target platform extension or codec fails safe before export | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T015 | RECIPE-CAPABILITY | Unsigned plan input changes are detected by canonical digest mismatch | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T016 | RECIPE-CAPABILITY | Offline static recipe path requires no mandatory cloud LLM provider | signed recipe manifest + schema/capability registry + no-owner-call trace | FUTURE / NOT EXECUTED |
| A08-T017 | CONTEXT-SECURITY | AI-05 ContextCapsule source citation binds exact owner revision and digest | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T018 | CONTEXT-SECURITY | AI-05 context listing never enumerates hidden project source names | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T019 | CONTEXT-SECURITY | Context budget clips at safe section boundaries with explicit partial receipt | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T020 | CONTEXT-SECURITY | Resource URI cannot become arbitrary filesystem or external network fetch | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T021 | CONTEXT-SECURITY | Changed source revision between pin and plan returns CONTEXT_STALE | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T022 | CONTEXT-SECURITY | Revoked actor grant between pin and use blocks subsequent hydration | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T023 | CONTEXT-SECURITY | AI-05 policy epoch changed invalidates workflow context cursor | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T024 | CONTEXT-SECURITY | Recipe title and imported document prompt injection remains inert data | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T025 | CONTEXT-SECURITY | Injected tool annotations cannot expand declared owner command capabilities | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T026 | CONTEXT-SECURITY | Cross-project AssetId reference without approved owner scope is rejected | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T027 | CONTEXT-SECURITY | Secret in linked source metadata is redacted before plan transcript | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T028 | CONTEXT-SECURITY | Untrusted instructions in localization string cannot call shell or export | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T029 | CONTEXT-SECURITY | Long imported document with token-amplification attack respects budget | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T030 | CONTEXT-SECURITY | Rights-restricted audio/font/texture cannot be silently copied to export | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T031 | CONTEXT-SECURITY | Source asset licensing provenance is retained in derived recipe output | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T032 | CONTEXT-SECURITY | Input context failure never downgrades to dumping entire repository | AI-05 owner revision+ACL oracle + redacted source/traffic proof | FUTURE / NOT EXECUTED |
| A08-T033 | 2D-3D-SCENE | 2D scene recipe emits typed SceneIR with stable scene/node/asset IDs | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T034 | 2D-3D-SCENE | 2D tilemap atlas layer parallax references are owner-validated | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T035 | 2D-3D-SCENE | 2D collision shapes obey owner unit and coordinate rules | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T036 | 2D-3D-SCENE | 2D camera and responsive viewport constraints receive semantic owner proof | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T037 | 2D-3D-SCENE | 2D animation keyframes and UI bindings form valid referenced graph | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T038 | 2D-3D-SCENE | 2D complete fixture needs zero manual editor placement actions | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T039 | 2D-3D-SCENE | 3D scene recipe emits typed transform hierarchy without ID collisions | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T040 | 2D-3D-SCENE | 3D prefab/variant override ancestry is preserved by semantic owner operations | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T041 | 2D-3D-SCENE | 3D lighting owner values obey units target and limits | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T042 | 2D-3D-SCENE | 3D mesh/material references remain stable after owner asset rename | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T043 | 2D-3D-SCENE | 3D physics/animation/script dependencies are ordered and supported | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T044 | 2D-3D-SCENE | OpenUSD layer/variant import is not trusted as native authoring authority | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T045 | 2D-3D-SCENE | glTF required unknown extension produces explicit UNSUPPORTED | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T046 | 2D-3D-SCENE | Scene owner readback equals predicted semantic fingerprint | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T047 | 2D-3D-SCENE | Runtime renderer generation distinct from committed source is reported | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T048 | 2D-3D-SCENE | 3D complete fixture needs zero manual editor scene placement actions | canonical DATA-04/WORLD source reopen + stable-ID graph + manual-edit counter | FUTURE / NOT EXECUTED |
| A08-T049 | MATERIAL-VFX-AUDIO | Material graph connects only owner-declared typed compatible sockets | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T050 | MATERIAL-VFX-AUDIO | Material shader graph rejects cycle or incompatible shader model | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T051 | MATERIAL-VFX-AUDIO | Material color space and PBR parameter ranges are validated | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T052 | MATERIAL-VFX-AUDIO | MaterialX unsupported node returns typed failure not fake shader compile | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T053 | MATERIAL-VFX-AUDIO | Shader compile owner receipt required before declaring compiled output | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T054 | MATERIAL-VFX-AUDIO | VFX emitter/event graph bounds particle count and time budgets | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T055 | MATERIAL-VFX-AUDIO | VFX GPU unsupported target returns UNSUPPORTED without host execution | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T056 | MATERIAL-VFX-AUDIO | VFX deterministic owner fixture matches pinned seed and simulation profile | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T057 | MATERIAL-VFX-AUDIO | Audio event graph references rights-cleared sound source AssetIds | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T058 | MATERIAL-VFX-AUDIO | Audio buses and distance attenuation preserve correct unit normalization | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T059 | MATERIAL-VFX-AUDIO | Missing audio source cannot be replaced with unlicensed sample fetch | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T060 | MATERIAL-VFX-AUDIO | Audio accessibility caption or cue metadata is validated when required | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T061 | MATERIAL-VFX-AUDIO | External media references in OTIO do not imply embedded playable audio | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T062 | MATERIAL-VFX-AUDIO | Material texture substitution preserves original owner rights and notice | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T063 | MATERIAL-VFX-AUDIO | VFX and audio optional steps cannot hide required scenario content | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T064 | MATERIAL-VFX-AUDIO | Shader VFX audio source and derived receipts remain independently traceable | GFX/VFX/AUDIO typed owner receipts + validation and license asset evidence | FUTURE / NOT EXECUTED |
| A08-T065 | SCRIPT-BEHAVIOR-UI | Gameplay script recipe uses approved GAME-02 sandboxed API and language version | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T066 | SCRIPT-BEHAVIOR-UI | Generated script cannot read filesystem or contact network without grant | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T067 | SCRIPT-BEHAVIOR-UI | Script syntax/lint/build compile receipt is required if owner capability exists | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T068 | SCRIPT-BEHAVIOR-UI | Behavior state machine rejects unbounded recursive transition graph | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T069 | SCRIPT-BEHAVIOR-UI | Behavior event binding targets stable actual scene component IDs | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T070 | SCRIPT-BEHAVIOR-UI | Script and behavior loop execution respects per-frame budget | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T071 | SCRIPT-BEHAVIOR-UI | Game UI responsive anchors constraints remain owner-valid | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T072 | SCRIPT-BEHAVIOR-UI | HUD labels preserve Unicode normalization and line break semantics | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T073 | SCRIPT-BEHAVIOR-UI | RTL and CJK font shaping fallback is verified by target owner | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T074 | SCRIPT-BEHAVIOR-UI | Gamepad keyboard mouse touch focus navigation graph is complete when required | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T075 | SCRIPT-BEHAVIOR-UI | Localization keys missing locale receive explicit fallback or validation error | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T076 | SCRIPT-BEHAVIOR-UI | Generated HUD text contrast and scaling checks have independent oracle | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T077 | SCRIPT-BEHAVIOR-UI | Accessible reduced-motion alternative is present for high-flash VFX fixture | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T078 | SCRIPT-BEHAVIOR-UI | License and redistribution rights attached to imported font are preserved | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T079 | SCRIPT-BEHAVIOR-UI | UI and behavior authoring cannot execute unreviewed template Javascript | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T080 | SCRIPT-BEHAVIOR-UI | Script UI behavior complete fixture produces actual owner receipts | GAME/EDIT/UI owner compile and accessibility fixtures + no-exec trace | FUTURE / NOT EXECUTED |
| A08-T081 | TRANSACTION-CONSENT-RECOVERY | Workflow plan compiles only to AI-07 typed ChangeSet with owner CommandIds | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T082 | TRANSACTION-CONSENT-RECOVERY | Workflow preview has zero canonical source/filesystem/external side effects | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T083 | TRANSACTION-CONSENT-RECOVERY | Plan includes complete semantic diff and explicit irreversible step classes | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T084 | TRANSACTION-CONSENT-RECOVERY | AI-06 one-use trusted UI consent is required for risk-classified export | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T085 | TRANSACTION-CONSENT-RECOVERY | MRTR input_required response never satisfies trusted mutation approval | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T086 | TRANSACTION-CONSENT-RECOVERY | Changed source revision after plan makes consent stale and denies commit | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T087 | TRANSACTION-CONSENT-RECOVERY | Changed tool args destination or project invalidates plan approval | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T088 | TRANSACTION-CONSENT-RECOVERY | Revoked grant during apply blocks next owner effect with truthful partial | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T089 | TRANSACTION-CONSENT-RECOVERY | AI-07 owner CAS conflict returns typed CONFLICT never last-write-wins | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T090 | TRANSACTION-CONSENT-RECOVERY | Duplicated workflow request idempotency key returns same owner receipt | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T091 | TRANSACTION-CONSENT-RECOVERY | Retry different payload with reused key produces idempotency conflict | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T092 | TRANSACTION-CONSENT-RECOVERY | Crash after first owner commit before second yields explicit PARTIAL_COMMIT | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T093 | TRANSACTION-CONSENT-RECOVERY | Resume inspects durable AI-07 journal and actual owner state before retry | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T094 | TRANSACTION-CONSENT-RECOVERY | Cancelled external publish reports already committed irreversible effects | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T095 | TRANSACTION-CONSENT-RECOVERY | Undo of workflow uses new authorized AI-07 inverse and preserves unrelated edits | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T096 | TRANSACTION-CONSENT-RECOVERY | Source commit succeeds but export fails reports EXPORT_PENDING not COMPLETE | AI-07 source/journal receipts + AI-06 approval + OS filesystem sentinel | FUTURE / NOT EXECUTED |
| A08-T097 | EXPORT-PROVENANCE-TARGET | Windows x64 target capability profile rejects unsupported codec or extension | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T098 | EXPORT-PROVENANCE-TARGET | Linux x64 export uses separately validated target owner packager receipt | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T099 | EXPORT-PROVENANCE-TARGET | macOS Apple Silicon export requires compatible signing/profile owner capability | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T100 | EXPORT-PROVENANCE-TARGET | Web target rejects unsupported native-only shader or script module | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T101 | EXPORT-PROVENANCE-TARGET | DATA-05 cook output is derived and not equal to source authoring commit | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T102 | EXPORT-PROVENANCE-TARGET | Export manifest includes versioned scene assets dependencies and licenses | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T103 | EXPORT-PROVENANCE-TARGET | glTF importer/exporter respects extensionsRequired and source integrity | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T104 | EXPORT-PROVENANCE-TARGET | Unknown external binary payload hash or rights fails target validation | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T105 | EXPORT-PROVENANCE-TARGET | External upload needs separate destination-specific trusted consent | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T106 | EXPORT-PROVENANCE-TARGET | Destination URL cannot be mutated by untrusted recipe field | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T107 | EXPORT-PROVENANCE-TARGET | Export from wrong ProjectId denied before any file or network effect | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T108 | EXPORT-PROVENANCE-TARGET | Asset font media licenses and required notices survive packaging step | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T109 | EXPORT-PROVENANCE-TARGET | Cook failure preserves committed source and returns truthful partial state | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T110 | EXPORT-PROVENANCE-TARGET | Reproducibility receipt pins actual media bytes not merely prompt seed | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T111 | EXPORT-PROVENANCE-TARGET | Same rights-cleared fixture export reopens manifest and validates digests | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T112 | EXPORT-PROVENANCE-TARGET | Owner readback proves actual output package exists before COMPLETE | target DATA-05 cook/package reopen + source/rights/owner manifest | FUTURE / NOT EXECUTED |
| A08-T113 | E2E-QUALITY-PERF | Full rights-cleared 2D game fixture generated by authorized tool calls without manual scene editing | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T114 | E2E-QUALITY-PERF | Full rights-cleared 3D fixture generated by authorized tool calls without manual scene editing | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T115 | E2E-QUALITY-PERF | Supported end-to-end exported fixture has actual source and cook package receipt | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T116 | E2E-QUALITY-PERF | Human trusted approval counted separately from manual editor modifications | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T117 | E2E-QUALITY-PERF | Required script audio material VFX UI step omission makes workflow not complete | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T118 | E2E-QUALITY-PERF | Model-free offline deterministic baseline runs without paid provider | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T119 | E2E-QUALITY-PERF | Optional model planner output passes same typed owner contract and validator | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T120 | E2E-QUALITY-PERF | Prompt injection adversarial fixture causes zero unauthorized tool effects | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T121 | E2E-QUALITY-PERF | Concurrent 32 agents remain scoped with no lost scene updates | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T122 | E2E-QUALITY-PERF | Restart at each graph stage reconciles owner progress without duplicate writes | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T123 | E2E-QUALITY-PERF | Pinned Codex host workflow uses advertised MCP capabilities only | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T124 | E2E-QUALITY-PERF | Pinned Claude host workflow uses advertised MCP capabilities only | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T125 | E2E-QUALITY-PERF | Optional Tasks-disabled SDK performs bounded supported work or returns UNSUPPORTED | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T126 | E2E-QUALITY-PERF | Owner quality gates evaluate accessibility behavior source graph and target compatibility | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T127 | E2E-QUALITY-PERF | Cold/warm p50 p95 p99 and rights-equal context/tool budgets recorded reproducibly | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |
| A08-T128 | E2E-QUALITY-PERF | Evidence bundle pins Git source model recipe owner OS host SDK SBOM and output rights | independent source/target ground truth + host/OS versions + bounded metric traces | FUTURE / NOT EXECUTED |

## Future security and capability gate
- All 128 cases designed above are **NOT EXECUTED** in P00; future implementation must report support/skip as UNSUPPORTED rather than PASS. No unimplemented owner can satisfy a complete 2D/3D scenario.
- Exactly THREE end-to-end future demonstrations include 2D, 3D and platform export with independent owner readback and zero manual scene editing. If export requires user approval it remains a required separate trusted consent.
- Zero known HIGH/CRITICAL unauthorized project write, prompt-to-shell, data exfiltration, unlicensed media, stale consent, lost update or silent partial/export false-success.
- Platform owner and real host versions verified at exact commits with measured targets; actual performance thresholds and licenses approved separately. ADR-0067 still PROPOSED; no code authorization.

[Architecture](../architecture/ai-08-authoring-workflows.md) · [Contracts](../contracts/ai-08-authoring-workflow-api.md) · [Benchmarks](../research/ai-08-authoring-benchmark-protocol.md).
