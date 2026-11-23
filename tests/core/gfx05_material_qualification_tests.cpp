#include "stormline/graphics/material/decal.hpp"
#include "stormline/graphics/material/pbr_material.hpp"
#include "stormline/graphics/material/texture_mip.hpp"
#include "stormline/graphics/material/texture_sampler.hpp"
#include "stormline/graphics/material/transparency.hpp"
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

struct PipelineResult {
    u32 material_count{0};
    u32 texture_count{0};
    u32 color_mips{0};
    u32 color_last_bytes{0};
    u32 normal_mips{0};
    u32 normal_last_bytes{0};
    u32 page_count{0};
    u32 page_first{0};
    u32 page_second{0};
    u32 page_bytes{0};
    bool page_truncated{false};
    u32 decal_count{0};
    u32 decal_first{0};
    u32 decal_second{0};
    u32 decal_third{0};
    u32 transparent_count{0};
    u32 transparent_first{0};
    u32 transparent_second{0};
    u32 transparent_third{0};
    u32 overdraw{0};
    MaterialError last_error{MaterialError::None};
};

[[nodiscard]] MaterialDesc material(u32 id) {
    MaterialDesc value{};
    value.id = id;
    value.revision = 1;
    value.parameters.metallic = 0.25f;
    value.parameters.roughness = 0.5f;
    return value;
}

[[nodiscard]] TextureDesc color_texture() {
    TextureDesc value{};
    value.id = 1;
    value.width = 256;
    value.height = 256;
    value.levels = 9;
    value.format = TextureFormat::Rgba8Srgb;
    value.color_space = ColorSpace::Srgb;
    value.usage = TextureUsage::BaseColor;
    return value;
}

[[nodiscard]] TextureDesc normal_texture() {
    TextureDesc value{};
    value.id = 2;
    value.width = 8;
    value.height = 4;
    value.levels = 4;
    value.format = TextureFormat::Rgba16Float;
    value.color_space = ColorSpace::Linear;
    value.usage = TextureUsage::Normal;
    return value;
}

[[nodiscard]] TransparentItem transparent(u32 id, f32 depth) {
    TransparentItem value{};
    value.id = id;
    value.depth = depth;
    value.alpha = AlphaMode::Blend;
    value.blend = BlendMode::AlphaBlend;
    value.depth_write = false;
    return value;
}

[[nodiscard]] PipelineResult run_pipeline() {
    PipelineResult result{};

    MaterialSet materials{};
    result.last_error = add_material(materials, material(1));
    if (result.last_error != MaterialError::None) {
        return result;
    }
    result.last_error = add_material(materials, material(2));
    result.material_count = materials.count;

    TextureSet textures{};
    result.last_error = add_texture(textures, color_texture());
    if (result.last_error != MaterialError::None) {
        return result;
    }
    result.last_error = add_texture(textures, normal_texture());
    result.texture_count = textures.count;

    MipChain color_chain{};
    MaterialDiagnostic diagnostic{};
    result.last_error = build_mip_chain(color_texture(), color_chain, diagnostic);
    if (result.last_error != MaterialError::None) {
        return result;
    }
    result.color_mips = color_chain.count;
    result.color_last_bytes = color_chain.levels[color_chain.count - 1].bytes;

    MipChain normal_chain{};
    result.last_error = build_mip_chain(normal_texture(), normal_chain, diagnostic);
    if (result.last_error != MaterialError::None) {
        return result;
    }
    result.normal_mips = normal_chain.count;
    result.normal_last_bytes = normal_chain.levels[normal_chain.count - 1].bytes;

    SamplerProfile sampler{};
    result.last_error = validate_sampler(sampler, diagnostic);
    if (result.last_error != MaterialError::None) {
        return result;
    }

    VirtualTexture virtual_texture{1, 4096, 8};
    RequestedPages requested{};
    requested.count = 4;
    requested.page_ids[0] = 1;
    requested.page_ids[1] = 2;
    requested.page_ids[2] = 3;
    requested.page_ids[3] = 4;
    ResidentPages resident{};
    resident.count = 1;
    resident.page_ids[0] = 2;

    PagePlan pages{};
    result.last_error = plan_pages(
        virtual_texture, requested, resident, 2, pages, diagnostic);
    if (result.last_error != MaterialError::None) {
        return result;
    }
    result.page_count = pages.count;
    result.page_first = pages.page_ids[0];
    result.page_second = pages.page_ids[1];
    result.page_bytes = pages.pages_bytes;
    result.page_truncated = pages.truncated;

    DecalSet decals{};
    decals.count = 3;
    decals.decals[0] = DecalDesc{20, 2, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, false};
    decals.decals[1] = DecalDesc{10, 1, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, false};
    decals.decals[2] = DecalDesc{30, 2, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, false};
    DecalPlan decal_plan{};
    result.last_error = plan_decals(decals, decal_plan, diagnostic);
    if (result.last_error != MaterialError::None) {
        return result;
    }
    result.decal_count = decal_plan.count;
    result.decal_first = decal_plan.decal_ids[0];
    result.decal_second = decal_plan.decal_ids[1];
    result.decal_third = decal_plan.decal_ids[2];

    TransparentSet items{};
    items.count = 3;
    items.items[0] = transparent(1, 5.0f);
    items.items[1] = transparent(2, 10.0f);
    items.items[2] = transparent(3, 10.0f);
    TransparencyPlan transparent_plan{};
    result.last_error = plan_transparency(
        items, 3, transparent_plan, diagnostic);
    if (result.last_error != MaterialError::None) {
        return result;
    }
    result.transparent_count = transparent_plan.count;
    result.transparent_first = transparent_plan.item_ids[0];
    result.transparent_second = transparent_plan.item_ids[1];
    result.transparent_third = transparent_plan.item_ids[2];
    result.overdraw = transparent_plan.overdraw_count;
    return result;
}

