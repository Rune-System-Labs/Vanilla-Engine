#pragma once

#include <cstdint>
#include <string_view>

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_NO_API

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace vl::Platform {
class Window{
public:
    Window() = default;
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool vlCreateWindow(std::uint32_t width, std::uint32_t height, std::string_view title);

    [[nodiscard]] GLFWwindow* GetHandle() const { return vlwindow_; }
    [[nodiscard]] std::uint32_t Width() const { return width_; }
    [[nodiscard]] std::uint32_t Height() const { return height_; }

private:
    GLFWwindow* vlwindow_ = nullptr;
    std::uint32_t width_ = 0;
    std::uint32_t height_ = 0;
    bool glfwInitialized_ = false;
};

} // namespace vl::Core
