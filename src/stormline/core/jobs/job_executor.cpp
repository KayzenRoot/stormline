#include "stormline/core/jobs/job_executor.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <new>
#include <thread>
#include <utility>
#include <vector>

namespace stormline::core::jobs {

struct JobStateAccess {
    static JobError construction_error(const TaskGraph& graph) noexcept {
        return graph.construction_error_;
    }

    static JobError validation_error(const TaskGraph& graph) noexcept {
        return graph.validation_error_;
    }

    static std::uint32_t task_count(const TaskGraph& graph) noexcept {
        return graph.task_count_;
    }

    static TaskId task_id(const TaskGraph& graph, std::uint32_t index) noexcept {
        return graph.tasks_[index].id;
    }

    static JobPriority task_priority(const TaskGraph& graph, std::uint32_t index) noexcept {
        return graph.tasks_[index].priority;
    }

    static JobAffinity task_affinity(const TaskGraph& graph, std::uint32_t index) noexcept {
        return graph.tasks_[index].affinity;
    }

    static CancellationScope task_scope(const TaskGraph& graph, std::uint32_t index) noexcept {
        return graph.tasks_[index].scope;
    }

    static JobFunction task_function(const TaskGraph& graph, std::uint32_t index) noexcept {
        return graph.tasks_[index].function;
    }

    static void* task_context(const TaskGraph& graph, std::uint32_t index) noexcept {
        return graph.tasks_[index].context;
    }

    static std::uint64_t edge_word(const TaskGraph& graph, std::uint32_t before,
                                   std::uint32_t word) noexcept {
        return graph.edges_[before].words[word];
    }

    static std::uint32_t commit_count(const TaskGraph& graph) noexcept {
        return graph.commit_count_;
    }

    static std::uint32_t commit_order(const TaskGraph& graph, std::uint32_t index) noexcept {
        return graph.commits_[index].order;
    }

    static TaskId commit_task(const TaskGraph& graph, std::uint32_t index) noexcept {
        return graph.commits_[index].task;
    }

    static CommitFunction commit_function(const TaskGraph& graph, std::uint32_t index) noexcept {
        return graph.commits_[index].function;
    }

    static void* commit_context(const TaskGraph& graph, std::uint32_t index) noexcept {
        return graph.commits_[index].context;
    }
};

namespace {

constexpr std::uint32_t max_jobs = 256;
constexpr std::uint32_t max_cancelled_scopes = 256;
constexpr std::uint32_t edge_word_count = TaskGraph::capacity / 64;
constexpr std::uint16_t no_commit = 0xFFFFU;
constexpr std::uint64_t generation_mask = (std::uint64_t{1} << 48U) - 1U;

thread_local bool tls_worker = false;
thread_local bool tls_in_task = false;
thread_local bool tls_in_commit = false;
thread_local bool tls_in_pump = false;

struct ScopedFlag {
    bool& flag;
    explicit ScopedFlag(bool& target) noexcept : flag(target) {
        flag = true;
    }
    ~ScopedFlag() {
        flag = false;
    }
    ScopedFlag(const ScopedFlag&) = delete;
    ScopedFlag& operator=(const ScopedFlag&) = delete;
};

enum class TaskState : std::uint8_t {
    Pending,
    Queued,
    Running,
    Completed,
    Cancelled,
    Failed,
    DependencyFailed
};

struct JobState;

struct WorkItem {
    std::shared_ptr<JobState> job;
    std::uint32_t task_slot{0};
    std::uint32_t sequence{0};
    JobPriority priority{JobPriority::Normal};
    TaskId id{};
};

struct ReadyCompare {
    bool operator()(const WorkItem& left, const WorkItem& right) const noexcept {
        if (left.priority != right.priority) {
            return left.priority < right.priority;
        }
        if (left.id.value != right.id.value) {
            return left.id.value > right.id.value;
        }
        if (left.sequence != right.sequence) {
            return left.sequence > right.sequence;
        }
        return left.task_slot > right.task_slot;
    }
};

class ReadyQueue final {
public:
    void reserve(std::size_t count) {
        heap_.reserve(count);
    }

    [[nodiscard]] bool empty() const noexcept {
        return heap_.empty();
    }

    void push(const WorkItem& item) {
        heap_.push_back(item);
        std::push_heap(heap_.begin(), heap_.end(), ReadyCompare{});
    }

    WorkItem pop() {
        std::pop_heap(heap_.begin(), heap_.end(), ReadyCompare{});
        WorkItem item = std::move(heap_.back());
        heap_.pop_back();
        return item;
    }

    void clear() noexcept {
        heap_.clear();
    }

