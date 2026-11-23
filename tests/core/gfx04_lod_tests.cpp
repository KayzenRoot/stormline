#include "stormline/graphics/geometry/geometry_lod.hpp"

#include <cstdio>
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

[[nodiscard]] LodChain chain() {
    LodChain value{};
    value.scene_generation = 1;
    value.mesh_id = 1;
    value.level_count = 3;
    value.levels[0] = LodLevel{0.0f, 1000};
    value.levels[1] = LodLevel{10.0f, 500};
    value.levels[2] = LodLevel{50.0f, 100};
    return value;
}

[[nodiscard]] SphereBounds bounds(f32 x) {
    SphereBounds value{};
    value.center = Vec3{x, 0.0f, 0.0f};
    value.radius = 1.0f;
    value.known = true;
    return value;
}

[[nodiscard]] HlodSet hlod() {
    HlodSet value{};
    value.scene_generation = 1;
    value.count = 4;
    value.nodes[0] = HlodNode{1, 0, 0.0f, 1000, false};
    value.nodes[1] = HlodNode{2, 1, 10.0f, 500, false};
    value.nodes[2] = HlodNode{3, 2, 20.0f, 100, true};
    value.nodes[3] = HlodNode{4, 0, 5.0f, 800, true};
    return value;
}

bool run_lod01() {
    begin();
    LodChain lod = chain();
    GeometryDiagnostic diagnostic{};
    expect(validate_lod_chain(lod, diagnostic) == GeometryError::None, "chain");
    LodSelection selection{};
    LodRequest request{};
    request.camera = Vec3{0.0f, 0.0f, 0.0f};
    request.screen_scale = 1.0f;
    request.max_screen_error = 2.0f;
    request.previous_level = 0;
    expect(select_lod(lod, bounds(10.0f), request, selection, diagnostic)
               == GeometryError::None,
           "select");
    expect(selection.level == 1 && selection.triangle_count == 500, "level 1");
    request.previous_level = 2;
    expect(select_lod(lod, bounds(10.0f), request, selection, diagnostic)
               == GeometryError::None,
           "hysteresis");
    expect(selection.level == 1, "hysteresis keeps finer");
    request.camera = Vec3{0.0f, 0.0f, 0.0f};
    request.previous_level = 1;
    expect(select_lod(lod, bounds(100.0f), request, selection, diagnostic)
               == GeometryError::None,
           "distance select");
    expect(selection.level == 1, "hysteresis at distance");
    SphereBounds unknown = bounds(10.0f);
    unknown.known = false;
    expect(select_lod(lod, unknown, request, selection, diagnostic)
               == GeometryError::None
               && selection.level == 0,
           "unknown bounds");

    LodChain invalid = lod;
    invalid.levels[0].geometric_error = 1.0f;
    expect(validate_lod_chain(invalid, diagnostic) == GeometryError::InvalidLodChain,
           "level0 error");
    invalid = lod;
    invalid.levels[2].triangle_count = 2000;
    expect(validate_lod_chain(invalid, diagnostic) == GeometryError::InvalidLodChain,
           "triangle order");
    invalid = lod;
    invalid.level_count = 0;
    expect(validate_lod_chain(invalid, diagnostic) == GeometryError::InvalidLodChain,
           "level count");
    invalid = lod;
    invalid.levels[1].triangle_count = 0;
    expect(validate_lod_chain(invalid, diagnostic) == GeometryError::InvalidLodChain,
           "zero triangles");
    invalid = lod;
    invalid.levels[1].geometric_error = -1.0f;
    expect(validate_lod_chain(invalid, diagnostic) == GeometryError::InvalidLodChain,
           "negative error");

    request = LodRequest{};
    request.camera = Vec3{};
    request.screen_scale = 0.0f;
    request.max_screen_error = 2.0f;
    expect(select_lod(lod, bounds(10.0f), request, selection, diagnostic)
               == GeometryError::InvalidArgument,
           "screen scale");
    request.screen_scale = 1.0f;
    request.max_screen_error = -1.0f;
    expect(select_lod(lod, bounds(10.0f), request, selection, diagnostic)
               == GeometryError::InvalidArgument,
           "max error");
    request.max_screen_error = 2.0f;
    request.previous_level = 3;
    expect(select_lod(lod, bounds(10.0f), request, selection, diagnostic)
               == GeometryError::InvalidArgument,
           "previous level");

    HlodSet hierarchy = hlod();
    expect(validate_hlod(hierarchy, diagnostic) == GeometryError::None, "hlod");
    HlodSelection hlod_selection{};
    expect(select_hlod(hierarchy, 1, 15.0f, hlod_selection, diagnostic)
               == GeometryError::None,
           "hlod select");
    expect(hlod_selection.mesh_id == 2 && !hlod_selection.proxy, "hlod node 2");
    expect(select_hlod(hierarchy, 1, 25.0f, hlod_selection, diagnostic)
               == GeometryError::None,
           "hlod coarse");
    expect(hlod_selection.mesh_id == 3 && hlod_selection.proxy, "hlod node 3");
    expect(select_hlod(hierarchy, 1, 0.0f, hlod_selection, diagnostic)
               == GeometryError::None
               && hlod_selection.mesh_id == 1,
           "hlod root fallback");
    expect(select_hlod(hierarchy, 4, 10.0f, hlod_selection, diagnostic)
               == GeometryError::None
               && hlod_selection.mesh_id == 4,
           "hlod other root");

    HlodSet cycle{};
    cycle.scene_generation = 1;
    cycle.count = 2;
    cycle.nodes[0] = HlodNode{1, 2, 0.0f, 10, false};
    cycle.nodes[1] = HlodNode{2, 1, 1.0f, 5, false};
    expect(validate_hlod(cycle, diagnostic) == GeometryError::HierarchyCycle,
           "cycle");
    HlodSet missing = hierarchy;
    missing.nodes[0].parent_mesh_id = 99;
    expect(validate_hlod(missing, diagnostic) == GeometryError::NotFound,
           "missing parent");
    HlodSet duplicate = hierarchy;
    duplicate.nodes[3].mesh_id = 2;
    expect(validate_hlod(duplicate, diagnostic) == GeometryError::DuplicateId,
           "duplicate");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx04_lod_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "lod01") { success = run_lod01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
