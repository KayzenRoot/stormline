#include "stormline/graphics/render_graph/graph_transient.hpp"

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

bool run_tra01() {
    begin();
    GraphDefinition disjoint = base();
    (void)add_pass(disjoint, PassDesc{10, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false});
    (void)add_pass(disjoint, PassDesc{20, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false});
    (void)add_pass(disjoint, PassDesc{30, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false});
    (void)add_pass(disjoint, PassDesc{40, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false});
    (void)add_resource(disjoint, ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_resource(disjoint, ResourceDesc{2, ResourceKind::Transient, 64, 8});
    (void)add_use(disjoint, UseDesc{10, 1, Access::Write});
    (void)add_use(disjoint, UseDesc{20, 1, Access::Read});
    (void)add_use(disjoint, UseDesc{30, 2, Access::Write});
    (void)add_use(disjoint, UseDesc{40, 2, Access::Read});
    DependencyPlan graph_dependencies{};
    expect(dependencies(disjoint, graph_dependencies), "disjoint deps");
    AliasPlan plan{};
    GraphDiagnostic diagnostic{};
    expect(plan_transients(disjoint, graph_dependencies, plan, diagnostic)
               == GraphError::None,
           "disjoint plan");
    expect(plan.lifetime_count == 2, "disjoint lifetimes");
    expect(plan.group_count == 1 && plan.groups[0].resource_count == 2,
           "disjoint group");
    expect(plan.alias_saved_bytes == 64, "disjoint saved");
    expect(plan.lifetimes[0].first_pass == 0 && plan.lifetimes[0].last_pass == 1,
           "first lifetime");
    expect(plan.lifetimes[1].first_pass == 2 && plan.lifetimes[1].last_pass == 3,
           "second lifetime");

    GraphDefinition overlap = base();
    (void)add_pass(overlap, PassDesc{10, rhi::QueueRole::Graphics,
                                     PassKind::Graphics, false});
    (void)add_pass(overlap, PassDesc{20, rhi::QueueRole::Graphics,
                                     PassKind::Graphics, false});
    (void)add_pass(overlap, PassDesc{30, rhi::QueueRole::Graphics,
                                     PassKind::Graphics, false});
    (void)add_pass(overlap, PassDesc{40, rhi::QueueRole::Graphics,
                                     PassKind::Graphics, false});
    (void)add_resource(overlap, ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_resource(overlap, ResourceDesc{2, ResourceKind::Transient, 64, 8});
    (void)add_use(overlap, UseDesc{10, 1, Access::Write});
    (void)add_use(overlap, UseDesc{20, 2, Access::Write});
    (void)add_use(overlap, UseDesc{30, 1, Access::Read});
    (void)add_use(overlap, UseDesc{40, 2, Access::Read});
    expect(dependencies(overlap, graph_dependencies), "overlap deps");
    expect(plan_transients(overlap, graph_dependencies, plan, diagnostic)
               == GraphError::None,
           "overlap plan");
    expect(plan.group_count == 2 && plan.alias_saved_bytes == 0,
           "overlap groups");

    GraphDefinition mismatch = base();
    (void)add_pass(mismatch, PassDesc{10, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false});
    (void)add_pass(mismatch, PassDesc{20, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false});
    (void)add_pass(mismatch, PassDesc{30, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false});
    (void)add_pass(mismatch, PassDesc{40, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false});
    (void)add_resource(mismatch, ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_resource(mismatch, ResourceDesc{2, ResourceKind::Transient, 128, 8});
    (void)add_use(mismatch, UseDesc{10, 1, Access::Write});
    (void)add_use(mismatch, UseDesc{20, 1, Access::Read});
    (void)add_use(mismatch, UseDesc{30, 2, Access::Write});
    (void)add_use(mismatch, UseDesc{40, 2, Access::Read});
    expect(dependencies(mismatch, graph_dependencies), "mismatch deps");
    expect(plan_transients(mismatch, graph_dependencies, plan, diagnostic)
               == GraphError::None,
           "mismatch plan");
    expect(plan.group_count == 2, "mismatch groups");

    GraphDefinition persistent = base();
    (void)add_pass(persistent, PassDesc{10, rhi::QueueRole::Graphics,
                                        PassKind::Graphics, false});
    (void)add_pass(persistent, PassDesc{20, rhi::QueueRole::Graphics,
                                        PassKind::Graphics, false});
    (void)add_resource(persistent, ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_resource(persistent, ResourceDesc{2, ResourceKind::Persistent, 64, 8});
    (void)add_use(persistent, UseDesc{10, 1, Access::Write});
    (void)add_use(persistent, UseDesc{20, 1, Access::Read});
    (void)add_use(persistent, UseDesc{20, 2, Access::Read});
    expect(dependencies(persistent, graph_dependencies), "persistent deps");
    expect(plan_transients(persistent, graph_dependencies, plan, diagnostic)
               == GraphError::None,
           "persistent plan");
    expect(plan.lifetime_count == 1 && plan.group_count == 1,
           "persistent excluded");

    GraphDefinition unused = base();
    (void)add_pass(unused, PassDesc{10, rhi::QueueRole::Graphics,
                                    PassKind::Graphics, false});
    (void)add_resource(unused, ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_resource(unused, ResourceDesc{2, ResourceKind::Transient, 64, 8});
    (void)add_use(unused, UseDesc{10, 1, Access::Write});
    expect(dependencies(unused, graph_dependencies), "unused deps");
    expect(plan_transients(unused, graph_dependencies, plan, diagnostic)
               == GraphError::None,
           "unused plan");
    expect(plan.lifetime_count == 1, "unused skipped");

    DependencyPlan invalid{};
    expect(plan_transients(disjoint, invalid, plan, diagnostic)
               == GraphError::InvalidArgument,
           "invalid deps");
    GraphDefinition invalid_graph{};
    expect(plan_transients(invalid_graph, invalid, plan, diagnostic)
               == GraphError::InvalidArgument,
           "invalid graph");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx03_transient_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "tra01") { success = run_tra01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
