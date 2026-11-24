#include "stormline/physics3d/body_plan.hpp"
#include "stormline/physics3d/shape_plan.hpp"
#include "stormline/physics3d/layer_plan.hpp"
#include "stormline/physics3d/query_plan.hpp"
#include "stormline/physics3d/constraint_plan.hpp"
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

struct Plans {
    BodyPlan bodies{};
    ShapePlan shapes{};
    LayerPlan layers{};
    QueryPlan queries{};
    ConstraintPlan constraints{};
    IntegrationPlan integrations{};
    Physics3DDiagnostic diagnostic{};
};

BodySetDesc make_bodies() {
    BodySetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.body_count = 3;
    desc.bodies[0] = BodyDesc{1, 1, BodyKind::Static, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, true,
                              false};
    desc.bodies[1] = BodyDesc{2, 1, BodyKind::Kinematic, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, false,
                              false};
    desc.bodies[2] = BodyDesc{3, 1, BodyKind::Dynamic, 2.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.1f, true,
                              true};
    return desc;
}

ShapeSetDesc make_shapes() {
    ShapeSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.shape_count = 4;
    desc.shapes[0] = ShapeDesc{1, 1, 1, ShapeKind::Sphere, 0.0f, 0.0f,
                               0.0f, 1.0f, 0.0f, 1.0f, 7, false};
    desc.shapes[1] = ShapeDesc{2, 1, 1, ShapeKind::Box, 1.0f, 1.0f, 1.0f,
                               0.0f, 0.0f, 1.0f, 7, true};
    desc.shapes[2] = ShapeDesc{3, 2, 1, ShapeKind::Capsule, 0.0f, 0.0f,
                               0.0f, 0.5f, 0.25f, 1.0f, 8, false};
    desc.shapes[3] = ShapeDesc{4, 3, 1, ShapeKind::Mesh, 1.0f, 2.0f, 1.0f,
                               0.0f, 0.0f, 1.0f, 9, false};
    return desc;
}

LayerSetDesc make_layers() {
    LayerSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.layer_count = 3;
    desc.layers[0] = LayerDesc{1, 1, 0x1, 0x2, 0};
    desc.layers[1] = LayerDesc{2, 1, 0x2, 0x1, 0};
    desc.layers[2] = LayerDesc{3, 1, 0x4, 0x8, 0};
    return desc;
}

QuerySetDesc make_queries() {
    QuerySetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.query_count = 3;
    desc.queries[0] = QueryDesc{1, 1, QueryKind::Ray, 0.0f, 0.0f, 0.0f,
                                1.0f, 0.0f, 0.0f, 10.0f, 1, 100};
    desc.queries[1] = QueryDesc{2, 1, QueryKind::Overlap, 1.0f, 1.0f, 1.0f,
                                0.0f, 0.0f, 0.0f, 1.0f, 2, 50};
    desc.queries[2] = QueryDesc{3, 2, QueryKind::Sweep, 0.0f, 1.0f, 0.0f,
                                1.0f, 1.0f, 0.0f, 2.0f, 4, 25};
    return desc;
}

ConstraintSetDesc make_constraints() {
    ConstraintSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.constraint_count = 3;
    desc.constraints[0] = ConstraintDesc{
        1, 1, ConstraintKind::Fixed, 1, 2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 10.0f, false, false};
    desc.constraints[1] = ConstraintDesc{
        2, 1, ConstraintKind::Hinge, 2, 3, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 10.0f, true, false};
    desc.constraints[2] = ConstraintDesc{
        3, 2, ConstraintKind::Slider, 1, 3, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 10.0f, false, true};
    return desc;
}

IntegrationSetDesc make_integrations() {
    IntegrationSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.integration_count = 4;
    desc.integrations[0] = IntegrationDesc{1, 1, IntegrationKind::Scene, 10,
                                           20, 0, 0, 0};
    desc.integrations[1] = IntegrationDesc{2, 1, IntegrationKind::Streaming,
                                           10, 0, 30, 0, 0};
    desc.integrations[2] = IntegrationDesc{3, 1, IntegrationKind::Authority,
                                           10, 0, 0, 0, 0x1};
    desc.integrations[3] = IntegrationDesc{4, 2, IntegrationKind::Tick, 10,
                                           0, 0, 60, 0};
    return desc;
}

bool plan_all(const BodySetDesc& bodies, const ShapeSetDesc& shapes,
              const LayerSetDesc& layers, const QuerySetDesc& queries,
              const ConstraintSetDesc& constraints,
              const IntegrationSetDesc& integrations, Plans& plans) {
    return plan_bodies(bodies, plans.bodies, plans.diagnostic)
               == Physics3DError::None
           && plan_shapes(shapes, plans.shapes, plans.diagnostic)
               == Physics3DError::None
           && plan_layers(layers, plans.layers, plans.diagnostic)
               == Physics3DError::None
           && plan_queries(queries, plans.queries, plans.diagnostic)
               == Physics3DError::None
           && plan_constraints(constraints, plans.constraints,
                               plans.diagnostic)
               == Physics3DError::None
           && plan_integrations(integrations, plans.integrations,
                                plans.diagnostic)
               == Physics3DError::None;
}

