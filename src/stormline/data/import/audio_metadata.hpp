#ifndef STORMLINE_DATA_IMPORT_AUDIO_METADATA_HPP
#define STORMLINE_DATA_IMPORT_AUDIO_METADATA_HPP

#include "stormline/data/import/import_types.hpp"

namespace stormline::data::imports {

struct AudioMetadata {
    u32 sample_rate{0};
    u8 channels{0};
    u8 bits_per_sample{0};
    u32 frame_count{0};
};

[[nodiscard]] inline ImportError validate_audio(
    const AudioMetadata& metadata, u32& warning_count) noexcept {
    warning_count = 0;
    const bool bits_ok = metadata.bits_per_sample == 8
        || metadata.bits_per_sample == 16 || metadata.bits_per_sample == 24
        || metadata.bits_per_sample == 32;
    if (metadata.sample_rate < 8000 || metadata.sample_rate > 192000
        || metadata.channels == 0 || metadata.channels > 8
        || !bits_ok
        || metadata.frame_count == 0 || metadata.frame_count > kMaxAudioFrames) {
        return ImportError::InvalidAudio;
    }
    return ImportError::None;
}

}  // namespace stormline::data::imports

#endif  // STORMLINE_DATA_IMPORT_AUDIO_METADATA_HPP
