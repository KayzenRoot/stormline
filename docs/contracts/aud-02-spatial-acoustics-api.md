# AUD-02 — Spatial Audio, Acoustic Geometry and Perceptual Rendering Semantic API v0.1

**P00 PROPOSED CONTRACT ONLY** | Research #198 | WO NLE-P00-WO-002-AUD-02 | Future code #53 OPEN/BLOCKED. Not a compiled ABI, wire schema, shipped HRTF data or authorized engine interface.

## Typed versioned contracts
| Type | Candidate fields | Owner + validation |
|---|---|---|
| `AcousticWorldHandleV1` | ProjectId, WorldId, SceneRevision, AcousticWorldEpoch, OriginEpoch | WORLD-02 scene/CAS, WORLD-03 leases and CORE-05 precision; reject reused world |
| `AcousticListenerHandleV1` | EntityGuid+generation, WorldId, pose/orientation/velocity, head orientation permission, output layout, listener role | WORLD/GAME listener authorization, finite orthonormal CORE-05 transform |
| `SpatialSourceHandleV1` | Entity/AudioVoiceHandle+generation, source AssetId, acoustic domain, directivity profile, role privacy scope, source transform revision | AUD-01 owns physical voice and its generational retirement, GAME/NET owns visibility role |
| `AcousticSurfaceV1` | WORLD-02 source, stable SurfaceGuid/revision, cooked mesh/proxy hash, frequency-band material absorption/transmission/scatter, thickness proxy | DATA-03/05 validated source, [0,1] coefficient bounds, no mesh pointer sharing |
| `AcousticMaterialProfileV1` | material AssetId/revision, bands, reflect/transmit/absorb fractions, source caveats and procedural updates | finite bounded response, do not assert full physically accurate wave model |
| `AcousticRoomV1` | RoomGuid, World/Cell, volume/hull/source revision, impulse-response/probe AssetId, transition priority, listener zone | WORLD-02 source, derived acoustic RoomIndex, no second ECS ownership |
| `AcousticPortalV1` | PortalGuid, RoomA/RoomB, opening fraction, source door generation, material/area/path loss, topology epoch | WORLD-02/03 source and SIM-06 geometry/destruction gated; no unverified passage |
| `AcousticGeometrySnapshotV1` | WorldEpoch, Cell leases, OriginEpoch, source scene/terrain/physics revisions, bounded geometry/proxies, coverage set | WORLD-02/03 immutable CPU off-RT source, cannot claim unknown world empty |
| `SOFAHrtfProfileV1` | HRTF AssetId/hash/provenance/rights, SOFA convention, source/listener axes and measurement count, sample rate, receiver channels, consent flag | DATA-03 importer sandbox, headset output/user HRTF privacy, no unauthorized redistribution |
| `SpatializationProfileV1` | tier (PAN/HEADPHONE_HRTF/OCCLUSION/REFLECTION/PROPAGATION), listener output layout, atten/directivity curves, Doppler cap, budget | stable typed mode with capability and actual readiness, no forced binaural on speakers |
| `AcousticCookManifestV1` | source cell geometry/material/portal revision, toolchain/recipe version, IR/probe/path bake hash, size, frequency and target capability | DATA-05 immutable validated cook, no proprietary HRTF included without rights |
| `AcousticQueryIntentV1` | World+Source+Listener handles, TickId, geometry epoch, requested bands/occlusion/ray count and deadline, actor role | non-RT CORE-03 queue, quotas, source privacy and freshness check |
| `AcousticQueryReceiptV1` | source/listener revision, World/Cell/Origin epoch, observed occlusion/transmission bands, path/reflection distance, coverage/uncertainty, source tick and result code | only accepted scene-snapshot ray/probe result, `UNREADY` never clear LOS |
| `AcousticRoomResponseV1` | room/portal graph hash, early delay/energy taps, late decay/IR ID, wet/dry send plan, source/target epoch, revision | derived, finite and budgeted; AUD-03 generic DSP may realize late reverb |
| `AcousticRenderPlanV1` | source listener/voice and DeviceEpoch, audio frame window, direction, gain/pan or validated HRTF filter ID, doppler pitch, occlusion bands, room sends, readiness/fallback | precomputed immutable plan consumed by AUD-01 bounded RT stage; no ray/file/alloc during callback |
| `AcousticCapabilitiesV1` | native/Web/headless, headphone/speaker, HRTF/SOFA/reflect/path, CPU/GPU mode, actual limits, dynamic geometry support | measured capabilities only, no universal Web/GPU promise |
| `AcousticEventReceiptV1` | EventId, TickId, World/Acoustic/DeviceEpoch, source/listener IDs, applied vs requested tier, stale/rejected/fallback reason | paginated role-redacted diagnostics, no hidden enemy position leak |
| `AcousticErrorV1` | typed error, source/timestamp, last safe plan, input revision, remediation/no private asset bytes | distinguish unloaded vs empty geometry, wrong rights vs unsupported tier |

