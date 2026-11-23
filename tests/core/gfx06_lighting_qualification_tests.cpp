#include "stormline/graphics/lighting/gi_plan.hpp"
#include "stormline/graphics/lighting/light.hpp"
#include "stormline/graphics/lighting/probe_plan.hpp"
#include "stormline/graphics/lighting/reflection_plan.hpp"
#include "stormline/graphics/lighting/shadow_plan.hpp"
#include "stormline/graphics/lighting/volumetric_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::lighting;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

struct PipelineResult {
    u32 light_count{0};
    u32 cascade_count{0};
    f32 first_near{0.0f};
    f32 last_far{0.0f};
    u32 page_count{0};
    u32 page_first{0};
    u32 page_second{0};
    u32 page_resident{0};
    u32 page_missing{0};
    bool page_fallback{false};
    GiMode gi_mode{GiMode::Unsupported};
    bool gi_degraded{false};
    u32 probe_count{0};
    u32 probe_first{0};
    u32 probe_second{0};
    ReflectionMode reflection_mode{ReflectionMode::Unsupported};
    ReflectionMode reflection_fallback{ReflectionMode::Unsupported};
    bool reflection_offscreen{false};
    u32 volumetric_count{0};
    u32 volumetric_first{0};
    u32 volumetric_second{0};
    u32 volumetric_steps{0};
    LightingError last_error{LightingError::None};
};

[[nodiscard]] LightDesc directional() {
    LightDesc light{};
    light.id = 1;
    light.revision = 1;
    light.kind = LightKind::Directional;
    light.unit = LightUnit::Lux;
    light.intensity = 1.0f;
    light.direction = Vec3{0.0f, -1.0f, 0.0f};
    light.shadow = ShadowMode::Cascaded;
    return light;
}

[[nodiscard]] LightDesc point(u32 id) {
    LightDesc light{};
    light.id = id;
    light.revision = 1;
    light.kind = LightKind::Point;
    light.unit = LightUnit::Candela;
    light.intensity = 1.0f;
    light.range = 10.0f;
    light.shadow = ShadowMode::Local;
    return light;
}

[[nodiscard]] ShadowPage page(u32 id, u32 light_id, f32 distance,
                              bool resident = false) {
    ShadowPage value{};
    value.id = id;
    value.light_id = light_id;
    value.distance = distance;
    value.resident = resident;
    return value;
}

[[nodiscard]] ProbeVolumeDesc probe(u32 id) {
    ProbeVolumeDesc value{};
    value.id = id;
    value.revision = 1;
    value.scene_generation = 7;
    value.origin = Vec3{0.0f, 0.0f, 0.0f};
    value.spacing = 1.0f;
    value.cells_x = 4;
    value.cells_y = 4;
    value.cells_z = 4;
    return value;
}

[[nodiscard]] VolumetricDesc volume(u32 id, u32 steps) {
    VolumetricDesc value{};
    value.id = id;
    value.revision = 1;
    value.density = 0.1f;
    value.extinction = 0.2f;
    value.scattering = 0.3f;
    value.step_count = steps;
    return value;
}

