#include "stormline/core/math/ids.hpp"

#include <cstdint>
#include <cstdio>
#include <string_view>

namespace {

using stormline::core::math::decode_persistent_id;
using stormline::core::math::encode_persistent_id;
using stormline::core::math::handle_is_current;
using stormline::core::math::IdBytes;
using stormline::core::math::MathError;
using stormline::core::math::PersistentId;
using stormline::core::math::RuntimeHandle;
using stormline::core::math::valid;

int failures = 0;

void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}

void begin_case() {
    failures = 0;
}

bool finish_case() {
    return failures == 0;
}

bool run_math10() {
    begin_case();

    expect(!valid(PersistentId{}), "zero persistent ID invalid");
    expect(valid(PersistentId{1, 0}), "high-half persistent ID valid");
    expect(valid(PersistentId{0, 1}), "low-half persistent ID valid");
    expect(PersistentId{1, 2} == PersistentId{1, 2}, "persistent ID equality");
    expect(!(PersistentId{1, 2} == PersistentId{2, 1}), "persistent ID inequality");

    const PersistentId fixture{
        0x0102030405060708ULL,
        0x1112131415161718ULL,
    };
    const IdBytes encoded = encode_persistent_id(fixture);
    const std::uint8_t expected[16] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    };
    bool bytes_match = true;
    for (std::size_t index = 0; index < 16; ++index) {
        bytes_match = bytes_match && encoded.bytes[index] == expected[index];
    }
    expect(bytes_match, "persistent ID big-endian bytes");

    const auto decoded = decode_persistent_id(encoded);
    expect(decoded.ok() && decoded.value == fixture, "persistent ID round-trip");

    const PersistentId maximum{
        0xffffffffffffffffULL,
        0xffffffffffffffffULL,
    };
    const auto maximum_decoded = decode_persistent_id(encode_persistent_id(maximum));
    expect(maximum_decoded.ok() && maximum_decoded.value == maximum,
           "persistent ID maximum round-trip");

    const auto zero_decoded = decode_persistent_id(IdBytes{});
    expect(!zero_decoded.ok() && zero_decoded.error == MathError::InvalidId,
           "zero bytes invalid ID");

    return finish_case();
}

bool run_math11() {
    begin_case();

    expect(!valid(RuntimeHandle{}), "zero runtime handle invalid");
    expect(!valid(RuntimeHandle{0, 1}), "zero index invalid");
    expect(!valid(RuntimeHandle{1, 0}), "zero generation invalid");
    expect(valid(RuntimeHandle{1, 1}), "valid runtime handle");

    const RuntimeHandle current{7, 12};
    expect(handle_is_current(current, 12), "current generation accepted");
    expect(!handle_is_current(current, 11), "old generation rejected");
    expect(!handle_is_current(current, 13), "future generation rejected");
    expect(!handle_is_current(RuntimeHandle{}, 12), "invalid handle rejected");

    const RuntimeHandle old_handle{7, 12};
    const RuntimeHandle recycled{7, 13};
    expect(old_handle == old_handle, "handle equality");
    expect(!(old_handle == recycled), "recycled handle differs");
    expect(!handle_is_current(old_handle, recycled.generation),
           "old handle cannot alias recycled slot");

    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core05_id_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "math10") {
        success = run_math10();
    } else if (mode == "math11") {
        success = run_math11();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
