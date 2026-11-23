#include "stormline/graphics/vfx/blend_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::vfx;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_bld01() {
    begin();
    VfxBlendDesc description{};
    description.material_id = 12;
    description.material_revision = 3;
    VfxBlendPlan plan{};
    VfxDiagnostic diagnostic{};

    expect(plan_blend(description, plan, diagnostic) == VfxError::None,
           "opaque");
    expect(plan.blend == BlendMode::Opaque
               && plan.depth == DepthPolicy::TestAndWrite,
           "opaque plan");

    description.material_id = 0;
    expect(plan_blend(description, plan, diagnostic)
               == VfxError::InvalidArgument,
           "zero material");
    expect(plan.blend == BlendMode::Opaque && !plan.needs_sort, "reset");

    description = VfxBlendDesc{12, 3, BlendMode::Mask,
                               DepthPolicy::TestOnly, false, false, false};
    expect(plan_blend(description, plan, diagnostic)
               == VfxError::MaterialMismatch,
           "mask without depth write");
    description = VfxBlendDesc{12, 3, BlendMode::Blend,
                               DepthPolicy::TestAndWrite, false, false, false};
    expect(plan_blend(description, plan, diagnostic)
               == VfxError::MaterialMismatch,
           "blend with depth write");
    description = VfxBlendDesc{12, 3, BlendMode::Blend,
                               DepthPolicy::TestOnly, true, true, true};
    expect(plan_blend(description, plan, diagnostic) == VfxError::None,
           "blend sorted oit");
    expect(plan.needs_sort && plan.oit_approx, "blend sort/oit plan");
    description = VfxBlendDesc{12, 3, BlendMode::Additive,
                               DepthPolicy::TestOnly, false, true, false};
    expect(plan_blend(description, plan, diagnostic)
               == VfxError::MaterialMismatch,
           "additive sort");
    description = VfxBlendDesc{12, 3, BlendMode::Additive,
                               DepthPolicy::TestOnly, false, false, true};
    expect(plan_blend(description, plan, diagnostic) == VfxError::Unsupported,
           "additive oit");
    description = VfxBlendDesc{12, 3, BlendMode::Opaque,
                               DepthPolicy::TestAndWrite, true, false, false};
    expect(plan_blend(description, plan, diagnostic)
               == VfxError::MaterialMismatch,
           "opaque premultiplied");
    description = VfxBlendDesc{12, 3, BlendMode::Additive,
                               DepthPolicy::Disabled, false, false, false};
    expect(plan_blend(description, plan, diagnostic) == VfxError::None,
           "additive");
    description.blend = static_cast<BlendMode>(200);
    expect(plan_blend(description, plan, diagnostic)
               == VfxError::InvalidArgument,
           "invalid blend");
    description.blend = BlendMode::Blend;
    description.depth = static_cast<DepthPolicy>(200);
    expect(plan_blend(description, plan, diagnostic)
               == VfxError::InvalidArgument,
           "invalid depth");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx08_blend_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "bld01") { success = run_bld01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
