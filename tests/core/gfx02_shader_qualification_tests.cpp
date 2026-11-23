#include "stormline/graphics/shader/shader_cache.hpp"
#include "stormline/graphics/shader/shader_incremental.hpp"
#include "stormline/graphics/shader/shader_reflection.hpp"
#include "stormline/graphics/shader/shader_variant.hpp"

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

constexpr std::string_view kSource =
    "shader Q { stage fragment;"
    "input vec2 uv; output vec4 color;"
    "uniform vec4 tint; uniform mat4 view; }";

[[nodiscard]] bool prepare(ShaderIr& ir, ShaderReflection& reflection,
                           SourcePath& path) {
    if (make_source_path("qualification.sscl", path) != ShaderError::None) {
        return false;
    }
    Diagnostic diagnostic{};
    return compile_shader(path, kSource, ir, diagnostic) == ShaderError::None
        && reflect_shader(ir, reflection) == ShaderError::None;
}

bool run_qlf_s01() {
    begin();
    ShaderIr ir{};
    ShaderReflection reflection{};
    SourcePath path{};
    expect(prepare(ir, reflection, path), "prepare");
    expect(ir.binding_count == 4 && reflection.binding_count == 4, "counts");
    expect(reflection.bindings[0].slot == 0
               && reflection.bindings[1].slot == 0
               && reflection.bindings[2].slot == 0
               && reflection.bindings[3].slot == 1,
           "slots");

    VariantPlan variants{};
    expect(plan_variants(ir, VariantRequest{4, 2, 4}, variants) == ShaderError::None,
           "variants");
    expect(variants.count == 4, "variant count");

    CacheKey key{};
    expect(make_cache_key(variants.keys[0], 11, key) == ShaderError::None, "cache key");
    ShaderCache cache;
    expect(cache.put(key, reflection.source_fingerprint) == ShaderError::None, "put");
    u64 payload = 0;
    expect(cache.get(key, payload) == ShaderError::None
               && payload == reflection.source_fingerprint,
           "get");

    DependencySet dependencies{};
    dependencies.count = 2;
    dependencies.dependencies[0] = DependencyRef{1, 10};
    dependencies.dependencies[1] = DependencyRef{2, 20};
    u64 fingerprint = 0;
    expect(dependency_fingerprint(dependencies, fingerprint) == ShaderError::None,
           "dependencies");
    bool rebuild = false;
    u64 planned = 0;
    expect(plan_incremental(dependencies, IncrementalState{fingerprint, key.value},
                            rebuild, planned) == ShaderError::None,
           "incremental");
    expect(!rebuild && planned == fingerprint, "incremental stable");
    return finish();
}

struct Snapshot {
    u64 source{0};
    u32 bindings{0};
    u32 reflection_bindings{0};
    u32 variant_count{0};
    u64 cache_key{0};
    u64 dependency_fingerprint{0};
};

[[nodiscard]] bool snapshot(Snapshot& out) {
    ShaderIr ir{};
    ShaderReflection reflection{};
    SourcePath path{};
    if (!prepare(ir, reflection, path)) {
        return false;
    }
    VariantPlan variants{};
    if (plan_variants(ir, VariantRequest{7, 2, 4}, variants) != ShaderError::None) {
        return false;
    }
    CacheKey key{};
    if (make_cache_key(variants.keys[2], 5, key) != ShaderError::None) {
        return false;
    }
    DependencySet dependencies{};
    dependencies.count = 2;
    dependencies.dependencies[0] = DependencyRef{2, 20};
    dependencies.dependencies[1] = DependencyRef{1, 10};
    u64 dependency = 0;
    if (dependency_fingerprint(dependencies, dependency) != ShaderError::None) {
        return false;
    }
    out.source = ir.source_fingerprint;
    out.bindings = ir.binding_count;
    out.reflection_bindings = reflection.binding_count;
    out.variant_count = variants.count;
    out.cache_key = key.value;
    out.dependency_fingerprint = dependency;
    return true;
}

bool run_qlf_s02() {
    begin();
    Snapshot first{};
    Snapshot second{};
    expect(snapshot(first), "first snapshot");
    expect(snapshot(second), "second snapshot");
    expect(first.source == second.source, "source repeat");
    expect(first.bindings == second.bindings, "bindings repeat");
    expect(first.reflection_bindings == second.reflection_bindings,
           "reflection repeat");
    expect(first.variant_count == second.variant_count, "variants repeat");
    expect(first.cache_key == second.cache_key, "cache repeat");
    expect(first.dependency_fingerprint == second.dependency_fingerprint,
           "dependency repeat");
    return finish();
}

