# Evidence Bundle — NLE-P00-WO-002-PLAT-02 Linux Desktop Target Research

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#321](https://github.com/KayzenRoot/stormline/issues/321) | NLE-P00-WO-002-PLAT-02 | future code [#85](https://github.com/KayzenRoot/stormline/issues/85) OPEN/BLOCKED | BASE 6271e5482e02fbc575d401feb2d72a24eaff2854.** Catalog 67/80; formal dependencies **GFX-01 + GAME-01 ONLY** (ADR-0014/0042 PROPOSED), CORE-01 transitive; 66/80 research documented at source, 14 pending, all 80 coding WOs BLOCKED; engine_implemented=false; engine license NLE-D009 OPEN.


## Source Check: observed before research
- GitHub main BASE 6271e5482e02fbc575d401feb2d72a24eaff2854, same requested HEAD, no open PRs at starting check; latest previous change PLAT-01 historical closeout.
- Catalog PLAT-02 67/80, formal **GFX-01 + GAME-01 ONLY**; both ADR-0014/0042 PROPOSED. CORE-01 SDL3 transitive.
- Registry exactly 80, 66 research documented, 14 research pending including PLAT-02, **80 BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, ready=0, approved_adr=0, all release_class UNDECIDED, engine_implemented=false.
- Future code #85 OPEN/BLOCKED; research [#321](https://github.com/KayzenRoot/stormline/issues/321) OPEN until independent checkpoint. Engine license NLE-D009 OPEN.
- Source precedence and exact Git blob SHA-1 **Context Lock** documented in [WO](../work-orders/NLE-P00-WO-002-PLAT-02.md). SHA-1 object IDs NOT raw SHA-256; code activation must compute real SHA-256 if needed.

