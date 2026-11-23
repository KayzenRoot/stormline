#include "stormline/graphics/render_graph/graph_sync.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::render_graph;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] GraphDefinition base() {
    GraphDefinition graph{};
    graph.device_generation = 1;
    return graph;
}

[[nodiscard]] bool dependencies(
    const GraphDefinition& graph, DependencyPlan& plan) {
    GraphDiagnostic diagnostic{};
    return build_dependency_plan(graph, plan, diagnostic) == GraphError::None;
}

bool run_syn01() {
    begin();
    GraphDefinition graph = base();
    (void)add_pass(graph, PassDesc{10, rhi::QueueRole::Graphics,
                                   PassKind::Graphics, false});
    (void)add_pass(graph, PassDesc{20, rhi::QueueRole::Compute,
                                   PassKind::Compute, false});
    (void)add_resource(graph, ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_use(graph, UseDesc{10, 1, Access::Write});
    (void)add_use(graph, UseDesc{20, 1, Access::Read});
    DependencyPlan graph_dependencies{};
    expect(dependencies(graph, graph_dependencies), "dependencies");

    SyncPlan plan{};
    GraphDiagnostic diagnostic{};
    expect(plan_sync(graph, graph_dependencies, plan, diagnostic)
               == GraphError::None,
           "sync");
    expect(plan.transition_count == 2, "transition count");
    expect(plan.transitions[0].resource_id == 1
               && plan.transitions[0].old_access == GraphAccess::None
               && plan.transitions[0].new_access == GraphAccess::Write
               && plan.transitions[0].old_queue == rhi::QueueRole::Graphics
               && plan.transitions[0].new_queue == rhi::QueueRole::Graphics
               && plan.transitions[0].before_pass == 10,
           "initial transition");
    expect(plan.transitions[1].old_access == GraphAccess::Write
               && plan.transitions[1].new_access == GraphAccess::Read
               && plan.transitions[1].old_queue == rhi::QueueRole::Graphics
               && plan.transitions[1].new_queue == rhi::QueueRole::Compute
               && plan.transitions[1].before_pass == 20,
           "queue/access transition");

    GraphDefinition reads = base();
    (void)add_pass(reads, PassDesc{10, rhi::QueueRole::Graphics,
                                   PassKind::Graphics, false});
    (void)add_pass(reads, PassDesc{20, rhi::QueueRole::Graphics,
                                   PassKind::Graphics, false});
    (void)add_resource(reads, ResourceDesc{1, ResourceKind::External, 64, 8});
    (void)add_use(reads, UseDesc{10, 1, Access::Read});
    (void)add_use(reads, UseDesc{20, 1, Access::Read});
    expect(dependencies(reads, graph_dependencies), "read dependencies");
    expect(plan_sync(reads, graph_dependencies, plan, diagnostic)
               == GraphError::None,
           "read sync");
    expect(plan.transition_count == 1, "read transition");

    GraphDefinition duplicate = base();
    (void)add_pass(duplicate, PassDesc{10, rhi::QueueRole::Graphics,
                                       PassKind::Graphics, false});
    (void)add_resource(duplicate, ResourceDesc{1, ResourceKind::External, 64, 8});
    (void)add_use(duplicate, UseDesc{10, 1, Access::Read});
    (void)add_use(duplicate, UseDesc{10, 1, Access::Read});
    expect(dependencies(duplicate, graph_dependencies), "duplicate dependencies");
    expect(plan_sync(duplicate, graph_dependencies, plan, diagnostic)
               == GraphError::None,
           "duplicate sync");
    expect(plan.transition_count == 1, "duplicate transition");

    DependencyPlan invalid{};
    expect(plan_sync(graph, invalid, plan, diagnostic) == GraphError::InvalidArgument,
           "missing dependencies");
    invalid.order_count = 1;
    invalid.order[0] = 10;
    expect(plan_sync(graph, invalid, plan, diagnostic) == GraphError::InvalidArgument,
           "short dependencies");
    invalid.order_count = 2;
    invalid.order[0] = 10;
    invalid.order[1] = 10;
    expect(plan_sync(graph, invalid, plan, diagnostic) == GraphError::InvalidArgument,
           "duplicate order");

    GraphDefinition invalid_graph{};
    expect(plan_sync(invalid_graph, invalid, plan, diagnostic)
               == GraphError::InvalidArgument,
           "invalid graph");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx03_sync_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "syn01") { success = run_syn01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
