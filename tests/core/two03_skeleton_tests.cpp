#include "stormline/animation/skeleton_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::animation;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

BoneDesc bone(u32 id, u32 parent) {
    BoneDesc desc{};
    desc.bone_id = id;
    desc.revision = 1;
    desc.parent_id = parent;
    return desc;
}

bool run_bon01() {
    begin();
    SkeletonDesc skeleton{};
    skeleton.skeleton_id = 9;
    skeleton.revision = 2;
    skeleton.bone_count = 3;
    skeleton.bones[0] = bone(1, 0);
    skeleton.bones[1] = bone(2, 1);
    skeleton.bones[2] = bone(3, 2);
    SkeletonPlan plan{};
    AnimationDiagnostic diagnostic{};

    expect(plan_skeleton(skeleton, plan, diagnostic) == AnimationError::None,
           "valid skeleton");
    expect(plan.bone_count == 3 && plan.max_depth == 3 && plan.root_count == 1,
           "valid plan");
    expect(diagnostic.code == AnimationError::None, "clean diagnostic");

    skeleton.bone_count = 0;
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::SkeletonInvalid,
           "empty skeleton");
    expect(plan.bone_count == 0 && plan.max_depth == 0 && plan.root_count == 0,
           "reset on empty");

    skeleton.bone_count = kMaxBones + 1;
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::SkeletonInvalid,
           "over capacity");

    skeleton.bone_count = 2;
    skeleton.skeleton_id = 0;
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero skeleton");
    skeleton.skeleton_id = 9;
    skeleton.revision = 0;
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::InvalidArgument,
           "zero revision");
    skeleton.revision = 1;

    skeleton.bones[0] = bone(0, 0);
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::SkeletonInvalid,
           "zero bone id");
    expect(diagnostic.index == 0 && diagnostic.source_id == 9,
           "bone diagnostic");
    skeleton.bones[0] = bone(1, 0);
    skeleton.bones[0].revision = 0;
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::SkeletonInvalid,
           "zero bone revision");
    skeleton.bones[0].revision = 1;

    skeleton.bones[0].local_x = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::NonFiniteValue,
           "nan x");
    skeleton.bones[0].local_x = 0.0f;
    skeleton.bones[0].local_y = std::numeric_limits<f32>::infinity();
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::NonFiniteValue,
           "infinite y");
    skeleton.bones[0].local_y = 0.0f;
    skeleton.bones[0].local_rotation
        = -std::numeric_limits<f32>::infinity();
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::NonFiniteValue,
           "infinite rotation");
    skeleton.bones[0].local_rotation = 0.0f;

    skeleton.bones[1] = bone(1, 1);
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::DuplicateId,
           "duplicate bone id");
    expect(diagnostic.index == 1, "duplicate index");
    skeleton.bones[1] = bone(2, 1);

    skeleton.bones[1] = bone(2, 99);
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::SkeletonInvalid,
           "missing parent");
    skeleton.bones[1] = bone(2, 2);
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::SkeletonInvalid,
           "self parent");

    skeleton.bones[0] = bone(1, 2);
    skeleton.bones[1] = bone(2, 1);
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::SkeletonInvalid,
           "two-bone cycle");

    skeleton.bones[0] = bone(1, 0);
    skeleton.bones[1] = bone(2, 0);
    expect(plan_skeleton(skeleton, plan, diagnostic) == AnimationError::None,
           "two roots");
    expect(plan.max_depth == 1 && plan.root_count == 2, "two root plan");

    skeleton.bone_count = 16;
    for (u32 index = 0; index < 16; ++index) {
        skeleton.bones[index] = bone(index + 1, index);
    }
    expect(plan_skeleton(skeleton, plan, diagnostic) == AnimationError::None,
           "depth sixteen");
    expect(plan.max_depth == 16 && plan.root_count == 1, "depth sixteen plan");

    skeleton.bone_count = 17;
    for (u32 index = 0; index < 17; ++index) {
        skeleton.bones[index] = bone(index + 1, index);
    }
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::DepthExceeded,
           "depth seventeen");
    expect(plan.bone_count == 0 && plan.max_depth == 0
               && plan.root_count == 0,
           "reset on depth");

    skeleton.bone_count = kMaxBones;
    for (u32 index = 0; index < kMaxBones; ++index) {
        skeleton.bones[index] = bone(index + 1, 0);
    }
    expect(plan_skeleton(skeleton, plan, diagnostic) == AnimationError::None,
           "capacity roots");
    expect(plan.bone_count == kMaxBones && plan.max_depth == 1
               && plan.root_count == kMaxBones,
           "capacity plan");

    skeleton.bones[0] = bone(1, 0);
    skeleton.bones[1] = bone(2, 3);
    skeleton.bones[2] = bone(3, 2);
    skeleton.bone_count = 3;
    expect(plan_skeleton(skeleton, plan, diagnostic)
               == AnimationError::SkeletonInvalid,
           "late cycle");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two03_skeleton_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "bon01") { success = run_bon01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
