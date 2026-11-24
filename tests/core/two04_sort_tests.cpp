#include "stormline/hybrid/sort_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::hybrid;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

HybridSortObject object(
    u32 id, u32 layer_order, f32 depth, u32 tie_breaker) {
    HybridSortObject desc{};
    desc.object_id = id;
    desc.revision = 1;
    desc.layer_order = layer_order;
    desc.depth_key = depth;
    desc.tie_breaker = tie_breaker;
    return desc;
}

HybridSortDesc scene() {
    HybridSortDesc desc{};
    desc.scene_id = 50;
    desc.revision = 1;
    desc.object_count = 5;
    desc.objects[0] = object(10, 1, 5.0f, 0);
    desc.objects[1] = object(20, 0, 9.0f, 0);
    desc.objects[2] = object(30, 0, 1.0f, 2);
    desc.objects[3] = object(40, 0, 1.0f, 1);
    desc.objects[4] = object(50, 0, 1.0f, 1);
    return desc;
}

bool run_srt01() {
    begin();
    HybridSortDesc sort = scene();
    HybridSortPlan plan{};
    HybridDiagnostic diagnostic{};

    expect(plan_sort(sort, plan, diagnostic) == HybridError::None,
           "valid sort");
    expect(plan.object_count == 5 && plan.order[0] == 40 && plan.order[1] == 50
               && plan.order[2] == 30 && plan.order[3] == 20
               && plan.order[4] == 10,
           "stable sort order");
    HybridSortPlan repeat{};
    expect(plan_sort(sort, repeat, diagnostic) == HybridError::None,
           "repeat sort");
    expect(plan.order == repeat.order, "deterministic order");

    sort.object_count = 0;
    expect(plan_sort(sort, plan, diagnostic) == HybridError::SortInvalid,
           "empty sort");
    expect(plan.object_count == 0 && plan.order[0] == 0, "reset on empty");
    sort.object_count = kMaxHybridObjects + 1;
    expect(plan_sort(sort, plan, diagnostic) == HybridError::SortInvalid,
           "object overflow");

    sort = scene();
    sort.scene_id = 0;
    expect(plan_sort(sort, plan, diagnostic)
               == HybridError::InvalidArgument,
           "zero scene");
    sort = scene();
    sort.revision = 0;
    expect(plan_sort(sort, plan, diagnostic)
               == HybridError::InvalidArgument,
           "zero scene revision");

    sort = scene();
    sort.objects[0].object_id = 0;
    expect(plan_sort(sort, plan, diagnostic) == HybridError::SortInvalid,
           "zero object id");
    sort = scene();
    sort.objects[0].revision = 0;
    expect(plan_sort(sort, plan, diagnostic) == HybridError::SortInvalid,
           "zero object revision");
    sort = scene();
    sort.objects[1].object_id = 10;
    expect(plan_sort(sort, plan, diagnostic) == HybridError::DuplicateId,
           "duplicate object id");
    sort = scene();
    sort.objects[0].depth_key = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_sort(sort, plan, diagnostic) == HybridError::NonFiniteValue,
           "nan depth");
    sort = scene();
    sort.objects[0].depth_key = std::numeric_limits<f32>::infinity();
    expect(plan_sort(sort, plan, diagnostic) == HybridError::NonFiniteValue,
           "infinite depth");

    sort = scene();
    sort.object_count = kMaxHybridObjects;
    for (u32 index = 0; index < kMaxHybridObjects; ++index) {
        sort.objects[index]
            = object(index + 1, kMaxHybridObjects - index, 0.0f, 0);
    }
    expect(plan_sort(sort, plan, diagnostic) == HybridError::None,
           "capacity sort");
    expect(plan.object_count == kMaxHybridObjects
               && plan.order[0] == kMaxHybridObjects
               && plan.order[kMaxHybridObjects - 1] == 1,
           "capacity order");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two04_sort_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "srt01") { success = run_srt01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