[[nodiscard]] PipelineResult run_pipeline() {
    PipelineResult result{};
    LightingDiagnostic diagnostic{};

    LightSet lights{};
    result.last_error = add_light(lights, directional());
    if (result.last_error != LightingError::None) {
        return result;
    }
    result.last_error = add_light(lights, point(2));
    result.last_error = add_light(lights, point(3));
    result.light_count = lights.count;

    CascadeRequest cascade_request{0.1f, 100.0f, 4, 0.5f};
    CascadePlan cascades{};
    result.last_error = build_cascade_plan(cascade_request, cascades, diagnostic);
    if (result.last_error != LightingError::None) {
        return result;
    }
    result.cascade_count = cascades.count;
    result.first_near = cascades.cascades[0].near_distance;
    result.last_far = cascades.cascades[cascades.count - 1].far_distance;

    ShadowPageSet pages{};
    pages.count = 3;
    pages.pages[0] = page(10, 1, 5.0f);
    pages.pages[1] = page(11, 1, 3.0f);
    pages.pages[2] = page(12, 2, 4.0f, true);
    ShadowPagePlan page_plan{};
    result.last_error = plan_shadow_pages(
        lights, pages, 2, page_plan, diagnostic);
    if (result.last_error != LightingError::None) {
        return result;
    }
    result.page_count = page_plan.count;
    result.page_first = page_plan.page_ids[0];
    result.page_second = page_plan.page_ids[1];
    result.page_resident = page_plan.resident_count;
    result.page_missing = page_plan.missing_count;
    result.page_fallback = page_plan.coarse_fallback;

    GiRequest gi_request{};
    gi_request.requested = GiMode::Baked;
    gi_request.probe_available = true;
    GiPlan gi_plan{};
    result.last_error = plan_gi(gi_request, gi_plan, diagnostic);
    if (result.last_error != LightingError::None) {
        return result;
    }
    result.gi_mode = gi_plan.mode;
    result.gi_degraded = gi_plan.degraded;

    ProbeVolumeSet probes{};
    probes.count = 2;
    probes.probes[0] = probe(21);
    probes.probes[1] = probe(20);
    ProbePlan probe_plan{};
    result.last_error = plan_probes(probes, 7, probe_plan, diagnostic);
    if (result.last_error != LightingError::None) {
        return result;
    }
    result.probe_count = probe_plan.count;
    result.probe_first = probe_plan.probe_ids[0];
    result.probe_second = probe_plan.probe_ids[1];

    ReflectionRequest reflection_request{};
    reflection_request.preferred = ReflectionMode::ScreenSpace;
    reflection_request.ssr_available = true;
    reflection_request.probe_available = true;
    ReflectionPlan reflection_plan{};
    result.last_error = plan_reflections(
        reflection_request, reflection_plan, diagnostic);
    if (result.last_error != LightingError::None) {
        return result;
    }
    result.reflection_mode = reflection_plan.mode;
    result.reflection_fallback = reflection_plan.fallback;
    result.reflection_offscreen = reflection_plan.offscreen_fallback;

    VolumetricSet volumes{};
    volumes.count = 2;
    volumes.volumes[0] = volume(31, 4);
    volumes.volumes[1] = volume(30, 6);
    VolumetricPlan volume_plan{};
    result.last_error = plan_volumetrics(volumes, 10, volume_plan, diagnostic);
    result.volumetric_count = volume_plan.count;
    result.volumetric_first = volume_plan.volume_ids[0];
    result.volumetric_second = volume_plan.volume_ids[1];
    result.volumetric_steps = volume_plan.total_steps;
    return result;
}

bool same_result(const PipelineResult& left, const PipelineResult& right) {
    return left.light_count == right.light_count
        && left.cascade_count == right.cascade_count
        && left.first_near == right.first_near
        && left.last_far == right.last_far
        && left.page_count == right.page_count
        && left.page_first == right.page_first
        && left.page_second == right.page_second
        && left.page_resident == right.page_resident
        && left.page_missing == right.page_missing
        && left.page_fallback == right.page_fallback
        && left.gi_mode == right.gi_mode
        && left.gi_degraded == right.gi_degraded
        && left.probe_count == right.probe_count
        && left.probe_first == right.probe_first
        && left.probe_second == right.probe_second
        && left.reflection_mode == right.reflection_mode
        && left.reflection_fallback == right.reflection_fallback
        && left.reflection_offscreen == right.reflection_offscreen
        && left.volumetric_count == right.volumetric_count
        && left.volumetric_first == right.volumetric_first
        && left.volumetric_second == right.volumetric_second
        && left.volumetric_steps == right.volumetric_steps
        && left.last_error == right.last_error;
}

bool run_qlf01() {
    begin();
    const PipelineResult result = run_pipeline();
    expect(result.last_error == LightingError::None, "pipeline");
    expect(result.light_count == 3, "lights");
    expect(result.cascade_count == 4 && result.first_near == 0.1f
               && result.last_far == 100.0f,
           "cascades");
    expect(result.page_count == 2 && result.page_first == 11
               && result.page_second == 10 && result.page_resident == 1
               && result.page_missing == 2 && !result.page_fallback,
           "shadow pages");
    expect(result.gi_mode == GiMode::ProbeFallback && result.gi_degraded,
           "gi");
    expect(result.probe_count == 2 && result.probe_first == 20
               && result.probe_second == 21,
           "probes");
    expect(result.reflection_mode == ReflectionMode::ScreenSpace
               && result.reflection_fallback == ReflectionMode::Probe
               && result.reflection_offscreen,
           "reflections");
    expect(result.volumetric_count == 2 && result.volumetric_first == 30
               && result.volumetric_second == 31
               && result.volumetric_steps == 10,
           "volumetrics");
    return finish();
}

