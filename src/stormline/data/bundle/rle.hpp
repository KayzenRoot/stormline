#ifndef STORMLINE_DATA_BUNDLE_RLE_HPP
#define STORMLINE_DATA_BUNDLE_RLE_HPP

#include "stormline/data/bundle/bundle_types.hpp"

#include <span>

namespace stormline::data::bundle {

[[nodiscard]] inline BundleError rle_encode(
    std::span<const u8> input, std::span<u8> output,
    u32& out_size) noexcept {
    out_size = 0;
    if (input.empty() || input.size() > kMaxChunkBytes) {
        return BundleError::InvalidArgument;
    }
    u32 required = 0;
    for (u32 index = 0; index < static_cast<u32>(input.size());) {
        u32 run = 1;
        while (index + run < input.size() && input[index + run] == input[index]
               && run < 255) {
            ++run;
        }
        required += 2;
        index += run;
    }
    if (output.size() < required) {
        out_size = required;
        return BundleError::BufferFull;
    }
    u32 written = 0;
    for (u32 index = 0; index < static_cast<u32>(input.size());) {
        u32 run = 1;
        while (index + run < input.size() && input[index + run] == input[index]
               && run < 255) {
            ++run;
        }
        output[written++] = static_cast<u8>(run);
        output[written++] = input[index];
        index += run;
    }
    out_size = written;
    return BundleError::None;
}

[[nodiscard]] inline BundleError rle_decode(
    std::span<const u8> encoded, std::span<u8> output,
    u32& out_size) noexcept {
    out_size = 0;
    if (encoded.empty() || (encoded.size() % 2) != 0) {
        return BundleError::InvalidArgument;
    }
    u32 required = 0;
    for (u32 index = 0; index < static_cast<u32>(encoded.size()); index += 2) {
        const u32 run = encoded[index];
        if (run == 0) {
            return BundleError::InvalidArgument;
        }
        if (required + run > kMaxChunkBytes) {
            return BundleError::CompressionLimit;
        }
        required += run;
    }
    if (output.size() < required) {
        out_size = required;
        return BundleError::BufferFull;
    }
    u32 written = 0;
    for (u32 index = 0; index < static_cast<u32>(encoded.size()); index += 2) {
        const u32 run = encoded[index];
        for (u32 count = 0; count < run; ++count) {
            output[written++] = encoded[index + 1];
        }
    }
    out_size = written;
    return BundleError::None;
}

}  // namespace stormline::data::bundle

#endif  // STORMLINE_DATA_BUNDLE_RLE_HPP