    template <typename Predicate>
    std::uint32_t prune(Predicate keep) {
        const std::size_t before = heap_.size();
        const auto new_end = std::remove_if(heap_.begin(), heap_.end(),
                                            [&](const WorkItem& item) { return !keep(item); });
        heap_.erase(new_end, heap_.end());
        std::make_heap(heap_.begin(), heap_.end(), ReadyCompare{});
        return static_cast<std::uint32_t>(before - heap_.size());
    }

private:
    std::vector<WorkItem> heap_;
};

struct CommitRuntime {
    std::uint32_t order{0};
    std::uint16_t task_slot{0};
    CommitFunction function{nullptr};
    void* context{nullptr};
};

struct JobState {
    std::uint32_t task_count{0};
    std::array<TaskState, TaskGraph::capacity> states{};
    std::array<std::uint16_t, TaskGraph::capacity> remaining{};
    std::array<TaskId, TaskGraph::capacity> ids{};
    std::array<JobPriority, TaskGraph::capacity> priorities{};
    std::array<JobAffinity, TaskGraph::capacity> affinities{};
    std::array<CancellationScope, TaskGraph::capacity> scopes{};
    std::array<JobFunction, TaskGraph::capacity> functions{};
    std::array<void*, TaskGraph::capacity> contexts{};
    std::array<std::array<std::uint64_t, edge_word_count>, TaskGraph::capacity> edges{};

    std::uint32_t commit_count{0};
    std::array<CommitRuntime, TaskGraph::capacity> commits{};
    std::uint32_t next_commit{0};
    bool commit_in_flight{false};

    std::uint32_t finished_tasks{0};
    std::uint32_t running_tasks{0};
    std::uint32_t queued_tasks{0};
    bool done{false};
    bool cancelled{false};
    bool failed{false};
    bool dependency_failed{false};
    JobError terminal_error{JobError::None};
};

struct JobSlot {
    std::shared_ptr<JobState> job;
    std::uint64_t generation{1};
    bool in_use{false};
};

[[nodiscard]] bool is_terminal(TaskState state) noexcept {
    return state == TaskState::Completed || state == TaskState::Cancelled
           || state == TaskState::Failed || state == TaskState::DependencyFailed;
}

}  // namespace

struct JobExecutor::Impl {
    Impl() = default;

    JobError start(WorkBudget requested) noexcept;
    JobError submit(const TaskGraph& graph, JobFence& fence) noexcept;
    JobError request_cancel(CancellationScope scope) noexcept;
    JobError wait(JobFence fence) noexcept;
    JobError drain() noexcept;
    JobError stop() noexcept;
    [[nodiscard]] ExecutorState state() const noexcept;
    [[nodiscard]] ExecutorStats stats() const noexcept;
    void pump_main_thread() noexcept;

    bool enqueue_locked(const std::shared_ptr<JobState>& job, std::uint32_t slot);
    void mark_cancelled_locked(JobState& job, std::uint32_t slot);
    void mark_dependency_failed_locked(JobState& job, std::uint32_t slot);
    void fail_overflow_locked(JobState& job);
    void finish_task_locked(const std::shared_ptr<JobState>& job_ptr, std::uint32_t slot,
                            bool success);
    void maybe_complete_job_locked(JobState& job);
    std::shared_ptr<JobState> next_ready_commit_locked(CommitRuntime& entry);
    void run_ready_commits();
    void cancel_pending_locked(JobState& job);
    void prune_finished_queues_locked();
    void worker_loop(std::uint32_t index);
    void release_slot_locked(std::uint32_t slot, std::uint64_t generation);
    [[nodiscard]] JobFence fence_for_slot_locked(std::uint32_t slot) const noexcept;
    [[nodiscard]] bool scope_cancelled(std::uint64_t scope) const noexcept;
    [[nodiscard]] bool add_cancelled_scope(std::uint64_t scope) noexcept;

    mutable std::mutex mutex_;
    std::mutex commit_mutex_;
    std::mutex stop_mutex_;
    std::condition_variable cv_;
    std::atomic<ExecutorState> state_{ExecutorState::Uninitialized};
    std::vector<std::thread> workers_;

    WorkBudget budget_{};
    std::thread::id owner_{};
    bool stop_requested_{false};
    bool draining_{false};

    std::array<JobSlot, max_jobs> slots_{};
    ReadyQueue frame_queue_;
    ReadyQueue background_queue_;
    ReadyQueue main_queue_;
    std::uint32_t queued_tasks_{0};
    std::uint32_t running_tasks_{0};
    std::uint64_t enqueue_sequence_{0};
    std::uint64_t work_generation_{0};
    std::array<std::uint64_t, max_cancelled_scopes> cancelled_scopes_{};
    std::uint32_t cancelled_scope_count_{0};

