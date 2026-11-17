#include "stormline/core/internal/lifecycle.hpp"

#if defined(SDL_h_)
#error "SDL header/type leaked through the CORE-01 lifecycle header"
#endif

#include <cstdint>
#include <cstdio>
#include <string_view>
#include <thread>

namespace {

using stormline::core::internal::InputEvent;
using stormline::core::internal::InputEventType;
using stormline::core::internal::LifecycleController;
using stormline::core::internal::LifecycleError;
using stormline::core::internal::LifecycleState;

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

InputEvent make_event(InputEventType type) {
    InputEvent event{};
    event.type = type;
    return event;
}

bool run_normal() {
    begin_case();
    LifecycleController lifecycle;
    expect(lifecycle.state() == LifecycleState::Running, "fresh lifecycle is running");
    expect(lifecycle.should_continue(), "running lifecycle continues");

    expect(lifecycle.request_suspend() == LifecycleError::None, "request suspend succeeds");
    expect(lifecycle.state() == LifecycleState::SuspendPending, "suspend is pending");
    expect(lifecycle.should_continue(), "pending suspend continues");
    expect(lifecycle.acknowledge_suspend() == LifecycleError::None, "acknowledge suspend succeeds");
    expect(lifecycle.state() == LifecycleState::Suspended, "lifecycle is suspended");
    expect(lifecycle.should_continue(), "suspended lifecycle continues");

    expect(lifecycle.request_resume() == LifecycleError::None, "request resume succeeds");
    expect(lifecycle.state() == LifecycleState::ResumePending, "resume is pending");
    expect(lifecycle.acknowledge_resume() == LifecycleError::None, "acknowledge resume succeeds");
    expect(lifecycle.state() == LifecycleState::Running, "lifecycle is running again");
    expect(lifecycle.should_continue(), "resumed lifecycle continues");
    return finish_case();
}

bool run_shutdown() {
    begin_case();
    for (LifecycleState start : {LifecycleState::Running, LifecycleState::SuspendPending,
                                 LifecycleState::Suspended, LifecycleState::ResumePending}) {
        LifecycleController lifecycle;
        if (start == LifecycleState::SuspendPending) {
            expect(lifecycle.request_suspend() == LifecycleError::None, "setup suspend pending");
        } else if (start == LifecycleState::Suspended) {
            expect(lifecycle.request_suspend() == LifecycleError::None, "setup suspend");
            expect(lifecycle.acknowledge_suspend() == LifecycleError::None, "setup suspended");
        } else if (start == LifecycleState::ResumePending) {
            expect(lifecycle.request_suspend() == LifecycleError::None, "setup suspend");
            expect(lifecycle.acknowledge_suspend() == LifecycleError::None, "setup suspended");
            expect(lifecycle.request_resume() == LifecycleError::None, "setup resume pending");
        }
        expect(lifecycle.request_shutdown() == LifecycleError::None, "request shutdown succeeds");
        expect(lifecycle.state() == LifecycleState::ShutdownPending, "shutdown is pending");
        expect(!lifecycle.should_continue(), "shutdown pending stops continuation");
        expect(lifecycle.request_shutdown() == LifecycleError::None, "repeated shutdown is idempotent");
        expect(lifecycle.acknowledge_shutdown() == LifecycleError::None, "acknowledge shutdown succeeds");
        expect(lifecycle.state() == LifecycleState::Terminated, "lifecycle is terminated");
        expect(lifecycle.acknowledge_shutdown() == LifecycleError::AlreadyTerminated,
               "repeated acknowledge is already terminated");
        expect(lifecycle.request_shutdown() == LifecycleError::AlreadyTerminated,
               "shutdown after termination is rejected");
    }
    return finish_case();
}

bool run_events() {
    begin_case();
    LifecycleController quit;
    expect(quit.observe(make_event(InputEventType::Quit)) == LifecycleError::None,
           "quit event is accepted");
    expect(quit.state() == LifecycleState::ShutdownPending, "quit requests shutdown");

    LifecycleController close;
    expect(close.observe(make_event(InputEventType::WindowCloseRequested)) == LifecycleError::None,
           "close-requested event is accepted");
    expect(close.state() == LifecycleState::ShutdownPending, "close requests shutdown");

    LifecycleController key;
    expect(key.observe(make_event(InputEventType::KeyDown)) == LifecycleError::None,
           "key event is ignored");
    expect(key.state() == LifecycleState::Running, "ignored event leaves state running");
    expect(key.observe(make_event(InputEventType::None)) == LifecycleError::None,
           "none event is ignored");
    expect(key.state() == LifecycleState::Running, "none event leaves state running");
    return finish_case();
}

bool run_invalid() {
    begin_case();
    LifecycleController lifecycle;
    expect(lifecycle.acknowledge_suspend() == LifecycleError::InvalidTransition,
           "acknowledge suspend while running is invalid");
    expect(lifecycle.state() == LifecycleState::Running, "invalid transition leaves running");
    expect(lifecycle.request_resume() == LifecycleError::InvalidTransition,
           "resume while running is invalid");
    expect(lifecycle.acknowledge_resume() == LifecycleError::InvalidTransition,
           "acknowledge resume while running is invalid");
    expect(lifecycle.acknowledge_shutdown() == LifecycleError::InvalidTransition,
           "acknowledge shutdown while running is invalid");
    expect(lifecycle.state() == LifecycleState::Running, "state remains running");

    expect(lifecycle.request_suspend() == LifecycleError::None, "request suspend succeeds");
    expect(lifecycle.request_suspend() == LifecycleError::InvalidTransition,
           "duplicate suspend is invalid");
    expect(lifecycle.request_shutdown() == LifecycleError::None, "shutdown from suspend pending");
    expect(lifecycle.request_suspend() == LifecycleError::InvalidTransition,
           "suspend after shutdown is invalid");
    expect(lifecycle.request_terminate() == LifecycleError::None, "terminate succeeds");
    expect(lifecycle.state() == LifecycleState::Terminated, "terminate reaches terminated");
    expect(lifecycle.request_terminate() == LifecycleError::AlreadyTerminated,
           "repeated terminate is already terminated");
    expect(lifecycle.request_suspend() == LifecycleError::InvalidTransition,
           "suspend after terminate is invalid");
    return finish_case();
}

bool run_wrong_thread() {
    begin_case();
    LifecycleController lifecycle;
    LifecycleError suspend = LifecycleError::None;
    LifecycleError resume = LifecycleError::None;
    LifecycleError shutdown = LifecycleError::None;
    LifecycleError observe = LifecycleError::None;
    std::thread worker([&lifecycle, &suspend, &resume, &shutdown, &observe] {
        suspend = lifecycle.request_suspend();
        resume = lifecycle.request_resume();
        shutdown = lifecycle.request_shutdown();
        observe = lifecycle.observe(make_event(InputEventType::Quit));
    });
    worker.join();
    expect(suspend == LifecycleError::WrongThread, "worker suspend is rejected");
    expect(resume == LifecycleError::WrongThread, "worker resume is rejected");
    expect(shutdown == LifecycleError::WrongThread, "worker shutdown is rejected");
    expect(observe == LifecycleError::WrongThread, "worker observe is rejected");
    expect(lifecycle.state() == LifecycleState::Running, "worker calls leave state running");
    expect(lifecycle.should_continue(), "worker calls leave lifecycle continuing");
    return finish_case();
}

bool run_recovery() {
    begin_case();
    LifecycleController lifecycle;
    bool ok = true;
    for (int cycle = 0; cycle < 100 && ok; ++cycle) {
        ok = lifecycle.request_suspend() == LifecycleError::None;
        ok = ok && lifecycle.acknowledge_suspend() == LifecycleError::None;
        ok = ok && lifecycle.request_resume() == LifecycleError::None;
        ok = ok && lifecycle.acknowledge_resume() == LifecycleError::None;
        ok = ok && lifecycle.state() == LifecycleState::Running;
    }
    expect(ok, "100 suspend/resume cycles succeed");
    expect(lifecycle.request_shutdown() == LifecycleError::None, "shutdown after recovery");
    expect(lifecycle.acknowledge_shutdown() == LifecycleError::None, "acknowledge final shutdown");
    expect(lifecycle.state() == LifecycleState::Terminated, "final state is terminated");
    expect(!lifecycle.should_continue(), "terminated lifecycle stops");
    return finish_case();
}

}  // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: %s <normal|shutdown|events|invalid|wrong_thread|recovery>\n",
                     argv[0]);
        return 2;
    }

    const std::string_view mode(argv[1]);
    if (mode == "normal") {
        return run_normal() ? 0 : 1;
    }
    if (mode == "shutdown") {
        return run_shutdown() ? 0 : 1;
    }
    if (mode == "events") {
        return run_events() ? 0 : 1;
    }
    if (mode == "invalid") {
        return run_invalid() ? 0 : 1;
    }
    if (mode == "wrong_thread") {
        return run_wrong_thread() ? 0 : 1;
    }
    if (mode == "recovery") {
        return run_recovery() ? 0 : 1;
    }

    std::fprintf(stderr, "unknown mode: %s\n", argv[1]);
    return 2;
}
