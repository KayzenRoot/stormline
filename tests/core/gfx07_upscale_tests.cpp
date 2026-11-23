#include "stormline/graphics/post/upscale_plan.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::post;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_ups01() {
    begin();
    UpscaleRequest request{1920, 1080, 1920, 1080,
                           ReconstructionStrategy::Native};
    UpscalePlan plan{};
    PostDiagnostic diagnostic{};

    expect(plan_upscale(request, plan, diagnostic) == PostError::None,
           "native");
    expect(!plan.reconstructed && plan.scale_numerator == 1
               && plan.scale_denominator == 1,
           "native plan");

    request.strategy = ReconstructionStrategy::Spatial;
    request.output_width = 2560;
    request.output_height = 1440;
    expect(plan_upscale(request, plan, diagnostic) == PostError::None,
           "spatial");
    expect(plan.reconstructed && plan.scale_numerator == 3
               && plan.scale_denominator == 4,
           "3/4 reduced fraction");
    expect(diagnostic.code == PostError::None, "success diagnostic");

    request.render_width = 1920;
    request.render_height = 1080;
    request.output_width = 3840;
    request.output_height = 2160;
    expect(plan_upscale(request, plan, diagnostic) == PostError::None,
           "double");
    expect(plan.scale_numerator == 1 && plan.scale_denominator == 2,
           "1/2 reduced fraction");

    request.render_width = 1000;
    request.render_height = 500;
    request.output_width = 1500;
    request.output_height = 750;
    expect(plan_upscale(request, plan, diagnostic) == PostError::None,
           "fraction");
    expect(plan.scale_numerator == 2 && plan.scale_denominator == 3,
           "2/3 reduced fraction");

    request.render_width = 1920;
    request.output_width = 1920;
    request.render_height = 1080;
    request.output_height = 2160;
    expect(plan_upscale(request, plan, diagnostic) == PostError::None,
           "height-only mismatch");
    expect(plan.reconstructed && plan.scale_numerator == 1
               && plan.scale_denominator == 1,
           "height-only plan");

    request = UpscaleRequest{1920, 1080, 3840, 2160,
                             ReconstructionStrategy::Taa};
    expect(plan_upscale(request, plan, diagnostic) == PostError::None,
           "taa metadata");
    expect(plan.reconstructed, "taa reconstructed");
    request.strategy = ReconstructionStrategy::VendorUpscale;
    expect(plan_upscale(request, plan, diagnostic) == PostError::None,
           "vendor metadata");

    request.strategy = ReconstructionStrategy::Native;
    expect(plan_upscale(request, plan, diagnostic) == PostError::Unsupported,
           "native mismatch");
    expect(plan.scale_numerator == 1 && plan.scale_denominator == 1
               && !plan.reconstructed,
           "native mismatch reset");

    request.strategy = ReconstructionStrategy::Spatial;
    request.render_width = 0;
    expect(plan_upscale(request, plan, diagnostic) == PostError::InvalidArgument,
           "zero render width");
    request.render_width = 1920;
    request.render_height = 0;
    expect(plan_upscale(request, plan, diagnostic) == PostError::InvalidArgument,
           "zero render height");
    request.render_height = 1080;
    request.output_width = 0;
    expect(plan_upscale(request, plan, diagnostic) == PostError::InvalidArgument,
           "zero output width");
    request.output_width = 3840;
    request.output_height = 0;
    expect(plan_upscale(request, plan, diagnostic) == PostError::InvalidArgument,
           "zero output height");

    request.output_height = 2160;
    request.output_width = 1280;
    request.output_height = 720;
    expect(plan_upscale(request, plan, diagnostic) == PostError::OutOfRange,
           "output smaller than render");
    expect(plan.scale_numerator == 1 && plan.scale_denominator == 1
               && !plan.reconstructed,
           "range reset");

    request.output_width = 3840;
    request.output_height = 2160;
    request.strategy = static_cast<ReconstructionStrategy>(200);
    expect(plan_upscale(request, plan, diagnostic) == PostError::InvalidArgument,
           "invalid strategy");
    expect(diagnostic.code == PostError::InvalidArgument, "invalid diagnostic");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx07_upscale_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "ups01") { success = run_ups01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
