#ifndef VL_CORE_H
#define VL_CORE_H
#include <iostream>
#include <d3d11.h>
#include <print>
#include <memory>
#include <wrl/client.h>
using namespace Microsoft::WRL;

namespace vl::Platform {
	class Window;
}

namespace vl {
	class Core {
	public:
		Core();
		~Core();
		void VlInitialize();
	private:
		ComPtr<ID3D11Device> device_;
		ComPtr<ID3D11DeviceContext> context_;
		ComPtr<IDXGISwapChain> swapChain_;
		ComPtr<ID3D11RenderTargetView> renderTargetView_;
		std::unique_ptr<vl::Platform::Window> window_;
		HRESULT hr = S_OK;
	};
}







#endif // VL_CORE_H