    std::uint64_t submitted_{0};
    std::uint64_t completed_{0};
    std::uint64_t cancelled_{0};
    std::uint64_t failed_{0};
    std::uint32_t peak_queue_depth_{0};
    std::atomic<std::uint64_t> busy_ns_{0};
    std::atomic<std::uint64_t> idle_ns_{0};
};

bool JobExecutor::Impl::enqueue_locked(const std::shared_ptr<JobState>& job,
                                       std::uint32_t slot) {
    if (job->states[slot] != TaskState::Pending) {
        return true;
    }
    if (queued_tasks_ >= budget_.max_tasks) {
        return false;
    }
    WorkItem item;
    item.job = job;
    item.task_slot = slot;
    item.sequence = static_cast<std::uint32_t>(enqueue_sequence_ & 0xFFFFFFFFU);
    ++enqueue_sequence_;
    item.priority = job->priorities[slot];
    item.id = job->ids[slot];
    job->states[slot] = TaskState::Queued;
    ++job->queued_tasks;
    ++queued_tasks_;
    if (queued_tasks_ > peak_queue_depth_) {
        peak_queue_depth_ = queued_tasks_;
    }
    if (job->affinities[slot] == JobAffinity::MainThread) {
        main_queue_.push(item);
    } else if (job->priorities[slot] == JobPriority::Background
               && budget_.background_quota > 0U) {
        background_queue_.push(item);
    } else {
        frame_queue_.push(item);
    }
    ++work_generation_;
    cv_.notify_all();
    return true;
}

void JobExecutor::Impl::mark_cancelled_locked(JobState& job, std::uint32_t slot) {
    if (job.states[slot] != TaskState::Pending && job.states[slot] != TaskState::Queued) {
        return;
    }
    job.states[slot] = TaskState::Cancelled;
    ++job.finished_tasks;
    ++cancelled_;
    job.cancelled = true;
    ++work_generation_;
    for (std::uint32_t after = 0; after < job.task_count; ++after) {
        const std::uint64_t word = job.edges[slot][after / 64U];
        if ((word & (std::uint64_t{1} << (after % 64U))) != 0U) {
            mark_dependency_failed_locked(job, after);
        }
    }
    maybe_complete_job_locked(job);
}

void JobExecutor::Impl::mark_dependency_failed_locked(JobState& job, std::uint32_t slot) {
    if (job.states[slot] != TaskState::Pending) {
        return;
    }
    job.states[slot] = TaskState::DependencyFailed;
    ++job.finished_tasks;
    ++failed_;
    job.dependency_failed = true;
    ++work_generation_;
    for (std::uint32_t after = 0; after < job.task_count; ++after) {
        const std::uint64_t word = job.edges[slot][after / 64U];
        if ((word & (std::uint64_t{1} << (after % 64U))) != 0U) {
            mark_dependency_failed_locked(job, after);
        }
    }
    maybe_complete_job_locked(job);
}

void JobExecutor::Impl::fail_overflow_locked(JobState& job) {
    if (job.terminal_error == JobError::None) {
        job.terminal_error = JobError::QueueFull;
    }
    for (std::uint32_t slot = 0; slot < job.task_count; ++slot) {
        if (job.states[slot] == TaskState::Pending || job.states[slot] == TaskState::Queued) {
            job.states[slot] = TaskState::Cancelled;
            ++job.finished_tasks;
            ++cancelled_;
            job.cancelled = true;
        }
    }
    ++work_generation_;
    maybe_complete_job_locked(job);
}

void JobExecutor::Impl::finish_task_locked(const std::shared_ptr<JobState>& job_ptr,
                                           std::uint32_t slot, bool success) {
    JobState& job = *job_ptr;
    if (job.states[slot] != TaskState::Running) {
        return;
    }
    if (running_tasks_ > 0U) {
        --running_tasks_;
    }
    if (job.running_tasks > 0U) {
        --job.running_tasks;
    }
    ++work_generation_;

    if (!success) {
        job.states[slot] = TaskState::Failed;
        ++job.finished_tasks;
        ++failed_;
        job.failed = true;
        if (job.terminal_error == JobError::None) {
            job.terminal_error = JobError::InternalFailure;
        }
        for (std::uint32_t after = 0; after < job.task_count; ++after) {
            const std::uint64_t word = job.edges[slot][after / 64U];
            if ((word & (std::uint64_t{1} << (after % 64U))) != 0U) {
                mark_dependency_failed_locked(job, after);
            }
        }
        maybe_complete_job_locked(job);
        cv_.notify_all();
        return;
    }

    job.states[slot] = TaskState::Completed;
    ++job.finished_tasks;
    ++completed_;

    for (std::uint32_t after = 0; after < job.task_count; ++after) {
        const std::uint64_t word = job.edges[slot][after / 64U];
        if ((word & (std::uint64_t{1} << (after % 64U))) == 0U) {
            continue;
        }
        if (job.states[after] != TaskState::Pending) {
            continue;
        }
        if (job.remaining[after] > 0U) {
            --job.remaining[after];
        }
        if (job.remaining[after] != 0U) {
            continue;
        }
        if (stop_requested_ || job.terminal_error != JobError::None) {
            mark_cancelled_locked(job, after);
            continue;
        }
        if (!enqueue_locked(job_ptr, after)) {
            fail_overflow_locked(job);
            break;
        }
    }

    maybe_complete_job_locked(job);
    cv_.notify_all();
}

void JobExecutor::Impl::maybe_complete_job_locked(JobState& job) {
    if (job.done || job.commit_in_flight) {
        return;
    }
    if (job.finished_tasks < job.task_count) {
        return;
    }
    while (job.next_commit < job.commit_count) {
        const CommitRuntime& commit = job.commits[job.next_commit];
        if (commit.task_slot >= job.task_count) {
            ++job.next_commit;
            continue;
        }
        const TaskState state = job.states[commit.task_slot];
        if (state == TaskState::Completed) {
            return;
        }
        if (is_terminal(state)) {
            ++job.next_commit;
            continue;
        }
        return;
    }
    job.done = true;
    if (job.terminal_error == JobError::None) {
        if (job.cancelled) {
            job.terminal_error = JobError::Cancelled;
        } else if (job.dependency_failed) {
            job.terminal_error = JobError::DependencyFailed;
        } else if (job.failed) {
            job.terminal_error = JobError::InternalFailure;
        }
    }
    ++work_generation_;
    cv_.notify_all();
    prune_finished_queues_locked();
}

std::shared_ptr<JobState> JobExecutor::Impl::next_ready_commit_locked(CommitRuntime& entry) {
    if (stop_requested_) {
        return nullptr;
    }
    for (JobSlot& slot : slots_) {
        if (!slot.in_use || !slot.job) {
            continue;
        }
        JobState& job = *slot.job;
        if (job.done || job.commit_in_flight) {
            continue;
        }
        while (job.next_commit < job.commit_count) {
            const CommitRuntime& candidate = job.commits[job.next_commit];
            if (candidate.task_slot >= job.task_count) {
                ++job.next_commit;
                continue;
            }
            const TaskState state = job.states[candidate.task_slot];
            if (state == TaskState::Completed) {
                entry = candidate;
                job.commit_in_flight = true;
                ++job.next_commit;
                return slot.job;
            }
            if (is_terminal(state)) {
                ++job.next_commit;
                continue;
            }
            break;
        }
        maybe_complete_job_locked(job);
    }
    return nullptr;
}

void JobExecutor::Impl::run_ready_commits() {
    if (tls_in_commit) {
        return;
    }
    std::unique_lock<std::mutex> commit_lock(commit_mutex_);

    for (;;) {
        std::shared_ptr<JobState> job;
        CommitRuntime entry;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            job = next_ready_commit_locked(entry);
            if (!job) {
                break;
            }
        }

        bool success = true;
        {
            ScopedFlag commit_flag(tls_in_commit);
            try {
                entry.function(entry.context);
            } catch (...) {
                success = false;
            }
        }

        {
            std::lock_guard<std::mutex> lock(mutex_);
            job->commit_in_flight = false;
            if (!success) {
                job->failed = true;
                if (job->terminal_error == JobError::None) {
                    job->terminal_error = JobError::InternalFailure;
                }
            }
            ++work_generation_;
            maybe_complete_job_locked(*job);
            cv_.notify_all();
        }
    }
}

