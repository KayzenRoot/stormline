#include "stormline/core/jobs/job_executor.hpp"
#include "stormline/core/jobs/task_graph.hpp"

#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <mutex>
#include <string_view>
#include <thread>
#include <vector>

namespace {

using stormline::core::jobs::CancellationScope;
using stormline::core::jobs::ExecutorState;
using stormline::core::jobs::JobAffinity;
using stormline::core::jobs::JobError;
using stormline::core::jobs::JobExecutor;
using stormline::core::jobs::JobFence;
using stormline::core::jobs::JobFunction;
using stormline::core::jobs::JobPriority;
using stormline::core::jobs::TaskGraph;
using stormline::core::jobs::TaskId;
using stormline::core::jobs::WorkBudget;

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

class Recorder final {
public:
    void push(std::uint32_t value) {
        std::lock_guard<std::mutex> lock(mutex_);
        values_.push_back(value);
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        values_.clear();
    }

    [[nodiscard]] std::vector<std::uint32_t> values() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return values_;
    }

private:
    mutable std::mutex mutex_;
    std::vector<std::uint32_t> values_;
};

struct RecordContext {
    Recorder* recorder{nullptr};
    std::uint32_t value{0};
};

void record_value(void* raw) {
    auto& context = *static_cast<RecordContext*>(raw);
    context.recorder->push(context.value);
}

void increment_counter(void* raw) {
    static_cast<std::atomic<std::uint32_t>*>(raw)->fetch_add(1, std::memory_order_relaxed);
}

struct ThreadContext {
    std::mutex mutex;
    std::thread::id id{};
    std::atomic<bool> ran{false};
};

void record_thread(void* raw) {
    auto& context = *static_cast<ThreadContext*>(raw);
    std::lock_guard<std::mutex> lock(context.mutex);
    context.id = std::this_thread::get_id();
    context.ran.store(true, std::memory_order_release);
}

struct WaitContext {
    JobExecutor* executor{nullptr};
    JobFence fence{};
    JobError result{JobError::None};
};

void wait_from_task(void* raw) {
    auto& context = *static_cast<WaitContext*>(raw);
    context.result = context.executor->wait(context.fence);
}

struct StopContext {
    JobExecutor* executor{nullptr};
    JobError result{JobError::None};
};

void stop_from_task(void* raw) {
    auto& context = *static_cast<StopContext*>(raw);
    context.result = context.executor->stop();
}

void wait_for_release(void* raw) {
    auto* flag = static_cast<std::atomic<bool>*>(raw);
    while (!flag->load(std::memory_order_acquire)) {
        std::this_thread::yield();
    }
}

void set_flag(void* raw) {
    static_cast<std::atomic<bool>*>(raw)->store(true, std::memory_order_release);
}

JobError add_task(TaskGraph& graph, std::uint32_t id, JobFunction function, void* context,
                  JobPriority priority = JobPriority::Normal,
                  JobAffinity affinity = JobAffinity::AnyWorker,
                  std::uint64_t scope = 0) {
    return graph.add_task(TaskId{id}, priority, affinity, CancellationScope{scope}, function,
                          context);
}

bool run_job01() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 2;
    budget.max_tasks = 64;
    expect(executor.start(budget) == JobError::None, "job01 start");
    expect(executor.state() == ExecutorState::Running, "job01 running state");

    std::atomic<std::uint32_t> count{0};
    TaskGraph graph(8);
    for (std::uint32_t index = 1; index <= 8; ++index) {
        expect(add_task(graph, index, increment_counter, &count) == JobError::None,
               "job01 add task");
    }
    expect(graph.finalize() == JobError::None, "job01 finalize");
    expect(graph.valid(), "job01 valid graph");

    JobFence fence;
    expect(executor.submit(graph, fence) == JobError::None, "job01 submit");
    expect(fence.value != 0U, "job01 fence nonzero");
    expect(executor.wait(fence) == JobError::None, "job01 wait");
    expect(count.load(std::memory_order_relaxed) == 8U, "job01 all tasks ran once");

    const auto stats = executor.stats();
    expect(stats.submitted == 8U, "job01 submitted");
    expect(stats.completed == 8U, "job01 completed");
    expect(stats.cancelled == 0U, "job01 cancelled zero");
    expect(stats.failed == 0U, "job01 failed zero");
    expect(stats.queue_depth == 0U, "job01 queue drained");
    expect(stats.peak_queue_depth >= stats.queue_depth, "job01 peak queue");
    expect(executor.stop() == JobError::None, "job01 stop");
    expect(executor.state() == ExecutorState::Stopped, "job01 stopped state");
    return finish_case();
}

