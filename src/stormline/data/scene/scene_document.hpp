#ifndef STORMLINE_DATA_SCENE_SCENE_DOCUMENT_HPP
#define STORMLINE_DATA_SCENE_SCENE_DOCUMENT_HPP

#include "stormline/data/registry/registry_types.hpp"
#include "stormline/data/scene/scene_schema.hpp"

#include <array>

namespace stormline::data::scene {

namespace registry = stormline::data::registry;

struct AssetRef {
    registry::AssetId asset{};
    EntityId entity{};
    u32 role{0};
};

class SceneDocument final {
public:
    SceneDocument() noexcept = default;

    [[nodiscard]] SceneError init(
        SceneId scene, registry::ProjectId project,
        const SchemaDescriptor& schema) noexcept {
        if (!valid(scene) || !registry::valid(project)) {
            return SceneError::InvalidArgument;
        }
        const SceneError schema_status = validate_schema(schema);
        if (schema_status != SceneError::None) {
            return schema_status;
        }
        scene_ = scene;
        project_ = project;
        schema_ = schema;
        revision_ = 1;
        entity_count_ = 0;
        component_count_ = 0;
        asset_ref_count_ = 0;
        initialized_ = true;
        return SceneError::None;
    }

    [[nodiscard]] SceneError add_entity(const EntityRecord& entity) noexcept {
        if (!initialized_) {
            return SceneError::InvalidArgument;
        }
        if (!valid(entity.id) || !valid_name(entity.name, entity.name_length)) {
            return SceneError::InvalidArgument;
        }
        for (u32 index = 0; index < entity_count_; ++index) {
            if (entities_[index].id.value == entity.id.value) {
                return SceneError::DuplicateId;
            }
        }
        if (valid(entity.parent)) {
            if (entity.parent.value == entity.id.value) {
                return SceneError::ParentCycle;
            }
            EntityId cursor = entity.parent;
            u32 guard = 0;
            bool found_parent = false;
            while (valid(cursor) && guard < kMaxEntities) {
                if (cursor.value == entity.id.value) {
                    return SceneError::ParentCycle;
                }
                bool found = false;
                for (u32 index = 0; index < entity_count_; ++index) {
                    if (entities_[index].id.value == cursor.value) {
                        cursor = entities_[index].parent;
                        found = true;
                        found_parent = found_parent || (guard == 0);
                        break;
                    }
                }
                if (!found) {
                    if (guard == 0) {
                        return SceneError::NotFound;
                    }
                    break;
                }
                ++guard;
            }
            if (!found_parent) {
                return SceneError::NotFound;
            }
        }
        if (entity_count_ >= kMaxEntities) {
            return SceneError::CapacityFull;
        }
        entities_[entity_count_++] = entity;
        return SceneError::None;
    }

    [[nodiscard]] SceneError add_component(const ComponentRecord& component) noexcept {
        if (!initialized_ || !valid(component.id) || !valid(component.entity)
            || component.type_id == 0 || component.type_version == 0) {
            return SceneError::InvalidArgument;
        }
        for (u32 index = 0; index < component_count_; ++index) {
            if (components_[index].id.value == component.id.value) {
                return SceneError::DuplicateId;
            }
        }
        EntityRecord entity{};
        if (find_entity(component.entity, entity) != SceneError::None) {
            return SceneError::NotFound;
        }
        if (component_count_ >= kMaxComponents) {
            return SceneError::CapacityFull;
        }
        components_[component_count_++] = component;
        return SceneError::None;
    }

    [[nodiscard]] SceneError add_asset_ref(const AssetRef& ref) noexcept {
        if (!initialized_ || !registry::valid(ref.asset) || !valid(ref.entity)) {
            return SceneError::InvalidArgument;
        }
        EntityRecord entity{};
        if (find_entity(ref.entity, entity) != SceneError::None) {
            return SceneError::NotFound;
        }
        for (u32 index = 0; index < asset_ref_count_; ++index) {
            if (asset_refs_[index].asset.high == ref.asset.high
                && asset_refs_[index].asset.low == ref.asset.low
                && asset_refs_[index].role == ref.role) {
                return SceneError::DuplicateId;
            }
        }
        if (asset_ref_count_ >= kMaxAssetRefs) {
            return SceneError::CapacityFull;
        }
        asset_refs_[asset_ref_count_++] = ref;
        return SceneError::None;
    }

