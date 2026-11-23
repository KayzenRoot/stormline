#include "stormline/graphics/lighting/light.hpp"

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

[[nodiscard]] LightDesc directional(u32 id = 1) {
    LightDesc light{};
    light.id = id;
    light.revision = 1;
    light.kind = LightKind::Directional;
    light.unit = LightUnit::Lux;
    light.color = Vec3{1.0f, 0.9f, 0.8f};
    light.intensity = 1.0f;
    light.direction = Vec3{0.0f, -1.0f, 0.0f};
    light.shadow = ShadowMode::Cascaded;
    return light;
}

[[nodiscard]] LightDesc point(u32 id = 2) {
    LightDesc light{};
    light.id = id;
    light.revision = 1;
    light.kind = LightKind::Point;
    light.unit = LightUnit::Candela;
    light.color = Vec3{1.0f, 0.5f, 0.25f};
    light.intensity = 5.0f;
    light.position = Vec3{1.0f, 2.0f, 3.0f};
    light.range = 10.0f;
    light.shadow = ShadowMode::Local;
    return light;
}

[[nodiscard]] LightDesc spot(u32 id = 3) {
    LightDesc light = point(id);
    light.kind = LightKind::Spot;
    light.inner_angle = 0.1f;
    light.outer_angle = 0.5f;
    return light;
}

[[nodiscard]] LightDesc area(u32 id = 4) {
    LightDesc light{};
    light.id = id;
    light.revision = 1;
    light.kind = LightKind::AreaRect;
    light.unit = LightUnit::Luminance;
    light.intensity = 2.0f;
    light.width = 2.0f;
    light.height = 1.0f;
    return light;
}

[[nodiscard]] LightDesc environment(u32 id = 5) {
    LightDesc light{};
    light.id = id;
    light.revision = 1;
    light.kind = LightKind::Environment;
    light.unit = LightUnit::Luminance;
    light.intensity = 1.0f;
    return light;
}

[[nodiscard]] LightDesc stylized(u32 id = 6) {
    LightDesc light = point(id);
    light.kind = LightKind::Stylized2D;
    light.unit = LightUnit::Luminance;
    light.shadow = ShadowMode::Disabled;
    return light;
}

