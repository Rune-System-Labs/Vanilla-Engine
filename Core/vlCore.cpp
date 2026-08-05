#include "vlCore.h"
#include "Platform/Windows/vlWindow.h"

namespace vl {
	Core::Core()
	{
	}
	void Core::VlInitialize(vl::Platform::Window& window) {
		device_ = ComPtr<ID3D11Device>();
		context_ = ComPtr<ID3D11DeviceContext>();
		swapChain_ = ComPtr<IDXGISwapChain>();
		renderTargetView_ = ComPtr<ID3D11RenderTargetView>();

		HWND hwnd = glfwGetWin32Window(window.GetHandle());

		DXGI_SWAP_CHAIN_DESC scd = {};
		scd.BufferCount = 1;
		scd.BufferDesc.Width = window.Width();
		scd.BufferDesc.Height = window.Height();
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.SampleDesc.Count = 1;
		scd.Windowed = TRUE;
		scd.OutputWindow = hwnd;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;

		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&scd,
			swapChain_.GetAddressOf(),
			device_.GetAddressOf(),
			nullptr,
			context_.GetAddressOf()
		);

		ComPtr<ID3D11Texture2D>backBuffer = ComPtr<ID3D11Texture2D>();
		HRESULT hr = swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

		if (backBuffer) {
			hr = device_->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView_.GetAddressOf());
			if (FAILED(hr)) {
				std::cerr << "VL::Could not create RTV!" << hr << std::endl;
				return;
			}
		}

		context_->OMSetRenderTargets(
			1,
			renderTargetView_.GetAddressOf(),
			nullptr
		);
	}

	Core::~Core()
	{
		std::println("VL::Core Resources Released");
	}
}
