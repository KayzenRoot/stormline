#ifndef STORMLINE_GRAPHICS_RHI_RHI_QUEUE_HPP
#define STORMLINE_GRAPHICS_RHI_RHI_QUEUE_HPP

#include "stormline/graphics/rhi/rhi_device.hpp"

namespace stormline::graphics::rhi {

[[nodiscard]] inline bool RhiDevice::queue_supported(QueueRole role) const noexcept {
    if (state_ != DeviceState::Ready) {
        return false;
    }
    switch (role) {
        case QueueRole::Graphics:
        case QueueRole::Transfer:
            return true;
        case QueueRole::Compute:
            return (capabilities_.feature_flags & kFeatureCompute) != 0;
        default:
            return false;
    }
}

[[nodiscard]] inline RhiError RhiDevice::submit(QueueRole role, u32 command_count) noexcept {
    if (state_ != DeviceState::Ready) {
        return RhiError::DeviceLost;
    }
    if (!queue_supported(role)) {
        return RhiError::QueueUnsupported;
    }
    if (command_count == 0 || command_count > 64) {
        return RhiError::InvalidArgument;
    }
    ++submit_count_;
    return RhiError::None;
}

[[nodiscard]] inline u32 RhiDevice::submit_count() const noexcept {
    return submit_count_;
}

}  // namespace stormline::graphics::rhi

#endif  // STORMLINE_GRAPHICS_RHI_RHI_QUEUE_HPP
