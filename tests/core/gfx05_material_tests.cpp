#include "stormline/graphics/material/pbr_material.hpp"

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

[[nodiscard]] MaterialDesc sample(u32 id, u32 revision = 1) {
    MaterialDesc value{};
    value.id = id;
    value.revision = revision;
    return value;
}

bool run_pbr01() {
    begin();
    MaterialSet set{};
    MaterialDiagnostic diagnostic{};

    expect(add_material(set, sample(10)) == MaterialError::None, "add");
    expect(set.count == 1, "count");
    expect(validate_materials(set, diagnostic) == MaterialError::None, "valid");
    expect(diagnostic.code == MaterialError::None, "diagnostic reset");

    expect(add_material(set, sample(10)) == MaterialError::DuplicateId, "duplicate");
    expect(set.count == 1, "duplicate atomic");
    expect(add_material(set, sample(0)) == MaterialError::InvalidArgument, "zero id");
    expect(add_material(set, sample(11, 0)) == MaterialError::InvalidArgument,
           "zero revision");

    MaterialDesc unlit = sample(11);
    unlit.model = MaterialModel::Unlit;
    expect(add_material(set, unlit) == MaterialError::None, "unlit");

    MaterialDesc blend = sample(12);
    blend.parameters.alpha = AlphaMode::Blend;
    expect(add_material(set, blend) == MaterialError::None, "blend");

    MaterialDesc mask = sample(13);
    mask.parameters.alpha = AlphaMode::Mask;
    mask.parameters.alpha_cutoff = 0.25f;
    expect(add_material(set, mask) == MaterialError::None, "mask");

    MaterialDesc mask_zero = sample(14);
    mask_zero.parameters.alpha = AlphaMode::Mask;
    mask_zero.parameters.alpha_cutoff = 0.0f;
    expect(add_material(set, mask_zero) == MaterialError::OutOfRange, "mask cutoff");
    expect(set.count == 4, "mask atomic");

    MaterialDesc invalid_model = sample(15);
    invalid_model.model = static_cast<MaterialModel>(200);
    expect(add_material(set, invalid_model) == MaterialError::InvalidArgument,
           "model");

    MaterialDesc invalid_alpha = sample(16);
    invalid_alpha.parameters.alpha = static_cast<AlphaMode>(200);
    expect(add_material(set, invalid_alpha) == MaterialError::InvalidAlphaMode,
           "alpha");

    MaterialDesc non_finite = sample(17);
    non_finite.parameters.base_color[1] =
        std::numeric_limits<f32>::quiet_NaN();
    expect(add_material(set, non_finite) == MaterialError::NonFiniteParameter,
           "nan color");

    non_finite = sample(18);
    non_finite.parameters.emissive[2] =
        std::numeric_limits<f32>::infinity();
    expect(add_material(set, non_finite) == MaterialError::NonFiniteParameter,
           "inf emissive");

    MaterialDesc out_of_range = sample(19);
    out_of_range.parameters.base_color[0] = -0.1f;
    expect(add_material(set, out_of_range) == MaterialError::OutOfRange,
           "color range");

    out_of_range = sample(20);
    out_of_range.parameters.metallic = 1.1f;
    expect(add_material(set, out_of_range) == MaterialError::OutOfRange,
           "metallic range");

    out_of_range = sample(21);
    out_of_range.parameters.roughness = -0.1f;
    expect(add_material(set, out_of_range) == MaterialError::OutOfRange,
           "roughness range");

    out_of_range = sample(22);
    out_of_range.parameters.occlusion = 2.0f;
    expect(add_material(set, out_of_range) == MaterialError::OutOfRange,
           "occlusion range");

    out_of_range = sample(23);
    out_of_range.parameters.normal_scale = 0.0f;
    expect(add_material(set, out_of_range) == MaterialError::OutOfRange,
           "normal scale zero");

    out_of_range = sample(24);
    out_of_range.parameters.alpha_cutoff = 1.1f;
    expect(add_material(set, out_of_range) == MaterialError::OutOfRange,
           "cutoff range");

    while (set.count < kMaxMaterials) {
        expect(add_material(set, sample(100 + set.count)) == MaterialError::None,
               "fill");
    }
    expect(add_material(set, sample(999)) == MaterialError::CapacityFull,
           "capacity");
    expect(set.count == kMaxMaterials, "capacity count");

    MaterialSet duplicate_set{};
    duplicate_set.count = 2;
    duplicate_set.materials[0] = sample(1);
    duplicate_set.materials[1] = sample(1);
    expect(validate_materials(duplicate_set, diagnostic)
               == MaterialError::DuplicateId,
           "manual duplicate");
    expect(diagnostic.code == MaterialError::DuplicateId, "duplicate diagnostic");
    expect(diagnostic.material_id == 1 && diagnostic.index == 1,
           "duplicate position");

    MaterialSet overflow{};
    overflow.count = kMaxMaterials + 1;
    expect(validate_materials(overflow, diagnostic)
               == MaterialError::InvalidArgument,
           "overflow");

    MaterialSet invalid_manual{};
    invalid_manual.count = 1;
    invalid_manual.materials[0] = sample(30);
    invalid_manual.materials[0].parameters.base_color[2] = 3.0f;
    expect(validate_materials(invalid_manual, diagnostic)
               == MaterialError::OutOfRange,
           "manual range");
    expect(diagnostic.material_id == 30 && diagnostic.index == 0,
           "range position");

    expect(std::string_view(material_error_name(MaterialError::None)) == "None",
           "error none");
    expect(std::string_view(material_error_name(MaterialError::DuplicateId))
               == "DuplicateId",
           "error duplicate");
    expect(std::string_view(material_error_name(
               static_cast<MaterialError>(200))) == "Unknown",
           "error unknown");
    return finish();
}
}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_gfx05_material_test <mode>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "pbr01") { success = run_pbr01(); }
    else { std::fprintf(stderr, "unknown mode: %s\n", argv[1]); return 2; }
    return success ? 0 : 1;
}
