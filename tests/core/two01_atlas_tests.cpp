#include "stormline/graphics/canvas2d/atlas_plan.hpp"

#include <cstdio>
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

AtlasDesc valid_atlas() {
    AtlasDesc atlas{};
    atlas.atlas_id = 4;
    atlas.revision = 2;
    atlas.width = 1024;
    atlas.height = 1024;
    atlas.gutter = 2;
    atlas.mip_count = 4;
    atlas.region_count = 2;
    atlas.regions[0] = AtlasRegion{10, 1, 0, 0, 256, 256};
    atlas.regions[1] = AtlasRegion{11, 1, 512, 512, 128, 128};
    return atlas;
}

bool run_atl01() {
    begin();
    AtlasDesc atlas = valid_atlas();
    AtlasPlan plan{};
    CanvasDiagnostic diagnostic{};

    expect(plan_atlas(atlas, plan, diagnostic) == CanvasError::None,
           "valid atlas");
    expect(plan.region_count == 2 && plan.mip_count == 4, "valid plan");

    atlas.atlas_id = 0;
    expect(plan_atlas(atlas, plan, diagnostic) == CanvasError::InvalidArgument,
           "zero atlas");
    expect(plan.region_count == 0, "reset");

    atlas = valid_atlas();
    atlas.width = 0;
    expect(plan_atlas(atlas, plan, diagnostic) == CanvasError::AtlasInvalid,
           "zero width");
    atlas = valid_atlas();
    atlas.mip_count = 0;
    expect(plan_atlas(atlas, plan, diagnostic) == CanvasError::AtlasInvalid,
           "zero mips");
    atlas = valid_atlas();
    atlas.mip_count = 17;
    expect(plan_atlas(atlas, plan, diagnostic) == CanvasError::AtlasInvalid,
           "mip cap");
    atlas = valid_atlas();
    atlas.region_count = kMaxAtlasRegions + 1;
    expect(plan_atlas(atlas, plan, diagnostic) == CanvasError::CapacityFull,
           "region cap");
    atlas = valid_atlas();
    atlas.regions[0].width = 0;
    expect(plan_atlas(atlas, plan, diagnostic) == CanvasError::AtlasInvalid,
           "zero region");
    atlas = valid_atlas();
    atlas.regions[0].x = 1000;
    atlas.regions[0].width = 256;
    expect(plan_atlas(atlas, plan, diagnostic) == CanvasError::AtlasInvalid,
           "region overflow x");
    atlas = valid_atlas();
    atlas.regions[1].y = 1000;
    atlas.regions[1].height = 128;
    expect(plan_atlas(atlas, plan, diagnostic) == CanvasError::AtlasInvalid,
           "region overflow y");
    atlas = valid_atlas();
    atlas.regions[1].region_id = 10;
    expect(plan_atlas(atlas, plan, diagnostic) == CanvasError::DuplicateId,
           "duplicate region");
    atlas = valid_atlas();
    atlas.regions[0].revision = 0;
    expect(plan_atlas(atlas, plan, diagnostic) == CanvasError::InvalidArgument,
           "zero region revision");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_two01_atlas_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "atl01") { success = run_atl01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
