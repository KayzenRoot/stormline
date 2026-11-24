#include "stormline/physics2d/body_plan.hpp"
#include "stormline/physics2d/shape_plan.hpp"
#include "stormline/physics2d/query_plan.hpp"
#include "stormline/physics2d/joint_plan.hpp"
#include "stormline/physics2d/trigger_plan.hpp"
#include "stormline/physics2d/mask_plan.hpp"

#include <cstdio>
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

struct Plans {
    BodyPlan bodies{};
    ShapePlan shapes{};
    QueryPlan queries{};
    JointPlan joints{};
    TriggerPlan triggers{};
    MaskPlan masks{};
    Physics2DDiagnostic diagnostic{};
};

BodySetDesc make_bodies() {
    BodySetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.body_count = 3;
    desc.bodies[0] = BodyDesc{1, 1, BodyKind::Static, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, true, false};
    desc.bodies[1] = BodyDesc{2, 1, BodyKind::Kinematic, 1.0f, 0.0f, 0.0f,
                              1.0f, 0.5f, false, false};
    desc.bodies[2] = BodyDesc{3, 1, BodyKind::Dynamic, 2.0f, 1.0f, 0.25f,
                              1.0f, 0.1f, true, true};
    return desc;
}

ShapeSetDesc make_shapes() {
    ShapeSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.shape_count = 4;
    desc.shapes[0] = ShapeDesc{1, 1, 1, ShapeKind::Circle, 0.0f, 0.0f,
                               1.0f, 1.0f, false};
    desc.shapes[1] = ShapeDesc{2, 1, 1, ShapeKind::Box, 1.0f, 1.0f,
                               0.0f, 1.0f, true};
    desc.shapes[2] = ShapeDesc{3, 2, 1, ShapeKind::Capsule, 0.0f, 0.0f,
                               0.5f, 1.0f, false};
    desc.shapes[3] = ShapeDesc{4, 3, 1, ShapeKind::Polygon, 1.0f, 2.0f,
                               0.0f, 1.0f, false};
    return desc;
}

QuerySetDesc make_queries() {
    QuerySetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.query_count = 3;
    desc.queries[0] = QueryDesc{1, 1, QueryKind::Ray, 0.0f, 0.0f, 1.0f,
                                0.0f, 10.0f, 1, 100};
    desc.queries[1] = QueryDesc{2, 1, QueryKind::Overlap, 1.0f, 1.0f, 0.0f,
                                0.0f, 1.0f, 2, 50};
    desc.queries[2] = QueryDesc{3, 2, QueryKind::ShapeCast, 0.0f, 1.0f, 1.0f,
                                1.0f, 2.0f, 4, 25};
    return desc;
}

JointSetDesc make_joints() {
    JointSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.joint_count = 3;
    desc.joints[0] = JointDesc{1, 1, JointKind::Distance, 1, 2, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 1.0f, false};
    desc.joints[1] = JointDesc{2, 1, JointKind::Revolute, 2, 3, 0.0f, 0.0f,
                               1.0f, 1.0f, -1.0f, 1.0f, false};
    desc.joints[2] = JointDesc{3, 2, JointKind::Prismatic, 1, 3, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 2.0f, true};
    return desc;
}

TriggerSetDesc make_triggers() {
    TriggerSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.trigger_count = 3;
    desc.triggers[0] = TriggerDesc{1, 1, 1, 1, 1, true, false};
    desc.triggers[1] = TriggerDesc{2, 1, 2, 2, 2, false, true};
    desc.triggers[2] = TriggerDesc{3, 2, 3, 3, 4, true, true};
    return desc;
}

MaskSetDesc make_masks() {
    MaskSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.mask_count = 3;
    desc.masks[0] = MaskDesc{1, 1, 0x1, 0x2, 0};
    desc.masks[1] = MaskDesc{2, 1, 0x2, 0x1, 0};
    desc.masks[2] = MaskDesc{3, 1, 0x4, 0x8, 0};
    return desc;
}

bool plan_all(const BodySetDesc& bodies, const ShapeSetDesc& shapes,
              const QuerySetDesc& queries, const JointSetDesc& joints,
              const TriggerSetDesc& triggers, const MaskSetDesc& masks,
              Plans& plans) {
    return plan_bodies(bodies, plans.bodies, plans.diagnostic)
               == Physics2DError::None
           && plan_shapes(shapes, plans.shapes, plans.diagnostic)
               == Physics2DError::None
           && plan_queries(queries, plans.queries, plans.diagnostic)
               == Physics2DError::None
           && plan_joints(joints, plans.joints, plans.diagnostic)
               == Physics2DError::None
           && plan_triggers(triggers, plans.triggers, plans.diagnostic)
               == Physics2DError::None
           && plan_masks(masks, plans.masks, plans.diagnostic)
               == Physics2DError::None;
}

