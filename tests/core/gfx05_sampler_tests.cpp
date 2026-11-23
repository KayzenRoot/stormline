#include "stormline/graphics/material/texture_sampler.hpp"

#include <cstdio>
#include <limits>
#include <string_view>

namespace {
using namespace stormline::graphics::material;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

bool run_smp01() {
    begin();
    SamplerProfile sampler{};
    MaterialDiagnostic diagnostic{};

    expect(validate_sampler(sampler, diagnostic) == MaterialError::None,
           "default valid");
    expect(diagnostic.code == MaterialError::None, "diagnostic reset");

    sampler = SamplerProfile{};
    sampler.min_filter = FilterMode::Nearest;
    sampler.mag_filter = FilterMode::Nearest;
    sampler.mip_filter = FilterMode::Nearest;
    sampler.wrap_u = WrapMode::Clamp;
    sampler.wrap_v = WrapMode::Mirror;
    sampler.lod_bias = -16.0f;
    sampler.lod_min = -16.0f;
    sampler.lod_max = 16.0f;
    sampler.max_anisotropy = 16;
    expect(validate_sampler(sampler, diagnostic) == MaterialError::None,
           "bounds valid");

    sampler = SamplerProfile{};
    sampler.format = static_cast<TextureFormat>(200);
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "format enum");
    sampler = SamplerProfile{};
    sampler.min_filter = static_cast<FilterMode>(200);
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "min filter");
    sampler = SamplerProfile{};
    sampler.mag_filter = static_cast<FilterMode>(200);
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "mag filter");
    sampler = SamplerProfile{};
    sampler.mip_filter = static_cast<FilterMode>(200);
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "mip filter");
    sampler = SamplerProfile{};
    sampler.wrap_u = static_cast<WrapMode>(200);
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "wrap u");
    sampler = SamplerProfile{};
    sampler.wrap_v = static_cast<WrapMode>(200);
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "wrap v");

    sampler = SamplerProfile{};
    sampler.lod_bias = std::numeric_limits<f32>::quiet_NaN();
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "lod bias nan");
    sampler = SamplerProfile{};
    sampler.lod_min = std::numeric_limits<f32>::infinity();
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "lod min inf");
    sampler = SamplerProfile{};
    sampler.lod_max = -17.0f;
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "lod max range");
    sampler = SamplerProfile{};
    sampler.lod_min = 5.0f;
    sampler.lod_max = 4.0f;
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "lod order");

    sampler = SamplerProfile{};
    sampler.max_anisotropy = 0;
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "anisotropy zero");
    sampler = SamplerProfile{};
    sampler.max_anisotropy = 3;
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "anisotropy power");
    sampler = SamplerProfile{};
    sampler.max_anisotropy = 17;
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "anisotropy range");

    sampler = SamplerProfile{};
    sampler.compare = true;
    expect(validate_sampler(sampler, diagnostic)
               == MaterialError::InvalidSampler,
           "compare color");
    sampler = SamplerProfile{};
    sampler.compare = true;
    sampler.format = TextureFormat::Depth32Float;
    expect(validate_sampler(sampler, diagnostic) == MaterialError::None,
           "compare depth");
    expect(diagnostic.code == MaterialError::None, "compare diagnostic reset");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx05_sampler_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "smp01") { success = run_smp01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
