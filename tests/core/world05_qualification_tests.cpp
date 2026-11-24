#include "stormline/procedural/seed_plan.hpp"
#include "stormline/procedural/graph_plan.hpp"
#include "stormline/procedural/rule_plan.hpp"
#include "stormline/procedural/biome_plan.hpp"
#include "stormline/procedural/geometry_plan.hpp"
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

struct Plans {
    SeedPlan seed{};
    GraphPlan graph{};
    RulePlan rules{};
    BiomePlan biomes{};
    GeometryPlan geometry{};
    GeneratorPlan generators{};
    ProcDiagnostic diagnostic{};
};

SeedSetDesc make_seed() {
    SeedSetDesc desc{};
    desc.project_id = 10;
    desc.graph_id = 20;
    desc.seed_high = 0x123456789abcdef0ull;
    desc.seed_low = 0x0fedcba987654321ull;
    desc.domain_count = 2;
    desc.domains[0] = SeedDomainDesc{1, 1, 4};
    desc.domains[1] = SeedDomainDesc{2, 1, 8};
    return desc;
}

GraphSetDesc make_graph() {
    GraphSetDesc desc{};
    desc.graph_id = 20;
    desc.revision = 1;
    desc.node_count = 4;
    desc.edge_count = 3;
    for (u32 index = 0; index < 4; ++index) {
        GraphNodeDesc& node = desc.nodes[index];
        node.node_id = index + 1;
        node.algorithm_id = 100 + index;
        node.algorithm_version = 1;
        node.input_type = 1;
        node.output_type = 2;
        node.fan_out = index < 3 ? 1 : 0;
    }
    for (u32 index = 0; index < 3; ++index) {
        desc.edges[index] = GraphEdgeDesc{index + 1, index + 1, index + 2};
    }
    return desc;
}

RuleSetDesc make_rules() {
    RuleSetDesc desc{};
    desc.graph_id = 20;
    desc.revision = 1;
    desc.rule_count = 3;
    desc.rules[0] = RuleDesc{1, 1, 10, 0.5f, 1, true};
    desc.rules[1] = RuleDesc{2, 1, 11, 0.25f, 2, true};
    desc.rules[2] = RuleDesc{3, 1, 12, 0.75f, 3, false};
    return desc;
}

BiomeSetDesc make_biomes() {
    BiomeSetDesc desc{};
    desc.graph_id = 20;
    desc.revision = 1;
    desc.zone_count = 3;
    desc.zones[0] = BiomeZoneDesc{1, 1, 100, 0.5f, 1, true};
    desc.zones[1] = BiomeZoneDesc{2, 1, 101, 0.25f, 2, true};
    desc.zones[2] = BiomeZoneDesc{3, 1, 102, 0.75f, 3, false};
    return desc;
}

GeometrySetDesc make_geometry() {
    GeometrySetDesc desc{};
    desc.graph_id = 20;
    desc.revision = 1;
    desc.recipe_count = 4;
    for (u32 index = 0; index < 4; ++index) {
        desc.recipes[index] = GeometryRecipeDesc{
            index + 1, 1, static_cast<PrimitiveKind>(index),
            100 + index, static_cast<f32>(index + 1), 1};
    }
    return desc;
}

GeneratorSetDesc make_generators() {
    GeneratorSetDesc desc{};
    desc.graph_id = 20;
    desc.revision = 1;
    desc.generator_count = 4;
    for (u32 index = 0; index < 4; ++index) {
        desc.generators[index] = ContentGeneratorDesc{
            index + 1, 1, static_cast<GeneratorCategory>(index),
            index + 1, 256};
    }
    return desc;
}

bool plan_all(const SeedSetDesc& seed, const GraphSetDesc& graph,
              const RuleSetDesc& rules, const BiomeSetDesc& biomes,
              const GeometrySetDesc& geometry,
              const GeneratorSetDesc& generators, Plans& plans) {
    return plan_seed_domains(seed, plans.seed, plans.diagnostic)
               == ProcError::None
           && plan_graph(graph, plans.graph, plans.diagnostic)
               == ProcError::None
           && plan_rules(rules, plans.rules, plans.diagnostic)
               == ProcError::None
           && plan_biomes(biomes, plans.biomes, plans.diagnostic)
               == ProcError::None
           && plan_geometry(geometry, plans.geometry, plans.diagnostic)
               == ProcError::None
           && plan_generators(generators, plans.generators, plans.diagnostic)
               == ProcError::None;
}

