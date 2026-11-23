cmake_minimum_required(VERSION 3.27)
project(stormline_core01_internal LANGUAGES C CXX)

option(STORMLINE_CORE01_ENABLE_SANITIZERS "Enable ASan/UBSan for the internal CORE-01 slice" OFF)
option(STORMLINE_CORE02_ALLOC_BENCH "Build the optional isolated CORE-02 allocator benchmark" OFF)
option(STORMLINE_CORE03_ENABLE_TSAN "Enable ThreadSanitizer for the internal CORE-03 slice" OFF)

if(STORMLINE_CORE01_ENABLE_SANITIZERS AND STORMLINE_CORE03_ENABLE_TSAN)
    message(FATAL_ERROR "ASan/UBSan and TSan cannot be enabled in the same build")
endif()

function(stormline_core_internal_apply_tsan target)
    if(STORMLINE_CORE03_ENABLE_TSAN)
        if(MSVC)
            message(FATAL_ERROR "ThreadSanitizer is not enabled for the MSVC internal slice")
        endif()
        target_compile_options(${target} PRIVATE -fsanitize=thread -fno-omit-frame-pointer)
        target_link_options(${target} PRIVATE -fsanitize=thread)
    endif()
endfunction()

function(stormline_core01_apply_options target scope)
    target_compile_features(${target} ${scope} cxx_std_20)
    set_target_properties(${target} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
    )
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    if(STORMLINE_CORE01_ENABLE_SANITIZERS)
        if(MSVC)
            message(FATAL_ERROR "Sanitizers are not enabled for the MSVC internal slice")
        endif()
        target_compile_options(${target} PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
        )
        target_link_options(${target} PRIVATE
            -fsanitize=address,undefined
        )
    endif()
endfunction()

include(FetchContent)

# Pinned official SDL3 3.4.20 source, fetched at build time only. No system
# install, vendor copy, package manager or runtime download.
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL_AUDIO OFF CACHE BOOL "" FORCE)
set(SDL_JOYSTICK OFF CACHE BOOL "" FORCE)
set(SDL_HAPTIC OFF CACHE BOOL "" FORCE)
set(SDL_HIDAPI OFF CACHE BOOL "" FORCE)
set(SDL_SENSOR OFF CACHE BOOL "" FORCE)
set(SDL_POWER OFF CACHE BOOL "" FORCE)
set(SDL_CAMERA OFF CACHE BOOL "" FORCE)
set(SDL_X11 ON CACHE BOOL "" FORCE)
set(SDL_WAYLAND ON CACHE BOOL "" FORCE)
set(SDL_KMSDRM OFF CACHE BOOL "" FORCE)
if(STORMLINE_CORE02_ALLOC_BENCH)
    # The isolated benchmark does not create windows; allow SDL configuration
    # on Linux runners without X11/Wayland development packages.
    set(SDL_UNIX_CONSOLE_BUILD ON CACHE BOOL "" FORCE)
else()
    set(SDL_UNIX_CONSOLE_BUILD OFF CACHE BOOL "" FORCE)
endif()
set(SDL_RENDER OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_GPU OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_VULKAN OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_METAL OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_D3D OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_D3D11 OFF CACHE BOOL "" FORCE)
set(SDL_RENDER_D3D12 OFF CACHE BOOL "" FORCE)
set(SDL_VULKAN OFF CACHE BOOL "" FORCE)
set(SDL_OPENGL OFF CACHE BOOL "" FORCE)
set(SDL_OPENGLES OFF CACHE BOOL "" FORCE)
set(SDL_METAL OFF CACHE BOOL "" FORCE)
set(SDL_GPU OFF CACHE BOOL "" FORCE)
set(SDL_DUMMYAUDIO OFF CACHE BOOL "" FORCE)
set(SDL_DISKAUDIO OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG f00dc919ca35b9756316e86c4777392de442f9b2
    GIT_SHALLOW FALSE
)
FetchContent_MakeAvailable(SDL3)

