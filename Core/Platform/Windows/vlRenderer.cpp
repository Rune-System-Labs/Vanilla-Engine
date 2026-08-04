#include "vlRenderer.h"

namespace vl::Platform {
void Renderer::vlViewport(const UINT width, const UINT height) {
		D3D11_VIEWPORT viewport;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = static_cast<FLOAT>(width);
		viewport.Height = static_cast<FLOAT>(height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		context->RSSetViewports(1, &viewport);
}

void Renderer::Present(){
	swapChain->Present(1, 0);
}

void Renderer::InitRenderer(ComPtr<ID3D11RenderTargetView> Rtv, ComPtr<ID3D11DeviceContext> Context,ComPtr<IDXGISwapChain>Swapchain){
	rtv = Rtv;
	context = Context;
	swapChain = Swapchain;
}


}

