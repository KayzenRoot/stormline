#include "stormline/graphics/shader/shader_cache.hpp"

#include <cstdio>
#include <string_view>

namespace {
using namespace stormline::graphics::shader;

int failures = 0;
void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}
void begin() { failures = 0; }
bool finish() { return failures == 0; }

[[nodiscard]] ShaderIr parsed(std::string_view source, bool& ok) {
    SourcePath path{};
    ok = make_source_path("cache.sscl", path) == ShaderError::None;
    ShaderIr ir{};
    Diagnostic diagnostic{};
    ok = ok && compile_shader(path, source, ir, diagnostic) == ShaderError::None;
    return ir;
}

bool run_cac01() {
    begin();
    bool ok = false;
    ShaderIr ir = parsed("shader C { stage vertex; uniform vec4 color; }", ok);
    expect(ok, "parse");
    VariantPlan variants{};
    expect(plan_variants(ir, VariantRequest{1, 1, 2}, variants) == ShaderError::None,
           "variants");

    CacheKey key{};
    expect(make_cache_key(variants.keys[0], 7, key) == ShaderError::None, "key");
    expect(key.value != 0, "key nonzero");
    CacheKey repeat{};
    expect(make_cache_key(variants.keys[0], 7, repeat) == ShaderError::None
               && repeat.value == key.value,
           "key deterministic");
    CacheKey different_dependency{};
    expect(make_cache_key(variants.keys[0], 8, different_dependency) == ShaderError::None
               && different_dependency.value != key.value,
           "dependency changes key");
    CacheKey different_variant{};
    expect(make_cache_key(variants.keys[1], 7, different_variant) == ShaderError::None
               && different_variant.value != key.value,
           "variant changes key");

    ShaderCache cache;
    expect(cache.size() == 0, "empty");
    u64 payload = 0;
    expect(cache.get(key, payload) == ShaderError::CacheMiss && payload == 0, "miss");
    expect(cache.put(key, 42) == ShaderError::None, "put");
    expect(cache.size() == 1, "put size");
    expect(cache.get(key, payload) == ShaderError::None && payload == 42, "get");
    expect(cache.put(key, 42) == ShaderError::None && cache.size() == 1,
           "idempotent");
    expect(cache.put(key, 43) == ShaderError::CacheMismatch && cache.size() == 1,
           "mismatch");
    expect(cache.put(CacheKey{0}, 1) == ShaderError::InvalidArgument, "zero key");
    expect(cache.put(CacheKey{99}, 0) == ShaderError::InvalidArgument, "zero payload");
    expect(cache.get(CacheKey{0}, payload) == ShaderError::InvalidArgument,
           "zero get");

    ShaderCache full;
    for (u32 index = 0; index < kMaxCacheEntries; ++index) {
        expect(full.put(CacheKey{static_cast<u64>(index + 1)},
                        static_cast<u64>(index + 10)) == ShaderError::None,
               "fill");
    }
    expect(full.size() == kMaxCacheEntries, "full size");
    expect(full.put(CacheKey{999}, 999) == ShaderError::CacheFull, "full");
    full.clear();
    expect(full.size() == 0, "clear size");
    expect(full.get(CacheKey{1}, payload) == ShaderError::CacheMiss, "clear miss");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx02_cache_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "cac01") { success = run_cac01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