if(TARGET SDL3::SDL3-static)
    get_target_property(SDL3_INTERFACE_INCLUDES SDL3::SDL3-static INTERFACE_INCLUDE_DIRECTORIES)
    if(SDL3_INTERFACE_INCLUDES)
        set_property(TARGET SDL3::SDL3-static PROPERTY
            INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${SDL3_INTERFACE_INCLUDES}")
    endif()
endif()

add_library(stormline_core01_headless STATIC
    src/stormline/core/internal/headless_host.cpp
)
target_include_directories(stormline_core01_headless PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
stormline_core01_apply_options(stormline_core01_headless PUBLIC)

add_library(stormline_core01_paths STATIC
    src/stormline/core/internal/process_paths.cpp
)
target_include_directories(stormline_core01_paths PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
stormline_core01_apply_options(stormline_core01_paths PUBLIC)

add_executable(stormline_core01_headless_test
    tests/core/headless_host_tests.cpp
)
target_link_libraries(stormline_core01_headless_test PRIVATE stormline_core01_headless)
stormline_core01_apply_options(stormline_core01_headless_test PRIVATE)

add_executable(stormline_core01_paths_test
    tests/core/process_paths_tests.cpp
)
target_link_libraries(stormline_core01_paths_test PRIVATE stormline_core01_paths)
stormline_core01_apply_options(stormline_core01_paths_test PRIVATE)

add_library(stormline_core01_sdl STATIC
    src/stormline/core/internal/sdl_runtime.cpp
)
target_include_directories(stormline_core01_sdl PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_core01_sdl PRIVATE SDL3::SDL3-static)
stormline_core01_apply_options(stormline_core01_sdl PUBLIC)

add_executable(stormline_core01_sdl_test
    tests/core/sdl_runtime_tests.cpp
)
target_link_libraries(stormline_core01_sdl_test PRIVATE stormline_core01_sdl)
stormline_core01_apply_options(stormline_core01_sdl_test PRIVATE)

add_library(stormline_core01_window STATIC
    src/stormline/core/internal/window.cpp
)
target_include_directories(stormline_core01_window PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_core01_window PRIVATE SDL3::SDL3-static)
stormline_core01_apply_options(stormline_core01_window PUBLIC)

add_executable(stormline_core01_window_test
    tests/core/window_tests.cpp
)
target_link_libraries(stormline_core01_window_test PRIVATE
    stormline_core01_window
    stormline_core01_sdl
)
stormline_core01_apply_options(stormline_core01_window_test PRIVATE)

add_library(stormline_core01_event_queue STATIC
    src/stormline/core/internal/event_queue.cpp
)
target_include_directories(stormline_core01_event_queue PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_core01_event_queue PRIVATE SDL3::SDL3-static)
stormline_core01_apply_options(stormline_core01_event_queue PUBLIC)

add_executable(stormline_core01_event_queue_test
    tests/core/event_queue_tests.cpp
)
target_link_libraries(stormline_core01_event_queue_test PRIVATE
    stormline_core01_event_queue
    stormline_core01_sdl
    SDL3::SDL3-static
)
stormline_core01_apply_options(stormline_core01_event_queue_test PRIVATE)

add_library(stormline_core01_display STATIC
    src/stormline/core/internal/display.cpp
)
target_include_directories(stormline_core01_display PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_core01_display PRIVATE SDL3::SDL3-static)
stormline_core01_apply_options(stormline_core01_display PUBLIC)

add_executable(stormline_core01_display_test
    tests/core/display_tests.cpp
)
target_link_libraries(stormline_core01_display_test PRIVATE
    stormline_core01_display
    stormline_core01_window
    stormline_core01_sdl
    SDL3::SDL3-static
)
stormline_core01_apply_options(stormline_core01_display_test PRIVATE)

add_library(stormline_core01_native_bridge STATIC
    src/stormline/core/internal/native_bridge.cpp
)
target_include_directories(stormline_core01_native_bridge PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_core01_native_bridge PRIVATE SDL3::SDL3-static)
stormline_core01_apply_options(stormline_core01_native_bridge PUBLIC)

add_executable(stormline_core01_native_bridge_test
    tests/core/native_bridge_tests.cpp
)
target_link_libraries(stormline_core01_native_bridge_test PRIVATE
    stormline_core01_native_bridge
    stormline_core01_window
    stormline_core01_sdl
    SDL3::SDL3-static
)
stormline_core01_apply_options(stormline_core01_native_bridge_test PRIVATE)

add_library(stormline_core01_lifecycle STATIC
    src/stormline/core/internal/lifecycle.cpp
)
target_include_directories(stormline_core01_lifecycle PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
stormline_core01_apply_options(stormline_core01_lifecycle PUBLIC)

add_executable(stormline_core01_lifecycle_test
    tests/core/lifecycle_tests.cpp
)
target_link_libraries(stormline_core01_lifecycle_test PRIVATE stormline_core01_lifecycle)
stormline_core01_apply_options(stormline_core01_lifecycle_test PRIVATE)

add_library(stormline_core01_capability_graph STATIC
    src/stormline/core/internal/capability_graph.cpp
)
target_include_directories(stormline_core01_capability_graph PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_core01_capability_graph PRIVATE SDL3::SDL3-static)
stormline_core01_apply_options(stormline_core01_capability_graph PUBLIC)

add_executable(stormline_core01_capability_graph_test
    tests/core/capability_graph_tests.cpp
)
target_link_libraries(stormline_core01_capability_graph_test PRIVATE
    stormline_core01_capability_graph
    stormline_core01_sdl
    SDL3::SDL3-static
)
stormline_core01_apply_options(stormline_core01_capability_graph_test PRIVATE)

add_executable(stormline_core01_soak_test
    tests/core/core01_soak_tests.cpp
)
target_link_libraries(stormline_core01_soak_test PRIVATE
    stormline_core01_headless
    stormline_core01_sdl
    stormline_core01_window
    stormline_core01_event_queue
    stormline_core01_display
    stormline_core01_native_bridge
    stormline_core01_lifecycle
    stormline_core01_capability_graph
    SDL3::SDL3-static
)
stormline_core01_apply_options(stormline_core01_soak_test PRIVATE)

add_executable(stormline_core01_qualification_test
    tests/core/core01_qualification_tests.cpp
)
target_link_libraries(stormline_core01_qualification_test PRIVATE
    stormline_core01_headless
    stormline_core01_sdl
    stormline_core01_window
    stormline_core01_event_queue
    stormline_core01_display
    stormline_core01_native_bridge
    stormline_core01_lifecycle
    stormline_core01_capability_graph
    SDL3::SDL3-static
)
stormline_core01_apply_options(stormline_core01_qualification_test PRIVATE)

# NLE-CORE01-QUAL-001: test-only, exploratory runtime measurements. The
# post-build receipt is required because standard CI CTest hides PASS stdout.
add_executable(stormline_core01_runtime_baseline_test
    tests/core/core01_runtime_baseline_tests.cpp
)
target_link_libraries(stormline_core01_runtime_baseline_test PRIVATE
    stormline_core01_headless
    stormline_core01_sdl
    stormline_core01_window
    SDL3::SDL3-static
)
if(WIN32)
    target_link_libraries(stormline_core01_runtime_baseline_test PRIVATE Psapi)
endif()
stormline_core01_apply_options(stormline_core01_runtime_baseline_test PRIVATE)
add_custom_command(TARGET stormline_core01_runtime_baseline_test POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E sha256sum
        "$<TARGET_FILE:stormline_core01_runtime_baseline_test>"
    COMMAND "$<TARGET_FILE:stormline_core01_runtime_baseline_test>" baseline
    COMMENT "CORE-01 exploratory runtime samples and executable SHA256 (NOT acceptance)"
    VERBATIM
)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_custom_command(TARGET stormline_core01_runtime_baseline_test POST_BUILD
        COMMAND "$<TARGET_FILE:stormline_core01_runtime_baseline_test>" no-display
        COMMENT "CORE-01 Linux fail-closed missing-display proof"
        VERBATIM
    )
endif()

# NLE-CORE01-QUAL-002: additive internal ABI fixture and native binary receipts.
# This does not establish an external ABI or minimum supported platform.
add_executable(stormline_core01_abi_portability_test
    tests/core/core01_abi_portability_tests.cpp
)
target_link_libraries(stormline_core01_abi_portability_test PRIVATE
    stormline_core01_window
    stormline_core01_sdl
    SDL3::SDL3-static
)
stormline_core01_apply_options(stormline_core01_abi_portability_test PRIVATE)
add_custom_command(TARGET stormline_core01_abi_portability_test POST_BUILD
    COMMAND "$<TARGET_FILE:stormline_core01_abi_portability_test>" positive
    COMMAND "${CMAKE_COMMAND}"
        "-DSTORM_ABI_BINARY=$<TARGET_FILE:stormline_core01_abi_portability_test>"
        "-DSTORM_ABI_PLATFORM=${CMAKE_SYSTEM_NAME}"
        "-DSTORM_ABI_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}"
        "-DSTORM_ABI_COMPILER_VERSION=${CMAKE_CXX_COMPILER_VERSION}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/core01_abi_probe.cmake"
    COMMENT "CORE-01 internal C++20 ABI observations and native PE/ELF/Mach-O evidence"
    VERBATIM
)

add_library(stormline_core02_telemetry STATIC
    src/stormline/core/memory/memory_telemetry.cpp
)
target_include_directories(stormline_core02_telemetry PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
stormline_core01_apply_options(stormline_core02_telemetry PUBLIC)

add_library(stormline_core02_memory STATIC
    src/stormline/core/memory/memory_block.cpp
)
target_include_directories(stormline_core02_memory PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_core02_memory PUBLIC stormline_core02_telemetry)
stormline_core01_apply_options(stormline_core02_memory PUBLIC)

add_executable(stormline_core02_memory_test
    tests/core/memory_block_tests.cpp
)
target_link_libraries(stormline_core02_memory_test PRIVATE stormline_core02_memory)
stormline_core01_apply_options(stormline_core02_memory_test PRIVATE)

add_library(stormline_core02_system_allocator STATIC
    src/stormline/core/memory/system_memory_resource.cpp
)
target_include_directories(stormline_core02_system_allocator PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
stormline_core01_apply_options(stormline_core02_system_allocator PUBLIC)

add_executable(stormline_core02_system_allocator_test
    tests/core/system_memory_resource_tests.cpp
)
target_link_libraries(stormline_core02_system_allocator_test PRIVATE
    stormline_core02_system_allocator
    stormline_core02_memory
)
stormline_core01_apply_options(stormline_core02_system_allocator_test PRIVATE)

add_library(stormline_core02_arena STATIC
    src/stormline/core/memory/monotonic_arena.cpp
)
target_include_directories(stormline_core02_arena PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_core02_arena PRIVATE stormline_core02_memory)
stormline_core01_apply_options(stormline_core02_arena PUBLIC)

add_executable(stormline_core02_arena_test
    tests/core/monotonic_arena_tests.cpp
)
target_link_libraries(stormline_core02_arena_test PRIVATE
    stormline_core02_arena
    stormline_core02_memory
)
stormline_core01_apply_options(stormline_core02_arena_test PRIVATE)

add_library(stormline_core02_budget STATIC
    src/stormline/core/memory/memory_budget.cpp
)
target_include_directories(stormline_core02_budget PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_core02_budget PUBLIC stormline_core02_telemetry)
stormline_core01_apply_options(stormline_core02_budget PUBLIC)

add_executable(stormline_core02_budget_test
    tests/core/memory_budget_tests.cpp
)
target_link_libraries(stormline_core02_budget_test PRIVATE stormline_core02_budget)
stormline_core01_apply_options(stormline_core02_budget_test PRIVATE)

add_library(stormline_core02_leak STATIC
    src/stormline/core/memory/leak_tracker.cpp
)
target_include_directories(stormline_core02_leak PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_core02_leak PUBLIC stormline_core02_telemetry)
stormline_core01_apply_options(stormline_core02_leak PUBLIC)

add_executable(stormline_core02_leak_test
    tests/core/leak_tracker_tests.cpp
)
target_link_libraries(stormline_core02_leak_test PRIVATE stormline_core02_leak)
stormline_core01_apply_options(stormline_core02_leak_test PRIVATE)

if(STORMLINE_CORE02_ALLOC_BENCH)
    find_package(Threads REQUIRED)

    # Optional, isolated benchmark dependencies. Never linked into production
    # engine targets and never allowed to override global allocation.
    set(MI_OVERRIDE OFF CACHE BOOL "" FORCE)
    set(MI_BUILD_SHARED OFF CACHE BOOL "" FORCE)
    set(MI_BUILD_STATIC ON CACHE BOOL "" FORCE)
    set(MI_BUILD_OBJECT OFF CACHE BOOL "" FORCE)
    set(MI_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(MI_OSX_INTERPOSE OFF CACHE BOOL "" FORCE)
    set(MI_OSX_ZONE OFF CACHE BOOL "" FORCE)
    set(MI_WIN_REDIRECT OFF CACHE BOOL "" FORCE)
    set(MI_STATS OFF CACHE STRING "" FORCE)
    set(MI_PROFILE OFF CACHE STRING "" FORCE)
    set(MI_USE_CXX OFF CACHE STRING "" FORCE)
    FetchContent_Declare(
        mimalloc
        GIT_REPOSITORY https://github.com/microsoft/mimalloc.git
        GIT_TAG 1ed67b5156a763441d2ec3c20221a7b3cd866129
        GIT_SHALLOW FALSE
    )
    FetchContent_MakeAvailable(mimalloc)

    FetchContent_Declare(
        rpmalloc
        GIT_REPOSITORY https://github.com/mjansson/rpmalloc.git
        GIT_TAG beef233c176b235587c0145f765e4316e5ca60d1
        GIT_SHALLOW FALSE
    )
    FetchContent_MakeAvailable(rpmalloc)
    add_library(stormline_rpmalloc STATIC
        "${rpmalloc_SOURCE_DIR}/rpmalloc/rpmalloc.c"
    )
    target_include_directories(stormline_rpmalloc PUBLIC
        "${rpmalloc_SOURCE_DIR}/rpmalloc"
    )
    target_compile_definitions(stormline_rpmalloc PRIVATE ENABLE_OVERRIDE=0)
    set_target_properties(stormline_rpmalloc PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
    )
    if(MSVC)
        target_compile_options(stormline_rpmalloc PRIVATE /experimental:c11atomics)
    endif()
    target_link_libraries(stormline_rpmalloc PUBLIC Threads::Threads)

    add_executable(stormline_core02_allocator_bench
        benchmarks/core02/allocator_compare.cpp
    )
    target_include_directories(stormline_core02_allocator_bench PRIVATE
        "${rpmalloc_SOURCE_DIR}/rpmalloc"
    )
    target_link_libraries(stormline_core02_allocator_bench PRIVATE
        stormline_core02_memory
        stormline_core02_system_allocator
        mimalloc-static
        stormline_rpmalloc
        Threads::Threads
    )
    stormline_core01_apply_options(stormline_core02_allocator_bench PRIVATE)
endif()

add_executable(stormline_core02_telemetry_test
    tests/core/memory_telemetry_tests.cpp
)
target_link_libraries(stormline_core02_telemetry_test PRIVATE
    stormline_core02_telemetry
    stormline_core02_memory
    stormline_core02_system_allocator
    stormline_core02_arena
    stormline_core02_budget
    stormline_core02_leak
)
stormline_core01_apply_options(stormline_core02_telemetry_test PRIVATE)

if(WIN32)
    add_executable(stormline_core02_fake_allocator_bench
        tests/core/fake_allocator_bench.cpp
    )
    stormline_core01_apply_options(stormline_core02_fake_allocator_bench PRIVATE)

    add_executable(stormline_core02_q4_profile_runner
        benchmarks/core02/q4_profile_runner.cpp
    )
    stormline_core01_apply_options(stormline_core02_q4_profile_runner PRIVATE)
endif()

add_executable(stormline_core02_qualification_test
    tests/core/core02_memory_qualification_tests.cpp
)
target_link_libraries(stormline_core02_qualification_test PRIVATE
    stormline_core02_telemetry
    stormline_core02_memory
    stormline_core02_system_allocator
    stormline_core02_arena
    stormline_core02_budget
    stormline_core02_leak
)
stormline_core01_apply_options(stormline_core02_qualification_test PRIVATE)

find_package(Threads REQUIRED)

add_library(stormline_core03_jobs STATIC
    src/stormline/core/jobs/task_graph.cpp
    src/stormline/core/jobs/job_executor.cpp
)
target_include_directories(stormline_core03_jobs PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_core03_jobs PUBLIC Threads::Threads)
stormline_core01_apply_options(stormline_core03_jobs PUBLIC)
stormline_core_internal_apply_tsan(stormline_core03_jobs)

add_executable(stormline_core03_jobs_test
    tests/core/job_executor_tests.cpp
)
target_link_libraries(stormline_core03_jobs_test PRIVATE stormline_core03_jobs)
stormline_core01_apply_options(stormline_core03_jobs_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core03_jobs_test)

add_executable(stormline_core03_qualification_test
    tests/core/core03_jobs_qualification_tests.cpp
)
target_link_libraries(stormline_core03_qualification_test PRIVATE stormline_core03_jobs)
stormline_core01_apply_options(stormline_core03_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core03_qualification_test)

add_library(stormline_core04_time STATIC
    src/stormline/core/time/clock_source.cpp
    src/stormline/core/time/timeline.cpp
)
target_include_directories(stormline_core04_time PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
stormline_core01_apply_options(stormline_core04_time PUBLIC)
stormline_core_internal_apply_tsan(stormline_core04_time)

add_executable(stormline_core04_clock_test
    tests/core/clock_source_tests.cpp
)
target_link_libraries(stormline_core04_clock_test PRIVATE stormline_core04_time)
stormline_core01_apply_options(stormline_core04_clock_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core04_clock_test)

add_executable(stormline_core04_timeline_test
    tests/core/timeline_tests.cpp
)
target_link_libraries(stormline_core04_timeline_test PRIVATE stormline_core04_time)
stormline_core01_apply_options(stormline_core04_timeline_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core04_timeline_test)

add_executable(stormline_core04_qualification_test
    tests/core/core04_time_qualification_tests.cpp
)
target_link_libraries(stormline_core04_qualification_test PRIVATE stormline_core04_time)
stormline_core01_apply_options(stormline_core04_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core04_qualification_test)

add_library(stormline_core05_math INTERFACE)
target_include_directories(stormline_core05_math INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_features(stormline_core05_math INTERFACE cxx_std_20)

add_executable(stormline_core05_vector_test
    tests/core/core05_vector_tests.cpp
)
target_link_libraries(stormline_core05_vector_test PRIVATE stormline_core05_math)
stormline_core01_apply_options(stormline_core05_vector_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core05_vector_test)

add_executable(stormline_core05_matrix_quat_test
    tests/core/core05_matrix_quat_tests.cpp
)
target_link_libraries(stormline_core05_matrix_quat_test PRIVATE stormline_core05_math)
stormline_core01_apply_options(stormline_core05_matrix_quat_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core05_matrix_quat_test)

add_executable(stormline_core05_coord_test
    tests/core/core05_coord_tests.cpp
)
target_link_libraries(stormline_core05_coord_test PRIVATE stormline_core05_math)
stormline_core01_apply_options(stormline_core05_coord_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core05_coord_test)

add_executable(stormline_core05_unit_test
    tests/core/core05_unit_tests.cpp
)
target_link_libraries(stormline_core05_unit_test PRIVATE stormline_core05_math)
stormline_core01_apply_options(stormline_core05_unit_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core05_unit_test)

add_executable(stormline_core05_precision_test
    tests/core/core05_precision_tests.cpp
)
target_link_libraries(stormline_core05_precision_test PRIVATE stormline_core05_math)
stormline_core01_apply_options(stormline_core05_precision_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core05_precision_test)

add_executable(stormline_core05_id_test
    tests/core/core05_id_tests.cpp
)
target_link_libraries(stormline_core05_id_test PRIVATE stormline_core05_math)
stormline_core01_apply_options(stormline_core05_id_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core05_id_test)

add_executable(stormline_core05_qualification_test
    tests/core/core05_qualification_tests.cpp
)
target_link_libraries(stormline_core05_qualification_test PRIVATE stormline_core05_math)
stormline_core01_apply_options(stormline_core05_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core05_qualification_test)

add_library(stormline_core06_diag INTERFACE)
target_include_directories(stormline_core06_diag INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_features(stormline_core06_diag INTERFACE cxx_std_20)

add_executable(stormline_core06_log_test
    tests/core/core06_log_tests.cpp
)
target_link_libraries(stormline_core06_log_test PRIVATE stormline_core06_diag)
stormline_core01_apply_options(stormline_core06_log_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core06_log_test)

add_executable(stormline_core06_trace_test
    tests/core/core06_trace_tests.cpp
)
target_link_libraries(stormline_core06_trace_test PRIVATE stormline_core06_diag)
stormline_core01_apply_options(stormline_core06_trace_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core06_trace_test)

add_executable(stormline_core06_counter_test
    tests/core/core06_counter_tests.cpp
)
target_link_libraries(stormline_core06_counter_test PRIVATE stormline_core06_diag)
stormline_core01_apply_options(stormline_core06_counter_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core06_counter_test)

add_executable(stormline_core06_crash_test
    tests/core/core06_crash_tests.cpp
)
target_link_libraries(stormline_core06_crash_test PRIVATE stormline_core06_diag)
stormline_core01_apply_options(stormline_core06_crash_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core06_crash_test)

add_executable(stormline_core06_profile_test
    tests/core/core06_profile_tests.cpp
)
target_link_libraries(stormline_core06_profile_test PRIVATE stormline_core06_diag)
stormline_core01_apply_options(stormline_core06_profile_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core06_profile_test)

add_executable(stormline_core06_telemetry_test
    tests/core/core06_telemetry_tests.cpp
)
target_link_libraries(stormline_core06_telemetry_test PRIVATE stormline_core06_diag)
stormline_core01_apply_options(stormline_core06_telemetry_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core06_telemetry_test)

add_executable(stormline_core06_qualification_test
    tests/core/core06_diagnostics_qualification_tests.cpp
)
target_link_libraries(stormline_core06_qualification_test PRIVATE stormline_core06_diag)
stormline_core01_apply_options(stormline_core06_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_core06_qualification_test)

add_library(stormline_data01_vfs INTERFACE)
target_include_directories(stormline_data01_vfs INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_features(stormline_data01_vfs INTERFACE cxx_std_20)

add_library(stormline_gfx01_rhi INTERFACE)
target_include_directories(stormline_gfx01_rhi INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_features(stormline_gfx01_rhi INTERFACE cxx_std_20)

add_library(stormline_gfx02_shader INTERFACE)
target_include_directories(stormline_gfx02_shader INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_features(stormline_gfx02_shader INTERFACE cxx_std_20)

add_library(stormline_gfx03_graph INTERFACE)
target_include_directories(stormline_gfx03_graph INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_gfx03_graph INTERFACE stormline_gfx01_rhi)
target_compile_features(stormline_gfx03_graph INTERFACE cxx_std_20)

add_library(stormline_gfx04_geometry INTERFACE)
target_include_directories(stormline_gfx04_geometry INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_features(stormline_gfx04_geometry INTERFACE cxx_std_20)

add_library(stormline_gfx05_material INTERFACE)
target_include_directories(stormline_gfx05_material INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_features(stormline_gfx05_material INTERFACE cxx_std_20)

add_library(stormline_gfx06_lighting INTERFACE)
target_include_directories(stormline_gfx06_lighting INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_features(stormline_gfx06_lighting INTERFACE cxx_std_20)

add_library(stormline_data05_bundle INTERFACE)
target_include_directories(stormline_data05_bundle INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_data05_bundle INTERFACE stormline_data02_registry)
target_compile_features(stormline_data05_bundle INTERFACE cxx_std_20)

add_library(stormline_data04_scene INTERFACE)
target_include_directories(stormline_data04_scene INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_data04_scene INTERFACE stormline_data02_registry)
target_compile_features(stormline_data04_scene INTERFACE cxx_std_20)

add_library(stormline_data03_import INTERFACE)
target_include_directories(stormline_data03_import INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_data03_import INTERFACE stormline_data02_registry stormline_data01_vfs)
target_compile_features(stormline_data03_import INTERFACE cxx_std_20)

add_library(stormline_data02_registry INTERFACE)
target_include_directories(stormline_data02_registry INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(stormline_data02_registry INTERFACE stormline_data01_vfs)
target_compile_features(stormline_data02_registry INTERFACE cxx_std_20)

add_executable(stormline_data01_path_test
    tests/core/data01_path_tests.cpp
)
target_link_libraries(stormline_data01_path_test PRIVATE stormline_data01_vfs)
stormline_core01_apply_options(stormline_data01_path_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data01_path_test)

add_executable(stormline_data01_mount_test
    tests/core/data01_mount_tests.cpp
)
target_link_libraries(stormline_data01_mount_test PRIVATE stormline_data01_vfs)
stormline_core01_apply_options(stormline_data01_mount_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data01_mount_test)

add_executable(stormline_data01_overlay_test
    tests/core/data01_overlay_tests.cpp
)
target_link_libraries(stormline_data01_overlay_test PRIVATE stormline_data01_vfs)
stormline_core01_apply_options(stormline_data01_overlay_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data01_overlay_test)

add_executable(stormline_data01_capability_test
    tests/core/data01_capability_tests.cpp
)
target_link_libraries(stormline_data01_capability_test PRIVATE stormline_data01_vfs)
stormline_core01_apply_options(stormline_data01_capability_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data01_capability_test)

add_executable(stormline_data01_cache_test
    tests/core/data01_cache_tests.cpp
)
target_link_libraries(stormline_data01_cache_test PRIVATE stormline_data01_vfs)
stormline_core01_apply_options(stormline_data01_cache_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data01_cache_test)

add_executable(stormline_data01_storage_test
    tests/core/data01_storage_tests.cpp
)
target_link_libraries(stormline_data01_storage_test PRIVATE stormline_data01_vfs)
stormline_core01_apply_options(stormline_data01_storage_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data01_storage_test)

add_executable(stormline_data01_vfs_qualification_test
    tests/core/data01_vfs_qualification_tests.cpp
)
target_link_libraries(stormline_data01_vfs_qualification_test PRIVATE stormline_data01_vfs)
stormline_core01_apply_options(stormline_data01_vfs_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data01_vfs_qualification_test)

add_executable(stormline_data02_id_test
    tests/core/data02_id_tests.cpp
)
target_link_libraries(stormline_data02_id_test PRIVATE stormline_data02_registry)
stormline_core01_apply_options(stormline_data02_id_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data02_id_test)

add_executable(stormline_data02_dependency_test
    tests/core/data02_dependency_tests.cpp
)
target_link_libraries(stormline_data02_dependency_test PRIVATE stormline_data02_registry)
stormline_core01_apply_options(stormline_data02_dependency_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data02_dependency_test)

add_executable(stormline_data02_tag_test
    tests/core/data02_tag_tests.cpp
)
target_link_libraries(stormline_data02_tag_test PRIVATE stormline_data02_registry)
stormline_core01_apply_options(stormline_data02_tag_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data02_tag_test)

add_executable(stormline_data02_query_test
    tests/core/data02_query_tests.cpp
)
target_link_libraries(stormline_data02_query_test PRIVATE stormline_data02_registry)
stormline_core01_apply_options(stormline_data02_query_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data02_query_test)

add_executable(stormline_data02_schema_test
    tests/core/data02_schema_tests.cpp
)
target_link_libraries(stormline_data02_schema_test PRIVATE stormline_data02_registry)
stormline_core01_apply_options(stormline_data02_schema_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data02_schema_test)

add_executable(stormline_data02_reference_test
    tests/core/data02_reference_tests.cpp
)
target_link_libraries(stormline_data02_reference_test PRIVATE stormline_data02_registry)
stormline_core01_apply_options(stormline_data02_reference_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data02_reference_test)

add_executable(stormline_data02_registry_qualification_test
    tests/core/data02_registry_qualification_tests.cpp
)
target_link_libraries(stormline_data02_registry_qualification_test PRIVATE stormline_data02_registry)
stormline_core01_apply_options(stormline_data02_registry_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data02_registry_qualification_test)

add_executable(stormline_data03_importer_test
    tests/core/data03_importer_tests.cpp
)
target_link_libraries(stormline_data03_importer_test PRIVATE stormline_data03_import)
stormline_core01_apply_options(stormline_data03_importer_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data03_importer_test)

add_executable(stormline_data03_texture_test
    tests/core/data03_texture_tests.cpp
)
target_link_libraries(stormline_data03_texture_test PRIVATE stormline_data03_import)
stormline_core01_apply_options(stormline_data03_texture_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data03_texture_test)

add_executable(stormline_data03_animation_test
    tests/core/data03_animation_tests.cpp
)
target_link_libraries(stormline_data03_animation_test PRIVATE stormline_data03_import)
stormline_core01_apply_options(stormline_data03_animation_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data03_animation_test)

add_executable(stormline_data03_audio_test
    tests/core/data03_audio_tests.cpp
)
target_link_libraries(stormline_data03_audio_test PRIVATE stormline_data03_import)
stormline_core01_apply_options(stormline_data03_audio_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data03_audio_test)

add_executable(stormline_data03_validation_test
    tests/core/data03_validation_tests.cpp
)
target_link_libraries(stormline_data03_validation_test PRIVATE stormline_data03_import)
stormline_core01_apply_options(stormline_data03_validation_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data03_validation_test)

add_executable(stormline_data03_receipt_test
    tests/core/data03_receipt_tests.cpp
)
target_link_libraries(stormline_data03_receipt_test PRIVATE stormline_data03_import)
stormline_core01_apply_options(stormline_data03_receipt_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data03_receipt_test)

add_executable(stormline_data03_import_qualification_test
    tests/core/data03_import_qualification_tests.cpp
)
target_link_libraries(stormline_data03_import_qualification_test PRIVATE stormline_data03_import)
stormline_core01_apply_options(stormline_data03_import_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data03_import_qualification_test)

add_executable(stormline_data04_schema_test
    tests/core/data04_schema_tests.cpp
)
target_link_libraries(stormline_data04_schema_test PRIVATE stormline_data04_scene)
stormline_core01_apply_options(stormline_data04_schema_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data04_schema_test)

add_executable(stormline_data04_document_test
    tests/core/data04_document_tests.cpp
)
target_link_libraries(stormline_data04_document_test PRIVATE stormline_data04_scene)
stormline_core01_apply_options(stormline_data04_document_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data04_document_test)

add_executable(stormline_data04_patch_test
    tests/core/data04_patch_tests.cpp
)
target_link_libraries(stormline_data04_patch_test PRIVATE stormline_data04_scene)
stormline_core01_apply_options(stormline_data04_patch_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data04_patch_test)

add_executable(stormline_data04_diff_test
    tests/core/data04_diff_tests.cpp
)
target_link_libraries(stormline_data04_diff_test PRIVATE stormline_data04_scene)
stormline_core01_apply_options(stormline_data04_diff_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data04_diff_test)

add_executable(stormline_data04_scene_qualification_test
    tests/core/data04_scene_qualification_tests.cpp
)
target_link_libraries(stormline_data04_scene_qualification_test PRIVATE stormline_data04_scene)
stormline_core01_apply_options(stormline_data04_scene_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data04_scene_qualification_test)

add_executable(stormline_data05_target_test
    tests/core/data05_target_tests.cpp
)
target_link_libraries(stormline_data05_target_test PRIVATE stormline_data05_bundle)
stormline_core01_apply_options(stormline_data05_target_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data05_target_test)

add_executable(stormline_data05_rle_test
    tests/core/data05_rle_tests.cpp
)
target_link_libraries(stormline_data05_rle_test PRIVATE stormline_data05_bundle)
stormline_core01_apply_options(stormline_data05_rle_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data05_rle_test)

add_executable(stormline_data05_stream_test
    tests/core/data05_stream_tests.cpp
)
target_link_libraries(stormline_data05_stream_test PRIVATE stormline_data05_bundle)
stormline_core01_apply_options(stormline_data05_stream_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data05_stream_test)

add_executable(stormline_data05_manifest_test
    tests/core/data05_manifest_tests.cpp
)
target_link_libraries(stormline_data05_manifest_test PRIVATE stormline_data05_bundle)
stormline_core01_apply_options(stormline_data05_manifest_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data05_manifest_test)

add_executable(stormline_data05_patch_test
    tests/core/data05_patch_tests.cpp
)
target_link_libraries(stormline_data05_patch_test PRIVATE stormline_data05_bundle)
stormline_core01_apply_options(stormline_data05_patch_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data05_patch_test)

add_executable(stormline_data05_bundle_qualification_test
    tests/core/data05_bundle_qualification_tests.cpp
)
target_link_libraries(stormline_data05_bundle_qualification_test PRIVATE stormline_data05_bundle)
stormline_core01_apply_options(stormline_data05_bundle_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_data05_bundle_qualification_test)

add_executable(stormline_gfx01_device_test
    tests/core/gfx01_device_tests.cpp
)
target_link_libraries(stormline_gfx01_device_test PRIVATE stormline_gfx01_rhi)
stormline_core01_apply_options(stormline_gfx01_device_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx01_device_test)

add_executable(stormline_gfx01_queue_test
    tests/core/gfx01_queue_tests.cpp
)
target_link_libraries(stormline_gfx01_queue_test PRIVATE stormline_gfx01_rhi)
stormline_core01_apply_options(stormline_gfx01_queue_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx01_queue_test)

add_executable(stormline_gfx01_buffer_test
    tests/core/gfx01_buffer_tests.cpp
)
target_link_libraries(stormline_gfx01_buffer_test PRIVATE stormline_gfx01_rhi)
stormline_core01_apply_options(stormline_gfx01_buffer_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx01_buffer_test)

add_executable(stormline_gfx01_texture_test
    tests/core/gfx01_texture_tests.cpp
)
target_link_libraries(stormline_gfx01_texture_test PRIVATE stormline_gfx01_rhi)
stormline_core01_apply_options(stormline_gfx01_texture_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx01_texture_test)

add_executable(stormline_gfx01_sync_test
    tests/core/gfx01_sync_tests.cpp
)
target_link_libraries(stormline_gfx01_sync_test PRIVATE stormline_gfx01_rhi)
stormline_core01_apply_options(stormline_gfx01_sync_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx01_sync_test)

add_executable(stormline_gfx01_feature_test
    tests/core/gfx01_feature_tests.cpp
)
target_link_libraries(stormline_gfx01_feature_test PRIVATE stormline_gfx01_rhi)
stormline_core01_apply_options(stormline_gfx01_feature_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx01_feature_test)

add_executable(stormline_gfx01_rhi_qualification_test
    tests/core/gfx01_rhi_qualification_tests.cpp
)
target_link_libraries(stormline_gfx01_rhi_qualification_test PRIVATE stormline_gfx01_rhi)
stormline_core01_apply_options(stormline_gfx01_rhi_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx01_rhi_qualification_test)

add_executable(stormline_gfx02_shader_test
    tests/core/gfx02_shader_tests.cpp
)
target_link_libraries(stormline_gfx02_shader_test PRIVATE stormline_gfx02_shader)
stormline_core01_apply_options(stormline_gfx02_shader_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx02_shader_test)

add_executable(stormline_gfx02_reflection_test
    tests/core/gfx02_reflection_tests.cpp
)
target_link_libraries(stormline_gfx02_reflection_test PRIVATE stormline_gfx02_shader)
stormline_core01_apply_options(stormline_gfx02_reflection_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx02_reflection_test)

add_executable(stormline_gfx02_variant_test
    tests/core/gfx02_variant_tests.cpp
)
target_link_libraries(stormline_gfx02_variant_test PRIVATE stormline_gfx02_shader)
stormline_core01_apply_options(stormline_gfx02_variant_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx02_variant_test)

add_executable(stormline_gfx02_cache_test
    tests/core/gfx02_cache_tests.cpp
)
target_link_libraries(stormline_gfx02_cache_test PRIVATE stormline_gfx02_shader)
stormline_core01_apply_options(stormline_gfx02_cache_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx02_cache_test)

add_executable(stormline_gfx02_incremental_test
    tests/core/gfx02_incremental_tests.cpp
)
target_link_libraries(stormline_gfx02_incremental_test PRIVATE stormline_gfx02_shader)
stormline_core01_apply_options(stormline_gfx02_incremental_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx02_incremental_test)

add_executable(stormline_gfx02_shader_qualification_test
    tests/core/gfx02_shader_qualification_tests.cpp
)
target_link_libraries(stormline_gfx02_shader_qualification_test PRIVATE stormline_gfx02_shader)
stormline_core01_apply_options(stormline_gfx02_shader_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx02_shader_qualification_test)

add_executable(stormline_gfx03_graph_test
    tests/core/gfx03_graph_tests.cpp
)
target_link_libraries(stormline_gfx03_graph_test PRIVATE stormline_gfx03_graph)
stormline_core01_apply_options(stormline_gfx03_graph_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx03_graph_test)

add_executable(stormline_gfx03_dependency_test
    tests/core/gfx03_dependency_tests.cpp
)
target_link_libraries(stormline_gfx03_dependency_test PRIVATE stormline_gfx03_graph)
stormline_core01_apply_options(stormline_gfx03_dependency_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx03_dependency_test)

add_executable(stormline_gfx03_sync_test
    tests/core/gfx03_sync_tests.cpp
)
target_link_libraries(stormline_gfx03_sync_test PRIVATE stormline_gfx03_graph)
stormline_core01_apply_options(stormline_gfx03_sync_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx03_sync_test)

add_executable(stormline_gfx03_transient_test
    tests/core/gfx03_transient_tests.cpp
)
target_link_libraries(stormline_gfx03_transient_test PRIVATE stormline_gfx03_graph)
stormline_core01_apply_options(stormline_gfx03_transient_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx03_transient_test)

add_executable(stormline_gfx03_budget_test
    tests/core/gfx03_budget_tests.cpp
)
target_link_libraries(stormline_gfx03_budget_test PRIVATE stormline_gfx03_graph)
stormline_core01_apply_options(stormline_gfx03_budget_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx03_budget_test)

add_executable(stormline_gfx03_graph_qualification_test
    tests/core/gfx03_graph_qualification_tests.cpp
)
target_link_libraries(stormline_gfx03_graph_qualification_test PRIVATE stormline_gfx03_graph)
stormline_core01_apply_options(stormline_gfx03_graph_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx03_graph_qualification_test)

add_executable(stormline_gfx04_instance_test
    tests/core/gfx04_instance_tests.cpp
)
target_link_libraries(stormline_gfx04_instance_test PRIVATE stormline_gfx04_geometry)
stormline_core01_apply_options(stormline_gfx04_instance_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx04_instance_test)

add_executable(stormline_gfx04_cull_test
    tests/core/gfx04_cull_tests.cpp
)
target_link_libraries(stormline_gfx04_cull_test PRIVATE stormline_gfx04_geometry)
stormline_core01_apply_options(stormline_gfx04_cull_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx04_cull_test)

add_executable(stormline_gfx04_lod_test
    tests/core/gfx04_lod_tests.cpp
)
target_link_libraries(stormline_gfx04_lod_test PRIVATE stormline_gfx04_geometry)
stormline_core01_apply_options(stormline_gfx04_lod_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx04_lod_test)

add_executable(stormline_gfx04_stream_test
    tests/core/gfx04_stream_tests.cpp
)
target_link_libraries(stormline_gfx04_stream_test PRIVATE stormline_gfx04_geometry)
stormline_core01_apply_options(stormline_gfx04_stream_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx04_stream_test)

add_executable(stormline_gfx04_vegetation_test
    tests/core/gfx04_vegetation_tests.cpp
)
target_link_libraries(stormline_gfx04_vegetation_test PRIVATE stormline_gfx04_geometry)
stormline_core01_apply_options(stormline_gfx04_vegetation_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx04_vegetation_test)

add_executable(stormline_gfx04_budget_test
    tests/core/gfx04_budget_tests.cpp
)
target_link_libraries(stormline_gfx04_budget_test PRIVATE stormline_gfx04_geometry)
stormline_core01_apply_options(stormline_gfx04_budget_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx04_budget_test)

add_executable(stormline_gfx04_geometry_qualification_test
    tests/core/gfx04_geometry_qualification_tests.cpp
)
target_link_libraries(stormline_gfx04_geometry_qualification_test PRIVATE stormline_gfx04_geometry)
stormline_core01_apply_options(stormline_gfx04_geometry_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx04_geometry_qualification_test)

add_executable(stormline_gfx05_material_test
    tests/core/gfx05_material_tests.cpp
)
target_link_libraries(stormline_gfx05_material_test PRIVATE stormline_gfx05_material)
stormline_core01_apply_options(stormline_gfx05_material_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx05_material_test)

add_executable(stormline_gfx05_texture_test
    tests/core/gfx05_texture_tests.cpp
)
target_link_libraries(stormline_gfx05_texture_test PRIVATE stormline_gfx05_material)
stormline_core01_apply_options(stormline_gfx05_texture_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx05_texture_test)

add_executable(stormline_gfx05_mip_test
    tests/core/gfx05_mip_tests.cpp
)
target_link_libraries(stormline_gfx05_mip_test PRIVATE stormline_gfx05_material)
stormline_core01_apply_options(stormline_gfx05_mip_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx05_mip_test)

add_executable(stormline_gfx05_sampler_test
    tests/core/gfx05_sampler_tests.cpp
)
target_link_libraries(stormline_gfx05_sampler_test PRIVATE stormline_gfx05_material)
stormline_core01_apply_options(stormline_gfx05_sampler_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx05_sampler_test)

add_executable(stormline_gfx05_decal_test
    tests/core/gfx05_decal_tests.cpp
)
target_link_libraries(stormline_gfx05_decal_test PRIVATE stormline_gfx05_material)
stormline_core01_apply_options(stormline_gfx05_decal_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx05_decal_test)

add_executable(stormline_gfx05_transparency_test
    tests/core/gfx05_transparency_tests.cpp
)
target_link_libraries(stormline_gfx05_transparency_test PRIVATE stormline_gfx05_material)
stormline_core01_apply_options(stormline_gfx05_transparency_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx05_transparency_test)

add_executable(stormline_gfx05_material_qualification_test
    tests/core/gfx05_material_qualification_tests.cpp
)
target_link_libraries(stormline_gfx05_material_qualification_test PRIVATE stormline_gfx05_material)
stormline_core01_apply_options(stormline_gfx05_material_qualification_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx05_material_qualification_test)

add_executable(stormline_gfx06_light_test
    tests/core/gfx06_light_tests.cpp
)
target_link_libraries(stormline_gfx06_light_test PRIVATE stormline_gfx06_lighting)
stormline_core01_apply_options(stormline_gfx06_light_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx06_light_test)

add_executable(stormline_gfx06_shadow_test
    tests/core/gfx06_shadow_tests.cpp
)
target_link_libraries(stormline_gfx06_shadow_test PRIVATE stormline_gfx06_lighting)
stormline_core01_apply_options(stormline_gfx06_shadow_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx06_shadow_test)

add_executable(stormline_gfx06_gi_test
    tests/core/gfx06_gi_tests.cpp
)
target_link_libraries(stormline_gfx06_gi_test PRIVATE stormline_gfx06_lighting)
stormline_core01_apply_options(stormline_gfx06_gi_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx06_gi_test)

add_executable(stormline_gfx06_probe_test
    tests/core/gfx06_probe_tests.cpp
)
target_link_libraries(stormline_gfx06_probe_test PRIVATE stormline_gfx06_lighting)
stormline_core01_apply_options(stormline_gfx06_probe_test PRIVATE)
stormline_core_internal_apply_tsan(stormline_gfx06_probe_test)

enable_testing()

add_test(NAME core01_headless_lifecycle
    COMMAND stormline_core01_headless_test lifecycle
)
add_test(NAME core01_headless_errors
    COMMAND stormline_core01_headless_test errors
)
add_test(NAME core01_headless_cleanup
    COMMAND stormline_core01_headless_test cleanup
)
add_test(NAME core01_headless_destructor
    COMMAND stormline_core01_headless_test destructor
)
add_test(NAME core01_headless_invalid
    COMMAND stormline_core01_headless_test invalid
)

add_test(NAME core01_paths_basic
    COMMAND stormline_core01_paths_test basic
)
add_test(NAME core01_paths_unicode
    COMMAND stormline_core01_paths_test unicode
)
add_test(NAME core01_paths_traversal
    COMMAND stormline_core01_paths_test traversal
)
add_test(NAME core01_paths_errors
    COMMAND stormline_core01_paths_test errors
)
add_test(NAME core01_paths_no_write
    COMMAND stormline_core01_paths_test no_write
)
add_test(NAME core01_paths_symlink
    COMMAND stormline_core01_paths_test symlink
)
add_test(NAME core01_paths_access
    COMMAND stormline_core01_paths_test access
)

add_test(NAME core01_sdl_basic
    COMMAND stormline_core01_sdl_test basic
)
add_test(NAME core01_sdl_wrong_thread
    COMMAND stormline_core01_sdl_test wrong_thread
)
add_test(NAME core01_sdl_init_failure
    COMMAND stormline_core01_sdl_test init_failure
)
add_test(NAME core01_sdl_destructor
    COMMAND stormline_core01_sdl_test destructor
)
add_test(NAME core01_sdl_version
    COMMAND stormline_core01_sdl_test version
)
add_test(NAME core01_sdl_header
    COMMAND stormline_core01_sdl_test header
)

add_test(NAME core01_window_basic
    COMMAND stormline_core01_window_test basic
)
add_test(NAME core01_window_invalid
    COMMAND stormline_core01_window_test invalid
)
add_test(NAME core01_window_wrong_thread
    COMMAND stormline_core01_window_test wrong_thread
)
add_test(NAME core01_window_not_initialized
    COMMAND stormline_core01_window_test not_initialized
)
add_test(NAME core01_window_lifetime
    COMMAND stormline_core01_window_test lifetime
)

add_test(NAME core01_events_basic
    COMMAND stormline_core01_event_queue_test basic
)
add_test(NAME core01_events_sequence
    COMMAND stormline_core01_event_queue_test sequence
)
add_test(NAME core01_events_overflow
    COMMAND stormline_core01_event_queue_test overflow
)
add_test(NAME core01_events_replay
    COMMAND stormline_core01_event_queue_test replay
)
add_test(NAME core01_events_wrong_thread
    COMMAND stormline_core01_event_queue_test wrong_thread
)
add_test(NAME core01_events_not_initialized
    COMMAND stormline_core01_event_queue_test not_initialized
)
add_test(NAME core01_events_empty_clear
    COMMAND stormline_core01_event_queue_test empty_clear
)
add_test(NAME core01_events_lifetime
    COMMAND stormline_core01_event_queue_test lifetime
)

add_test(NAME core01_display_displays
    COMMAND stormline_core01_display_test displays
)
add_test(NAME core01_display_errors
    COMMAND stormline_core01_display_test errors
)
add_test(NAME core01_display_wrong_thread
    COMMAND stormline_core01_display_test wrong_thread
)
add_test(NAME core01_display_surface
    COMMAND stormline_core01_display_test surface
)
add_test(NAME core01_display_surface_errors
    COMMAND stormline_core01_display_test surface_errors
)
add_test(NAME core01_display_stability
    COMMAND stormline_core01_display_test stability
)
add_test(NAME core01_display_lifetime
    COMMAND stormline_core01_display_test lifetime
)

add_test(NAME core01_native_system
    COMMAND stormline_core01_native_bridge_test system
)
add_test(NAME core01_native_handle
    COMMAND stormline_core01_native_bridge_test handle
)
add_test(NAME core01_native_unavailable
    COMMAND stormline_core01_native_bridge_test unavailable
)
add_test(NAME core01_native_errors
    COMMAND stormline_core01_native_bridge_test errors
)
add_test(NAME core01_native_wrong_thread
    COMMAND stormline_core01_native_bridge_test wrong_thread
)
add_test(NAME core01_native_lifetime
    COMMAND stormline_core01_native_bridge_test lifetime
)

add_test(NAME core01_lifecycle_normal
    COMMAND stormline_core01_lifecycle_test normal
)
add_test(NAME core01_lifecycle_shutdown
    COMMAND stormline_core01_lifecycle_test shutdown
)
add_test(NAME core01_lifecycle_events
    COMMAND stormline_core01_lifecycle_test events
)
add_test(NAME core01_lifecycle_invalid
    COMMAND stormline_core01_lifecycle_test invalid
)
add_test(NAME core01_lifecycle_wrong_thread
    COMMAND stormline_core01_lifecycle_test wrong_thread
)
add_test(NAME core01_lifecycle_recovery
    COMMAND stormline_core01_lifecycle_test recovery
)

add_test(NAME core01_capability_states
    COMMAND stormline_core01_capability_graph_test states
)
add_test(NAME core01_capability_uninitialized
    COMMAND stormline_core01_capability_graph_test uninitialized
)
add_test(NAME core01_capability_dummy
    COMMAND stormline_core01_capability_graph_test dummy
)
add_test(NAME core01_capability_real
    COMMAND stormline_core01_capability_graph_test real
)
add_test(NAME core01_capability_wrong_thread
    COMMAND stormline_core01_capability_graph_test wrong_thread
)
add_test(NAME core01_capability_benchmark
    COMMAND stormline_core01_capability_graph_test benchmark
)
add_test(NAME core01_soak
    COMMAND stormline_core01_soak_test soak
)
add_test(NAME core01_qualification
    COMMAND stormline_core01_qualification_test qualify
)
add_test(NAME core01_runtime_baseline
    COMMAND stormline_core01_runtime_baseline_test baseline
)
add_test(NAME core01_runtime_baseline_selftest
    COMMAND stormline_core01_runtime_baseline_test selftest
)
set_tests_properties(core01_runtime_baseline core01_runtime_baseline_selftest
    PROPERTIES TIMEOUT 300
)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_test(NAME core01_runtime_no_display
        COMMAND stormline_core01_runtime_baseline_test no-display
    )
    set_tests_properties(core01_runtime_no_display
        PROPERTIES TIMEOUT 10
    )
endif()

add_test(NAME core01_abi_internal_positive
    COMMAND stormline_core01_abi_portability_test positive
)
add_test(NAME core01_abi_internal_negative
    COMMAND stormline_core01_abi_portability_test negative
)
add_test(NAME core01_abi_native_probe
    COMMAND "${CMAKE_COMMAND}"
        "-DSTORM_ABI_BINARY=$<TARGET_FILE:stormline_core01_abi_portability_test>"
        "-DSTORM_ABI_PLATFORM=${CMAKE_SYSTEM_NAME}"
        "-DSTORM_ABI_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}"
        "-DSTORM_ABI_COMPILER_VERSION=${CMAKE_CXX_COMPILER_VERSION}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/core01_abi_probe.cmake"
)
add_test(NAME core01_abi_native_negative
    COMMAND "${CMAKE_COMMAND}"
        "-DSTORM_ABI_BINARY=$<TARGET_FILE:stormline_core01_abi_portability_test>"
        "-DSTORM_ABI_PLATFORM=${CMAKE_SYSTEM_NAME}"
        "-DSTORM_ABI_MODE=negative"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/core01_abi_probe.cmake"
)
set_tests_properties(
    core01_abi_internal_positive core01_abi_internal_negative
    core01_abi_native_probe core01_abi_native_negative
    PROPERTIES TIMEOUT 60
)

add_test(NAME core02_memory_basic
    COMMAND stormline_core02_memory_test basic
)
add_test(NAME core02_memory_invalid
    COMMAND stormline_core02_memory_test invalid
)
add_test(NAME core02_memory_owned
    COMMAND stormline_core02_memory_test owned
)
add_test(NAME core02_memory_move
    COMMAND stormline_core02_memory_test move
)
add_test(NAME core02_memory_release
    COMMAND stormline_core02_memory_test release
)
add_test(NAME core02_memory_resource
    COMMAND stormline_core02_memory_test resource
)
add_test(NAME core02_memory_oom
    COMMAND stormline_core02_memory_test oom
)
add_test(NAME core02_memory_cross_thread
    COMMAND stormline_core02_memory_test cross_thread
)
add_test(NAME core02_memory_lifetime
    COMMAND stormline_core02_memory_test lifetime
)

add_test(NAME core02_system_basic
    COMMAND stormline_core02_system_allocator_test basic
)
add_test(NAME core02_system_alignment
    COMMAND stormline_core02_system_allocator_test alignment
)
add_test(NAME core02_system_block
    COMMAND stormline_core02_system_allocator_test block
)
add_test(NAME core02_system_lifetime
    COMMAND stormline_core02_system_allocator_test lifetime
)
add_test(NAME core02_system_cross_thread
    COMMAND stormline_core02_system_allocator_test cross_thread
)
add_test(NAME core02_system_benchmark
    COMMAND stormline_core02_system_allocator_test benchmark
)

add_test(NAME core02_arena_basic
    COMMAND stormline_core02_arena_test basic
)
add_test(NAME core02_arena_alignment
    COMMAND stormline_core02_arena_test alignment
)
add_test(NAME core02_arena_overflow
    COMMAND stormline_core02_arena_test overflow
)
add_test(NAME core02_arena_invalid
    COMMAND stormline_core02_arena_test invalid
)
add_test(NAME core02_arena_resource
    COMMAND stormline_core02_arena_test resource
)
add_test(NAME core02_arena_lifetime
    COMMAND stormline_core02_arena_test lifetime
)
add_test(NAME core02_arena_wrong_thread
    COMMAND stormline_core02_arena_test wrong_thread
)

add_test(NAME core02_budget_basic
    COMMAND stormline_core02_budget_test basic
)
add_test(NAME core02_budget_invalid
    COMMAND stormline_core02_budget_test invalid
)
add_test(NAME core02_budget_hard
    COMMAND stormline_core02_budget_test hard
)
add_test(NAME core02_budget_underflow
    COMMAND stormline_core02_budget_test underflow
)
add_test(NAME core02_budget_lifetime
    COMMAND stormline_core02_budget_test lifetime
)
add_test(NAME core02_budget_wrong_thread
    COMMAND stormline_core02_budget_test wrong_thread
)

add_test(NAME core02_leak_basic
    COMMAND stormline_core02_leak_test basic
)
add_test(NAME core02_leak_invalid
    COMMAND stormline_core02_leak_test invalid
)
add_test(NAME core02_leak_capacity
    COMMAND stormline_core02_leak_test capacity
)
add_test(NAME core02_leak_token
    COMMAND stormline_core02_leak_test token
)
add_test(NAME core02_leak_lifetime
    COMMAND stormline_core02_leak_test lifetime
)
add_test(NAME core02_leak_wrong_thread
    COMMAND stormline_core02_leak_test wrong_thread
)

add_test(NAME core02_telemetry_basic
    COMMAND stormline_core02_telemetry_test basic
)
add_test(NAME core02_telemetry_invalid
    COMMAND stormline_core02_telemetry_test invalid
)
add_test(NAME core02_telemetry_underflow
    COMMAND stormline_core02_telemetry_test underflow
)
add_test(NAME core02_telemetry_integration
    COMMAND stormline_core02_telemetry_test integration
)
add_test(NAME core02_telemetry_concurrent
    COMMAND stormline_core02_telemetry_test concurrent
)
add_test(NAME core02_telemetry_benchmark
    COMMAND stormline_core02_telemetry_test benchmark
)

add_test(NAME core02_qualification_integrated
    COMMAND stormline_core02_qualification_test integrated
)
add_test(NAME core02_qualification_stress
    COMMAND stormline_core02_qualification_test stress
)
add_test(NAME core02_qualification_recovery
    COMMAND stormline_core02_qualification_test recovery
)
add_test(NAME core02_qualification_size_churn
    COMMAND stormline_core02_qualification_test size_churn
)
add_test(NAME core02_qualification_benchmark
    COMMAND stormline_core02_qualification_test benchmark
)

add_test(NAME core03_job01_basic
    COMMAND stormline_core03_jobs_test job01
)
add_test(NAME core03_job02_dependencies
    COMMAND stormline_core03_jobs_test job02
)
add_test(NAME core03_job03_invalid
    COMMAND stormline_core03_jobs_test job03
)
add_test(NAME core03_job04_priority
    COMMAND stormline_core03_jobs_test job04
)
add_test(NAME core03_job05_cancel
    COMMAND stormline_core03_jobs_test job05
)
add_test(NAME core03_job06_affinity
    COMMAND stormline_core03_jobs_test job06
)
add_test(NAME core03_job07_backpressure
    COMMAND stormline_core03_jobs_test job07
)
add_test(NAME core03_job08_shutdown
    COMMAND stormline_core03_jobs_test job08
)
add_test(NAME core03_job09_stress
    COMMAND stormline_core03_jobs_test job09
)
add_test(NAME core03_job10_benchmark
    COMMAND stormline_core03_jobs_test job10
)
set_tests_properties(
    core03_job01_basic
    core03_job02_dependencies
    core03_job03_invalid
    core03_job04_priority
    core03_job05_cancel
    core03_job06_affinity
    core03_job07_backpressure
    core03_job08_shutdown
    core03_job09_stress
    core03_job10_benchmark
    PROPERTIES TIMEOUT 180
)

add_test(NAME core03_qualification_integrated
    COMMAND stormline_core03_qualification_test qlf01
)
add_test(NAME core03_qualification_stress
    COMMAND stormline_core03_qualification_test qlf02
)
add_test(NAME core03_qualification_recovery
    COMMAND stormline_core03_qualification_test qlf03
)
add_test(NAME core03_qualification_overload
    COMMAND stormline_core03_qualification_test qlf04
)
add_test(NAME core03_qualification_benchmark
    COMMAND stormline_core03_qualification_test qlf05
)
set_tests_properties(
    core03_qualification_integrated
    core03_qualification_stress
    core03_qualification_recovery
    core03_qualification_overload
    core03_qualification_benchmark
    PROPERTIES TIMEOUT 300
)

add_test(NAME core04_clock_basic
    COMMAND stormline_core04_clock_test basic
)
add_test(NAME core04_clock_injected
    COMMAND stormline_core04_clock_test injected
)
add_test(NAME core04_clock_errors
    COMMAND stormline_core04_clock_test errors
)
add_test(NAME core04_clock_monotonic
    COMMAND stormline_core04_clock_test monotonic
)
add_test(NAME core04_clock_defaults
    COMMAND stormline_core04_clock_test defaults
)
add_test(NAME core04_clock_lifetime
    COMMAND stormline_core04_clock_test lifetime
)
set_tests_properties(
    core04_clock_basic
    core04_clock_injected
    core04_clock_errors
    core04_clock_monotonic
    core04_clock_defaults
    core04_clock_lifetime
    PROPERTIES TIMEOUT 120
)

add_test(NAME core04_timeline_fps
    COMMAND stormline_core04_timeline_test fps
)
add_test(NAME core04_timeline_long_run
    COMMAND stormline_core04_timeline_test long_run
)
add_test(NAME core04_timeline_pause
    COMMAND stormline_core04_timeline_test pause
)
add_test(NAME core04_timeline_step
    COMMAND stormline_core04_timeline_test step
)
add_test(NAME core04_timeline_drop
    COMMAND stormline_core04_timeline_test drop
)
add_test(NAME core04_timeline_carry
    COMMAND stormline_core04_timeline_test carry
)
add_test(NAME core04_timeline_scale
    COMMAND stormline_core04_timeline_test scale
)
add_test(NAME core04_timeline_overflow
    COMMAND stormline_core04_timeline_test overflow
)
add_test(NAME core04_timeline_replay
    COMMAND stormline_core04_timeline_test replay
)
add_test(NAME core04_timeline_lifecycle
    COMMAND stormline_core04_timeline_test lifecycle
)
add_test(NAME core04_timeline_determinism
    COMMAND stormline_core04_timeline_test determinism
)
set_tests_properties(
    core04_timeline_fps
    core04_timeline_long_run
    core04_timeline_pause
    core04_timeline_step
    core04_timeline_drop
    core04_timeline_carry
    core04_timeline_scale
    core04_timeline_overflow
    core04_timeline_replay
    core04_timeline_lifecycle
    core04_timeline_determinism
    PROPERTIES TIMEOUT 300
)

add_test(NAME core04_qualification_integrated
    COMMAND stormline_core04_qualification_test qlf01
)
add_test(NAME core04_qualification_stress
    COMMAND stormline_core04_qualification_test qlf02
)
add_test(NAME core04_qualification_recovery
    COMMAND stormline_core04_qualification_test qlf03
)
add_test(NAME core04_qualification_overload
    COMMAND stormline_core04_qualification_test qlf04
)
add_test(NAME core04_qualification_benchmark
    COMMAND stormline_core04_qualification_test qlf05
)
set_tests_properties(
    core04_qualification_integrated
    core04_qualification_stress
    core04_qualification_recovery
    core04_qualification_overload
    core04_qualification_benchmark
    PROPERTIES TIMEOUT 300
)

add_test(NAME core05_vector_math01
    COMMAND stormline_core05_vector_test math01
)
add_test(NAME core05_vector_math02
    COMMAND stormline_core05_vector_test math02
)
add_test(NAME core05_vector_errors
    COMMAND stormline_core05_vector_test errors
)
set_tests_properties(
    core05_vector_math01
    core05_vector_math02
    core05_vector_errors
    PROPERTIES TIMEOUT 60
)

add_test(NAME core05_matrix_math03
    COMMAND stormline_core05_matrix_quat_test math03
)
add_test(NAME core05_matrix_math04
    COMMAND stormline_core05_matrix_quat_test math04
)
add_test(NAME core05_quat_math05
    COMMAND stormline_core05_matrix_quat_test math05
)
set_tests_properties(
    core05_matrix_math03
    core05_matrix_math04
    core05_quat_math05
    PROPERTIES TIMEOUT 60
)

add_test(NAME core05_coord_math06
    COMMAND stormline_core05_coord_test math06
)
set_tests_properties(core05_coord_math06 PROPERTIES TIMEOUT 60)

add_test(NAME core05_unit_math07
    COMMAND stormline_core05_unit_test math07
)
set_tests_properties(core05_unit_math07 PROPERTIES TIMEOUT 60)

add_test(NAME core05_precision_math08
    COMMAND stormline_core05_precision_test math08
)
add_test(NAME core05_precision_math09
    COMMAND stormline_core05_precision_test math09
)
set_tests_properties(
    core05_precision_math08
    core05_precision_math09
    PROPERTIES TIMEOUT 60
)

add_test(NAME core05_id_math10
    COMMAND stormline_core05_id_test math10
)
add_test(NAME core05_id_math11
    COMMAND stormline_core05_id_test math11
)
set_tests_properties(
    core05_id_math10
    core05_id_math11
    PROPERTIES TIMEOUT 60
)

add_test(NAME core05_qualification_integrated
    COMMAND stormline_core05_qualification_test qlf01
)
add_test(NAME core05_qualification_repeatability
    COMMAND stormline_core05_qualification_test qlf02
)
add_test(NAME core05_qualification_recovery
    COMMAND stormline_core05_qualification_test qlf03
)
add_test(NAME core05_qualification_large_coordinates
    COMMAND stormline_core05_qualification_test qlf04
)
set_tests_properties(
    core05_qualification_integrated
    core05_qualification_repeatability
    core05_qualification_recovery
    core05_qualification_large_coordinates
    PROPERTIES TIMEOUT 120
)

add_test(NAME core06_log_01
    COMMAND stormline_core06_log_test log01
)
add_test(NAME core06_log_02
    COMMAND stormline_core06_log_test log02
)
add_test(NAME core06_log_03
    COMMAND stormline_core06_log_test log03
)
set_tests_properties(
    core06_log_01
    core06_log_02
    core06_log_03
    PROPERTIES TIMEOUT 60
)

add_test(NAME core06_trace_01
    COMMAND stormline_core06_trace_test trace01
)
set_tests_properties(core06_trace_01 PROPERTIES TIMEOUT 60)

add_test(NAME core06_counter_01
    COMMAND stormline_core06_counter_test counter01
)
set_tests_properties(core06_counter_01 PROPERTIES TIMEOUT 60)

add_test(NAME core06_crash_01
    COMMAND stormline_core06_crash_test crash01
)
set_tests_properties(core06_crash_01 PROPERTIES TIMEOUT 60)

add_test(NAME core06_profile_01
    COMMAND stormline_core06_profile_test prof01
)
set_tests_properties(core06_profile_01 PROPERTIES TIMEOUT 60)

add_test(NAME core06_telemetry_01
    COMMAND stormline_core06_telemetry_test tel01
)
set_tests_properties(core06_telemetry_01 PROPERTIES TIMEOUT 60)

add_test(NAME core06_qualification_integrated
    COMMAND stormline_core06_qualification_test qlfd01
)
add_test(NAME core06_qualification_repeatability
    COMMAND stormline_core06_qualification_test qlfd02
)
add_test(NAME core06_qualification_recovery
    COMMAND stormline_core06_qualification_test qlfd03
)
add_test(NAME core06_qualification_overload
    COMMAND stormline_core06_qualification_test qlfd04
)
set_tests_properties(
    core06_qualification_integrated
    core06_qualification_repeatability
    core06_qualification_recovery
    core06_qualification_overload
    PROPERTIES TIMEOUT 120
)

add_test(NAME data01_path_01
    COMMAND stormline_data01_path_test path01
)
set_tests_properties(data01_path_01 PROPERTIES TIMEOUT 60)

add_test(NAME data01_mount_01
    COMMAND stormline_data01_mount_test mount01
)
set_tests_properties(data01_mount_01 PROPERTIES TIMEOUT 60)

add_test(NAME data01_overlay_01
    COMMAND stormline_data01_overlay_test overlay01
)
set_tests_properties(data01_overlay_01 PROPERTIES TIMEOUT 60)

add_test(NAME data01_capability_01
    COMMAND stormline_data01_capability_test cap01
)
set_tests_properties(data01_capability_01 PROPERTIES TIMEOUT 60)

add_test(NAME data01_cache_01
    COMMAND stormline_data01_cache_test cache01
)
set_tests_properties(data01_cache_01 PROPERTIES TIMEOUT 60)

add_test(NAME data01_storage_01
    COMMAND stormline_data01_storage_test storage01
)
set_tests_properties(data01_storage_01 PROPERTIES TIMEOUT 60)

add_test(NAME data01_vfs_qualification_01
    COMMAND stormline_data01_vfs_qualification_test qlf01
)
set_tests_properties(data01_vfs_qualification_01 PROPERTIES TIMEOUT 60)

add_test(NAME data01_vfs_qualification_02
    COMMAND stormline_data01_vfs_qualification_test qlf02
)
set_tests_properties(data01_vfs_qualification_02 PROPERTIES TIMEOUT 60)

add_test(NAME data01_vfs_qualification_03
    COMMAND stormline_data01_vfs_qualification_test qlf03
)
set_tests_properties(data01_vfs_qualification_03 PROPERTIES TIMEOUT 60)

add_test(NAME data01_vfs_qualification_04
    COMMAND stormline_data01_vfs_qualification_test qlf04
)
set_tests_properties(data01_vfs_qualification_04 PROPERTIES TIMEOUT 60)

add_test(NAME data02_id_01
    COMMAND stormline_data02_id_test id01
)
set_tests_properties(data02_id_01 PROPERTIES TIMEOUT 60)

add_test(NAME data02_dependency_01
    COMMAND stormline_data02_dependency_test dep01
)
set_tests_properties(data02_dependency_01 PROPERTIES TIMEOUT 60)

add_test(NAME data02_tag_01
    COMMAND stormline_data02_tag_test tag01
)
set_tests_properties(data02_tag_01 PROPERTIES TIMEOUT 60)

add_test(NAME data02_query_01
    COMMAND stormline_data02_query_test query01
)
set_tests_properties(data02_query_01 PROPERTIES TIMEOUT 60)

add_test(NAME data02_schema_01
    COMMAND stormline_data02_schema_test schema01
)
set_tests_properties(data02_schema_01 PROPERTIES TIMEOUT 60)

add_test(NAME data02_reference_01
    COMMAND stormline_data02_reference_test ref01
)
set_tests_properties(data02_reference_01 PROPERTIES TIMEOUT 60)

add_test(NAME data02_registry_qualification_01
    COMMAND stormline_data02_registry_qualification_test qlf01
)
set_tests_properties(data02_registry_qualification_01 PROPERTIES TIMEOUT 120)

add_test(NAME data02_registry_qualification_02
    COMMAND stormline_data02_registry_qualification_test qlf02
)
set_tests_properties(data02_registry_qualification_02 PROPERTIES TIMEOUT 120)

add_test(NAME data02_registry_qualification_03
    COMMAND stormline_data02_registry_qualification_test qlf03
)
set_tests_properties(data02_registry_qualification_03 PROPERTIES TIMEOUT 120)

add_test(NAME data02_registry_qualification_04
    COMMAND stormline_data02_registry_qualification_test qlf04
)
set_tests_properties(data02_registry_qualification_04 PROPERTIES TIMEOUT 120)

add_test(NAME data03_importer_01
    COMMAND stormline_data03_importer_test imp01
)
set_tests_properties(data03_importer_01 PROPERTIES TIMEOUT 60)

add_test(NAME data03_texture_01
    COMMAND stormline_data03_texture_test tex01
)
set_tests_properties(data03_texture_01 PROPERTIES TIMEOUT 60)

add_test(NAME data03_animation_01
    COMMAND stormline_data03_animation_test anim01
)
set_tests_properties(data03_animation_01 PROPERTIES TIMEOUT 60)

add_test(NAME data03_audio_01
    COMMAND stormline_data03_audio_test audio01
)
set_tests_properties(data03_audio_01 PROPERTIES TIMEOUT 60)

add_test(NAME data03_validation_01
    COMMAND stormline_data03_validation_test val01
)
set_tests_properties(data03_validation_01 PROPERTIES TIMEOUT 60)

add_test(NAME data03_receipt_01
    COMMAND stormline_data03_receipt_test rec01
)
set_tests_properties(data03_receipt_01 PROPERTIES TIMEOUT 60)

add_test(NAME data03_import_qualification_01
    COMMAND stormline_data03_import_qualification_test qlf01
)
set_tests_properties(data03_import_qualification_01 PROPERTIES TIMEOUT 120)

add_test(NAME data03_import_qualification_02
    COMMAND stormline_data03_import_qualification_test qlf02
)
set_tests_properties(data03_import_qualification_02 PROPERTIES TIMEOUT 120)

add_test(NAME data03_import_qualification_03
    COMMAND stormline_data03_import_qualification_test qlf03
)
set_tests_properties(data03_import_qualification_03 PROPERTIES TIMEOUT 120)

add_test(NAME data03_import_qualification_04
    COMMAND stormline_data03_import_qualification_test qlf04
)
set_tests_properties(data03_import_qualification_04 PROPERTIES TIMEOUT 120)

add_test(NAME data04_schema_01
    COMMAND stormline_data04_schema_test sch01
)
set_tests_properties(data04_schema_01 PROPERTIES TIMEOUT 60)

add_test(NAME data04_document_01
    COMMAND stormline_data04_document_test doc01
)
set_tests_properties(data04_document_01 PROPERTIES TIMEOUT 60)

add_test(NAME data04_patch_01
    COMMAND stormline_data04_patch_test patch01
)
set_tests_properties(data04_patch_01 PROPERTIES TIMEOUT 60)

add_test(NAME data04_diff_01
    COMMAND stormline_data04_diff_test diff01
)
set_tests_properties(data04_diff_01 PROPERTIES TIMEOUT 60)

add_test(NAME data04_scene_qualification_01
    COMMAND stormline_data04_scene_qualification_test qlf01
)
set_tests_properties(data04_scene_qualification_01 PROPERTIES TIMEOUT 120)

add_test(NAME data04_scene_qualification_02
    COMMAND stormline_data04_scene_qualification_test qlf02
)
set_tests_properties(data04_scene_qualification_02 PROPERTIES TIMEOUT 120)

add_test(NAME data04_scene_qualification_03
    COMMAND stormline_data04_scene_qualification_test qlf03
)
set_tests_properties(data04_scene_qualification_03 PROPERTIES TIMEOUT 120)

add_test(NAME data04_scene_qualification_04
    COMMAND stormline_data04_scene_qualification_test qlf04
)
set_tests_properties(data04_scene_qualification_04 PROPERTIES TIMEOUT 120)

add_test(NAME data05_target_01
    COMMAND stormline_data05_target_test tgt01
)
set_tests_properties(data05_target_01 PROPERTIES TIMEOUT 60)

add_test(NAME data05_rle_01
    COMMAND stormline_data05_rle_test rle01
)
set_tests_properties(data05_rle_01 PROPERTIES TIMEOUT 60)

add_test(NAME data05_stream_01
    COMMAND stormline_data05_stream_test str01
)
set_tests_properties(data05_stream_01 PROPERTIES TIMEOUT 60)

add_test(NAME data05_manifest_01
    COMMAND stormline_data05_manifest_test man01
)
set_tests_properties(data05_manifest_01 PROPERTIES TIMEOUT 60)

add_test(NAME data05_patch_01
    COMMAND stormline_data05_patch_test pat01
)
set_tests_properties(data05_patch_01 PROPERTIES TIMEOUT 60)

add_test(NAME data05_bundle_qualification_01
    COMMAND stormline_data05_bundle_qualification_test qlf01
)
set_tests_properties(data05_bundle_qualification_01 PROPERTIES TIMEOUT 120)

add_test(NAME data05_bundle_qualification_02
    COMMAND stormline_data05_bundle_qualification_test qlf02
)
set_tests_properties(data05_bundle_qualification_02 PROPERTIES TIMEOUT 120)

add_test(NAME data05_bundle_qualification_03
    COMMAND stormline_data05_bundle_qualification_test qlf03
)
set_tests_properties(data05_bundle_qualification_03 PROPERTIES TIMEOUT 120)

add_test(NAME data05_bundle_qualification_04
    COMMAND stormline_data05_bundle_qualification_test qlf04
)
set_tests_properties(data05_bundle_qualification_04 PROPERTIES TIMEOUT 120)

add_test(NAME gfx01_device_01
    COMMAND stormline_gfx01_device_test dev01
)
set_tests_properties(gfx01_device_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx01_queue_01
    COMMAND stormline_gfx01_queue_test que01
)
set_tests_properties(gfx01_queue_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx01_buffer_01
    COMMAND stormline_gfx01_buffer_test buf01
)
set_tests_properties(gfx01_buffer_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx01_texture_01
    COMMAND stormline_gfx01_texture_test tex01
)
set_tests_properties(gfx01_texture_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx01_sync_01
    COMMAND stormline_gfx01_sync_test syn01
)
set_tests_properties(gfx01_sync_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx01_feature_01
    COMMAND stormline_gfx01_feature_test tier01
)
set_tests_properties(gfx01_feature_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx01_rhi_qualification_01
    COMMAND stormline_gfx01_rhi_qualification_test qlf01
)
set_tests_properties(gfx01_rhi_qualification_01 PROPERTIES TIMEOUT 120)

add_test(NAME gfx01_rhi_qualification_02
    COMMAND stormline_gfx01_rhi_qualification_test qlf02
)
set_tests_properties(gfx01_rhi_qualification_02 PROPERTIES TIMEOUT 120)

add_test(NAME gfx01_rhi_qualification_03
    COMMAND stormline_gfx01_rhi_qualification_test qlf03
)
set_tests_properties(gfx01_rhi_qualification_03 PROPERTIES TIMEOUT 120)

add_test(NAME gfx01_rhi_qualification_04
    COMMAND stormline_gfx01_rhi_qualification_test qlf04
)
set_tests_properties(gfx01_rhi_qualification_04 PROPERTIES TIMEOUT 120)

add_test(NAME gfx02_shader_01
    COMMAND stormline_gfx02_shader_test par01
)
set_tests_properties(gfx02_shader_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx02_reflection_01
    COMMAND stormline_gfx02_reflection_test ref01
)
set_tests_properties(gfx02_reflection_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx02_variant_01
    COMMAND stormline_gfx02_variant_test var01
)
set_tests_properties(gfx02_variant_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx02_cache_01
    COMMAND stormline_gfx02_cache_test cac01
)
set_tests_properties(gfx02_cache_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx02_incremental_01
    COMMAND stormline_gfx02_incremental_test inc01
)
set_tests_properties(gfx02_incremental_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx02_shader_qualification_01
    COMMAND stormline_gfx02_shader_qualification_test qlf01
)
set_tests_properties(gfx02_shader_qualification_01 PROPERTIES TIMEOUT 120)

add_test(NAME gfx02_shader_qualification_02
    COMMAND stormline_gfx02_shader_qualification_test qlf02
)
set_tests_properties(gfx02_shader_qualification_02 PROPERTIES TIMEOUT 120)

add_test(NAME gfx02_shader_qualification_03
    COMMAND stormline_gfx02_shader_qualification_test qlf03
)
set_tests_properties(gfx02_shader_qualification_03 PROPERTIES TIMEOUT 120)

add_test(NAME gfx02_shader_qualification_04
    COMMAND stormline_gfx02_shader_qualification_test qlf04
)
set_tests_properties(gfx02_shader_qualification_04 PROPERTIES TIMEOUT 120)

add_test(NAME gfx03_graph_01
    COMMAND stormline_gfx03_graph_test def01
)
set_tests_properties(gfx03_graph_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx03_dependency_01
    COMMAND stormline_gfx03_dependency_test dep01
)
set_tests_properties(gfx03_dependency_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx03_sync_01
    COMMAND stormline_gfx03_sync_test syn01
)
set_tests_properties(gfx03_sync_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx03_transient_01
    COMMAND stormline_gfx03_transient_test tra01
)
set_tests_properties(gfx03_transient_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx03_budget_01
    COMMAND stormline_gfx03_budget_test bud01
)
set_tests_properties(gfx03_budget_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx03_graph_qualification_01
    COMMAND stormline_gfx03_graph_qualification_test qlf01
)
set_tests_properties(gfx03_graph_qualification_01 PROPERTIES TIMEOUT 120)

add_test(NAME gfx03_graph_qualification_02
    COMMAND stormline_gfx03_graph_qualification_test qlf02
)
set_tests_properties(gfx03_graph_qualification_02 PROPERTIES TIMEOUT 120)

add_test(NAME gfx03_graph_qualification_03
    COMMAND stormline_gfx03_graph_qualification_test qlf03
)
set_tests_properties(gfx03_graph_qualification_03 PROPERTIES TIMEOUT 120)

add_test(NAME gfx03_graph_qualification_04
    COMMAND stormline_gfx03_graph_qualification_test qlf04
)
set_tests_properties(gfx03_graph_qualification_04 PROPERTIES TIMEOUT 120)

add_test(NAME gfx04_instance_01
    COMMAND stormline_gfx04_instance_test ins01
)
set_tests_properties(gfx04_instance_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx04_cull_01
    COMMAND stormline_gfx04_cull_test cul01
)
set_tests_properties(gfx04_cull_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx04_lod_01
    COMMAND stormline_gfx04_lod_test lod01
)
set_tests_properties(gfx04_lod_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx04_stream_01
    COMMAND stormline_gfx04_stream_test str01
)
set_tests_properties(gfx04_stream_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx04_vegetation_01
    COMMAND stormline_gfx04_vegetation_test veg01
)
set_tests_properties(gfx04_vegetation_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx04_budget_01
    COMMAND stormline_gfx04_budget_test geo01
)
set_tests_properties(gfx04_budget_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx04_geometry_qualification_01
    COMMAND stormline_gfx04_geometry_qualification_test qlf01
)
set_tests_properties(gfx04_geometry_qualification_01 PROPERTIES TIMEOUT 120)

add_test(NAME gfx04_geometry_qualification_02
    COMMAND stormline_gfx04_geometry_qualification_test qlf02
)
set_tests_properties(gfx04_geometry_qualification_02 PROPERTIES TIMEOUT 120)

add_test(NAME gfx04_geometry_qualification_03
    COMMAND stormline_gfx04_geometry_qualification_test qlf03
)
set_tests_properties(gfx04_geometry_qualification_03 PROPERTIES TIMEOUT 120)

add_test(NAME gfx04_geometry_qualification_04
    COMMAND stormline_gfx04_geometry_qualification_test qlf04
)
set_tests_properties(gfx04_geometry_qualification_04 PROPERTIES TIMEOUT 120)

add_test(NAME gfx05_material_01
    COMMAND stormline_gfx05_material_test pbr01
)
set_tests_properties(gfx05_material_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx05_texture_01
    COMMAND stormline_gfx05_texture_test vtx01
)
set_tests_properties(gfx05_texture_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx05_mip_01
    COMMAND stormline_gfx05_mip_test mip01
)
set_tests_properties(gfx05_mip_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx05_sampler_01
    COMMAND stormline_gfx05_sampler_test smp01
)
set_tests_properties(gfx05_sampler_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx05_decal_01
    COMMAND stormline_gfx05_decal_test dec01
)
set_tests_properties(gfx05_decal_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx05_transparency_01
    COMMAND stormline_gfx05_transparency_test trn01
)
set_tests_properties(gfx05_transparency_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx05_material_qualification_01
    COMMAND stormline_gfx05_material_qualification_test qlf01
)
set_tests_properties(gfx05_material_qualification_01 PROPERTIES TIMEOUT 120)

add_test(NAME gfx05_material_qualification_02
    COMMAND stormline_gfx05_material_qualification_test qlf02
)
set_tests_properties(gfx05_material_qualification_02 PROPERTIES TIMEOUT 120)

add_test(NAME gfx05_material_qualification_03
    COMMAND stormline_gfx05_material_qualification_test qlf03
)
set_tests_properties(gfx05_material_qualification_03 PROPERTIES TIMEOUT 120)

add_test(NAME gfx05_material_qualification_04
    COMMAND stormline_gfx05_material_qualification_test qlf04
)
set_tests_properties(gfx05_material_qualification_04 PROPERTIES TIMEOUT 120)

add_test(NAME gfx06_light_01
    COMMAND stormline_gfx06_light_test lgt01
)
set_tests_properties(gfx06_light_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx06_shadow_01
    COMMAND stormline_gfx06_shadow_test shd01
)
set_tests_properties(gfx06_shadow_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx06_gi_01
    COMMAND stormline_gfx06_gi_test gi01
)
set_tests_properties(gfx06_gi_01 PROPERTIES TIMEOUT 60)

add_test(NAME gfx06_probe_01
    COMMAND stormline_gfx06_probe_test prb01
)
set_tests_properties(gfx06_probe_01 PROPERTIES TIMEOUT 60)

if(WIN32)
    add_test(NAME core02_q4_helper_failclosed
        COMMAND powershell -NoProfile -ExecutionPolicy Bypass
            -File "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/core02/test_run_physical_profile.ps1"
            -FakeExecutable $<TARGET_FILE:stormline_core02_fake_allocator_bench>
    )
    set_tests_properties(core02_q4_helper_failclosed PROPERTIES TIMEOUT 180)

    add_test(NAME core02_q4_profile_runner_failclosed
        COMMAND powershell -NoProfile -ExecutionPolicy Bypass
            -File "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/core02/test_q4_profile_runner.ps1"
            -RunnerExecutable $<TARGET_FILE:stormline_core02_q4_profile_runner>
            -FakeExecutable $<TARGET_FILE:stormline_core02_fake_allocator_bench>
    )
    set_tests_properties(core02_q4_profile_runner_failclosed PROPERTIES TIMEOUT 180)
endif()

if(STORMLINE_CORE02_ALLOC_BENCH)
    add_test(NAME core02_allocator_bench
        COMMAND stormline_core02_allocator_bench full
    )
    set_tests_properties(core02_allocator_bench PROPERTIES TIMEOUT 300)
endif()

set_tests_properties(
    core01_headless_lifecycle
    core01_headless_errors
    core01_headless_cleanup
    core01_headless_destructor
    core01_headless_invalid
    core01_paths_basic
    core01_paths_unicode
    core01_paths_traversal
    core01_paths_errors
    core01_paths_no_write
    core01_paths_symlink
    core01_paths_access
    core01_sdl_basic
    core01_sdl_wrong_thread
    core01_sdl_init_failure
    core01_sdl_destructor
    core01_sdl_version
    core01_sdl_header
    core01_window_basic
    core01_window_invalid
    core01_window_wrong_thread
    core01_window_not_initialized
    core01_window_lifetime
    core01_events_basic
    core01_events_sequence
    core01_events_overflow
    core01_events_replay
    core01_events_wrong_thread
    core01_events_not_initialized
    core01_events_empty_clear
    core01_events_lifetime
    core01_display_displays
    core01_display_errors
    core01_display_wrong_thread
    core01_display_surface
    core01_display_surface_errors
    core01_display_stability
    core01_display_lifetime
    core01_native_system
    core01_native_handle
    core01_native_unavailable
    core01_native_errors
    core01_native_wrong_thread
    core01_native_lifetime
    core01_lifecycle_normal
    core01_lifecycle_shutdown
    core01_lifecycle_events
    core01_lifecycle_invalid
    core01_lifecycle_wrong_thread
    core01_lifecycle_recovery
    core01_capability_states
    core01_capability_uninitialized
    core01_capability_dummy
    core01_capability_real
    core01_capability_wrong_thread
    core01_capability_benchmark
    core01_soak
    core01_qualification
    core02_memory_basic
    core02_memory_invalid
    core02_memory_owned
    core02_memory_move
    core02_memory_release
    core02_memory_resource
    core02_memory_oom
    core02_memory_cross_thread
    core02_memory_lifetime
    core02_system_basic
    core02_system_alignment
    core02_system_block
    core02_system_lifetime
    core02_system_cross_thread
    core02_system_benchmark
    core02_arena_basic
    core02_arena_alignment
    core02_arena_overflow
    core02_arena_invalid
    core02_arena_resource
    core02_arena_lifetime
    core02_arena_wrong_thread
    core02_budget_basic
    core02_budget_invalid
    core02_budget_hard
    core02_budget_underflow
    core02_budget_lifetime
    core02_budget_wrong_thread
    core02_leak_basic
    core02_leak_invalid
    core02_leak_capacity
    core02_leak_token
    core02_leak_lifetime
    core02_leak_wrong_thread
    core02_telemetry_basic
    core02_telemetry_invalid
    core02_telemetry_underflow
    core02_telemetry_integration
    core02_telemetry_concurrent
    core02_telemetry_benchmark
    core02_qualification_integrated
    core02_qualification_stress
    core02_qualification_recovery
    core02_qualification_size_churn
    core02_qualification_benchmark
    PROPERTIES TIMEOUT 180
)

set_tests_properties(
    core01_sdl_basic
    core01_sdl_wrong_thread
    core01_sdl_init_failure
    core01_sdl_destructor
    core01_sdl_version
    core01_sdl_header
    core01_events_basic
    core01_events_sequence
    core01_events_overflow
    core01_events_replay
    core01_events_wrong_thread
    core01_events_not_initialized
    core01_events_empty_clear
    core01_events_lifetime
    core01_display_displays
    core01_display_errors
    core01_display_wrong_thread
    core01_display_surface
    core01_display_surface_errors
    core01_display_stability
    core01_display_lifetime
    core01_native_unavailable
    core01_capability_uninitialized
    core01_capability_dummy
    core01_capability_wrong_thread
    core01_capability_benchmark
    PROPERTIES ENVIRONMENT "SDL_VIDEODRIVER=dummy"
)

if(WIN32)
    set(STORMLINE_WINDOW_VIDEO_DRIVER windows)
elseif(APPLE)
    set(STORMLINE_WINDOW_VIDEO_DRIVER cocoa)
else()
    set(STORMLINE_WINDOW_VIDEO_DRIVER x11)
endif()

set_tests_properties(
    core01_window_basic
    core01_window_invalid
    core01_window_wrong_thread
    core01_window_not_initialized
    core01_window_lifetime
    core01_native_system
    core01_native_handle
    core01_native_errors
    core01_native_wrong_thread
    core01_native_lifetime
    core01_capability_real
    core01_soak
    core01_qualification
    PROPERTIES ENVIRONMENT "SDL_VIDEODRIVER=${STORMLINE_WINDOW_VIDEO_DRIVER}"
)
