#include "stormline/graphics/rhi/rhi_texture.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::rhi;

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
    RhiDevice device;
    ResourceHandle handle{};
    expect(device.create_texture(TextureDesc{16, 16, 1, Format::Rgba8Unorm, 1}, handle)
           == RhiError::DeviceLost, "uninitialized");
    Capabilities caps{};
    expect(device.init(DeviceDescriptor{1, kFeatureCompute, 1}, caps) == RhiError::None,
           "init");
    expect(device.create_texture(TextureDesc{0, 16, 1, Format::Rgba8Unorm, 1}, handle)
           == RhiError::InvalidDescriptor, "width");
    expect(device.create_texture(TextureDesc{16, 0, 1, Format::Rgba8Unorm, 1}, handle)
           == RhiError::InvalidDescriptor, "height");
    expect(device.create_texture(TextureDesc{kMaxTextureDimension + 1, 16, 1,
                                             Format::Rgba8Unorm, 1}, handle)
           == RhiError::InvalidDescriptor, "wide");
    expect(device.create_texture(TextureDesc{16, 16, 0, Format::Rgba8Unorm, 1}, handle)
           == RhiError::InvalidDescriptor, "levels");
    expect(device.create_texture(TextureDesc{16, 16, kMaxTextureLevels + 1,
                                             Format::Rgba8Unorm, 1}, handle)
           == RhiError::InvalidDescriptor, "many levels");
    expect(device.create_texture(TextureDesc{16, 16, 1, Format::Rgba8Unorm, 0}, handle)
           == RhiError::InvalidDescriptor, "usage");
    expect(device.create_texture(TextureDesc{16, 16, 1, Format::Rgba8Unorm, 0x40}, handle)
           == RhiError::InvalidDescriptor, "usage bits");
    expect(device.create_texture(TextureDesc{16, 16, 1, Format::Rgba8Unorm, 1}, handle)
           == RhiError::None, "create");
    expect(handle.resource_class == ResourceClass::Texture, "class");
    ResourceClass cls{};
    u32 size = 0;
    expect(device.resource_info(handle, cls, size) == RhiError::None
           && cls == ResourceClass::Texture && size == 256, "info");
    expect(device.release(handle) == RhiError::None, "release");
    expect(device.resource_info(handle, cls, size) == RhiError::StaleHandle, "released");

    RhiDevice full;
    (void)full.init(DeviceDescriptor{1, kFeatureCompute, 1}, caps);
    for (u32 index = 0; index < kMaxResources; ++index) {
        expect(full.create_texture(TextureDesc{1, 1, 1, Format::Rgba8Unorm, 1}, handle)
               == RhiError::None, "fill");
    }
    expect(full.create_texture(TextureDesc{1, 1, 1, Format::Rgba8Unorm, 1}, handle)
           == RhiError::CapacityFull, "capacity");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx01_texture_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "tex01") { success = run_tex01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
