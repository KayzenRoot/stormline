#include "stormline/graphics/canvas2d/sprite_plan.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::canvas2d;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_spr01() {
    begin();
    SpriteDrawDesc sprite{};
    sprite.sprite_id = 7;
    sprite.revision = 2;
    sprite.asset_id = 21;
    sprite.asset_revision = 3;
    sprite.atlas_id = 4;
    sprite.layer_id = 1;
    sprite.region_x = 8;
    sprite.region_y = 16;
    sprite.region_width = 32;
    sprite.region_height = 48;
    sprite.pivot_x = 0.5f;
    sprite.pivot_y = 0.5f;
    sprite.tint_r = 1.0f;
    sprite.tint_g = 0.8f;
    sprite.tint_b = 0.6f;
    sprite.tint_a = 1.0f;
    SpritePlan plan{};
    CanvasDiagnostic diagnostic{};

    expect(plan_sprite(sprite, plan, diagnostic) == CanvasError::None,
           "valid sprite");
    expect(plan.visible && plan.sprite_id == 7 && plan.atlas_id == 4
               && plan.layer_id == 1,
           "valid plan");

    sprite.sprite_id = 0;
    expect(plan_sprite(sprite, plan, diagnostic) == CanvasError::InvalidArgument,
           "zero sprite");
    expect(!plan.visible && plan.sprite_id == 0, "reset");

    sprite.sprite_id = 7;
    sprite.asset_id = 0;
    expect(plan_sprite(sprite, plan, diagnostic) == CanvasError::InvalidArgument,
           "zero asset");
    sprite.asset_id = 21;
    sprite.region_width = 0;
    expect(plan_sprite(sprite, plan, diagnostic) == CanvasError::SpriteInvalid,
           "zero region");
    sprite.region_width = 32;
    sprite.region_height = 0;
    expect(plan_sprite(sprite, plan, diagnostic) == CanvasError::SpriteInvalid,
           "zero region height");
    sprite.region_height = 48;
    sprite.pivot_x = std::numeric_limits<f32>::quiet_NaN();
    expect(plan_sprite(sprite, plan, diagnostic)
               == CanvasError::NonFiniteValue,
           "nonfinite pivot");
    sprite.pivot_x = 0.5f;
    sprite.tint_g = 1.5f;
    expect(plan_sprite(sprite, plan, diagnostic) == CanvasError::OutOfRange,
           "tint range");
    sprite.tint_g = 0.8f;
    sprite.tint_a = -0.1f;
    expect(plan_sprite(sprite, plan, diagnostic) == CanvasError::OutOfRange,
           "alpha range");
    sprite.tint_a = 1.0f;
    sprite.layer_id = 0;
    expect(plan_sprite(sprite, plan, diagnostic) == CanvasError::InvalidArgument,
           "zero layer");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two01_sprite_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "spr01") { success = run_spr01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
