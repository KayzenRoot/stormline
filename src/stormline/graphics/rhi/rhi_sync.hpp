#ifndef STORMLINE_GRAPHICS_RHI_RHI_SYNC_HPP
#define STORMLINE_GRAPHICS_RHI_RHI_SYNC_HPP

#include "stormline/graphics/rhi/rhi_buffer.hpp"

namespace stormline::graphics::rhi {

[[nodiscard]] inline RhiError RhiDevice::validate_barrier(
    const Barrier& barrier) const noexcept {
    if (state_ != DeviceState::Ready) {
        return RhiError::DeviceLost;
    }
    const ResourceHandle& handle = barrier.resource;
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
    constexpr u32 kAccessMask = 0x3F;
    constexpr u32 kStageMask = 0xF;
    if (barrier.old_access == 0 || barrier.new_access == 0
        || (barrier.old_access & ~kAccessMask) != 0
        || (barrier.new_access & ~kAccessMask) != 0) {
        return RhiError::SyncInvalid;
    }
    if (barrier.old_stage == 0 || barrier.new_stage == 0
        || (barrier.old_stage & ~kStageMask) != 0
        || (barrier.new_stage & ~kStageMask) != 0) {
        return RhiError::SyncInvalid;
    }
    if (barrier.old_access == barrier.new_access
        && barrier.old_stage == barrier.new_stage) {
        return RhiError::SyncInvalid;
    }
    return RhiError::None;
}

}  // namespace stormline::graphics::rhi

#endif  // STORMLINE_GRAPHICS_RHI_RHI_SYNC_HPP
