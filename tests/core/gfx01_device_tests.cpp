#include "stormline/graphics/rhi/rhi_device.hpp"

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

bool run_dev01() {
    begin();
    AdapterInfo adapter{};
    expect(adapter_count() == 1, "adapter count");
    expect(adapter_at(0, adapter) == RhiError::None, "adapter");
    expect(adapter.adapter_id == 1 && adapter.backend == Backend::Null, "adapter values");
    expect(adapter_at(1, adapter) == RhiError::InvalidAdapter, "adapter range");

    RhiDevice device;
    expect(device.state() == DeviceState::Uninitialized, "initial");
    Capabilities caps{};
    expect(device.init(DeviceDescriptor{1, kFeatureCompute, 1}, caps) == RhiError::None,
           "init");
    expect(device.state() == DeviceState::Ready && device.generation() == 1, "ready");
    expect(caps.device_generation == 1 && (caps.feature_flags & kFeatureCompute) != 0,
           "caps");
    expect(device.init(DeviceDescriptor{1, kFeatureCompute, 1}, caps)
               == RhiError::UnsupportedFeature,
           "double init");
    expect(device.lose() == RhiError::None, "lose");
    expect(device.state() == DeviceState::Lost, "lost");
    expect(device.recover(caps) == RhiError::None, "recover");
    expect(device.generation() == 2 && caps.device_generation == 2, "generation");
    expect(device.close() == RhiError::None, "close");
    expect(device.state() == DeviceState::Disposed, "disposed");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx01_device_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "dev01") { success = run_dev01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