void JobExecutor::Impl::cancel_pending_locked(JobState& job) {
    bool changed = false;
    for (std::uint32_t slot = 0; slot < job.task_count; ++slot) {
        if (job.states[slot] == TaskState::Pending || job.states[slot] == TaskState::Queued) {
            job.states[slot] = TaskState::Cancelled;
            ++job.finished_tasks;
            ++cancelled_;
            job.cancelled = true;
            changed = true;
        }
    }
    if (changed) {
        if (job.terminal_error == JobError::None) {
            job.terminal_error = JobError::Cancelled;
        }
        ++work_generation_;
    }
    maybe_complete_job_locked(job);
}

void JobExecutor::Impl::prune_finished_queues_locked() {
    const auto keep = [](const WorkItem& item) {
        return item.job && !item.job->done
               && item.job->states[item.task_slot] == TaskState::Queued;
    };
    std::uint32_t removed = frame_queue_.prune(keep);
    removed += background_queue_.prune(keep);
    removed += main_queue_.prune(keep);
    if (removed <= queued_tasks_) {
        queued_tasks_ -= removed;
    } else {
        queued_tasks_ = 0;
    }
}

void JobExecutor::Impl::worker_loop(std::uint32_t index) {
    ScopedFlag worker_flag(tls_worker);
    const bool background_lane = budget_.background_quota > 0U && index < budget_.background_quota;

    for (;;) {
        WorkItem item;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            for (;;) {
                if (stop_requested_) {
                    return;
                }
                ReadyQueue& queue = background_lane ? background_queue_ : frame_queue_;
                if (!queue.empty()) {
                    break;
                }
                const auto idle_start = std::chrono::steady_clock::now();
                cv_.wait(lock);
                const auto idle_end = std::chrono::steady_clock::now();
                idle_ns_.fetch_add(
                    static_cast<std::uint64_t>(
                        std::chrono::duration_cast<std::chrono::nanoseconds>(idle_end - idle_start)
                            .count()),
                    std::memory_order_relaxed);
            }
            item = (background_lane ? background_queue_ : frame_queue_).pop();
            if (queued_tasks_ > 0U) {
                --queued_tasks_;
            }
            if (item.job->states[item.task_slot] != TaskState::Queued) {
                continue;
            }
            if (scope_cancelled(item.job->scopes[item.task_slot].value)) {
                mark_cancelled_locked(*item.job, item.task_slot);
                continue;
            }
            item.job->states[item.task_slot] = TaskState::Running;
            ++item.job->running_tasks;
            ++running_tasks_;
        }

        bool success = true;
        const auto busy_start = std::chrono::steady_clock::now();
        {
            ScopedFlag task_flag(tls_in_task);
            try {
                item.job->functions[item.task_slot](item.job->contexts[item.task_slot]);
            } catch (...) {
                success = false;
            }
        }
        const auto busy_end = std::chrono::steady_clock::now();
        busy_ns_.fetch_add(
            static_cast<std::uint64_t>(
                std::chrono::duration_cast<std::chrono::nanoseconds>(busy_end - busy_start)
                    .count()),
            std::memory_order_relaxed);

        {
            std::lock_guard<std::mutex> lock(mutex_);
            finish_task_locked(item.job, item.task_slot, success);
        }
        run_ready_commits();
        cv_.notify_all();
    }
}

