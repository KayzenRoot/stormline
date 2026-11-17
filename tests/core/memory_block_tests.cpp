#include "stormline/core/memory/memory_block.hpp"

#if defined(SDL_h_)
#error "SDL header/type leaked through the CORE-02 memory header"
#endif

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <memory_resource>
#include <new>
#include <string_view>
#include <thread>
#include <type_traits>

namespace {

using stormline::core::memory::MemoryBlock;
using stormline::core::memory::MemoryDomain;
using stormline::core::memory::MemoryError;

static_assert(!std::is_copy_constructible_v<MemoryBlock>);
static_assert(!std::is_copy_assignable_v<MemoryBlock>);
static_assert(std::is_nothrow_move_constructible_v<MemoryBlock>);
static_assert(std::is_nothrow_move_assignable_v<MemoryBlock>);
static_assert(std::is_nothrow_destructible_v<MemoryBlock>);

int failures = 0;

void expect(bool condition, const char* description) {
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s\n", description);
        ++failures;
    }
}

void begin_case() {
    failures = 0;
}

bool finish_case() {
    return failures == 0;
}

class CountingResource final : public std::pmr::memory_resource {
public:
    std::atomic<int> allocations{0};
    std::atomic<int> deallocations{0};
    std::atomic<int> live{0};
    std::atomic<std::size_t> last_bytes{0};
    std::atomic<std::size_t> last_alignment{0};
    std::atomic<bool> fail{false};

private:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        if (fail.load(std::memory_order_relaxed)) {
            throw std::bad_alloc();
        }
        void* pointer = std::pmr::new_delete_resource()->allocate(bytes, alignment);
        allocations.fetch_add(1, std::memory_order_relaxed);
        live.fetch_add(1, std::memory_order_relaxed);
        last_bytes.store(bytes, std::memory_order_relaxed);
        last_alignment.store(alignment, std::memory_order_relaxed);
        return pointer;
    }

    void do_deallocate(void* pointer, std::size_t bytes, std::size_t alignment) override {
        std::pmr::new_delete_resource()->deallocate(pointer, bytes, alignment);
        deallocations.fetch_add(1, std::memory_order_relaxed);
        live.fetch_sub(1, std::memory_order_relaxed);
        last_bytes.store(bytes, std::memory_order_relaxed);
        last_alignment.store(alignment, std::memory_order_relaxed);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};

bool is_aligned(const void* pointer, std::size_t alignment) {
    return reinterpret_cast<std::uintptr_t>(pointer) % alignment == 0;
}

bool run_basic() {
    begin_case();
    MemoryBlock block;
    expect(!block.valid(), "fresh block is invalid");
    expect(!static_cast<bool>(block), "fresh block is false");
    expect(MemoryBlock::allocate(nullptr, 256, 64, MemoryDomain::Persistent, block)
               == MemoryError::None,
           "allocate from the default resource succeeds");
    expect(block.valid(), "block is valid after allocate");
    expect(static_cast<bool>(block), "block is true after allocate");
    expect(block.size() == 256, "block records the exact size");
    expect(block.alignment() == 64, "block records the exact alignment");
    expect(block.domain() == MemoryDomain::Persistent, "block records the domain");
    expect(is_aligned(block.data(), 64), "block honors the requested alignment");

    std::memset(block.data(), 0x5a, block.size());
    expect(block.data()[0] == std::byte{0x5a}, "block is writable at the front");
    expect(block.data()[255] == std::byte{0x5a}, "block is writable at the back");
    expect(block.release() == MemoryError::None, "release succeeds");
    expect(!block.valid(), "block is invalid after release");
    expect(block.release() == MemoryError::None, "repeated release is idempotent");
    return finish_case();
}

bool run_invalid() {
    begin_case();
    MemoryBlock block;

    expect(MemoryBlock::allocate(nullptr, 0, 16, MemoryDomain::Frame, block)
               == MemoryError::InvalidSize,
           "zero size is rejected");
    expect(!block.valid(), "zero size leaves the block invalid");
    expect(MemoryBlock::allocate(nullptr, 16, 0, MemoryDomain::Job, block)
               == MemoryError::InvalidAlignment,
           "zero alignment is rejected");
    expect(MemoryBlock::allocate(nullptr, 16, 3, MemoryDomain::Job, block)
               == MemoryError::InvalidAlignment,
           "non-power-of-two alignment is rejected");
    expect(MemoryBlock::allocate(nullptr, 16, 24, MemoryDomain::Job, block)
               == MemoryError::InvalidAlignment,
           "another non-power-of-two alignment is rejected");
    expect(!block.valid(), "invalid requests leave the block invalid");
    return finish_case();
}

