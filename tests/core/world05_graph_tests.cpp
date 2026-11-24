#include "stormline/procedural/graph_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::procedural;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

GraphNodeDesc node(u32 id, u32 fan_out = 1) {
    GraphNodeDesc desc{};
    desc.node_id = id;
    desc.algorithm_id = 100 + id;
    desc.algorithm_version = 1;
    desc.input_type = 1;
    desc.output_type = 2;
    desc.fan_out = fan_out;
    return desc;
}

GraphEdgeDesc edge(u32 id, u32 from, u32 to) {
    GraphEdgeDesc desc{};
    desc.edge_id = id;
    desc.from_node = from;
    desc.to_node = to;
    return desc;
}

GraphSetDesc graph_set() {
    GraphSetDesc desc{};
    desc.graph_id = 20;
    desc.revision = 1;
    desc.node_count = 4;
    desc.edge_count = 3;
    desc.nodes[0] = node(1);
    desc.nodes[1] = node(2);
    desc.nodes[2] = node(3);
    desc.nodes[3] = node(4, 0);
    desc.edges[0] = edge(1, 1, 2);
    desc.edges[1] = edge(2, 2, 3);
    desc.edges[2] = edge(3, 3, 4);
    return desc;
}

bool run_graph01() {
    begin();
    GraphSetDesc graph = graph_set();
    GraphPlan plan{};
    ProcDiagnostic diagnostic{};
    expect(plan_graph(graph, plan, diagnostic) == ProcError::None,
           "valid graph");
    expect(plan.node_count == 4 && plan.edge_count == 3
               && plan.root_count == 1 && plan.leaf_count == 1
               && plan.max_depth == 4,
           "valid plan");
    expect(diagnostic.code == ProcError::None, "success diagnostic");
    GraphPlan repeat{};
    expect(plan_graph(graph, repeat, diagnostic) == ProcError::None,
           "repeat graph");
    expect(repeat.max_depth == plan.max_depth
               && repeat.root_count == plan.root_count,
           "deterministic plan");

    graph.graph_id = 0;
    expect(plan_graph(graph, plan, diagnostic)
               == ProcError::InvalidArgument,
           "zero graph");
    expect(plan.node_count == 0 && plan.max_depth == 0,
           "reset on zero graph");
    graph = graph_set();
    graph.revision = 0;
    expect(plan_graph(graph, plan, diagnostic)
               == ProcError::InvalidArgument,
           "zero revision");
    graph = graph_set();
    graph.node_count = 0;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::GraphInvalid,
           "zero nodes");
    graph.node_count = kMaxGraphNodes + 1;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::CapacityFull,
           "node overflow");
    graph = graph_set();
    graph.edge_count = kMaxGraphEdges + 1;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::CapacityFull,
           "edge overflow");

    graph = graph_set();
    graph.nodes[1].node_id = 0;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::GraphInvalid,
           "zero node id");
    expect(diagnostic.index == 1, "zero node diagnostic");
    graph = graph_set();
    graph.nodes[1].algorithm_id = 0;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::GraphInvalid,
           "zero algorithm");
    graph = graph_set();
    graph.nodes[1].algorithm_version = 0;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::GraphInvalid,
           "zero algorithm version");
    graph = graph_set();
    graph.nodes[1].input_type = 0;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::GraphInvalid,
           "zero input type");
    graph = graph_set();
    graph.nodes[1].output_type = 0;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::GraphInvalid,
           "zero output type");
    graph = graph_set();
    graph.nodes[1].fan_out = kMaxNodeFanOut + 1;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::GraphInvalid,
           "declared fan-out overflow");
    graph = graph_set();
    graph.nodes[2].node_id = 1;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::DuplicateId,
           "duplicate node");
    expect(diagnostic.index == 2, "duplicate node diagnostic");

    graph = graph_set();
    graph.edges[2].edge_id = 0;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::GraphInvalid,
           "zero edge id");
    graph = graph_set();
    graph.edges[2].to_node = 3;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::GraphInvalid,
           "self edge");
    graph = graph_set();
    graph.edges[1].edge_id = 1;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::DuplicateId,
           "duplicate edge id");
    graph = graph_set();
    graph.edges[1].from_node = 1;
    graph.edges[1].to_node = 2;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::DuplicateId,
           "duplicate edge pair");
    graph = graph_set();
    graph.edges[2].to_node = 99;
    expect(plan_graph(graph, plan, diagnostic) == ProcError::NotFound,
           "missing endpoint");
    graph = graph_set();
    graph.edges[2].to_node = 1;
    expect(plan_graph(graph, plan, diagnostic)
               == ProcError::CycleDetected,
           "cycle");

    graph = graph_set();
    graph.node_count = 17;
    graph.edge_count = 16;
    for (u32 index = 0; index < 17; ++index) {
        graph.nodes[index] = node(index + 1, index == 16 ? 0 : 1);
    }
    for (u32 index = 0; index < 16; ++index) {
        graph.edges[index] = edge(index + 1, index + 1, index + 2);
    }
    expect(plan_graph(graph, plan, diagnostic) == ProcError::OutOfRange,
           "depth overflow");

    graph = graph_set();
    graph.node_count = kMaxGraphNodes;
    graph.edge_count = 0;
    for (u32 index = 0; index < kMaxGraphNodes; ++index) {
        graph.nodes[index] = node(index + 1, 0);
    }
    expect(plan_graph(graph, plan, diagnostic) == ProcError::None,
           "capacity graph");
    expect(plan.root_count == kMaxGraphNodes
               && plan.leaf_count == kMaxGraphNodes && plan.max_depth == 1,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world05_graph_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "graph01") { success = run_graph01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