void JobExecutor::Impl::release_slot_locked(std::uint32_t slot, std::uint64_t generation) {
    if (slot >= max_jobs) {
        return;
    }
    JobSlot& target = slots_[slot];
    if (!target.in_use || target.generation != generation) {
        return;
    }
    target.job.reset();
    target.in_use = false;
    target.generation = (target.generation + 1U) & generation_mask;
    if (target.generation == 0U) {
        target.generation = 1U;
    }
}

JobFence JobExecutor::Impl::fence_for_slot_locked(std::uint32_t slot) const noexcept {
    JobFence fence;
    const std::uint64_t generation = slots_[slot].generation & generation_mask;
    fence.value = (generation << 16U) | (static_cast<std::uint64_t>(slot) + 1U);
    return fence;
}

bool JobExecutor::Impl::scope_cancelled(std::uint64_t scope) const noexcept {
    for (std::uint32_t index = 0; index < cancelled_scope_count_; ++index) {
        if (cancelled_scopes_[index] == scope) {
            return true;
        }
    }
    return false;
}

bool JobExecutor::Impl::add_cancelled_scope(std::uint64_t scope) noexcept {
    if (scope_cancelled(scope)) {
        return true;
    }
    if (cancelled_scope_count_ >= max_cancelled_scopes) {
        return false;
    }
    cancelled_scopes_[cancelled_scope_count_] = scope;
    ++cancelled_scope_count_;
    return true;
}

