#include "stormline/graphics/geometry/geometry_budget.hpp"
#include "stormline/graphics/geometry/geometry_cull.hpp"
#include "stormline/graphics/geometry/geometry_lod.hpp"
#include "stormline/graphics/geometry/geometry_stream.hpp"
#include "stormline/graphics/geometry/geometry_vegetation.hpp"

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

[[nodiscard]] InstanceDesc item(u32 id, Vec3 center, bool known,
                                VegetationKind kind) {
    InstanceDesc value{};
    value.id = id;
    value.mesh_id = 10;
    value.material_id = 20;
    value.bounds.center = center;
    value.bounds.radius = 1.0f;
    value.bounds.known = known;
    value.vegetation = kind;
    value.double_sided = true;
    value.alpha_cutout = true;
    value.billboard_allowed = true;
    return value;
}

[[nodiscard]] bool scene(InstanceSet& set) {
    set.scene_generation = 1;
    return add_instance(set, item(1, Vec3{0.0f, 0.0f, 0.0f}, true,
                                  VegetationKind::Grass)) == GeometryError::None
        && add_instance(set, item(2, Vec3{100.0f, 0.0f, 0.0f}, true,
                                  VegetationKind::Tree)) == GeometryError::None
        && add_instance(set, item(3, Vec3{-100.0f, 0.0f, 0.0f}, false,
                                  VegetationKind::Bush)) == GeometryError::None;
}

[[nodiscard]] LodChain lod_chain() {
    LodChain chain{};
    chain.scene_generation = 1;
    chain.mesh_id = 10;
    chain.level_count = 3;
    chain.levels[0] = LodLevel{0.0f, 1000};
    chain.levels[1] = LodLevel{10.0f, 500};
    chain.levels[2] = LodLevel{50.0f, 100};
    return chain;
}

[[nodiscard]] HlodSet hlod() {
    HlodSet set{};
    set.scene_generation = 1;
    set.count = 2;
    set.nodes[0] = HlodNode{10, 0, 0.0f, 1000, false};
    set.nodes[1] = HlodNode{11, 10, 10.0f, 500, true};
    return set;
}

struct Snapshot {
    u32 batches{0};
    u32 visible{0};
    u32 lod_level{0};
    u32 hlod_mesh{0};
    u32 stream_count{0};
    u32 vegetation_class{0};
    u64 total_triangles{0};
};

[[nodiscard]] bool pipeline(Snapshot& out) {
    InstanceSet instances{};
    if (!scene(instances)) {
        return false;
    }
    BatchPlan batches{};
    GeometryDiagnostic diagnostic{};
    if (plan_batches(instances, batches, diagnostic) != GeometryError::None) {
        return false;
    }
    ViewFrustum view{};
    view.scene_generation = 1;
    view.plane_count = 1;
    view.planes[0] = Plane{Vec3{1.0f, 0.0f, 0.0f}, 1000.0f};
    view.camera = Vec3{0.0f, 0.0f, 0.0f};
    view.max_distance = 50.0f;
    CullResult cull{};
    if (cull_instances(instances, view, cull, diagnostic) != GeometryError::None) {
        return false;
    }
    LodChain chain = lod_chain();
    LodRequest request{};
    request.camera = Vec3{0.0f, 0.0f, 0.0f};
    request.screen_scale = 1.0f;
    request.max_screen_error = 20.0f;
    LodSelection lod{};
    if (select_lod(chain, SphereBounds{Vec3{0.0f, 0.0f, 0.0f}, 1.0f, true},
                   request, lod, diagnostic) != GeometryError::None) {
        return false;
    }
    HlodSet hierarchy = hlod();
    HlodSelection hlod_selection{};
    if (select_hlod(hierarchy, 10, 15.0f, hlod_selection, diagnostic)
        != GeometryError::None) {
        return false;
    }
    ChunkSet chunks{};
    chunks.scene_generation = 1;
    chunks.count = 2;
    chunks.chunks[0] = GeometryChunk{1, 10, 0, 100, true};
    chunks.chunks[1] = GeometryChunk{2, 10, 1, 200, true};
    ResidentChunks resident{};
    resident.count = 1;
    resident.chunk_ids[0] = 1;
    StreamPlan stream{};
    if (plan_stream(chunks, resident, 500, stream, diagnostic) != GeometryError::None) {
        return false;
    }
    VegetationRequest vegetation_request{};
    vegetation_request.camera = Vec3{0.0f, 0.0f, 0.0f};
    vegetation_request.billboard_distance = 10.0f;
    VegetationDecision vegetation{};
    if (classify_vegetation(instances.instances[1], vegetation_request,
                            vegetation, diagnostic) != GeometryError::None) {
        return false;
    }
    GeometryMetricSet metrics{};
    metrics.count = 1;
    metrics.meshes[0] = GeometryMetrics{10, 100, 50, 1000};
    GeometryBudgetPlan budget{};
    if (validate_geometry_budget(metrics, GeometryBudget{100, 50, 1000},
                                 budget, diagnostic) != GeometryError::None) {
        return false;
    }
    out.batches = batches.count;
    out.visible = cull.visible_count;
    out.lod_level = lod.level;
    out.hlod_mesh = hlod_selection.mesh_id;
    out.stream_count = stream.count;
    out.vegetation_class = static_cast<u32>(vegetation.render_class);
    out.total_triangles = budget.total_triangles;
    return true;
}

