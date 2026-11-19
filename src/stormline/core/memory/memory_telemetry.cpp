#include "stormline/core/memory/memory_telemetry.hpp"

namespace stormline::core::memory {
namespace {

constexpr std::memory_order relaxed = std::memory_order_relaxed;

bool valid_domain(MemoryDomain domain) noexcept {
    return static_cast<std::uint8_t>(domain) < memory_telemetry_domain_count;
}

std::size_t domain_index(MemoryDomain domain) noexcept {
    return static_cast<std::size_t>(domain);
}

void update_peak(std::atomic<std::uint64_t>& peak, std::uint64_t candidate) noexcept {
    std::uint64_t current = peak.load(relaxed);
    while (candidate > current &&
           !peak.compare_exchange_weak(current, candidate, relaxed, relaxed)) {
    }
}

}  // namespace

TelemetryError MemoryTelemetry::record_allocate(MemoryDomain domain,
                                                std::size_t bytes) noexcept {
    try {
        if (bytes == 0) {
            return TelemetryError::InvalidBytes;
        }
        if (!valid_domain(domain)) {
            return TelemetryError::InvalidDomain;
        }

        Counters& counters = domains_[domain_index(domain)];
        counters.allocations.fetch_add(1, relaxed);
        counters.live_allocations.fetch_add(1, relaxed);
        const std::uint64_t domain_live =
            counters.live_bytes.fetch_add(bytes, relaxed) + bytes;
        counters.total_allocated_bytes.fetch_add(bytes, relaxed);
        update_peak(counters.peak_live_bytes, domain_live);

        allocations_.fetch_add(1, relaxed);
        live_allocations_.fetch_add(1, relaxed);
        const std::uint64_t total_live = live_bytes_.fetch_add(bytes, relaxed) + bytes;
        total_allocated_bytes_.fetch_add(bytes, relaxed);
        update_peak(peak_live_bytes_, total_live);
        return TelemetryError::None;
    } catch (...) {
        return TelemetryError::InternalFailure;
    }
}

TelemetryError MemoryTelemetry::record_release(MemoryDomain domain,
                                               std::size_t bytes) noexcept {
    try {
        if (bytes == 0) {
            return TelemetryError::InvalidBytes;
        }
        if (!valid_domain(domain)) {
            return TelemetryError::InvalidDomain;
        }

        Counters& counters = domains_[domain_index(domain)];
        std::uint64_t domain_allocations = counters.live_allocations.load(relaxed);
        for (;;) {
            if (domain_allocations == 0) {
                return TelemetryError::ReleaseUnderflow;
            }
            if (counters.live_allocations.compare_exchange_weak(
                    domain_allocations, domain_allocations - 1, relaxed, relaxed)) {
                break;
            }
        }

        std::uint64_t domain_bytes = counters.live_bytes.load(relaxed);
        for (;;) {
            if (domain_bytes < bytes) {
                counters.live_allocations.fetch_add(1, relaxed);
                return TelemetryError::ReleaseUnderflow;
            }
            if (counters.live_bytes.compare_exchange_weak(
                    domain_bytes, domain_bytes - bytes, relaxed, relaxed)) {
                break;
            }
        }

        std::uint64_t total_allocations = live_allocations_.load(relaxed);
        for (;;) {
            if (total_allocations == 0) {
                counters.live_allocations.fetch_add(1, relaxed);
                counters.live_bytes.fetch_add(bytes, relaxed);
                return TelemetryError::ReleaseUnderflow;
            }
            if (live_allocations_.compare_exchange_weak(
                    total_allocations, total_allocations - 1, relaxed, relaxed)) {
                break;
            }
        }

        std::uint64_t total_bytes = live_bytes_.load(relaxed);
        for (;;) {
            if (total_bytes < bytes) {
                live_allocations_.fetch_add(1, relaxed);
                counters.live_allocations.fetch_add(1, relaxed);
                counters.live_bytes.fetch_add(bytes, relaxed);
                return TelemetryError::ReleaseUnderflow;
            }
            if (live_bytes_.compare_exchange_weak(
                    total_bytes, total_bytes - bytes, relaxed, relaxed)) {
                break;
            }
        }

        counters.releases.fetch_add(1, relaxed);
        counters.total_released_bytes.fetch_add(bytes, relaxed);
        releases_.fetch_add(1, relaxed);
        total_released_bytes_.fetch_add(bytes, relaxed);
        return TelemetryError::None;
    } catch (...) {
        return TelemetryError::InternalFailure;
    }
}

void MemoryTelemetry::record_budget_reserve(std::size_t bytes, BudgetStatus status) noexcept {
    budget_reservations_.fetch_add(1, relaxed);
    const std::uint64_t reserved = budget_reserved_bytes_.fetch_add(bytes, relaxed) + bytes;
    update_peak(budget_peak_reserved_bytes_, reserved);
    if (status == BudgetStatus::SoftPressure) {
        budget_soft_pressure_events_.fetch_add(1, relaxed);
    }
}

void MemoryTelemetry::record_budget_release(std::size_t bytes) noexcept {
    budget_releases_.fetch_add(1, relaxed);
    budget_released_bytes_.fetch_add(bytes, relaxed);
}

void MemoryTelemetry::record_budget_rejection() noexcept {
    budget_hard_rejections_.fetch_add(1, relaxed);
}

void MemoryTelemetry::record_leak_track(std::size_t bytes) noexcept {
    leak_tracked_.fetch_add(1, relaxed);
    const std::uint64_t tracked = leak_tracked_bytes_.fetch_add(bytes, relaxed) + bytes;
    update_peak(leak_peak_tracked_bytes_, tracked);
}

void MemoryTelemetry::record_leak_release(std::size_t bytes) noexcept {
    leak_released_.fetch_add(1, relaxed);
    leak_released_bytes_.fetch_add(bytes, relaxed);
}

void MemoryTelemetry::record_arena_slice(std::size_t bytes,
                                         std::size_t high_water_bytes) noexcept {
    arena_slices_.fetch_add(1, relaxed);
    arena_slice_bytes_.fetch_add(bytes, relaxed);
    update_peak(arena_high_water_bytes_, high_water_bytes);
}

void MemoryTelemetry::snapshot(MemoryTelemetrySnapshot& out) const noexcept {
    for (std::size_t index = 0; index < domains_.size(); ++index) {
        const Counters& counters = domains_[index];
        MemoryTelemetryDomainSnapshot& domain = out.domains[index];
        domain.allocations = counters.allocations.load(relaxed);
        domain.releases = counters.releases.load(relaxed);
        domain.live_allocations = counters.live_allocations.load(relaxed);
        domain.live_bytes = counters.live_bytes.load(relaxed);
        domain.peak_live_bytes = counters.peak_live_bytes.load(relaxed);
        domain.total_allocated_bytes = counters.total_allocated_bytes.load(relaxed);
        domain.total_released_bytes = counters.total_released_bytes.load(relaxed);
    }

    out.budget.reservations = budget_reservations_.load(relaxed);
    out.budget.releases = budget_releases_.load(relaxed);
    out.budget.reserved_bytes = budget_reserved_bytes_.load(relaxed);
    out.budget.released_bytes = budget_released_bytes_.load(relaxed);
    out.budget.peak_reserved_bytes = budget_peak_reserved_bytes_.load(relaxed);
    out.budget.soft_pressure_events = budget_soft_pressure_events_.load(relaxed);
    out.budget.hard_rejections = budget_hard_rejections_.load(relaxed);

    out.leak.tracked = leak_tracked_.load(relaxed);
    out.leak.released = leak_released_.load(relaxed);
    out.leak.tracked_bytes = leak_tracked_bytes_.load(relaxed);
    out.leak.released_bytes = leak_released_bytes_.load(relaxed);
    out.leak.peak_tracked_bytes = leak_peak_tracked_bytes_.load(relaxed);

    out.arena.slices = arena_slices_.load(relaxed);
    out.arena.slice_bytes = arena_slice_bytes_.load(relaxed);
    out.arena.high_water_bytes = arena_high_water_bytes_.load(relaxed);

    out.allocations = allocations_.load(relaxed);
    out.releases = releases_.load(relaxed);
    out.live_allocations = live_allocations_.load(relaxed);
    out.live_bytes = live_bytes_.load(relaxed);
    out.peak_live_bytes = peak_live_bytes_.load(relaxed);
    out.total_allocated_bytes = total_allocated_bytes_.load(relaxed);
    out.total_released_bytes = total_released_bytes_.load(relaxed);
}

bool MemoryTelemetry::empty() const noexcept {
    return live_allocations_.load(relaxed) == 0 && live_bytes_.load(relaxed) == 0;
}

}  // namespace stormline::core::memory