bool plan_default(Plans& plans) {
    return plan_all(make_bodies(), make_shapes(), make_layers(),
                    make_queries(), make_constraints(), make_integrations(),
                    plans);
}

bool run_qlfs201() {
    begin();
    Plans plans{};
    expect(plan_default(plans), "integrated plans");
    expect(plans.bodies.body_count == 3 && plans.bodies.static_count == 1
               && plans.bodies.kinematic_count == 1
               && plans.bodies.dynamic_count == 1
               && plans.bodies.enabled_count == 2,
           "body plan");
    expect(plans.shapes.shape_count == 4 && plans.shapes.sphere_count == 1
               && plans.shapes.box_count == 1
               && plans.shapes.capsule_count == 1
               && plans.shapes.mesh_count == 1
               && plans.shapes.sensor_count == 1,
           "shape plan");
    expect(plans.layers.layer_count == 3 && plans.layers.group_count == 0
               && plans.layers.compatible_pair_count == 1,
           "layer plan");
    expect(plans.queries.query_count == 3 && plans.queries.ray_count == 1
               && plans.queries.overlap_count == 1
               && plans.queries.sweep_count == 1
               && plans.queries.total_result_limit == 175,
           "query plan");
    expect(plans.constraints.constraint_count == 3
               && plans.constraints.fixed_count == 1
               && plans.constraints.hinge_count == 1
               && plans.constraints.slider_count == 1
               && plans.constraints.motor_count == 1
               && plans.constraints.collide_count == 1,
           "constraint plan");
    expect(plans.integrations.integration_count == 4
               && plans.integrations.scene_count == 1
               && plans.integrations.streaming_count == 1
               && plans.integrations.authority_count == 1
               && plans.integrations.tick_count == 1
               && plans.integrations.min_tick_hz == 60,
           "integration plan");
    expect(plans.diagnostic.code == Physics3DError::None,
           "integrated diagnostic");
    return finish();
}

bool run_qlfs202() {
    begin();
    Plans first{};
    expect(plan_default(first), "deterministic first");
    for (u32 attempt = 0; attempt < 100; ++attempt) {
        Plans repeat{};
        expect(plan_default(repeat), "deterministic repeat success");
        expect(repeat.bodies.enabled_count == first.bodies.enabled_count,
               "bodies identical");
        expect(repeat.shapes.sensor_count == first.shapes.sensor_count,
               "shapes identical");
        expect(repeat.layers.compatible_pair_count
                   == first.layers.compatible_pair_count,
               "layers identical");
        expect(repeat.queries.total_result_limit
                   == first.queries.total_result_limit,
               "queries identical");
        expect(repeat.constraints.motor_count == first.constraints.motor_count,
               "constraints identical");
        expect(repeat.integrations.min_tick_hz
                   == first.integrations.min_tick_hz,
               "integrations identical");
    }
    return finish();
}

bool run_qlfs203() {
    begin();
    Plans plans{};

    BodySetDesc bodies = make_bodies();
    bodies.bodies[2].body_id = 1;
    expect(plan_bodies(bodies, plans.bodies, plans.diagnostic)
               == Physics3DError::DuplicateId,
           "body failure");
    expect(plans.bodies.body_count == 0, "body reset");
    expect(plan_bodies(make_bodies(), plans.bodies, plans.diagnostic)
               == Physics3DError::None,
           "body recovery");

    ShapeSetDesc shapes = make_shapes();
    shapes.shapes[3].shape_id = 1;
    expect(plan_shapes(shapes, plans.shapes, plans.diagnostic)
               == Physics3DError::DuplicateId,
           "shape failure");
    expect(plans.shapes.shape_count == 0, "shape reset");
    expect(plan_shapes(make_shapes(), plans.shapes, plans.diagnostic)
               == Physics3DError::None,
           "shape recovery");

    LayerSetDesc layers = make_layers();
    layers.layers[2].layer_id = 1;
    expect(plan_layers(layers, plans.layers, plans.diagnostic)
               == Physics3DError::DuplicateId,
           "layer failure");
    expect(plans.layers.layer_count == 0, "layer reset");
    expect(plan_layers(make_layers(), plans.layers, plans.diagnostic)
               == Physics3DError::None,
           "layer recovery");

    QuerySetDesc queries = make_queries();
    queries.queries[2].query_id = 1;
    expect(plan_queries(queries, plans.queries, plans.diagnostic)
               == Physics3DError::DuplicateId,
           "query failure");
    expect(plans.queries.query_count == 0, "query reset");
    expect(plan_queries(make_queries(), plans.queries, plans.diagnostic)
               == Physics3DError::None,
           "query recovery");

    ConstraintSetDesc constraints = make_constraints();
    constraints.constraints[2].constraint_id = 1;
    expect(plan_constraints(constraints, plans.constraints,
                            plans.diagnostic)
               == Physics3DError::DuplicateId,
           "constraint failure");
    expect(plans.constraints.constraint_count == 0, "constraint reset");
    expect(plan_constraints(make_constraints(), plans.constraints,
                            plans.diagnostic)
               == Physics3DError::None,
           "constraint recovery");

    IntegrationSetDesc integrations = make_integrations();
    integrations.integrations[2].integration_id = 1;
    expect(plan_integrations(integrations, plans.integrations,
                             plans.diagnostic)
               == Physics3DError::DuplicateId,
           "integration failure");
    expect(plans.integrations.integration_count == 0, "integration reset");
    expect(plan_integrations(make_integrations(), plans.integrations,
                             plans.diagnostic)
               == Physics3DError::None,
           "integration recovery");
    return finish();
}