bool same_result(const PipelineResult& left, const PipelineResult& right) {
    return left.material_count == right.material_count
        && left.texture_count == right.texture_count
        && left.color_mips == right.color_mips
        && left.color_last_bytes == right.color_last_bytes
        && left.normal_mips == right.normal_mips
        && left.normal_last_bytes == right.normal_last_bytes
        && left.page_count == right.page_count
        && left.page_first == right.page_first
        && left.page_second == right.page_second
        && left.page_bytes == right.page_bytes
        && left.page_truncated == right.page_truncated
        && left.decal_count == right.decal_count
        && left.decal_first == right.decal_first
        && left.decal_second == right.decal_second
        && left.decal_third == right.decal_third
        && left.transparent_count == right.transparent_count
        && left.transparent_first == right.transparent_first
        && left.transparent_second == right.transparent_second
        && left.transparent_third == right.transparent_third
        && left.overdraw == right.overdraw
        && left.last_error == right.last_error;
}

bool run_qlf01() {
    begin();
    const PipelineResult result = run_pipeline();
    expect(result.last_error == MaterialError::None, "pipeline");
    expect(result.material_count == 2 && result.texture_count == 2, "counts");
    expect(result.color_mips == 9 && result.color_last_bytes == 4, "color mips");
    expect(result.normal_mips == 4 && result.normal_last_bytes == 8,
           "normal mips");
    expect(result.page_count == 2 && result.page_first == 1
               && result.page_second == 3 && result.page_bytes == 8192
               && result.page_truncated,
           "page plan");
    expect(result.decal_count == 3 && result.decal_first == 10
               && result.decal_second == 20 && result.decal_third == 30,
           "decal plan");
    expect(result.transparent_count == 3 && result.transparent_first == 2
               && result.transparent_second == 3
               && result.transparent_third == 1 && result.overdraw == 2,
           "transparency plan");
    return finish();
}

bool run_qlf02() {
    begin();
    const PipelineResult first = run_pipeline();
    const PipelineResult second = run_pipeline();
    expect(first.last_error == MaterialError::None, "first");
    expect(second.last_error == MaterialError::None, "second");
    expect(same_result(first, second), "deterministic repeat");
    return finish();
}

