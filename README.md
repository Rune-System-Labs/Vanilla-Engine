# Vanilla Engine

A small DirectX 11 learning engine written in C++.

Current milestone: a rotating, textured cube with a GLFW window, depth testing, a movable camera (`WASD`, `Space`, `Left Shift`), and an ImGui dashboard.

## Layout

- `Core/` — application lifetime and platform window code.
- `Engine/` — graphics device, renderer, camera, shader/mesh data, and textures.
- `Sandbox/` — executable entry point; use it for experiments without cluttering engine code.
- `Core/Vendor/` — third-party code (GLFW and Dear ImGui).

## Build

Open this folder in Visual Studio with CMake support, select the `x64-debug` preset, and build `Vanilla`. The HLSL shader files are copied beside the executable automatically.

## Good next steps

1. Replace the procedural 2×2 texture in `Engine/Texture.cpp` with a PNG loader.
2. Add resize handling to recreate DirectX render targets.
3. Extract keyboard input from `Renderer` into `Core/Input`.