bool run_job02() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 1;
    budget.max_tasks = 32;
    expect(executor.start(budget) == JobError::None, "job02 start");

    Recorder task_order;
    Recorder commit_order;
    std::array<RecordContext, 4> task_contexts{};
    std::array<RecordContext, 4> commit_contexts{};
    TaskGraph graph(4);
    for (std::uint32_t index = 0; index < 4; ++index) {
        task_contexts[index] = RecordContext{&task_order, index + 1U};
        commit_contexts[index] = RecordContext{&commit_order, (index + 1U) * 10U};
        expect(add_task(graph, index + 1U, record_value, &task_contexts[index]) == JobError::None,
               "job02 add task");
    }
    expect(graph.add_dependency(TaskId{1}, TaskId{2}) == JobError::None, "job02 edge 1-2");
    expect(graph.add_dependency(TaskId{2}, TaskId{3}) == JobError::None, "job02 edge 2-3");
    expect(graph.add_dependency(TaskId{3}, TaskId{4}) == JobError::None, "job02 edge 3-4");
    expect(graph.add_commit(40, TaskId{4}, record_value, &commit_contexts[3]) == JobError::None,
           "job02 commit 40");
    expect(graph.add_commit(30, TaskId{3}, record_value, &commit_contexts[2]) == JobError::None,
           "job02 commit 30");
    expect(graph.add_commit(20, TaskId{2}, record_value, &commit_contexts[1]) == JobError::None,
           "job02 commit 20");
    expect(graph.add_commit(10, TaskId{1}, record_value, &commit_contexts[0]) == JobError::None,
           "job02 commit 10");
    expect(graph.finalize() == JobError::None, "job02 finalize");

    JobFence fence;
    expect(executor.submit(graph, fence) == JobError::None, "job02 submit");
    expect(executor.wait(fence) == JobError::None, "job02 wait");

    const auto tasks = task_order.values();
    expect(tasks.size() == 4U, "job02 four tasks");
    for (std::uint32_t index = 0; index < 4U && index < tasks.size(); ++index) {
        expect(tasks[index] == index + 1U, "job02 dependency order");
    }
    const auto commits = commit_order.values();
    expect(commits.size() == 4U, "job02 four commits");
    for (std::uint32_t index = 0; index < 4U && index < commits.size(); ++index) {
        expect(commits[index] == (index + 1U) * 10U, "job02 deterministic commit order");
    }
    expect(executor.stop() == JobError::None, "job02 stop");
    return finish_case();
}

