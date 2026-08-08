#include "vlRenderer.h"
#include "imgui.h"

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

void Renderer::vlGenRenderState(){
	rasterizerState = ComPtr<ID3D11RasterizerState>();
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FrontCounterClockwise = FALSE;
	rasterizerDesc.DepthBias = 0;

	ImGui::Text("Rendering mode");
	ImGui::RadioButton("Solid", &Options, RenderStateOptions::Solid);
	ImGui::RadioButton("Wireframe", &Options, RenderStateOptions::Wireframe);
	if (Options == RenderStateOptions::Solid){
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	}
	else if (Options == RenderStateOptions::Wireframe){
		rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
	}
}

void Renderer::Present(){
	swapChain->Present(1, 0);
}

void Renderer::ClearScreen(){
	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	context->ClearRenderTargetView(rtv.Get(), color);
}

void Renderer::vlStageRenderer(){
	if (SUCCEEDED(device->CreateRasterizerState(&rasterizerDesc, rasterizerState.GetAddressOf()))) {
		context->RSSetState(rasterizerState.Get());
	}
}

Renderer::~Renderer(){
}

void Renderer::InitRenderer(ComPtr<ID3D11Device>Device,ComPtr<ID3D11RenderTargetView> Rtv, ComPtr<ID3D11DeviceContext> Context,ComPtr<IDXGISwapChain>Swapchain){
	rtv = Rtv;
	context = Context;
	swapChain = Swapchain;
	device = Device;
}


}

