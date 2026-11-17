#pragma once

#include <cstddef>
#include <cstdint>
#include <thread>

namespace stormline::core::internal {

struct DisplayInfo final {
    std::uint32_t id{0};
    bool primary{false};
    int x{0};
    int y{0};
    int width{0};
    int height{0};
    int usable_x{0};
    int usable_y{0};
    int usable_width{0};
    int usable_height{0};
    float content_scale{1.0F};
};

enum class DisplayError : std::uint8_t {
    None,
    VideoNotInitialized,
    WrongThread,
    NoDisplays,
    BufferTooSmall,
    InvalidArgument,
    QueryFailed,
    InternalFailure
};

class DisplayService final {
public:
    DisplayService() noexcept;
    ~DisplayService() noexcept = default;

    DisplayService(const DisplayService&) = delete;
    DisplayService& operator=(const DisplayService&) = delete;
    DisplayService(DisplayService&&) = delete;
    DisplayService& operator=(DisplayService&&) = delete;

    [[nodiscard]] DisplayError enumerate(DisplayInfo* out, std::size_t capacity,
                                         std::size_t& count) noexcept;
    [[nodiscard]] DisplayError primary(DisplayInfo& out) noexcept;

private:
    std::thread::id owner_thread_;
};

}  // namespace stormline::core::internal
