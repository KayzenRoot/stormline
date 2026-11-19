#pragma once

#include "stormline/core/memory/memory_block.hpp"
#include "stormline/core/memory/memory_budget.hpp"

#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>

namespace stormline::core::memory {

inline constexpr std::size_t memory_telemetry_domain_count = 9;

enum class TelemetryError : std::uint8_t {
    None,
    InvalidBytes,
    InvalidDomain,
    ReleaseUnderflow,
    InternalFailure
};

struct MemoryTelemetryDomainSnapshot {
    std::uint64_t allocations{0};
    std::uint64_t releases{0};
    std::uint64_t live_allocations{0};
    std::uint64_t live_bytes{0};
    std::uint64_t peak_live_bytes{0};
    std::uint64_t total_allocated_bytes{0};
    std::uint64_t total_released_bytes{0};
};

struct MemoryTelemetryBudgetSnapshot {
    std::uint64_t reservations{0};
    std::uint64_t releases{0};
    std::uint64_t reserved_bytes{0};
    std::uint64_t released_bytes{0};
    std::uint64_t peak_reserved_bytes{0};
    std::uint64_t soft_pressure_events{0};
    std::uint64_t hard_rejections{0};
};

struct MemoryTelemetryLeakSnapshot {
    std::uint64_t tracked{0};
    std::uint64_t released{0};
    std::uint64_t tracked_bytes{0};
    std::uint64_t released_bytes{0};
    std::uint64_t peak_tracked_bytes{0};
};

struct MemoryTelemetryArenaSnapshot {
    std::uint64_t slices{0};
    std::uint64_t slice_bytes{0};
    std::uint64_t high_water_bytes{0};
};

struct MemoryTelemetrySnapshot {
    std::array<MemoryTelemetryDomainSnapshot, memory_telemetry_domain_count> domains{};
    MemoryTelemetryBudgetSnapshot budget;
    MemoryTelemetryLeakSnapshot leak;
    MemoryTelemetryArenaSnapshot arena;
    std::uint64_t allocations{0};
    std::uint64_t releases{0};
    std::uint64_t live_allocations{0};
    std::uint64_t live_bytes{0};
    std::uint64_t peak_live_bytes{0};
    std::uint64_t total_allocated_bytes{0};
    std::uint64_t total_released_bytes{0};
};

class MemoryTelemetry final {
public:
    static constexpr std::size_t domain_count = memory_telemetry_domain_count;

    MemoryTelemetry() noexcept = default;
    ~MemoryTelemetry() noexcept = default;

    MemoryTelemetry(const MemoryTelemetry&) = delete;
    MemoryTelemetry& operator=(const MemoryTelemetry&) = delete;
    MemoryTelemetry(MemoryTelemetry&&) = delete;
    MemoryTelemetry& operator=(MemoryTelemetry&&) = delete;

    [[nodiscard]] TelemetryError record_allocate(MemoryDomain domain,
                                                 std::size_t bytes) noexcept;
    [[nodiscard]] TelemetryError record_release(MemoryDomain domain,
                                                std::size_t bytes) noexcept;

    void record_budget_reserve(std::size_t bytes, BudgetStatus status) noexcept;
    void record_budget_release(std::size_t bytes) noexcept;
    void record_budget_rejection() noexcept;
    void record_leak_track(std::size_t bytes) noexcept;
    void record_leak_release(std::size_t bytes) noexcept;
    void record_arena_slice(std::size_t bytes, std::size_t high_water_bytes) noexcept;

    void snapshot(MemoryTelemetrySnapshot& out) const noexcept;
    [[nodiscard]] bool empty() const noexcept;

private:
    struct Counters {
        std::atomic<std::uint64_t> allocations{0};
        std::atomic<std::uint64_t> releases{0};
        std::atomic<std::uint64_t> live_allocations{0};
        std::atomic<std::uint64_t> live_bytes{0};
        std::atomic<std::uint64_t> peak_live_bytes{0};
        std::atomic<std::uint64_t> total_allocated_bytes{0};
        std::atomic<std::uint64_t> total_released_bytes{0};
    };

    std::array<Counters, memory_telemetry_domain_count> domains_{};
    std::atomic<std::uint64_t> allocations_{0};
    std::atomic<std::uint64_t> releases_{0};
    std::atomic<std::uint64_t> live_allocations_{0};
    std::atomic<std::uint64_t> live_bytes_{0};
    std::atomic<std::uint64_t> peak_live_bytes_{0};
    std::atomic<std::uint64_t> total_allocated_bytes_{0};
    std::atomic<std::uint64_t> total_released_bytes_{0};
    std::atomic<std::uint64_t> budget_reservations_{0};
    std::atomic<std::uint64_t> budget_releases_{0};
    std::atomic<std::uint64_t> budget_reserved_bytes_{0};
    std::atomic<std::uint64_t> budget_released_bytes_{0};
    std::atomic<std::uint64_t> budget_peak_reserved_bytes_{0};
    std::atomic<std::uint64_t> budget_soft_pressure_events_{0};
    std::atomic<std::uint64_t> budget_hard_rejections_{0};
    std::atomic<std::uint64_t> leak_tracked_{0};
    std::atomic<std::uint64_t> leak_released_{0};
    std::atomic<std::uint64_t> leak_tracked_bytes_{0};
    std::atomic<std::uint64_t> leak_released_bytes_{0};
    std::atomic<std::uint64_t> leak_peak_tracked_bytes_{0};
    std::atomic<std::uint64_t> arena_slices_{0};
    std::atomic<std::uint64_t> arena_slice_bytes_{0};
    std::atomic<std::uint64_t> arena_high_water_bytes_{0};
};

}  // namespace stormline::core::memory
