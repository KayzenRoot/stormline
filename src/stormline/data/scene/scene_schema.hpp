#ifndef STORMLINE_DATA_SCENE_SCENE_SCHEMA_HPP
#define STORMLINE_DATA_SCENE_SCENE_SCHEMA_HPP

#include "stormline/data/scene/scene_types.hpp"

namespace stormline::data::scene {

[[nodiscard]] inline SceneError validate_schema(
    const SchemaDescriptor& schema) noexcept {
    if (schema.schema_id != 1) {
        return SceneError::InvalidSchema;
    }
    if (schema.version < 1 || schema.version > 3) {
        return SceneError::UnsupportedSchema;
    }
    if ((schema.capabilities & ~static_cast<u32>(0x3)) != 0) {
        return SceneError::UnsupportedSchema;
    }
    if (schema.canonicalization_version != 1) {
        return SceneError::UnsupportedSchema;
    }
    return SceneError::None;
}

}  // namespace stormline::data::scene

#endif  // STORMLINE_DATA_SCENE_SCENE_SCHEMA_HPP
