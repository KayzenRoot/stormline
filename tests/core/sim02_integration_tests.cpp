#include "stormline/physics3d/integration_plan.hpp"

#include <cstdio>
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

IntegrationDesc entry(u32 id, IntegrationKind kind) {
    IntegrationDesc desc{};
    desc.integration_id = id;
    desc.revision = 1;
    desc.kind = kind;
    desc.world_id = 10;
    switch (kind) {
        case IntegrationKind::Scene:
            desc.scene_id = 20;
            break;
        case IntegrationKind::Streaming:
            desc.cell_id = 30;
            break;
        case IntegrationKind::Authority:
            desc.authority_bits = 0x1;
            break;
        case IntegrationKind::Tick:
            desc.tick_hz = 60;
            break;
    }
    return desc;
}

IntegrationSetDesc integration_set() {
    IntegrationSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.integration_count = 4;
    desc.integrations[0] = entry(1, IntegrationKind::Scene);
    desc.integrations[1] = entry(2, IntegrationKind::Streaming);
    desc.integrations[2] = entry(3, IntegrationKind::Authority);
    desc.integrations[3] = entry(4, IntegrationKind::Tick);
    desc.integrations[3].tick_hz = 30;
    return desc;
}

bool run_integration301() {
    begin();
    IntegrationSetDesc integrations = integration_set();
    IntegrationPlan plan{};
    Physics3DDiagnostic diagnostic{};
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::None,
           "valid integrations");
    expect(plan.integration_count == 4 && plan.scene_count == 1
               && plan.streaming_count == 1 && plan.authority_count == 1
               && plan.tick_count == 1 && plan.min_tick_hz == 30
               && plan.max_tick_hz == 30,
           "valid plan");
    expect(diagnostic.code == Physics3DError::None, "success diagnostic");

    IntegrationPlan repeat{};
    expect(plan_integrations(integrations, repeat, diagnostic)
               == Physics3DError::None,
           "repeat integrations");
    expect(repeat.min_tick_hz == plan.min_tick_hz, "deterministic plan");

    integrations.world_id = 0;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "zero world");
    expect(plan.integration_count == 0, "reset on zero world");
    integrations = integration_set();
    integrations.revision = 0;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "zero revision");
    integrations = integration_set();
    integrations.integration_count = kMaxIntegrations + 1;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::CapacityFull,
           "integration overflow");

    integrations = integration_set();
    integrations.integrations[1].integration_id = 0;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::IntegrationInvalid,
           "zero integration id");
    expect(diagnostic.index == 1, "zero integration diagnostic");
    integrations = integration_set();
    integrations.integrations[1].revision = 0;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::IntegrationInvalid,
           "zero revision");
    integrations = integration_set();
    integrations.integrations[1].kind = static_cast<IntegrationKind>(9);
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::IntegrationInvalid,
           "invalid kind");
    integrations = integration_set();
    integrations.integrations[1].world_id = 0;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::IntegrationInvalid,
           "zero descriptor world");
    integrations = integration_set();
    integrations.integrations[1].world_id = 11;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::InvalidArgument,
           "world mismatch");
    integrations = integration_set();
    integrations.integrations[0].scene_id = 0;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::IntegrationInvalid,
           "scene requirement");
    integrations = integration_set();
    integrations.integrations[1].cell_id = 0;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::IntegrationInvalid,
           "streaming requirement");
    integrations = integration_set();
    integrations.integrations[2].authority_bits = 0;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::IntegrationInvalid,
           "authority requirement");
    integrations = integration_set();
    integrations.integrations[3].tick_hz = 0;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "zero tick");
    integrations = integration_set();
    integrations.integrations[3].tick_hz = kMaxTickHz + 1;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::OutOfRange,
           "tick overflow");
    integrations = integration_set();
    integrations.integrations[2].integration_id = 1;
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::DuplicateId,
           "duplicate integration");
    expect(diagnostic.index == 2, "duplicate integration diagnostic");

    integrations = integration_set();
    integrations.integration_count = kMaxIntegrations;
    for (u32 index = 0; index < kMaxIntegrations; ++index) {
        integrations.integrations[index] =
            entry(index + 1, static_cast<IntegrationKind>(index % 4));
        if (index % 4 == 3) {
            integrations.integrations[index].tick_hz = 24 + index;
        }
    }
    expect(plan_integrations(integrations, plan, diagnostic)
               == Physics3DError::None,
           "capacity integrations");
    expect(plan.integration_count == kMaxIntegrations
               && plan.tick_count == kMaxIntegrations / 4
               && plan.min_tick_hz == 27 && plan.max_tick_hz == 87,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim02_integration_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "integration301") { success = run_integration301(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
