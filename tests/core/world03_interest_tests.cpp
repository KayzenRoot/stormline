#include "stormline/spatial/interest_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::spatial;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

InterestBounds bounds(f32 min_x, f32 min_z, f32 max_x, f32 max_z) {
    InterestBounds value{};
    value.min_x = min_x;
    value.min_z = min_z;
    value.max_x = max_x;
    value.max_z = max_z;
    return value;
}

InterestSourceDesc source(
    u32 id, InterestRole role, InterestBounds box, bool required) {
    InterestSourceDesc desc{};
    desc.source_id = id;
    desc.revision = 1;
    desc.role = role;
    desc.bounds = box;
    desc.priority = id;
    desc.required_complete = required;
    return desc;
}

InterestSetDesc interest_set() {
    InterestSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 3;
    desc.source_count = 3;
    desc.sources[0] = source(1, InterestRole::Player,
                             bounds(-4.0f, -2.0f, 4.0f, 2.0f), true);
    desc.sources[1] = source(2, InterestRole::Camera,
                             bounds(-8.0f, -1.0f, 8.0f, 1.0f), true);
    desc.sources[2] = source(3, InterestRole::Ai,
                             bounds(0.0f, -6.0f, 2.0f, 6.0f), false);
    return desc;
}

bool run_int01() {
    begin();
    InterestSetDesc interest = interest_set();
    InterestPlan plan{};
    SpatialDiagnostic diagnostic{};
    expect(plan_interest(interest, plan, diagnostic) == SpatialError::None,
           "valid interest");
    expect(plan.source_count == 3 && plan.complete_count == 2
               && plan.incomplete_count == 1,
           "valid counts");
    expect(plan.union_bounds.min_x == -8.0f
               && plan.union_bounds.min_z == -6.0f
               && plan.union_bounds.max_x == 8.0f
               && plan.union_bounds.max_z == 6.0f,
           "union bounds");
    expect(diagnostic.code == SpatialError::None,
           "success diagnostic");
    InterestPlan repeat{};
    expect(plan_interest(interest, repeat, diagnostic) == SpatialError::None,
           "repeat interest");
    expect(plan.complete_count == repeat.complete_count
               && plan.union_bounds.max_x == repeat.union_bounds.max_x,
           "deterministic plan");

    interest.source_count = 0;
    expect(plan_interest(interest, plan, diagnostic) == SpatialError::None,
           "empty interest");
    expect(plan.source_count == 0 && plan.complete_count == 0
               && plan.incomplete_count == 0,
           "empty counts");
    expect(plan.union_bounds.min_x == 0.0f && plan.union_bounds.max_z == 0.0f,
           "empty union");

    interest = interest_set();
    interest.world_id = 0;
    expect(plan_interest(interest, plan, diagnostic)
               == SpatialError::InvalidArgument,
           "zero world");
    expect(plan.source_count == 0 && plan.complete_count == 0,
           "reset on zero world");
    interest = interest_set();
    interest.revision = 0;
    expect(plan_interest(interest, plan, diagnostic)
               == SpatialError::InvalidArgument,
           "zero revision");
    interest = interest_set();
    interest.source_count = kMaxInterestSources + 1;
    expect(plan_interest(interest, plan, diagnostic)
               == SpatialError::CapacityFull,
           "source overflow");

    interest = interest_set();
    interest.sources[1].source_id = 0;
    expect(plan_interest(interest, plan, diagnostic)
               == SpatialError::InterestInvalid,
           "zero source id");
    expect(diagnostic.index == 1, "zero source diagnostic");
    interest = interest_set();
    interest.sources[2].revision = 0;
    expect(plan_interest(interest, plan, diagnostic)
               == SpatialError::InterestInvalid,
           "zero source revision");
    interest = interest_set();
    interest.sources[2].source_id = 1;
    expect(plan_interest(interest, plan, diagnostic)
               == SpatialError::DuplicateId,
           "duplicate source id");
    expect(diagnostic.source_id == 1 && diagnostic.index == 2,
           "duplicate source diagnostic");
    interest = interest_set();
    interest.sources[0].role =
        static_cast<InterestRole>(static_cast<u8>(99));
    expect(plan_interest(interest, plan, diagnostic)
               == SpatialError::InterestInvalid,
           "unknown role");

    interest = interest_set();
    interest.sources[0].bounds.min_x =
        std::numeric_limits<f32>::quiet_NaN();
    expect(plan_interest(interest, plan, diagnostic)
               == SpatialError::NonFiniteValue,
           "nan bounds");
    interest = interest_set();
    interest.sources[1].bounds.max_z =
        std::numeric_limits<f32>::infinity();
    expect(plan_interest(interest, plan, diagnostic)
               == SpatialError::NonFiniteValue,
           "infinite bounds");
    expect(diagnostic.source_id == 2, "nonfinite source diagnostic");
    interest = interest_set();
    interest.sources[0].bounds.min_x = 4.0f;
    expect(plan_interest(interest, plan, diagnostic)
               == SpatialError::OutOfRange,
           "reversed x bounds");
    interest = interest_set();
    interest.sources[1].bounds.min_z = 1.0f;
    expect(plan_interest(interest, plan, diagnostic)
               == SpatialError::OutOfRange,
           "reversed z bounds");
    expect(diagnostic.index == 1, "range index diagnostic");

    interest = interest_set();
    interest.source_count = kMaxInterestSources;
    for (u32 index = 0; index < kMaxInterestSources; ++index) {
        interest.sources[index] =
            source(index + 1, InterestRole::Player,
                   bounds(static_cast<f32>(index),
                          static_cast<f32>(index),
                          static_cast<f32>(index) + 1.0f,
                          static_cast<f32>(index) + 1.0f),
                   index % 2 == 0);
    }
    expect(plan_interest(interest, plan, diagnostic) == SpatialError::None,
           "capacity interest");
    expect(plan.source_count == kMaxInterestSources
               && plan.complete_count == 8 && plan.incomplete_count == 8,
           "capacity counts");
    expect(plan.union_bounds.min_x == 0.0f
               && plan.union_bounds.max_x == 16.0f,
           "capacity union");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world03_interest_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "int01") { success = run_int01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