## Reproducible external research / no implementation
- SDL3 [Linux](https://wiki.libsdl.org/SDL3/README-linux), [Wayland limits](https://wiki.libsdl.org/SDL3/README-wayland), [backend hint](https://wiki.libsdl.org/SDL3/SDL_HINT_VIDEO_DRIVER) and [migration](https://wiki.libsdl.org/SDL3/README-migration): one CORE-01 host, Wayland-first candidate, X11 conditional, DPI/position/minimize limitations.
- Khronos [Wayland](https://docs.vulkan.org/refpages/latest/refpages/source/VK_KHR_wayland_surface.html), [XCB](https://docs.vulkan.org/refpages/latest/refpages/source/VK_KHR_xcb_surface.html) WSI and [loader ICD discovery](https://github.com/KhronosGroup/Vulkan-Loader/blob/main/docs/LoaderDriverInterface.md): GFX-01 retains surface/device ownership, trusted driver provenance required; no hardware feature inferred.
- [XDG Base Directory](https://specifications.freedesktop.org/basedir/), [portal FileChooser](https://flatpak.github.io/xdg-desktop-portal/docs/doc-org.freedesktop.portal.FileChooser.html), [Flatpak](https://docs.flatpak.org/en/latest/), [AppImage concepts](https://docs.appimage.org/introduction/concepts.html): absolute user paths, user grants, sandbox rights, old supported glibc build floor and system GPU driver exclusions.
- [PipeWire](https://docs.pipewire.org/) and SDL Linux support for per-session audio, CMake and ELF/glibc toolchain, no PLAT audio mixer, no untrusted loader or elevated privilege.
- All technologies/licensing are candidates. No versions pinned, package built or vulnerability clearance claimed.

## Exactly eight NEW Markdown research docs
1. [Architecture](../architecture/plat-02-linux-desktop-target.md).
2. [ADR-0070 PROPOSED](../adr/0070-plat-02-linux-host-compatibility-policy.md).
3. [Tech/license/security](../research/plat-02-linux-technology-license-security-matrix.md).
4. [API v0.1](../contracts/plat-02-linux-target-api.md).
5. [Exactly 128 FUTURE tests](../testing/plat-02-acceptance-matrix.md).
6. [Future hardware benchmark](../research/plat-02-linux-benchmark-protocol.md).
7. [Work Order](../work-orders/NLE-P00-WO-002-PLAT-02.md).
8. This Evidence Bundle.

Research-only diff, no source, queue registry, CI, checkpoint, backlog or prior ADR alteration.

## Claim/verification table
| Assertion | Evidence now | Not proven |
|---|---|---|
| 8 research docs authored | tree/PR file list, to be verified | no native C++ backend |
| 128 numbered future cases | P02-T001..P02-T128, verify uniqueness by readback | ZERO executed, PASS, GPU smoke |
| Source precedence/fingerprints | Git blob OIDs and base SHA from Source Check | no code-source SHA-256 lock |
| Technology reasoning | linked upstream official sources | no exact tag/redistribution approval |
| No code queue unlock | 80-entry readback, no registry edits in research | no dependency implementation |
| Hardware/performance | future test protocol + required fields | no physical Linux Editor/game run or measured FPS |
| Security/licensing | threat matrix and negative test designs | no penetration/sandbox test or cleared engine license |

## CI / audit / merge status at initial documentation authoring
- Research branch: docs/NLE-P00-WO-002-PLAT-02-linux-research; base 6271e5482e02fbc575d401feb2d72a24eaff2854; research PR number/head SHA, Docs Validation run/job, audit verdict, squash SHA and main readback **PENDING UNTIL ACTUALLY OBSERVED**. Do not turn PENDING into SUCCESS without real logs.
- Rollback: ordinary audited revert of docs-only research; no engine data migrations, binary or native host state touched.
- Risk: P00 document LOW; future ELF loader injection, driver permissions, binary signing, updater/root and native drivers ELEVATED/HIGH_ASSURANCE. Stop known HIGH/CRITICAL and unsafe or unlicensed defaults.

## Independent checkpoint proposal (NOT self-promoted)
After exact-head research PR CI SUCCESS, pt-BR objective audit APPROVED, normal squash and main readback:
1. Separate **five-file** PR modifies only docs/11-checkpoint.md, docs/08-backlog.md, docs/queue/implementation-registry.json, this Evidence and this WO.
2. Registry **sole** PLAT-02 research_status change RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED; no change to any implementation WO, dependency, approved_adr, release_class or engine status.
3. Target **67/80 researched (83.75%), 13 pending**, all 80 code packets blocked, 0 ready, 0 approved_adr, all releases UNDECIDED, engine=false; ADR-0070 PROPOSED; 128 future tests NOT EXECUTED.
4. Checkpoint has own CI/audit/squash/main readback; only then close research issue #321 (reopen if prematurely auto-closed), code issue #85 stays OPEN/BLOCKED.
5. Separate **four Markdown only** factual historical closeout (checkpoint/backlog/WO/Evidence) and own CI/audit/squash/readback; next catalog PLAT-03 Browser Runtime (68/80), deps TWO-01 + GFX-01 + DATA-05.


## Research PR #322 factual proof, independently proposed checkpoint
- [Research PR #322](https://github.com/KayzenRoot/stormline/pull/322) base `6271e5482e02fbc575d401feb2d72a24eaff2854`, head `cbc96c4b0245b19484458cfd4e725fd4c997e601`, exactly eight new Markdown, [Docs Validation run #43786413485](https://github.com/KayzenRoot/stormline/actions/runs/43786413485) SUCCESS job #133034958213 including Source Pack/links, catalog DAG, 80 registry and blocked selector, [objective pt-BR audit #6904800530](https://github.com/KayzenRoot/stormline/pull/322#issuecomment-6904800530) APPROVED documentary, squash/main readback `2f30d8613209739e15a025ebb5c68abc341b8b05`.
- Independent research checkpoint target **67/80 documented (83.75%), 13 pending; all 80/80 implementation WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class UNDECIDED all, engine_implemented=false**. Sole registry semantic mutation PLAT-02 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED` (all other 79 module entries and flags preserved). ADR-0070 PROPOSED, formal deps GFX-01+GAME-01 only, CORE-01 transitive, NLE-D009 license OPEN, P02-T001..P02-T128 future NOT EXECUTED, no Linux native code/build/hardware result.
- [Research issue #321](https://github.com/KayzenRoot/stormline/issues/321) OPEN pending own checkpoint CI/audit/squash/readback; future code [#85](https://github.com/KayzenRoot/stormline/issues/85) OPEN/BLOCKED. After verification close #321 and independently document history in a four-Markdown-only PR. Next PLAT-03 Browser Runtime 68/80 deps TWO-01+GFX-01+DATA-05.
- Research P00 only; package signing/source licensing/adopted backend/real Linux hardware remain unverified. Own checkpoint CI/audit/squash/readback pending.