bool run_job03() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 2;
    budget.max_tasks = 32;
    expect(executor.start(budget) == JobError::None, "job03 start");
    std::atomic<std::uint32_t> ran{0};

    TaskGraph cycle(2);
    expect(add_task(cycle, 1, increment_counter, &ran) == JobError::None, "job03 cycle task 1");
    expect(add_task(cycle, 2, increment_counter, &ran) == JobError::None, "job03 cycle task 2");
    expect(cycle.add_dependency(TaskId{1}, TaskId{2}) == JobError::None, "job03 cycle edge 1");
    expect(cycle.add_dependency(TaskId{2}, TaskId{1}) == JobError::None, "job03 cycle edge 2");
    expect(cycle.finalize() == JobError::CycleDetected, "job03 cycle detected");
    expect(!cycle.valid(), "job03 cycle invalid");
    JobFence cycle_fence;
    expect(executor.submit(cycle, cycle_fence) == JobError::CycleDetected,
           "job03 submit cycle rejected");
    expect(cycle_fence.value == 0U, "job03 cycle fence zero");

    TaskGraph duplicate(4);
    expect(add_task(duplicate, 1, increment_counter, &ran) == JobError::None,
           "job03 duplicate first");
    expect(add_task(duplicate, 1, increment_counter, &ran) == JobError::InvalidTask,
           "job03 duplicate rejected");
    expect(add_task(duplicate, 0, increment_counter, &ran) == JobError::InvalidTask,
           "job03 zero id rejected");
    expect(duplicate.add_task(TaskId{2}, JobPriority::Normal, JobAffinity::AnyWorker,
                              CancellationScope{0}, nullptr, nullptr) == JobError::InvalidTask,
           "job03 null function rejected");
    expect(duplicate.add_task(TaskId{3}, static_cast<JobPriority>(9), JobAffinity::AnyWorker,
                              CancellationScope{0}, increment_counter, &ran) == JobError::InvalidTask,
           "job03 invalid priority rejected");
    expect(duplicate.add_task(TaskId{4}, JobPriority::Normal, static_cast<JobAffinity>(9),
                              CancellationScope{0}, increment_counter, &ran) == JobError::InvalidTask,
           "job03 invalid affinity rejected");

    TaskGraph invalid_edges(2);
    expect(add_task(invalid_edges, 1, increment_counter, &ran) == JobError::None,
           "job03 dangling task");
    expect(invalid_edges.add_dependency(TaskId{1}, TaskId{2}) == JobError::InvalidGraph,
           "job03 dangling edge rejected");
    expect(invalid_edges.add_dependency(TaskId{1}, TaskId{1}) == JobError::InvalidGraph,
           "job03 self edge rejected");

    TaskGraph duplicate_edge(2);
    expect(add_task(duplicate_edge, 1, increment_counter, &ran) == JobError::None,
           "job03 duplicate edge task 1");
    expect(add_task(duplicate_edge, 2, increment_counter, &ran) == JobError::None,
           "job03 duplicate edge task 2");
    expect(duplicate_edge.add_dependency(TaskId{1}, TaskId{2}) == JobError::None,
           "job03 first edge");
    expect(duplicate_edge.add_dependency(TaskId{1}, TaskId{2}) == JobError::InvalidGraph,
           "job03 duplicate edge rejected");

    TaskGraph duplicate_commit(2);
    expect(add_task(duplicate_commit, 1, increment_counter, &ran) == JobError::None,
           "job03 commit task 1");
    expect(add_task(duplicate_commit, 2, increment_counter, &ran) == JobError::None,
           "job03 commit task 2");
    expect(duplicate_commit.add_commit(1, TaskId{1}, record_value, &ran) == JobError::None,
           "job03 commit one");
    expect(duplicate_commit.add_commit(2, TaskId{1}, record_value, &ran) == JobError::None,
           "job03 second commit on same task allowed");
    expect(duplicate_commit.add_commit(1, TaskId{2}, record_value, &ran) == JobError::InvalidGraph,
           "job03 duplicate commit order rejected");
    expect(duplicate_commit.add_commit(3, TaskId{9}, record_value, &ran) == JobError::InvalidTask,
           "job03 commit unknown task rejected");

    TaskGraph zero(0);
    expect(add_task(zero, 1, increment_counter, &ran) == JobError::InvalidCapacity,
           "job03 zero capacity add");
    expect(zero.finalize() == JobError::InvalidCapacity, "job03 zero capacity finalize");

    TaskGraph too_large(257);
    expect(add_task(too_large, 1, increment_counter, &ran) == JobError::InvalidCapacity,
           "job03 oversized capacity add");

    TaskGraph finalized(2);
    expect(add_task(finalized, 1, increment_counter, &ran) == JobError::None,
           "job03 finalized task");
    expect(finalized.finalize() == JobError::None, "job03 finalized finalize");
    expect(add_task(finalized, 2, increment_counter, &ran) == JobError::InvalidGraph,
           "job03 add after finalize rejected");

    TaskGraph empty(4);
    expect(empty.finalize() == JobError::None, "job03 empty finalize");
    JobFence empty_fence;
    expect(executor.submit(empty, empty_fence) == JobError::None, "job03 empty submit");
    expect(executor.wait(empty_fence) == JobError::None, "job03 empty wait");

    expect(ran.load(std::memory_order_relaxed) == 0U, "job03 invalid graphs never ran");
    expect(executor.stop() == JobError::None, "job03 stop");
    return finish_case();
}