    [[nodiscard]] SceneError find_entity(EntityId id, EntityRecord& out) const noexcept {
        for (u32 index = 0; index < entity_count_; ++index) {
            if (entities_[index].id.value == id.value) {
                out = entities_[index];
                return SceneError::None;
            }
        }
        return SceneError::NotFound;
    }

    [[nodiscard]] SceneError find_component(
        ComponentId id, ComponentRecord& out) const noexcept {
        for (u32 index = 0; index < component_count_; ++index) {
            if (components_[index].id.value == id.value) {
                out = components_[index];
                return SceneError::None;
            }
        }
        return SceneError::NotFound;
    }

    [[nodiscard]] bool entity_at(u32 index, EntityRecord& out) const noexcept {
        if (index >= entity_count_) {
            return false;
        }
        out = entities_[index];
        return true;
    }

    [[nodiscard]] SceneError remove_entity(EntityId id) noexcept {
        u32 index = 0;
        while (index < entity_count_ && entities_[index].id.value != id.value) {
            ++index;
        }
        if (index >= entity_count_) {
            return SceneError::NotFound;
        }
        for (u32 next = index + 1; next < entity_count_; ++next) {
            entities_[next - 1] = entities_[next];
        }
        --entity_count_;
        u32 component_index = 0;
        while (component_index < component_count_) {
            if (components_[component_index].entity.value == id.value) {
                for (u32 next = component_index + 1; next < component_count_; ++next) {
                    components_[next - 1] = components_[next];
                }
                --component_count_;
            } else {
                ++component_index;
            }
        }
        u32 ref_index = 0;
        while (ref_index < asset_ref_count_) {
            if (asset_refs_[ref_index].entity.value == id.value) {
                for (u32 next = ref_index + 1; next < asset_ref_count_; ++next) {
                    asset_refs_[next - 1] = asset_refs_[next];
                }
                --asset_ref_count_;
            } else {
                ++ref_index;
            }
        }
        return SceneError::None;
    }

    [[nodiscard]] SceneError set_enabled(EntityId id, bool enabled) noexcept {
        for (u32 index = 0; index < entity_count_; ++index) {
            if (entities_[index].id.value == id.value) {
                entities_[index].enabled = enabled;
                return SceneError::None;
            }
        }
        return SceneError::NotFound;
    }

    void advance_revision() noexcept { ++revision_; }

    [[nodiscard]] SceneId scene() const noexcept { return scene_; }
    [[nodiscard]] registry::ProjectId project() const noexcept { return project_; }
    [[nodiscard]] SchemaDescriptor schema() const noexcept { return schema_; }
    [[nodiscard]] u64 revision() const noexcept { return revision_; }
    [[nodiscard]] u32 entity_count() const noexcept { return entity_count_; }
    [[nodiscard]] u32 component_count() const noexcept { return component_count_; }
    [[nodiscard]] u32 asset_ref_count() const noexcept { return asset_ref_count_; }

private:
    static bool valid_name(const std::array<char, kMaxNameBytes>& name, u32 length) noexcept {
        if (length == 0 || length > kMaxNameBytes) {
            return false;
        }
        for (u32 index = 0; index < length; ++index) {
            const char byte = name[index];
            if (byte < 0x20 || byte > 0x7E || byte == '/' || byte == ':'
                || static_cast<unsigned char>(byte) == 0x5Cu) {
                return false;
            }
        }
        return true;
    }

    bool initialized_{false};
    SceneId scene_{};
    registry::ProjectId project_{};
    SchemaDescriptor schema_{};
    u64 revision_{0};
    std::array<EntityRecord, kMaxEntities> entities_{};
    std::array<ComponentRecord, kMaxComponents> components_{};
    std::array<AssetRef, kMaxAssetRefs> asset_refs_{};
    u32 entity_count_{0};
    u32 component_count_{0};
    u32 asset_ref_count_{0};
};

}  // namespace stormline::data::scene

#endif  // STORMLINE_DATA_SCENE_SCENE_DOCUMENT_HPP
