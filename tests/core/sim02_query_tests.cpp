#include "stormline/physics3d/query_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::physics3d;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

QueryDesc query(u32 id, QueryKind kind, f32 max_distance, u32 max_results) {
    QueryDesc desc{};
    desc.query_id = id;
    desc.revision = 1;
    desc.kind = kind;
    desc.origin_x = 0.0f;
    desc.origin_y = 1.0f;
    desc.origin_z = 2.0f;
    desc.direction_x = 1.0f;
    desc.direction_y = 0.0f;
    desc.direction_z = 0.0f;
    desc.max_distance = max_distance;
    desc.layer_bits = 1;
    desc.max_results = max_results;
    return desc;
}

QuerySetDesc query_set() {
    QuerySetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.query_count = 4;
    desc.queries[0] = query(1, QueryKind::Ray, 10.0f, 100);
    desc.queries[1] = query(2, QueryKind::Overlap, 1.0f, 50);
    desc.queries[2] = query(3, QueryKind::Sweep, 2.0f, 25);
    desc.queries[3] = query(4, QueryKind::ShapeCast, 3.0f, 25);
    return desc;
}

bool run_query301() {
    begin();
    QuerySetDesc queries = query_set();
    QueryPlan plan{};
    Physics3DDiagnostic diagnostic{};
    expect(plan_queries(queries, plan, diagnostic) == Physics3DError::None,
           "valid queries");
    expect(plan.query_count == 4 && plan.ray_count == 1
               && plan.overlap_count == 1 && plan.sweep_count == 1
               && plan.shape_cast_count == 1
               && plan.total_result_limit == 200,
           "valid plan");
    expect(diagnostic.code == Physics3DError::None, "success diagnostic");

    QueryPlan repeat{};
    expect(plan_queries(queries, repeat, diagnostic) == Physics3DError::None,
           "repeat queries");
    expect(repeat.total_result_limit == plan.total_result_limit,
           "deterministic plan");

    queries.world_id = 0;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "zero world");
    expect(plan.query_count == 0, "reset on zero world");
    queries = query_set();
    queries.revision = 0;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "zero revision");
    queries = query_set();
    queries.query_count = kMaxQueries + 1;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::CapacityFull,
           "query overflow");

    queries = query_set();
    queries.queries[1].query_id = 0;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::QueryInvalid,
           "zero query id");
    expect(diagnostic.index == 1, "zero query diagnostic");
    queries = query_set();
    queries.queries[1].revision = 0;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::QueryInvalid,
           "zero revision");
    queries = query_set();
    queries.queries[1].layer_bits = 0;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::QueryInvalid,
           "zero layer bits");
    queries = query_set();
    queries.queries[1].kind = static_cast<QueryKind>(9);
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::QueryInvalid,
           "invalid kind");

    queries = query_set();
    queries.queries[1].origin_z = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::NonFiniteValue,
           "non-finite origin");
    queries = query_set();
    queries.queries[0].max_results = 0;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "zero max results");
    queries = query_set();
    queries.queries[0].max_results = kMaxQueryResults + 1;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "max results overflow");
    queries = query_set();
    queries.queries[0].direction_x = 0.0f;
    queries.queries[0].direction_y = 0.0f;
    queries.queries[0].direction_z = 0.0f;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "zero ray direction");
    queries = query_set();
    queries.queries[2].max_distance = 0.0f;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "zero sweep distance");
    queries = query_set();
    queries.queries[1].max_distance = -1.0f;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "negative overlap distance");
    queries = query_set();
    queries.queries[2].query_id = 1;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics3DError::DuplicateId,
           "duplicate query");
    expect(diagnostic.index == 2, "duplicate query diagnostic");

    queries = query_set();
    queries.query_count = kMaxQueries;
    for (u32 index = 0; index < kMaxQueries; ++index) {
        queries.queries[index] =
            query(index + 1, static_cast<QueryKind>(index % 4), 1.0f, 256);
    }
    expect(plan_queries(queries, plan, diagnostic) == Physics3DError::None,
           "capacity queries");
    expect(plan.query_count == kMaxQueries
               && plan.total_result_limit == kMaxTotalQueryResults,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim02_query_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "query301") { success = run_query301(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