bool run_job04() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 1;
    budget.max_tasks = 32;
    expect(executor.start(budget) == JobError::None, "job04 start");

    Recorder order;
    std::array<RecordContext, 8> contexts{};
    struct TaskSpec {
        std::uint32_t id;
        JobPriority priority;
    };
    const std::array<TaskSpec, 8> specs = {{
        {4, JobPriority::Normal},
        {2, JobPriority::Background},
        {7, JobPriority::FrameCritical},
        {1, JobPriority::Background},
        {8, JobPriority::FrameCritical},
        {5, JobPriority::High},
        {3, JobPriority::Normal},
        {6, JobPriority::High},
    }};

    TaskGraph graph(8);
    for (std::uint32_t index = 0; index < 8; ++index) {
        contexts[index] = RecordContext{&order, specs[index].id};
        expect(add_task(graph, specs[index].id, record_value, &contexts[index],
                        specs[index].priority)
                   == JobError::None,
               "job04 add task");
    }
    expect(graph.finalize() == JobError::None, "job04 finalize");
    JobFence fence;
    expect(executor.submit(graph, fence) == JobError::None, "job04 submit");
    expect(executor.wait(fence) == JobError::None, "job04 wait");

    const auto values = order.values();
    const std::array<std::uint32_t, 8> expected = {{7, 8, 5, 6, 3, 4, 1, 2}};
    expect(values.size() == expected.size(), "job04 task count");
    for (std::uint32_t index = 0; index < expected.size() && index < values.size(); ++index) {
        expect(values[index] == expected[index], "job04 priority and TaskId order");
    }
    expect(executor.stop() == JobError::None, "job04 stop");

    JobExecutor quota_executor;
    WorkBudget quota_budget;
    quota_budget.max_workers = 2;
    quota_budget.max_tasks = 16;
    quota_budget.background_quota = 1;
    expect(quota_executor.start(quota_budget) == JobError::None, "job04 quota start");
    std::atomic<bool> release_frame{false};
    std::atomic<bool> background_ran{false};
    TaskGraph quota_graph(3);
    expect(add_task(quota_graph, 1, wait_for_release, &release_frame, JobPriority::FrameCritical)
               == JobError::None,
           "job04 frame task 1");
    expect(add_task(quota_graph, 2, wait_for_release, &release_frame, JobPriority::FrameCritical)
               == JobError::None,
           "job04 frame task 2");
    expect(add_task(quota_graph, 3, set_flag, &background_ran, JobPriority::Background)
               == JobError::None,
           "job04 background task");
    expect(quota_graph.finalize() == JobError::None, "job04 quota finalize");
    JobFence quota_fence;
    expect(quota_executor.submit(quota_graph, quota_fence) == JobError::None,
           "job04 quota submit");
    for (std::uint32_t attempt = 0; attempt < 2000U; ++attempt) {
        if (background_ran.load(std::memory_order_acquire)) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    expect(background_ran.load(std::memory_order_acquire),
           "job04 background quota runs during frame blocking");
    release_frame.store(true, std::memory_order_release);
    expect(quota_executor.wait(quota_fence) == JobError::None, "job04 quota wait");
    expect(quota_executor.stop() == JobError::None, "job04 quota stop");
    return finish_case();
}

bool run_job05() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 1;
    budget.max_tasks = 32;
    expect(executor.start(budget) == JobError::None, "job05 start");

    Recorder ran;
    std::array<RecordContext, 3> contexts{};
    TaskGraph graph(3);
    for (std::uint32_t index = 0; index < 3; ++index) {
        contexts[index] = RecordContext{&ran, index + 1U};
        const std::uint64_t scope = index < 2U ? 7U : 8U;
        expect(add_task(graph, index + 1U, record_value, &contexts[index],
                        JobPriority::Normal, JobAffinity::MainThread, scope)
                   == JobError::None,
               "job05 add task");
    }
    expect(graph.finalize() == JobError::None, "job05 finalize");
    JobFence fence;
    expect(executor.submit(graph, fence) == JobError::None, "job05 submit");
    expect(executor.request_cancel(CancellationScope{7}) == JobError::None, "job05 cancel");
    executor.pump_main_thread();
    expect(executor.wait(fence) == JobError::Cancelled, "job05 wait cancelled");

    const auto values = ran.values();
    expect(values.size() == 1U, "job05 only uncancelled task ran");
    if (!values.empty()) {
        expect(values[0] == 3U, "job05 scope isolation");
    }
    const auto stats = executor.stats();
    expect(stats.submitted == 3U, "job05 submitted");
    expect(stats.completed == 1U, "job05 completed");
    expect(stats.cancelled == 2U, "job05 cancelled count");
    expect(stats.queue_depth == 0U, "job05 cancelled queue pruned");
    expect(executor.stop() == JobError::None, "job05 stop");
    return finish_case();
}