bool run_qlf_g401() {
    begin();
    Snapshot snapshot{};
    expect(pipeline(snapshot), "pipeline");
    expect(snapshot.batches == 1, "batches");
    expect(snapshot.visible == 2, "visible");
    expect(snapshot.lod_level == 1, "lod");
    expect(snapshot.hlod_mesh == 11, "hlod");
    expect(snapshot.stream_count == 1, "stream");
    expect(snapshot.vegetation_class
               == static_cast<u32>(VegetationRenderClass::Billboard),
           "vegetation");
    expect(snapshot.total_triangles == 50, "triangles");
    return finish();
}

bool run_qlf_g402() {
    begin();
    Snapshot first{};
    Snapshot second{};
    expect(pipeline(first), "first");
    expect(pipeline(second), "second");
    expect(first.batches == second.batches, "batch repeat");
    expect(first.visible == second.visible, "visible repeat");
    expect(first.lod_level == second.lod_level, "lod repeat");
    expect(first.hlod_mesh == second.hlod_mesh, "hlod repeat");
    expect(first.stream_count == second.stream_count, "stream repeat");
    expect(first.vegetation_class == second.vegetation_class, "vegetation repeat");
    expect(first.total_triangles == second.total_triangles, "triangles repeat");
    return finish();
}

bool run_qlf_g403() {
    begin();
    InstanceSet set{};
    set.scene_generation = 1;
    expect(add_instance(set, InstanceDesc{}) == GeometryError::InvalidArgument,
           "bad instance");
    expect(scene(set), "after bad instance");
    GeometryDiagnostic diagnostic{};
    ViewFrustum view{};
    view.scene_generation = 2;
    view.plane_count = 1;
    view.planes[0] = Plane{Vec3{1.0f, 0.0f, 0.0f}, 1000.0f};
    view.max_distance = 50.0f;
    CullResult cull{};
    expect(cull_instances(set, view, cull, diagnostic)
               == GeometryError::GenerationMismatch,
           "generation");
    view.scene_generation = 1;
    expect(cull_instances(set, view, cull, diagnostic) == GeometryError::None,
           "after generation");

    LodChain bad_chain = lod_chain();
    bad_chain.level_count = 0;
    LodSelection lod{};
    LodRequest request{};
    request.max_screen_error = 20.0f;
    expect(select_lod(bad_chain, SphereBounds{Vec3{}, 1.0f, true}, request,
                      lod, diagnostic) == GeometryError::InvalidLodChain,
           "lod");
    expect(select_lod(lod_chain(), SphereBounds{Vec3{}, 1.0f, true}, request,
                      lod, diagnostic) == GeometryError::None,
           "after lod");

    HlodSet cycle{};
    cycle.scene_generation = 1;
    cycle.count = 2;
    cycle.nodes[0] = HlodNode{1, 2, 0.0f, 10, false};
    cycle.nodes[1] = HlodNode{2, 1, 1.0f, 5, false};
    HlodSelection hlod_selection{};
    expect(select_hlod(cycle, 1, 1.0f, hlod_selection, diagnostic)
               == GeometryError::HierarchyCycle,
           "hlod cycle");
    expect(select_hlod(hlod(), 10, 15.0f, hlod_selection, diagnostic)
               == GeometryError::None,
           "after hlod");

    ChunkSet chunks{};
    chunks.scene_generation = 1;
    chunks.count = 1;
    chunks.chunks[0] = GeometryChunk{1, 10, 0, 100, false};
    StreamPlan stream{};
    expect(plan_stream(chunks, ResidentChunks{}, 500, stream, diagnostic)
               == GeometryError::UnverifiedChunk,
           "unverified");
    chunks.chunks[0].verified = true;
    expect(plan_stream(chunks, ResidentChunks{}, 500, stream, diagnostic)
               == GeometryError::None,
           "after unverified");

    VegetationDecision vegetation{};
    VegetationRequest vegetation_request{};
    vegetation_request.billboard_distance = 10.0f;
    InstanceDesc no_category = item(1, Vec3{}, true, VegetationKind::None);
    expect(classify_vegetation(no_category, vegetation_request, vegetation,
                               diagnostic) == GeometryError::InvalidArgument,
           "vegetation");
    expect(classify_vegetation(item(1, Vec3{}, true, VegetationKind::Grass),
                               vegetation_request, vegetation, diagnostic)
               == GeometryError::None,
           "after vegetation");

    GeometryMetricSet metrics{};
    metrics.count = 1;
    metrics.meshes[0] = GeometryMetrics{10, 100, 50, 1000};
    GeometryBudgetPlan budget{};
    expect(validate_geometry_budget(metrics, GeometryBudget{50, 50, 1000},
                                    budget, diagnostic)
               == GeometryError::GeometryBudgetExceeded,
           "budget");
    expect(validate_geometry_budget(metrics, GeometryBudget{100, 50, 1000},
                                    budget, diagnostic) == GeometryError::None,
           "after budget");
    return finish();
}

bool run_qlf_g404() {
    begin();
    Snapshot snapshot{};
    for (u32 index = 0; index < 10000; ++index) {
        expect(pipeline(snapshot), "bounded pipeline");
        InstanceSet invalid{};
        expect(add_instance(invalid, InstanceDesc{}) == GeometryError::InvalidArgument,
               "bounded reject");
    }
    expect(snapshot.visible == 2 && snapshot.total_triangles == 50, "bounded values");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx04_geometry_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") { success = run_qlf_g401(); }
    else if (mode == "qlf02") { success = run_qlf_g402(); }
    else if (mode == "qlf03") { success = run_qlf_g403(); }
    else if (mode == "qlf04") { success = run_qlf_g404(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
