#include "stormline/data/import/import_validation.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::data::imports;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_val01() {
    begin();
    ArtifactMetadata metadata{};
    ValidationResult result{};
    metadata.type = ArtifactType::Unknown;
    expect(validate_artifact(metadata, result) == ImportError::InvalidArgument,
           "unknown type");

    metadata.type = ArtifactType::Texture2D;
    metadata.texture = TextureMetadata{64, 64, 7, 4, true};
    expect(validate_artifact(metadata, result) == ImportError::None, "texture valid");
    expect(result.status == ValidationStatus::Valid && result.warning_count == 0,
           "texture result");

    metadata.texture.width = 100;
    metadata.texture.height = 64;
    metadata.texture.mip_levels = 7;
    expect(validate_artifact(metadata, result) == ImportError::None, "texture warning");
    expect(result.status == ValidationStatus::Valid && result.warning_count == 1,
           "warning result");

    metadata.texture.width = 0;
    expect(validate_artifact(metadata, result) == ImportError::InvalidTexture,
           "texture invalid");
    expect(result.status == ValidationStatus::Invalid
           && result.error == ImportError::InvalidTexture, "invalid result");

    metadata.type = ArtifactType::Animation;
    metadata.animation = AnimationMetadata{2, 3, 4, 100};
    expect(validate_artifact(metadata, result) == ImportError::None, "animation valid");
    metadata.animation.joint_count = 0;
    expect(validate_artifact(metadata, result) == ImportError::InvalidAnimation,
           "animation invalid");

    metadata.type = ArtifactType::Audio;
    metadata.audio = AudioMetadata{48000, 2, 16, 100};
    expect(validate_artifact(metadata, result) == ImportError::None, "audio valid");
    metadata.audio.bits_per_sample = 12;
    expect(validate_artifact(metadata, result) == ImportError::InvalidAudio,
           "audio invalid");

    metadata.type = ArtifactType::Mesh;
    expect(validate_artifact(metadata, result) == ImportError::None, "mesh valid");
    expect(result.status == ValidationStatus::Valid, "mesh status");
    metadata.type = ArtifactType::Metadata;
    expect(validate_artifact(metadata, result) == ImportError::None, "metadata valid");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data03_validation_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "val01") { success = run_val01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