bool run_owned() {
    begin_case();
    MemoryBlock block;
    expect(MemoryBlock::allocate(nullptr, 32, 16, MemoryDomain::Editor, block)
               == MemoryError::None,
           "initial allocation succeeds");
    void* const original = block.data();
    const std::size_t original_size = block.size();
    const MemoryDomain original_domain = block.domain();

    expect(MemoryBlock::allocate(nullptr, 64, 64, MemoryDomain::Vfx, block)
               == MemoryError::AlreadyOwned,
           "already-owned destination is rejected");
    expect(block.data() == original, "rejected allocation preserves the pointer");
    expect(block.size() == original_size, "rejected allocation preserves the size");
    expect(block.domain() == original_domain, "rejected allocation preserves the domain");
    expect(block.release() == MemoryError::None, "original block releases");
    return finish_case();
}

bool run_move() {
    begin_case();
    CountingResource resource;

    MemoryBlock first;
    expect(MemoryBlock::allocate(&resource, 64, 32, MemoryDomain::Job, first)
               == MemoryError::None,
           "first move-test allocation succeeds");
    void* const first_pointer = first.data();

    MemoryBlock second(std::move(first));
    expect(!first.valid(), "move construction invalidates the source");
    expect(second.valid(), "move construction keeps the destination valid");
    expect(second.data() == first_pointer, "move construction preserves the pointer");
    expect(second.size() == 64, "move construction preserves the size");
    expect(second.alignment() == 32, "move construction preserves the alignment");
    expect(second.domain() == MemoryDomain::Job, "move construction preserves the domain");

    MemoryBlock third;
    expect(MemoryBlock::allocate(&resource, 16, 16, MemoryDomain::Network, third)
               == MemoryError::None,
           "second move-test allocation succeeds");
    void* const third_pointer = third.data();

    MemoryBlock fourth(std::move(third));
    expect(!third.valid(), "move construction invalidates the second source");
    expect(fourth.data() == third_pointer, "second move preserves the pointer");

    second = std::move(fourth);
    expect(!fourth.valid(), "move assignment invalidates the source");
    expect(second.data() == third_pointer, "move assignment takes the new pointer");
    expect(second.size() == 16, "move assignment takes the new size");
    expect(resource.deallocations.load() == 1,
           "move assignment releases the previous destination exactly once");
    expect(resource.live.load() == 1, "move assignment leaves exactly one live block");

    expect(second.release() == MemoryError::None, "moved-to block releases");
    expect(resource.deallocations.load() == 2, "moved-to block releases exactly once");
    expect(resource.live.load() == 0, "no live block remains after move/release");

    MemoryBlock self;
    expect(MemoryBlock::allocate(&resource, 8, 8, MemoryDomain::Frame, self)
               == MemoryError::None,
           "self-move allocation succeeds");
    void* const self_pointer = self.data();
    self = std::move(self);
    expect(self.valid(), "self-move assignment leaves the block valid");
    expect(self.data() == self_pointer, "self-move assignment preserves the pointer");
    expect(self.release() == MemoryError::None, "self-move block releases");
    expect(resource.live.load() == 0, "self-move does not leak");
    return finish_case();
}

bool run_release() {
    begin_case();
    CountingResource resource;
    {
        MemoryBlock block;
        expect(MemoryBlock::allocate(&resource, 48, 16, MemoryDomain::Streaming, block)
                   == MemoryError::None,
               "release-test allocation succeeds");
        expect(block.release() == MemoryError::None, "explicit release succeeds");
        expect(block.release() == MemoryError::None, "second explicit release is idempotent");
        expect(resource.deallocations.load() == 1, "explicit release deallocates once");
        expect(resource.live.load() == 0, "explicit release leaves no live block");
    }
    expect(resource.deallocations.load() == 1, "invalid destructor does not deallocate");

    {
        MemoryBlock block;
        expect(MemoryBlock::allocate(&resource, 32, 16, MemoryDomain::AudioRealtime, block)
                   == MemoryError::None,
               "destructor-test allocation succeeds");
    }
    expect(resource.deallocations.load() == 2, "destructor deallocates once");
    expect(resource.live.load() == 0, "destructor leaves no live block");
    return finish_case();
}

