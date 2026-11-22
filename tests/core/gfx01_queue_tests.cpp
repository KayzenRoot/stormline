#include "stormline/graphics/rhi/rhi_queue.hpp"

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

bool run_que01() {
    begin();
    RhiDevice device;
    expect(!device.queue_supported(QueueRole::Graphics), "uninitialized queue");
    Capabilities caps{};
    expect(device.init(DeviceDescriptor{1, kFeatureCompute, 1}, caps) == RhiError::None,
           "init");
    expect(device.queue_supported(QueueRole::Graphics), "graphics");
    expect(device.queue_supported(QueueRole::Compute), "compute");
    expect(device.queue_supported(QueueRole::Transfer), "transfer");
    expect(device.submit(QueueRole::Graphics, 1) == RhiError::None, "submit");
    expect(device.submit(QueueRole::Compute, 64) == RhiError::None, "submit compute");
    expect(device.submit_count() == 2, "submit count");
    expect(device.submit(QueueRole::Graphics, 0) == RhiError::InvalidArgument, "zero");
    expect(device.submit(QueueRole::Graphics, 65) == RhiError::InvalidArgument, "many");
    expect(device.lose() == RhiError::None, "lose");
    expect(device.submit(QueueRole::Graphics, 1) == RhiError::DeviceLost, "lost");
    expect(!device.queue_supported(QueueRole::Graphics), "lost support");
    expect(device.recover(caps) == RhiError::None, "recover");
    expect(device.submit(QueueRole::Transfer, 1) == RhiError::None, "after recover");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx01_queue_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "que01") { success = run_que01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
