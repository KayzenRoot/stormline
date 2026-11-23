#include "stormline/graphics/lighting/probe_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::lighting;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] ProbeVolumeDesc probe(u32 id, u64 generation = 7) {
    ProbeVolumeDesc value{};
    value.id = id;
    value.revision = 1;
    value.scene_generation = generation;
    value.origin = Vec3{1.0f, 2.0f, 3.0f};
    value.spacing = 1.0f;
    value.cells_x = 4;
    value.cells_y = 4;
    value.cells_z = 4;
    return value;
}

bool run_prb01() {
    begin();
    ProbePlan plan{};
    LightingDiagnostic diagnostic{};

    expect(plan_probes(ProbeVolumeSet{}, 7, plan, diagnostic)
               == LightingError::None,
           "empty");
    expect(plan.count == 0, "empty count");

    ProbeVolumeSet set{};
    set.count = 2;
    set.probes[0] = probe(20);
    set.probes[1] = probe(10);
    expect(plan_probes(set, 7, plan, diagnostic) == LightingError::None,
           "plan");
    expect(plan.count == 2 && plan.probe_ids[0] == 10
               && plan.probe_ids[1] == 20,
           "sorted ids");

    set.probes[1].scene_generation = 6;
    expect(plan_probes(set, 7, plan, diagnostic) == LightingError::HistoryInvalid,
           "stale generation");
    expect(plan.count == 0, "stale reset");
    set.probes[1] = probe(10);

    set.probes[1].id = 0;
    expect(plan_probes(set, 7, plan, diagnostic) == LightingError::InvalidProbe,
           "zero id");
    set.probes[1] = probe(10);
    set.probes[1].revision = 0;
    expect(plan_probes(set, 7, plan, diagnostic) == LightingError::InvalidProbe,
           "zero revision");
    set.probes[1] = probe(20);
    expect(plan_probes(set, 7, plan, diagnostic) == LightingError::DuplicateId,
           "duplicate id");
    set.probes[1] = probe(10);
    set.probes[1].origin.y = std::numeric_limits<f32>::infinity();
    expect(plan_probes(set, 7, plan, diagnostic) == LightingError::InvalidProbe,
           "origin");
    set.probes[1] = probe(10);
    set.probes[1].spacing = 0.0f;
    expect(plan_probes(set, 7, plan, diagnostic) == LightingError::InvalidProbe,
           "spacing zero");
    set.probes[1].spacing = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_probes(set, 7, plan, diagnostic) == LightingError::InvalidProbe,
           "spacing nan");
    set.probes[1] = probe(10);
    set.probes[1].cells_x = 0;
    expect(plan_probes(set, 7, plan, diagnostic) == LightingError::InvalidProbe,
           "cells zero");
    set.probes[1] = probe(10);
    set.probes[1].cells_x = 100;
    set.probes[1].cells_y = 100;
    set.probes[1].cells_z = 100;
    expect(plan_probes(set, 7, plan, diagnostic) == LightingError::InvalidProbe,
           "cells max");
    expect(diagnostic.index == 1, "diagnostic index");

    set.count = kMaxProbes + 1;
    expect(plan_probes(set, 7, plan, diagnostic)
               == LightingError::InvalidArgument,
           "capacity");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx06_probe_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "prb01") { success = run_prb01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
