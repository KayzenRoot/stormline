#include "stormline/graphics/render_graph/graph_budget.hpp"

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

[[nodiscard]] bool aliases_for(
    const GraphDefinition& graph, AliasPlan& aliases) {
    DependencyPlan dependencies{};
    GraphDiagnostic diagnostic{};
    return build_dependency_plan(graph, dependencies, diagnostic)
            == GraphError::None
        && plan_transients(graph, dependencies, aliases, diagnostic)
            == GraphError::None;
}

bool run_bud01() {
    begin();
    GraphDefinition graph{};
    graph.device_generation = 1;
    (void)add_pass(graph, PassDesc{10, rhi::QueueRole::Graphics,
                                   PassKind::Graphics, false});
    (void)add_pass(graph, PassDesc{20, rhi::QueueRole::Graphics,
                                   PassKind::Graphics, false});
    (void)add_pass(graph, PassDesc{30, rhi::QueueRole::Graphics,
                                   PassKind::Graphics, false});
    (void)add_pass(graph, PassDesc{40, rhi::QueueRole::Graphics,
                                   PassKind::Graphics, false});
    (void)add_resource(graph, ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_resource(graph, ResourceDesc{2, ResourceKind::Transient, 64, 8});
    (void)add_resource(graph, ResourceDesc{3, ResourceKind::Persistent, 512, 64});
    (void)add_resource(graph, ResourceDesc{4, ResourceKind::External, 1024, 64});
    (void)add_use(graph, UseDesc{10, 1, Access::Write});
    (void)add_use(graph, UseDesc{20, 1, Access::Read});
    (void)add_use(graph, UseDesc{30, 2, Access::Write});
    (void)add_use(graph, UseDesc{40, 2, Access::Read});
    AliasPlan aliases{};
    expect(aliases_for(graph, aliases), "aliases");
    expect(aliases.group_count == 1 && aliases.alias_saved_bytes == 64,
           "alias values");

    BudgetPlan plan{};
    GraphDiagnostic diagnostic{};
    expect(plan_budget(graph, aliases, GpuBudgetSnapshot{true, 2048, 1024},
                       plan, diagnostic) == GraphError::None,
           "budget");
    expect(plan.persistent_bytes == 512, "persistent");
    expect(plan.transient_peak_bytes == 64, "transient");
    expect(plan.alias_saved_bytes == 64, "saved");
    expect(plan.required_bytes == 576 && plan.within_budget, "required");

    expect(plan_budget(graph, aliases, GpuBudgetSnapshot{false, 2048, 1024},
                       plan, diagnostic) == GraphError::BudgetUnknown,
           "unknown");
    expect(plan_budget(graph, aliases, GpuBudgetSnapshot{true, 2048, 0},
                       plan, diagnostic) == GraphError::BudgetUnknown,
           "zero headroom");
    expect(plan_budget(graph, aliases, GpuBudgetSnapshot{true, 100, 200},
                       plan, diagnostic) == GraphError::InvalidArgument,
           "headroom range");
    expect(plan_budget(graph, aliases, GpuBudgetSnapshot{true, 2048, 100},
                       plan, diagnostic) == GraphError::BudgetExceeded,
           "overcommit");
    expect(!plan.within_budget && plan.required_bytes == 576,
           "overcommit values");

    GraphDefinition history = graph;
    (void)add_resource(history, ResourceDesc{5, ResourceKind::History, 128, 64});
    AliasPlan history_aliases{};
    expect(aliases_for(history, history_aliases), "history aliases");
    expect(plan_budget(history, history_aliases,
                       GpuBudgetSnapshot{true, 2048, 1024}, plan, diagnostic)
               == GraphError::None,
           "history budget");
    expect(plan.persistent_bytes == 640 && plan.required_bytes == 704,
           "history accounting");

    GraphDefinition overflow{};
    overflow.device_generation = 1;
    (void)add_pass(overflow, PassDesc{10, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false});
    (void)add_resource(overflow,
        ResourceDesc{1, ResourceKind::Persistent, 0x7FFFFFFFFFFFFFFFULL, 1});
    (void)add_resource(overflow,
        ResourceDesc{2, ResourceKind::Persistent, 0x7FFFFFFFFFFFFFFFULL, 1});
    (void)add_resource(overflow,
        ResourceDesc{3, ResourceKind::Persistent, 0x7FFFFFFFFFFFFFFFULL, 1});
    AliasPlan empty_aliases{};
    expect(plan_budget(overflow, empty_aliases,
                       GpuBudgetSnapshot{true, 0xFFFFFFFFFFFFFFFFULL,
                                         0xFFFFFFFFFFFFFFFFULL},
                       plan, diagnostic) == GraphError::InvalidArgument,
           "persistent overflow");

    GraphDefinition bad_alias = graph;
    AliasPlan bad_aliases{};
    bad_aliases.group_count = 1;
    bad_aliases.groups[0].bytes = 0;
    bad_aliases.groups[0].resource_count = 1;
    expect(plan_budget(bad_alias, bad_aliases,
                       GpuBudgetSnapshot{true, 2048, 1024}, plan, diagnostic)
               == GraphError::InvalidArgument,
           "empty alias group");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx03_budget_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "bud01") { success = run_bud01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
