#include "stormline/world/query_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::world;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

EntityQueryDesc query() {
    EntityQueryDesc desc{};
    desc.query_id = 21;
    desc.revision = 1;
    desc.world_epoch = 3;
    desc.required_count = 3;
    desc.required_types[0] = 10;
    desc.required_types[1] = 20;
    desc.required_types[2] = 30;
    desc.excluded_count = 2;
    desc.excluded_types[0] = 40;
    desc.excluded_types[1] = 50;
    return desc;
}

bool run_qry01() {
    begin();
    EntityQueryDesc filter = query();
    EntityQueryPlan plan{};
    WorldDiagnostic diagnostic{};

    expect(plan_entity_query(filter, plan, diagnostic) == WorldError::None,
           "valid query");
    expect(plan.required_count == 3 && plan.excluded_count == 2,
           "valid plan");
    EntityQueryPlan repeat{};
    expect(plan_entity_query(filter, repeat, diagnostic) == WorldError::None,
           "repeat query");
    expect(plan.required_count == repeat.required_count
               && plan.excluded_count == repeat.excluded_count,
           "deterministic plan");

    filter.query_id = 0;
    expect(plan_entity_query(filter, plan, diagnostic)
               == WorldError::InvalidArgument,
           "zero query");
    expect(plan.required_count == 0 && plan.excluded_count == 0,
           "reset on zero query");
    filter = query();
    filter.revision = 0;
    expect(plan_entity_query(filter, plan, diagnostic)
               == WorldError::InvalidArgument,
           "zero revision");
    filter = query();
    filter.world_epoch = 0;
    expect(plan_entity_query(filter, plan, diagnostic)
               == WorldError::InvalidArgument,
           "zero epoch");

    filter = query();
    filter.required_count = 0;
    expect(plan_entity_query(filter, plan, diagnostic)
               == WorldError::QueryInvalid,
           "zero required");
    filter.required_count = kMaxQueryTypes + 1;
    expect(plan_entity_query(filter, plan, diagnostic)
               == WorldError::QueryInvalid,
           "required overflow");
    filter = query();
    filter.excluded_count = kMaxQueryTypes + 1;
    expect(plan_entity_query(filter, plan, diagnostic)
               == WorldError::QueryInvalid,
           "excluded overflow");
    filter = query();
    filter.required_types[0] = 0;
    expect(plan_entity_query(filter, plan, diagnostic)
               == WorldError::QueryInvalid,
           "zero required type");
    filter = query();
    filter.excluded_types[0] = 0;
    expect(plan_entity_query(filter, plan, diagnostic)
               == WorldError::QueryInvalid,
           "zero excluded type");
    filter = query();
    filter.required_types[1] = 10;
    expect(plan_entity_query(filter, plan, diagnostic)
               == WorldError::DuplicateId,
           "duplicate required");
    filter = query();
    filter.excluded_types[1] = 40;
    expect(plan_entity_query(filter, plan, diagnostic)
               == WorldError::DuplicateId,
           "duplicate excluded");
    filter = query();
    filter.excluded_types[0] = 10;
    expect(plan_entity_query(filter, plan, diagnostic)
               == WorldError::DuplicateId,
           "overlap sets");

    filter = query();
    filter.excluded_count = 0;
    expect(plan_entity_query(filter, plan, diagnostic) == WorldError::None,
           "no exclusions");
    expect(plan.excluded_count == 0, "no exclusions plan");

    filter = query();
    filter.required_count = kMaxQueryTypes;
    filter.excluded_count = kMaxQueryTypes;
    for (u32 index = 0; index < kMaxQueryTypes; ++index) {
        filter.required_types[index] = index + 1;
        filter.excluded_types[index] = index + 100;
    }
    expect(plan_entity_query(filter, plan, diagnostic) == WorldError::None,
           "capacity query");
    expect(plan.required_count == kMaxQueryTypes
               && plan.excluded_count == kMaxQueryTypes,
           "capacity counts");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world01_query_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qry01") { success = run_qry01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
