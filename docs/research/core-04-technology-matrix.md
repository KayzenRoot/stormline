# CORE-04 — Clock, Tick & Replay Technology Matrix

**Work Order:** NLE-P00-WO-002-CORE-04 | **Issue:** #99 | **Status:** PROPOSED / DOCUMENTATION ONLY

| Candidate | Mechanics / source | License/OS assessment | Benefits | Limitations / decision gate |
|---|---|---|---|---|
| C++20 std::chrono::steady_clock | standard monotonic relative timepoints | C++ standard library; native compiler runtime on Windows/Linux/macOS | portable, dependency-free, injectable wrapper | check actual resolution, time-source conversion, suspend semantics, no deterministic physics guarantee |
| SDL3 SDL_GetTicksNS | SDL process-init-relative integer nanoseconds | SDL3 zlib (verify pinned version/notice); Win/Linux/macOS planned by CORE-01 | interoperates with candidate CORE-01 SDL3 | SDL initialization coupling; don't force SDL into headless simulation API |
| SDL3 performance counter/frequency | hardware/platform counter + conversion | same SDL3 zlib terms | profiling resolution comparator | conversion/overflow/frequency, sampling cost; not needed for basic frame timeline |
| Native Windows QueryPerformanceCounter | Windows monotonic high-resolution counter | platform API, no third-party package | high-resolution diagnostic baseline; native fallback | Windows-only, avoid direct RDTSC; hide behind CORE-01 |
| Linux clock_gettime / macOS mach monotonic services | platform native monotonic source | OS API, platform-specific | fallback for explicit platform needs | divergent semantics and source maintenance; use only with evidence |
| Variable delta game loop | update physics with measured frame dt | no dependency | simple | **REJECT** for stable physics/replay; behavior varies with FPS |
| Float accumulator with fixed dt | classic fixed-step demonstration | no dependency | easy prototype | drifts across long runs and can produce off-by-one boundaries; not default long-lived clock contract |
| Integer/rational accumulator + injected ClockSource | owned, small custom scheduling policy over standard primitives | original Stormline code when implemented; no external runtime package | exact tick numbering, fake clock testing, decouple sim/render | checked math + carry remainder + overflow proof required |

## Selection recommendation (NOT APPROVED AS IMPLEMENTATION)
- **Preferred baseline for research:** standard C++20 monotonic time source; owned ClockSource adapter plus integer/rational fixed-tick accumulator. No new third-party library required in CORE-04.
- **SDL3** is an adapter/comparator only if CORE-01 approves/pins it; no direct dependency in the public simulation clock.
- **Windows QPC** is a platform-specific diagnostic alternative, not part of the portable public API. No engine performance benefit claimed.
- Stable tick schedule is separable from physics/netcode determinism. No purchased dependency/SDK needed.

## Weighted criteria (scores pending measured data)
Correctness/long-duration drift 30%; frame independence and overload behavior 25%; platform/headless portability 15%; observability/testing 15%; integration footprint and maintainability 10%; sampling overhead 5%. Do not fill scores with unsourced guesses.

## Evidence / official references
- std::chrono::steady_clock semantics: https://en.cppreference.com/w/cpp/chrono/steady_clock
- MSVC mapping to QPC: https://learn.microsoft.com/en-us/cpp/standard-library/steady-clock-struct?view=msvc-170
- Windows QPC guidance: https://learn.microsoft.com/en-us/windows/win32/sysinfo/acquiring-high-resolution-time-stamps
- SDL nanosecond uptime: https://wiki.libsdl.org/SDL3/SDL_GetTicksNS
- SDL performance counter: https://wiki.libsdl.org/SDL3/SDL_GetPerformanceCounter and https://wiki.libsdl.org/SDL3/SDL_GetPerformanceFrequency
- Fixed step/interpolation discussion: https://www.gafferongames.com/post/fix_your_timestep/
- Unity fixed updates (comparative behavior): https://docs.unity.com/en-us/engine/6000.3/manual/scripting/managing-time-and-frame-rate/fixed-updates
- Box2D fixed step and explicit non-guarantee of application determinism: https://box2d.org/documentation/md_simulation.html

**License caveat:** document exact third-party tags, notices, vulnerabilities and packaging at the later code-activation gate; no code is imported now.