bool run_job06() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 2;
    budget.max_tasks = 32;
    const std::thread::id owner = std::this_thread::get_id();
    expect(executor.start(budget) == JobError::None, "job06 start");

    ThreadContext worker_thread;
    ThreadContext main_thread;
    TaskGraph graph(2);
    expect(add_task(graph, 1, record_thread, &worker_thread) == JobError::None,
           "job06 worker task");
    expect(add_task(graph, 2, record_thread, &main_thread, JobPriority::Normal,
                    JobAffinity::MainThread)
               == JobError::None,
           "job06 main task");
    expect(graph.add_dependency(TaskId{1}, TaskId{2}) == JobError::None, "job06 dependency");
    expect(graph.finalize() == JobError::None, "job06 finalize");

    JobFence fence;
    expect(executor.submit(graph, fence) == JobError::None, "job06 submit");
    expect(executor.wait(fence) == JobError::None, "job06 wait");
    expect(worker_thread.ran.load(std::memory_order_acquire), "job06 worker ran");
    expect(main_thread.ran.load(std::memory_order_acquire), "job06 main ran");
    {
        std::lock_guard<std::mutex> lock(worker_thread.mutex);
        expect(worker_thread.id != owner, "job06 worker is not owner");
    }
    {
        std::lock_guard<std::mutex> lock(main_thread.mutex);
        expect(main_thread.id == owner, "job06 main task on owner");
    }

    JobFence dummy;
    JobError wrong_thread_result = JobError::None;
    std::thread outsider([&]() {
        wrong_thread_result = executor.wait(dummy);
    });
    outsider.join();
    expect(wrong_thread_result == JobError::WrongThread, "job06 non-owner wait rejected");

    WaitContext wait_context{&executor, dummy, JobError::None};
    TaskGraph worker_wait(1);
    expect(add_task(worker_wait, 1, wait_from_task, &wait_context) == JobError::None,
           "job06 waiter task");
    expect(worker_wait.finalize() == JobError::None, "job06 waiter finalize");
    JobFence waiter_fence;
    expect(executor.submit(worker_wait, waiter_fence) == JobError::None, "job06 waiter submit");
    expect(executor.wait(waiter_fence) == JobError::None, "job06 waiter wait");
    expect(wait_context.result == JobError::DeadlockRisk, "job06 worker wait deadlock risk");

    Recorder main_only_ran;
    RecordContext main_only_context{&main_only_ran, 1U};
    TaskGraph main_only(1);
    expect(add_task(main_only, 1, record_value, &main_only_context, JobPriority::Normal,
                    JobAffinity::MainThread)
               == JobError::None,
           "job06 main-only task");
    expect(main_only.finalize() == JobError::None, "job06 main-only finalize");
    JobFence main_only_fence;
    expect(executor.submit(main_only, main_only_fence) == JobError::None,
           "job06 main-only submit");
    std::thread wrong_pump([&]() { executor.pump_main_thread(); });
    wrong_pump.join();
    expect(main_only_ran.values().empty(), "job06 wrong-thread pump is a no-op");
    expect(executor.wait(main_only_fence) == JobError::None, "job06 main-only wait");
    expect(main_only_ran.values().size() == 1U, "job06 owner pump ran main task");

    expect(executor.stop() == JobError::None, "job06 stop");
    return finish_case();
}

