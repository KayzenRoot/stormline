#include "stormline/core/jobs/task_graph.hpp"

#include <array>
#include <cstddef>

namespace stormline::core::jobs {
namespace {

constexpr std::uint32_t word_index(std::uint32_t slot) noexcept {
    return slot / 64U;
}

constexpr std::uint64_t bit_mask(std::uint32_t slot) noexcept {
    return std::uint64_t{1} << (slot % 64U);
}

}  // namespace

TaskGraph::TaskGraph(std::uint32_t tasks) noexcept {
    if (tasks == 0U || tasks > capacity) {
        construction_error_ = JobError::InvalidCapacity;
        return;
    }
    size_limit_ = tasks;
}

std::uint32_t TaskGraph::find_task(TaskId id) const noexcept {
    for (std::uint32_t index = 0; index < task_count_; ++index) {
        if (tasks_[index].id.value == id.value) {
            return index;
        }
    }
    return capacity;
}

bool TaskGraph::has_edge(std::uint32_t before, std::uint32_t after) const noexcept {
    return (edges_[before].words[word_index(after)] & bit_mask(after)) != 0U;
}

void TaskGraph::set_edge(std::uint32_t before, std::uint32_t after) noexcept {
    edges_[before].words[word_index(after)] |= bit_mask(after);
}

JobError TaskGraph::add_task(TaskId id, JobPriority priority, JobAffinity affinity,
                             CancellationScope scope, JobFunction function,
                             void* context) noexcept {
    if (construction_error_ != JobError::None) {
        return construction_error_;
    }
    if (finalized_) {
        return JobError::InvalidGraph;
    }
    if (id.value == 0U || function == nullptr || priority > JobPriority::FrameCritical
        || affinity > JobAffinity::MainThread) {
        return JobError::InvalidTask;
    }
    if (find_task(id) != capacity) {
        return JobError::InvalidTask;
    }
    if (task_count_ >= size_limit_) {
        return JobError::ResourceExhausted;
    }
    TaskRecord& record = tasks_[task_count_];
    record.id = id;
    record.priority = priority;
    record.affinity = affinity;
    record.scope = scope;
    record.function = function;
    record.context = context;
    ++task_count_;
    return JobError::None;
}

JobError TaskGraph::add_dependency(TaskId before, TaskId after) noexcept {
    if (construction_error_ != JobError::None) {
        return construction_error_;
    }
    if (finalized_) {
        return JobError::InvalidGraph;
    }
    const std::uint32_t before_index = find_task(before);
    const std::uint32_t after_index = find_task(after);
    if (before_index == capacity || after_index == capacity || before_index == after_index) {
        return JobError::InvalidGraph;
    }
    if (has_edge(before_index, after_index)) {
        return JobError::InvalidGraph;
    }
    set_edge(before_index, after_index);
    return JobError::None;
}

JobError TaskGraph::add_commit(std::uint32_t order, TaskId task,
                               CommitFunction function, void* context) noexcept {
    if (construction_error_ != JobError::None) {
        return construction_error_;
    }
    if (finalized_) {
        return JobError::InvalidGraph;
    }
    if (function == nullptr) {
        return JobError::InvalidTask;
    }
    const std::uint32_t task_index = find_task(task);
    if (task_index == capacity) {
        return JobError::InvalidTask;
    }
    for (std::uint32_t index = 0; index < commit_count_; ++index) {
        if (commits_[index].order == order) {
            return JobError::InvalidGraph;
        }
    }
    if (commit_count_ >= capacity) {
        return JobError::ResourceExhausted;
    }
    CommitRecord& record = commits_[commit_count_];
    record.order = order;
    record.task = task;
    record.function = function;
    record.context = context;
    ++commit_count_;
    return JobError::None;
}

JobError TaskGraph::finalize() noexcept {
    if (construction_error_ != JobError::None) {
        return construction_error_;
    }
    if (finalized_) {
        return validation_error_;
    }
    finalized_ = true;

    std::array<std::uint16_t, capacity> indegree{};
    for (std::uint32_t before = 0; before < task_count_; ++before) {
        for (std::uint32_t after = 0; after < task_count_; ++after) {
            if (has_edge(before, after)) {
                ++indegree[after];
            }
        }
    }

    std::array<std::uint16_t, capacity> queue{};
    std::uint32_t head = 0;
    std::uint32_t tail = 0;
    for (std::uint32_t index = 0; index < task_count_; ++index) {
        if (indegree[index] == 0U) {
            queue[tail] = static_cast<std::uint16_t>(index);
            ++tail;
        }
    }

    std::uint32_t processed = 0;
    while (head < tail) {
        const std::uint32_t current = queue[head];
        ++head;
        ++processed;
        for (std::uint32_t after = 0; after < task_count_; ++after) {
            if (!has_edge(current, after)) {
                continue;
            }
            --indegree[after];
            if (indegree[after] == 0U) {
                queue[tail] = static_cast<std::uint16_t>(after);
                ++tail;
            }
        }
    }

    if (processed != task_count_) {
        validation_error_ = JobError::CycleDetected;
        return validation_error_;
    }
    valid_ = true;
    return JobError::None;
}

bool TaskGraph::valid() const noexcept {
    return valid_;
}

}  // namespace stormline::core::jobs
