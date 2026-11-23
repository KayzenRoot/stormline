#include "stormline/graphics/material/texture_mip.hpp"

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

[[nodiscard]] TextureDesc base_texture() {
    TextureDesc texture{};
    texture.id = 1;
    texture.width = 256;
    texture.height = 256;
    texture.levels = 9;
    texture.format = TextureFormat::Rgba8Srgb;
    texture.color_space = ColorSpace::Srgb;
    texture.usage = TextureUsage::BaseColor;
    return texture;
}

bool run_mip01() {
    begin();
    MipChain chain{};
    MaterialDiagnostic diagnostic{};

    expect(build_mip_chain(base_texture(), chain, diagnostic)
               == MaterialError::None,
           "build");
    expect(chain.texture_id == 1 && chain.count == 9, "chain identity");
    expect(chain.levels[0].width == 256 && chain.levels[0].height == 256
               && chain.levels[0].bytes == 262144,
           "level zero");
    expect(chain.levels[1].width == 128 && chain.levels[1].height == 128
               && chain.levels[1].bytes == 65536,
           "level one");
    expect(chain.levels[8].width == 1 && chain.levels[8].height == 1
               && chain.levels[8].bytes == 4,
           "level last");

    TextureDesc half = base_texture();
    half.id = 2;
    half.width = 8;
    half.height = 4;
    half.levels = 4;
    half.format = TextureFormat::Rgba16Float;
    half.color_space = ColorSpace::Linear;
    half.usage = TextureUsage::Normal;
    expect(build_mip_chain(half, chain, diagnostic) == MaterialError::None,
           "half build");
    expect(chain.count == 4, "half count");
    expect(chain.levels[0].width == 8 && chain.levels[0].height == 4
               && chain.levels[0].bytes == 256,
           "half level zero");
    expect(chain.levels[1].width == 4 && chain.levels[1].height == 2
               && chain.levels[1].bytes == 64,
           "half level one");
    expect(chain.levels[2].width == 2 && chain.levels[2].height == 1
               && chain.levels[2].bytes == 16,
           "half level two");
    expect(chain.levels[3].width == 1 && chain.levels[3].height == 1
               && chain.levels[3].bytes == 8,
           "half level three");

    TextureDesc single{};
    single.id = 3;
    single.width = 1;
    single.height = 1;
    single.levels = 1;
    single.format = TextureFormat::Rgba8Unorm;
    single.color_space = ColorSpace::Linear;
    single.usage = TextureUsage::Height;
    expect(build_mip_chain(single, chain, diagnostic) == MaterialError::None,
           "single build");
    expect(chain.count == 1 && chain.levels[0].bytes == 4, "single bytes");

    TextureDesc wide = base_texture();
    wide.id = 4;
    wide.width = 16384;
    wide.height = 16384;
    wide.levels = 12;
    expect(build_mip_chain(wide, chain, diagnostic) == MaterialError::None,
           "wide build");
    expect(chain.count == 12, "wide count");
    expect(chain.levels[0].width == 16384 && chain.levels[0].height == 16384
               && chain.levels[0].bytes == 1073741824u,
           "wide level zero");
    expect(chain.levels[11].width == 8 && chain.levels[11].height == 8
               && chain.levels[11].bytes == 256,
           "wide level last");

    TextureDesc invalid = base_texture();
    invalid.levels = 0;
    expect(build_mip_chain(invalid, chain, diagnostic)
               == MaterialError::InvalidMipChain,
           "levels zero");
    expect(chain.count == 0, "levels zero reset");
    invalid.levels = 13;
    expect(build_mip_chain(invalid, chain, diagnostic)
               == MaterialError::InvalidMipChain,
           "levels too many");
    invalid.levels = 8;
    expect(build_mip_chain(invalid, chain, diagnostic)
               == MaterialError::InvalidMipChain,
           "levels mismatch");
    expect(diagnostic.texture_id == 1, "diagnostic texture");

    invalid = base_texture();
    invalid.width = 0;
    invalid.height = 0;
    invalid.levels = 0;
    expect(build_mip_chain(invalid, chain, diagnostic)
               == MaterialError::InvalidMipChain,
           "zero dimension levels");

    invalid = base_texture();
    invalid.width = 0;
    expect(build_mip_chain(invalid, chain, diagnostic)
               == MaterialError::InvalidArgument,
           "zero width");
    invalid = base_texture();
    invalid.format = static_cast<TextureFormat>(200);
    expect(build_mip_chain(invalid, chain, diagnostic)
               == MaterialError::InvalidArgument,
           "invalid format");
    invalid = base_texture();
    invalid.color_space = ColorSpace::Linear;
    expect(build_mip_chain(invalid, chain, diagnostic)
               == MaterialError::InvalidArgument,
           "invalid color use");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx05_mip_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "mip01") { success = run_mip01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
