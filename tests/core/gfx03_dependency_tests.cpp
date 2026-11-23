#include "stormline/graphics/render_graph/graph_dependency.hpp"

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

bool run_dep01() {
    begin();
    GraphDefinition simple = base();
    expect(add_pass(simple, PassDesc{10, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false}) == GraphError::None,
           "simple pass 10");
    expect(add_pass(simple, PassDesc{20, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false}) == GraphError::None,
           "simple pass 20");
    expect(add_resource(simple, ResourceDesc{1, ResourceKind::Transient, 64, 8})
               == GraphError::None, "simple resource");
    expect(add_use(simple, UseDesc{10, 1, Access::Write}) == GraphError::None,
           "simple write");
    expect(add_use(simple, UseDesc{20, 1, Access::Read}) == GraphError::None,
           "simple read");
    DependencyPlan plan{};
    GraphDiagnostic diagnostic{};
    expect(build_dependency_plan(simple, plan, diagnostic) == GraphError::None,
           "simple plan");
    expect(plan.order_count == 2 && plan.order[0] == 10 && plan.order[1] == 20,
           "simple order");
    expect(plan.edge_count == 1 && plan.edges[0].producer_pass == 10
               && plan.edges[0].consumer_pass == 20
               && plan.edges[0].hazard == Hazard::RAW,
           "simple edge");

    GraphDefinition reversed = base();
    (void)add_pass(reversed, PassDesc{20, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false});
    (void)add_pass(reversed, PassDesc{10, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false});
    (void)add_resource(reversed, ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_use(reversed, UseDesc{20, 1, Access::Read});
    (void)add_use(reversed, UseDesc{10, 1, Access::Write});
    expect(build_dependency_plan(reversed, plan, diagnostic) == GraphError::None,
           "reversed plan");
    expect(plan.order[0] == 10 && plan.order[1] == 20, "topology over declaration");

    GraphDefinition independent = base();
    (void)add_pass(independent, PassDesc{10, rhi::QueueRole::Graphics,
                                         PassKind::Graphics, false});
    (void)add_pass(independent, PassDesc{20, rhi::QueueRole::Graphics,
                                         PassKind::Graphics, false});
    (void)add_resource(independent, ResourceDesc{1, ResourceKind::External, 64, 8});
    expect(build_dependency_plan(independent, plan, diagnostic) == GraphError::None
               && plan.edge_count == 0, "independent plan");
    expect(plan.order[0] == 10 && plan.order[1] == 20, "declaration tie-break");

    GraphDefinition ambiguous = base();
    (void)add_pass(ambiguous, PassDesc{10, rhi::QueueRole::Graphics,
                                       PassKind::Graphics, false});
    (void)add_pass(ambiguous, PassDesc{20, rhi::QueueRole::Graphics,
                                       PassKind::Graphics, false});
    (void)add_resource(ambiguous, ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_use(ambiguous, UseDesc{10, 1, Access::Write});
    (void)add_use(ambiguous, UseDesc{20, 1, Access::Write});
    expect(build_dependency_plan(ambiguous, plan, diagnostic)
               == GraphError::AmbiguousWriter,
           "ambiguous writer");

    GraphDefinition uninitialized = base();
    (void)add_pass(uninitialized, PassDesc{10, rhi::QueueRole::Graphics,
                                           PassKind::Graphics, false});
    (void)add_resource(uninitialized,
                       ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_use(uninitialized, UseDesc{10, 1, Access::Read});
    expect(build_dependency_plan(uninitialized, plan, diagnostic)
               == GraphError::UninitializedRead,
           "uninitialized read");

    GraphDefinition external = base();
    (void)add_pass(external, PassDesc{10, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false});
    (void)add_resource(external, ResourceDesc{1, ResourceKind::External, 64, 8});
    (void)add_use(external, UseDesc{10, 1, Access::Read});
    expect(build_dependency_plan(external, plan, diagnostic) == GraphError::None
               && plan.edge_count == 0, "external read");

    GraphDefinition cycle = base();
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
    expect(build_dependency_plan(cycle, plan, diagnostic) == GraphError::Cycle,
           "cycle");
    expect(diagnostic.code == GraphError::Cycle, "cycle diagnostic");

    GraphDefinition rw = base();
    (void)add_pass(rw, PassDesc{10, rhi::QueueRole::Graphics,
                                PassKind::Graphics, false});
    (void)add_pass(rw, PassDesc{20, rhi::QueueRole::Graphics,
                                PassKind::Graphics, false});
    (void)add_resource(rw, ResourceDesc{1, ResourceKind::Transient, 64, 8});
    (void)add_use(rw, UseDesc{10, 1, Access::ReadWrite});
    (void)add_use(rw, UseDesc{20, 1, Access::Read});
    (void)add_use(rw, UseDesc{20, 1, Access::Read});
    expect(build_dependency_plan(rw, plan, diagnostic) == GraphError::None
               && plan.edge_count == 1, "readwrite dedup");
    expect(plan.order[0] == 10 && plan.order[1] == 20, "readwrite order");

    GraphDefinition invalid{};
    expect(build_dependency_plan(invalid, plan, diagnostic)
               == GraphError::InvalidArgument,
           "invalid graph");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx03_dependency_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "dep01") { success = run_dep01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