bool run_qlfs204() {
    begin();
    Plans plans{};
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        BodySetDesc bodies = make_bodies();
        bodies.body_count = kMaxBodies;
        for (u32 index = 0; index < kMaxBodies; ++index) {
            bodies.bodies[index] =
                BodyDesc{index + 1, 1, static_cast<BodyKind>(index % 3),
                         0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                         1.0f, 0.5f, index % 2 == 0, false};
        }
        expect(plan_bodies(bodies, plans.bodies, plans.diagnostic)
                   == Physics3DError::None,
               "overload bodies");
        expect(plans.bodies.body_count <= kMaxBodies, "body cap");

        ShapeSetDesc shapes = make_shapes();
        shapes.shape_count = kMaxShapes;
        for (u32 index = 0; index < kMaxShapes; ++index) {
            shapes.shapes[index] =
                ShapeDesc{index + 1, 1, 1, static_cast<ShapeKind>(index % 7),
                          1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 7,
                          index % 2 == 0};
        }
        expect(plan_shapes(shapes, plans.shapes, plans.diagnostic)
                   == Physics3DError::None,
               "overload shapes");
        expect(plans.shapes.shape_count <= kMaxShapes, "shape cap");

        LayerSetDesc layers = make_layers();
        layers.layer_count = kMaxLayers;
        for (u32 index = 0; index < kMaxLayers; ++index) {
            layers.layers[index] =
                LayerDesc{index + 1, 1, 0x1, 0x1, index < 16 ? 1u : 0u};
        }
        expect(plan_layers(layers, plans.layers, plans.diagnostic)
                   == Physics3DError::None,
               "overload layers");
        expect(plans.layers.layer_count <= kMaxLayers, "layer cap");

        QuerySetDesc queries = make_queries();
        queries.query_count = kMaxQueries;
        for (u32 index = 0; index < kMaxQueries; ++index) {
            queries.queries[index] =
                QueryDesc{index + 1, 1, static_cast<QueryKind>(index % 4),
                          0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1,
                          256};
        }
        expect(plan_queries(queries, plans.queries, plans.diagnostic)
                   == Physics3DError::None,
               "overload queries");
        expect(plans.queries.query_count <= kMaxQueries, "query cap");
        expect(plans.queries.total_result_limit <= kMaxTotalQueryResults,
               "query total cap");

        ConstraintSetDesc constraints = make_constraints();
        constraints.constraint_count = kMaxConstraints;
        for (u32 index = 0; index < kMaxConstraints; ++index) {
            constraints.constraints[index] = ConstraintDesc{
                index + 1, 1, static_cast<ConstraintKind>(index % 6),
                index + 1, index + 2, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 10.0f, index % 2 == 0,
                index % 3 == 0};
        }
        expect(plan_constraints(constraints, plans.constraints,
                                plans.diagnostic)
                   == Physics3DError::None,
               "overload constraints");
        expect(plans.constraints.constraint_count <= kMaxConstraints,
               "constraint cap");

        IntegrationSetDesc integrations = make_integrations();
        integrations.integration_count = kMaxIntegrations;
        for (u32 index = 0; index < kMaxIntegrations; ++index) {
            integrations.integrations[index] = IntegrationDesc{
                index + 1, 1, static_cast<IntegrationKind>(index % 4), 10,
                index % 4 == 0 ? 20u : 0u, index % 4 == 1 ? 30u : 0u,
                index % 4 == 3 ? 24u + index : 0u,
                index % 4 == 2 ? 1u : 0u};
        }
        expect(plan_integrations(integrations, plans.integrations,
                                 plans.diagnostic)
                   == Physics3DError::None,
               "overload integrations");
        expect(plans.integrations.integration_count <= kMaxIntegrations,
               "integration cap");
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_sim02_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlfs201") { success = run_qlfs201(); }
    else if (mode == "qlfs202") { success = run_qlfs202(); }
    else if (mode == "qlfs203") { success = run_qlfs203(); }
    else if (mode == "qlfs204") { success = run_qlfs204(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
