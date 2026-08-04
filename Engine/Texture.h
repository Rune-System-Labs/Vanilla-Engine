#pragma once

#include <wrl/client.h>

#include <d3d11.h>

class Graphics;

// A tiny procedural texture keeps this learning project self-contained.
// Replace it later with an image loader (WIC, DirectXTK, or stb_image).
class Texture final {
public:
    explicit Texture(const Graphics& graphics);

    [[nodiscard]] ID3D11ShaderResourceView* GetShaderResourceView() const { return shaderResourceView_.Get(); }
    [[nodiscard]] ID3D11SamplerState* GetSamplerState() const { return samplerState_.Get(); }

private:
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState_;
};