bool run_lgt01() {
    begin();
    LightSet set{};
    LightingDiagnostic diagnostic{};

    expect(add_light(set, directional()) == LightingError::None, "directional");
    expect(add_light(set, point()) == LightingError::None, "point");
    expect(add_light(set, spot()) == LightingError::None, "spot");
    expect(add_light(set, area()) == LightingError::None, "area");
    expect(add_light(set, environment()) == LightingError::None, "environment");
    expect(add_light(set, stylized()) == LightingError::None, "stylized");
    expect(set.count == 6, "count");
    expect(validate_lights(set, diagnostic) == LightingError::None, "valid");

    expect(add_light(set, point(2)) == LightingError::DuplicateId, "duplicate");
    expect(set.count == 6, "duplicate atomic");
    expect(add_light(set, point(0)) == LightingError::InvalidArgument, "zero id");
    LightDesc invalid = point(7);
    invalid.revision = 0;
    expect(add_light(set, invalid) == LightingError::InvalidArgument,
           "zero revision");

    invalid = point(7);
    invalid.kind = static_cast<LightKind>(200);
    expect(add_light(set, invalid) == LightingError::InvalidLightKind,
           "kind enum");
    invalid = point(7);
    invalid.unit = static_cast<LightUnit>(200);
    expect(add_light(set, invalid) == LightingError::InvalidUnit, "unit enum");
    invalid = directional(7);
    invalid.unit = LightUnit::Candela;
    expect(add_light(set, invalid) == LightingError::InvalidUnit,
           "directional unit");
    invalid = point(7);
    invalid.unit = LightUnit::Lux;
    expect(add_light(set, invalid) == LightingError::InvalidUnit, "point unit");
    invalid = area(7);
    invalid.unit = LightUnit::Lux;
    expect(add_light(set, invalid) == LightingError::InvalidUnit, "area unit");

    invalid = point(7);
    invalid.color.x = std::numeric_limits<f32>::quiet_NaN();
    expect(add_light(set, invalid) == LightingError::NonFiniteValue,
           "color nan");
    invalid = point(7);
    invalid.intensity = std::numeric_limits<f32>::infinity();
    expect(add_light(set, invalid) == LightingError::NonFiniteValue,
           "intensity inf");
    invalid = point(7);
    invalid.position.y = std::numeric_limits<f32>::infinity();
    expect(add_light(set, invalid) == LightingError::NonFiniteValue,
           "position inf");
    invalid = point(7);
    invalid.direction.z = std::numeric_limits<f32>::quiet_NaN();
    expect(add_light(set, invalid) == LightingError::NonFiniteValue,
           "direction nan");
    invalid = point(7);
    invalid.range = std::numeric_limits<f32>::infinity();
    expect(add_light(set, invalid) == LightingError::NonFiniteValue,
           "range inf");

    invalid = point(7);
    invalid.color.z = -1.0f;
    expect(add_light(set, invalid) == LightingError::OutOfRange,
           "negative color");
    invalid = point(7);
    invalid.intensity = -1.0f;
    expect(add_light(set, invalid) == LightingError::OutOfRange,
           "negative intensity");
    invalid = point(7);
    invalid.direction = Vec3{};
    expect(add_light(set, invalid) == LightingError::InvalidArgument,
           "zero direction");
    invalid = point(7);
    invalid.range = 0.0f;
    expect(add_light(set, invalid) == LightingError::OutOfRange,
           "point range");

    invalid = spot(7);
    invalid.outer_angle = 0.0f;
    expect(add_light(set, invalid) == LightingError::OutOfRange,
           "spot outer zero");
    invalid = spot(7);
    invalid.outer_angle = kPi;
    expect(add_light(set, invalid) == LightingError::OutOfRange,
           "spot outer range");
    invalid = spot(7);
    invalid.inner_angle = 0.6f;
    expect(add_light(set, invalid) == LightingError::OutOfRange,
           "spot inner order");
    invalid = spot(7);
    invalid.inner_angle = -0.1f;
    expect(add_light(set, invalid) == LightingError::OutOfRange,
           "spot inner negative");
    invalid = area(7);
    invalid.width = 0.0f;
    expect(add_light(set, invalid) == LightingError::OutOfRange,
           "area width");
    invalid = area(7);
    invalid.height = 0.0f;
    expect(add_light(set, invalid) == LightingError::OutOfRange,
           "area height");

    invalid = directional(7);
    invalid.shadow = ShadowMode::Local;
    expect(add_light(set, invalid) == LightingError::InvalidArgument,
           "directional shadow");
    invalid = point(7);
    invalid.shadow = ShadowMode::Cascaded;
    expect(add_light(set, invalid) == LightingError::InvalidArgument,
           "point shadow");
    invalid = area(7);
    invalid.shadow = ShadowMode::Cascaded;
    expect(add_light(set, invalid) == LightingError::InvalidArgument,
           "area shadow");

    LightSet duplicate_set{};
    duplicate_set.count = 2;
    duplicate_set.lights[0] = point(1);
    duplicate_set.lights[1] = point(1);
    expect(validate_lights(duplicate_set, diagnostic)
               == LightingError::DuplicateId,
           "manual duplicate");
    expect(diagnostic.light_id == 1 && diagnostic.index == 1,
           "duplicate position");

    LightSet overflow{};
    overflow.count = kMaxLights + 1;
    expect(validate_lights(overflow, diagnostic)
               == LightingError::InvalidArgument,
           "overflow");

    LightSet invalid_manual{};
    invalid_manual.count = 1;
    invalid_manual.lights[0] = point(30);
    invalid_manual.lights[0].range = 0.0f;
    expect(validate_lights(invalid_manual, diagnostic)
               == LightingError::OutOfRange,
           "manual range");
    expect(diagnostic.light_id == 30 && diagnostic.index == 0,
           "range position");

    while (set.count < kMaxLights) {
        expect(add_light(set, point(100 + set.count)) == LightingError::None,
               "fill");
    }
    expect(add_light(set, point(999)) == LightingError::CapacityFull,
           "capacity");
    expect(set.count == kMaxLights, "capacity count");

    expect(std::string_view(lighting_error_name(LightingError::None)) == "None",
           "error none");
    expect(std::string_view(lighting_error_name(
               static_cast<LightingError>(200))) == "Unknown",
           "error unknown");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx06_light_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "lgt01") { success = run_lgt01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
