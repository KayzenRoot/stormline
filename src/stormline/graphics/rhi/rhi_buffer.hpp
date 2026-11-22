#ifndef STORMLINE_GRAPHICS_RHI_RHI_BUFFER_HPP
#define STORMLINE_GRAPHICS_RHI_RHI_BUFFER_HPP

#include "stormline/graphics/rhi/rhi_device.hpp"

namespace stormline::graphics::rhi {

[[nodiscard]] inline RhiError RhiDevice::create_buffer(
    const BufferDesc& descriptor, ResourceHandle& out) noexcept {
    out = ResourceHandle{};
    if (state_ != DeviceState::Ready) {
        return RhiError::DeviceLost;
    }
    const bool aligned = descriptor.alignment != 0
        && (descriptor.alignment & (descriptor.alignment - 1)) == 0
        && descriptor.alignment <= 256;
    if (descriptor.size == 0 || descriptor.size > kMaxBufferBytes
        || descriptor.usage == 0 || (descriptor.usage & ~static_cast<u32>(0x3F)) != 0
        || !aligned) {
        return RhiError::InvalidDescriptor;
    }
    for (u32 slot = 0; slot < kMaxResources; ++slot) {
        if (resources_[slot].used) {
            continue;
        }
        if (resources_[slot].slot_generation == 0xFFFFFFFFu) {
            return RhiError::StaleGeneration;
        }
        ++resources_[slot].slot_generation;
        resources_[slot].used = true;
        resources_[slot].resource_class = ResourceClass::Buffer;
        resources_[slot].size = descriptor.size;
        out = ResourceHandle{
            generation_, slot, resources_[slot].slot_generation, ResourceClass::Buffer};
        return RhiError::None;
    }
    return RhiError::CapacityFull;
}

[[nodiscard]] inline RhiError RhiDevice::release(const ResourceHandle& handle) noexcept {
    if (state_ != DeviceState::Ready) {
        return RhiError::DeviceLost;
    }
    if (handle.device_generation == 0 || handle.slot >= kMaxResources) {
        return RhiError::StaleHandle;
    }
    if (handle.device_generation != generation_) {
        return RhiError::StaleGeneration;
    }
    ResourceSlot& slot = resources_[handle.slot];
    if (!slot.used || slot.slot_generation != handle.slot_generation
        || slot.resource_class != handle.resource_class) {
        return RhiError::StaleHandle;
    }
    slot.used = false;
    ++slot.slot_generation;
    return RhiError::None;
}

[[nodiscard]] inline RhiError RhiDevice::resource_info(
    const ResourceHandle& handle, ResourceClass& out_class,
    u32& out_size) const noexcept {
    out_class = ResourceClass::Buffer;
    out_size = 0;
    if (state_ != DeviceState::Ready) {
        return RhiError::DeviceLost;
    }
    if (handle.device_generation == 0 || handle.slot >= kMaxResources) {
        return RhiError::StaleHandle;
    }
    if (handle.device_generation != generation_) {
        return RhiError::StaleGeneration;
    }
    const ResourceSlot& slot = resources_[handle.slot];
    if (!slot.used || slot.slot_generation != handle.slot_generation
        || slot.resource_class != handle.resource_class) {
        return RhiError::StaleHandle;
    }
    out_class = slot.resource_class;
    out_size = slot.size;
    return RhiError::None;
}

}  // namespace stormline::graphics::rhi

#endif  // STORMLINE_GRAPHICS_RHI_RHI_BUFFER_HPP