bool run_job07() {
    begin_case();
    JobExecutor executor;
    JobFence before_start_fence;
    TaskGraph before_start(1);
    expect(executor.submit(before_start, before_start_fence) == JobError::NotInitialized,
           "job07 submit before start");
    expect(executor.wait(JobFence{1}) == JobError::NotInitialized, "job07 wait before start");

    WorkBudget invalid_budget;
    invalid_budget.max_workers = 0;
    expect(executor.start(invalid_budget) == JobError::InvalidCapacity, "job07 zero workers");
    invalid_budget.max_workers = 33;
    expect(executor.start(invalid_budget) == JobError::InvalidCapacity, "job07 too many workers");
    invalid_budget.max_workers = 1;
    invalid_budget.max_tasks = 0;
    expect(executor.start(invalid_budget) == JobError::InvalidCapacity, "job07 zero tasks");
    invalid_budget.max_tasks = 16;
    invalid_budget.background_quota = 1;
    expect(executor.start(invalid_budget) == JobError::InvalidCapacity,
           "job07 background quota exhausts workers");

    WorkBudget budget;
    budget.max_workers = 1;
    budget.max_tasks = 2;
    expect(executor.start(budget) == JobError::None, "job07 start");

    std::atomic<std::uint32_t> ran{0};
    TaskGraph too_large(4);
    for (std::uint32_t index = 1; index <= 4; ++index) {
        expect(add_task(too_large, index, increment_counter, &ran) == JobError::None,
               "job07 overflow task");
    }
    expect(too_large.finalize() == JobError::None, "job07 overflow finalize");
    JobFence overflow_fence;
    expect(executor.submit(too_large, overflow_fence) == JobError::QueueFull,
           "job07 overflow rejected");
    expect(overflow_fence.value == 0U, "job07 overflow fence zero");
    expect(ran.load(std::memory_order_relaxed) == 0U, "job07 overflow did not run");
    auto stats = executor.stats();
    expect(stats.submitted == 0U, "job07 overflow submitted unchanged");
    expect(stats.queue_depth == 0U, "job07 overflow queue unchanged");

    TaskGraph fit(2);
    for (std::uint32_t index = 1; index <= 2; ++index) {
        expect(add_task(fit, index, increment_counter, &ran) == JobError::None,
               "job07 fit task");
    }
    expect(fit.finalize() == JobError::None, "job07 fit finalize");
    JobFence fit_fence;
    expect(executor.submit(fit, fit_fence) == JobError::None, "job07 fit submit");
    expect(executor.wait(fit_fence) == JobError::None, "job07 fit wait");
    stats = executor.stats();
    expect(stats.submitted == 2U, "job07 fit submitted");
    expect(stats.completed == 2U, "job07 fit completed");
    expect(executor.stop() == JobError::None, "job07 stop");
    return finish_case();
}

