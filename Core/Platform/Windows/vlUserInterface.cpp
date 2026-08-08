#include "vlUserInterface.h"

namespace vl::UI{
    void UserInterface::vlInitUI(GLFWwindow* window, ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> context){
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOther(window, true);
    ImGui_ImplDX11_Init(device.Get(), context.Get());
    }

    void UserInterface::vlStageUI(){
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

     if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("Settings")) {
				ImGui::MenuItem("Open Settings", nullptr, &settingsOpen_);
				ImGui::EndMenu();
			}
            ImGui::EndMainMenuBar();
        }

		if (settingsOpen_) {
			if (ImGui::Begin("Settings", &settingsOpen_, ImGuiWindowFlags_NoCollapse)) {
				ImGui::BeginChild("SettingsNavigation", ImVec2(180.0f, 0.0f), true);
				ImGui::Text("Categories");
				ImGui::Separator();
				if (ImGui::Selectable("Rendering", selectedSettingsPage_ == 0)) {
					selectedSettingsPage_ = 0;
				}
				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginChild("SettingsOptions", ImVec2(0.0f, 0.0f), true);
				if (selectedSettingsPage_ == 0) {
					ImGui::Text("Rendering");
					ImGui::Separator();
					vlSyncSettingsCallback();
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}
    }

    void UserInterface::RegisterSettingsCallback(SettingsCallback callback){
		settingsCallbacks_.push_back(callback);
    }

    void UserInterface::vlSyncSettingsCallback(){
		for (auto& callback : settingsCallbacks_) {
			if (callback) callback();
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
