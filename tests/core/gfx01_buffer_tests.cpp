#include "stormline/graphics/rhi/rhi_buffer.hpp"

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

bool run_buf01() {
    begin();
    RhiDevice device;
    ResourceHandle handle{};
    expect(device.create_buffer(BufferDesc{16, 1, 4}, handle) == RhiError::DeviceLost,
           "uninitialized");
    Capabilities caps{};
    expect(device.init(DeviceDescriptor{1, kFeatureCompute, 1}, caps) == RhiError::None,
           "init");
    expect(device.create_buffer(BufferDesc{0, 1, 1}, handle)
           == RhiError::InvalidDescriptor, "size 0");
    expect(device.create_buffer(BufferDesc{kMaxBufferBytes + 1, 1, 1}, handle)
           == RhiError::InvalidDescriptor, "too large");
    expect(device.create_buffer(BufferDesc{16, 0, 1}, handle)
           == RhiError::InvalidDescriptor, "usage");
    expect(device.create_buffer(BufferDesc{16, 0x40, 1}, handle)
           == RhiError::InvalidDescriptor, "usage bits");
    expect(device.create_buffer(BufferDesc{16, 1, 3}, handle)
           == RhiError::InvalidDescriptor, "alignment");
    expect(device.create_buffer(BufferDesc{16, 1, 4}, handle) == RhiError::None, "create");
    expect(handle.device_generation == 1 && handle.slot == 0 && handle.slot_generation == 1,
           "handle");
    ResourceClass cls{};
    u32 size = 0;
    expect(device.resource_info(handle, cls, size) == RhiError::None
           && cls == ResourceClass::Buffer && size == 16, "info");
    expect(device.release(handle) == RhiError::None, "release");
    expect(device.release(handle) == RhiError::StaleHandle, "double release");
    expect(device.resource_info(handle, cls, size) == RhiError::StaleHandle, "released info");

    ResourceHandle reused{};
    expect(device.create_buffer(BufferDesc{32, 1, 1}, reused) == RhiError::None, "reuse");
    expect(reused.slot == handle.slot && reused.slot_generation != handle.slot_generation,
           "reused generation");
    expect(device.release(handle) == RhiError::StaleHandle, "old handle");

    RhiDevice full;
    (void)full.init(DeviceDescriptor{1, kFeatureCompute, 1}, caps);
    ResourceHandle handles[kMaxResources]{};
    for (u32 index = 0; index < kMaxResources; ++index) {
        expect(full.create_buffer(BufferDesc{1, 1, 1}, handles[index]) == RhiError::None,
               "fill");
    }
    expect(full.create_buffer(BufferDesc{1, 1, 1}, handle) == RhiError::CapacityFull,
           "capacity");
    expect(device.lose() == RhiError::None, "lose");
    expect(device.release(reused) == RhiError::DeviceLost, "lost device");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx01_buffer_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "buf01") { success = run_buf01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
