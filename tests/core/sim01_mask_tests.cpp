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

MaskDesc mask(u32 id, u32 category, u32 collision, u32 group = 0) {
    MaskDesc desc{};
    desc.mask_id = id;
    desc.revision = 1;
    desc.category_bits = category;
    desc.collision_bits = collision;
    desc.group_index = group;
    return desc;
}

MaskSetDesc mask_set() {
    MaskSetDesc desc{};
    desc.world_id = 10;
    desc.revision = 2;
    desc.mask_count = 3;
    desc.masks[0] = mask(1, 0x1, 0x2);
    desc.masks[1] = mask(2, 0x2, 0x1);
    desc.masks[2] = mask(3, 0x4, 0x8);
    return desc;
}

bool run_msk01() {
    begin();
    MaskSetDesc masks = mask_set();
    MaskPlan plan{};
    Physics2DDiagnostic diagnostic{};
    expect(plan_masks(masks, plan, diagnostic) == Physics2DError::None,
           "valid masks");
    expect(plan.mask_count == 3 && plan.group_count == 0
               && plan.symmetric_pair_count == 1,
           "valid plan");
    expect(diagnostic.code == Physics2DError::None, "success diagnostic");
    expect(masks_compatible(masks.masks[0], masks.masks[1]), "bits match");
    expect(!masks_compatible(masks.masks[0], masks.masks[2]), "bits differ");

    MaskDesc group_a = mask(4, 0x1, 0x1, 7);
    MaskDesc group_b = mask(5, 0x2, 0x2, 7);
    MaskDesc group_c = mask(6, 0x1, 0x1, 8);
    expect(masks_compatible(group_a, group_b), "same group overrides bits");
    expect(!masks_compatible(group_a, group_c), "different group blocks");
    expect(!masks_compatible(group_a, masks.masks[0]), "group vs no group");
    expect(masks_compatible(group_a, group_b) == masks_compatible(group_b, group_a),
           "compatibility symmetric");

    MaskPlan repeat{};
    expect(plan_masks(masks, repeat, diagnostic) == Physics2DError::None,
           "repeat masks");
    expect(repeat.symmetric_pair_count == plan.symmetric_pair_count,
           "deterministic plan");

    masks.world_id = 0;
    expect(plan_masks(masks, plan, diagnostic)
               == Physics2DError::InvalidArgument,
           "zero world");
    expect(plan.mask_count == 0 && plan.symmetric_pair_count == 0,
           "reset on zero world");
    masks = mask_set();
    masks.revision = 0;
    expect(plan_masks(masks, plan, diagnostic)
               == Physics2DError::InvalidArgument,
           "zero revision");
    masks = mask_set();
    masks.mask_count = kMaxMasks + 1;
    expect(plan_masks(masks, plan, diagnostic)
               == Physics2DError::CapacityFull,
           "mask overflow");

    masks = mask_set();
    masks.masks[1].mask_id = 0;
    expect(plan_masks(masks, plan, diagnostic)
               == Physics2DError::MaskInvalid,
           "zero mask id");
    expect(diagnostic.index == 1, "zero mask diagnostic");
    masks = mask_set();
    masks.masks[1].revision = 0;
    expect(plan_masks(masks, plan, diagnostic)
               == Physics2DError::MaskInvalid,
           "zero mask revision");
    masks = mask_set();
    masks.masks[1].category_bits = 0;
    expect(plan_masks(masks, plan, diagnostic)
               == Physics2DError::MaskInvalid,
           "zero category");
    masks = mask_set();
    masks.masks[1].collision_bits = 0;
    expect(plan_masks(masks, plan, diagnostic)
               == Physics2DError::MaskInvalid,
           "zero collision bits");
    masks = mask_set();
    masks.masks[2].mask_id = 1;
    expect(plan_masks(masks, plan, diagnostic)
               == Physics2DError::DuplicateId,
           "duplicate mask");
    expect(diagnostic.index == 2, "duplicate mask diagnostic");

    masks = mask_set();
    masks.mask_count = kMaxMasks;
    for (u32 index = 0; index < kMaxMasks; ++index) {
        masks.masks[index] =
            mask(index + 1, 0x1, 0x1, index < 16 ? 1u : 0u);
    }
    expect(plan_masks(masks, plan, diagnostic) == Physics2DError::None,
           "capacity masks");
    expect(plan.mask_count == kMaxMasks && plan.group_count == 1
               && plan.symmetric_pair_count == 240,
           "capacity plan");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_sim01_mask_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "msk01") { success = run_msk01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
