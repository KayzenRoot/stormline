#include "stormline/core/jobs/job_executor.hpp"

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

void increment_counter(void* raw) {
    static_cast<std::atomic<std::uint32_t>*>(raw)->fetch_add(1, std::memory_order_relaxed);
}

class Recorder final {
public:
    void push(std::uint32_t value) {
        std::lock_guard<std::mutex> lock(mutex_);
        values_.push_back(value);
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

JobError add_task(TaskGraph& graph, std::uint32_t id, JobPriority priority, JobAffinity affinity,
                  std::uint64_t scope, void* context) {
    return graph.add_task(TaskId{id}, priority, affinity, CancellationScope{scope},
                          increment_counter, context);
}

bool run_qlf01() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 4;
    budget.max_tasks = 64;
    expect(executor.start(budget) == JobError::None, "qlf01 start");

    std::atomic<std::uint32_t> a_ran{0};
    std::atomic<std::uint32_t> b_ran{0};
    std::atomic<std::uint32_t> c_ran{0};
    Recorder commit_order;
    std::array<RecordContext, 3> commit_contexts{};

    TaskGraph job_a(6);
    expect(add_task(job_a, 1, JobPriority::Normal, JobAffinity::AnyWorker, 0, &a_ran)
               == JobError::None,
           "qlf01 a1");
    expect(add_task(job_a, 2, JobPriority::High, JobAffinity::AnyWorker, 0, &a_ran)
               == JobError::None,
           "qlf01 a2");
    expect(add_task(job_a, 3, JobPriority::Normal, JobAffinity::MainThread, 0, &a_ran)
               == JobError::None,
           "qlf01 a3");
    expect(add_task(job_a, 4, JobPriority::FrameCritical, JobAffinity::AnyWorker, 0, &a_ran)
               == JobError::None,
           "qlf01 a4");
    expect(add_task(job_a, 5, JobPriority::Normal, JobAffinity::AnyWorker, 0, &a_ran)
               == JobError::None,
           "qlf01 a5");
    expect(add_task(job_a, 6, JobPriority::Normal, JobAffinity::AnyWorker, 0, &a_ran)
               == JobError::None,
           "qlf01 a6");
    expect(job_a.add_dependency(TaskId{1}, TaskId{2}) == JobError::None, "qlf01 dep 1-2");
    expect(job_a.add_dependency(TaskId{2}, TaskId{3}) == JobError::None, "qlf01 dep 2-3");
    expect(job_a.add_dependency(TaskId{4}, TaskId{5}) == JobError::None, "qlf01 dep 4-5");
    commit_contexts[0] = RecordContext{&commit_order, 30U};
    commit_contexts[1] = RecordContext{&commit_order, 20U};
    commit_contexts[2] = RecordContext{&commit_order, 10U};
    expect(job_a.add_commit(30, TaskId{1}, record_value, &commit_contexts[0]) == JobError::None,
           "qlf01 commit 30");
    expect(job_a.add_commit(20, TaskId{2}, record_value, &commit_contexts[1]) == JobError::None,
           "qlf01 commit 20");
    expect(job_a.add_commit(10, TaskId{3}, record_value, &commit_contexts[2]) == JobError::None,
           "qlf01 commit 10");
    expect(job_a.finalize() == JobError::None, "qlf01 a finalize");

    TaskGraph job_b(3);
    for (std::uint32_t index = 1; index <= 3; ++index) {
        expect(add_task(job_b, index, JobPriority::Normal, JobAffinity::MainThread, 777, &b_ran)
                   == JobError::None,
               "qlf01 b task");
    }
    expect(job_b.finalize() == JobError::None, "qlf01 b finalize");

    TaskGraph job_c(4);
    for (std::uint32_t index = 1; index <= 4; ++index) {
        expect(add_task(job_c, index, JobPriority::Normal, JobAffinity::AnyWorker, 0, &c_ran)
                   == JobError::None,
               "qlf01 c task");
    }
    expect(job_c.finalize() == JobError::None, "qlf01 c finalize");

    JobFence fence_a;
    JobFence fence_b;
    JobFence fence_c;
    expect(executor.submit(job_a, fence_a) == JobError::None, "qlf01 submit a");
    expect(executor.submit(job_b, fence_b) == JobError::None, "qlf01 submit b");
    expect(executor.submit(job_c, fence_c) == JobError::None, "qlf01 submit c");
    expect(executor.request_cancel(CancellationScope{777}) == JobError::None,
           "qlf01 cancel b");
    executor.pump_main_thread();
    expect(executor.wait(fence_a) == JobError::None, "qlf01 wait a");
    expect(executor.wait(fence_b) == JobError::Cancelled, "qlf01 wait b cancelled");
    expect(executor.wait(fence_c) == JobError::None, "qlf01 wait c");

    expect(a_ran.load(std::memory_order_relaxed) == 6U, "qlf01 a ran");
    expect(b_ran.load(std::memory_order_relaxed) == 0U, "qlf01 b never ran");
    expect(c_ran.load(std::memory_order_relaxed) == 4U, "qlf01 c ran");
    const auto commits = commit_order.values();
    expect(commits.size() == 3U, "qlf01 commit count");
    for (std::uint32_t index = 0; index < commits.size(); ++index) {
        expect(commits[index] == (index + 1U) * 10U, "qlf01 commit order");
    }
    const auto stats = executor.stats();
    expect(stats.submitted == 13U, "qlf01 submitted");
    expect(stats.completed == 10U, "qlf01 completed");
    expect(stats.cancelled == 3U, "qlf01 cancelled");
    expect(stats.failed == 0U, "qlf01 failed");
    expect(stats.queue_depth == 0U, "qlf01 queue drained");
    expect(executor.stop() == JobError::None, "qlf01 stop");
    return finish_case();
}

bool run_qlf02() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 8;
    budget.max_tasks = 1024;
    expect(executor.start(budget) == JobError::None, "qlf02 start");

