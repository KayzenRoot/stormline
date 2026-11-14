# TWO-04 — Future Hybrid 2D/3D Acceptance and Safety Matrix

**Research #156 | WO NLE-P00-WO-002-TWO-04 | Future coding issue #40 BLOCKED**.  
**ALL 109 CASES LISTED HERE ARE FUTURE / NOT EXECUTED.** No scene rendering, shader/device test, 2.5D animation, light/shadow, HUD, output screenshot or benchmark recorded.

| Test ID | Future test/proof obligation | Expected proof surface |
|---|---|---|
| PRO-001 | 2D pixels to 3D meters round-trip with explicit unit factor | CPU math |
| PRO-002 | Right-handed glTF Y-up source transform to engine scheme validated | CPU/import |
| PRO-003 | Negative determinant changes winding/normal handedness correctly | CPU |
| PRO-004 | Ortho camera projection of sprite anchor invertible | CPU golden |
| PRO-005 | Perspective projected anchor near/far clipping valid | CPU golden |
| PRO-006 | Sprite camera facing billboard rotates correctly around roll | GPU golden |
| PRO-007 | Axis-locked billboard and up vector degeneracy safely handled | CPU |
| PRO-008 | World-plane sprite pivots/feet origin stay stable under camera tilt | GPU |
| PRO-009 | Screen overlay never accidentally writes world depth | GPU |
| PRO-010 | Large 64-bit world origin rebasing no visible sprite jitter | CPU/GPU |
| PRO-011 | Perspective to ortho cut invalidates old projection-dependent plans | integration |
| PRO-012 | Negative zoom, invalid FOV, NaN transform rejected | fuzz |
| DEP-001 | 3D opaque wall occludes sprite behind its pixels | GPU golden |
| DEP-002 | Sprite in front of 3D wall visible with valid depth | GPU golden |
| DEP-003 | 3D mesh in between two masked sprites occlusion correct | GPU |
| DEP-004 | Alpha mask cutout writes depth only surviving fragments | GPU |
| DEP-005 | Alpha blend generally tests depth without writing | GPU |
| DEP-006 | Depth compare and reversed Z convention matched by owner | GPU |
| DEP-007 | Near/far precision depth fighting quantified with named device | hardware |
| DEP-008 | Depth24plus versus depth32float feature probes and fallbacks | WebGPU |
| DEP-009 | MSAA depth resolve/alpha-to-coverage behavior validated | GPU |
| DEP-010 | Depth-based DoF/SSAO after flattened overlay warns unsupported | GPU |
| DEP-011 | World-plane sprite 2-sided culling and backface policy explicit | GPU |
| DEP-012 | Depth and stencil attachments same GFX03 graph no alias hazard | graph |
| DEP-013 | GFX04 mesh LOD transition preserves sprite occlusion relative | integration |
| DEP-014 | Far camera disocclusion large-world rebase consistency | GPU |
| DEP-015 | No physics collision inferred from visual depth test | architecture |
| SRT-001 | Canvas painter order identical before/after 2.5D overlay | golden |
| SRT-002 | Stable same-depth sprites tie-break follows author order | CPU |
| SRT-003 | Y sort affects authored group not global arbitrary world depth | CPU |
| SRT-004 | Sprite feet sort point versus center with tall actor | 2D golden |
| SRT-005 | Projected bounds of tall sprites do not vanish across camera | GPU |
| SRT-006 | Translucent order independent of legal batch merge changes | golden |
| SRT-007 | Transparent overlapping sprites/meshes disclose unavoidable ambiguity | diagnostic |
| SRT-008 | Camera perspective change resort transparent group deterministically | GPU |
| SRT-009 | Opaque mesh sort and Canvas layer order stay independent | integration |
| SRT-010 | Mixed layer masks prevent cross-group occlusion leakage | GPU |
| ALP-001 | Premultiplied source-over in linear scene HDR composited once | numeric/GPU |
| ALP-002 | Cutout feathering and MSAA alpha-to-coverage only if supported | GPU |
| ALP-003 | Soft-depth particles blend with opaque geometry and reactive mask | GFX08 |
| ALP-004 | World-space transparent sprite vs refractive glass warns limitation | visual |
| ALP-005 | Weighted OIT approximation quantified versus sorted reference | benchmark |
| ALP-006 | Weighted OIT not falsely presented as exact refraction | audit |
| ALP-007 | No PPLL/SSBO compute requirement in WebGL2 tier | browser |
| ALP-008 | Multiply/additive with Canvas layer isolation avoids double alpha | golden |
| ALP-009 | Alpha depth-write conflict denied unless explicit author proof | security |
| CAM-001 | HDR scene-linear sprite light/color matches 3D mesh within tolerance | color |
| CAM-002 | SDR gamma and sRGB texture sampling no double decode | color |
| CAM-003 | HDR10 PQ/P3 only on actual capable display backend | GFX07 |
| CAM-004 | Native-resolution unjittered pixel-art HUD after scene post | golden |
| CAM-005 | World sprite under TAA retains motion vectors and no ghost trail | temporal |
| CAM-006 | Camera cut resets depth/temporal histories and subviews | temporal |
| CAM-007 | Dynamic-resolution scene and native HUD coordinate mapping | GPU |
| CAM-008 | Split-screen camera independent layer and depth attachments | GPU |
| CAM-009 | Viewport DPI/zoom change no pixel-jitter leak into labels | golden |
| CAM-010 | Camera recenter/rebase invalidates cache epochs | integration |
| LIT-001 | Unlit world sprites retain authored color under 3D lighting | color |
| LIT-002 | Lit normal-mapped sprite reacts to shared 3D directional light | GFX06 |
| LIT-003 | Billboard normal world vs view tangent basis correct | GPU |
| LIT-004 | Mirrored sprite normal map does not invert accidental light | GPU |
| LIT-005 | Shadow caster cutout geometry proxy consistent with sprite alpha | shadow |
| LIT-006 | Shadow receive masks and light budget honored | budget |
| LIT-007 | Fog and GI only applied with available world depth | GFX06 |
| LIT-008 | 2D overlay with no depth not falsely volumetric-fogged | GFX06 |
| LIT-009 | Emissive sprite in HDR not double exposed by compositor | GFX07 |
| LIT-010 | No one shadowcasting light per particle fallback explosion | stress |
| SUB-001 | Subview color/alpha render-to-texture appears in 3D screen | GPU |
| SUB-002 | 3D preview composited in 2D UI without depth claim | GPU |
| SUB-003 | SubView depth cannot be reused across incompatible projections | validation |
| SUB-004 | Subview depth reprojection rejected unless verified camera transform | CPU |
| SUB-005 | Subview recursive cycle rejected by render graph | fuzz |
| SUB-006 | Subview max dimensions/VRAM budget and active count enforced | stress |
| SUB-007 | Subview stale frame reports age and falls back visibly | fault |
| SUB-008 | Subview resize realloc/free after fence without stale descriptor | GFX03 |
| SUB-009 | Device loss cancels pending subview sampling and recovers | GFX03 |
| SUB-010 | Subview external scene/project privacy forbidden | security |
| SUB-011 | Minimap/picture-in-picture independent update cadence traced | benchmark |
| INT-001 | TWO01 Canvas ClipStack preserves material/alpha and atlas | integration |
| INT-002 | TWO02 tile camera parallax layered with GFX04 world depth | integration |
| INT-003 | TWO03 skinned 2D rig world anchor moves under camera correctly | integration |
| INT-004 | GFX05 PBR sprite and mesh materials use compatible working spaces | integration |
| INT-005 | GFX06 shadow atlas ownership and lighting same source | integration |
| INT-006 | GFX07 frame reconstruction history reactive/disocclusion declared | integration |
| INT-007 | GFX08 transparent VFX respects hybrid depth without sim duplication | integration |
| INT-008 | GFX03 graph barriers and resource retirement checked on edit | integration |
| INT-009 | WORLD PHYS truth unaffected by camera render occlusion | architecture |
| INT-010 | Editor CLI MCP same semantic versioned authoring results | contract |
| SEC-001 | Untrusted glTF anchors/source scale/path via DATA03 only | security |
| SEC-002 | NaN/Inf camera transform, alpha and depth values rejected | fuzz |
| SEC-003 | MCP cross-project edit/view/reference blocked | security |
| SEC-004 | MCP huge camera/subview iteration quota enforced | security |
| SEC-005 | Render graph attachment read/write feedback forbidden | security |
| SEC-006 | No arbitrary shader or GPU pointer from hybrid authoring | security |
| SEC-007 | Potential alpha/depth semantic fallback never silent | safety |
| SEC-008 | Asset licenses and competitive scene rights documented | license |
| SEC-009 | Device loss/OOM does not leak or reuse stale buffers | fault |
| SEC-010 | Layer sorting ties stable across platforms/project reimports | replay |
| BEN-001 | Two cameras perspective/ortho original sprites/3D meshs goldens | benchmark |
| BEN-002 | CPU GPU full-frame p50 p95 p99 under camera sweep | benchmark |
| BEN-003 | Layer batching versus visual correctness image error | benchmark |
| BEN-004 | Transparency overdraw cost versus order/OIT accuracy | benchmark |
| BEN-005 | Shadow proxy and lighting accuracy versus GPU memory | benchmark |
| BEN-006 | Native Vulkan DX12 Metal original mixed scene captures | hardware |
| BEN-007 | WebGPU/limited WebGL2 browser original scene captures | browser |
| BEN-008 | SubViews resolution/number GPU VRAM Pareto | benchmark |
| BEN-009 | Pixel art/HiDPI HDR scene and crisp UI quality metric | benchmark |
| BEN-010 | SDOI prove-or-drop versus plain mode validation false positives | R&D |
| BEN-011 | Godot/Unity independent original matched scenes not competitor art | reference |
| BEN-012 | No FPS/superiority claims without actual measurements | audit |