bool run_resource() {
    begin_case();
    CountingResource resource;
    MemoryBlock block;
    expect(MemoryBlock::allocate(&resource, 100, 64, MemoryDomain::Plugin, block)
               == MemoryError::None,
           "custom-resource allocation succeeds");
    expect(resource.allocations.load() == 1, "custom resource saw one allocation");
    expect(resource.last_bytes.load() == 100, "custom resource saw the exact size");
    expect(resource.last_alignment.load() == 64, "custom resource saw the exact alignment");
    expect(block.release() == MemoryError::None, "custom-resource release succeeds");
    expect(resource.deallocations.load() == 1, "custom resource saw one deallocation");
    expect(resource.last_bytes.load() == 100, "deallocation used the exact size");
    expect(resource.last_alignment.load() == 64, "deallocation used the exact alignment");
    expect(resource.live.load() == 0, "custom resource has no live block");
    return finish_case();
}

bool run_oom() {
    begin_case();
    CountingResource resource;
    resource.fail.store(true, std::memory_order_relaxed);
    MemoryBlock block;
    expect(MemoryBlock::allocate(&resource, 64, 16, MemoryDomain::Persistent, block)
               == MemoryError::OutOfMemory,
           "bad_alloc maps to OutOfMemory");
    expect(!block.valid(), "failed allocation leaves the block invalid");
    expect(resource.allocations.load() == 0, "failed allocation does not count as allocated");
    expect(resource.deallocations.load() == 0, "failed allocation does not deallocate");

    resource.fail.store(false, std::memory_order_relaxed);
    expect(MemoryBlock::allocate(&resource, 64, 16, MemoryDomain::Persistent, block)
               == MemoryError::None,
           "resource recovers after a failed request");
    expect(block.release() == MemoryError::None, "recovered block releases");
    expect(resource.live.load() == 0, "recovered block leaves no live allocation");
    return finish_case();
}

bool run_cross_thread() {
    begin_case();
    CountingResource resource;
    MemoryBlock block;
    expect(MemoryBlock::allocate(&resource, 128, 64, MemoryDomain::Network, block)
               == MemoryError::None,
           "cross-thread allocation succeeds");

    MemoryError worker_result = MemoryError::InternalFailure;
    std::thread worker([&block, &worker_result] {
        worker_result = block.release();
    });
    worker.join();

    expect(worker_result == MemoryError::None, "worker release succeeds");
    expect(!block.valid(), "worker release invalidates the block");
    expect(resource.deallocations.load() == 1, "worker release deallocates once");
    expect(resource.live.load() == 0, "worker release leaves no live block");
    return finish_case();
}

bool run_lifetime() {
    begin_case();
    CountingResource resource;
    bool ok = true;
    for (int cycle = 0; cycle < 1000 && ok; ++cycle) {
        MemoryBlock block;
        const std::size_t bytes = 32 + (static_cast<std::size_t>(cycle) % 17);
        const std::size_t alignment = (cycle % 5 == 0) ? 128 : 16;
        ok = MemoryBlock::allocate(&resource, bytes, alignment, MemoryDomain::Frame, block)
                 == MemoryError::None;
        ok = ok && block.valid();
        ok = ok && block.size() == bytes;
        ok = ok && block.alignment() == alignment;
        ok = ok && is_aligned(block.data(), alignment);
        ok = ok && block.release() == MemoryError::None;
    }
    expect(ok, "1000 allocate/release cycles succeed");
    expect(resource.allocations.load() == 1000, "lifetime test allocated exactly 1000 blocks");
    expect(resource.deallocations.load() == 1000, "lifetime test deallocated exactly 1000 blocks");
    expect(resource.live.load() == 0, "lifetime test leaves no live block");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: %s <basic|invalid|owned|move|release|resource|oom|cross_thread|lifetime>\n",
                     argv[0]);
        return 2;
    }

    const std::string_view mode(argv[1]);
    if (mode == "basic") {
        return run_basic() ? 0 : 1;
    }
    if (mode == "invalid") {
        return run_invalid() ? 0 : 1;
    }
    if (mode == "owned") {
        return run_owned() ? 0 : 1;
    }
    if (mode == "move") {
        return run_move() ? 0 : 1;
    }
    if (mode == "release") {
        return run_release() ? 0 : 1;
    }
    if (mode == "resource") {
        return run_resource() ? 0 : 1;
    }
    if (mode == "oom") {
        return run_oom() ? 0 : 1;
    }
    if (mode == "cross_thread") {
        return run_cross_thread() ? 0 : 1;
    }
    if (mode == "lifetime") {
        return run_lifetime() ? 0 : 1;
    }

    std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return 2;
}
