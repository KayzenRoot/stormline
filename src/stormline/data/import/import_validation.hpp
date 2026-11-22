#ifndef STORMLINE_DATA_IMPORT_IMPORT_VALIDATION_HPP
#define STORMLINE_DATA_IMPORT_IMPORT_VALIDATION_HPP

#include "stormline/data/import/animation_metadata.hpp"
#include "stormline/data/import/audio_metadata.hpp"
#include "stormline/data/import/texture_metadata.hpp"

namespace stormline::data::imports {

struct ArtifactMetadata {
    ArtifactType type{ArtifactType::Unknown};
    TextureMetadata texture{};
    AnimationMetadata animation{};
    AudioMetadata audio{};
};

struct ValidationResult {
    ValidationStatus status{ValidationStatus::Invalid};
    ImportError error{ImportError::None};
    u32 warning_count{0};
};

[[nodiscard]] inline ImportError validate_artifact(
    const ArtifactMetadata& metadata, ValidationResult& out) noexcept {
    out = ValidationResult{};
    ImportError status = ImportError::None;
    u32 warnings = 0;
    switch (metadata.type) {
        case ArtifactType::Texture2D:
            status = validate_texture(metadata.texture, warnings);
            break;
        case ArtifactType::Animation:
            status = validate_animation(metadata.animation, warnings);
            break;
        case ArtifactType::Audio:
            status = validate_audio(metadata.audio, warnings);
            break;
        case ArtifactType::Mesh:
        case ArtifactType::Metadata:
            status = ImportError::None;
            break;
        default:
            return ImportError::InvalidArgument;
    }
    out.error = status;
    out.warning_count = warnings;
    out.status = status == ImportError::None
        ? ValidationStatus::Valid
        : ValidationStatus::Invalid;
    return status;
}

}  // namespace stormline::data::imports

#endif  // STORMLINE_DATA_IMPORT_IMPORT_VALIDATION_HPP
