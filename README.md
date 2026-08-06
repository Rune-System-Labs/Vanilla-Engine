# Vanilla Engine

A Game Engine Built while Learning

## Current milestone:

1. Viewing around the world made by Vector and Matrix math from the DirectX11 Math Library
2. WASD Movements for moving around the World.
3. Asset manager(3D Models,Textures e.t.c).
4. An interactive User Interface for the Engine using dear imgui library.

## Layout

- `Core/` — application lifetime and platform window code.
- `Sandbox/` — other executable entry point; use it for experiments without cluttering engine code.
- `Core/Vendor/` — third-party code (GLFW and Dear ImGui).

## Build

Open this folder in Visual Studio with CMake support, select the `x64-debug` preset, and build `Vanilla`. The HLSL shader files are copied beside the executable automatically.

## Tool Needed To Run This Code In Visual Studio
1. Desktop Developement with C/C++
2. HLSL Tools
3. your PC's GPU must be supporting DirectX11
