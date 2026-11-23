# GFX-07 internal camera/color/post-processing pipeline (INTERNAL_ONLY)

**Status:** `PROPOSED LOGICAL ARCHITECTURE / NO GPU / NO VISUAL QUALIFICATION`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md). **Governance:** [gfx-07-governance-v0](../contracts/gfx-07-governance-v0.md). **Queue:** `NLE-PRPLAN-GFX-07-01`.

## 1. Purpose

Describe the bounded logical model GFX-07 will implement before any backend, shader, HDR output or visual work. It validates camera/exposure/color/reconstruction metadata, derives deterministic plans and reports typed fallback/degradation reasons. It does not produce an image.

## 2. Modules and boundaries

- **GFX-07** owns logical camera/view plans, exposure, tone/color policy, HDR availability, AA strategy, motion-blur and upscale plans.
- **GFX-01** owns device/swapchain/display HDR capability and presentation.
- **GFX-02** owns shader compilation and layouts.
- **GFX-03** owns passes, resources, history and fences.
- **GFX-04** owns depth/velocity/jitter semantics on geometry.
- **GFX-05/06** own material/alpha and scene-linear lighting.
- **DATA-02/03/04** own durable camera IDs, color assets and scene revisions.

No dependency is added to a native graphics API, HDR monitor, vendor upscaler SDK, LUT runtime, codec, network service or hardware driver.

## 3. Logical model

### 3.1 Camera and view

- Stable camera/view IDs/revisions, perspective/orthographic kind, finite vertical FOV or ortho extent, aspect, near/far and previous-frame relation.
- Jitter metadata is bounded and flagged world-only; UI must remain unjittered.
- Zero/NaN/Inf/singular parameters and impossible near/far fail closed. No matrix is inverted.

### 3.2 Exposure

- Manual EV100 or auto-exposure metadata with metering percentiles, dark/bright adaptation and flash policy.
- EVs and times are finite/bounded; percentiles are ordered in `[0,100]`.
- No image histogram, metering texture or adaptation state is read or updated.

### 3.3 Tone/color plan

- Declared working primaries/transfer, output transfer, tone curve, exposure stops and gamut policy.
- SDR sRGB is the required fallback; HDR modes are only selected from explicit capabilities.
- Double transfer/tone mapping is detectable from declared flags and fails closed.
- No LUT, OCIO/ACES runtime, pixel transform or color-accurate image exists.

### 3.4 HDR availability

- A logical display request resolves to SDR or HDR only from supplied display/swapchain/OS/encoding flags.
- Unknown or unsupported paths fall back to SDR with `degraded=true`; an internal float format never implies HDR.
- No swapchain, monitor query, PQ/HLG signal or screenshot is created.

### 3.5 Reconstruction strategy

- Declared native/spatial/TAA/TAAU/vendor strategy with required inputs and fallback.
- Missing depth/velocity/history/light epoch selects the declared safe fallback; no temporal accumulator exists.
- Vendor strategies are metadata; no DLL/SDK is installed, loaded or called.

### 3.6 Motion blur

- Optional velocity/shutter metadata, bounded shutter angle and per-view enable.
- Reduced-motion/pixel-art policy can force disable; invalid values fail closed.
- No motion vector is generated, sampled or blurred.

### 3.7 Upscale

- Render/output dimensions and scale ratio are bounded and positive; scale is derived with checked arithmetic.
- Strategy/fallback metadata is explicit; native output is distinguished from reconstructed output.
- No upscaler, sharpening kernel, vendor SDK or image is produced.

## 4. Determinism and failure

- All plans are pure functions of validated inputs; stable IDs and declared order determine output.
- Errors are typed and fail closed; partial plans are not emitted.
- History/device/display mismatch resets to a declared safe SDR/spatial path rather than reusing stale metadata.
- No allocation, exception, file, network, thread or global state in the internal implementation.

## 5. Test strategy

- Unit oracles for camera, exposure, tone/HDR, reconstruction, motion blur and upscale.
- Integrated qualification QLF-G701..G704: valid pipeline, deterministic repeat, failure recovery and 10,000 bounded attempts.
- Native CI on Linux/ASan/UBSan/TSan/Windows/macOS; no visual/display/hardware assertion.

## 6. Explicit non-goals

No GPU implementation, swapchain, HDR signal, tone mapper, bloom, AA, motion blur, upscaler, LUT/OCIO runtime, vendor SDK, visual golden, performance, hardware monitor, public ABI or release. Those require separate owner-approved gates.
