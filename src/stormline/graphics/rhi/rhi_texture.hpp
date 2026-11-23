#ifndef STORMLINE_GRAPHICS_RHI_RHI_TEXTURE_HPP
#define STORMLINE_GRAPHICS_RHI_RHI_TEXTURE_HPP

#include "stormline/graphics/rhi/rhi_buffer.hpp"

namespace stormline::graphics::rhi {

[[nodiscard]] inline RhiError RhiDevice::create_texture(
    const TextureDesc& descriptor, ResourceHandle& out) noexcept {
    out = ResourceHandle{};
    if (state_ != DeviceState::Ready) {
        return RhiError::DeviceLost;
    }
    if (descriptor.width == 0 || descriptor.width > kMaxTextureDimension
        || descriptor.height == 0 || descriptor.height > kMaxTextureDimension
        || descriptor.levels == 0 || descriptor.levels > kMaxTextureLevels
        || descriptor.usage == 0
        || (descriptor.usage & ~static_cast<u32>(0x3F)) != 0
        || static_cast<std::uint8_t>(descriptor.format) > 3) {
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
        resources_[slot].resource_class = ResourceClass::Texture;
        resources_[slot].size = descriptor.width * descriptor.height;
        out = ResourceHandle{
            generation_, slot, resources_[slot].slot_generation, ResourceClass::Texture};
        return RhiError::None;
    }
    return RhiError::CapacityFull;
}

}  // namespace stormline::graphics::rhi

#endif  // STORMLINE_GRAPHICS_RHI_RHI_TEXTURE_HPP
