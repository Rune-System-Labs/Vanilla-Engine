#pragma once

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_glfw.h>

class UI final {
public:
    ~UI();
    void InitUI(GLFWwindow* window, ID3D11Device* device, ID3D11DeviceContext* context);
    void RunFrame();

private:
    bool initialized_ = false;
};
