#include "stormline/graphics/rhi/rhi_feature.hpp"
#include "stormline/graphics/rhi/rhi_queue.hpp"
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

[[nodiscard]] bool init_device(RhiDevice& device, Capabilities& caps,
                               u32 features = kFeatureCompute | kFeatureIndirectDraw) {
    return device.init(DeviceDescriptor{1, features, 1}, caps) == RhiError::None;
}

bool run_qlf_g01() {
    begin();
    AdapterInfo adapter{};
    expect(adapter_count() == 1 && adapter_at(0, adapter) == RhiError::None, "adapter");
    RhiDevice device;
    Capabilities caps{};
    expect(init_device(device, caps), "init");
    expect(caps.device_generation == 1, "generation");
    expect(device.queue_supported(QueueRole::Graphics)
               && device.queue_supported(QueueRole::Compute)
               && device.queue_supported(QueueRole::Transfer),
           "queues");
    expect(device.submit(QueueRole::Graphics, 1) == RhiError::None, "submit graphics");
    expect(device.submit(QueueRole::Compute, 2) == RhiError::None, "submit compute");
    expect(device.submit(QueueRole::Transfer, 3) == RhiError::None, "submit transfer");
    expect(device.submit_count() == 3, "submit count");

    ResourceHandle buffer{};
    expect(device.create_buffer(BufferDesc{256, 1, 1}, buffer) == RhiError::None,
           "buffer");
    ResourceClass buffer_class{};
    u32 buffer_size = 0;
    expect(device.resource_info(buffer, buffer_class, buffer_size) == RhiError::None
               && buffer_class == ResourceClass::Buffer && buffer_size == 256,
           "buffer info");
    expect(device.validate_barrier(Barrier{buffer, 1, 2, 1, 2}) == RhiError::None,
           "buffer barrier");

    ResourceHandle texture{};
    expect(device.create_texture(TextureDesc{64, 32, 2, Format::Rgba8Srgb, 1}, texture)
               == RhiError::None,
           "texture");
    ResourceClass texture_class{};
    u32 texture_size = 0;
    expect(device.resource_info(texture, texture_class, texture_size) == RhiError::None
               && texture_class == ResourceClass::Texture && texture_size == 64 * 32,
           "texture info");
    expect(device.validate_barrier(Barrier{texture, 1, 2, 1, 2}) == RhiError::None,
           "texture barrier");

    expect(device.lose() == RhiError::None, "lose");
    expect(device.submit(QueueRole::Graphics, 1) == RhiError::DeviceLost, "lost submit");
    ResourceHandle lost_handle{};
    expect(device.create_buffer(BufferDesc{1, 1, 1}, lost_handle) == RhiError::DeviceLost,
           "lost create");
    expect(device.validate_barrier(Barrier{texture, 1, 2, 1, 2}) == RhiError::DeviceLost,
           "lost barrier");
    expect(device.recover(caps) == RhiError::None, "recover");
    expect(caps.device_generation == 2, "recovered generation");
    expect(device.validate_barrier(Barrier{buffer, 1, 2, 1, 2})
               == RhiError::StaleGeneration,
           "stale barrier");
    expect(device.release(texture) == RhiError::StaleGeneration, "stale release");

    ResourceHandle recovered_buffer{};
    ResourceHandle recovered_texture{};
    expect(device.create_buffer(BufferDesc{8, 1, 1}, recovered_buffer) == RhiError::None,
           "recovered buffer");
    expect(device.create_texture(TextureDesc{2, 2, 1, Format::R32Float, 1},
                                 recovered_texture) == RhiError::None,
           "recovered texture");
    expect(device.validate_barrier(Barrier{recovered_buffer, 1, 2, 1, 2})
               == RhiError::None,
           "recovered barrier");
    expect(device.submit(QueueRole::Graphics, 1) == RhiError::None, "recovered submit");
    expect(device.close() == RhiError::None && device.state() == DeviceState::Disposed,
           "close");
    return finish();
}

struct Snapshot {
    u64 generation{0};
    u32 features{0};
    u32 buffer_bytes{0};
    u32 dimension{0};
    u32 levels{0};
    u32 queue_roles{0};
    u32 submit_count{0};
    u32 buffer_slot{0};
    u32 buffer_slot_generation{0};
    u32 texture_slot{0};
    u32 texture_slot_generation{0};
    u32 barrier_result{0};
};

