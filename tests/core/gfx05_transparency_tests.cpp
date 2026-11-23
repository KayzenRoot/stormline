#include "stormline/graphics/material/transparency.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::material;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] TransparentItem item(u32 id, f32 depth) {
    TransparentItem value{};
    value.id = id;
    value.depth = depth;
    value.alpha = AlphaMode::Blend;
    value.blend = BlendMode::AlphaBlend;
    value.depth_write = false;
    return value;
}

bool run_trn01() {
    begin();
    TransparencyPlan plan{};
    MaterialDiagnostic diagnostic{};

    expect(plan_transparency(TransparentSet{}, 1, plan, diagnostic)
               == MaterialError::None,
           "empty");
    expect(plan.count == 0 && plan.overdraw_count == 0, "empty counts");

    TransparentSet set{};
    set.count = 3;
    set.items[0] = item(1, 5.0f);
    set.items[1] = item(2, 10.0f);
    set.items[2] = item(3, 10.0f);
    expect(plan_transparency(set, 3, plan, diagnostic) == MaterialError::None,
           "plan");
    expect(plan.count == 3 && plan.overdraw_count == 2, "plan counts");
    expect(plan.item_ids[0] == 2 && plan.item_ids[1] == 3
               && plan.item_ids[2] == 1,
           "back to front");

    expect(plan_transparency(set, 2, plan, diagnostic)
               == MaterialError::TransparencyBudgetExceeded,
           "budget");
    expect(plan.count == 0 && plan.overdraw_count == 0, "budget reset");
    expect(plan_transparency(set, 0, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "zero budget");
    expect(plan_transparency(set, kMaxTransparentItems + 1, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "budget capacity");

    set.items[1] = item(1, 10.0f);
    expect(plan_transparency(set, 3, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "duplicate");
    set.items[1] = item(2, 10.0f);
    set.items[1].id = 0;
    expect(plan_transparency(set, 3, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "zero id");
    set.items[1] = item(2, std::numeric_limits<f32>::quiet_NaN());
    expect(plan_transparency(set, 3, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "depth nan");
    set.items[1] = item(2, std::numeric_limits<f32>::infinity());
    expect(plan_transparency(set, 3, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "depth inf");
    set.items[1] = item(2, 10.0f);
    set.items[1].alpha = AlphaMode::Opaque;
    expect(plan_transparency(set, 3, plan, diagnostic)
               == MaterialError::InvalidAlphaMode,
           "opaque");
    set.items[1].alpha = AlphaMode::Mask;
    expect(plan_transparency(set, 3, plan, diagnostic)
               == MaterialError::InvalidAlphaMode,
           "mask");
    set.items[1].alpha = static_cast<AlphaMode>(200);
    expect(plan_transparency(set, 3, plan, diagnostic)
               == MaterialError::InvalidAlphaMode,
           "alpha enum");
    set.items[1] = item(2, 10.0f);
    set.items[1].depth_write = true;
    expect(plan_transparency(set, 3, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "depth write");
    set.items[1] = item(2, 10.0f);
    set.items[1].blend = BlendMode::Opaque;
    expect(plan_transparency(set, 3, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "blend opaque");
    set.items[1] = item(2, 10.0f);
    set.items[1].blend = static_cast<BlendMode>(200);
    expect(plan_transparency(set, 3, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "blend enum");
    set.items[1] = item(2, 10.0f);
    set.items[1].alpha = AlphaMode::Transmission;
    set.items[1].blend = BlendMode::Premultiplied;
    expect(plan_transparency(set, 3, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "transmission premultiplied");

    set.items[1] = item(2, 10.0f);
    set.items[1].alpha = AlphaMode::Transmission;
    set.items[1].blend = BlendMode::AlphaBlend;
    expect(plan_transparency(set, 3, plan, diagnostic) == MaterialError::None,
           "transmission");
    set.items[1] = item(2, 10.0f);
    set.items[1].blend = BlendMode::Premultiplied;
    expect(plan_transparency(set, 3, plan, diagnostic) == MaterialError::None,
           "premultiplied");

    set.count = kMaxTransparentItems + 1;
    expect(plan_transparency(set, kMaxTransparentItems, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "set capacity");

    set.count = kMaxTransparentItems;
    for (u32 index = 0; index < set.count; ++index) {
        set.items[index] = item(index + 1, static_cast<f32>(index));
    }
    expect(plan_transparency(set, kMaxTransparentItems, plan, diagnostic)
               == MaterialError::None,
           "max valid");
    expect(plan.count == kMaxTransparentItems
               && plan.overdraw_count == kMaxTransparentItems - 1,
           "max counts");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx05_transparency_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "trn01") { success = run_trn01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