bool run_job08() {
    begin_case();
    JobExecutor uninitialized;
    expect(uninitialized.stop() == JobError::None, "job08 uninitialized stop");
    expect(uninitialized.state() == ExecutorState::Stopped, "job08 uninitialized stopped");

    JobExecutor drain_executor;
    WorkBudget drain_budget;
    drain_budget.max_workers = 2;
    drain_budget.max_tasks = 32;
    expect(drain_executor.start(drain_budget) == JobError::None, "job08 drain start");
    std::atomic<std::uint32_t> drained{0};
    TaskGraph drain_graph(4);
    expect(add_task(drain_graph, 1, increment_counter, &drained) == JobError::None,
           "job08 drain worker task 1");
    expect(add_task(drain_graph, 2, increment_counter, &drained, JobPriority::Normal,
                    JobAffinity::MainThread)
               == JobError::None,
           "job08 drain main task 1");
    expect(add_task(drain_graph, 3, increment_counter, &drained) == JobError::None,
           "job08 drain worker task 2");
    expect(add_task(drain_graph, 4, increment_counter, &drained, JobPriority::Normal,
                    JobAffinity::MainThread)
               == JobError::None,
           "job08 drain main task 2");
    expect(drain_graph.finalize() == JobError::None, "job08 drain finalize");
    JobFence drain_fence;
    expect(drain_executor.submit(drain_graph, drain_fence) == JobError::None,
           "job08 drain submit");
    expect(drain_executor.drain() == JobError::None, "job08 drain");
    expect(drained.load(std::memory_order_relaxed) == 4U, "job08 drain ran all tasks");
    expect(drain_executor.state() == ExecutorState::Running, "job08 drain restores running");
    expect(drain_executor.stop() == JobError::None, "job08 drain stop");

    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 2;
    budget.max_tasks = 32;
    expect(executor.start(budget) == JobError::None, "job08 start");
    expect(executor.start(budget) == JobError::None, "job08 repeated start");
    expect(executor.stop() == JobError::None, "job08 stop");
    expect(executor.stop() == JobError::None, "job08 repeated stop");
    expect(executor.state() == ExecutorState::Stopped, "job08 stopped");
    expect(executor.start(budget) == JobError::InvalidGraph, "job08 restart rejected");
    expect(executor.drain() == JobError::ShuttingDown, "job08 drain after stop");

    TaskGraph after_stop(1);
    expect(add_task(after_stop, 1, increment_counter, nullptr) == JobError::None,
           "job08 after stop task");
    expect(after_stop.finalize() == JobError::None, "job08 after stop finalize");
    JobFence after_stop_fence;
    expect(executor.submit(after_stop, after_stop_fence) == JobError::ShuttingDown,
           "job08 submit after stop rejected");

    JobExecutor worker_stop_executor;
    expect(worker_stop_executor.start(budget) == JobError::None, "job08 worker stop start");
    StopContext stop_context{&worker_stop_executor, JobError::None};
    TaskGraph stop_graph(1);
    expect(add_task(stop_graph, 1, stop_from_task, &stop_context) == JobError::None,
           "job08 stop task");
    expect(stop_graph.finalize() == JobError::None, "job08 stop finalize");
    JobFence stop_fence;
    expect(worker_stop_executor.submit(stop_graph, stop_fence) == JobError::None,
           "job08 stop submit");
    expect(worker_stop_executor.wait(stop_fence) == JobError::None, "job08 stop wait");
    expect(stop_context.result == JobError::DeadlockRisk, "job08 worker stop deadlock risk");
    expect(worker_stop_executor.stop() == JobError::None, "job08 owner stop");

    std::atomic<std::uint32_t> ran{0};
    {
        JobExecutor destructor_executor;
        expect(destructor_executor.start(budget) == JobError::None, "job08 destructor start");
        TaskGraph graph(16);
        for (std::uint32_t index = 1; index <= 16; ++index) {
            expect(add_task(graph, index, increment_counter, &ran) == JobError::None,
                   "job08 destructor task");
        }
        expect(graph.finalize() == JobError::None, "job08 destructor finalize");
        JobFence fence;
        expect(destructor_executor.submit(graph, fence) == JobError::None,
               "job08 destructor submit");
    }
    expect(ran.load(std::memory_order_relaxed) <= 16U, "job08 destructor stopped cleanly");
    return finish_case();
}

bool run_job09() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 8;
    budget.max_tasks = 1024;
    expect(executor.start(budget) == JobError::None, "job09 start");

    std::atomic<std::uint32_t> executed{0};
    Recorder commit_order;
    std::array<RecordContext, 64> commit_contexts{};
    TaskGraph graph(64);
    for (std::uint32_t index = 0; index < 64; ++index) {
        commit_contexts[index] = RecordContext{&commit_order, index + 1U};
        expect(graph.add_task(TaskId{index + 1U}, JobPriority::Normal, JobAffinity::AnyWorker,
                              CancellationScope{0}, increment_counter, &executed)
                   == JobError::None,
               "job09 add task");
        expect(graph.add_commit(index + 1U, TaskId{index + 1U}, record_value,
                                &commit_contexts[index])
                   == JobError::None,
               "job09 add commit");
    }
    for (std::uint32_t layer = 1; layer < 8; ++layer) {
        for (std::uint32_t lane = 0; lane < 8; ++lane) {
            const std::uint32_t before = (layer - 1U) * 8U + lane + 1U;
            const std::uint32_t after = layer * 8U + lane + 1U;
            expect(graph.add_dependency(TaskId{before}, TaskId{after}) == JobError::None,
                   "job09 dependency");
        }
    }
    expect(graph.finalize() == JobError::None, "job09 finalize");

    for (std::uint32_t run = 0; run < 20; ++run) {
        commit_order.clear();
        JobFence fence;
        expect(executor.submit(graph, fence) == JobError::None, "job09 submit");
        expect(executor.wait(fence) == JobError::None, "job09 wait");
        const auto values = commit_order.values();
        expect(values.size() == 64U, "job09 commit count");
        for (std::uint32_t index = 0; index < 64U && index < values.size(); ++index) {
            expect(values[index] == index + 1U, "job09 deterministic commit sequence");
        }
    }
    const auto stats = executor.stats();
    expect(stats.submitted == 64U * 20U, "job09 submitted total");
    expect(stats.completed == 64U * 20U, "job09 completed total");
    expect(stats.cancelled == 0U, "job09 cancelled zero");
    expect(stats.failed == 0U, "job09 failed zero");
    expect(executed.load(std::memory_order_relaxed) == 64U * 20U, "job09 task execution total");

    std::array<std::atomic<std::uint32_t>, 10> counters{};
    std::array<JobFence, 10> fences{};
    std::array<TaskGraph, 10> graphs = {{
        TaskGraph(16), TaskGraph(16), TaskGraph(16), TaskGraph(16), TaskGraph(16),
        TaskGraph(16), TaskGraph(16), TaskGraph(16), TaskGraph(16), TaskGraph(16)}};
    for (std::uint32_t job = 0; job < 10; ++job) {
        for (std::uint32_t index = 1; index <= 16; ++index) {
            expect(add_task(graphs[job], index, increment_counter, &counters[job])
                       == JobError::None,
                   "job09 concurrent task");
        }
        expect(graphs[job].finalize() == JobError::None, "job09 concurrent finalize");
        expect(executor.submit(graphs[job], fences[job]) == JobError::None,
               "job09 concurrent submit");
    }
    for (std::uint32_t job = 0; job < 10; ++job) {
        expect(executor.wait(fences[job]) == JobError::None, "job09 concurrent wait");
        expect(counters[job].load(std::memory_order_relaxed) == 16U,
               "job09 concurrent execution");
    }
    expect(executor.stop() == JobError::None, "job09 stop");
    return finish_case();
}

