#include "stormline/procedural/generator_plan.hpp"

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

ContentGeneratorDesc generator(
    u32 id, GeneratorCategory category, u32 domain, u32 cap) {
    ContentGeneratorDesc desc{};
    desc.generator_id = id;
    desc.revision = 1;
    desc.category = category;
    desc.seed_domain_id = domain;
    desc.output_cap = cap;
    return desc;
}

GeneratorSetDesc generator_set() {
    GeneratorSetDesc desc{};
    desc.graph_id = 20;
    desc.revision = 1;
    desc.generator_count = 4;
    desc.generators[0] = generator(1, GeneratorCategory::Biome, 1, 128);
    desc.generators[1] = generator(2, GeneratorCategory::Geometry, 2, 256);
    desc.generators[2] = generator(3, GeneratorCategory::Placement, 3, 512);
    desc.generators[3] = generator(4, GeneratorCategory::Rule, 4, 1024);
    return desc;
}

bool run_gen01() {
    begin();
    GeneratorSetDesc generators = generator_set();
    GeneratorPlan plan{};
    ProcDiagnostic diagnostic{};
    expect(plan_generators(generators, plan, diagnostic) == ProcError::None,
           "valid generators");
    expect(plan.generator_count == 4 && plan.biome_count == 1
               && plan.geometry_count == 1 && plan.placement_count == 1
               && plan.rule_count == 1 && plan.total_output_cap == 1920,
           "valid plan");
    expect(diagnostic.code == ProcError::None, "success diagnostic");
    GeneratorPlan repeat{};
    expect(plan_generators(generators, repeat, diagnostic)
               == ProcError::None,
           "repeat generators");
    expect(repeat.total_output_cap == plan.total_output_cap
               && repeat.rule_count == plan.rule_count,
           "deterministic plan");

    generators.generator_count = 0;
    expect(plan_generators(generators, plan, diagnostic) == ProcError::None,
           "empty generators");
    expect(plan.generator_count == 0 && plan.total_output_cap == 0,
           "empty plan");

    generators = generator_set();
    generators.graph_id = 0;
    expect(plan_generators(generators, plan, diagnostic)
               == ProcError::InvalidArgument,
           "zero graph");
    expect(plan.generator_count == 0 && plan.biome_count == 0,
           "reset on zero graph");
    generators = generator_set();
    generators.revision = 0;
    expect(plan_generators(generators, plan, diagnostic)
               == ProcError::InvalidArgument,
           "zero revision");
    generators = generator_set();
    generators.generator_count = kMaxContentGenerators + 1;
    expect(plan_generators(generators, plan, diagnostic)
               == ProcError::CapacityFull,
           "generator overflow");

    generators = generator_set();
    generators.generators[1].generator_id = 0;
    expect(plan_generators(generators, plan, diagnostic)
               == ProcError::GeneratorInvalid,
           "zero generator id");
    expect(diagnostic.index == 1, "zero generator diagnostic");
    generators = generator_set();
    generators.generators[1].revision = 0;
    expect(plan_generators(generators, plan, diagnostic)
               == ProcError::GeneratorInvalid,
           "zero generator revision");
    generators = generator_set();
    generators.generators[1].seed_domain_id = 0;
    expect(plan_generators(generators, plan, diagnostic)
               == ProcError::GeneratorInvalid,
           "zero seed domain");
    generators = generator_set();
    generators.generators[1].category =
        static_cast<GeneratorCategory>(static_cast<u8>(99));
    expect(plan_generators(generators, plan, diagnostic)
               == ProcError::GeneratorInvalid,
           "unknown category");
    generators = generator_set();
    generators.generators[3].generator_id = 1;
    expect(plan_generators(generators, plan, diagnostic)
               == ProcError::DuplicateId,
           "duplicate generator");
    expect(diagnostic.index == 3, "duplicate generator diagnostic");

    generators = generator_set();
    generators.generators[0].output_cap = 0;
    expect(plan_generators(generators, plan, diagnostic)
               == ProcError::OutOfRange,
           "zero output cap");
    generators = generator_set();
    generators.generators[0].output_cap = kMaxGeneratorOutputCap + 1;
    expect(plan_generators(generators, plan, diagnostic)
               == ProcError::OutOfRange,
           "output cap overflow");
    generators = generator_set();
    generators.generator_count = 16;
    for (u32 index = 0; index < 16; ++index) {
        generators.generators[index] =
            generator(index + 1, GeneratorCategory::Biome, index + 1,
                      4096);
    }
    expect(plan_generators(generators, plan, diagnostic) == ProcError::None,
           "total cap boundary");
    expect(plan.total_output_cap == kMaxTotalOutputCap,
           "total cap exact");

    generators = generator_set();
    generators.generator_count = kMaxContentGenerators;
    for (u32 index = 0; index < kMaxContentGenerators; ++index) {
        generators.generators[index] =
            generator(index + 1,
                      static_cast<GeneratorCategory>(index % 4), index + 1,
                      1024);
    }
    expect(plan_generators(generators, plan, diagnostic) == ProcError::None,
           "capacity generators");
    expect(plan.generator_count == kMaxContentGenerators
               && plan.biome_count == 8 && plan.geometry_count == 8
               && plan.placement_count == 8 && plan.rule_count == 8
               && plan.total_output_cap == 32768,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world05_generator_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "gen01") { success = run_gen01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