    constexpr std::uint32_t job_count = 100;
    constexpr std::uint32_t tasks_per_job = 100;
    std::array<std::atomic<std::uint32_t>, job_count> counters{};
    std::vector<TaskGraph> graphs;
    graphs.reserve(job_count);
    for (std::uint32_t job = 0; job < job_count; ++job) {
        graphs.emplace_back(tasks_per_job);
        TaskGraph& graph = graphs.back();
        for (std::uint32_t task = 1; task <= tasks_per_job; ++task) {
            expect(add_task(graph, task, JobPriority::Normal, JobAffinity::AnyWorker, 0,
                            &counters[job])
                       == JobError::None,
                   "qlf02 add task");
            if (task > 1U) {
                expect(graph.add_dependency(TaskId{task - 1U}, TaskId{task}) == JobError::None,
                       "qlf02 dependency");
            }
        }
        expect(graph.finalize() == JobError::None, "qlf02 finalize");
    }

    std::array<JobFence, job_count> fences{};
    for (std::uint32_t job = 0; job < job_count; ++job) {
        expect(executor.submit(graphs[job], fences[job]) == JobError::None, "qlf02 submit");
    }
    for (std::uint32_t job = 0; job < job_count; ++job) {
        expect(executor.wait(fences[job]) == JobError::None, "qlf02 wait");
        expect(counters[job].load(std::memory_order_relaxed) == tasks_per_job,
               "qlf02 per-job counter");
    }

    const auto stats = executor.stats();
    const std::uint64_t total = static_cast<std::uint64_t>(job_count) * tasks_per_job;
    expect(stats.submitted == total, "qlf02 submitted 10000");
    expect(stats.completed == total, "qlf02 completed 10000");
    expect(stats.cancelled == 0U, "qlf02 cancelled zero");
    expect(stats.failed == 0U, "qlf02 failed zero");
    expect(stats.queue_depth == 0U, "qlf02 queue drained");
    expect(executor.stop() == JobError::None, "qlf02 stop");
    return finish_case();
}

