#pragma once

#include <cstddef>
#include <cstdint>
#include <memory_resource>

namespace stormline::core::memory {

class MemoryTelemetry;

enum class MemoryDomain : std::uint8_t {
    Persistent,
    Frame,
    Job,
    Streaming,
    Vfx,
    AudioRealtime,
    Network,
    Editor,
    Plugin
};

enum class MemoryError : std::uint8_t {
    None,
    InvalidSize,
    InvalidAlignment,
    OutOfMemory,
    AlreadyOwned,
    InternalFailure
};

class MemoryBlock final {
public:
    MemoryBlock() noexcept = default;
    ~MemoryBlock() noexcept;

    MemoryBlock(const MemoryBlock&) = delete;
    MemoryBlock& operator=(const MemoryBlock&) = delete;
    MemoryBlock(MemoryBlock&& other) noexcept;
    MemoryBlock& operator=(MemoryBlock&& other) noexcept;

    [[nodiscard]] static MemoryError allocate(
        std::pmr::memory_resource* resource,
        std::size_t bytes,
        std::size_t alignment,
        MemoryDomain domain,
        MemoryBlock& out,
        MemoryTelemetry* telemetry = nullptr) noexcept;

    [[nodiscard]] MemoryError release() noexcept;
    [[nodiscard]] std::byte* data() noexcept;
    [[nodiscard]] const std::byte* data() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] std::size_t alignment() const noexcept;
    [[nodiscard]] MemoryDomain domain() const noexcept;
    [[nodiscard]] bool valid() const noexcept;
    [[nodiscard]] explicit operator bool() const noexcept;

private:
    MemoryBlock(std::pmr::memory_resource* resource, void* data, std::size_t bytes,
                std::size_t alignment, MemoryDomain domain,
                MemoryTelemetry* telemetry) noexcept;

    std::pmr::memory_resource* resource_{nullptr};
    void* data_{nullptr};
    std::size_t bytes_{0};
    std::size_t alignment_{0};
    MemoryDomain domain_{MemoryDomain::Persistent};
    MemoryTelemetry* telemetry_{nullptr};
};

}  // namespace stormline::core::memory
