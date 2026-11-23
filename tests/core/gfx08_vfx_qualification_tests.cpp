#include "stormline/graphics/vfx/blend_plan.hpp"
#include "stormline/graphics/vfx/density_plan.hpp"
#include "stormline/graphics/vfx/emitter_plan.hpp"
#include "stormline/graphics/vfx/pool_plan.hpp"
#include "stormline/graphics/vfx/ribbon_plan.hpp"
#include "stormline/graphics/vfx/trail_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::vfx;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

struct Pipeline {
    VfxGraphPlan graph{};
    VfxEmitterPlan emitter{};
    VfxRibbonPlan ribbon{};
    VfxTrailPlan trail{};
    VfxBlendPlan blend{};
    VfxDensityPlan density{};
    VfxPoolPlan pool{};
    VfxDiagnostic diagnostic{};
};

VfxGraphNode node(u32 id, VfxNodeKind kind) {
    VfxGraphNode value{};
    value.node_id = id;
    value.revision = 1;
    value.kind = kind;
    return value;
}

    VfxGraphDesc graph_desc() {
    VfxGraphDesc graph{};
    graph.graph_id = 11;
    graph.revision = 2;
    graph.node_count = 3;
    graph.nodes[0] = node(1, VfxNodeKind::Emitter);
    graph.nodes[1] = node(2, VfxNodeKind::Update);
    graph.nodes[2] = node(3, VfxNodeKind::Render);
    graph.edge_count = 2;
    graph.edges[0] = VfxGraphEdge{1, 2, VfxPortType::Flow};
    graph.edges[1] = VfxGraphEdge{2, 3, VfxPortType::Flow};
    return graph;
}

VfxTrailDesc trail_desc() {
    VfxTrailDesc trail{};
    trail.source_id = 4;
    trail.revision = 1;
    trail.sample_count = 4;
    trail.samples[0] = VfxTrailSample{0.0f, 0.3f};
    trail.samples[1] = VfxTrailSample{0.1f, 0.2f};
    trail.samples[2] = VfxTrailSample{0.2f, 0.15f};
    trail.samples[3] = VfxTrailSample{0.3f, 0.1f};
    trail.max_segments = 4;
    trail.max_vertices = 8;
    trail.max_age_seconds = 1.0f;
    return trail;
}

bool run_pipeline(Pipeline& pipeline) {
    pipeline = Pipeline{};
    const VfxGraphDesc graph = graph_desc();
    if (validate_graph(graph, pipeline.graph, pipeline.diagnostic)
        != VfxError::None) {
        return false;
    }
    VfxEmitterDesc emitter{};
    emitter.emitter_id = 2;
    emitter.revision = 1;
    emitter.graph_id = 11;
    emitter.graph_revision = 2;
    emitter.spawn_per_tick = 6;
    emitter.burst_count = 2;
    emitter.lifetime_seconds = 1.5f;
    emitter.seed = 42;
    if (plan_emitter(emitter, VfxSpawnBudget{16, 32}, pipeline.emitter,
                     pipeline.diagnostic) != VfxError::None) {
        return false;
    }
    VfxRibbonDesc ribbon{};
    ribbon.source_id = 3;
    ribbon.revision = 1;
    ribbon.sample_count = 6;
    ribbon.width = 0.2f;
    ribbon.min_sample_distance = 0.05f;
    ribbon.max_segments = 8;
    ribbon.max_vertices = 16;
    if (plan_ribbon(ribbon, pipeline.ribbon, pipeline.diagnostic)
        != VfxError::None) {
        return false;
    }
    const VfxTrailDesc trail = trail_desc();
    if (plan_trail(trail, pipeline.trail, pipeline.diagnostic)
        != VfxError::None) {
        return false;
    }
    VfxBlendDesc blend{};
    blend.material_id = 5;
    blend.material_revision = 1;
    blend.blend = BlendMode::Blend;
    blend.depth = DepthPolicy::TestOnly;
    blend.premultiplied_alpha = true;
    blend.sort_required = true;
    blend.oit_approximation_allowed = true;
    if (plan_blend(blend, pipeline.blend, pipeline.diagnostic)
        != VfxError::None) {
        return false;
    }
    VfxDensityStampDesc stamp{};
    stamp.stamp_id = 8;
    stamp.revision = 1;
    stamp.density = 0.5f;
    stamp.extinction = 0.25f;
    stamp.extent_x = 1.0f;
    stamp.extent_y = 1.0f;
    stamp.extent_z = 1.0f;
    stamp.lifetime_seconds = 1.0f;
    stamp.max_density = 1.0f;
    if (plan_density_stamp(stamp, pipeline.density, pipeline.diagnostic)
        != VfxError::None) {
        return false;
    }
    VfxPoolDesc pool{};
    pool.pool_id = 9;
    pool.capacity = 64;
    pool.generation = 3;
    pool.expected_generation = 3;
    pool.particles = 8;
    pool.ribbons = 2;
    pool.trails = 2;
    pool.light_requests = 1;
    return plan_pool(pool, VfxQualityBudget{16, 4, 4, 2}, pipeline.pool,
                     pipeline.diagnostic) == VfxError::None;
}