bool run_qlf03() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 2;
    budget.max_tasks = 16;
    expect(executor.start(budget) == JobError::None, "qlf03 start");

    std::atomic<std::uint32_t> storm_ran{0};
    constexpr std::uint32_t storm_jobs = 20;
    std::vector<TaskGraph> storm_graphs;
    storm_graphs.reserve(storm_jobs);
    std::array<JobFence, storm_jobs> storm_fences{};
    for (std::uint32_t job = 0; job < storm_jobs; ++job) {
        storm_graphs.emplace_back(2);
        TaskGraph& graph = storm_graphs.back();
        expect(add_task(graph, 1, JobPriority::Normal, JobAffinity::MainThread, 1000U + job,
                        &storm_ran)
                   == JobError::None,
               "qlf03 storm task 1");
        expect(add_task(graph, 2, JobPriority::Normal, JobAffinity::MainThread, 1000U + job,
                        &storm_ran)
                   == JobError::None,
               "qlf03 storm task 2");
        expect(graph.finalize() == JobError::None, "qlf03 storm finalize");
        expect(executor.submit(graph, storm_fences[job]) == JobError::None,
               "qlf03 storm submit");
        expect(executor.request_cancel(CancellationScope{1000U + job}) == JobError::None,
               "qlf03 storm cancel");
    }
    expect(executor.drain() == JobError::Cancelled, "qlf03 drain cancelled");
    expect(storm_ran.load(std::memory_order_relaxed) == 0U, "qlf03 storm never ran");

    TaskGraph cycle(2);
    expect(add_task(cycle, 1, JobPriority::Normal, JobAffinity::AnyWorker, 0, &storm_ran)
               == JobError::None,
           "qlf03 cycle task 1");
    expect(add_task(cycle, 2, JobPriority::Normal, JobAffinity::AnyWorker, 0, &storm_ran)
               == JobError::None,
           "qlf03 cycle task 2");
    expect(cycle.add_dependency(TaskId{1}, TaskId{2}) == JobError::None, "qlf03 cycle edge 1");
    expect(cycle.add_dependency(TaskId{2}, TaskId{1}) == JobError::None, "qlf03 cycle edge 2");
    expect(cycle.finalize() == JobError::CycleDetected, "qlf03 cycle detected");
    JobFence cycle_fence;
    expect(executor.submit(cycle, cycle_fence) == JobError::CycleDetected,
           "qlf03 cycle submit rejected");

    TaskGraph zero(0);
    expect(add_task(zero, 1, JobPriority::Normal, JobAffinity::AnyWorker, 0, &storm_ran)
               == JobError::InvalidCapacity,
           "qlf03 zero capacity");
    JobFence zero_fence;
    expect(executor.submit(zero, zero_fence) == JobError::InvalidCapacity,
           "qlf03 zero submit rejected");

    TaskGraph overflow(20);
    for (std::uint32_t index = 1; index <= 20; ++index) {
        expect(add_task(overflow, index, JobPriority::Normal, JobAffinity::AnyWorker, 0,
                        &storm_ran)
                   == JobError::None,
               "qlf03 overflow task");
    }
    expect(overflow.finalize() == JobError::None, "qlf03 overflow finalize");
    JobFence overflow_fence;
    expect(executor.submit(overflow, overflow_fence) == JobError::QueueFull,
           "qlf03 overflow rejected");
    expect(overflow_fence.value == 0U, "qlf03 overflow fence zero");

    TaskGraph small(2);
    for (std::uint32_t index = 1; index <= 2; ++index) {
        expect(add_task(small, index, JobPriority::Normal, JobAffinity::AnyWorker, 0,
                        &storm_ran)
                   == JobError::None,
               "qlf03 small task");
    }
    expect(small.finalize() == JobError::None, "qlf03 small finalize");
    JobFence small_fence;
    expect(executor.submit(small, small_fence) == JobError::None, "qlf03 small submit");
    expect(executor.wait(small_fence) == JobError::None, "qlf03 small wait");
    expect(storm_ran.load(std::memory_order_relaxed) == 2U, "qlf03 small executed");
    expect(executor.stop() == JobError::None, "qlf03 stop");

    JobExecutor replacement;
    WorkBudget replacement_budget;
    replacement_budget.max_workers = 2;
    replacement_budget.max_tasks = 16;
    expect(replacement.start(replacement_budget) == JobError::None, "qlf03 replacement start");
    std::atomic<std::uint32_t> replacement_ran{0};
    TaskGraph replacement_graph(4);
    for (std::uint32_t index = 1; index <= 4; ++index) {
        expect(add_task(replacement_graph, index, JobPriority::Normal, JobAffinity::AnyWorker, 0,
                        &replacement_ran)
                   == JobError::None,
               "qlf03 replacement task");
    }
    expect(replacement_graph.finalize() == JobError::None, "qlf03 replacement finalize");
    JobFence replacement_fence;
    expect(replacement.submit(replacement_graph, replacement_fence) == JobError::None,
           "qlf03 replacement submit");
    expect(replacement.wait(replacement_fence) == JobError::None, "qlf03 replacement wait");
    expect(replacement_ran.load(std::memory_order_relaxed) == 4U,
           "qlf03 replacement executed");
    expect(replacement.stop() == JobError::None, "qlf03 replacement stop");
    return finish_case();
}

