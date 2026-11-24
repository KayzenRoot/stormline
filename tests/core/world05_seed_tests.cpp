#include "stormline/procedural/seed_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::procedural;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

SeedDomainDesc domain(u32 id, u32 version, u32 channels) {
    SeedDomainDesc desc{};
    desc.domain_id = id;
    desc.derivation_version = version;
    desc.channel_count = channels;
    return desc;
}

SeedSetDesc seed_set() {
    SeedSetDesc desc{};
    desc.project_id = 10;
    desc.graph_id = 20;
    desc.seed_high = 0x0123456789abcdefull;
    desc.seed_low = 0xfedcba9876543210ull;
    desc.domain_count = 3;
    desc.domains[0] = domain(1, 1, 4);
    desc.domains[1] = domain(2, 1, 8);
    desc.domains[2] = domain(3, 2, 2);
    return desc;
}

bool run_seed01() {
    begin();
    SeedSetDesc seed = seed_set();
    SeedPlan plan{};
    ProcDiagnostic diagnostic{};
    expect(plan_seed_domains(seed, plan, diagnostic) == ProcError::None,
           "valid seed");
    expect(plan.domain_count == 3 && plan.total_channels == 14
               && plan.seed_high == seed.seed_high
               && plan.seed_low == seed.seed_low,
           "valid plan");
    expect(diagnostic.code == ProcError::None, "success diagnostic");
    SeedPlan repeat{};
    expect(plan_seed_domains(seed, repeat, diagnostic) == ProcError::None,
           "repeat seed");
    expect(repeat.total_channels == plan.total_channels
               && repeat.seed_high == plan.seed_high,
           "deterministic plan");

    seed.project_id = 0;
    expect(plan_seed_domains(seed, plan, diagnostic)
               == ProcError::InvalidArgument,
           "zero project");
    expect(plan.domain_count == 0 && plan.total_channels == 0,
           "reset on zero project");
    seed = seed_set();
    seed.graph_id = 0;
    expect(plan_seed_domains(seed, plan, diagnostic)
               == ProcError::InvalidArgument,
           "zero graph");
    seed = seed_set();
    seed.seed_high = 0;
    seed.seed_low = 0;
    expect(plan_seed_domains(seed, plan, diagnostic)
               == ProcError::SeedInvalid,
           "zero seed");
    seed = seed_set();
    seed.domain_count = 0;
    expect(plan_seed_domains(seed, plan, diagnostic)
               == ProcError::SeedInvalid,
           "zero domains");
    seed.domain_count = kMaxSeedDomains + 1;
    expect(plan_seed_domains(seed, plan, diagnostic)
               == ProcError::CapacityFull,
           "domain overflow");

    seed = seed_set();
    seed.domains[1].domain_id = 0;
    expect(plan_seed_domains(seed, plan, diagnostic)
               == ProcError::SeedInvalid,
           "zero domain id");
    expect(diagnostic.index == 1, "zero domain diagnostic");
    seed = seed_set();
    seed.domains[1].derivation_version = 0;
    expect(plan_seed_domains(seed, plan, diagnostic)
               == ProcError::SeedInvalid,
           "zero derivation");
    seed = seed_set();
    seed.domains[0].channel_count = 0;
    expect(plan_seed_domains(seed, plan, diagnostic)
               == ProcError::OutOfRange,
           "zero channels");
    seed = seed_set();
    seed.domains[0].channel_count = 9;
    expect(plan_seed_domains(seed, plan, diagnostic)
               == ProcError::OutOfRange,
           "channel overflow");
    seed = seed_set();
    seed.domains[2].domain_id = 1;
    expect(plan_seed_domains(seed, plan, diagnostic)
               == ProcError::DuplicateId,
           "duplicate domain");
    expect(diagnostic.index == 2, "duplicate domain diagnostic");

    seed = seed_set();
    seed.domain_count = kMaxSeedDomains;
    for (u32 index = 0; index < kMaxSeedDomains; ++index) {
        seed.domains[index] = domain(index + 1, 1, 8);
    }
    expect(plan_seed_domains(seed, plan, diagnostic) == ProcError::None,
           "capacity seed");
    expect(plan.domain_count == kMaxSeedDomains
               && plan.total_channels == 128,
           "capacity channels");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_world05_seed_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "seed01") { success = run_seed01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
