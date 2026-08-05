cmake_minimum_required(VERSION 3.21)

project(VanillaEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# DirectXTex is vendored under Core/Vendor and built as a static library.
set(BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(BUILD_SAMPLE OFF CACHE BOOL "" FORCE)
add_subdirectory(Core/Vendor/DirectXTex EXCLUDE_FROM_ALL)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(Core/Vendor/glfw)

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Core/Vendor/imgui")
set(ENGINE_SOURCES
    Core/Application.cpp
    Core/Platform/Windows/vlWindow.cpp
    Core/Resources/Buffer.h
    Core/Resources/Buffer.cpp
    Core/Platform/Windows/vlRenderer.cpp
    UI.cpp
    "Core/Main.cpp"
)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_dx11.cpp
 "Core/vlCore.h" "Core/vlCore.cpp" "Core/Platform/DirectX/VertexShader.cpp" "Core/Platform/DirectX/VertexShader.h" "Core/Platform/Windows/vlUserInterface.cpp" "Core/Platform/Windows/vlUserInterface.h" "Core/Platform/DirectX/PixelShader.h" "Core/Platform/DirectX/PixelShader.cpp" "Core/Resources/TextureRes.cpp" "Core/Resources/TextureRes.h")

add_executable(Vanilla ${ENGINE_SOURCES} ${IMGUI_SOURCES})
target_include_directories(Vanilla PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)
target_link_libraries(Vanilla PRIVATE glfw DirectXTex d3d11 d3dcompiler dxgi gdi32)

# Shaders are compiled at startup, so copy them beside the program.
add_custom_command(TARGET Vanilla POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/VS.hlsl" "$<TARGET_FILE_DIR:Vanilla>/VS.hlsl"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/PS.hlsl" "$<TARGET_FILE_DIR:Vanilla>/PS.hlsl"
)