bool run_qlf04() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 1;
    budget.max_tasks = 2;
    expect(executor.start(budget) == JobError::None, "qlf04 start");

    std::atomic<std::uint32_t> ran{0};
    TaskGraph overflow(4);
    for (std::uint32_t index = 1; index <= 4; ++index) {
        expect(add_task(overflow, index, JobPriority::Normal, JobAffinity::AnyWorker, 0, &ran)
                   == JobError::None,
               "qlf04 overflow task");
    }
    expect(overflow.finalize() == JobError::None, "qlf04 overflow finalize");
    for (std::uint32_t attempt = 0; attempt < 10U; ++attempt) {
        JobFence fence;
        expect(executor.submit(overflow, fence) == JobError::QueueFull,
               "qlf04 overflow rejected");
        expect(fence.value == 0U, "qlf04 overflow fence zero");
    }
    auto stats = executor.stats();
    expect(stats.submitted == 0U, "qlf04 overflow no submission");
    expect(stats.queue_depth == 0U, "qlf04 overflow no queue");
    expect(ran.load(std::memory_order_relaxed) == 0U, "qlf04 overflow no execution");

    TaskGraph fit(2);
    for (std::uint32_t index = 1; index <= 2; ++index) {
        expect(add_task(fit, index, JobPriority::Normal, JobAffinity::AnyWorker, 0, &ran)
                   == JobError::None,
               "qlf04 fit task");
    }
    expect(fit.finalize() == JobError::None, "qlf04 fit finalize");
    JobFence fit_fence;
    expect(executor.submit(fit, fit_fence) == JobError::None, "qlf04 fit submit");
    expect(executor.wait(fit_fence) == JobError::None, "qlf04 fit wait");
    expect(ran.load(std::memory_order_relaxed) == 2U, "qlf04 fit executed");
    stats = executor.stats();
    expect(stats.submitted == 2U, "qlf04 fit submitted");
    expect(stats.completed == 2U, "qlf04 fit completed");
    expect(executor.stop() == JobError::None, "qlf04 stop");
    return finish_case();
}

bool run_qlf05() {
    begin_case();
    JobExecutor executor;
    WorkBudget budget;
    budget.max_workers = 4;
    budget.max_tasks = 256;
    budget.frame_budget_ns = 0;
    expect(executor.start(budget) == JobError::None, "qlf05 start");

    std::atomic<std::uint32_t> executed{0};
    TaskGraph graph(128);
    for (std::uint32_t index = 1; index <= 128; ++index) {
        expect(add_task(graph, index, JobPriority::Normal, JobAffinity::AnyWorker, 0, &executed)
                   == JobError::None,
               "qlf05 add task");
    }
    expect(graph.finalize() == JobError::None, "qlf05 finalize");

    constexpr std::uint32_t runs = 20;
    const auto start = std::chrono::steady_clock::now();
    for (std::uint32_t run = 0; run < runs; ++run) {
        JobFence fence;
        expect(executor.submit(graph, fence) == JobError::None, "qlf05 submit");
        expect(executor.wait(fence) == JobError::None, "qlf05 wait");
    }
    const auto end = std::chrono::steady_clock::now();
    const auto elapsed_ns = static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    const std::uint64_t total_tasks = static_cast<std::uint64_t>(runs) * 128U;
    const double seconds = static_cast<double>(elapsed_ns) / 1000000000.0;
    const double tasks_per_second = seconds > 0.0 ? static_cast<double>(total_tasks) / seconds : 0.0;
    std::printf("QLF05_BENCH runs=%u tasks_per_run=128 elapsed_ns=%llu tasks_per_second=%.2f\n",
                static_cast<unsigned>(runs),
                static_cast<unsigned long long>(elapsed_ns), tasks_per_second);
    expect(executed.load(std::memory_order_relaxed) == total_tasks, "qlf05 executed total");
    expect(executor.stats().completed == total_tasks, "qlf05 completed total");
    expect(executor.stop() == JobError::None, "qlf05 stop");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: stormline_core03_qualification_test <qlf01..qlf05>\n");
        return 2;
    }
    const std::string_view mode(argv[1]);
    bool success = false;
    if (mode == "qlf01") {
        success = run_qlf01();
    } else if (mode == "qlf02") {
        success = run_qlf02();
    } else if (mode == "qlf03") {
        success = run_qlf03();
    } else if (mode == "qlf04") {
        success = run_qlf04();
    } else if (mode == "qlf05") {
        success = run_qlf05();
    } else {
        std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
        return 2;
    }
    return success ? 0 : 1;
}