JobError JobExecutor::Impl::start(WorkBudget requested) noexcept {
    if (tls_worker || tls_in_task || tls_in_commit) {
        return JobError::DeadlockRisk;
    }
    std::unique_lock<std::mutex> lock(mutex_);
    const ExecutorState current = state_.load(std::memory_order_acquire);
    if (current == ExecutorState::Running) {
        return JobError::None;
    }
    if (current != ExecutorState::Uninitialized) {
        return JobError::InvalidGraph;
    }
    if (requested.max_workers == 0U || requested.max_workers > JobExecutor::max_workers
        || requested.max_tasks == 0U
        || requested.background_quota >= requested.max_workers) {
        return JobError::InvalidCapacity;
    }

    budget_ = requested;
    owner_ = std::this_thread::get_id();
    stop_requested_ = false;
    draining_ = false;
    queued_tasks_ = 0;
    running_tasks_ = 0;
    enqueue_sequence_ = 0;
    work_generation_ = 0;
    peak_queue_depth_ = 0;
    submitted_ = 0;
    completed_ = 0;
    cancelled_ = 0;
    failed_ = 0;
    busy_ns_.store(0, std::memory_order_relaxed);
    idle_ns_.store(0, std::memory_order_relaxed);
    cancelled_scope_count_ = 0;
    frame_queue_.clear();
    background_queue_.clear();
    main_queue_.clear();
    for (JobSlot& slot : slots_) {
        slot.job.reset();
        slot.in_use = false;
    }
    try {
        frame_queue_.reserve(requested.max_tasks);
        background_queue_.reserve(requested.max_tasks);
        main_queue_.reserve(requested.max_tasks);
        state_.store(ExecutorState::Running, std::memory_order_release);
        workers_.reserve(requested.max_workers);
        for (std::uint32_t index = 0; index < requested.max_workers; ++index) {
            workers_.emplace_back([this, index]() { worker_loop(index); });
        }
    } catch (...) {
        stop_requested_ = true;
        state_.store(ExecutorState::Failed, std::memory_order_release);
        cv_.notify_all();
        std::vector<std::thread> failed_workers = std::move(workers_);
        lock.unlock();
        for (std::thread& worker : failed_workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
        return JobError::ResourceExhausted;
    }
    return JobError::None;
}

JobError JobExecutor::Impl::submit(const TaskGraph& graph, JobFence& fence) noexcept {
    fence.value = 0;
    std::lock_guard<std::mutex> lock(mutex_);
    const ExecutorState current = state_.load(std::memory_order_acquire);
    if (current == ExecutorState::Uninitialized) {
        return JobError::NotInitialized;
    }
    if (current != ExecutorState::Running || stop_requested_ || draining_) {
        return JobError::ShuttingDown;
    }
    if (!graph.valid()) {
        const JobError validation = JobStateAccess::validation_error(graph);
        if (validation != JobError::None) {
            return validation;
        }
        const JobError construction = JobStateAccess::construction_error(graph);
        return construction != JobError::None ? construction : JobError::InvalidGraph;
    }

    const std::uint32_t task_count = JobStateAccess::task_count(graph);
    std::uint32_t slot_index = max_jobs;
    for (std::uint32_t index = 0; index < max_jobs; ++index) {
        if (!slots_[index].in_use) {
            slot_index = index;
            break;
        }
    }
    if (slot_index == max_jobs) {
        return JobError::ResourceExhausted;
    }

    std::uint32_t initial_ready = 0;
    for (std::uint32_t task = 0; task < task_count; ++task) {
        bool ready = true;
        for (std::uint32_t before = 0; before < task_count && ready; ++before) {
            const std::uint64_t word = JobStateAccess::edge_word(graph, before, task / 64U);
            if ((word & (std::uint64_t{1} << (task % 64U))) != 0U) {
                ready = false;
            }
        }
        if (ready && task_count > 0U
            && !scope_cancelled(JobStateAccess::task_scope(graph, task).value)) {
            ++initial_ready;
        }
    }
    if (queued_tasks_ + initial_ready > budget_.max_tasks) {
        return JobError::QueueFull;
    }

    std::shared_ptr<JobState> job;
    try {
        job = std::make_shared<JobState>();
    } catch (...) {
        return JobError::ResourceExhausted;
    }
    job->task_count = task_count;
    for (std::uint32_t task = 0; task < task_count; ++task) {
        job->ids[task] = JobStateAccess::task_id(graph, task);
        job->priorities[task] = JobStateAccess::task_priority(graph, task);
        job->affinities[task] = JobStateAccess::task_affinity(graph, task);
        job->scopes[task] = JobStateAccess::task_scope(graph, task);
        job->functions[task] = JobStateAccess::task_function(graph, task);
        job->contexts[task] = JobStateAccess::task_context(graph, task);
        std::uint16_t dependencies = 0;
        for (std::uint32_t before = 0; before < task_count; ++before) {
            const std::uint64_t word = JobStateAccess::edge_word(graph, before, task / 64U);
            if ((word & (std::uint64_t{1} << (task % 64U))) != 0U) {
                ++dependencies;
            }
        }
        job->remaining[task] = dependencies;
        for (std::uint32_t word = 0; word < edge_word_count; ++word) {
            job->edges[task][word] = JobStateAccess::edge_word(graph, task, word);
        }
    }

    job->commit_count = JobStateAccess::commit_count(graph);
    for (std::uint32_t commit_index = 0; commit_index < job->commit_count; ++commit_index) {
        CommitRuntime& commit = job->commits[commit_index];
        commit.order = JobStateAccess::commit_order(graph, commit_index);
        commit.function = JobStateAccess::commit_function(graph, commit_index);
        commit.context = JobStateAccess::commit_context(graph, commit_index);
        const TaskId task_id = JobStateAccess::commit_task(graph, commit_index);
        commit.task_slot = no_commit;
        for (std::uint32_t task = 0; task < task_count; ++task) {
            if (job->ids[task].value == task_id.value) {
                commit.task_slot = static_cast<std::uint16_t>(task);
                break;
            }
        }
    }
    std::sort(job->commits.begin(), job->commits.begin() + job->commit_count,
              [](const CommitRuntime& left, const CommitRuntime& right) {
                  return left.order < right.order;
              });

    JobSlot& slot = slots_[slot_index];
    slot.job = job;
    slot.in_use = true;
    const JobFence created_fence = fence_for_slot_locked(slot_index);
    submitted_ += task_count;

    for (std::uint32_t task = 0; task < task_count; ++task) {
        if (job->remaining[task] != 0U || job->states[task] != TaskState::Pending) {
            continue;
        }
        if (scope_cancelled(job->scopes[task].value)) {
            mark_cancelled_locked(*job, task);
            continue;
        }
        if (!enqueue_locked(job, task)) {
            fail_overflow_locked(*job);
            slot.job.reset();
            slot.in_use = false;
            return JobError::QueueFull;
        }
    }

    maybe_complete_job_locked(*job);
    fence = created_fence;
    cv_.notify_all();
    return JobError::None;
}

JobError JobExecutor::Impl::request_cancel(CancellationScope scope) noexcept {
    std::lock_guard<std::mutex> lock(mutex_);
    const ExecutorState current = state_.load(std::memory_order_acquire);
    if (current == ExecutorState::Uninitialized) {
        return JobError::NotInitialized;
    }
    if (current == ExecutorState::Stopped || current == ExecutorState::Failed) {
        return JobError::ShuttingDown;
    }
    if (!add_cancelled_scope(scope.value)) {
        return JobError::ResourceExhausted;
    }
    for (JobSlot& slot : slots_) {
        if (!slot.in_use || !slot.job) {
            continue;
        }
        JobState& job = *slot.job;
        for (std::uint32_t task = 0; task < job.task_count; ++task) {
            if (job.scopes[task].value == scope.value
                && (job.states[task] == TaskState::Pending
                    || job.states[task] == TaskState::Queued)) {
                mark_cancelled_locked(job, task);
            }
        }
    }
    cv_.notify_all();
    return JobError::None;
}

JobError JobExecutor::Impl::wait(JobFence fence) noexcept {
    if (tls_worker || tls_in_task || tls_in_commit || tls_in_pump) {
        return JobError::DeadlockRisk;
    }
    if (state_.load(std::memory_order_acquire) == ExecutorState::Uninitialized) {
        return JobError::NotInitialized;
    }
    if (std::this_thread::get_id() != owner_) {
        return JobError::WrongThread;
    }
    const std::uint64_t slot_code = fence.value & 0xFFFFU;
    const std::uint64_t generation = (fence.value >> 16U) & generation_mask;
    if (fence.value == 0U || slot_code == 0U || generation == 0U) {
        return JobError::InvalidTask;
    }
    const std::uint32_t slot_index = static_cast<std::uint32_t>(slot_code - 1U);
    if (slot_index >= max_jobs) {
        return JobError::InvalidTask;
    }

    std::shared_ptr<JobState> job;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!slots_[slot_index].in_use || slots_[slot_index].generation != generation) {
            return JobError::InvalidTask;
        }
        job = slots_[slot_index].job;
    }

    for (;;) {
        std::uint64_t observed_generation = 0;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (job->done) {
                const JobError result = job->terminal_error;
                release_slot_locked(slot_index, generation);
                return result;
            }
            observed_generation = work_generation_;
        }

        pump_main_thread();
        run_ready_commits();

        std::unique_lock<std::mutex> lock(mutex_);
        if (job->done) {
            const JobError result = job->terminal_error;
            release_slot_locked(slot_index, generation);
            return result;
        }
        const ExecutorState current = state_.load(std::memory_order_acquire);
        if (current == ExecutorState::Stopped || current == ExecutorState::Failed) {
            return JobError::ShuttingDown;
        }
        cv_.wait(lock, [&]() {
            return job->done || work_generation_ != observed_generation
                   || state_.load(std::memory_order_acquire) == ExecutorState::Stopped
                   || state_.load(std::memory_order_acquire) == ExecutorState::Failed;
        });
    }
}