[[nodiscard]] bool snapshot(Snapshot& out) {
    RhiDevice device;
    Capabilities caps{};
    if (!init_device(device, caps)) {
        return false;
    }
    if (device.submit(QueueRole::Graphics, 1) != RhiError::None
        || device.submit(QueueRole::Compute, 2) != RhiError::None) {
        return false;
    }
    ResourceHandle buffer{};
    ResourceHandle texture{};
    if (device.create_buffer(BufferDesc{128, 1, 1}, buffer) != RhiError::None
        || device.create_texture(TextureDesc{8, 8, 2, Format::Rgba8Unorm, 1}, texture)
               != RhiError::None) {
        return false;
    }
    if (device.validate_barrier(Barrier{buffer, 1, 2, 1, 2}) != RhiError::None) {
        return false;
    }
    if (device.lose() != RhiError::None || device.recover(caps) != RhiError::None) {
        return false;
    }
    out.generation = device.generation();
    out.features = caps.feature_flags;
    out.buffer_bytes = caps.max_buffer_bytes;
    out.dimension = caps.max_texture_dimension;
    out.levels = caps.max_texture_levels;
    out.queue_roles = caps.queue_roles;
    out.submit_count = device.submit_count();
    out.buffer_slot = buffer.slot;
    out.buffer_slot_generation = buffer.slot_generation;
    out.texture_slot = texture.slot;
    out.texture_slot_generation = texture.slot_generation;
    out.barrier_result = static_cast<u32>(
        device.validate_barrier(Barrier{buffer, 1, 2, 1, 2}));
    return true;
}

bool run_qlf_g02() {
    begin();
    Snapshot first{};
    Snapshot second{};
    expect(snapshot(first), "first snapshot");
    expect(snapshot(second), "second snapshot");
    expect(first.generation == second.generation, "generation repeat");
    expect(first.features == second.features, "features repeat");
    expect(first.buffer_bytes == second.buffer_bytes, "buffer repeat");
    expect(first.dimension == second.dimension, "dimension repeat");
    expect(first.levels == second.levels, "levels repeat");
    expect(first.queue_roles == second.queue_roles, "queues repeat");
    expect(first.submit_count == second.submit_count, "submit repeat");
    expect(first.buffer_slot == second.buffer_slot, "buffer slot repeat");
    expect(first.buffer_slot_generation == second.buffer_slot_generation,
           "buffer generation repeat");
    expect(first.texture_slot == second.texture_slot, "texture slot repeat");
    expect(first.texture_slot_generation == second.texture_slot_generation,
           "texture generation repeat");
    expect(first.barrier_result == second.barrier_result, "barrier repeat");
    return finish();
}

