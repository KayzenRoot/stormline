#ifndef STORMLINE_GRAPHICS_RHI_RHI_DEVICE_HPP
#define STORMLINE_GRAPHICS_RHI_RHI_DEVICE_HPP

#include "stormline/graphics/rhi/rhi_types.hpp"

#include <array>

namespace stormline::graphics::rhi {

[[nodiscard]] inline u32 adapter_count() noexcept {
    return 1;
}

[[nodiscard]] inline RhiError adapter_at(u32 index, AdapterInfo& out) noexcept {
    if (index != 0) {
        return RhiError::InvalidAdapter;
    }
    out = AdapterInfo{
        1, Backend::Null, 0xFFFF, 0x0001,
        kFeatureCompute | kFeatureIndirectDraw,
        kMaxBufferBytes, kMaxTextureDimension, kMaxTextureLevels};
    return RhiError::None;
}

class RhiDevice final {
public:
    RhiDevice() noexcept = default;

    [[nodiscard]] RhiError init(const DeviceDescriptor& descriptor, Capabilities& out) noexcept {
        if (state_ != DeviceState::Uninitialized || descriptor.adapter_id == 0
            || descriptor.required_features == 0
            || (descriptor.required_features & ~kAllFeatures) != 0
            || descriptor.required_tier != 1) {
            return RhiError::UnsupportedFeature;
        }
        AdapterInfo adapter{};
        if (adapter_at(0, adapter) != RhiError::None
            || adapter.adapter_id != descriptor.adapter_id) {
            return RhiError::InvalidAdapter;
        }
        if ((descriptor.required_features & ~adapter.feature_flags) != 0) {
            return RhiError::UnsupportedFeature;
        }
        state_ = DeviceState::Ready;
        generation_ = 1;
        capabilities_ = Capabilities{
            static_cast<u32>(generation_), adapter.feature_flags,
            adapter.max_buffer_bytes, adapter.max_texture_dimension,
            adapter.max_texture_levels, 0x3};
        out = capabilities_;
        return RhiError::None;
    }

    [[nodiscard]] RhiError close() noexcept {
        if (state_ == DeviceState::Uninitialized) {
            return RhiError::InvalidArgument;
        }
        state_ = DeviceState::Disposed;
        return RhiError::None;
    }

    [[nodiscard]] RhiError lose() noexcept {
        if (state_ != DeviceState::Ready) {
            return RhiError::InvalidArgument;
        }
        state_ = DeviceState::Lost;
        return RhiError::None;
    }

    [[nodiscard]] RhiError recover(Capabilities& out) noexcept {
        if (state_ != DeviceState::Lost) {
            return RhiError::InvalidArgument;
        }
        ++generation_;
        state_ = DeviceState::Ready;
        capabilities_.device_generation = static_cast<u32>(generation_);
        out = capabilities_;
        return RhiError::None;
    }

    [[nodiscard]] DeviceState state() const noexcept { return state_; }
    [[nodiscard]] u64 generation() const noexcept { return generation_; }
    [[nodiscard]] Capabilities capabilities() const noexcept { return capabilities_; }

    [[nodiscard]] RhiError create_buffer(
        const BufferDesc& descriptor, ResourceHandle& out) noexcept;
    [[nodiscard]] RhiError create_texture(
        const TextureDesc& descriptor, ResourceHandle& out) noexcept;
    [[nodiscard]] RhiError release(const ResourceHandle& handle) noexcept;
    [[nodiscard]] RhiError resource_info(
        const ResourceHandle& handle, ResourceClass& out_class,
        u32& out_size) const noexcept;
    [[nodiscard]] bool queue_supported(QueueRole role) const noexcept;
    [[nodiscard]] RhiError submit(QueueRole role, u32 command_count) noexcept;
    [[nodiscard]] u32 submit_count() const noexcept;
    [[nodiscard]] RhiError validate_barrier(const Barrier& barrier) const noexcept;

private:
    DeviceState state_{DeviceState::Uninitialized};
    u64 generation_{0};
    struct ResourceSlot {
        bool used{false};
        ResourceClass resource_class{ResourceClass::Buffer};
        u32 size{0};
        u32 slot_generation{0};
    };

    Capabilities capabilities_{};
    std::array<ResourceSlot, kMaxResources> resources_{};
    u32 submit_count_{0};
};

}  // namespace stormline::graphics::rhi

#endif  // STORMLINE_GRAPHICS_RHI_RHI_DEVICE_HPP
