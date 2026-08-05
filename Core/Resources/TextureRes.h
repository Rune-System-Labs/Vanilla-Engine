#ifndef TEXTURERES_H
#define TEXTURERES_H
#include <iostream>
#include <wrl/client.h>
#include <d3d11.h>
#include <span>
#include <DirectXTex.h>
using namespace Microsoft::WRL;

namespace vl::Resources {
    class Texture{
    public:
        template<typename T>
		void vlCreateTextureResource(ComPtr<ID3D11Device>& device,std::span<T>& data,UINT arraysize, ComPtr<ID3D11Texture2D>& tex_, UINT BindFlags, D3D11_USAGE usage);
        void vlLoadDDS(DirectX::ScratchImage image, DirectX::DDSMetaData metadata);
        [[nodiscard]] ID3D11ShaderResourceView* GetShaderResourceView() const { return shaderResourceView_.Get(); }
        [[nodiscard]] ID3D11SamplerState* GetSamplerState() const { return samplerState_.Get(); }
    private:
        ComPtr<ID3D11ShaderResourceView> shaderResourceView_;
        ComPtr<ID3D11SamplerState> samplerState_;
    };
    template<typename T>
    inline void Texture::vlCreateTextureResource(ComPtr<ID3D11Device>& device, std::span<T>& data,UINT arraysize,ComPtr<ID3D11Texture2D>&tex_,UINT BindFlags,D3D11_USAGE usage){
        D3D11_TEXTURE2D_DESC description{};
        description.MipLevels = -1;
        description.ArraySize = arraysize;;
        description.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        description.SampleDesc.Count = 1;
        description.Usage = usage;
        description.BindFlags = BindFlags;

        D3D11_SUBRESOURCE_DATA Initdata{};
        Initdata.pSysMem = data.data();
        Initdata.SysMemPitch = data.size() * sizeof(std::uint32_t);

        if (Initdata.pSysMem == nullptr) {
            device->CreateTexture2D(&description, nullptr, tex_.GetAddressOf());
        }
        else{
            device->CreateTexture2D(&description, &Initdata, tex_.GetAddressOf());
        }
    }
}

#endif TEXTURERES_H
