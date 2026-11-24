#ifndef STORMLINE_PROCEDURAL_BIOME_PLAN_HPP
#define STORMLINE_PROCEDURAL_BIOME_PLAN_HPP

#include <array>

#include "stormline/procedural/procedural_types.hpp"

namespace stormline::procedural {

struct BiomeZoneDesc {
    u32 zone_id{0};
    u32 revision{0};
    u32 palette_asset_id{0};
    f32 weight{0.0f};
    u32 priority{0};
    bool enabled{false};
};

struct BiomeSetDesc {
    u32 graph_id{0};
    u32 revision{0};
    u32 zone_count{0};
    std::array<BiomeZoneDesc, kMaxBiomeZones> zones{};
};

struct BiomePlan {
    u32 zone_count{0};
    u32 enabled_count{0};
    f32 total_weight{0.0f};
    u32 max_priority{0};
};

[[nodiscard]] inline ProcError plan_biomes(
    const BiomeSetDesc& biomes, BiomePlan& plan,
    ProcDiagnostic& diagnostic) noexcept {
    plan = BiomePlan{};
    diagnostic = ProcDiagnostic{};
    if (biomes.graph_id == 0 || biomes.revision == 0) {
        return detail::set_proc_error(
            diagnostic, ProcError::InvalidArgument, biomes.graph_id, 0);
    }
    if (biomes.zone_count == 0) {
        return detail::set_proc_error(
            diagnostic, ProcError::BiomeInvalid, biomes.graph_id, 0);
    }
    if (biomes.zone_count > kMaxBiomeZones) {
        return detail::set_proc_error(
            diagnostic, ProcError::CapacityFull, biomes.graph_id, 0);
    }
    for (u32 index = 0; index < biomes.zone_count; ++index) {
        const BiomeZoneDesc& zone = biomes.zones[index];
        if (zone.zone_id == 0 || zone.revision == 0
            || zone.palette_asset_id == 0) {
            return detail::set_proc_error(
                diagnostic, ProcError::BiomeInvalid, biomes.graph_id, index);
        }
        if (!detail::finite(zone.weight) || !(zone.weight >= 0.0f)
            || !(zone.weight <= 1.0f)) {
            return detail::set_proc_error(
                diagnostic, ProcError::OutOfRange, biomes.graph_id, index);
        }
        for (u32 previous = 0; previous < index; ++previous) {
            if (biomes.zones[previous].zone_id == zone.zone_id) {
                return detail::set_proc_error(
                    diagnostic, ProcError::DuplicateId, biomes.graph_id,
                    index);
            }
        }
    }
    plan.zone_count = biomes.zone_count;
    for (u32 index = 0; index < biomes.zone_count; ++index) {
        const BiomeZoneDesc& zone = biomes.zones[index];
        if (zone.enabled) {
            ++plan.enabled_count;
        }
        plan.total_weight += zone.weight;
        if (!(plan.total_weight <= 16.0f)) {
            plan = BiomePlan{};
            return detail::set_proc_error(
                diagnostic, ProcError::OutOfRange, biomes.graph_id, index);
        }
        if (zone.priority > plan.max_priority) {
            plan.max_priority = zone.priority;
        }
    }
    return ProcError::None;
}

}  // namespace stormline::procedural

#endif  // STORMLINE_PROCEDURAL_BIOME_PLAN_HPP
