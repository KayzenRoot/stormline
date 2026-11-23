#include "stormline/graphics/render_graph/graph_budget.hpp"
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

[[nodiscard]] GraphDefinition good_graph() {
    GraphDefinition graph{};
    graph.device_generation = 1;
    (void)add_pass(graph, PassDesc{10, rhi::QueueRole::Graphics,
                                   PassKind::Graphics, false});
    (void)add_pass(graph, PassDesc{20, rhi::QueueRole::Graphics,
                                   PassKind::Graphics, false});
    (void)add_pass(graph, PassDesc{30, rhi::QueueRole::Compute,
                                   PassKind::Compute, false});
    (void)add_pass(graph, PassDesc{40, rhi::QueueRole::Compute,
                                   PassKind::Compute, false});
    (void)add_resource(graph, ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_resource(graph, ResourceDesc{2, ResourceKind::Transient, 64, 8});
    (void)add_resource(graph, ResourceDesc{3, ResourceKind::Persistent, 512, 64});
    (void)add_resource(graph, ResourceDesc{4, ResourceKind::External, 1024, 64});
    (void)add_use(graph, UseDesc{10, 1, Access::Write});
    (void)add_use(graph, UseDesc{20, 1, Access::Read});
    (void)add_use(graph, UseDesc{30, 2, Access::Write});
    (void)add_use(graph, UseDesc{40, 2, Access::Read});
    return graph;
}

struct Snapshot {
    u32 order_count{0};
    u32 edge_count{0};
    u32 transition_count{0};
    u32 lifetime_count{0};
    u32 group_count{0};
    u64 alias_saved{0};
    u64 required{0};
};

[[nodiscard]] bool pipeline(const GraphDefinition& graph, Snapshot& out) {
    DependencyPlan dependencies{};
    SyncPlan sync{};
    AliasPlan aliases{};
    BudgetPlan budget{};
    GraphDiagnostic diagnostic{};
    if (build_dependency_plan(graph, dependencies, diagnostic)
            != GraphError::None
        || plan_sync(graph, dependencies, sync, diagnostic) != GraphError::None
        || plan_transients(graph, dependencies, aliases, diagnostic)
            != GraphError::None
        || plan_budget(graph, aliases, GpuBudgetSnapshot{true, 2048, 1024},
                       budget, diagnostic) != GraphError::None) {
        return false;
    }
    out.order_count = dependencies.order_count;
    out.edge_count = dependencies.edge_count;
    out.transition_count = sync.transition_count;
    out.lifetime_count = aliases.lifetime_count;
    out.group_count = aliases.group_count;
    out.alias_saved = aliases.alias_saved_bytes;
    out.required = budget.required_bytes;
    return true;
}

bool run_qlf_g301() {
    begin();
    GraphDefinition graph = good_graph();
    Snapshot snapshot{};
    expect(pipeline(graph, snapshot), "pipeline");
    expect(snapshot.order_count == 4, "order");
    expect(snapshot.edge_count == 2, "edges");
    expect(snapshot.transition_count == 4, "transitions");
    expect(snapshot.lifetime_count == 2 && snapshot.group_count == 1,
           "lifetimes");
    expect(snapshot.alias_saved == 64, "saved");
    expect(snapshot.required == 576, "required");
    return finish();
}

bool run_qlf_g302() {
    begin();
    Snapshot first{};
    Snapshot second{};
    expect(pipeline(good_graph(), first), "first");
    expect(pipeline(good_graph(), second), "second");
    expect(first.order_count == second.order_count, "order repeat");
    expect(first.edge_count == second.edge_count, "edge repeat");
    expect(first.transition_count == second.transition_count, "transition repeat");
    expect(first.lifetime_count == second.lifetime_count, "lifetime repeat");
    expect(first.group_count == second.group_count, "group repeat");
    expect(first.alias_saved == second.alias_saved, "saved repeat");
    expect(first.required == second.required, "required repeat");
    return finish();
}

bool run_qlf_g303() {
    begin();
    GraphDefinition invalid{};
    GraphDiagnostic diagnostic{};
    DependencyPlan dependencies{};
    expect(build_dependency_plan(invalid, dependencies, diagnostic)
               == GraphError::InvalidArgument,
           "invalid graph");
    expect(build_dependency_plan(good_graph(), dependencies, diagnostic)
               == GraphError::None,
           "after invalid graph");

    GraphDefinition ambiguous = good_graph();
    (void)add_use(ambiguous, UseDesc{20, 1, Access::Write});
    expect(build_dependency_plan(ambiguous, dependencies, diagnostic)
               == GraphError::AmbiguousWriter,
           "ambiguous");
    expect(build_dependency_plan(good_graph(), dependencies, diagnostic)
               == GraphError::None,
           "after ambiguous");

    GraphDefinition uninitialized{};
    uninitialized.device_generation = 1;
    (void)add_pass(uninitialized, PassDesc{10, rhi::QueueRole::Graphics,
                                           PassKind::Graphics, false});
    (void)add_resource(uninitialized,
                       ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_use(uninitialized, UseDesc{10, 1, Access::Read});
    expect(build_dependency_plan(uninitialized, dependencies, diagnostic)
               == GraphError::UninitializedRead,
           "uninitialized");
    expect(build_dependency_plan(good_graph(), dependencies, diagnostic)
               == GraphError::None,
           "after uninitialized");

    GraphDefinition cycle{};
    cycle.device_generation = 1;
    (void)add_pass(cycle, PassDesc{10, rhi::QueueRole::Graphics,
                                   PassKind::Graphics, false});
    (void)add_pass(cycle, PassDesc{20, rhi::QueueRole::Graphics,
                                   PassKind::Graphics, false});
    (void)add_resource(cycle, ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_resource(cycle, ResourceDesc{2, ResourceKind::Transient, 64, 8});
    (void)add_use(cycle, UseDesc{10, 1, Access::Read});
    (void)add_use(cycle, UseDesc{10, 2, Access::Write});
    (void)add_use(cycle, UseDesc{20, 2, Access::Read});
    (void)add_use(cycle, UseDesc{20, 1, Access::Write});
    expect(build_dependency_plan(cycle, dependencies, diagnostic)
               == GraphError::Cycle,
           "cycle");
    expect(build_dependency_plan(good_graph(), dependencies, diagnostic)
               == GraphError::None,
           "after cycle");

    DependencyPlan empty_dependencies{};
    SyncPlan sync{};
    AliasPlan aliases{};
    expect(plan_sync(good_graph(), empty_dependencies, sync, diagnostic)
               == GraphError::InvalidArgument,
           "sync deps");
    expect(plan_transients(good_graph(), empty_dependencies, aliases, diagnostic)
               == GraphError::InvalidArgument,
           "transient deps");

    BudgetPlan budget{};
    expect(plan_budget(good_graph(), aliases, GpuBudgetSnapshot{},
                       budget, diagnostic) == GraphError::BudgetUnknown,
           "unknown budget");
    expect(build_dependency_plan(good_graph(), dependencies, diagnostic)
               == GraphError::None,
           "after unknown");
    expect(plan_transients(good_graph(), dependencies, aliases, diagnostic)
               == GraphError::None,
           "aliases for budget");
    expect(plan_budget(good_graph(), aliases, GpuBudgetSnapshot{true, 2048, 100},
                       budget, diagnostic) == GraphError::BudgetExceeded,
           "overcommit");
    expect(plan_budget(good_graph(), aliases, GpuBudgetSnapshot{true, 2048, 1024},
                       budget, diagnostic) == GraphError::None,
           "after overcommit");
    return finish();
}

bool run_qlf_g304() {
    begin();
    Snapshot snapshot{};
    for (u32 index = 0; index < 10000; ++index) {
        expect(pipeline(good_graph(), snapshot), "bounded pipeline");
        GraphDefinition invalid{};
        GraphDiagnostic diagnostic{};
        DependencyPlan dependencies{};
        expect(build_dependency_plan(invalid, dependencies, diagnostic)
                   == GraphError::InvalidArgument,
               "bounded reject");
    }
    expect(snapshot.order_count == 4 && snapshot.required == 576,
           "bounded values");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx03_graph_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") { success = run_qlf_g301(); }
    else if (mode == "qlf02") { success = run_qlf_g302(); }
    else if (mode == "qlf03") { success = run_qlf_g303(); }
    else if (mode == "qlf04") { success = run_qlf_g304(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