bool run_qlf03() {
    begin();
    MaterialDiagnostic diagnostic{};
    MaterialSet materials{};
    expect(add_material(materials, material(1)) == MaterialError::None,
           "valid material");
    expect(add_material(materials, material(1)) == MaterialError::DuplicateId,
           "duplicate material");
    expect(add_material(materials, material(3)) == MaterialError::None,
           "recover material");

    TextureSet textures{};
    expect(add_texture(textures, color_texture()) == MaterialError::None,
           "valid texture");
    TextureDesc invalid_texture = color_texture();
    invalid_texture.id = 2;
    invalid_texture.levels = 2;
    expect(add_texture(textures, invalid_texture) == MaterialError::InvalidArgument,
           "invalid texture");
    expect(add_texture(textures, normal_texture()) == MaterialError::None,
           "recover texture");

    VirtualTexture virtual_texture{1, 4096, 8};
    RequestedPages duplicate{};
    duplicate.count = 2;
    duplicate.page_ids[0] = 1;
    duplicate.page_ids[1] = 1;
    PagePlan pages{};
    expect(plan_pages(virtual_texture, duplicate, ResidentPages{}, 2, pages,
                      diagnostic) == MaterialError::InvalidArgument,
           "invalid pages");
    RequestedPages valid{};
    valid.count = 1;
    valid.page_ids[0] = 1;
    expect(plan_pages(virtual_texture, valid, ResidentPages{}, 2, pages,
                      diagnostic) == MaterialError::None,
           "recover pages");

    TextureDesc invalid_mip = color_texture();
    invalid_mip.levels = 0;
    MipChain chain{};
    expect(build_mip_chain(invalid_mip, chain, diagnostic)
               == MaterialError::InvalidMipChain,
           "invalid mip");
    expect(build_mip_chain(color_texture(), chain, diagnostic)
               == MaterialError::None,
           "recover mip");

    SamplerProfile invalid_sampler{};
    invalid_sampler.max_anisotropy = 3;
    expect(validate_sampler(invalid_sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "invalid sampler");
    expect(validate_sampler(SamplerProfile{}, diagnostic)
               == MaterialError::None,
           "recover sampler");

    DecalSet decals{};
    decals.count = 2;
    decals.decals[0] = DecalDesc{1, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, false};
    decals.decals[1] = DecalDesc{1, 0, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, false};
    DecalPlan decal_plan{};
    expect(plan_decals(decals, decal_plan, diagnostic)
               == MaterialError::DecalConflict,
           "invalid decal");
    decals.decals[1].id = 2;
    expect(plan_decals(decals, decal_plan, diagnostic) == MaterialError::None,
           "recover decal");

    TransparentSet items{};
    items.count = 3;
    items.items[0] = transparent(1, 1.0f);
    items.items[1] = transparent(2, 2.0f);
    items.items[2] = transparent(3, 3.0f);
    TransparencyPlan transparent_plan{};
    expect(plan_transparency(items, 2, transparent_plan, diagnostic)
               == MaterialError::TransparencyBudgetExceeded,
           "invalid transparency");
    expect(plan_transparency(items, 3, transparent_plan, diagnostic)
               == MaterialError::None,
           "recover transparency");
    return finish();
}

bool run_qlf04() {
    begin();
    bool bounded = true;
    for (u32 iteration = 0; iteration < 10000; ++iteration) {
        const PipelineResult result = run_pipeline();
        bounded = bounded && result.last_error == MaterialError::None
            && result.material_count <= kMaxMaterials
            && result.texture_count <= kMaxTextures
            && result.color_mips <= kMaxMips
            && result.normal_mips <= kMaxMips
            && result.page_count <= kMaxPages
            && result.decal_count <= kMaxDecals
            && result.transparent_count <= kMaxTransparentItems;

        MaterialSet materials{};
        const MaterialError invalid =
            add_material(materials, material(0));
        bounded = bounded && invalid == MaterialError::InvalidArgument
            && materials.count == 0;
    }
    expect(bounded, "bounded overload");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx05_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") { success = run_qlf01(); }
    else if (mode == "qlf02") { success = run_qlf02(); }
    else if (mode == "qlf03") { success = run_qlf03(); }
    else if (mode == "qlf04") { success = run_qlf04(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
