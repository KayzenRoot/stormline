#ifndef STORMLINE_GRAPHICS_LIGHTING_PROBE_PLAN_HPP
#define STORMLINE_GRAPHICS_LIGHTING_PROBE_PLAN_HPP

#include "stormline/graphics/lighting/light.hpp"

#include <algorithm>

namespace stormline::graphics::lighting {

struct ProbeVolumeDesc {
    u32 id{0};
    u32 revision{0};
    u64 scene_generation{0};
    Vec3 origin{};
    f32 spacing{0.0f};
    u32 cells_x{0};
    u32 cells_y{0};
    u32 cells_z{0};
};

struct ProbeVolumeSet {
    u32 count{0};
    std::array<ProbeVolumeDesc, kMaxProbes> probes{};
};

struct ProbePlan {
    u32 count{0};
    std::array<u32, kMaxProbes> probe_ids{};
};

[[nodiscard]] inline LightingError plan_probes(
    const ProbeVolumeSet& probes, u64 expected_generation,
    ProbePlan& plan, LightingDiagnostic& diagnostic) noexcept {
    plan = ProbePlan{};
    diagnostic = LightingDiagnostic{};
    if (probes.count > kMaxProbes) {
        return detail::set_light_error(
            diagnostic, LightingError::InvalidArgument, 0, 0);
    }
    std::array<u32, kMaxProbes> ids{};
    for (u32 index = 0; index < probes.count; ++index) {
        const ProbeVolumeDesc& probe = probes.probes[index];
        if (probe.id == 0 || probe.revision == 0) {
            return detail::set_light_error(
                diagnostic, LightingError::InvalidProbe, probe.id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (probes.probes[previous].id == probe.id) {
                return detail::set_light_error(
                    diagnostic, LightingError::DuplicateId, probe.id, index);
            }
        }
        if (probe.scene_generation != expected_generation) {
            return detail::set_light_error(
                diagnostic, LightingError::HistoryInvalid, probe.id, index);
        }
        if (!detail::finite_vec(probe.origin)
            || !detail::finite(probe.spacing)
            || !(probe.spacing > 0.0f)) {
            return detail::set_light_error(
                diagnostic, LightingError::InvalidProbe, probe.id, index);
        }
        if (probe.cells_x == 0 || probe.cells_y == 0 || probe.cells_z == 0) {
            return detail::set_light_error(
                diagnostic, LightingError::InvalidProbe, probe.id, index);
        }
        const u64 cells = static_cast<u64>(probe.cells_x)
            * static_cast<u64>(probe.cells_y)
            * static_cast<u64>(probe.cells_z);
        if (cells > kMaxProbeCells) {
            return detail::set_light_error(
                diagnostic, LightingError::InvalidProbe, probe.id, index);
        }
        ids[index] = probe.id;
    }
    std::sort(ids.begin(), ids.begin() + probes.count);
    plan.count = probes.count;
    for (u32 index = 0; index < probes.count; ++index) {
        plan.probe_ids[index] = ids[index];
    }
    return LightingError::None;
}

}  // namespace stormline::graphics::lighting

#endif  // STORMLINE_GRAPHICS_LIGHTING_PROBE_PLAN_HPP
