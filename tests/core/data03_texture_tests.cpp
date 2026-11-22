#include "stormline/data/import/texture_metadata.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::data::imports;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_tex01() {
    begin();
    TextureMetadata texture{};
    u32 warnings = 99;
    texture.width = 1;
    texture.height = 1;
    texture.channels = 1;
    expect(validate_texture(texture, warnings) == ImportError::None, "minimal");
    expect(warnings == 0, "minimal warnings");
    texture.width = kMaxTextureDimension;
    texture.height = kMaxTextureDimension;
    texture.mip_levels = kMaxMipLevels;
    expect(validate_texture(texture, warnings) == ImportError::None, "maximal");
    expect(warnings == 0, "maximal warnings");

    texture.width = 100;
    texture.height = 64;
    texture.mip_levels = 7;
    expect(validate_texture(texture, warnings) == ImportError::None, "non pot");
    expect(warnings == 1, "non pot warning");

    texture.width = 0;
    expect(validate_texture(texture, warnings) == ImportError::InvalidTexture, "zero width");
    texture.width = kMaxTextureDimension + 1;
    expect(validate_texture(texture, warnings) == ImportError::InvalidTexture, "wide");
    texture.width = 64;
    texture.height = 0;
    expect(validate_texture(texture, warnings) == ImportError::InvalidTexture, "zero height");
    texture.height = kMaxTextureDimension + 1;
    expect(validate_texture(texture, warnings) == ImportError::InvalidTexture, "tall");
    texture.height = 64;
    texture.channels = 0;
    expect(validate_texture(texture, warnings) == ImportError::InvalidTexture, "zero channels");
    texture.channels = 5;
    expect(validate_texture(texture, warnings) == ImportError::InvalidTexture, "many channels");
    texture.channels = 4;
    texture.mip_levels = kMaxMipLevels + 1;
    expect(validate_texture(texture, warnings) == ImportError::InvalidTexture, "too many mips");
    texture.mip_levels = 7;
    expect(validate_texture(texture, warnings) == ImportError::None, "max mips for 64");
    texture.width = 8;
    texture.height = 8;
    texture.mip_levels = 4;
    expect(validate_texture(texture, warnings) == ImportError::None, "mips 8");
    texture.mip_levels = 5;
    expect(validate_texture(texture, warnings) == ImportError::InvalidTexture, "mips 8 plus");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data03_texture_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "tex01") { success = run_tex01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
