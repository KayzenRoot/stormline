#include "stormline/graphics/geometry/geometry_vegetation.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::geometry;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] InstanceDesc plant(f32 x) {
    InstanceDesc value{};
    value.id = 1;
    value.mesh_id = 10;
    value.material_id = 20;
    value.bounds.center = Vec3{x, 0.0f, 0.0f};
    value.bounds.radius = 1.0f;
    value.bounds.known = true;
    value.vegetation = VegetationKind::Grass;
    value.double_sided = true;
    value.alpha_cutout = true;
    value.billboard_allowed = true;
    return value;
}

bool run_veg01() {
    begin();
    VegetationRequest request{};
    request.camera = Vec3{0.0f, 0.0f, 0.0f};
    request.billboard_distance = 10.0f;
    VegetationDecision decision{};
    GeometryDiagnostic diagnostic{};

    expect(classify_vegetation(plant(5.0f), request, decision, diagnostic)
               == GeometryError::None,
           "near");
    expect(decision.render_class == VegetationRenderClass::Mesh, "near mesh");
    expect(decision.double_sided && decision.alpha_cutout, "flags");

    expect(classify_vegetation(plant(20.0f), request, decision, diagnostic)
               == GeometryError::None,
           "far");
    expect(decision.render_class == VegetationRenderClass::Billboard, "far billboard");

    InstanceDesc no_billboard = plant(20.0f);
    no_billboard.billboard_allowed = false;
    expect(classify_vegetation(no_billboard, request, decision, diagnostic)
               == GeometryError::None
               && decision.render_class == VegetationRenderClass::Mesh,
           "not allowed");

    InstanceDesc unknown = plant(20.0f);
    unknown.bounds.known = false;
    expect(classify_vegetation(unknown, request, decision, diagnostic)
               == GeometryError::None
               && decision.render_class == VegetationRenderClass::Mesh,
           "unknown bounds");

    InstanceDesc none = plant(5.0f);
    none.vegetation = VegetationKind::None;
    expect(classify_vegetation(none, request, decision, diagnostic)
               == GeometryError::InvalidArgument,
           "category");
    expect(classify_vegetation(InstanceDesc{}, request, decision, diagnostic)
               == GeometryError::InvalidArgument,
           "empty");

    VegetationRequest bad_request = request;
    bad_request.billboard_distance = 0.0f;
    expect(classify_vegetation(plant(5.0f), bad_request, decision, diagnostic)
               == GeometryError::InvalidArgument,
           "distance");
    bad_request = request;
    bad_request.camera.x = std::numeric_limits<f32>::infinity();
    expect(classify_vegetation(plant(5.0f), bad_request, decision, diagnostic)
               == GeometryError::InvalidArgument,
           "camera");

    InstanceDesc invalid_bounds = plant(5.0f);
    invalid_bounds.bounds.radius = -1.0f;
    expect(classify_vegetation(invalid_bounds, request, decision, diagnostic)
               == GeometryError::InvalidArgument,
           "bounds");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx04_vegetation_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "veg01") { success = run_veg01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
