#pragma once

#include "stormline/core/jobs/task_graph.hpp"

#include <memory>

namespace stormline::core::jobs {

class JobExecutor final {
public:
    static constexpr std::uint32_t max_workers = 32;

    JobExecutor() noexcept;
    ~JobExecutor() noexcept;

    JobExecutor(const JobExecutor&) = delete;
    JobExecutor& operator=(const JobExecutor&) = delete;
    JobExecutor(JobExecutor&&) = delete;
    JobExecutor& operator=(JobExecutor&&) = delete;

    [[nodiscard]] JobError start(WorkBudget budget) noexcept;
    [[nodiscard]] JobError submit(const TaskGraph& graph, JobFence& fence) noexcept;
    [[nodiscard]] JobError request_cancel(CancellationScope scope) noexcept;
    [[nodiscard]] JobError wait(JobFence fence) noexcept;
    [[nodiscard]] JobError drain() noexcept;
    [[nodiscard]] JobError stop() noexcept;
    [[nodiscard]] ExecutorState state() const noexcept;
    [[nodiscard]] ExecutorStats stats() const noexcept;
    void pump_main_thread() noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}  // namespace stormline::core::jobs
