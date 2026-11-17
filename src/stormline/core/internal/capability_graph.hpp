#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <thread>

namespace stormline::core::internal {

enum class CapabilityId : std::uint8_t {
    Video,
    Events,
    Window,
    Displays,
    WaylandRuntime
};

enum class CapabilityState : std::uint8_t {
    Unknown,
    Supported,
    Unsupported
};

enum class CapabilitySource : std::uint8_t {
    Unknown,
    SdlProbe,
    Explicit
};

enum class CapabilityError : std::uint8_t {
    None,
    WrongThread,
    GraphFull,
    InvalidId,
    InternalFailure
};

struct CapabilityRecord final {
    CapabilityId id{CapabilityId::Video};
    CapabilityState state{CapabilityState::Unknown};
    CapabilitySource source{CapabilitySource::Unknown};
};

class CapabilityGraph final {
public:
    static constexpr std::size_t capacity = 8;

    CapabilityGraph() noexcept = default;
    ~CapabilityGraph() noexcept = default;

    CapabilityGraph(const CapabilityGraph&) = delete;
    CapabilityGraph& operator=(const CapabilityGraph&) = delete;
    CapabilityGraph(CapabilityGraph&&) = delete;
    CapabilityGraph& operator=(CapabilityGraph&&) = delete;

    [[nodiscard]] bool set(CapabilityId id, CapabilityState state,
                           CapabilitySource source) noexcept;
    [[nodiscard]] bool find(CapabilityId id, CapabilityRecord& out) const noexcept;
    [[nodiscard]] CapabilityState state(CapabilityId id) const noexcept;
    [[nodiscard]] std::size_t count() const noexcept;
    void clear() noexcept;

private:
    std::array<CapabilityRecord, capacity> records_{};
    std::size_t count_{0};
};

class CapabilityProbe final {
public:
    CapabilityProbe() noexcept;
    ~CapabilityProbe() noexcept = default;

    CapabilityProbe(const CapabilityProbe&) = delete;
    CapabilityProbe& operator=(const CapabilityProbe&) = delete;
    CapabilityProbe(CapabilityProbe&&) = delete;
    CapabilityProbe& operator=(CapabilityProbe&&) = delete;

    [[nodiscard]] CapabilityError probe(CapabilityGraph& graph) noexcept;

private:
    std::thread::id owner_thread_;
};

}  // namespace stormline::core::internal
