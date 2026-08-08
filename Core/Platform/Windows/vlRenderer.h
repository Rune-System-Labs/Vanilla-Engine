#ifndef VL_RENDERER_H
#define VL_RENDERER_H
#include <d3d11.h>
#include <iostream>
#include <wrl/client.h>
using namespace Microsoft::WRL;

enum RenderStateOptions {
	Solid = 0,
	Wireframe = 1,
};

namespace vl::Platform {
	class Renderer {
	public:
		~Renderer();
		void InitRenderer(ComPtr<ID3D11Device>Device,ComPtr<ID3D11RenderTargetView>Rtv, ComPtr<ID3D11DeviceContext>Context, ComPtr<IDXGISwapChain>Swapchain);
		void vlViewport(const UINT width, const UINT height);
        void vlGenRenderState();
		void Present();
		void ClearScreen();
		void vlStageRenderer();
	private:
		int Options = 0;
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		ComPtr<ID3D11RenderTargetView>rtv;
		ComPtr<ID3D11DeviceContext>context;
		ComPtr<IDXGISwapChain> swapChain;
		ComPtr<ID3D11Device>device;
		ComPtr<ID3D11RasterizerState> rasterizerState;
	};
}

#endif // VL_RENDERER_H
