#include "UI.h"


UI::~UI(){
    if (!initialized_) return;
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UI::InitUI(GLFWwindow* window, ID3D11Device* device, ID3D11DeviceContext* context) {
    ImGui::CreateContext();

    // Setup Platform/Renderer backends
    // The 'true' tells ImGui to install its own callbacks for mouse/keyboard
    ImGui_ImplGlfw_InitForOther(window, true);
    ImGui_ImplDX11_Init(device, context);
    initialized_ = true;
}

void UI::RunFrame() {
    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Your UI Logic here...
    ImGui::Begin("Dashboard");
    ImGui::Text("D3D11");
    ImGui::End();

    // Rendering
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
