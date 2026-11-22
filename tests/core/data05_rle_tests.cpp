#include "stormline/data/bundle/rle.hpp"

#include <array>
#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::data::bundle;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_rle01() {
    begin();
    const std::array<std::uint8_t, 6> input{1, 1, 1, 2, 2, 3};
    std::array<std::uint8_t, 16> encoded{};
    u32 encoded_size = 0;
    expect(rle_encode(input, encoded, encoded_size) == BundleError::None, "encode");
    expect(encoded_size == 6 && encoded[0] == 3 && encoded[1] == 1, "encoded values");
    std::array<std::uint8_t, 16> decoded{};
    u32 decoded_size = 0;
    expect(rle_decode(std::span<const std::uint8_t>(encoded.data(), encoded_size),
                      decoded, decoded_size) == BundleError::None, "decode");
    expect(decoded_size == input.size(), "decoded size");
    for (u32 index = 0; index < decoded_size; ++index) {
        expect(decoded[index] == input[index], "decoded value");
    }

    std::array<std::uint8_t, 300> repeated{};
    for (auto& byte : repeated) {
        byte = 9;
    }
    std::array<std::uint8_t, 600> encoded_repeat{};
    expect(rle_encode(std::span<const std::uint8_t>(repeated.data(), kMaxChunkBytes), encoded_repeat, encoded_size) == BundleError::None,
           "encode repeat");
    expect(encoded_size == 4 && encoded_repeat[0] == 255 && encoded_repeat[2] == 1,
           "run split");

    const std::array<std::uint8_t, 1> one{7};
    expect(rle_encode(one, std::span<std::uint8_t>(), encoded_size)
           == BundleError::BufferFull, "encode buffer");
    expect(encoded_size == 2, "encode required");
    expect(rle_encode(std::span<const std::uint8_t>(), encoded, encoded_size)
           == BundleError::InvalidArgument, "empty input");

    const std::array<std::uint8_t, 2> bad_run{0, 1};
    expect(rle_decode(bad_run, decoded, decoded_size) == BundleError::InvalidArgument,
           "zero run");
    const std::array<std::uint8_t, 1> odd{1};
    expect(rle_decode(odd, decoded, decoded_size) == BundleError::InvalidArgument,
           "odd");
    std::array<std::uint8_t, 512> huge{};
    huge[0] = 255;
    huge[1] = 1;
    huge[2] = 255;
    huge[3] = 1;
    expect(rle_decode(std::span<const std::uint8_t>(huge.data(), 4), decoded, decoded_size)
           == BundleError::CompressionLimit, "limit");
    const std::array<std::uint8_t, 2> small_output{2, 1};
    expect(rle_decode(small_output, std::span<std::uint8_t>(), decoded_size)
           == BundleError::BufferFull, "decode buffer");
    expect(decoded_size == 2, "decode required");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_data05_rle_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "rle01") { success = run_rle01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
