#include "stormline/physics2d/query_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::physics2d;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

QueryDesc query(
    u32 id, QueryKind kind, f32 distance, u32 results,
    u32 mask = 0xffffffffu) {
    QueryDesc desc{};
    desc.query_id = id;
    desc.revision = 1;
    desc.kind = kind;
    desc.origin_x = 1.0f;
    desc.origin_y = -1.0f;
    desc.direction_x = 1.0f;
    desc.direction_y = 0.0f;
    desc.max_distance = distance;
    desc.mask_bits = mask;
    desc.max_results = results;
    return desc;
}

QuerySetDesc query_set() {
    QuerySetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.query_count = 3;
    desc.queries[0] = query(1, QueryKind::Ray, 10.0f, 8);
    desc.queries[1] = query(2, QueryKind::Overlap, 0.0f, 16);
    desc.queries[2] = query(3, QueryKind::ShapeCast, 5.0f, 4);
    return desc;
}

bool run_qry01() {
    begin();
    QuerySetDesc queries = query_set();
    QueryPlan plan{};
    Physics2DDiagnostic diagnostic{};
    expect(plan_queries(queries, plan, diagnostic) == Physics2DError::None,
           "valid queries");
    expect(plan.query_count == 3 && plan.ray_count == 1
               && plan.overlap_count == 1 && plan.shape_cast_count == 1
               && plan.total_result_limit == 28,
           "valid plan");
    expect(diagnostic.code == Physics2DError::None, "success diagnostic");
    QueryPlan repeat{};
    expect(plan_queries(queries, repeat, diagnostic) == Physics2DError::None,
           "repeat queries");
    expect(repeat.total_result_limit == plan.total_result_limit
               && repeat.ray_count == plan.ray_count,
           "deterministic plan");

    queries.world_id = 0;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::InvalidArgument,
           "zero world");
    expect(plan.query_count == 0 && plan.total_result_limit == 0,
           "reset on zero world");
    queries = query_set();
    queries.revision = 0;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::InvalidArgument,
           "zero revision");
    queries = query_set();
    queries.query_count = kMaxQueries + 1;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::CapacityFull,
           "query overflow");

    queries = query_set();
    queries.queries[1].query_id = 0;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::QueryInvalid,
           "zero query id");
    expect(diagnostic.index == 1, "zero query diagnostic");
    queries = query_set();
    queries.queries[1].revision = 0;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::QueryInvalid,
           "zero query revision");
    queries = query_set();
    queries.queries[1].kind =
        static_cast<QueryKind>(static_cast<u8>(99));
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::QueryInvalid,
           "unknown kind");
    queries = query_set();
    queries.queries[1].mask_bits = 0;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::QueryInvalid,
           "zero mask");
    queries = query_set();
    queries.queries[2].query_id = 1;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::DuplicateId,
           "duplicate query");
    expect(diagnostic.index == 2, "duplicate query diagnostic");

    queries = query_set();
    queries.queries[0].origin_x = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::NonFiniteValue,
           "nan origin");
    queries = query_set();
    queries.queries[0].max_results = 0;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::OutOfRange,
           "zero results");
    queries = query_set();
    queries.queries[0].max_results = kMaxQueryResults + 1;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::OutOfRange,
           "results overflow");
    queries = query_set();
    queries.queries[0].max_distance = 0.0f;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::OutOfRange,
           "zero ray distance");
    queries = query_set();
    queries.queries[1].max_distance = -1.0f;
    expect(plan_queries(queries, plan, diagnostic)
               == Physics2DError::OutOfRange,
           "negative overlap distance");
    queries = query_set();
    queries.queries[0].max_results = 512;
    queries.queries[1].max_results = 512;
    queries.queries[2].max_results = 512;
    expect(plan_queries(queries, plan, diagnostic) == Physics2DError::None,
           "result limit sum");
    expect(plan.total_result_limit == 1536, "result limit value");

    queries = query_set();
    queries.query_count = kMaxQueries;
    for (u32 index = 0; index < kMaxQueries; ++index) {
        queries.queries[index] =
            query(index + 1, static_cast<QueryKind>(index % 3),
                  static_cast<f32>(index + 1), 256);
    }
    expect(plan_queries(queries, plan, diagnostic) == Physics2DError::None,
           "capacity queries");
    expect(plan.query_count == kMaxQueries && plan.ray_count == 11
               && plan.overlap_count == 11 && plan.shape_cast_count == 10
               && plan.total_result_limit == 8192,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim01_query_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qry01") { success = run_qry01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