## Semantic operations and state machine
1. `StageAcousticScene(profile, expectedWorldRevision, principal)`: common Editor/CLI/MCP authenticated authoring with DATA-04 revision CAS, source/right check and dry-run; no raw mesh or OS input privileged writes.
2. `RegisterListener(world, entity, outputProfile, principal)`: verify listener EntityGuid+generation and GAME role, CORE-05 transform, AUD-01 output device capabilities; revoke on despawn/seat transfer.
3. `AttachSpatialSource(world, AudioVoiceHandle, entity, directivity, expectedRevision)`: validate AUD-01 voice generation, WORLD-02 source, privacy authority, no duplication of voice/mix or secret gameplay producer.
4. `StageAcousticGeometry(snapshot, expectedSceneRevision)`: WORLD-02/03/04 source with Cell lease, coordinate frame, material coverage and immutable geometry/probe proxy; no ray trace on callback.
5. `StageSOFAImport(fileAsset, expectedAssetRevision, principal)`: DATA-03 security/provenance rights, SOFA convention/axes/channels/direction/rate/size; never unsafe HDF5 parsing in audio thread.
6. `SubmitSpatialQuery(intent, boundedDeadline)`: non-RT CORE-03 ray/probe/path job, dedup, generation and CPU quota; `PENDING` if cell missing/geometry stale rather than false clear route.
7. `SampleAcousticRoomAndPortal(world, listener, source, queryReceipt)`: derive room transmission, early/late response based on matching revisions and path constraints.
8. `PublishAcousticRenderPlanAtAudioBoundary(plan, expectedVoiceAndDeviceEpoch)`: install immutable bounded HRTF/pan/occlusion/reverb send settings for AUD-01. Previous buffers retired after callback fence, no allocation/lock/IO/scene query in RT.
9. `ReadSpatialVoiceState(source, listener, principal, cursor)`: authorized paged summary including applied tier, source age, unknown/occluded state, privacy filters, no serialized HRTF raw personal data.
10. `StageAcousticBake(recipe, expectedSourceHash, principal)`: DATA-05 cooks legal verified scene IR/probe/path assets from DATA-03 importer under bounded CLI/editor workers; no direct sandbox bypass.
11. `NotifyAcousticTopologyChanged(WorldEpoch, ChangedCellSet, SourceRevision)`: WORLD-03/04/SIM-06 invalidates stale geometry/IR and cancels old jobs, stages fallback before new plan publish.
12. `DetachSpatialSource/Listener(handle)`: mark inactive, revoke generation, defer HRTF/filter/room/scene frees through AUD-01 callback epoch and WORLD-03 leases, release correctly on shutdown.

## Error catalog
`UNAUTHORIZED_SPATIAL_SOURCE`, `LISTENER_ROLE_DENIED`, `STALE_LISTENER`, `STALE_SPATIAL_SOURCE`, `STALE_VOICE_HANDLE`, `STALE_WORLD_EPOCH`, `STALE_ORIGIN_EPOCH`, `GEOMETRY_UNREADY`, `CELL_NOT_RESIDENT`, `MATERIAL_REVISION_MISMATCH`, `ROOM_GRAPH_CONFLICT`, `PORTAL_TOPOLOGY_STALE`, `AMBISONIC_LAYOUT_INVALID`, `SOFA_CONVENTION_UNSUPPORTED`, `HRTF_RIGHTS_REQUIRED`, `PERSONAL_HRTF_CONSENT_REQUIRED`, `HRTF_DATA_TOO_LARGE`, `IR_BUDGET_EXCEEDED`, `SOURCE_DIRECTION_INVALID`, `RAY_BUDGET_EXCEEDED`, `ACOUSTIC_JOB_TIMEOUT`, `QUERY_CANCELED`, `OUTPUT_MODE_UNSUPPORTED`, `DEVICE_EPOCH_CHANGED`, `LATENCY_LIMIT`, `RT_PLAN_NOT_READY`, `UNSAFE_SAMPLE_GAIN`, `INTERNAL_FAILURE`.

## Proof obligations, not implemented
- HRTF headphone-only mode unless actual crosstalk compensated speaker plan; output layout and SOFA rights/coordinates must match.
- No audio-visible 3D source leaks beyond GAME/NET allowed role; acoustic queries cannot reveal hidden actors through structured telemetry.
- Active Scene/Cell/Origin revisions gate any ray, material and room result. `UNKNOWN` is never `CLEAR`; stale data must carry age/uncertainty and safe fallback.
- AUD-01 is sole mixer/voice/device owner and sample clock; acoustics prepares filter coefficients and bounded DSP plans without raycasting, file parse, allocation, network or blocking on callback.
- Headless and Web tiers may degrade effects transparently but must not alter GAME sound-origin/event truth. No bit-exact cross-OS PCM, universal localization, low latency or performance proof exists today.
