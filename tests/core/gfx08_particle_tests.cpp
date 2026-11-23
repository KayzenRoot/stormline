#include "stormline/graphics/vfx/emitter_plan.hpp"

#include <cstdio>
#include <limits>
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

VfxGraphNode node(u32 id, VfxNodeKind kind,
                  VfxPortType input = VfxPortType::Flow,
                  VfxPortType output = VfxPortType::Flow) {
    VfxGraphNode value{};
    value.node_id = id;
    value.revision = 1;
    value.kind = kind;
    value.input_type = input;
    value.output_type = output;
    return value;
}

VfxGraphDesc valid_graph() {
    VfxGraphDesc graph{};
    graph.graph_id = 9;
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

bool run_vfx01() {
    begin();
    VfxGraphDesc graph = valid_graph();
    VfxGraphPlan plan{};
    VfxDiagnostic diagnostic{};

    expect(validate_graph(graph, plan, diagnostic) == VfxError::None,
           "valid graph");
    expect(plan.acyclic && plan.node_count == 3 && plan.edge_count == 2,
           "valid plan");
    expect(plan.order[0] == 1 && plan.order[1] == 2 && plan.order[2] == 3,
           "topological order");

    graph.graph_id = 0;
    expect(validate_graph(graph, plan, diagnostic) == VfxError::InvalidArgument,
           "zero graph id");
    expect(!plan.acyclic && plan.node_count == 0, "reset");

    graph = valid_graph();
    graph.nodes[1].node_id = 1;
    expect(validate_graph(graph, plan, diagnostic) == VfxError::DuplicateId,
           "duplicate node");
    graph = valid_graph();
    graph.nodes[1].kind = static_cast<VfxNodeKind>(200);
    expect(validate_graph(graph, plan, diagnostic) == VfxError::InvalidArgument,
           "unknown node kind");
    graph = valid_graph();
    graph.nodes[1].input_type = static_cast<VfxPortType>(200);
    expect(validate_graph(graph, plan, diagnostic) == VfxError::InvalidArgument,
           "unknown port type");
    graph = valid_graph();
    graph.edge_count = 3;
    graph.edges[2] = VfxGraphEdge{1, 1, VfxPortType::Flow};
    expect(validate_graph(graph, plan, diagnostic) == VfxError::InvalidArgument,
           "self edge");
    graph = valid_graph();
    graph.edge_count = 3;
    graph.edges[2] = VfxGraphEdge{2, 3, VfxPortType::Flow};
    expect(validate_graph(graph, plan, diagnostic) == VfxError::DuplicateId,
           "duplicate edge");
    graph = valid_graph();
    graph.edges[0] = VfxGraphEdge{1, 99, VfxPortType::Flow};
    expect(validate_graph(graph, plan, diagnostic) == VfxError::NotFound,
           "missing target");
    graph = valid_graph();
    graph.edges[0] = VfxGraphEdge{1, 2, VfxPortType::Scalar};
    expect(validate_graph(graph, plan, diagnostic) == VfxError::PortTypeMismatch,
           "port mismatch");
    graph = valid_graph();
    graph.node_count = 2;
    graph.edge_count = 2;
    graph.edges[0] = VfxGraphEdge{1, 2, VfxPortType::Flow};
    graph.edges[1] = VfxGraphEdge{2, 1, VfxPortType::Flow};
    expect(validate_graph(graph, plan, diagnostic) == VfxError::GraphCycle,
           "cycle");
    graph = valid_graph();
    graph.node_count = kMaxGraphNodes + 1;
    expect(validate_graph(graph, plan, diagnostic) == VfxError::GraphTooComplex,
           "node cap");
    graph = valid_graph();
    graph.edge_count = kMaxGraphEdges + 1;
    expect(validate_graph(graph, plan, diagnostic) == VfxError::GraphTooComplex,
           "edge cap");
    return finish();
}

VfxEmitterDesc valid_emitter() {
    VfxEmitterDesc emitter{};
    emitter.emitter_id = 5;
    emitter.revision = 1;
    emitter.graph_id = 9;
    emitter.graph_revision = 2;
    emitter.spawn_per_tick = 10;
    emitter.burst_count = 5;
    emitter.lifetime_seconds = 2.5f;
    emitter.seed = 1234;
    emitter.policy = SimulationPolicy::CpuReference;
    return emitter;
}

bool run_spawn01() {
    begin();
    VfxEmitterDesc emitter = valid_emitter();
    VfxSpawnBudget budget{20, 50};
    VfxEmitterPlan plan{};
    VfxDiagnostic diagnostic{};

    expect(plan_emitter(emitter, budget, plan, diagnostic) == VfxError::None,
           "valid emitter");
    expect(plan.spawn_per_tick == 15 && plan.alive_capacity == 50,
           "valid plan");
    expect(plan.policy == SimulationPolicy::CpuReference, "policy preserved");

    emitter.emitter_id = 0;
    expect(plan_emitter(emitter, budget, plan, diagnostic)
               == VfxError::InvalidArgument,
           "zero emitter id");
    expect(plan.spawn_per_tick == 0, "reset");

    emitter = valid_emitter();
    emitter.lifetime_seconds = 0.0f;
    expect(plan_emitter(emitter, budget, plan, diagnostic)
               == VfxError::OutOfRange,
           "zero lifetime");
    emitter.lifetime_seconds = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_emitter(emitter, budget, plan, diagnostic)
               == VfxError::NonFiniteValue,
           "nonfinite lifetime");
    emitter = valid_emitter();
    emitter.policy = static_cast<SimulationPolicy>(200);
    expect(plan_emitter(emitter, budget, plan, diagnostic)
               == VfxError::InvalidArgument,
           "unknown policy");
    emitter = valid_emitter();
    expect(plan_emitter(emitter, VfxSpawnBudget{0, 50}, plan, diagnostic)
               == VfxError::InvalidArgument,
           "zero spawn cap");
    emitter.spawn_per_tick = std::numeric_limits<u32>::max();
    emitter.burst_count = 1;
    expect(plan_emitter(emitter, budget, plan, diagnostic)
               == VfxError::OutOfRange,
           "overflow");
    emitter = valid_emitter();
    budget.max_spawn_per_tick = 14;
    expect(plan_emitter(emitter, budget, plan, diagnostic)
               == VfxError::SpawnBudgetExceeded,
           "spawn cap");
    budget = VfxSpawnBudget{20, 4};
    expect(plan_emitter(emitter, budget, plan, diagnostic)
               == VfxError::SpawnBudgetExceeded,
           "alive cap");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx08_particle_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "vfx01") { success = run_vfx01(); }
    else if (mode == "spawn01") { success = run_spawn01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
