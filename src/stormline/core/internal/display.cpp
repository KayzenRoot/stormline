#include "stormline/core/internal/display.hpp"

#include <SDL3/SDL.h>

#include <thread>

namespace stormline::core::internal {
namespace {

bool on_owner_thread(const std::thread::id& owner) noexcept {
    return std::this_thread::get_id() == owner;
}

bool fill_display(SDL_DisplayID id, bool primary, DisplayInfo& out) noexcept {
    SDL_Rect bounds{};
    SDL_Rect usable{};
    if (!SDL_GetDisplayBounds(id, &bounds)) {
        return false;
    }
    if (!SDL_GetDisplayUsableBounds(id, &usable)) {
        return false;
    }
    const float scale = SDL_GetDisplayContentScale(id);
    if (!(scale > 0.0F)) {
        return false;
    }

    out.id = static_cast<std::uint32_t>(id);
    out.primary = primary;
    out.x = bounds.x;
    out.y = bounds.y;
    out.width = bounds.w;
    out.height = bounds.h;
    out.usable_x = usable.x;
    out.usable_y = usable.y;
    out.usable_width = usable.w;
    out.usable_height = usable.h;
    out.content_scale = scale;
    return true;
}

}  // namespace

DisplayService::DisplayService() noexcept
    : owner_thread_(std::this_thread::get_id()) {}

DisplayError DisplayService::enumerate(DisplayInfo* out, std::size_t capacity,
                                       std::size_t& count) noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return DisplayError::WrongThread;
        }
        if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
            return DisplayError::VideoNotInitialized;
        }
        if (out == nullptr && capacity != 0) {
            return DisplayError::InvalidArgument;
        }

        int display_count = 0;
        SDL_DisplayID* displays = SDL_GetDisplays(&display_count);
        if (displays == nullptr || display_count <= 0) {
            SDL_free(displays);
            count = 0;
            return DisplayError::NoDisplays;
        }

        const std::size_t total = static_cast<std::size_t>(display_count);
        if (capacity < total) {
            SDL_free(displays);
            count = total;
            return DisplayError::BufferTooSmall;
        }

        const SDL_DisplayID primary_id = SDL_GetPrimaryDisplay();
        for (std::size_t index = 0; index < total; ++index) {
            if (!fill_display(displays[index], displays[index] == primary_id, out[index])) {
                SDL_free(displays);
                return DisplayError::QueryFailed;
            }
        }

        SDL_free(displays);
        count = total;
        return DisplayError::None;
    } catch (...) {
        return DisplayError::InternalFailure;
    }
}

DisplayError DisplayService::primary(DisplayInfo& out) noexcept {
    try {
        if (!on_owner_thread(owner_thread_)) {
            return DisplayError::WrongThread;
        }
        if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
            return DisplayError::VideoNotInitialized;
        }

        const SDL_DisplayID primary_id = SDL_GetPrimaryDisplay();
        if (primary_id == 0) {
            return DisplayError::NoDisplays;
        }
        return fill_display(primary_id, true, out)
                   ? DisplayError::None
                   : DisplayError::QueryFailed;
    } catch (...) {
        return DisplayError::InternalFailure;
    }
}

}  // namespace stormline::core::internal
