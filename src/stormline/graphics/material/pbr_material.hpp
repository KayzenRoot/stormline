#ifndef STORMLINE_GRAPHICS_MATERIAL_PBR_MATERIAL_HPP
#define STORMLINE_GRAPHICS_MATERIAL_PBR_MATERIAL_HPP

#include "stormline/graphics/material/material_types.hpp"

#include <cmath>

namespace stormline::graphics::material {

namespace detail {

inline MaterialError set_error(
    MaterialDiagnostic& diagnostic, MaterialError code, u32 material_id,
    u32 index) noexcept {
    diagnostic = MaterialDiagnostic{code, material_id, 0, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return std::isfinite(value);
}

inline bool in_unit_range(f32 value) noexcept {
    return finite(value) && value >= 0.0f && value <= 1.0f;
}

inline bool valid_color(const std::array<f32, 3>& color) noexcept {
    return in_unit_range(color[0]) && in_unit_range(color[1])
        && in_unit_range(color[2]);
}

inline bool valid_model(MaterialModel model) noexcept {
    switch (model) {
        case MaterialModel::PbrMetallicRoughness:
        case MaterialModel::Unlit:
        case MaterialModel::Stylized:
            return true;
    }
    return false;
}

inline bool valid_alpha_mode(AlphaMode alpha) noexcept {
    switch (alpha) {
        case AlphaMode::Opaque:
        case AlphaMode::Mask:
        case AlphaMode::Blend:
        case AlphaMode::Transmission:
            return true;
    }
    return false;
}

inline MaterialError validate_parameters(
    const PbrParameters& parameters) noexcept {
    if (!finite(parameters.metallic) || !finite(parameters.roughness)
        || !finite(parameters.occlusion) || !finite(parameters.emissive[0])
        || !finite(parameters.emissive[1]) || !finite(parameters.emissive[2])
        || !finite(parameters.base_color[0]) || !finite(parameters.base_color[1])
        || !finite(parameters.base_color[2]) || !finite(parameters.normal_scale)
        || !finite(parameters.alpha_cutoff)) {
        return MaterialError::NonFiniteParameter;
    }
    if (!valid_color(parameters.base_color)
        || !in_unit_range(parameters.metallic)
        || !in_unit_range(parameters.roughness)
        || !in_unit_range(parameters.occlusion)
        || !in_unit_range(parameters.emissive[0])
        || !in_unit_range(parameters.emissive[1])
        || !in_unit_range(parameters.emissive[2])
        || !in_unit_range(parameters.alpha_cutoff)) {
        return MaterialError::OutOfRange;
    }
    if (!(parameters.normal_scale > 0.0f)) {
        return MaterialError::OutOfRange;
    }
    if (!valid_alpha_mode(parameters.alpha)) {
        return MaterialError::InvalidAlphaMode;
    }
    if (parameters.alpha == AlphaMode::Mask && parameters.alpha_cutoff <= 0.0f) {
        return MaterialError::OutOfRange;
    }
    return MaterialError::None;
}

inline u32 find_material(const MaterialSet& set, u32 id) noexcept {
    for (u32 index = 0; index < set.count; ++index) {
        if (set.materials[index].id == id) {
            return index;
        }
    }
    return kMaxMaterials;
}

}  // namespace detail

[[nodiscard]] inline const char* material_error_name(
    MaterialError error) noexcept {
    switch (error) {
        case MaterialError::None: return "None";
        case MaterialError::InvalidArgument: return "InvalidArgument";
        case MaterialError::DuplicateId: return "DuplicateId";
        case MaterialError::NotFound: return "NotFound";
        case MaterialError::CapacityFull: return "CapacityFull";
        case MaterialError::NonFiniteParameter: return "NonFiniteParameter";
        case MaterialError::OutOfRange: return "OutOfRange";
        case MaterialError::InvalidMipChain: return "InvalidMipChain";
        case MaterialError::InvalidSampler: return "InvalidSampler";
        case MaterialError::InvalidAlphaMode: return "InvalidAlphaMode";
        case MaterialError::DecalConflict: return "DecalConflict";
        case MaterialError::TransparencyBudgetExceeded:
            return "TransparencyBudgetExceeded";
        case MaterialError::StaleGeneration: return "StaleGeneration";
    }
    return "Unknown";
}

[[nodiscard]] inline MaterialError add_material(
    MaterialSet& set, const MaterialDesc& material) noexcept {
    if (set.count >= kMaxMaterials) {
        return MaterialError::CapacityFull;
    }
    if (material.id == 0 || material.revision == 0) {
        return MaterialError::InvalidArgument;
    }
    if (!detail::valid_model(material.model)) {
        return MaterialError::InvalidArgument;
    }
    if (detail::find_material(set, material.id) != kMaxMaterials) {
        return MaterialError::DuplicateId;
    }
    const MaterialError parameter_error =
        detail::validate_parameters(material.parameters);
    if (parameter_error != MaterialError::None) {
        return parameter_error;
    }
    set.materials[set.count] = material;
    ++set.count;
    return MaterialError::None;
}

[[nodiscard]] inline MaterialError validate_materials(
    const MaterialSet& set, MaterialDiagnostic& diagnostic) noexcept {
    diagnostic = MaterialDiagnostic{};
    if (set.count > kMaxMaterials) {
        return detail::set_error(
            diagnostic, MaterialError::InvalidArgument, 0, 0);
    }
    for (u32 index = 0; index < set.count; ++index) {
        const MaterialDesc& material = set.materials[index];
        if (material.id == 0 || material.revision == 0) {
            return detail::set_error(
                diagnostic, MaterialError::InvalidArgument, material.id, index);
        }
        if (!detail::valid_model(material.model)) {
            return detail::set_error(
                diagnostic, MaterialError::InvalidArgument, material.id, index);
        }
        const MaterialError parameter_error =
            detail::validate_parameters(material.parameters);
        if (parameter_error != MaterialError::None) {
            return detail::set_error(
                diagnostic, parameter_error, material.id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (set.materials[previous].id == material.id) {
                return detail::set_error(
                    diagnostic, MaterialError::DuplicateId, material.id, index);
            }
        }
    }
    return MaterialError::None;
}

}  // namespace stormline::graphics::material

#endif  // STORMLINE_GRAPHICS_MATERIAL_PBR_MATERIAL_HPP