bool run_qlf_s03() {
    begin();
    SourcePath path{};
    expect(make_source_path("recovery.sscl", path) == ShaderError::None, "path");
    ShaderIr ir{};
    Diagnostic diagnostic{};

    expect(compile_shader(path, "", ir, diagnostic) == ShaderError::EmptySource,
           "empty");
    expect(compile_shader(path, kSource, ir, diagnostic) == ShaderError::None,
           "after empty");
    expect(compile_shader(path, "shader X { @ }", ir, diagnostic)
               == ShaderError::InvalidToken,
           "token");
    expect(compile_shader(path, kSource, ir, diagnostic) == ShaderError::None,
           "after token");

    ShaderReflection reflection{};
    ShaderIr invalid = ir;
    invalid.binding_count = kMaxBindings + 1;
    expect(reflect_shader(invalid, reflection) == ShaderError::InvalidArgument,
           "reflection");
    expect(reflect_shader(ir, reflection) == ShaderError::None, "after reflection");

    VariantPlan variants{};
    expect(plan_variants(ir, VariantRequest{0, 1, 2}, variants)
               == ShaderError::InvalidArgument,
           "variant recipe");
    expect(plan_variants(ir, VariantRequest{1, 1, 2}, variants) == ShaderError::None,
           "after variant recipe");
    expect(plan_variants(ir, VariantRequest{1, 7, 64}, variants)
               == ShaderError::VariantLimit,
           "variant limit");
    expect(plan_variants(ir, VariantRequest{1, 1, 2}, variants) == ShaderError::None,
           "after variant limit");

    ShaderCache cache;
    CacheKey key{};
    expect(make_cache_key(variants.keys[0], 1, key) == ShaderError::None, "key");
    expect(cache.put(key, 1) == ShaderError::None, "cache put");
    expect(cache.put(key, 2) == ShaderError::CacheMismatch, "cache mismatch");
    u64 payload = 0;
    expect(cache.get(key, payload) == ShaderError::None && payload == 1,
           "after mismatch");
    cache.clear();
    for (u32 index = 0; index < kMaxCacheEntries; ++index) {
        expect(cache.put(CacheKey{static_cast<u64>(index + 10)},
                         static_cast<u64>(index + 20)) == ShaderError::None,
               "cache fill");
    }
    expect(cache.put(CacheKey{9999}, 9999) == ShaderError::CacheFull, "cache full");
    cache.clear();
    expect(cache.put(key, 1) == ShaderError::None, "after cache full");

    DependencySet dependencies{};
    dependencies.count = 2;
    dependencies.dependencies[0] = DependencyRef{1, 1};
    dependencies.dependencies[1] = DependencyRef{1, 2};
    u64 fingerprint = 0;
    expect(dependency_fingerprint(dependencies, fingerprint)
               == ShaderError::InvalidArgument,
           "dependency");
    dependencies.dependencies[1].id = 2;
    expect(dependency_fingerprint(dependencies, fingerprint) == ShaderError::None,
           "after dependency");
    bool rebuild = false;
    u64 planned = 0;
    dependencies.count = 0;
    expect(plan_incremental(dependencies, IncrementalState{}, rebuild, planned)
               == ShaderError::InvalidArgument,
           "incremental");
    dependencies.count = 1;
    expect(plan_incremental(dependencies, IncrementalState{}, rebuild, planned)
               == ShaderError::None,
           "after incremental");
    return finish();
}

bool run_qlf_s04() {
    begin();
    SourcePath path{};
    expect(make_source_path("overload.sscl", path) == ShaderError::None, "path");
    ShaderIr ir{};
    Diagnostic diagnostic{};
    ShaderReflection reflection{};
    for (u32 index = 0; index < 10000; ++index) {
        expect(compile_shader(path, kSource, ir, diagnostic) == ShaderError::None,
               "bounded compile");
        expect(compile_shader(path, "", ir, diagnostic) == ShaderError::EmptySource,
               "bounded reject");
    }
    expect(compile_shader(path, kSource, ir, diagnostic) == ShaderError::None,
           "final compile");
    for (u32 index = 0; index < 10000; ++index) {
        expect(reflect_shader(ir, reflection) == ShaderError::None,
               "bounded reflection");
    }
    VariantPlan variants{};
    for (u32 index = 0; index < 10000; ++index) {
        expect(plan_variants(ir, VariantRequest{1, 1, 2}, variants)
                   == ShaderError::None,
               "bounded variants");
    }
    CacheKey key{};
    expect(make_cache_key(variants.keys[0], 1, key) == ShaderError::None, "key");
    ShaderCache cache;
    for (u32 index = 0; index < 10000; ++index) {
        expect(cache.put(key, 1) == ShaderError::None, "bounded cache");
    }
    expect(cache.size() == 1, "bounded cache size");
    DependencySet dependencies{};
    dependencies.count = kMaxDependencies;
    for (u32 index = 0; index < kMaxDependencies; ++index) {
        dependencies.dependencies[index] = DependencyRef{index + 1, index + 10};
    }
    u64 fingerprint = 0;
    bool rebuild = false;
    for (u32 index = 0; index < 10000; ++index) {
        expect(plan_incremental(dependencies, IncrementalState{}, rebuild, fingerprint)
                   == ShaderError::None,
               "bounded incremental");
        expect(rebuild, "bounded rebuild");
    }
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx02_shader_qualification_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") { success = run_qlf_s01(); }
    else if (mode == "qlf02") { success = run_qlf_s02(); }
    else if (mode == "qlf03") { success = run_qlf_s03(); }
    else if (mode == "qlf04") { success = run_qlf_s04(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