bool run_qlfw501() {
    begin();
    Plans plans{};
    expect(plan_all(make_seed(), make_graph(), make_rules(), make_biomes(),
                    make_geometry(), make_generators(), plans),
           "integrated plans");
    expect(plans.seed.domain_count == 2 && plans.seed.total_channels == 12,
           "seed plan");
    expect(plans.graph.node_count == 4 && plans.graph.max_depth == 4
               && plans.graph.root_count == 1,
           "graph plan");
    expect(plans.rules.enabled_count == 2 && plans.rules.max_priority == 3,
           "rules plan");
    expect(plans.biomes.enabled_count == 2
               && plans.biomes.total_weight == 1.5f,
           "biomes plan");
    expect(plans.geometry.recipe_count == 4
               && plans.geometry.max_unit_scale == 4.0f,
           "geometry plan");
    expect(plans.generators.generator_count == 4
               && plans.generators.total_output_cap == 1024,
           "generator plan");
    expect(plans.diagnostic.code == ProcError::None,
           "integrated diagnostic");
    return finish();
}

bool run_qlfw502() {
    begin();
    const SeedSetDesc seed = make_seed();
    const GraphSetDesc graph = make_graph();
    const RuleSetDesc rules = make_rules();
    const BiomeSetDesc biomes = make_biomes();
    const GeometrySetDesc geometry = make_geometry();
    const GeneratorSetDesc generators = make_generators();
    Plans first{};
    expect(plan_all(seed, graph, rules, biomes, geometry, generators, first),
           "deterministic first");
    for (u32 attempt = 0; attempt < 100; ++attempt) {
        Plans repeat{};
        expect(plan_all(seed, graph, rules, biomes, geometry, generators,
                        repeat),
               "deterministic repeat success");
        expect(repeat.seed.total_channels == first.seed.total_channels,
               "seed identical");
        expect(repeat.graph.max_depth == first.graph.max_depth,
               "graph identical");
        expect(repeat.rules.enabled_count == first.rules.enabled_count,
               "rules identical");
        expect(repeat.biomes.total_weight == first.biomes.total_weight,
               "biomes identical");
        expect(repeat.geometry.max_unit_scale
                   == first.geometry.max_unit_scale,
               "geometry identical");
        expect(repeat.generators.total_output_cap
                   == first.generators.total_output_cap,
               "generators identical");
    }
    return finish();
}

bool run_qlfw503() {
    begin();
    Plans plans{};
    SeedSetDesc seed = make_seed();
    seed.domains[1].domain_id = 1;
    expect(plan_seed_domains(seed, plans.seed, plans.diagnostic)
               == ProcError::DuplicateId,
           "seed failure");
    expect(plans.seed.domain_count == 0, "seed reset");
    seed = make_seed();
    expect(plan_seed_domains(seed, plans.seed, plans.diagnostic)
               == ProcError::None,
           "seed recovery");

    GraphSetDesc graph = make_graph();
    graph.nodes[3].node_id = 1;
    expect(plan_graph(graph, plans.graph, plans.diagnostic)
               == ProcError::DuplicateId,
           "graph failure");
    expect(plans.graph.node_count == 0, "graph reset");
    graph = make_graph();
    expect(plan_graph(graph, plans.graph, plans.diagnostic)
               == ProcError::None,
           "graph recovery");

    RuleSetDesc rules = make_rules();
    rules.rules[2].rule_id = 1;
    expect(plan_rules(rules, plans.rules, plans.diagnostic)
               == ProcError::DuplicateId,
           "rules failure");
    rules = make_rules();
    expect(plan_rules(rules, plans.rules, plans.diagnostic)
               == ProcError::None,
           "rules recovery");

    BiomeSetDesc biomes = make_biomes();
    biomes.zones[2].zone_id = 1;
    expect(plan_biomes(biomes, plans.biomes, plans.diagnostic)
               == ProcError::DuplicateId,
           "biomes failure");
    biomes = make_biomes();
    expect(plan_biomes(biomes, plans.biomes, plans.diagnostic)
               == ProcError::None,
           "biomes recovery");

    GeometrySetDesc geometry = make_geometry();
    geometry.recipes[3].recipe_id = 1;
    expect(plan_geometry(geometry, plans.geometry, plans.diagnostic)
               == ProcError::DuplicateId,
           "geometry failure");
    geometry = make_geometry();
    expect(plan_geometry(geometry, plans.geometry, plans.diagnostic)
               == ProcError::None,
           "geometry recovery");

    GeneratorSetDesc generators = make_generators();
    generators.generators[3].generator_id = 1;
    expect(plan_generators(generators, plans.generators, plans.diagnostic)
               == ProcError::DuplicateId,
           "generators failure");
    generators = make_generators();
    expect(plan_generators(generators, plans.generators, plans.diagnostic)
               == ProcError::None,
           "generators recovery");
    return finish();
}

