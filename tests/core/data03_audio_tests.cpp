#include "stormline/data/import/audio_metadata.hpp"

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

bool run_audio01() {
    begin();
    AudioMetadata audio{44100, 2, 16, 1};
    u32 warnings = 99;
    expect(validate_audio(audio, warnings) == ImportError::None, "valid");
    expect(warnings == 0, "warnings");
    audio = AudioMetadata{8000, 1, 8, 1};
    expect(validate_audio(audio, warnings) == ImportError::None, "min valid");
    audio = AudioMetadata{192000, 8, 32, kMaxAudioFrames};
    expect(validate_audio(audio, warnings) == ImportError::None, "max valid");
    audio = AudioMetadata{7999, 2, 16, 1};
    expect(validate_audio(audio, warnings) == ImportError::InvalidAudio, "low rate");
    audio = AudioMetadata{192001, 2, 16, 1};
    expect(validate_audio(audio, warnings) == ImportError::InvalidAudio, "high rate");
    audio = AudioMetadata{44100, 0, 16, 1};
    expect(validate_audio(audio, warnings) == ImportError::InvalidAudio, "zero channels");
    audio = AudioMetadata{44100, 9, 16, 1};
    expect(validate_audio(audio, warnings) == ImportError::InvalidAudio, "many channels");
    audio = AudioMetadata{44100, 2, 12, 1};
    expect(validate_audio(audio, warnings) == ImportError::InvalidAudio, "bits 12");
    audio = AudioMetadata{44100, 2, 16, 0};
    expect(validate_audio(audio, warnings) == ImportError::InvalidAudio, "zero frames");
    audio = AudioMetadata{44100, 2, 16, kMaxAudioFrames + 1};
    expect(validate_audio(audio, warnings) == ImportError::InvalidAudio, "many frames");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data03_audio_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "audio01") { success = run_audio01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
