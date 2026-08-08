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

## Changelog

### 2026-08-08

- Changed `UserInterface::vlInitUI` to receive a non-owning `GLFWwindow*`. The application owns the window, so the UI must borrow it rather than put it in another `unique_ptr`.
- Connected the UI frame lifecycle to the application loop: start a frame, build the UI, render the UI, then present the swap chain.
- Added a basic engine-style Settings window with categories on the left and options on the right.
- Added the `Rendering` category with Solid and Wireframe options.
- Fixed the settings callback flow so registered callbacks are invoked inside the selected category.
- Fixed DirectX render-state creation and binding after the callback changes the selected mode.
- Fixed ImGui `Begin`/`End` pairing. Every successful or unsuccessful `Begin` call must have a matching `End` call.
- Rebuilt and verified the `x64-debug` target successfully.