bool plan_default(Plans& plans) {
    return plan_all(make_bodies(), make_shapes(), make_queries(),
                    make_joints(), make_triggers(), make_masks(), plans);
}

bool run_qlfs101() {
    begin();
    Plans plans{};
    expect(plan_default(plans), "integrated plans");
    expect(plans.bodies.body_count == 3 && plans.bodies.static_count == 1
               && plans.bodies.kinematic_count == 1
               && plans.bodies.dynamic_count == 1
               && plans.bodies.enabled_count == 2,
           "body plan");
    expect(plans.shapes.shape_count == 4 && plans.shapes.circle_count == 1
               && plans.shapes.box_count == 1
               && plans.shapes.capsule_count == 1
               && plans.shapes.polygon_count == 1
               && plans.shapes.sensor_count == 1,
           "shape plan");
    expect(plans.queries.query_count == 3 && plans.queries.ray_count == 1
               && plans.queries.overlap_count == 1
               && plans.queries.shape_cast_count == 1
               && plans.queries.total_result_limit == 175,
           "query plan");
    expect(plans.joints.joint_count == 3
               && plans.joints.distance_count == 1
               && plans.joints.revolute_count == 1
               && plans.joints.prismatic_count == 1
               && plans.joints.weld_count == 0
               && plans.joints.collide_count == 1,
           "joint plan");
    expect(plans.triggers.trigger_count == 3
               && plans.triggers.enter_count == 2
               && plans.triggers.exit_count == 2
               && plans.triggers.both_count == 1,
           "trigger plan");
    expect(plans.masks.mask_count == 3 && plans.masks.group_count == 0
               && plans.masks.symmetric_pair_count == 1,
           "mask plan");
    expect(plans.diagnostic.code == Physics2DError::None,
           "integrated diagnostic");
    return finish();
}

bool run_qlfs102() {
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
        expect(repeat.queries.total_result_limit
                   == first.queries.total_result_limit,
               "queries identical");
        expect(repeat.joints.collide_count == first.joints.collide_count,
               "joints identical");
        expect(repeat.triggers.both_count == first.triggers.both_count,
               "triggers identical");
        expect(repeat.masks.symmetric_pair_count
                   == first.masks.symmetric_pair_count,
               "masks identical");
    }
    return finish();
}

bool run_qlfs103() {
    begin();
    Plans plans{};

    BodySetDesc bodies = make_bodies();
    bodies.bodies[2].body_id = 1;
    expect(plan_bodies(bodies, plans.bodies, plans.diagnostic)
               == Physics2DError::DuplicateId,
           "body failure");
    expect(plans.bodies.body_count == 0, "body reset");
    expect(plan_bodies(make_bodies(), plans.bodies, plans.diagnostic)
               == Physics2DError::None,
           "body recovery");

    ShapeSetDesc shapes = make_shapes();
    shapes.shapes[3].shape_id = 1;
    expect(plan_shapes(shapes, plans.shapes, plans.diagnostic)
               == Physics2DError::DuplicateId,
           "shape failure");
    expect(plans.shapes.shape_count == 0, "shape reset");
    expect(plan_shapes(make_shapes(), plans.shapes, plans.diagnostic)
               == Physics2DError::None,
           "shape recovery");

    QuerySetDesc queries = make_queries();
    queries.queries[2].query_id = 1;
    expect(plan_queries(queries, plans.queries, plans.diagnostic)
               == Physics2DError::DuplicateId,
           "query failure");
    expect(plans.queries.query_count == 0, "query reset");
    expect(plan_queries(make_queries(), plans.queries, plans.diagnostic)
               == Physics2DError::None,
           "query recovery");

    JointSetDesc joints = make_joints();
    joints.joints[2].joint_id = 1;
    expect(plan_joints(joints, plans.joints, plans.diagnostic)
               == Physics2DError::DuplicateId,
           "joint failure");
    expect(plans.joints.joint_count == 0, "joint reset");
    expect(plan_joints(make_joints(), plans.joints, plans.diagnostic)
               == Physics2DError::None,
           "joint recovery");

    TriggerSetDesc triggers = make_triggers();
    triggers.triggers[2].trigger_id = 1;
    expect(plan_triggers(triggers, plans.triggers, plans.diagnostic)
               == Physics2DError::DuplicateId,
           "trigger failure");
    expect(plans.triggers.trigger_count == 0, "trigger reset");
    expect(plan_triggers(make_triggers(), plans.triggers, plans.diagnostic)
               == Physics2DError::None,
           "trigger recovery");

    MaskSetDesc masks = make_masks();
    masks.masks[2].mask_id = 1;
    expect(plan_masks(masks, plans.masks, plans.diagnostic)
               == Physics2DError::DuplicateId,
           "mask failure");
    expect(plans.masks.mask_count == 0, "mask reset");
    expect(plan_masks(make_masks(), plans.masks, plans.diagnostic)
               == Physics2DError::None,
           "mask recovery");
    return finish();
}