JobError JobExecutor::Impl::drain() noexcept {
    if (tls_worker || tls_in_task || tls_in_commit || tls_in_pump) {
        return JobError::DeadlockRisk;
    }
    if (state_.load(std::memory_order_acquire) == ExecutorState::Uninitialized) {
        return JobError::NotInitialized;
    }
    if (std::this_thread::get_id() != owner_) {
        return JobError::WrongThread;
    }
    {
        std::lock_guard<std::mutex> lock(mutex_);
        const ExecutorState current = state_.load(std::memory_order_acquire);
        if (current == ExecutorState::Stopped || current == ExecutorState::Failed) {
            return JobError::ShuttingDown;
        }
        if (draining_) {
            return JobError::None;
        }
        draining_ = true;
        state_.store(ExecutorState::Draining, std::memory_order_release);
        cv_.notify_all();
    }

    std::array<JobFence, max_jobs> fences{};
    std::uint32_t fence_count = 0;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        for (std::uint32_t slot = 0; slot < max_jobs; ++slot) {
            if (slots_[slot].in_use && slots_[slot].job) {
                fences[fence_count] = fence_for_slot_locked(slot);
                ++fence_count;
            }
        }
    }

    JobError first_error = JobError::None;
    for (std::uint32_t index = 0; index < fence_count; ++index) {
        const JobError result = wait(fences[index]);
        if (result != JobError::None && first_error == JobError::None) {
            first_error = result;
        }
    }

    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (state_.load(std::memory_order_acquire) == ExecutorState::Draining) {
            draining_ = false;
            state_.store(ExecutorState::Running, std::memory_order_release);
        }
        cv_.notify_all();
    }
    return first_error;
}

JobError JobExecutor::Impl::stop() noexcept {
    if (tls_worker || tls_in_task || tls_in_commit || tls_in_pump) {
        return JobError::DeadlockRisk;
    }
    std::lock_guard<std::mutex> stop_lock(stop_mutex_);
    {
        std::lock_guard<std::mutex> lock(mutex_);
        const ExecutorState current = state_.load(std::memory_order_acquire);
        if (current == ExecutorState::Stopped) {
            return JobError::None;
        }
        if (current == ExecutorState::Uninitialized) {
            state_.store(ExecutorState::Stopped, std::memory_order_release);
            return JobError::None;
        }
        stop_requested_ = true;
        draining_ = true;
        state_.store(ExecutorState::Draining, std::memory_order_release);
        cv_.notify_all();
    }

    {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [&]() { return running_tasks_ == 0U; });
    }

    {
        // Serialize with the single commit lane before finalizing jobs, so no
        // commit callback cannot still be running when stop() returns.
        std::lock_guard<std::mutex> commit_lock(commit_mutex_);
        std::lock_guard<std::mutex> lock(mutex_);
        for (JobSlot& slot : slots_) {
            if (!slot.in_use || !slot.job) {
                continue;
            }
            cancel_pending_locked(*slot.job);
            if (!slot.job->done) {
                if (slot.job->terminal_error == JobError::None) {
                    slot.job->terminal_error = JobError::Cancelled;
                }
                slot.job->done = true;
            }
        }
        frame_queue_.clear();
        background_queue_.clear();
        main_queue_.clear();
        queued_tasks_ = 0;
        state_.store(ExecutorState::Stopped, std::memory_order_release);
        ++work_generation_;
        cv_.notify_all();
    }

    for (std::thread& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    workers_.clear();
    return JobError::None;
}

