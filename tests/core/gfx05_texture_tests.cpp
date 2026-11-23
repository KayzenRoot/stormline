#include "stormline/graphics/material/virtual_texture.hpp"

#include <cstdio>
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

[[nodiscard]] TextureDesc base_texture(u32 id = 1) {
    TextureDesc texture{};
    texture.id = id;
    texture.width = 256;
    texture.height = 256;
    texture.levels = 9;
    texture.format = TextureFormat::Rgba8Srgb;
    texture.color_space = ColorSpace::Srgb;
    texture.usage = TextureUsage::BaseColor;
    return texture;
}

[[nodiscard]] TextureDesc linear_texture(u32 id = 2) {
    TextureDesc texture{};
    texture.id = id;
    texture.width = 256;
    texture.height = 256;
    texture.levels = 9;
    texture.format = TextureFormat::Rgba8Unorm;
    texture.color_space = ColorSpace::Linear;
    texture.usage = TextureUsage::Normal;
    return texture;
}

bool run_vtx01() {
    begin();
    TextureSet set{};
    MaterialDiagnostic diagnostic{};

    expect(add_texture(set, base_texture()) == MaterialError::None, "add");
    expect(set.count == 1, "count");
    expect(validate_textures(set, diagnostic) == MaterialError::None, "valid");
    expect(add_texture(set, base_texture()) == MaterialError::DuplicateId,
           "duplicate");
    expect(set.count == 1, "duplicate atomic");
    expect(add_texture(set, base_texture(0)) == MaterialError::InvalidArgument,
           "zero id");

    TextureDesc invalid = base_texture(10);
    invalid.width = 0;
    expect(add_texture(set, invalid) == MaterialError::InvalidArgument,
           "width zero");
    invalid = base_texture(10);
    invalid.height = 16385;
    expect(add_texture(set, invalid) == MaterialError::InvalidArgument,
           "height range");
    invalid = base_texture(10);
    invalid.levels = 8;
    expect(add_texture(set, invalid) == MaterialError::InvalidArgument,
           "levels mismatch");
    invalid = base_texture(10);
    invalid.levels = 0;
    expect(add_texture(set, invalid) == MaterialError::InvalidArgument,
           "levels zero");
    invalid = base_texture(10);
    invalid.format = static_cast<TextureFormat>(200);
    expect(add_texture(set, invalid) == MaterialError::InvalidArgument,
           "format enum");
    invalid = base_texture(10);
    invalid.usage = static_cast<TextureUsage>(200);
    expect(add_texture(set, invalid) == MaterialError::InvalidArgument,
           "usage enum");
    invalid = base_texture(10);
    invalid.color_space = static_cast<ColorSpace>(200);
    expect(add_texture(set, invalid) == MaterialError::InvalidArgument,
           "space enum");

    invalid = base_texture(11);
    invalid.color_space = ColorSpace::Linear;
    expect(add_texture(set, invalid) == MaterialError::InvalidArgument,
           "base color srgb");
    invalid = linear_texture(11);
    invalid.color_space = ColorSpace::Srgb;
    expect(add_texture(set, invalid) == MaterialError::InvalidArgument,
           "normal linear");
    invalid = linear_texture(11);
    invalid.usage = TextureUsage::Occlusion;
    invalid.color_space = ColorSpace::Srgb;
    expect(add_texture(set, invalid) == MaterialError::InvalidArgument,
           "occlusion linear");
    invalid = linear_texture(11);
    invalid.usage = TextureUsage::Height;
    invalid.color_space = ColorSpace::Srgb;
    expect(add_texture(set, invalid) == MaterialError::InvalidArgument,
           "height linear");
    invalid = base_texture(11);
    invalid.format = TextureFormat::Depth32Float;
    expect(add_texture(set, invalid) == MaterialError::InvalidArgument,
           "depth base color");

    TextureDesc emissive = base_texture(12);
    emissive.usage = TextureUsage::Emissive;
    expect(add_texture(set, emissive) == MaterialError::None, "emissive srgb");
    emissive = base_texture(13);
    emissive.usage = TextureUsage::Emissive;
    emissive.format = TextureFormat::Rgba16Float;
    emissive.color_space = ColorSpace::Linear;
    expect(add_texture(set, emissive) == MaterialError::None, "emissive linear");
    TextureDesc depth = linear_texture(14);
    depth.usage = TextureUsage::Height;
    depth.format = TextureFormat::Depth32Float;
    expect(add_texture(set, depth) == MaterialError::None, "depth height");

    TextureDesc wide = base_texture(15);
    wide.width = 16384;
    wide.height = 16384;
    wide.levels = 12;
    expect(add_texture(set, wide) == MaterialError::None, "capped levels");

    TextureDesc single = base_texture(16);
    single.width = 1;
    single.height = 1;
    single.levels = 1;
    expect(add_texture(set, single) == MaterialError::None, "single level");

    while (set.count < kMaxTextures) {
        expect(add_texture(set, linear_texture(100 + set.count))
                   == MaterialError::None,
               "fill");
    }
    expect(add_texture(set, linear_texture(999)) == MaterialError::CapacityFull,
           "capacity");
    expect(set.count == kMaxTextures, "capacity count");

    TextureSet duplicate_set{};
    duplicate_set.count = 2;
    duplicate_set.textures[0] = base_texture(1);
    duplicate_set.textures[1] = base_texture(1);
    expect(validate_textures(duplicate_set, diagnostic)
               == MaterialError::DuplicateId,
           "manual duplicate");
    expect(diagnostic.texture_id == 1 && diagnostic.index == 1,
           "duplicate position");

    TextureSet overflow{};
    overflow.count = kMaxTextures + 1;
    expect(validate_textures(overflow, diagnostic)
               == MaterialError::InvalidArgument,
           "overflow");

    TextureSet invalid_manual{};
    invalid_manual.count = 1;
    invalid_manual.textures[0] = base_texture(20);
    invalid_manual.textures[0].levels = 2;
    expect(validate_textures(invalid_manual, diagnostic)
               == MaterialError::InvalidArgument,
           "manual levels");
    expect(diagnostic.texture_id == 20 && diagnostic.index == 0,
           "levels position");

    VirtualTexture vt{};
    vt.texture_id = 1;
    vt.page_size = 4096;
    vt.page_count = 8;

    RequestedPages requested{};
    requested.count = 4;
    requested.page_ids[0] = 1;
    requested.page_ids[1] = 2;
    requested.page_ids[2] = 3;
    requested.page_ids[3] = 5;
    ResidentPages resident{};
    resident.count = 2;
    resident.page_ids[0] = 2;
    resident.page_ids[1] = 5;

    PagePlan plan{};
    expect(plan_pages(vt, requested, resident, 2, plan, diagnostic)
               == MaterialError::None,
           "pages");
    expect(plan.count == 2 && plan.page_ids[0] == 1 && plan.page_ids[1] == 3,
           "page order");
    expect(plan.pages_bytes == 8192 && !plan.truncated, "page bytes");

    expect(plan_pages(vt, requested, resident, 1, plan, diagnostic)
               == MaterialError::None,
           "budget pages");
    expect(plan.count == 1 && plan.page_ids[0] == 1 && plan.truncated,
           "budget truncation");

    expect(plan_pages(vt, requested, resident, 0, plan, diagnostic)
               == MaterialError::None,
           "zero budget");
    expect(plan.count == 0 && plan.pages_bytes == 0 && plan.truncated,
           "zero budget truncation");

    resident.count = 4;
    resident.page_ids[0] = 1;
    resident.page_ids[1] = 2;
    resident.page_ids[2] = 3;
    resident.page_ids[3] = 5;
    expect(plan_pages(vt, requested, resident, 8, plan, diagnostic)
               == MaterialError::None,
           "resident all");
    expect(plan.count == 0 && !plan.truncated, "resident empty");

    RequestedPages duplicate_request = requested;
    duplicate_request.count = 2;
    duplicate_request.page_ids[0] = 1;
    duplicate_request.page_ids[1] = 1;
    expect(plan_pages(vt, duplicate_request, ResidentPages{}, 2, plan,
                      diagnostic) == MaterialError::InvalidArgument,
           "request duplicate");

    RequestedPages out_of_range = requested;
    out_of_range.count = 2;
    out_of_range.page_ids[0] = 1;
    out_of_range.page_ids[1] = 9;
    expect(plan_pages(vt, out_of_range, ResidentPages{}, 2, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "request range");
    out_of_range.page_ids[1] = 0;
    expect(plan_pages(vt, out_of_range, ResidentPages{}, 2, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "request zero");

    ResidentPages duplicate_resident{};
    duplicate_resident.count = 2;
    duplicate_resident.page_ids[0] = 3;
    duplicate_resident.page_ids[1] = 3;
    expect(plan_pages(vt, requested, duplicate_resident, 2, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "resident duplicate");

    RequestedPages too_many{};
    too_many.count = kMaxPages + 1;
    expect(plan_pages(vt, too_many, ResidentPages{}, 2, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "request capacity");
    ResidentPages too_many_resident{};
    too_many_resident.count = kMaxPages + 1;
    expect(plan_pages(vt, requested, too_many_resident, 2, plan, diagnostic)
               == MaterialError::InvalidArgument,
           "resident capacity");

    VirtualTexture invalid_vt{};
    expect(plan_pages(invalid_vt, RequestedPages{}, ResidentPages{}, 0, plan,
                      diagnostic) == MaterialError::InvalidArgument,
           "empty vt");
    invalid_vt.texture_id = 1;
    invalid_vt.page_count = 8;
    expect(plan_pages(invalid_vt, RequestedPages{}, ResidentPages{}, 0, plan,
                      diagnostic) == MaterialError::InvalidArgument,
           "zero page size");
    invalid_vt.page_size = 4096;
    invalid_vt.page_count = 0;
    expect(plan_pages(invalid_vt, RequestedPages{}, ResidentPages{}, 0, plan,
                      diagnostic) == MaterialError::InvalidArgument,
           "zero page count");
    invalid_vt.page_count = 0xFFFFFFFFu;
    invalid_vt.page_size = 2;
    expect(plan_pages(invalid_vt, RequestedPages{}, ResidentPages{}, 0, plan,
                      diagnostic) == MaterialError::InvalidArgument,
           "page bytes overflow");
    expect(diagnostic.texture_id == 1, "page diagnostic");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx05_texture_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "vtx01") { success = run_vtx01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
