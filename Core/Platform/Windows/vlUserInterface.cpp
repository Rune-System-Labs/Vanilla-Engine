#include "vlUserInterface.h"

namespace vl::UI{
    void UserInterface::vlInitUI(std::unique_ptr<GLFWwindow>& window, ComPtr<ID3D11Device>& device, ComPtr<ID3D11DeviceContext>& context){
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOther(window.get(), true);
    ImGui_ImplDX11_Init(device.Get(), context.Get());
    }

    void UserInterface::vlStageUI(){
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

     if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("GG")) {
				ImGui::Separator();
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void UserInterface::RegisterSettingsCallback(SettingsCallback callback){
		settingsCallbacks_.push_back(callback);
    }

    void UserInterface::vlSyncSettingsCallback(){
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Settings")) {
                for (auto& callback : settingsCallbacks_) {
                    callback();
                }
                ImGui::EndMenu();
            }
			ImGui::EndMenuBar();
        }
    }

    void UserInterface::vlRenderUI() {
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }


    UserInterface::~UserInterface(){
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