bool run_job10() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 4;
    budget.max_tasks = 1024;
    budget.frame_budget_ns = 0;
    expect(executor.start(budget) == JobError::None, "job10 start");

    std::atomic<std::uint32_t> executed{0};
    std::atomic<std::uint32_t> committed{0};
    TaskGraph graph(128);
    for (std::uint32_t index = 0; index < 128; ++index) {
        expect(graph.add_task(TaskId{index + 1U}, JobPriority::Normal, JobAffinity::AnyWorker,
                              CancellationScope{0}, increment_counter, &executed)
                   == JobError::None,
               "job10 add task");
        expect(graph.add_commit(index + 1U, TaskId{index + 1U}, increment_counter, &committed)
                   == JobError::None,
               "job10 add commit");
    }
    expect(graph.finalize() == JobError::None, "job10 finalize");

    constexpr std::uint32_t runs = 20;
    const auto start = std::chrono::steady_clock::now();
    for (std::uint32_t run = 0; run < runs; ++run) {
        JobFence fence;
        expect(executor.submit(graph, fence) == JobError::None, "job10 submit");
        expect(executor.wait(fence) == JobError::None, "job10 wait");
    }
    const auto end = std::chrono::steady_clock::now();
    const auto elapsed_ns = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    const std::uint64_t total_tasks = static_cast<std::uint64_t>(runs) * 128U;
    const double seconds = static_cast<double>(elapsed_ns) / 1000000000.0;
    const double tasks_per_second = seconds > 0.0 ? static_cast<double>(total_tasks) / seconds : 0.0;
    std::printf("JOB10_BENCH runs=%u tasks_per_run=128 elapsed_ns=%llu tasks_per_second=%.2f\n",
                static_cast<unsigned>(runs),
                static_cast<unsigned long long>(elapsed_ns), tasks_per_second);
    expect(executed.load(std::memory_order_relaxed) == total_tasks, "job10 executed all tasks");
    expect(committed.load(std::memory_order_relaxed) == total_tasks, "job10 committed all tasks");
    expect(executor.stop() == JobError::None, "job10 stop");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core03_jobs_test <job01..job10>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "job01") {
        success = run_job01();
    } else if (mode == "job02") {
        success = run_job02();
    } else if (mode == "job03") {
        success = run_job03();
    } else if (mode == "job04") {
        success = run_job04();
    } else if (mode == "job05") {
        success = run_job05();
    } else if (mode == "job06") {
        success = run_job06();
    } else if (mode == "job07") {
        success = run_job07();
    } else if (mode == "job08") {
        success = run_job08();
    } else if (mode == "job09") {
        success = run_job09();
    } else if (mode == "job10") {
        success = run_job10();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
