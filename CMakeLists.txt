cmake_minimum_required(VERSION 3.27)
project(stormline_core01_internal LANGUAGES C CXX)

option(STORMLINE_CORE01_ENABLE_SANITIZERS "Enable ASan/UBSan for the internal CORE-01 slice" OFF)
option(STORMLINE_CORE02_ALLOC_BENCH "Build the optional isolated CORE-02 allocator benchmark" OFF)

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
