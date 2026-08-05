#ifndef VL_USERINTERFACE_H
#define VL_USERINTERFACE_H
#include <d3d11.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <wrl/client.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_glfw.h>
#include <functional>
#include <iostream>
#include <vector>
using namespace Microsoft::WRL;

namespace vl::UI {
	class UserInterface {
	public:
		UserInterface() = default;
		~UserInterface();
		using SettingsCallback = std::function<void()>;
		void vlInitUI(std::unique_ptr<GLFWwindow>window, ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext>context);
		void vlStageUI();
		void RegisterSettingsCallback(SettingsCallback callback);
		void vlRenderUI();
	private:
		void vlSyncSettingsCallback();
		bool initialized_ = false;
		std::vector<SettingsCallback> settingsCallbacks_;
	};
}






#endif // VL_USERINTERFACE_H