void JobExecutor::Impl::pump_main_thread() noexcept {
    if (tls_worker || tls_in_task || tls_in_commit || tls_in_pump) {
        return;
    }
    {
        const ExecutorState current = state_.load(std::memory_order_acquire);
        if (current != ExecutorState::Running && current != ExecutorState::Draining) {
            return;
        }
    }
    if (std::this_thread::get_id() != owner_) {
        return;
    }

    ScopedFlag pump_flag(tls_in_pump);
    for (;;) {
        WorkItem item;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            const ExecutorState current = state_.load(std::memory_order_acquire);
            if (current != ExecutorState::Running && current != ExecutorState::Draining) {
                break;
            }
            if (stop_requested_ || main_queue_.empty()) {
                break;
            }
            item = main_queue_.pop();
            if (queued_tasks_ > 0U) {
                --queued_tasks_;
            }
            if (item.job->states[item.task_slot] != TaskState::Queued) {
                continue;
            }
            if (scope_cancelled(item.job->scopes[item.task_slot].value)) {
                mark_cancelled_locked(*item.job, item.task_slot);
                continue;
            }
            item.job->states[item.task_slot] = TaskState::Running;
            ++item.job->running_tasks;
            ++running_tasks_;
        }

        bool success = true;
        const auto busy_start = std::chrono::steady_clock::now();
        {
            ScopedFlag task_flag(tls_in_task);
            try {
                item.job->functions[item.task_slot](item.job->contexts[item.task_slot]);
            } catch (...) {
                success = false;
            }
        }
        const auto busy_end = std::chrono::steady_clock::now();
        busy_ns_.fetch_add(
            static_cast<std::uint64_t>(
                std::chrono::duration_cast<std::chrono::nanoseconds>(busy_end - busy_start)
                    .count()),
            std::memory_order_relaxed);

        {
            std::lock_guard<std::mutex> lock(mutex_);
            finish_task_locked(item.job, item.task_slot, success);
        }
        run_ready_commits();
        cv_.notify_all();
    }
    run_ready_commits();
}

ExecutorState JobExecutor::Impl::state() const noexcept {
    return state_.load(std::memory_order_acquire);
}

ExecutorStats JobExecutor::Impl::stats() const noexcept {
    ExecutorStats snapshot;
    std::lock_guard<std::mutex> lock(mutex_);
    snapshot.submitted = submitted_;
    snapshot.completed = completed_;
    snapshot.cancelled = cancelled_;
    snapshot.failed = failed_;
    snapshot.queue_depth = queued_tasks_;
    snapshot.peak_queue_depth = peak_queue_depth_;
    snapshot.busy_ns = busy_ns_.load(std::memory_order_relaxed);
    snapshot.idle_ns = idle_ns_.load(std::memory_order_relaxed);
    return snapshot;
}

JobExecutor::JobExecutor() noexcept
    : impl_(new (std::nothrow) Impl()) {}

JobExecutor::~JobExecutor() noexcept {
    if (impl_) {
        (void)stop();
    }
}

JobError JobExecutor::start(WorkBudget budget) noexcept {
    if (!impl_) {
        return JobError::ResourceExhausted;
    }
    return impl_->start(budget);
}

JobError JobExecutor::submit(const TaskGraph& graph, JobFence& fence) noexcept {
    if (!impl_) {
        fence.value = 0;
        return JobError::ResourceExhausted;
    }
    return impl_->submit(graph, fence);
}

JobError JobExecutor::request_cancel(CancellationScope scope) noexcept {
    if (!impl_) {
        return JobError::NotInitialized;
    }
    return impl_->request_cancel(scope);
}

JobError JobExecutor::wait(JobFence fence) noexcept {
    if (!impl_) {
        return JobError::NotInitialized;
    }
    return impl_->wait(fence);
}

JobError JobExecutor::drain() noexcept {
    if (!impl_) {
        return JobError::NotInitialized;
    }
    return impl_->drain();
}

JobError JobExecutor::stop() noexcept {
    if (!impl_) {
        return JobError::NotInitialized;
    }
    return impl_->stop();
}

ExecutorState JobExecutor::state() const noexcept {
    if (!impl_) {
        return ExecutorState::Failed;
    }
    return impl_->state();
}

ExecutorStats JobExecutor::stats() const noexcept {
    if (!impl_) {
        return ExecutorStats{};
    }
    return impl_->stats();
}

void JobExecutor::pump_main_thread() noexcept {
    if (impl_) {
        impl_->pump_main_thread();
    }
}

}  // namespace stormline::core::jobs
