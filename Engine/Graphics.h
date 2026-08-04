#pragma once

#include <cstdint>
#include <wrl/client.h>

#include <d3d11.h>

struct GLFWwindow;

class Graphics final {
public:
    Graphics(GLFWwindow* window, std::uint32_t width, std::uint32_t height);

    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;

    [[nodiscard]] ID3D11Device* GetDevice() const { return device_.Get(); }
    [[nodiscard]] ID3D11DeviceContext* GetContext() const { return context_.Get(); }
    [[nodiscard]] GLFWwindow* GetWindow() const { return window_; }
    [[nodiscard]] IDXGISwapChain* GetSwapChain() const { return swapChain_.Get(); }
    [[nodiscard]] ID3D11RenderTargetView* GetRenderTargetView() const { return renderTargetView_.Get(); }
    [[nodiscard]] ID3D11DepthStencilView* GetDepthStencilView() const { return depthStencilView_.Get(); }
    [[nodiscard]] ID3D11DepthStencilState* GetDepthStencilState() const { return depthStencilState_.Get(); }
    [[nodiscard]] float AspectRatio() const { return static_cast<float>(width_) / static_cast<float>(height_); }

private:
    void CreateRenderTargets();
    void CreatePipelineState();

    GLFWwindow* window_ = nullptr;
    std::uint32_t width_ = 0;
    std::uint32_t height_ = 0;
    Microsoft::WRL::ComPtr<ID3D11Device> device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView_;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilTexture_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView_;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState_;
};