bool same_pipeline(const Pipeline& left, const Pipeline& right) {
    return left.graph.acyclic == right.graph.acyclic
        && left.graph.node_count == right.graph.node_count
        && left.emitter.spawn_per_tick == right.emitter.spawn_per_tick
        && left.emitter.alive_capacity == right.emitter.alive_capacity
        && left.ribbon.segments == right.ribbon.segments
        && left.ribbon.vertices == right.ribbon.vertices
        && left.trail.segments == right.trail.segments
        && left.trail.vertices == right.trail.vertices
        && left.trail.lifetime_seconds == right.trail.lifetime_seconds
        && left.blend.blend == right.blend.blend
        && left.blend.needs_sort == right.blend.needs_sort
        && left.blend.oit_approx == right.blend.oit_approx
        && left.density.density == right.density.density
        && left.density.clamped == right.density.clamped
        && left.pool.admitted_particles == right.pool.admitted_particles
        && left.pool.available == right.pool.available
        && left.pool.degraded == right.pool.degraded
        && left.diagnostic.code == right.diagnostic.code;
}

bool run_qlfg801() {
    begin();
    Pipeline pipeline{};
    expect(run_pipeline(pipeline), "integrated pipeline");
    expect(pipeline.graph.acyclic && pipeline.graph.order[0] == 1,
           "graph plan");
    expect(pipeline.emitter.spawn_per_tick == 8, "emitter plan");
    expect(pipeline.ribbon.segments == 5 && pipeline.ribbon.vertices == 12,
           "ribbon plan");
    expect(pipeline.trail.segments == 3 && pipeline.trail.vertices == 8,
           "trail plan");
    expect(pipeline.blend.needs_sort && pipeline.blend.oit_approx,
           "blend plan");
    expect(pipeline.density.density == 0.5f && !pipeline.density.clamped,
           "density plan");
    expect(pipeline.pool.available == 51 && !pipeline.pool.degraded,
           "pool plan");
    return finish();
}

bool run_qlfg802() {
    begin();
    Pipeline first{};
    Pipeline second{};
    expect(run_pipeline(first), "first run");
    expect(run_pipeline(second), "second run");
    expect(same_pipeline(first, second), "deterministic plans");
    for (u32 attempt = 0; attempt < 100; ++attempt) {
        Pipeline repeated{};
        expect(run_pipeline(repeated), "repeat succeeds");
        expect(same_pipeline(first, repeated), "repeat identical");
        if (failures != 0) {
            break;
        }
    }
    return finish();
}

