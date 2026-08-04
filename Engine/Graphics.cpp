#include "Graphics.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <stdexcept>

Graphics::Graphics(GLFWwindow* window, const std::uint32_t width, const std::uint32_t height)
    : window_(window), width_(width), height_(height) {
    if (window_ == nullptr) {
        throw std::runtime_error("Graphics needs a valid window.");
    }

    DXGI_SWAP_CHAIN_DESC swapChainDescription{};
    swapChainDescription.BufferCount = 1;
    swapChainDescription.BufferDesc.Width = width_;
    swapChainDescription.BufferDesc.Height = height_;
    swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDescription.SampleDesc.Count = 1;
    swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescription.OutputWindow = glfwGetWin32Window(window_);
    swapChainDescription.Windowed = TRUE;

    const HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        nullptr, 0, D3D11_SDK_VERSION, &swapChainDescription, &swapChain_, &device_, nullptr, &context_);
    if (FAILED(result)) {
        throw std::runtime_error("Could not create the Direct3D 11 device and swap chain.");
    }

    CreateRenderTargets();
    CreatePipelineState();
}

void Graphics::CreateRenderTargets() {
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    if (FAILED(swapChain_->GetBuffer(0, IID_PPV_ARGS(&backBuffer))) ||
        FAILED(device_->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView_))) {
        throw std::runtime_error("Could not create the render target view.");
    }

    D3D11_TEXTURE2D_DESC depthDescription{};
    depthDescription.Width = width_;
    depthDescription.Height = height_;
    depthDescription.MipLevels = 1;
    depthDescription.ArraySize = 1;
    depthDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDescription.SampleDesc.Count = 1;
    depthDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    if (FAILED(device_->CreateTexture2D(&depthDescription, nullptr, &depthStencilTexture_)) ||
        FAILED(device_->CreateDepthStencilView(depthStencilTexture_.Get(), nullptr, &depthStencilView_))) {
        throw std::runtime_error("Could not create the depth-stencil buffer.");
    }

    ID3D11RenderTargetView* target = renderTargetView_.Get();
    context_->OMSetRenderTargets(1, &target, depthStencilView_.Get());

    D3D11_VIEWPORT viewport{};
    viewport.Width = static_cast<float>(width_);
    viewport.Height = static_cast<float>(height_);
    viewport.MaxDepth = 1.0f;
    context_->RSSetViewports(1, &viewport);
}

void Graphics::CreatePipelineState() {
    D3D11_RASTERIZER_DESC rasterizerDescription{};
    rasterizerDescription.FillMode = D3D11_FILL_SOLID;
    rasterizerDescription.CullMode = D3D11_CULL_BACK;
    rasterizerDescription.DepthClipEnable = TRUE;
    if (FAILED(device_->CreateRasterizerState(&rasterizerDescription, &rasterizerState_))) {
        throw std::runtime_error("Could not create the rasterizer state.");
    }
    context_->RSSetState(rasterizerState_.Get());

    D3D11_DEPTH_STENCIL_DESC depthStencilDescription{};
    depthStencilDescription.DepthEnable = TRUE;
    depthStencilDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDescription.DepthFunc = D3D11_COMPARISON_LESS;
    if (FAILED(device_->CreateDepthStencilState(&depthStencilDescription, &depthStencilState_))) {
        throw std::runtime_error("Could not create the depth-stencil state.");
    }
    context_->OMSetDepthStencilState(depthStencilState_.Get(), 0);
}