bool run_qlfs104() {
    begin();
    Plans plans{};
    for (u32 attempt = 0; attempt < 10000; ++attempt) {
        BodySetDesc bodies = make_bodies();
        bodies.body_count = kMaxBodies;
        for (u32 index = 0; index < kMaxBodies; ++index) {
            bodies.bodies[index] =
                BodyDesc{index + 1, 1, static_cast<BodyKind>(index % 3),
                         0.0f, 0.0f, 0.0f, 1.0f, 0.5f, true, false};
        }
        expect(plan_bodies(bodies, plans.bodies, plans.diagnostic)
                   == Physics2DError::None,
               "overload bodies");
        expect(plans.bodies.body_count <= kMaxBodies, "body cap");

        ShapeSetDesc shapes = make_shapes();
        shapes.shape_count = kMaxShapes;
        for (u32 index = 0; index < kMaxShapes; ++index) {
            shapes.shapes[index] =
                ShapeDesc{index + 1, 1, 1, static_cast<ShapeKind>(index % 4),
                          1.0f, 1.0f, 1.0f, 1.0f, index % 2 == 0};
        }
        expect(plan_shapes(shapes, plans.shapes, plans.diagnostic)
                   == Physics2DError::None,
               "overload shapes");
        expect(plans.shapes.shape_count <= kMaxShapes, "shape cap");

        QuerySetDesc queries = make_queries();
        queries.query_count = kMaxQueries;
        for (u32 index = 0; index < kMaxQueries; ++index) {
            queries.queries[index] =
                QueryDesc{index + 1, 1, static_cast<QueryKind>(index % 3),
                          0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1, 256};
        }
        expect(plan_queries(queries, plans.queries, plans.diagnostic)
                   == Physics2DError::None,
               "overload queries");
        expect(plans.queries.query_count <= kMaxQueries, "query cap");
        expect(plans.queries.total_result_limit <= kMaxTotalQueryResults,
               "query total cap");

        JointSetDesc joints = make_joints();
        joints.joint_count = kMaxJoints;
        for (u32 index = 0; index < kMaxJoints; ++index) {
            joints.joints[index] =
                JointDesc{index + 1, 1, static_cast<JointKind>(index % 4),
                          index + 1, index + 2, 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, index % 3 == 0};
        }
        expect(plan_joints(joints, plans.joints, plans.diagnostic)
                   == Physics2DError::None,
               "overload joints");
        expect(plans.joints.joint_count <= kMaxJoints, "joint cap");

        TriggerSetDesc triggers = make_triggers();
        triggers.trigger_count = kMaxTriggers;
        for (u32 index = 0; index < kMaxTriggers; ++index) {
            triggers.triggers[index] =
                TriggerDesc{index + 1, 1, index + 1, index + 1, 1,
                            true, index % 2 == 0};
        }
        expect(plan_triggers(triggers, plans.triggers, plans.diagnostic)
                   == Physics2DError::None,
               "overload triggers");
        expect(plans.triggers.trigger_count <= kMaxTriggers, "trigger cap");

        MaskSetDesc masks = make_masks();
        masks.mask_count = kMaxMasks;
        for (u32 index = 0; index < kMaxMasks; ++index) {
            masks.masks[index] = MaskDesc{index + 1, 1, 0x1, 0x1, 0};
        }
        expect(plan_masks(masks, plans.masks, plans.diagnostic)
                   == Physics2DError::None,
               "overload masks");
        expect(plans.masks.mask_count <= kMaxMasks, "mask cap");
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr,
                     "usage: stormline_sim01_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlfs101") { success = run_qlfs101(); }
    else if (mode == "qlfs102") { success = run_qlfs102(); }
    else if (mode == "qlfs103") { success = run_qlfs103(); }
    else if (mode == "qlfs104") { success = run_qlfs104(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