## Future functional and nonfunctional acceptance requirements
- Create independent **original licensed scene fixtures**: sprite character standing in front/behind an opaque 3D wall, large tree cutout and building with many 2D/3D transparent foliage meshes, unlit+normal-mapped 2D actor, 2D tilemap parallax, 3D meshes from rights-cleared glTF, a lit cutscene with 2D animated bones and VFX, scene camera tilt and HDR/unlit overlay, UI/pixel-art icons/labels, subview picture-in-picture with device restart. No copying Unity/Godot games, proprietary assets or competitor benchmarks as samples.
- CPU reference mathematics proves px↔world meters, stable model/atlas IDs, handedness and unit transforms, Y/sort ties, orthographic/perspective depth mapping and finite invalid inputs. **Only** real GPU screenshots prove pixel occlusion, HDR/AA and subview correctness. CPU reference is not hardware quality test.
- Depth truth: opaque/masked depth write, blended depth test/non-write default; subview colors cannot imply interoperable world depth; weighted OIT approximate, no refractive glass/soft particle universal exactness claim. Existing GFX-03/04/05/06/07/08 ownership must be verified against actual interfaces before code.
- Verify actual Windows DX12/Vulkan, Linux Vulkan, macOS Apple Silicon Metal and limited WebGPU/WebGL2 browsers, feature-probe depth format/attachments/MSAA/resolves and independent device loss; no assumed compute support on WebGL2.
- Quantified target only after owner approval: named hardware/scene resolution, pixel-art sharpness/alpha error, light/shadow fidelity and latency, GPU frame p50/p95/p99, draw/overdraw and subview VRAM/UMA, history ghost/disocclusion and visual depth-error metric. **Numerical thresholds and 60 FPS target NOT VERIFIED**.
- Security: untrusted glTF paths/scale, cross-project frame and camera leakage, scene update CAS, shader injection, hostile subview recursion, huge attachments, GPU use-after-free and attacker supplied invalid transforms must be tested. No HIGH/CRITICAL allowed in implementation.