bool run_qlf02() {
    begin();
    const PipelineResult first = run_pipeline();
    const PipelineResult second = run_pipeline();
    expect(first.last_error == LightingError::None, "first");
    expect(second.last_error == LightingError::None, "second");
    expect(same_result(first, second), "deterministic repeat");
    return finish();
}

bool run_qlf03() {
    begin();
    LightingDiagnostic diagnostic{};
    LightSet lights{};
    expect(add_light(lights, directional()) == LightingError::None, "light");
    expect(add_light(lights, directional()) == LightingError::DuplicateId,
           "duplicate light");
    expect(add_light(lights, point(2)) == LightingError::None,
           "recover light");

    CascadePlan cascades{};
    CascadeRequest invalid_cascade{};
    expect(build_cascade_plan(invalid_cascade, cascades, diagnostic)
               == LightingError::InvalidCascade,
           "invalid cascade");
    expect(build_cascade_plan(CascadeRequest{0.1f, 100.0f, 4, 0.5f},
                              cascades, diagnostic) == LightingError::None,
           "recover cascade");

    ShadowPageSet pages{};
    pages.count = 2;
    pages.pages[0] = page(1, 1, 1.0f);
    pages.pages[1] = page(1, 1, 2.0f);
    ShadowPagePlan page_plan{};
    expect(plan_shadow_pages(lights, pages, 1, page_plan, diagnostic)
               == LightingError::DuplicateId,
           "invalid page");
    pages.pages[1] = page(2, 1, 2.0f);
    expect(plan_shadow_pages(lights, pages, 1, page_plan, diagnostic)
               == LightingError::None,
           "recover page");

    GiRequest gi_request{};
    GiPlan gi_plan{};
    expect(plan_gi(gi_request, gi_plan, diagnostic)
               == LightingError::GiUnavailable,
           "invalid gi");
    gi_request.environment_available = true;
    expect(plan_gi(gi_request, gi_plan, diagnostic) == LightingError::None,
           "recover gi");

    ProbeVolumeSet probes{};
    probes.count = 1;
    probes.probes[0] = probe(1);
    probes.probes[0].scene_generation = 6;
    ProbePlan probe_plan{};
    expect(plan_probes(probes, 7, probe_plan, diagnostic)
               == LightingError::HistoryInvalid,
           "invalid probe");
    probes.probes[0].scene_generation = 7;
    expect(plan_probes(probes, 7, probe_plan, diagnostic)
               == LightingError::None,
           "recover probe");

    ReflectionPlan reflection_plan{};
    ReflectionRequest reflection_request{};
    expect(plan_reflections(reflection_request, reflection_plan, diagnostic)
               == LightingError::ReflectionOffscreen,
           "invalid reflection");
    reflection_request.environment_available = true;
    expect(plan_reflections(reflection_request, reflection_plan, diagnostic)
               == LightingError::None,
           "recover reflection");

    VolumetricSet volumes{};
    volumes.count = 1;
    volumes.volumes[0] = volume(1, 8);
    VolumetricPlan volume_plan{};
    expect(plan_volumetrics(volumes, 4, volume_plan, diagnostic)
               == LightingError::VolumetricBudgetExceeded,
           "invalid volume");
    expect(plan_volumetrics(volumes, 8, volume_plan, diagnostic)
               == LightingError::None,
           "recover volume");
    return finish();
}

bool run_qlf04() {
    begin();
    bool bounded = true;
    for (u32 iteration = 0; iteration < 10000; ++iteration) {
        const PipelineResult result = run_pipeline();
        bounded = bounded && result.last_error == LightingError::None
            && result.light_count <= kMaxLights
            && result.cascade_count <= kMaxCascades
            && result.page_count <= kMaxShadowPages
            && result.probe_count <= kMaxProbes
            && result.volumetric_count <= kMaxVolumetrics;

        LightSet lights{};
        LightDesc invalid{};
        bounded = bounded
            && add_light(lights, invalid) == LightingError::InvalidArgument
            && lights.count == 0;
    }
    expect(bounded, "bounded overload");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx06_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") { success = run_qlf01(); }
    else if (mode == "qlf02") { success = run_qlf02(); }
    else if (mode == "qlf03") { success = run_qlf03(); }
    else if (mode == "qlf04") { success = run_qlf04(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
