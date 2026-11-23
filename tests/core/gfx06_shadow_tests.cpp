#include "stormline/graphics/lighting/shadow_plan.hpp"

#include <cstdio>
#include <limits>
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

[[nodiscard]] LightDesc directional(u32 id) {
    LightDesc light{};
    light.id = id;
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

[[nodiscard]] LightDesc area(u32 id) {
    LightDesc light{};
    light.id = id;
    light.revision = 1;
    light.kind = LightKind::AreaRect;
    light.unit = LightUnit::Luminance;
    light.intensity = 1.0f;
    light.width = 1.0f;
    light.height = 1.0f;
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

bool run_shd01() {
    begin();
    CascadePlan plan{};
    LightingDiagnostic diagnostic{};

    CascadeRequest request{0.1f, 100.0f, 4, 0.5f};
    expect(build_cascade_plan(request, plan, diagnostic) == LightingError::None,
           "cascade plan");
    expect(plan.count == 4, "cascade count");
    expect(plan.cascades[0].near_distance == 0.1f, "cascade first near");
    expect(plan.cascades[3].far_distance == 100.0f, "cascade last far");
    expect(plan.cascades[0].far_distance == plan.cascades[1].near_distance
               && plan.cascades[1].far_distance
                   == plan.cascades[2].near_distance
               && plan.cascades[2].far_distance
                   == plan.cascades[3].near_distance,
           "cascade contiguous");
    expect(plan.cascades[0].blend > 0.0f, "cascade blend");

    CascadeRequest uniform{0.1f, 100.0f, 4, 0.0f};
    expect(build_cascade_plan(uniform, plan, diagnostic) == LightingError::None,
           "uniform");
    expect(std::fabs(plan.cascades[0].far_distance - 25.075f) < 0.001f,
           "uniform split");

    CascadeRequest logarithmic{0.1f, 100.0f, 4, 1.0f};
    expect(build_cascade_plan(logarithmic, plan, diagnostic)
               == LightingError::None,
           "logarithmic");
    expect(std::fabs(plan.cascades[0].far_distance - 0.5623f) < 0.001f,
           "log split");

    CascadeRequest invalid{0.0f, 100.0f, 4, 0.5f};
    expect(build_cascade_plan(invalid, plan, diagnostic)
               == LightingError::InvalidCascade,
           "near zero");
    invalid = CascadeRequest{10.0f, 10.0f, 4, 0.5f};
    expect(build_cascade_plan(invalid, plan, diagnostic)
               == LightingError::InvalidCascade,
           "far order");
    invalid = CascadeRequest{0.1f, 100.0f, 0, 0.5f};
    expect(build_cascade_plan(invalid, plan, diagnostic)
               == LightingError::InvalidCascade,
           "count zero");
    invalid = CascadeRequest{0.1f, 100.0f, kMaxCascades + 1, 0.5f};
    expect(build_cascade_plan(invalid, plan, diagnostic)
               == LightingError::InvalidCascade,
           "count max");
    invalid = CascadeRequest{0.1f, 100.0f, 4, -0.1f};
    expect(build_cascade_plan(invalid, plan, diagnostic)
               == LightingError::InvalidCascade,
           "lambda low");
    invalid = CascadeRequest{0.1f, 100.0f, 4, 1.1f};
    expect(build_cascade_plan(invalid, plan, diagnostic)
               == LightingError::InvalidCascade,
           "lambda high");
    invalid = CascadeRequest{
        std::numeric_limits<f32>::quiet_NaN(), 100.0f, 4, 0.5f};
    expect(build_cascade_plan(invalid, plan, diagnostic)
               == LightingError::InvalidCascade,
           "nan near");
    expect(plan.count == 0, "invalid reset");

    LightSet lights{};
    expect(add_light(lights, directional(1)) == LightingError::None, "light 1");
    expect(add_light(lights, point(2)) == LightingError::None, "light 2");
    expect(add_light(lights, area(3)) == LightingError::None, "light 3");

    ShadowPageSet pages{};
    pages.count = 4;
    pages.pages[0] = page(10, 1, 5.0f);
    pages.pages[1] = page(11, 1, 3.0f);
    pages.pages[2] = page(12, 2, 4.0f, true);
    pages.pages[3] = page(13, 1, 1.0f);

    ShadowPagePlan page_plan{};
    expect(plan_shadow_pages(lights, pages, 2, page_plan, diagnostic)
               == LightingError::None,
           "page plan");
    expect(page_plan.count == 2 && page_plan.page_ids[0] == 13
               && page_plan.page_ids[1] == 11,
           "page order");
    expect(page_plan.resident_count == 1 && page_plan.missing_count == 3
               && page_plan.coarse_fallback,
           "page counts");

    expect(plan_shadow_pages(lights, pages, 3, page_plan, diagnostic)
               == LightingError::None,
           "page budget 3");
    expect(page_plan.count == 3 && page_plan.page_ids[2] == 10
               && !page_plan.coarse_fallback,
           "page full");

    expect(plan_shadow_pages(lights, pages, 0, page_plan, diagnostic)
               == LightingError::None,
           "page zero budget");
    expect(page_plan.count == 0 && page_plan.coarse_fallback, "page zero");

    ShadowPageSet duplicate{};
    duplicate.count = 2;
    duplicate.pages[0] = page(20, 1, 1.0f);
    duplicate.pages[1] = page(20, 1, 2.0f);
    expect(plan_shadow_pages(lights, duplicate, 1, page_plan, diagnostic)
               == LightingError::DuplicateId,
           "page duplicate");

    ShadowPageSet unknown{};
    unknown.count = 1;
    unknown.pages[0] = page(21, 99, 1.0f);
    expect(plan_shadow_pages(lights, unknown, 1, page_plan, diagnostic)
               == LightingError::NotFound,
           "page light");

    ShadowPageSet disabled{};
    disabled.count = 1;
    disabled.pages[0] = page(22, 3, 1.0f);
    expect(plan_shadow_pages(lights, disabled, 1, page_plan, diagnostic)
               == LightingError::InvalidArgument,
           "page disabled");

    ShadowPageSet invalid_page{};
    invalid_page.count = 1;
    invalid_page.pages[0] = page(23, 1, -1.0f);
    expect(plan_shadow_pages(lights, invalid_page, 1, page_plan, diagnostic)
               == LightingError::InvalidArgument,
           "page negative");
    invalid_page.pages[0].distance =
        std::numeric_limits<f32>::quiet_NaN();
    expect(plan_shadow_pages(lights, invalid_page, 1, page_plan, diagnostic)
               == LightingError::InvalidArgument,
           "page nan");
    invalid_page.pages[0] = page(0, 1, 1.0f);
    expect(plan_shadow_pages(lights, invalid_page, 1, page_plan, diagnostic)
               == LightingError::InvalidArgument,
           "page zero id");

    ShadowPageSet too_many{};
    too_many.count = kMaxShadowPages + 1;
    expect(plan_shadow_pages(lights, too_many, 1, page_plan, diagnostic)
               == LightingError::InvalidArgument,
           "page capacity");
    expect(plan_shadow_pages(lights, pages, kMaxShadowPages + 1, page_plan,
                             diagnostic) == LightingError::InvalidArgument,
           "budget capacity");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx06_shadow_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "shd01") { success = run_shd01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
