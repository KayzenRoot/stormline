#include "stormline/graphics/rhi/rhi_sync.hpp"
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

[[nodiscard]] bool ready_device(RhiDevice& device) {
    Capabilities caps{};
    return device.init(DeviceDescriptor{1, kFeatureCompute, 1}, caps) == RhiError::None;
}

bool run_syn01() {
    begin();
    RhiDevice device;
    ResourceHandle buffer{};
    expect(device.create_buffer(BufferDesc{64, 1, 1}, buffer) == RhiError::DeviceLost,
           "buffer before init");

    expect(ready_device(device), "init");
    expect(device.create_buffer(BufferDesc{64, 1, 1}, buffer) == RhiError::None, "buffer");

    expect(device.validate_barrier(Barrier{buffer, 1, 2, 1, 2}) == RhiError::None,
           "valid buffer transition");
    expect(device.validate_barrier(Barrier{buffer, 1, 1, 1, 2}) == RhiError::None,
           "access unchanged stage changes");
    expect(device.validate_barrier(Barrier{buffer, 1, 2, 1, 1}) == RhiError::None,
           "stage unchanged access changes");
    expect(device.validate_barrier(Barrier{buffer, 1, 1, 1, 1}) == RhiError::SyncInvalid,
           "no-op barrier");
    expect(device.validate_barrier(Barrier{buffer, 0, 2, 1, 2}) == RhiError::SyncInvalid,
           "zero old access");
    expect(device.validate_barrier(Barrier{buffer, 1, 0, 1, 2}) == RhiError::SyncInvalid,
           "zero new access");
    expect(device.validate_barrier(Barrier{buffer, 0x40, 2, 1, 2}) == RhiError::SyncInvalid,
           "unknown old access");
    expect(device.validate_barrier(Barrier{buffer, 1, 0x40, 1, 2}) == RhiError::SyncInvalid,
           "unknown new access");
    expect(device.validate_barrier(Barrier{buffer, 1, 2, 0, 2}) == RhiError::SyncInvalid,
           "zero old stage");
    expect(device.validate_barrier(Barrier{buffer, 1, 2, 1, 0}) == RhiError::SyncInvalid,
           "zero new stage");
    expect(device.validate_barrier(Barrier{buffer, 1, 2, 0x10, 2}) == RhiError::SyncInvalid,
           "unknown old stage");
    expect(device.validate_barrier(Barrier{buffer, 1, 2, 1, 0x10}) == RhiError::SyncInvalid,
           "unknown new stage");

    ResourceHandle forged{};
    expect(device.create_buffer(BufferDesc{8, 1, 1}, forged) == RhiError::None, "forged base");
    forged.slot = kMaxResources;
    expect(device.validate_barrier(Barrier{forged, 1, 2, 1, 2}) == RhiError::StaleHandle,
           "slot range");
    forged.slot = 0;
    forged.device_generation = 0;
    expect(device.validate_barrier(Barrier{forged, 1, 2, 1, 2}) == RhiError::StaleHandle,
           "zero generation");
    forged = ResourceHandle{device.generation(), buffer.slot, buffer.slot_generation + 1,
                            buffer.resource_class};
    expect(device.validate_barrier(Barrier{forged, 1, 2, 1, 2}) == RhiError::StaleHandle,
           "slot generation");
    forged = ResourceHandle{device.generation(), buffer.slot, buffer.slot_generation,
                            ResourceClass::Texture};
    expect(device.validate_barrier(Barrier{forged, 1, 2, 1, 2}) == RhiError::StaleHandle,
           "wrong class");

    expect(device.release(buffer) == RhiError::None, "release");
    expect(device.validate_barrier(Barrier{buffer, 1, 2, 1, 2}) == RhiError::StaleHandle,
           "released handle");
    ResourceHandle reused{};
    expect(device.create_buffer(BufferDesc{16, 1, 1}, reused) == RhiError::None, "reuse");
    expect(device.validate_barrier(Barrier{buffer, 1, 2, 1, 2}) == RhiError::StaleHandle,
           "reused generation");
    expect(device.validate_barrier(Barrier{reused, 1, 2, 1, 2}) == RhiError::None,
           "reused valid");

    ResourceHandle texture{};
    expect(device.create_texture(TextureDesc{4, 4, 1, Format::Rgba8Unorm, 1}, texture)
               == RhiError::None,
           "texture");
    expect(device.validate_barrier(Barrier{texture, 1, 2, 1, 2}) == RhiError::None,
           "texture transition");

    expect(device.lose() == RhiError::None, "lose");
    expect(device.validate_barrier(Barrier{texture, 1, 2, 1, 2}) == RhiError::DeviceLost,
           "lost device");
    Capabilities caps{};
    expect(device.recover(caps) == RhiError::None, "recover");
    expect(device.validate_barrier(Barrier{texture, 1, 2, 1, 2}) == RhiError::StaleGeneration,
           "stale device generation");
    ResourceHandle recovered{};
    expect(device.create_texture(TextureDesc{2, 2, 1, Format::Rgba8Unorm, 1}, recovered)
               == RhiError::None,
           "recovered texture");
    expect(device.validate_barrier(Barrier{recovered, 1, 2, 1, 2}) == RhiError::None,
           "recovered valid");
    expect(device.close() == RhiError::None, "close");
    expect(device.validate_barrier(Barrier{recovered, 1, 2, 1, 2}) == RhiError::DeviceLost,
           "closed device");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx01_sync_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "syn01") { success = run_syn01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
