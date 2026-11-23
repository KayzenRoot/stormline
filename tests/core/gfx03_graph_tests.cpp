#include "stormline/graphics/render_graph/graph_definition.hpp"

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
    (void)add_pass(graph, PassDesc{20, rhi::QueueRole::Compute,
                                   PassKind::Compute, true});
    (void)add_resource(graph, ResourceDesc{1, ResourceKind::Transient, 256, 16});
    (void)add_resource(graph, ResourceDesc{2, ResourceKind::Persistent, 512, 64});
    (void)add_use(graph, UseDesc{10, 1, Access::Write});
    (void)add_use(graph, UseDesc{20, 1, Access::Read});
    return graph;
}

bool run_def01() {
    begin();
    GraphDefinition graph = good_graph();
    GraphDiagnostic diagnostic{};
    expect(validate_graph(graph, diagnostic) == GraphError::None, "valid");
    expect(graph.pass_count == 2 && graph.resource_count == 2
               && graph.use_count == 2,
           "counts");

    GraphDefinition empty{};
    expect(validate_graph(empty, diagnostic) == GraphError::InvalidArgument,
           "empty");
    empty.device_generation = 1;
    expect(validate_graph(empty, diagnostic) == GraphError::InvalidArgument,
           "empty after generation");

    GraphDefinition duplicate = good_graph();
    expect(add_pass(duplicate, PassDesc{10, rhi::QueueRole::Graphics,
                                        PassKind::Graphics, false})
               == GraphError::DuplicatePass, "duplicate pass");
    expect(duplicate.pass_count == 2, "duplicate pass no mutation");
    expect(add_resource(duplicate, ResourceDesc{1, ResourceKind::Transient, 1, 1})
               == GraphError::DuplicateResource, "duplicate resource");
    expect(duplicate.resource_count == 2, "duplicate resource no mutation");

    GraphDefinition invalid = good_graph();
    expect(add_resource(invalid, ResourceDesc{3, ResourceKind::Transient, 0, 1})
               == GraphError::InvalidArgument, "zero bytes");
    expect(add_resource(invalid, ResourceDesc{3, ResourceKind::Transient, 1, 3})
               == GraphError::InvalidArgument, "bad alignment");
    expect(add_resource(invalid, ResourceDesc{3, ResourceKind::Transient, 1, 8192})
               == GraphError::InvalidArgument, "alignment range");
    expect(add_resource(invalid,
        ResourceDesc{3, static_cast<ResourceKind>(9), 1, 1})
               == GraphError::InvalidArgument, "resource kind");
    expect(add_pass(invalid, PassDesc{0, rhi::QueueRole::Graphics,
                                      PassKind::Graphics, false})
               == GraphError::InvalidArgument, "zero pass id");
    expect(add_pass(invalid,
        PassDesc{30, static_cast<rhi::QueueRole>(9), PassKind::Graphics, false})
               == GraphError::InvalidArgument, "queue");
    expect(add_pass(invalid,
        PassDesc{30, rhi::QueueRole::Graphics, static_cast<PassKind>(9), false})
               == GraphError::InvalidArgument, "pass kind");
    expect(add_use(invalid, UseDesc{10, 1, static_cast<Access>(9)})
               == GraphError::InvalidUse, "use access");
    expect(add_use(invalid, UseDesc{99, 1, Access::Read}) == GraphError::NotFound,
           "use pass");
    expect(add_use(invalid, UseDesc{10, 99, Access::Read}) == GraphError::NotFound,
           "use resource");

    GraphDefinition forced = good_graph();
    forced.device_generation = 0;
    expect(validate_graph(forced, diagnostic) == GraphError::InvalidArgument,
           "generation");

    GraphDefinition too_many{};
    too_many.device_generation = 1;
    for (u32 index = 0; index < kMaxPasses; ++index) {
        expect(add_pass(too_many, PassDesc{index + 1, rhi::QueueRole::Graphics,
                                           PassKind::Graphics, false})
                   == GraphError::None, "fill passes");
    }
    expect(add_pass(too_many, PassDesc{kMaxPasses + 1,
                                       rhi::QueueRole::Graphics,
                                       PassKind::Graphics, false})
               == GraphError::CapacityFull, "pass capacity");
    for (u32 index = 0; index < kMaxResources; ++index) {
        expect(add_resource(too_many,
            ResourceDesc{index + 1, ResourceKind::Transient, 1, 1})
                   == GraphError::None, "fill resources");
    }
    expect(add_resource(too_many,
        ResourceDesc{kMaxResources + 1, ResourceKind::Transient, 1, 1})
               == GraphError::CapacityFull, "resource capacity");
    for (u32 index = 0; index < kMaxUses; ++index) {
        expect(add_use(too_many,
            UseDesc{static_cast<u32>((index % kMaxPasses) + 1),
                    static_cast<u32>((index % kMaxResources) + 1),
                    Access::Read}) == GraphError::None, "fill uses");
    }
    expect(add_use(too_many, UseDesc{1, 1, Access::Read})
               == GraphError::CapacityFull, "use capacity");

    expect(std::string_view(graph_error_name(GraphError::Cycle)) == "Cycle",
           "error name");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx03_graph_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "def01") { success = run_def01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
