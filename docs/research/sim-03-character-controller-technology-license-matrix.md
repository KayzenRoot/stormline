# SIM-03 — Character Motor Technology, Rights and Portability Matrix

**NLE-P00-WO-002-SIM-03 | Research #180 | PROPOSED, NO SDK/FILE INSTALLED, NO RUNTIME**.

| Candidate | Class | Evidence from official source | Constraints / approval gate |
|---|---|---|---|
| Original Stormline typed tick motor, profile and receipts | NECESSARY | Engine-owned C++20 abstract, independently specified | Check licensing after engine license ADR, ABI, capability budget and headless goldens |
| Jolt Physics `CharacterVirtual` 3D adapter | LEADING CANDIDATE, NOT SELECTED | Jolt MIT; `CharacterVirtual` supports Update/ExtendedUpdate, stairs, stick-to-floor and contact state; virtual character must be explicitly updated and saved separately from ordinary PhysicsSystem state | Must share pinned SIM-02 backend/profile and document order, contact callbacks, support sampling, collision layer filtering, snapshots/replay and Win/Linux/macOS/WASM actual builds |
| Jolt physics `Character` rigid-body controller | CONDITIONAL | Simulated restricted-rotation body suitable for some NPCs per Jolt architecture | Physical state compromises precision and player feel, avoid general default; verify constraints, active count and dynamic mass |
| Box2D 3.1+ geometric character mover | EXPERIMENTAL 2D CANDIDATE | Box2D official docs explicitly mark mover experimental; geometric capsule outside standard simulation world | Compatible with SIM-01 pin; check license of exact tag, API stability, one-way platforms and snapshot/contact lifecycle |
| Rapier KinematicCharacterController 2D/3D | COMPARISON ONLY | Official Rust and C APIs describe steps, slopes and ground snapping | Rust toolchain/native C API licensing/transitive packages, ABI and WASM maintenance; avoid adding second physics runtime unless measured benefit |
| Godot `CharacterBody2D/3D` semantics | REFERENCE ONLY | Documented `move_and_slide`, slope/ground snapping and motion modes; Godot engine MIT | Conceptual inspiration, never copy protected game content; do not vendor Godot's scene/physics runtime |
| Existing SIM-01/02 collision-query owner API | NECESSARY CONTRACT | Future engine-owned typed narrowphase casts and post-step receipts | Cannot activate SIM-03 until physics code/runtime integration and support fidelity evidence exist |
| GPU character collision / proprietary SDKs | FUTURE / OUT OF SCOPE | No portable baseline evidence | CPU-first and headless required, avoid mandatory paid/proprietary runtime |
| Native/Web editor/CLI/MCP authoring | IMPORTANT AFTER ENGINE CORE | Versioned profile source transaction via common command kernel | No remote arbitrary force/memory; no extra engine command kernel |

## Official primary references checked
- Jolt C++ architecture character controllers: https://github.com/jrouwe/JoltPhysics/blob/master/Docs/Architecture.md
- Jolt CharacterVirtual class: https://jrouwe.github.io/JoltPhysics/class_character_virtual.html
- Jolt MIT license: https://github.com/jrouwe/JoltPhysics/blob/master/LICENSE
- Box2D experimental character mover: https://box2d.org/documentation/md_character.html
- Box2D project/legal notices: https://github.com/erincatto/box2d
- Rapier C controller: https://rapier.rs/docs/user_guides/c/character_controller/
- Rapier Rust controller: https://rapier.rs/docs/user_guides/rust/character_controller/
- Godot CharacterBody3D: https://docs.godotengine.org/en/stable/classes/class_characterbody3d.html
- Godot engine license: https://github.com/godotengine/godot/blob/master/LICENSE.txt

Every source above is **research reference**, not an integrated dependency or approved version. Pin commit/tag and transitive notices, verify actual API/profile, perf and security before any adoption. No proprietary sample assets or copyrighted game implementation will be copied.
