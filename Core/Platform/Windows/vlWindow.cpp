#include "vlWindow.h"

#include <iostream>

namespace vl::Platform {
    Window::~Window() {
        if (vlwindow_ != nullptr) {
            glfwDestroyWindow(vlwindow_);
        }
        if (glfwInitialized_) {
            glfwTerminate();
        }
    }

    bool Window::vlCreateWindow(const std::uint32_t width, const std::uint32_t height, const std::string_view title) {
        if (!glfwInit()) {
            std::cerr << "VL: Failed to initialize GLFW.\n";
            return false;
        }
        glfwInitialized_ = true;
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        vlwindow_ = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.data(), nullptr, nullptr);
        if (vlwindow_ == nullptr) {
            std::cerr << "VL: Failed to create the window.\n";
            return false;
        }

        width_ = width;
        height_ = height;
        return true;
    }
}