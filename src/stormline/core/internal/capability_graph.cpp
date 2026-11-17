#include "stormline/core/internal/capability_graph.hpp"

#include <SDL3/SDL.h>

#include <cstring>
#include <thread>

namespace stormline::core::internal {
namespace {

bool on_owner_thread(const std::thread::id& owner) noexcept {
    return std::this_thread::get_id() == owner;
}

bool is_valid(CapabilityId id) noexcept {
    switch (id) {
        case CapabilityId::Video:
        case CapabilityId::Events:
        case CapabilityId::Window:
        case CapabilityId::Displays:
        case CapabilityId::WaylandRuntime:
            return true;
    }
    return false;
}

CapabilityState wayland_state(const char* driver) noexcept {
    if (driver == nullptr) {
        return CapabilityState::Unknown;
    }
    if (std::strcmp(driver, "wayland") == 0) {
        return CapabilityState::Supported;
    }
    if (std::strcmp(driver, "dummy") == 0 || std::strcmp(driver, "offscreen") == 0) {
        return CapabilityState::Unknown;
    }
    return CapabilityState::Unsupported;
}

CapabilityError apply(CapabilityGraph& graph, CapabilityId id, CapabilityState state,
                      CapabilitySource source) noexcept {
    return graph.set(id, state, source) ? CapabilityError::None : CapabilityError::GraphFull;
}

}  // namespace

bool CapabilityGraph::set(CapabilityId id, CapabilityState state,
                          CapabilitySource source) noexcept {
    if (!is_valid(id)) {
        return false;
    }
    for (std::size_t index = 0; index < count_; ++index) {
        if (records_[index].id == id) {
            records_[index].state = state;
            records_[index].source = source;
            return true;
        }
    }
    if (count_ >= capacity) {
        return false;
    }
    records_[count_] = CapabilityRecord{id, state, source};
    ++count_;
    return true;
}

bool CapabilityGraph::find(CapabilityId id, CapabilityRecord& out) const noexcept {
    for (std::size_t index = 0; index < count_; ++index) {
        if (records_[index].id == id) {
            out = records_[index];
            return true;
        }
    }
    return false;
}

CapabilityState CapabilityGraph::state(CapabilityId id) const noexcept {
    CapabilityRecord record{};
    return find(id, record) ? record.state : CapabilityState::Unknown;
}

std::size_t CapabilityGraph::count() const noexcept {
    return count_;
}

void CapabilityGraph::clear() noexcept {
    count_ = 0;
}

CapabilityProbe::CapabilityProbe() noexcept
    : owner_thread_(std::this_thread::get_id()) {}

CapabilityError CapabilityProbe::probe(CapabilityGraph& graph) noexcept {
    if (!on_owner_thread(owner_thread_)) {
        return CapabilityError::WrongThread;
    }

    try {
        const bool video = SDL_WasInit(SDL_INIT_VIDEO) != 0;
        if (!video) {
            for (CapabilityId id : {CapabilityId::Video, CapabilityId::Events,
                                    CapabilityId::Window, CapabilityId::Displays,
                                    CapabilityId::WaylandRuntime}) {
                const CapabilityError error = apply(
                    graph, id, CapabilityState::Unknown, CapabilitySource::SdlProbe);
                if (error != CapabilityError::None) {
                    return error;
                }
            }
            return CapabilityError::None;
        }

        for (CapabilityId id : {CapabilityId::Video, CapabilityId::Events,
                                CapabilityId::Window, CapabilityId::Displays}) {
            const CapabilityError error = apply(
                graph, id, CapabilityState::Supported, CapabilitySource::SdlProbe);
            if (error != CapabilityError::None) {
                return error;
            }
        }

        const CapabilityError error = apply(
            graph, CapabilityId::WaylandRuntime,
            wayland_state(SDL_GetCurrentVideoDriver()), CapabilitySource::SdlProbe);
        return error;
    } catch (...) {
        return CapabilityError::InternalFailure;
    }
}

}  // namespace stormline::core::internal
