#include "stormline/graphics/geometry/geometry_budget.hpp"

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

[[nodiscard]] GeometryMetricSet metrics() {
    GeometryMetricSet set{};
    set.count = 2;
    set.meshes[0] = GeometryMetrics{1, 100, 50, 1000};
    set.meshes[1] = GeometryMetrics{2, 200, 100, 2000};
    return set;
}

bool run_geo01() {
    begin();
    GeometryBudgetPlan plan{};
    GeometryDiagnostic diagnostic{};
    GeometryBudget budget{300, 150, 3000};
    expect(validate_geometry_budget(metrics(), budget, plan, diagnostic)
               == GeometryError::None,
           "budget");
    expect(plan.total_vertices == 300 && plan.total_triangles == 150
               && plan.total_bytes == 3000 && plan.within_budget,
           "totals");
    GeometryBudget exceeded{299, 150, 3000};
    expect(validate_geometry_budget(metrics(), exceeded, plan, diagnostic)
               == GeometryError::GeometryBudgetExceeded,
           "exceeded");
    expect(!plan.within_budget && plan.total_vertices == 300, "exceeded totals");

    GeometryMetricSet duplicate = metrics();
    duplicate.meshes[1].mesh_id = 1;
    expect(validate_geometry_budget(duplicate, budget, plan, diagnostic)
               == GeometryError::DuplicateId,
           "duplicate");
    GeometryMetricSet invalid = metrics();
    invalid.meshes[0].vertex_count = 0;
    expect(validate_geometry_budget(invalid, budget, plan, diagnostic)
               == GeometryError::InvalidArgument,
           "zero vertices");
    invalid = metrics();
    invalid.meshes[0].byte_count = 0;
    expect(validate_geometry_budget(invalid, budget, plan, diagnostic)
               == GeometryError::InvalidArgument,
           "zero bytes");
    GeometryBudget invalid_budget{0, 1, 1};
    expect(validate_geometry_budget(metrics(), invalid_budget, plan, diagnostic)
               == GeometryError::InvalidArgument,
           "zero budget");

    GeometryMetricSet many{};
    many.count = kMaxMeshes;
    for (u32 index = 0; index < kMaxMeshes; ++index) {
        many.meshes[index] = GeometryMetrics{index + 1, 1, 1, 1};
    }
    expect(validate_geometry_budget(many, GeometryBudget{64, 64, 64},
                                    plan, diagnostic) == GeometryError::None,
           "capacity");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx04_budget_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "geo01") { success = run_geo01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