bool run_qlf_g03() {
    begin();
    AdapterInfo adapter{};
    expect(adapter_at(1, adapter) == RhiError::InvalidAdapter, "bad adapter");
    expect(adapter_at(0, adapter) == RhiError::None, "after bad adapter");

    RhiDevice device;
    ResourceHandle buffer{};
    expect(device.create_buffer(BufferDesc{1, 1, 1}, buffer) == RhiError::DeviceLost,
           "pre-init buffer");
    Capabilities caps{};
    expect(device.init(DeviceDescriptor{1, kFeatureTimestampQuery, 1}, caps)
               == RhiError::UnsupportedFeature,
           "unsupported feature");
    expect(init_device(device, caps), "after unsupported feature");
    expect(device.create_buffer(BufferDesc{0, 1, 1}, buffer)
               == RhiError::InvalidDescriptor,
           "bad buffer");
    expect(device.create_buffer(BufferDesc{16, 1, 1}, buffer) == RhiError::None,
           "after bad buffer");
    ResourceHandle bad_handle{};
    expect(device.create_texture(TextureDesc{0, 1, 1, Format::Rgba8Unorm, 1}, bad_handle)
               == RhiError::InvalidDescriptor,
           "bad texture");
    ResourceHandle texture{};
    expect(device.create_texture(TextureDesc{2, 2, 1, Format::Rgba8Unorm, 1}, texture)
               == RhiError::None,
           "after bad texture");
    expect(device.submit(QueueRole::Graphics, 0) == RhiError::InvalidArgument,
           "zero submit");
    expect(device.submit(QueueRole::Graphics, 1) == RhiError::None, "after zero submit");
    expect(device.submit(static_cast<QueueRole>(99), 1) == RhiError::QueueUnsupported,
           "bad queue");
    expect(device.submit(QueueRole::Graphics, 1) == RhiError::None, "after bad queue");
    expect(device.validate_barrier(Barrier{buffer, 0, 2, 1, 2}) == RhiError::SyncInvalid,
           "bad barrier");
    expect(device.validate_barrier(Barrier{buffer, 1, 2, 1, 2}) == RhiError::None,
           "after bad barrier");
    expect(device.release(buffer) == RhiError::None, "release");
    ResourceClass resource_class{};
    u32 size = 0;
    expect(device.resource_info(buffer, resource_class, size) == RhiError::StaleHandle,
           "stale handle");
    ResourceHandle reused{};
    expect(device.create_buffer(BufferDesc{4, 1, 1}, reused) == RhiError::None,
           "after stale handle");
    expect(device.lose() == RhiError::None, "lose");
    expect(device.release(texture) == RhiError::DeviceLost, "lost release");
    expect(device.recover(caps) == RhiError::None, "recover");
    expect(device.validate_barrier(Barrier{reused, 1, 2, 1, 2})
               == RhiError::StaleGeneration,
           "stale generation");
    ResourceHandle recovered{};
    expect(device.create_buffer(BufferDesc{4, 1, 1}, recovered) == RhiError::None,
           "after stale generation");

    RhiDevice full;
    expect(init_device(full, caps), "full init");
    ResourceHandle handles[kMaxResources]{};
    for (u32 index = 0; index < kMaxResources; ++index) {
        expect(full.create_buffer(BufferDesc{1, 1, 1}, handles[index]) == RhiError::None,
               "fill capacity");
    }
    expect(full.create_buffer(BufferDesc{1, 1, 1}, recovered) == RhiError::CapacityFull,
           "capacity full");
    expect(full.release(handles[0]) == RhiError::None, "release for capacity");
    expect(full.create_buffer(BufferDesc{1, 1, 1}, recovered) == RhiError::None,
           "after capacity");
    return finish();
}

bool run_qlf_g04() {
    begin();
    RhiDevice device;
    Capabilities caps{};
    expect(init_device(device, caps), "init");

    ResourceHandle buffer{};
    for (u32 index = 0; index < 10000; ++index) {
        expect(device.create_buffer(BufferDesc{1, 1, 1}, buffer) == RhiError::None,
               "bounded create");
        expect(device.release(buffer) == RhiError::None, "bounded release");
    }

    ResourceHandle handles[kMaxResources]{};
    u32 created = 0;
    for (u32 index = 0; index < 10000; ++index) {
        ResourceHandle candidate{};
        const RhiError status = device.create_buffer(BufferDesc{1, 1, 1}, candidate);
        if (status == RhiError::None) {
            if (created < kMaxResources) {
                handles[created] = candidate;
            }
            ++created;
        } else {
            expect(status == RhiError::CapacityFull, "capacity typed");
        }
    }
    expect(created == kMaxResources, "bounded capacity");
    for (u32 index = 0; index < kMaxResources; ++index) {
        expect(device.release(handles[index]) == RhiError::None, "release capacity");
    }

    for (u32 index = 0; index < 10000; ++index) {
        expect(device.submit(QueueRole::Graphics, 1) == RhiError::None,
               "bounded submit");
    }
    expect(device.submit_count() == 10000, "submit total");

    expect(device.create_buffer(BufferDesc{8, 1, 1}, buffer) == RhiError::None,
           "barrier buffer");
    for (u32 index = 0; index < 10000; ++index) {
        expect(device.validate_barrier(Barrier{buffer, 1, 2, 1, 2}) == RhiError::None,
               "bounded barrier");
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx01_rhi_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") { success = run_qlf_g01(); }
    else if (mode == "qlf02") { success = run_qlf_g02(); }
    else if (mode == "qlf03") { success = run_qlf_g03(); }
    else if (mode == "qlf04") { success = run_qlf_g04(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
