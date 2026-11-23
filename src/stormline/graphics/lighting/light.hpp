#ifndef STORMLINE_GRAPHICS_LIGHTING_LIGHT_HPP
#define STORMLINE_GRAPHICS_LIGHTING_LIGHT_HPP

#include "stormline/graphics/lighting/lighting_types.hpp"

#include <cmath>

namespace stormline::graphics::lighting {

namespace detail {

inline LightingError set_light_error(
    LightingDiagnostic& diagnostic, LightingError code, u32 light_id,
    u32 index) noexcept {
    diagnostic = LightingDiagnostic{code, light_id, 0, index};
    return code;
}

inline bool finite(f32 value) noexcept {
    return std::isfinite(value);
}

inline bool finite_vec(const Vec3& value) noexcept {
    return finite(value.x) && finite(value.y) && finite(value.z);
}

inline bool valid_kind(LightKind kind) noexcept {
    switch (kind) {
        case LightKind::Directional:
        case LightKind::Point:
        case LightKind::Spot:
        case LightKind::AreaRect:
        case LightKind::Environment:
        case LightKind::Stylized2D:
            return true;
    }
    return false;
}

inline bool valid_unit(LightUnit unit) noexcept {
    switch (unit) {
        case LightUnit::Lux:
        case LightUnit::Candela:
        case LightUnit::Luminance:
            return true;
    }
    return false;
}

inline bool valid_shadow(ShadowMode shadow) noexcept {
    switch (shadow) {
        case ShadowMode::Disabled:
        case ShadowMode::Cascaded:
        case ShadowMode::Local:
            return true;
    }
    return false;
}

inline LightUnit unit_for_kind(LightKind kind) noexcept {
    switch (kind) {
        case LightKind::Directional:
            return LightUnit::Lux;
        case LightKind::Point:
        case LightKind::Spot:
            return LightUnit::Candela;
        case LightKind::AreaRect:
        case LightKind::Environment:
        case LightKind::Stylized2D:
            return LightUnit::Luminance;
    }
    return LightUnit::Lux;
}

inline bool shadow_matches(LightKind kind, ShadowMode shadow) noexcept {
    if (shadow == ShadowMode::Disabled) {
        return true;
    }
    if (kind == LightKind::Directional) {
        return shadow == ShadowMode::Cascaded;
    }
    if (kind == LightKind::Point || kind == LightKind::Spot) {
        return shadow == ShadowMode::Local;
    }
    return false;
}

inline u32 find_light(const LightSet& set, u32 id) noexcept {
    for (u32 index = 0; index < set.count; ++index) {
        if (set.lights[index].id == id) {
            return index;
        }
    }
    return kMaxLights;
}

inline LightingError validate_light(const LightDesc& light) noexcept {
    if (light.id == 0 || light.revision == 0) {
        return LightingError::InvalidArgument;
    }
    if (!valid_kind(light.kind)) {
        return LightingError::InvalidLightKind;
    }
    if (!valid_unit(light.unit)) {
        return LightingError::InvalidUnit;
    }
    if (light.unit != unit_for_kind(light.kind)) {
        return LightingError::InvalidUnit;
    }
    if (!valid_shadow(light.shadow)) {
        return LightingError::InvalidArgument;
    }
    if (!finite_vec(light.color) || !finite(light.intensity)
        || !finite_vec(light.position) || !finite_vec(light.direction)
        || !finite(light.range) || !finite(light.inner_angle)
        || !finite(light.outer_angle) || !finite(light.width)
        || !finite(light.height)) {
        return LightingError::NonFiniteValue;
    }
    if (light.color.x < 0.0f || light.color.y < 0.0f
        || light.color.z < 0.0f || light.intensity < 0.0f) {
        return LightingError::OutOfRange;
    }
    const f32 length_squared =
        light.direction.x * light.direction.x
        + light.direction.y * light.direction.y
        + light.direction.z * light.direction.z;
    if (!(length_squared > 1.0e-12f)) {
        return LightingError::InvalidArgument;
    }
    if (!shadow_matches(light.kind, light.shadow)) {
        return LightingError::InvalidArgument;
    }
    switch (light.kind) {
        case LightKind::Directional:
            break;
        case LightKind::Point:
            if (!(light.range > 0.0f)) {
                return LightingError::OutOfRange;
            }
            break;
        case LightKind::Spot:
            if (!(light.range > 0.0f)) {
                return LightingError::OutOfRange;
            }
            if (!(light.outer_angle > 0.0f) || light.outer_angle > kPi * 0.5f
                || light.inner_angle < 0.0f
                || light.inner_angle > light.outer_angle) {
                return LightingError::OutOfRange;
            }
            break;
        case LightKind::AreaRect:
            if (!(light.width > 0.0f) || !(light.height > 0.0f)) {
                return LightingError::OutOfRange;
            }
            break;
        case LightKind::Environment:
            break;
        case LightKind::Stylized2D:
            if (!(light.range > 0.0f)) {
                return LightingError::OutOfRange;
            }
            break;
    }
    return LightingError::None;
}

}  // namespace detail

[[nodiscard]] inline const char* lighting_error_name(
    LightingError error) noexcept {
    switch (error) {
        case LightingError::None: return "None";
        case LightingError::InvalidArgument: return "InvalidArgument";
        case LightingError::DuplicateId: return "DuplicateId";
        case LightingError::NotFound: return "NotFound";
        case LightingError::CapacityFull: return "CapacityFull";
        case LightingError::NonFiniteValue: return "NonFiniteValue";
        case LightingError::OutOfRange: return "OutOfRange";
        case LightingError::InvalidLightKind: return "InvalidLightKind";
        case LightingError::InvalidUnit: return "InvalidUnit";
        case LightingError::InvalidCascade: return "InvalidCascade";
        case LightingError::ShadowPageMissing: return "ShadowPageMissing";
        case LightingError::ShadowBudgetExceeded: return "ShadowBudgetExceeded";
        case LightingError::GiUnavailable: return "GiUnavailable";
        case LightingError::InvalidProbe: return "InvalidProbe";
        case LightingError::HistoryInvalid: return "HistoryInvalid";
        case LightingError::ReflectionOffscreen: return "ReflectionOffscreen";
        case LightingError::VolumetricBudgetExceeded:
            return "VolumetricBudgetExceeded";
        case LightingError::Unsupported: return "Unsupported";
    }
    return "Unknown";
}

[[nodiscard]] inline LightingError add_light(
    LightSet& set, const LightDesc& light) noexcept {
    if (set.count >= kMaxLights) {
        return LightingError::CapacityFull;
    }
    const LightingError validation = detail::validate_light(light);
    if (validation != LightingError::None) {
        return validation;
    }
    if (detail::find_light(set, light.id) != kMaxLights) {
        return LightingError::DuplicateId;
    }
    set.lights[set.count] = light;
    ++set.count;
    return LightingError::None;
}

[[nodiscard]] inline LightingError validate_lights(
    const LightSet& set, LightingDiagnostic& diagnostic) noexcept {
    diagnostic = LightingDiagnostic{};
    if (set.count > kMaxLights) {
        return detail::set_light_error(
            diagnostic, LightingError::InvalidArgument, 0, 0);
    }
    for (u32 index = 0; index < set.count; ++index) {
        const LightDesc& light = set.lights[index];
        const LightingError validation = detail::validate_light(light);
        if (validation != LightingError::None) {
            return detail::set_light_error(
                diagnostic, validation, light.id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (set.lights[previous].id == light.id) {
                return detail::set_light_error(
                    diagnostic, LightingError::DuplicateId, light.id, index);
            }
        }
    }
    return LightingError::None;
}

}  // namespace stormline::graphics::lighting

#endif  // STORMLINE_GRAPHICS_LIGHTING_LIGHT_HPP