bool run_qlfw504() {
    begin();
    Plans plans{};
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        SeedSetDesc seed = make_seed();
        seed.domain_count = kMaxSeedDomains;
        for (u32 index = 0; index < kMaxSeedDomains; ++index) {
            seed.domains[index] = SeedDomainDesc{index + 1, 1, 8};
        }
        expect(plan_seed_domains(seed, plans.seed, plans.diagnostic)
                   == ProcError::None,
               "overload seed");
        expect(plans.seed.total_channels <= 128, "seed cap");

        GraphSetDesc graph = make_graph();
        graph.node_count = kMaxGraphDepth;
        graph.edge_count = kMaxGraphDepth - 1;
        for (u32 index = 0; index < kMaxGraphDepth; ++index) {
            GraphNodeDesc& node = graph.nodes[index];
            node.node_id = index + 1;
            node.algorithm_id = index + 1;
            node.algorithm_version = 1;
            node.input_type = 1;
            node.output_type = 2;
            node.fan_out = index + 1 < kMaxGraphDepth ? 1 : 0;
        }
        for (u32 index = 0; index + 1 < kMaxGraphDepth; ++index) {
            graph.edges[index] = GraphEdgeDesc{index + 1, index + 1,
                                               index + 2};
        }
        expect(plan_graph(graph, plans.graph, plans.diagnostic)
                   == ProcError::None,
               "overload graph");
        expect(plans.graph.max_depth <= kMaxGraphDepth, "graph depth cap");

        RuleSetDesc rules = make_rules();
        rules.rule_count = kMaxRules;
        for (u32 index = 0; index < kMaxRules; ++index) {
            rules.rules[index] =
                RuleDesc{index + 1, 1, index + 1, 1.0f, index, false};
        }
        expect(plan_rules(rules, plans.rules, plans.diagnostic)
                   == ProcError::None,
               "overload rules");
        expect(plans.rules.rule_count <= kMaxRules, "rules cap");

        BiomeSetDesc biomes = make_biomes();
        biomes.zone_count = kMaxBiomeZones;
        for (u32 index = 0; index < kMaxBiomeZones; ++index) {
            biomes.zones[index] =
                BiomeZoneDesc{index + 1, 1, index + 1, 1.0f, index, true};
        }
        expect(plan_biomes(biomes, plans.biomes, plans.diagnostic)
                   == ProcError::None,
               "overload biomes");
        expect(plans.biomes.zone_count <= kMaxBiomeZones, "biomes cap");

        GeometrySetDesc geometry = make_geometry();
        geometry.recipe_count = kMaxGeometryRecipes;
        for (u32 index = 0; index < kMaxGeometryRecipes; ++index) {
            geometry.recipes[index] = GeometryRecipeDesc{
                index + 1, 1, static_cast<PrimitiveKind>(index % 4),
                index + 1, 1.0f, 1};
        }
        expect(plan_geometry(geometry, plans.geometry, plans.diagnostic)
                   == ProcError::None,
               "overload geometry");
        expect(plans.geometry.recipe_count <= kMaxGeometryRecipes,
               "geometry cap");

        GeneratorSetDesc generators = make_generators();
        generators.generator_count = kMaxContentGenerators;
        for (u32 index = 0; index < kMaxContentGenerators; ++index) {
            generators.generators[index] = ContentGeneratorDesc{
                index + 1, 1,
                static_cast<GeneratorCategory>(index % 4), index + 1,
                1024};
        }
        expect(plan_generators(generators, plans.generators,
                               plans.diagnostic)
                   == ProcError::None,
               "overload generators");
        expect(plans.generators.total_output_cap <= kMaxTotalOutputCap,
               "generator cap");

        if (attempt % 100 == 0) {
            seed.domain_count = kMaxSeedDomains + 1;
            expect(plan_seed_domains(seed, plans.seed, plans.diagnostic)
                       == ProcError::CapacityFull,
                   "overload seed rejection");
            expect(plans.seed.domain_count == 0, "overload seed reset");
        }
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_world05_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlfw501") { success = run_qlfw501(); }
    else if (mode == "qlfw502") { success = run_qlfw502(); }
    else if (mode == "qlfw503") { success = run_qlfw503(); }
    else if (mode == "qlfw504") { success = run_qlfw504(); }
    else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
