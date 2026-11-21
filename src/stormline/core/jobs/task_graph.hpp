#pragma once

#include <array>
#include <cstdint>

namespace stormline::core::jobs {

enum class JobPriority : std::uint8_t {
    Background,
    Normal,
    High,
    FrameCritical
};

enum class JobAffinity : std::uint8_t {
    AnyWorker,
    MainThread
};

enum class CancellationStatus : std::uint8_t {
    Active,
    Requested
};

enum class JobError : std::uint8_t {
    None,
    InvalidCapacity,
    InvalidTask,
    InvalidGraph,
    CycleDetected,
    DependencyFailed,
    Cancelled,
    QueueFull,
    ResourceExhausted,
    DeadlineMissed,
    AffinityViolation,
    DeadlockRisk,
    WrongThread,
    NotInitialized,
    ShuttingDown,
    InternalFailure
};

enum class ExecutorState : std::uint8_t {
    Uninitialized,
    Running,
    Draining,
    Stopped,
    Failed
};

struct TaskId {
    std::uint32_t value{0};
};

struct JobHandle {
    std::uint64_t value{0};
};

struct CancellationScope {
    std::uint64_t value{0};
};

struct JobFence {
    std::uint64_t value{0};
};

struct WorkBudget {
    std::uint32_t max_workers{1};
    std::uint32_t max_tasks{256};
    std::uint64_t frame_budget_ns{0};
    std::uint32_t background_quota{0};
};

struct ExecutorStats {
    std::uint64_t submitted{0};
    std::uint64_t completed{0};
    std::uint64_t cancelled{0};
    std::uint64_t failed{0};
    std::uint64_t queue_depth{0};
    std::uint64_t peak_queue_depth{0};
    std::uint64_t busy_ns{0};
    std::uint64_t idle_ns{0};
};

using JobFunction = void (*)(void* context);
using CommitFunction = void (*)(void* context);

struct JobStateAccess;

class TaskGraph final {
public:
    static constexpr std::uint32_t capacity = 256;

    explicit TaskGraph(std::uint32_t tasks) noexcept;

    [[nodiscard]] JobError add_task(TaskId id, JobPriority priority, JobAffinity affinity,
                                    CancellationScope scope, JobFunction function,
                                    void* context) noexcept;
    [[nodiscard]] JobError add_dependency(TaskId before, TaskId after) noexcept;
    [[nodiscard]] JobError add_commit(std::uint32_t order, TaskId task,
                                      CommitFunction function, void* context) noexcept;
    [[nodiscard]] JobError finalize() noexcept;
    [[nodiscard]] bool valid() const noexcept;

private:
    friend struct JobStateAccess;

    static constexpr std::uint32_t edge_words = capacity / 64;

    struct TaskRecord {
        TaskId id{};
        JobPriority priority{JobPriority::Normal};
        JobAffinity affinity{JobAffinity::AnyWorker};
        CancellationScope scope{};
        JobFunction function{nullptr};
        void* context{nullptr};
    };

    struct CommitRecord {
        std::uint32_t order{0};
        TaskId task{};
        CommitFunction function{nullptr};
        void* context{nullptr};
    };

    struct EdgeRow {
        std::array<std::uint64_t, edge_words> words{};
    };

    [[nodiscard]] std::uint32_t find_task(TaskId id) const noexcept;
    [[nodiscard]] bool has_edge(std::uint32_t before, std::uint32_t after) const noexcept;
    void set_edge(std::uint32_t before, std::uint32_t after) noexcept;

    std::uint32_t size_limit_{0};
    std::uint32_t task_count_{0};
    std::uint32_t commit_count_{0};
    JobError construction_error_{JobError::None};
    JobError validation_error_{JobError::None};
    bool finalized_{false};
    bool valid_{false};
    std::array<TaskRecord, capacity> tasks_{};
    std::array<EdgeRow, capacity> edges_{};
    std::array<CommitRecord, capacity> commits_{};
};

}  // namespace stormline::core::jobs
