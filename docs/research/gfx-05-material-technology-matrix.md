# GFX-05 — Materials and Texture Technology / Licensing Research Matrix

**Research:** #135 | **WO:** NLE-P00-WO-002-GFX-05 | **State:** PROPOSED, no dependency has been selected, downloaded, vendor-integrated or benchmarked.

| Option / upstream | Role | License / risk | Proposed evaluation and decision gates |
|---|---|---|---|
| glTF 2.0 metallic-roughness + KHR materials extensions (Khronos) | Stable interoperable physical material semantics | Specification use; check exact extension approval, example content rights separate | **Preferred semantic baseline**, explicit feature extension compatibility; preserve unknown required extension as error |
| Khronos glTF Render Fidelity & Sample Assets | Golden test reference for PBR, alpha, variants, transmission, sheen | Per-model fixture licenses vary; review individual attribution | Reference for fidelity tests, **not** importing copyrighted game art blindly |
| KTX2 / KHR_texture_basisu | Portable container / compressed texture asset interchange | Khronos format/spec; rights in content separately | **Preferred distribution candidate**; validate KTX2 fields, support ETC1S/UASTC, preserve format/color semantics |
| Basis Universal (Binomial LLC) | ETC1S/UASTC encoder/transcoder; potential C/C++/WASM | Apache-2.0 core + NOTICE, mixed transitive third-party components | Strong candidate for target texture transformation; pin exact commit/release, review dependencies/SBOM, exploit-resistant corpus |
| Khronos KTX-Software | KTX2 read/write/transcode reference and tooling | Mostly Apache-2.0, multi-license tree; `external/etcdec/etcdec.cxx` is explicitly **non-open-source**, may be excluded with `LIBKTX_FEATURE_ETC_UNPACK=NO` | Strong tooling candidate only after audited build flags/REUSE SPDX bill of materials and license compatibility |
| ASWF MaterialX 1.39.x | Portable material graph interchange and generators | Apache-2.0; generated code/licensing/third-party components must be reviewed | **Optional** authoring interchange; 1.39.5 announced May 2026; native Metal/WebGPU output correctness, feature parity and compile timing require platform proof |
| Filament PBR implementation/docs (Google) | BRDF/performance and material validation reference | Apache-2.0 project; imported snippets/assets must be attribution-reviewed | Read-only physics reference first, **not** make a runtime engine dependency |
| AMD Compressonator SDK/CLI | Offline compressor alternative for BCn/ASTC/etc | Inspect exact file licenses, platform binary/toolchain dependencies | Benchmark only in future DATA-05 cook step; no mandatory proprietary plugin |
| BC1/3/5/7 / ASTC / ETC2 / RGBA fallback | Derived target-specific GPU formats | Formats/capability support differ; encoding libraries have separate licenses | Choose by measured adapter support, source HDR/normal/alpha needs and error/latency/cost |
| Hardware sparse / virtual texturing | High density texture pages on large worlds | Capability/driver/maintenance complexity, Web/Metal limitations | OPTIONAL R&D against ordinary mip streaming; no release MUST-HAVE without explicit need |
| Weighted blended OIT | Order-independent approximate alpha composition | Literature/implementation licensing independent | Experimental fallback candidate where scene metrics justify approximation; compare sorted alpha oracle |

## Selection principles
1. **No unverified 'fully cross-platform' claim.** KTX2 container interchange does not imply identical target compression support or visual output. No default ETC2, ASTC, BC7, sparse/bindless guarantee on all devices.
2. **Artist fidelity first:** define linear-vs-sRGB semantics, alpha coverage, normal map and mip behavior; test color-management and golden fixtures. Transparency and transmission have distinct equations.
3. **Keep packages out of server runtime** unless actual headless capability requires a tiny verified decoder. Texture transcoder/cook belongs DATA-05/toolchain; GFX-05 receives already verified target artifacts.
4. **Portable fallback** to a supported uncompressed/mip texture under explicit RAM/VRAM budget and user-visible quality degradation, or typed unsupported error if budget insufficient.
5. **Pin versions late, but before coding**: version, exact release/commit, language/compiler profile, license texts, SBOM, transitive package security, reproducible build and fallback plan must be in approved ADR. Release class remains UNDECIDED.
6. **Prove vs baseline** with shader compilation/variant counts (GFX-02), texture cook time/size/quality (DATA-05), CPU/GPU p50/p95/p99, VRAM, overdraw, scene-specific visual tolerance and named device/driver/browser; no metrics exist yet.

## Source links
- Khronos glTF PBR https://www.khronos.org/gltf/pbr
- KHR_texture_basisu specification https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Khronos/KHR_texture_basisu/README.md
- KTX developer guide https://github.com/KhronosGroup/3D-Formats-Guidelines/blob/main/KTXDeveloperGuide.md
- Khronos KTX mixed licensing https://github.com/KhronosGroup/KTX-Software/blob/main/LICENSE.md
- Basis Universal licensing/NOTICE https://github.com/BinomialLLC/basis_universal/blob/master/README.md
- MaterialX official release and license https://materialx.org/
- Khronos glTF Render Fidelity https://github.khronos.org/glTF-Render-Fidelity/
- AMD Compressonator https://gpuopen.com/compressonator/

## Unresolved, must not silently assume
Exact glTF extension versions, release-class, reference BRDF tolerances, HDR pipeline and GFX-07 interface, BCn/ASTC/ETC2 format matrix, source ICC policies, compressed level index handling, mips cutout coverage, normal map tangent convention, KTX decoder build flags, MaterialX packaging, proprietary image fixture rights, golden thresholds and runtime residency budgets.
