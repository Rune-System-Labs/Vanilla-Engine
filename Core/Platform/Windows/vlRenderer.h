#ifndef VL_RENDERER_H
#define VL_RENDERER_H
#include <d3d11.h>
#include <iostream>
#include <wrl/client.h>
using namespace Microsoft::WRL;

namespace vl::Platform {
	class Renderer {
	public:
		void InitRenderer(ComPtr<ID3D11RenderTargetView>Rtv, ComPtr<ID3D11DeviceContext>Context, ComPtr<IDXGISwapChain>Swapchain);
		void vlViewport(const UINT width, const UINT height);
        void vlGenRenderState();
		void Present();
	private:
		ComPtr<ID3D11RenderTargetView>rtv;
		ComPtr<ID3D11DeviceContext>context;
		ComPtr<IDXGISwapChain> swapChain;
	};
}

#endif // VL_RENDERER_H
