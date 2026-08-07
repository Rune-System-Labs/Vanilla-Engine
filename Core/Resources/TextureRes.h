#ifndef TEXTURERES_H
#define TEXTURERES_H
#include <iostream>
#include <wrl/client.h>
#include <d3d11.h>
#include <span>
#include <DirectXTex.h>
#include <string_view>
using namespace Microsoft::WRL;

namespace vl::Resources {
    class Texture{
    public:
        template<typename T>
		void vlCreateTextureResource(ComPtr<ID3D11Device>& device,std::span<T>& data,UINT arraysize, ComPtr<ID3D11Texture2D>& tex_, UINT BindFlags, D3D11_USAGE usage);
        ComPtr<ID3D11ShaderResourceView> vlLoadDDS(ComPtr<ID3D11ShaderResourceView>& srv,ComPtr<ID3D11Device>& device, const wchar_t* filename_);
        ComPtr<ID3D11ShaderResourceView> vlLoadWIC(ComPtr<ID3D11ShaderResourceView>& srv, ComPtr<ID3D11Device>& device, const wchar_t* filename_);
        [[nodiscard]] ID3D11ShaderResourceView* GetShaderResourceView() const { return shaderResourceView_.Get(); }
        [[nodiscard]] ID3D11SamplerState* GetSamplerState() const { return samplerState_.Get(); }
    private:
        ComPtr<ID3D11ShaderResourceView> shaderResourceView_;
        ComPtr<ID3D11SamplerState> samplerState_;
        HRESULT hr = S_OK;
    };
    template<typename T>
    inline void Texture::vlCreateTextureResource(ComPtr<ID3D11Device>& device, std::span<T>& data,UINT arraysize,ComPtr<ID3D11Texture2D>&tex_,UINT BindFlags,D3D11_USAGE usage){
        D3D11_TEXTURE2D_DESC Texdescription{};
        Texdescription.MipLevels = -1;
        Texdescription.ArraySize = arraysize;;
        Texdescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        Texdescription.SampleDesc.Count = 1;
        Texdescription.Usage = usage;
        Texdescription.BindFlags = BindFlags;

        D3D11_SUBRESOURCE_DATA Initdata{};
        Initdata.pSysMem = data.data();
        Initdata.SysMemPitch = data.size() * sizeof(T);

        if (Initdata.pSysMem == nullptr) {
            device->CreateTexture2D(&description, nullptr, tex_.GetAddressOf());
        }
        else{
            device->CreateTexture2D(&description, &Initdata, tex_.GetAddressOf());
        }
    }
}

#endif // TEXTURERES_H
