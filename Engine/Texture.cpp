#include "Texture.h"

#include "Graphics.h"

#include <array>
#include <cstdint>
#include <stdexcept>

Texture::Texture(const Graphics& graphics) {
    // RGBA pixels: red, yellow, blue, white. This proves the texture pipeline works.
    constexpr std::array<std::uint32_t, 4> pixels = { 0xFF3030FF, 0xFF30E0FF, 0xFFFF7030, 0xFFFFFFFF };

    D3D11_TEXTURE2D_DESC description{};
    description.Width = 2;
    description.Height = 2;
    description.MipLevels = 1;
    description.ArraySize = 1;
    description.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    description.SampleDesc.Count = 1;
    description.Usage = D3D11_USAGE_DEFAULT;
    description.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA data{};
    data.pSysMem = pixels.data();
    data.SysMemPitch = 2 * sizeof(std::uint32_t);

    if (FAILED(graphics.GetDevice()->CreateTexture2D(&description, &data, &texture_)) ||
        FAILED(graphics.GetDevice()->CreateShaderResourceView(texture_.Get(), nullptr, &shaderResourceView_))) {
        throw std::runtime_error("Could not create the checkerboard texture.");
    }

    D3D11_SAMPLER_DESC samplerDescription{};
    samplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDescription.MaxLOD = D3D11_FLOAT32_MAX;
    if (FAILED(graphics.GetDevice()->CreateSamplerState(&samplerDescription, &samplerState_))) {
        throw std::runtime_error("Could not create the texture sampler.");
    }
}