bool run_qlfg803() {
    begin();
    Pipeline pipeline{};
    expect(run_pipeline(pipeline), "baseline pipeline");
    VfxDiagnostic diagnostic{};

    VfxGraphDesc graph = graph_desc();
    graph.edge_count = 2;
    graph.edges[1] = VfxGraphEdge{2, 1, VfxPortType::Flow};
    expect(validate_graph(graph, pipeline.graph, diagnostic)
               == VfxError::GraphCycle,
           "graph failure");
    graph = graph_desc();
    expect(validate_graph(graph, pipeline.graph, diagnostic) == VfxError::None,
           "graph recovery");

    VfxEmitterDesc emitter{};
    emitter.emitter_id = 2;
    emitter.revision = 1;
    emitter.graph_id = 11;
    emitter.graph_revision = 2;
    emitter.spawn_per_tick = 32;
    emitter.burst_count = 1;
    emitter.lifetime_seconds = 1.0f;
    expect(plan_emitter(emitter, VfxSpawnBudget{16, 32}, pipeline.emitter,
                        diagnostic) == VfxError::SpawnBudgetExceeded,
           "emitter failure");
    emitter.spawn_per_tick = 4;
    expect(plan_emitter(emitter, VfxSpawnBudget{16, 32}, pipeline.emitter,
                        diagnostic) == VfxError::None,
           "emitter recovery");

    VfxRibbonDesc ribbon{};
    ribbon.source_id = 3;
    ribbon.revision = 1;
    ribbon.sample_count = 6;
    ribbon.width = 0.2f;
    ribbon.min_sample_distance = 0.05f;
    ribbon.max_segments = 8;
    ribbon.max_vertices = 8;
    expect(plan_ribbon(ribbon, pipeline.ribbon, diagnostic)
               == VfxError::BudgetExceeded,
           "ribbon failure");
    ribbon.max_vertices = 16;
    expect(plan_ribbon(ribbon, pipeline.ribbon, diagnostic) == VfxError::None,
           "ribbon recovery");

    VfxTrailDesc trail = trail_desc();
    trail.samples[2].age_seconds = 0.05f;
    expect(plan_trail(trail, pipeline.trail, diagnostic)
               == VfxError::GeometryInvalid,
           "trail failure");
    trail = trail_desc();
    expect(plan_trail(trail, pipeline.trail, diagnostic) == VfxError::None,
           "trail recovery");

    VfxBlendDesc blend{};
    blend.material_id = 5;
    blend.material_revision = 1;
    blend.blend = BlendMode::Blend;
    blend.depth = DepthPolicy::TestAndWrite;
    expect(plan_blend(blend, pipeline.blend, diagnostic)
               == VfxError::MaterialMismatch,
           "blend failure");
    blend.depth = DepthPolicy::TestOnly;
    expect(plan_blend(blend, pipeline.blend, diagnostic) == VfxError::None,
           "blend recovery");

    VfxDensityStampDesc stamp{};
    stamp.stamp_id = 8;
    stamp.revision = 1;
    stamp.density = -1.0f;
    stamp.extinction = 0.1f;
    stamp.extent_x = 1.0f;
    stamp.extent_y = 1.0f;
    stamp.extent_z = 1.0f;
    stamp.lifetime_seconds = 1.0f;
    stamp.max_density = 1.0f;
    expect(plan_density_stamp(stamp, pipeline.density, diagnostic)
               == VfxError::DensityInvalid,
           "density failure");
    stamp.density = 0.5f;
    expect(plan_density_stamp(stamp, pipeline.density, diagnostic)
               == VfxError::None,
           "density recovery");

    VfxPoolDesc pool{};
    pool.pool_id = 9;
    pool.capacity = 4;
    pool.generation = 3;
    pool.expected_generation = 3;
    pool.particles = 5;
    expect(plan_pool(pool, VfxQualityBudget{16, 4, 4, 2}, pipeline.pool,
                     diagnostic) == VfxError::PoolExhausted,
           "pool failure");
    pool.capacity = 64;
    expect(plan_pool(pool, VfxQualityBudget{16, 4, 4, 2}, pipeline.pool,
                     diagnostic) == VfxError::None,
           "pool recovery");
    return finish();
}

bool run_qlfg804() {
    begin();
    VfxDiagnostic diagnostic{};
    VfxGraphDesc too_large = graph_desc();
    too_large.node_count = kMaxGraphNodes + 1;
    VfxGraphPlan graph{};
    VfxPoolDesc pool{};
    pool.pool_id = 9;
    pool.capacity = 8;
    pool.generation = 1;
    pool.expected_generation = 1;
    pool.particles = 9;
    VfxPoolPlan pool_plan{};
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        expect(validate_graph(too_large, graph, diagnostic)
                   == VfxError::GraphTooComplex,
               "graph cap bounded");
        expect(plan_pool(pool, VfxQualityBudget{16, 4, 4, 2}, pool_plan,
                         diagnostic) == VfxError::PoolExhausted,
               "pool cap bounded");
        if (failures != 0) {
            break;
        }
    }
    expect(!graph.acyclic && pool_plan.available == 0, "caps reset");
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        Pipeline pipeline{};
        expect(run_pipeline(pipeline), "bounded pipeline succeeds");
        if (failures != 0) {
            break;
        }
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx08_vfx_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlfg801") { success = run_qlfg801(); }
    else if (mode == "qlfg802") { success = run_qlfg802(); }
    else if (mode == "qlfg803") { success = run_qlfg803(); }
    else if (mode == "qlfg804") { success = run_qlfg804(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
