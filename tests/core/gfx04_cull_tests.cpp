#include "stormline/graphics/geometry/geometry_cull.hpp"

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

[[nodiscard]] InstanceDesc instance(u32 id, Vec3 center) {
    InstanceDesc value{};
    value.id = id;
    value.mesh_id = 1;
    value.material_id = 1;
    value.bounds.center = center;
    value.bounds.radius = 1.0f;
    value.bounds.known = true;
    return value;
}

[[nodiscard]] ViewFrustum view(f32 max_distance) {
    ViewFrustum value{};
    value.scene_generation = 1;
    value.plane_count = 1;
    value.planes[0] = Plane{Vec3{1.0f, 0.0f, 0.0f}, 10.0f};
    value.camera = Vec3{0.0f, 0.0f, 0.0f};
    value.max_distance = max_distance;
    return value;
}

bool run_cul01() {
    begin();
    InstanceSet set{};
    set.scene_generation = 1;
    expect(add_instance(set, instance(1, Vec3{0.0f, 0.0f, 0.0f})) == GeometryError::None,
           "near");
    expect(add_instance(set, instance(2, Vec3{100.0f, 0.0f, 0.0f}))
               == GeometryError::None, "far");
    InstanceDesc unknown = instance(3, Vec3{-100.0f, 0.0f, 0.0f});
    unknown.bounds.known = false;
    expect(add_instance(set, unknown) == GeometryError::None, "unknown");

    CullResult result{};
    GeometryDiagnostic diagnostic{};
    expect(cull_instances(set, view(50.0f), result, diagnostic) == GeometryError::None,
           "cull");
    expect(result.visible_count == 2 && result.culled_count == 1, "counts");
    expect(result.visible_ids[0] == 1 && result.visible_ids[1] == 3, "visible ids");

    ViewFrustum plane_view = view(50.0f);
    plane_view.planes[0] = Plane{Vec3{1.0f, 0.0f, 0.0f}, 0.0f};
    InstanceSet outside{};
    outside.scene_generation = 1;
    expect(add_instance(outside, instance(1, Vec3{-10.0f, 0.0f, 0.0f}))
               == GeometryError::None, "outside");
    expect(cull_instances(outside, plane_view, result, diagnostic)
               == GeometryError::None,
           "plane cull");
    expect(result.visible_count == 0 && result.culled_count == 1, "plane culled");

    ViewFrustum mismatch = view(50.0f);
    mismatch.scene_generation = 2;
    expect(cull_instances(set, mismatch, result, diagnostic)
               == GeometryError::GenerationMismatch,
           "generation");
    ViewFrustum bad_plane = view(50.0f);
    bad_plane.planes[0].normal = Vec3{2.0f, 0.0f, 0.0f};
    expect(cull_instances(set, bad_plane, result, diagnostic)
               == GeometryError::InvalidCamera,
           "normal");
    ViewFrustum bad_distance = view(0.0f);
    expect(cull_instances(set, bad_distance, result, diagnostic)
               == GeometryError::InvalidCamera,
           "max distance");
    ViewFrustum bad_camera = view(50.0f);
    bad_camera.camera.x = std::numeric_limits<f32>::quiet_NaN();
    expect(cull_instances(set, bad_camera, result, diagnostic)
               == GeometryError::InvalidCamera,
           "camera");
    ViewFrustum no_planes = view(50.0f);
    no_planes.plane_count = 0;
    expect(cull_instances(set, no_planes, result, diagnostic)
               == GeometryError::InvalidCamera,
           "planes");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx04_cull_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "cul01") { success = run_cul01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
